#include <qgl.h>
#include <qapplication.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGPassiveWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>

OSG_USING_NAMESPACE

// our widget class will be derived from QGLWidget,
// a widget offering support for plain OpenGL

class OpenSGWidget : public QGLWidget{
public:
	OpenSGWidget( QGLFormat f, QWidget *parent=0, const char *name=0 );
	SimpleSceneManager *getManager(void);

protected:
	// these replace the callback functions
	// you now from the other tutorials
	void initializeGL();
	void resizeGL(int, int);
	void paintGL();
	void mousePressEvent(QMouseEvent *ev);
	void mouseMoveEvent(QMouseEvent *ev);
	void mouseReleaseEvent(QMouseEvent *ev);
	void wheelEvent(QWheelEvent *ev);

	SimpleSceneManager *mMgr;
	// no GLUT window this time, but a passive one
	PassiveWindowPtr mPwin;
};

