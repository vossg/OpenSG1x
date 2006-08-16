#include <stdlib.h>

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
#include <OSGQuaternion.h>
#include <OSGVector.h>

#include <OSGSimpleSceneManager.h>

#include <OSGSceneFileHandler.h>

#include <OSGShadowViewport.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

GLUTWindowPtr gwin;
ShadowViewportPtr svp;

NodePtr rootNode;
NodePtr point1;
NodePtr point2;
NodePtr point3;
NodePtr point4;
NodePtr point5;
NodePtr point6;
NodePtr point7;
SpotLightPtr spot1_core;
SpotLightPtr spot2_core;
SpotLightPtr spot3_core;
SpotLightPtr spot4_core;
SpotLightPtr spot5_core;
SpotLightPtr spot6_core;
SpotLightPtr spot7_core;
DirectionalLightPtr raumlicht_core;
//PointLightPtr _point1_core;
DirectionalLightPtr _point1_core;
PointLightPtr _point2_core;
PointLightPtr _point3_core;
PointLightPtr _point4_core;
PointLightPtr _point5_core;
PointLightPtr _point6_core;
PointLightPtr _point7_core;
TransformPtr _box_trans;
TransformPtr _cylinder1_trans;
TransformPtr _cylinder2_trans;

bool animateScene;
bool useStandardScene;

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
        printf("aktuelle FPS: %i                              \r", frameCount);
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
        "Load a scene with first param, else a standard scene will be used.\n"
        );
    printf(
        "Press key 'u', 'i', 'o' ,'p', 'j', 'k', 'l' to switch between 1...7 light sources.\n");
    printf("Set the shadow mode with key '1' ... '7'\n");
    printf("Change MapSize with keys 'y'(512), 'x'(1024), 'c'(2048)\n");
    printf("NOTE: Real point lights only supported for ShadowMode 1...5!\n");

    // OSG init
    osgInit(argc, argv);

    // GLUT init
    int                     winid = setupGLUT(&argc, argv);
    gwin = GLUTWindow::create();

    useStandardScene = false;

    if(argc <= 1)
    {
        useStandardScene = true;
        animateScene = true;
        //Erstellen der benötigten Komponenten--------------------------------------

        rootNode = makeCoredNode<Group>();
        NodePtr             scene = makeCoredNode<Group>();

        // create lights
        TransformPtr        point1_trans;
        point1 = makeCoredNode<DirectionalLight>(&_point1_core);
        NodePtr             point1_beacon = makeCoredNode<Transform>
            (&point1_trans);
        beginEditCP(point1_trans);
        point1_trans->getMatrix().setTranslate(0.0, 0.0, 100.0);
        endEditCP(point1_trans);

        beginEditCP(_point1_core);
        _point1_core->setAmbient(0.15, 0.15, 0.15, 1);
        _point1_core->setDiffuse(0.4, 0.4, 0.4, 1);
        _point1_core->setSpecular(0.0, 0.0, 0.0, 1);
        _point1_core->setBeacon(point1_beacon);
        _point1_core->setOn(true);
        _point1_core->setShadowIntensity(0.7);
        _point1_core->setDirection(0.4, 0.2, 0.8);
        endEditCP(_point1_core);

        TransformPtr        point2_trans;
        point2 = makeCoredNode<PointLight>(&_point2_core);
        NodePtr             point2_beacon = makeCoredNode<Transform>
            (&point2_trans);
        beginEditCP(point2_trans);
        point2_trans->getMatrix().setTranslate(20.0, -30.0, 100.0);
        endEditCP(point2_trans);

        beginEditCP(_point2_core);
        _point2_core->setAmbient(0.15, 0.15, 0.15, 1);
        _point2_core->setDiffuse(0.4, 0.4, 0.4, 1);
        _point2_core->setSpecular(0.0, 0.0, 0.0, 1);
        _point2_core->setBeacon(point2_beacon);
        _point2_core->setOn(true);
        _point2_core->setShadowIntensity(0.7);
        endEditCP(_point2_core);

        TransformPtr        point3_trans;
        point3 = makeCoredNode<PointLight>(&_point3_core);
        NodePtr             point3_beacon = makeCoredNode<Transform>
            (&point3_trans);
        beginEditCP(point3_trans);
        point3_trans->getMatrix().setTranslate(10.0, -15.0, 100.0);
        endEditCP(point3_trans);

        beginEditCP(_point3_core);
        _point3_core->setAmbient(0.15, 0.15, 0.15, 1);
        _point3_core->setDiffuse(0.4, 0.4, 0.4, 1);
        _point3_core->setSpecular(0.0, 0.0, 0.0, 1);
        _point3_core->setBeacon(point3_beacon);
        _point3_core->setOn(true);
        _point3_core->setShadowIntensity(0.7);
        endEditCP(_point3_core);

        TransformPtr        point4_trans;
        point4 = makeCoredNode<PointLight>(&_point4_core);
        NodePtr             point4_beacon = makeCoredNode<Transform>
            (&point4_trans);
        beginEditCP(point4_trans);
        point4_trans->getMatrix().setTranslate(35.0, -45.0, 100.0);
        endEditCP(point4_trans);

        beginEditCP(_point4_core);
        _point4_core->setAmbient(0.15, 0.15, 0.15, 1);
        _point4_core->setDiffuse(0.4, 0.4, 0.4, 1);
        _point4_core->setSpecular(0.0, 0.0, 0.0, 1);
        _point4_core->setBeacon(point4_beacon);
        _point4_core->setOn(true);
        _point4_core->setShadowIntensity(0.7);
        endEditCP(_point4_core);

        TransformPtr        point5_trans;
        point5 = makeCoredNode<PointLight>(&_point5_core);
        NodePtr             point5_beacon = makeCoredNode<Transform>
            (&point5_trans);
        beginEditCP(point5_trans);
        point5_trans->getMatrix().setTranslate(40.0, -60.0, 100.0);
        endEditCP(point5_trans);

        beginEditCP(_point5_core);
        _point5_core->setAmbient(0.15, 0.15, 0.15, 1);
        _point5_core->setDiffuse(0.4, 0.4, 0.4, 1);
        _point5_core->setSpecular(0.0, 0.0, 0.0, 1);
        _point5_core->setBeacon(point5_beacon);
        _point5_core->setOn(true);
        _point5_core->setShadowIntensity(0.7);
        endEditCP(_point5_core);

        TransformPtr        point6_trans;
        point6 = makeCoredNode<PointLight>(&_point6_core);
        NodePtr             point6_beacon = makeCoredNode<Transform>
            (&point6_trans);
        beginEditCP(point6_trans);
        point6_trans->getMatrix().setTranslate(17.0, -55.0, 100.0);
        endEditCP(point6_trans);

        beginEditCP(_point6_core);
        _point6_core->setAmbient(0.15, 0.15, 0.15, 1);
        _point6_core->setDiffuse(0.4, 0.4, 0.4, 1);
        _point6_core->setSpecular(0.0, 0.0, 0.0, 1);
        _point6_core->setBeacon(point6_beacon);
        _point6_core->setOn(true);
        _point6_core->setShadowIntensity(0.7);
        endEditCP(_point6_core);

        TransformPtr        point7_trans;
        point7 = makeCoredNode<PointLight>(&_point7_core);
        NodePtr             point7_beacon = makeCoredNode<Transform>
            (&point7_trans);
        beginEditCP(point7_trans);
        point7_trans->getMatrix().setTranslate(5.0, -42.0, 100.0);
        endEditCP(point7_trans);

        beginEditCP(_point7_core);
        _point7_core->setAmbient(0.15, 0.15, 0.15, 1);
        _point7_core->setDiffuse(0.4, 0.4, 0.4, 1);
        _point7_core->setSpecular(0.0, 0.0, 0.0, 1);
        _point7_core->setBeacon(point7_beacon);
        _point7_core->setOn(true);
        _point7_core->setShadowIntensity(0.7);
        endEditCP(_point7_core);

        beginEditCP(point1);
        point1->addChild(point2);
        endEditCP(point1);

        beginEditCP(point2);
        point2->addChild(point3);
        endEditCP(point2);

        beginEditCP(point3);
        point3->addChild(point4);
        endEditCP(point3);

        beginEditCP(point4);
        point4->addChild(point5);
        endEditCP(point4);

        beginEditCP(point5);
        point5->addChild(point6);
        endEditCP(point5);

        beginEditCP(point6);
        point6->addChild(point7);
        endEditCP(point6);

        beginEditCP(point7);
        point7->addChild(scene);
        endEditCP(point7);

        // create scene

        // bottom
        NodePtr             plane = makePlane(50.0, 50.0, 128, 128);

        UChar8              imgdata[] =
        {
            255, 0, 0, 0, 255, 0, 0, 0, 255, 255, 255, 0
        };
        ImagePtr            plane_img = Image::create();
        plane_img->set(Image::OSG_RGB_PF, 2, 2, 1, 1, 1, 0, imgdata);

        TextureChunkPtr     plane_tex = TextureChunk::create();
        beginEditCP(plane_tex);
        plane_tex->setImage(plane_img);
        plane_tex->setMinFilter(GL_LINEAR);
        plane_tex->setMagFilter(GL_LINEAR);
        plane_tex->setWrapS(GL_REPEAT);
        plane_tex->setWrapT(GL_REPEAT);
        plane_tex->setEnvMode(GL_MODULATE);
        endEditCP(plane_tex);

        SimpleMaterialPtr   plane_mat = SimpleMaterial::create();
        beginEditCP(plane_mat);
        plane_mat->setAmbient(Color3f(0.3, 0.3, 0.3));
        plane_mat->setDiffuse(Color3f(1.0, 1.0, 1.0));
        plane_mat->addChunk(plane_tex);
        endEditCP(plane_mat);

        GeometryPtr         plane_geo = GeometryPtr::dcast(plane->getCore());
        beginEditCP(plane_geo);
        plane_geo->setMaterial(plane_mat);
        beginEditCP(plane_geo);

        // box
        NodePtr             box_trans_node = makeCoredNode<Transform>
            (&_box_trans);
        beginEditCP(_box_trans);
        _box_trans->getMatrix().setTranslate(0.0, 0.0, 2.0);
        endEditCP(_box_trans);
        NodePtr             box = makeBox(8.0, 8.0, 0.8, 10, 10, 10);
        beginEditCP(box_trans_node);
        box_trans_node->addChild(box);
        endEditCP(box_trans_node);

        SimpleMaterialPtr   box_mat = SimpleMaterial::create();
        beginEditCP(box_mat);
        box_mat->setAmbient(Color3f(0.0, 0.0, 0.0));
        box_mat->setDiffuse(Color3f(0.0, 0.0, 1.0));
        endEditCP(box_mat);

        GeometryPtr         box_geo = GeometryPtr::dcast(box->getCore());
        beginEditCP(box_geo);
        box_geo->setMaterial(box_mat);
        beginEditCP(box_geo);

        // cylinder1
        NodePtr             cylinder1_trans_node = makeCoredNode<Transform>
            (&_cylinder1_trans);

        Quaternion          q;

        beginEditCP(_cylinder1_trans);
        q.setValueAsAxisDeg(1, 1, 0, 145.0);
        _cylinder1_trans->getMatrix().setRotate(q);
        _cylinder1_trans->getMatrix().setTranslate(0.0, 0.0, 5.0);
        endEditCP(_cylinder1_trans);

        NodePtr             cylinder1 = OSG::makeCylinder(30.0, 0.9, 32, true,
                                                          true, true);
        beginEditCP(cylinder1_trans_node);
        cylinder1_trans_node->addChild(cylinder1);
        endEditCP(cylinder1_trans_node);

        SimpleMaterialPtr   cylinder1_mat = SimpleMaterial::create();
        beginEditCP(cylinder1_mat);
        cylinder1_mat->setAmbient(Color3f(0.0, 0.0, 0.0));
        cylinder1_mat->setDiffuse(Color3f(1.0, 0.0, 0.0));
        endEditCP(cylinder1_mat);

        GeometryPtr         cylinder1_geo = GeometryPtr::dcast(
            cylinder1->getCore());
        beginEditCP(cylinder1_geo);
        cylinder1_geo->setMaterial(cylinder1_mat);
        beginEditCP(cylinder1_geo);

        // cylinder2
        NodePtr             cylinder2_trans_node = makeCoredNode<Transform>
            (&_cylinder2_trans);
        beginEditCP(_cylinder2_trans);
        _cylinder2_trans->getMatrix().setTranslate(10.0, 0.0, 10.0);
        endEditCP(_cylinder2_trans);
        NodePtr             cylinder2 = OSG::makeBox(4.0, 4.0, 1.0, 4, 4, 4);
        beginEditCP(cylinder2_trans_node);
        cylinder2_trans_node->addChild(cylinder2);
        endEditCP(cylinder2_trans_node);

        SimpleMaterialPtr   cylinder2_mat = SimpleMaterial::create();
        beginEditCP(cylinder2_mat);
        cylinder2_mat->setAmbient(Color3f(0.0, 0.0, 0.0));
        cylinder2_mat->setDiffuse(Color3f(0.0, 1.0, 0.0));
        endEditCP(cylinder2_mat);

        GeometryPtr         cylinder2_geo = GeometryPtr::dcast(
            cylinder2->getCore());
        beginEditCP(cylinder2_geo);
        cylinder2_geo->setMaterial(cylinder2_mat);
        beginEditCP(cylinder2_geo);

        // scene
        beginEditCP(scene);
        scene->addChild(plane);
        //scene->addChild(box_trans_node);
        scene->addChild(cylinder1_trans_node);
        scene->addChild(cylinder2_trans_node);
        endEditCP(scene);


        beginEditCP(rootNode);
        rootNode->addChild(point1_beacon);
        rootNode->addChild(point2_beacon);
        rootNode->addChild(point3_beacon);
        rootNode->addChild(point4_beacon);
        rootNode->addChild(point5_beacon);
        rootNode->addChild(point6_beacon);
        rootNode->addChild(point7_beacon);
        rootNode->addChild(point1);
        endEditCP(rootNode);

        //one active light at startup
        beginEditCP(_point2_core);
        _point2_core->setOn(false);
        endEditCP(_point2_core);
        beginEditCP(_point1_core);
        _point1_core->setOn(true);
        _point1_core->setAmbient(0.3, 0.3, 0.3, 1);
        _point1_core->setDiffuse(0.8, 0.8, 0.8, 1);
        endEditCP(_point1_core);

    }
    else
    {
        animateScene = false;
        rootNode = SceneFileHandler::the().read(argv[1]);
        if(rootNode == NullFC)
        {
            fprintf(stderr, "Couldn't load '%s'!\n", argv[1]);
            exit(1);
        }
    }


    svp = ShadowViewport::create();
    GradientBackgroundPtr   gbg = GradientBackground::create();
    SolidBackgroundPtr      sbg = SolidBackground::create();

    beginEditCP(gbg);
    gbg->addLine(Color3f(0.7, 0.7, 0.8), 0);
    gbg->addLine(Color3f(0.0, 0.1, 0.3), 1);
    endEditCP(gbg);


    // Shadow viewport
    beginEditCP(svp);
    svp->setBackground(gbg);
    svp->setRoot(rootNode);
    svp->setSize(0, 0, 1, 1);
    //you can set Offset here
    //svp->setOffFactor(4.0);
    //svp->setOffBias(8.0);
    svp->setMapSize(512);
    //if globalShadowIntensity > 0.0, it is used for all lights
    //svp->setGlobalShadowIntensity(0.8);
    //ShadowSmoothness used for PCF_SHADOW_MAP and VARIANCE_SHADOW_MAP, defines Filter Width. Range can be 0.0 ... 1.0.
    //ShadowSmoothness also used to define the light size for PCSS Soft Shadows
    svp->setShadowSmoothness(0.5);

    //svp->setOffBias(8.0);
    // you can add the light sources here
    if(argv[1] == NULL)
    {
        svp->setAutoSearchForLights(false);
        svp->getLightNodes().push_back(point1);
        svp->getLightNodes().push_back(point2);
        svp->getLightNodes().push_back(point3);
        svp->getLightNodes().push_back(point4);
        svp->getLightNodes().push_back(point5);
        svp->getLightNodes().push_back(point6);
        svp->getLightNodes().push_back(point7);
        svp->setOffFactor(4.0);
        svp->setOffBias(8.0);
    }
    else
    {
        //if set, all lights in the scene will be used
        svp->setAutoSearchForLights(true);
    }

    endEditCP(svp);

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

    beginEditCP(svp);//Viewport
    svp->setCamera(mgr->getCamera());
    endEditCP(svp);

    startFpsCounter();

    ((RenderAction *)mgr->getAction())->setLocalLights(true);
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
    showFpsCounter();

    if(animateScene)
    {
        static Real64   t0 = OSG::getSystemTime();

        Real64          t = OSG::getSystemTime() - t0;

        Real32          rotb = t * 10.0;
        if(rotb > 360.0)
            rotb -= 360.0;

        Real32          rotc1 = t * 20.0;
        if(rotc1 > 360.0)
            rotc1 -= 360.0;

        Real32          rotc2 = t * 40.0;
        if(rotc2 > 360.0)
            rotc2 -= 360.0;

        Quaternion      q;
        /*beginEditCP(_box_trans);
           q.setValueAsAxisDeg(0,0,1, rotb);
           _box_trans->getMatrix().setRotate(q);
           endEditCP(_box_trans);*/

        beginEditCP(_cylinder1_trans);
        q.setValueAsAxisDeg(1, 0, 0, rotc1);
        _cylinder1_trans->getMatrix().setRotate(q);
        endEditCP(_cylinder1_trans);

        beginEditCP(_cylinder2_trans);
        _cylinder2_trans->getMatrix().setTranslate(10.0, 0.0, 10.0 +
                                                   (9.0 * sin(rotb / 10.0)));
        endEditCP(_cylinder2_trans);

        /*beginEditCP(_cylinder2_trans);
           q.setValueAsAxisDeg(0,0,1, rotc2);
           _cylinder2_trans->getMatrix().setRotate(q);
           endEditCP(_cylinder2_trans);*/
    }


    mgr->redraw();
}

