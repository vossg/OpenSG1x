#ifndef XMDIALOG_H
#define XMDIALOG_H

//
//	Class name : XMDialog
//
//	Author: Johannes Behr 
//
//	Description :
//

#include "XMBase.h"

///
class XMDialog : public XMBase {

  ///
  static void okCB (Widget w, XtPointer obj, XtPointer cr)
    { ((XMDialog *)obj)->ok(w, cr); }
  ///
  virtual void ok (Widget, XtPointer);

///
	static void cancelCB (Widget w, XtPointer obj, XtPointer cr)
    { ((XMDialog *)obj)->cancel(w,cr); }
  ///
  virtual void cancel (Widget, XtPointer);

///
	static void helpCB (Widget w, XtPointer obj, XtPointer cr)
    { ((XMDialog *)obj)->help(w,cr); }
  ///
  virtual void help (Widget, XtPointer);

protected:

  ///
  void setDialogWidget (Widget dialog);
  
public:
///
	XMDialog(char *name);
///
	virtual ~XMDialog(void);
	
///
	bool isPoped (void) { return (XtIsManaged(topWidget()) ? true : false); }
///
	void popup(void) { manage(); }
///
	void popdown(void);
};


#endif //XMDIALOG_H

