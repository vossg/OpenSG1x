
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGPassiveWindow.h>
#include <OSGSimpleSceneManager.h>

#include <OSGSceneFileHandler.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

// redraw the window
void display(void)
{   
    mgr->redraw();
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
    NodePtr leftscene, rightscene;
    
    if(argc > 2)
    {
        leftscene = SceneFileHandler::the().read(argv[1]);
        rightscene = SceneFileHandler::the().read(argv[2]);
    }
    else
    {
        leftscene = makeBox(2,2,2, 1,1,1);
        rightscene = makeTorus(.5, 2, 16, 16);
    }

    leftscene->setTravMask(0x1);
    rightscene->setTravMask(0x2);
    
    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // create the window and initial camera/viewport
    mgr->setWindow(pwin );
    // tell the manager what to manage
    NodePtr scene = Node::create();
    GroupPtr gcore = Group::create();
    
    beginEditCP(scene);
    scene->setCore(gcore);
    scene->addChild(leftscene);
    scene->addChild(rightscene);
    endEditCP(scene);
    
    mgr->setRoot  (scene);
     
    mgr->showAll();
   
    // now create the second vp
    ViewportPtr vp = pwin->getPort(0);
           
    ViewportPtr vpright = Viewport::create();

    beginEditCP(vp);
    vp->setLeft(0);
    vp->setRight(0.5);
    vp->setBottom(0);
    vp->setTop(1);
    vp->setTravMask(0x1);
    endEditCP  (vp);

    beginEditCP(vpright);
    vpright->setLeft(0.5);
    vpright->setRight(1);
    vpright->setBottom(0);
    vpright->setTop(1);
    vpright->setBackground(vp->getBackground());
    vpright->setRoot(vp->getRoot());
    vpright->setCamera(vp->getCamera());
    vpright->setTravMask(0x2);
    endEditCP  (vpright);

    beginEditCP(pwin); 
    pwin->addPort(vpright);  
    endEditCP  (pwin); 

    // make it notice the changes
//    mgr->setWindow(pwin);
    
    // show the whole scene
    mgr->showAll();
    
    // GLUT main loop
    glutMainLoop();

    return 0;
}
