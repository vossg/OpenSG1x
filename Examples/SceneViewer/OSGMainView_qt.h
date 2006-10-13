/****************************************************************************
** Form interface generated from reading ui file 'OSGMainView_qt.ui'
**
** Created: Fr 13. Okt 18:48:14 2006
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.1.2   edited Dec 19 11:45 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef OSGMAINVIEW_H
#define OSGMAINVIEW_H

#include <qvariant.h>
#include <qpixmap.h>
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
    QPopupMenu *PopupMenu;
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
    QActionGroup* renderOC;
    QAction* renderOCOff;
    QAction* renderOCStopAndWait;
    QAction* renderOCMultiFrame;
    QAction* renderOCHierarchicalMultiFrame;
    QActionGroup* renderShadow;
    QAction* renderShadowOff;
    QAction* renderShadowStandard;
    QAction* renderShadowPerspective;
    QAction* renderShadowDitherF;
    QAction* renderShadowPCF;
    QAction* renderShadowPCSS;
    QAction* renderShadowVariance;
    QAction* statistic;
    QAction* headlight;

public slots:
    virtual void init();
    virtual void destroyMainView();
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
    virtual void setStatistics( bool val );
    virtual void shadowOff();
    virtual void shadowStandard();
    virtual void shadowPerspective();
    virtual void shadowDither();
    virtual void shadowPCF();
    virtual void shadowPCSS();
    virtual void shadowVariance();
    virtual void ocStopAndWait();
    virtual void ocMultiFrame();
    virtual void ocHierarchicalMultiFrame();
    virtual void ocOff();
    virtual void setHeadlight(bool);

protected:
    OSGSceneView *sceneView;
    osg::NodePtr root;

    QHBoxLayout* OSGMainViewLayout;

protected slots:
    virtual void languageChange();

private:
    QPixmap image0;
    QPixmap image1;
    QPixmap image2;
    QPixmap image3;
    QPixmap image4;
    QPixmap image5;
    QPixmap image6;
    QPixmap image7;

};

#endif // OSGMAINVIEW_H
