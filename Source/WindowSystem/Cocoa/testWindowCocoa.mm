#include <OSGConfig.h>

#include <iostream>

#import <Cocoa/Cocoa.h>

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
#include "OSGCocoaWindow.h"
#include "OSGCamera.h"
#include "OSGPerspectiveCamera.h"
#include "OSGSolidBackground.h"

#include "OSGTrackball.h"

// This prevents warnings that "NSApplication might not
// respond to setAppleMenu" on OS X 10.4
@interface NSApplication(OpenSG)
- (void)setAppleMenu:(NSMenu *)menu;
@end

using namespace OSG;

CocoaWindowPtr    win;
DrawAction    *ract;
NodePtr           root;
NodePtr           file;
ViewportPtr   vp;
TransformPtr  cam_trans;
Trackball     tball;

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

@interface MyOpenGLView: NSOpenGLView
{
}
- (BOOL) acceptsFirstResponder;

- (void) handleMouseEvent: (NSEvent*) event;

- (void) mouseDown: (NSEvent*) event;
- (void) mouseDragged: (NSEvent*) event;
- (void) mouseUp: (NSEvent*) event;
- (void) rightMouseDown: (NSEvent*) event;
- (void) rightMouseDragged: (NSEvent*) event;
- (void) rightMouseUp: (NSEvent*) event;
- (void) otherMouseDown: (NSEvent*) event;
- (void) otherMouseDragged: (NSEvent*) event;
- (void) otherMouseUp: (NSEvent*) event;

- (void) keyDown: (NSEvent*) event;

- (void) reshape;
- (void) drawRect: (NSRect) bounds;
@end

@implementation MyOpenGLView

- (BOOL) acceptsFirstResponder
{
    return YES;
}

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

- (void) mouseDown: (NSEvent*) event
{
    [self handleMouseEvent: event];
}

- (void) mouseDragged: (NSEvent*) event
{
    [self handleMouseEvent: event];
}

- (void) mouseUp: (NSEvent*) event
{
    [self handleMouseEvent: event];
}

- (void) rightMouseDown: (NSEvent*) event
{
    [self handleMouseEvent: event];
}

- (void) rightMouseDragged: (NSEvent*) event
{
    [self handleMouseEvent: event];
}

- (void) rightMouseUp: (NSEvent*) event
{
    [self handleMouseEvent: event];
}

- (void) otherMouseDown: (NSEvent*) event
{
    [self handleMouseEvent: event];
}

- (void) otherMouseDragged: (NSEvent*) event
{
    [self handleMouseEvent: event];
}

- (void) otherMouseUp: (NSEvent*) event
{
    [self handleMouseEvent: event];
}

