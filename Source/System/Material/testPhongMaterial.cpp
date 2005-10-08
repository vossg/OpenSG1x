// Headers
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>

#include <OSGPassiveWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGAction.h>
#include <OSGSFSysTypes.h>
#include <OSGSceneFileHandler.h>
#include <OSGBaseFunctions.h>
#include <OSGSimpleTexturedMaterial.h>
#include <OSGSimpleMaterial.h>
#include <OSGGradientBackground.h>

#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGTransform.h>
#include <OSGPointLight.h>

#include <OSGPhongMaterial.h>

#include <iostream>


// Activate the OpenSG namespace
OSG_USING_NAMESPACE


// ------------------- global vars ----------------------
//
// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
// The scene
NodePtr scene;
// Point light source
PointLightPtr pl;
// Material pointers

GeometryPtr geo;

PhongMaterialPtr pmat;
SimpleMaterialPtr smat;

bool moveLight = true;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    std::cout << "***********************************************************" << std::endl;
    std::cout << "*      OpenSG - material with phong shading               *" << std::endl;
    std::cout << "***********************************************************" << std::endl;
    std::cout << "\nKeys:   'q' exit" << std::endl;
    std::cout << "        'w' wireframe" << std::endl;
    std::cout << "        'l' animate light" << std::endl;
    std::cout << "        'p' phong shading" << std::endl;
    std::cout << "        'g' gouraud shading" << std::endl;
    std::cout << "        '}' move light source forward" << std::endl;
    std::cout << "        '{' move light source backward" << std::endl;
    std::cout << "       'Up' move light source up    (NumLock is ON)" << std::endl;
    std::cout << "     'Down' move light source down  (NumLock is ON)" << std::endl;
    std::cout << "     'Left' move light source left  (NumLock is ON)" << std::endl;
    std::cout << "    'Right' move light source right (NumLock is ON)" << std::endl;

    // OSG init
    osgInit(argc,argv);
    
    // just to simulate a card without fragment shader.
    //OSG::Window::ignoreExtensions("GL_ARB_fragment_program");

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    PassiveWindowPtr pwin = PassiveWindow::create();
    pwin->init(); 

    pmat = PhongMaterial::create();
    addRefCP(pmat);
    beginEditCP(pmat);
        pmat->setAmbient(Color3f(0.1, 0.1, 0.1));
        pmat->setDiffuse(Color3f(0.397194,0.175152, 0.0699518));
        pmat->setSpecular(Color3f(0.8, 0.8, 0.8));
        pmat->setShininess(128);
        pmat->setTransparency(0.0);
    endEditCP(pmat);

    smat = SimpleMaterial::create();
    addRefCP(smat);
    beginEditCP(smat);
        smat->setAmbient(Color3f(0.1, 0.1, 0.1));
        smat->setDiffuse(Color3f(0.397194,0.175152, 0.0699518));
        smat->setSpecular(Color3f(0.8, 0.8, 0.8));
        smat->setShininess(128);
        smat->setTransparency(0.0);
    endEditCP(smat);
    
    // create root node
    scene = Node::create();
    
    // create geometry
    //geo = makeTorusGeo(0.25, 0.5, 32, 32);
    geo = makePlaneGeo(1.0, 1.0, 1, 1);

    beginEditCP(geo, Geometry::MaterialFieldMask);
        geo->setMaterial(pmat);
    endEditCP(geo, Geometry::MaterialFieldMask);
    
    NodePtr torus = Node::create();
    beginEditCP( torus, Node::CoreFieldMask );
        torus->setCore( geo );
    endEditCP( torus, Node::CoreFieldMask );
    
    // create light
    NodePtr tnode = Node::create();
    TransformPtr tr = Transform::create();
    
    beginEditCP(tr);
        tnode->setCore(tr);
    endEditCP(tr);
    
    NodePtr plight = Node::create();
    pl = PointLight::create();
    beginEditCP(plight);
        plight->setCore( pl );
    endEditCP(plight);
    
    // set attributes of light source
    beginEditCP(pl);
        pl->setAmbient( 1, 1, 1, 1 );
        pl->setDiffuse( 1, 1, 1, 1 );
        pl->setSpecular( 1, 1, 1, 1 );
        pl->setPosition(0,0,10);
        pl->setBeacon( tnode );
    endEditCP(pl);
    
    // add light and geometry to scene
    GroupPtr gr = Group::create();
    beginEditCP(scene);
        scene->setCore( gr );
        scene->addChild( plight );
        scene->addChild( torus );
    endEditCP(scene);
    
    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(pwin);
    mgr->setRoot(scene);

    // Background
    GradientBackgroundPtr gbkgnd = GradientBackground::create();
    beginEditCP(gbkgnd, GradientBackground::LineFieldMask);
        gbkgnd->addLine(Color3f(0.0/255.0, 3.0/255.0, 46.0/255.0), 0.0);
        gbkgnd->addLine(Color3f(112.0/255.0, 119.0/255.0, 193.0/255.0), 1.0);
    endEditCP  (gbkgnd, GradientBackground::LineFieldMask);

    // Viewport
    if(!mgr->getWindow()->getPort().empty())
    {
        ViewportPtr vp = mgr->getWindow()->getPort()[0];
        beginEditCP(vp);
            vp->setBackground(gbkgnd);
        endEditCP(vp);
    }
    
    // show the whole scene
    mgr->showAll();
    mgr->getNavigator()->setFrom(Pnt3f(0.0, 0.0, 1.0));

    // no headlight
    mgr->turnHeadlightOff();

    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

