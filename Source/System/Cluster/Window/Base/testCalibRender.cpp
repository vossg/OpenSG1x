// Minimalistic OpenSG program

#include <fstream>

// GLUT is used for window handling
#include <OSGGLUT.h>

// General OpenSG configuration, needed everywhere
#include <OSGConfig.h>

// The GLUT-OpenSG connection class
#include <OSGGLUTWindow.h>

// A little helper to simplify scene management and interaction
#include <OSGSimpleSceneManager.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OSGSimpleGeometry.h>

#include <OSGSolidBackground.h>

#include <OSGImageFileHandler.h>
#include <OSGPathHandler.h>

#include <OSGSceneFileHandler.h>
#include <OSGGraphOpSeq.h>
#include <OSGVerifyGeoGraphOp.h>
#include <OSGStripeGraphOp.h>

#include <OSGDisplayCalibration.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

int mode;
SimpleSceneManager *mgr;
DisplayCalibrationPtr calib;
NodePtr scene = NullFC;

// Standard GLUT callback functions
void display( void )
{
    mgr->getNavigator()->updateCameraTransformation();
    mgr->getWindow()->activate();
    mgr->getWindow()->frameInit();
    mgr->getWindow()->renderAllViewports((RenderActionBase*)mgr->getAction());
    calib->calibrate(mgr->getWindow(),(RenderActionBase*)mgr->getAction());
    mgr->getWindow()->swap();
    mgr->getWindow()->frameExit();

    if(mode==4)
    {
        beginEditCP(calib);
        Vec2f pos = calib->getGrid()[4];
        pos[0] = fmod(pos[0]+.01,1);
        pos[1] = fmod(pos[1]+.01,1);
        calib->getGrid()[4] = pos;
        endEditCP(calib);
    }
}

void reshape( int w, int h )
{
    mgr->resize( w, h );
    glutPostRedisplay();
}

void
motion(int x, int y)
{
    mgr->mouseMove( x, y );
    glutPostRedisplay();
}

void
mouse(int button, int state, int x, int y)
{
    if ( state )
        mgr->mouseButtonRelease( button, x, y );
    else
        mgr->mouseButtonPress( button, x, y );
    glutPostRedisplay();
}

void
key(unsigned char key, int , int )
{
    switch(key)
    {
    case 27:    exit(1);
    case 'a':   mgr->setHighlight(scene);
                break;
    case 's':   mgr->setHighlight(NullFC);
                break;
    case 'l':   mgr->useOpenSGLogo();
                break;
    case 'f':   mgr->setNavigationMode(Navigator::FLY);
                break;
    case 't':   mgr->setNavigationMode(Navigator::TRACKBALL);
                break;
    case 'q':   mgr->setStatistics(true);
                break;
    case 'w':   mgr->setStatistics(false);
                break;
    case '1':   
        mode=1;
        beginEditCP(calib);
        calib->setGridWidth(2);
        calib->setGridHeight(2);
        calib->getGrid().clear();
        calib->getGrid().push_back(Vec2f(0,0));
        calib->getGrid().push_back(Vec2f(1,0));
        calib->getGrid().push_back(Vec2f(0,1));
        calib->getGrid().push_back(Vec2f(1,1));
        endEditCP(calib);
        break;
    case '2':   
        mode=2;
        beginEditCP(calib);
        calib->setGridWidth(2);
        calib->setGridHeight(2);
        calib->getGrid().clear();
        calib->getGrid().push_back(Vec2f(0.1,0.1));
        calib->getGrid().push_back(Vec2f(0.9,0.1));
        calib->getGrid().push_back(Vec2f(0.1,0.9));
        calib->getGrid().push_back(Vec2f(0.9,0.9));
        endEditCP(calib);
        break;
    case '3':
    {
        mode=3;
        beginEditCP(calib);
        calib->setGridWidth(21);
        calib->setGridHeight(21);
        calib->getGrid().clear();
        int x,y;
        float xx,yy;
        for(y=-10 ; y<=10 ; ++y)
            for(x=-10 ; x<=10 ; ++x)
            {
                xx = x/20.0*sqrtf(10.0f*10.0f-y*y)/10.0f + .5f;
                yy = (y+10.0f)/20.0f;
                calib->getGrid().push_back(Vec2f(xx,yy));
            }
        endEditCP(calib);
    }
    break;
    case '4':
    {
        mode=4;
        beginEditCP(calib);
        calib->setGridWidth(3);
        calib->setGridHeight(3);
        calib->getGrid().clear();
        int x,y;
        float xx,yy;
        for(y=0 ; y<=2 ; ++y)
            for(x=0 ; x<=2 ; ++x)
                calib->getGrid().push_back(Vec2f(x/2.0,y/2.0));
        endEditCP(calib);
    }
    break;
    case 'd':
        beginEditCP(calib);
        calib->setScaleDown(.1);
        endEditCP(calib);
        break;
    case 'D':
        beginEditCP(calib);
        calib->setScaleDown(1);
        endEditCP(calib);
        break;
    case 'c':
        beginEditCP(calib);
        calib->setColorMatrix(Matrix(0,0,1,0,
                                     1,0,0,0,
                                     0,1,0,0,
                                     0,0,0,1));
        endEditCP(calib);
        break;
    case 'C':
        beginEditCP(calib);
        calib->setColorMatrix(Matrix(1,0,0,0,
                                     0,1,0,0,
                                     0,0,1,0,
                                     0,0,0,1));
        endEditCP(calib);
        break;
    break;
    }
    glutPostRedisplay();
}

// Initialize GLUT & OpenSG and set up the scene
int main (int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // GLUT init
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    int winid = glutCreateWindow("OpenSG");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(key);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();

    // create the scene

    const char *fileName = (argc > 1) ? argv[1] : "test.raw";
    scene = SceneFileHandler::the().read(fileName);
    if(scene == NullFC)
    {
        std::cerr << "Error loading " << fileName << "!" << std::endl;
        scene = makeTorus( .5, 2, 16, 16 );
    }

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    mgr->setWindow( gwin );
    mgr->setRoot( scene );
    mgr->showAll();

    WindowPtr win = mgr->getWindow();
    endEditCP(win);

    calib = DisplayCalibration::create();

    // GLUT main loop
    glutMainLoop();

    return 0;
}
