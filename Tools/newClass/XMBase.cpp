#include <sysConfig.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "XMBase.h"
#include <Xm/PushB.h>
#include <Xm/ToggleB.h>
#include <Xm/Label.h>
#include <Xm/RowColumn.h>
#include <Xm/CascadeB.h>
#include <Xm/Separator.h>

//----------------------------------------------------------------------
XMBase::XMBase(char *name)
{
	_widget = 0;
	_cursor = 0;
	if (!name)
	  name = "NoName";
	
	_name = new char[strlen(name)+1];
	if (_name)
		strcpy (_name,name);
	else
		{	cerr << "ERROR: Couldn't create _name in XMBase::XMBase() !\n";
			exit(-1);
		}
}

//----------------------------------------------------------------------
XMBase::~XMBase ()
{
  cout << "Info: XMBase::~XMBase() for " << _name << endl; // DEBUG
  
	if (_widget)
		{ XtRemoveCallback 	(	_widget, XmNdestroyCallback,
													XMBase::destroyCB, (XtPointer) this
												);
			XtDestroyWidget(_widget);
		}
	delete [] _name;
}

//----------------------------------------------------------------------
void XMBase::destroyCB(Widget, XtPointer clientData, XtPointer)
{
	XMBase *obj = (XMBase *) clientData;
	
	obj->_widget = 0;
	delete obj;
}

//----------------------------------------------------------------------
bool XMBase::setTopWidget(Widget topWidget)
{
	_widget = topWidget;
	
	if (_widget)
		{	XtAddCallback (	_widget, XmNdestroyCallback,
											XMBase::destroyCB, (XtPointer) this
										);
			_display = XtDisplay(_widget);
		}
	else
		{	cerr << "Warning: Couldn't install destoryCB without _widget !\n";
			return false;
		}
	return true;
}

//----------------------------------------------------------------------
void XMBase::setDefaultResources(const Widget, const String *)
{
	cout << "WARNING: In XMBase::setDefaultResources() !" << endl;
	return; 
}

//----------------------------------------------------------------------
void XMBase::getResources	(	const XtResourceList resources, 
														const int numResources
													)
{
	if (_widget && resources)
		XtGetSubresources (	XtParent(_widget), (XtPointer) this,
												name(), className(), resources, numResources, 0, 0
											);
}

//----------------------------------------------------------------------
void XMBase::resetCursor(Widget widget)
{
	Window window;
	
	if (!_cursor)
	  return;
	
	if (widget)
		window = XtWindow(widget);
	else
	  if (_widget)
	    window = XtWindow(_widget);
	  else
	    return;
	
	if (window)
		{	XUndefineCursor (_display, window);
			XFreeCursor (_display, _cursor);
			_cursor = 0;
		}				
}

//----------------------------------------------------------------------
void XMBase::setCursor(int cursor, Widget widget)
{
	Window window;
	
	if (widget)
		window = XtWindow(widget);
	else
	  if (_widget)
	    window = XtWindow(_widget);
	  else
	    return;
	
	if (window)
		{	if (this->_cursor)
       	XFreeCursor (_display, _cursor);
			_cursor = XCreateFontCursor (_display, cursor);
			if (_cursor)
				{	XDefineCursor (_display, window, _cursor);
					XFlush (_display);
				}
			else
				cerr << "Error: Couln't not set _cursor to " << cursor << " !\n";
		}
}


