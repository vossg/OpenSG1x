#include <OSGConfig.h>

#include <iostream>

#include <GL/glx.h>
#include <X11/keysym.h>
#include <OSGThread.h>
#include <OSGThreadManager.h>
#include <OSGRenderAction.h>
#include <OSGSceneFileHandler.h>
#include <OSGViewport.h>
#include <OSGCamera.h>
#include <OSGWindow.h>
#include <OSGXWindow.h>
#include <OSGCamera.h>
#include <OSGTransform.h>
#include <OSGGroup.h>
#include <OSGDirectionalLight.h>
#include <OSGPerspectiveCamera.h>
#include <OSGSolidBackground.h>
#include <OSGTrackball.h>
#include <OSGSimpleGeometry.h>
#include <OSGTileLoadBalancer.h>
#include <OSGTileCameraDecorator.h>

using namespace OSG;

struct WinInfo {
    std::string         dpyName;
    Display       *dpy;
    ::Window       hwin;
    XWindowPtr     win;
    ThreadBase    *thread;
    int            tile;
};
std::vector<std::string>    files;
std::vector<WinInfo>        windowList;
NodePtr                     root;
PerspectiveCameraPtr        cam;
TransformPtr                camTrans;
Trackball                   tball;
SolidBackgroundPtr          bkgnd;
int                         lastx;
int                         lasty;
ThreadBase                 *mainThread  = NULL;
Barrier                    *syncBarrier = NULL;
Barrier                    *swapBarrier = NULL;
ThreadBase                 *syncThread;
int                         syncCount;
int                         swapCount;
bool                        doRun=true;
bool                        fullscreen=false;
int                         width=0;
int                         height=0;
TileLoadBalancer           *tileLoadBalancer;
TileLoadBalancer::ResultT   region;
XWindowPtr                  mainWindow;

void readArgs(int argc,char **argv)
{
    char  option;
    char *value;
    int   valueSkip;

    for(int a=1;a<argc;a++)
    {
        option=' ';
        value ="";
        if(argv[a][0]=='-')
        {
            option=argv[a][1];
            if(strlen(argv[a])>2)
            {
                value=argv[a]+2;
                valueSkip=0;
            }
            else
                if((a+1)<argc)
                {
                    value=argv[a+1];
                    valueSkip=1;
                }
            switch(option)
            {
                case 'd':
                    if(value)
                    {
                        WinInfo winInfo;
                        winInfo.dpyName=value;
                        windowList.push_back(winInfo);
                        a+=valueSkip;
                    }
                    break;
                case 'f':
                    fullscreen=true;
                    break;
                case 'h':
                    std::cout << argv[0] << " " 
                              << "file ... -d display -d display ... -f "
                              << std::endl;
                    std::cout << "-d Display   e.g :0 or xyz:1.0" << std::endl;
                    std::cout << "-f           fullscreen" << std::endl;
                    exit(0);
            }
        }
        else
        {
            files.push_back(argv[a]);
        }
    }
}

int waitMapNotify(Display *, XEvent *event, char *arg)
{
    return( event->type == MapNotify && event->xmap.window == (::Window)arg );
}

