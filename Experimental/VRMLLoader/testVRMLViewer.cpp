#include <OSGConfig.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <unistd.h> 
#include <map>
#include <string>

#include <OSGGLUT.h>

#include <OSGTime.h>
#include <OSGFieldContainerPtr.h>
#include <OSGFieldContainerFactory.h>
#include <OSGSFSysTypes.h>
#include <OSGFieldContainerPtr.h>
#include <OSGNodePtr.h>
#include <OSGVector.h>
#include <OSGQuaternion.h>
#include <OSGMatrix.h>
#include <OSGMatrixUtility.h>
#include <OSGBoxVolume.h>
#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGThread.h>
#include <OSGTransform.h>
#include <OSGAttachment.h>
#include <OSGMFVecTypes.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>
#include <OSGRenderAction.h>
#include <OSGGeometry.h>
#include <OSGGeoFunctions.h>
#include <OSGDirectionalLight.h>
#include <OSGViewport.h>
#include <OSGCamera.h>
#include <OSGWindow.h>
#include <OSGGLUTWindow.h>
#include <OSGCamera.h>
#include <OSGPerspectiveCamera.h>
#include <OSGSolidBackground.h>
#include <OSGBaseFunctions.h>
#include <OSGTrackball.h>
#include <OSGVRMLFile.h>
#include <OSGComponentTransform.h>
#include <OSGMField.h>
#include <OSGSceneFileHandler.h>
#include <OSGAnimation.h>
#include <OSGImageForeground.h>
#include <OSGStatCollector.h>

#ifdef TUBS
#include "OSGTubsMesh.h"
#include "OSGTubs3DText.h"
#endif

OSG::NodePtr             root;
OSG::NodePtr             dlight;
OSG::DirectionalLightPtr dl;

#ifdef TUBS
OSG::OSGTubsMeshPtr pMesh;
#endif

OSG::DrawAction   *dact;
OSG::RenderAction *ract;

bool doWire = false;

OSG::NodePtr            file;

OSG::WindowPtr            win;

OSG::ComponentTransformPtr     cam_trans;

OSG::Trackball            tball;

OSG::PerspectiveCameraPtr cam;

OSG::NodePtr            t1n;
OSG::ComponentTransformPtr   t1;

OSG::NodePtr            sceneTransNode;
OSG::ComponentTransformPtr   sceneTransCore;

OSG::Animation         *animation = NULL;
vector<string>          animTargetNames;
map<const string, OSG::ComponentTransformPtr> animMap;
typedef map<const string, OSG::ComponentTransformPtr>::iterator AnimIter;
bool                    doInterpolators = false;

OSG::Time               startTime;
OSG::Time               globalTime = 0.0;

int     mouseb = 0;
int     lastx=0, lasty=0;

// --- camera animation stuff
int                        selectedCam     = 0;
int                        lastSelectedCam = 0;
OSG::MField<OSG::NodePtr>   cameraBeacons;  
//bool                 doAnim = false;
OSG::Real32                 animFraction = 0.0;
OSG::Real32                 animDelta = 0.05;
OSG::Vec3f                  startPoint, endPoint;
OSG::Quaternion             startQuat, endQuat;
OSG::Real32                 startFov, endFov;
OSG::NodePtr                stdCamNode;
OSG::ComponentTransformPtr       stdCamBeacon;

OSG::Real32                 animDuration;
OSG::Real32                 frameDuration = 0.0;
bool                        bFixedDelta = false;
int                         renderFrames     = -1;

OSG::Vec3f                  interPnt;
OSG::Quaternion             interQuat;
OSG::Real32                 interFov;

OSG::Vec3f                  flyPos;
OSG::Vec3f                  flyOri;
OSG::Matrix                 lastTBallMatrix;

bool                        bDraw = false;
 
static OSG::Pnt2f           logoPos[2] = { OSG::Pnt2f(0.0, 0.0), 
                                           OSG::Pnt2f(0.8, 0.0) };

OSG::UInt32                 uiLogoCount = 0;
OSG::ImageForegroundPtr     pLogo       = OSG::NullFC;

// --- animation creation

vector<OSG::Vec3f>      aniPositions;
vector<OSG::Quaternion> aniRotations;

// --- fps calculation

OSG::StatCollector   collector;
bool                 doStats = true;

OSG::Time              timeOld, timeNew;

enum NavMode { FLY, EXAMINE, TRACKBALL, ANIM };

NavMode  navMode;
NavMode  lastNavMode;


// background

OSG::Color3f bkgndgcol;

// --- forward declaration

OSG::Real32                 setNear = -1;

/*------------- v2a file check & read -------------------------------------*/

