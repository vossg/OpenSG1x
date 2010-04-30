#include <OSGConfig.h>

#include <iostream>

#include <OSGFieldContainerFactory.h>
#include <OSGSFSysTypes.h>
#include <OSGVector.h>
#include <OSGQuaternion.h>
#include <OSGMatrix.h>
#include <OSGMatrixUtility.h>
#include <OSGBoxVolume.h>
#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGTransform.h>
#include <OSGAttachment.h>
#include <OSGSimpleGeometry.h>
#include <OSGMFVecTypes.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>
#include <OSGSceneFileHandler.h>
#include <OSGDirectionalLight.h>

#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGCoreGLWindow.h"
#include "OSGCamera.h"
#include "OSGPerspectiveCamera.h"
#include "OSGSolidBackground.h"

#include "OSGTrackball.h"

#include <Cocoa/Cocoa.h>

using namespace OSG;

CoreGLWindowPtr    win;

DrawAction    *ract;
NodePtr           root;
NodePtr           file;
ViewportPtr   vp;
TransformPtr  cam_trans;
Trackball     tball;
PerspectiveCameraPtr cam;

bool          stopIt = false;
int           lastx=0, lasty=0;

void redraw ( void )
{
    Matrix m1, m2, m3;
    Quaternion q1;

    win->frameInit();

    win->resizeGL();

    tball.getRotation().getValue(m3);
    q1.setValue(m3);
    m1.setRotate(q1);
    m2.setTranslate( tball.getPosition() );
    m1.mult( m2 );
    cam_trans->getSFMatrix()->setValue( m1 );

    win->drawAllViewports( ract );
    win->swap();
    win->frameExit();
}

@interface MyApp : NSApplication

@end

@implementation MyApp

- (void) handleMouseEvent: (NSEvent*) event
{
    Real32 w,h,a,b,c,d;

    int buttonNumber = [event buttonNumber];
    unsigned int modifierFlags = [event modifierFlags];

    // Traditionally, Apple mice just have one button. It is common practice to simulate
    // the middle and the right button by pressing the option or the control key.
    if (buttonNumber == 0)
    {
        if (modifierFlags & NSAlternateKeyMask)
            buttonNumber = 2;
        if (modifierFlags & NSControlKeyMask)
            buttonNumber = 1;
    }

    NSPoint location = [event locationInWindow];

    switch ([event type])
    {
    case NSLeftMouseDown:
    case NSRightMouseDown:
    case NSOtherMouseDown:
        lastx = static_cast<int>(location.x);
        lasty = static_cast<int>(location.y);
        switch (buttonNumber)
        {
        case 0: // left button
            break;
        case 1: // right button
            tball.setAutoPositionNeg(true);
            break;
        case 2: // middle button
            tball.setAutoPosition(true);
            break;
        }
        break;

    case NSLeftMouseUp:
    case NSRightMouseUp:
    case NSOtherMouseUp:
        switch (buttonNumber)
        {
        case 0: // left button
            break;
        case 1: // right button
            tball.setAutoPositionNeg(false);
            break;
        case 2: // middle button
            tball.setAutoPosition(false);
            break;
        }
        break;

    case NSLeftMouseDragged:
    case NSRightMouseDragged:
    case NSOtherMouseDragged:
        w = win->getWidth();
        h = win->getHeight();
        a = -2. * ( lastx / w - .5 );
        b = -2. * ( lasty / h - .5);
        c = -2. * ( location.x / w - .5 );
        d = -2. * ( location.y / h - .5 );
        switch (buttonNumber)
        {
        case 0: // left button
            tball.updateRotation( a, b, c, d );
            break;
        case 1: // right button
            tball.updatePositionNeg( a, b, c, d );
            break;
        case 2: // middle button
            tball.updatePosition( a, b, c, d );
            break;
        }
        lastx = static_cast<int>(location.x);
        lasty = static_cast<int>(location.y);
        redraw();
        break;

    default:
        break;
    }
}

- (void)keyDown:(NSEvent *)theEvent
{
    if ([[theEvent characters] length] != 1)
        return;
    switch ([[theEvent characters] characterAtIndex: 0])
    {
    case 27:
        [NSApp terminate:nil];
        break;
    case 'a':
        glDisable( GL_LIGHTING );
        redraw();
        break;
    case 's':
        glEnable( GL_LIGHTING );
        redraw();
        break;
    case 'z':
        glPolygonMode( GL_FRONT_AND_BACK, GL_POINT);
        redraw();
        break;
    case 'x':
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
        redraw();
        break;
    case 'c':
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
        redraw();
        break;
    default:
        break;
    }
}

