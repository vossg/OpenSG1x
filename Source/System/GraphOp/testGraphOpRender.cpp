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

#include <OSGGradientBackground.h>

#include <OSGImageFileHandler.h>
#include <OSGPathHandler.h>

#include <OSGSceneFileHandler.h>
#include <OSGGraphOpSeq.h>
#include <OSGVerifyGeoGraphOp.h>
#include <OSGStripeGraphOp.h>
#include <OSGMergeGraphOp.h>
#include <OSGSharePtrGraphOp.h>

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

    // set a callback for reading progress.
    SceneFileHandler::the().setReadProgressCB(progress);

    GraphOpSeq *graphop = new GraphOpSeq;
    
    // verify geometry
    graphop->addGraphOp(new VerifyGeoGraphOp);
    
    // merge geometry nodes, flush transformations, ...
    graphop->addGraphOp(new MergeGraphOp);

    // stripes the geometry nodes, ok the striper doesn't like shared geo
    // properties so we stripe before the SharePtrGraphOp!
    graphop->addGraphOp(new StripeGraphOp);

    // tries to share all FieldContainerPtr's with the same content.
    SharePtrGraphOp *share = new SharePtrGraphOp;
    // you can add include or exlcude lists, it is not allowed to set includes and excludes!
    //share->setIncludes("Material, TextureChunk"); // this one just shares equal materials and texture chunks.
    //share->setExcludes("GeoPTypesUI8, GeoPLengthsUI32, GeoIndicesUI32, GeoPositions3f, GeoNormals3f, GeoTexCoords2f"); // share all except some geo properties.
    graphop->addGraphOp(share);

    scene = SceneFileHandler::the().read(fileName, graphop);
    
    if(scene == NullFC)
    {
        std::cerr << "Error loading " << fileName << "!" << std::endl;
        scene = makeTorus( .5, 2, 16, 16 );
    }

    //scene.dump();

    // write optimized file out.
    SceneFileHandler::the().write(scene, "test.osb.gz", true);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    mgr->setWindow( gwin );
    mgr->setRoot( scene );

    mgr->showAll();

    // create a gradient background.
    GradientBackgroundPtr gback = GradientBackground::create();
    beginEditCP(gback, GradientBackground::LineFieldMask);
        gback->clearLines();
        gback->addLine(Color3f(0.7, 0.7, 0.8), 0);
        gback->addLine(Color3f(0.0, 0.1, 0.3), 1);
    endEditCP(gback, GradientBackground::LineFieldMask);

    WindowPtr win = mgr->getWindow();
    beginEditCP(win);
        for(UInt32 i=0;i<win->getPort().size();++i)
        {
            ViewportPtr vp = win->getPort()[i];
            beginEditCP(vp);
                vp->setBackground(gback);
            endEditCP(vp);
        }
    endEditCP(win);

    
    // GLUT main loop
    glutMainLoop();

    return 0;
}
