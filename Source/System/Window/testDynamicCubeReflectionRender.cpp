
#include <OSGGLUT.h>
#include <OSGGLEXT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGPassiveWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSceneFileHandler.h>
#include <OSGSolidBackground.h>
#include <OSGTextureGrabForeground.h>
#include <OSGImage.h>
#include <OSGDirectionalLight.h>
#include <OSGMatrixCameraDecorator.h>

#include <OSGSimpleMaterial.h>
#include <OSGCubeTextureChunk.h>
#include <OSGTexGenChunk.h>
#include <OSGTextureTransformChunk.h>

#include <OSGTestCubeMaps.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

SimpleMaterialPtr cuberefmat;
TextureTransformChunkPtr ttransform;
PassiveWindowPtr pwin;

TransformPtr rtrans;
NodePtr scene, reflector;

CameraPtr camera;

// redraw the window
void display(void)
{    
    Real32 time = glutGet(GLUT_ELAPSED_TIME); 
     
    // move the reflector
    
    Pnt3f smin,smax,rmin,rmax;
    Real32 sdia,rdia;
    
    scene->updateVolume();
    smin = scene->getVolume().getMin();
    smax = scene->getVolume().getMax();
    sdia = (smax-smin).length();
    
    reflector->updateVolume();
    rmin = reflector->getVolume().getMin();
    rmax = reflector->getVolume().getMax();
    rdia = (rmax-rmin).length();
  
    Matrix m;
    m.setTransform(Vec3f( osgcos(time / 1500) * (rdia+sdia) *.7,
                          osgcos(time / 1500) * (rdia+sdia) *.7,
                          // ((smax+smin.subZero()) * .5)[1],
                          osgsin(time / 1500) * (rdia+sdia)) *.7);
    
    beginEditCP(rtrans);
    rtrans->setMatrix(m);
    endEditCP(rtrans);
    
    
     
    // transform the cube reflection texture coords
    Matrix n;
    camera->getViewing(n, pwin->getPort()[0]->getPixelWidth(), pwin->getPort()[0]->getPixelHeight());
    
    n.transpose();
    
    beginEditCP(ttransform);
    ttransform->setMatrix(n);
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



Action::ResultE setGeoMaterial(NodePtr& node)
{   
    GeometryPtr geo = GeometryPtr::dcast(node->getCore());
    
    if(geo!=NullFC)
    {
        geo->setMaterial(cuberefmat);
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

    pwin=PassiveWindow::create();
    pwin->init();        

    // create the scene
    if(argc > 1)
    {
        scene = SceneFileHandler::the().read(argv[1]);
    }
    else
    {
        scene = Node::create();       
        beginEditCP(scene);
        scene->setCore(Group::create());
        
        NodePtr lightnode = Node::create();
        DirectionalLightPtr light = DirectionalLight::create();
        beginEditCP(light);
        light->setBeacon(lightnode);
        light->setAmbient(Color4f(1,1,1,1));
        light->setDiffuse(Color4f(1,1,1,1));
        light->setSpecular(Color4f(1,1,1,1));
        light->setDirection(Vec3f(1,1,1));

        beginEditCP(lightnode);
        lightnode->setCore(light);
        lightnode->addChild(makeTorus(.5, 3, 16, 16));
        endEditCP(lightnode);
        
        scene->addChild(lightnode);
        
        endEditCP(scene);
    }
    
    // cubemap size
    UInt32 cmsize = 128;
    
    
    if(argc > 2)
    {
        if(sscanf(argv[2], "%d", &cmsize)!=1)
            cmsize = 128;
    }
    
    
    // show the cube map viewports
    bool showports = true;
    
    // create the reflector
    if(argc > 3)
    {
        reflector = SceneFileHandler::the().read(argv[3]);
    }
    else
    {
        // scene = makeTorus(.5, 3, 16, 16);
        reflector = makeSphere(3, 1);
    }
   
    NodePtr rtransnode = Node::create();
    rtrans = Transform::create();

    beginEditCP(rtransnode);
    rtransnode->setCore(rtrans);
    rtransnode->addChild(reflector);
    endEditCP(rtransnode);

    // create the cube reflection material
    cuberefmat = SimpleMaterial::create();
    
    ttransform = TextureTransformChunk::create();
    
    CubeTextureChunkPtr cubetex = CubeTextureChunk::create();

    ImagePtr img = Image::create();
    
    beginEditCP(img);
    img->set(Image::OSG_RGB_PF, 256, 256);
    endEditCP(img);
    
    // using the same image is no problem, as it's replaced directly in texture
    // memory
    beginEditCP(cubetex);
    cubetex->setImage(img); 
    cubetex->setPosZImage(img);
    cubetex->setNegXImage(img);
    cubetex->setPosXImage(img);
    cubetex->setNegYImage(img);
    cubetex->setPosYImage(img);
    cubetex->setMinFilter(GL_LINEAR);
    cubetex->setMagFilter(GL_LINEAR);   
    cubetex->setMinFilter(GL_LINEAR_MIPMAP_LINEAR);
    cubetex->setWrapR(GL_CLAMP);   
    cubetex->setWrapS(GL_CLAMP);   
    cubetex->setWrapT(GL_CLAMP);   
    endEditCP(cubetex);
     
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
    
    // set the reflector to use the cube reflection material
    traverse(reflector, 
             osgTypedFunctionFunctor1CPtrRef<Action::ResultE, NodePtr>
             (setGeoMaterial));

    // create the root
    NodePtr rootnode = Node::create();
    GroupPtr root = Group::create();
    
    beginEditCP(rootnode);
    rootnode->setCore(root);
    rootnode->addChild(scene);
    rootnode->addChild(rtransnode);  
    endEditCP(rootnode);
    
    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // create the window and initial camera/viewport
    mgr->setWindow(pwin);
    // tell the manager what to manage
    mgr->setRoot  (rootnode);
    
    mgr->setHeadlight(false);
    
    // create the cube texture viewports
    GLenum targets[6] = { GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB,
                          GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB,
                          GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB,
                          GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB,
                          GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB,
                          GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB };

#if 0                          
    Matrix transforms[6] = { Matrix(-1,0, 0,0,  0,1, 0,0,   0, 0, 1,0, 0,0,0,1),
                             Matrix( 1,0, 0,0,  0,1, 0,0,   0, 0,-1,0, 0,0,0,1),
                             Matrix(-1,0, 0,0,  0,0, 1,0,   0,-1, 0,0, 0,0,0,1),
                             Matrix(-1,0, 0,0,  0,0,-1,0,   0, 1, 0,0, 0,0,0,1),
                             Matrix( 0,0,-1,0,  0,1, 0,0,  -1, 0, 0,0, 0,0,0,1),
                             Matrix( 0,0, 1,0,  0,1, 0,0,   1, 0, 0,0, 0,0,0,1)
                           };
#else                          
    Matrix transforms[6] = { Matrix( 1,0, 0,0,  0,1, 0,0,   0, 0, 1,0, 0,0,0,1),
                             Matrix(-1,0, 0,0,  0,1, 0,0,   0, 0,-1,0, 0,0,0,1),
                             Matrix( 1,0, 0,0,  0,0, 1,0,   0,-1, 0,0, 0,0,0,1),
                             Matrix( 1,0, 0,0,  0,0,-1,0,   0, 1, 0,0, 0,0,0,1),
                             Matrix( 0,0,-1,0,  0,1, 0,0,   1, 0, 0,0, 0,0,0,1),
                             Matrix( 0,0, 1,0,  0,1, 0,0,  -1, 0, 0,0, 0,0,0,1)
                           };
#endif
     
    Pnt2f positions[6] = {  Pnt2f(1,1), Pnt2f(3,1), Pnt2f(1,2), 
                            Pnt2f(1,0), Pnt2f(0,1), Pnt2f(2,1) };
                            
                       
    // main camera, needed for texture transformation
    camera = pwin->getPort()[0]->getCamera();
    // the Camera for the cubemap
    PerspectiveCameraPtr cam = PerspectiveCamera::create();
    beginEditCP(cam);
    cam->setFov(osgdegree2rad(90));
    cam->setAspect(1);
    
    scene->updateVolume();
    Real32 dia = (scene->getVolume().getMax() -
                  scene->getVolume().getMin()).length();
                  
    cam->setNear(dia / 10.f);
    cam->setFar(dia * 10.f);   
    cam->setBeacon(rtransnode);
    endEditCP(cam);
    
    SolidBackgroundPtr bkg = SolidBackground::create();
    beginEditCP(bkg);
    bkg->setColor(Color3f(0,0,1));
    endEditCP(bkg);
    
    beginEditCP(pwin);
    for(UInt16 i = 0; i < 6; ++i)
    {
        ViewportPtr vp = Viewport::create();
        beginEditCP(vp);
        
        Real32 l,b;
        if(showports)
        {
            l = positions[i][0] * cmsize;
            b = positions[i][1] * cmsize;
        }
        else
        {
            l = b = 0;
        }
        vp->setLeft(l);
        vp->setRight(l + cmsize - 1);
        vp->setBottom(b);
        vp->setTop(b + cmsize - 1);
        
        vp->setRoot(scene);
        vp->setBackground(bkg);

        MatrixCameraDecoratorPtr deco = MatrixCameraDecorator::create();      
        beginEditCP(deco);
        deco->setDecoratee(cam);
        deco->setPreProjection(transforms[i]);
        endEditCP(deco);
        
        vp->setCamera(deco);
        
        TextureGrabForegroundPtr fg = TextureGrabForeground::create();
        beginEditCP(fg);
        fg->setTexture(cubetex);
        fg->setBindTarget(GL_TEXTURE_CUBE_MAP_ARB);
        fg->setCopyTarget(targets[i]);      
        endEditCP(fg);
         
        vp->getForegrounds().push_back(fg);
        
        if(showports)
        {
            pwin->addPort(vp);
        }
        else
        {
            // add the ports before the main port, to make them invisible
            vp->setParent(pwin);
            pwin->getPort().insert(pwin->getPort().begin(), vp);
        }
       
        endEditCP(vp);
    }
    endEditCP(pwin);
   
    // show the whole scene
    mgr->showAll();
    mgr->redraw();
   
    // GLUT main loop
    glutMainLoop();

    return 0;
}
