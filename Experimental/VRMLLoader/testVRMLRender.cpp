#include <OSGConfig.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <GL/glut.h>

#include <vector>

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
#ifdef TUBS
#include "OSGTubsMesh.h"
#include "OSGTubs3DText.h"
#endif

OSG::DrawAction * ract;
OSG::Bool doWire = false;

OSG::NodePtr  root;

//std::vector<OSG::NodePtr>  file;
OSG::NodePtr file;

OSG::WindowPtr win;

OSG::TransformPtr cam_trans;

OSG::Trackball tball;

int mouseb = 0;
int lastx=0, lasty=0;

OSG::DirectionalLightPtr dl;


#ifdef TUBS
OSG::OSGTubsMeshPtr pMesh;
#endif

void 
display(void)
{
/*
	OSG::Matrix m1, m2;

	m1.setRotate( tball.getRotation() );
	m2.setTranslate( tball.getPosition() );
	
	m1.mult( m2 );
    */

	cam_trans->getSFMatrix()->setValue( tball.getFullTrackballMatrix() );

	win->draw( ract );

    OSG::Thread::getCurrentChangeList()->clearAll();
}

void reshape( int w, int h )
{
	cerr << "Reshape: " << w << "," << h << endl;
	win->resize( w, h );
}

void loadMesh(const char *szFilename, OSG::NodePtr dlight)
{
    // Mesh
    
#ifdef TUBS
    pMesh = OSG::OSGTubsMesh::create();
            
    pMesh->loadMesh(szFilename, 1.0);
    
    OSG::NodePtr pMeshNode = OSG::Node::create();
    
    pMeshNode->setCore(pMesh);
    
    pMeshNode->updateVolume();
    
    dlight->addChild  (pMeshNode);
    
    // Volume Mesh
    // should check first. ok for now.
    
    const OSG::BoxVolume *volMesh = (OSG::BoxVolume *) 
        &(pMeshNode->getVolume());
    
    OSG::Vec3f meshMin, meshMax;
    OSG::Pnt3f meshCenter;
    
    volMesh->getBounds(meshMin, meshMax);
    volMesh->getCenter(meshCenter);
    
    
    // Text 1
    
    OSG::NodePtr pTextNode1 = OSG::Node::create();
    
    OSG::OSGTubs3DTextPtr pText1 = OSG::OSGTubs3DText::create();
    
    pText1->loadFont("comic.ttf");
    
    pText1->setText("The Power of");
    
    pTextNode1->setCore(pText1);
    
    pTextNode1->updateVolume();
    
    
    // Volume Text
    
    // should check first. ok for now.
    const OSG::BoxVolume *volText1 = (OSG::BoxVolume *) 
        & (pTextNode1->getVolume());
    
    OSG::Vec3f text1Min, text1Max;
    
    volText1->getBounds(text1Min, text1Max);
    
    OSG::NodePtr pTextTrNode1             = 
        OSG::Node::create();
    
    OSG::ComponentTransformPtr pTextTransform1 = 
        OSG::ComponentTransform::create();
    
    pTextTrNode1->setCore(pTextTransform1);
    
    pTextTrNode1->addChild(pTextNode1);
    
    OSG::Vec3f      textScale1(0.2, 0.2, 0.2);
    OSG::Vec3f      textTrans1(0., 0., 0.);
    OSG::Quaternion textRot1;
    
    textRot1.setValueAsAxisDeg(-1., 0., 0., -90.);
    
    textTrans1[0] = -0.5 * (text1Max[0] - text1Min[0]) * 0.2;
    textTrans1[2] = meshCenter[2] + 
        (-0.8 * (meshMax[2] - meshMin[2]));
    
    beginEditCP(pTextTransform1);
    {
        pTextTransform1->setScale      (textScale1);
        pTextTransform1->setRotation   (textRot1  );
        pTextTransform1->setTranslation(textTrans1);
    }
    endEditCP  (pTextTransform1);
    
    dlight->addChild(pTextTrNode1);
    
    
    // Text 2
    
    OSG::NodePtr pTextNode2 = OSG::Node::create();
    
    OSG::OSGTubs3DTextPtr pText2 = OSG::OSGTubs3DText::create();
    
    pText2->loadFont("comic.ttf");
    
    pText2->setText("Subdivision Surfaces");
    
    pTextNode2->setCore(pText2);

    pTextNode2->updateVolume();


    // Volume Text

            // should check first. ok for now.
    const OSG::BoxVolume *volText2 = (OSG::BoxVolume *) 
        & (pTextNode2->getVolume());
        
    OSG::Vec3f text2Min, text2Max;

    volText2->getBounds(text2Min, text2Max);

    OSG::NodePtr pTextTrNode2             = 
        OSG::Node::create();

    OSG::ComponentTransformPtr pTextTransform2 = 
        OSG::ComponentTransform::create();

    pTextTrNode2->setCore(pTextTransform2);

    pTextTrNode2->addChild(pTextNode2);

    OSG::Vec3f      textScale2(0.2, 0.2, 0.2);
    OSG::Vec3f      textTrans2(0., 0., 0.);
    OSG::Quaternion textRot2;

    textRot2.setValueAsAxisDeg(-1., 0., 0., -90.);

    textTrans2[0] = -0.5 * (text2Max[0] - text2Min[0]) * 0.2;
    textTrans2[2] = 
        meshCenter[2] + (-0.8 * (meshMax[2] - meshMin[2])) +
        -1.2 * (text1Max[2] - text1Min[2]);

    beginEditCP(pTextTransform2);
    {
        pTextTransform2->setScale      (textScale2);
        pTextTransform2->setRotation   (textRot2  );
        pTextTransform2->setTranslation(textTrans2);
    }
    endEditCP  (pTextTransform2);

    dlight->addChild(pTextTrNode2);
#endif
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

	if ( g->getNormals() == OSG::NullFC )
	{
		OSG::calcVertexNormals( g );
	}	
	
	return OSG::Action::Continue;
}