void loadMesh(const char *, OSG::NodePtr )
{
#ifdef TUBS
    // Mesh
    
    pMesh = OSG::OSGTubsMesh::create();
            
    pMesh->loadMesh(szFilename, 1.0);
    
    OSG::NodePtr pMeshNode = OSG::Node::create();
    
    pMeshNode->setCore(pMesh);
    
    pMeshNode->updateVolume();
    
    dlight->addChild  (pMeshNode);
    
    // Volume Mesh
    // should check first. ok for now.
    
    const OSG::BoxVolume *volMesh = (OSG::BoxVolume *) 
        &(pMeshNode->getVolume());
    
    OSG::Vec3f meshMin, meshMax;
    OSG::Pnt3f meshCenter;
    
    volMesh->getBounds(meshMin, meshMax);
    volMesh->getCenter(meshCenter);
    
    
    // Text 1
    
    OSG::NodePtr pTextNode1 = OSG::Node::create();
    
    OSG::OSGTubs3DTextPtr pText1 = OSG::OSGTubs3DText::create();
    
    pText1->loadFont("comic.ttf");
    
    pText1->setText("The Power of");
    
    pTextNode1->setCore(pText1);
    
    pTextNode1->updateVolume();
    
    
    // Volume Text
    
    // should check first. ok for now.
    const OSG::BoxVolume *volText1 = (OSG::BoxVolume *) 
        & (pTextNode1->getVolume());
    
    OSG::Vec3f text1Min, text1Max;
    
    volText1->getBounds(text1Min, text1Max);
    
    OSG::NodePtr pTextTrNode1             = 
        OSG::Node::create();
    
    OSG::ComponentTransformPtr pTextTransform1 = 
        OSG::ComponentTransform::create();
    
    pTextTrNode1->setCore(pTextTransform1);
    
    pTextTrNode1->addChild(pTextNode1);
    
    OSG::Vec3f      textScale1(0.2, 0.2, 0.2);
    OSG::Vec3f      textTrans1(0., 0., 0.);
    OSG::Quaternion textRot1;
    
    textRot1.setValueAsAxisDeg(-1., 0., 0., -90.);
    
    textTrans1[0] = -0.5 * (text1Max[0] - text1Min[0]) * 0.2;
    textTrans1[2] = meshCenter[2] + 
        (-0.8 * (meshMax[2] - meshMin[2]));
    
    beginEditCP(pTextTransform1);
    {
        pTextTransform1->setScale      (textScale1);
        pTextTransform1->setRotation   (textRot1  );
        pTextTransform1->setTranslation(textTrans1);
    }
    endEditCP  (pTextTransform1);
    
    dlight->addChild(pTextTrNode1);
    
    
    // Text 2
    
    OSG::NodePtr pTextNode2 = OSG::Node::create();
    
    OSG::OSGTubs3DTextPtr pText2 = OSG::OSGTubs3DText::create();
    
    pText2->loadFont("comic.ttf");
    
    pText2->setText("Subdivision Surfaces");
    
    pTextNode2->setCore(pText2);

    pTextNode2->updateVolume();


    // Volume Text

            // should check first. ok for now.
    const OSG::BoxVolume *volText2 = (OSG::BoxVolume *) 
        & (pTextNode2->getVolume());
        
    OSG::Vec3f text2Min, text2Max;

    volText2->getBounds(text2Min, text2Max);

    OSG::NodePtr pTextTrNode2             = 
        OSG::Node::create();

    OSG::ComponentTransformPtr pTextTransform2 = 
        OSG::ComponentTransform::create();

    pTextTrNode2->setCore(pTextTransform2);

    pTextTrNode2->addChild(pTextNode2);

    OSG::Vec3f      textScale2(0.2, 0.2, 0.2);
    OSG::Vec3f      textTrans2(0., 0., 0.);
    OSG::Quaternion textRot2;

    textRot2.setValueAsAxisDeg(-1., 0., 0., -90.);

    textTrans2[0] = -0.5 * (text2Max[0] - text2Min[0]) * 0.2;
    textTrans2[2] = 
        meshCenter[2] + (-0.8 * (meshMax[2] - meshMin[2])) +
        -1.2 * (text1Max[2] - text1Min[2]);

    beginEditCP(pTextTransform2);
    {
        pTextTransform2->setScale      (textScale2);
        pTextTransform2->setRotation   (textRot2  );
        pTextTransform2->setTranslation(textTrans2);
    }
    endEditCP  (pTextTransform2);

    dlight->addChild(pTextTrNode2);
#endif
}

bool readv2aFile(const string& filename)
{
    FILE        *f = NULL;
    bool   ok;

    if(filename[0] == '+')
    {
        cerr << "Trying to read animation file: " 
             << &(filename.c_str()[1]) << "... ";

        f = fopen( &(filename.c_str()[1]), "r" );

        if( f==NULL )
        {
            cerr << "Couldn't read animation file [" 
                 << &(filename.c_str()[1]) << "].\n";
        }
        else
        {
            ok = animation->parse(&(filename.c_str()[1]));  
        }
    }
    else
    {
        cerr << "Trying to read animation file: " 
             << filename << "... ";

        f = fopen( filename.c_str(), "r" );

        if( f==NULL )
        {
            cerr << "Couldn't read animation file [" << filename << "].\n";
        }
        else
        {
            ok = animation->parse( filename );  
        }
    }
    
        
    cerr << "Found " << animation->getNrOfInterpols() 
         << " interpolators in [" << filename << "].\n";
            
    return ok;
}


/*! Tries to read the animation file named according to the specified
    vrmlfile. The suffix is replaced by .v2a and that is tried to
    be openend. 
    If succesfull the animation data is parsed.
 */

bool tryv2aFile( const string vrmlfile )
{
    int     delimiter   = vrmlfile.find( '.' );
    string  basename    = vrmlfile.substr( 0, delimiter );
    string  v2aname     = basename + ".v2a";
    FILE    *v2afile; 
    
    if(v2aname[0] == '+')
    {
        cerr << "Trying to read animation file: " 
             << &(v2aname.c_str()[1]) << "... ";

        v2afile = fopen( &(v2aname.c_str()[1]), "r" );
    }
    else
    {
        cerr << "Trying to read animation file: " 
             << v2aname << "... ";

        v2afile = fopen( v2aname.c_str(), "r" );
    }

    if( v2afile==NULL )
    {
        cerr << "not found. No animation available.\n";
        return false;
    }   
    else 
    {
        cerr << "found. Reading animations..." << endl;
        fclose( v2afile );      
        readv2aFile( v2aname );     
        cerr << "done!\n";
        return true;
    }

}

OSG::NodePtr readModelFile( const string& modelfile )
{
    OSG::NodePtr f = OSG::NullFC;
    
    cerr << "Trying to read model [" << modelfile << "]... ";

    if(modelfile[0] == '+')
    {
        loadMesh(&(modelfile.c_str()[1]), dlight);
    }
    else
    {
        f = OSG::SceneFileHandler::the().read(modelfile.c_str(), 
                                              OSG::VRMLFile::CreateNormals);    
        
        if( f == OSG::NullFC )
        {
            cerr << "failed!\n";
            return OSG::NullFC;
        }
        else
        {
            cerr << "ok!\n";
            
            OSG::beginEditCP(dlight);
            dlight->addChild( f );
            dlight->invalidateVolume();
            OSG::endEditCP(dlight);
        }
    }

    return f;
}

/*------------- fps calculation -------------------------------------------*/

OSG::Real32 fps( OSG::Real32 frameTime )
{
    return 1000000.0/frameTime;
}

/*-------------------------------------------------------------------------*/


