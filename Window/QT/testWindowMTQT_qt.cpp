
// An early example showing how to do multi-threaded rendering in Qt
// 
// This is by no means a prototype on how to do it, quite the contrary.
// It only uses ont aspect due to some synch problems we're working on,
// so don't do it like this. It's just to prove that it's possible.

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
#pragma reset woff 1375
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
#include <OSGThread.h>
#include <OSGThreadManager.h>
#include <OSGBarrier.h>
#include <OSGFunctors.h>
#include <OSGTime.h>
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
#include "OSGGradientBackground.h"

#if defined(__linux)
#include "OSGRAWSceneFileType.h"
#endif

#include "OSGTrackball.h"

using namespace OSG;

class MyOSGQGLWidget : public OSGQGLWidget
{
    Q_OBJECT

    public:
        MyOSGQGLWidget( QWidget *parent=0, const char *name=0 );

        QTWindowPtr _osgWin;
        Bool        _stop;
 
        virtual void paintGL (void);
       
    protected:		
        virtual void resizeGL (int w, int h);
		virtual void mousePressEvent ( QMouseEvent* );
		virtual void mouseReleaseEvent ( QMouseEvent* );
		virtual void mouseMoveEvent ( QMouseEvent* );
		virtual void keyPressEvent ( QKeyEvent* );
		
		UInt32		_mouseb;
		UInt32		_lastx;
		UInt32		_lasty;
};


#define NUM_THREADS 2

ThreadManager	*gThreadManager;
Thread		    *drawThread[NUM_THREADS];

UInt32	        drawThreadID[NUM_THREADS];

Barrier 		* drawBarrier = NULL;


MyOSGQGLWidget  *glWidget[NUM_THREADS];
QApplication    *a;

DrawAction	    *ract;
NodePtr		    root;
NodePtr		    file;
ViewportPtr     vp;
TransformPtr    cam_trans;
PerspectiveCameraPtr cam;

Trackball	tball;
 

double basetime;
#define dpr cout << getSystemTime()-basetime << ":" << Thread::getAspect() << ":"

MyOSGQGLWidget::MyOSGQGLWidget ( QWidget *parent, const char *name ) :
    OSGQGLWidget( parent, name ),_stop(false)
{
}

void MyOSGQGLWidget::paintGL( void )
{
	if ( drawBarrier )
		drawBarrier->enter( NUM_THREADS + 1 );	
}

void doCamTrans ( void )
{
	Matrix m1, m2, m3;
    Quaternion q1;

    tball.getRotation().getValue(m3);
    q1.setValue(m3);
    m1.setRotate(q1);
    m2.setTranslate( tball.getPosition() );
	m1.mult( m2 );
	cam_trans->getSFMatrix()->setValue( m1 );
}

void MyOSGQGLWidget::resizeGL ( int w, int h )
{   
   if ( ! _osgWin->isResizePending() )
   {
       _osgWin->resize( w, h );
   }
   paintGL();
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
	_mouseb |= me->button();	
	_lastx = me->x();
	_lasty = me->y();
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
	_mouseb &= me->button();
	_lastx = me->x();
	_lasty = me->y();	
}

void MyOSGQGLWidget::mouseMoveEvent ( QMouseEvent *me )
{				
	Real32 w = _osgWin->getWidth();	// force the calc to Real32
	Real32 h = _osgWin->getHeight();
	
	Real32 a = -2. * ( _lastx / w - .5 );
	Real32 b = -2. * ( .5 - _lasty / h );
	Real32 c = -2. * ( me->pos().x() / w - .5 );
	Real32 d = -2. * ( .5 - me->pos().y() / h );
					
	if ( _mouseb & LeftButton )
	{
		tball.updateRotation( a, b, c, d );
	}
	else if ( _mouseb & MidButton )
	{
		tball.updatePosition( a, b, c, d );
	}
	else if ( _mouseb & RightButton )
	{
		tball.updatePositionNeg( a, b, c, d );
	}
	_lastx = me->pos().x();
	_lasty = me->pos().y();
	
	doCamTrans();
	paintGL();
}


