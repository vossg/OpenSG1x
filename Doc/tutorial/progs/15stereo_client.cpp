// all needed include files
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSolidBackground.h>
#include <OpenSG/OSGDirectionalLight.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGRenderAction.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGGradientBackground.h>
#include <OpenSG/OSGImageBackground.h>
#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGImageForeground.h>
#include <OpenSG/OSGFileGrabForeground.h>
#include <OpenSG/OSGShearedStereoCameraDecorator.h>
#include <OpenSG/OSGMultiDisplayWindow.h>

OSG_USING_NAMESPACE
using namespace std;

NodePtr scene;

// one camera will be used only  - the
// decorators will distinguish of left and right
// eye position
PerspectiveCameraPtr camera;

// we need two viewports - one for the left
// and one for the right eye
ViewportPtr leftViewport;
ViewportPtr rightViewport;

MultiDisplayWindowPtr multiWindow;

NodePtr camBeacon, lightBeacon, lightNode;

RenderAction *renderAction;

int setupGLUT( int *argc, char *argv[] );

NodePtr createScenegraph(){
    //create geometry - just a simple torus
	NodePtr torus = makeTorus(1,5,8,16);
	
	//create transformations & beacons for cameras & light
	camBeacon = Node::create();
	lightBeacon = Node::create();
	
	// the following style is a bit different than from before
	// this is only to remind you that beginEditCP()'s can also
	// be interleaved
	
	beginEditCP(camBeacon);
	beginEditCP(lightBeacon);
		
		//create Transformations
		TransformPtr camTrans, lightTrans;
		
		camTrans = Transform::create();
		lightTrans = Transform::create();
		
		beginEditCP(camTrans);
		beginEditCP(lightTrans);
			
			Matrix camM, lightM;
			camM.setTransform(Vec3f(0,1,10));
			lightM.setTransform(Vec3f(1,10,2));
			
			camTrans->setMatrix(camM);
			lightTrans->setMatrix(lightM);
			
		endEditCP(camTrans);
		endEditCP(lightTrans);
		
		camBeacon->setCore(camTrans);
		lightBeacon->setCore(lightTrans);
	endEditCP(camBeacon);
	endEditCP(lightBeacon);
	// -- end of camera beacon creation
	
	//create the light source
	DirectionalLightPtr dLight = DirectionalLight::create();

	beginEditCP(dLight);
		dLight->setDirection(Vec3f(0,1,2));
		
		//color information
		dLight->setDiffuse(Color4f(1,1,1,1));
		dLight->setAmbient(Color4f(0.2,0.2,0.2,1));
		dLight->setSpecular(Color4f(1,1,1,1));
		
		//set the beacon
		dLight->setBeacon(lightBeacon);
	endEditCP  (dLight);
	
	// create the node that will contain the light source
	
	lightNode = Node::create();
	beginEditCP(lightNode);
		lightNode->setCore(dLight);
		lightNode->addChild(torus);
	endEditCP(lightNode);
	
	// now create the root and add all children
	
	NodePtr root = Node::create();
	beginEditCP(root);
		root->setCore(Group::create());
		root->addChild(lightNode);
		root->addChild(camBeacon);
		root->addChild(lightBeacon);
	endEditCP(root);
	
	return root;
}

int main(int argc, char **argv)
{
    osgInit(argc,argv);
        
    int winid = setupGLUT(&argc, argv);
	
	//create the main window for navigation
	GLUTWindowPtr navWindow = GLUTWindow::create();
    navWindow->setId(winid);
    navWindow->setSize(300,300);
	navWindow->init();
	
	scene =createScenegraph();
	
    //we beginn with creating our cameras
	camera = PerspectiveCamera::create();
	
	beginEditCP(camera);
		camera->setBeacon(camBeacon);
		camera->setFov(deg2rad(90));
		camera->setNear(0.1);
		camera->setFar(100);
	endEditCP(camera);
		
	//next we create the backgrounds
	
	SolidBackgroundPtr bkg = SolidBackground::create();
	beginEditCP(bkg);
		bkg->setColor(Color3f(0,0,0));
	endEditCP(bkg);
	
	leftViewport = Viewport::create();
	rightViewport = Viewport::create();
	
	//the decorator decarates the camera and will create the left eye
	ShearedStereoCameraDecoratorPtr cameraDecorator = ShearedStereoCameraDecorator::create();
    beginEditCP(cameraDecorator);
        cameraDecorator->setLeftEye(true);
		//unit length assume that one unit equals one meter
        cameraDecorator->setEyeSeparation(0.06);
        cameraDecorator->setDecoratee(camera);
        cameraDecorator->setZeroParallaxDistance(2);
        beginEditCP(leftViewport);
            leftViewport->setCamera    (cameraDecorator);
            leftViewport->setBackground(bkg);
			leftViewport->setRoot      (scene);
            leftViewport->setSize      (0,0,.5,1);
        endEditCP(leftViewport);
    endEditCP(cameraDecorator);
	
	//thr right decorator for the right eye
	cameraDecorator=OSG::ShearedStereoCameraDecorator::create();
    beginEditCP(cameraDecorator);
        cameraDecorator->setLeftEye(false);
        cameraDecorator->setEyeSeparation(0.06);
        cameraDecorator->setDecoratee(camera);
        cameraDecorator->setZeroParallaxDistance(2);
        beginEditCP(rightViewport);
            rightViewport->setCamera    (cameraDecorator);
            rightViewport->setBackground(bkg);
            rightViewport->setRoot      (scene);
            rightViewport->setSize      (.5,0,1,1);
        endEditCP(rightViewport);
    endEditCP(cameraDecorator);

	multiWindow = MultiDisplayWindow::create();
	
	beginEditCP(multiWindow);
		multiWindow->setClientWindow(navWindow);
		multiWindow->setConnectionType("Multicast");
		multiWindow->getServers().push_back("Server1");
		multiWindow->getServers().push_back("Server2");
		multiWindow->setHServers(2);
		multiWindow->setVServers(1);
		multiWindow->addPort(leftViewport);
		multiWindow->addPort(rightViewport);
		multiWindow->init();
	endEditCP(multiWindow);
	
	// add an logo foreground to the right viwport
	
	//and the render action - more on that later
	renderAction = RenderAction::create();
	
	cout << "create scenegraph..." << endl;
	
    glutMainLoop();

    return 0;
}

void reshape(int w, int h)
{
    multiWindow->resize(w, h);
    glutPostRedisplay();
}

void display(void)
{
	multiWindow->render(renderAction);
	
	//the changelist should be cleared - else things
	//could be copied multiple times
	OSG::Thread::getCurrentChangeList()->clearAll();
	
	// to ensure a black navigation window
	glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
    glutPostRedisplay();
}

void motion(int x, int y)
{
    glutPostRedisplay();
}

void keyboard(unsigned char k, int x, int y){
    switch(k){
        case 27:    {
            osgExit();
            exit(1);
        }
        break;
	}
}

int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG Navigation Window");
    
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(display);
    return winid;
}
