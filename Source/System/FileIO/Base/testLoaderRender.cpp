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

#include <OSGImageFileHandler.h>
#include <OSGPathHandler.h>

#include <OSGSceneFileHandler.h>
#include <OSGGraphOpSeq.h>
#include <OSGVerifyGeoGraphOp.h>
#include <OSGStripeGraphOp.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

NodePtr scene = NullFC;

// Standard GLUT callback functions
void display( void )
{
    mgr->redraw();
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
    }
    glutPostRedisplay();
}

static void progress(UInt32 p)
{
    std::cerr << "Loading " << p << "%" << '\r';
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
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(key);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();

    // create the scene

    const char *fileName = (argc > 1) ? argv[1] : "test.raw";

    SceneFileHandler::the().print();

    // As default the SceneFileHandler sets a PathHandler for geo and image files,
    // but it is also possible use your own PathHandler.
    /*
    // set image and scene path handler to find relative texture and scene paths.
    PathHandler pathHandler;
    pathHandler.push_frontCurrentDir();
    pathHandler.setBaseFile(fileName);
    ImageFileHandler::the().setPathHandler(&pathHandler);
    SceneFileHandler::the().setPathHandler(&pathHandler);
    */

    // This sets loader specific options. 
    // Format of the options string: <OpName1>(<param1>,<param2>,...,<paramN>) <OpName2>() ...
    //SceneFileHandler::the().setOptions("wrl", "LineWidth(2.2)");
    
    // set a callback for reading progress.
    SceneFileHandler::the().setReadProgressCB(progress);

    // Using the stream interface
    // The last parameter is the filetype e.g. "bin", "osg" but it is
    // also possible to use the filename with a extension.
    //std::ifstream in(fileName, std::ios::binary);
    //scene = SceneFileHandler::the().read(in, fileName);
    //in.close();

    // As a default all geometries are striped with the StripeGraphOp
    // To disable the default striper you can add a empty or a NULL GraphOpSeq instance.
    //GraphOpSeq *graphop = new GraphOpSeq;
    //SceneFileHandler::the().setDefaultGraphOp(graphop);
    //scene = SceneFileHandler::the().read(fileName);
    // or
    //SceneFileHandler::the().setDefaultGraphOp(NULL);
    //scene = SceneFileHandler::the().read(fileName);
    // or
    //GraphOpSeq *graphop = new GraphOpSeq;
    //scene = SceneFileHandler::the().read(fileName, graphop);
    // or
    //scene = SceneFileHandler::the().read(fileName, NULL);
    
    // You can also add your own GraphOP's
    GraphOpSeq *graphop = new GraphOpSeq;
    graphop->addGraphOp(new VerifyGeoGraphOp);
    graphop->addGraphOp(new StripeGraphOp);
    scene = SceneFileHandler::the().read(fileName, graphop);
    
    if(scene == NullFC)
    {
        std::cerr << "Error loading " << fileName << "!" << std::endl;
        scene = makeTorus( .5, 2, 16, 16 );
    }

    //scene.dump();

    // stream out test.
    //std::ofstream out("test.bin", std::ios::binary);
    //SceneFileHandler::the().write(scene, out, "bin");
    //out.close();
    
    // file out test.
    //SceneFileHandler::the().write(scene, "test.osg", true);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    mgr->setWindow( gwin );
    mgr->setRoot( scene );

    mgr->showAll();

    // GLUT main loop
    glutMainLoop();

    return 0;
}