/*! Selects a camera 
    \param cameraNr in the range [1,nrOfCameras]
 */
void selectCamera(int cameraNr)
{
    OSG::AttachmentPtr     foundAttach = OSG::NullFC;
    OSG::NodePtr           node        = OSG::NullFC;
    OSG::ComponentTransformPtr  vrmlTrans;
    OSG::SFReal32         *fieldOfViewField;
    OSG::Real32            fieldOfView = .75;
    OSG::NamePtr           namePtr;

    if(cameraNr >= cameraBeacons.size())
        return;

    if(lastSelectedCam == cameraNr)
        return;

    selectedCam     = cameraNr;
    lastSelectedCam = cameraNr;

    node = cameraBeacons[cameraNr];
    vrmlTrans = OSG::ComponentTransformPtr::dcast( node->getCore() );

    // --- find the viewpoint attachment
    foundAttach = vrmlTrans->findAttachment(
        OSG::GenericAtt::getClassType().getGroupId());

      
    if(foundAttach != OSG::NullFC)
    {
        OSG::Field *pField = foundAttach->getField("fieldOfView");

        fieldOfViewField = static_cast<OSG::SFReal32 *>(pField);

        if(fieldOfViewField != NULL)
        {
            fieldOfView = fieldOfViewField->getValue();
        }
        else
        {
            fieldOfView = .75f;
        }
    }

    // --- find the name attachment
    namePtr = OSG::NamePtr::dcast( 
        node->findAttachment(OSG::Name::getClassType().getGroupId()) );

    cerr << "Activating viewpoint (" << cameraNr << ") : ";
    
    if(namePtr != OSG::NullFC)
    {
        cerr << namePtr->getFieldPtr()->getValue() << endl;
    }
    else
    {
        cerr << "unnamed" << endl;
    }

    cerr << "Position:    " 
         << vrmlTrans->getSFTranslation()->getValue() 
         << endl
         << "Orientation: " 
         << vrmlTrans->getSFRotation()->getValue() 
         << endl
         << "Fov:         " 
         << fieldOfView
         << endl << endl;

    cam_trans  = vrmlTrans; 
    startPoint = tball.getPosition();
    endPoint   = vrmlTrans->getSFTranslation()->getValue();
    startQuat  = tball.getRotation();
    endQuat    = vrmlTrans->getSFRotation()->getValue();
    startFov   = cam->getFov();
    endFov     = fieldOfView;
    // doAnim       = true;

    if(navMode != ANIM)
        lastNavMode = navMode;

    navMode     = ANIM;
    
    tball.setStartPosition( endPoint, true );
    tball.setStartRotation( endQuat, true );

    //tball.reset();      

    // --- set the new beacon for the camera
    OSG::beginEditCP(cam);                      
    cam->setFov(fieldOfView);
    cam->setBeacon( node );                     
    OSG::endEditCP(cam);   
    
    OSG::beginEditCP(dl);                      
    //cam->setFov(fieldOfView);
    dl->setBeacon( node );                     
    OSG::endEditCP(dl);   
         
}

/*-------------------------------------------------------------------------*/

void display(void)
{
    long        diff;
    OSG::Real32 nrOfSteps;
    
    if(bDraw == true)
    {
        win->draw  (dact);
    }
    else
    {
        win->render(ract);
    }

    // store previous time value
    timeOld = timeNew;  
    
    // get new time value
    timeNew = OSG::getSystemTime();
    
    // calc difference between previous and current time    
    diff =  timeNew - timeOld;
        
    // calc nr
    //nrOfSteps = (animDuration*1000) / ( diff/1000.0 );
    nrOfSteps = animDuration / diff;
    
//  cout << "fps: " << fps( diff ) << endl;
    
    if(!bFixedDelta)
        animDelta = 1.0/nrOfSteps;   
        
    if(renderFrames >= 0)
    {
        if(doStats)
        {
            string str;
            collector.putToString(str);
            cout << str << endl;
        }
        if(renderFrames-- == 0)
            exit(0);
        
        if((renderFrames % 10) == 0)
            cerr << renderFrames << " frames left" << endl;
    }   
}

/*-------------------------------------------------------------------------*/

void reshape( int w, int h )
{
//  cerr << "Reshape: " << w << "," << h << endl;
    win->resize(w, h);
}

void fly2examine(const OSG::Matrix &camFly, 
                 const OSG::Matrix &trackbTrans,
                       OSG::Matrix &result     )
{
    OSG::Matrix trackbTransInv;
    
    trackbTrans.inverse( trackbTransInv );
    result = trackbTrans;
    
    result.mult( camFly );
    result.mult( trackbTransInv );
}                

/*-------------------------------------------------------------------------*/

void animate(void)
{
    OSG::Matrix m1, m2, caminv, camm, m1inv, m2inv, mtemp;
    long        diff;
    OSG::Real32 nrOfSteps;

    // --- interpolate the pos, rot and fov for animation

    if(navMode == ANIM)
    {
        interPnt  = OSG::linearInterpol(startPoint,endPoint, animFraction);
        interQuat = startQuat.slerp(startQuat, endQuat, animFraction);      
        interFov  = OSG::linearInterpol(startFov, endFov, animFraction); 

        m1.setRotate   (interQuat);      
        m2.setTranslate(interPnt ); 
                
        OSG::beginEditCP(cam);
        {  
            cam->setFov(interFov);                
        }
        OSG::endEditCP  (cam);    
        
        animFraction += animDelta;

        if(animFraction > 1.0)
        {
            navMode      = EXAMINE;
            animFraction = 0.0; 
        }
        
        m2.mult( m1 );                  
        cam_trans->getSFMatrix()->setValue(m2);                       
    }
    else 
    {
        m1.setRotate   ( tball.getRotation() );
        m2.setTranslate( tball.getPosition() );                             
    }
    
    if(navMode == FLY)
    {
        m2.mult(m1);
        cam_trans->getSFMatrix()->setValue( m2 );                              
    }
    else if(navMode == EXAMINE)
    {
        cam_trans->getSFMatrix()->setValue(tball.getFullExamineMatrix());
        
    }   
    else if(navMode == TRACKBALL)
    {
        cam_trans->getSFMatrix()->setValue(tball.getFullTrackballMatrix());
    }   

    // --- interpolator animation
    
    if(bFixedDelta)
        globalTime += animDelta;
    else
        globalTime = OSG::getSystemTime() - startTime;
    
    if(doInterpolators)
    {
        animation->setRelTime(globalTime);
    }

    OSG::Thread::getCurrentChangeList()->clearAll();

    glutPostRedisplay();
}

