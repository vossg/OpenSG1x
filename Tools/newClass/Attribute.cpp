#include <sysConfig.h>
#include <iostream>
#include <string>

#include "XMAttributeView.h"

#include "Class.h"

#include "Method.h"

#include "Attribute.h"

unsigned Attribute::_objCount = 0;

Attribute::Attribute(Class *c, char *name)
{
	_id = ++_objCount;

	_getMethod = 0;
	_setMethod = 0;

	_accessType = PRIVATE_ACCESS;
	_memoryModel = DEFAULT_MODEL;

	_name = 0;
	setName (name);

	_type = 0;
	_description = 0;
	_initialValue = 0;
	
	_defaultModelValues = true;

	_underscorePrefix = true;
	_getPrefix = true;

	_class = 0;
	setClass(c);
}

Attribute::Attribute(Attribute &attribute)
{
	_id = ++_objCount;

	_accessType = attribute._accessType;
	_memoryModel = attribute._memoryModel;
	_defaultModelValues = attribute._defaultModelValues;
	_underscorePrefix = attribute._underscorePrefix;
	_getPrefix = attribute._getPrefix;

	_name = 0;
	setName(attribute._name);
	_type = 0;
	setType(attribute._type);
	_description = 0;
	setDescription(attribute._description);
	_initialValue = 0;
	setInitialValue(attribute._initialValue);

	_class = 0;
	setClass(attribute._class);

	_getMethod = 0;
	if (attribute._getMethod)
		createGetMethod();

	_setMethod = 0;
	if (attribute._setMethod)
		createSetMethod();
}

Attribute::~Attribute(void)
{
	cout << "INFO: In Method::~Method()" << endl;

	delete [] _name;
	delete [] _type;
	delete [] _description;

	delete _setMethod;
	delete _getMethod;

	setClass(0);
}

void Attribute::setClass (Class *newClass)
{
	Class *oldClass = _class;

	if (newClass == _class)
		return;

	_class = 0;
	if (oldClass)
		oldClass->removeAttribute(this);
	
	_class = newClass;
	if (newClass)
		newClass->addAttribute(this);
}

void Attribute::setName(char *name)
{
	delete [] _name;

	if (name) {
		_name = new char [strlen(name)+1];
		strcpy (_name, name);
	} else
		_name = 0;
}

void Attribute::setType(char *type)
{
	delete [] _type;

	if (type) {
		_type = new char [strlen(type)+1];
		strcpy (_type, type);
	} else
		_type = 0;
}

void Attribute::setDescription ( char *description)
{
	delete [] _description;

	if (description) {
		_description = new char [strlen(description)+1];
		strcpy (_description, description);
	} else
		_description = 0;
}

void Attribute::setInitialValue ( char *initialValue)
{
	delete [] _initialValue;

	if (initialValue) {
		_initialValue = new char [strlen(initialValue)+1];
		strcpy (_initialValue, initialValue);
	} else
		_initialValue = 0;
}

void Attribute::popupAttribView(void)
{
	if (_attribView)
		_attribView->refresh();
	else
		_attribView = new XMAttributeView(this);
	 
	_attribView->popup();
}

bool Attribute::createSetMethod(void)
{
	delete _setMethod;

	_setMethod = new Method(_class);
	_setMethod->setDependence (this, SET_METHOD);
	_setMethod->setImplementType (INLINE_IMP);
	_setMethod->touchModelValues();

	return true;
}

bool Attribute::createGetMethod(void)
{
	delete _getMethod;
	
	_getMethod = new Method(_class);
	_getMethod->setDependence (this, GET_METHOD);
	_getMethod->setImplementType (INLINE_IMP);
	_getMethod->touchModelValues();

	return true;
}

bool Attribute::releaseMethodDepend(Method *method)
{
	bool retCode;

	if (method == _setMethod) {
		_setMethod = 0;
		retCode = true;
	}
	else {
		if (method == _getMethod) {
			_getMethod = 0;
			retCode = true;
		}
		else {
			retCode = false;
		}
	}

	return retCode;
}
		
		







