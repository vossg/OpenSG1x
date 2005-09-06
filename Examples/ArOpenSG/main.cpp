#include <string>
#include <vector>
#include <iostream>

#ifdef _WIN32

#include "DirectShowFrameGrabber.h"
typedef DirectShowFrameGrabber FrameGrabber;

#else

#include "V4LFrameGrabber.h"
typedef V4LFrameGrabber FrameGrabber;

// Not using the ARTKP library, just declare it here
#include "ARToolKitPlus/MemoryManager.h"

ARToolKitPlus::MemoryManager *memManager = NULL;

#endif

#define ARTOOLKITPLUS


#ifdef ARTOOLKITPLUS

//artoolkitpplus header
#include "ARToolKitPlus/TrackerSingleMarkerImpl.h"

#else
//artoolkit header
#include <AR/ar.h>

#endif


#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGGLUTWindowBase.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGMatrixUtility.h>
#include <OpenSG/OSGMatrixCamera.h>
#include <OpenSG/OSGSceneFileHandler.h>

#include <OpenSG/OSGGLEXT.h>
#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGTextureChunk.h>
#include <OpenSG/OSGTextureBackground.h>


// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The pointer to the transformation
TransformPtr modelTrans;
NodePtr modelNode;

// The pointer to the dynamic image and the texture
ImagePtr        image;
TextureChunkPtr tex;


bool horAverage = false;

bool showBinary = false;

int thresh = 100;

// Some helper flags for different code pathes

// flag to indicate whether the images are power-of-two (POT) in size or not
bool  isPOT = false;

// flag to indicate whether rectangular textures are available
bool  hasRectTex = false;

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );


MatrixCameraPtr camera;
NodePtr rootScene;
FrameGrabber *dfg = NULL;
#ifdef ARTOOLKITPLUS
ARToolKitPlus::TrackerSingleMarker *tracker = NULL;
ARToolKitPlus::ARMarkerInfo *markers = NULL;
#else
ARParam cameraParam;
ARMarkerInfo *markers = NULL;
#endif
float modelScale;

// Grab/update the image
// This just update the image's data and tells the texture that it changed.
// For a video this would grab the next frame
void grabImage(ImagePtr img)
{
    beginEditCP(img, Image::PixelFieldMask);
    
    UInt8* data = img->getData();

	// grab video frame from video device...
	dfg->grabFrame();
	unsigned char *buffer = dfg->getFrame();

    // Fill the whole picture
	int w = img->getWidth();
	int h = img->getHeight();
	int w_x_bpp = w * img->getBpp();
	int k;

    // Do top-down to bottom-up conversion
    
    if(dfg->isTopDown())
    {
	    for(UInt32 i = 0; i < h; ++i)
            memcpy(data + i * w_x_bpp, buffer + (h-i-1) * w_x_bpp, w_x_bpp);
    }
    else
    {
    	memcpy(data, buffer, w_x_bpp * h);
    }
    
    // Do a little horizontal averaging to eliminate noise
    if(horAverage)
    {
        UInt8 * d = data, v;
        
        for(UInt32 i = image->getWidth() * image->getHeight() / 2; i > 0; 
                --i, d+=6)
        {
            v = (d[0] + d[3]) / 2;
            d[0] = d[3] = v;
            v = (d[1] + d[4]) / 2;
            d[1] = d[4] = v;
            v = (d[2] + d[5]) / 2;
            d[2] = d[5] = v;
        }
    }
    
    endEditCP(img, Image::PixelFieldMask);

    // Everything changed
    tex->imageContentChanged();
}

static void arMatrixToOSGMatrix(ARFloat arMatrix[3][4], Matrix &m) 
{
	for (int j = 0; j < 3; j++ ) 
      for (int i = 0; i < 4; i++ ) 
			m[i][j] = arMatrix[j][i];
      
	// invert first row
    m[0][0] = -m[0][0];
	m[1][0] = -m[1][0];
	m[2][0] = -m[2][0];
	m[3][0] = -m[3][0];

	// homogeneous stuff...
    m[0][3] = 0.0;
	m[1][3] = 0.0;
	m[2][3] = 0.0;
	m[3][3] = 1.0;

	// invert translation part
	m[3][0] = -m[3][0];
	m[3][1] = -m[3][1];
	m[3][2] = -m[3][2];
}