/*-------------------------------------------------------------------------*/

// tball stuff

void motion(int x, int y)
{   
    OSG::Real32 w = win->getWidth(), h = win->getHeight();

    OSG::Real32 
        a = -2. * ( lastx / w - .5 ),
        b = -2. * ( .5 - lasty / h ),
        c = -2. * ( x / w - .5 ),
        d = -2. * ( .5 - y / h );

    if(mouseb & ( 1 << GLUT_LEFT_BUTTON))
    {
        tball.updateRotation(a, b, c, d);
    }
    else if(mouseb & (1 << GLUT_MIDDLE_BUTTON))
    {
        tball.updatePosition(a, b, c, d); 
    }
    else if (mouseb & (1 << GLUT_RIGHT_BUTTON ))
    {
        tball.updatePositionNeg(a, b, c, d);  
    }

    lastx = x;
    lasty = y;
}

/*-------------------------------------------------------------------------*/

void mouse(int button, int state, int x, int y)
{
    if ( state == 0 )
    {
        switch ( button )
        {
            case GLUT_LEFT_BUTTON:  break;
            case GLUT_MIDDLE_BUTTON:
                tball.setAutoPosition(true);
                break;
            case GLUT_RIGHT_BUTTON: 
                tball.setAutoPositionNeg(true);
                break;
        }

        mouseb |= 1 << button;
    }
    else if ( state == 1 )
    {
        switch ( button )
        {
            case GLUT_LEFT_BUTTON:  break;
            case GLUT_MIDDLE_BUTTON:
                tball.setAutoPosition(false);
                break;
            case GLUT_RIGHT_BUTTON: 
                tball.setAutoPositionNeg(false);
                break;
        }       

        mouseb &= ~(1 << button);
    }

    lastx = x;
    lasty = y;
}

/*-------------------------------------------------------------------------*/

void vis(int visible)
{
    if(visible == GLUT_VISIBLE) 
    {
        glutIdleFunc(animate);
    } 
    else 
    {
        glutIdleFunc(NULL);
    }
}

/*-------------------------------------------------------------------------*/


/*! \brief Traverses the scenegraph and checks for ComponentTransforms with
    viewpoint attachment.
    
    If there are any transformations with viewpoint attachment these
    are stored in a global vector. These transformations act as camera 
    beacons.
    
    \todo Perhaps add code for moving the collected transformations 
    under the root node of the scenegraph.
 */ 
    
OSG::Action::ResultE viewpointCheck(OSG::CNodePtr &, OSG::Action *action)
{
    OSG::NodePtr            node        = action->getActNode();
    OSG::ComponentTransformPtr   vrmlTrans   = OSG::NullFC;
    OSG::AttachmentPtr      foundAttach = OSG::NullFC;
                    
    vrmlTrans = OSG::ComponentTransformPtr::dcast(node->getCore());
        
    if(!vrmlTrans)
    {
        cerr << "ERROR! The Node " << node << " does not have a core.\n";
    }
    else
    {
        // test for a viewpoint attachment
        foundAttach = vrmlTrans->findAttachment(
            OSG::GenericAtt::getClassType().getGroupId());

        // if one is present -> the ComponentTransformation is a camera beacon
        if(foundAttach != OSG::NullFC)
        {
            OSG::Field *pField = foundAttach->getField("isViewpoint");

            if(pField != NULL)
            {
                OSG::addRefCP(node);

                cameraBeacons.push_back(node);
            }
        }   
        else
        {
            //cerr << "viewpoint has NO Viewpoint attachment.\n";
        }
    }
    
    return OSG::Action::Continue;
}

/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/

OSG::Action::ResultE wireDraw( OSG::CNodePtr &, OSG::Action * action )
{
    OSG::NodePtr node = action->getActNode();
    
    if ( doWire )
    {       
        node->updateVolume();
        const OSG::DynamicVolume& vol = node->getVolume();

        OSG::Pnt3f min,max;
        vol.getBounds( min, max );

        bool l = glIsEnabled( GL_LIGHTING );
        glDisable( GL_LIGHTING );
        
        glColor3f( .8,.8,.8 );
        glBegin( GL_LINE_LOOP );
        glVertex3f( min[0], min[1], min[2] );   
        glVertex3f( max[0], min[1], min[2] );   
        glVertex3f( max[0], max[1], min[2] );   
        glVertex3f( min[0], max[1], min[2] );   
        glVertex3f( min[0], min[1], min[2] );   
        glVertex3f( min[0], min[1], max[2] );   
        glVertex3f( max[0], min[1], max[2] );   
        glVertex3f( max[0], max[1], max[2] );   
        glVertex3f( min[0], max[1], max[2] );   
        glVertex3f( min[0], min[1], max[2] );   
        glEnd();

        glBegin( GL_LINES );
        glVertex3f( min[0], max[1], min[2] );   
        glVertex3f( min[0], max[1], max[2] );   
        glVertex3f( max[0], max[1], min[2] );   
        glVertex3f( max[0], max[1], max[2] );   
        glVertex3f( max[0], min[1], min[2] );   
        glVertex3f( max[0], min[1], max[2] );   
        glEnd();
        
        if ( l )
            glEnable( GL_LIGHTING );
    }
    
    OSG::GeometryPtr g = OSG::GeometryPtr::dcast( node->getCore() );
    
    return g->doDraw( action );
}

/*-------------------------------------------------------------------------*/

OSG::Action::ResultE calcVNormal( OSG::CNodePtr &, OSG::Action * action )
{
    OSG::NodePtr node = action->getActNode();
    OSG::GeometryPtr g = OSG::GeometryPtr::dcast( node->getCore() );

    if ( g->getNormals() == OSG::NullFC )
    {
        OSG::calcVertexNormals( g );
    }   
    
    return OSG::Action::Continue;
}

