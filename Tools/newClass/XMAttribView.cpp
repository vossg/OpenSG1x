#include <sysConfig.h>

#include <iostream>
#include "XMAttribView.h"
#include "XMApp.h"


//----------------------------------------------------------------------
//	Method name : char *name, Base *base, Widget *widget
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
XMAttribView::XMAttribView(char *name, Base *base, Widget widget)
: XMPopup (name, widget)
{
  this->_base = base;
  _destroyBase = false;
  
  if (base)
    {	if (base->_attribView)
	  		{	cout << '\a' << endl;
					delete base->_attribView;
	  		}
			base->_attribView = this;
    }
}

//----------------------------------------------------------------------
//	Method name : ~XMAttribView
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
XMAttribView::~XMAttribView(void)
{
	if (_base)
	  {	_base->_attribView = 0;
			if (_destroyBase)
		  	delete _base;
	  }
}

//----------------------------------------------------------------------
//	Method name : refresh
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
void XMAttribView::refresh(void)
{
  cout << "In XMAttribView::refresh() !\n";
}











