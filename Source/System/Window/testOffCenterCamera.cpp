
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGPassiveWindow.h>
#include <OSGSimpleSceneManager.h>

#include <OSGPerspectiveCamera.h>
#include <OSGStereoBufferViewport.h>
#include <OSGColorBufferViewport.h>
#include <OSGOffCenterPerspectiveCamera.h>
#include <OSGSceneFileHandler.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

Vec2f principalpoint;
OffCenterPerspectiveCameraPtr cam;

// redraw the window
void display(void)
{   
    mgr->redraw();

    // all done, swap    
    glutSwapBuffers();
}

// react to size changes
void reshape(int w, int h)
{
    mgr->resize(w,h);
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
void keyboard(unsigned char k, int, int)
{
    switch(k)
    {
    case 27:    exit(1);
    case 'w':   principalpoint[1] += .1;
                break;
    case 's':   principalpoint[1] -= .1;
                break;
    case 'd':   principalpoint[0] += .1;
                break;
    case 'a':   principalpoint[0] -= .1;
                break;
    }
    
    std::cout << "Principal Point:" << principalpoint << std::endl;
    
    beginEditCP(cam);
    cam->setPrincipalPoint(principalpoint);
    endEditCP  (cam);
}


int main(int argc, char **argv)
{
    osgInit(argc,argv);

    // GLUT init
    glutInit(&argc, argv);
    
    bool stereobuffer = false;
    if(argc >= 2 && !strcmp(argv[1],"-s"))
    {
        stereobuffer = true;
        --argc, ++argv;
    }
    
    
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE |
                        (stereobuffer?GLUT_STEREO:0) );
    
    glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    PassiveWindowPtr pwin=PassiveWindow::create();
    pwin->init();

    // create the scene
    NodePtr scene;
    
    if(argc > 1)
    {
        scene = SceneFileHandler::the().read(argv[1]);
    }
    else
    {
        scene = makeBox(2,2,2, 1,1,1);
    }

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // create the window and initial camera/viewport
    mgr->setWindow(pwin );
    // tell the manager what to manage
    mgr->setRoot  (scene);
    
    cam = OffCenterPerspectiveCamera::create();
    
    // now change the camera
    ViewportPtr vp = pwin->getPort(0);
    
    PerspectiveCameraPtr ocam = PerspectiveCameraPtr::dcast(vp->getCamera());
    beginEditCP(cam);
    cam->setFov(ocam->getFov());
    cam->setAspect(ocam->getAspect());
    cam->setBeacon(ocam->getBeacon());
    cam->setNear(ocam->getNear());
    cam->setFar(ocam->getFar());
    endEditCP  (cam);
    
    beginEditCP(vp);
    vp->setCamera(cam);
    endEditCP(vp);
    
    mgr->showAll();
    
    // GLUT main loop
    glutMainLoop();

    return 0;
}
