#include <OSGConfig.h>

// just compile under Windows
#ifdef WIN32

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <OSGGL.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <OSGFieldContainerFactory.h>
#include <OSGSFSysTypes.h>
#include <OSGVector.h>
#include <OSGQuaternion.h>
#include <OSGMatrix.h>
#include <OSGMatrixUtility.h>
#include <OSGBoxVolume.h>
#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGSimpleGeometry.h>
#include <OSGThread.h>
#include <OSGThreadManager.h>
#include <OSGTime.h>
#include <OSGTransform.h>
#include <OSGAttachment.h>
#include <OSGMFVecTypes.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>
#include <OSGSceneFileHandler.h>
#include <OSGDirectionalLight.h>

#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGWIN32Window.h"
#include "OSGCamera.h"
#include "OSGPerspectiveCamera.h"
#include "OSGSolidBackground.h"

#if defined(__linux) || ( defined(WIN32) && ! defined(OSG_BUILD_DLL) )
#include "RAW/OSGRAWSceneFileType.h"
#endif

#include "OSGTrackball.h"

using namespace osg;


#define             NUM_THREADS 2

ThreadManager  *gThreadManager;
Thread         *drawThread[NUM_THREADS];

UInt32         drawThreadID[NUM_THREADS];

bool           drawThreadStop[NUM_THREADS],
               doResize[NUM_THREADS],
               stopIt = false;

HWND           hwnd[NUM_THREADS];

WIN32WindowPtr win[NUM_THREADS];

DrawAction     *ract;
NodePtr            root;
NodePtr            file;
PerspectiveCameraPtr cam[NUM_THREADS];
ViewportPtr    vp;
TransformPtr   cam_trans[NUM_THREADS];
Trackball      tball[NUM_THREADS];

int            lastx[NUM_THREADS],
               lasty[NUM_THREADS],
               mouseb;

double  basetime;
#define dpr std::cout << getSystemTime()-basetime << ":" << Thread::getAspect() << ":"


void display (UInt32 id)
{
    Matrix m1, m2, m3;
    Quaternion q1;

    win[id]->frameInit();
    win[id]->resizeGL();

    tball[id].getRotation().getValue(m3);
    q1.setValue(m3);
    m1.setRotate(q1);
    m2.setTranslate( tball[id].getPosition() );
    m1.mult( m2 );
    cam_trans[id]->getSFMatrix()->setValue( m1 );
    
    win[id]->drawAllViewports( ract );
    win[id]->swap();
    win[id]->frameExit();
}


void drawThreadProc (void *arg) 
{               
    int     *my_id = (int *) arg;
            
    _sleep(2+*my_id);
    dpr << "drawThread " << *my_id << " started." << std::endl;
    
    win[*my_id]->activate();
    
    // some manual init, will be moved into StateChunks later
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glEnable( GL_DEPTH_TEST );
    
    while ( ! drawThreadStop[*my_id] )
    {               
        display( *my_id );
    }
    
    win[*my_id]->deactivate();

    return;
}