void printHelp()
{
    cerr << "\nUsage: testAnimViewer [OPTION] MODELFILE ...\n\n"
         << "  Options:\n"
         << "    -a v2afile\toptional animation file in .v2a format.\n"
         << "    -c camspeed\tspeed for the camera during viewpoint change [0.0,10.0]\n"
         << "    -n val\tnear clipping plane distance.\n"
         << "    -b imagefile\tadd logo image.\n"
         << "    -B color\tbackground color.\n"
         << "    -d delta\tuse fixed animation delta.\n"
         << "    -r \tautomatically run animation.\n"
         << "    -f nframes\trender nframes frames and exit.\n"
         << "    -s \trecord and print statistics information.\n"
         << "\n    If no -a option is specified the v2a file is automatically searched\n"
         << "    using the VRMLFILE basename (foo.wrl -> foo.v2a)\n\n"
         << "  Keys:\n"
         << "    ESC - quits the viewer\n"
         << "    a   - disables lighting\n"
         << "    s   - enables lighting\n"
         << "    z   - point mode\n"
         << "    x   - line mode (wireframe)\n"
         << "    c   - polygon mode\n"
         << "    w   - bboxes on/off\n"
         << "    f   - fly navigation\n"
         << "    e   - examine navigation\n"
         << "    p   - start/stop animation (from .v2a file)\n"
         << "    h   - prints this help\n"
         << "    SPACE - stores a viewpoint (for saving)\n"
         << "    d   - writes stored viewpoint to test.v2a\n"
         << "\n   PAGE_UP/DOWN - toggle viewpoints\n"        
         << "\n\n";
//  cerr << "\nUsage: testVRMLViewer [-a<v2afile>] [-c <camspeed>] <vrmlfile> [<vrmlfile> ...]\n";
}
/*-------------------------------------------------------------------------*/

void dumpUserAnim()
{
    ofstream f;
    int      nrOfKeys = aniPositions.size();
    OSG::Vec3f      pos;
    OSG::Vec3f      axis;
    OSG::Real32     radians;
    OSG::Quaternion rot;
    
    f.open("test.v2a");
    
    if( !f.fail() )
    {
        int i;
        
        f << "/* FHS animation file. Created by OpenSG testVRMLViewer. */\n";
        f << "\nduration 10\n";
        
        // --- write Positions
        f << "POSKEY_Pfad1 Kamera 1 Position {\n";
        
        // write keys
        f << "\tkey [ ";
        
        for( i=0; i<=nrOfKeys; ++i )
        {
            f << (1.0/nrOfKeys)*i << (i==nrOfKeys? "":", ");
        }
        f << " ]\n";
        
        // write key-values
        f << "\tkeyValue [ ";
        
        for(  i=0; i<=nrOfKeys; ++i )
        {
            pos = aniPositions[i];
            f << pos[0] << " " << pos[1] << " " << pos[2]
              << (i==nrOfKeys? "":", ");
        }
        f << " ]\n}\n\n";
        
        // --- write Rotations
        // write keys
        f << "ROTKEY_Pfad1 Kamera 1 Orientation {\n";
        f << "\tkey [ ";
        
        for(  i=0; i<=nrOfKeys; ++i )
        {
            f << (1.0/nrOfKeys)*i << (i==nrOfKeys? "":", ");
        }
        f << " ]\n";
        
        // write key-values
        f << "\tkeyValue [ ";
        
        for(  i=0; i<=nrOfKeys; ++i )
        {
            rot = aniRotations[i];
            rot.getValueAsAxisRad( axis, radians );
            f << axis[0] << " " << axis[1] << " " << axis[2] << " " << radians
              << (i==nrOfKeys? "":", ");
        }
        f << " ]\n}\n\n";
                                        
        cerr << "Animation [test.v2a] file succesfully written.\n";
        
        f.close();
        
    }
    else
        cerr << "ERROR! Could not write test.v2a.\n";
}

/*-------------------------------------------------------------------------*/

void key(unsigned char key, int , int )
{
    int cameraNr;
    OSG::Matrix m1,m2;
    OSG::Vec3f  pos;
    OSG::Vec3f  axis;
    OSG::Real32 radians;
    OSG::Quaternion ori;
    
    switch ( key )
    {
        case 27:    OSG::osgExit(); exit(0);
        case 'a':   glDisable( GL_LIGHTING );
            cerr << "Lighting disabled." << endl;
            break;
        case 's':   glEnable( GL_LIGHTING );
            cerr << "Lighting enabled." << endl;
            break;
        case 'z':   glPolygonMode( GL_FRONT_AND_BACK, GL_POINT);
            cerr << "PolygonMode: Point." << endl;
            break;
        case 'x':   glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
            cerr << "PolygonMode: Line." << endl;
            break;
        case 'c':   glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
            cerr << "PolygonMode: Fill." << endl;
            break;
        case 'w':   doWire = !doWire;
            cerr << "BBox render: " << (doWire?"on":"off") << endl;
            break;
        case 'v':
            glEnable(GL_COLOR_MATERIAL);
            cerr << "Color material on" << endl;
            break;
        case 'V':
            glDisable(GL_COLOR_MATERIAL);
            cerr << "Color material off" << endl;
            break;
        case 'b':     
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            cerr << "Blending on" << endl;
            break;
        case 'B':     
            glDisable(GL_BLEND);
            cerr << "Blending off" << endl;
            break;
        case 'f':   
            //tball.setMode( OSG::Trackball::OSGCamera );
            navMode=FLY;
                
            /* funzt halb (trans ok, rot not)
               lastTBallMatrix.setRotate( tball.getRotation() );
               m2.setTranslate( tball.getPosition() );      
               lastTBallMatrix.mult( m2 );
               */
            lastTBallMatrix.setTranslate( tball.getPosition() );    
            m2.setRotate( tball.getRotation() );
            lastTBallMatrix.mult( m2 );
                

            break;
        case 'e':   
            //tball.setMode( OSG::Trackball::OSGObject );
            navMode=EXAMINE;
            tball.setTranslationGen(OSG::Trackball::OSGOrientedTranslation);
            break;              
        case 't':   
            lastSelectedCam = -1;
            selectCamera(0);
            //tball.setMode( OSG::Trackball::OSGObject );
            navMode=TRACKBALL;
            tball.setTranslationGen(OSG::Trackball::OSGAbsoluteTranslation);
            break;              
        case 'T':
#ifdef TUBS
            if(pMesh != OSG::NullFC)
            {
                pMesh->toogleShowTessalation();
            }
#endif
            break;
        case 'R':
#ifdef TUBS
            if(pMesh != OSG::NullFC)
            {
                pMesh->toggleRenderSmooth();
            }
            break;
#endif
        case 'p':   
//            navMode = FLY;
            //tball.setMode( OSG::Trackball::OSGCamera );
            startTime = OSG::getSystemTime();
            doInterpolators = !doInterpolators;
            cerr << "doInterpolators: " 
                 << (doInterpolators?"on":"off") << endl;
            break;
        case 'h':   
            printHelp();
            break;
        case 'r':
            bDraw = !bDraw;
            break;
        case 32:    
            cerr << "creating viewpoint.\n";
            m1   = cam_trans->getSFMatrix()->getValue();
            pos.setValues( m1[3][0], m1[3][1], m1[3][2]);
            ori.setValue( m1 );
            ori.getValueAsAxisRad( axis, radians );
                
            aniPositions.push_back( pos );
            aniRotations.push_back( ori );
                                
            cout << "pos: " << pos << ", ori: " << axis << radians << endl;
                
            break;      
        case 'd':               
            dumpUserAnim();
            break;
                
            // forcing fall-through by ommiting break statement!            
        case '0':
        case '1':                   
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            cameraNr = int(key) - 48;

            cerr << "Trying to acticate : " << cameraNr 
                 << "from  | "              << key      << endl;

            selectCamera(cameraNr);     

            break;  
    }

    cerr << "Active " << selectedCam << " | " << lastSelectedCam << endl;
}

