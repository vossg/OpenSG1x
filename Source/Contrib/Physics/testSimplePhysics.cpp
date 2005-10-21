// OpenSG Example: ode<->opensg
//
// 
// 
// used as test case for ode<->osg
//
#include <OSGBaseFunctions.h>

#include <OSGSpotLight.h>
#include <OSGDirectionalLight.h>
#include <OSGPointLight.h>
#include <OSGPerspectiveCamera.h>
#include <OSGGradientBackground.h>
#include <OSGSolidBackground.h>
#include <OSGDrawAction.h>
#include <OSGRenderAction.h>
#include <OSGImage.h>
#include <OSGSimpleMaterial.h>
#include <OSGTextureChunk.h>
#include <OSGTransform.h>
#include <OSGGroup.h>
#include <OSGTrackball.h>
#include <OSGMatrix.h>
#include <OSGQuaternion.h>
#include <OSGVector.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSceneFileHandler.h>    

#include <OSGShadowMapViewport.h>
// GLUT is used for window handling
#include <OSGGLUT.h>

// General OpenSG configuration, needed everywhere
#include <OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OSGSimpleGeometry.h>

// The GLUT-OpenSG connection class
#include <OSGGLUTWindow.h>

// A little helper to simplify scene management and interaction
#include <OSGSimpleSceneManager.h>

//saving and loading a scene
#include <OSGSceneFileHandler.h>

//Name our nodes
#include <OSGSimpleAttachments.h>


#include <OSGCoredNodePtr.h>

#include <OSGPhysics.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

PhysicsRayGeomPtr r = PhysicsRayGeom::create();

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

//collision and physics handler
PhysicsHandlerPtr physHandler;
PhysicsWorldPtr physicsWorld;
PhysicsHashSpacePtr hashSpace;

dJointGroupID physColJointGroupId;
dContact *physContactArray;

//just for hierarchy
NodePtr spaceGroupNode;

ShadowMapViewportPtr svp;
NodePtr rootNode;


// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );
void buildCar();


