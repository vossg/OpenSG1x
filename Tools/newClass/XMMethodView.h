#ifndef XMMETHODVIEW_H
#define XMMETHODVIEW_H

///
class Method;

#include "XMAttribView.h"

class XMMethodView : public XMAttribView {

///
	enum CallbackCode { DISMISS = 0, ENGAGE, DELETE };

///
	void createWidgetTree (Widget parent);

 ///
 	Widget _nameLabel, _nameInput;
///
	Widget _typeLabel, _typeInput;
///
	Widget _paramLabel, _paramInput;
///
	Widget _descriptionLabel, _descriptionInput;
///
	Widget _taskLabel, _taskText;

///
	Widget _staticMemoryInput, _virtualMemoryInput;
///
	Widget _defaultMemoryInput;
	
///
	Widget _privateInput, _protectedInput;
///
	Widget _publicInput;

///
	Widget _abstractInput, _inlineInput, _impFileInput;

///
	Widget _constructorInput, _descructorInput, _friendClassInput,     	    	    	    	    	    	    	    	_operatorInput;

///
	CALLBACK_METHOD (XMMethodView, setMemoryModel);
///
	CALLBACK_METHOD (XMMethodView, setAccessType);
///
	CALLBACK_METHOD (XMMethodView, setImplementation);
///
	CALLBACK_METHOD (XMMethodView, setTask);

	CALLBACK_METHOD (XMMethodView, setType);
///
	void updateModel();

  ///
  virtual void pushAction (int code);

public:

///
	XMMethodView (Method *method);
///
	virtual ~XMMethodView (void);

///
	Method *method (void);

///
	virtual void refresh(void);

};

#endif // XMMETHODVIEW_H