void openWindows(int argc,char **argv)
{
    int dummy;
    int dblBuf[] = {GLX_RGBA, 
                    GLX_DEPTH_SIZE, 1, 
                    GLX_DOUBLEBUFFER, 
                    None};
    XVisualInfo          *vi;
    Colormap             cmap;
    XSetWindowAttributes swa;
    XEvent               event;
    RenderNode           rn;
    int                  tile=0;

    // create default window
    if(windowList.size()==0)
    {
        WinInfo winInfo;
        winInfo.dpyName=":0";
        windowList.push_back(winInfo);
    }                

    for(std::vector<WinInfo>::iterator w=windowList.begin();
        w!=windowList.end();
        ++w)
    {
        w->dpy = XOpenDisplay(w->dpyName.c_str());
        if (w->dpy == NULL) 
        {
            std::cerr << "Error: Could not open display:" 
                 << w->dpyName << std::endl;
            exit(0);
        }
        if(!glXQueryExtension(w->dpy, &dummy, &dummy))
        {
            std::cerr << "Error: X server has no OpenGL GLX extension:" 
                 << w->dpyName << std::endl;
            exit(0);
        }
        vi = glXChooseVisual(w->dpy, DefaultScreen(w->dpy), dblBuf);
        if ( vi == NULL ) 
        {
            std::cerr << "no RGB visual with depth buffer"
                 << w->dpyName << std::endl;
            exit(0);
        }
        cmap = XCreateColormap(w->dpy, 
                               RootWindow(w->dpy,vi->screen), 
                               vi->visual, AllocNone);
        swa.colormap = cmap;
        swa.border_pixel = 0;
        swa.event_mask = 
            ExposureMask | 
            ButtonPressMask | 
            ButtonReleaseMask |
            KeyPressMask |
            Button1MotionMask |
            Button2MotionMask |
            Button3MotionMask | 
            StructureNotifyMask;
        if(fullscreen)
        {
            swa.override_redirect = 1; 
            if(!width)
                width=DisplayWidth  (w->dpy, vi->screen);
            if(!height)
                height=DisplayHeight(w->dpy, vi->screen);
        }
        else
        {
            if(!width)
                width=400;
            if(!height)
                height=400;
            swa.override_redirect = 0; 
        }
        w->hwin = XCreateWindow(w->dpy,
                                RootWindow(w->dpy,
                                           vi->screen),
                                0, 0, width, height, 0,
                                vi->depth,
                                InputOutput, 
                                vi->visual, 
                                CWBorderPixel | CWColormap | 
                                CWEventMask | CWOverrideRedirect,
                                &swa);

        XSetStandardProperties(w->dpy, w->hwin, 
                               "testWindowX", "testWindowX", None,
                               argv, argc, NULL);
        
        XMapWindow(w->dpy, w->hwin);
        XIfEvent(w->dpy, &event, waitMapNotify, (char *)w->hwin);
        XSetInputFocus(w->dpy, w->hwin, RevertToParent, CurrentTime);

        w->win = XWindow::create();
        beginEditCP(w->win, 
                    XWindow::DisplayFieldMask|
                    XWindow::WindowFieldMask|
                    OSG::Window::PortFieldMask);
        w->win->setDisplay ( w->dpy );
        w->win->setWindow ( w->hwin );
        w->win->init();
        w->win->activate();
        rn.determinePerformance(w->win);
        w->tile=tile++;
        tileLoadBalancer->addRenderNode(rn,w->tile);
        w->win->deactivate();
        w->win->resize(width,height);

        // Viewport
    
        ViewportPtr vp = Viewport::create();
        TileCameraDecoratorPtr deco=TileCameraDecorator::create();
        beginEditCP(vp);
        beginEditCP(deco);
        deco->setFullWidth ( width );
        deco->setFullHeight( height );
        deco->setDecoratee( cam );
        deco->setSize( 0,0, 1,1 );
        vp->setCamera( deco );
        vp->setBackground( bkgnd );
        vp->setRoot( root );
        vp->setSize( 0,0, 1,1 );
        endEditCP(vp);
        endEditCP(deco);
        w->win->addPort( vp );          
        endEditCP  (w->win,
                    XWindow::DisplayFieldMask|
                    XWindow::WindowFieldMask|
                    OSG::Window::PortFieldMask);

    }

    // create window with main viewport
    mainWindow = XWindow::create();
    beginEditCP(mainWindow);
    mainWindow->resize(width,height);
    // Viewport
    ViewportPtr vp = Viewport::create();
    beginEditCP(vp);
    vp->setCamera( cam );
    vp->setBackground( bkgnd );
    vp->setRoot( root );
    vp->setSize( 0,0, 1,1 );
    endEditCP(vp);
    mainWindow->addPort( vp );          
    endEditCP  (mainWindow);

}