/*-------------------------------------------------------------------------*/

void specialKey(int key, int , int )
{
    switch ( key )
    {               
        // forcing fall-through by ommiting break statement!            
        case GLUT_KEY_PAGE_UP:  

            cerr << "inc camera " << selectedCam << "("
                 << cameraBeacons.size() << endl;

            if(selectedCam < cameraBeacons.size() - 1)
                selectedCam++;
            else 
                selectedCam = 0;
            
            break;              

        case GLUT_KEY_PAGE_DOWN:                        

            cerr << "dec camera " << selectedCam << "("
                 << cameraBeacons.size() << endl;

            if(selectedCam > 0)
                selectedCam--;
            else
                selectedCam = cameraBeacons.size() - 1;
            break;  

        case GLUT_KEY_UP:
            break;
        case GLUT_KEY_DOWN:
            break;  
    }

    cerr << "Trying to acticate : " << selectedCam 
         << endl;

    selectCamera(selectedCam);     

    cerr << "Active " << selectedCam << " | " << lastSelectedCam << endl;
}

void addImageForeground(const char *szFilename)
{
    if(szFilename == NULL)
        return;

    cerr << "Adding Image " << szFilename << endl; 

    if(pLogo == OSG::NullFC)
    {
        pLogo = OSG::ImageForeground::create();
    }

    if(uiLogoCount < 2)
    {
        OSG::ImageP pImage = new OSG::Image;

        pImage->read(szFilename);

        pLogo->addImage(pImage, logoPos[uiLogoCount]);

        uiLogoCount++;
    }
}
/*-------------------------------------------------------------------------*/

#ifdef WIN32


/*
*  This is the AT&T public domain source for getopt(3).  It is the code
*  which was given out at the 1985 UNIFORUM conference in Dallas.
*   
*  There is no manual page.  That is because the one they gave out at
*  UNIFORUM was slightly different from the current System V Release 2
*  manual page.  The difference apparently involved a note about the
*  famous rules 5 and 6, recommending using white space between an
*  option and its first argument, and not grouping options that have
*  arguments.  Getopt itself is currently lenient about both of these
*  things.  White space is allowed, but not mandatory, and the last option
*  in a group can have an argument.  That particular version of the man
*  page evidently has no official existence.  The current SVR2 man page
*  reflects the actual behavor of this getopt.
*/



/*LINTLIBRARY*/
#ifndef NULL
#define NULL    0
#endif
#define EOF     (-1)
#define ERR(str, chr) (opterr ? fprintf(stderr, "%s%s%c\n", argv[0], str, chr) : 0)

int     opterr = 1;
int     optind = 1;
int     optopt = 0;
char    *optarg = 0;

int
getopt(int argc, char **argv, char *opts)
{
        static int sp = 1;
        register int c;
        register char *cp;

        if(sp == 1) {
                if(optind >= argc || (argv[optind][0] != '+' &&
                   argv[optind][0] != '-') || argv[optind][1] == '\0')
                        return(EOF);
                else if(strcmp(argv[optind], "--") == 0) {
                        optind++;
                        return(EOF);
                }
                /* '+' for config options, '+' should not be in the opts list */
                if (argv[optind][0] == '+') {
                        optarg = argv[optind++] + 1;
                        return '+';
                }
        }
        optopt = c = argv[optind][sp];
        if(c == ':' || (cp=strchr(opts, c)) == NULL) {
                ERR(": illegal option -- ", c);
                if(argv[optind][++sp] == '\0') {
                        optind++;
                        sp = 1;
                }
                return('\0');
        }
        if(*++cp == ':') {
                if(argv[optind][sp+1] != '\0')
                        optarg = &argv[optind++][sp+1];
                else if(++optind >= argc) {
                        ERR(": option requires an argument -- ", c);
                        sp = 1;
                        return('\0');
                } else
                        optarg = argv[optind++];
                sp = 1;
        } else {
                if(argv[optind][++sp] == '\0') {
                        sp = 1;
                        optind++;
                }
                optarg = NULL;
        }
        return(c);
}

#endif

