// OpenSG FBO example: 29FBOTexture.cpp
//
// Shows how to use the FBOViewport for render-to-texture
//

#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGGradientBackground.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGTextureChunk.h>
#include <OpenSG/OSGFBOViewport.h>
#include <OpenSG/OSGSimpleTexturedMaterial.h>
#include <OpenSG/OSGMatrixUtility.h>
#include <OpenSG/OSGPointLight.h>
#include <OpenSG/OSGQuaternion.h>
#include <OpenSG/OSGGeoFunctions.h>
#include <OpenSG/OSGImageFunctions.h>
#include <OpenSG/OSGTwoSidedLightingChunk.h>
#include <OpenSG/OSGComponentTransform.h>
#include <OpenSG/OSGImageFileType.h>
#include <OpenSG/OSGTextureTransformChunk.h>

OSG_USING_NAMESPACE

// globals
SimpleSceneManager *mgr          (NULL);
FBOViewportPtr      fboVP        (NullFC);
TransformPtr        fboSceneTrans(NullFC);
NodePtr             fboCamBeacon (NullFC);
GeometryPtr         flagGeo      (NullFC);

// flag parameters
const float flagHeight   = 8.0f;
const float flagWidth    = 16.0f;
const int   flagGeoHor   = (int)flagWidth  * 3;
const int   flagGeoVert  = (int)flagHeight / 2;
const float flagWaveDamp = 0.06f;

const float poleHeight   = 24.0f;
const float poleDia      = poleHeight * 0.01f;

// fbo size
const int   fboWidth     = (int)flagWidth  * 32;
const int   fboHeight    = (int)flagHeight * 32;

// forward declarations
Matrix showAll(NodePtr root, PerspectiveCameraPtr cam);

void animateFlag (Real64 t);
void spinFBOScene(Real64 t);

SimpleTexturedMaterialPtr createWoodMaterial();
NodePtr buildFlag(TextureChunkPtr fboTexture, const int &flagHor, const int &flagVert);
NodePtr buildFBOScene(int argc, char **argv );
void setupFBO(TextureChunkPtr fboTexture, GLUTWindowPtr gwin, NodePtr fboScene );
          
// redraw the window
void display(void)
{
    static Real64 t0 = OSG::getSystemTime();

    // get the current time
    Real64 t = OSG::getSystemTime() - t0;

    // animate flag
    animateFlag(t);

    // spin the fbo scene
    spinFBOScene(t);

    // render fbo and main scene
    ::mgr->redraw();
}

// react to size changes
void reshape(int w, int h)
{
    ::mgr->resize(w,h);
    glutPostRedisplay();
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
    if (state)
        ::mgr->mouseButtonRelease(button, x, y);
    else
        ::mgr->mouseButtonPress(button, x, y);

    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    ::mgr->mouseMove(x, y);
    glutPostRedisplay();
}

// react to keys
void keyboard(unsigned char k, int, int)
{
    switch(k)
    {
    case 27:    exit(1);
    default:    break;
    }
}


