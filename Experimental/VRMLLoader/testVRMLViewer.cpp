#include <OpenSG/OSGConfig.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <sys/time.h>
#include <unistd.h> 

#include <GL/glut.h>

#include <OpenSG/OSGFieldContainerPtr.h>
#include <OpenSG/OSGFieldContainerFactory.h>
#include <OpenSG/OSGSFSysTypes.h>
#include <OpenSG/OSGFieldContainerPtr.h>
#include <OpenSG/OSGNodePtr.h>
#include <OpenSG/OSGVector.h>
#include <OpenSG/OSGQuaternion.h>
#include <OpenSG/OSGMatrix.h>
#include <OpenSG/OSGMatrixUtility.h>
#include <OpenSG/OSGBoxVolume.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGThread.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGAttachment.h>
#include <OpenSG/OSGMFVecTypes.h>
#include <OpenSG/OSGAction.h>
#include <OpenSG/OSGDrawAction.h>
#include <OpenSG/OSGGeometry.h>
#include <OpenSG/OSGGeoFunctions.h>

#include <OpenSG/OSGDirectionalLight.h>

#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGCamera.h>
#include <OpenSG/OSGWindow.h>
#include <OpenSG/OSGGLUTWindow.h>
//#include <OpenSG/OSGPipe.h>
#include <OpenSG/OSGCamera.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGSolidBackground.h>

#include <OpenSG/OSGTrackball.h>

#include <OpenSG/OSGVRMLFile.h>

#include "OpenSG/OSGViewpointAttachment.h"
#include <OpenSG/OSGVRMLTransform.h>
#include <OpenSG/OSGMField.h>

OSG::DrawAction * ract;
OSG::Bool doWire = false;

OSG::NodePtr  root;

OSG::NodePtr  file;

OSG::WindowPtr win;

OSG::VRMLTransformPtr cam_trans;

OSG::Trackball tball;

OSG::PerspectiveCameraPtr cam;

OSG::NodePtr 		t1n;
OSG::VRMLTransformPtr	t1;


OSG::NodePtr 		sceneTransNode;
OSG::VRMLTransformPtr	sceneTransCore;


//OSG::NodePtr b1n;

int mouseb = 0;
int lastx=0, lasty=0;

// --- camera animation stuff
int		selectedCam=0;
OSG::MField<OSG::NodePtr>	cameraBeacons;	
OSG::Bool   doAnim = false;
OSG::Real32	animFraction = 0.0;
OSG::Real32	animDelta = 0.05;
OSG::Vec3f	startPoint, endPoint;
OSG::Quaternion startQuat, endQuat;
OSG::Real32	startFov, endFov;
OSG::NodePtr stdCamNode;
OSG::VRMLTransformPtr stdCamBeacon;

OSG::Real32 animDuration;
OSG::Real32 frameDuration = 0.0;

OSG::Vec3f		interPnt;
OSG::Quaternion interQuat;
OSG::Real32		interFov;

// --- fps calculation

struct timeval timeOld, timeNew;

/*------------- Linear interpolation --------------------------------------*/

/*! \brief Linear interpolation between p1 and p2
	\lambda in the range [0,1]
	\return linear interpolated value 
 */
 
template<class T>
T linearInterpol( T& p1, T& p2, OSG::Real32 lambda )
{
	return ( p2*lambda + p1*(1.0-lambda) );
}

/*------------- Time-difference calculation -------------------------------*/

/*! \brief Returns the difference between time t1 and t2.
	\return the differnce is returned in microseconds
 */

long diffTime( const timeval& t1, const timeval& t2 )
{
	return 
		(t2.tv_sec*1000000 + t2.tv_usec) - (t1.tv_sec*1000000 + t1.tv_usec);
}

/*------------- fps calculation -------------------------------------------*/

OSG::Real32	fps( OSG::Real32 frameTime )
{
	return 1000000.0/frameTime;
}

/*-------------------------------------------------------------------------*/

