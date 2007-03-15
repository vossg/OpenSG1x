#include <OSGGLUT.h>
#include <OSGConfig.h>

#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGBaseFunctions.h>

#include <OSGSpotLight.h>
#include <OSGDirectionalLight.h>
#include <OSGPointLight.h>            

#include <OSGViewport.h>
#include <OSGPerspectiveCamera.h>
#include <OSGTextureBackground.h>
#include <OSGGradientBackground.h>
#include <OSGSolidBackground.h>    
#include <OSGDrawAction.h>
#include <OSGRenderAction.h>
#include <OSGImage.h>
#include <OSGSimpleMaterial.h>
#include <OSGTextureChunk.h>
#include <OSGPolygonChunk.h>

#include <OSGTransform.h>
#include <OSGGroup.h>
#include <OSGTrackball.h>

#include <OSGMatrix.h>
#include <OSGQuaternion.h>
#include <OSGVector.h>

#include <OSGSHLChunk.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSceneFileHandler.h>    

#include <OSGShadowViewport.h>

#include <OSGFBOViewport.h>

// vertex shader program for bump mapping in surface local coordinates
static std::string _vp_program =
"void main(void)\n"
"{\n"
"    gl_Position = ftransform();\n"
"    gl_TexCoord[0]  = gl_TextureMatrix[0] * gl_MultiTexCoord0;\n"
"}\n";

// fragment shader program for bump mapping in surface local coordinates
static std::string _fp_program =
"uniform sampler2D tex0;\n"
"void main (void)\n"
"{\n"
"    gl_FragColor = texture2D(tex0, gl_TexCoord[0].st);\n"
"}\n";


OSG_USING_NAMESPACE

SimpleSceneManager *mgr;
GLUTWindowPtr gwin;
ShadowViewportPtr vp;

FBOViewportPtr fbo_vp;
UInt16 imageWinWidth = 256;
UInt16 imageWinHeight = 256;

NodePtr rootNode;
SpotLightPtr spot1_core;
SpotLightPtr spot2_core;
DirectionalLightPtr raumlicht_core;
PointLightPtr _point1_core;
PointLightPtr _point2_core;
TransformPtr _box_trans;
TransformPtr _cylinder1_trans;
TransformPtr _cylinder2_trans;

NodePtr box_trans_node;
PerspectiveCameraPtr cam;


// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);
    gwin = GLUTWindow::create();

    // create root
    rootNode = makeCoredNode<Group>();
    NodePtr scene = makeCoredNode<Group>();

    // create lights
    TransformPtr point1_trans;
    NodePtr point1 = makeCoredNode<PointLight>(&_point1_core);
    NodePtr point1_beacon = makeCoredNode<Transform>(&point1_trans);
    beginEditCP(point1_trans);
        point1_trans->getMatrix().setTranslate(0.0, 0.0, 25.0);
    endEditCP(point1_trans);

    beginEditCP(_point1_core);
        _point1_core->setAmbient(0.15,0.15,0.15,1);
        _point1_core->setDiffuse(0.4,0.4,0.4,1);
        _point1_core->setSpecular(0.0,0.0,0.0,1);
        _point1_core->setBeacon(point1_beacon);
        _point1_core->setOn(true);
    endEditCP(_point1_core);

    TransformPtr point2_trans;
    NodePtr point2 = makeCoredNode<PointLight>(&_point2_core);
    NodePtr point2_beacon = makeCoredNode<Transform>(&point2_trans);
    beginEditCP(point2_trans);
        point2_trans->getMatrix().setTranslate(5.0, 5.0, 20.0);
    endEditCP(point2_trans);

    beginEditCP(_point2_core);
        _point2_core->setAmbient(0.15,0.15,0.15,1);
        _point2_core->setDiffuse(0.4,0.4,0.4,1);
        _point2_core->setSpecular(0.0,0.0,0.0,1);
        _point2_core->setBeacon(point2_beacon);
        _point2_core->setOn(true);
    endEditCP(_point2_core);

    beginEditCP(point1);
        point1->addChild(point2);
    endEditCP(point1);

    beginEditCP(point2);
        point2->addChild(scene);
    endEditCP(point2);

    // create scene
    
    // bottom
    NodePtr plane = makePlane(25.0, 25.0, 128, 128);
    
    int size = imageWinWidth*imageWinHeight*256;

    ImagePtr plane_img = Image::create();

    beginEditCP(plane_img);
    plane_img->set(Image::OSG_RGBA_PF, imageWinWidth, imageWinHeight, 1, 1, 1, 0, NULL);
    endEditCP(plane_img);

    TextureChunkPtr plane_tex = TextureChunk::create();
    beginEditCP(plane_tex);
        plane_tex->setImage(plane_img);
        plane_tex->setMinFilter(GL_LINEAR);
        plane_tex->setMagFilter(GL_LINEAR);
        plane_tex->setTarget(GL_TEXTURE_2D);
        plane_tex->setInternalFormat(GL_RGBA16F_ARB);
    endEditCP(plane_tex);

    SHLChunkPtr shl = SHLChunk::create();
    beginEditCP(shl);
        shl->setVertexProgram(_vp_program);
        shl->setFragmentProgram(_fp_program);
        shl->setUniformParameter("tex0", 0);
    endEditCP(shl);

    SimpleMaterialPtr plane_mat = SimpleMaterial::create();
    beginEditCP(plane_mat);
        plane_mat->setAmbient(Color3f(0.3,0.3,0.3));
        plane_mat->setDiffuse(Color3f(1.0,1.0,1.0));
        plane_mat->addChunk(plane_tex);
        plane_mat->addChunk(shl);
    endEditCP(plane_mat);

    GeometryPtr plane_geo = GeometryPtr::dcast(plane->getCore());
    beginEditCP(plane_geo);
        plane_geo->setMaterial(plane_mat);
    beginEditCP(plane_geo);
    
    // box
    box_trans_node = makeCoredNode<Transform>(&_box_trans);
    beginEditCP(_box_trans);
        _box_trans->getMatrix().setTranslate(0.0, 0.0, 12.0);
    endEditCP(_box_trans);
    NodePtr box = makeBox(4.0, 4.0, 0.8, 10, 10 , 10);
    beginEditCP(box_trans_node);
        box_trans_node->addChild(box);
    endEditCP(box_trans_node);
    
    PolygonChunkPtr pchunk = osg::PolygonChunk::create();
    beginEditCP(pchunk);
        pchunk->setCullFace(GL_BACK);
    endEditCP(pchunk);

    SimpleMaterialPtr box_mat = SimpleMaterial::create();
    beginEditCP(box_mat);
        box_mat->setAmbient(Color3f(0.0,0.0,0.0));
        box_mat->setDiffuse(Color3f(0.0,0.0,1.0));
        box_mat->addChunk(pchunk);
    endEditCP(box_mat);

    GeometryPtr box_geo = GeometryPtr::dcast(box->getCore());
    beginEditCP(box_geo);
        box_geo->setMaterial(box_mat);
    beginEditCP(box_geo);

    // cylinder1
    NodePtr cylinder1_trans_node = makeCoredNode<Transform>(&_cylinder1_trans);
    beginEditCP(_cylinder1_trans);
        _cylinder1_trans->getMatrix().setTranslate(0.0, 0.0, 5.0);
    endEditCP(_cylinder1_trans);
    NodePtr cylinder1 = OSG::makeCylinder(10.0, 0.4, 32, true, true ,true);
    beginEditCP(cylinder1_trans_node);
        cylinder1_trans_node->addChild(cylinder1);
    endEditCP(cylinder1_trans_node);

    SimpleMaterialPtr cylinder1_mat = SimpleMaterial::create();
    beginEditCP(cylinder1_mat);
        cylinder1_mat->setAmbient(Color3f(0.0,0.0,0.0));
        cylinder1_mat->setDiffuse(Color3f(1.0,0.0,0.0));
        cylinder1_mat->addChunk(pchunk);
    endEditCP(cylinder1_mat);

    GeometryPtr cylinder1_geo = GeometryPtr::dcast(cylinder1->getCore());
    beginEditCP(cylinder1_geo);
        cylinder1_geo->setMaterial(cylinder1_mat);
    beginEditCP(cylinder1_geo);
    
    // cylinder2
    NodePtr cylinder2_trans_node = makeCoredNode<Transform>(&_cylinder2_trans);
    beginEditCP(_cylinder2_trans);
        _cylinder2_trans->getMatrix().setTranslate(0.0, 0.0, 8.0);
    endEditCP(_cylinder2_trans);
    NodePtr cylinder2 = OSG::makeCylinder(10.0, 0.4, 32, true, true ,true);
    beginEditCP(cylinder2_trans_node);
        cylinder2_trans_node->addChild(cylinder2);
    endEditCP(cylinder2_trans_node);

    SimpleMaterialPtr cylinder2_mat = SimpleMaterial::create();
    beginEditCP(cylinder2_mat);
        cylinder2_mat->setAmbient(Color3f(0.0,0.0,0.0));
        cylinder2_mat->setDiffuse(Color3f(0.0,1.0,0.0));
        cylinder2_mat->addChunk(pchunk);
    endEditCP(cylinder2_mat);

    GeometryPtr cylinder2_geo = GeometryPtr::dcast(cylinder2->getCore());
    beginEditCP(cylinder2_geo);
        cylinder2_geo->setMaterial(cylinder2_mat);
    beginEditCP(cylinder2_geo);

    // scene
    beginEditCP(scene);
        scene->addChild(plane);
        scene->addChild(box_trans_node);
        scene->addChild(cylinder1_trans_node);
        scene->addChild(cylinder2_trans_node);
    endEditCP(scene);

    vp = ShadowViewport::create();
    
    GradientBackgroundPtr gbg = GradientBackground::create();
    SolidBackgroundPtr sbg = SolidBackground::create();

    UChar8 imgdata[] = {  255,0,0,  0,255,0,  0,0,255, 255,255,0 };
    ImagePtr img1 = Image::create();
    img1->set(Image::OSG_RGB_PF, 2, 2, 1, 1, 1, 0, imgdata);

    TextureChunkPtr tcPtr = TextureChunk::create();
    beginEditCP(tcPtr);
        tcPtr->setImage(img1);
    endEditCP(tcPtr);
    TextureBackgroundPtr bkg = TextureBackground::create();
    beginEditCP(bkg);
        bkg->setTexture(tcPtr);
    endEditCP(bkg);
    
    beginEditCP(sbg);
        sbg->setColor(Color3f(0.2,0.4,0.6));
    endEditCP(sbg);
    
    beginEditCP(gbg);
        gbg->addLine(Color3f(0.7, 0.7, 0.8), 0);
        gbg->addLine(Color3f(0.1, 0.1, 0.3), 1);
    endEditCP(gbg);

    beginEditCP(rootNode);
        rootNode->addChild(point1);
        rootNode->addChild(point1_beacon);
        rootNode->addChild(point2_beacon);
    endEditCP(rootNode);

    //FBOViewportPtr
    fbo_vp = FBOViewport::create();
    addRefCP(fbo_vp);

    // the Camera for the map
    cam = PerspectiveCamera::create();
    beginEditCP(cam);
        cam->setFov(osgdegree2rad(90));
        cam->setAspect(1);
        cam->setNear(0.001);
        cam->setFar(10000);
        cam->setBeacon(box_trans_node);
    endEditCP(cam);

    beginEditCP(fbo_vp);
        fbo_vp->setBackground(bkg);
        fbo_vp->setRoot(rootNode);
        fbo_vp->setCamera(cam);
        fbo_vp->setSize(0,0,imageWinWidth-1, imageWinHeight-1);
        fbo_vp->setStorageWidth(imageWinWidth);
        fbo_vp->setStorageHeight(imageWinHeight);
        fbo_vp->setDirty(true);
        fbo_vp->getTextures().push_back(plane_tex);
        fbo_vp->getExcludeNodes().push_back(plane);
        fbo_vp->setFboOn(true);
    endEditCP(fbo_vp);

    // normal shadow viewport
    beginEditCP(vp);
        vp->setBackground(gbg);
        vp->setRoot(rootNode);
        vp->setSize(0,0,1,1);
    endEditCP(vp);

    beginEditCP(gwin); //Window
        gwin->setId(winid);
        gwin->addPort(vp);
        gwin->init();
    endEditCP(gwin);

    Vec3f min,max;
    rootNode->updateVolume();
    rootNode->getVolume().getBounds( min, max );

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    mgr->setWindow(gwin);
    mgr->setRoot(rootNode);

    //Viewport
    beginEditCP(vp);
        vp->setCamera(mgr->getCamera());
    endEditCP(vp);

    mgr->turnHeadlightOff();

    mgr->showAll();

    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

