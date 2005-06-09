// OpenSG Tutorial Example: Materials
//
// This example shows how to manually change the render order of materials.
// For intersecting geometries transparent sorting doesn't work so
// we set for each material a sort key.

// Headers
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGPointLight.h>
#include <OpenSG/OSGRenderAction.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGPolygonChunk.h>

// the headers for the SimpleMaterials
#include <OpenSG/OSGSimpleMaterial.h>
#include <OpenSG/OSGImage.h>


// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *_mgr = NULL;
NodePtr _scene = NullFC;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT(int *argc, char *argv[]);

// redraw the window
void display(void)
{
    _mgr->redraw();
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
    _scene = makeCoredNode<Group>();

    // create a polygon chunk for backface culling.
    PolygonChunkPtr pchunk = PolygonChunk::create();
    beginEditCP(pchunk);
        pchunk->setCullFace(GL_BACK);
    endEditCP(pchunk);
    
    // create three transparent boxes.
    SimpleMaterialPtr mat1 = SimpleMaterial::create();
    beginEditCP(mat1);
        mat1->setAmbient      (Color3f(0.2,0.2,0.2));
        mat1->setDiffuse      (Color3f(1.0,0.0,0.0));
        mat1->setEmission     (Color3f(0.0,0.0,0.0));
        mat1->setSpecular     (Color3f(0.4,0.4,0.4));
        mat1->setShininess    (80);
        mat1->setTransparency (0.5);
        // render this first (key 0)
        mat1->setSortKey      (0);
        mat1->addChunk        (pchunk);
    endEditCP (mat1);
    NodePtr box1 = makeBox(2.5, 2.5, 2.5, 1, 1, 1);
    GeometryPtr geo = GeometryPtr::dcast(box1->getCore());
    beginEditCP(geo, Geometry::MaterialFieldMask);
        geo->setMaterial(mat1);
    endEditCP(geo, Geometry::MaterialFieldMask);
    
    SimpleMaterialPtr mat2 = SimpleMaterial::create();
    beginEditCP(mat2);
        mat2->setAmbient      (Color3f(0.2,0.2,0.2));
        mat2->setDiffuse      (Color3f(0.0,1.0,0.0));
        mat2->setEmission     (Color3f(0.0,0.0,0.0));
        mat2->setSpecular     (Color3f(0.4,0.4,0.4));
        mat2->setShininess    (80);
        mat2->setTransparency (0.5);
        // render this second (key 1)
        mat2->setSortKey      (1);
        mat2->addChunk        (pchunk);
    endEditCP (mat2);
    NodePtr box2 = makeBox(5.0, 5.0, 5.0, 1, 1, 1);
    geo = GeometryPtr::dcast(box2->getCore());
    beginEditCP(geo, Geometry::MaterialFieldMask);
        geo->setMaterial(mat2);
    endEditCP(geo, Geometry::MaterialFieldMask);
    
    SimpleMaterialPtr mat3 = SimpleMaterial::create();
    beginEditCP(mat3);
        mat3->setAmbient      (Color3f(0.2,0.2,0.2));
        mat3->setDiffuse      (Color3f(0.0,0.0,1.0));
        mat3->setEmission     (Color3f(0.0,0.0,0.0));
        mat3->setSpecular     (Color3f(0.4,0.4,0.4));
        mat3->setShininess    (80);
        mat3->setTransparency (0.5);
        // render this third (key 2)
        mat3->setSortKey      (2);
        mat3->addChunk        (pchunk);
    endEditCP (mat3);
    NodePtr box3 = makeBox(10.0, 10.0, 10.0, 1, 1, 1);
    geo = GeometryPtr::dcast(box3->getCore());
    beginEditCP(geo, Geometry::MaterialFieldMask);
        geo->setMaterial(mat3);
    endEditCP(geo, Geometry::MaterialFieldMask);

    beginEditCP(_scene);
        _scene->addChild(box1);
        _scene->addChild(box2);
        _scene->addChild(box3);
    endEditCP(_scene);

    // create the SimpleSceneManager helper
    _mgr = new SimpleSceneManager;

    // tell the manager what to manage
    _mgr->setWindow(gwin );
    _mgr->setRoot  (_scene);

    // show the whole scene
    _mgr->showAll();

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
    _mgr->resize(w, h);
    glutPostRedisplay();
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
    if (state)
        _mgr->mouseButtonRelease(button, x, y);
    else
        _mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    _mgr->mouseMove(x, y);
    glutPostRedisplay();
}

// react to keys
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:
            OSG::osgExit();
            exit(0);
        break;
        case 'w':
            SceneFileHandler::the().write(_scene, "scene.osb.gz", true);
            printf("wrote scene.\n");
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
    glutIdleFunc(display);

    return winid;
}
