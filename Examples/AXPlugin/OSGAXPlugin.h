/*!
 * \class OSGAXPlugin
 * \brief
 * \author Andreas Zieringer
 */
 
#include <qgl.h>
#include <qaxbindable.h>
#include <qpushbutton.h>

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

    void toggleWireframe(void);
    void setHeadlightEnabled(bool s);
    bool isHeadlightEnabled(void);
    void toggleStatistic(void);
    void toggleFullScreen(void);

signals:

    void droppedFiles(const QStringList &files);
    void initializedGL(void);
    void changedHeadlight(bool s);
    void toggleTools(void);

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
    virtual void keyPressEvent(QKeyEvent *e);

    OSG::SimpleSceneManager  *_mgr;
    OSG::PassiveWindowPtr    _pwin;

    bool _render_wireframe;
    bool _render_statistic;
    bool _fullscreen;
    QWidget *_parent;
    bool _initialized_gl;
};

// -----------------------------

class OSGAXPlugin : public QWidget, public QAxBindable
{
    Q_OBJECT
    Q_PROPERTY( QString src READ getSrc WRITE setSrc )
    Q_PROPERTY( QString from READ getFrom WRITE setFrom )
    Q_PROPERTY( QString at READ getAt WRITE setAt )
    Q_PROPERTY( QString up READ getUp WRITE setUp )
    Q_PROPERTY( QString near READ getNear WRITE setNear )
    Q_PROPERTY( QString far READ getFar WRITE setFar )
    Q_PROPERTY( QString motionFactor READ getMotionFactor WRITE setMotionFactor )

public:
    
    OSGAXPlugin(QWidget *parent = 0, const char *name = 0);
    virtual ~OSGAXPlugin();

    QAxAggregated *createAggregate();

    void destroyScene(void);
    OSG::NodePtr load(const QString &filename);
    void setShowTools(bool s);

    QString getSrc(void) const;

    QString getFrom(void) const;
    QString getAt(void) const;
    QString getUp(void) const;

    QString getNear(void) const;
    QString getFar(void) const;
    QString getMotionFactor(void) const;

public slots:
    
    void setSrc(const QString &src);

    void setFrom(const QString &fromstr);
    void setAt(const QString &atstr);
    void setUp(const QString &upstr);

    void setNear(const QString &nearstr);
    void setFar(const QString &farstr);
    void setMotionFactor(const QString &mfstr);

    void about(void);

private slots:

    void initializedGL(void);
    void showAll(void);
    void toggledHeadlight(bool s);
    void droppedFiles(const QStringList &files);
    void changedHeadlight(bool s);
    void toggleTools(void);

protected:

    QHBox *_tools;

private:

    QVBox *_main;
    QVBox        *_gl_container;
    OpenSGWidget *_gl;
    OSG::NodePtr _root;
    bool _show_tools;

    QPushButton *_headlight;
};
