
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
#include <OSGTextureTransformChunk.h>


OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

TextureChunkPtr tx1,tx2;

// redraw the window
void display(void)
{      
    static Real32 lastTime = 0;
    Real32 time = (getSystemTime() - lastTime) / 5;
    lastTime = getSystemTime();
    
    beginEditCP(tx2, TextureChunk::ShaderOffsetMatrixFieldMask);
    tx2->setShaderOffsetMatrix(osgsin(time),0,0,osgsin(time));       
    endEditCP(tx2, TextureChunk::ShaderOffsetMatrixFieldMask);
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
    
    // create the two textures
    tx1 = TextureChunk::create();
   
    const UInt16 p1size = 128;
    
    ImagePtr pImg1 = Image::create();
    pImg1->set(Image::OSG_LA_PF, p1size, p1size );
    
    beginEditCP(pImg1);
    UInt8 *d = pImg1->getData();
    
    for(UInt16 y = 0; y < p1size; ++y)
    {
        for(UInt16 x = 0; x < p1size; ++x)
        {
            Real32 rx = x / static_cast<Real32>(p1size) * 2 - 1,
                   ry = y / static_cast<Real32>(p1size) * 2 - 1;
            
            Real32 v = osgsqrt(rx * rx + ry * ry) * 5;
            
            *d++ = static_cast<UInt8>(rx * osgcos(v) * 16 + 32);
            *d++ = static_cast<UInt8>(ry * osgsin(v) * 16 + 32);
        }
    }
    endEditCP(pImg1);
    
    
    beginEditCP(tx1);
    tx1->setImage(pImg1); 
    tx1->setMinFilter(GL_LINEAR);
    tx1->setMagFilter(GL_LINEAR);
    tx1->setWrapS(GL_REPEAT);
    tx1->setWrapT(GL_REPEAT);
    tx1->setInternalFormat(GL_DSDT_NV);
    tx1->setExternalFormat(GL_DSDT_NV);
    
//    tx1->setInternalFormat(GL_LUMINANCE_ALPHA);
//    tx1->setExternalFormat(GL_LUMINANCE_ALPHA);

    tx1->setShaderOperation(GL_TEXTURE_2D);
    
    endEditCP(tx1);

    tx2 = TextureChunk::create();
   
   
    const UInt16 p2size = 128;
    const UInt16 t2size = 16;
    
    ImagePtr pImg2 = Image::create();
    pImg2->set(Image::OSG_RGB_PF, p2size, p2size );
    
    beginEditCP(pImg2);
    d = pImg2->getData();
    
    for(UInt16 y = 0; y < p2size; ++y)
    {
        for(UInt16 x = 0; x < p2size; ++x)
        {
            if((x / t2size + y / t2size) & 1)
            {
                *d++ = 0;
                *d++ = 0;
                *d++ = 0;
            }
            else
            {
                *d++ = 64;
                *d++ = 128;
                *d++ = 255;
            }
        }
    }
    endEditCP(pImg2);
    
    beginEditCP(tx2);
    tx2->setImage(pImg2);
    tx2->setMinFilter(GL_LINEAR);
    tx2->setMagFilter(GL_LINEAR);
    tx2->setWrapS(GL_REPEAT);
    tx2->setWrapT(GL_REPEAT);
    
    tx2->setShaderOperation(GL_OFFSET_TEXTURE_2D_NV);
    tx2->setShaderInput    (GL_TEXTURE0_ARB);   
    tx2->setShaderOffsetMatrix(0.5,0,0,0.5);   
    
    endEditCP(tx2);
   
    // create the material
    SimpleMaterialPtr mat = SimpleMaterial::create();
    
    beginEditCP(mat);
    mat->setDiffuse(Color3f(1,1,1));
    mat->setLit(false);
    mat->addChunk(tx1);
    mat->addChunk(tx2);
    endEditCP(mat);
    
    // create the scene
    NodePtr scene;
    
    scene = Node::create();
    GeometryPtr g1 = Geometry::create();

    beginEditCP(scene);
    scene->setCore(g1);
    endEditCP(scene);

    beginEditCP(g1);

    GeoPositions3fPtr pnts = GeoPositions3f::create();
    g1->setPositions(pnts);

    MFPnt3f* p = pnts->getFieldPtr();

    beginEditCP(pnts);
    p->push_back(Pnt3f(-1, -1, -1));
    p->push_back(Pnt3f( 1, -1, -1));
    p->push_back(Pnt3f( 1,  1, -1));
    p->push_back(Pnt3f(-1,  1, -1));
    p->push_back(Pnt3f(-1, -1,  1));
    p->push_back(Pnt3f( 1, -1,  1));
    p->push_back(Pnt3f( 1,  1,  1));
    p->push_back(Pnt3f(-1,  1,  1));
    endEditCP(pnts);


    GeoNormals3fPtr norms = GeoNormals3f::create();
    g1->setNormals(norms);
    beginEditCP(norms);
    norms->push_back(Vec3f(-1, -1, -1));
    norms->push_back(Vec3f( 1, -1, -1));
    norms->push_back(Vec3f( 1,  1, -1));
    norms->push_back(Vec3f(-1,  1, -1));
    norms->push_back(Vec3f(-1, -1,  1));
    norms->push_back(Vec3f( 1, -1,  1));
    norms->push_back(Vec3f( 1,  1,  1));
    norms->push_back(Vec3f(-1,  1,  1));
    endEditCP(norms);

    GeoTexCoords2fPtr texs = GeoTexCoords2f::create();
    g1->setTexCoords(texs);
    beginEditCP(texs);
    texs->push_back(Vec2f(0, 0));
    texs->push_back(Vec2f(1, 0));
    texs->push_back(Vec2f(1, 1));
    texs->push_back(Vec2f(0, 1));
    texs->push_back(Vec2f(0, 0));
    texs->push_back(Vec2f(2, 0));
    texs->push_back(Vec2f(2, 2));
    texs->push_back(Vec2f(0, 2));
    endEditCP(texs);

    g1->setTexCoords1(texs);

    GeoPLengthsPtr lens = GeoPLengthsUI32::create();    
    g1->setLengths(lens);
    beginEditCP(lens);
    lens->push_back(8);
    endEditCP(lens);

    GeoPTypesPtr type = GeoPTypesUI8::create();     
    g1->setTypes(type);
    beginEditCP(type);
    type->push_back(GL_QUADS);
    endEditCP(type);

    g1->setMaterial(mat);
    
    endEditCP(g1);

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
