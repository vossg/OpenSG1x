#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "OSGConfig.h"
#include "OSGSimpleGeometry.h"
#include "OSGSimpleSceneManager.h"
#include "OSGAction.h"
#include "OSGSceneFileHandler.h"
#include "OSGFOXGLWidget.h"
#include "OSGFOXWindow.h"
OSG_USING_NAMESPACE

#ifdef WIN32
#pragma warning (disable : 698 47 373 383 171)
#endif

#include "fox/fxdefs.h"
#include "fox/fx.h"
#include "fox/fx3d.h"

class FOXRenderWidget : public FOXGLWidget
{
   FXDECLARE(FOXRenderWidget)

public:
    FOXRenderWidget (FXComposite* p, FXGLVisual* vis, FXObject* tgt=NULL, 
		    FXSelector sel=0, FXuint opts=0, 
		    FXint x=0, FXint y=0, FXint w=0, FXint h=0);
   ~FOXRenderWidget ();

   void    initScene    (const char* filename);
   void    setTrackball (bool flag);
   bool    getTrackball () const;

   // FOX stuff
   virtual void create ();

   // Messages
   enum {
      ID_IDLE=FOXGLWidget::ID_LAST,
      ID_LAST
   };
   // Message handlers
   long onIdle             (FXObject*, FXSelector, void*);
   long onPaint            (FXObject*, FXSelector, void*);
   long onMotion           (FXObject*, FXSelector, void*);
   long onLeftButtonPress     (FXObject*, FXSelector, void*);
   long onLeftButtonRelease   (FXObject*, FXSelector, void*);
   long onRightButtonPress    (FXObject*, FXSelector, void*);
   long onRightButtonRelease  (FXObject*, FXSelector, void*);
   long onMiddleButtonPress   (FXObject*, FXSelector, void*);
   long onMiddleButtonRelease (FXObject*, FXSelector, void*);
   long onQueryHelp         (FXObject*, FXSelector, void*);

protected:
  FOXRenderWidget () {}

#ifdef IDLE_WITH_TIMER
   static int   s_idleTimeout; //idle timeout in milliseconds
   FXTimer* m_timer;
#else
   FXChore* m_chore;
#endif

   // OSG stuff
   SimpleSceneManager* m_manager;
   NodePtr             m_content;
};

#ifdef IDLE_WITH_TIMER
int FOXRenderWidget::s_idleTimeout = 10;
#endif

// Map
FXDEFMAP(FOXRenderWidget) FOXRenderWidgetMap[] = {
  FXMAPFUNC(SEL_PAINT,               0,                    FOXRenderWidget::onPaint),
  FXMAPFUNC(SEL_MOTION,              0,                    FOXRenderWidget::onMotion),
  FXMAPFUNC(SEL_LEFTBUTTONPRESS,     0,                    FOXRenderWidget::onLeftButtonPress),
  FXMAPFUNC(SEL_LEFTBUTTONRELEASE,   0,                    FOXRenderWidget::onLeftButtonRelease),
  FXMAPFUNC(SEL_MIDDLEBUTTONPRESS,   0,                    FOXRenderWidget::onMiddleButtonPress),
  FXMAPFUNC(SEL_MIDDLEBUTTONRELEASE, 0,                    FOXRenderWidget::onMiddleButtonRelease),
  FXMAPFUNC(SEL_RIGHTBUTTONPRESS,    0,                    FOXRenderWidget::onRightButtonPress),
  FXMAPFUNC(SEL_RIGHTBUTTONRELEASE,  0,                    FOXRenderWidget::onRightButtonRelease),
# ifdef IDLE_WITH_TIMER
  FXMAPFUNC(SEL_TIMEOUT,             FOXRenderWidget::ID_IDLE,    FOXRenderWidget::onIdle),
# else
  FXMAPFUNC(SEL_CHORE  ,             FOXRenderWidget::ID_IDLE,    FOXRenderWidget::onIdle),
# endif
  FXMAPFUNC(SEL_UPDATE,              FXWindow::ID_QUERY_HELP, FOXRenderWidget::onQueryHelp)
};
// Object implementation
FXIMPLEMENT(FOXRenderWidget, 
	    FOXGLWidget, 
	    FOXRenderWidgetMap, 
	    ARRAYNUMBER(FOXRenderWidgetMap))


FOXRenderWidget::FOXRenderWidget (FXComposite* p, FXGLVisual* vis, FXObject* tgt, FXSelector sel, FXuint opts, 
		      FXint x, FXint y, FXint w, FXint h)
  : FOXGLWidget(p, vis, tgt, sel, opts, x, y, w, h), 
    m_manager(NULL)
