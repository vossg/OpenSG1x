
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGPassiveWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSceneFileHandler.h>

#include <OSGSimpleMaterial.h>
#include <OSGTextureChunk.h>
#include <OSGCubeTextureChunk.h>
#include <OSGImage.h>
#include <OSGTexGenChunk.h>
#include <OSGTextureTransformChunk.h>

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

    UInt32 ntex, ntexgen;
    UInt32 uselodbias, usepointsprite, usecubemaps;
    
    if(argc < 2 || sscanf(argv[1], "%d", &ntex) != 1)
        ntex = 2;
    if(argc < 3 || sscanf(argv[2], "%d", &ntexgen) != 1)
        ntexgen = 0;
    if(argc < 4 || sscanf(argv[3], "%d", &uselodbias) != 1)
        uselodbias = 0;
    if(argc < 5 || sscanf(argv[4], "%d", &usepointsprite) != 1)
        usepointsprite = 0;
    if(argc < 6 || sscanf(argv[5], "%d", &usecubemaps) != 1)
        usecubemaps = 0;
        
    // create the textures
    TextureChunkPtr *tx = new TextureChunkPtr [ntex];
   
    UChar8 imgdata1[] =
        {  255,0,0,  0,255,0,  0,0,255, 255,0,255 };
    ImagePtr pImg1 = Image::create();
    pImg1->set(Image::OSG_RGB_PF, 2, 2, 1, 1, 1, 0, imgdata1 );
   
    UChar8 imgdata2[] =
        {  64,64,64, 128,128,128, 192,192,192, 255,255,255 };
    ImagePtr pImg2 = Image::create();
    pImg2->set(Image::OSG_RGB_PF, 2, 2, 1, 1, 1, 0, imgdata2 );
    
    for(UInt16 i = 0; i < ntex; ++i)
    {
        CubeTextureChunkPtr ctp;
        
        if(usecubemaps)
        {
            ctp = CubeTextureChunk::create();
            tx[i] = ctp;
        }
        else
            tx[i] = TextureChunk::create();
            
        beginEditCP(tx[i]);
        tx[i]->setImage( (i&1) ? pImg2 : pImg1 ); 
        if(usecubemaps)
        {
            ctp->setPosZImage( (i&1) ? pImg2 : pImg1 );
            ctp->setPosXImage( (i&1) ? pImg2 : pImg1 );
            ctp->setNegXImage( (i&1) ? pImg2 : pImg1 );
            ctp->setPosYImage( (i&1) ? pImg2 : pImg1 );
            ctp->setNegYImage( (i&1) ? pImg2 : pImg1 );
        }
        tx[i]->setMinFilter(GL_LINEAR);
        tx[i]->setMagFilter(GL_LINEAR);
        tx[i]->setWrapS(GL_REPEAT);
        tx[i]->setWrapT(GL_REPEAT);
        tx[i]->setEnvMode(GL_REPLACE);
        if(uselodbias)
            tx[i]->setLodBias(2);
        if(usepointsprite)
            tx[i]->setPointSprite(true);
        endEditCP(tx[i]);
    }
    
    TexGenChunkPtr tg = TexGenChunk::create();
    
    beginEditCP(tg);
    tg->setGenFuncS(GL_EYE_LINEAR);
    tg->setGenFuncSPlane(Vec4f(0,.15,0,0));
    endEditCP(tg);

    // create the multi-textured material
    SimpleMaterialPtr mat = SimpleMaterial::create();
    
    beginEditCP(mat);
    mat->setDiffuse(Color3f(1,1,1));
    mat->setLit(false);
    
    for(UInt16 i = 0; i < ntex; ++i)
    {
        mat->addChunk(tx[i]);
    }
    
    for(UInt16 i = 0; i < ntexgen; ++i)
    {
        mat->addChunk(tg);
    }

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

    // use second texture coordinates
    texs = GeoTexCoords2f::create();
    g1->setTexCoords1(texs);
    beginEditCP(texs);
    texs->push_back(Vec2f(0, 0));
    texs->push_back(Vec2f(2, 0));
    texs->push_back(Vec2f(2, 2));
    texs->push_back(Vec2f(0, 2));
    texs->push_back(Vec2f(0, 0));
    texs->push_back(Vec2f(1, 0));
    texs->push_back(Vec2f(1, 1));
    texs->push_back(Vec2f(0, 1));
    endEditCP(texs);

    GeoPLengthsPtr lens = GeoPLengthsUI32::create();    
    g1->setLengths(lens);
    beginEditCP(lens);
    lens->push_back(4);
    lens->push_back(4);
    endEditCP(lens);

    GeoPTypesPtr type = GeoPTypesUI8::create();     
    g1->setTypes(type);
    beginEditCP(type);
    type->push_back(GL_POLYGON);
    type->push_back(GL_POLYGON);
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
   
    pwin->dumpExtensions();
    
    // GLUT main loop
    glutMainLoop();

    return 0;
}