void selectCamera( uint cameraNr )
{
	OSG::ViewpointAttachmentPtr foundAttach = 
				OSG::ViewpointAttachmentPtr::NullPtr;
	OSG::NodePtr			node = OSG::NullNode;
	OSG::VRMLTransformPtr	vrmlTrans;
	OSG::Real32				fieldOfView;

	if( cameraNr>cameraBeacons.size() )
	{
		cameraNr=cameraBeacons.size();
		cerr << "Only " << cameraBeacons.size() << " cameras available.\n"; 
	}

	node = cameraBeacons[cameraNr-1];
	vrmlTrans = OSG::VRMLTransformPtr::dcast( node->getCore() );

	// --- find the viewpoint attachment
	foundAttach =
	OSG::ViewpointAttachmentPtr::dcast( node->findAttachment
			(OSG::ViewpointAttachment::getClassType().getGroupId()) );						

	if( foundAttach == OSG::ViewpointAttachmentPtr::NullPtr )
		fieldOfView = 60.0;
	else
		fieldOfView = foundAttach->getFieldOfView();
	
	
	cerr << "Activating camera#" << cameraNr << endl
		<< "Position:    " << vrmlTrans->getSFTranslation()->getValue() << endl
		<< "Orientation: " << vrmlTrans->getSFRotation()->getValue() << endl
		<< "Fov:         " << fieldOfView << endl << endl;

	cam_trans  = vrmlTrans;	
	startPoint = tball.getPosition();
	endPoint   = vrmlTrans->getSFTranslation()->getValue();
	startQuat  = tball.getRotation();
	endQuat    = vrmlTrans->getSFRotation()->getValue();
	startFov   = cam->getFov();
	endFov     = fieldOfView;
	doAnim = true;
	tball.setStartPosition( endPoint, true );
	tball.setStartRotation( endQuat, true );

	tball.reset();		

	// --- set the new beacon as the cams core		
	OSG::beginEditCP(cam);						
		cam->setFov( fieldOfView );
		cam->setBeacon( node );						
	OSG::endEditCP(cam);		
}

/*-------------------------------------------------------------------------*/

void 
display(void)
{
	OSG::Matrix m1, m2;
	long		diff;
	OSG::Real32 nrOfSteps;
	
	// --- adjust the position for animation
	if( doAnim )
	{
		interPnt  = linearInterpol(startPoint,endPoint, animFraction);
		interQuat = startQuat.slerp(startQuat, endQuat, animFraction);
		interFov  = linearInterpol(startFov, endFov, animFraction); 
		
		m2.setTranslate( interPnt ); 
		m1.setRotate( interQuat );
				
		OSG::beginEditCP(cam);	
			cam->setFov( interFov );				
		OSG::endEditCP(cam);	
		
		animFraction += animDelta;
		if( animFraction > 1.0 )
		{
			doAnim = false;
			animFraction = 0.0;			
		}
	
		// adjust trackball (for correct interruption of the animation)
		//tball.setStartPosition( interPnt, true );
		//tball.setStartRotation( interQuat, true );			
	}
	else {
		m1.setRotate( tball.getRotation() );
 		m2.setTranslate( tball.getPosition() );
	}
	
	m2.mult( m1 );	
	
	cam_trans->getSFMatrix()->setValue( m2 );
		
	win->draw( ract );
	
	// store previous time value
	timeOld = timeNew;	
	
	// get new time value
	gettimeofday( &timeNew, 0 ); 
	
	// calc difference between previous and current time	
	diff = 	diffTime(timeOld, timeNew);
		
	// calc nr
	//nrOfSteps = (animDuration*1000) / ( diff/1000.0 );
	nrOfSteps = (animDuration*1000000) / diff;
	
//	cout << "fps: " << fps( diff ) << endl;
	
	animDelta = 1.0/nrOfSteps;	
}

/*-------------------------------------------------------------------------*/