#ifdef IDLE_WITH_TIMER
  , m_timer(NULL)
#else
  , m_chore(NULL)
#endif
{
}

FOXRenderWidget::~FOXRenderWidget ()
{
   delete m_manager;
}

void FOXRenderWidget::initScene (const char* filename)
{
   m_content = SceneFileHandler::the().read(filename);
   if (m_content == NullFC) {
      m_content = makeTorus(.5, 2, 16, 16);
   }

   m_manager->setRoot(m_content);
   m_manager->showAll();
}

void FOXRenderWidget::create ()
{
   FOXGLWidget::create();
   if (makeCurrent()) {
      glEnable(GL_NORMALIZE);
      glShadeModel(GL_SMOOTH);
      glDisable(GL_CULL_FACE);
      glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

      // create the SimpleSceneManager helper
      m_manager = new SimpleSceneManager;

      // tell the manager what to manage
      m_manager->setWindow(getWindow());
   }
}

// mouse callbacks
long FOXRenderWidget::onMotion (FXObject*, FXSelector, void* ptr)
{
   FXEvent* event = (FXEvent*)ptr;
   int x = event->win_x;
   int y = event->win_y;

   m_manager->mouseMove(x, y);
   update();
   return 1;
}
long FOXRenderWidget::onLeftButtonPress (FXObject*, FXSelector, void* ptr)
{
   FXEvent* event = (FXEvent*)ptr;
   int x = event->win_x;
   int y = event->win_y;
#ifdef IDLE_WITH_TIMER
   if (m_timer != NULL) {
      getApp()->removeTimeout(m_timer);
   }
#else
   if (m_chore != NULL) {
      getApp()->removeChore(m_chore);
   }
#endif

   m_manager->mouseButtonPress(SimpleSceneManager::MouseLeft, x, y);
   return 1;
}
long FOXRenderWidget::onLeftButtonRelease (FXObject*, FXSelector, void* ptr)
{
   FXEvent* event = (FXEvent*)ptr;
   int x = event->win_x;
   int y = event->win_y;
#ifdef IDLE_WITH_TIMER
   m_timer = getApp()->addTimeout(s_idleTimeout, this, ID_IDLE);
#else
   m_chore = getApp()->addChore(this, ID_IDLE);
#endif

   m_manager->mouseButtonRelease(SimpleSceneManager::MouseLeft, x, y);
   update();
   return 1;
}
long FOXRenderWidget::onRightButtonPress (FXObject*, FXSelector, void* ptr)
{
   FXEvent* event = (FXEvent*)ptr;
   int x = event->win_x;
   int y = event->win_y;
#ifdef IDLE_WITH_TIMER
   if (m_timer != NULL) {
      getApp()->removeTimeout(m_timer);
   }
#else
   if (m_chore != NULL) {
      getApp()->removeChore(m_chore);
   }
#endif

   m_manager->mouseButtonPress(SimpleSceneManager::MouseRight, x, y);
   return 1;
}
long FOXRenderWidget::onRightButtonRelease (FXObject*, FXSelector, void* ptr)
{
   FXEvent* event = (FXEvent*)ptr;
   int x = event->win_x;
   int y = event->win_y;
#ifdef IDLE_WITH_TIMER
   m_timer = getApp()->addTimeout(s_idleTimeout, this, ID_IDLE);
#else
   m_chore = getApp()->addChore(this, ID_IDLE);
#endif

   m_manager->mouseButtonRelease(SimpleSceneManager::MouseRight, x, y);
   update();
   return 1;
}
long FOXRenderWidget::onMiddleButtonPress (FXObject*, FXSelector, void* ptr)
{
   FXEvent* event = (FXEvent*)ptr;
   int x = event->win_x;
   int y = event->win_y;
#ifdef IDLE_WITH_TIMER
   if (m_timer != NULL) {
      getApp()->removeTimeout(m_timer);
   }
#else
   if (m_chore != NULL) {
      getApp()->removeChore(m_chore);
   }
#endif

   m_manager->mouseButtonPress(SimpleSceneManager::MouseMiddle, x, y);
   return 1;
}
long FOXRenderWidget::onMiddleButtonRelease (FXObject*, FXSelector, void* ptr)
{
   FXEvent* event = (FXEvent*)ptr;
   int x = event->win_x;
   int y = event->win_y;
#ifdef IDLE_WITH_TIMER
   m_timer = getApp()->addTimeout(s_idleTimeout, this, ID_IDLE);
#else
   m_chore = getApp()->addChore(this, ID_IDLE);
#endif

   m_manager->mouseButtonRelease(SimpleSceneManager::MouseMiddle, x, y);
   update();
   return 1;
}

