#ifndef BASE_H
#define BASE_H

//
//	Class name : Base
//
//	Author: Johannes Behr 
//
//	Description :
//

class XMAttribView;

class Base {

  friend class XMAttribView;
  
	bool _active;
	
protected:
    
	XMAttribView *_attribView;
	
public:

  Base(void);
	virtual ~Base(void);

	virtual bool active(void) { return _active; }
	virtual void setActive(bool flag = true) { _active = flag; } 
	virtual void setInActive(void) { setActive(false); }

	XMAttribView *attribView(void) { return _attribView; }
	virtual void popupAttribView(void);
 
	virtual bool operator> (Base &) { return true; }
	
	virtual char * name(void) { return "NoName"; }
	virtual char * className(void) { return "Base"; }

	virtual void print(void);
};


#endif //BASE_H