int main(int argc, char **argv)
{
    // OpenSG init
    osgInit(argc,argv);

    // GLUT init
    glutInit(&argc, argv);
    glutInitWindowSize(800,600);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    int winid = glutCreateWindow("OpenSG " OSG_VERSION_STRING " FBO example");

    // register GLUT callbacks
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);


    // create a GLUTWindow
    GLUTWindowPtr gwin = GLUTWindow::create();
    beginEditCP(gwin);
        gwin->setId(winid);
        gwin->init();
    endEditCP(gwin);

    // create the SimpleSceneManager helper
    ::mgr = new SimpleSceneManager;
    
    // create the texture that is used as render target by the sub-scene
    // and as texture in the main scene
    TextureChunkPtr fboTexture = TextureChunk::create();
    beginEditCP(fboTexture);
        fboTexture->setEnvMode(GL_MODULATE);
    endEditCP(fboTexture);
     
    // create the main scene
    NodePtr mainScene = buildFlag(fboTexture, ::flagGeoHor, ::flagGeoVert);

    // create the fbo scene
    NodePtr fboScene  = buildFBOScene(argc, argv);
    
    // create and setup the FBO
    setupFBO(fboTexture, gwin, fboScene);
    
    // create the window and initial camera/viewport
    ::mgr->setWindow(gwin);

    // tell the manager what to manage
    ::mgr->setRoot(mainScene);

    // show the whole scene
    ::mgr->showAll();

    // set a nicer background
    GradientBackgroundPtr bkg = GradientBackground::create();
    beginEditCP(bkg);
        bkg->addLine(Color3f(0.7, 0.7, 0.8), 0);
        bkg->addLine(Color3f(0.0, 0.1, 0.3), 1);
    endEditCP(bkg);
    gwin->getPort(0)->setBackground(bkg);
    
    // enable logo
    mgr->useOpenSGLogo();
    
    // add the FBOViewport as first vp to the window - it must be rendered
    // before the full scene
    beginEditCP(gwin);
        ViewportPtr vp = gwin->getPort(0);
        addRefCP(vp);
        
        gwin->subPort(0);
        gwin->addPort(fboVP);
        gwin->addPort(vp   );
    endEditCP  (gwin);
    
    // make sure the window is setup before rendering to the FBO
    mgr->redraw();

    // enter the GLUT main loop
    glutMainLoop();

    return 0;
}

// copied from SimpleSceneManager
Matrix showAll(NodePtr root, PerspectiveCameraPtr cam)
{
    root->updateVolume();

    Vec3f min,max;
    root->getVolume().getBounds( min, max );
    Vec3f d = max - min;

    if(d.length() < Eps) // Nothing loaded? Use a unity box
    {
        min.setValues(-1.f,-1.f,-1.f);
        max.setValues( 1.f, 1.f, 1.f);
        d = max - min;
    }

    Real32 dist = osgMax(d[0],d[1]) / (2 * osgtan(cam->getFov() / 2.f));

    Vec3f up(0,1,0);
    Pnt3f at((min[0] + max[0]) * .5f,(min[1] + max[1]) * .5f,(min[2] + max[2]) * .5f);
    Pnt3f from = at;
    from[2]+=(dist+fabs(max[2]-min[2])*0.5f);

    // set the camera to go from 1% of the object to twice its size
    Real32 diag = osgMax(osgMax(d[0], d[1]), d[2]);
    beginEditCP(cam);
        cam->setFar  (10 * diag);
    endEditCP(cam);

    Matrix m;
    MatrixLookAt(m, from, at, up);

    return m;
}

void animateFlag( Real64 t )
{
    // get positions
    GeoPositions3fPtr pos = GeoPositions3fPtr::dcast(::flagGeo->getPositions());
    beginEditCP(pos, GeoPositions3f::GeoPropDataFieldMask);
        Pnt3f offset(-0.5f * flagWidth, 3, 0);
        float t2 = 8.0f * t;
        for(UInt32 i = 0; i < pos->getSize(); ++i)
        {
            Pnt3f p = pos->getValue(i);
            float v = p.dist(offset);
            // the flag geometry is centered at the origin
            // we need to offset the wave calculations
            float x = p[0] - offset.x();
            // make a wave, dampened towards the poleS
            p[2]  = x * flagWaveDamp * osgsin(v-t2);
            pos->setValue(p, i);
        }
    endEditCP(pos, GeoPositions3f::GeoPropDataFieldMask);   
   
    // correct normals
    calcVertexNormals(::flagGeo);
}

void spinFBOScene( Real64 t )
{
    beginEditCP(::fboSceneTrans, Transform::MatrixFieldMask);
        Matrix m;
        Quaternion q;
        q.setValueAsAxisDeg(0, 1, 0, t * 16.66f);
        m.setRotate(q);
        ::fboSceneTrans->setMatrix(m);
    endEditCP(::fboSceneTrans, Transform::MatrixFieldMask);
}