//////////////////////////////////////////////////////////////////////////
//! Initialize GLUT & OpenSG and set up the scene
//////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
	// OSG init
    OSG::osgLog().setLogLevel ( OSG::LOG_NOTICE);
	osgInit(argc,argv);

	// GLUT init
	int winid = setupGLUT(&argc, argv);

	// the connection between GLUT and OpenSG
	GLUTWindowPtr gwin= GLUTWindow::create();

	// create the rootNode
	rootNode = makeCoredNode<Group>();
    setName(rootNode, "rootNode");
	NodePtr scene = makeCoredNode<Group>();
    setName(scene, "scene");
	
	// create lights
	PointLightPtr _point1_core;
	TransformPtr point1_trans;
	NodePtr point1 = makeCoredNode<PointLight>(&_point1_core);
    setName(point1, "Lightpoint1");
	NodePtr point1_beacon = makeCoredNode<Transform>(&point1_trans);
    setName(point1_beacon, "point1_beacon");
	beginEditCP(point1_trans);
		point1_trans->getMatrix().setTranslate(0.0, 0.0, 25.0);
	endEditCP(point1_trans);

	beginEditCP(_point1_core);
		_point1_core->setAmbient(0.9,0.9,0.9,1);
		_point1_core->setDiffuse(0.9,0.9,0.9,1);
		_point1_core->setSpecular(0.3,0.3,0.3,1);
		_point1_core->setBeacon(point1_beacon);
		_point1_core->setOn(true);
	endEditCP(_point1_core);
	
	beginEditCP(point1);
		point1->addChild(scene);
	endEditCP(point1);
	
	svp = ShadowMapViewport::create();
	GradientBackgroundPtr gbg = GradientBackground::create();
	SolidBackgroundPtr sbg = SolidBackground::create();

	beginEditCP(gbg);
		gbg->addLine(Color3f(0.7, 0.7, 0.8), 0);
		gbg->addLine(Color3f(0.0, 0.1, 0.3), 1);
	endEditCP(gbg);

	beginEditCP(rootNode);
		rootNode->addChild(point1);
		rootNode->addChild(point1_beacon);
	endEditCP(rootNode);

	// Shadow viewport
	beginEditCP(svp);
		svp->setBackground(gbg);
		svp->setRoot(rootNode);
		svp->setSize(0,0,1,1);
		svp->setOffFactor(10.0);
		svp->setOffBias(4.0);
		svp->setShadowColor(Color4f(0.1, 0.1, 0.1, 1.0));
		svp->setMapSize(1024);
		// you can add the light sources here, as default all light source in
		// the scenegraph are used.
		svp->getLightNodes().push_back(point1);
	endEditCP(svp);

    //create physics
    physHandler = PhysicsHandler::create();
    physicsWorld = PhysicsWorld::create();
    physicsWorld->setGravity(Vec3f(0.0, 0.0, -9.81));
    hashSpace = PhysicsHashSpace::create();
    CPEdit(physHandler, PhysicsHandler::WorldFieldMask |
        PhysicsHandler::SpaceFieldMask);
        physHandler->setWorld(physicsWorld);
        physHandler->setSpace(hashSpace);


    CPEdit(rootNode, Node::AttachmentsFieldMask);
        rootNode->addAttachment(physHandler);    
        rootNode->addAttachment(physicsWorld);
        rootNode->addAttachment(hashSpace);


	beginEditCP(gwin);//Window
		gwin->setId(winid);
		gwin->addPort(svp);
		gwin->init();
	endEditCP(gwin);
	
	//---end shadow bla
    //
    
    physContactArray = new dContact[32];
    physColJointGroupId = dJointGroupCreate(0);
    for (Int32 index = 0; index < 32; index++)
    {
        physContactArray[index].surface.mode = dContactApprox1;
        physContactArray[index].surface.mu = 0.75;
    }


	/************************************************************************/
	/* print some dWorld params                                                                     */
	/************************************************************************/

	printf("getting all defaut global dWorld values from ODE...\n");
	Vec3f g= physicsWorld->getGravity();
	printf(" erp: %f \n cfm: %f \n gravity: (%f, %f, %f)\n"
		" autoDisableFlag: %d \n autoDisableLinearThreshold:%f \n"
		" autoDisbaleAngularThreshold:%f \n autoDisableSteps:%d \n"
		" autoDisableTime:%f \n \n",physicsWorld->getErp(), 
                                    physicsWorld->getCfm(), 
                                    g.x(),
		                            g.y(),
                                    g.z(),
                                    physicsWorld->getAutoDisableFlag(),
                                    physicsWorld->getAutoDisableLinearThreshold(),
		                            physicsWorld->getAutoDisableAngularThreshold(),
                                    physicsWorld->getAutoDisableSteps(),
                                    physicsWorld->getAutoDisableTime());


	/************************************************************************/
	/* create spaces, geoms and bodys                                                                     */
	/************************************************************************/
    //create a group for our space
    GroupPtr spaceGroup;
	spaceGroupNode = makeCoredNode<Group>(&spaceGroup);
    //create the ground plane
    GeometryPtr plane;
	NodePtr planeNode = makeBox(200.0, 200.0, 1.0, 1, 1, 1);
    plane = GeometryPtr::dcast(planeNode->getCore());
    //and its Material
	SimpleMaterialPtr plane_mat = SimpleMaterial::create();
	beginEditCP(plane_mat);
		plane_mat->setAmbient(Color3f(0.7,0.7,0.7));
		plane_mat->setDiffuse(Color3f(0.9,0.6,1.0));
	endEditCP(plane_mat);
    beginEditCP(plane, Geometry::MaterialFieldMask);
	    plane->setMaterial(plane_mat);
    endEditCP(plane);


    //create Physical Attachments
	PhysicsBoxGeomPtr planeGeom = PhysicsBoxGeom::create();
    CPEdit(planeGeom, PhysicsBoxGeom::LenghtsFieldMask | 
                      PhysicsBoxGeom::SpaceFieldMask);
        planeGeom->setLenghts(Vec3f(200.0, 200.0, 1.0));
        //add geoms to space for collision
        planeGeom->setSpace(hashSpace);

	//add Attachments to nodes...
    beginEditCP(spaceGroupNode, Node::AttachmentsFieldMask | 
                            Node::ChildrenFieldMask);
	    spaceGroupNode->addAttachment(hashSpace);
        spaceGroupNode->addChild(planeNode);
    endEditCP(spaceGroupNode);
    beginEditCP(planeNode, Node::AttachmentsFieldMask);
        planeNode->addAttachment(planeGeom);
    endEditCP(planeNode);
    

    CPEdit(scene, Node::ChildrenFieldMask);
	    scene->addChild(spaceGroupNode);


	// create the SimpleSceneManager helper
	mgr = new SimpleSceneManager;

	// tell the manager what to manage
	mgr->setWindow(gwin );
    mgr->setRoot(rootNode);
	beginEditCP(svp);//Viewport
		svp->setCamera(mgr->getCamera());
	endEditCP(svp);
    svp->setShadowOn(false);
    RenderAction *renderAction = dynamic_cast<RenderAction*>(mgr->getAction());
    assert(renderAction);
    
    //renderAction->setVolumeDrawing(true);


	// show the whole scene
	mgr->showAll();

	// GLUT main loop
	glutMainLoop();
    //clean mem
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//! build a box
//////////////////////////////////////////////////////////////////////////
void buildBox(void)
{
    Matrix m;
    //create OpenSG mesh
    GeometryPtr box;
    NodePtr boxNode = makeBox(1.0, 1.0, 1.0, 1, 1, 1);
    box = GeometryPtr::dcast(boxNode->getCore());
    SimpleMaterialPtr box_mat = SimpleMaterial::create();
    beginEditCP(box_mat);
        box_mat->setAmbient(Color3f(0.0,0.0,0.0));
        box_mat->setDiffuse(Color3f(0.0,1.0 ,0.0));
    endEditCP(box_mat);
    beginEditCP(box, Geometry::MaterialFieldMask);
        box->setMaterial(box_mat);
    endEditCP(box);
    TransformPtr boxTrans;
    NodePtr boxTransNode = makeCoredNode<Transform>(&boxTrans);
    m.setIdentity();
    Real32 randX = (Real32)(rand()%10);
    Real32 randY = (Real32)(rand()%10);
    m.setTranslate(randX, randY, 10.0);
    beginEditCP(boxTrans, Transform::MatrixFieldMask);
        boxTrans->setMatrix(m);
    endEditCP(boxTrans);
    //create ODE data
    PhysicsBodyPtr boxBody = PhysicsBody::create();
    boxBody->setWorld(physicsWorld);
    CPEdit(boxBody, PhysicsBody::PositionFieldMask);
        boxBody->setPosition(Vec3f(randX, randY, 10.0));
    PhysicsBoxGeomPtr boxGeom = PhysicsBoxGeom::create();
    CPEdit(boxGeom, PhysicsBoxGeom::BodyFieldMask | PhysicsBoxGeom::SpaceFieldMask);
        boxGeom->setBody(boxBody);
        boxGeom->setSpace(hashSpace);
    //add attachments
    beginEditCP(boxNode, Node::AttachmentsFieldMask);
        boxNode->addAttachment(boxGeom);
    endEditCP(boxNode);
    beginEditCP(boxTransNode, Node::AttachmentsFieldMask | Node::ChildrenFieldMask);
        boxTransNode->addAttachment(boxBody);
        boxTransNode->addChild(boxNode);
    endEditCP(boxTransNode);
    //add to SceneGraph
    beginEditCP(spaceGroupNode, Node::ChildrenFieldMask);
        spaceGroupNode->addChild(boxTransNode);
    endEditCP(spaceGroupNode);
}

