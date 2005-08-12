// OpenSG Testprogram: Direct Volume Rendering Node
//
// It demonstrates some of the capabilities of the OpenSG Volume Rendering Node
// in an interactive scene viewer.
//

// GLUT is used for window handling
#include <OSGGLUT.h>

// General OpenSG configuration, needed everywhere
#include <OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OSGSimpleGeometry.h>

// The GLUT-OpenSG connection class
#include <OSGGLUTWindow.h>

// A little helper to simplify scene management and interaction
#include <OSGSimpleSceneManager.h>

// For loading files
#include <OSGSceneFileHandler.h>

// For log information
#include <OSGLog.h>

// Includes for the volume rendering library
#include <OSGDVRVolume.h>
#include <OSGDVRVolumeTexture.h>
#include <OSGDVRAppearance.h>
#include <OSGDVRIsoSurface.h>
#include <OSGDVRIsoShader.h>


// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

// Some fieldcontainer pointers that we require for interaction
NodePtr      scene  = NullFC;
DVRVolumePtr volume = NullFC;
DVRShaderPtr shader = NullFC;

// Do an animation
int   animate  = 1;
float aniSpeed = 0.5;
float lastFrame;

// Test data structure
typedef struct {
    int    mode;
    char * name;
} ShaderTest;

// Lists of Shader Modes
//!! They are used internally for testing the functionality on differernt
//!! platforms and MUST not be set manually a program 
ShaderTest shaderTests[] = {
    {0, "Automatic Mode Selection                 "},
    {1, "SGI Color Matrix Lighting (2D)           "},
    {2, "SGI Color Matrix Lighting (3D)           "},
    {3, "NV  Register Combiners Lighting (2D)     "},
    {4, "NV  Register Combiners Lighting (Multi2D)"},
    {5, "NV  Register Combiners Lighting (3D)     "},
    {6, "ARB Fragment Program Lighting (2D)       "},
    {7, "ARB Fragment Program Lighting (3D)       "},
    {8, "INACTIVE                                 "}
};

// Number of Shader Modes
int numModes = sizeof(shaderTests) / sizeof(ShaderTest);
// Current Shader Mode
int curMode = 0;
// Desired Shader Mode
int newMode = 1;

// forward declaration of the volume node construction function
NodePtr makeVolume( const char * datFile);

// forware declaration of field access methods
template <class T, int id> void setField(FieldContainerPtr fc, char * fieldName, T newValue);
template <class T> T getField(FieldContainerPtr fc, char * fieldName, T* dummy = NULL);

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

// Initialize GLUT & OpenSG and set up the scene
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
    
    // create the scene or load it from a .osg-file
    if (argc == 1)
        scene = makeVolume("00_data64x64x64.dat");
    else
    {
        if(!strcmp(argv[1], "-i"))
        {
            scene = makeVolume(argv[2]);
        }
        else
        {
            scene = SceneFileHandler::the().read(argv[1]);
	        if (scene == NullFC)
	        {
	            SLOG << "Could not read file " << argv[1] << std::endl;
	            exit(-1);
	        }
        }
    }

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow   (gwin );
    mgr->setRoot     (scene);
    mgr->setHighlight(scene);

    // show the whole scene
    mgr->showAll();
    Pnt3f from = mgr->getNavigator()->getFrom();
    from[2] = 3 * from[2];
    mgr->getNavigator()->setFrom(from);
    
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
    if (animate)
    {
	// Eventually switch between different hardware modes
	float ctime   = glutGet(GLUT_ELAPSED_TIME);
	int   dtime   = (int)ctime / 1000 / 2;

	newMode = dtime % numModes;

        // Make the volume rotate
	int movement = (int) ((ctime - lastFrame) * aniSpeed);
	if (movement != 0) lastFrame = ctime;

        mgr->mouseButtonPress  (GLUT_LEFT_BUTTON,  0, 0);
	mgr->mouseMove         (movement, 0);
	mgr->mouseButtonRelease(GLUT_LEFT_BUTTON, movement, 0);
    }

    // Switch shader mode if desired
    if (newMode != curMode)
    {
        beginEditCP(shader, DVRIsoShader::ShadeModeFieldMask);
	setField<Int8,0>(shader, "shadeMode", newMode);
	endEditCP(shader, DVRIsoShader::ShadeModeFieldMask);
    }

    mgr->redraw();

    // Output active shader mode - field is valid after redraw only
    if (newMode != curMode)
    {
        SLOG << "Mode " << newMode
	     << ": " << shaderTests[newMode].name << " --> "
	     << shaderTests[getField<Int8>(shader, "activeShadeMode")].name << std::endl;
	
	curMode = newMode;
    }
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
void keyboard(unsigned char k, int OSG_CHECK_ARG(x), int OSG_CHECK_ARG(y))
{
    switch(k)
    {
        case 27:        
        {
            OSG::osgExit();
            exit(0);
        }
        break;

        case 'a':
	{
	    animate = 1 - animate;
	}
	break;

        case '+':
	{
	    newMode = (newMode + 1) % numModes;
	}
	break;

        case '-':
	{
	    newMode = (newMode > 1) ? (newMode - 1) % numModes : numModes - 1;
	}
	break;
    }
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE | GLUT_STENCIL);
    
    int winid = glutCreateWindow("OpenSG DVRIsoShader");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    glutIdleFunc(display);

    return winid;
}

