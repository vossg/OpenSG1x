
#include <OSGGLUT.h>

#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>

#include <OSGTime.h>
#include <OSGImage.h>
#include <OSGTextureChunk.h>
#include <OSGComponentTransform.h>
#include <OSGMatrixCamera.h>

#include <OSGTextureGrabForeground.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

GeoTexCoords2fPtr texcoords;

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
    NodePtr scene = makeTorus(.5, 2, 16, 16);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);
    
    // Create the textured material
    
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
    tex->setEnvMode(GL_MODULATE);
    tex->setInternalFormat(GL_RGB5);
    endEditCP  (tex);
    addRefCP(tex);
   
    SimpleMaterialPtr mat = SimpleMaterial::create();
    beginEditCP(mat);
    mat->setLit(false);
    mat->setDiffuse(Color3f(1,.5,.5));
    mat->addChunk(tex);
    endEditCP(mat);
    
    // Add the grab foreground
    
    TextureGrabForegroundPtr tg = TextureGrabForeground::create();
    
    beginEditCP(tg);
    tg->setTexture(tex);
    endEditCP(tg);
    
    // take the viewport
    ViewportPtr vp = gwin->getPort(0);
    
    beginEditCP(vp);
    vp->setLeft(0);
    vp->setRight(1);
    vp->setBottom(0);
    vp->setTop(1);
    
    vp->getForegrounds().push_back(tg);
    
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
    
    ViewportPtr vp2 = Viewport::create();
    beginEditCP(vp2);
    vp2->setCamera(cam);
    vp2->setRoot(tr);
    vp2->setBackground(vp->getBackground());
    
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
