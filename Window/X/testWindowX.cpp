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
#include <OSGTransform.h>
#include <OSGAttachment.h>
#include <OSGSimpleGeometry.h>
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

#include "OSGRAWSceneFileType.h"
#include "OSGTrackball.h"

using namespace OSG;

// GLX Stuff

static int    snglBuf[] = {GLX_RGBA, GLX_DEPTH_SIZE, 16, None};
static int    dblBuf[] = {GLX_RGBA, GLX_DEPTH_SIZE, 16, GLX_DOUBLEBUFFER, None};

Display       *dpy;
::Window      hwin;
GLboolean     doubleBuffer = GL_FALSE;

XVisualInfo   *vi;
Colormap      cmap;
XEvent        event;
XSetWindowAttributes swa;

XWindowPtr    win;

DrawAction	  *ract;
NodePtr		  root;
NodePtr		  file;
ViewportPtr   vp;
TransformPtr  cam_trans;
Trackball	  tball;
PerspectiveCameraPtr cam;

Bool          stopIt = false;
int 		  lastx=0, lasty=0;

int wait_for_map_notify(Display *display, XEvent *event, char *arg)
{
    return( event->type == MapNotify && event->xmap.window == (::Window)arg );
}

void redraw ( void )
{
	Matrix m1, m2, m3;
    Quaternion q1;

	win->frameInit();		
	
	win->resizeGL();

    tball.getRotation().getValue(m3);
    q1.setValue(m3);
    m1.setRotate(q1);
    m2.setTranslate( tball.getPosition() );
	m1.mult( m2 );
	cam_trans->getSFMatrix()->setValue( m1 );	
	
	win->drawAllViewports( ract );
	win->swap();
	win->frameExit();		
}

int main (int argc, char **argv)
{
    int dummy;

	// OSG init

    osgInit(argc, argv);

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

	// transformation
    NodePtr t1n = Node::create();
    TransformPtr t1 = Transform::create();
	beginEditCP(t1n);
	t1n->setCore( t1 );
	t1n->addChild( b1n );
	endEditCP(t1n);

	cam_trans = t1;

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

	// Camera
	PerspectiveCameraPtr cam = PerspectiveCamera::create();

	cam->setBeacon( b1n );
	cam->setFov( 60 );
	cam->setNear( 0.1 );
	cam->setFar( 10000 );

	// Background
	SolidBackgroundPtr bkgnd = SolidBackground::create();
	
	// Viewport
	
	ViewportPtr vp = Viewport::create();
	vp->setCamera( cam );
	vp->setBackground( bkgnd );
	vp->setRoot( root );
	vp->setSize( 0,0, 1,1 );

	// Action
	
	ract = DrawAction::create();

	// tball

	Vec3f pos( 0, 0, max[2] + ( max[2] - min[2] ) * 1.5 );

	tball.setMode( Trackball::OSGObject );
	tball.setStartPosition( pos, true );
	tball.setSum( true );
	tball.setTranslationMode( Trackball::OSGFree );

	// X init

    dpy = XOpenDisplay(NULL);
    if (dpy == NULL) 
    {
	    cerr << "Error: Could not open display!" << endl;
    }

    if( ! glXQueryExtension( dpy, &dummy, &dummy ) )
	{
        cerr << "Error: X server has no OpenGL GLX extension" << endl;
    }

    vi = glXChooseVisual( dpy, DefaultScreen(dpy), dblBuf );
    if ( vi == NULL ) 
    {

       vi = glXChooseVisual( dpy, DefaultScreen(dpy), snglBuf );
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

    cmap = XCreateColormap( dpy, 
						    RootWindow(dpy, vi->screen), 
							vi->visual, 
							AllocNone );
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

    // Create Window
    
	// Create a Window and connect it to the main display dpy
	hwin = XCreateWindow( dpy, 
						  RootWindow(dpy, vi->screen), 
						  0, 0, 300, 300, 
						  0, 
						  vi->depth,
						  InputOutput, 
						  vi->visual, 
						  CWBorderPixel | CWColormap | CWEventMask, 
						  &swa );
							
	XSetStandardProperties(dpy, hwin, "testWindowX", "testWindowX", None, argv, argc, NULL);
			
	win = XWindow::create();
	win->addPort( vp );			
	win->setDisplay ( dpy );
	win->setWindow ( hwin );	
    win->init();
		
	XMapWindow(dpy, hwin);
	XIfEvent(dpy, &event, wait_for_map_notify, (char *)hwin);
	
	win->activate();
	
	// do some OpenGL init. Will move into State Chunks later.
	
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );


	// main loop ( event dispatching )

	Real32 w,h,a,b,c,d;
	
    while ( !stopIt ) 
    {
		do
		{
		    XNextEvent(dpy, &event);
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
					lastx = event.xbutton.x;
					lasty = event.xbutton.y;
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
					lastx = event.xbutton.x;
					lasty = event.xbutton.y;
					break;
					
				case MotionNotify:
					cout << "MotionNotify" << endl;
					
					w = win->getWidth();
					h = win->getHeight();
					a = -2. * ( lastx / w - .5 );
					b = -2. * ( .5 - lasty / h );
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
					lastx = event.xmotion.x;
					lasty = event.xmotion.y;
					redraw();
					break;
					
			    case ConfigureNotify:
			        cout << "ConfigureNotify" << endl;
				    if ( ! win->isResizePending() )
					{
					    win->resize( event.xconfigure.width,
								     event.xconfigure.height );
					}													
				
				case Expose:
					redraw();
			 }
			 
		}     
		while ( XPending(dpy) );
    }	
    return (0);
}