// Create a volume rendering node with all desired attachments
NodePtr makeVolume( const char * datFile)
{  
    DVRVolumePtr         vol         = DVRVolume::create();
    DVRAppearancePtr     app         = DVRAppearance::create(); 
    DVRVolumeTexturePtr  tex         = DVRVolumeTexture::create();
    DVRIsoSurfacePtr     iso         = DVRIsoSurface::create();

    volume = vol;
    
    // Load the 3D-image and store it in the volume texture attachment
    ImagePtr datImage = Image::create();
    if (false == datImage->read(datFile)) {
        SLOG << "File: " << datFile << " not found" << std::endl;
	exit (-1);
    }
    beginEditCP(tex);
    tex->setImage(datImage);
    tex->setFileName(datFile);
    endEditCP(tex);

    // Initialize the isovalue
    beginEditCP(iso, DVRIsoSurface::IsoValueFieldMask);
    iso->setIsoValue(0.2);
    endEditCP(iso, DVRIsoSurface::IsoValueFieldMask);

    // Attach the volume texture and isosurface to the appearance
    beginEditCP(app, Node::AttachmentsFieldMask);
    app->addAttachment(tex);
    app->addAttachment(iso);
    endEditCP  (app, Node::AttachmentsFieldMask);

    // Create a shader
    shader = DVRIsoShader::create();
    
    // Assign the appearance and shader to the volume core
    beginEditCP(vol);
    vol->setFileName(datFile);
    vol->setAppearance(app);
    vol->setShader(shader);
    
    vol->setBrickStaticMemoryMB(64);
    
    setField<bool,2>(vol, "showBricks", true);

    endEditCP(vol);

    // Create a node for the volume core
    NodePtr newGeom = Node::create();
    beginEditCP(newGeom);
    newGeom->setCore(vol);
    endEditCP(newGeom);
    
    return newGeom;
}

// Functions for generically accessing fields
template <class T, int id>
void setField(FieldContainerPtr fc, char * fieldName, T newValue)
{
    const FieldDescription * desc    = fc->getType().findFieldDescription(fieldName); 
    Field *                  field   = fc->getField(desc->getFieldId()); 
    SField<T,id> *              dataptr = dynamic_cast<SField<T,id>*>(field); 

    if (dataptr)
        dataptr->setValue(newValue);
}

template <class T>
T getField(FieldContainerPtr fc, char * fieldName, T * )
{
    const FieldDescription * desc    = fc->getType().findFieldDescription(fieldName); 
    Field *                  field   = fc->getField(desc->getFieldId()); 
    SField<T> *              dataptr = dynamic_cast<SField<T>*>(field); 

    if (dataptr)
        return dataptr->getValue();
    else
        return 0;
}
