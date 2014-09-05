// This file illustrates how to use CGFXMaterial2 in conjunction
// with the accompanyig shader fragments.
// Not that the effect is not designed to be pretty, but to 
// demonstrate concepts.
// Make sure you also look at the file 'test_shaderfragments.cgfx'.
//

#ifdef MSVC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#pragma warning(push)
#pragma warning(disable:4231)
#pragma warning(push)
#pragma warning(disable:4996)
#pragma warning(push)
#pragma warning(disable:4275)
#endif


// GLUT is used for window handling
#include "OSGGLUT.h"

// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// Methods to create simple geometry: boxes, spheres, tori etc.
#include "OSGSimpleGeometry.h"

// The GLUT-OpenSG connection class
#include "OSGGLUTWindow.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"

#include "OSGSimpleTexturedMaterial.h"
#include "OSGImage.h"

#include "OSGCGFXMaterial.h"

#ifdef MSVC_VER
#pragma warning(pop)
#pragma warning(pop)
#pragma warning(pop)
#pragma warning(pop)
#endif

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

// Our global CGFXMaterial
CGFXMaterialPtr mat;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );
ImagePtr createCheckerboard();

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{

    OSG::osgLog().setLogLevel( LOG_INFO );

#if 1
  #if defined(_WIN32)
    const char* effectFilename = (argc > 1) ? argv[1] : "C:/work/OpenSG/Source/Contrib/CGFXMaterial2/test_shaderfragments.cgfx";
    const char* shaderfragmentPath = (argc > 2) ? argv[2] : "C:/work/OpenSG/Source/Contrib/CGFXMaterial2/shaderfragments";
  #else
    const char* effectFilename = (argc > 1) ? argv[1] : "/media/disk/work/OpenSG/Source/Contrib/CGFXMaterial2/test_shaderfragments.cgfx";
    const char* shaderfragmentPath = (argc > 2) ? argv[2] : "/media/disk/work/OpenSG/Source/Contrib/CGFXMaterial2/shaderfragments";
  #endif
#else
    const char* effectFilename = 0;
    const char* shaderfragmentPath = 0;
    if( argc > 2 )
    {
        effectFilename =  argv[1];
        shaderfragmentPath = argv[2];
    }
    else
    {
        FINFO(("Usage: test_shaderfragments effectFilename shaderfragmentPath\n"));
        return -1;
    }
#endif

    FINFO(("Using '%s' as effectFilename\n", effectFilename));
    FINFO(("Using '%s' as shaderfragmentPath\n", shaderfragmentPath));


    // OSG init
    osgInit(argc,argv);


    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();
    
    // create a CGFXMaterial
    FieldContainerPtr fcp = FieldContainerFactory::the()->createFieldContainer("CGFXMaterial");
    mat = CGFXMaterialPtr::dcast( fcp );
    assert( mat != NullFC );

    // load the color texture and name it, so the material can find it later on
    //ImagePtr image = Image::create();
    //image->read("test.jpg");
    ImagePtr image = createCheckerboard();
    beginEditCP( image );
        image->setName( "ColorSampler" );
    endEditCP( image );

    // setup material
    beginEditCP( mat );
//		mat->setEffectFile( "c:/work/colourCAD/shaders/Main.cgfx" );
        mat->setEffectFile( effectFilename );

        // set some defines and the include path for the cg compiler
        mat->editMFCompilerOptions()->push_back("-DOPEN_SG");
        mat->editMFCompilerOptions()->push_back("-DSTD_VERTEX_TANGENTS_AS_TEXCOORDS");
        mat->editMFCompilerOptions()->push_back("-DNUM_LIGHTS=2");
        mat->editMFCompilerOptions()->push_back(std::string("-I") + shaderfragmentPath);
// 		mat->editMFCompilerOptions()->push_back("-debug");

        mat->addImage( image );

        // first light is a point light
        mat->setParameter( "lights[0].position", Vec3f(5.f,5.f,5.f) );
        mat->setParameter( "lights[0].emission", Vec3f(1.f,1.f,1.f) );
        mat->setParameter( "lights[0].type", 0 );

        // second light is a directional light from opposite direction
        mat->setParameter( "lights[1].direction", Vec3f(-0.577f,-0.577f,-0.577f) );
        mat->setParameter( "lights[1].emission", 0.1f*Vec3f(0.f,0.f,1.f) );
        mat->setParameter( "lights[1].type", 1 );

        // the brdf is a linear combination of a perfect diffuse and a phong
        // term, equally weighted
        mat->setParameter( "brdf", std::string("LinCombi2BRDF") );
        mat->setParameter( "brdf.weights", Vec2f(1,1) );

        // first brdf of the linCombi is a LambertBRDF which is wrapped by
        // a VaryingParameter0BRDF. This is needed to feed the actual brdf
        // with the colors of the texture we set up earlier.
        mat->setParameter( "brdf.brdf1", std::string("VaryingParameter0BRDF") );
        mat->setParameter( "brdf.brdf1.vpp0", std::string("Sampler2DVPP") );
        mat->setParameter( "brdf.brdf1.vpp0._sampler", std::string("ColorSampler") );
        mat->setParameter( "brdf.brdf1.brdf", std::string("LambertBRDF") );
        mat->setParameter( "brdf.brdf1.brdf.rho", Vec3f(10,0,10) );

        // second brdf is simply a PhongBRDF
        mat->setParameter( "brdf.brdf2", std::string("PhongBRDF") );
        mat->setParameter( "brdf.brdf2.C_s", Vec3f(1,1,1) );
        mat->setParameter( "brdf.brdf2.shininess", 128.f );

        // make it a little brighter...
        mat->setParameter( "toneMappingParameter", 0.01f );

        mat->setTechnique( 0 );
    endEditCP( mat );

//	std::string techname = mat->getTechniqueString(0);

    // create the scene (simply a torus)
    NodePtr geo0 = makeTorus( 1, 2, 32, 32 );
    GeometryPtr gp = GeometryPtr::dcast( geo0->getCore() );
    beginEditCP( gp );
    {
        gp->setMaterial( mat );
    }
    endEditCP( gp );

    NodePtr scene = geo0;

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();
    
//	reshape( 1024, 768 );

    // GLUT main loop
    glutMainLoop();

    return 0;
}

ImagePtr createCheckerboard()
{
    ImagePtr ret = Image::create();
    UInt8 data[ 8*8*4 ];
    for( int x=0; x<8; ++x )
    {
        for( int y=0; y<8; ++y )
        {

            int const i = x + y*8;
            UInt8 c = 0;
            if( x % 2 && y % 2 )
            {
                c = 255;
            }
            data[ i*4 + 0 ] = c;
            data[ i*4 + 1 ] = c;
            data[ i*4 + 2 ] = c;
            data[ i*4 + 3 ] = 255;
        }
    }

    beginEditCP( ret );
    ret->set( Image::OSG_RGBA_PF, 8, 8, 1, 1, 1, 0, data, Image::OSG_UINT8_IMAGEDATA, true, 1 );
    endEditCP( ret );

//	assert( ret->getMipMapCount() == 1 );

    return ret;
}

void reloadMat()
{

    if( mat != NullFC )
    {
        beginEditCP( mat );
            mat->setEffectFile( mat->getEffectFile() );
        endEditCP( mat );
    }
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
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:        
        {
            OSG::osgExit();
            exit(0);
        }
        case 'r':
        {
            reloadMat();
            break;
        }
    }
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG CgFX Demo");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
//	glutIdleFunc(display);

    return winid;
}
