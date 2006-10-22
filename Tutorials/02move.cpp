// OpenSG Tutorial Example: Move An Object
//
// This example shows how to use Transform nodes to move objects aroung
//

// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>

// new headers: 

// some wrappers for standard functions for platform independence, e.g. 
// osgsin, osgcos, osgtan
#include <OpenSG/OSGBaseFunctions.h>

// the transformation node core
#include <OpenSG/OSGTransform.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The pointer to the transformation
TransformPtr trans;


// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

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
    
    /*
       When manipulating OpenSG structures, they need to be informed  of what
       you're going to do, so they can create copies of the data if needed for
       thread safety. Use beginEditCP to do that. It takes the changing object
       (FieldContainer, to be exact) and a bitmask describing which fields are
       going to be changed. 

       Every field of a FieldContainer has an associated constant that can be
       or-ed together to create the field mask. If you don't know beforehand
       what's going to change you can just ignore it. In that case the system
       will assume that you're going to change everything. That's safe, but if
       you do know what's going to change, using the mask is more efficient.

       The following style is just a suggestion how to structure the code to
       visualize what's happening, there's no programmatic reason to do it.
    */
    
    beginEditCP(trans, Transform::MatrixFieldMask);
    {
        trans->setMatrix(m);
    }   
    /*
       After the object has been changed, the system has to be informed about
       it, so it knows that the object is done now and necessary updates can
       be done. endEditCP needs to be passed the same field mask as
       beginEditCP.
    */
    endEditCP  (trans, Transform::MatrixFieldMask);
   
    mgr->redraw();
}

void update(void)
{
    glutPostRedisplay();
}

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

    NodePtr torus = makeTorus( .5, 2, 16, 32 );

    // create the transformation node
    // scenegraph nodes are split into 2 parts: the node and its core
    
    // 1. create the Node
    NodePtr scene = Node::create();
    
    // 2. create the core
    trans = Transform::create();
    
    // 3. associate the core with the node
 
    // OpenSG objects need to be informed when they are being changed, 
    // that's what beginEditCP() and endEditCP() do
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        scene->setCore(trans);
 
        // add the torus as a child
        scene->addChild(torus);
    }
    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    

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
        case 27:  
        {
            OSG::osgExit();
            exit(0);
        }
        break;
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
    glutIdleFunc(update);

    return winid;
}