//////////////////////////////////////////////////////////////////////////
//! build a sphere
//////////////////////////////////////////////////////////////////////////
void buildSphere(void)
{
    Matrix m;
    //create OpenSG mesh
    GeometryPtr sphere;
    NodePtr sphereNode = makeSphere(1, 1);
    sphere = GeometryPtr::dcast(sphereNode->getCore());
    SimpleMaterialPtr sphere_mat = SimpleMaterial::create();
    beginEditCP(sphere_mat);
    sphere_mat->setAmbient(Color3f(0.0,0.0,0.0));
    sphere_mat->setDiffuse(Color3f(0.0,0.0,1.0));
    endEditCP(sphere_mat);
    beginEditCP(sphere, Geometry::MaterialFieldMask);
    sphere->setMaterial(sphere_mat);
    endEditCP(sphere);
    TransformPtr sphereTrans;
    NodePtr sphereTransNode = makeCoredNode<Transform>(&sphereTrans);
    m.setIdentity();
    Real32 randX = (Real32)(rand()%10);
    Real32 randY = (Real32)(rand()%10);
    m.setTranslate(randX, randY, 10.0);
    beginEditCP(sphereTrans, Transform::MatrixFieldMask);
    sphereTrans->setMatrix(m);
    endEditCP(sphereTrans);
    //create ODE data
    PhysicsBodyPtr sphereBody = PhysicsBody::create();
    sphereBody->setWorld(physicsWorld);
    CPEdit(sphereBody, PhysicsBody::PositionFieldMask);
    sphereBody->setPosition(Vec3f(randX, randY, 10.0));
    PhysicsSphereGeomPtr sphereGeom = PhysicsSphereGeom::create();
    CPEdit(sphereGeom, PhysicsSphereGeom::BodyFieldMask | PhysicsSphereGeom::SpaceFieldMask);
        sphereGeom->setBody(sphereBody);
        sphereGeom->setSpace(hashSpace);
    
    //add attachments
    beginEditCP(sphereNode, Node::AttachmentsFieldMask);
    sphereNode->addAttachment(sphereGeom);
    endEditCP(sphereNode);
    beginEditCP(sphereTransNode, Node::AttachmentsFieldMask | Node::ChildrenFieldMask);
    sphereTransNode->addAttachment(sphereBody);
    sphereTransNode->addChild(sphereNode);
    endEditCP(sphereTransNode);
    //add to SceneGraph
    beginEditCP(spaceGroupNode, Node::ChildrenFieldMask);
    spaceGroupNode->addChild(sphereTransNode);
    endEditCP(spaceGroupNode);
}

