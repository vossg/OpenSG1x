#include <OSGConfig.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <GL/gl.h>
#include <GL/glut.h>

#include <OSGFieldContainerFactory.h>
#include <OSGSFSysTypes.h>
#include <OSGVector.h>
#include <OSGQuaternion.h>
#include <OSGMatrix.h>
#include <OSGMatrixUtility.h>
#include <OSGBoxVolume.h>
#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGThread.h>
#include <OSGTransform.h>
#include <OSGAttachment.h>
#include <OSGMFVecTypes.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>
#include <OSGGeometry.h>
#include <OSGSimpleGeometry.h>

#include <OSGDirectionalLight.h>

#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGGLUTWindow.h"
#include "OSGCamera.h"
#include "OSGPerspectiveCamera.h"
#include "OSGSolidBackground.h"
//#include "OSGUniformBackground.h"

#if defined(__linux) || ( defined(WIN32) && ! defined(OSG_BUILD_DLL) )
#include "RAW/OSGRAWSceneFileType.h"
#endif

#include "OSGTrackball.h"

using namespace OSG;

DrawAction * ract;

NodePtr  root;

PerspectiveCameraPtr cam;
ViewportPtr vp;
WindowPtr win;

TransformPtr cam_trans;

Trackball tball;

int mouseb = 0;
int lastx=0, lasty=0;


// GL object test

UInt32 glid2 = -1;
UInt32 glid = -1;

void dlist( Window *win, UInt32 id )
{
	Window::GLObjectStatusE mode = win->getGLObjectStatus( id );
	
	if ( mode == Window::destroy )
	{
		glDeleteLists( id, 1 );
	}
	else if ( mode == Window::finaldestroy )
	{
		cerr << "Last display list destroyed" << endl;
	}
	else if ( mode == Window::initialize )
	{
		glNewList( id, GL_COMPILE );
		glutSolidTorus( .2, 1, 16, 16 );
		glEndList();
	}
	else
	{
		cerr << "Illegal mode: " << mode << " for id " << id << endl;
	}
}


void dlist2( Window *win, UInt32 id )
{
	Window::GLObjectStatusE mode = win->getGLObjectStatus( id );
	
	if ( mode == Window::destroy )
	{
		glDeleteLists( id, 1 );
	}
	else if ( mode == Window::finaldestroy )
	{
		cerr << "Last display list destroyed" << endl;
	}
	else if ( mode == Window::initialize )
	{
		glNewList( id, GL_COMPILE );
		glutSolidSphere( .3, 16, 16 );
		glEndList();
	}
	else
	{
		cerr << "Illegal mode: " << mode << " for id " << id << endl;
	}
}

// a little cheat: override the geometry draw function for drawAct to use 
// this, so we can test OpenGL object handling

	
Action::ResultE doDraw( CNodePtr& node, Action * action )
{
	DrawAction *a = dynamic_cast<DrawAction*>(action);

	// validate it, so that it's valid in this context
	a->getWindow()->validateGLObject( glid );
	a->getWindow()->validateGLObject( glid2 );
	
	// use it
	glCallList( glid );
	glCallList( glid2 );
	
	return Action::Continue;
}


void 
display(void)
{
	Matrix m1, m2, m3;
    Quaternion q1;

    tball.getRotation().getValue(m3);

    q1.setValue(m3);

    m1.setRotate(q1);
    
//    cout << "TBROT" << endl << tball.getRotation() << endl;
//    cout << "M3" << endl << m3 << endl;
//    cout << "Q1" << endl << q1 << endl;
//    cout << "M1" << endl << m1 << endl;

//	m1.setRotate( tball.getRotation() );
	m2.setTranslate( tball.getPosition() );
	
//cout << "Pos: " << tball.getPosition() << ", Rot: " << tball.getRotation() << endl;

//    cout << tball.getRotation() << endl;

	m1.mult( m2 );
	cam_trans->getSFMatrix()->setValue( m1 );

	win->draw( ract );
}

void reshape( int w, int h )
{
	cerr << "Reshape: " << w << "," << h << endl;
	win->resize( w, h );
}


void
animate(void)
{
	glutPostRedisplay();
}

// tballall stuff


void
motion(int x, int y)
{	
	Real32 w = win->getWidth(), h = win->getHeight();
	

	Real32	a = -2. * ( lastx / w - .5 ),
				b = -2. * ( .5 - lasty / h ),
				c = -2. * ( x / w - .5 ),
				d = -2. * ( .5 - y / h );

	if ( mouseb & ( 1 << GLUT_LEFT_BUTTON ) )
	{
		tball.updateRotation( a, b, c, d );	
	}
	else if ( mouseb & ( 1 << GLUT_MIDDLE_BUTTON ) )
	{
		tball.updatePosition( a, b, c, d );	
	}
	else if ( mouseb & ( 1 << GLUT_RIGHT_BUTTON ) )
	{
		tball.updatePositionNeg( a, b, c, d );	
	}
	lastx = x;
	lasty = y;
}

