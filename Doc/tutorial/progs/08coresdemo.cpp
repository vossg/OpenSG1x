// all needed include files
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>

//additional headder files
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGDistanceLOD.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;
NodePtr scene;

int setupGLUT( int *argc, char *argv[] );

NodePtr createScenegraph(){
    //At first we load all needed models from file
    NodePtr w_high = SceneFileHandler::the().read("data/woman_high.wrl");
    NodePtr w_medium = SceneFileHandler::the().read("data/woman_medium.wrl");
    NodePtr w_low = SceneFileHandler::the().read("data/woman_low.wrl");
    
    //we check the result
    if ((w_high == NullFC)&&(w_medium == NullFC)&&(w_low == NullFC)){
        std::cout << "It was not possible to load all needed models from file" << std::endl;
        return NullFC;
    }
    
    //now the LOD core
    DistanceLODPtr lod = DistanceLOD::create();
    beginEditCP(lod, DistanceLOD::CenterFieldMask | DistanceLOD::RangeFieldMask);
        lod->getSFCenter()->setValue(Pnt3f(0,0,0));
        lod->getMFRange()->push_back(200);
        lod->getMFRange()->push_back(500);
    endEditCP(lod, DistanceLOD::CenterFieldMask | DistanceLOD::RangeFieldMask);
    
    //the node containing the LOD core. The three models will be
    //added as its children
    NodePtr lodNode = Node::create();
    beginEditCP(lodNode);
        lodNode->setCore(lod);
        lodNode->addChild(w_high);
        lodNode->addChild(w_medium);
        lodNode->addChild(w_low);
    endEditCP(lodNode);
    
    NodePtr root = Node::create();
    beginEditCP(root);
        root->setCore(Group::create());
        root->addChild(lodNode);
    endEditCP(root);
    
    return root;
}

int main(int argc, char **argv)
{
    osgInit(argc,argv);
        
    int winid = setupGLUT(&argc, argv);
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();

    scene =createScenegraph();

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
