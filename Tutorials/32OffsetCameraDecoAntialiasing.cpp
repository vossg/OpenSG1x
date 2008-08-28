// OpenSG Tutorial Example: Antialiasing using OffsetCameraDecorator

// GLUT is used for window handling
#include <OpenSG/OSGGLUT.h>

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// The GLUT-OpenSG connection class
#include <OpenSG/OSGGLUTWindow.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>

#include <OpenSG/OSGOffsetCameraDecorator.h>
#include <OpenSG/OSGRenderAction.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGSceneFileHandler.h>

const osg::Vec2f JITTER1[] = {osg::Vec2f(0.5, 0.5)};
const osg::Vec2f JITTER2[] = {osg::Vec2f(0.25, 0.75), 
                              osg::Vec2f(0.75, 0.25)};
const osg::Vec2f JITTER3[] = {osg::Vec2f(0.5033922635, 0.8317967229), 
                              osg::Vec2f(0.7806016275, 0.2504380877),
                              osg::Vec2f(0.2261828938, 0.4131553612)};
const osg::Vec2f JITTER4[] = {osg::Vec2f(0.375, 0.25), 
                              osg::Vec2f(0.125, 0.75), 
                              osg::Vec2f(0.875, 0.25), 
                              osg::Vec2f(0.625, 0.75)};
const osg::Vec2f JITTER5[] = {osg::Vec2f(0.5, 0.5), 
                              osg::Vec2f(0.3, 0.1), 
                              osg::Vec2f(0.7, 0.9), 
                              osg::Vec2f(0.9, 0.3), 
                              osg::Vec2f(0.1, 0.7)};
const osg::Vec2f JITTER6[] = {osg::Vec2f(0.4646464646, 0.4646464646), 
                              osg::Vec2f(0.1313131313, 0.7979797979),
                              osg::Vec2f(0.5353535353, 0.8686868686), 
                              osg::Vec2f(0.8686868686, 0.5353535353),
                              osg::Vec2f(0.7979797979, 0.1313131313), 
                              osg::Vec2f(0.2020202020, 0.2020202020)};
const osg::Vec2f JITTER8[] = {osg::Vec2f(0.5625, 0.4375), 
                              osg::Vec2f(0.0625, 0.9375), 
                              osg::Vec2f(0.3125, 0.6875), 
                              osg::Vec2f(0.6875, 0.8125),  
                              osg::Vec2f(0.8125, 0.1875), 
                              osg::Vec2f(0.9375, 0.5625), 
                              osg::Vec2f(0.4375, 0.0625), 
                              osg::Vec2f(0.1875, 0.3125)};
const osg::Vec2f JITTER9[] = {osg::Vec2f(0.5, 0.5), 
                              osg::Vec2f(0.1666666666, 0.9444444444), 
                              osg::Vec2f(0.5, 0.1666666666), 
                              osg::Vec2f(0.5, 0.8333333333), 
                              osg::Vec2f(0.1666666666, 0.2777777777), 
                              osg::Vec2f(0.8333333333, 0.3888888888), 
                              osg::Vec2f(0.1666666666, 0.6111111111),
                              osg::Vec2f(0.8333333333, 0.7222222222), 
                              osg::Vec2f(0.8333333333, 0.0555555555)};
const osg::Vec2f JITTER12[] = {osg::Vec2f(0.4166666666, 0.625), 
                               osg::Vec2f(0.9166666666, 0.875), 
                               osg::Vec2f(0.25, 0.375),
                               osg::Vec2f(0.4166666666, 0.125), 
                               osg::Vec2f(0.75, 0.125), 
                               osg::Vec2f(0.0833333333, 0.125), 
                               osg::Vec2f(0.75, 0.625),
                               osg::Vec2f(0.25, 0.875), 
                               osg::Vec2f(0.5833333333, 0.375), 
                               osg::Vec2f(0.9166666666, 0.375),
                               osg::Vec2f(0.0833333333, 0.625), 
                               osg::Vec2f(0.583333333, 0.875)};
