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

#include <OSGNFIOFactory.h>
#include <OSGBaseFunctions.h>

#include "OSGGroup.h"


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

    
    // some tests
    //NFIOFactory::the().create("Test")->read();
    //NFIOFactory::the().create("Geometry")->read();
    //NFIOBase::read();
    //NFIOBase::write();

    
    // create the scene
#if 0
    const char *fileName = (argc > 1) ? argv[1] : "test.osx";

    SceneFileHandler::the().print();

    // set a callback for reading progress.
    SceneFileHandler::the().setReadProgressCB(progress);

    GraphOpSeq graphop;
    graphop.addGraphOp(new VerifyGeoGraphOp);
    graphop.addGraphOp(new StripeGraphOp);
    scene = SceneFileHandler::the().read(fileName, &graphop);
#endif

#if 0
    scene = SceneFileHandler::the().read("test.osb", NULL);
    return 0;
#endif

    if(argc > 1)
    {
        double t = getSystemTime();
        scene = SceneFileHandler::the().read(argv[1], NULL);
        printf("Read '%s' in %f seconds.\n", argv[1], getSystemTime() - t);
        if(scene == NullFC)
        {
            printf("Couldn't load file '%s'!\n", argv[1]);
            return 0;
        }
    }
    
    if(scene == NullFC && argc == 1)
    {
        printf("**************** creating torus *********************\n");
        scene = makeTorus( .5, 2, 16, 16 );
    }
    
    if(argc == 2)
    {
        // Default settings:
        // "inlineTextures=true,"
        // "compressTextures=false,"
        // "texturesCompressionQuality=75,"
        // "texturesImageType=png,"
        // "quantizePositions=0,"
        // "quantizeNormals=0,"
        // "quantizeTexCoords=0,"
        // "packIndices=false"

        SceneFileHandler::the().setOptions("osb", "compressTextures=true,"
                                                  "texturesCompressionQuality=75,"
                                                  "texturesImageType=jpeg,"
                                                  "quantizePositions=16,"
                                                  "quantizeNormals=8,"
                                                  "quantizeTexCoords=16");
        
        double t = getSystemTime();
        SceneFileHandler::the().write(scene, "test.osb");
        //SceneFileHandler::the().write(scene, "test.osb.gz", true);
        printf("wrote osb in %f seconds.\n", getSystemTime() - t);
        t = getSystemTime();
        SceneFileHandler::the().write(scene, "test.bin");
        //SceneFileHandler::the().write(scene, "test.bin.gz", true);
        printf("wrote bin in %f seconds.\n", getSystemTime() - t);
    }
    
    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    mgr->setWindow( gwin );
    mgr->setRoot( scene );

    mgr->showAll();

    // GLUT main loop
    glutMainLoop();

    return 0;
}