// create a wood texture
SimpleTexturedMaterialPtr createWoodMaterial()
{
    SimpleTexturedMaterialPtr mat = SimpleTexturedMaterial::create();
    beginEditCP(mat);
        ImagePtr img = Image::create();
        createNoise(img, Image::OSG_L_PF, 7, 64);
        mat->setImage(img);
        mat->setEnvMode(GL_MODULATE);
        mat->setDiffuse(Color3f(0.9f, 0.57f, 0.1f));
        mat->setSpecular(Color3f(0.2f, 0.2f, 0.1f));
        TextureTransformChunkPtr ttrans = TextureTransformChunk::create();
        beginEditCP(ttrans);
            Matrix m;
            m.setScale(2.0, 8.0, 2.0);
            ttrans->setMatrix(m);
        endEditCP(ttrans);
        mat->addChunk(ttrans);
    endEditCP(mat);

    return mat;
}

NodePtr buildFlag(TextureChunkPtr fboTexture, const int &flagHor, const int &flagVert)
{
    NodePtr flagScene = makeCoredNode<Group>();
    
    ::flagGeo = makePlaneGeo(flagWidth, flagHeight, flagHor, flagVert);
    
    // disable caching as we will change this geometry every frame
    beginEditCP(::flagGeo);
        ::flagGeo->setVbo(false);
        ::flagGeo->setDlistCache(false);
    endEditCP(::flagGeo);

    SimpleMaterialPtr fboMaterial = SimpleMaterial::create();
    beginEditCP(fboMaterial);
        fboMaterial->addChunk(fboTexture);
        
        // add a light glossy effect (environment noise-map)
        {
            ImagePtr noise = Image::create();
            createNoise(noise, Image::OSG_I_PF, 5, 256);
            beginEditCP(noise);
                // make noise image darker (as it will be GL_ADDed)
                UInt8 *data = noise->editData();
                for(int i = 0; i < noise->getSize(); ++i)
                    data[i] >>= 2; // *= 0.125
            endEditCP(noise);
            TextureChunkPtr gloss = TextureChunk::create();
            beginEditCP(gloss);
                gloss->setImage(noise);
                gloss->setEnvMode(GL_ADD);
            endEditCP(gloss);
            TexGenChunkPtr envMap = TexGenChunk::create();
            beginEditCP(envMap);
                envMap->setGenFuncS(GL_SPHERE_MAP);
                envMap->setGenFuncT(GL_SPHERE_MAP);
            endEditCP(envMap);
            // add for use with 2nd texture unit
            fboMaterial->addChunk(gloss, 1);
            fboMaterial->addChunk(envMap, 1);
        }
 
        fboMaterial->addChunk(TwoSidedLightingChunk::create());
        fboMaterial->setSpecular(Color3f(0.7f, 0.7f, 0.7f));
        fboMaterial->setDiffuse(Color3f(0.22f, 0.2f, 0.2f));
    endEditCP(fboMaterial);


    beginEditCP(::flagGeo);
        ::flagGeo->setMaterial(fboMaterial);
    endEditCP(::flagGeo);

    // create transform node to hook up the flag to the pole
    ComponentTransformPtr flagTrans;
    NodePtr flag = makeCoredNode<ComponentTransform>(&flagTrans);
    beginEditCP(flagTrans);
        Vec3f v(0.5f * flagWidth, 0.5f * (poleHeight - flagHeight) , 0.0f);
        flagTrans->setTranslation(v);
    endEditCP(flagTrans);

    // attach flag-geometry to transform-node
    beginEditCP(flag);
        flag->addChild(makeNodeFor(::flagGeo));
    endEditCP(flag);

    // build flag pole
    NodePtr pole = makeCylinder(poleHeight, poleDia, 24, true, true, true);
    MaterialPtr woodMat = createWoodMaterial();
    GeometryPtr cyl = GeometryPtr::dcast(pole->getCore());
    beginEditCP(cyl);
        cyl->setMaterial(woodMat);
    endEditCP(cyl);

    // attach objects to group node
    beginEditCP(flagScene);
        flagScene->addChild(flag);
        flagScene->addChild(pole);
    endEditCP(flagScene);

    return flagScene;
}

