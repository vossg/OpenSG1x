
// An early example showing how to do multi-threaded rendering in X
// 
// This is by no means a prototype on how to do it, quite the contrary.
// It only uses one aspect due to some synch problems we're working on,
// so don't do it like this. It's just to prove that it's possible.

#include <OSGConfig.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <GL/glx.h>
#undef Bool

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
#include <OSGFunctors.h>
#include <OSGTime.h>
#include <OSGTransform.h>
#include <OSGAttachment.h>
#include <OSGMFVecTypes.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>
#include <OSGSceneFileHandler.h>
#include <OSGDirectionalLight.h>

#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGXWindow.h"
#include "OSGCamera.h"
#include "OSGPerspectiveCamera.h"
#include "OSGSolidBackground.h"

#if defined(__linux) || ( defined(WIN32) && ! defined(OSG_BUILD_DLL) )
#include "OSGRAWSceneFileType.h"
#endif

#include "OSGTrackball.h"

using namespace OSG;

#define NUM_THREADS 2

ThreadManager *gThreadManager;
Thread  	  *drawThread[NUM_THREADS];

UInt32	      drawThreadID[NUM_THREADS];

Bool          drawThreadStop[NUM_THREADS],
              doResize[NUM_THREADS],
              stopIt = false;
		
XWindowPtr    win[NUM_THREADS];

// GLX Stuff

static int    snglBuf[] = {GLX_RGBA, GLX_DEPTH_SIZE, 1, None};
static int    dblBuf[] = {GLX_RGBA, GLX_DEPTH_SIZE, 1, GLX_DOUBLEBUFFER, None};

Display       *dpy;

::Window      hwin [NUM_THREADS];
GLboolean     doubleBuffer = GL_FALSE;

XVisualInfo   *vi;

Colormap      cmap;
GLXContext    cx [NUM_THREADS];
XEvent        event;
XSetWindowAttributes swa;

DrawAction	   *ract;
NodePtr		   root;
NodePtr		   file;
PerspectiveCameraPtr cam;
ViewportPtr    vp;
TransformPtr   cam_trans;
Trackball	   tball;

int 		   mouseb = 0,
	 		   lastx[NUM_THREADS], 
    		   lasty[NUM_THREADS];

double  basetime;
#define dpr cout << getSystemTime()-basetime << ":" << Thread::getAspect() << ":"

void doCamTrans (UInt32 id)
{
	Matrix m1, m2, m3;
    Quaternion q1;

    tball.getRotation().getValue(m3);
    q1.setValue(m3);
    m1.setRotate(q1);
    m2.setTranslate( tball.getPosition() );
	m1.mult( m2 );
	cam_trans->getSFMatrix()->setValue( m1 );
}


void *drawThreadProc (void *arg) 
{				
  	int		   my_id = (int) arg;
	XWindowPtr my_win = win[my_id];
	
	// give the window some time to open and X to settle down
	// otherwise XFree might crash...
	
	sleep(2+my_id);
	dpr << "drawThead " << my_id << " started." << endl;
	
	my_win->activate();
	
	// do some OpenGL init. Will move into State Chunks later.
	
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	
	while ( ! drawThreadStop[my_id] )
	{
		my_win->frameInit();
		my_win->resizeGL();
		
		doCamTrans( my_id );
		my_win->drawAllViewports( ract );
		
		my_win->swap();
		my_win->frameExit();
	}
	
	// Destroy context
	return ( NULL );
}

int wait_for_map_notify(Display *display, XEvent *event, char *arg)
{
    return( event->type == MapNotify && event->xmap.window == (::Window)arg );
}

