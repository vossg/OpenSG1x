
// Minimalistic OpenSG program

// GLUT is used for window handling
#include <GL/glut.h>

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGLog.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGSimpleGeometry.h>

#include <OpenSG/OSGSceneFileHandler.h>

#include <OpenSG/OSGThread.h>
#include <OpenSG/OSGThreadManager.h>
#include <OpenSG/OSGChangeList.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

Thread  *pLoader = NULL;

NodePtr scene;

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

void *load(void *arg)
{
    scene = SceneFileHandler::the().read((char *) arg);

    return NULL;
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

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setWinID(winid);
    gwin->init();
   
    if ( argc < 2 )
    {
        FFATAL(("No file given!\n"));
        return 1;
    }

    // create the loader thread
    pLoader = OSG::Thread::get("Loader");
    
    if(pLoader == NULL)
    {
        FFATAL(("Could not create thread\n"));
        return 1;
    }

    // run it, using a separate aspect
    pLoader->run(load, 1, (void *) argv[1] );

    // wait for it to finish
    Thread::join(pLoader);
    
    // success?
    if(scene == NullFC)
    {
        FFATAL(("Could not load %s\n", argv[1] ));
        return 1;
    }

    // merge the changes into our aspect
    pLoader->getChangeList()->applyToCurrent();
    pLoader->getChangeList()->clearAll();

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    mgr->setWindow( gwin );
    mgr->setRoot( scene );

    mgr->showAll();

    // GLUT main loop
    glutMainLoop();

    return 0;
}
