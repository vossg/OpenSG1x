#include <sysConfig.h>
#include <iostream>
#include <string.h>

#include <Xm/Label.h>

#include "XMHelp.h"

bool 					XMHelp::_classValid 	= false;
Widget 				XMHelp::_infoShell		= 0;
Widget 				XMHelp::_infoText 		= 0;
bool					XMHelp::_isUp 				= false;

//----------------------------------------------------------------------
//	Method name : XMHelp
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
XMHelp::XMHelp(Widget widget, char *info, char *help)
: XMBase("help")
{
	classConstructor(widget);
	_infoTimer = 0;

  if (widget)
  	setTopWidget(widget);
  else
    return;

	if (info)
		{	_info = new char[strlen(info)+1];
			strcpy (_info, info);
			XtAddEventHandler	( widget, 
													EnterWindowMask,
													False, viewInfoEH, this 
												);
			XtAddEventHandler	( widget, 
													LeaveWindowMask | ButtonPressMask,
													False, removeInfoEH, this 
												);
		}
	else
		_info = 0;

	if (help)
		{ _help = new char[strlen(help)+1];
			strcpy (_help, help);
		 	XtAddCallback	(	widget, XmNhelpCallback, viewHelpCB, this);
		}
	else
		_help = 0;
  
}

//----------------------------------------------------------------------
//	Method name : ~XMHelp
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
XMHelp::~XMHelp(void)
{
	if (_info)
		delete [] _info;
	
	if (_help)
		delete [] _help;

	if (_infoTimer)
		{	XtRemoveTimeOut (_infoTimer);
			_infoTimer = 0;
		}
}

//----------------------------------------------------------------------
//	Method name : classConstructor 
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
void XMHelp::classConstructor (Widget widget)
{
  Arg		wargs[16];
  int		n;
	Widget parent;

	if (_classValid)
		return;
	
	cout << "Search Root Widget ";
	parent = widget;

	for (parent = widget; parent; parent = XtParent(widget)) {
		widget = parent;
		cout << '.';
	}
	cout << " done" << endl;

	n = 0;
	XtSetArg(wargs[n], XmNautoUnmanage, False); n++;
	XtSetArg(wargs[n], XmNheight, 20); n++;
	XtSetArg(wargs[n], XmNwidth, 100); n++;
	XtSetArg(wargs[n], XmNborderWidth, 1); n++;
	XtSetArg(wargs[n], XmNmwmDecorations, 0); n++;
	XtSetArg(wargs[n], XmNoverrideRedirect, True); n++;
	XtSetArg(wargs[n], XmNallowShellResize, True); n++;
	XtSetArg(wargs[n], XmNsaveUnder, True); n++;	
	
	_infoShell = XtCreateWidget	(	"infoShell", shellWidgetClass, 
																widget, wargs, n
															);

	_infoText = XtVaCreateManagedWidget	(	"infoText", xmLabelWidgetClass, 
																				_infoShell, 
																				0
																			);
	_classValid = true;

	return;
}

//----------------------------------------------------------------------
//	Method name : viewHelp
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
bool XMHelp::viewHelp(XtPointer)
{
  char *message;
  
  if (!_info && !_help)
    message = "No help needed !";
  else
    message = _help ? _help : _info;
  
  cout << message;
	return true;
}

//----------------------------------------------------------------------
//	Method name : viewInfo
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
bool XMHelp::viewInfo(Widget widget, XEvent *, Boolean *) 
{		
	Position 	rootX, rootY;
	Dimension	height;

  if (_info && _infoText)
		setLabel (_infoText, _info);
	else
  	return false;
 		
	XtTranslateCoords(widget, 0, 0, &rootX, &rootY); 
	XtVaGetValues (widget, XmNheight, &height, 0);
	XtVaSetValues (_infoShell, XmNx, rootX, XmNy, rootY+height, 0);

	_infoTimer = XtAppAddTimeOut	(	XtWidgetToApplicationContext(topWidget()), 
																	400, infoTimerCB, this
																);
  return true;
}

//----------------------------------------------------------------------
//	Method name : removeInfo
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
bool XMHelp::removeInfo(Widget, XEvent *, Boolean *) 
{
  if (_infoTimer)
		{	XtRemoveTimeOut (_infoTimer);
			_infoTimer = 0;
		}
	else
		if (_isUp)
			XtPopdown (_infoShell);
	_isUp = 0;

  return true;
}

//----------------------------------------------------------------------
//	Method name : infoTimer
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
bool XMHelp::infoTimer(XtIntervalId *) 
{
	XtPopup (_infoShell, XtGrabNone);
	_infoTimer = 0;
	_isUp = true;

	return true;
}
