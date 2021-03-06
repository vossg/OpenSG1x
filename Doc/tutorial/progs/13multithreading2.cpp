// all needed include files
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>

#include <OpenSG/OSGThreadManager.h>

OSG_USING_NAMESPACE
using namespace std;

SimpleSceneManager *mgr;
NodePtr scene;

//we will store the transformation globally - this
//is not necessary, but comfortable
TransformPtr trans;
Thread* animationThread;
Thread* applicationThread;
Barrier *syncBarrier;

int setupGLUT(int *argc, char *argv[]);

NodePtr createScenegraph()
{
    // the scene must be created here
    NodePtr n = makeTorus(.5,2,16,16);
    
    //add a simple Transformation
    trans = Transform::create();
    beginEditCP(trans);
        Matrix m;
        m.setIdentity();
        trans->setMatrix(m);
    endEditCP(trans);
    
    NodePtr transNode = Node::create();
    beginEditCP(transNode);
        transNode->setCore(trans);
        transNode->addChild(n);
    endEditCP(transNode);
    
    return transNode;
}

//this function will run in a thread and simply will
//rotate the cube by setting a new transformation matrix
void rotate(void *args)
{
    // sync this thread to the main thread, i.e. pull in all changes done
    // during scene construction
    syncBarrier->enter(2);
    applicationThread->getChangeList()->applyAndClear();
    syncBarrier->enter(2);
    
    // we won't stop calculating new matrices....
    while(true)
    {
        Real32 time = glutGet(GLUT_ELAPSED_TIME);
        Matrix m;
        m.setIdentity();
        m.setRotate(Quaternion(Vec3f(0,1,0), time/1000));
        
        beginEditCP(trans);
            trans->setMatrix(m);
        endEditCP(trans);
        // nothing unusual until here
        
        //well that's new...
        
        //wait until two threads are cought in the
        //same barrier
        syncBarrier->enter(2);    // barrier (1)
        
        //just the same again
        syncBarrier->enter(2);    // barrier (2)
    }
}

int main(int argc, char **argv)
{
 #if OSG_MINOR_VERSION > 2
    ChangeList::setReadWriteDefault();
#endif
    osgInit(argc,argv);
        
    int winid = setupGLUT(&argc, argv);
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();

    scene =createScenegraph();
    
    //create the barrier, that will be used to
    //synchronize threads
    
    //instead of NULL you could provide a name
    syncBarrier = Barrier::get(NULL);

    mgr = new SimpleSceneManager;
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);
    mgr->showAll();
    
    // store a pointer to the application thread
    applicationThread = dynamic_cast<Thread *>(ThreadManager::getAppThread());
    
    //create the thread that will run generation of new matrices
    animationThread = dynamic_cast<Thread *>(ThreadManager::the()->getThread("anim"));

    //do it...
    animationThread->runFunction(rotate, 1, NULL);
    
    // wait for animationThread to complete its sync
    syncBarrier->enter(2);
    syncBarrier->enter(2);
    
    glutMainLoop();

    return 0;
}

void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}

void display(void)
{
    // we wait here until the animation thread enters
    // barrier (1)
    syncBarrier->enter(2);
    
    //now we sync data
    animationThread->getChangeList()->applyAndClear();
    
    // now wait for animation thread to enter barrier (2)
    syncBarrier->enter(2);
    
    // !!!! Attention
    // you will find a more detailed description
    // of what's going on here in the documentation
    // itself!
    
    // now render...
    mgr->redraw();
}

void mouse(int button, int state, int x, int y)
{
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}

void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG First Application");
    
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);
    return winid;
}