const osg::Vec2f JITTER16[] = {osg::Vec2f(0.375, 0.4375), 
                               osg::Vec2f(0.625, 0.0625), 
                               osg::Vec2f(0.875, 0.1875), 
                               osg::Vec2f(0.125, 0.0625), 
                               osg::Vec2f(0.375, 0.6875), 
                               osg::Vec2f(0.875, 0.4375), 
                               osg::Vec2f(0.625, 0.5625), 
                               osg::Vec2f(0.375, 0.9375), 
                               osg::Vec2f(0.625, 0.3125), 
                               osg::Vec2f(0.125, 0.5625), 
                               osg::Vec2f(0.125, 0.8125), 
                               osg::Vec2f(0.375, 0.1875), 
                               osg::Vec2f(0.875, 0.9375), 
                               osg::Vec2f(0.875, 0.6875), 
                               osg::Vec2f(0.125, 0.3125), 
                               osg::Vec2f(0.625, 0.8125)};

const osg::Vec2f * JITTER[]     = {JITTER1, JITTER2, JITTER3, JITTER4,
                                   JITTER5, JITTER6, JITTER8, JITTER9,
                                   JITTER12, JITTER16                  };
const int          JITTERSIZE[] = {1, 2, 3, 4, 5, 6, 8, 9, 12, 16      };

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
OffsetCameraDecoratorPtr cameraDecorator;
RenderAction* raction;
int activeJitter = 4;
float jitterRadius = 1.0f;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

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

    // create the scene
    NodePtr scene = SceneFileHandler::the().read("Data/dinopet.3ds");

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);
    mgr->redraw();

    raction = RenderAction::create();
    cameraDecorator = OffsetCameraDecorator::create();
    beginEditCP(cameraDecorator);
        cameraDecorator->setDecoratee(mgr->getWindow()->getPort(0)->getCamera());
    endEditCP(cameraDecorator);

    beginEditCP(mgr->getWindow()->getPort(0));
        mgr->getWindow()->getPort(0)->setCamera(cameraDecorator);
    endEditCP(mgr->getWindow()->getPort(0));


    // show the whole scene
    mgr->showAll();
    
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
    mgr->getNavigator()->updateCameraTransformation();

    mgr->getWindow()->activate();
    mgr->getWindow()->frameInit();

    raction->setWindow(getCPtr(mgr->getWindow()));

    ViewportPtr viewport = mgr->getWindow()->getPort(0);

    glClear(GL_ACCUM_BUFFER_BIT);

    for (int i=0; i < JITTERSIZE[activeJitter]; i++) {
        beginEditCP(cameraDecorator);
            cameraDecorator->setOffset(
                (JITTER[activeJitter][i].x() - 0.5) * jitterRadius,
                (JITTER[activeJitter][i].y() - 0.5) * jitterRadius);
        endEditCP(cameraDecorator);

        viewport->render(raction);
    
        glAccum(GL_ACCUM, 1.0f / float(JITTERSIZE[activeJitter]));
        glAccum(GL_RETURN, float(JITTERSIZE[activeJitter]) / float(i + 1));
    }

    glAccum(GL_RETURN, 1.0f);

    mgr->getWindow()->swap();
    mgr->getWindow()->frameExit();
}

// react to size changes
void reshape(int w, int h)
{
    mgr->resize(w, h);
    
    if (cameraDecorator) {
        beginEditCP(cameraDecorator);
            cameraDecorator->setFullSize(w, h);
        endEditCP(cameraDecorator);
    }
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
    if(k==27)
    {
        OSG::osgExit();
        exit(0);
    }
    else if(k >= 48 && k<=57)
    {
        // '0' to '9'
        activeJitter = k-48;
        
        std::cout << "Number of samples: " << JITTERSIZE[activeJitter]
                  << std::endl;
    }
    else if(k == 43)
    {
        // '+'
        jitterRadius += 1.0;
        
        std::cout << "Jitter radius: " << jitterRadius << std::endl;
    }
    else if(k == 45)
    {
        // '-'
        if (jitterRadius >= 1.0)
            jitterRadius -= 1.0;
            
        std::cout << "Jitter radius: " << jitterRadius << std::endl;
    }
    else
    {
        std::cout <<   "Keys 0-9 select number of samples"
                  << "\nKey  +   increase jitter radius"
                  << "\nKey  -   decrease jitter radius"
                  << std::endl;
    }
    
    glutPostRedisplay();
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE | GLUT_ACCUM );
    
    int winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}
