
#include <OSGGLUT.h>

#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGPassiveWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGTransform.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;
TransformNodePtr trans;

int width,height;

// redraw the window
void display(void)
{
    Real32 f = glutGet(GLUT_ELAPSED_TIME);
    
    // do OpenGL stuff
    
    glClearColor(0,1,0,0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glColor3f(fmod(f/800,1), fmod(f/1500,1), fmod(f/2000,1));
    
    glPushMatrix();
    glRotatef( f/100, 0,0,1);
    glBegin(GL_QUADS);
    glVertex2f(-.8, -.8);
    glVertex2f( .8, -.8);
    glVertex2f( .8,  .8);
    glVertex2f(-.8,  .8);
    glEnd();
    glPopMatrix();
    
    // now do the OpenSG part
    
    // Move the object a little
    
    beginEditCP(trans);
    Matrix m;
    m.setTransform(Vec3f(sin(f/100), 0, cos(f/100)));
    trans->setMatrix(m);
    endEditCP(trans);

    // and draw it
    
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);     
    // you should only push what you need yourself here
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    
    mgr->redraw();

    glPopAttrib();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    // And a little more OpenGL

    NodePtr node = trans.node()->getChild(0);
    
    ViewportPtr port = mgr->getWindow()->getPort(0);
    CameraPtr cam = port->getCamera();
    int w = port->getPixelWidth(), h = port->getPixelHeight();
    Matrix proj, view;
    
    cam->getProjection(proj, w, h);
    cam->getViewing(view, w, h);
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadMatrixf(proj.getValues());
    
    glMatrixMode(GL_MODELVIEW);     
    glPushMatrix();
    glLoadMatrixf(view.getValues());
    glMultMatrixf(node->getToWorld().getValues());

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glViewport(0,0,w,h);

    
    Pnt3f low, high;
    node->getVolume().getBounds(low,high);
    
    glColor3f(fmod(f/2000,1), fmod(f/1500,1), fmod(f/800,1));
    
    glBegin(GL_LINE_LOOP);
    glVertex3f( low[0],  low[1],  low[2]);
    glVertex3f(high[0],  low[1],  low[2]);
    glVertex3f(high[0], high[1],  low[2]);
    glVertex3f( low[0], high[1],  low[2]);
    glVertex3f( low[0],  low[1],  low[2]);

    glVertex3f( low[0],  low[1], high[2]);
    glVertex3f(high[0],  low[1], high[2]);
    glVertex3f(high[0], high[1], high[2]);
    glVertex3f( low[0], high[1], high[2]);
    glVertex3f( low[0],  low[1], high[2]);    
    glEnd();
    
    glBegin(GL_LINES);
    glVertex3f(high[0],  low[1],  low[2]);
    glVertex3f(high[0],  low[1], high[2]);
    
    glVertex3f(high[0], high[1],  low[2]);
    glVertex3f(high[0], high[1], high[2]);
    
    glVertex3f( low[0], high[1],  low[2]);
    glVertex3f( low[0], high[1], high[2]);
    glEnd();

    glPopAttrib();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    
    // all done, swap    
    glutSwapBuffers();
}

// react to size changes
void reshape(int w, int h)
{
    width=w;
    height=h;
    glViewport(width/2,0,width,height);
    // make sure the OpenSG window knows about resizes
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
    
    trans = Transform::create();
    
    NodePtr scene = makeTorus(.5, 2, 16, 16);

    beginEditCP(trans.node());
    trans.node()->addChild(scene);
    endEditCP(trans.node());
    
    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(pwin );
    mgr->setRoot  (trans.node());
    
    // take the viewport  and make it smaller
    ViewportPtr vp = pwin->getPort(0);
    
    beginEditCP(vp);
    vp->setLeft(0);
    vp->setRight(0.5);
    vp->setBottom(0);
    vp->setTop(1);
    endEditCP  (vp);
    
    // show the whole scene
    mgr->showAll();
    
    // GLUT main loop
    glutMainLoop();

    return 0;
}
