#include <OSGConfig.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

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
#include <OSGGeoFunctions.h>

#include <OSGDirectionalLight.h>

#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGGLUTWindow.h"
//#include "OSGPipe.h"
#include "OSGCamera.h"
#include "OSGPerspectiveCamera.h"
#include "OSGSolidBackground.h"
#include "OSGSceneFileHandler.h"

#include "OSGTrackball.h"

#include "OSGVRMLFile.h"

OSG::DrawAction * ract;
OSG::Bool doWire = false;

OSG::NodePtr  root;

OSG::NodePtr  file;

OSG::WindowPtr win;

OSG::TransformPtr cam_trans;

OSG::Trackball tball;

int mouseb = 0;
int lastx=0, lasty=0;

void 
display(void)
{
	OSG::Matrix m1, m2;

	m1.setRotate( tball.getRotation() );
	m2.setTranslate( tball.getPosition() );
	
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
	OSG::Real32 w = win->getWidth(), h = win->getHeight();
	

	OSG::Real32	a = -2. * ( lastx / w - .5 ),
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

OSG::Action::ResultE wireDraw( OSG::CNodePtr &, OSG::Action * action )
{
	OSG::NodePtr node = action->getActNode();
	
	if ( doWire )
	{		
		node->updateVolume();
		const OSG::DynamicVolume& vol = node->getVolume();

		OSG::Pnt3f min,max;
		vol.getBounds( min, max );

		OSG::Bool l = glIsEnabled( GL_LIGHTING );
		glDisable( GL_LIGHTING );
		
		glColor3f( .8,.8,.8 );
		glBegin( GL_LINE_LOOP );
		glVertex3f( min[0], min[1], min[2] );	
		glVertex3f( max[0], min[1], min[2] );	
		glVertex3f( max[0], max[1], min[2] );	
		glVertex3f( min[0], max[1], min[2] );	
		glVertex3f( min[0], min[1], min[2] );	
		glVertex3f( min[0], min[1], max[2] );	
		glVertex3f( max[0], min[1], max[2] );	
		glVertex3f( max[0], max[1], max[2] );	
		glVertex3f( min[0], max[1], max[2] );	
		glVertex3f( min[0], min[1], max[2] );	
		glEnd();

		glBegin( GL_LINES );
		glVertex3f( min[0], max[1], min[2] );	
		glVertex3f( min[0], max[1], max[2] );	
		glVertex3f( max[0], max[1], min[2] );	
		glVertex3f( max[0], max[1], max[2] );	
		glVertex3f( max[0], min[1], min[2] );	
		glVertex3f( max[0], min[1], max[2] );	
		glEnd();
		
		if ( l )
			glEnable( GL_LIGHTING );
	}
	
	OSG::GeometryPtr g = OSG::GeometryPtr::dcast( node->getCore() );
	
	return g->doDraw( action );
}

OSG::Action::ResultE calcVNormal( OSG::CNodePtr &, OSG::Action * action )
{
	OSG::NodePtr node = action->getActNode();
	OSG::GeometryPtr g = OSG::GeometryPtr::dcast( node->getCore() );

	if ( g->getNormals() == OSG::GeoNormalPtr::NullPtr )
	{
		OSG::calcVertexNormals( g );
	}	
	
	return OSG::Action::Continue;
}

void key(unsigned char key, int x, int y)
{
	switch ( key )
	{
	case 27:	OSG::osgExit(); exit(0);
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
	case 'w':	doWire = !doWire;
				cerr << "BBox render: " << (doWire?"on":"off") << endl;
				break;
	}
}


int main (int argc, char **argv)
{
	OSG::osgInit(argc,argv);

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
    glEnable( GL_NORMALIZE );
	// OSG

	// create the graph

	// beacon for camera and light	
    OSG::NodePtr b1n = OSG::Node::create();
    OSG::GroupPtr b1 = OSG::Group::create();
	OSG::beginEditCP(b1n);
	b1n->setCore( b1 );
	OSG::endEditCP(b1n);

	// transformation
    OSG::NodePtr t1n = OSG::Node::create();
    OSG::TransformPtr t1 = OSG::Transform::create();
	OSG::beginEditCP(t1n);
	t1n->setCore( t1 );
	t1n->addChild( b1n );
	OSG::endEditCP(t1n);

	cam_trans = t1;

	// light
	
	OSG::NodePtr dlight = OSG::Node::create();
	OSG::DirectionalLightPtr dl = OSG::DirectionalLight::create();

	OSG::beginEditCP(dlight);
	dlight->setCore( dl );
	OSG::endEditCP(dlight);
	
	OSG::beginEditCP(dl);
	dl->setAmbient( .3, .3, .3, 1 );
	dl->setDiffuse( 1, 1, 1, 1 );
	dl->setDirection(0,0,1);
	dl->setBeacon( b1n);
	OSG::endEditCP(dl);

	// root
    root = OSG::Node::create();
    OSG::GroupPtr gr1 = OSG::Group::create();
	OSG::beginEditCP(root);
	root->setCore( gr1 );
	root->addChild( t1n );
	root->addChild( dlight );
	OSG::endEditCP(root);

	// Load the file

    for(OSG::UInt32 numFiles = 1; numFiles < argc; numFiles++)
    {
        file = OSG::SceneFileHandler::the().read(argv[numFiles]);
                     
        OSG::beginEditCP(dlight);
        dlight->addChild( file );
        dlight->invalidateVolume();
        OSG::endEditCP(dlight);
    }


    dlight->updateVolume();

    // should check first. ok for now.
    const OSG::BoxVolume *vol = (OSG::BoxVolume *)&dlight->getVolume();
        
    OSG::Vec3f min,max;
    vol->getBounds( min, max );
	
    cout << "Volume: from " << min << " to " << max << endl;

//	cerr << "Tree: " << endl;
//    root->print();

	// Camera
	OSG::PerspectiveCameraPtr cam = OSG::PerspectiveCamera::create();

	cam->setBeacon( b1n );
	cam->setFov( OSG::deg2rad( 60 ) );
	cam->setNear( 0.1 );
	cam->setFar( 5000 );

	// Solid Background
	OSG::SolidBackgroundPtr bkgnd = OSG::SolidBackground::create();
	bkgnd->setColor( OSG::Color3f(0,0,1) );

	// Viewport

	OSG::ViewportPtr vp = OSG::Viewport::create();
	vp->setCamera( cam );
	vp->setBackground( bkgnd );
	vp->setRoot( root );
	vp->setSize( 0,0, 1,1 );

	// Window
	cout << "GLUT winid: " << winid << endl;

	OSG::GLUTWindowPtr gwin;

	GLint glvp[4];
	glGetIntegerv( GL_VIEWPORT, glvp );

	gwin = OSG::GLUTWindow::create();
	gwin->setWinID(winid);
	gwin->setSize( glvp[2], glvp[3] );

	win = gwin;

	win->addPort( vp );

	// Action
	
	ract = OSG::DrawAction::create();

	cerr << "Calculating normals...";
	
	// Task 1: Cal Vertex Normals
	ract->registerEnterFunction( OSG::Geometry::getClassType(),
									OSG::osgFunctionFunctor2( calcVNormal ) );
	
//	ract->apply( dlight );

	cerr << "done." << endl;
	
	// Task 2: draw wireframe bbox, if wanted
	ract->registerEnterFunction( OSG::Geometry::getClassType(),
									OSG::osgFunctionFunctor2( wireDraw ) );
									

	// tball
    
    OSG::Vec3f pos(min[0] + ((max[0] - min[0]) * 0.5), 
                   min[1] + ((max[1] - min[1]) * 0.5), 
                   max[2] + ( max[2] - min[2] ) * 1.5 );

	tball.setMode( OSG::Trackball::OSGObject );
	tball.setStartPosition( pos, true );
	tball.setSum( true );
	tball.setTranslationMode( OSG::Trackball::OSGFree );
    tball.setTranslationScale(50.);
	// run...
	
	glutMainLoop();
	
    return 0;
}

