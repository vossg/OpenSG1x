
// Synced Threads: use a synchronized producer to create the geometry in
// parallel to the renderer

#include <GL/glut.h>

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGLog.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGSimpleGeometry.h>

#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGGeoFunctions.h>
#include <OpenSG/OSGTime.h>
#include <OpenSG/OSGLog.h>

#include <OpenSG/OSGThread.h>
#include <OpenSG/OSGThreadManager.h>
#include <OpenSG/OSGChangeList.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

Thread  *producer = NULL;
Barrier *syncBarrier = NULL;

NodePtr scene;
GeometryPtr plane;

volatile Bool exiting = false;

#undef FLOG
#if 0
#define FLOG(var) printf var
#else
#define FLOG(var) 
#endif

// Standard GLUT callback functions
void display( void )
{
    FLOG(( "display::waitProd\n"));
    // check for the producer to finish its part
    syncBarrier->enter( 2 );
    
    FLOG(( "display::merge\n"));
    // merge the changes into our aspect
    producer->getChangeList()->applyToCurrent();
    producer->getChangeList()->clearAll();

    FLOG(( "display::waitSync\n"));
    // notify successful synchronisation
    syncBarrier->enter( 2 );
    FLOG(( "display::synced\n"));

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
key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:    exiting = true;
                syncBarrier->enter( 2 );
                syncBarrier->enter( 2 );
                Thread::join(producer);
                exit(0);
                break;
    }
}

void *produce(void *arg)
{
    GeoPositions3fPtr pos = GeoPositions3fPtr::dcast(plane->getPositions());
    
    GeoPositions3f::StoredFieldType *posfield = pos->getFieldPtr();
        
    GeoPositions3f::StoredFieldType::iterator last,it;
    Time start = getSystemTime();
    
    FLOG(( "produce::start\n"));
    while(exiting == false)
    {
        FLOG(( "produce::produce\n"));
        // produce the data for the next frame
        Time now = getSystemTime();
        Time delta = now - start;
        
        last = posfield->end();
       
        FLOG(( "produce: %d elements, value %f\n",last-posfield->begin(), 
            osgsin(delta) ));
#if 1        
        beginEditCP(pos);
        
        for ( it = posfield->begin(); it != last; ++it )
        {
            Real32 d = osgsqrt( (*it)[0] * (*it)[0] + (*it)[1] * (*it)[1] );
            (*it)[2] = osgsin( d + delta );
            //FLOG(( "it:%p [0]:%.3f [1]:%.3f [2]:%.3f\n",it,(*it)[0],(*it)[1],(*it)[2]));
        }
        
        endEditCP(pos);
        
        calcVertexNormals(plane);
#endif        
        FLOG(( "produce::waitDraw\n"));
        // wait for drawer to finish drawing
        syncBarrier->enter( 2 );

        FLOG(( "produce::waitSync\n"));
        // wait for drawer to finish synchronization
        syncBarrier->enter( 2 );
        FLOG(( "produce::synced\n"));
     }
     FLOG(( "produce::stop\n"));
     
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
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(key);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setWinID(winid);
    gwin->init();

    // create the geometry to manipulate
    
    plane = makePlaneGeo( 6, 6, 32, 32 );

    beginEditCP(plane);
    plane->setDlistCache(false);
    endEditCP(plane);
    
    NodePtr scene = Node::create();   
    beginEditCP(scene);
    scene->setCore(plane);
    endEditCP(scene);

    // setup the logger to add timestamps
    osgLog().addHeaderElem(LOG_TIMESTAMP_HEADER);
    
    // create the barrier
    syncBarrier = Barrier::get("Producer");
   
    // create the producer thread
    producer =  OSG::Thread::get("Producer");
    
    if(producer == NULL)
    {
        FFATAL(("Could not create thread\n"));
        return 1;
    }

    // Populate the producer's aspect
    Thread::getCurrent()->getChangeList()->applyTo(1);
    Thread::getCurrent()->getChangeList()->clearAll();
    
    // run it, using a separate aspect
    producer->run(produce, 1, (void *) NULL );

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    mgr->setWindow( gwin );
    mgr->setRoot( scene );

    mgr->showAll();

    // GLUT main loop
    glutMainLoop();

    return 0;
}