int main (int argc, char **argv)
{
    int i,
	    eventThread,
        dummy;

	// OSG init

    osgInit(argc, argv);
    basetime = getSystemTime();
    gThreadManager = ThreadManager::the();	

#ifdef WIN32
    RAWSceneFileType *pR = &(RAWSceneFileType::staticThe());
#endif

    SceneFileHandler::the().print();

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

	NodePtr file = NullNode;
	
	if ( argc > 1 )
		file = SceneFileHandler::the().read(argv[1]);
	
	if ( file == NullNode )
	{
		cerr << "Couldn't load file, ignoring" << endl;
		file = makeTorus( .5, 2, 16, 16 );
	}
	
	file->updateVolume();

	Vec3f min,max;
	file->getVolume().getBounds( min, max );
	
	cout << "Volume: from " << min << " to " << max << endl;

	beginEditCP(dlight);
	dlight->addChild( file );
	endEditCP(dlight);

	cerr << "Tree: " << endl;
	root->dump();

	// Background
	SolidBackgroundPtr bkgnd = SolidBackground::create();
	
	// Action
	
	ract = DrawAction::create();

	// tball

	Vec3f pos( 0, 0, max[2] + ( max[2] - min[2] ) * 1.5 );

	for ( i = 0; i < NUM_THREADS; i++ )
	{
		lastx[i] = 0;
		lasty[i] = 0;
	}
	
	tball.setMode( Trackball::OSGObject );
	tball.setStartPosition( pos, true );
	tball.setSum( true );
	tball.setTranslationMode( Trackball::OSGFree );

	// Camera
	cam = PerspectiveCamera::create();

	cam->setBeacon( cam_trans->getMFParents()->getValue(0) );
	cam->setFov( 60 );
	cam->setNear( 0.1 );
	cam->setFar( 10000 );

	// X init

    dpy = XOpenDisplay(NULL);
    if (dpy == NULL) 
    {
	    cerr << "Error: Could not open display!" << endl;
    }

    if(!glXQueryExtension(dpy, &dummy, &dummy))
	{
        cerr << "Error: X server has no OpenGL GLX extension" << endl;
    }

    vi = glXChooseVisual(dpy, DefaultScreen(dpy), dblBuf);
    if ( vi == NULL ) 
    {

       vi = glXChooseVisual(dpy, DefaultScreen(dpy), snglBuf);
       if (vi == NULL)
       {
  		   cerr << "no RGB visual with depth buffer" << endl;
       }

       doubleBuffer = GL_FALSE;
    }
    if (vi->c_class != TrueColor)
    {
	    cerr << "TrueColor visual required for this program" << endl;
    }

    cmap = XCreateColormap(dpy, RootWindow(dpy, vi->screen), vi->visual, AllocNone);
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

    // Create Windows
    
    for ( i = 0; i < NUM_THREADS; i++ )
    {	
		// Create a Window and connect it to the main display dpy

		hwin[i] = XCreateWindow(dpy, RootWindow(dpy, vi->screen), 0, 0, 300, 300, 0, vi->depth,
								InputOutput, vi->visual, CWBorderPixel | CWColormap | CWEventMask, &swa);
		XSetStandardProperties(dpy, hwin[i], "testWindowX", "testWindowX", None, argv, argc, NULL);
			
		win[i] = XWindow::create();
		win[i]->setDisplay ( dpy );
		win[i]->setWindow ( hwin[i] );
	    win[i]->init();
		
		XMapWindow(dpy, hwin[i]);
		XIfEvent(dpy, &event, wait_for_map_notify, (char *)hwin[i]);
		
		// Viewport
	
		ViewportPtr vp = Viewport::create();
		vp->setCamera( cam );
		vp->setBackground( bkgnd );
		vp->setRoot( root );
		vp->setSize( 0,0, 1,1 );
		win[i]->addPort( vp );			
	}
	
    for (i = 0; i < NUM_THREADS; i++)
    {	    	    
		// reset thread stop/resize notify variables
		drawThreadStop[i] = false;

		// get new thread
		drawThread[i] = 
            dynamic_cast<Thread *>(gThreadManager->getThread(NULL));
		if ( drawThread[i] != NULL )   // and spin it ...
      	{	   
			drawThread[i]->run( drawThreadProc, 0, (void *)i );
		}
    }

	// main loop ( event dispatching )
	Real32 w,h,a,b,c,d;
	
    while ( !stopIt ) 
    {
		do
		{
		    XNextEvent(dpy, &event);
		  		  
		    for (i=0;i<NUM_THREADS;i++)
		    {
			    // Thread's window ID equals event's window ID ?
		        if ( hwin[i] == event.xany.window )
				{
				    eventThread = i;
					break;
				}
		    }		   
						
			dpr << "from thread " << eventThread << " ... ";

			switch (event.type) 
		    {
			    case KeyPress:			 
				    cout << "Key pressed: " << event.xkey.keycode << endl;
					switch ( event.xkey.keycode ) 
					{
					    case 16: 
  						    stopIt = true;
							break;
					}
					break;

			    case ButtonPress:
				    cout << "Button pressed: " << event.xbutton.button << endl;				
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
					cout << "Button released: " << event.xbutton.button << endl;					
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
					cout << "MotionNotify" << endl;
					
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
			        cout << "ConfigureNotify" << endl;
				    if ( ! win[eventThread]->isResizePending() )
					{
					    win[eventThread]->resize( event.xconfigure.width,
												  event.xconfigure.height );
					}				 
					
				default: cout << "unhandled" << endl;
			  }
		}
		while ( XPending(dpy) );

    }
	 
    for ( i=0; i<NUM_THREADS; i++ )
    {
		drawThreadStop[i] = 1;
		Thread::join( drawThread[i] );
    }

    return (0);
}