void MyOSGQGLWidget::keyPressEvent ( QKeyEvent *ke )
{
	if ( ke->key() == Key_Escape )
	{
		a->quit();
	}
}

void *drawThreadProc (void *arg) 
{				
	int	          *my_id = (int *) arg;
	MyOSGQGLWidget *my_widget = glWidget[*my_id];
	QTWindowPtr    my_win = my_widget->_osgWin;

	osgsleep( 2 + *my_id );
	dpr << "drawThead " << *my_id << " started." << endl;

	my_win->init(); 	// create the context
	my_win->activate(); // and activate it

	// some manual init, will be moved into StateChunks later
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	glEnable( GL_DEPTH_TEST );

	int predraw = 5; // draw some preliminary frames
	
	while ( ! my_widget->_stop )
	{
        my_win->frameInit();

		my_win->resizeGL();

		my_win->drawAllViewports( ract );

		my_win->swap();
		my_win->frameExit();
	  
	  	if ( predraw-- < 0 )
			drawBarrier->enter( NUM_THREADS + 1 );
	}

	// Destroy context
	return ( NULL );
}

int main( int argc, char **argv )
{
    Int32 i,
          retVal;

	// OSG init

    osgInit(argc, argv);
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

	NodePtr file = NullNode;
	
	if ( argc > 1 )
		file = SceneFileHandler::the().read(argv[1]);
	
	if ( file == NullNode )
	{
		cerr << "Couldn't load file, ignoring" << endl;
		file = makePlane( 2,2,2,2 );
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
	cam->setNear( 0.1 );
	cam->setFar( 10000 );

	// Background
	GradientBackgroundPtr bkgnd = GradientBackground::create();
	bkgnd->addColor( Color3f( 0,0,0 ), 0 );
	bkgnd->addColor( Color3f( 0,0,1 ), 0 );

	
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
	
	tball.setMode( Trackball::OSGObject );
	tball.setStartPosition( pos, true );
	tball.setSum( true );
	tball.setTranslationMode( Trackball::OSGFree );

    // Create Windows
    
    for ( i = 0; i < NUM_THREADS; i++ )
    {	
	    glWidget[i] = new MyOSGQGLWidget();

    	// Viewport

    	vp = Viewport::create();
    	vp->setCamera( cam );
    	vp->setBackground( bkgnd );
    	vp->setRoot( root );
    	vp->setSize( 0,0, 1,1 );

		glWidget[i]->_osgWin = QTWindow::create();
		glWidget[i]->_osgWin->setGlWidget( glWidget[i] );
	    glWidget[i]->_osgWin->addPort( vp );
	    glWidget[i]->_osgWin->init();
		
		if ( i == 0 )
		{		  
			a->setMainWidget( glWidget[0] );
		}

		glWidget[i]->show();
	}
	
    for (i = 0; i < NUM_THREADS; i++)
    {	  
		drawThread[i] = 
            dynamic_cast<Thread *>(gThreadManager->getThread(NULL));

		if ( drawThread[i] != NULL )
      	{	   
			drawThreadID[i] = i;
			drawThread[i]->run( drawThreadProc, 0, (void *) &(drawThreadID[i]) );
		}
    }

	drawBarrier = gThreadManager->getBarrier( "drawBarrier" );

	glWidget[0]->paintGL();
	
	retVal = a->exec();    // execute QT main loop
	
	// stop th ethreads
    for ( i=0; i<NUM_THREADS; i++ )
	    glWidget[i]->_stop = true;

	drawBarrier->enter( NUM_THREADS + 1 );

    for ( i=0; i<NUM_THREADS; i++ )
		Thread::join( drawThread[i] );

    return (retVal);
}

#include "testWindowMTQT_qt_moc.cpp"
