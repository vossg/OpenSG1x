#ifndef XMPOPUP_H
#define XMPOPUP_H

//
//	Class name : XMPopup
//
//	Author: Johannes Behr 
//
//	Description :
//

#include "XMBase.h"
#include "List.h"

///
class XMPopup : public XMBase {

  ///
  struct CallbackMessage {
    
  ///
  	XMPopup *popup;
    ///
    int 		code;
    ///
    Widget	widget;
   
   ///
   	virtual bool operator> (CallbackMessage &) { return true; }
  };
  
///
	List<CallbackMessage> _callbackMessageList;
  
  ///
  Widget 	_shell, _form, _desk, _iconBar, _info;
///
	Widget	_engage, _cancel;  
  ///
  bool _isPoped, _isRealized;
    
  ///
  Widget createWidgetTree (char *name, Widget parent);

  ///
  static void buttonCB (Widget, XtPointer cd, XtPointer);
  ///
  virtual void pushAction (int code);

protected:

  ///
  Widget desk(void) { return _desk; }
///
	Widget engage(void) { return _engage; }
///
	Widget cancel(void) { return _cancel; }

  ///
  void addButton(char *name, int code, char *info = 0, char *help = 0);
///
	Widget getButtonWidget (int code);
	
///
	void info(char *message);
	
	void suicide (void) { XtDestroyWidget(topWidget()); } 

public:
///
	XMPopup(char *name, Widget parent = 0);
///
	virtual ~XMPopup(void);

///
	bool isPoped(void) { return _isPoped; }
///
	virtual void popup(void);
///
	virtual void popdown(void);
	
///
	virtual void refresh (void) {;}
};

#endif //XMPOPUP_H