void checkOptions( int argc, char** argv )
{
    string      modelfile;
    bool   hasOptionA = false;
    bool   hasAnimDuration = false;
    int         option;
    
    if( argc<2 )
    {
        printHelp();
        exit(0);
    }
    
    bkgndgcol.setValuesRGB(.3, .3, 1);
    do
    {
        option = getopt( argc, argv, "a:b:c:hB:n:d:rf:s" );

        if( option != '?' )
        {
            switch( option )
            {
                case 'a':
                    hasOptionA = true;
                    readv2aFile( optarg );
                    break;
                case 'c':
                    hasAnimDuration = true;
                    animDuration = atoi( optarg );
                    break;
                case 'n':
                    setNear = atof( optarg );
                    break;
                case 'b':
                    addImageForeground(optarg);
                    break;
                case 'B':
                    bkgndgcol.setValue(optarg);
                    break;
                case 'h':
                    printHelp();
                    exit(0);
                    break;
                case 'd':
                    bFixedDelta = true;
                    animDelta = atof( optarg );
                    break;
                case 'r':
                    doInterpolators = true;
                     break;
                case 'f':
                    renderFrames = atoi( optarg );
                    break;
                case 's':
                    doStats = false;
                    break;
            }
        }
    }
    while( option != -1 );
    
    if( optind >= argc )
    {
        cerr << "No model specified for loading\n";
        printHelp();
        exit(0);
    }
    
    while( optind < argc )
    {
        modelfile = argv[optind++];
        readModelFile( modelfile );
    }
    
    // if no -a option, try to auto-load animation file
    if( !hasOptionA )
        tryv2aFile( modelfile );
    
    if( !hasAnimDuration )
        animDuration=2.0;
}   

/*-------------------------------------------------------------------------*/

int main (int argc, char **argv)
{
    OSG::osgInit(argc,argv);
        
    // GLUT init
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    int winid = glutCreateWindow("OpenSG");
    glutKeyboardFunc(key);
    glutSpecialFunc(specialKey);
    glutVisibilityFunc(vis);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);       
    glutMouseFunc(mouse);   
    glutMotionFunc(motion); 
    
    //glutIdleFunc( animate );  
    glutIdleFunc( display );    

    // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glEnable( GL_NORMALIZE );
    // OSG

    // create the graph

    animation = OSG::Animation::getAnim();

    // transformation
    t1n = OSG::Node::create();
    t1  = OSG::ComponentTransform::create();

    OSG::beginEditCP(t1n);
    {
        t1n->setCore(t1 );
    }
    OSG::endEditCP  (t1n);


    sceneTransNode  = OSG::Node::create();
    sceneTransCore  = OSG::ComponentTransform::create();

    OSG::beginEditCP(sceneTransNode);
    {
        sceneTransNode->setCore(sceneTransCore);
    }
    OSG::endEditCP  (sceneTransNode);

    // light
    
    dlight = OSG::Node::create();
    dl = OSG::DirectionalLight::create();

    OSG::beginEditCP(dlight);
    {
        dlight->setCore(dl);
    }
    OSG::endEditCP  (dlight);
    
    OSG::beginEditCP(dl);
    {
        dl->setAmbient( .3, .3, .3, 1 );
        dl->setDiffuse( 1, 1, 1, 1 );
        dl->setDirection(0,0,1);
        dl->setBeacon( t1n);
    }
    OSG::endEditCP  (dl);

    // root
    root = OSG::Node::create();

    OSG::GroupPtr gr1 = OSG::Group::create();

    OSG::beginEditCP(root);
    {
        root->setCore (gr1           );
        root->addChild(t1n           );
        root->addChild(sceneTransNode);
    }
    OSG::endEditCP  (root);

    OSG::beginEditCP(sceneTransNode);
    {
        sceneTransNode->addChild(dlight);
    }
    OSG::endEditCP  (sceneTransNode);
    
    // --- parse the command line
    checkOptions(argc, argv);

    // --- update volume of geometries parent node
    dlight->updateVolume();
    
    // should check first. ok for now.
    const OSG::BoxVolume *vol = (OSG::BoxVolume *) &dlight->getVolume();
        
    OSG::Vec3f min, max;
    OSG::Vec3f size;
    OSG::Pnt3f center;

    vol->getBounds(min, max);
    vol->getCenter(center);

    size = max - min;
    
    // Camera
    cam = OSG::PerspectiveCamera::create();

    cam->setBeacon(t1n                );
    cam->setFov   (60                 );

    cerr << "Scene size: " << size.length() << endl;
    
    if((size.length() * 4.5) > 10000.)
    {
        cam->setNear( 10 );
    }
    else if((size.length() * 4.5) > 1000.)
    {
        cam->setNear( 1 );
    }
    else if((size.length()) < 100.)
    {
        cam->setNear(0.01);
    }
    else
    {
        cam->setNear(0.1);
    }

    cam->setFar(size.length() * 4.5);
    
    if ( setNear > 0 )
        cam->setNear(setNear);
        
    // Solid Background
    OSG::SolidBackgroundPtr bkgnd = OSG::SolidBackground::create();
    bkgnd->setColor( bkgndgcol );

    // Viewport
    OSG::ViewportPtr vp = OSG::Viewport::create();

    vp->setCamera    (cam       );
    vp->setBackground(bkgnd     );
    vp->setRoot      (root      );
    vp->setSize      (0, 0, 1, 1);

    if(pLogo != OSG::NullFC)
    {
        cerr << "Added logo " << endl;

        vp->getForegrounds().push_back(pLogo);
    }
    else
    {
        cerr << "No logo available" << endl;
    }

    // Window
    cout << "GLUT winid: " << winid << endl;

    OSG::GLUTWindowPtr gwin;

    GLint glvp[4];

    glGetIntegerv( GL_VIEWPORT, glvp );

    gwin = OSG::GLUTWindow::create();

    gwin->setId  (winid);
    gwin->setSize(glvp[2], glvp[3]);

    win = gwin;

    win->addPort(vp);

    // Statistics
    
    // add optional elements
    collector.getElem(OSG::Geometry::statNTriangles);
    
    // Action
    
    dact = OSG::DrawAction::create();
    ract = OSG::RenderAction::create();

    if(doStats)
    {
        dact->setStatistics(&collector);
        ract->setStatistics(&collector);
    }
    
    // Task 2: draw wireframe bbox, if wanted
