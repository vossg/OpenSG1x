#ifndef XMATTRIBUTEVIEW_H
#define XMATTRIBUTEVIEW_H

///
class Attribute;

#include "XMAttribView.h"

class XMAttributeView : public XMAttribView {

///
	enum CallbackCode { DISMISS = 0, ENGAGE, DELETE };

///
	void createWidgetTree (Widget parent);

 ///
 	Widget _nameLabel, _nameInput;
///
	Widget _typeLabel, _typeInput;
///
	Widget _descriptionLabel, _descriptionInput;

	Widget _initialValueLabel, _initialValueInput;


///
	Widget _staticMemoryInput, _defaultMemoryInput;
	Widget _enumMemoryInput, _typedefMemoryInput;
///
	Widget _privateInput, _protectedInput, _publicInput;

	///
	Widget _getMethodInput, _setMethodInput, _prefixInput, _getPrefixInput;

///
	CALLBACK_METHOD (XMAttributeView, setMemoryModel);
///
	CALLBACK_METHOD (XMAttributeView, setAccessType);
///
	CALLBACK_METHOD (XMAttributeView, setMethodBinding);
	///
	CALLBACK_METHOD (XMAttributeView, setType);

///
	void updateModel();

  ///
  virtual void pushAction (int code);

public:

///
	XMAttributeView (Attribute *attribute);
///
	virtual ~XMAttributeView (void);

///
	Attribute *attribute (void);

///
	virtual void refresh(void);

};

#endif // XMATTRIBUTEVIEW_H






