#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSimpleTexturedMaterial.h>
#include <OSGTextureTransformChunk.h>
#include <OSGImage.h>
#include <OSGImageFunctions.h>

OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

TextureTransformChunkPtr tt;

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
    NodePtr scene = makePlane( 2, 2, 2, 2 );

    GeometryPtr plane_geo = GeometryPtr::dcast(scene->getCore());
    SimpleTexturedMaterialPtr pm = SimpleTexturedMaterial::create();
    beginEditCP(pm);
    pm->setDiffuse( Color3f( 1,0,0 ) );
    pm->setAmbient( Color3f( 1,0,0 ) );
    pm->setSpecular( Color3f( 1,1,1 ) );
    pm->setShininess( 10 );

    ImagePtr pImage = Image::create();
    
    if(argc < 6)
    {
        FWARNING(("testNoiseRender: <ncomp> <numOct> <size> <dim> "
                  "<splitOct>\n"));
        exit(-1);
    }
    
    Image::PixelFormat pixelformat = Image::OSG_RGBA_PF;
    UInt16 numOctaves = 6;
    UInt16 size = 128;
    UInt8  dim  = 2;
    bool   splitOctaves = false;
    UInt8  ncomp  = 1;

    ncomp = atoi(argv[1]);
    switch(ncomp)
    {
    case 1: pixelformat = Image::OSG_L_PF; break;
    case 2: pixelformat = Image::OSG_LA_PF; break;
    case 3: pixelformat = Image::OSG_RGB_PF; break;
    case 4: pixelformat = Image::OSG_RGBA_PF; break;
    default:    FFATAL(("NComp %d unknown!\n", ncomp));
                exit(1);
    }
    
    numOctaves = atoi(argv[2]);
    size = atoi(argv[3]);
    dim = atoi(argv[4]);
    splitOctaves = atoi(argv[5]);
    
    pImage = Image::create();
    
    createNoise(pImage, pixelformat, numOctaves, size, dim, splitOctaves);
    
    pImage->dump();

    pm->setImage( pImage ); 
    pm->setMinFilter( GL_NEAREST_MIPMAP_NEAREST );
    pm->setMagFilter( GL_NEAREST );
    
    
    tt = TextureTransformChunk::create();
    
    pm->addChunk(tt);
    endEditCP(pm);

    plane_geo->setMaterial( pm );

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();
    
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
    Real32 time = glutGet(GLUT_ELAPSED_TIME);
    
    Matrix m;
    
    m.setTransform(Vec3f(0,0,sin(time/1000)));
    
    beginEditCP(tt);
    tt->setMatrix(m);
    endEditCP(tt);
    
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
void keyboard(unsigned char k, 
              int /* x */,
              int /* y */)
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
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}