//do Animation-Calculations here
void Animate()
{
    static Real64 t0 = OSG::getSystemTime();

    Real64 t = OSG::getSystemTime() - t0;

    Real32 rotb = t * 10.0;
    if(rotb > 360.0)
        rotb -= 360.0;

    Real32 rotc1 = t * 20.0;
    if(rotc1 > 360.0)
        rotc1 -= 360.0;

    Real32 rotc2 = t * 40.0;
    if(rotc2 > 360.0)
        rotc2 -= 360.0;

    Quaternion q;
    beginEditCP(_box_trans);
        q.setValueAsAxisDeg(0.2,0,1, rotb);
        _box_trans->getMatrix().setRotate(q);
    endEditCP(_box_trans);

    beginEditCP(_cylinder1_trans);
        q.setValueAsAxisDeg(0,0,1, rotc1);
        _cylinder1_trans->getMatrix().setRotate(q);
    endEditCP(_cylinder1_trans);

    beginEditCP(_cylinder2_trans);
        q.setValueAsAxisDeg(0,0,1, rotc2);
        _cylinder2_trans->getMatrix().setRotate(q);
    endEditCP(_cylinder2_trans);

    beginEditCP(box_trans_node);
    endEditCP(box_trans_node);
    beginEditCP(cam);
    endEditCP(cam);

    mgr->redraw();
    glutPostRedisplay();
}