- (void) keyDown: (NSEvent*) event
{
    if ([[event characters] length] != 1)
        return;
    switch ([[event characters] characterAtIndex: 0])
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

- (void) reshape
{
    [self update];
    NSRect frame = [self bounds];
    win->resize(static_cast<int>(frame.size.width), static_cast<int>(frame.size.height));
}

- (void) drawRect: (NSRect) bounds
{
    redraw();
}

@end

@interface MyDelegate : NSObject

{
    NSWindow *window;
    MyOpenGLView *glView;
}

- (void) applicationWillFinishLaunching: (NSNotification*) notification;

- (BOOL) applicationShouldTerminateAfterLastWindowClosed: (NSApplication*) application;

@end

@implementation MyDelegate

- (void) dealloc
{
    [window release];
    [super dealloc];
}

- (void) applicationWillFinishLaunching: (NSNotification*) notification
{
    /* Set up the menubar */
    [NSApp setMainMenu:[[NSMenu alloc] init]];

    NSString *appName = @"testWindowCocoa";
    NSMenu *appleMenu = [[NSMenu alloc] initWithTitle:@""];

    /* Add menu items */

    NSMenu *servicesMenu = [[NSMenu alloc] initWithTitle:@""];
    NSMenuItem *menuItem = [[NSMenuItem alloc] initWithTitle:@"Services" action:nil keyEquivalent:@""];
    [menuItem setSubmenu:servicesMenu];
    [appleMenu addItem:menuItem];
    [NSApp setServicesMenu: servicesMenu];

    [appleMenu addItem:[NSMenuItem separatorItem]];

    NSString *title = [@"Hide " stringByAppendingString:appName];
    [appleMenu addItemWithTitle:title action:@selector(hide:) keyEquivalent:@"h"];

    menuItem = (NSMenuItem *)[appleMenu addItemWithTitle:@"Hide Others" action:@selector(hideOtherApplications:) keyEquivalent:@"h"];
    [menuItem setKeyEquivalentModifierMask:(NSAlternateKeyMask|NSCommandKeyMask)];

    [appleMenu addItemWithTitle:@"Show All" action:@selector(unhideAllApplications:) keyEquivalent:@""];

    [appleMenu addItem:[NSMenuItem separatorItem]];

    title = [@"Quit " stringByAppendingString:appName];
    [appleMenu addItemWithTitle:title action:@selector(terminate:) keyEquivalent:@"q"];

    /* Put menu into the menubar */
    menuItem = [[NSMenuItem alloc] initWithTitle:@"" action:nil keyEquivalent:@""];
    [menuItem setSubmenu:appleMenu];
    [[NSApp mainMenu] addItem:menuItem];

    /* Tell the application object that this is now the application menu */
    [NSApp setAppleMenu:appleMenu];

    /* Finally give up our references to the objects */
    [appleMenu release];
    [menuItem release];

    // Create the window
    window = [NSWindow alloc];
    NSRect rect = { { 0, 0 }, { 300, 300 } };
    [window initWithContentRect: rect styleMask: (NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask) backing: NSBackingStoreBuffered defer: YES];
    [window setTitle: @"testWindowCocoa"];
    [window setReleasedWhenClosed: NO];

    glView = [[MyOpenGLView alloc] autorelease];
    [glView initWithFrame: rect];
    [glView setAutoresizingMask: NSViewMaxXMargin | NSViewWidthSizable | NSViewMaxYMargin | NSViewHeightSizable];
    [[window contentView] addSubview: glView];

    NSOpenGLPixelFormatAttribute attrs[] =
    {
        NSOpenGLPFAWindow,
        NSOpenGLPFADoubleBuffer,
        NSOpenGLPFADepthSize, NSOpenGLPixelFormatAttribute(16),
        NSOpenGLPixelFormatAttribute(0)
    };
    NSOpenGLPixelFormat *pixFmt = [[NSOpenGLPixelFormat alloc] initWithAttributes: attrs];
    [glView setPixelFormat: pixFmt];

    // Create OpenSG window
    win = CocoaWindow::create();
    win->addPort( vp );
    win->setContext ( [glView openGLContext] );
    win->init();
    win->resize( 300, 300 );

    win->activate();

    // do some OpenGL init. Will move into State Chunks later.

    glEnable( GL_DEPTH_TEST );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

	// Show the window
    [window makeKeyAndOrderFront: nil];
    [window makeFirstResponder:glView];
}

- (BOOL) applicationShouldTerminateAfterLastWindowClosed: (NSApplication*) application
{
    return YES;
}

@end

// A magic method that allows applications to react to events even
// when they are not organized in a bundle
void osx_AllowForeground()
{
    ProcessSerialNumber psn = { 0, kCurrentProcess };
    TransformProcessType(&psn, kProcessTransformToForegroundApplication);
    SetFrontProcess(&psn);
}

int main(int argc, char *argv[])
{
    osx_AllowForeground();

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

    vp = Viewport::create();
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

    // Create application
    [NSApplication sharedApplication];

    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

    [NSApp setDelegate: [[MyDelegate new] autorelease]];

    // Run the message loop
    [NSApp run];

   [pool release];

    return EXIT_SUCCESS;
}