void detectMarker(ImagePtr image)
{
	static NodePtr oldND;
	int numberOfMarkers = 0;
	Matrix m;
	Matrix rot;
	Matrix scale;

	if( !dfg->getFrame() )
		return;
   
	// ar library marker detection
#ifdef ARTOOLKITPLUS
		tracker->arDetectMarker((ARToolKitPlus::ARUint8*)image->getData(),
                                thresh, &markers, &numberOfMarkers);
#else
		arDetectMarker(image->getData(), thresh, &markers, &numberOfMarkers);
#endif

std::cout << numberOfMarkers << ":";
for(int i=0; i < numberOfMarkers; i++) 
    std::cout << markers[i].id << " ";
std::cout << '\r';

	if( numberOfMarkers > 0 && markers[0].id >= 0 )
    {
		//printf( "detected marker at pixel position %f %f\n", (float)markers[0].pos[0], (float)markers[0].pos[1] );
 
        ARFloat markerCenter[2] = {0.0, 0.0};
        ARFloat markerOrientation[3][4];

#ifdef ARTOOLKITPLUS
        tracker->arGetTransMat(&markers[0], markerCenter, 100, markerOrientation);
#else
		arGetTransMat(&markers[0], markerCenter, 100, markerOrientation);
#endif

		arMatrixToOSGMatrix(markerOrientation, m);
      
		// scale/orient the model
		scale.setScale( modelScale, modelScale, modelScale );
		
		rot[2][1] = 1;
		rot[1][2] = -1;

		rot[1][1] = 0;
		rot[2][2] = 0;

		m.mult(scale);
		m.mult(rot);

		beginEditCP( modelTrans );
			modelTrans->setMatrix( m );
		endEditCP( modelTrans );

		beginEditCP(modelNode);
		{
			// makes the object visible
			modelNode->setTravMask(1);
		}
		endEditCP  (modelNode);
	
	}
    else
    {
		// no marker detected, hide object
		beginEditCP(modelNode);
			modelNode->setTravMask(0);
		endEditCP(modelNode);
	}


    if(showBinary)
    {      
        UInt8 * d = image->getData();
        
        for(UInt32 i = image->getWidth() * image->getHeight(); i > 0; 
                --i, d+=3)
        {
            if((d[0] + d[1] + d[2]) < thresh * 3)
                d[0] = d[1] = d[2] = 0;
            else
                d[0] = d[1] = d[2] = 255;
        }           
    }
}


// redraw the window
void display( void )
{
    // get image from camera
    grabImage(image);
    
	// detect marker in image
	detectMarker(image);
	
    // redraw the screen
    mgr->redraw();
}


int setupVideoCamera()
{
	dfg = new FrameGrabber();

	return 0;
}

int setupAR()
{
	int width = dfg->getWidth();
    int height = dfg->getHeight();
	  
#ifdef ARTOOLKITPLUS
	tracker = new ARToolKitPlus::TrackerSingleMarkerImpl<16,16,16, ARToolKitPlus::PIXEL_FORMAT_BGR, 150, 300>(width,height);
	tracker->init("camera_para.dat", 1, 1000, 0 );
	 
	tracker->setImageProcessingMode( ARToolKitPlus::IMAGE_FULL_RES );
     
	// load a marker, it´s a standard hiro pattern
	int id = tracker->arLoadPatt("patt.hiro");
#else
	ARParam param;

    arParamLoad("camera_para.dat", 1, &param);

	arParamChangeSize(&param, width, height, &cameraParam);

    arInitCparam(&cameraParam);
    arParamDisp(&cameraParam);

	// load a marker, it´s a standard hiro pattern
	int id = arLoadPatt("patt.hiro");
#endif

	return 0;
}

#ifndef ARTOOLKITPLUS
void argConvGLcpara(double cparam[3][4], int width, int height, double gnear, double gfar, double m[16]) {
	double icpara[3][4];
    double trans[3][4];
    double p[3][3], q[4][4];
    int i, j;

    if (arParamDecompMat(cparam, icpara, trans) < 0) {
      printf("gConvGLcpara: Parameter error!!\n");
      exit(0);
    }

    for (i = 0; i < 3; i++) 
      for (j = 0; j < 3; j++) 
        p[i][j] = icpara[i][j] / icpara[2][2];
        
    q[0][0] = (2.0 * p[0][0] / width);
    q[0][1] = (2.0 * p[0][1] / width);
    q[0][2] = ((2.0 * p[0][2] / width)  - 1.0);
    q[0][3] = 0.0;

    q[1][0] = 0.0;
    q[1][1] = (2.0 * p[1][1] / height);
    q[1][2] = ((2.0 * p[1][2] / height) - 1.0);
    q[1][3] = 0.0;

    q[2][0] = 0.0;
    q[2][1] = 0.0;
    q[2][2] = (gfar + gnear)/(gfar - gnear);
    q[2][3] = -2.0 * gfar * gnear / (gfar - gnear);

    q[3][0] = 0.0;
    q[3][1] = 0.0;
    q[3][2] = 1.0;
    q[3][3] = 0.0;

    for (i = 0; i < 4; i++) {
      for (j = 0; j < 3; j++) {
        m[i + j * 4] = q[i][0] * trans[0][j]
                     + q[i][1] * trans[1][j]
                     + q[i][2] * trans[2][j];
      }
      m[i + 3 * 4] = q[i][0] * trans[0][3]
                   + q[i][1] * trans[1][3]
                   + q[i][2] * trans[2][3]
                   + q[i][3];
    }
}
#endif