static bool multipass = true;

// redraw the window
void display(void)
{
    WindowPtr win = mgr->getWindow();
    
    //mgr->redraw();
    win->activate();
    win->frameInit();
    
    //RenderAction *rAct = (RenderAction*)mgr->getAction();
    
    if (multipass)
    {
        RenderAction *rAct = RenderAction::create();
        
        fbo_vp->setParent(win);
        
        rAct->setWindow(win.getCPtr());
        
        fbo_vp->render(rAct);
        
        fbo_vp->setParent(NullFC);
        
        delete rAct;
        
        //multipass = false;
    }

    win->getPort(0)->render((RenderAction*)mgr->getAction());
    //win->renderAllViewports(rAct);

    win->swap();
    win->frameExit();
    win->deactivate();
}

// react to size changes
void reshape(int w, int h)
{
    mgr->resize( w, h );
    glutPostRedisplay();
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
    if ( state )
        mgr->mouseButtonRelease( button, x, y );
    else
        mgr->mouseButtonPress( button, x, y );
    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    mgr->mouseMove( x, y );
    glutPostRedisplay();
}

// react to keys
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:
        {
            OSG::osgExit();
            exit(0);
        }
        break;

        case '1':
        {
            beginEditCP(fbo_vp);
                fbo_vp->setCamera(mgr->getCamera());
            endEditCP(fbo_vp);
            break;
        }
        case '2':
        {
            beginEditCP(fbo_vp);
                fbo_vp->setCamera(cam);
            endEditCP(fbo_vp);
            break;
        }
        case 'm':
        {
            multipass = !multipass;
            FWARNING(("Toggle multipass to %s\n", multipass?"true":"false"));
            break;
        }
        case 'x':
        {
            SceneFileHandler::the().write(rootNode, "test.osb.gz", true);
        }
    }
    glutPostRedisplay();
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL | GLUT_DOUBLE);

    //Set WindowSize here
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(0, 0);
    int winid = glutCreateWindow("Framebuffer-Objects Mirror-Scene");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(Animate);

    return winid;
}
