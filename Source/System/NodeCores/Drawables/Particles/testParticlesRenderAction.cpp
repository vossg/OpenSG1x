
#include <string.h>
#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGImage.h>

#include <OSGSimpleTexturedMaterial.h>
#include <OSGBlendChunk.h>
#include <OSGParticles.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

int setupGLUT( int *argc, char *argv[] );

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();

    // create the scene
    NodePtr scene = Node::create();
    ParticlesPtr particles = Particles::create();

    beginEditCP(scene);
    scene->setCore( particles );
    endEditCP(scene);

    UInt32 count = 100;
    
    if (argc > 1)
    {
        count = atoi(argv[1]);
    }
    
    beginEditCP(particles);

    GeoPositions3fPtr pnts = GeoPositions3f::create();
    particles->setPositions( pnts );

    MFPnt3f* p = pnts->getFieldPtr();

    beginEditCP(pnts);
    UInt32 i;
    for(i = 0; i < count; ++i)
    {
        Pnt3f pnt(osgrand(),osgrand(),osgrand());
        p->push_back(pnt);        
    }
    endEditCP(pnts);


    GeoColors3fPtr cols = GeoColors3f::create();
    particles->setColors( cols );
    beginEditCP(cols);
    for(i = 0; i < count; ++i)
    {
        cols->getFieldPtr()->push_back( Color3f(osgrand(),osgrand(),osgrand()) );
    }
    endEditCP(cols);

    MFVec3f *size = particles->getMFSizes();
    for(i = 0; i < count; ++i)
    {
        Real32 s=osgrand()/10.f;
        size->push_back(Vec3f(s,0,0));
    }
     
    endEditCP(particles);

    SimpleTexturedMaterialPtr tm;

    tm = SimpleTexturedMaterial::create();

    UChar8 imgdata[] =
        {  255,0,0,  255,0,0,  255,0,255,
           255,0,0,  255,0,0,  255,0,255 };
    ImagePtr pImage = Image::create();

    if (argc > 2)
    {

        pImage->read(argv[2]);
    }
    else
    {
        pImage->set(Image::OSG_RGB_PF, 3, 2, 1, 1, 1, 0, imgdata);
    }
    
    beginEditCP(tm);
    tm->setDiffuse( Color3f( 1,1,1 ) );
    tm->setLit( false );

    tm->setImage( pImage );
    tm->setEnvMode( GL_MODULATE );
    
    BlendChunkPtr bl=BlendChunk::create();
    
    beginEditCP(bl);
    bl->setSrcFactor(GL_SRC_ALPHA);
    bl->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
    bl->setAlphaFunc(GL_EQUAL);
    bl->setAlphaValue(1);   
    endEditCP(bl);
   
    tm->addChunk(bl);
    
    endEditCP(tm);

    particles->setMaterial( tm );


    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();

    mgr->setHighlight(scene);
        
    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

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
void keyboard(unsigned char k, int , int )
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

    return winid;
}
