#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGBaseFunctions.h>
#include <OSGSpotLight.h>
#include <OSGDirectionalLight.h>
#include <OSGPointLight.h>
#include <OSGPerspectiveCamera.h>
#include <OSGGradientBackground.h>
#include <OSGSolidBackground.h>
#include <OSGDrawAction.h>
#include <OSGRenderAction.h>
#include <OSGImage.h>
#include <OSGSimpleMaterial.h>
#include <OSGTextureChunk.h>
#include <OSGTransform.h>
#include <OSGGroup.h>
#include <OSGTrackball.h>
#include <OSGMatrix.h>
#include <OSGMatrixUtility.h>
#include <OSGQuaternion.h>
#include <OSGVector.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSceneFileHandler.h>
#include <OSGNavigator.h>
#include "OSGShadowViewport.h"

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

GLUTWindowPtr gwin;
ShadowViewportPtr svp;


NodePtr rootNode;
//DirectionalLightPtr _dir1_core;
PointLightPtr _dir1_core;

//SpotLightPtr _dir2_core;
PointLightPtr _dir2_core;
TransformPtr dir2_trans;

TransformPtr _obj1_trans;
TransformPtr _dino1_trans, _dino2_trans, _dino3_trans, _dino4_trans;
TransformPtr _tree1_trans, _tree2_trans, _tree3_trans, _tree4_trans,
    _tree5_trans, _tree6_trans, _tree7_trans, _tree8_trans, _tree9_trans;

MatrixCameraPtr camera;
PerspectiveCameraPtr Pcamera;
NodePtr cam_beacon;
TransformPtr cam_trans;
Vec3f camPos;
Vec3f camDir;

Navigator _navigator;
Int16 _lastx;
Int16 _lasty;
UInt16 _mousebuttons;

UInt32 frameCount;
Real32 fps = 0.0;
Real32 startTime2;


//FPS Counter
void startFpsCounter()
{
    startTime2 = OSG::getSystemTime();
}

void showFpsCounter()
{
    frameCount++;
    if(OSG::getSystemTime() - startTime2 >= 1.0)
    {
        printf("aktuelle FPS: %i\r", frameCount);
        frameCount = 0;
        startTime2 = OSG::getSystemTime();
    }
}



