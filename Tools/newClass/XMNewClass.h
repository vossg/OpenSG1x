#ifndef XMNEWCLASS_H
#define XMNEWCLASS_H

#include "XMBase.h"

///
class Class;

///
class XMNewClass : public XMBase {

///
	Class *_class;

	///
	Widget _ok, _cancel;

	///
	Widget _attributeLabel;
	Widget _newAttribute, _deleteAttribute, _editAttribute, _cloneAttribute;

	///
	Widget _methodLabel;
	Widget _newMethod, _deleteMethod, _editMethod, _cloneMethod;

	///
	Widget _classNameLabel, _classNameInput;
	Widget _publicClassNameLabel, _publicClassName;

	///
	Widget _parentNameLabel, _parentNameInput;

	///
	Widget _descriptionLabel, _descriptionInput;

	/// 
	Widget _responsibilityLabel, _responsibilityInput;

	///
	Widget _attributeListInput, _methodListInput, _relationListInput;

	///
	bool createWidgetTree(Widget parent, char *className = 0);

	///
	CALLBACK_METHOD (XMNewClass, setClassName);

	///
	CALLBACK_METHOD (XMNewClass, ok);
	///
	CALLBACK_METHOD (XMNewClass, cancel);

	///
	CALLBACK_METHOD (XMNewClass, newAttribute);

	///
	CALLBACK_METHOD (XMNewClass, deleteAttribute);

	///
	CALLBACK_METHOD (XMNewClass, editAttribute);

	CALLBACK_METHOD (XMNewClass, cloneAttribute);


	///
	CALLBACK_METHOD (XMNewClass, newMethod);
	
	///
	CALLBACK_METHOD (XMNewClass, deleteMethod);

	///
	CALLBACK_METHOD (XMNewClass, editMethod);

	///
	CALLBACK_METHOD (XMNewClass, cloneMethod);

protected:

	///
	void refreshAttributeList(void);

	///
	void refreshMethodList(void);

public:

///
	XMNewClass (Widget parent, char *className = 0);
///
	virtual ~XMNewClass (void);

	virtual void refresh(void);

};

#endif // XMNEWCLASS_H





