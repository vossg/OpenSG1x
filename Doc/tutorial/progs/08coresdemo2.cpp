// all needed include files
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>

//additional headder files
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGDistanceLOD.h>
#include <OpenSG/OSGSwitch.h>
#include <OpenSG/OSGSimpleAttachments.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;
NodePtr scene;

int setupGLUT( int *argc, char *argv[] );

// this function will return the node named "FACESET_Woman"
// if there is no such node NullFC will be returned
NodePtr checkName(NodePtr n){
    UInt32 children = n->getNChildren();
    
    //make sure a name existes
    if (getName(n))
        //check if it is the name we are looking for
        if (getName(n)== std::string("FACESET_Woman"))
            // We got the node!
            return n;
    
    //check all children
    for (int i = 0; i < children; i++){
        NodePtr r = checkName(n->getChild(i));
        if (r != NullFC)
            // if it is not NullFC it is the node we are looking for
            // so just pass it through
            return r;
    }
    // no children's name matches or there are no more childs
    // so return NullFC, indicating that the node was not found yet
    return NullFC;
}

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
    
        //create the node with switch core ********************
    SwitchPtr sw = Switch::create();
    beginEditCP(sw, Switch::ChoiceFieldMask);
        //Notice: the first choice is 0
        sw->setChoice(0);
    endEditCP(sw, Switch::ChoiceFieldMask);
    
    NodePtr switchNode = Node::create();
    beginEditCP(switchNode);
        switchNode->setCore(sw);
        switchNode->addChild(lodNode);
    endEditCP(switchNode);
    
    //end witch creation **********************************
    
    NodePtr root = Node::create();
    beginEditCP(root);
        root->setCore(Group::create());
        root->addChild(switchNode);
    endEditCP(root);
    
    // we know want to extract the mesh geometry out of the graph
    // it is sufficent to pass the model only as root for searching
    NodePtr womanGeometry = checkName(w_high);
    GeometryPtr geo = GeometryPtr::dcast(womanGeometry->getCore());
    
    // generating a material *********************************
    
    SimpleMaterialPtr mat = SimpleMaterial::create();
    beginEditCP(mat);
        mat->setAmbient(Color3f(0.2,0.2,0.2));
        mat->setDiffuse(Color3f(0.6,0.3,0.1));
        mat->setSpecular(Color3f(1,1,1));
        mat->setShininess(0.8);
    endEditCP(mat);
    
    beginEditCP(geo, Geometry::MaterialFieldMask);
        geo->setMaterial(mat);
    endEditCP(geo, Geometry::MaterialFieldMask);
    
    // end material generation *******************************
    
    //new node with "old" geometry core referenced
    NodePtr woman = Node::create();
    beginEditCP(woman);
        woman->setCore(geo);
    endEditCP(woman);
    
    //translate it a bit to see both women
    NodePtr womanTrans = Node::create();
    TransformPtr t = Transform::create();
    beginEditCP(t);
        Matrix m;
        m.setIdentity();
        m.setTranslate(Vec3f(0,0,200));
        t->setMatrix(m);
    endEditCP(t); 
    beginEditCP(womanTrans);
        womanTrans->setCore(t);
        womanTrans->addChild(woman);
    endEditCP(womanTrans);
    
    //add it to the root
    beginEditCP(root);
        root->addChild(womanTrans);
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