//----------------------------------------------------------------------
//	Method name : createSubMenu
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
Widget XMBase::createSubMenu	(	char *name, Widget parent, 
				 													Widget &button, bool help
				 												)
{
  Widget subMenu;
	char 	*menuName = 0;
	
	if (name)
	  menuName = new char[strlen(name)+5];
	else
	  name = "NoName";
	
	if (menuName)
	  {	strcpy (menuName, name);
			strcat (menuName, "Menu");
	  }
	else
	  menuName = name;
	
	subMenu = XmCreatePulldownMenu (parent, menuName, 0, 0);
	XtVaSetValues (	subMenu, 
		       				XmNtearOffModel, XmTEAR_OFF_ENABLED, 
		       				// Motif 2.0, XmNtearOffTitle, XmString, menuName,
		       				0
		       			);
	button  = XtVaCreateManagedWidget	(	name, xmCascadeButtonWidgetClass, parent,
														XmNsubMenuId, subMenu,
				 										0
				 									);
	if (help)
		XtVaSetValues (parent, XmNmenuHelpWidget, button, 0);
	return subMenu;
}

//----------------------------------------------------------------------
//	Method name : createPushButton
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
Widget XMBase::createPushButton	(	char *name, Widget parent, 
				 													XtCallbackProc proc, 
				 													Pixmap disarmPixmap, Pixmap armPixmap
				 												)
{
  Cardinal 		n;
  Arg					args[8];
  Widget 			button;
   
  n = 0;
  if (disarmPixmap)
    {	XtSetArg (args[n], XmNlabelType, XmPIXMAP); n++;
			XtSetArg (args[n], XmNlabelPixmap, disarmPixmap); n++;
    }
  if (armPixmap)
    {	XtSetArg (args[n], XmNarmPixmap, armPixmap); n++;
    }

  button = XtCreateManagedWidget 	(	name, xmPushButtonWidgetClass, parent, 
				    												args, n
				    											);
	if (proc)
  	XtAddCallback ( button, XmNactivateCallback, proc, this);
  
  return button;			     													
}

//----------------------------------------------------------------------
//	Method name : createVerSeparator
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
Widget XMBase::createVerSeparator(char *name, Widget parent)
{
	return XtVaCreateManagedWidget (	name, xmSeparatorWidgetClass, parent, 
																		XmNorientation, XmVERTICAL,
																		0
																 );
}

//----------------------------------------------------------------------
//	Method name : createHorSeparator
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
Widget XMBase::createHorSeparator(char *name, Widget parent)
{
	return XtVaCreateManagedWidget 	(	name, xmSeparatorWidgetClass, parent, 
																		XmNorientation, XmHORIZONTAL,
																		0
																	);
}

//----------------------------------------------------------------------
//	Method name : readIcon
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
Pixmap XMBase::readIcon(Widget widget, char *fileName)
{
  Display				*display = XtDisplay(widget);
  int						screen = DefaultScreen(display);
  Window				rootWindow = RootWindow(display,screen);
	unsigned int	depth = DefaultDepth(display, screen);
  unsigned int 	width, height;
  int 					xHot, yHot;
	Pixmap 				bitmap, pixmap;
	int						retCode;
	char					*errorMessage = 0;
	GC						gc;
	XGCValues			gcValues;
	
	retCode = XReadBitmapFile ( display, rootWindow, fileName, 
				   										&width, &height, &bitmap, &xHot, &yHot
				   									);
	
	switch(retCode)
	  {	case BitmapOpenFailed:
	    	errorMessage = "BitmapOpenFailed";
				break;
			case BitmapFileInvalid:
				errorMessage = "BitmapFileInvalid";
				break;
			case BitmapNoMemory:
				errorMessage = "BitmapNoMemory";
				break;
			case BitmapSuccess:
				errorMessage = 0;
				break;
			default:
  			errorMessage = "ReadBitmapFile-UnknownError";
				break;
		}

	if (errorMessage)
		{ cerr 	<< "Warning: Couldn't read Icon " << fileName 
						<< " (" << errorMessage << ") !\n";
			return 0;
		}
	
	pixmap = XCreatePixmap (display, rootWindow, width, height, depth);

	XtVaGetValues (	widget, 
		       				XmNforeground, &gcValues.foreground,
		       				XmNbackground, &gcValues.background,
		       				0
					      );
	gc = XtGetGC (widget, GCForeground | GCBackground, &gcValues );
	
	if (!gc)
	  { cerr << "ERROR: Couldn't create GC in XMBase::readIcon !\n";
	    return 0;
	  }
	
	if (pixmap)
	  XCopyPlane (display, bitmap, pixmap, gc, 0, 0, width, height, 0, 0, 1);
	else
	  {	cerr << "Warning: Couldn't create Pixmap in XMBase::readIcon() !\n";
			return 0;
	  }
	  
	XtReleaseGC(widget,gc);
	XFreePixmap(display, bitmap);    
	return pixmap;
}

