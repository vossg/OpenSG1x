// OpenSG Tutorial Example: LinearCombinerGeometry
//
// Demonstrates the use of LinearCombinerGeometry Node
// 

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGLinearCombinerGeometry.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;
NodePtr	scene;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

int main(int argc, char **argv)
{
    osgInit(argc,argv);
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();

    // create the scene
    NodePtr torus1 = makeTorus(1, 2, 16, 16);
    NodePtr torus2 = makeTorus(.5, 2, 16, 16);
    
    scene = createLinearCombinerStructure(torus1);
    addToLinearCombinerStructure(torus2, scene);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);
    mgr->setHighlight(scene);


    // show the whole scene
    mgr->showAll();
    
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

void idle(void)
{
	static float angle=0.0;
	
	float w = (sin(angle)/2.0)+0.5;
	angle += 0.01;
	
	// change weights and redraw	
	std::vector<LinearCombinerGeometryPtr> cores;
	getLinearCombinerCores(cores, scene);
	
	for(int index = 0; index < cores.size(); index++)
	{
		LinearCombinerGeometryPtr lingeo = cores[index];
		
		beginEditCP(lingeo, LinearCombinerGeometry::WeightsFieldMask);	
		{
			lingeo->getWeights()[0] = w;
			lingeo->getWeights()[1] = 1.0-w;	
		}
		endEditCP(lingeo, LinearCombinerGeometry::WeightsFieldMask);	
	}
	
	glutPostRedisplay();
}

// redraw the window
void display(void)
{
    mgr->redraw();
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
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    return winid;
}
