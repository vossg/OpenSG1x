#include <sysConfig.h>

#include <iostream>

#include "XMDialog.h"


//----------------------------------------------------------------------
//	Method name : XMDialog
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
XMDialog::XMDialog(char *name)
: XMBase(name)
{
  return;
}


//----------------------------------------------------------------------
//	Method name : ~XMDialog
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
XMDialog::~XMDialog(void)
{
  return;
}

//----------------------------------------------------------------------
//	Method name : setDialogWidget
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
void XMDialog::setDialogWidget(Widget dialog)
{
  if (!dialog)
    {	cerr << "Error: !dialog in XMDialog::setDialogWidget() !\n";
  		return;
    }
  
	XtAddCallback ( dialog, XmNokCallback, XMDialog::okCB, 					this);
  XtAddCallback ( dialog, XmNcancelCallback, XMDialog::cancelCB, 	this);
  XtAddCallback ( dialog, XmNhelpCallback, XMDialog::helpCB, 			this);
  
  XMBase::setTopWidget(dialog);
}


//------------------------------------------------------
//	Method name : ok
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
void XMDialog::ok(Widget, XtPointer)
{
	cout << "In XMDialog::ok() !\n";
}


//----------------------------------------------------------------------
//	Method name : cancel
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
void XMDialog::cancel(Widget, XtPointer)
{
  cout << "In XMDialog::cancel() !\n";
}


//----------------------------------------------------------------------
//	Method name : help
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
void XMDialog::help(Widget, XtPointer)
{
	cout << "In XMDialog::help() !\n"; 
}


//----------------------------------------------------------------------
//	Method name : popdown
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
void XMDialog::popdown(void)
{
  cout << "In XMDialog::popdown() !\n";
  
	unmanage(); 
	XSync(XtDisplay(topWidget()),True); 
}









