
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGPassiveWindow.h>
#include <OSGSimpleSceneManager.h>

#include <OSGPerspectiveCamera.h>
#include <OSGStereoBufferViewport.h>
#include <OSGShearedStereoCameraDecorator.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

ShearedStereoCameraDecoratorPtr decoleft, decoright;
Real32 zpp = 2, ed = 1;

// redraw the window
void display(void)
{   
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
    case 'a':   zpp /= 1.1;
                break;
    case 's':   zpp *= 1.1;
                break;
    case 'z':   ed /= 1.1;
                break;
    case 'x':   ed *= 1.1;
                break;         
    }
    
    cout << "ZPP:" << zpp << " ED:" << ed << endl;
    
    beginEditCP(decoleft);
    decoleft->setEyeSeparation(ed);
    decoleft->setZeroParallaxDistance(zpp);
    endEditCP  (decoleft);
    
    beginEditCP(decoright);
    decoright->setEyeSeparation(ed);
    decoright->setZeroParallaxDistance(zpp);
    endEditCP  (decoright);
}


int main(int argc, char **argv)
{
    osgInit(argc,argv);

    // GLUT init
    glutInit(&argc, argv);
    
    bool stereobuffer = false;
    if(argc >= 2 && !strcmp(argv[1],"-s"))
        stereobuffer = true;
    
    
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE |
                        (stereobuffer?GLUT_STEREO:0) );
    
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
    NodePtr scene = makeBox(2,2,2, 1,1,1);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // create the window and initial camera/viewport
    mgr->setWindow(pwin );
    // tell the manager what to manage
    mgr->setRoot  (scene);
    
    // now crete the second vp for stereo
    ViewportPtr vp = pwin->getPort(0);
    
    PerspectiveCameraPtr cam = PerspectiveCameraPtr::dcast(vp->getCamera());
    beginEditCP(cam);
    cam->setFov(deg2rad(90));
    endEditCP  (cam);

    Navigator *nav = mgr->getNavigator();
    nav->setAt(Pnt3f(0,0,0));
    nav->setDistance(1.5);
    
    // create the decorators and the second viewport
    ViewportPtr vpleft,vpright;
       
    decoleft = ShearedStereoCameraDecorator::create();
    decoright = ShearedStereoCameraDecorator::create();
    
    beginEditCP(decoleft);
    decoleft->setEyeSeparation(ed);
    decoleft->setZeroParallaxDistance(zpp);
    decoleft->setLeftEye(true);  
    decoleft->setDecoratee(cam);  
    endEditCP  (decoleft);
    
    beginEditCP(decoright);
    decoright->setEyeSeparation(ed);
    decoright->setZeroParallaxDistance(zpp);
    decoright->setLeftEye(false);  
    decoright->setDecoratee(cam);  
    endEditCP  (decoright);

    if(stereobuffer)
    {
        StereoBufferViewportPtr svpleft = StereoBufferViewport::create();
        StereoBufferViewportPtr svpright = StereoBufferViewport::create();
 
        beginEditCP(svpleft);
        svpleft->setLeft(0);
        svpleft->setRight(1);
        svpleft->setBottom(0);
        svpleft->setTop(1);
        svpleft->setCamera(decoleft);
        svpleft->setBackground(vp->getBackground());
        svpleft->setRoot(vp->getRoot());
        svpleft->setLeftBuffer(true);
        svpleft->setRightBuffer(false);
        endEditCP  (svpleft);
 
        beginEditCP(svpright);
        svpright->setLeft(0);
        svpright->setRight(1);
        svpright->setBottom(0);
        svpright->setTop(1);
        svpright->setCamera(decoright);
        svpright->setBackground(vp->getBackground());
        svpright->setRoot(vp->getRoot());
        svpright->setLeftBuffer(false);
        svpright->setRightBuffer(true);
        endEditCP  (svpright);
        
        vpleft = svpleft;
        vpright = svpright;
    }
    else
    {
        vpleft = vp;
        vpright = Viewport::create();

        beginEditCP(vpleft);
        vpleft->setLeft(0);
        vpleft->setRight(1);
        vpleft->setBottom(0);
        vpleft->setTop(0.5);
        endEditCP  (vpleft);

        beginEditCP(vpright);
        vpright->setLeft(0);
        vpright->setRight(1);
        vpright->setBottom(0.5);
        vpright->setTop(1);
        vpright->setBackground(vp->getBackground());
        vpright->setRoot(vp->getRoot());
        endEditCP  (vpright);
    }
    
    beginEditCP(vpleft);
    vpleft->setCamera(decoleft);
    endEditCP  (vpleft);
    
    beginEditCP(vpright);
    vpright->setCamera(decoright);
    endEditCP  (vpright);
 
    beginEditCP(pwin); 
    pwin->subPort(vp);  
    pwin->addPort(vpleft);  
    pwin->addPort(vpright);  
    endEditCP  (pwin); 

    // make it notice the changes
    mgr->setWindow(pwin );
    
    // show the whole scene
    mgr->showAll();
    
    // GLUT main loop
    glutMainLoop();

    return 0;
}