void FOXRenderWidget::setTrackball (bool flag) 
{
   m_manager->setNavigationMode((flag ? Navigator::TRACKBALL : Navigator::FLY));
}
bool FOXRenderWidget::getTrackball () const
{
   return (m_manager->getNavigator()->getMode()==Navigator::TRACKBALL);
}

// status message
long FOXRenderWidget::onQueryHelp  (FXObject* sender, FXSelector, void*)
{
   FXString statusText = "";
   sender->handle(this, MKUINT(ID_SETSTRINGVALUE, SEL_COMMAND), &statusText);
   return 1;
}

// redraw and idle callbacks
long FOXRenderWidget::onPaint (FXObject*, FXSelector, void*)
{
   m_manager->redraw();
   return 1;
}

long FOXRenderWidget::onIdle (FXObject*, FXSelector, void*)
{

#ifdef IDLE_WITH_TIMER
   m_timer = getApp()->addTimeout(s_idleTimeout, this, ID_IDLE);
#else
   m_chore = getApp()->addChore(this, ID_IDLE);
#endif
   return 1;
}

class FOXMainWindow : public FXMainWindow
{
  FXDECLARE(FOXMainWindow)

public:
  FOXMainWindow (FXApp* a);

  virtual void create();

  // Messages
  enum {
     ID_OPEN = FXMainWindow::ID_LAST,
     ID_TRACKBALL,
     ID_ABOUT,
     ID_LAST
  };

  // Message handlers
  long onCmdOpen         (FXObject*, FXSelector, void*);
  long onCmdTrackball    (FXObject*, FXSelector, void*);
  long onUpdTrackball    (FXObject*, FXSelector, void*);
  long onCmdAbout        (FXObject*, FXSelector, void*);

protected:
  FOXMainWindow() {}
  
  FXToolTip*         tooltip;
  FXMenuBar*         menubar;
  FXMenuPane*        filemenu;
  FXMenuPane*        optionsmenu;
  FXMenuPane*        helpmenu;
  FXStatusBar*       status;
  FXPacker*          content;
  FXGLVisual*        visual;
  FOXRenderWidget*   widget;
};

// Map
FXDEFMAP(FOXMainWindow) FOXMainWindowMap[] = {
  FXMAPFUNC(SEL_COMMAND,  FOXMainWindow::ID_OPEN,          FOXMainWindow::onCmdOpen),
  FXMAPFUNC(SEL_COMMAND,  FOXMainWindow::ID_TRACKBALL,     FOXMainWindow::onCmdTrackball),
  FXMAPFUNC(SEL_UPDATE,   FOXMainWindow::ID_TRACKBALL,     FOXMainWindow::onUpdTrackball),
  FXMAPFUNC(SEL_COMMAND,  FOXMainWindow::ID_ABOUT,         FOXMainWindow::onCmdAbout)
};

// Object implementation
FXIMPLEMENT(FOXMainWindow, FXMainWindow, FOXMainWindowMap, ARRAYNUMBER(FOXMainWindowMap))

FOXMainWindow::FOXMainWindow (FXApp* a)
  : FXMainWindow(a, "testFOXWindow", NULL, NULL, DECOR_ALL, 0,0,900,600)
{
  menubar = new FXMenuBar(this, LAYOUT_SIDE_TOP);
  
  // File menu
  filemenu=new FXMenuPane(this);
  new FXMenuCommand(filemenu, "&Open\tCtl-O\tOpen scene.",
		    NULL, this, ID_OPEN, 0);
  new FXMenuCommand(filemenu, "&Quit\tCtl-Q\tQuit application.",
		    NULL, getApp(), FXApp::ID_QUIT, 0);
  new FXMenuTitle(menubar, "&File", NULL, filemenu);

  // Options menu
  optionsmenu=new FXMenuPane(this);
  new FXMenuCommand(optionsmenu, "&Trackball\tCtl-T\tTrackball/Fly",
		    NULL, this, ID_TRACKBALL, 0);
  new FXMenuTitle(menubar, "&Options", NULL, optionsmenu);

  // Help menu
  helpmenu=new FXMenuPane(this);
  new FXMenuTitle(menubar,    "&Help",NULL, helpmenu, LAYOUT_RIGHT);
  new FXMenuCommand(helpmenu, "&About OpenSG Viewer...\t\tDisplay about message.",
		    NULL, this, ID_ABOUT, 0);

  // Tooltips
  tooltip = new FXToolTip(getApp(),0,100,100);

  // Status bar
  status   = new FXStatusBar(this, LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X|STATUSBAR_WITH_DRAGCORNER);

  content = new FXPacker(this,
			 LAYOUT_SIDE_RIGHT|LAYOUT_FILL_X|LAYOUT_FILL_Y);

  // OpenGL visual
  visual = new FXGLVisual(getApp(), VISUAL_DOUBLEBUFFER);
  visual->setAlphaSize(8);
  visual->setStencilSize(0);
  visual->setAccumRedSize(0);
  visual->setAccumGreenSize(0);
  visual->setAccumBlueSize(0);
  visual->setAccumAlphaSize(0);

  // FOX widget and OpenSG window
  widget = new FOXRenderWidget(content, visual, NULL, 0, LAYOUT_FILL_X|LAYOUT_FILL_Y);
  FOXWindowPtr win = FOXWindow::create();
  // widget references window
  widget->setWindow(win);
  // and window references widget
  win->setGlWidget(widget);
}

