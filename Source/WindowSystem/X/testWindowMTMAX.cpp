
// An early example showing how to do multi-threaded rendering in X
// 

#include <OSGConfig.h>

#include <iostream>

#include <GL/glx.h>

#include <OSGFieldContainerFactory.h>
#include <OSGSFSysTypes.h>
#include <OSGVector.h>
#include <OSGQuaternion.h>
#include <OSGMatrix.h>
#include <OSGMatrixUtility.h>
#include <OSGBoxVolume.h>
#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGSimpleGeometry.h>
#include <OSGThread.h>
#include <OSGThreadManager.h>
#include <OSGTime.h>
#include <OSGTransform.h>
#include <OSGAttachment.h>
#include <OSGMFVecTypes.h>
#include <OSGAction.h>
#include <OSGRenderAction.h>
#include <OSGSceneFileHandler.h>
#include <OSGDirectionalLight.h>

#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGXWindow.h"
#include "OSGCamera.h"
#include "OSGPerspectiveCamera.h"
#include "OSGSolidBackground.h"

#include "OSGTrackball.h"

using namespace OSG;

#define MAX_THREADS 6

UInt16 usedThreads=0;

ThreadManager *gThreadManager;
Thread        *drawThread[MAX_THREADS];

UInt32        drawThreadID[MAX_THREADS];

bool          stopIt = false;
        
XWindowPtr    win[MAX_THREADS];

// GLX Stuff

static int    snglBuf[] = {GLX_RGBA, GLX_DEPTH_SIZE, 1, None};
static int    dblBuf[] = {GLX_RGBA, GLX_DEPTH_SIZE, 1, GLX_DOUBLEBUFFER, None};

Display       *dpy [MAX_THREADS];

::Window      hwin [MAX_THREADS];
GLboolean     doubleBuffer = GL_FALSE;

XVisualInfo   *vi;

Colormap      cmap;
GLXContext    cx [MAX_THREADS];
XEvent        event;
XSetWindowAttributes swa;

RenderAction     *ract[MAX_THREADS];
NodePtr            root;
NodePtr            file;
PerspectiveCameraPtr cam;
ViewportPtr    vp;
TransformPtr   cam_trans;
Trackball      tball;

int            mouseb = 0,
               lastx[MAX_THREADS], 
               lasty[MAX_THREADS];


ThreadBase *mainThread = NULL;
Barrier *syncBarrier = NULL;

volatile bool exiting = false;

#undef FLOG
#if 1
#define FLOG(var) FDEBUG(var)
#else
#define FLOG(var) 
#endif


double  basetime;
#define dpr std::cout << getSystemTime()-basetime << ":" << Thread::getAspect() << ":"

void doCamTrans (UInt32 )
{
    Matrix m1, m2, m3;
    Quaternion q1;

    tball.getRotation().getValue(m3);
    q1.setValue(m3);
    m1.setRotate(q1);
    m2.setTranslate( tball.getPosition() );
    m1.mult( m2 );
    beginEditCP(cam_trans);
    cam_trans->getSFMatrix()->setValue( m1 );
    endEditCP(cam_trans);
}


void drawThreadProc (void *arg) 
{               
    UInt32            my_id = static_cast<Uint32>(arg);
    XWindowPtr my_win = win[my_id];
    
    // give the window some time to open and X to settle down
    // otherwise XFree might crash...
    
    sleep(2+my_id);
    FLOG(( "display::started %d\n", my_id));
    
    my_win->activate();
       
    while ( ! stopIt )
    {
        // dpr << "draw" << std::endl;

        FLOG(( "display::waitSync\n"));
        // notify successful synchronisation
        syncBarrier->enter( usedThreads+1 );
        FLOG(( "display::synced\n"));
        
        my_win->frameInit();
        
        doCamTrans( my_id );
        my_win->renderAllViewports( ract[my_id] );
        
        FLOG(( "display::waitSwap\n"));
        // check for the mainThread to finish its part
        syncBarrier->enter( usedThreads+1 );
        
        my_win->swap();
        my_win->frameExit();

        FLOG(( "display::merge\n"));
        // merge the changes into our aspect
        mainThread->getChangeList()->applyAndClear();
    }
    
    return;
}

int wait_for_map_notify(Display *, XEvent *event, char *arg)
{
    return( event->type == MapNotify && event->xmap.window == (::Window)arg );
}

