// all needed include files
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;
NodePtr scene;
TransformPtr planetTransform;
TransformPtr moonTransform;

int setupGLUT( int *argc, char *argv[] );

NodePtr createScenegraph(){

    //create sun, planet & moon geometry

    GeometryPtr sun = makeSphereGeo(3, 6);
    NodePtr planet = makeSphere(3, 3);
    NodePtr moon = makeSphere(2,1);
        
    //the root node will be the sun
    NodePtr root = Node::create();
    beginEditCP(root, Node::CoreFieldMask);
        root->setCore(sun);
    endEditCP(root, Node::CoreFieldMask);
        
    NodePtr planetTransformNode = Node::create();
    NodePtr moonTransformNode = Node::create();

    // these were declared globally
    planetTransform = Transform::create();
    moonTransform = Transform::create();
        
    // Now we need to fill it with live
    // We want to have the planet some distance away from the sun, 
    // but initial with no rotation. The same aplies to the moon
    Matrix m,n;
        
    m.setIdentity();
    n.setIdentity();
        
    m.setTranslate(20,0,0);
    n.setTranslate(8,0,0);
        
    beginEditCP(planetTransform, Transform::MatrixFieldMask);
        planetTransform->setMatrix(m);
    endEditCP(planetTransform, Transform::MatrixFieldMask);
        
    beginEditCP(moonTransform, Transform::MatrixFieldMask);
        moonTransform->setMatrix(n);
    endEditCP(moonTransform, Transform::MatrixFieldMask);
        
    //Insert the cores into the apropiate nodes and add the geometry
    beginEditCP(planetTransformNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        planetTransformNode->setCore(planetTransform);
        planetTransformNode->addChild(planet);
    endEditCP(planetTransformNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        
    beginEditCP(moonTransformNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        moonTransformNode->setCore(moonTransform);
        moonTransformNode->addChild(moon);
    endEditCP(moonTransformNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        
    //add the planet to the sun
    beginEditCP(root, Node::ChildrenFieldMask);
        root->addChild(planetTransformNode);
        root->addChild(moonTransformNode);
    endEditCP(root, Node::ChildrenFieldMask);
        
    //now we are done
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
    Real32 time = glutGet(GLUT_ELAPSED_TIME );
    
    //create the Quaternion the describes the rotation of
    //the planet around the sun
    Quaternion planetRot = Quaternion(Vec3f(0,1,0), time/float(1000));
    
    //now the rotation of the moon around the planet
    //the division by 12 speeds up the rotation by 12 compared to the
    //planet rotation
    Quaternion moonRot = Quaternion(Vec3f(0,1,0), time/float(1000/12));
    
    //generate the Matrices
    Matrix p,m,t1,r1,t2,r2;
    
    t1.setTransform(Vec3f(20,0,0));
    r1.setTransform(planetRot);
    r1.mult(t1);
    p.setValue(r1);
    
    t2.setTransform(Vec3f(8,0,0));
    r2.setTransform(moonRot);
    r2.mult(t2);
    r1.mult(r2);
    m.setValue(r1);

    beginEditCP(planetTransform, Transform::MatrixFieldMask);
        planetTransform->setMatrix(p);
    endEditCP(planetTransform, Transform::MatrixFieldMask);
    
    beginEditCP(moonTransform, Transform::MatrixFieldMask);
        moonTransform->setMatrix(m);
    endEditCP(moonTransform, Transform::MatrixFieldMask);
    
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
