#include <OSGConfig.h>

#include <iostream>

#ifdef __sgi
#pragma set woff 1375
#endif

#include <qapplication.h>

#ifdef __sgi
#pragma set woff 1375
#endif


#include <OSGSimpleSceneManager.h>
#include <OSGSimpleGeometry.h>

#include <OSGQTWindow.h>

OSG_USING_NAMESPACE

const int nwindows = 2;

class MyOSGQGLWidget : public OSGQGLWidget
{
    Q_OBJECT

    public:
        MyOSGQGLWidget( QWidget *parent=0, const char *name=0 );

        SimpleSceneManager _manager;
 
    protected:      
        virtual void initializeGL (void);
        virtual void paintGL (void);
        virtual void resizeGL (int w, int h);
        virtual void mousePressEvent ( QMouseEvent* );
        virtual void mouseReleaseEvent ( QMouseEvent* );
        virtual void mouseMoveEvent ( QMouseEvent* );
        virtual void keyPressEvent ( QKeyEvent* );
        
};

MyOSGQGLWidget  *glWidgets[nwindows];
QApplication    *a;

NodePtr             scene;

MyOSGQGLWidget::MyOSGQGLWidget ( QWidget *parent, const char *name ) :
    OSGQGLWidget( parent, name )
{
}

void MyOSGQGLWidget::initializeGL ( void )
{
    _manager.getWindow()->init();   // create the context
}

void MyOSGQGLWidget::paintGL ( void )
{
    _manager.redraw();
}

void MyOSGQGLWidget::resizeGL ( int w, int h )
{   
    _manager.resize(w, h);
    repaint();
}

void MyOSGQGLWidget::mousePressEvent ( QMouseEvent *me )
{
    UInt16 but;
    switch ( me->button() ) 
    {
    case LeftButton:    but=SimpleSceneManager::MouseLeft;   break;
    case MidButton:     but=SimpleSceneManager::MouseMiddle; break;
    case RightButton:   but=SimpleSceneManager::MouseRight;  break;
    }
    
    _manager.mouseButtonPress( but, me->pos().x(), me->pos().y() );
    repaint();
}

void MyOSGQGLWidget::mouseReleaseEvent ( QMouseEvent *me )
{
    UInt16 but;
    switch ( me->button() ) 
    {
    case LeftButton:    but=SimpleSceneManager::MouseLeft;   break;
    case MidButton:     but=SimpleSceneManager::MouseMiddle; break;
    case RightButton:   but=SimpleSceneManager::MouseRight;  break;
    }
    
    _manager.mouseButtonRelease( but, me->pos().x(), me->pos().y() );
    repaint();
}

void MyOSGQGLWidget::mouseMoveEvent ( QMouseEvent *me )
{               
    _manager.mouseMove( me->pos().x(), me->pos().y() );
    repaint();
}


void MyOSGQGLWidget::keyPressEvent ( QKeyEvent *ke )
{
    if ( ke->key() == Key_Escape )
    {
        a->quit();
    }
    repaint();
}


int main( int argc, char **argv )
{
    // OSG init

    osgInit(argc, argv);
    
    // QT init

    QApplication::setColorSpec( QApplication::CustomColor );
    a = new QApplication( argc, argv );

    if ( !QGLFormat::hasOpenGL() )
    {
        qWarning( "This system has no OpenGL support. Exiting." );
        return -1;
    }

    // Create Windows

    QGLFormat::setDefaultFormat(QGLFormat(QGL::DirectRendering | 
                                          QGL::DoubleBuffer    |  
                                          QGL::DepthBuffer     |
                                          QGL::Rgba            ));
    
    
    for(int i = 0; i < nwindows; ++i)
    {
        glWidgets[i] = new MyOSGQGLWidget();

        QTWindowPtr win = QTWindow::create();
        win->setGlWidget( glWidgets[i] );

        // note: you can't share the scene between the windows, as the SSM
        // adds it to his lightsource, and that can only be done for one
        // node (single parent paradigm).
        // If you want to do that, you have to manage the scene yourself
        // without the SSM.
        scene = makeTorus( .5, 2, 16, 16 );

        glWidgets[i]->_manager.setWindow( win );
        glWidgets[i]->_manager.setRoot( scene );
        glWidgets[i]->_manager.showAll();

        a->processEvents();

        glWidgets[i]->show();
    }

    a->setMainWidget( glWidgets[0] );
    
    return ( a->exec() );    // execute QT main loop
}

#include "testWindowQTSSM_qt_moc.cpp"
