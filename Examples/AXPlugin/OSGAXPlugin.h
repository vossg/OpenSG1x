/*!
 * \class OSGAXPlugin
 * \brief
 * \author Andreas Zieringer
 */
 
#include <qgl.h>
#include <qaxbindable.h>

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

class OSGAXPlugin : public QWidget, public QAxBindable
{
    Q_OBJECT
    Q_PROPERTY( QString src READ getSrc WRITE setSrc )

public:
    
    OSGAXPlugin(QWidget *parent = 0, const char *name = 0);
    virtual ~OSGAXPlugin();

    QAxAggregated *createAggregate();

    void destroyScene(void);
    OSG::NodePtr load(const QString &filename);
    void setShowTools(bool s);

    QString getSrc(void) const;

public slots:
    
    void setSrc(const QString &src);

private slots:

    void initializedGL(void);
    void showAll(void);
    void toggledHeadlight(bool s);
    void droppedFiles(const QStringList &files);

protected:

    QHBox *_tools;

private:

    QVBox *_main;
    OpenSGWidget *_gl;
    OSG::NodePtr _root;
    bool _show_tools;
};