int main (int argc, char **argv)
{
    int i,
        eventThread,
        dummy;

    // OSG init
    ChangeList::setReadWriteDefault();
    osgInit(argc, argv);
    basetime = getSystemTime();
    gThreadManager = ThreadManager::the();  

#if 0
    FieldContainerPtr pProto = Geometry::getClassType().getPrototype();
    GeometryPtr pGeoProto = GeometryPtr::dcast(pProto);

    if(pGeoProto != NullFC)
    {
        pGeoProto->setDlistCache(false);
    }
#endif

    // create the graph

    // beacon for camera and light  
    NodePtr b1n = Node::create();
    GroupPtr b1 = Group::create();
    beginEditCP(b1n);
    b1n->setCore( b1 );
    endEditCP(b1n);
    
    // light
    
    NodePtr dlight = Node::create();
    DirectionalLightPtr dl = DirectionalLight::create();

    beginEditCP(dlight);
    dlight->setCore( dl );
    endEditCP(dlight);
    
    beginEditCP(dl);
    dl->setAmbient( .3, .3, .3, 1 );
    dl->setDiffuse( 1, 1, 1, 1 );
    dl->setDirection(0,0,1);
    dl->setBeacon( b1n);
    endEditCP(dl);

    // root
    root = Node::create();
    GroupPtr gr1 = Group::create();
    beginEditCP(root);
    root->setCore( gr1 );

    // transformation
    
        NodePtr t1n = Node::create();
    TransformPtr t1 = Transform::create();
    beginEditCP(t1n);
    t1n->setCore( t1 );
    t1n->addChild( b1n );
    endEditCP(t1n);

    cam_trans = t1;
    root->addChild( t1n );

    root->addChild( dlight );
    endEditCP(root);

    // Load the file

    NodePtr file = NullFC;
    
    if ( argc > 1 )
    {
        file = SceneFileHandler::the().read(argv[1]);
        argc--, argv++;
    }
    
    if ( file == NullFC )
    {
        std::cerr << "Couldn't load file, ignoring" << std::endl;
        file = makeTorus( .5, 2, 16, 16 );
    }
    
    file->updateVolume();

    Vec3f min,max;
    file->getVolume().getBounds( min, max );
    
    std::cout << "Volume: from " << min << " to " << max << std::endl;

    beginEditCP(dlight);
    dlight->addChild( file );
    endEditCP(dlight);

    // Background
    SolidBackgroundPtr bkgnd = SolidBackground::create();

    // set up some default windows, if none given
    
    if(argc < 2)
    {
        static char *defarg[] = { "testWindowMTX", NULL, NULL };
        argc = 3;
        argv = defarg;       
    }
    
    // tball

    Vec3f pos( 0, 0, max[2] + ( max[2] - min[2] ) * 1.5 );
    
    tball.setMode( Trackball::OSGObject );
    tball.setStartPosition( pos, true );
    tball.setSum( true );
    tball.setTranslationMode( Trackball::OSGFree );

    // Camera
    cam = PerspectiveCamera::create();
    beginEditCP(cam);
    cam->setBeacon( (*(cam_trans->getMFParents()))[0] );
    cam->setFov( deg2rad( 60 ) );
    cam->setNear( 0.1 );
    cam->setFar( 10000 );
    endEditCP  (cam);

    // X init

    // Create Windows
    
    usedThreads = argc - 1;
    
    for ( i = 0; i < usedThreads; i++ )
    {   
        // Create a Window and connect it to the main display dpy
        dpy[i] = XOpenDisplay(argv[i+1]);

        if (dpy[i] == NULL) 
        {
            std::cerr << "Error: Could not open display!" << std::endl;
        }

        if(!glXQueryExtension(dpy[i], &dummy, &dummy))
        {
            std::cerr << "Error: X server has no OpenGL GLX extension" << std::endl;
        }

        vi = glXChooseVisual(dpy[i], DefaultScreen(dpy[i]), dblBuf);
        if ( vi == NULL ) 
        {

           vi = glXChooseVisual(dpy[i], DefaultScreen(dpy[i]), snglBuf);
           if (vi == NULL)
           {
               std::cerr << "no RGB visual with depth buffer" << std::endl;
           }

           doubleBuffer = GL_FALSE;
        }
        if (vi->c_class != TrueColor)
        {
            std::cerr << "TrueColor visual required for this program" << std::endl;
        }

        cmap = XCreateColormap(dpy[i], RootWindow(dpy[i], vi->screen), vi->visual, AllocNone);
        swa.colormap = cmap;
        swa.border_pixel = 0;
        swa.event_mask = ExposureMask | 
                         ButtonPressMask | 
                         ButtonReleaseMask |
                         KeyPressMask |
                         Button1MotionMask |
                         Button2MotionMask |
                         Button3MotionMask | 
                         StructureNotifyMask;
            
        hwin[i] = XCreateWindow(dpy[i], RootWindow(dpy[i], vi->screen), 0, 0, 300, 300, 0, vi->depth,
                                InputOutput, vi->visual, CWBorderPixel | CWColormap | CWEventMask, &swa);
        XSetStandardProperties(dpy[i], hwin[i], "testWindowX", "testWindowX", None, argv, argc, NULL);
        
        XMapWindow(dpy[i], hwin[i]);
        XIfEvent(dpy[i], &event, wait_for_map_notify, (char *)hwin[i]);

        win[i] = XWindow::create();
        beginEditCP(win[i], XWindow::DisplayFieldMask|
                            XWindow::WindowFieldMask|
                            OSG::Window::PortFieldMask);
        win[i]->setDisplay ( dpy[i] );
        win[i]->setWindow ( hwin[i] );
        win[i]->init();
        win[i]->deactivate();
      
        // Viewport
    
        ViewportPtr vp = Viewport::create();
        beginEditCP(vp);
        vp->setCamera( cam );
        vp->setBackground( bkgnd );
        vp->setRoot( root );
        vp->setSize( 0,0, 1,1 );
        endEditCP(vp);
        win[i]->addPort( vp );          
        endEditCP  (win[i], XWindow::DisplayFieldMask|
                            XWindow::WindowFieldMask|
                            OSG::Window::PortFieldMask);


        lastx[i] = 0;
        lasty[i] = 0;
    
        // Action
    
        ract[i] = RenderAction::create();
    }
    
    mainThread = Thread::getCurrent();
    
    // create the barrier
    syncBarrier = Barrier::get(NULL);

    // Populate the drawers' aspect

    fprintf(stderr, "WARNING WARNING WARNING\n");
    fprintf(stderr, "Must be fixed, does not run (GV)\n");

    //Thread::getCurrent()->getChangeList()->applyTo(1);
    //Thread::getCurrent()->getChangeList()->clearAll();
     
    for (i = 0; i < usedThreads; i++)
    {               
        // get new thread
        drawThread[i] = 
            dynamic_cast<Thread *>(gThreadManager->getThread(NULL));
        if ( drawThread[i] != NULL )   // and spin it ...
        {      
            drawThread[i]->runFunction( drawThreadProc, 1, (void *)i );
        }
    }

    // main loop ( event dispatching )
    Real32 w,h,a,b,c,d;
    
    while ( !stopIt ) 
    {          
        FLOG(( "main::waitMerge\n"));
        // wait for drawer to finish drawing
        syncBarrier->enter(usedThreads + 1);
        
        FLOG(( "main::merged\n"));
        mainThread->getChangeList()->clearAll();

        for (int i=0;i<usedThreads;i++)
        {
            while ( XPending(dpy[i]) )
            {
                XNextEvent(dpy[i], &event);

                eventThread = i;

                // dpr << "for thread " << eventThread << " ... ";

                switch (event.type) 
                {
                    case KeyPress:           
                        //  << "Key pressed: " << event.xkey.keycode << std::endl;
                        switch ( event.xkey.keycode ) 
                        {
                            case 16: 
                                stopIt = true;
                                break;
                        }
                        break;

                    case ButtonPress:
                        // std::cout << "Button pressed: " << event.xbutton.button << std::endl;                 
                        switch ( event.xbutton.button ) 
                        {                       
                            case 2:
                                tball.setAutoPosition(true);
                                break;
                            case 3:
                                tball.setAutoPositionNeg(true);
                        }
                        lastx[eventThread] = event.xbutton.x;
                        lasty[eventThread] = event.xbutton.y;
                        break;

                    case ButtonRelease:
                        // std::cout << "Button released: " << event.xbutton.button << std::endl;                    
                        switch ( event.xbutton.button ) 
                        {                       
                            case 2:
                                tball.setAutoPosition(false); 
                                break;
                            case 3:
                                tball.setAutoPositionNeg(false);
                        }
                        lastx[eventThread] = event.xbutton.x;
                        lasty[eventThread] = event.xbutton.y;
                        break;

                    case MotionNotify:
                        // std::cout << "MotionNotify" << std::endl;

                        w = win[eventThread]->getWidth();
                        h = win[eventThread]->getHeight();
                        a = -2. * ( lastx[eventThread] / w - .5 );
                        b = -2. * ( .5 - lasty[eventThread] / h );
                        c = -2. * ( event.xmotion.x / w - .5 );
                        d = -2. * ( .5 - event.xmotion.y / h );

                        if ( event.xmotion.state & Button1MotionMask )
                        {
                            tball.updateRotation( a, b, c, d );
                        }
                        if ( event.xmotion.state & Button2MotionMask )
                        {
                            tball.updatePosition( a, b, c, d );
                        }
                        if ( event.xmotion.state & Button3MotionMask )
                        {
                            tball.updatePositionNeg( a, b, c, d );
                        }
                        lastx[eventThread] = event.xmotion.x;
                        lasty[eventThread] = event.xmotion.y;
                        break;

                    case ConfigureNotify:
                        // std::cout << "ConfigureNotify" << std::endl;
                        //if ( ! win[eventThread]->isResizePending() )
                        {
                            win[eventThread]->resize( event.xconfigure.width,
                                                      event.xconfigure.height );
                        }                

                    default: //std::cout << "unhandled" << std::endl;
                             break;
                } // switch event.type
            } // while pending
        } // thread loop

        FLOG(( "main::waitSwap\n"));
        // wait for drawer to finish synchronization
        syncBarrier->enter(usedThreads + 1);
        FLOG(( "main::synced\n"));
        
        if(stopIt)
            break;
    }
     
    for ( i=0; i<usedThreads; i++ )
    {
        Thread::join( drawThread[i] );
    }

    return (0);
}