LRESULT CALLBACK WndProc(HWND hwnd2, UINT uMsg,
                         WPARAM wParam, LPARAM lParam)
{
    RECT clientRect;
    int  eventThread = 0, x, y, i;

    for (i=0; i<NUM_THREADS; i++)
    {
        if ( hwnd2 == hwnd[i] )
        {
            eventThread = i;
            break;
        }
    }

    switch(uMsg)
    {       
        case WM_LBUTTONDOWN:
            mouseb |= 1 << 1;
            lastx[eventThread] = (int)LOWORD(lParam);
            lasty[eventThread] = (int)HIWORD(lParam);
            break;
        case WM_MBUTTONDOWN:
            tball[eventThread].setAutoPosition(true);
            mouseb |= 1 << 2;
            lastx[eventThread] = (int)LOWORD(lParam);
            lasty[eventThread] = (int)HIWORD(lParam);
            break;
        case WM_RBUTTONDOWN:
            tball[eventThread].setAutoPositionNeg(true);    
            mouseb |= 1 << 3;
            lastx[eventThread] = (int)LOWORD(lParam);
            lasty[eventThread] = (int)HIWORD(lParam);
            break;   
        case WM_LBUTTONUP:
            mouseb &= ~(1 << 1);
            lastx[eventThread] = (int)LOWORD(lParam);
            lasty[eventThread] = (int)HIWORD(lParam);
            break;              
        case WM_MBUTTONUP:
            tball[eventThread].setAutoPositionNeg(false); 
            mouseb &= ~(1 << 2);
            lastx[eventThread] = (int)LOWORD(lParam);
            lasty[eventThread] = (int)HIWORD(lParam);
            break;
        case WM_RBUTTONUP:
            tball[eventThread].setAutoPositionNeg(false); 
            mouseb &= ~(1 << 3);
            lastx[eventThread] = (int)LOWORD(lParam);
            lasty[eventThread] = (int)HIWORD(lParam);
            break;

        case WM_MOUSEMOVE:
            {
            Real32 w,h,a,b,c,d;
            
            x = (int)LOWORD(lParam);
            y = (int)HIWORD(lParam);
            w = win[eventThread]->getWidth();
            h = win[eventThread]->getHeight();
    
            a = -2. * ( lastx[eventThread] / w - .5 );
            b = -2. * ( .5 - lasty[eventThread] / h );
            c = -2. * ( x / w - .5 );
            d = -2. * ( .5 - y / h );
                    
            if ( mouseb & ( 1 << 1 ) )
            {
                dpr << "Left button dragged" << std::endl;
                tball[eventThread].updateRotation( a, b, c, d );
            }
            else if ( mouseb & ( 1 << 2 ) )
            {
                dpr << "Middle button dragged" << std::endl;
                tball[eventThread].updatePosition( a, b, c, d );
            }
            else if ( mouseb & ( 1 << 3 ) )
            {
                dpr << "Right button dragged" << std::endl;
                tball[eventThread].updatePositionNeg( a, b, c, d );
            }
            lastx[eventThread] = x;
            lasty[eventThread] = y;
            }
            break;
                                    
        case WM_KEYDOWN:
            dpr << "Key pressed: " << wParam << std::endl;
            if ( (int)wParam == VK_ESCAPE )
            {
                exit(0);
            }
            break;
                                    
        case WM_SIZE:
            dpr << "Resize: " << wParam << " " << LOWORD(lParam)
                << " " << HIWORD( lParam ) << std::endl;
            if ( win[eventThread] != NullFC)
                win[eventThread]->resize( LOWORD(lParam), HIWORD(lParam) );
            break;
                                    
        case WM_CLOSE:
            return ( DefWindowProc(hwnd2,uMsg,wParam,lParam) );
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd2, uMsg, wParam, lParam);
    }
    return 0;
}

