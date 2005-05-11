
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGPassiveWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSceneFileHandler.h>

#include <OSGSimpleMaterial.h>
#include <OSGTextureChunk.h>
#include <OSGTexGenChunk.h>
#include <OSGTextureTransformChunk.h>
#include <OSGDepthChunk.h>
#include <OSGMultiPassMaterial.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;


// redraw the window
void display(void)
{      
    // render
    
    mgr->redraw();

    // all done, swap    
    glutSwapBuffers();
}

// react to size changes
void reshape(int w, int h)
{
    mgr->resize(w,h);
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
void keyboard(unsigned char k, int, int)
{
    switch(k)
    {
    case 27:    exit(1);
    }
}


int main(int argc, char **argv)
{
    osgInit(argc,argv);

    // GLUT init
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    PassiveWindowPtr pwin=PassiveWindow::create();
    pwin->init();
     
    // create the scene
    NodePtr scene;
    
    scene = Node::create();
   
    // create the material
    
    // Pass 1: Simple red, shiny, depth-tested
    
    DepthChunkPtr cl1 = DepthChunk::create();
    beginEditCP(cl1);
    cl1->setEnable(true);
    cl1->setFunc(GL_LEQUAL);
    endEditCP(cl1);
    
    SimpleMaterialPtr mat = SimpleMaterial::create();
    beginEditCP(mat);
    mat->setDiffuse(Color3f(1,0,0));
    mat->setSpecular(Color3f(.9,.9,.9));
    mat->setShininess(30);
    mat->setLit(true);
    mat->addChunk(cl1);
    endEditCP(mat);
    
    // Pass 2: Green unlit, without depth testing
     
    DepthChunkPtr cl2 = DepthChunk::create();
    beginEditCP(cl2);
    cl2->setEnable(false);
    endEditCP(cl2);
   
    SimpleMaterialPtr mat2 = SimpleMaterial::create();
    beginEditCP(mat2);
    mat2->setDiffuse(Color3f(0,1,0));
    mat2->setLit(false);
    mat2->setTransparency(.8);
    mat2->addChunk(cl2);
    endEditCP(mat2);

    // Bring them together
    
    MultiPassMaterialPtr mpm = MultiPassMaterial::create();
    
    beginEditCP(mpm);
    mpm->getMaterials().push_back(mat);
    mpm->getMaterials().push_back(mat2);
    endEditCP(mpm);
    
    GeometryPtr g1 = makeTorusGeo(0.2, 2, 8, 16);

    beginEditCP(scene);
    scene->setCore(g1);
    endEditCP(scene);
   
    beginEditCP(g1);

    g1->setMaterial(mpm);
    
    endEditCP(g1);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // create the window and initial camera/viewport
    mgr->setWindow(pwin );
    // tell the manager what to manage
    mgr->setRoot  (scene);
    
    // show the whole scene
    mgr->showAll();
    mgr->redraw();
    
    // GLUT main loop
    glutMainLoop();

    return 0;
}
