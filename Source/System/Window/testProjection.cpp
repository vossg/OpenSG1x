
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGPassiveWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSceneFileHandler.h>

#include <OSGPerspectiveCamera.h>
#include <OSGStereoBufferViewport.h>
#include <OSGProjectionCameraDecorator.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

Real32 ed = 1;

TransformPtr usertrans;

StereoCameraDecoratorPtr decos[6];

int width,height;

// redraw the window
void display(void)
{   
    glViewport(0,0,width,height);
    glClear(GL_COLOR_BUFFER_BIT);
    
    mgr->redraw();

    // all done, swap    
    glutSwapBuffers();
}

// react to size changes
void reshape(int w, int h)
{
    width = w;
    height = h;
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
    case 'z':   ed = ed ? ed / 1.1 : 1;
                break;
    case 'x':   ed = ed ? ed * 1.1 : 1;
                break;         
    case 'm':   ed = 0;
                break;         
    }
    
    std::cout << " ED:" << ed << std::endl;
    
    for (int i = 0; i < 6; ++i)
    {
        beginEditCP(decos[i]);
        decos[i]->setEyeSeparation(ed);
        endEditCP  (decos[i]);
    }
 }


int main(int argc, char **argv)
{
    osgInit(argc,argv);

    // GLUT init
    glutInit(&argc, argv);
    
    bool stereobuffer = false;
    if(argc >= 2 && !strcmp(argv[1],"-s"))
    {
        stereobuffer = true;
        argc--;
        argv++;
    }
    
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE |
                        (stereobuffer?GLUT_STEREO:0) );
    
    glutInitWindowSize(400,300);
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
    
    if(argc > 1)
    {
        scene = SceneFileHandler::the().read(argv[1]);
    }
    else
    {
        scene = makeBox(2,2,2, 1,1,1);
        GeometryPtr geo = GeometryPtr::dcast(scene->getCore());
        beginEditCP(geo);
        geo->setMaterial(getDefaultUnlitMaterial());
        endEditCP(geo);
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    }
    
    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // create the window and initial camera/viewport
    mgr->setWindow(pwin );
    // tell the manager what to manage
    mgr->setRoot  (scene);
    
    // now crete the second vp for stereo
    ViewportPtr vp = pwin->getPort(0);
    
    // create the decorators and the second viewport
    Pnt4f vppos[6] = {  Pnt4f(.25,.33,.50,.66),  // front
                        Pnt4f(.75,.33,1. ,.66),  // back
                        Pnt4f(0. ,.33,.25,.66),  // left
                        Pnt4f(.50,.33,.75,.66),  // right
                        Pnt4f(.25,0. ,.50,.33),  // bottom
                        Pnt4f(.25,.66,.50,1. )   // top
                      };
#if 1                     
    Pnt3f vpproj[6][4] = { 
        { Pnt3f(-1,-1,-1), Pnt3f( 1,-1,-1), Pnt3f( 1, 1,-1), Pnt3f(-1, 1,-1)},
        { Pnt3f( 1,-1, 1), Pnt3f(-1,-1, 1), Pnt3f(-1, 1, 1), Pnt3f( 1, 1, 1)},
        { Pnt3f(-1,-1, 1), Pnt3f(-1,-1,-1), Pnt3f(-1, 1,-1), Pnt3f(-1, 1, 1)},
        { Pnt3f( 1,-1,-1), Pnt3f( 1,-1, 1), Pnt3f( 1, 1, 1), Pnt3f( 1, 1,-1)},
        { Pnt3f(-1,-1, 1), Pnt3f( 1,-1, 1), Pnt3f( 1,-1,-1), Pnt3f(-1,-1,-1)},
        { Pnt3f(-1, 1,-1), Pnt3f( 1, 1,-1), Pnt3f( 1, 1, 1), Pnt3f(-1, 1, 1)}
        };
#else                        
    Pnt3f vpproj[6][4] = { 
        { Pnt3f(-1,-1,-1), Pnt3f( 1,-1,-1), Pnt3f( 1, 1,-1), Pnt3f(-1, 1,-1)},
        { Pnt3f( 3,-1,-1), Pnt3f( 5,-1,-1), Pnt3f( 5, 1,-1), Pnt3f( 3, 1,-1)},
        { Pnt3f(-3,-1,-1), Pnt3f(-1,-1,-1), Pnt3f(-1, 1,-1), Pnt3f(-3, 1,-1)},
        { Pnt3f( 1,-1,-1), Pnt3f( 3,-1,-1), Pnt3f( 3, 1,-1), Pnt3f( 1, 1,-1)},
        { Pnt3f(-1,-3,-1), Pnt3f( 1,-3,-1), Pnt3f( 1,-1,-1), Pnt3f(-1,-1,-1)},
        { Pnt3f(-1, 1,-1), Pnt3f( 1, 1,-1), Pnt3f( 1, 3,-1), Pnt3f(-1, 3,-1)},
        };
#endif

    usertrans = Transform::create();   
    beginEditCP(usertrans);
    usertrans->setMatrix(Matrix::identity());
    endEditCP  (usertrans);
    
    NodePtr tnode = Node::create();
    beginEditCP(tnode);
    tnode->setCore(usertrans);
    endEditCP  (tnode);
    
    PerspectiveCameraPtr cam = PerspectiveCameraPtr::dcast(vp->getCamera());
    beginEditCP(cam->getBeacon());
    cam->getBeacon()->addChild(tnode);
    endEditCP  (cam->getBeacon());
    
 
    beginEditCP(pwin); 
    pwin->subPort(vp);  
       
    for(UInt16 i = 0; i < 6; ++i)
    {
        ProjectionCameraDecoratorPtr d = ProjectionCameraDecorator::create();
        
        decos[i] = d;
        
        beginEditCP(d);
        d->setEyeSeparation(ed);
        d->setLeftEye(true);  
        d->setUser(tnode);  
        d->setDecoratee(cam);  
        d->getSurface().push_back(vpproj[i][0]);
        d->getSurface().push_back(vpproj[i][1]);
        d->getSurface().push_back(vpproj[i][2]);
        d->getSurface().push_back(vpproj[i][3]);
        endEditCP  (d);
        
        ViewportPtr v = Viewport::create();
        
        beginEditCP(v);
        v->setLeft(vppos[i][0]);
        v->setRight(vppos[i][2]);
        v->setBottom(vppos[i][1]);
        v->setTop(vppos[i][3]);
        v->setCamera(d);
        v->setBackground(vp->getBackground());
        v->setRoot(vp->getRoot());        
        endEditCP  (v);
        
        pwin->addPort(v);
    }
    
    endEditCP  (pwin);
    
    // make it notice the changes
    mgr->setWindow(pwin );
    
    // show the whole scene
    mgr->showAll();

    Navigator *nav = mgr->getNavigator();
    nav->setAt(Pnt3f(0,0,0));
    nav->setDistance(2);
    
    beginEditCP(cam);
    cam->setNear(0.1);
    cam->setFar (2000);
    endEditCP  (cam);
    
    // GLUT main loop
    glutMainLoop();

    return 0;
}
