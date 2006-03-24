
// This is not actually a special Inventor test program, as the Inventor loader
// integrated itself into the SceneFileHandler, but I needed an example program
// here.

#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGPassiveWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSceneFileHandler.h>

#include <OSGDrawable.h>
#include <OSGSimpleStatisticsForeground.h>
#include <OSGStatElemTypes.h>
#include <OSGStatCollector.h>
#include <OSGGradientBackground.h>
#include <OSGPerfSceneFileType.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

StatCollector *collector;

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
        case 27:    
        {
            osgExit();
            exit(0);
        }
        
        case 'v':
        {
            mgr->getAction()->setVolumeDrawing(
                                    !mgr->getAction()->getVolumeDrawing());
		    std::cerr << "Volume Drawing: " 
                      << (mgr->getAction()->getVolumeDrawing()?"on":"off") 
                      << std::endl;
        }
        break;
        
        case 'w':
        {
            std::cerr << "Writing osb...";
            SceneFileHandler::the().write(mgr->getRoot(), "test.osb");
            std::cerr << "done." << std::endl;

        }
        break;
        
        case 'W':
        {
            std::cerr << "Writing osg...";
            SceneFileHandler::the().write(mgr->getRoot(), "test.osg");
            std::cerr << "done." << std::endl;

        }
        break;
    }
}


int main(int argc, char **argv)
{
    osgInit(argc,argv);

    // GLUT init
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    glutInitWindowSize(500, 500);
    glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    PassiveWindowPtr pwin=PassiveWindow::create();
    pwin->init();

    if(argc > 1 && !strcmp(argv[1], "-a"))
    {
        SceneFileType *sft = SceneFileHandler::the().getFileType("pfb");
        PerfSceneFileType *pft = dynamic_cast<PerfSceneFileType *>(sft);
        
        pft->setHighestLODOnly(false);
        
        argc--;
        argv++;
    }

    // create the scene
    NodePtr scene;
    
    if(argc > 1)
    {
        scene = Node::create();
        GroupPtr g = Group::create();
        
        beginEditCP(scene);
        scene->setCore(g);
        
        for(UInt16 i = 1; i < argc; ++i)
            scene->addChild(SceneFileHandler::the().read(argv[i]));
        
        endEditCP(scene);
    }
    else
    {
        scene = makeTorus(.5, 3, 16, 16);
    }

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // create the window and initial camera/viewport
    mgr->setWindow(pwin );
    // tell the manager what to manage
    mgr->setRoot  (scene);


    // Background
    GradientBackgroundPtr gbkgnd = GradientBackground::create();

    beginEditCP(gbkgnd, GradientBackground::LineFieldMask);
    gbkgnd->addLine( Color3f(.7,.7,1.), 0.0 );
    gbkgnd->addLine( Color3f(0, 0, 1), 0.5 );
    gbkgnd->addLine( Color3f(0, 0, .2), 1.0 );
    endEditCP  (gbkgnd, GradientBackground::LineFieldMask);
    
    mgr->getWindow()->getPort(0)->setBackground(gbkgnd);
    
    // show the whole scene
    mgr->showAll();
    
    mgr->setStatistics(true);
  
    // GLUT main loop
    glutMainLoop();

    return 0;
}
