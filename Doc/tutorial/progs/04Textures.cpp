// all needed include files
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>

// these headers are need for textures and images
#include <OpenSG/OSGSimpleTexturedMaterial.h>
#include <OpenSG/OSGImage.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;
NodePtr scene;

int setupGLUT( int *argc, char *argv[] );

NodePtr createScenegraph(){
    // the scene must be created here
    
    //create the geometry which we will assign a texture to
    GeometryPtr boxGeo= makeBoxGeo(10,10,10,1,1,1);
    
    //Load the image we want to use as a texture
    ImagePtr image = Image::create();
    image->read("data/bricks.jpg");
    
    //now we create the texture that will hold the image
    SimpleTexturedMaterialPtr tex = SimpleTexturedMaterial::create();
    beginEditCP(tex);
        tex->setImage(image);
    endEditCP(tex);
    
    //now assign the fresh texture to the geometry
    beginEditCP(boxGeo, Geometry::MaterialFieldMask);
        boxGeo->setMaterial(tex);
    endEditCP(boxGeo, Geometry::MaterialFieldMask);
    
    // Create the node that will hold our geometry
    NodePtr n = Node::create();
    beginEditCP(n, Node::CoreFieldMask);
        n->setCore(boxGeo);
    endEditCP(n, Node::CoreFieldMask);
    
    return n;
}

int main(int argc, char **argv)
{
    osgInit(argc,argv);
        
    int winid = setupGLUT(&argc, argv);
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();

    scene = createScenegraph();
    
    mgr = new SimpleSceneManager;
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);
    mgr->showAll();
    
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
