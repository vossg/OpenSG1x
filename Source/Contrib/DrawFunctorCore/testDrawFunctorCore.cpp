// OpenSG Example: DrawFunctorCore
// A NodeCore that calls user-supplied functors for rendering.
// Two functors are needed: one for the actual drawing, one for the bounding
// volume update.
// The Draw functor should leave OpenGL exactly in the state it was found in,
// otherwise the results are undefined. 

// The problem with this core is, that it cannot be written to a file nor
// distributed over a cluster, as the code behind the functor cannot be 
// marshalled. That's why the use of this Core is not recommended.

// Standad includes
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSimpleGeometry.h>

// The new core
#include "OSGDrawFunctorCore.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

// Direct functions

// Volume update function

void volUpdate(Volume *volume)
{
    volume->extendBy(Pnt3f(-1,-1,-1));
    volume->extendBy(Pnt3f( 1, 1, 1));
}

// Draw function

Action::ResultE draw(DrawActionBase*)
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    
    glColor3f(1,0,0);
    glBegin(GL_QUADS);
    glVertex3f(-1,-1,-1);
    glVertex3f(-1, 1,-1);
    glVertex3f(-1, 1, 1);
    glVertex3f(-1,-1, 1);
    glVertex3f( 1,-1,-1);
    glVertex3f( 1, 1,-1);
    glVertex3f( 1, 1, 1);
    glVertex3f( 1,-1, 1);
    glEnd();
    
    glPopAttrib();
    
    return Action::Continue;
}


// Using static methods of an object

class SWrapper
{
  public:
  
    SWrapper()
    {
    }
  
    static void volUpdate(Volume *volume)
    {
        volume->extendBy(Pnt3f(-0.9,-0.9,-0.9));
        volume->extendBy(Pnt3f( 0.9, 0.9, 0.9));
    }

    static Action::ResultE draw(DrawActionBase*)
    {
        glPushAttrib(GL_ALL_ATTRIB_BITS);

        glColor4f(0,0,1,.4);
        glBegin(GL_QUADS);
        glVertex3f(-0.9,-0.9,-0.9);
        glVertex3f(-0.9,-0.9, 0.9);
        glVertex3f( 0.9,-0.9, 0.9);
        glVertex3f( 0.9,-0.9,-0.9);
        glVertex3f( 0.9, 0.9,-0.9);
        glVertex3f( 0.9, 0.9, 0.9);
        glVertex3f(-0.9, 0.9, 0.9);
        glVertex3f(-0.9, 0.9,-0.9);
        glEnd();

        glPopAttrib();

        return Action::Continue;
    }
};

// Using methods of an object instance

class Wrapper
{
  public:
  
    Wrapper(Color4f col) : _col(col)
    {
    }
  
    void volUpdate(Volume *volume)
    {
        volume->extendBy(Pnt3f(-0.8,-0.8,-0.8));
        volume->extendBy(Pnt3f( 0.8, 0.8, 0.8));
    }

    Action::ResultE draw(DrawActionBase*)
    {
        glPushAttrib(GL_ALL_ATTRIB_BITS);

        glColor4fv(_col.getValuesRGBA());
        glBegin(GL_QUADS);
        glVertex3f(-0.8,-0.8,-0.8);
        glVertex3f(-0.8, 0.8,-0.8);
        glVertex3f( 0.8, 0.8,-0.8);
        glVertex3f( 0.8,-0.8,-0.8);
        glVertex3f(-0.8, 0.8, 0.8);
        glVertex3f(-0.8,-0.8, 0.8);
        glVertex3f( 0.8,-0.8, 0.8);
        glVertex3f( 0.8, 0.8, 0.8);
        glEnd();

        glPopAttrib();

        return Action::Continue;
    }
    
    
  private:
  
    Color4f _col;
};


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
   
    // Create the Scene
    NodePtr scene = Node::create();
    GroupPtr grcore = Group::create();
    
    beginEditCP(scene);
    scene->setCore(grcore);

    // Add a Torus for background
    
    scene->addChild(makeTorus(.2, 2, 16, 16));

    // The actual creation of the functors is a little complicated.
    // Mainly because the braindead M$ compiler has problems with, you have to
    // explicitly create the functor for the right combination of return value
    // type, number of arguments and argument types (values, pointers,
    // references, etc.) and whether it is a function, a static method or an
    // instance method.
    // Given that the signatures of the draw and volumeUpdate functions are
    // fixed, the three variants shown here should cover all the bases

    // Add the DrawFunctor node for standard functions
    
    NodePtr df = Node::create();
    DrawFunctorCorePtr func = DrawFunctorCore::create();

    beginEditCP(func);
    func->setMaterial(getDefaultUnlitMaterial());  
    
    func->setDraw(
        osgTypedFunctionFunctor1Ptr< Action::ResultE, DrawActionBase >(draw));
            
    func->setVolumeUpdate(
        osgTypedFunctionVoidFunctor1Ptr< Volume >(volUpdate));
            
    endEditCP(func);

    beginEditCP(df);
    df->setCore(func);
    endEditCP(df);

    scene->addChild(df);

    // Some transparent material
    // Even though the DrawFunctorCore can do any kind of OpenGL functions, the
    // Material of the Core is used to decide whether the node should be sorted
    // and rendered last
    
    SimpleMaterialPtr transmat = SimpleMaterial::create();
    
    beginEditCP(transmat);
    transmat->setTransparency(0.1);  // The actual value is overriden by the draw
                                // anyway, but it has to be != 0 to be
                                // considered transparent
    transmat->setLit(false);
    endEditCP(transmat);
    
    // Add the DrawFunctor node for static methods of a class
    // Static methods are pretty much the same as functions
    
    NodePtr dfsm = Node::create();
    DrawFunctorCorePtr funcsm = DrawFunctorCore::create();

    beginEditCP(funcsm);
    funcsm->setMaterial(transmat);    
    
    funcsm->setDraw(
        osgTypedFunctionFunctor1Ptr< Action::ResultE, DrawActionBase >(
            &SWrapper::draw));
            
    funcsm->setVolumeUpdate(
        osgTypedFunctionVoidFunctor1Ptr< Volume >(&SWrapper::volUpdate));
    
    endEditCP(funcsm);

    beginEditCP(dfsm);
    dfsm->setCore(funcsm);
    endEditCP(dfsm);

    scene->addChild(dfsm);

    // Add the DrawFunctor node for methods
    // The functor creation functions need the type of the object for which
    // methods should be called.
    
    Wrapper wrap(Color4f(0,1,0,.3));
    
    NodePtr dfm = Node::create();
    DrawFunctorCorePtr funcm = DrawFunctorCore::create();

    beginEditCP(funcm);

    funcm->setMaterial(transmat);    

    funcm->setDraw(
        osgTypedMethodFunctor1ObjPtr< Action::ResultE, Wrapper, DrawActionBase >(
            &wrap, &Wrapper::draw));

    funcm->setVolumeUpdate(
        osgTypedMethodVoidFunctor1ObjPtr< Wrapper, Volume >(
            &wrap, &Wrapper::volUpdate));

    endEditCP(funcm);

    beginEditCP(dfm);
    dfm->setCore(funcm);
    endEditCP(dfm);

    scene->addChild(dfm);
    
    // Add a Sphere, just for fun
    
    scene->addChild(makeLatLongSphere(16,16,.4));


    endEditCP(scene);
    
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
void display(void)
{
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

    return winid;
}
