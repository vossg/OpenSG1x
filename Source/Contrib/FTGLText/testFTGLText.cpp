// OpenSG Example: Text
//

// GLUT is used for window handling
#include <OSGGLUT.h>

// General OpenSG configuration, needed everywhere
#include <OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OSGSimpleGeometry.h>

// The GLUT-OpenSG connection class
#include <OSGGLUTWindow.h>

// A little helper to simplify scene management and interaction
#include <OSGSimpleSceneManager.h>

#include <OSGSimpleGeometry.h>
#include <OSGSceneFileHandler.h>


#include <OSGFTGLFont.h>
#include <OSGFTGLText.h>


//#include "OSGText.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
GLUTWindowPtr gwin2;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );



// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    glutInit(&argc, argv);
    osgInit(argc, argv);

    std::string fontfile("testfont.ttf");
    std::string testtext("Test Text");
    UInt32 drawmode;
    
    if(argc > 1)
        testtext = argv[1];
    if(argc > 2)
        fontfile = argv[2];
    if(argc < 4 || sscanf(argv[3], "%d", &drawmode) != 1 )
        drawmode = FTGLFont::Outline;
        
    // GLUT 
    int winid = setupGLUT(&argc, argv);
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();
   
    
    // Create the Cubes node

    NodePtr scene = makeCoredNode<Group>();

    beginEditCP(scene);
    
    scene->addChild( makeBox(200,200,200, 1,1,1) );
//    scene->addChild( SceneFileHandler::the().read("tie.wrl") );
    endEditCP(scene);


    // Create the text
    
    FTGLFontPtr font = FTGLFont::create();
    
    beginEditCP(font);
    font->setName(fontfile);
    font->setDrawType(drawmode);
    font->setSize(40);
    font->setRes(72);
    font->setDepth(20);
    endEditCP(font);

    FTGLTextPtr text;
    NodePtr tnode = makeCoredNode<FTGLText>(&text);
    
    beginEditCP(text);
    text->setFont(font);
    text->setText(testtext);
    text->setPosition(Pnt3f(0,300,0));
    text->setMaterial(getDefaultMaterial());      
    endEditCP(text);
    

    beginEditCP(scene);
    scene->addChild(tnode);
    endEditCP(scene);
    
    
    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();
        
    // copy to second window 
    int winid2 = setupGLUT(&argc, argv);
    gwin2= GLUTWindow::create();
    gwin2->setId(winid2);
    gwin2->init();
    
    ViewportPtr ovp = gwin->getPort()[0];
    
    ViewportPtr vp = Viewport::create();
    
    beginEditCP(vp);
    vp->setLeft(0);
    vp->setRight(400);
    vp->setBottom(0);
    vp->setTop(400);
    vp->setCamera(ovp->getCamera());
    vp->setRoot(ovp->getRoot());
    vp->setBackground(ovp->getBackground());
    vp->setParent(gwin2);
    endEditCP(vp);
    
    beginEditCP(gwin2);
    gwin2->getPort().push_back(vp);
    endEditCP(gwin2);
    
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
    mgr->redraw();
    
    gwin2->render(dynamic_cast<RenderAction*>(mgr->getAction()));
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
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
    case 27:    exit(1);
    }
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}