NodePtr buildFBOScene( int argc, char ** argv )
{
    PointLightPtr light;
    NodePtr fboRoot = makeCoredNode<PointLight>(&light);
    ::fboCamBeacon = makeNodeFor(Transform::create());

    // attach camera beacon to root node
    beginEditCP(fboRoot);
        fboRoot->addChild(::fboCamBeacon);
    endEditCP(fboRoot);

    // set camera beacon as light beacon (-> headlight)
    beginEditCP(light);
        light->setBeacon(::fboCamBeacon);
        light->setOn(true);
    endEditCP(light);

    // load given model, the cow, or make a torus
    NodePtr scene;
    if(argc >= 2)
        scene = SceneFileHandler::the().read(argv[1]);
    else
        scene = SceneFileHandler::the().read("Data/cow.obj.gz");

    // fallback if loading failed
    if(!scene)
        scene = makeTorus(0.3, 4, 16, 64);

    NodePtr fboScene = makeCoredNode<Transform>(&::fboSceneTrans);
    beginEditCP(fboScene);
    beginEditCP(fboRoot);
        fboScene->addChild(scene);
        fboRoot->addChild(fboScene);
    endEditCP(fboRoot);
    endEditCP(fboScene);

    return fboRoot;
}

void setupFBO( TextureChunkPtr fboTexture, GLUTWindowPtr gwin, NodePtr fboScene )
{
    // setup FBO
    ImagePtr img = Image::create();
    beginEditCP(img);
        img->set(Image::OSG_RGBA_PF, ::fboWidth, ::fboHeight);
    endEditCP(img);
    beginEditCP(fboTexture);
        fboTexture->setMinFilter(GL_LINEAR);
        fboTexture->setMagFilter(GL_LINEAR);
        fboTexture->setTarget(GL_TEXTURE_2D);
        fboTexture->setInternalFormat(GL_RGBA8);
        fboTexture->setImage(img);
    endEditCP(fboTexture);


    // add background
    GradientBackgroundPtr bg = GradientBackground::create();
    beginEditCP(bg);
        // flag of neutral-moresnet
        bg->addLine(Color3f(0.0, 0.0, 0.8), 0.000);
        bg->addLine(Color3f(0.0, 0.0, 0.8), 0.333);

        bg->addLine(Color3f(0.8, 0.8, 0.8), 0.333);
        bg->addLine(Color3f(0.8, 0.8, 0.8), 0.666);

        bg->addLine(Color3f(0.0, 0.0, 0.0), 0.666);
        bg->addLine(Color3f(0.0, 0.0, 0.0), 1.000);
    endEditCP(bg);


    // setup camera
    PerspectiveCameraPtr fboCam = PerspectiveCamera::create();
    beginEditCP(fboCam);
        // we already compensated aspect ratio with the texture/fbo sizes
        fboCam->setAspect(1.0);
        fboCam->setFov(osgdegree2rad(60));
        fboCam->setNear(0.01);
        fboCam->setFar(100);
        fboCam->setBeacon(::fboCamBeacon);
    endEditCP(fboCam);

    // create FBOViewport
    ::fboVP = FBOViewport::create();
    beginEditCP(::fboVP);
        ::fboVP->setSize(0, 0, ::fboWidth - 1, ::fboHeight - 1);
        ::fboVP->setStorageWidth(::fboWidth);
        ::fboVP->setStorageHeight(::fboHeight);
        ::fboVP->setBackground(bg);
        ::fboVP->setCamera(fboCam);
        ::fboVP->setParent(gwin);
        // attach texture as render target
        ::fboVP->editMFTextures()->push_back(fboTexture);
        ::fboVP->setRoot(fboScene);
    endEditCP(::fboVP);

    // set the fbo camera to show the whole model
    TransformPtr trans = TransformPtr::dcast(::fboCamBeacon->getCore());
    beginEditCP(trans, Transform::MatrixFieldMask);
        trans->setMatrix(showAll(fboScene, fboCam));
    endEditCP(trans, Transform::MatrixFieldMask);
}
