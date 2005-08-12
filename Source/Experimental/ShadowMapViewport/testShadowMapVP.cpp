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

#include "OSGShadowMapViewport.h"

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

GLUTWindowPtr gwin;
ShadowMapViewportPtr svp;

NodePtr rootNode;
SpotLightPtr spot1_core;
SpotLightPtr spot2_core;
DirectionalLightPtr raumlicht_core;
PointLightPtr _point1_core;
PointLightPtr _point2_core;
TransformPtr _box_trans;
TransformPtr _cylinder1_trans;
TransformPtr _cylinder2_trans;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    printf("Press key '1' or '2' to switch between one and two light sources.\n");
    // OSG init
    osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);
    gwin = GLUTWindow::create();

    //Erstellen der benötigten Komponenten--------------------------------------

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

    UChar8 imgdata[] =
        {  255,0,0,  0,255,0,  0,0,255, 255,255,0 };
    ImagePtr plane_img = Image::create();
    plane_img->set(Image::OSG_RGB_PF, 2, 2, 1, 1, 1, 0, imgdata);

    TextureChunkPtr plane_tex = TextureChunk::create();
    beginEditCP(plane_tex);
        plane_tex->setImage(plane_img);
        plane_tex->setMinFilter(GL_LINEAR);
        plane_tex->setMagFilter(GL_LINEAR);
        plane_tex->setWrapS(GL_REPEAT);
        plane_tex->setWrapT(GL_REPEAT);
        plane_tex->setEnvMode(GL_MODULATE);
    endEditCP(plane_tex);

    SimpleMaterialPtr plane_mat = SimpleMaterial::create();
    beginEditCP(plane_mat);
        plane_mat->setAmbient(Color3f(0.3,0.3,0.3));
        plane_mat->setDiffuse(Color3f(1.0,1.0,1.0));
        plane_mat->addChunk(plane_tex);
    endEditCP(plane_mat);

    GeometryPtr plane_geo = GeometryPtr::dcast(plane->getCore());
    beginEditCP(plane_geo);
        plane_geo->setMaterial(plane_mat);
    beginEditCP(plane_geo);
    
    // box
    NodePtr box_trans_node = makeCoredNode<Transform>(&_box_trans);
    beginEditCP(_box_trans);
        _box_trans->getMatrix().setTranslate(0.0, 0.0, 2.0);
    endEditCP(_box_trans);
    NodePtr box = makeBox(8.0, 8.0, 0.8, 10, 10 , 10);
    beginEditCP(box_trans_node);
        box_trans_node->addChild(box);
    endEditCP(box_trans_node);

    SimpleMaterialPtr box_mat = SimpleMaterial::create();
    beginEditCP(box_mat);
        box_mat->setAmbient(Color3f(0.0,0.0,0.0));
        box_mat->setDiffuse(Color3f(0.0,0.0,1.0));
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

    svp = ShadowMapViewport::create();
    GradientBackgroundPtr gbg = GradientBackground::create();
    SolidBackgroundPtr sbg = SolidBackground::create();

    beginEditCP(gbg);
        gbg->addLine(Color3f(0.7, 0.7, 0.8), 0);
        gbg->addLine(Color3f(0.0, 0.1, 0.3), 1);
    endEditCP(gbg);

    beginEditCP(rootNode);
        rootNode->addChild(point1);
        rootNode->addChild(point1_beacon);
        rootNode->addChild(point2_beacon);
    endEditCP(rootNode);

    // Shadow viewport
    beginEditCP(svp);
        svp->setBackground(gbg);
        svp->setRoot(rootNode);
        svp->setSize(0,0,1,1);
        svp->setOffFactor(10.0);
        svp->setOffBias(4.0);
        svp->setShadowColor(Color4f(0.1, 0.1, 0.1, 1.0));
        svp->setMapSize(1024);
        // you can add the light sources here, as default all light source in
        // the scenegraph are used.
        svp->getLightNodes().push_back(point1);
        svp->getLightNodes().push_back(point2);
    endEditCP(svp);

    beginEditCP(gwin);//Window
        gwin->setId(winid);
        gwin->addPort(svp);
        gwin->init();
    endEditCP(gwin);

    Vec3f min,max;
    rootNode->updateVolume();
    rootNode->getVolume().getBounds( min, max );

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    mgr->setWindow(gwin);
    mgr->setRoot(rootNode);

    beginEditCP(svp);//Viewport
        svp->setCamera(mgr->getCamera());
    endEditCP(svp);

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
        q.setValueAsAxisDeg(0,0,1, rotb);
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
            beginEditCP(_point1_core);
                _point1_core->setOn(true);
                _point1_core->setAmbient(0.3,0.3,0.3,1);
                _point1_core->setDiffuse(0.8,0.8,0.8,1);
            endEditCP(_point1_core);

            beginEditCP(_point2_core);
                _point2_core->setOn(false);
            endEditCP(_point2_core);
            break;
        }

        case '2':
        {
            beginEditCP(_point1_core);
                _point1_core->setAmbient(0.15,0.15,0.15,1);
                _point1_core->setDiffuse(0.4,0.4,0.4,1);
                _point1_core->setOn(true);
            endEditCP(_point1_core);

            beginEditCP(_point2_core);
                _point2_core->setAmbient(0.15,0.15,0.15,1);
                _point2_core->setDiffuse(0.4,0.4,0.4,1);
                _point2_core->setOn(true);
            endEditCP(_point2_core);
            break;
        }

        case 'w':
        {
            Real32 t = svp->getOffBias();
            
            beginEditCP(svp, ShadowMapViewport::OffBiasFieldMask);
                svp->setOffBias(++t);
            endEditCP(svp, ShadowMapViewport::OffBiasFieldMask);
            SLOG << "Polygon-OffsetBias is: " << t << endLog;
            break;
        }
        
        case 's':
        {
            Real32 t = svp->getOffBias();
            
            beginEditCP(svp, ShadowMapViewport::OffBiasFieldMask);
                svp->setOffBias(--t);
            endEditCP(svp, ShadowMapViewport::OffBiasFieldMask);
            SLOG << "Polygon-OffsetBias is: " << t << endLog;
            break;
        }
        
        case 'e':
        {
            Real32 t = svp->getOffFactor();
            
            beginEditCP(svp, ShadowMapViewport::OffFactorFieldMask);
                svp->setOffFactor(++t);
            endEditCP(svp, ShadowMapViewport::OffFactorFieldMask);
            SLOG << "Polygon-OffsetFactor is: " << t << endLog;
            break;
        }
        
        case 'd':
        {    
            Real32 t = svp->getOffFactor();    
            
            beginEditCP(svp, ShadowMapViewport::OffFactorFieldMask);
                svp->setOffFactor(--t);
            endEditCP(svp, ShadowMapViewport::OffFactorFieldMask);
            SLOG << "Polygon-OffsetFactor is: " << t << endLog;
            break;
        }
        case 'a':
        {
            bool s = svp->getShadowOn();
            beginEditCP(svp, ShadowMapViewport::OffFactorFieldMask);
                svp->setShadowOn(!s);
            endEditCP(svp, ShadowMapViewport::OffFactorFieldMask);
        }
        case 'x':
        {
            SceneFileHandler::the().write(rootNode, "shadow.osb.gz", true);
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
    glutInitWindowSize(640,640);
    int winid = glutCreateWindow("Shadow-Scene");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(Animate);

    return winid;
}