// redraw the window
void display(void)
{
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

        case 'u':
            {
                if(useStandardScene)
                {
                    beginEditCP(_point1_core);
                    _point1_core->setOn(true);
                    _point1_core->setAmbient(0.3, 0.3, 0.3, 1);
                    _point1_core->setDiffuse(0.8, 0.8, 0.8, 1);
                    endEditCP(_point1_core);

                    beginEditCP(_point2_core);
                    _point2_core->setOn(false);
                    endEditCP(_point2_core);

                    beginEditCP(_point3_core);
                    _point3_core->setOn(false);
                    endEditCP(_point3_core);

                    beginEditCP(_point4_core);
                    _point4_core->setOn(false);
                    endEditCP(_point4_core);

                    beginEditCP(_point5_core);
                    _point5_core->setOn(false);
                    endEditCP(_point5_core);

                    beginEditCP(_point6_core);
                    _point6_core->setOn(false);
                    endEditCP(_point6_core);

                    beginEditCP(_point7_core);
                    _point7_core->setOn(false);
                    endEditCP(_point7_core);
                }
                break;
            }

        case 'i':
            {
                if(useStandardScene)
                {
                    beginEditCP(_point1_core);
                    _point1_core->setAmbient(0.15, 0.15, 0.15, 1);
                    _point1_core->setDiffuse(0.4, 0.4, 0.4, 1);
                    _point1_core->setOn(true);
                    endEditCP(_point1_core);

                    beginEditCP(_point2_core);
                    _point2_core->setAmbient(0.15, 0.15, 0.15, 1);
                    _point2_core->setDiffuse(0.4, 0.4, 0.4, 1);
                    _point2_core->setOn(true);
                    endEditCP(_point2_core);

                    beginEditCP(_point3_core);
                    _point3_core->setOn(false);
                    endEditCP(_point3_core);

                    beginEditCP(_point4_core);
                    _point4_core->setOn(false);
                    endEditCP(_point4_core);

                    beginEditCP(_point5_core);
                    _point5_core->setOn(false);
                    endEditCP(_point5_core);

                    beginEditCP(_point6_core);
                    _point6_core->setOn(false);
                    endEditCP(_point6_core);

                    beginEditCP(_point7_core);
                    _point7_core->setOn(false);
                    endEditCP(_point7_core);
                }
                break;
            }

        case 'o':
            {
                if(useStandardScene)
                {
                    beginEditCP(_point1_core);
                    _point1_core->setAmbient(0.3 / 3.0, 0.3 / 3.0, 0.3 / 3.0,
                                             1);
                    _point1_core->setDiffuse(0.8 / 3.0, 0.8 / 3.0, 0.8 / 3.0,
                                             1);
                    _point1_core->setOn(true);
                    endEditCP(_point1_core);

                    beginEditCP(_point2_core);
                    _point2_core->setAmbient(0.3 / 3.0, 0.3 / 3.0, 0.3 / 3.0,
                                             1);
                    _point2_core->setDiffuse(0.8 / 3.0, 0.8 / 3.0, 0.8 / 3.0,
                                             1);
                    _point2_core->setOn(true);
                    endEditCP(_point2_core);

                    beginEditCP(_point3_core);
                    _point3_core->setAmbient(0.3 / 3.0, 0.3 / 3.0, 0.3 / 3.0,
                                             1);
                    _point3_core->setDiffuse(0.8 / 3.0, 0.8 / 3.0, 0.8 / 3.0,
                                             1);
                    _point3_core->setOn(true);
                    endEditCP(_point3_core);

                    beginEditCP(_point4_core);
                    _point4_core->setOn(false);
                    endEditCP(_point4_core);

                    beginEditCP(_point5_core);
                    _point5_core->setOn(false);
                    endEditCP(_point5_core);

                    beginEditCP(_point6_core);
                    _point6_core->setOn(false);
                    endEditCP(_point6_core);

                    beginEditCP(_point7_core);
                    _point7_core->setOn(false);
                    endEditCP(_point7_core);
                }
                break;
            }

        case 'p':
            {
                if(useStandardScene)
                {
                    beginEditCP(_point1_core);
                    _point1_core->setAmbient(0.3 / 4.0, 0.3 / 4.0, 0.3 / 4.0,
                                             1);
                    _point1_core->setDiffuse(0.8 / 4.0, 0.8 / 4.0, 0.8 / 4.0,
                                             1);
                    _point1_core->setOn(true);
                    endEditCP(_point1_core);

                    beginEditCP(_point2_core);
                    _point2_core->setAmbient(0.3 / 4.0, 0.3 / 4.0, 0.3 / 4.0,
                                             1);
                    _point2_core->setDiffuse(0.8 / 4.0, 0.8 / 4.0, 0.8 / 4.0,
                                             1);
                    _point2_core->setOn(true);
                    endEditCP(_point2_core);

                    beginEditCP(_point3_core);
                    _point3_core->setAmbient(0.3 / 4.0, 0.3 / 4.0, 0.3 / 4.0,
                                             1);
                    _point3_core->setDiffuse(0.8 / 4.0, 0.8 / 4.0, 0.8 / 4.0,
                                             1);
                    _point3_core->setOn(true);
                    endEditCP(_point3_core);

                    beginEditCP(_point4_core);
                    _point4_core->setOn(true);
                    _point4_core->setAmbient(0.3 / 4.0, 0.3 / 4.0, 0.3 / 4.0,
                                             1);
                    _point4_core->setDiffuse(0.8 / 4.0, 0.8 / 4.0, 0.8 / 4.0,
                                             1);
                    endEditCP(_point4_core);

                    beginEditCP(_point5_core);
                    _point5_core->setOn(false);
                    endEditCP(_point5_core);

                    beginEditCP(_point6_core);
                    _point6_core->setOn(false);
                    endEditCP(_point6_core);

                    beginEditCP(_point7_core);
                    _point7_core->setOn(false);
                    endEditCP(_point7_core);
                }
                break;
            }

        case 'j':
            {
                if(useStandardScene)
                {
                    beginEditCP(_point1_core);
                    _point1_core->setAmbient(0.3 / 5.0, 0.3 / 5.0, 0.3 / 5.0,
                                             1);
                    _point1_core->setDiffuse(0.8 / 5.0, 0.8 / 5.0, 0.8 / 5.0,
                                             1);
                    _point1_core->setOn(true);
                    endEditCP(_point1_core);

                    beginEditCP(_point2_core);
                    _point2_core->setAmbient(0.3 / 5.0, 0.3 / 5.0, 0.3 / 5.0,
                                             1);
                    _point2_core->setDiffuse(0.8 / 5.0, 0.8 / 5.0, 0.8 / 5.0,
                                             1);
                    _point2_core->setOn(true);
                    endEditCP(_point2_core);

                    beginEditCP(_point3_core);
                    _point3_core->setAmbient(0.3 / 5.0, 0.3 / 5.0, 0.3 / 5.0,
                                             1);
                    _point3_core->setDiffuse(0.8 / 5.0, 0.8 / 5.0, 0.8 / 5.0,
                                             1);
                    _point3_core->setOn(true);
                    endEditCP(_point3_core);

                    beginEditCP(_point4_core);
                    _point4_core->setOn(true);
                    _point4_core->setAmbient(0.3 / 5.0, 0.3 / 5.0, 0.3 / 5.0,
                                             1);
                    _point4_core->setDiffuse(0.8 / 5.0, 0.8 / 5.0, 0.8 / 5.0,
                                             1);
                    endEditCP(_point4_core);

                    beginEditCP(_point5_core);
                    _point5_core->setOn(true);
                    _point5_core->setAmbient(0.3 / 5.0, 0.3 / 5.0, 0.3 / 5.0,
                                             1);
                    _point5_core->setDiffuse(0.8 / 5.0, 0.8 / 5.0, 0.8 / 5.0,
                                             1);
                    endEditCP(_point5_core);

                    beginEditCP(_point6_core);
                    _point6_core->setOn(false);
                    endEditCP(_point6_core);

                    beginEditCP(_point7_core);
                    _point7_core->setOn(false);
                    endEditCP(_point7_core);
                }
                break;
            }

        case 'k':
            {
                if(useStandardScene)
                {
                    beginEditCP(_point1_core);
                    _point1_core->setAmbient(0.3 / 6.0, 0.3 / 6.0, 0.3 / 6.0,
                                             1);
                    _point1_core->setDiffuse(0.8 / 6.0, 0.8 / 6.0, 0.8 / 6.0,
                                             1);
                    _point1_core->setOn(true);
                    endEditCP(_point1_core);

                    beginEditCP(_point2_core);
                    _point2_core->setAmbient(0.3 / 6.0, 0.3 / 6.0, 0.3 / 6.0,
                                             1);
                    _point2_core->setDiffuse(0.8 / 6.0, 0.8 / 6.0, 0.8 / 6.0,
                                             1);
                    _point2_core->setOn(true);
                    endEditCP(_point2_core);

                    beginEditCP(_point3_core);
                    _point3_core->setAmbient(0.3 / 6.0, 0.3 / 6.0, 0.3 / 6.0,
                                             1);
                    _point3_core->setDiffuse(0.8 / 6.0, 0.8 / 6.0, 0.8 / 6.0,
                                             1);
                    _point3_core->setOn(true);
                    endEditCP(_point3_core);

                    beginEditCP(_point4_core);
                    _point4_core->setOn(true);
                    _point4_core->setAmbient(0.3 / 6.0, 0.3 / 6.0, 0.3 / 6.0,
                                             1);
                    _point4_core->setDiffuse(0.8 / 6.0, 0.8 / 6.0, 0.8 / 6.0,
                                             1);
                    endEditCP(_point4_core);

                    beginEditCP(_point5_core);
                    _point5_core->setOn(true);
                    _point5_core->setAmbient(0.3 / 6.0, 0.3 / 6.0, 0.3 / 6.0,
                                             1);
                    _point5_core->setDiffuse(0.8 / 6.0, 0.8 / 6.0, 0.8 / 6.0,
                                             1);
                    endEditCP(_point5_core);

                    beginEditCP(_point6_core);
                    _point6_core->setOn(true);
                    _point6_core->setAmbient(0.3 / 6.0, 0.3 / 6.0, 0.3 / 6.0,
                                             1);
                    _point6_core->setDiffuse(0.8 / 6.0, 0.8 / 6.0, 0.8 / 6.0,
                                             1);
                    endEditCP(_point6_core);

                    beginEditCP(_point7_core);
                    _point7_core->setOn(false);
                    endEditCP(_point7_core);
                }
                break;
            }

        case 'l':
            {
                if(useStandardScene)
                {
                    beginEditCP(_point1_core);
                    _point1_core->setAmbient(0.3 / 7.0, 0.3 / 7.0, 0.3 / 7.0,
                                             1);
                    _point1_core->setDiffuse(0.8 / 7.0, 0.8 / 7.0, 0.8 / 7.0,
                                             1);
                    _point1_core->setOn(true);
                    endEditCP(_point1_core);

                    beginEditCP(_point2_core);
                    _point2_core->setAmbient(0.3 / 7.0, 0.3 / 7.0, 0.3 / 7.0,
                                             1);
                    _point2_core->setDiffuse(0.8 / 7.0, 0.8 / 7.0, 0.8 / 7.0,
                                             1);
                    _point2_core->setOn(true);
                    endEditCP(_point2_core);

                    beginEditCP(_point3_core);
                    _point3_core->setAmbient(0.3 / 7.0, 0.3 / 7.0, 0.3 / 7.0,
                                             1);
                    _point3_core->setDiffuse(0.8 / 7.0, 0.8 / 7.0, 0.8 / 7.0,
                                             1);
                    _point3_core->setOn(true);
                    endEditCP(_point3_core);

                    beginEditCP(_point4_core);
                    _point4_core->setOn(true);
                    _point4_core->setAmbient(0.3 / 7.0, 0.3 / 7.0, 0.3 / 7.0,
                                             1);
                    _point4_core->setDiffuse(0.8 / 7.0, 0.8 / 7.0, 0.8 / 7.0,
                                             1);
                    endEditCP(_point4_core);

                    beginEditCP(_point5_core);
                    _point5_core->setOn(true);
                    _point5_core->setAmbient(0.3 / 7.0, 0.3 / 7.0, 0.3 / 7.0,
                                             1);
                    _point5_core->setDiffuse(0.8 / 7.0, 0.8 / 7.0, 0.8 / 7.0,
                                             1);
                    endEditCP(_point5_core);

                    beginEditCP(_point6_core);
                    _point6_core->setOn(true);
                    _point6_core->setAmbient(0.3 / 7.0, 0.3 / 7.0, 0.3 / 7.0,
                                             1);
                    _point6_core->setDiffuse(0.8 / 7.0, 0.8 / 7.0, 0.8 / 7.0,
                                             1);
                    endEditCP(_point6_core);

                    beginEditCP(_point7_core);
                    _point7_core->setOn(true);
                    _point7_core->setAmbient(0.3 / 7.0, 0.3 / 7.0, 0.3 / 7.0,
                                             1);
                    _point7_core->setDiffuse(0.8 / 7.0, 0.8 / 7.0, 0.8 / 7.0,
                                             1);
                    endEditCP(_point7_core);
                }
                break;
            }

        case '1':
            {
                beginEditCP(svp, ShadowViewport::ShadowModeFieldMask);
                svp->setShadowMode(ShadowViewport::NO_SHADOW);
                endEditCP(svp, ShadowViewport::ShadowModeFieldMask);
                break;
            }

        case '2':
            {
                beginEditCP(svp, ShadowViewport::ShadowModeFieldMask);
                svp->setShadowMode(ShadowViewport::STD_SHADOW_MAP);
                endEditCP(svp, ShadowViewport::ShadowModeFieldMask);
                break;
            }

        case '3':
            {
                beginEditCP(svp, ShadowViewport::ShadowModeFieldMask);
                svp->setShadowMode(ShadowViewport::PERSPECTIVE_SHADOW_MAP);
                endEditCP(svp, ShadowViewport::ShadowModeFieldMask);
                break;
            }

        case '4':
            {
                beginEditCP(svp, ShadowViewport::ShadowModeFieldMask);
                svp->setShadowMode(ShadowViewport::DITHER_SHADOW_MAP);
                endEditCP(svp, ShadowViewport::ShadowModeFieldMask);
                break;
            }

        case '5':
            {
                beginEditCP(svp, ShadowViewport::ShadowModeFieldMask);
                svp->setShadowMode(ShadowViewport::PCF_SHADOW_MAP);
                //svp->setShadowSmoothness(0.5);
                endEditCP(svp, ShadowViewport::ShadowModeFieldMask);
                break;
            }

        case '6':
            {
                beginEditCP(svp, ShadowViewport::ShadowModeFieldMask);
                svp->setShadowMode(ShadowViewport::PCSS_SHADOW_MAP);
                svp->setShadowSmoothness(0.2);
                endEditCP(svp, ShadowViewport::ShadowModeFieldMask);
                break;
            }

        case '7':
            {
                beginEditCP(svp, ShadowViewport::ShadowModeFieldMask);
                svp->setShadowMode(ShadowViewport::VARIANCE_SHADOW_MAP);
                svp->setShadowSmoothness(0.5);
                endEditCP(svp, ShadowViewport::ShadowModeFieldMask);
                break;
            }

        case 'w':
            {
                Real32  t = svp->getOffBias();

                beginEditCP(svp, ShadowViewport::OffBiasFieldMask);
                svp->setOffBias(++t);
                endEditCP(svp, ShadowViewport::OffBiasFieldMask);
                SLOG << "Polygon-OffsetBias is: " << ++t << endLog;
                break;
            }

        case 's':
            {
                Real32  t = svp->getOffBias();

                beginEditCP(svp, ShadowViewport::OffBiasFieldMask);
                svp->setOffBias(--t);
                endEditCP(svp, ShadowViewport::OffBiasFieldMask);
                SLOG << "Polygon-OffsetBias is: " << --t << endLog;
                break;
            }

        case 'e':
            {
                Real32  u = svp->getOffFactor();

                beginEditCP(svp, ShadowViewport::OffFactorFieldMask);
                svp->setOffFactor(++u);
                endEditCP(svp, ShadowViewport::OffFactorFieldMask);
                SLOG << "Polygon-OffsetFactor is: " << ++u << endLog;
                break;
            }

        case 'd':
            {
                Real32  u = svp->getOffFactor();

                beginEditCP(svp, ShadowViewport::OffFactorFieldMask);
                svp->setOffFactor(--u);
                endEditCP(svp, ShadowViewport::OffFactorFieldMask);
                SLOG << "Polygon-OffsetFactor is: " << --u << endLog;
                break;
            }

        case '+':
            {
                Real32  r = svp->getShadowSmoothness();

                beginEditCP(svp, ShadowViewport::ShadowSmoothnessFieldMask);
                svp->setShadowSmoothness(r + 0.1);
                endEditCP(svp, ShadowViewport::ShadowSmoothnessFieldMask);
                //SLOG << "ShadowSmoothness is: " << r << endLog;
                break;
            }

        case '-':
            {
                Real32  r = svp->getShadowSmoothness();

                beginEditCP(svp, ShadowViewport::ShadowSmoothnessFieldMask);
                svp->setShadowSmoothness(r - 0.1);
                endEditCP(svp, ShadowViewport::ShadowSmoothnessFieldMask);
                //SLOG << "ShadowSmoothness is: " << r << endLog;
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

        case 'a':
            {
                if(useStandardScene)
                {
                    animateScene = !animateScene;
                }
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

    int w = 640, h = 512;

    if(*argc == 4)
    {
        w = atoi(argv[2]);
        h = atoi(argv[3]);
    }
    
    //Set WindowSize here
    glutInitWindowSize(w, h);
    int winid = glutCreateWindow("Shadow-Scene");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(Animate);

    return winid;
}
