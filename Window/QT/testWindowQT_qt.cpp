#include <OSGConfig.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#ifdef __sgi
#pragma set woff 1375
#endif

#include <qapplication.h>

#ifdef __sgi
#pragma set woff 1375
#endif

// Single-threaded QT example

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
#include <OSGMFVecTypes.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>
#include <OSGSceneFileHandler.h>
#include <OSGDirectionalLight.h>
#include <OSGSimpleGeometry.h>

#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGQTWindow.h"
#include "OSGCamera.h"
#include "OSGPerspectiveCamera.h"
#include "OSGSolidBackground.h"
#include "OSGGradientBackground.h"

#if defined(__linux) || ( defined(WIN32) && ! defined(OSG_BUILD_DLL) )
#include "RAW/OSGRAWSceneFileType.h"
#endif

#include "OSGTrackball.h"

OSG_BEGIN_NAMESPACE

class MyOSGQGLWidget : public OSGQGLWidget
{
    Q_OBJECT

    public:
        MyOSGQGLWidget( QWidget *parent=0, const char *name=0 );

		Trackball	tball;
        QTWindowPtr osgWin;

    protected:		
        virtual void initializeGL (void);
        virtual void paintGL (void);
        virtual void resizeGL (int w, int h);
		virtual void mousePressEvent ( QMouseEvent* );
		virtual void mouseReleaseEvent ( QMouseEvent* );
		virtual void mouseMoveEvent ( QMouseEvent* );
		virtual void keyPressEvent ( QKeyEvent* );
		
		UInt32		mouseb;
		Int32		lastx;
		Int32		lasty;
};

OSG_END_NAMESPACE

using namespace OSG;

MyOSGQGLWidget  *glWidget;
QApplication    *a;

DrawAction	    *ract;
NodePtr		    root;
NodePtr		    file;
ViewportPtr     vp;
TransformPtr    cam_trans;
PerspectiveCameraPtr cam;

QTWindowPtr osgTWin;

MyOSGQGLWidget::MyOSGQGLWidget ( QWidget *parent, const char *name ) :
    OSGQGLWidget( parent, name )
{
}

void MyOSGQGLWidget::initializeGL ( void )
{
	osgWin->init(); 	// create the context
	osgWin->activate(); // and activate it
	
	// some manual init, will be moved into StateChunks later
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	glEnable( GL_DEPTH_TEST );
}

void MyOSGQGLWidget::paintGL ( void )
{
	Matrix m1, m2, m3;
    Quaternion q1;

	osgWin->frameInit();	// frame-cleanup

	tball.getRotation().getValue(m3);
    q1.setValue(m3);
    m1.setRotate(q1);
    m2.setTranslate( tball.getPosition() );
	m1.mult( m2 );
	cam_trans->getSFMatrix()->setValue( m1 );
	
	osgWin->drawAllViewports( ract );	// draw the viewports     
    osgWin->swap(); 
			
	osgWin->frameExit();	// frame-cleanup
}

void MyOSGQGLWidget::resizeGL ( int w, int h )
{   
   if ( ! osgWin->isResizePending() )
   {
        osgWin->resize( w, h );
    	osgWin->resizeGL(); // handle resize events
   }
}

void MyOSGQGLWidget::mousePressEvent ( QMouseEvent *me )
{
	switch ( me->button() ) 
	{
		case MidButton:
			tball.setAutoPosition(true);
			break;
		case RightButton:
			tball.setAutoPositionNeg(true);
			break;
	}
	mouseb |= me->button();	
	lastx = me->x();
	lasty = me->y();
}

void MyOSGQGLWidget::mouseReleaseEvent ( QMouseEvent *me )
{
	switch ( me->button() )
	{
		case MidButton:
			tball.setAutoPosition(false);
			break;
		case RightButton:
			tball.setAutoPositionNeg(false);
			break;
	}
	mouseb &= ~me->button();

	lastx = me->x();
	lasty = me->y();	
}

void MyOSGQGLWidget::mouseMoveEvent ( QMouseEvent *me )
{				
	Real32 w = osgWin->getWidth();	// force the calc to Real32
	Real32 h = osgWin->getHeight();
	
	Real32 a = -2. * ( lastx / w - .5 );
	Real32 b = -2. * ( .5 - lasty / h );
	Real32 c = -2. * ( me->pos().x() / w - .5 );
	Real32 d = -2. * ( .5 - me->pos().y() / h );
					
	if ( mouseb & LeftButton )
	{
		tball.updateRotation( a, b, c, d );
	}
	else if ( mouseb & MidButton )
	{
		tball.updatePosition( a, b, c, d );
	}
	else if ( mouseb & RightButton )
	{
		tball.updatePositionNeg( a, b, c, d );
	}

	lastx = me->pos().x();
	lasty = me->pos().y();
	
	paintGL();
}


void MyOSGQGLWidget::keyPressEvent ( QKeyEvent *ke )
{
	if ( ke->key() == Key_Escape )
	{
		a->quit();
	}
}


int main( int argc, char **argv )
{
 	// OSG init

    osgInit(argc, argv);

    SceneFileHandler::the().print();

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
		cerr << "Couldn't load file, ignoring" << endl;
		file = makeTorus( .5, 2, 16, 16 );
	}
	
	file->updateVolume();

	Vec3f min,max;
	file->getVolume().getBounds( min, max );
	
	cout << "Volume: from " << min << " to " << max << endl;

	beginEditCP(dlight);
	dlight->addChild( file );
	endEditCP(dlight);

	cerr << "Tree: " << endl;
	root->dump();

	// Camera
	PerspectiveCameraPtr cam = PerspectiveCamera::create();

	cam->setBeacon( b1n );
	cam->setFov( deg2rad( 60 ) );
	cam->setNear( 100 );
	cam->setFar( 100000 );

	// Background
	SolidBackgroundPtr bkgnd = SolidBackground::create();
	bkgnd->setColor( Color3f( 0,0,1 ) );

    // Viewport

    vp = Viewport::create();
    vp->setCamera( cam );
    vp->setBackground( bkgnd );
    vp->setRoot( root );
    vp->setSize( 0,0, 1,1 );

	
	// Action
	
	ract = DrawAction::create();

	// QT init

    QApplication::setColorSpec( QApplication::CustomColor );
	a = new QApplication( argc, argv );

	if ( !QGLFormat::hasOpenGL() )
    {
	    qWarning( "This system has no OpenGL support. Exiting." );
		return -1;
    }

	Vec3f pos( 0, 0, max[2] + ( max[2] - min[2] ) * 1.5 );

    // Create Window
 	
	glWidget = new MyOSGQGLWidget();

	glWidget->tball.setMode( Trackball::OSGObject );
	glWidget->tball.setStartPosition( pos, true );
	glWidget->tball.setSum( true );
	glWidget->tball.setTranslationMode( Trackball::OSGFree );

	glWidget->osgWin = QTWindow::create();
	glWidget->osgWin->setGlWidget( glWidget );
	glWidget->osgWin->addPort( vp );
//	glWidget->osgWin->init();

/*
	osgTWin = QTWindow::create();
	osgTWin->setGlWidget( glWidget );
	osgTWin->addPort( vp );
	osgTWin->init();
*/    

	a->setMainWidget( glWidget );
	
    a->processEvents();

	glWidget->show();
	
	return ( a->exec() );    // execute QT main loop
}

#include "testWindowQT_qt_moc.cpp"
