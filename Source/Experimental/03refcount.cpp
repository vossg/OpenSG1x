// OpenSG Tutorial Example: Reference Counting
//
// This example shows how to destroy OpenSG objects and what to do to prevent
// that happening inadvertedly.
//

// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGTransform.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The pointer to the transformation
TransformPtr trans;
TransformPtr trans2;


// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

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

    /*
        OpenSG uses reference counting to keep track of used and no longer used
        objects.
        
        The idea is that every part of the code that keeps a reference to
        another object increases its reference count by calling addRefCP() and
        decreases it by calling subRefCP() when the reference is no longer
        used. When the reference count reaches zero or less during a
        subRefCP() the object is not needed anymore and can be destroyed. 

        The 'or less' part can actually happen, as objects are created with a
        refcount of zero.
        
        Right now this is only done for Nodes, i.e. when adding a node to
        another Node its reference count is increased. When subbing it from
        another Node its reference count is decreased. Same thing for cores.

        Think about that for a second.
        
        What that means is that as soon as a node is taken out of another node
        it is destryed, as its reference count goes to zero. Iff the node
        in question does not hold a core.
        
        
        When you remove a node from the graph, be aware of the reference counts
        involved, or you will get into trouble. See below for ways how to
        handle that.
    */

    // create the scene

    // the torus is created. RefCnt: 1 / Do not forget the hidden geo core
    NodePtr torus = makeTorus( .5, 2, 16, 16 );

    // create the transformation node. RefCnt: 0
    NodePtr scene = Node::create();
    // create the transformation node core. RefCnt: 1
    trans = Transform::create();
    
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        scene->setCore(trans);

        // add the torus to the scene. RefCnt: 2
        scene->addChild(torus);
    }
    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
 
    // create a second transformation node. 
    // RefCnt (after the following line): 0
    NodePtr scene2 = Node::create();
    // RefCnt (after the following line): 1
    trans2 = Transform::create();

    beginEditCP(scene2, Node::CoreFieldMask);
    {
        scene2->setCore(trans2);
    }
    endEditCP  (scene2, Node::CoreFieldMask);
 
    
    /*
        Now let's say we want to move the torus from scene to scene2.
    */
    
    /*
      simple approach: remove it from scene, add it to scene2, which is 
      only ok iff both nodes contain cores (or are referenced otherwise
    */

    beginEditCP(scene, Node::ChildrenFieldMask);
    {
        // sub the torus from scene. RefCnt: 2->1! The torus is not destroyed!
        scene->subChild(torus);
    }
    endEditCP  (scene, Node::ChildrenFieldMask);
    
    /*
       You can do the following, again iff both nodes contain a core or
       are referenced otherwise.
    */
    beginEditCP(scene2, Node::ChildrenFieldMask);
    {
        // add the torus to scene2.
        scene2->addChild(torus);
    }
    endEditCP  (scene2, Node::ChildrenFieldMask);

    beginEditCP(scene2, Node::ChildrenFieldMask);
    {
        // add the torus to scene2.
        scene2->subChild(torus);
    }
    endEditCP  (scene2, Node::ChildrenFieldMask);

    // destroy the torus;
    torus->unlinkSubTree();
   
    // Let's try again, this time independend of the presence of cores or
    // other refcounts.
    
    // Get a new torus. RefCnt: 1
    torus = makeTorus( .5, 2, 16, 16 );
    
    // add it to scene
    beginEditCP(scene, Node::ChildrenFieldMask);
    {
        // add the torus to the scene. RefCnt: 1
        scene->addChild(torus);
    }
    endEditCP  (scene, Node::ChildrenFieldMask);
   
    /*
        The following makes sure that the torus' reference count is always
        high enough so that it is not accidentally deleted.
    */
    // bump the refcount. RefCnt: 2
    addRefCP(torus);
    
    // remove it from scene    
    beginEditCP(scene, Node::ChildrenFieldMask);
    {
        // sub the torus from scene. RefCnt: 1. OK.
        scene->subChild(torus);
    }
    endEditCP  (scene, Node::ChildrenFieldMask);
   
    // add it to scene2. 
    beginEditCP(scene2, Node::ChildrenFieldMask);
    {
        // add the torus to scene2. RefCnt: 2
        scene2->addChild(torus);
    }
    endEditCP  (scene2, Node::ChildrenFieldMask);
   
    // unbump the refcount. RefCnt: 1, just the way we want it
    subRefCP(torus);

    /*
        This is a bit complicated, just for moving nodes around in the
        scenegraph. But it's important to be aware of what's happening behind
        the scenes, otherwise the resulting errors will be very hard to find.
        
        For the actual problem there is a much simpler solution.
        
        addChild() actually takes care of all of that. As Nodes can only have
        one parent in OpenSG, when a Node is added as a child to another Node,
        it is automatically removed from its old parent.
        
        Concerning beginEdit()/endEdit(): you only need to call that for the
        object that you're directly manipulating, i.e. whose methods you call.
        If other objects are influenced by the action, their
        beginEdit()/endEdit()s will be done internally.
    */
    // move the torus from scene2 back to scene
    beginEditCP(scene, Node::ChildrenFieldMask);
    {
        // add the torus from scene. RefCnt: 1. Internally it's 1->2->1
        scene->addChild(torus);
    }
    endEditCP  (scene, Node::ChildrenFieldMask);
    
    /*
        How to delete an object should be obvious by now: just make sure that
        its reference count goes to or below 0.
    */    
    // Let's remove scene2, as it's not needed anymore.
    scene2->unlinkSubTree();

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);
    
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
void display( void )
{
    // create the matrix
    Matrix m;
    Real32 t = glutGet(GLUT_ELAPSED_TIME );
    
    m.setTransform(Vec3f(      osgsin(t / 1000.f), 
                               osgcos(t / 1000.f), 
                               osgsin(t / 1000.f)),
                   Quaternion( Vec3f(0,1,0), 
                               t / 1000.f));
    
    // set the transform's matrix
#ifdef BUGGY_MOVE_CHILD
    beginEditCP(trans, Transform::MatrixFieldMask);
    {
        trans->setMatrix(m);
    }   
    endEditCP  (trans, Transform::MatrixFieldMask);
#else
    beginEditCP(trans2, Transform::MatrixFieldMask);
    {
        trans2->setMatrix(m);
    }   
    endEditCP  (trans2, Transform::MatrixFieldMask);
#endif
   
    mgr->redraw();
}

// react to size changes
void reshape(int w, int h)
{
    mgr->resize(w, h);
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
    switch(k)
    {
    case 27:    exit(1);
    }
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    // call the redraw function whenever there's nothing else to do
    glutIdleFunc(display);

    return winid;
}
