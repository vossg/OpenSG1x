
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


OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

TextureChunkPtr tx1,tx2;
TransformPtr trans;

// redraw the window
void display(void)
{      
    Matrix m;
    Real32 t = glutGet(GLUT_ELAPSED_TIME );
    
    m.setTransform(Vec3f(      osgsin(t / 1000.f), 
                               osgcos(t / 1000.f), 
                               osgsin(t / 1000.f)),
                   Quaternion( Vec3f(0,1,0), 
                               t / 1000.f));   
    
    beginEditCP(trans, Transform::MatrixFieldMask);
    {
        trans->setMatrix(m);
    }   
    endEditCP  (trans, Transform::MatrixFieldMask);

    // render    
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

    case 27:    osgExit();
                exit(1);
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

    TexGenChunkPtr tg = TexGenChunk::create();
    
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
       
    NodePtr transn = makeCoredNode<Transform>(&trans);
    beginEditCP(transn, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        transn->addChild(torus);
    }
    endEditCP  (transn, Node::CoreFieldMask | Node::ChildrenFieldMask);

    NodePtr scene = makeCoredNode<Group>();  
    beginEditCP(scene);
    scene->addChild(transn);
    endEditCP(scene);
    
    beginEditCP(tg);
    tg->setSBeacon(scene);
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
    
    // GLUT main loop
    glutMainLoop();

    return 0;
}