//----------------------------------------------------------------------
//	Method name : createIcon
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
Pixmap XMBase::createIcon(Widget widget, char *data, unsigned int width, unsigned int height)
{
  Display				*display = XtDisplay(widget);
  int						screen = DefaultScreen(display);
  Window				rootWindow = RootWindow(display,screen);
	unsigned int	depth = DefaultDepth(display, screen);
	Pixmap 				pixmap;
	unsigned long	fg, bg;
	
	XtVaGetValues (	widget, XmNforeground, &fg, XmNbackground, &bg, 0);

	pixmap = XCreatePixmapFromBitmapData 	(	display, rootWindow, data,
																					width, height, fg, bg, depth
																				);

	if (!pixmap)
		cerr << "Error: Counld't create Icon !\n";

	return pixmap;
}

//----------------------------------------------------------------------
//	Method name : createToggleButton
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
Widget XMBase::createToggleButton	(	char *name, Widget parent, 
				 														XtCallbackProc proc, 
				 														Pixmap disarmPixmap, Pixmap armPixmap
				 													)
{
  Cardinal 		n;
  Arg					args[8];
  Widget 			button;
   
  n = 0;
  XtSetArg (args[n], XmNindicatorOn, FALSE); n++; 
	XtSetArg (args[n], XmNfillOnSelect, TRUE); n++;
	XtSetArg (args[n], XmNshadowThickness, 2); n++;
  if (disarmPixmap)
    {	XtSetArg (args[n], XmNlabelType, XmPIXMAP); n++;
			XtSetArg (args[n], XmNlabelPixmap, disarmPixmap); n++;
    }
  if (armPixmap)
    {	XtSetArg (args[n], XmNarmPixmap, armPixmap); n++;
    }

  button = XtCreateManagedWidget 	(	name, xmToggleButtonWidgetClass, parent, 
				    												args, n
				    											);
	if (proc)
  	XtAddCallback ( button, XmNvalueChangedCallback, proc, this);
  
  return button;			     													
}

//----------------------------------------------------------------------
//	Method name : createToggleIndicatorButton
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
Widget XMBase::createToggleIndicatorButton	(	char *name, Widget parent, 
				 																			XtCallbackProc proc
				 																		)
{
  Widget 			button;
   
  button = XtVaCreateManagedWidget 	(	name, xmToggleButtonWidgetClass, parent, 0);
	if (proc)
  	XtAddCallback ( button, XmNvalueChangedCallback, proc, this);
  
  return button;			     													
}

//----------------------------------------------------------------------
Widget XMBase::createLabel (char *name, Widget parent)
{
  Widget label;
  
	label = XtVaCreateManagedWidget 	(	name, xmLabelWidgetClass, parent,
																			XmNalignment, XmALIGNMENT_BEGINNING,
				 															0
						 												);
	return label;
}