void reshape( int w, int h )
{
	cerr << "Reshape: " << w << "," << h << endl;
	win->resize( w, h );
}

/*-------------------------------------------------------------------------*/

void
animate(void)
{
	glutPostRedisplay();
}

/*-------------------------------------------------------------------------*/

// tball stuff

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

/*-------------------------------------------------------------------------*/

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

/*-------------------------------------------------------------------------*/

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

/*-------------------------------------------------------------------------*/


/*! \brief Traverses the scenegraph and checks for VRMLTransforms with
	viewpoint attachment.
	
	If there are any transformations with viewpoint attachment these
	are stored in a global vector. These transformations act as camera 
	beacons.
	
	\todo Perhaps add code for moving the collected transformations 
	under the root node of the scenegraph.
 */	
	
OSG::Action::ResultE viewpointCheck( OSG::CNodePtr &, OSG::Action * action )
{
	OSG::NodePtr			node 	  = action->getActNode();
	OSG::VRMLTransformPtr   vrmlTrans = OSG::VRMLTransformPtr::NullPtr;				
	OSG::ViewpointAttachmentPtr foundAttach = 
				OSG::ViewpointAttachmentPtr::NullPtr;
					
	vrmlTrans = OSG::VRMLTransformPtr::dcast( node->getCore() );
		
	if( !vrmlTrans )
	{
		cerr << "ERROR! The Node " << node << " does not have a core.\n";
	}
	else
	{
		// test for a viewpoint attachment
		foundAttach =
			OSG::ViewpointAttachmentPtr::dcast( node->findAttachment
					(OSG::ViewpointAttachment::getClassType().getGroupId()));

		// if one is present -> the VRMLTransformation is a camera beacon
		if( foundAttach != OSG::ViewpointAttachmentPtr::NullPtr )
		{
			cameraBeacons.push_back( node );
		}	
		else
			cerr << "viewpoint has NO Viewpoint attachment.\n";
	}
	
   return OSG::Action::Continue;
}

/*-------------------------------------------------------------------------*/

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

/*-------------------------------------------------------------------------*/

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

/*-------------------------------------------------------------------------*/

void key(unsigned char key, int x, int y)
{
	int cameraNr;

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
				
	// forcing fall-through by ommiting break statement!			
	case '1':					
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		cameraNr = int(key)-48;
		selectCamera(cameraNr);		
		break;	
	}
}

/*-------------------------------------------------------------------------*/

void specialKey(int key, int x, int y)
{
	int cameraNr;

	switch ( key )
	{				
	// forcing fall-through by ommiting break statement!			
	case GLUT_KEY_PAGE_UP:	
		if( selectedCam < cameraBeacons.size() )
			selectedCam++;
		else 
			selectedCam=1;
		break;				
	case GLUT_KEY_PAGE_DOWN:						
//		cameraNr = int(key)-48;
		if( selectedCam > 1 )
			selectedCam--;
		else
			selectedCam = cameraBeacons.size();
		break;	
	}
	
	selectCamera(selectedCam);	
}


/*-------------------------------------------------------------------------*/

