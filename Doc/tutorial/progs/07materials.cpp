// all needed include files
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGMaterialGroup.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;
NodePtr scene;

int setupGLUT( int *argc, char *argv[] );

NodePtr createScenegraph(){
    
    SimpleMaterialPtr simpleMaterial = SimpleMaterial::create();

    beginEditCP (simpleMaterial,    SimpleMaterial::DiffuseFieldMask |
                                    SimpleMaterial::AmbientFieldMask |
                                    SimpleMaterial::TransparencyFieldMask);
                
        simpleMaterial->setDiffuse(Color3f(1,0,0));
        simpleMaterial->setAmbient(Color3f(0.2, 0.2, 0.2));
        simpleMaterial->setTransparency(0.5);

    endEditCP   (simpleMaterial,    SimpleMaterial::DiffuseFieldMask |
                                    SimpleMaterial::AmbientFieldMask |
                                    SimpleMaterial::TransparencyFieldMask);
                                    
    NodePtr simpleMaterialNode = Node::create();
    NodePtr sphere = makeSphere(2,6);
    
    MaterialGroupPtr mg = MaterialGroup::create();
    beginEditCP(mg);
        mg->setMaterial(simpleMaterial);
    endEditCP(mg);
    
    beginEditCP(simpleMaterialNode);
        simpleMaterialNode->setCore(mg);
        simpleMaterialNode->addChild(sphere);
    endEditCP(simpleMaterialNode);
    
    NodePtr root = Node::create();
    
    beginEditCP(root);
        root->setCore(Group::create());
        root->addChild(simpleMaterialNode);
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