//----------------------------------------------------------------------
bool XMBase::setAttachment	( Widget widget,
															Widget top, Widget bottom, Widget left, Widget right
														)
{
	Widget 			form;
  Cardinal 		n = 0;
  Arg					args[16];
   
	if (widget)
		form = XtParent(widget);
	else
		return false;

	// attach top
	if (top)
		if (top == form)
			{	XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM); n++;
			}
		else
			{ XtSetArg (args[n], XmNtopAttachment, XmATTACH_WIDGET); n++;
				XtSetArg (args[n], XmNtopWidget, top); n++;
			}
	else
		{	XtSetArg (args[n], XmNtopAttachment, XmATTACH_NONE ); n++;
		}
	
	// attach bottom
	if (bottom)
		if (bottom == form)
			{	XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
			}
		else
			{ XtSetArg (args[n], XmNbottomAttachment, XmATTACH_WIDGET); n++;
				XtSetArg (args[n], XmNbottomWidget, bottom); n++;
			}
	else
		{	XtSetArg (args[n], XmNbottomAttachment, XmATTACH_NONE ); n++;
		}

	// attach left
	if (left)
		if (left == form)
			{	XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM); n++;
			}
		else
			{ XtSetArg (args[n], XmNleftAttachment, XmATTACH_WIDGET); n++;
				XtSetArg (args[n], XmNleftWidget, left); n++;
			}
	else
		{	XtSetArg (args[n], XmNleftAttachment, XmATTACH_NONE ); n++;
		}

	// attach right
	if (right)
		if (right == form)
			{	XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM); n++;
			}
		else
			{ XtSetArg (args[n], XmNrightAttachment, XmATTACH_WIDGET); n++;
				XtSetArg (args[n], XmNrightWidget, right); n++;
			}
	else
		{	XtSetArg (args[n], XmNrightAttachment, XmATTACH_NONE ); n++;
		}

	XtSetValues (widget, args, n);
	
	return true;
}

//----------------------------------------------------------------------
//	Method name : setSensitive
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
void XMBase::setSensitive(Widget widget, bool sensitive)
{
  if (widget)
  	if (sensitive)
	  	XtVaSetValues (widget, XmNsensitive, True,  0);
  	else
	  	XtVaSetValues (widget, XmNsensitive, False, 0);
}

//----------------------------------------------------------------------
//	Method name : createHorRowColumn
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
Widget XMBase::createHorRowColumn(char *name, Widget parent)
{
	return XtVaCreateManagedWidget 	(	name, xmRowColumnWidgetClass, parent, 
																		XmNorientation, XmHORIZONTAL,
																		0
																	);
}

//----------------------------------------------------------------------
//	Method name : createVerRowColumn
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
Widget XMBase::createVerRowColumn(char *name, Widget parent)
{
	return XtVaCreateManagedWidget 	(	name, xmRowColumnWidgetClass, parent, 
																		XmNorientation, XmVERTICAL,
																		XmNradioBehavior, True,
																		XmNradioAlwaysOne, True,
																		0
																	);
}

//----------------------------------------------------------------------
//	Method name : createHorRadioBox
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
Widget XMBase::createHorRadioBox(char *name, Widget parent)
{
	return XtVaCreateManagedWidget 	(	name, xmRowColumnWidgetClass, parent, 
																		XmNorientation, XmHORIZONTAL,
																		XmNradioBehavior, True,
																		XmNradioAlwaysOne, True,
																		0
																	);
}

//----------------------------------------------------------------------
//	Method name : createVerRadioBox
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
Widget XMBase::createVerRadioBox(char *name, Widget parent)
{
	return XtVaCreateManagedWidget 	(	name, xmRowColumnWidgetClass, parent, 
																		XmNorientation, XmVERTICAL,
																		XmNradioBehavior, True,
																		XmNradioAlwaysOne, True,
																		0
																	);
}


//----------------------------------------------------------------------
//	Method name : setLabel
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
void XMBase::setLabel(Widget label, int value)
{
  char str[128];
  
  sprintf(str,"%d", value);
  this->setLabel(label,str);
}

//----------------------------------------------------------------------
//	Method name : setLabel
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
void XMBase::setLabel(Widget label, double value)
{
  char str[128];
  
  sprintf(str,"%g", value);
  this->setLabel(label,str);
}

