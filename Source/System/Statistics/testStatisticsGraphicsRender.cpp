#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGLog.h>

#include <OSGDrawable.h>
#include <OSGSimpleGeometry.h>
#include <OSGPassiveWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSceneFileHandler.h>

#include <OSGGraphicStatisticsForeground.h>
#include <OSGStatElemTypes.h>
#include <OSGStatCollector.h>

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
    NodePtr scene;
    
    if(argc > 1)
    {
        scene = SceneFileHandler::the().read(argv[1]);
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
    
    // show the whole scene
    mgr->showAll();

    // add the statistics forground
    
    GraphicStatisticsForegroundPtr statfg =
	  GraphicStatisticsForeground::create();

	Color4f lowColor(1.0 , 0.0 , 0.0, 0.75);
	Color4f currentColor(1.0 , 1.0 , 0.0 , 0.75);
	Color4f highColor(0.0 , 1.0 , 0.0 , 0.75);


	beginEditCP(statfg);
	
	statfg->addElement(RenderAction::statDrawTime,
					   GraphicStatisticsForeground::OSG_ANALOG,
					   Vec2f(0.0,0.0),
					   Vec2f(-1.0,0.25),
					   highColor,
					   lowColor,
					   currentColor,
					   0.0,
					   0.0,
					   GraphicStatisticsForeground::OSG_RECIPROC | 
             GraphicStatisticsForeground::OSG_OVERFLOW_RESIZE | 
             GraphicStatisticsForeground::OSG_SMOOTH,
					   100,
					   "FPS"
					   );
	statfg->addElement(RenderAction::statDrawTime,
                     GraphicStatisticsForeground::OSG_BAR,
					 //  GraphicStatisticsForeground::OSG_ANALOG,                     
					   Vec2f(0.0,-1.0),
					   Vec2f(0.4,0.2),
					   highColor,
					   lowColor,
					   currentColor,
					   0.0,
					   0.0,
					   GraphicStatisticsForeground::OSG_RECIPROC | 
             GraphicStatisticsForeground::OSG_OVERFLOW_RESIZE |
             GraphicStatisticsForeground::OSG_SMOOTH,
					   100,
					   "FPS"
					   );
	statfg->addElement(RenderAction::statDrawTime,
                     GraphicStatisticsForeground::OSG_LINE_CHART,
                     Vec2f(-1.0,0.0),
                     Vec2f(0.4,0.2),
                     highColor,
                     lowColor,
                     currentColor,
                     0.0,
                     0.0,
                     GraphicStatisticsForeground::OSG_RECIPROC | 
                     GraphicStatisticsForeground::OSG_OVERFLOW_RESIZE |
                     GraphicStatisticsForeground::OSG_SMOOTH | 
                     GraphicStatisticsForeground::OSG_ENABLE_POINTS |
                     GraphicStatisticsForeground::OSG_MAX_TEXT | 
                     GraphicStatisticsForeground::OSG_MIN_TEXT,
                     100,
                     "FPS"
                     );

	statfg->addElement(RenderAction::statDrawTime,
					   GraphicStatisticsForeground::OSG_CHART,
					   Vec2f(-1.0,-1.0),
					   Vec2f(0.4,0.2),
					   highColor,
					   lowColor,
					   currentColor,
					   0.0,
					   0.0,
					   GraphicStatisticsForeground::OSG_RECIPROC 
             | GraphicStatisticsForeground::OSG_OVERFLOW_RESIZE
					   | GraphicStatisticsForeground::OSG_SMOOTH,
					   100,
					   "FPS"
					   );


	//statfg->setLineWidth(2.0);
	
	//Color3f a(1.0,0.0,0.0);
	//statfg->setColorBackground(a);
	//	statfg->setBorderEnabled(false);
	//  statfg->setBackgroundEnabled(false);
    
    //statfg->setTextEnabled(false);
	/*
	statfg->addElement(DrawActionBase::statTravTime,
					   STATISTIK_CHART,
					   pos2,
					   size2,
					   highColor,
					   lowColor,
					   currentColor,
					   0.0,
					   0.0,
					   STATISTIK_RECIPROC | STATISTIK_OVERFLOW_RESIZE
					   | STATISTIK_SMOOTH,
					   
					   50);
	
	*/

	
	endEditCP(statfg);

    /*
	  beginEditCP(statfg);
	  statfg->setSize(25);
	  statfg->setColor(Color4f(0,1,0,0.7));
	  statfg->addElement(RenderAction::statDrawTime, "Draw FPS: %r.3f");
	  statfg->addElement(DrawActionBase::statTravTime, "TravTime: %.3f s");
	  statfg->addElement(RenderAction::statDrawTime, "DrawTime: %.3f s");
	  statfg->addElement(DrawActionBase::statCullTestedNodes, 
	  "%d Nodes culltested");
	  statfg->addElement(DrawActionBase::statCulledNodes, 
	  "%d Nodes culled");
	  statfg->addElement(RenderAction::statNMaterials, 
	  "%d material changes");
	  statfg->addElement(RenderAction::statNMatrices, 
	  "%d matrix changes");
	  statfg->addElement(RenderAction::statNGeometries, 
	  "%d Nodes drawn");
	  statfg->addElement(RenderAction::statNTransGeometries, 
	  "%d transparent Nodes drawn");
	  statfg->addElement(Geometry::statNTriangles, 
	  "%d triangles drawn");
	  statfg->addElement(Geometry::statNLines, 
	  "%d lines drawn");
	  statfg->addElement(Geometry::statNPoints, 
	  "%d points drawn");
	  statfg->addElement(Geometry::statNVertices, 
	  "%d vertices transformed");
	  endEditCP(statfg);
	  
	  collector = &statfg->getCollector();
		  
	  // add optional elements
	  collector->getElem(Geometry::statNTriangles);
	  
	  mgr->getAction()->setStatistics(collector);
	*/
	
	collector = &statfg->getCollector();
    collector->getElem(Drawable::statNTriangles);
    mgr->getAction()->setStatistics(collector);

    beginEditCP(pwin->getPort(0));
    pwin->getPort(0)->getForegrounds().push_back(statfg);
    endEditCP  (pwin->getPort(0));
    
    // GLUT main loop
    glutMainLoop();

    return 0;
}