// redraw the window
void display(void)
{
    if(moveLight)
    {
        Real32 time = glutGet(GLUT_ELAPSED_TIME);
        Real32 lightRadius = 1;

        Vec3f t(lightRadius*sin(time / 1000), lightRadius*cos(time / 1000), 5.0);
        
        // Change position of light source
        beginEditCP(pl, PointLight::PositionFieldMask);
            pl->setPosition(t);
        endEditCP(pl, PointLight::PositionFieldMask);
    }

    // render scene
    mgr->redraw();
    // all done, swap    
    glutSwapBuffers();
  
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
void keyboard(unsigned char k, int /*x*/, int /*y*/)
{
    static bool wireframe = false;
    Pnt3f lpos;
    Vec3f t;
    Real32 step = 1.0;
    Color3f value;

    switch(k)
    {
        case 27:
        case 'q':
            exit(1);
        
        case 'w': // wireframe
            wireframe ^= 1;
            if(wireframe)
                glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
            else
                glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
        break;
            
        case 'l':
            moveLight ^= 1;
        break;
        
        case 'p':  // Enable phong shading
            beginEditCP(geo, Geometry::MaterialFieldMask);
                geo->setMaterial(pmat);
            endEditCP(geo, Geometry::MaterialFieldMask);
        break;
        
        case 'g': // Enable gouraud shading
            beginEditCP(geo, Geometry::MaterialFieldMask);
                geo->setMaterial(smat);
            endEditCP(geo, Geometry::MaterialFieldMask);
        break;
        
        case 54:  // (Right). Moving light to the right
            lpos = pl->getPosition();
            // Change position of light source
            t[0] = lpos[0] + 0.2;
            t[1] = lpos[1];
            t[2] = lpos[2];
            beginEditCP(pl);
                pl->setPosition(t);
            endEditCP(pl);
        break;
        
        case 52:  // (Left). Moving light to the left
            lpos = pl->getPosition();
            // Change position of light source
            t[0] = lpos[0] - 0.2;
            t[1] = lpos[1];
            t[2] = lpos[2];
            beginEditCP(pl);
                pl->setPosition(t);
            endEditCP(pl);
        break;
        
        case 56:  // (Up). Moving light to the up
            lpos = pl->getPosition();
            // Change position of light source
            t[0] = lpos[0];
            t[1] = lpos[1] + 0.2;
            t[2] = lpos[2];
            beginEditCP(pl);
                pl->setPosition(t);
            endEditCP(pl);
        break;
        
        case 50:  // (oDwn. Moving light to the left
            lpos = pl->getPosition();
            // Change position of light source
            t[0] = lpos[0];
            t[1] = lpos[1] - 0.2;
            t[2] = lpos[2];
            beginEditCP(pl);
                pl->setPosition(t);
            endEditCP(pl);
        break;
        
        case 93:  // }  Moving light forward
            lpos = pl->getPosition();
            // Change position of light source
            t[0] = lpos[0];
            t[1] = lpos[1];
            t[2] = lpos[2] + 0.2;
            beginEditCP(pl);
                pl->setPosition(t);
            endEditCP(pl);
        break;
        
        case 91:  // {  Moving light back
            lpos = pl->getPosition();
            // Change position of light source
            t[0] = lpos[0];
            t[1] = lpos[1];
            t[2] = lpos[2] - 0.2;
            beginEditCP(pl);
                pl->setPosition(t);
            endEditCP(pl);
        break;
    }

     glutPostRedisplay();
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    int winid = glutCreateWindow("OpenSG");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}