void handleWindows()
{
    XEvent       event;
    char         buffer[31];
    KeySym       keysym;
    Real32       width,height,a,b,c,d;

    for(std::vector<WinInfo>::iterator w=windowList.begin();
        w!=windowList.end();
        ++w)
    {
        while ( XPending(w->dpy) )
        {
            XNextEvent(w->dpy, &event);
            switch (event.type) 
            {
                case KeyPress:           
                    XLookupString(&event.xkey, buffer, 30, &keysym, NULL);
                    switch ( keysym ) 
                    {
                        case XK_Escape: 
                            doRun=false;
                            exit(0);
                            break;
                    }
                case ButtonPress:
                    switch ( event.xbutton.button ) 
                    {                       
                        case 2:
                            tball.setAutoPosition(true);
                            break;
                        case 3:
                            tball.setAutoPositionNeg(true);
                    }
                    lastx = event.xbutton.x;
                    lasty = event.xbutton.y;
                    break;
                case ButtonRelease:
                    switch ( event.xbutton.button ) 
                    {                       
                        case 2:
                            tball.setAutoPosition(false); 
                            break;
                        case 3:
                            tball.setAutoPositionNeg(false);
                    }
                    lastx = event.xbutton.x;
                    lasty = event.xbutton.y;
                    break;
                case MotionNotify:
                    width  = w->win->getWidth();
                    height = w->win->getHeight();
                    a = -2. * ( lastx / width - .5 );
                    b = -2. * ( .5 - lasty / height );
                    c = -2. * ( event.xmotion.x / width - .5 );
                    d = -2. * ( .5 - event.xmotion.y / height );
                    
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
                    lastx = event.xmotion.x;
                    lasty = event.xmotion.y;
                    break;
                case ConfigureNotify:
                {
                    w->win->resize( event.xconfigure.width,
                                    event.xconfigure.height );
                }                
                default:
                    break;
            } 
        } 
    }
}

void createGraph()
{
    int i;

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

    camTrans = t1;
    root->addChild( t1n );
    
    root->addChild( dlight );
    endEditCP(root);
    
    // Load the file
    NodePtr fileGroupNode=Node::create();
    GroupPtr fileGroup=Group::create();
    beginEditCP(fileGroupNode);
    beginEditCP(fileGroup);
    fileGroupNode->setCore(fileGroup);

    NodePtr file = NullFC;
    
    for(i=0;i<files.size();++i)
    {
        file = SceneFileHandler::the().read(files[i].c_str());
        if(file!=NullFC)
        {
            file->updateVolume();
            fileGroupNode->addChild(file);
        }
    }

    if ( files.size()==0 )
    {
        file = makeTorus( .5, 2, 16, 16 );
        file->updateVolume();
        fileGroupNode->addChild(file);
    }
    
    fileGroupNode->updateVolume();

    endEditCP(fileGroupNode);
    endEditCP(fileGroup);

    Vec3f min,max;
    fileGroupNode->getVolume().getBounds( min, max );
    
    std::cout << "Volume: from " << min << " to " << max << std::endl;

    beginEditCP(dlight);
    dlight->addChild( fileGroupNode );
    endEditCP(dlight);

    // Background
    bkgnd = SolidBackground::create();
    
    // tball

    Vec3f pos( 0, 0, max[2] + ( max[2] - min[2] ) * 1.5 );
    
    tball.setMode( Trackball::OSGObject );
    tball.setStartPosition( pos, true );
    tball.setSum( true );
    tball.setTranslationMode( Trackball::OSGFree );

    // Camera
    cam = PerspectiveCamera::create();
    beginEditCP(cam);
    cam->setBeacon( (*(camTrans->getMFParents()))[0] );
    cam->setFov( deg2rad( 60 ) );
    cam->setNear( 0.1 );
    cam->setFar( 10000 );
    endEditCP  (cam);
}