long FOXMainWindow::onCmdAbout(FXObject*,FXSelector,void*)
{
   static char status[1000];
   sprintf(status, 
	   "FOXWindow for OpenSG"
	   "\nChristoph Fuenfzig, TU Braunschweig"
	   "\n\n   Color (%d/%d/%d/%d)"
	   "\n   Accum (%d/%d/%d/%d)"
	   "\n   Depth   %d"
	   "\n   Stencil %d"
	   "\n   %s"
	   "\n   %s",
	   visual->getActualRedSize(),
	   visual->getActualGreenSize(),
	   visual->getActualBlueSize(),
	   visual->getActualAlphaSize(),
	   visual->getActualAccumRedSize(),
	   visual->getActualAccumGreenSize(),
	   visual->getActualAccumBlueSize(),
	   visual->getActualAccumAlphaSize(),
	   visual->getActualDepthSize(),
	   visual->getActualStencilSize(),
	   (visual->isDoubleBuffer() ? "Double buffered" : "Single buffered"),
	   (visual->isStereo()       ? "Stereo" : "NoStereo"));
   FXMessageBox::information(this, MBOX_OK, 	   
			     "About testFOXWindow", status);
   return 1;
}

long FOXMainWindow::onCmdTrackball (FXObject*, FXSelector, void*)
{
   widget->setTrackball(!widget->getTrackball());
   return 1;
}
long FOXMainWindow::onUpdTrackball (FXObject* sender, FXSelector, void*)
{
   sender->handle(this,
		  MKUINT(FXWindow::ID_SETVALUE, SEL_COMMAND),
		  (void*)widget->getTrackball());
   return 1;
}

// access()
#ifdef WIN32
# include <io.h>
# define access _access
#else
# include <unistd.h> 
#endif
long FOXMainWindow::onCmdOpen (FXObject*, FXSelector, void*)
{
   FXFileDialog dlgFilename(this, "Open Scene");
   FXString pattern;
   FXString all("All supported scenes (");
   list<const char*> suffixList;
   SceneFileHandler::the().getSuffixList(suffixList);
   for (list<const char*>::iterator sI = suffixList.begin(); 
	sI != suffixList.end(); 
	sI++) {
      pattern += "\n";
      pattern += *sI;
      pattern += " (";
      pattern += "*.";
      pattern += *sI;
      pattern += ")";

      if (sI == suffixList.begin()) {
	 all += "*.";
      } else {
	 all += ",*.";
      }
      all += *sI;
   }
   all += ")";
   dlgFilename.setPatternList(all + pattern);
   if (!dlgFilename.execute()) {
      return 0;
   }
   FXString filename = dlgFilename.getFilename();

   // check if we may read the file
   if (access(filename.text(), 4)) {
      char msg[100];
      sprintf(msg, "Cannot access the file\n'%s'\nfor reading!", filename.text());
      FXMessageBox(this, "Problem!", msg);
      return 0;
   }

   setTitle(filename);
   widget->initScene(filename.text());
   return 1;
}

void FOXMainWindow::create()
{
  FXMainWindow::create();
  show(PLACEMENT_SCREEN);
}

int main (int argc, char *argv[])
{
  osgInit(argc,argv);
  // Make application
  FXApp* application = new FXApp("FOXWindow", "Test application");
  
  // Open display
  application->init(argc,argv);
  
  // Make window
  FOXMainWindow* mainWindow = new FOXMainWindow(application);

  // Create app
  application->create();

  // Run
  application->run();

  osgExit();
  return 1;
}

#ifdef WIN32
#pragma warning (error : 698 47 373 171)
#pragma warning (default : 383)
#endif


