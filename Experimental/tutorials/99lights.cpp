// OpenSG Tutorial Example: Light Sources
//
// This example shows how to create and use lights.
//
// Hit a, s and d to switch between the different kinds of lights.
//

// Headers
#include <GL/glut.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGGroup.h>

// new headers: 

// The headers for the light sources
#include <OpenSG/OSGDirectionalLight.h>
#include <OpenSG/OSGPointLight.h>
#include <OpenSG/OSGSpotLight.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The pointer to the transformation
TransformPtr trans;

// pointers to the used lights
DirectionalLightPtr dlight;
PointLightPtr       plight;
SpotLightPtr        slight;

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

// redraw the window
void display( void )
{
    // create the matrix
    Matrix m;
    Real32 t = glutGet(GLUT_ELAPSED_TIME );
   
    m.setTransform(Vec3f(      osgsin(t / 1500.f), 
                               osgcos(t / 1500.f), 
                               osgsin(t / 1000.f) / 1.5 + 0.9),
                    Quaternion( Vec3f(1,1,0), 
                               osgsin(t /  800.f)));

    // set the transform's matrix
    beginEditCP(trans, Transform::MatrixFieldMask);
    {
        trans->setMatrix(m);
    }   
    endEditCP  (trans, Transform::MatrixFieldMask);
   
    mgr->redraw();
}

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setWinID(winid);
    gwin->init();

    // create the scene

    NodePtr scene = Node::create();

    /*
        Create some geometry. The large plane is the lit object, the small
        plane shows the position and direction of the light source.
    */
    
    // Geometry
    NodePtr g1;
    g1 = makePlane( 3, 3, 30, 30 );
    
    // Light Position Indicator
    NodePtr g2 = Node::create();
    GeometryPtr lgeo = makePlaneGeo( .2, .2, 1, 1 );
    beginEditCP(lgeo, Geometry::MaterialFieldMask);
    {
        lgeo->setMaterial(getDefaultUnlitMaterial());
    }
    endEditCP  (lgeo, Geometry::MaterialFieldMask);
    beginEditCP(g2, Node::CoreFieldMask);
    {
        g2->setCore( lgeo );
    }
    endEditCP  (g2, Node::CoreFieldMask);


    // Transform

    NodePtr tnode = Node::create();
    trans = Transform::create();
    beginEditCP(tnode);
    tnode->setCore( trans );
    tnode->addChild( g2 );
    endEditCP(tnode);

    // Create Lights

    NodePtr dlightnode = Node::create();
    dlight = DirectionalLight::create();

    beginEditCP(dlightnode);
    dlightnode->setCore(dlight);
    dlightnode->addChild(g1);
    endEditCP(dlightnode);
    
    beginEditCP(dlight);
    dlight->setAmbient( .2, .2, .2, .2 );
    dlight->setDiffuse( 1, 0, 0, 1 );
    dlight->setSpecular( 1, 0, 0, 1 );
    dlight->setDirection(0,0,1);
    dlight->setBeacon( tnode );
    endEditCP(dlight);


    NodePtr plightnode = Node::create();
    plight = PointLight::create();
    addRefCP( plightnode ); // add a reference to keep it alive when removing from tree

    beginEditCP(plightnode);
    plightnode->setCore( plight );
    plightnode->addChild( dlightnode );
    endEditCP(plightnode);
    
    beginEditCP(plight);
    plight->setAmbient( .2, .2, .2, .2 );
    plight->setDiffuse( 0, 1, 0, 1 );
//    plight->setConstantAttenuation(.5);
//    plight->setLinearAttenuation(.5);
 //   plight->setQuadraticAttenuation(2);     
    plight->setPosition(0,0,0);
    plight->setBeacon( tnode );
    plight->setOn(false);
    endEditCP(plight);


    NodePtr slightnode = Node::create();
    slight = SpotLight::create();
    addRefCP( slightnode ); // add a reference to keep it alive when removing from tree

    beginEditCP(slightnode);
    slightnode->setCore( slight );
    slightnode->addChild( plightnode );
    endEditCP(slightnode);
    
    beginEditCP(slight);
    slight->setAmbient( .2, .2, .2, .2 );
    slight->setDiffuse( 0, 0, 1, 1 );
    slight->setPosition(0,0,0);
    slight->setSpotDirection(0,0,-1);
    slight->setSpotExponent(10);
    slight->setSpotCutOffDeg(45);
    slight->setBeacon( tnode );
    slight->setOn(false);
    endEditCP(slight);

    GroupPtr gr = Group::create();
    beginEditCP(scene);
    scene->setCore( gr );
    scene->addChild( tnode );
    scene->addChild( slightnode );
    endEditCP(scene);
    
     

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();
    mgr->turnHeadlightOff();

    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

// react to size changes
void reshape(int w, int h)
{
    mgr->resize(w, h);
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
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
    case 27:    exit(1);
    case 'a':   beginEditCP(dlight, DirectionalLight::OnFieldMask);
                beginEditCP(plight,       PointLight::OnFieldMask);
                beginEditCP(slight,        SpotLight::OnFieldMask);
                    dlight->setOn(true );
                    plight->setOn(false);
                    slight->setOn(false);
                endEditCP  (dlight, DirectionalLight::OnFieldMask);
                endEditCP  (plight,       PointLight::OnFieldMask);
                endEditCP  (slight,        SpotLight::OnFieldMask);
                break;
    case 's':   beginEditCP(dlight, DirectionalLight::OnFieldMask);
                beginEditCP(plight,       PointLight::OnFieldMask);
                beginEditCP(slight,        SpotLight::OnFieldMask);
                    dlight->setOn(false);
                    plight->setOn(true );
                    slight->setOn(false);
                endEditCP  (dlight, DirectionalLight::OnFieldMask);
                endEditCP  (plight,       PointLight::OnFieldMask);
                endEditCP  (slight,        SpotLight::OnFieldMask);
                break;
    case 'd':   beginEditCP(dlight, DirectionalLight::OnFieldMask);
                beginEditCP(plight,       PointLight::OnFieldMask);
                beginEditCP(slight,        SpotLight::OnFieldMask);
                    dlight->setOn(false);
                    plight->setOn(false);
                    slight->setOn(true );
                endEditCP  (dlight, DirectionalLight::OnFieldMask);
                endEditCP  (plight,       PointLight::OnFieldMask);
                endEditCP  (slight,        SpotLight::OnFieldMask);
                break;
    }
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    // call the redraw function whenever there's nothing else to do
    glutIdleFunc(display);

    return winid;
}