//    ract->registerEnterFunction(OSG::Geometry::getClassType(),
//                                OSG::osgFunctionFunctor2(wireDraw));

    cerr << "Testing for viewpoints...\n";                          
    
    // --- traverse graph and collect viewpoints
    OSG::Action *act1;  

    act1 = OSG::Action::create();   

    act1->registerEnterFunction(OSG::ComponentTransform::getClassType(),
                                OSG::osgTypedFunctionFunctor2CPtrRef<
                                     OSG::Action::ResultE, 
                                     OSG::CNodePtr,
                                     OSG::Action *         >(viewpointCheck));
    act1->apply(dlight);
    
    
    // --- move viewpoint nodes to be child of the root node    

    for(OSG::UInt16 i = 0; i < cameraBeacons.size(); i++)
    {
        cerr << "moving cam" << i << endl;

        cameraBeacons[i]->getParent()->subChild(cameraBeacons[i]);

        root->addChild(cameraBeacons[i]);
    }
        
    cerr << "Testing for viewpoints...done.\n";

    // tball    
    OSG::Vec3f pos(min[0] + ((max[0] - min[0]) * 0.5), 
                   min[1] + ((max[1] - min[1]) * 0.5), 
                   max[2] + ( max[2] - min[2] ) * 1.5 );

    if(cameraBeacons.size() == 0)
    {
        stdCamNode   = OSG::Node::create();      
        stdCamBeacon = OSG::ComponentTransform::create();
        
        OSG::beginEditCP(stdCamNode);
        {
            stdCamNode->setCore(stdCamBeacon);
        }
        OSG::endEditCP(stdCamNode);
        
        OSG::beginEditCP(stdCamBeacon);
        {
            stdCamBeacon->setTranslation(pos);
        }
        OSG::endEditCP(stdCamBeacon);
        
        OSG::NamePtr namePtr = OSG::Name::create();     
        
        namePtr->getFieldPtr()->setValue(string("Camera"));
        
        OSG::beginEditCP(stdCamNode);
        {
            stdCamNode->addAttachment(namePtr);
        }
        OSG::endEditCP  (stdCamNode);
        
        OSG::addRefCP          (stdCamNode);
        cameraBeacons.push_back(stdCamNode);
        
        ///cam_trans = stdCamBeacon;

        OSG::beginEditCP(root);
        {
            root->addChild(stdCamNode);
        }
        OSG::endEditCP  (root);
        
        cam_trans = stdCamBeacon;

        cam->setBeacon(stdCamNode);
    
        OSG::beginEditCP(dl);
        {
            dl->setBeacon(stdCamNode);
        }
        OSG::endEditCP  (dl);

        startPoint = pos;

        cerr << "Activating default viewpoint: ";
        cerr << "Position:    " 
             << startPoint 
             << endl
             << "Orientation: " 
             << startQuat
             << endl
             << "Fov:         " 
             << 0.75
             << endl << endl;
    }
    else
    {
        OSG::Real32    fieldOfView      = .75f;
        OSG::NodePtr   node             = cameraBeacons[0];
        OSG::SFReal32 *fieldOfViewField = NULL;
        OSG::NamePtr   namePtr;

        OSG::ComponentTransformPtr vrmlTrans = 
            OSG::ComponentTransformPtr::dcast( node->getCore() );

        // --- find the viewpoint attachment
        OSG::AttachmentPtr foundAttach = vrmlTrans->findAttachment(
            OSG::GenericAtt::getClassType().getGroupId());
        
        if(foundAttach != OSG::NullFC)
        {
            OSG::Field *pField = foundAttach->getField("fieldOfView");
            
            fieldOfViewField = static_cast<OSG::SFReal32 *>(pField);
            
            if(fieldOfViewField != NULL)
            {
                fieldOfView = fieldOfViewField->getValue();
            }
        }

        cam_trans  = vrmlTrans; 
        startPoint = vrmlTrans->getSFTranslation()->getValue();
        startQuat  = vrmlTrans->getSFRotation()->getValue();

        // --- set the new beacon for the camera
        OSG::beginEditCP(cam);                      
        {
            cam->setFov   (fieldOfView);
            cam->setBeacon(node       );                     
        }
        OSG::endEditCP  (cam);   
        
        OSG::beginEditCP(dl);                      
        {
            dl->setBeacon(node);                     
        }
        OSG::endEditCP  (dl);   

        namePtr = OSG::NamePtr::dcast( 
            node->findAttachment(OSG::Name::getClassType().getGroupId()) );

        cerr << "Activating viewpoint: ";
        
        if(namePtr != OSG::NullFC)
        {
            cerr << namePtr->getFieldPtr()->getValue() << endl;
        }
        else
        {
            cerr << "unnamed" << endl;
        }
        
        cerr << "Position:    " 
             << vrmlTrans->getSFTranslation()->getValue() 
             << endl
             << "Orientation: " 
             << vrmlTrans->getSFRotation()->getValue() 
             << endl
             << "Fov:         " 
             << fieldOfView
             << endl << endl;
    }
    
    cout << "Using camera speed: " << animDuration << "s\n";
    
    // --- check animation file data and search for target nodes

    animation->resolve(root);

    cout << "Volume: from " << min << " to " << max << endl;

    cout << "Near-Plane: "  << cam->getNear() << endl;
    cout << "Far-Plane:  "  << cam->getFar() << endl; 

    tball.setMode            (OSG::Trackball::OSGObject);
    tball.setStartPosition   (startPoint, true         );
    tball.setStartRotation   (startQuat,  true         );
    tball.setSum             (true                     );
    tball.setTranslationMode (OSG::Trackball::OSGFree  );
    tball.setTranslationScale(size.length() / 5.       );
    tball.setRotationCenter  (center);
    // run...
    
    // initial navigation mode 
    
    navMode = TRACKBALL;
    tball.setTranslationGen(OSG::Trackball::OSGAbsoluteTranslation);

//    key('e', 0, 0);   

    globalTime = 0;
    startTime = OSG::getSystemTime();
    
    glutMainLoop();
    
    return 0;
}

