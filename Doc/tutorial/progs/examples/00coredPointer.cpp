// all needed include files
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>

#include <OpenSG/OSGCoredNodePtr.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;
NodePtr scene;

typedef CoredNodePtr<Group> GroupNodePtr;
typedef CoredNodePtr<Geometry> GeometryNodePtr;

int setupGLUT( int *argc, char *argv[] );

NodePtr createScenegraph(){
	//create the torus geometry (core and geometry)
	GeometryNodePtr torus = GeometryNodePtr::create();
	torus = makeTorusGeo(0.5,2,8,12);
	
	//create box
	GeometryNodePtr box = GeometryNodePtr::create();
	box = makeBoxGeo(0.5,0.5,0.5,1,1,1);
	
	//create the group node and core
	GroupNodePtr root = GroupNodePtr::create();
	root = Group::create();
	
	//add the torus and box to the group node
	root.node()->addChild(torus);
	root.node()->addChild(box);
	
	addRefCP(torus.node());
	addRefCP(box.node());
	addRefCP(root.node());
	
	return root.node();
}

int main(int argc, char **argv)
{
    osgInit(argc,argv);
        
    int winid = setupGLUT(&argc, argv);

    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();
	
    scene = createScenegraph();

    mgr = new SimpleSceneManager;
    mgr->setWindow(gwin );
	mgr->setRoot  (scene);
    mgr->showAll();
    
    glutMainLoop();

    return 0;
}

void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}

void display(void)
{
        mgr->redraw();
}

void mouse(int button, int state, int x, int y)
{
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}

void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG First Application");
    
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);
    return winid;
}
