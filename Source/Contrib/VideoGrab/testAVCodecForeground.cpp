// Headers
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGAction.h>
#include <OSGGroup.h>
#include <OSGSceneFileHandler.h>

#include "OSGAVCodecGrabForeground.h"

#include <string>
#include <iostream>

using namespace std;

std::string   filename="opensg.avi";


// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

AVCodecGrabForegroundPtr avfground;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

void writeframe(int val);

// react to keys
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
    case 'r':
        std::cout << "Start recording to " << filename << std::endl;
        avfground->setAutoWrite(false);
        avfground->setActive(true);
        glutTimerFunc(40, writeframe, 1);
        break;
        
    case 'R':
        std::cout << "Start recording every frame to " << filename << std::endl;
        avfground->setAutoWrite(true);
        avfground->setActive(true);
        glutTimerFunc(1000, writeframe, 0);
        break;

    case 's':
        std::cout << "Stop recording" << std::endl;
        avfground->setActive(false);
        glutTimerFunc(1000, writeframe, 0);

        break;

    case 27 :   exit(1);
    }
}

// Initialize GLUT & OpenSG and set up the scene
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
    // Choose a window size divisible by 16.
    glutReshapeWindow(352, 288);

    if ( argc >= 2  && argv[2] )
    {
      filename=std::string(argv[2]);
    }

    // The scene group

    NodePtr  scene;

    if(argc < 2)
    {
        scene = makeTorus(.5, 2, 16, 16);
    }
    else
    {
        scene = SceneFileHandler::the().read(argv[1]);
    }

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);

    avfground= AVCodecGrabForeground::create();
    beginEditCP(avfground);
    avfground->setName(filename.c_str());
    avfground->setKbit(1400);
    avfground->setCodecid(38); // FFV1
    endEditCP(avfground);

    beginEditCP(gwin->getPort(0));
    gwin->getPort(0)->getForegrounds().push_back(avfground);
    endEditCP  (gwin->getPort(0));

    // show the logo
    mgr->useOpenSGLogo();

    // show the whole scene
    mgr->showAll();
    
    try
    {
        // GLUT main loop
        glutMainLoop();
    }   
    catch(OSG_STDEXCEPTION_NAMESPACE::exception &e)
    {
        SFATAL << e.what() << std::endl;
    }

    return 0;
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

void writeframe( int val )
{
  if ( val )
  {
    avfground->writeFrame();
    glutTimerFunc(40, writeframe, 1);
  }

  return;
}


// setup the GLUT library which handles the windows for us
int setupGLUT(int* argc, char* argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    // The window HAS to have a size that's dividible by 8 or 16, depending
    // on the codec. Use 16 to be safe.
    
    glutInitWindowSize(304,304);

    int winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);


    return winid;
}