void key(unsigned char key, int x, int y)
{
	switch ( key )
	{
        case 27:	
            OSG::osgExit(); 
            exit(0);
        case 'a':	
            glDisable( GL_LIGHTING );
            cerr << "Lighting disabled." << endl;
            break;
        case 's':	
            glEnable( GL_LIGHTING );
            cerr << "Lighting enabled." << endl;
            break;
        case 'z':	
            glPolygonMode( GL_FRONT_AND_BACK, GL_POINT);
            cerr << "PolygonMode: Point." << endl;
            break;
        case 'x':	
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
            cerr << "PolygonMode: Line." << endl;
            break;
        case 'c':	
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
            cerr << "PolygonMode: Fill." << endl;
            break;
        case 'w':	
            doWire = !doWire;
            cerr << "BBox render: " << (doWire?"on":"off") << endl;
            break;
        case 'd':
            root->dump(0, 0);
            break;
        case 'v':
            glEnable(GL_COLOR_MATERIAL);
            break;
        case 'V':
            glDisable(GL_COLOR_MATERIAL);
            break;
        case 'b':     
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            break;
        case 'B':     
            glDisable(GL_BLEND);
            break;
        case 'f':     
            ract->setFrustumCulling(true);
            cerr << "Frustum cull on" << endl;
            break;
        case 'F':     
            ract->setFrustumCulling(false);            
            cerr << "Frustum cull off" << endl;
            break;

        case 't':
#ifdef TUBS
            if(pMesh != OSG::NullFC)
            {
                pMesh->toogleShowTessalation();
            }
#endif
            break;
        case 'r':
#ifdef TUBS
            if(pMesh != OSG::NullFC)
            {
                pMesh->toggleRenderSmooth();
            }
#endif
            break;

        case '1':
            dl->setDirection(0,0,1);
            break;
        case '2':
            dl->setDirection(0,0,-1);
            break;
                
        case '3':
            dl->setDirection(0,1,0);
            break;
        case '4':
            dl->setDirection(0,-1,0);
            break;

        case '5':
            dl->setDirection(1,0,0);
            break;
        case '6':
            dl->setDirection(-1,0,0);
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

    cerr << "Got : " << endl 
         << glutGet(GLUT_WINDOW_DEPTH_SIZE) << endl
         << glutGet(GLUT_WINDOW_RED_SIZE) << endl
         << glutGet(GLUT_WINDOW_GREEN_SIZE) << endl
         << glutGet(GLUT_WINDOW_BLUE_SIZE) << endl
         << glutGet(GLUT_WINDOW_DOUBLEBUFFER) << endl
         << endl;

	// glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
//    glEnable( GL_NORMALIZE );
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
	dl = OSG::DirectionalLight::create();

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

    OSG::beginEditCP(dlight);

    for(OSG::UInt32 numFiles = 1; numFiles < argc; numFiles++)
    {
        if(argv[numFiles][0] == '-')
        {
            loadMesh(&(argv[numFiles][1]), dlight);
        }
        else
        {
/*
            file = 
                OSG::SceneFileHandler::the().readTopNodes(
                    argv[numFiles], 
                    OSG::VRMLFile::StripeGeometry |
                    OSG::VRMLFile::CreateNormals);
                    */

			file = OSG::SceneFileHandler::the().read(argv[numFiles],
										OSG::VRMLFile::StripeGeometry |
                   		 				OSG::VRMLFile::CreateNormals);

            dlight->addChild(file);
/*
			for(OSG::UInt32 i=0; i<file.size(); ++i)
			{
				dlight->addChild(file[i]);
			}
            */
		}
    }
    
    dlight->invalidateVolume();

    OSG::endEditCP(dlight);
    
    dlight->updateVolume();

    // should check first. ok for now.
    const OSG::BoxVolume *vol = (OSG::BoxVolume *)&dlight->getVolume();
        
    OSG::Vec3f min,max;
    OSG::Vec3f size;
    OSG::Pnt3f center;

    vol->getBounds(min, max);
	vol->getCenter(center);

    size = max - min;

    cout << "Volume: from " << min << " to " << max << endl;

//	cerr << "Tree: " << endl;
//    root->print();

	// Camera
	OSG::PerspectiveCameraPtr cam = OSG::PerspectiveCamera::create();

	cam->setBeacon( b1n );
	cam->setFov( OSG::deg2rad( 60 ) );
	cam->setNear( 1 );
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

    

    float scale = (max[2] - min[2] + max[1] - min[1] + max[0] - min[0]) / 6;

	tball.setMode( OSG::Trackball::OSGObject );
	tball.setStartPosition( pos, true );
	tball.setSum( true );
	tball.setTranslationMode( OSG::Trackball::OSGFree );
    tball.setTranslationScale(scale);
    tball.setRotationCenter(center);
    tball.setTranslationGen(OSG::Trackball::OSGAbsoluteTranslation);

	// run...
#if 0
	cam->setFar(size.length() * 4.5);

    if((size.length() * 4.5) > 1000.)
    {
        cam->setNear( 1 );
    }
    else if((size.length()) < 100.)
    {
        cam->setNear(0.01);
    }
    else
    {
        cam->setNear(0.1);
    }
#endif
	

	glutMainLoop();
	
    return 0;
}