int main (int argc, char **argv)
{   
    WNDCLASS  wndClass;
    PIXELFORMATDESCRIPTOR   pfd;    
    HDC           hDC;
    MSG           msg;
    Int32     i,
                  iPixelFormat,
                  eventThread,
                  dummy;

    // OSG init

    osgInit(argc,argv);
    basetime = getSystemTime();
    gThreadManager = ThreadManager::the();  

    SceneFileHandler::the().print();

    // create the graph

    // beacon for camera and light  
    NodePtr b1n = Node::create();
    GroupPtr b1 = Group::create();
    beginEditCP(b1n);
    b1n->setCore( b1 );
    endEditCP(b1n);

    

    // light
    
    NodePtr dlight = Node::create();
    DirectionalLightPtr dl = DirectionalLight::create();
    
    beginEditCP(dlight);
    dlight->setCore( dl );
    endEditCP(dlight);
    
    beginEditCP(dl);
    dl->setAmbient( .3, .3, .3, 1 );
    dl->setDiffuse( 1, 1, 1, 1 );
    dl->setDirection(0,0,1);
    dl->setBeacon( b1n);
    endEditCP(dl);

    // root
    root = Node::create();
    GroupPtr gr1 = Group::create();
    beginEditCP(root);
    root->setCore( gr1 );
    
    root->addChild( dlight );
    endEditCP(root);
    
        // Load the file

    NodePtr file = NullFC;
    
    if ( argc > 1 )
        file = SceneFileHandler::the().read(argv[1]);
    
    if ( file == NullFC )
    {
        std::cerr << "Couldn't load file, ignoring" << std::endl;
        file = makeTorus( .5, 2, 16, 16 );
    }
    
    file->updateVolume();

    Vec3f min,max;
    file->getVolume().getBounds( min, max );
    
    std::cout << "Volume: from " << min << " to " << max << std::endl;

    beginEditCP(dlight);
    dlight->addChild( file );
    endEditCP(dlight);       
    
    // Background
    SolidBackgroundPtr bkgnd = SolidBackground::create();
    
    // Action
    
    ract = DrawAction::create();

    // tball

    Vec3f pos( 0, 0, max[2] + ( max[2] - min[2] ) * 1.5 );

    for ( i = 0; i < NUM_THREADS; i++ )
    {
        // transformation
        NodePtr t1n = Node::create();
        TransformPtr t1 = Transform::create();
        beginEditCP(t1n);
        t1n->setCore( t1 );
        t1n->addChild( b1n );
        endEditCP(t1n);
        cam_trans[i] = t1;      
        
        beginEditCP( root );
        root->addChild( t1n );
        endEditCP( root );
        
        // Camera
        cam[i] = PerspectiveCamera::create();

        cam[i]->setBeacon( t1n );
        cam[i]->setFov( deg2rad( 60 ) );
        cam[i]->setNear( 0.1 );
        cam[i]->setFar( 10000 );
        
        tball[i].setMode( Trackball::OSGObject );
        tball[i].setStartPosition( pos, true );
        tball[i].setSum( true );
        tball[i].setTranslationMode( Trackball::OSGFree );
    }

    // Win32 Init

    memset(&wndClass, 0, sizeof(wndClass));
    //wndClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = WndProc;
    wndClass.hInstance = GetModuleHandle(NULL);
    // doesn't compile?!? wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.lpszClassName = "testWindowMTWIN32";
    if (!RegisterClass(&wndClass)) 
    {
        return FALSE;
    }

    memset(&pfd, 0, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.iLayerType = PFD_MAIN_PLANE;
    pfd.cDepthBits = 16;            
    
    // Create Windows
    
    for ( i = 0; i < NUM_THREADS; i++ )
    {   
        // Create a Window
        hwnd[i] = CreateWindow( "testWindowMTWIN32", "testWindowMTWIN32",
                    WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                    CW_USEDEFAULT, 
                    0, 
                    CW_USEDEFAULT, 
                    0,
                    NULL, 
                    NULL, 
                    GetModuleHandle(NULL), 
                    0 );
        hDC = GetDC(hwnd[i]);
        iPixelFormat = ChoosePixelFormat(hDC, &pfd);
        SetPixelFormat(hDC, iPixelFormat, &pfd);
        
        ShowWindow( hwnd[i], SW_SHOWNORMAL );
        SetActiveWindow( hwnd[i] );
    
        // init the OSG window  
        win[i] = WIN32Window::create();
        win[i]->setHdc ( hDC );
        win[i]->setHwnd ( hwnd[i] );
        
        // Viewport
        ViewportPtr vp = Viewport::create();
        vp->setCamera( cam[i] );
        vp->setRoot( root );
        vp->setSize( 0,0, 1,1 );                
        win[i]->addPort( vp );
        
        win[i]->init();
    }
    
    for (i = 0; i < NUM_THREADS; i++)
    {               
        // reset thread stop/resize notify variables
        drawThreadStop[i] = false;

        // get new thread
        drawThread[i] = Thread::get(NULL);
        if ( drawThread[i] != NULL )
        {      
            drawThreadID[i] = i;
            drawThread[i]->runFunction( drawThreadProc, 0, (void *) &(drawThreadID[i]) );
        }
    }

    // main loop 
    while ( GetMessage(&msg, NULL, 0, 0) )
        DispatchMessage(&msg);
     
    for ( i=0; i<NUM_THREADS; i++ )
    {
        drawThreadStop[i] = 1;
        Thread::join( drawThread[i] );
    }

    return (0);
}

// just compile under Windows
#endif