// forward declaration so we can have the interesting stuff upfront
int setupGLUT(int *argc, char *argv[]);

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    printf(
        "Press key '8' or '9' to switch between light sources. Press key '0' to use both lights\n");
    printf("Set the shadow mode with key '1' ... '7'\n");
    printf("Change MapSize with keys 'y' = 512, 'x' = 1024, 'c' = 2048\n");
    printf("NOTE: Real point lights only supported for ShadowMode 1...5!\n");
    // OSG init
    osgInit(argc, argv);

    // GLUT init
    int                     winid = setupGLUT(&argc, argv);
    gwin = GLUTWindow::create();

    //Erstellen der benötigten Komponenten--------------------------------------

    rootNode = makeCoredNode<Group>();
    NodePtr                 scene = makeCoredNode<Group>();

    // create lights
    /*//Directional Light 1
       TransformPtr dir1_trans;
       NodePtr dir1 = makeCoredNode<DirectionalLight>(&_dir1_core);
       NodePtr dir1_beacon = makeCoredNode<Transform>(&dir1_trans);
       beginEditCP(dir1_trans);
       dir1_trans->getMatrix().setTranslate(0.0, 0.0, 0.0);
       endEditCP(dir1_trans);
       
       beginEditCP(_dir1_core);
       _dir1_core->setDirection(0.5,0.5,0.8);
       _dir1_core->setAmbient(0.15,0.15,0.15,1);
       _dir1_core->setDiffuse(0.5,0.5,0.5,1);
       _dir1_core->setSpecular(0.0,0.0,0.0,1);
       _dir1_core->setBeacon(dir1_beacon);
       _dir1_core->setShadowIntensity(0.7);
       _dir1_core->setOn(true);
       endEditCP(_dir1_core);*/

    //Point Light 1
    TransformPtr            dir1_trans;
    NodePtr                 dir1 = makeCoredNode<PointLight>(&_dir1_core);
    NodePtr                 dir1_beacon = makeCoredNode<Transform>
        (&dir1_trans);
    beginEditCP(dir1_trans);
    dir1_trans->getMatrix().setTranslate(350.0, 300.0, 300.0);
    endEditCP(dir1_trans);

    beginEditCP(_dir1_core);
    _dir1_core->setAmbient(0.15, 0.15, 0.15, 1);
    _dir1_core->setDiffuse(0.5, 0.5, 0.5, 1);
    _dir1_core->setSpecular(0.0, 0.0, 0.0, 1);
    _dir1_core->setBeacon(dir1_beacon);
    _dir1_core->setOn(true);
    _dir1_core->setShadowIntensity(0.8);
    endEditCP(_dir1_core);

    /*//Spot Light 2
       //TransformPtr dir2_trans;
       NodePtr dir2 = makeCoredNode<SpotLight>(&_dir2_core);
       NodePtr dir2_beacon = makeCoredNode<Transform>(&dir2_trans);
       beginEditCP(dir2_trans);
       //dir2_trans->getMatrix().setTranslate(75.0, 0.0, 25.0);
       dir2_trans->getMatrix().setTranslate(250.0, -250.0, 300.0);
       endEditCP(dir2_trans);
       
       beginEditCP(_dir2_core);
       _dir2_core->setAmbient(0.15,0.15,0.15,1);
       _dir2_core->setDiffuse(0.5,0.5,0.5,1);
       _dir2_core->setSpecular(0.0,0.0,0.0,1);
       _dir2_core->setSpotCutOffDeg(40.0);
       _dir2_core->setSpotDirection(-0.85,0.85,-1.0);
       _dir2_core->setBeacon(dir2_beacon);
       _dir2_core->setOn(true);
       endEditCP(_dir2_core);*/

    //Point Light 2
    //TransformPtr dir2_trans;
    NodePtr                 dir2 = makeCoredNode<PointLight>(&_dir2_core);
    NodePtr                 dir2_beacon = makeCoredNode<Transform>
        (&dir2_trans);
    beginEditCP(dir2_trans);
    dir2_trans->getMatrix().setTranslate(40.0, 0.0, 40.0);
    endEditCP(dir2_trans);

    beginEditCP(_dir2_core);
    _dir2_core->setAmbient(0.15, 0.15, 0.15, 1);
    _dir2_core->setDiffuse(0.5, 0.5, 0.5, 1);
    _dir2_core->setSpecular(0.0, 0.0, 0.0, 1);
    _dir2_core->setBeacon(dir2_beacon);
    _dir2_core->setOn(true);
    _dir2_core->setShadowIntensity(0.7);
    endEditCP(_dir2_core);


    beginEditCP(dir1);
    dir1->addChild(dir2);
    endEditCP(dir1);

    beginEditCP(dir2);
    dir2->addChild(scene);
    endEditCP(dir2);

    //Eigene Kamera erstellen
    Pcamera = PerspectiveCamera::create();
    cam_beacon = makeCoredNode<Transform>(&cam_trans);
    beginEditCP(cam_trans);
    cam_trans->getMatrix().setTranslate(0.0, 0.0, 25.0);
    endEditCP(cam_trans);

    beginEditCP(Pcamera);
    Pcamera->setBeacon(cam_beacon);
    Pcamera->setFov(deg2rad(60));
    Pcamera->setNear(1.0);
    Pcamera->setFar(1000);
    endEditCP(Pcamera);


    // create scene

    // bottom
    NodePtr                 plane = makePlane(300.0, 300.0, 256, 256);

    ImagePtr                plane_img = Image::create();
    plane_img->read("gras.jpg");

    TextureChunkPtr         plane_tex = TextureChunk::create();
    beginEditCP(plane_tex);
    plane_tex->setImage(plane_img);
    plane_tex->setMinFilter(GL_LINEAR);
    plane_tex->setMagFilter(GL_LINEAR);
    plane_tex->setWrapS(GL_REPEAT);
    plane_tex->setWrapT(GL_REPEAT);
    plane_tex->setEnvMode(GL_MODULATE);
    endEditCP(plane_tex);

    SimpleMaterialPtr       plane_mat = SimpleMaterial::create();
    beginEditCP(plane_mat);
    plane_mat->setAmbient(Color3f(0.3, 0.3, 0.3));
    plane_mat->setDiffuse(Color3f(1.0, 1.0, 1.0));
    plane_mat->addChunk(plane_tex);
    endEditCP(plane_mat);

    GeometryPtr             plane_geo = GeometryPtr::dcast(plane->getCore());
    beginEditCP(plane_geo);
    plane_geo->setMaterial(plane_mat);
    beginEditCP(plane_geo);

    //load Tree Objects

    NodePtr                 tree1_trans_node = makeCoredNode<Transform>
        (&_tree1_trans);
    NodePtr                 tree2_trans_node = makeCoredNode<Transform>
        (&_tree2_trans);
    NodePtr                 tree3_trans_node = makeCoredNode<Transform>
        (&_tree3_trans);
    NodePtr                 tree4_trans_node = makeCoredNode<Transform>
        (&_tree4_trans);
    NodePtr                 tree5_trans_node = makeCoredNode<Transform>
        (&_tree5_trans);
    NodePtr                 tree6_trans_node = makeCoredNode<Transform>
        (&_tree6_trans);
    NodePtr                 tree7_trans_node = makeCoredNode<Transform>
        (&_tree7_trans);
    NodePtr                 tree8_trans_node = makeCoredNode<Transform>
        (&_tree8_trans);
    NodePtr                 tree9_trans_node = makeCoredNode<Transform>
        (&_tree9_trans);

    beginEditCP(_tree1_trans);
    _tree1_trans->getMatrix().setTranslate(-80.0, -80.0, 0.0);
    _tree1_trans->getMatrix().setScale(Vec3f(12.0, 12.0, 10.0));
    endEditCP(_tree1_trans);

    beginEditCP(_tree2_trans);
    _tree2_trans->getMatrix().setTranslate(0.0, -80.0, 0.0);
    _tree2_trans->getMatrix().setScale(Vec3f(12.0, 12.0, 10.0));
    endEditCP(_tree2_trans);

    beginEditCP(_tree3_trans);
    _tree3_trans->getMatrix().setTranslate(80.0, -80.0, 0.0);
    _tree3_trans->getMatrix().setScale(Vec3f(12.0, 12.0, 10.0));
    endEditCP(_tree3_trans);

    beginEditCP(_tree4_trans);
    _tree4_trans->getMatrix().setTranslate(-80.0, 0.0, 0.0);
    _tree4_trans->getMatrix().setScale(Vec3f(12.0, 12.0, 10.0));
    endEditCP(_tree4_trans);

    beginEditCP(_tree5_trans);
    _tree5_trans->getMatrix().setTranslate(0.0, 0.0, 0.0);
    _tree5_trans->getMatrix().setScale(Vec3f(12.0, 12.0, 10.0));
    endEditCP(_tree5_trans);

    beginEditCP(_tree6_trans);
    _tree6_trans->getMatrix().setTranslate(80.0, 0.0, 0.0);
    _tree6_trans->getMatrix().setScale(Vec3f(12.0, 12.0, 10.0));
    endEditCP(_tree6_trans);

    beginEditCP(_tree7_trans);
    _tree7_trans->getMatrix().setTranslate(-80.0, 80.0, 0.0);
    _tree7_trans->getMatrix().setScale(Vec3f(12.0, 12.0, 10.0));
    endEditCP(_tree7_trans);

    beginEditCP(_tree8_trans);
    _tree8_trans->getMatrix().setTranslate(0.0, 80.0, 0.0);
    _tree8_trans->getMatrix().setScale(Vec3f(12.0, 12.0, 10.0));
    endEditCP(_tree8_trans);

    beginEditCP(_tree9_trans);
    _tree9_trans->getMatrix().setTranslate(80.0, 80.0, 0.0);
    _tree9_trans->getMatrix().setScale(Vec3f(12.0, 12.0, 10.0));
    endEditCP(_tree9_trans);

    NodePtr                 tree1 = SceneFileHandler::the().read("tree1.3ds");

    beginEditCP(tree1_trans_node);
    tree1_trans_node->addChild(tree1);
    endEditCP(tree1_trans_node);

    beginEditCP(tree2_trans_node);
    tree2_trans_node->addChild(cloneTree(tree1));
    endEditCP(tree2_trans_node);


    beginEditCP(tree3_trans_node);
    tree3_trans_node->addChild(cloneTree(tree1));
    endEditCP(tree3_trans_node);

    beginEditCP(tree4_trans_node);
    tree4_trans_node->addChild(cloneTree(tree1));
    endEditCP(tree4_trans_node);

    beginEditCP(tree5_trans_node);
    tree5_trans_node->addChild(cloneTree(tree1));
    endEditCP(tree5_trans_node);

    beginEditCP(tree6_trans_node);
    tree6_trans_node->addChild(cloneTree(tree1));
    endEditCP(tree6_trans_node);

    beginEditCP(tree7_trans_node);
    tree7_trans_node->addChild(cloneTree(tree1));
    endEditCP(tree7_trans_node);

    beginEditCP(tree8_trans_node);
    tree8_trans_node->addChild(cloneTree(tree1));
    endEditCP(tree8_trans_node);

    beginEditCP(tree9_trans_node);
    tree9_trans_node->addChild(cloneTree(tree1));
    endEditCP(tree9_trans_node);

    NodePtr                 trees = makeCoredNode<Group>();

    beginEditCP(trees);
    trees->addChild(tree1_trans_node);
    trees->addChild(tree2_trans_node);
    trees->addChild(tree3_trans_node);
    trees->addChild(tree4_trans_node);
    trees->addChild(tree5_trans_node);
    trees->addChild(tree6_trans_node);
    trees->addChild(tree7_trans_node);
    trees->addChild(tree8_trans_node);
    trees->addChild(tree9_trans_node);
    endEditCP(trees);

    /*//load Airplane Object
       NodePtr obj1_trans_node = makeCoredNode<Transform>(&_obj1_trans);
       
       beginEditCP(_obj1_trans);
       _obj1_trans->getMatrix().setTranslate(0.0, 0.0, 10.0);
       _obj1_trans->getMatrix().setScale(Vec3f(0.15,0.15,0.15));
       endEditCP(_obj1_trans);
       
       NodePtr object1 = SceneFileHandler::the().read("triplane.3ds");
       
       beginEditCP(obj1_trans_node);
       obj1_trans_node->addChild(object1);
       endEditCP(obj1_trans_node);*/

    //Load a Quad as Pointlight
    GeometryPtr             boxGeo = makeBoxGeo(15, 15, 15, 1, 1, 1);
    NodePtr                 boxNode = Node::create();
    beginEditCP(boxNode, Node::CoreFieldMask);
    boxNode->setCore(boxGeo);
    endEditCP(boxNode, Node::CoreFieldMask);

    SimpleMaterialPtr       box_mat = SimpleMaterial::create();
    beginEditCP(box_mat);
    box_mat->setAmbient(Color3f(0.95, 1.0, 0.2));
    box_mat->setDiffuse(Color3f(0.95, 1.0, 0.2));
    endEditCP(box_mat);

    beginEditCP(boxGeo);
    boxGeo->setMaterial(box_mat);
    beginEditCP(boxGeo);

    NodePtr                 obj1_trans_node = makeCoredNode<Transform>
        (&_obj1_trans);

    beginEditCP(obj1_trans_node);
    obj1_trans_node->addChild(boxNode);
    endEditCP(obj1_trans_node);

    //load Dino Objects

    NodePtr                 dino1_trans_node = makeCoredNode<Transform>
        (&_dino1_trans);
    NodePtr                 dino2_trans_node = makeCoredNode<Transform>
        (&_dino2_trans);
    NodePtr                 dino3_trans_node = makeCoredNode<Transform>
        (&_dino3_trans);
    NodePtr                 dino4_trans_node = makeCoredNode<Transform>
        (&_dino4_trans);

    beginEditCP(_dino1_trans);
    _dino1_trans->getMatrix().setTranslate(-20.0, -20.0, 10.0);
    _dino1_trans->getMatrix().setScale(Vec3f(5.0, 5.0, 5.0));
    endEditCP(_dino1_trans);

    beginEditCP(_dino2_trans);
    _dino2_trans->getMatrix().setTranslate(-20.0, -20.0, 6.0);
    _dino2_trans->getMatrix().setScale(Vec3f(3.0, 3.0, 3.0));
    endEditCP(_dino2_trans);

    beginEditCP(_dino3_trans);
    _dino3_trans->getMatrix().setTranslate(-20.0, -20.0, 6.0);
    _dino3_trans->getMatrix().setScale(Vec3f(3.0, 3.0, 3.0));
    endEditCP(_dino3_trans);

    beginEditCP(_dino4_trans);
    _dino4_trans->getMatrix().setTranslate(-20.0, -20.0, 6.0);
    _dino4_trans->getMatrix().setScale(Vec3f(3.0, 3.0, 3.0));
    endEditCP(_dino4_trans);

    NodePtr                 dino1 = SceneFileHandler::the().read(
        "dinopet.3ds");

    beginEditCP(dino1_trans_node);
    dino1_trans_node->addChild(dino1);
    endEditCP(dino1_trans_node);

    beginEditCP(dino2_trans_node);
    dino2_trans_node->addChild(cloneTree(dino1));
    endEditCP(dino2_trans_node);

    beginEditCP(dino3_trans_node);
    dino3_trans_node->addChild(cloneTree(dino1));
    endEditCP(dino3_trans_node);

    beginEditCP(dino4_trans_node);
    dino4_trans_node->addChild(cloneTree(dino1));
    endEditCP(dino4_trans_node);

    NodePtr                 dinos = makeCoredNode<Group>();

    beginEditCP(dinos);
    dinos->addChild(dino1_trans_node);
    dinos->addChild(dino2_trans_node);
    dinos->addChild(dino3_trans_node);
    dinos->addChild(dino4_trans_node);
    endEditCP(dinos);

    //load Stone Objects

    TransformPtr            _stone_trans1, _stone_trans2, _stone_trans3,
                            _stone_trans4, _stone_trans5, _stone_trans6,
                            _stone_trans7, _stone_trans8,
                            _stone_trans9;
    NodePtr                 stone_trans_node1 = makeCoredNode<Transform>
        (&_stone_trans1);
    NodePtr                 stone_trans_node2 = makeCoredNode<Transform>
        (&_stone_trans2);
    NodePtr                 stone_trans_node3 = makeCoredNode<Transform>
        (&_stone_trans3);
    NodePtr                 stone_trans_node4 = makeCoredNode<Transform>
        (&_stone_trans4);
    NodePtr                 stone_trans_node5 = makeCoredNode<Transform>
        (&_stone_trans5);
    NodePtr                 stone_trans_node6 = makeCoredNode<Transform>
        (&_stone_trans6);
    NodePtr                 stone_trans_node7 = makeCoredNode<Transform>
        (&_stone_trans7);
    NodePtr                 stone_trans_node8 = makeCoredNode<Transform>
        (&_stone_trans8);
    NodePtr                 stone_trans_node9 = makeCoredNode<Transform>
        (&_stone_trans9);

    beginEditCP(_stone_trans1);
    _stone_trans1->getMatrix().setTranslate(-70, -70, 0);
    endEditCP(_stone_trans1);

    beginEditCP(_stone_trans2);
    _stone_trans2->getMatrix().setTranslate(10, -70, 0);
    endEditCP(_stone_trans2);

    beginEditCP(_stone_trans3);
    _stone_trans3->getMatrix().setTranslate(90, -70, 0);
    endEditCP(_stone_trans3);

    beginEditCP(_stone_trans4);
    _stone_trans4->getMatrix().setTranslate(-70, 10, 0);
    endEditCP(_stone_trans4);

    beginEditCP(_stone_trans5);
    _stone_trans5->getMatrix().setTranslate(10, 10, 0);
    endEditCP(_stone_trans5);

    beginEditCP(_stone_trans6);
    _stone_trans6->getMatrix().setTranslate(90, 10, 0);
    endEditCP(_stone_trans6);

    beginEditCP(_stone_trans7);
    _stone_trans7->getMatrix().setTranslate(-70, 90, 0);
    endEditCP(_stone_trans7);

    beginEditCP(_stone_trans8);
    _stone_trans8->getMatrix().setTranslate(10, 90, 0);
    endEditCP(_stone_trans8);

    beginEditCP(_stone_trans9);
    _stone_trans9->getMatrix().setTranslate(90, 90, 0);
    endEditCP(_stone_trans9);

    NodePtr                 stone1 = makeSphere(1.0, 7.0);
    NodePtr                 stone2 = makeSphere(1.0, 7.0);
    NodePtr                 stone3 = makeSphere(1.0, 7.0);
    NodePtr                 stone4 = makeSphere(1.0, 7.0);
    NodePtr                 stone5 = makeSphere(1.0, 7.0);
    NodePtr                 stone6 = makeSphere(1.0, 7.0);
    NodePtr                 stone7 = makeSphere(1.0, 7.0);
    NodePtr                 stone8 = makeSphere(1.0, 7.0);
    NodePtr                 stone9 = makeSphere(1.0, 7.0);

    ImagePtr                plane_img2 = Image::create();
    plane_img2->read("stone.jpg");

    TextureChunkPtr         plane_tex2 = TextureChunk::create();
    beginEditCP(plane_tex2);
    plane_tex2->setImage(plane_img2);
    plane_tex2->setMinFilter(GL_LINEAR);
    plane_tex2->setMagFilter(GL_LINEAR);
    plane_tex2->setWrapS(GL_REPEAT);
    plane_tex2->setWrapT(GL_REPEAT);
    plane_tex2->setEnvMode(GL_MODULATE);
    endEditCP(plane_tex2);

    SimpleMaterialPtr       plane_mat2 = SimpleMaterial::create();
    beginEditCP(plane_mat2);
    plane_mat2->setAmbient(Color3f(0.3, 0.3, 0.3));
    plane_mat2->setDiffuse(Color3f(1.0, 1.0, 1.0));
    plane_mat2->addChunk(plane_tex2);
    endEditCP(plane_mat2);

    GeometryPtr             plane_geo3 = GeometryPtr::dcast(stone1->getCore());
    beginEditCP(plane_geo3);
    plane_geo3->setMaterial(plane_mat2);
    beginEditCP(plane_geo3);

    plane_geo3 = GeometryPtr::dcast(stone2->getCore());
    beginEditCP(plane_geo3);
    plane_geo3->setMaterial(plane_mat2);
    beginEditCP(plane_geo3);

    plane_geo3 = GeometryPtr::dcast(stone3->getCore());
    beginEditCP(plane_geo3);
    plane_geo3->setMaterial(plane_mat2);
    beginEditCP(plane_geo3);

    plane_geo3 = GeometryPtr::dcast(stone4->getCore());
    beginEditCP(plane_geo3);
    plane_geo3->setMaterial(plane_mat2);
    beginEditCP(plane_geo3);

    plane_geo3 = GeometryPtr::dcast(stone5->getCore());
    beginEditCP(plane_geo3);
    plane_geo3->setMaterial(plane_mat2);
    beginEditCP(plane_geo3);

    plane_geo3 = GeometryPtr::dcast(stone6->getCore());
    beginEditCP(plane_geo3);
    plane_geo3->setMaterial(plane_mat2);
    beginEditCP(plane_geo3);

    plane_geo3 = GeometryPtr::dcast(stone7->getCore());
    beginEditCP(plane_geo3);
    plane_geo3->setMaterial(plane_mat2);
    beginEditCP(plane_geo3);

    plane_geo3 = GeometryPtr::dcast(stone8->getCore());
    beginEditCP(plane_geo3);
    plane_geo3->setMaterial(plane_mat2);
    beginEditCP(plane_geo3);

    plane_geo3 = GeometryPtr::dcast(stone9->getCore());
    beginEditCP(plane_geo3);
    plane_geo3->setMaterial(plane_mat2);
    beginEditCP(plane_geo3);


    beginEditCP(stone_trans_node1);
    stone_trans_node1->addChild(stone1);
    endEditCP(stone_trans_node1);

    beginEditCP(stone_trans_node2);
    stone_trans_node2->addChild(stone2);
    endEditCP(stone_trans_node2);

    beginEditCP(stone_trans_node3);
    stone_trans_node3->addChild(stone3);
    endEditCP(stone_trans_node3);

    beginEditCP(stone_trans_node4);
    stone_trans_node4->addChild(stone4);
    endEditCP(stone_trans_node4);

    beginEditCP(stone_trans_node5);
    stone_trans_node5->addChild(stone5);
    endEditCP(stone_trans_node5);

    beginEditCP(stone_trans_node6);
    stone_trans_node6->addChild(stone6);
    endEditCP(stone_trans_node6);

    beginEditCP(stone_trans_node7);
    stone_trans_node7->addChild(stone7);
    endEditCP(stone_trans_node7);

    beginEditCP(stone_trans_node8);
    stone_trans_node8->addChild(stone8);
    endEditCP(stone_trans_node8);

    beginEditCP(stone_trans_node9);
    stone_trans_node9->addChild(stone9);
    endEditCP(stone_trans_node9);

    NodePtr                 stones = makeCoredNode<Group>();

    beginEditCP(stones);
    stones->addChild(stone_trans_node1);
    stones->addChild(stone_trans_node2);
    stones->addChild(stone_trans_node3);
    stones->addChild(stone_trans_node4);
    stones->addChild(stone_trans_node5);
    stones->addChild(stone_trans_node6);
    stones->addChild(stone_trans_node7);
    stones->addChild(stone_trans_node8);
    stones->addChild(stone_trans_node9);
    endEditCP(stones);


    beginEditCP(scene);
    scene->addChild(plane);
    scene->addChild(obj1_trans_node);
    scene->addChild(trees);
    scene->addChild(stones);
    scene->addChild(dinos);
    endEditCP(scene);

    svp = ShadowViewport::create();
    GradientBackgroundPtr   gbg = GradientBackground::create();
    SolidBackgroundPtr      sbg = SolidBackground::create();

    beginEditCP(gbg);
    gbg->addLine(Color3f(0.7, 0.7, 0.8), 0);
    gbg->addLine(Color3f(0.0, 0.1, 0.3), 1);
    endEditCP(gbg);

    beginEditCP(rootNode);
    rootNode->addChild(dir1);
    rootNode->addChild(dir1_beacon);
    rootNode->addChild(dir2_beacon);
    rootNode->addChild(cam_beacon);
    endEditCP(rootNode);


    // Shadow viewport
    beginEditCP(svp);
    svp->setBackground(gbg);
    svp->setRoot(rootNode);
    svp->setSize(0, 0, 1, 1);
    //svp->setOffFactor(4.0);
    //svp->setOffBias(8.0);
    //used to set global shadow intensity, ignores shadow intensity from light sources if != 0.0
    //svp->setGlobalShadowIntensity(0.8);
    svp->setMapSize(1024);
    //ShadowSmoothness used for PCF_SHADOW_MAP and VARIANCE_SHADOW_MAP, defines Filter Width. Range can be 0.0 ... 1.0.
    //ShadowSmoothness also used to define the light size for PCSS_SHADOW_MAP
    svp->setShadowSmoothness(0.5);
    // add light sources here
    svp->getLightNodes().push_back(dir1);
    svp->getLightNodes().push_back(dir2);
    svp->getExcludeNodes().push_back(obj1_trans_node);
    //svp->setAutoSearchForLights(true);
    endEditCP(svp);

    //one active light at startup
    beginEditCP(_dir2_core);
    _dir2_core->setOn(true);
    _dir2_core->setAmbient(0.3, 0.3, 0.3, 1);
    _dir2_core->setDiffuse(0.8, 0.8, 0.8, 1);
    endEditCP(_dir2_core);
    beginEditCP(_dir1_core);
    _dir1_core->setOn(false);
    //_dir1_core->setAmbient(0.3,0.3,0.3,1);
    //_dir1_core->setDiffuse(0.8,0.8,0.8,1);
    endEditCP(_dir1_core);

    beginEditCP(gwin);//Window
    gwin->setId(winid);
    gwin->addPort(svp);
    gwin->init();
    endEditCP(gwin);

    Vec3f                   min, max;
    rootNode->updateVolume();
    rootNode->getVolume().getBounds(min, max);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    mgr->setWindow(gwin);
    mgr->setRoot(rootNode);

    _navigator.setMode(Navigator::TRACKBALL);

    _navigator.setViewport(svp);
    _navigator.setCameraTransformation(cam_beacon);


    Vec3f                   up(0,1,0);
    Pnt3f                   at(0,0,0);
    Pnt3f                   from(0.0,-100.1,20.0);

    _navigator.set(from, at, up);

    _navigator.setMotionFactor(0.5f);


    beginEditCP(svp);//Viewport
    svp->setCamera(Pcamera);
    endEditCP(svp);

    //activate Framecounter
    startFpsCounter();

    ((RenderAction *)mgr->getAction())->setLocalLights(true);
    mgr->turnHeadlightOff();

    mgr->showAll();

    // GLUT main loop
    glutMainLoop();

    return 0;
}

