
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGPassiveWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSceneFileHandler.h>

#include <OSGSimpleMaterial.h>
#include <OSGTextureChunk.h>
#include <OSGImage.h>
#include <OSGTexGenChunk.h>
#include <OSGTextureTransformChunk.h>

#include <OSGPointChunk.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

PointChunkPtr pc;

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
    case 'a':   
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

    // create the point chunk  
    pc = PointChunk::create();
    beginEditCP(pc);
    
    pc->setSize(10);
    pc->setSmooth(true);
 
    pc->setMinSize(3);
    pc->setMaxSize(200);
    pc->setConstantAttenuation(0);
    pc->setLinearAttenuation(0.3);
    pc->setQuadraticAttenuation(0);
    pc->setFadeThreshold(0);
 
    pc->setSprite(false);
    pc->setRMode(GL_ZERO);
   
    endEditCP(pc);
    
    
    // create the two textures
    TextureChunkPtr tx1 = TextureChunk::create();
   
    UChar8 imgdata1[] =
        {  255,0,0,  0,255,0,  0,0,255, 255,0,255 };
    ImagePtr pImg1 = Image::create();
    pImg1->set(Image::OSG_RGB_PF, 2, 2, 1, 1, 1, 0, imgdata1 );
    
    beginEditCP(tx1);
    tx1->setImage(pImg1); // NOTE: the image is NOT copied, the variable
                          // needs to be kept around as long as the 
                          // texture is used
    tx1->setMinFilter(GL_LINEAR);
    tx1->setMagFilter(GL_LINEAR);
    tx1->setWrapS(GL_REPEAT);
    tx1->setWrapT(GL_REPEAT);
    tx1->setEnvMode(GL_REPLACE);
    tx1->setPointSprite(true);
    endEditCP(tx1);
   
    // create the material
    SimpleMaterialPtr mat = SimpleMaterial::create();
    
    beginEditCP(mat);
    mat->setDiffuse(Color3f(1,1,1));
    mat->setLit(false);
    mat->addChunk(tx1);
    mat->addChunk(pc);
    endEditCP(mat);
    
    // create the scene
    NodePtr scene;
    
    scene = Node::create();
    GeometryPtr g1 = Geometry::create();

    beginEditCP(scene);
    scene->setCore(g1);
    endEditCP(scene);

    beginEditCP(g1);

    GeoPositions3fPtr pnts = GeoPositions3f::create();
    g1->setPositions(pnts);

    MFPnt3f* p = pnts->getFieldPtr();

    beginEditCP(pnts);
    p->push_back(Pnt3f(-1, -1, -1));
    p->push_back(Pnt3f( 1, -1, -1));
    p->push_back(Pnt3f( 1,  1, -1));
    p->push_back(Pnt3f(-1,  1, -1));
    p->push_back(Pnt3f(-1, -1,  1));
    p->push_back(Pnt3f( 1, -1,  1));
    p->push_back(Pnt3f( 1,  1,  1));
    p->push_back(Pnt3f(-1,  1,  1));
    endEditCP(pnts);


    GeoTexCoords2fPtr texs = GeoTexCoords2f::create();
    g1->setTexCoords(texs);
    beginEditCP(texs);
    texs->push_back(Vec2f(0, 0));
    texs->push_back(Vec2f(1, 0));
    texs->push_back(Vec2f(1, 1));
    texs->push_back(Vec2f(0, 1));
    texs->push_back(Vec2f(0, 0));
    texs->push_back(Vec2f(2, 0));
    texs->push_back(Vec2f(2, 2));
    texs->push_back(Vec2f(0, 2));
    endEditCP(texs);

    GeoPLengthsPtr lens = GeoPLengthsUI32::create();    
    g1->setLengths(lens);
    beginEditCP(lens);
    lens->push_back(8);
    endEditCP(lens);

    GeoPTypesPtr type = GeoPTypesUI8::create();     
    g1->setTypes(type);
    beginEditCP(type);
    type->push_back(GL_POINTS);
    endEditCP(type);

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
    
    // GLUT main loop
    glutMainLoop();

    return 0;
}
