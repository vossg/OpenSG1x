#ifndef XMBASE_H
#define XMBASE_H

#include <X11/X.h>
#include <Xm/Xm.h>
#include <X11/cursorfont.h>

#include "Base.h"

///
class XMBase : public Base {

  ///
  char		*_name;

///
	static void destroyCB (Widget, XtPointer, XtPointer);

///
	Display *_display;
///
	Widget 	_widget;
	
///
	Cursor	_cursor;
	
protected:

///
	bool setTopWidget(Widget topWidget); 
	
///
	void setDefaultResources (const Widget, const String *);
///
	void getResources (const XtResourceList, const int);

///
  void allocColor	( Display *dpy, Colormap cmap, int cmapSize,
               			XColor *color, int *exact 
									);

///
	XMBase (char *name);
	
public:

///
	virtual ~XMBase ();
	
///
	Display *display(void) { return _display; }
///
	Widget topWidget(void) { return _widget; }
	
///
	virtual char * name(void) { return _name; }
///
	virtual char * className(void) { return "XMBase"; }
		
///
	virtual void manage (void) { if (!XtIsManaged(_widget)) XtManageChild(_widget); }
///
	virtual void unmanage (void) { if (XtIsManaged(_widget)) XtUnmanageChild(_widget); }
	
///
	virtual void resetCursor(Widget Widget = 0);
///

	void setCursor(int cursor, Widget widget = 0);


	/// tool methods
	Pixmap readIcon(Widget widget, char *fileName);
///
	Pixmap createIcon(Widget widget, char *data, unsigned int width, unsigned int height);
///
	Widget createHorSeparator(char *name, Widget parent);
///
	Widget createVerSeparator(char *name, Widget parent);
///
	Widget createHorRowColumn (char *name, Widget parent);
///
	Widget createVerRowColumn (char *name, Widget parent);
///
	Widget createHorRadioBox (char *name, Widget parent);
///
	Widget createVerRadioBox (char *name, Widget parent);
 ///
 	Widget createSubMenu 	(	char *name, Widget parent, 
				     							Widget &button, bool help=false
				     						);
///
	Widget createPushButton (	char *name, Widget parent, 
				 										XtCallbackProc proc, 
				 										Pixmap disarmPixmap = 0, Pixmap armPixmap = 0
				 									);
///
	Widget createToggleButton (	char *name, Widget parent, 
				 											XtCallbackProc proc, 
				 											Pixmap disarmPixmap = 0, Pixmap armPixmap = 0
				 										);
///
	Widget createToggleIndicatorButton	(	char *name, Widget parent, XtCallbackProc proc);

///
	Widget createLabel ( char *name, Widget parent );
///
	bool setAttachment	(	Widget widget, 
												Widget top, Widget bottom, Widget left, Widget right 
											);
///
	void setSensitive (Widget widget, bool sensitive = true);
	
///
	void setLabel (Widget widget, int value);
///
	void setLabel (Widget widget, unsigned value) { setLabel(widget,int(value)); }
///
	void setLabel (Widget widget, double value);
///
	void setLabel (Widget widget, char *value);

	void setText (Widget widget, char *text);
///
	char *getText (Widget widget);
	
///
	void setToggle (Widget widget, bool value = true);
///
	bool getToggle (Widget widget);
	
///
	virtual void refresh(void) {;}
};

#define CALLBACK_METHOD(class, method) static void method ## CB (Widget w, XtPointer obj, XtPointer cr)	{ (( class  *)obj)-> ## method (w,cr); } void method (Widget w = 0, XtPointer cr = 0);

#endif // XMBASE_H
	
