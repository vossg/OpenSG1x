#ifndef XMATTRIBVIEW_H
#define XMATTRIBVIEW_H

//
//	Class name : XMAttribView
//
//	Author: Johannes Behr 
//
//	Description :
//

#include "XMPopup.h"

///
class Base;

class XMAttribView : public XMPopup {

  ///
  Base *_base;

  bool						_destroyBase;
  
protected:

  ///
	Base *base(void) 			{ return _base; }

	void destroyBase(void) { _destroyBase = true; }

public:
///
	XMAttribView(char *name, Base *base, Widget parent = 0);
///
	virtual ~XMAttribView(void);
	
///
	virtual void refresh (void);
};


#endif //XMATTRIBVIEW_H