//////////////////////////////////////////////////////////////////////////
//! trimesh defined by filenode will be loaded
//////////////////////////////////////////////////////////////////////////
void buildTriMesh(void)
{
    NodePtr tri = makeTorus(0.5, 1.0, 24, 12);
    if(tri!=NullFC)
    {
        GeometryPtr triGeo = GeometryPtr::dcast(tri->getCore()); 
        Matrix m;
        SimpleMaterialPtr tri_mat = SimpleMaterial::create();
        beginEditCP(tri_mat);
        tri_mat->setAmbient(Color3f(0.1,0.1,0.2));
        tri_mat->setDiffuse(Color3f(1.0,0.1,0.7));
        endEditCP(tri_mat);
        triGeo->setMaterial(tri_mat);
        TransformPtr triTrans;
        NodePtr triTransNode = makeCoredNode<Transform>(&triTrans);
        m.setIdentity();
        Real32 randX = (Real32)(rand()%10);
        Real32 randY = (Real32)(rand()%10);
        m.setTranslate(0, 0, 18.0);
        triTrans->setMatrix(m);
        //create ODE data
        PhysicsBodyPtr triBody = PhysicsBody::create();
        triBody->setWorld(physicsWorld);
        triBody->setPosition(Vec3f(0, 0, 18.0));
        PhysicsTriMeshGeomPtr triGeom = PhysicsTriMeshGeom::create();
        CPEdit(triGeom, PhysicsTriMeshGeom::BodyFieldMask | 
                        PhysicsTriMeshGeom::SpaceFieldMask | 
                        PhysicsTriMeshGeom::GeometryNodeFieldMask);
            triGeom->setBody(triBody);
            //add geom to space for collision
            triGeom->setSpace(hashSpace);
            //set the geometryNode to fill the ode-triMesh
            triGeom->setGeometryNode(tri);
        
        //add attachments
        tri->addAttachment(triGeom);
        triTransNode->addAttachment(triBody);
        //add to SceneGraph
        triTransNode->addChild(tri);
        spaceGroupNode->addChild(triTransNode);
    }
    else
    {
        SLOG << "Could not read MeshData!" << endLog;
    }
}

//
// GLUT callback functions
//

// redraw the window
void display(void)
{
	mgr->redraw();
}

// react to size changes
void reshape(int w, int h)
{
	mgr->resize(w, h);
	glutPostRedisplay();
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
	if (state)
		mgr->mouseButtonRelease(button, x, y);
	else
		mgr->mouseButtonPress(button, x, y);

	glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
	mgr->mouseMove(x, y);
	glutPostRedisplay();
}

// react to keys
void keyboard(unsigned char k, int x, int y)
{
	switch(k)
	{
	case 27:        
		{
			OSG::osgExit();
			exit(0);
		}
	break;
    case 's':
		{
            buildSphere();
		}
	break;
	case 'b':
		{
			buildBox();
		}
	break;
    case 'z':
        {
            SceneFileHandler::the().write(rootNode, "scene.osb");
        }
    break;
    case 't':
        {
            buildTriMesh();
        }
    break;
	}
}

/************************************************************************/
/* the callback function for collision handling                         */
/************************************************************************/

void physCollisionCallback(void* somedata, dGeomID o1, dGeomID o2)
{
    Int32 numContacts = dCollide(o1, o2, 32, 
        &physContactArray[0].geom, sizeof(dContact));
    //SLOG << "found contacts: " << numContacts << endLog;
    for (Int32 i=0; i < numContacts; i++)
    {
        dJointID jointId = dJointCreateContact(physHandler->getWorld()->getWorldID(), 
            physColJointGroupId, 
            &physContactArray[i]);

        dJointAttach(jointId, dGeomGetBody(o1), dGeomGetBody(o2));
    }
}
/************************************************************************/
/* this method should be called whenever you want to update the physics */
/************************************************************************/

void doPhysicsOnNode(NodePtr node)
{
    //PhysicsHandlerPtr tmpPtr(*this);
    //free contact Joints
    dJointGroupEmpty(physColJointGroupId);
    //collide
    physHandler->getSpace()->Collide(0 , physCollisionCallback);
    //step the world
    physHandler->getWorld()->worldQuickStep(0.03);

    //update matrices
    physHandler->updateWorld(node);
}

void doPhysics(int n)
{
    doPhysicsOnNode(rootNode);
    glutPostRedisplay();
    glutTimerFunc(1000/60, doPhysics, 1);
}



// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

	int winid = glutCreateWindow("ODE<->OpenSG");

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	//glutIdleFunc(display);
    //do physics on consant framerate (60 Hz)
    glutTimerFunc(1000/60, doPhysics, 1);

	return winid;
}
