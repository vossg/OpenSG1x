#include <sysConfig.h>
#include <stdio.h>
#include <string.h>

#include "XMAttribView.h"
#include "XMMethodView.h"

#include "Attribute.h"
#include "Class.h"

#include "Method.h"

char Method::tmpNameBuffer[256];
char Method::tmpParamBuffer[256];
char Method::tmpDescriptionBuffer[256];
unsigned Method::_objCount = 0;

Method::Method (Class *c, char *name)
{
	_id = ++_objCount;

	_dependAttribute = 0;

	_name = 0;
	setName(name);

	_type = 0;
	_param = 0;
	_description = 0;

	_methodType = UNDEF_METHOD;
	_memoryModel = VIRTUAL_MODEL;
	_accessType = PUBLIC_ACCESS;
	_implementType = IMPFILE_IMP;

	_defaultModelValues = true;

	_class = 0;
	setClass(c);
}

Method::Method (Method &method)
{
	_id = ++_objCount;

	_dependAttribute = 0;

	_methodType = method._methodType;
	_memoryModel = method._memoryModel;
	_accessType = method._accessType;
	_implementType = _implementType;
	_defaultModelValues = method._defaultModelValues;

	_name = 0;
	setName(method._name);
	_type = 0;
	setType(method._type);
	_param = 0;
	setParam(method._param);
	_description = 0;
	setDescription(method._description);

	_class = 0;
	setClass(method._class);
}

Method::~Method ()
{
	cout << "INFO: In Method::~Method()" << endl;

	delete [] _name;
	delete [] _param;
	delete [] _type;
	delete [] _description;

	if (_dependAttribute)
		_dependAttribute->releaseMethodDepend(this);

	setClass (0);
}

void Method::setClass (Class *newClass)
{
	Class *oldClass = _class;

	if (newClass == _class)
		return;

	_class = 0;
	if (oldClass)
		oldClass->removeMethod(this);
	
	_class = newClass;
	if (newClass)
		newClass->addMethod(this);
}

char *Method::name (void)
{
	char *retName, *attribName, *firstChar;

	switch (_methodType) {
	  case CONSTRUCTOR_METHOD:
			retName = _class->name();
			break;
	  case DESTRUCTOR_METHOD:
			sprintf(tmpNameBuffer,"~%s", _class->name());
			retName = tmpNameBuffer;
			break;
   	case SET_METHOD:
			if (!_name && _dependAttribute) {
				attribName = _dependAttribute->name();
				sprintf(tmpNameBuffer,"set%s", attribName);
				firstChar = tmpNameBuffer + 3;
				if (*firstChar >= 'a' && *firstChar <= 'z')
					*firstChar = *firstChar + 'A' - 'a';
				retName = tmpNameBuffer;
			}
			else
				retName = _name;
			break;
  	case GET_METHOD:
			if (!_name && _dependAttribute) {
				attribName = _dependAttribute->name();
				if ( _dependAttribute->getPrefix() || 
						 !(_dependAttribute->underscorePrefix()) ) {
					sprintf(tmpNameBuffer,"get%s", attribName);
					firstChar = tmpNameBuffer + 3;
					if (*firstChar >= 'a' && *firstChar <= 'z')
						*firstChar = *firstChar + 'A' - 'a';
					retName = tmpNameBuffer;
				}
				else 
					retName = _dependAttribute->name();
			}
			else
				retName = _name;
			break;
	  case UNDEF_METHOD:
	  default:
			retName = _name;
	}

	return retName;
}		

void Method::setName(char *name)
{
	delete [] _name;

	if (name && *name) {
		_name = new char [strlen (name)+1];
		strcpy (_name, name);
	}
	else
		_name = 0;
}

char* Method::type (void)
{
	char *retStr;

	switch (_methodType)
		{
		case CONSTRUCTOR_METHOD:
		case DESTRUCTOR_METHOD:
			retStr = "";
			break;
		case GET_METHOD:
			if (!_type && _dependAttribute)
				retStr = _dependAttribute->type();
			else
				retStr = _type;
			break;
		case SET_METHOD:
			if (!_type && _dependAttribute)
				retStr = "void";
			else
				retStr = _type;
			break;
		default:
		case UNDEF_METHOD:
			retStr = _type;
		}

	return retStr;
}

void Method::setType(char *type)
{
	delete [] _type;

	if (!type || *type == 0)
		type = "void";

	_type = new char [strlen (type)+1];
	strcpy (_type, type);
}

char *Method::param (void)
{
	char *retStr;

	switch (_methodType)
		{
		case CONSTRUCTOR_METHOD:
			retStr = _param;
			break;
		case DESTRUCTOR_METHOD:
			retStr = "void";
			break;
		case GET_METHOD:
			if (!_param && _dependAttribute)
				retStr = "void";
			else
				retStr = _param;
			break;
		case SET_METHOD:
			if (!_param && _dependAttribute) {
				if (_dependAttribute->underscorePrefix())
					sprintf ( tmpParamBuffer,"%s %s", 
										_dependAttribute->type(),
										_dependAttribute->name()
									);
				else
					sprintf ( tmpParamBuffer,"%s %sNew", 
										_dependAttribute->type(),
										_dependAttribute->name()
									);					
				retStr = tmpParamBuffer;
			}
			else
				retStr = _param;
			break;
		default:
		case UNDEF_METHOD:
			retStr = _param;
		}

	return retStr;
}	

void Method::setParam(char *param)
{
	delete [] _param;

	if (!param || *param == 0)
		param = "void";

	_param = new char [strlen (param)+1];
	strcpy (_param, param);
}

char *Method::description (void)
{
	char *retStr;

	if (_dependAttribute)
		{ sprintf ( tmpDescriptionBuffer, "%s method for attribute %s",
								_methodType == SET_METHOD ? "set" : "get",
								_dependAttribute->name()
							);
		  retStr = tmpDescriptionBuffer;
		}
	else
		retStr = _description;
	
	return retStr;
}

void Method::setDescription (char *description)
{
	delete [] _description;
	
	if (description) {
		_description = new char [strlen (description) + 1];
		strcpy (_description, description);
	}
	else
		_description = 0;
}

void Method::popupAttribView (void)
{
	if (_attribView)
		_attribView->refresh();
	else
		_attribView = new XMMethodView(this);
	 
	_attribView->popup();
}

void Method::setDependence (Attribute *attribute, MethodType methodType)
{
	delete [] _name;

	cout << "INFO: In setDependence for " << attribute->name() << endl;

	_name = 0;
	_dependAttribute = attribute;
	_methodType = methodType;
}







