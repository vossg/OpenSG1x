/****************************************************************************
** Form interface generated from reading ui file 'OSGMainView_qt.ui'
**
** Created: Sat Oct 6 15:45:58 2001
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef OSGMAINVIEW_H
#define OSGMAINVIEW_H

#include <qvariant.h>
#include <qmainwindow.h>
#include "OSGSceneView_qt.h"
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QAction;
class QActionGroup;
class QToolBar;
class QPopupMenu;
class QTabWidget;

class OSGMainView : public QMainWindow
{ 
    Q_OBJECT

public:
    OSGMainView( QWidget* parent = 0, const char* name = 0, WFlags fl = WType_TopLevel );
    ~OSGMainView();

    QTabWidget* tabView;
    QMenuBar *menubar;
    QPopupMenu *fileMenu;
    QPopupMenu *helpMenu;
    QToolBar *toolBar;
    QToolBar *Toolbar;
    QAction* fileNewAction;
    QAction* fileOpenAction;
    QAction* fileSaveAction;
    QAction* fileSaveAsAction;
    QAction* filePrintAction;
    QAction* fileExitAction;
    QAction* helpContentsAction;
    QAction* helpIndexAction;
    QAction* helpAboutAction;
    QAction* createViewAction;
    QAction* fileInsertAction;


public slots:
    virtual void init();
    virtual void destroy();
    virtual void fileExit();
    virtual void fileNew();
    virtual void fileOpen();
    virtual void fileInsert();
    virtual void filePrint();
    virtual void fileSave();
    virtual void fileSaveAs();
    virtual void helpAbout();
    virtual void helpContents();
    virtual void helpIndex();
    virtual void createView();

protected:
    QHBoxLayout* OSGMainViewLayout;

    osg::NodePtr root;
    OSGSceneView *sceneView;
};

#endif // OSGMAINVIEW_H
