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

//need to control the joint params

ShadowMapViewportPtr svp;
NodePtr scene;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );


//////////////////////////////////////////////////////////////////////////
//! Initialize GLUT & OpenSG and set up the scene
//////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();

    // load the scene

    if(argc < 2)
    {
        FWARNING(("No file given!!!!!!!!!!!!!!!!!!!!!!\n"));
        return -1;
    }
    else
    {
        /*
        All scene file loading is handled via the SceneFileHandler.
        */
        scene = SceneFileHandler::the().read(argv[1]);
    }
    assert(scene != NullFC);

    //get physics
    PhysicsHandlerFinder pFinder;
    physHandler = pFinder(scene);
    assert(physHandler!=NullFC);
    //traverse once ode nodes and init them to synchronize ode with opensg data
    physHandler->odeInit(scene);
    physicsWorld = physHandler->getWorld();
    hashSpace = PhysicsHashSpacePtr::dcast(physHandler->getSpace());


	beginEditCP(gwin);//Window
		gwin->setId(winid);
		gwin->addPort(svp);
		gwin->init();
	endEditCP(gwin);
	
    physContactArray = new dContact[32];
    physColJointGroupId = dJointGroupCreate(0);
    for (Int32 index = 0; index < 32; index++)
    {
        physContactArray[index].surface.mode = dContactApprox1;
        physContactArray[index].surface.mu = 0.75;
    }


	/************************************************************************/
	/* print some dWorld params                                             */
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

	// create the SimpleSceneManager helper
	mgr = new SimpleSceneManager;

	// tell the manager what to manage
	mgr->setWindow(gwin );
    mgr->setRoot(scene);
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
        box_mat->setAmbient(Color3f(0.2,0.2,0.0));
        box_mat->setDiffuse(Color3f(0.0,0.0,1.0));
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
    beginEditCP(scene, Node::ChildrenFieldMask);
        scene->addChild(boxTransNode);
    endEditCP(scene);
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
    sphere_mat->setAmbient(Color3f(0.9,0.2,0.0));
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
    beginEditCP(scene, Node::ChildrenFieldMask);
    scene->addChild(sphereTransNode);
    endEditCP(scene);
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
            SceneFileHandler::the().write(scene, "scene.osg");
        }
    break;
	}
}

/************************************************************************/
/* the callback function for collision handling                         */
/************************************************************************/

void physCollisionCallback(void* somedata, dGeomID o1, dGeomID o2)
{
    //set the max num contacts you want to be checked
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
    doPhysicsOnNode(scene);
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
