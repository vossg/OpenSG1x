
#include <OSGGLUT.h>
#include <OSGGLEXT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGPassiveWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSceneFileHandler.h>

#include <OSGMaterialGroup.h>
#include <OSGSimpleMaterial.h>
#include <OSGCubeTextureChunk.h>
#include <OSGTexGenChunk.h>
#include <OSGTextureTransformChunk.h>

#include <OSGTestCubeMaps.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

SimpleMaterialPtr cuberefmat;
TextureTransformChunkPtr ttransform;

// redraw the window
void display(void)
{      
     
    // transform the cube reflection texture coords by the inverse viewer, 
    // orientation only
    NodePtr beacon = mgr->getAction()->getCamera()->getBeacon();    
    Matrix m;
    beacon->getToWorld(m);
    
    m.invert();
    m[3].setValues(0,0,0,0);
    
    beginEditCP(ttransform);
    ttransform->setMatrix(m);
    endEditCP(ttransform);
    
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



Action::ResultE setMaterial(NodePtr& node)
{   
    GeometryPtr geo = GeometryPtr::dcast(node->getCore());
    
    if(geo!=NullFC)
    {
        geo->setMaterial(cuberefmat);
    }   
    
    MaterialGroupPtr mg = MaterialGroupPtr::dcast(node->getCore());
    
    if(mg!=NullFC)
    {
        mg->setMaterial(cuberefmat);
    }   
    
    return Action::Continue; 
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
    
    if(argc > 1)
    {
        scene = SceneFileHandler::the().read(argv[1]);
    }
    else
    {
        // scene = makeTorus(.5, 3, 16, 16);
        scene = makeSphere(3, 1);
    }

    // create the cube reflection material
    cuberefmat = SimpleMaterial::create();
    
    ttransform = TextureTransformChunk::create();
    
    CubeTextureChunkPtr cubetex = CubeTextureChunk::create();

    setTestCubeImages(cubetex);
    
    TexGenChunkPtr texgen = TexGenChunk::create();
    beginEditCP(texgen);
    texgen->setGenFuncS(GL_REFLECTION_MAP_ARB);
    texgen->setGenFuncT(GL_REFLECTION_MAP_ARB);
    texgen->setGenFuncR(GL_REFLECTION_MAP_ARB);   
    endEditCP(texgen);
  
    beginEditCP(cuberefmat);
    cuberefmat->setDiffuse( Color3f( .8,.8,.8 ) );
    cuberefmat->setAmbient( Color3f( .5,.5,.5 ) );
    cuberefmat->setSpecular( Color3f( 1,1,1 ) );
    cuberefmat->setShininess( 30 );
    cuberefmat->addChunk(cubetex);
    cuberefmat->addChunk(ttransform);
    cuberefmat->addChunk(texgen); 
    endEditCP(cuberefmat);
    
    // set all geos to use the cube reflection material
    traverse(scene, 
             osgTypedFunctionFunctor1CPtrRef<Action::ResultE, NodePtr>
             (setMaterial));

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