void setupARCameraMatrix()
{
	Matrix m;
#ifdef ARTOOLKITPLUS
	const ARFloat *p = tracker->getProjectionMatrix();

	for( int j = 0; j < 4; ++j )
		for( int i = 0; i < 4; ++i )
			m[j][i] = p[j*4+i];

	// swap y-axis, rotating 180 deg around z 
	m[0][1] = -m[0][1];
	m[1][1] = -m[1][1];
	m[2][1] = -m[2][1];
#else
	double glm[16];

	argConvGLcpara( cameraParam.mat, dfg->getWidth(), dfg->getHeight(), 1, 10000, glm );

	for( int j = 0; j < 4; ++j )
		for( int i = 0; i < 4; ++i )
			m[j][i] = glm[j*4+i];
	
	 for( int i = 0; i < 4; ++i )
        cameraParam.mat[1][i] = (cameraParam.ysize - 1)*(cameraParam.mat[2][i]) - cameraParam.mat[1][i];
      
    
	m[3][0] = 0.0;
	m[3][1] = 0.0;
	m[3][2] = 0.0;
	m[3][3] = 1.0;
#endif

	Matrix modelViewMatrix;
	osg::MatrixLookAt( modelViewMatrix, 0, 0, 0, 0, 0, 1, 0, -1, 0 );

	beginEditCP(camera);
		camera->setModelviewMatrix(modelViewMatrix);
		camera->setProjectionMatrix(m);
	endEditCP(camera);
}

// load a vrml model from disk
void loadModel()
{
	printf( "loading...\n" );

	NodePtr vrml = osg::SceneFileHandler::the().read("test.wrl");
			
	modelNode = Node::create();
	modelTrans = Transform::create();

	beginEditCP(modelNode);
	{
		modelNode->setCore(modelTrans);
		modelNode->addChild(vrml);
		modelNode->setTravMask(0);
	}
	endEditCP(modelNode);

	Vec3f bbmin,bbmax;
	vrml->getVolume(true).getBounds( bbmin, bbmax );
	std::cout << bbmin << " " << bbmax << std::endl;

	float diffX = bbmax[0]-bbmin[0];
	float diffY = bbmax[1]-bbmin[1];

	if( diffX > diffY )
		modelScale = 100.0/diffX; // 100.0 is the marker width
	else
		modelScale = 100.0/diffY; // 100.0 is the marker width

	printf( "...done.\n" );
}

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
#ifndef  __linux
	// initialize MFC
	AfxWinInit( ::GetModuleHandle( NULL ), NULL, ::GetCommandLine(), 0);
