
#include <string>

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

#include <OSGImage.h>
#include <OSGImageFileHandler.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

SimpleMaterialPtr cuberefmat;
TextureTransformChunkPtr ttransform;

TexGenChunkPtr texgen;
TextureChunkPtr tex;
std::string imagefn;

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
    case ' ':   beginEditCP(cuberefmat);
                if(cuberefmat->find(texgen) < 0)
                {
                    cuberefmat->addChunk(texgen);
                    cuberefmat->addChunk(ttransform);
                    FLOG(("Texgen added\n"));
                }
                else
                {
                    cuberefmat->subChunk(texgen);                
                    cuberefmat->subChunk(ttransform);
                    FLOG(("Texgen subbed\n"));
                }
                endEditCP(cuberefmat);
                break;
    case 't':   beginEditCP(cuberefmat);
                if(cuberefmat->find(ttransform) < 0)
                {
                    cuberefmat->addChunk(ttransform);
                    FLOG(("TexTransform added\n"));
                }
                else
                {
                    cuberefmat->subChunk(ttransform);
                    FLOG(("TexTransform subbed\n"));
                }
                endEditCP(cuberefmat);
                break;
    case 'r':   beginEditCP(texgen);
                if(texgen->getGenFuncS() == GL_REFLECTION_MAP_ARB)
                {
                    texgen->setGenFuncS(GL_NORMAL_MAP_ARB);
                    texgen->setGenFuncT(GL_NORMAL_MAP_ARB);
                    texgen->setGenFuncR(GL_NORMAL_MAP_ARB);   
                }
                else
                {
                    texgen->setGenFuncS(GL_REFLECTION_MAP_ARB);
                    texgen->setGenFuncT(GL_REFLECTION_MAP_ARB);
                    texgen->setGenFuncR(GL_REFLECTION_MAP_ARB);   
                }
                endEditCP(texgen);
                break;
    case 'l':
    {
                ImagePtr cubeimage = ImageFileHandler::the().read(imagefn.c_str());
                cubeimage->dump();
                beginEditCP(tex);
                    tex->setImage(cubeimage);
                endEditCP(tex);
                break;
    }
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
    bool use_cube = false;
    bool is_cube = false;
    
    ImagePtr cubeimage;

    if(argc > 1)
    {
        imagefn = argv[1];
        cubeimage = ImageFileHandler::the().read(argv[1]);
        cubeimage->dump();
        argc--, argv++;
    }
    else
    {
        UChar8 cubedata[] = { 0,255,255,  0,128,128,  0,64,64,  255,255,255,
                              255,0,255,  128,0,128,  64,0,64,  255,255,255,
                              255,255,0,  128,128,0,  64,64,0,  255,255,255,
                              0,0,255,  0,0,128,  0,0,64,  255,255,255,
                              0,255,0,  0,128,0,  0,64,0,  255,255,255,
                              255,0,0,  128,0,0,  64,0,0,   255,255,255 };
                              
        cubeimage = Image::create();
        beginEditCP(cubeimage);
        cubeimage->set( Image::OSG_RGB_PF, 2, 2, 1, 1, 1, 0, cubedata, 
                        Image::OSG_UINT8_IMAGEDATA, true, 6 );
        endEditCP(cubeimage);
        is_cube = true;
    }
    
    if(argc > 1)
    {
        scene = SceneFileHandler::the().read(argv[1]);
    }
    else
    {
        //scene = makeTorus(.5, 3, 16, 16);
        scene = makeLatLongSphere(16, 16, 3);
    }

    // create the cube reflection material
    cuberefmat = SimpleMaterial::create();
    
    ttransform = TextureTransformChunk::create();
    addRefCP(ttransform);
    
    TextureChunkPtr ctex;
    
    if(use_cube)
    {
        CubeTextureChunkPtr cubetex = CubeTextureChunk::create();

        UChar8 negz[] = {  255,0,0,  128,0,0,  64,0,0,   255,255,255 },
               posz[] = {  0,255,0,  0,128,0,  0,64,0,  255,255,255 },
               negy[] = {  0,0,255,  0,0,128,  0,0,64,  255,255,255 },
               posy[] = {  255,255,0,  128,128,0,  64,64,0,  255,255,255 },
               negx[] = {  255,0,255,  128,0,128,  64,0,64,  255,255,255 },
               posx[] = {  0,255,255,  0,128,128,  0,64,64,  255,255,255 };

        ImagePtr inegz = Image::create();
        ImagePtr iposz = Image::create();
        ImagePtr inegy = Image::create();
        ImagePtr iposy = Image::create();
        ImagePtr inegx = Image::create();
        ImagePtr iposx = Image::create();

        inegz->set( Image::OSG_RGB_PF, 2, 2, 1, 1, 1, 0, negz );
        iposz->set( Image::OSG_RGB_PF, 2, 2, 1, 1, 1, 0, posz );
        inegy->set( Image::OSG_RGB_PF, 2, 2, 1, 1, 1, 0, negy );
        iposy->set( Image::OSG_RGB_PF, 2, 2, 1, 1, 1, 0, posy );
        inegx->set( Image::OSG_RGB_PF, 2, 2, 1, 1, 1, 0, negx );
        iposx->set( Image::OSG_RGB_PF, 2, 2, 1, 1, 1, 0, posx );

        beginEditCP(cubetex);
        cubetex->setImage( inegz );
        cubetex->setPosZImage( iposz );
        cubetex->setPosYImage( iposy );
        cubetex->setNegYImage( inegy );
        cubetex->setPosXImage( iposx );
        cubetex->setNegXImage( inegx );
        cubetex->setMinFilter( GL_LINEAR );
        cubetex->setMagFilter( GL_NEAREST );
        cubetex->setWrapS( GL_CLAMP_TO_EDGE );
        cubetex->setWrapT( GL_CLAMP_TO_EDGE );
        cubetex->setEnvMode( GL_MODULATE );
        endEditCP(cubetex);
        
        ctex = cubetex;
        is_cube = true;
    }
    else
    {
         
        tex = TextureChunk::create();
        
        beginEditCP(tex);
        tex->setImage( cubeimage );
        if(cubeimage->getMipMapCount() > 1)
            tex->setMinFilter( GL_LINEAR_MIPMAP_LINEAR );
        else
            tex->setMinFilter( GL_LINEAR );
        tex->setMagFilter( GL_NEAREST );
        tex->setWrapS( GL_CLAMP_TO_EDGE );
        tex->setWrapT( GL_CLAMP_TO_EDGE );
        tex->setEnvMode( GL_MODULATE );
        endEditCP(tex);
        
        ctex = tex;
        is_cube = (cubeimage->getSideCount() > 1);
    }
    
    texgen = TexGenChunk::create();
    addRefCP(texgen);
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
    cuberefmat->addChunk(ctex);
    if(is_cube)
    {
        cuberefmat->addChunk(ttransform);
        cuberefmat->addChunk(texgen); 
    }
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
