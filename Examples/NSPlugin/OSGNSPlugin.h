/*!
 * \class OSGNSPlugin
 * \brief
 * \author Andreas Zieringer
 */
 
#include <qgl.h>
#include "qnp.h"

#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGPassiveWindow.h>

class QVBox;
class QHBox;

class OpenSGWidget : public QGLWidget
{
    Q_OBJECT
public:
    OpenSGWidget( QGLFormat f, QWidget *parent=0, const char *name=0 );
    virtual ~OpenSGWidget();

    OSG::SimpleSceneManager *getManager(void);

signals:

    void droppedFiles(const QStringList &files);
    void initializedGL(void);

protected:
    
    virtual void initializeGL();

    virtual void resizeGL( int, int );
    virtual void paintGL();
    virtual void mousePressEvent( QMouseEvent *ev );
    virtual void mouseMoveEvent( QMouseEvent *ev );
    virtual void mouseReleaseEvent( QMouseEvent *ev );
    virtual void wheelEvent( QWheelEvent *ev );
    virtual void dragEnterEvent(QDragEnterEvent *e);
    virtual void dropEvent(QDropEvent *e);

    OSG::SimpleSceneManager  *_mgr;
    OSG::PassiveWindowPtr    _pwin;
};

// -----------------------------

class OSGNSPlugin : public QNPWidget
{
    Q_OBJECT
public:
    
    OSGNSPlugin();
    virtual ~OSGNSPlugin();

    void destroyScene(void);
    OSG::NodePtr load(const QString &filename);
    void setShowTools(bool s);

    virtual void paintEvent(QPaintEvent* event);

private slots:

    void initializedGL(void);
    void showAll(void);
    void toggledHeadlight(bool s);
    void droppedFiles(const QStringList &files);

protected:

    QHBox *_tools;

private:
    
    void repaintAll(QWidget *widget);

    QVBox *_main;
    OpenSGWidget *_gl;
    OSG::NodePtr _root;
    bool _show_tools;
};

// -----------------------------

class OSGNSPluginInstance : public QNPInstance
{
    Q_OBJECT
public:

    OSGNSPluginInstance();

    virtual  QNPWidget *newWindow();
    virtual bool newStreamCreated(QNPStream *, StreamMode & smode);
    virtual void streamAsFile(QNPStream *, const char * fname);

private:

    OSGNSPlugin *_plugin;
};

// -----------------------------

class OSGNSPluginPlugin : public QNPlugin
{
public:

    OSGNSPluginPlugin();
    virtual ~OSGNSPluginPlugin();

    virtual QNPInstance* newInstance();
    virtual const char* getMIMEDescription() const;
    virtual const char * getPluginNameString() const;
    virtual const char * getPluginDescriptionString() const;

private:
    
    static bool _intialized_osg;

};
