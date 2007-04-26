// OpenSG example: testSHL
//
// Demonstrates the use of the ClipPlane

// Headers
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUT.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGAction.h>
#include <OSGSFSysTypes.h>
#include <OSGMFVecTypes.h>
#include <OSGSceneFileHandler.h>
#include <OSGBaseFunctions.h>
#include <OSGSceneFileHandler.h>

#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGTransform.h>
#include <OSGClipPlane.h>

#include <OSGImage.h>
#include <OSGChunkMaterial.h>
#include <OSGMaterialChunk.h>


// Activate the OpenSG namespace
OSG_USING_NAMESPACE


// ------------------- global vars ----------------------
//
// The SimpleSceneManager to manage simple applications
static SimpleSceneManager *_mgr;

static NodePtr _scene = NullFC;
static TransformPtr _beacon_trans = NullFC;
static ClipPlanePtr _cp = NullFC;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    printf("press key y/x to move the clipping plane, press c to toggle clipping plane.\n");

    // OSG init
    osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    gwin->setSize( 800, 800 );
    gwin->init();

    NodePtr file = NullFC;
    if(argc > 1)
    {
        file = SceneFileHandler::the().read(argv[1], NULL);
    }
    else
    {
        // create a box.
        file = makeBox(1.0f, 1.0f, 1.0f, 1, 1, 1);
    }

    _beacon_trans = Transform::create();
    NodePtr beacon = Node::create();
    beginEditCP(beacon);
        beacon->setCore(_beacon_trans);
    endEditCP(beacon);


    _cp = ClipPlane::create();
    beginEditCP(_cp);
        _cp->setEquation(Vec4f(0.0f, 0.0f, -1.0f, 0.0f));
        _cp->setBeacon(beacon);
    endEditCP(_cp);

    NodePtr clipPlane = Node::create();
    beginEditCP(clipPlane);
        clipPlane->setCore(_cp);
        clipPlane->addChild(file);
    endEditCP(clipPlane);

    _scene = Node::create();
    beginEditCP(_scene);
        _scene->setCore(Group::create());
        _scene->addChild(beacon);
        _scene->addChild(clipPlane);
    endEditCP(_scene);

    // create the SimpleSceneManager helper
    _mgr = new SimpleSceneManager;

    // tell the manager what to manage
    _mgr->setWindow(gwin );
    _mgr->setRoot(_scene);

    // show the whole scene
    _mgr->showAll();

    // enable local lights.
    RenderAction *ract = (RenderAction *) _mgr->getAction();
    ract->setLocalLights(true);

    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

// redraw the window
void display(void)
{
  // render scene
  _mgr->redraw();
}

// react to size changes
void reshape(int w, int h)
{
    _mgr->resize(w, h);
    glutPostRedisplay();
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
    if (state)
        _mgr->mouseButtonRelease(button, x, y);
    else
        _mgr->mouseButtonPress(button, x, y);

    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    _mgr->mouseMove(x, y);
    glutPostRedisplay();
}

// react to keys
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:
        case 'q':
            exit(1);
        break;
        case 'w':
            SceneFileHandler::the().write(_scene, "scene.osb", true);
            printf("wrote scene.osb\n");
        break;
        case 'y':
        {
            beginEditCP(_beacon_trans);
                _beacon_trans->getMatrix()[3][0] -= 0.1f;
                _beacon_trans->getMatrix()[3][1] -= 0.1f;
                _beacon_trans->getMatrix()[3][2] -= 0.1f;
            endEditCP(_beacon_trans);
        }
        break;
        case 'x':
            beginEditCP(_beacon_trans);
                _beacon_trans->getMatrix()[3][0] += 0.1f;
                _beacon_trans->getMatrix()[3][1] += 0.1f;
                _beacon_trans->getMatrix()[3][2] += 0.1f;
            endEditCP(_beacon_trans);
        break;
        case 'c':
            beginEditCP(_cp);
                _cp->setOn(!_cp->getOn());
            endEditCP(_cp);
        break;
    }

    glutPostRedisplay();
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(512, 512);

    int winid = glutCreateWindow("OpenSG ClipPlane");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}


