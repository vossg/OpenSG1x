
#include <OSGGLUT.h>
#include <OSGGLEXT.h>
#include <OSGConfig.h>
#include <OSGTime.h>
#include <OSGSimpleGeometry.h>
#include <OSGPassiveWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSceneFileHandler.h>

#include <OSGSimpleMaterial.h>
#include <OSGTextureChunk.h>
#include <OSGImage.h>
#include <OSGTexGenChunk.h>

#include <OSGWebInterface.h>


OSG_USING_NAMESPACE
using namespace std;

SimpleSceneManager *mgr;
WebInterface *webInterface;

TextureChunkPtr tx1,tx2;
TransformPtr trans1,trans2;
NodePtr transn1,transn2;
TexGenChunkPtr tg;

bool animate = true;

// redraw the window
void display(void)
{      
    Matrix m;
    Real32 t = glutGet(GLUT_ELAPSED_TIME );
    
    if(animate)
    {
        m.setTransform(Vec3f(      osgsin(t / 1000.f), 
                                   osgcos(t / 1000.f), 
                                   osgsin(t / 1000.f)),
                       Quaternion( Vec3f(0,1,0), 
                                   t / 1000.f),
                       Vec3f(      osgsin(t / 900.f)*.5+.7, 
                                   osgcos(t / 900.f)*.5+.7, 
                                   osgsin(t / 900.f)*.5+.7));   

        beginEditCP(trans1, Transform::MatrixFieldMask);
        {
            trans1->setMatrix(m);
        }   
        endEditCP  (trans1, Transform::MatrixFieldMask);

        m.setTransform(Vec3f(      osgsin(t / 500.f), 
                                   osgcos(t / 500.f), 
                                   osgsin(t / 500.f)),
                       Quaternion( Vec3f(0,1,0), 
                                   t / 1000.f),
                       Vec3f(      osgsin(t / 400.f)*.5+.7, 
                                   osgcos(t / 400.f)*.5+.7, 
                                   osgsin(t / 400.f)*.5+.7));   

        beginEditCP(trans2, Transform::MatrixFieldMask);
        {
            trans2->setMatrix(m);
        }   
        endEditCP  (trans2, Transform::MatrixFieldMask);
    }
    
    // render    
    mgr->redraw();

    // all done, swap    
    glutSwapBuffers();
}

void idle( void )
{
    webInterface->waitRequest(0.01);
    webInterface->handleRequests();
    glutPostRedisplay();
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

    case 27:    osgExit();
                exit(1);
    case '1':   beginEditCP(tg);
                tg->setSBeacon(transn1);
                endEditCP(tg);
                cout << "trans1" << endl;
                break;
    case '2':   beginEditCP(tg);
                tg->setSBeacon(transn2);
                endEditCP(tg);
                cout << "trans2" << endl;
                break;
    case 'a':   animate = !animate;
                cout << (animate?"":"don't ") << "animate" << endl;
                break;
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
    glutIdleFunc(idle);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    PassiveWindowPtr pwin=PassiveWindow::create();
    pwin->init();   
    
    // create the texture
    tx1 = TextureChunk::create();
   
    const UInt16 width = 16, height = 1;
    
    ImagePtr pImg1 = Image::create();
    pImg1->set(Image::OSG_RGB_PF, width, height );
    
    beginEditCP(pImg1);
    UInt8 *d = pImg1->getData();
    
    for(UInt16 y = 0; y < height; ++y)
    {
        for(UInt16 x = 0; x < width; ++x)
        {
            *d++ = static_cast<UInt8>(x * 255.f / width);
            *d++ = static_cast<UInt8>(y * 255.f / height);
            *d++ = static_cast<UInt8>(128);
        }
    }
    endEditCP(pImg1);
    
    
    beginEditCP(tx1);
    tx1->setImage(pImg1); 
    tx1->setMinFilter(GL_NEAREST);
    tx1->setMagFilter(GL_NEAREST);
    tx1->setWrapS(GL_REPEAT);
    tx1->setWrapT(GL_REPEAT);
    endEditCP(tx1);

    tg = TexGenChunk::create();
    
    beginEditCP(tg);
    tg->setGenFuncS(GL_EYE_LINEAR);
    tg->setGenFuncSPlane(Vec4f(0,.15,0,0));
    endEditCP(tg);
    
  
    // create the material
    SimpleMaterialPtr mat = SimpleMaterial::create();
    
    beginEditCP(mat);
    mat->setDiffuse(Color3f(1,1,1));
    mat->setLit(false);
    mat->addChunk(tx1);
    mat->addChunk(tg);
    endEditCP(mat);
    
    // create the scene

    NodePtr torus = makeTorus( .5, 2, 16, 32 );

    GeometryPtr geo = GeometryPtr::dcast(torus->getCore());
    
    beginEditCP(geo, Geometry::MaterialFieldMask);
    geo->setMaterial(mat);
    endEditCP(geo, Geometry::MaterialFieldMask);
      
    transn1 = makeCoredNode<Transform>(&trans1);
    beginEditCP(transn1, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        transn1->addChild(torus);
    }
    endEditCP  (transn1, Node::CoreFieldMask | Node::ChildrenFieldMask);


    transn2 = makeCoredNode<Transform>(&trans2);

    NodePtr scene = makeCoredNode<Group>();  
    beginEditCP(scene);
    scene->addChild(transn1);
    scene->addChild(transn2);
    endEditCP(scene);
    
    beginEditCP(tg);
    tg->setSBeacon(torus);
    endEditCP(tg);
    
    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // create the window and initial camera/viewport
    mgr->setWindow(pwin );
    // tell the manager what to manage
    mgr->setRoot  (scene);
    
    // show the whole scene
    mgr->showAll();
    mgr->redraw();

    webInterface = new WebInterface();
    webInterface->setRoot(scene);
    
    // GLUT main loop
    glutMainLoop();

    return 0;
}
