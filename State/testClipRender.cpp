
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
#include <OSGClipPlaneChunk.h>

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
    SimpleMaterialPtr mat = SimpleMaterial::create();
    
    ClipPlaneChunkPtr cl1 = ClipPlaneChunk::create();
    beginEditCP(cl1);
    cl1->setEquation(Vec4f(1,0,0,0));
    cl1->setEnable(true);
    cl1->setBeacon(scene);
    endEditCP(cl1);
    
    ClipPlaneChunkPtr cl2 = ClipPlaneChunk::create();
    beginEditCP(cl2);
    cl2->setEquation(Vec4f(0,1,0,0));
    cl2->setEnable(true);
    cl2->setBeacon(scene);
    endEditCP(cl2);
    
    beginEditCP(mat);
    mat->setDiffuse(Color3f(1,0,0));
    mat->setSpecular(Color3f(1,1,1));
    mat->setLit(true);
    mat->addChunk(cl1);
    mat->addChunk(cl2);
    endEditCP(mat);

    GeometryPtr g1 = makeTorusGeo(0.2, 2, 8, 16);

    beginEditCP(scene);
    scene->setCore(g1);
    endEditCP(scene);
   
    beginEditCP(g1);

    g1->setMaterial(mat);
    
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
   
    pwin->dumpExtensions();
    
    // GLUT main loop
    glutMainLoop();

    return 0;
}
