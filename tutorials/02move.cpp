
// Use a transformation to move objects

#include <GL/glut.h>

#include <OpenSG/OSGConfig.h>

// some wrappers for standard functions for platform independence
#include <OpenSG/OSGBaseFunctions.h>

// the transformation node core
#include <OpenSG/OSGTransform.h>

#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGSimpleGeometry.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

// The pointer to the transformation
TransformPtr trans;

// Standard GLUT callback functions
void display( void )
{
    // create the matrix
    Matrix m;
    Real32 t = glutGet(GLUT_ELAPSED_TIME );
    
    m.setTransform(Vec3f(osgsin(t / 1000.f), 
                         osgcos(t / 1000.f), 
                         osgsin(t / 1000.f)));
    
    // set the transform's matrix
    beginEditCP(trans);
    trans->setMatrix(m);
    endEditCP(trans);
   
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
    glutIdleFunc(display);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setWinID(winid);
    gwin->init();

    // create the scene

    NodePtr torus = makeTorus( .5, 2, 16, 16 );

    // create the transformation node
    // scenegraph nodes are split into 2 parts: the node and its core
    
    // 1. create the Node
    NodePtr scene = Node::create();
    
    // 2. create the core
    trans = Transform::create();
    
    // 3. associate the core with the node
 
    // OpenSG objects need to be informed when they are being changed, 
    // that's what beginEditCP() and endEditCP() do;
    beginEditCP(scene);

    scene->setCore(trans);
 
    // add the torus as a child
    scene->addChild(torus);

    endEditCP(scene);
    
 
    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    mgr->setWindow( gwin );
    mgr->setRoot( scene );

    mgr->showAll();

    // GLUT main loop
    glutMainLoop();

    return 0;
}