//----------------------------------------------------------------------
//	Method name : setLabel
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
void XMBase::setLabel(Widget label, char *value)
{
  if (!value)
    value = " ";
  
	if (label)
    XtVaSetValues (label, XmNlabelString, (XtArgVal)XmStringCreateSimple(value), 0);
  else
    cerr << "Error: No Label Widget in void XMBase::setLabel() !\n";
}

//----------------------------------------------------------------------
//	Method name : allocColor
//
//	Author : Johannes Behr 
//	Description :
//  A replacement for XAllocColor.  This function should never
//  fail to allocate a color.  When XAllocColor fails, we return
//  the nearest matching color.  If we have to allocate many colors
//  this function isn't too efficient; the XQueryColors() could be
//  done just once.
//  Input:  dpy - X display
//          cmap - X colormap
//          cmapSize - size of colormap
//  In/Out: color - the XColor struct
//  Output:  exact - 1=exact color match, 0=closest match
void XMBase::allocColor	( Display *dpy, Colormap cmap, int cmapSize,
                    			XColor *color, int *exact 
												)
{
   XColor *ctable, subColor;
   int i, bestmatch;
   double mindist;       /* 3*2^16^2 exceeds long int precision. */

   /* First try just using XAllocColor. */
   if (XAllocColor(dpy, cmap, color)) {
      *exact = 1;
      return;
   }

   /* Alloc failed, search for closest match */

   /* Retrieve color table entries. */
   /* XXX alloca candidate. */
   ctable = (XColor *) malloc(cmapSize * sizeof(XColor));
   for (i = 0; i < cmapSize; i++) {
      ctable[i].pixel = i;
   }
   XQueryColors(dpy, cmap, ctable, cmapSize);

   /* Find best match. */
   bestmatch = -1;
   mindist = 0.0;
   for (i = 0; i < cmapSize; i++) {
      double dr = 0.30 * ((double) color->red - (double) ctable[i].red);
      double dg = 0.59 * ((double) color->green - (double) ctable[i].green);
      double db = 0.11 * ((double) color->blue - (double) ctable[i].blue);
      double dist = dr * dr + dg * dg + db * db;
      if (bestmatch < 0 || dist < mindist) {
         bestmatch = i;
         mindist = dist;
      }
   }

   /* Return result. */
   subColor.red   = ctable[bestmatch].red;
   subColor.green = ctable[bestmatch].green;
   subColor.blue  = ctable[bestmatch].blue;
   /* Try to allocate the closest match color.  This should only
    * fail if the cell is read/write.  Otherwise, we're incrementing
    * the cell's reference count.
    */
   if (!XAllocColor(dpy, cmap, &subColor)) {
      /* do this to work around a problem reported by Frank Ortega */
      subColor.pixel = (unsigned long) bestmatch;
      subColor.red   = ctable[bestmatch].red;
      subColor.green = ctable[bestmatch].green;
      subColor.blue  = ctable[bestmatch].blue;   
      subColor.flags = DoRed | DoGreen | DoBlue;
   }
   free(ctable);
   *color = subColor;
   *exact = 0;
}

//----------------------------------------------------------------------
//	Method name : setText
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
void XMBase::setText (Widget widget, char *text)
{
	XtVaSetValues (widget, XmNvalue, text, 0);
}

//----------------------------------------------------------------------
//	Method name : getText
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
char *XMBase::getText (Widget widget)
{	
	char *str;

	XtVaGetValues ( widget, XmNvalue, &str, 0);

	return str;
}

//----------------------------------------------------------------------
//	Method name : setToggle
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
void XMBase::setToggle(Widget widget, bool value)
{
	unsigned char set = (value == true) ? TRUE : FALSE;

	XtVaSetValues (widget, XmNset, set, 0);

	return;
}

//----------------------------------------------------------------------
//	Method name : getToggle
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
bool XMBase::getToggle (Widget widget)
{
	unsigned char set;

	XtVaGetValues (widget, XmNset, &set, 0);
	
	return (set == TRUE) ? true : false;
}	


