
#include <OSGGLUT.h>

#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>

#include <OSGTime.h>
#include <OSGImage.h>
#include <OSGTextureChunk.h>
#include <OSGRegisterCombinersChunk.h>
#include <OSGComponentTransform.h>
#include <OSGMatrixCamera.h>
#include <OSGSceneFileHandler.h>

#include <OSGTextureGrabBackground.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

GeoTexCoords2fPtr texcoords;

ImagePtr argammaimg;
TextureChunkPtr argammachunk;    

ImagePtr gbgammaimg;
TextureChunkPtr gbgammachunk;    

RegisterCombinersChunkPtr reg;

// redraw the window
void display(void)
{
    static Time lastTime = 0; 
    static UInt32 frames = 0, lastFrame = 0;
    
    ++frames;
    Time now = getSystemTime();
    
    if(now - 4 > lastTime)
    {
        if(lastTime != 0)
        {
            char title[200];
            sprintf(title, "%.2f fps", 
                            (frames - lastFrame) / (now - lastTime) );
            printf("%s\n", title);
        }
        lastTime = now;
        lastFrame = frames;
    }
    
    mgr->redraw();
}

// react to size changes
void reshape(int w, int h)
{
    mgr->resize(w,h);
    
    Real32 tw = osgnextpower2(w), th = osgnextpower2(h);
    
    beginEditCP(texcoords);
    texcoords->clear();
    texcoords->addValue(Vec2f(0,0));
    texcoords->addValue(Vec2f(w/tw,0));
    texcoords->addValue(Vec2f(w/tw,h/th));
    texcoords->addValue(Vec2f(0,h/th));
    endEditCP(texcoords);

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

void updateMatrix(Matrix &m)
{
    Color4f m1(m[0][0]/2+.5,m[0][1]/2+.5,m[0][2]/2+.5,0),
            m2(m[1][0]/2+.5,m[1][1]/2+.5,m[1][2]/2+.5,0),
            m3(m[2][0]/2+.5,m[2][1]/2+.5,m[2][2]/2+.5,0),
            m4(m[3][0]/2+.5,m[3][1]/2+.5,m[3][2]/2+.5,0);
    
    Color4f selectR(1,0,0,0), selectG(0,1,0,0), selectB(0,0,1,0);

    UInt16 ncomb = 0;
    
    beginEditCP(reg);

    reg->setCombinerRGB(ncomb,
        GL_TEXTURE1_ARB,       GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable A
        GL_ZERO,               GL_UNSIGNED_INVERT_NV,   GL_RGB, // variable B
        GL_TEXTURE2_ARB,       GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable C
        GL_ZERO,               GL_UNSIGNED_INVERT_NV,   GL_RGB, // variable D
        GL_DISCARD_NV, GL_DISCARD_NV, GL_TEXTURE0_ARB,   // ABout, CDout, Sumout
        GL_NONE, GL_NONE,                            // scale, bias
        GL_FALSE, GL_FALSE, GL_FALSE );                // ABdot, CDdot, muxSum

    ncomb++;

    // first combiner: spare0 = dot(col, m1), spare1 = dot(col,m2)      
     
    reg->setCombinerColors(ncomb, m1, m2);

    reg->setCombinerRGB(ncomb,
        GL_TEXTURE0_ARB,       GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable A
        GL_CONSTANT_COLOR0_NV, GL_EXPAND_NORMAL_NV,     GL_RGB, // variable B
        GL_TEXTURE0_ARB,       GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable C
        GL_CONSTANT_COLOR1_NV, GL_EXPAND_NORMAL_NV,     GL_RGB, // variable D
        GL_SPARE0_NV, GL_SPARE1_NV, GL_DISCARD_NV,   // ABout, CDout, Sumout
        GL_NONE, GL_NONE,                            // scale, bias
        GL_TRUE, GL_TRUE, GL_FALSE );                // ABdot, CDdot, muxSum

    ncomb++;
    
    // second combiner: tex0 = dot(col, m3), spare0 = spare0.r   
    
    reg->setCombinerColors(ncomb, m3, selectR);

    reg->setCombinerRGB(ncomb,
        GL_TEXTURE0_ARB,       GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable A
        GL_CONSTANT_COLOR0_NV, GL_EXPAND_NORMAL_NV,     GL_RGB, // variable B
        GL_SPARE0_NV,          GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable C
        GL_CONSTANT_COLOR1_NV, GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable D
        GL_TEXTURE3_ARB, GL_SPARE0_NV, GL_DISCARD_NV, // ABout, CDout, Sumout
        GL_NONE, GL_NONE,                             // scale, bias
        GL_TRUE, GL_FALSE, GL_FALSE );                 // ABdot, CDdot, muxSum

    ncomb++;
    
    // final combiner 
    
    reg->setColor0(selectG);
    reg->setColor1(selectB);
    
    // RGB = D + AB + (1-A)C
    reg->setFinalCombiner( 
         GL_CONSTANT_COLOR0_NV, GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable A
         GL_SPARE1_NV,          GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable B
         GL_E_TIMES_F_NV,       GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable C
         GL_SPARE0_NV,          GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable D
         GL_CONSTANT_COLOR1_NV, GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable E
         GL_TEXTURE3_ARB,       GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable F
         GL_PRIMARY_COLOR_NV,   GL_UNSIGNED_IDENTITY_NV, GL_ALPHA );// variable G

    endEditCP(reg);
}

void updateGamma(Real32 gamma, UInt16 res)
{
    UInt16 x,y;
    UInt8 *data;
    
    argammaimg->set(GL_RGB,res,res);

    beginEditCP(argammaimg);
    data = argammaimg->getData();
    
    memset(data, 0, res * res * 3);
    
    for(y = 0; y < res; ++y)
    {
        UInt8 v = (int)(pow(y/(Real32)(res-1),gamma)*255+0.5);
        for(x = 0; x < res; ++x)
        {
            *data++ = v;
            *data++ = 0;
            *data++ = 0;           
        }
    }
    endEditCP(argammaimg);

    beginEditCP(argammachunk);
    argammachunk->setImage(argammaimg);
    endEditCP(argammachunk);

    gbgammaimg->set(GL_RGB,res,res);

    beginEditCP(gbgammaimg);
    data = gbgammaimg->getData();
    
    memset(data, 0, res * res * 3);
    
    for(y = 0; y < res; ++y)
    {
        UInt8 vy = (int)(pow(y/(Real32)(res-1),gamma)*255+0.5);
        for(x = 0; x < res; ++x)
        {
            UInt8 vx = (int)(pow(x/(Real32)(res-1),gamma)*255+0.5);
            *data++ = 0;
            *data++ = vx;
            *data++ = vy;           
        }
    }
    endEditCP(gbgammaimg);

    beginEditCP(gbgammachunk);
    gbgammachunk->setImage(gbgammaimg);
    endEditCP(gbgammachunk);
}

// react to keys
void keyboard(unsigned char k, int, int)
{
    switch(k)
    {
    case 27:    osgExit();
                exit(1);
    case 'm':   {
                Matrix m;
                std::cout << "Enter Matrix:" << std::endl;
                std::cin >> m[0][0] >> m[0][1] >> m[0][2]
                         >> m[1][0] >> m[1][1] >> m[1][2]
                         >> m[2][0] >> m[2][1] >> m[2][2];
                updateMatrix(m);
                }
                break;
    case 'g':   {
                Real32 gamma;
                UInt16 res;
                std::cout << "Enter Gamma:" << std::endl;
                std::cin >> gamma;
                std::cout << "Enter Res:" << std::endl;
                std::cin >> res;
                updateGamma(gamma,res);
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
    
    int id=glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    GLUTWindowPtr gwin=GLUTWindow::create();
    gwin->setId(id);
    gwin->init();

    // create the scene   
    NodePtr scene;
    if(argc > 1)
    {
        scene = SceneFileHandler::the().read(argv[1]);
    }
    else
    {
        scene = makeTorus(.5, 2, 16, 16);
    }
    
    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);
    
    
    // The color correction material
    
    // Step 1: The texture from the GrabBackground
    
    // The texture to keep the image
    
    ImagePtr img = Image::create();
    beginEditCP(img);
    img->set(GL_RGB,1,1);
    endEditCP(img);
    addRefCP(img);
    
    TextureChunkPtr tex = TextureChunk::create();    
    beginEditCP(tex);
    tex->setImage(img);
    tex->setMinFilter(GL_NEAREST);
    tex->setScale(false);
    tex->setEnvMode(GL_REPLACE);
    tex->setShaderOperation(GL_TEXTURE_2D);
    endEditCP  (tex);
    addRefCP(tex);
     
    // Step 2: The textures for the initial gamma mapping
  
    // Texture Chunks for gamma mapping

    UChar8 argammadata[] =
        {  0,  0,  0,    0,  0,  0,    0,  0,  0,    0,  0,  0,    
          80,  0,  0,   80,  0,  0,   80,  0,  0,   80,  0,  0,    
         160,  0,  0,  160,  0,  0,  160,  0,  0,  160,  0,  0,    
         255,  0,  0,  255,  0,  0,  255,  0,  0,  255,  0,  0  
        };
    
    argammaimg = Image::create();
    beginEditCP(argammaimg);
    argammaimg->set(GL_RGB,4,4,1,1,1,0,argammadata);
    endEditCP(argammaimg);
    addRefCP(argammaimg);
    
    argammachunk = TextureChunk::create();    
    beginEditCP(argammachunk);
    argammachunk->setImage(argammaimg);
    argammachunk->setInternalFormat(GL_RGB8);
    argammachunk->setMinFilter(GL_NEAREST);
    argammachunk->setMagFilter(GL_NEAREST);
#ifdef GL_CLAMP_TO_EDGE
    argammachunk->setWrapS(GL_CLAMP_TO_EDGE);
    argammachunk->setWrapT(GL_CLAMP_TO_EDGE);
#else
    argammachunk->setWrapS(GL_CLAMP);
    argammachunk->setWrapT(GL_CLAMP);
#endif
    argammachunk->setShaderOperation(GL_DEPENDENT_AR_TEXTURE_2D_NV);
    argammachunk->setShaderInput    (GL_TEXTURE0_ARB);
    endEditCP  (argammachunk);
    addRefCP(argammachunk);


    UChar8 gbgammadata[] =
        {  0,  0,  0,     0, 80,  0,     0,160,  0,    0,255,  0,
           0,  0, 80,     0, 80, 80,     0,160, 80,    0,255, 80,
           0,  0,160,     0, 80,160,     0,160,160,    0,255,160,
           0,  0,255,     0, 80,255,     0,160,255,    0,255,255
        };
    
    gbgammaimg = Image::create();
    beginEditCP(gbgammaimg);
    gbgammaimg->set(GL_RGB,4,4,1,1,1,0,gbgammadata);
    endEditCP(gbgammaimg);
    addRefCP(gbgammaimg);
    
    gbgammachunk = TextureChunk::create();    
    beginEditCP(gbgammachunk);
    gbgammachunk->setImage(gbgammaimg);
    gbgammachunk->setInternalFormat(GL_RGB8);
    gbgammachunk->setMinFilter(GL_NEAREST);
    gbgammachunk->setMagFilter(GL_NEAREST);
#ifdef GL_CLAMP_TO_EDGE
    gbgammachunk->setWrapS(GL_CLAMP_TO_EDGE);
    gbgammachunk->setWrapT(GL_CLAMP_TO_EDGE);
#else
    gbgammachunk->setWrapS(GL_CLAMP);
    gbgammachunk->setWrapT(GL_CLAMP);
#endif
    gbgammachunk->setShaderOperation(GL_DEPENDENT_GB_TEXTURE_2D_NV);
    gbgammachunk->setShaderInput    (GL_TEXTURE0_ARB);
    endEditCP  (gbgammachunk);
    addRefCP(gbgammachunk);


    // Step 3: RegisterCombiners Chunk for color matrix multiply

    Matrix m;
    m.setValue(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);     
    m.setValue(1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,1);
    
    reg = RegisterCombinersChunk::create();
    
    updateMatrix(m);
   
    // putting it all together
        
    ChunkMaterialPtr mat = ChunkMaterial::create();
    beginEditCP(mat);
    mat->addChunk(tex);
    mat->addChunk(argammachunk);
    mat->addChunk(gbgammachunk);
    mat->addChunk(reg);
    endEditCP(mat);
    
    // take the viewport
    ViewportPtr vp = gwin->getPort(0);
    
    beginEditCP(vp);
    vp->setLeft(0);
    vp->setRight(1);
    vp->setBottom(0);
    vp->setTop(1);
    
    endEditCP  (vp);
    
    // add the second viewport
     
    GeoPTypesUI8Ptr  types = GeoPTypesUI8::create();
    beginEditCP(types);
    types->addValue(GL_QUADS);
    endEditCP(types);
    
    GeoPositions3fPtr pos = GeoPositions3f::create();
    beginEditCP(pos);
    pos->addValue(Pnt3f(-1, -1, -0.5));
    pos->addValue(Pnt3f( 1, -1, -0.5));
    pos->addValue(Pnt3f( 1,  1, -0.5));
    pos->addValue(Pnt3f(-1,  1, -0.5));
    endEditCP(pos);
    
    texcoords = GeoTexCoords2f::create();
    beginEditCP(texcoords);
    texcoords->addValue(Vec2f(0,0));
    texcoords->addValue(Vec2f(1,0));
    texcoords->addValue(Vec2f(1,1));
    texcoords->addValue(Vec2f(0,1));
    endEditCP(texcoords);
   
    GeometryPtr geo = Geometry::create();
    beginEditCP(geo);
    geo->setMaterial(mat);
//    geo->setMaterial(getDefaultUnlitMaterial());
    geo->setPositions(pos);
    geo->setTypes(types);
    geo->setTexCoords(texcoords);
    endEditCP  (geo);
 
    NodePtr cube = Node::create();
    beginEditCP(cube);
    cube->setCore(geo);
    endEditCP(cube);
   
    ComponentTransformPtr trans = ComponentTransform::create();
    beginEditCP(trans);
    trans->setTranslation(Vec3f(0,0,0));
    endEditCP(trans);
    
    NodePtr tr = Node::create();
    beginEditCP(tr);
    tr->setCore(trans);
    tr->addChild(cube);
    endEditCP(tr);
 
    GroupPtr group = Group::create();
    NodePtr gr = Node::create();
    beginEditCP(gr);
    gr->setCore(group);
    gr->addChild(tr);
    endEditCP(gr);
   
    MatrixCameraPtr cam = MatrixCamera::create();
    
    beginEditCP(cam);
    cam->setNear(0.1);
    cam->setFar(10);
    cam->setModelviewMatrix(Matrix::identity());
    cam->setProjectionMatrix(Matrix::identity());   
    endEditCP(cam);
    
    // Add the grab background
    
    TextureGrabBackgroundPtr tg = TextureGrabBackground::create();
    
    beginEditCP(tg);
    tg->setTexture(tex);
    tg->setColor(Color3f(0,0,1));
    endEditCP(tg);
    
    ViewportPtr vp2 = Viewport::create();
    beginEditCP(vp2);
    vp2->setCamera(cam);
    vp2->setRoot(tr);
    vp2->setBackground(tg);
    
    vp2->setLeft(0);
    vp2->setRight(1);
    vp2->setBottom(0);
    vp2->setTop(1);
    
    endEditCP(vp2);
    
    beginEditCP(gwin);
    gwin->addPort(vp2);
    endEditCP(gwin);
    
    // show the whole scene
    mgr->showAll();
    
    // GLUT main loop
    glutMainLoop();

    return 0;
}
