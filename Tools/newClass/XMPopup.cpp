#include <sysConfig.h>

#include <iostream>
#include <stdlib.h>
 
#include <X11/Xmu/Editres.h>

#include "XMPopup.h"
#include "XMHelp.h"
#include "XMApp.h"

#include <Xm/Form.h>
#include <Xm/RowColumn.h>
#include <Xm/PushB.h>

//----------------------------------------------------------------------
XMPopup::XMPopup(char *name, Widget parent)
:	XMBase (name)
{
  _isPoped = _isRealized = false;

  _info = 0;
  
  setTopWidget(createWidgetTree(name, parent ? parent : xmApp->topWidget()));
}

//----------------------------------------------------------------------
XMPopup::~XMPopup()
{
  _callbackMessageList.deleteAllElem();
}

//----------------------------------------------------------------------
//	Method name : createWidgetTree
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
Widget XMPopup::createWidgetTree(char *name, Widget parent)
{
  Widget sep;
  
  _shell = XtCreatePopupShell	( name, transientShellWidgetClass, parent,
	                              0, 0
                            	);
  _form = XtVaCreateManagedWidget ( "form", xmFormWidgetClass, _shell, 0 );
  
  _info = createLabel ("info", _form );
  setAttachment ( _info, 0, _form, _form, _form );
  
  sep = createHorSeparator ("infoSep", _form);
  setAttachment (	sep, 0, _info, _form, _form );
  
  _iconBar = XtVaCreateManagedWidget 	(	"iconBar", 
				      													xmRowColumnWidgetClass, _form, 
				      													XmNorientation, XmHORIZONTAL,
				      													0
				     	 												);
  
  setAttachment ( _iconBar, 0, sep, _form, _form );
  
  sep = createHorSeparator ("iconBarSep", _form );
  setAttachment ( sep, 0, _iconBar, _form, _form );
  
  _desk = XtVaCreateManagedWidget ( "desk", xmFormWidgetClass, _form, 0 );
  setAttachment ( _desk, _form, sep, _form, _form );
  
	XtAddEventHandler (	_shell, (EventMask) 0, 1,
											(XtEventHandler) _XEditResCheckMessages, 0
										);
	return _shell;
}

//----------------------------------------------------------------------
//	Method name : buttonCB
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
void XMPopup::buttonCB(Widget, XtPointer cd, XtPointer)
{
	CallbackMessage *message = (CallbackMessage*)cd;
	
	/* steschne mode
	if (message->code == 1)
	  {	cout << "system: play /igd/a7/home2/jbehr/snd/myStuff/engage.au &";
			system ("play /igd/a7/home2/jbehr/snd/myStuff/engage.au &");  
	  }
	*/
	
	message->popup->pushAction(message->code);
}


//----------------------------------------------------------------------
//	Method name : pushAction
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
void XMPopup::pushAction(int code)
{
  cout << "In XMPopup::pushAction() with code: " << code << endl;
}

//----------------------------------------------------------------------
void XMPopup::popup(void)
{
  int   			x,y;
  Window    	dW;
  int       	dI;
  unsigned 		dUI;
  Dimension		width, height;
	int					min = 32;				// DEBUG
	
	if (!_isPoped)
		{	if (!_isRealized)
		  	XtRealizeWidget(_shell);
			XtVaGetValues (	_shell, XmNwidth, &width, XmNheight, &height, 0);
			XQueryPointer	(	XtDisplay(_shell), XtWindow(_shell),
											&dW, &dW, &x, &y, &dI, &dI, &dUI
					 					);
			x -= width/2;
			y -= height/2;
			XtVaSetValues	(	_shell, 
					 						XmNx, Position(x < min ? min : x), 
					 						XmNy, Position(y < min ? min : y), 
					 						0
					 					);
			XtPopup (_shell, XtGrabNone);
			_isPoped = true;
		}
}

	
//----------------------------------------------------------------------
void XMPopup::popdown(void)
{
  cout << "In XMPopup::popdown() !\n";
  
	if (_isPoped)
		{	XtPopdown (_shell);
			XSync(XtDisplay(topWidget()),True); 
			_isPoped = false;
		}
}

//----------------------------------------------------------------------
//	Method name : addButton
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
void XMPopup::addButton(char *name, int code, char *info, char *help)
{
  CallbackMessage *callbackMessage = new CallbackMessage;
  
  if (!callbackMessage)
    {	cerr 	<< "Error: Couldn't create new CallbackMessage "
      			<< "in XMPopup::addButton() !\n";
			return;
    }
  
  callbackMessage->popup = this;
  callbackMessage->code	 = code;
  callbackMessage->widget = XtVaCreateManagedWidget (	name, 
						   																				xmPushButtonWidgetClass, 
						   																				_iconBar, 
				    																					0
						   																			);
	XtAddCallback ( callbackMessage->widget, XmNactivateCallback, 
		       				XMPopup::buttonCB, callbackMessage
		       			);
  if (info || help)
  	new XMHelp (callbackMessage->widget, info, help );
  
  if (code == 0) // Cancel
		XtVaSetValues (_iconBar, XmNmenuHelpWidget, callbackMessage->widget, 0);

  _callbackMessageList.append(callbackMessage);
  return;
}

//----------------------------------------------------------------------
//	Method name : getButtonWidget
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
Widget XMPopup::getButtonWidget(int code)
{
  for	(	_callbackMessageList.begin(); 
	 			_callbackMessageList.current();
	 			_callbackMessageList.next()
	 		)
    if (_callbackMessageList.current()->code == code)
      return _callbackMessageList.current()->widget;
  
  return 0;
}

//----------------------------------------------------------------------
//	Method name : info
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
void XMPopup::info(char *message)
{
  if (_info)
    { XtVaSetValues ( _info, 
                  		XmNlabelString, (XtArgVal)XmStringCreateSimple(message),
                  		0
		     						);
    }
  else
    cerr << "Info: " << message << endl;
}



