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

OSG_USING_NAMESPACE

NodePtr scene;

PerspectiveCameraPtr leftCamera;
PerspectiveCameraPtr rightCamera;

ViewportPtr leftViewport;
ViewportPtr rightViewport;

WindowPtr window;

NodePtr leftCamBeacon, rightCamBeacon, lightBeacon, lightNode;

RenderAction *renderAction;

int setupGLUT( int *argc, char *argv[] );

NodePtr createScenegraph(){
    //create geometry - just a simple torus
	NodePtr torus = makeTorus(1,5,8,16);
	
	//create transformations & beacons for cameras & light
	leftCamBeacon = Node::create();
	rightCamBeacon = Node::create();
	lightBeacon = Node::create();
	
	// the following style is a bit different than from before
	// this is only to remind you that beginEditCP()'s can also
	// be interleaved
	
	beginEditCP(leftCamBeacon);
	beginEditCP(rightCamBeacon);
	beginEditCP(lightBeacon);
		
		//create Transformations
		TransformPtr leftCamTrans, rightCamTrans, lightTrans;
		
		leftCamTrans = Transform::create();
		rightCamTrans = Transform::create();
		lightTrans = Transform::create();
		
		beginEditCP(leftCamTrans);
		beginEditCP(rightCamTrans);
		beginEditCP(lightTrans);
			
			Matrix leftM, rightM, lightM;
			leftM.setTransform(Vec3f(-5,6,10));
			rightM.setTransform(Vec3f(5,-6,10));
			lightM.setTransform(Vec3f(1,10,2));
			
			leftCamTrans->setMatrix(leftM);
			rightCamTrans->setMatrix(rightM);
			lightTrans->setMatrix(lightM);
			
		endEditCP(leftCamTrans);
		endEditCP(rightCamTrans);
		endEditCP(lightTrans);
		
		leftCamBeacon->setCore(leftCamTrans);
		rightCamBeacon->setCore(rightCamTrans);
		lightBeacon->setCore(lightTrans);
	endEditCP(leftCamBeacon);
	endEditCP(rightCamBeacon);
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
		root->addChild(leftCamBeacon);
		root->addChild(rightCamBeacon);
		root->addChild(lightBeacon);
	endEditCP(root);
	
	return root;
}

int main(int argc, char **argv)
{
    osgInit(argc,argv);
        
    int winid = setupGLUT(&argc, argv);

    scene =createScenegraph();

    //we beginn with creating our cameras
	
	leftCamera = PerspectiveCamera::create();
	rightCamera = PerspectiveCamera::create();
    
	beginEditCP(leftCamera);
		leftCamera->setBeacon(leftCamBeacon);
		leftCamera->setFov(deg2rad(90));
		leftCamera->setNear(0.1);
		leftCamera->setFar(100);
	endEditCP(leftCamera);
	
	beginEditCP(rightCamera);
		rightCamera->setBeacon(rightCamBeacon);
		rightCamera->setFov(deg2rad(90));
		rightCamera->setNear(0.1);
		rightCamera->setFar(100);
	endEditCP(rightCamera);
	
	//next we create the backgrounds
	
	GradientBackgroundPtr leftBkg = GradientBackground::create();
	beginEditCP(leftBkg);
		leftBkg->addLine(Color3f(0,0,0),0);
		leftBkg->addLine(Color3f(1,1,1),1);
	endEditCP(leftBkg);
	
	//load the image file
	ImagePtr bkgImage = Image::create();
	beginEditCP(bkgImage);
		bkgImage->read("data/front.jpg");
	endEditCP(bkgImage);
	
	ImageBackgroundPtr rightBkg = ImageBackground::create();
	beginEditCP(rightBkg);
		rightBkg->setImage(bkgImage);
		rightBkg->setScale(true);
	endEditCP(rightBkg);
	//now the viewports
	
	leftViewport = Viewport::create();
	rightViewport = Viewport::create();
	
	beginEditCP(leftViewport);
		leftViewport->setCamera(leftCamera);
		leftViewport->setBackground(leftBkg);
		leftViewport->setRoot(scene);
		leftViewport->setSize(0,0,0.5,1);
	endEditCP(leftViewport);
	
	beginEditCP(rightViewport);
		rightViewport->setCamera(rightCamera);
		rightViewport->setBackground(rightBkg);
		rightViewport->setRoot(scene);
		rightViewport->setSize(0.5,0,1,1);
	endEditCP(rightViewport);
	
	// -- end of viewport creation

	// add an logo foreground to the right viwport
	
	//load the logo image file
	ImagePtr frgImage = Image::create();
	beginEditCP(frgImage);
		frgImage->read("data/logo.png");
	endEditCP(frgImage);
	
	ImageForegroundPtr imgFrg = ImageForeground::create();
	beginEditCP(imgFrg);
		//NOTE: the position values are between 0 and 1
		//and are relative to the viewport!
		imgFrg->addImage(frgImage,Pnt2f(0.1,0));
	endEditCP(imgFrg);
	
	//add the created foreground by appending it to
	//the vieports foreground multifield
	rightViewport->getMFForegrounds()->push_back(imgFrg);
	
	//create the foreground for screenshot functionality
	FileGrabForegroundPtr fileGrab = FileGrabForeground::create();
	beginEditCP(fileGrab);
		fileGrab->setActive(false);
		fileGrab->setName("data/screenshot%04d.jpg");
	endEditCP(fileGrab);
	
	//add this one to the right viewport, too
	rightViewport->getMFForegrounds()->push_back(fileGrab);
	
	//to make a screenshot the foreground has to be set to active
	//were doing that if the user pressen the 's' key
	//have a look at the keyboard callback function
	
	//and the render action - more on that later
	renderAction = RenderAction::create();

	//create the window now
	
	GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    gwin->setSize(600,300);
	window = gwin;
	
	window->addPort(leftViewport);
	window->addPort(rightViewport);
	
	window->init();
	
    glutMainLoop();

    return 0;
}

void reshape(int w, int h)
{
    window->resize(w, h);
    glutPostRedisplay();
}

void display(void)
{
	window->render(renderAction);
}

void mouse(int button, int state, int x, int y)
{
    /*
	if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);
     */   
    glutPostRedisplay();
}

void motion(int x, int y)
{
    //mgr->mouseMove(x, y);
    glutPostRedisplay();
}

void keyboard(unsigned char k, int x, int y){
    switch(k){
        case 27:    {
            osgExit();
            exit(1);
        }
        break;
		
		case 's':
			// The return value is actually a pointer to on osgPtr class
			// I don't know if that makes much sense at all...
			MFForegroundPtr foregrounds = *(window->getPort(1)->getMFForegrounds());
			FileGrabForegroundPtr fg = FileGrabForegroundPtr::dcast(foregrounds[1]);
			
			if (!fg->getActive()){
				std::cout << "start recording..." << std::endl;
				fg->setActive(true);
			}else{
				std::cout << "stopped" << std::endl;
				fg->setActive(false);
			}
		break;
	}
}

int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG First Application");
    
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
    glutIdleFunc(display);
    return winid;
}