void drawThreadProc (void *arg) 
{               
    RenderAction *ract = RenderAction::create();
    WinInfo *w=(WinInfo*)arg;
    ViewportPtr vp;
    TileCameraDecoratorPtr deco;

    while(doRun)
    {
        syncBarrier->enter( syncCount );
        syncBarrier->enter( syncCount );
        vp=w->win->getPort(0);
        deco=TileCameraDecoratorPtr::dcast(vp->getCamera());
        beginEditCP(vp);
        beginEditCP(deco);

        vp->setSize(region[w->tile].x1,
                    region[w->tile].y1,
                    region[w->tile].x2,
                    region[w->tile].y2);
        if(deco!=NullFC)
        {
            deco->setSize(region[w->tile].x1 / (float)width,
                          region[w->tile].y1 / (float)height,
                          region[w->tile].x2 / (float)width,
                          region[w->tile].y2 / (float)height);
        }

        endEditCP(deco);
        endEditCP(vp);
        w->win->activate();
        glDisable(GL_SCISSOR_TEST);
        glClearColor(0,0,0,0);
        glClear(GL_COLOR_BUFFER_BIT);
        w->win->frameInit();
        w->win->renderAllViewports( ract );
        swapBarrier->enter( swapCount );
        w->win->swap();
        w->win->frameExit();
        w->win->deactivate();
    }
}

void syncThreadProc (void *OSG_CHECK_ARG(arg)) 
{               
    while(doRun)
    {
        syncBarrier->enter( syncCount );

        mainThread->getChangeList()->applyAndClear();
        syncBarrier->enter( syncCount );
    }
}

void startThreads()
{
    // start renderers
    for(std::vector<WinInfo>::iterator w=windowList.begin();
        w!=windowList.end();
        ++w)
    {
        w->thread=
            dynamic_cast<Thread *>(ThreadManager::the()->getThread(NULL));
        if ( w->thread == NULL )   
        {
            std::cerr << "Unable to create thread" << std::endl;
            exit(0);
        }
        w->thread->runFunction( drawThreadProc, 1, (void *)(&(*w)) );
    }
    // start sync thread
    syncThread=
        dynamic_cast<Thread *>(ThreadManager::the()->getThread(NULL));
    if ( syncThread == NULL )   
    {
        std::cerr << "Unable to create syncThread" << std::endl;
        exit(0);
    }
    syncThread->runFunction( syncThreadProc, 1, NULL );
}

void joinThreads()
{
    for(std::vector<WinInfo>::iterator w=windowList.begin();
        w!=windowList.end();
        ++w)
    {
        Thread::join( w->thread );
    }
    Thread::join( syncThread );
}

int main(int argc,char **argv)
{
    TileLoadBalancer::ResultT   localRegion;
    osgInit(argc, argv);
    readArgs(argc,argv);
    tileLoadBalancer=new TileLoadBalancer(false);
    createGraph();
    openWindows(argc,argv);
    mainThread  = Thread::getCurrent();
    syncBarrier = Barrier::get(NULL);
    swapBarrier = Barrier::get(NULL);
    syncCount   = windowList.size()+2;
    swapCount   = windowList.size();
    startThreads();
    
    while(doRun)
    {
        handleWindows();
        beginEditCP(camTrans);
        camTrans->setMatrix( tball.getFullTrackballMatrix() );
        endEditCP(camTrans);
        tileLoadBalancer->update(root);
        tileLoadBalancer->balance(mainWindow->getPort()[0],false,region);
#if 0        
        for(int i=0;i<region.size();i+=4)
        {
            std::cout << "Region: " << i/4 << " ";
            std::cout << region[i+0] << " ";
            std::cout << region[i+1] << " ";
            std::cout << region[i+2] << " ";
            std::cout << region[i+3] << std::endl;
        }
#endif
        syncBarrier->enter( syncCount );
        region=localRegion;
        syncBarrier->enter( syncCount );
        mainThread->getChangeList()->clearAll();
    }

    joinThreads();
}