void
mouse(int button, int state, int x, int y)
{
	if ( state == 0 )
	{
		switch ( button )
		{
		case GLUT_LEFT_BUTTON:	break;
		case GLUT_MIDDLE_BUTTON:tball.setAutoPosition(true);
								break;
		case GLUT_RIGHT_BUTTON:	tball.setAutoPositionNeg(true);
								break;
		}
		mouseb |= 1 << button;
	}
	else if ( state == 1 )
	{
		switch ( button )
		{
		case GLUT_LEFT_BUTTON:	break;
		case GLUT_MIDDLE_BUTTON:tball.setAutoPosition(false);
								break;
		case GLUT_RIGHT_BUTTON:	tball.setAutoPositionNeg(false);
								break;
		}		
		mouseb &= ~(1 << button);
	}
	lastx = x;
	lasty = y;
}

void
vis(int visible)
{
	if (visible == GLUT_VISIBLE) 
	{
		glutIdleFunc(animate);
	} 
	else 
	{
		glutIdleFunc(NULL);
	}
}

void key(unsigned char key, int x, int y)
{
	switch ( key )
	{
	case 27:	osgExit(); exit(0);
	case 'a':	glDisable( GL_LIGHTING );
				cerr << "Lighting disabled." << endl;
				break;
	case 's':	glEnable( GL_LIGHTING );
				cerr << "Lighting enabled." << endl;
				break;
	case 'z':	glPolygonMode( GL_FRONT_AND_BACK, GL_POINT);
				cerr << "PolygonMode: Point." << endl;
				break;
	case 'x':	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
				cerr << "PolygonMode: Line." << endl;
				break;
	case 'c':	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
				cerr << "PolygonMode: Fill." << endl;
				break;
	case 'r':	cerr << "Sending ray through " << x << "," << y << endl;
				Line l;
				cam->calcViewRay( l, x, y, *vp );
				cerr << "From " << l.getPosition() << ", dir " << l.getDirection() << endl;
				break;
	}
}


int main (int argc, char **argv)
{
	osgInit(argc,argv);

	// GLUT init

	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	int winid = glutCreateWindow("OpenSG");
	glutKeyboardFunc(key);
	glutVisibilityFunc(vis);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);       
	glutMouseFunc(mouse);   
	glutMotionFunc(motion); 
	
	glutIdleFunc(display);	

	// glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );

	// OSG

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

	// just a dummy
	NodePtr geo = makeSphere( 1,1 );

	geo->updateVolume();

	// should check first. ok for now.
	const BoxVolume *vol = (BoxVolume *)&geo->getVolume();

	Vec3f min,max;
	vol->getBounds( min, max );
	
	cout << "Volume: from " << min << " to " << max << endl;

	beginEditCP(dlight);
	dlight->addChild( geo );
	endEditCP(dlight);

	cerr << "Tree: " << endl;
	root->dump();

	// Camera
	
	cam = PerspectiveCamera::create();
	cam->setBeacon( b1n );
	cam->setFov( deg2rad( 90 ) );
	cam->setNear( 0.1 );
	cam->setFar( 10000 );

	// Background
	SolidBackgroundPtr bkgnd = SolidBackground::create();

	// Viewport

	vp = Viewport::create();
	vp->setCamera( cam );
	vp->setBackground( bkgnd );
	vp->setRoot( root );
	vp->setSize( 0,0, 1,1 );

	// Window
	cout << "GLUT winid: " << winid << endl;

	GLUTWindowPtr gwin;

	GLint glvp[4];
	glGetIntegerv( GL_VIEWPORT, glvp );

	gwin = GLUTWindow::create();
	gwin->setWinID(winid);
	gwin->setSize( glvp[2], glvp[3] );

	win = gwin;

	win->addPort( vp );

	win->init();

	// Action
	
	ract = DrawAction::create();
	
	// tweak it use our function for geometry rendering
	ract->registerEnterFunction( 	Geometry::getClassType(), 
									osgFunctionFunctor2( doDraw ) );

	
	// tball

	Vec3f pos( 0, 0, max[2] + ( max[2] - min[2] ) * 1.5 );

	tball.setMode( Trackball::OSGObject );
	tball.setStartPosition( pos, true );
	tball.setSum( true );
	tball.setTranslationMode( Trackball::OSGFree );

	// allocate the GL id
	
	glid = Window::registerGLObject( osgFunctionFunctor2( dlist ), 1 );
	glid2 = Window::registerGLObject( osgFunctionFunctor2( dlist2 ), 1 );
	
	// run...
	
	glutMainLoop();
	
    return 0;
}

