// OpenSG Testprogram: Direct Volume Rendering Node
//
// It demonstrates some of the capabilities of the OpenSG Volume Renderin Node
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
#include <OSGDVRClipObjects.h>
#include <OSGDVRClipGeometry.h>
#include <OSGDVRSimpleShader.h>
#include <OSGPolygonChunk.h>
#include <OSGSimpleMaterial.h>
#include <OSGSwitch.h>
#include <OSGComponentTransform.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

// Some fieldcontainer pointers that we require for interaction
NodePtr              volumeNode          = NullFC;
DVRVolumePtr         volume              = NullFC;
DVRAppearancePtr     appearance          = NullFC;
DVRClipObjectsPtr    clipObjects         = NullFC;
SwitchPtr            clipObjectsSelector = NullFC;
MFDVRClipGeometryPtr clipGeometries;

// Do an animation
int animate = 1;

// Test data structure
typedef struct {
    int    mode;
    char * name;
} Test;

// Lists of Clip Modes
//!! They are used internally for testing the functionality on differernt
//!! platforms and MUST not be set manually a program 
Test clipTests[] = {
    {0, "No Clipping      "},
    {1, "Intersect mode   "},
    {2, "Subtract mode    "}
};

// Number of clip Modes
int numModes = sizeof(clipTests) / sizeof(Test);
// Current clip Mode
int curMode = 0;
// Desired clip Mode
int newMode = 0;


// clip object definition structure
typedef struct{
    char *name;
    char *params;
} ClipObjectsDef;

// List of clip objects
GeometryPtr *clipObjectsList;

//Number of clip objects
int numClipObjects;
// idx of current clip object
int currentObject = -1;
// idx of the newly selected clip object
int selectedObject = 0;


// forward declaration of the volume node construction function
NodePtr makeVolume( const char * datFile);

// forward declaration of the clip object construction function
NodePtr createClipObjects();