- (void)sendEvent:(NSEvent *)anEvent
{
	switch ([anEvent type])
	{
    case NSLeftMouseDown:
    case NSRightMouseDown:
    case NSOtherMouseDown:
    case NSLeftMouseUp:
    case NSRightMouseUp:
    case NSOtherMouseUp:
    case NSLeftMouseDragged:
    case NSRightMouseDragged:
    case NSOtherMouseDragged:
		[self handleMouseEvent:anEvent];
		break;
	case NSKeyDown:
		[self keyDown:anEvent];
		break;
	default:
		[super sendEvent:anEvent];
		break;
	}
}

@end

int main (int argc, char **argv)
{
    int dummy;

    // OSG init

    osgInit(argc, argv);

    // create the graph

    // beacon for camera and light
    NodePtr b1n = Node::create();
    GroupPtr b1 = Group::create();
    beginEditCP(b1n);
    b1n->setCore( b1 );
    endEditCP(b1n);

    // transformation
    NodePtr t1n = Node::create();
    TransformPtr t1 = Transform::create();
    beginEditCP(t1n);
    t1n->setCore( t1 );
    t1n->addChild( b1n );
    endEditCP(t1n);

    cam_trans = t1;

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
    root->addChild( t1n );
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

    std::cerr << "Tree: " << std::endl;
    root->dump();

    // Camera
    PerspectiveCameraPtr cam = PerspectiveCamera::create();

    cam->setBeacon( b1n );
    cam->setFov( deg2rad( 90 ) );
    cam->setNear( 0.1 );
    cam->setFar( 100000 );

    // Background
    SolidBackgroundPtr bkgnd = SolidBackground::create();
    beginEditCP(bkgnd, SolidBackground::ColorFieldMask);
    bkgnd->setColor(Color3f(1,1,1));
    endEditCP(bkgnd, SolidBackground::ColorFieldMask);

    // Viewport

    ViewportPtr vp = Viewport::create();
    vp->setCamera( cam );
    vp->setBackground( bkgnd );
    vp->setRoot( root );
    vp->setSize( 0,0, 1,1 );

    // Action

    ract = DrawAction::create();

    // tball

    Vec3f pos( 0, 0, max[2] + ( max[2] - min[2] ) * 1.5 );

    tball.setMode( Trackball::OSGObject );
    tball.setStartPosition( pos, true );
    tball.setSum( true );
    tball.setTranslationMode( Trackball::OSGFree );

    // CoreGL init

    CGDisplayCapture(kCGDirectMainDisplay);
    CGLPixelFormatAttribute attribs[] =
    {
        kCGLPFADoubleBuffer,
        kCGLPFAFullScreen,
        kCGLPFADepthSize,
        (CGLPixelFormatAttribute)16,
        kCGLPFADisplayMask,
        (CGLPixelFormatAttribute)CGDisplayIDToOpenGLDisplayMask(kCGDirectMainDisplay),
        (CGLPixelFormatAttribute)0
    };
    CGLPixelFormatObj pixelFormatObj;
    GLint numPixelFormats;
    CGLChoosePixelFormat(attribs, &pixelFormatObj, &numPixelFormats); 

    CGLContextObj contextObj;
    CGLCreateContext(pixelFormatObj, 0, &contextObj);

    CGLDestroyPixelFormat(pixelFormatObj);

    CGLSetCurrentContext(contextObj);
    CGLSetFullScreen(contextObj);

    // Create OpenSG window
    win = CoreGLWindow::create();
    win->addPort( vp );             
    win->setContext ( contextObj );
    win->init();
    win->resize( CGDisplayPixelsWide(kCGDirectMainDisplay), CGDisplayPixelsHigh(kCGDirectMainDisplay) );

    win->activate();

    // do some OpenGL init. Will move into State Chunks later.

    glEnable( GL_DEPTH_TEST );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    redraw();

    // Create application
    [MyApp sharedApplication];

    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

    // Run the message loop
    [NSApp run];

    [pool release];

    // Cleanup
    CGLSetCurrentContext(0);
    CGLClearDrawable(contextObj);
    CGLDestroyContext(contextObj);
    CGReleaseAllDisplays();

    return (0);
}
