#include <sysConfig.h>

#include <iostream>
#include "Base.h"

#include "XMAttribView.h"


//----------------------------------------------------------------------
//	Method name : Base
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
Base::Base(void)
{
  _active = true;
  _attribView = 0;
}


//----------------------------------------------------------------------
//	Method name : ~Base
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
Base::~Base(void)
{
  if (_attribView)
    delete _attribView;
}

//----------------------------------------------------------------------
//	Method name : print
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
void Base::print(void)
{
  cout << "In Base::print() !\n";
}

//----------------------------------------------------------------------
//	Method name : popupAttribView
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
void Base::popupAttribView(void)
{
  cout << "In Base::attribView() !\n";
  
  this->print();
}