void Animate()
{
    //Show FPS
    showFpsCounter();

    static Real64   t0 = OSG::getSystemTime();

    Real64          t = OSG::getSystemTime() - t0;

    Real32          rot0 = t * 0.25;
    if(rot0 > 360.0)
        rot0 -= 360.0;

    Real32          rota = t * 0.5;
    if(rota > 360.0)
        rota -= 360.0;

    Real32          rotb = t * 1.0;
    if(rotb > 360.0)
        rotb -= 360.0;

    Real32          rotc = t * 1.5;
    if(rotc > 360.0)
        rotc -= 360.0;

    Real32          rotd = t * 2.0;
    if(rotd > 360.0)
        rotd -= 360.0;

    //beginEditCP(dir2_trans);
    //    dir2_trans->getMatrix().setTranslate(-100.0*sin(rota),-100.0*cos(rota), 250.0);
    //endEditCP(dir2_trans);

    //animate Trees
    Quaternion      q;

    beginEditCP(_tree1_trans);
    q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rota));
    _tree1_trans->getMatrix().setRotate(q);
    _tree1_trans->getMatrix().setScale(Vec3f(12.0, 12.0, 10.0));
    endEditCP(_tree1_trans);

    q.setIdentity();

    beginEditCP(_tree2_trans);
    q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotc));
    _tree2_trans->getMatrix().setRotate(q);
    _tree2_trans->getMatrix().setScale(Vec3f(12.0, 12.0, 10.0));
    endEditCP(_tree2_trans);

    q.setIdentity();

    beginEditCP(_tree3_trans);
    q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotb));
    _tree3_trans->getMatrix().setRotate(q);
    _tree3_trans->getMatrix().setScale(Vec3f(12.0, 12.0, 10.0));
    endEditCP(_tree3_trans);

    q.setIdentity();

    beginEditCP(_tree4_trans);
    q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotb));
    _tree4_trans->getMatrix().setRotate(q);
    _tree4_trans->getMatrix().setScale(Vec3f(12.0, 12.0, 10.0));
    endEditCP(_tree4_trans);

    q.setIdentity();

    beginEditCP(_tree5_trans);
    q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotc));
    _tree5_trans->getMatrix().setRotate(q);
    _tree5_trans->getMatrix().setScale(Vec3f(12.0, 12.0, 10.0));
    endEditCP(_tree5_trans);

    q.setIdentity();

    beginEditCP(_tree6_trans);
    q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotb));
    _tree6_trans->getMatrix().setRotate(q);
    _tree6_trans->getMatrix().setScale(Vec3f(12.0, 12.0, 10.0));
    endEditCP(_tree6_trans);

    q.setIdentity();

    beginEditCP(_tree7_trans);
    q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotd));
    _tree7_trans->getMatrix().setRotate(q);
    _tree7_trans->getMatrix().setScale(Vec3f(12.0, 12.0, 10.0));
    endEditCP(_tree7_trans);

    q.setIdentity();

    beginEditCP(_tree8_trans);
    q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotb));
    _tree8_trans->getMatrix().setRotate(q);
    _tree8_trans->getMatrix().setScale(Vec3f(12.0, 12.0, 10.0));
    endEditCP(_tree8_trans);

    q.setIdentity();

    beginEditCP(_tree9_trans);
    q.setValueAsAxisRad(1, 1, 1, 0.5 * sin(rotc));
    _tree9_trans->getMatrix().setRotate(q);
    _tree9_trans->getMatrix().setScale(Vec3f(12.0, 12.0, 10.0));
    endEditCP(_tree9_trans);

    q.setIdentity();

    beginEditCP(_obj1_trans);
    {
        Matrix  m;
        m.setIdentity();
        Vec3f   scale(0.15,0.15,0.15);
        Vec3f   trans(-40.0 * sin(rotb),-40.0 * cos(rotb),
                      50.0 + 25.0 * sin(rotd));
        q.setValueAsAxisRad(0, 0, 1, -rotb);
        m.setTransform(trans, q, scale);
        _obj1_trans->setMatrix(m);
    }
    endEditCP(_obj1_trans);


    beginEditCP(dir2_trans);
    {
        dir2_trans->getMatrix().setTranslate(-40.0 * sin(rotb), -40.0 *
                                             cos(rotb),
                                             50.0 + 25.0 * sin(rotd));
    }
    endEditCP(dir2_trans);

    //animate Dinos

    beginEditCP(_dino1_trans);
    {
        Matrix  m;
        m.setIdentity();
        Vec3f   scale(5.0,5.0,5.0);
        Real32  ztrans1 = sin(2.0 * rotd);
        if(ztrans1 < 0)
            ztrans1 *= -1.0;
        Vec3f   trans(-96.0 * cos(rot0),-96.0 * sin(rot0),
                      10.0 + 8.0 * ztrans1);
        m.setScale(Vec3f(5.0, 5.0, 5.0));
        q.setValueAsAxisRad(0, 0, 1, rot0 - 170);
        m.setTransform(trans, q, scale);
        _dino1_trans->setMatrix(m);
    }
    endEditCP(_dino1_trans);

    beginEditCP(_dino2_trans);
    {
        Matrix  m;
        m.setIdentity();
        Vec3f   scale(3.0,3.0,3.0);
        Real32  ztrans1 = sin(2.5 * rotd);
        if(ztrans1 < 0)
            ztrans1 *= -1.0;
        Vec3f   trans(-96.0 * cos((rot0 - 0.5)),-96.0 * sin((rot0 - 0.5)),
                      6.0 + 8.0 * ztrans1);
        m.setScale(Vec3f(5.0, 5.0, 5.0));
        q.setValueAsAxisRad(0, 0, 1, rot0 - 169.9);
        m.setTransform(trans, q, scale);
        _dino2_trans->setMatrix(m);
    }
    endEditCP(_dino2_trans);

    beginEditCP(_dino3_trans);
    {
        Matrix  m;
        m.setIdentity();
        Vec3f   scale(3.0,3.0,3.0);
        Real32  ztrans1 = sin(3.0 * rotd);
        if(ztrans1 < 0)
            ztrans1 *= -1.0;
        Vec3f   trans(-96.0 * cos((rot0 - 0.8)),-96.0 * sin((rot0 - 0.8)),
                      6.0 + 8.0 * ztrans1);
        m.setScale(Vec3f(5.0, 5.0, 5.0));
        q.setValueAsAxisRad(0, 0, 1, rot0 - 170.1);
        m.setTransform(trans, q, scale);
        _dino3_trans->setMatrix(m);
    }
    endEditCP(_dino3_trans);

    beginEditCP(_dino4_trans);
    {
        Matrix  m;
        m.setIdentity();
        Vec3f   scale(3.0,3.0,3.0);
        Real32  ztrans1 = sin(2.75 * rotd);
        if(ztrans1 < 0)
            ztrans1 *= -1.0;
        Vec3f   trans(-96.0 * cos((rot0 - 1.2)),-96.0 * sin((rot0 - 1.2)),
                      6.0 + 8.0 * ztrans1);
        m.setScale(Vec3f(5.0, 5.0, 5.0));
        q.setValueAsAxisRad(0, 0, 1, rot0 - 170.1);
        m.setTransform(trans, q, scale);
        _dino4_trans->setMatrix(m);
    }
    endEditCP(_dino4_trans);

    _navigator.idle(_mousebuttons, _lastx, _lasty);
    mgr->redraw();
}