#endif
	
	// select physically connected camera
	setupVideoCamera();
	
	// setup ar tracker
	setupAR();

    // OSG init
    osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
	gwin->init();

    
    // Create the parts needed for the video background
    
    UInt32 width = dfg->getWidth();
    UInt32 height = dfg->getHeight();
    
    // get the desired size from the command line
    if(argc >= 3)
    {
        width = atoi(argv[1]);
        height = atoi(argv[2]);
    }
    
    // An OpenGL prefers textures that are power of two (POT) sizes, 
    // things are a little more complicated for non-POT (NPOT)
    // textures. The following flag shows where in the code changes 
    // need to be made for that case
    
    isPOT = osgispower2(width) && osgispower2(height);
    
    
    // To check OpenGL extensions, the Window needs to have run through
    // frameInit at least once. This automatically happens when rendering,
    // but we don't don't to wait for that here.
    gwin->activate();
    gwin->frameInit();
    
    // Now we can check for OpenGL extensions    
    hasRectTex = gwin->hasExtension("GL_ARB_texture_rectangle");
    
    // Print what we've got
    SLOG << "Got " << (isPOT?"":"non-") << "power-of-two images and "
         << (hasRectTex?"can":"cannot") << " use rectangular textures" 
         << endLog;
    
    
    // Ok, now for the meat of the code...
    // first we need an Image to hold the picture(s) to show
    image = Image::create();
    
    beginEditCP(image);
    {
        // set the image's size and type, and allocate memory
        // this example uses RGB. On some systems (e.g. Windows) BGR
        // or BGRA might be faster, it depends on how the images are 
        // acquired
		image->set(Image::OSG_BGR_PF, width, height);
    }
    endEditCP(image);
    
    // Now create the texture to be used for the background
    tex = TextureChunk::create();
    
    beginEditCP(tex);
    {
        // Associate image and texture
        tex->setImage(image);
        // Set filtering modes. LINEAR is cheap and good if the image size
        // changes very little (i.e. the window is about the same size as 
        // the images).
        tex->setMinFilter(GL_LINEAR);
        tex->setMagFilter(GL_LINEAR);        
        
        // Set the wrapping modes. We don't need repetition, it might actually
        // introduce artifactes at the borders, so switch it off.
        tex->setWrapS(GL_CLAMP_TO_EDGE);
        tex->setWrapT(GL_CLAMP_TO_EDGE);        
       
        
        if(isPOT)
        {
            // power-of-two image. Nice, nothing special to do here.
        }
        else if(hasRectTex)
        {
            // Rectangular textures are available, but they need to be 
            // explicitly enabled
            tex->setScale(false);
            tex->setTarget(GL_TEXTURE_RECTANGLE_ARB);
        }
        else
        {
            // OpenGL can only handle POT textures. When using NPOT 
            // textures they need to be embedded in a POT texture. By default
            // OpenSG scales up the image to fill the whole texture, to make 
            // repetition work. But this is very expensive and not useable
            // for images that change a lot.
            // So tell OpenSG not to scale the image. In this case, only the 
            // lower left corner of the texture will be used.
            tex->setScale(false);
        }
    }
    endEditCP(tex);
    
    // Create the background
    TextureBackgroundPtr back = TextureBackground::create();
    
    beginEditCP(back);
    {
        // Set the texture to use
        back->setTexture(tex);
        
        // Set up texture coordinates for the background
        
        if(isPOT)
        {
            // Standard texture coords for power-of-two image.
            back->getTexCoords().push_back(Pnt2f(0,0));
            back->getTexCoords().push_back(Pnt2f(1,0));
            back->getTexCoords().push_back(Pnt2f(1,1));
            back->getTexCoords().push_back(Pnt2f(0,1));
        }
        else if(hasRectTex)
        {
            // Rectangular textures have pixel-based texture
            // coordinates
            back->getTexCoords().push_back(Pnt2f(0,0));
            back->getTexCoords().push_back(Pnt2f(width-1,0));
            back->getTexCoords().push_back(Pnt2f(width-1,height-1));
            back->getTexCoords().push_back(Pnt2f(0,height-1));
        }
        else
        {
            // Using NPOT texture embedded in larger POT texture
            // Set the texcoords so that only the used part is visible
           
            Real32 w = static_cast<Real32>(width) / osgnextpower2(width);
            Real32 h = static_cast<Real32>(height) / osgnextpower2(height);
           
            back->getTexCoords().push_back(Pnt2f(0,0));
            back->getTexCoords().push_back(Pnt2f(w,0));
            back->getTexCoords().push_back(Pnt2f(w,h));
            back->getTexCoords().push_back(Pnt2f(0,h));
            
        }
    }
    endEditCP(back);
    

	TransformPtr trans;
    trans = Transform::create();
	

	// load vrml model(s) assosciated to the marker
	loadModel();
	
	rootScene = Node::create();

    beginEditCP(rootScene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
		rootScene->setCore(trans);
        rootScene->addChild(modelNode);
    }
    endEditCP  (rootScene, Node::CoreFieldMask | Node::ChildrenFieldMask);


	// create custom camera for AR
	camera = MatrixCamera::create();

	// setup camera matrix...
	setupARCameraMatrix();


    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin);
    mgr->setRoot  (rootScene);

    // replace the background
    // This has to be done after the viewport has been created, which the 
    // SSM does in setRoot().
    ViewportPtr vp = gwin->getPort()[0];
    
    beginEditCP(vp, Viewport::BackgroundFieldMask);
    {
        vp->setBackground(back);
    }
    endEditCP(vp, Viewport::BackgroundFieldMask);
    



	beginEditCP(vp, Viewport::CameraFieldMask );
	{
		vp->setCamera( camera );
	}
	endEditCP(vp, Viewport::CameraFieldMask);


    // GLUT main loop
    glutMainLoop();

    return 0;
}

#ifndef __linux
class CMyApp : public CWinApp
         {
         public:
             virtual BOOL InitInstance( ) {  return FALSE; };
			 virtual BOOL InitApplication() { return TRUE; };
         };

CMyApp theApp;
#endif

//
// GLUT callback functions
//

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
        break;
        
        case 'h':
            horAverage = !horAverage;
            break;
        
        case 'b':
            showBinary = !showBinary;
            break;
        
        case 'a':
            thresh++;
            std::cout << "Threshold at " << thresh << std::endl;
            break;
        
        case 's':
            thresh--;
            std::cout << "Threshold at " << thresh << std::endl;
            break;
    }
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize( 640, 480 );

    int winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
	
    // call the redraw function whenever there's nothing else to do
    glutIdleFunc(display);

    return winid;
}

