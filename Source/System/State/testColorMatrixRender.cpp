
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
#include <OSGRegisterCombinersChunk.h>

#include <OSGOSGWriter.h>
#include <OSGImage.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

RegisterCombinersChunkPtr rchunk;
SimpleMaterialPtr mat;

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

void setupRegComb(Matrix &m, bool usetex)
{
    // create the RegisterCombiner to do the matrix multiply
    // only the first 3 elements are used, no projective color yet
    
    Color4f m1(m[0][0]/2+.5,m[0][1]/2+.5,m[0][2]/2+.5,0),
            m2(m[1][0]/2+.5,m[1][1]/2+.5,m[1][2]/2+.5,0),
            m3(m[2][0]/2+.5,m[2][1]/2+.5,m[2][2]/2+.5,0),
            m4(m[3][0]/2+.5,m[3][1]/2+.5,m[3][2]/2+.5,0);
    
    Color4f selectR(1,0,0,0), selectG(0,1,0,0), selectB(0,0,1,0), one(1,1,1,1);
 
    GLenum source = (usetex ? GL_TEXTURE0_ARB : GL_PRIMARY_COLOR_NV);
 
    beginEditCP(rchunk);
    
    rchunk->clearCombiners();

    // first combiner: spare0 = (col.m1), spare1 = (col.m2)      
     
    rchunk->setCombinerColors(0, m1, m2);

    rchunk->setCombinerRGB( 0,
        source,                GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable A
        GL_CONSTANT_COLOR0_NV, GL_EXPAND_NORMAL_NV,     GL_RGB, // variable B
        source,                GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable C
        GL_CONSTANT_COLOR1_NV, GL_EXPAND_NORMAL_NV,     GL_RGB, // variable D
        GL_SPARE0_NV, GL_SPARE1_NV, GL_DISCARD_NV,   // ABout, CDout, Sumout
        GL_NONE, GL_NONE,                            // scale, bias
        GL_TRUE, GL_TRUE, GL_FALSE );                // ABdot, CDdot, muxSum

    // second combiner: tex0 = (col.m3), spare0 = (col.m1)_r 
    
    rchunk->setCombinerColors(1, m3, selectR);

    rchunk->setCombinerRGB( 1,
        source,                GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable A
        GL_CONSTANT_COLOR0_NV, GL_EXPAND_NORMAL_NV,     GL_RGB, // variable B
        GL_SPARE0_NV,          GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable C
        GL_CONSTANT_COLOR1_NV, GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable D
        GL_TEXTURE0_ARB, GL_SPARE0_NV, GL_DISCARD_NV, // ABout, CDout, Sumout
        GL_NONE, GL_NONE,                             // scale, bias
        GL_TRUE, GL_FALSE, GL_FALSE );                 // ABdot, CDdot, muxSum

    // third combiner: spare0 = (col.m1)_r + m4
    
    rchunk->setCombinerColors(2, one, m4);

    rchunk->setCombinerRGB( 2,
        source,                GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable A
        GL_CONSTANT_COLOR0_NV, GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable B
        GL_CONSTANT_COLOR1_NV, GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable C
        GL_CONSTANT_COLOR0_NV, GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable D
        GL_DISCARD_NV, GL_DISCARD_NV, GL_SPARE0_NV, // ABout, CDout, Sumout
        GL_NONE, GL_NONE,                             // scale, bias
        GL_FALSE, GL_FALSE, GL_FALSE );                 // ABdot, CDdot, muxSum

    // final combiner 
    
    rchunk->setColor0(selectG);
    rchunk->setColor1(selectB);
    
    // RGB = D + AB + (1-A)C
    //     = (col.m1)_r + m4 + (col.m2)_g + (1,0,1).((col.m3)_b)
    //
    rchunk->setFinalCombiner( 
         GL_CONSTANT_COLOR0_NV, GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable A
         GL_SPARE1_NV, GL_UNSIGNED_IDENTITY_NV, GL_RGB,            // variable B
         GL_E_TIMES_F_NV, GL_UNSIGNED_IDENTITY_NV, GL_RGB,       // variable C
         GL_SPARE0_NV, GL_UNSIGNED_IDENTITY_NV, GL_RGB,          // variable D
         GL_CONSTANT_COLOR1_NV, GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable E
         GL_TEXTURE0_ARB, GL_UNSIGNED_IDENTITY_NV, GL_RGB,       // variable F
         GL_PRIMARY_COLOR_NV, GL_UNSIGNED_IDENTITY_NV, GL_ALPHA );// variable G

    endEditCP(rchunk);

}

// react to keys
void keyboard(unsigned char k, int, int)
{
    switch(k)
    {
    case 27:    exit(1);
    case 'a':   beginEditCP(mat);
                mat->subChunk(rchunk);
                endEditCP(mat);
                break;
    case 's':   beginEditCP(mat);
                mat->addChunk(rchunk);
                endEditCP(mat);
                break;    
    case 'm':   {
                Matrix m;
                std::cout << "Enter Matrix:" << std::endl;
                std::cin >> m[0][0] >> m[0][1] >> m[0][2]
                         >> m[1][0] >> m[1][1] >> m[1][2]
                         >> m[2][0] >> m[2][1] >> m[2][2];
                setupRegComb(m,true);
                }
                break;
    case 'n':   {
                Matrix m;
                std::cout << "Enter Matrix:" << std::endl;
                std::cin >> m[0][0] >> m[0][1] >> m[0][2]
                         >> m[1][0] >> m[1][1] >> m[1][2]
                         >> m[2][0] >> m[2][1] >> m[2][2];
                setupRegComb(m,false);
                }
                break;
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

    // create the texture
    TextureChunkPtr tx1 = TextureChunk::create();
   
    UInt8 imgdata1[] =
        {  255,0,0,  0,255,0,  0,0,255, 255,255,255 };

    ImagePtr img1 = Image::create();    
    beginEditCP(img1);
    img1->set(Image::OSG_RGB_PF, 2, 2, 1, 1, 1, 0, imgdata1 );
    endEditCP(img1);
    
    beginEditCP(tx1);
    tx1->setImage(img1); // NOTE: the image is NOT copied, the variable
                          // needs to be kept around as long as the 
                          // texture is used
    tx1->setMinFilter(GL_NEAREST);
    tx1->setMagFilter(GL_NEAREST);
    tx1->setWrapS(GL_REPEAT);
    tx1->setWrapT(GL_REPEAT);
    tx1->setEnvMode(GL_REPLACE);
    endEditCP(tx1);
    
    // Matrix to transform the colors with
    
    Matrix m(1,1,1,0, 0,1,0,0, 0,0,1,0, 0,0,0.5,1);
    
    rchunk = RegisterCombinersChunk::create();
    
    addRefCP(rchunk);
    
    setupRegComb(m,true);
     
    OSGWriter writer( std::cout, 4 );
    writer.write( rchunk );
     
    // create the corrected material
    mat = SimpleMaterial::create();
    
    beginEditCP(mat);
    mat->setDiffuse(Color3f(1,1,1));
    mat->setLit(false);
    mat->addChunk(tx1);
    mat->addChunk(rchunk);
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
    
    // GLUT main loop
    glutMainLoop();

    return 0;
}
