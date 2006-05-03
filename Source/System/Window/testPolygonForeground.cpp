
#include <OSGGLUT.h>

#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>

#include <OSGTime.h>
#include <OSGImage.h>
#include <OSGTextureChunk.h>
#include <OSGComponentTransform.h>

#include <OSGSimpleTexturedMaterial.h>

#include <OSGPolygonForeground.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

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
    case 27:    osgExit();
                exit(1);
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
//    NodePtr scene = makeTorus(.5, 2, 16, 16);
    NodePtr scene = makeBox(1,1,1, 1,1,1);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);
    
    // Create the textured material
    UChar8 imgdata[] =
      {  255,0,0,128,  0,255,0,128,  0,0,255,255,  255,255,255,255 };
   
    ImagePtr img = Image::create();
    beginEditCP(img);
    if(argc > 1)
        img->read(argv[1]);
    else
        img->set( Image::OSG_RGBA_PF, 2, 2, 1, 1, 1, 0, imgdata );
    endEditCP(img);
    addRefCP(img);
   
    SimpleTexturedMaterialPtr mat = SimpleTexturedMaterial::create();
    beginEditCP(mat);
    mat->setLit(false);
    mat->setDiffuse(Color3f(0,1,0));
    mat->setImage(img);
    mat->setMinFilter(GL_NEAREST);
    mat->setMagFilter(GL_NEAREST);
    mat->setEnvMode(GL_REPLACE);
    endEditCP(mat);
    
    // Add the polygon foregrounds
    
    Pnt2f pos[][4] = { 
        { Vec2f(.4,.4), Vec2f(.6,.4), Vec2f(.6,.6), Vec2f(.4,.6) },
        { Vec2f(0,0), Vec2f(1,0), Vec2f(1,.1), Vec2f(0,.1) },
        { Vec2f(1,-100), Vec2f(-2,-100), Vec2f(-2,-2), Vec2f(1,-2) },
        { Vec2f(-1000,-1000), Vec2f(0,0), Vec2f(0,0), Vec2f(0,0) }
    };
    bool normx[] = { true, true, false };
    bool normy[] = { true, true, false };
    
    for(UInt16 ind = 0; pos[ind][0][0] != -1000; ++ind)
    {   
        PolygonForegroundPtr pg = PolygonForeground::create();

        beginEditCP(pg);
        pg->setMaterial(mat);
        pg->getTexCoords().push_back(Vec3f( 0.,0.,0.));
        pg->getPositions().push_back(pos[ind][0]);
        pg->getTexCoords().push_back(Vec3f( 1.,0.,0.));
        pg->getPositions().push_back(pos[ind][1]);
        pg->getTexCoords().push_back(Vec3f( 1.,1.,0.));
        pg->getPositions().push_back(pos[ind][2]);
        pg->getTexCoords().push_back(Vec3f( 0.,1.,0.));
        pg->getPositions().push_back(pos[ind][3]);
 
        pg->setNormalizedX(normx[ind]);
        pg->setNormalizedY(normy[ind]);
        endEditCP(pg);

        // take the viewport
        ViewportPtr vp = gwin->getPort(0);

        beginEditCP(vp);
        vp->getForegrounds().push_back(pg);    
        endEditCP  (vp);
    }
     
    // Create the edgeblend foreground
    const int blendpixel = 50;
    
    UChar8 ebimgdata[] =
      {  0,0,0,0,  0,0,0,255 };
   
    ImagePtr ebimg = Image::create();
    beginEditCP(ebimg);
    ebimg->set( Image::OSG_RGBA_PF, 2, 1, 1, 1, 1, 0, ebimgdata );
    endEditCP(ebimg);
    addRefCP(ebimg);
   
    TextureChunkPtr tc = TextureChunk::create();
    beginEditCP(tc);
    tc->setImage(ebimg);
    tc->setMinFilter(GL_NEAREST);
    tc->setMagFilter(GL_LINEAR);
    tc->setEnvMode(GL_REPLACE);
    tc->setWrapS(GL_CLAMP);
    endEditCP(tc);
    
    BlendChunkPtr bl = BlendChunk::create();
    beginEditCP(bl);
    bl->setSrcFactor(GL_SRC_ALPHA);
    bl->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
    endEditCP(bl);
    
    ChunkMaterialPtr ebmat = ChunkMaterial::create();
    beginEditCP(ebmat);
    ebmat->addChunk(tc);
    ebmat->addChunk(bl);
    endEditCP(ebmat);

    PolygonForegroundPtr ebpg = PolygonForeground::create();

    beginEditCP(ebpg);
    ebpg->setMaterial(ebmat);
    ebpg->getTexCoords().push_back(Vec3f( 0.25,0.,0.));
    ebpg->getTexCoords().push_back(Vec3f( 0.75,0.,0.));
    ebpg->getTexCoords().push_back(Vec3f( 0.75,1.,0.));
    ebpg->getTexCoords().push_back(Vec3f( 0.25,1.,0.));

    ebpg->getPositions().push_back(Pnt2f(-blendpixel-1, 0));
    ebpg->getPositions().push_back(Pnt2f(           -1, 0));
    ebpg->getPositions().push_back(Pnt2f(           -1, 1));
    ebpg->getPositions().push_back(Pnt2f(-blendpixel-1, 1));

    ebpg->setNormalizedX(false);
    ebpg->setNormalizedY(true);
    endEditCP(ebpg);

    // take the viewport
    ViewportPtr vp = gwin->getPort(0);

    beginEditCP(vp);
    vp->getForegrounds().push_back(ebpg);    
    endEditCP  (vp);

// show the whole scene
    mgr->showAll();
    
    // GLUT main loop
    glutMainLoop();

    return 0;
}