// forware declaration of field access methods
template <class T> void setField(FieldContainerPtr fc, char * fieldName, T newValue);
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
    

    // create the scene
    NodePtr scene = Node::create();
    GroupPtr root = Group::create();
    beginEditCP(scene, Node::CoreFieldMask);
    scene->setCore(root);
    endEditCP(scene, Node::CoreFieldMask);

    if(scene != NullFC){
        beginEditCP(scene);
        scene->addChild(makeVolume("00_data64x64x64.dat"));
        scene->addChild(createClipObjects());
        endEditCP(scene);
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
        // Make the volume rotate
        mgr->mouseButtonPress  (GLUT_LEFT_BUTTON,  0, 0);
	mgr->mouseMove         (1, 0);
	mgr->mouseButtonRelease(GLUT_LEFT_BUTTON, 10, 0);

	// Eventually switch between different hardware modes
	float ctime   = glutGet(GLUT_ELAPSED_TIME);
	int   dtime   = (int)(ctime / 1000 / 2);

	newMode = dtime % numModes;
        if(newMode == 0 && newMode != curMode)
            selectedObject = (selectedObject+1)%clipGeometries.size();
    }

    // Switch shader mode and clipif desired
    if (newMode != curMode) {
        beginEditCP(clipObjects, DVRClipObjects::ClipModeFieldMask);
	clipObjects->setClipMode(newMode);
	endEditCP(clipObjects, DVRClipObjects::ClipModeFieldMask);
	curMode = newMode;
        SLOG << "Clip Mode ... " << clipTests[newMode].name << std::endl;	
    }

    // switch clip object
    if(selectedObject != currentObject) {
#if 1
        beginEditCP(clipObjects, DVRClipObjects::ClipModeFieldMask | DVRClipObjects::ClipObjectsFieldMask);
        clipObjects->remove((UInt32)0);
        clipObjects->add(clipGeometries[selectedObject]);
        endEditCP(clipObjects, DVRClipObjects::ClipModeFieldMask | DVRClipObjects::ClipObjectsFieldMask);
#endif
        beginEditCP(clipObjectsSelector,Switch::ChoiceFieldMask);
        clipObjectsSelector->setChoice(selectedObject);
        endEditCP(clipObjectsSelector,Switch::ChoiceFieldMask);
        currentObject = selectedObject; 
    }

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
void keyboard(unsigned char k, int OSG_CHECK_ARG(x), int OSG_CHECK_ARG(y))
{
    switch(k)
    {
        case 27:        
        {
            delete mgr;
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

        case 'o':
	{
	    selectedObject = (selectedObject + 1) % numClipObjects;
	}
	break;

        case 'O':
	{
	    selectedObject = selectedObject ? selectedObject - 1 : numClipObjects-1;
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

    volume = vol;
    appearance = app;
    
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

    // create clip attachment
    DVRClipObjectsPtr clip = DVRClipObjects::create();
    clipObjects = clip;

    // Initialize the clip objects
    beginEditCP(clip, DVRClipObjects::ClipModeFieldMask);
    clip->setClipMode(0);
    endEditCP(clip, DVRClipObjects::ClipModeFieldMask);    

    // Attach the volume texture and the clip attachment to the appearance
    beginEditCP(app, Node::AttachmentsFieldMask);
    app->addAttachment(clip);
    app->addAttachment(tex);
    endEditCP  (app, Node::AttachmentsFieldMask);

    // Create a shader
    DVRSimpleShaderPtr shader = DVRSimpleShader::create();
    
    // Assign the appearance and shader to the volume core
    beginEditCP(vol);
    vol->setFileName(datFile);
    vol->setAppearance(app);
    vol->setShader(shader);
    endEditCP(vol);

    // Create a node for the volume core
    NodePtr newNode = Node::create();
    beginEditCP(newNode);
    newNode->setCore(vol);
    endEditCP(newNode);

    volumeNode = newNode;
    
    return newNode;
}

NodePtr createClipObjects()
{
    // create the switch node used to select the object the should be used
    NodePtr   clipSwitchNode = Node::create();
    SwitchPtr clipSwitch = Switch::create();

    clipObjectsSelector = clipSwitch;

    beginEditCP(clipSwitchNode,Node::CoreFieldMask);
      clipSwitchNode->setCore(clipSwitch);
    endEditCP(clipSwitchNode,Node::CoreFieldMask);

    // create the "scale" node used to scale the clip object
    NodePtr   scaleNode = Node::create();
    ComponentTransformPtr scale = ComponentTransform::create();

    beginEditCP(scale);
    scale->setScale(Vec3f(10.0, 10.0, 10.0));
    endEditCP(scale);

    beginEditCP(scaleNode,Node::CoreFieldMask | Node::ChildrenFieldMask);
      scaleNode->setCore(scale);
      scaleNode->addChild(clipSwitchNode);
    endEditCP(scaleNode,Node::CoreFieldMask | Node::ChildrenFieldMask);

    // create a common material for all geometries
    PolygonChunkPtr polyChunk = PolygonChunk::create();
    
    beginEditCP(polyChunk, PolygonChunk::FrontModeFieldMask | PolygonChunk::BackModeFieldMask);
    polyChunk->setFrontMode(GL_LINE);
    polyChunk->setBackMode(GL_LINE);
    endEditCP(polyChunk, PolygonChunk::FrontModeFieldMask | PolygonChunk::BackModeFieldMask);

    SimpleMaterialPtr mat = SimpleMaterial::create();
    beginEditCP(mat);
    mat->addChunk(polyChunk);
    mat->setDiffuse(Color3f(.7,.7,.5));
    mat->setAmbient(Color3f(0.1,0.1,0.1));
    mat->setSpecular(Color3f(1,1,1));
    mat->setShininess(20);
    endEditCP(mat);

    // create the clip objects and add them to the switch
    GeometryPtr cl[] = {
        makeBoxGeo(4, 4, 4, 2, 2, 2),
        makeSphereGeo(2, 2.5),
        makeCylinderGeo(4, 2.5, 20, true, true, true),
        //makeConeGeo(4, 2, 20, true, true),
        makeConicalFrustumGeo(4, 0.001, 3, 20, true, true, true),
        makeConicalFrustumGeo(4, 1.5, 3, 20, true, true, true)
    };    
    clipObjectsList = cl;
    numClipObjects = sizeof(cl) / sizeof(GeometryPtr);
    for(int i = 0; i < numClipObjects; i++){
        // create geometry node
        GeometryPtr geo = clipObjectsList[i];
        beginEditCP(geo, Geometry::MaterialFieldMask);
          geo->setMaterial(mat);
        endEditCP(geo, Geometry::MaterialFieldMask);
        NodePtr node = Node::create();
        beginEditCP(node, Node::CoreFieldMask);
          node->setCore(geo);
        endEditCP(node, Node::CoreFieldMask);
        // add to switch
        beginEditCP(clipSwitchNode);
          clipSwitchNode->addChild(node);
        endEditCP(clipSwitchNode);
        // create clip geometry
        DVRClipGeometryPtr clipGeo = DVRClipGeometry::create();
        beginEditCP(clipGeo, DVRClipGeometry::GeometryNodeFieldMask | DVRClipGeometry::BeaconFieldMask);
          clipGeo->setGeometryNode(node);
          clipGeo->setBeacon(NullFC);
        endEditCP(clipGeo, DVRClipGeometry::GeometryNodeFieldMask | DVRClipGeometry::BeaconFieldMask);        
        clipGeometries.push_back(clipGeo);
        addRefCP(clipGeo);
    }
    return scaleNode;
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