// redraw the window
void display(void)
{
    _navigator.updateCameraTransformation();
    mgr->redraw();
}

// react to size changes
void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
    if(state)
    {
        mgr->mouseButtonRelease(button, x, y);
        switch(button)
        {
            case 0:
                _navigator.buttonRelease(Navigator::LEFT_MOUSE, x, y);
                break;
            case 1:
                _navigator.buttonRelease(Navigator::MIDDLE_MOUSE, x, y);
                break;
            case 2:
                _navigator.buttonRelease(Navigator::RIGHT_MOUSE, x, y);
                break;
            case 3:
                _navigator.buttonRelease(Navigator::UP_MOUSE, x, y);
                break;
            case 4:
                _navigator.buttonRelease(Navigator::DOWN_MOUSE, x, y);
                break;
        }
        _mousebuttons &= ~(1 << button);
        _lastx = x;
        _lasty = y;
    }

    else
    {
        mgr->mouseButtonPress(button, x, y);
        switch(button)
        {
            case 0:
                _navigator.buttonPress(Navigator::LEFT_MOUSE, x, y);
                break;
            case 1:
                _navigator.buttonPress(Navigator::MIDDLE_MOUSE, x, y);
                break;
            case 2:
                _navigator.buttonPress(Navigator::RIGHT_MOUSE, x, y);
                break;
            case 3:
                _navigator.buttonPress(Navigator::UP_MOUSE, x, y);
                break;
            case 4:
                _navigator.buttonPress(Navigator::DOWN_MOUSE, x, y);
                break;
        }
        _mousebuttons |= 1 << button;
        _lastx = x;
        _lasty = y;
    }

    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    mgr->mouseMove(x, y);

    if(_mousebuttons)
        _navigator.moveTo(x, y);
    _lastx = x;
    _lasty = y;

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

        case '9':
            {
                beginEditCP(_dir1_core);
                _dir1_core->setOn(true);
                _dir1_core->setAmbient(0.3, 0.3, 0.3, 1);
                _dir1_core->setDiffuse(0.8, 0.8, 0.8, 1);
                endEditCP(_dir1_core);

                beginEditCP(_dir2_core);
                _dir2_core->setOn(false);
                endEditCP(_dir2_core);
                break;
            }

        case '8':
            {
                beginEditCP(_dir1_core);
                _dir1_core->setOn(false);
                endEditCP(_dir1_core);

                beginEditCP(_dir2_core);
                _dir2_core->setAmbient(0.3, 0.3, 0.3, 1);
                _dir2_core->setDiffuse(0.8, 0.8, 0.8, 1);
                _dir2_core->setOn(true);
                endEditCP(_dir2_core);
                break;
            }

        case '0':
            {
                beginEditCP(_dir1_core);
                _dir1_core->setAmbient(0.15, 0.15, 0.15, 1);
                _dir1_core->setDiffuse(0.4, 0.4, 0.4, 1);
                _dir1_core->setOn(true);
                endEditCP(_dir1_core);

                beginEditCP(_dir2_core);
                _dir2_core->setAmbient(0.15, 0.15, 0.15, 1);
                _dir2_core->setDiffuse(0.4, 0.4, 0.4, 1);
                _dir2_core->setOn(true);
                endEditCP(_dir2_core);
                break;
            }

        case 'w':
            {
                Real32  t = svp->getOffBias();

                beginEditCP(svp, ShadowViewport::OffBiasFieldMask);
                svp->setOffBias((t + 0.2));
                endEditCP(svp, ShadowViewport::OffBiasFieldMask);
                SLOG << "Polygon-OffsetBias is: " << (t + 0.2) << endLog;
                break;
            }

        case 's':
            {
                Real32  t = svp->getOffBias();

                beginEditCP(svp, ShadowViewport::OffBiasFieldMask);
                svp->setOffBias((t - 0.2));
                endEditCP(svp, ShadowViewport::OffBiasFieldMask);
                SLOG << "Polygon-OffsetBias is: " << (t - 0.2) << endLog;
                break;
            }

        case 'e':
            {
                Real32  t = svp->getOffFactor();

                beginEditCP(svp, ShadowViewport::OffFactorFieldMask);
                svp->setOffFactor(++t);
                endEditCP(svp, ShadowViewport::OffFactorFieldMask);
                SLOG << "Polygon-OffsetFactor is: " << ++t << endLog;
                break;
            }

        case 'd':
            {
                Real32  t = svp->getOffFactor();

                beginEditCP(svp, ShadowViewport::OffFactorFieldMask);
                svp->setOffFactor(--t);
                endEditCP(svp, ShadowViewport::OffFactorFieldMask);
                SLOG << "Polygon-OffsetFactor is: " << --t << endLog;
                break;
            }
        case 'o':
            {
                bool    s = svp->getShadowOn();
                beginEditCP(svp, ShadowViewport::OffFactorFieldMask);
                svp->setShadowOn(!s);
                endEditCP(svp, ShadowViewport::OffFactorFieldMask);
                break;
            }
            /*case 'x':
               {
               SceneFileHandler::the().write(rootNode, "shadow.osb.gz", true);
               break;
               }*/

        case '1':
            {
                beginEditCP(svp, ShadowViewport::ShadowModeFieldMask);
                svp->setShadowMode(ShadowViewport::NO_SHADOW);
                endEditCP(svp, ShadowViewport::ShadowModeFieldMask);
                SLOG << "ShadowMode is: NO_SHADOW" << endLog;
                break;
            }

        case '2':
            {
                beginEditCP(svp, ShadowViewport::ShadowModeFieldMask);
                svp->setShadowMode(ShadowViewport::STD_SHADOW_MAP);
                endEditCP(svp, ShadowViewport::ShadowModeFieldMask);
                SLOG << "ShadowMode is: STD_SHADOW_MAP" << endLog;
                break;
            }

        case '3':
            {
                beginEditCP(svp, ShadowViewport::ShadowModeFieldMask);
                svp->setShadowMode(ShadowViewport::PERSPECTIVE_SHADOW_MAP);
                endEditCP(svp, ShadowViewport::ShadowModeFieldMask);
                SLOG << "ShadowMode is: PERSPECTIVE_SHADOW_MAP" << endLog;
                break;
            }

        case '4':
            {
                beginEditCP(svp, ShadowViewport::ShadowModeFieldMask);
                svp->setShadowMode(ShadowViewport::DITHER_SHADOW_MAP);
                endEditCP(svp, ShadowViewport::ShadowModeFieldMask);
                SLOG << "ShadowMode is: DITHER_SHADOW_MAP" << endLog;
                break;
            }

        case '5':
            {
                beginEditCP(svp, ShadowViewport::ShadowModeFieldMask);
                svp->setShadowMode(ShadowViewport::PCF_SHADOW_MAP);
                svp->setShadowSmoothness(0.5);
                endEditCP(svp, ShadowViewport::ShadowModeFieldMask);
                SLOG << "ShadowMode is: PCF_SHADOW_MAP" << endLog;
                break;
            }

        case '6':
            {
                beginEditCP(svp, ShadowViewport::ShadowModeFieldMask);
                svp->setShadowMode(ShadowViewport::PCSS_SHADOW_MAP);
                svp->setShadowSmoothness(1.0);
                endEditCP(svp, ShadowViewport::ShadowModeFieldMask);
                SLOG << "ShadowMode is: PCSS_SHADOW_MAP" << endLog;
                break;
            }

        case '7':
            {
                beginEditCP(svp, ShadowViewport::ShadowModeFieldMask);
                svp->setShadowMode(ShadowViewport::VARIANCE_SHADOW_MAP);
                svp->setShadowSmoothness(0.5);
                endEditCP(svp, ShadowViewport::ShadowModeFieldMask);
                SLOG << "ShadowMode is: VARIANCE_SHADOW_MAP" << endLog;
                break;
            }

        case 'y':
            {
                beginEditCP(svp, ShadowViewport::MapSizeFieldMask);
                svp->setMapSize(512);
                endEditCP(svp, ShadowViewport::MapSizeFieldMask);
                break;
            }

        case 'x':
            {
                beginEditCP(svp, ShadowViewport::MapSizeFieldMask);
                svp->setMapSize(1024);
                endEditCP(svp, ShadowViewport::MapSizeFieldMask);
                SLOG << "ShadowMode is: NO_SHADOW" << endLog;
                break;
            }

        case 'c':
            {
                beginEditCP(svp, ShadowViewport::MapSizeFieldMask);
                svp->setMapSize(2048);
                endEditCP(svp, ShadowViewport::MapSizeFieldMask);
                SLOG << "ShadowMode is: NO_SHADOW" << endLog;
                break;
            }

        case '+':
            {
                Real32  t = svp->getShadowSmoothness();

                beginEditCP(svp, ShadowViewport::ShadowSmoothnessFieldMask);
                svp->setShadowSmoothness(t + 0.1);
                endEditCP(svp, ShadowViewport::ShadowSmoothnessFieldMask);
                //SLOG << "ShadowSmoothness is: " << t << endLog;
                break;
            }

        case '-':
            {
                Real32  t = svp->getShadowSmoothness();

                beginEditCP(svp, ShadowViewport::ShadowSmoothnessFieldMask);
                svp->setShadowSmoothness(t - 0.1);
                endEditCP(svp, ShadowViewport::ShadowSmoothnessFieldMask);
                //SLOG << "ShadowSmoothness is: " << t << endLog;
                break;
            }
    }
    glutPostRedisplay();
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    //Set WindowSize here
    glutInitWindowSize(640, 512);

    int winid = glutCreateWindow("Shadow-Scene");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(Animate);

    return winid;
}
