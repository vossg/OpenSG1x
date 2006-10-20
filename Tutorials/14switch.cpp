// OpenSG Tutorial Example: Switch
//
// This example shows how to use the Switch NodeCore to selectively display one
// of a number of children of a node.
//
// You can use the keys 1-0 to display a single node, 'a' to select all nodes
// and 'n' to select none.
//

// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGTransform.h>

// new headers: 

// the Switch node core
#include <OpenSG/OSGSwitch.h>


// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// the Switch Core
SwitchPtr sw;

// number of copies to create
const UInt16 ncopies = 10;

// Transforms to move the nodes
TransformPtr trans[ncopies];


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
    
    // set the transforms' matrices
    for(UInt16 i=0; i<ncopies; ++i)
    {
        m.setTransform(Vec3f(      osgsin(t / 1000.f + i * 4 * ncopies / Pi), 
                                   osgcos(t / 1000.f + i * 6 * ncopies / Pi), 
                                   osgsin(t / 1000.f + i * 7 * ncopies / Pi)),
                       Quaternion( Vec3f (1,1,0), 
                                          t / 1000.f + i * 4 * ncopies / Pi));
    
        beginEditCP(trans[i], Transform::MatrixFieldMask);
        {
            trans[i]->setMatrix(m);
        }
        endEditCP  (trans[i], Transform::MatrixFieldMask);
    }
    
    mgr->redraw();
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
    
    // this time, create just the core of the geometry
    GeometryPtr torus = makeTorusGeo( .5, 2, 8, 12 );

    // create the scene
    // the scene has a single group with ncopies transformations below,
    // each of these carries a Node that shares the geometry
    
    /*
       The Switch NodeCore very similar to the Group, but it has the additional
       capability to only show one or none of its children.
       
       This is controlled by the choice Field, and is used below in the keys
       function.
    */
    
    // create the root Switch node
    NodePtr  scene = Node::create();
    
    sw = Switch::create();
    beginEditCP(sw, Switch::ChoiceFieldMask);
    sw->setChoice(-2);  // Note: this will be Switch::ALL in 1.2
    endEditCP(sw, Switch::ChoiceFieldMask);

    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    scene->setCore(sw);
    
    // create the copied geometry nodes and their transformations
    for(UInt16 i = 0; i<ncopies; ++i)
    {
        // create the nodes for the shared Geometry core
        NodePtr geonode = Node::create();
        
        // assign the Core to the Node
        beginEditCP(geonode, Node::CoreFieldMask );
        {
            geonode->setCore(torus);
        }
        endEditCP  (geonode, Node::CoreFieldMask );

        // add a transformation for every Geometry
        NodePtr transnode = Node::create();
        
        trans[i] = Transform::create();
         
        beginEditCP(transnode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        {
            transnode->setCore (trans[i]);
            transnode->addChild(geonode );
        }
        endEditCP  (transnode, Node::CoreFieldMask | Node::ChildrenFieldMask);
       
        scene->addChild(transnode);       
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
void keyboard(unsigned char k, int , int )
{
    switch(k)
    {
        case 27:
        {
            osgExit();
            exit(1);
        }
        break;

        case '0':   case '1':   case '2':   case '3':   case '4':   
        case '5':   case '6':   case '7':   case '8':   case '9': 
        {   
            beginEditCP(sw, Switch::ChoiceFieldMask);
            sw->setChoice(k - '0');
            endEditCP(sw, Switch::ChoiceFieldMask);
            break;
        }
        break;

        case 'a':
        {
            beginEditCP(sw, Switch::ChoiceFieldMask);
            sw->setChoice(Switch::ALL); 
            endEditCP(sw, Switch::ChoiceFieldMask);
        }
        break;

        case 'n':
        {
            beginEditCP(sw, Switch::ChoiceFieldMask);
            sw->setChoice(Switch::NONE); 
            endEditCP(sw, Switch::ChoiceFieldMask);
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
    glutIdleFunc(glutPostRedisplay);

    return winid;
}