int main (int argc, char **argv)
{
	// parse command line
	if( argc<2 )
	{
		cerr << endl << "Usage: " << argv[0]
			 << " <vrmlfile> [cameraSpeed]" << endl << endl;
		exit(0);
	}
	else if( argc<3 )
		animDuration = 2.0;		
	else
		animDuration = atof(argv[2]);

	OSG::osgInit(argc,argv);
		
	cout << "No camera speed specified, using: " << animDuration << "s\n";

	// GLUT init

	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	int winid = glutCreateWindow("OpenSG");
	glutKeyboardFunc(key);
	glutSpecialFunc(specialKey);
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

	// transformation
    t1n = OSG::Node::create();
    t1  = OSG::VRMLTransform::create();
	OSG::beginEditCP(t1n);
		t1n->setCore( t1 );
	OSG::endEditCP(t1n);

	cam_trans = t1;

	sceneTransNode = OSG::Node::create();
    sceneTransCore  = OSG::VRMLTransform::create();
	OSG::beginEditCP(sceneTransNode);
		sceneTransNode->setCore( sceneTransCore );
	OSG::endEditCP(sceneTransNode);

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
		dl->setBeacon( t1n);
	OSG::endEditCP(dl);

	// root
    root = OSG::Node::create();
    OSG::GroupPtr gr1 = OSG::Group::create();
	OSG::beginEditCP(root);
		root->setCore( gr1 );
		root->addChild( t1n );
		root->addChild( sceneTransNode );
	OSG::endEditCP(root);

	OSG::beginEditCP(sceneTransNode);
		sceneTransNode->addChild( dlight );
	OSG::endEditCP(sceneTransNode);
	

	// Load the file
	
    OSG::VRMLFile *pLoader = new OSG::VRMLFile();

    pLoader->scanStandardPrototypes("std.supported.wrl", 0);

    for(OSG::UInt32 numFiles = 1; numFiles < argc; numFiles++)
    {
        pLoader->scanFile(argv[numFiles], 0);

        file = pLoader->getRoot();
                     
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

	// Camera
	cam = OSG::PerspectiveCamera::create();
	cam->setBeacon( t1n );
	cam->setFov( 60 );
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

	//OSG::GLUTWindowPtr gwin;
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

	// test for the viewpoint node....
					
	

	
	// ---	
	cerr << "Calculating normals...";
	
	// Task 1: Cal Vertex Normals
	ract->registerEnterFunction( OSG::Geometry::getClassType(),
									OSG::osgFunctionFunctor2( calcVNormal ) );
	
	ract->apply( dlight );

	cerr << "done." << endl;
	
	// Task 2: draw wireframe bbox, if wanted
	ract->registerEnterFunction( OSG::Geometry::getClassType(),
									OSG::osgFunctionFunctor2( wireDraw ) );
	root->dump();	

	cam_trans = t1;

	// tball    
    OSG::Vec3f pos(min[0] + ((max[0] - min[0]) * 0.5), 
                   min[1] + ((max[1] - min[1]) * 0.5), 
                   max[2] + ( max[2] - min[2] ) * 1.5 );

	cerr << "Testing for viewpoints...\n";							
	// --- traverse graph and collect viewpoints
	OSG::Action *act1;	
	act1 = OSG::Action::create();	
	act1->registerEnterFunction( OSG::VRMLTransform::getClassType(),
								 OSG::osgFunctionFunctor2(viewpointCheck) );		
	act1->apply(dlight);

	// --- move viewpoint nodes to be child of the root node
	
	for( int i=0; i<cameraBeacons.size(); i++ )
	{
		cerr << "moving cam" << i << endl;
		cameraBeacons[i]->getParent()->subChild( cameraBeacons[i] );
		root->addChild( cameraBeacons[i] );
	}


	if( cameraBeacons.size() < 1 )
	{
		cerr << "No Viewpoint node in VRML97 file. Adding standard viewpoint."
			 << endl;
		stdCamNode 	= OSG::Node::create();		
		stdCamBeacon= OSG::VRMLTransform::create();
		
		beginEditCP( stdCamNode );
			stdCamNode->setCore( stdCamBeacon );
		endEditCP( stdCamNode );
		
		beginEditCP( stdCamBeacon );
			stdCamBeacon->setTranslation( pos );
		endEditCP( stdCamBeacon );
		
		cameraBeacons.push_back( stdCamNode );
	}
	cerr << "Testing for viewpoints...done.\n";


	tball.setMode( OSG::Trackball::OSGObject );
	tball.setStartPosition( pos, true );
	tball.setSum( true );
	tball.setTranslationMode( OSG::Trackball::OSGFree );
    tball.setTranslationScale(50.);
	// run...
	
	glutMainLoop();
	
    return 0;
}

