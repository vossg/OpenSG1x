#ifndef XMHELP_H
#define XMHELP_H

//
//	Class name : XMHelp
//
//	Author: Johannes Behr 
//
//	Description :
//

#include "XMBase.h"

///
class	XMHelp : public XMBase {
  
///
	static bool _classValid;
///
	static void classConstructor(Widget w);
///
	static bool _isUp;

///
	XtIntervalId _infoTimer;

///
	char 		*_info;
///
	char		*_help;
	
///
	static Widget  		_infoShell, _infoText;
///
	static XmFontList _infoFontlist;
	
///
	static void viewHelpCB (Widget, XtPointer obj, XtPointer cr)
		{ ((XMHelp *)obj)->viewHelp(cr); }
///
	bool viewHelp(XtPointer);
	
///
	static void viewInfoEH (Widget w, XtPointer obj, XEvent* e, Boolean* ef)
	  { ((XMHelp *)obj)->viewInfo (w, e, ef); }
///
	bool viewInfo(Widget, XEvent *, Boolean*);
				    
///
	static void removeInfoEH (Widget w, XtPointer obj, XEvent* e, Boolean* ef)
	  { ((XMHelp *)obj)->removeInfo (w, e, ef); }
///
	bool removeInfo(Widget, XEvent *, Boolean*);

///
	static void infoTimerCB (XtPointer obj, XtIntervalId *id)
	  { ((XMHelp *)obj)->infoTimer (id); }
///
	bool infoTimer (XtIntervalId *id);

public:
		
  ///
  XMHelp(Widget widget, char *info, char *help = 0);
///
	virtual ~XMHelp(void);

}; 	

#endif //XMHELP_H


