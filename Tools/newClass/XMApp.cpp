#include <sysConfig.h>
#include <iostream>
#include <string.h>

#include "XMApp.h"

#include <X11/Xmu/Editres.h>

XMApp *xmApp;

XMApp *XMApp::_app = 0;
	
//----------------------------------------------------------------------
XMApp::XMApp(char *appClass, int &argc, char **argv)
: XMBase ("xmApp")
{
	Widget _shell, child;
	_argc = argc;
	_argv = argv;
	_debug = 1;
	int	len;
	
	len = strlen(appClass);
	if (len)
		{ _appClass = new char[len+1];
			strcpy(_appClass, appClass);
		}
	else
		cout << "Warning: No appClass in XMApp::XMApp() !\n";

	_shell = XtAppInitialize 	(	&_appContext, appClass, 0, 0,
															&argc, argv, 0, 0, 0
														);

	if (!_shell)
	  {	cerr << "Could not create shell Widget !!!" << endl;
			exit(-1);
	  }
	else
		setTopWidget(_shell);

	_warningDialog	= XmCreateWarningDialog ( _shell, "warning", 0, 0);
	child = XmMessageBoxGetChild ( _warningDialog, XmDIALOG_CANCEL_BUTTON );
	XtUnmanageChild(child);
	child = XmMessageBoxGetChild ( _warningDialog, XmDIALOG_HELP_BUTTON );
	XtUnmanageChild(child);

	// needed for editres
	XtAddEventHandler (	_shell, (EventMask) 0, 1,
											(XtEventHandler) _XEditResCheckMessages, 0 );
	if (_app)
	  { cerr << "ERROR: _app != 0 in XMApp::XMApp() !\n";
	    exit (-1);
	  }
	else
	  _app = this;
	    
	xmApp = this; // DEBUG

	_screen = DefaultScreen ( display() );
	_visual = DefaultVisual ( display(), _screen );
	_visualDepth = DefaultDepth ( display(), _screen );
	
	if (_visualDepth == 1)
 		_displayType = MONO_DISPLAY;
 	else
		switch ( _visual->c_class ) {
				case PseudoColor:
 					_displayType = PSEUDOCOLOR_DISPLAY;
					break;
				case GrayScale:
 					_displayType = GREYSCALE_DISPLAY;
					break;
				case DirectColor:
 					_displayType = DIRECTCOLOR_DISPLAY;
					break;
				case TrueColor:
					_displayType = TRUECOLOR_DISPLAY;
					break;
				default:
					_displayType = UNKNOWN_DISPLAY;
					break;
			}

	setTitle(0);
}

//----------------------------------------------------------------------
XMApp::~XMApp(void)
{
	;
}

//----------------------------------------------------------------------
bool XMApp::engage(void)
{
  int   			x,y;
  Window    	dW;
  int       	dI;
  unsigned 		dUI;
  Dimension		width, height;
	int         min = 16;
	
	XtRealizeWidget(topWidget());
	XtVaGetValues (	topWidget(), XmNwidth, &width, XmNheight, &height, 0);
	XQueryPointer	(	XtDisplay(topWidget()), XtWindow(topWidget()),
									&dW, &dW, &x, &y, &dI, &dI, &dUI
			 					);
	x -= width/2;
	y -= height/2;
	XtVaSetValues	( topWidget(), 
			 						XmNx, Position(x < min ? min : x), 
			 						XmNy, Position(y < min ? min : y), 
			 						0
			 					);
	
	XtAppMainLoop(_appContext);
	return false;
}

//----------------------------------------------------------------------
void XMApp::dismiss(void)
{
  cout << "\n------------------------------------\nbye bye \n";
	exit(0);
}

//----------------------------------------------------------------------
void XMApp::warning(char *message)
{
	cerr << message << "\n";
}

//----------------------------------------------------------------------
void XMApp::debug(char *message)
{
	if (_debug)
		cerr << message << "\n";
}


//----------------------------------------------------------------------
//	Method name : info
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
void XMApp::info(char *message)
{
  if (_infoWidget)
    { XtVaSetValues ( _infoWidget, 
                  		XmNlabelString, (XtArgVal)XmStringCreateSimple(message),
                  		0
		     						);
    }
  else
    cerr << "Info: " << message << endl;
}


//----------------------------------------------------------------------
//  Method name : setTitle
//
//  Author : Johannes Behr
//  Description :
//  Input :
//  Output :
//
void XMApp::setTitle(char *title)
{
	char titleStr[256];

	if (_appClass)
		strcpy (titleStr, _appClass);
	else
		strcpy (titleStr, "XMApp");

	if (title)
		{ strcat (titleStr, " --- ");
			strcat (titleStr, title);
		}

	XtVaSetValues (topWidget(), XmNtitle, titleStr, 0);

	return;
}


//----------------------------------------------------------------------
//	Method name : sync
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
void XMApp::sync(void)
{
	XEvent       event;
 
	while(XtAppPending(_appContext) & XtIMXEvent )
	  {	XtAppNextEvent(_appContext, &event);
			XtDispatchEvent(&event);
   	}
	
 	return;
}

//----------------------------------------------------------------------
//	Method name : quitCB
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
void XMApp::quitCB (Widget , XtPointer , XtPointer )
{
	cout << "Info: In XMApp::quitCB";
	XMApp::current()->end();
}

	
