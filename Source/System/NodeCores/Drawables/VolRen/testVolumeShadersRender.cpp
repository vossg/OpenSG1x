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
#include <OSGDVRLookupTable.h>


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

// List of shaders to be tested
char * shaderList[] = {
    "DVRSimpleShader",
    "DVRSimpleLUTShader",
    "DVRIsoShader",
    "DVRMtexLUTShader"
};

// Number of Shader Modes
int numShaders = sizeof(shaderList) / sizeof(char *);
// Current Shader Mode
int curShader = -1;
// Desired Shader Mode
int newShader = 0;

// A lookup table for the test scene
unsigned char lutData[1024] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 72, 72, 72, 72,
    76, 76, 76, 76, 76, 76, 76, 76, 77, 77, 77, 77, 77, 77, 77, 77,
    77, 77, 77, 77, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 103, 0, 0, 103, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 108, 0, 108, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 113, 113,
    0, 0, 113, 113, 0, 0, 0, 0, 0, 0, 0, 0, 138, 138, 138, 138,
    138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138,
    138, 138, 138, 138, 138, 138, 138, 138, 139, 139, 139, 139,
    139, 139, 139, 139, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

// forward declaration of the volume node construction function
NodePtr makeVolume( const char * datFile);

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
        scene = SceneFileHandler::the().read(argv[1]);
	if (scene == NullFC)
	{
	    SLOG << "Could not read file " << argv[1] << std::endl;
	    exit(-1);
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

	newShader = dtime % numShaders;

	// Make the volume rotate
	int movement = ((ctime - lastFrame) * aniSpeed);
 	if (movement != 0) lastFrame = ctime;

	mgr->mouseButtonPress  (GLUT_LEFT_BUTTON,  0, 0);
 	mgr->mouseMove         (movement, 0);
 	mgr->mouseButtonRelease(GLUT_LEFT_BUTTON, movement, 0);
    }

    // Switch shader mode if desired
    if (newShader != curShader)
    {
        DVRShaderPtr shd = DVRShaderPtr::dcast(
	  FieldContainerFactory::the()->createFieldContainer(shaderList[newShader]));
          
	// change to new shader object
	beginEditCP(volume, DVRVolume::ShaderFieldMask);            
	volume->setShader(shd);
	endEditCP(volume, DVRVolume::ShaderFieldMask);
    }

    mgr->redraw();

    // Output active shader mode - field is valid after redraw only
    if (newShader != curShader)
    {
        SLOG << "Active Shader " << newShader << ": "
	     << (volume->getShader() != NullFC ?
	            volume->getShader()->getTypeName() : "NullFC")
	     << std::endl;

	curShader = newShader;
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
	    newShader = (newShader + 1) % numShaders;
	}
	break;

        case '-':
	{
	    newShader = (newShader > 1) ? (newShader - 1) % numShaders : numShaders - 1;
	}
	break;
    }
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE | GLUT_STENCIL);
    
    int winid = glutCreateWindow("OpenSG Shader Test");
    
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
    DVRLookupTablePtr    lut         = DVRLookupTable::create();
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

    //!! FIXME - Initialize the lookup table
    //!! This should not be neccessary if the OpenSG reader works correctly
    beginEditCP(lut, DVRLookupTable::TouchedFieldMask);
    lut->setTouched(true);
    endEditCP(lut, DVRLookupTable::TouchedFieldMask);

    // Initialize the lookup table
    beginEditCP(lut, DVRLookupTable::DataFieldMask);
    for (int i = 0; i < 1024; i++)
        lut->getData()[i] = lutData[i];
    endEditCP(lut, DVRLookupTable::DataFieldMask);

    // Initialize the isovalue
    beginEditCP(iso, DVRIsoSurface::IsoValueFieldMask);
    iso->setIsoValue(0.2);
    endEditCP(iso, DVRIsoSurface::IsoValueFieldMask);

    // Attach the volume texture and isosurface to the appearance
    beginEditCP(app, Node::AttachmentsFieldMask);
    app->addAttachment(tex);
    app->addAttachment(lut);
    app->addAttachment(iso);
    endEditCP  (app, Node::AttachmentsFieldMask);

    // Assign the appearance and shader to the volume core
    beginEditCP(vol);
    vol->setFileName(datFile);
    vol->setAppearance(app);
    vol->setShader(shader);
    endEditCP(vol);

    // Create a node for the volume core
    NodePtr newGeom = Node::create();
    beginEditCP(newGeom);
    newGeom->setCore(vol);
    endEditCP(newGeom);
    
    return newGeom;
}

// Functions for generically accessing fields
template <class T>
void setField(FieldContainerPtr fc, char * fieldName, T newValue)
{
    const FieldDescription * desc    = fc->getType().findFieldDescription(fieldName); 
    Field *                  field   = fc->getField(desc->getFieldId()); 
    SField<T> *              dataptr = dynamic_cast<SField<T>*>(field); 

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
