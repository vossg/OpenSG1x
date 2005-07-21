#include <OSGConfig.h>

#include <iostream>
#include <ctype.h>
#include <OSGGLUT.h>

#include <OSGBaseFunctions.h>
#include <OSGSFSysTypes.h>
#include <OSGMFVecTypes.h>
#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGThread.h>
#include <OSGTransform.h>
#include <OSGAttachment.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>

#include <OSGSimpleMaterial.h>

#include <OSGWindow.h>
#include <OSGGLUTWindow.h>
#include <OSGImage.h>

#include <OSGGeometry.h>
#include <OSGSimpleGeometry.h>
#include <OSGMaterialGroup.h>

#include <OSGSimpleSceneManager.h>

OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

GLUTWindowPtr win;

void
display(void)
{
    mgr->redraw();
}

void key( unsigned char key, int, int )
{
    switch ( tolower( key ) )
    {
    case 27:    exit(0);
    }
}

// react to size changes
void resize( int w, int h )
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

int main (int argc, char **argv)
{
    // GLUT init
    osgInit(argc, argv);

    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    UInt32 id = glutCreateWindow("OpenSG");

    glutKeyboardFunc(key);
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    
    glutIdleFunc(display);

    // create the tree

    GroupNodePtr root = GroupNodePtr::create();
    
    {
    CPEditAll(root);
    
    MaterialGroupNodePtr mg1 = MaterialGroupNodePtr::create();

    root.node()->addChild(mg1);
    
    SimpleMaterialPtr green = SimpleMaterial::create();
    
    CPEditAll(green);
    green->setDiffuse(Color3f(0,1,0));
    
    CPEditAll(mg1);
    mg1->setMaterial(green);
    
    MaterialGroupNodePtr mg2 = MaterialGroupNodePtr::create();

    mg1.node()->addChild(mg2);
    
    SimpleMaterialPtr red = SimpleMaterial::create();
    
    CPEditAll(red);
    red->setDiffuse(Color3f(1,0,0));
    
    CPEditAll(mg2);
    mg2->setMaterial(red);
    
    GeometryNodePtr torus;
    torus = makeTorusGeo(.5, 2, 16, 16);

    mg2.node()->addChild(torus);
    }
    
    // 
    // The action

    win = GLUTWindow::create();
    win->setId(id);
    win->init();

    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(win);
    mgr->setRoot  (root);

    // show the whole scene
    mgr->showAll();

    glutMainLoop();
    
    return 0;
}

