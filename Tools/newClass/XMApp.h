#ifndef MAPP_H
#define MAPP_H

#include <stdlib.h>  // for exit()
#include "XMBase.h"

#include <Xm/MessageB.h>

///
enum DisplayType	{	MONO_DISPLAY = 1, PSEUDOCOLOR_DISPLAY, GREYSCALE_DISPLAY,
								  	DIRECTCOLOR_DISPLAY, TRUECOLOR_DISPLAY, UNKNOWN_DISPLAY
									};
  
///
class XMApp : public XMBase {

  ///
  static XMApp *_app;
  
///
	char		*_appClass;

///
	int			_argc;
///
	char		**_argv;

///
	XtAppContext	_appContext;	

///
	int       		_screen;
///
	Visual				*_visual;
///
	unsigned char _visualDepth;
	
///
	DisplayType		_displayType;
	
///
	Widget				_infoWidget;	
	
///
	Widget				_warningDialog;
///
	int	_debug;

public:

///
	XMApp (char *AppClass, int &argc, char **argv);
///
	virtual ~XMApp(void);

///
	bool engage(void);
///
	bool run(void) { return engage(); }
///
	void dismiss(void);
///
	void end(void) {  dismiss(); }
	
///
	void info (char *message);
	
///
	void warning (char *message);
	
///
	void debug (char *message);
///
	void debugOn (void) { _debug = 1; }
///
	void debugOff (void) { _debug = 0; }

///
	int screen(void) { return _screen; }
///
	Visual *visual(void) { return _visual; }
///
	unsigned char visualDepth(void) { return _visualDepth; }
///
	XtAppContext context(void) { return _appContext; }

///
	DisplayType displayType (void) { return _displayType; }

///
	const char *const progName (void) { return *_argv; }

///
	void setInfoWidget(Widget widget) { _infoWidget = widget; }

  ///
  virtual char *className(void) { return "XMApp"; }

///
	static XMApp *current(void) { return _app; }

///
	static void quitCB (Widget w, XtPointer obj, XtPointer cd);

///
	void setTitle (char *name);

///
	void sync (void);
};

///
extern XMApp *xmApp;

#endif // MAPP_H
