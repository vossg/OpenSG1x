// System declarations
#include <iostream>
#include <stdio.h>
#include <string.h>

// Application declarations

using namespace std;

// Class declarations
#include "FieldContainer.h"
#include "Field.h"


// Static Class Varible implementations: 
const char *Field::_defaultTypeName[] = {	
	"Bool",
	"Int16",
	"Int32",
	"Int64", 
	"Real32", 
	"Real64", 
	"Color3f",
	"Color4f",
	"Pnt2f",
	"Pnt3f",
	"Pnt4f",
	"Vec2f",
	"Vec3f",
	"Vec4f",
	"Quaternion",
	"Matrix",
	"String",
	"Time",
	"Image",
	"FieldContainerPtr"
};

const char *Field::_cardinalityName[] = {
	"single", "multi"
};

const char *Field::_visibilityName[] = {
	"internal", "external"
};

const char *Field::_accessName[] = {
	"public", "protected", "private"
};

std::vector<std::string> Field::_typeName;

//----------------------------------------------------------------------
// Method: Field
// Author: jbehr
// Date:   Thu Jan  8 19:55:06 1998
// Description:
//         Class Constructor
//----------------------------------------------------------------------
Field::Field (void )
	: _name(0), _defaultValue(0), _defaultHeader(0), 
	  _description(0), _header(0)
{
	_type = 0;
	_cardinality = 0;
	_visibility = 0;
	_access = 0;

	return;
}

//----------------------------------------------------------------------
// Method: Field
// Author: jbehr
// Date:   Thu Jan  8 19:55:06 1998
// Description:
//         Class Copy Constructor
//----------------------------------------------------------------------
Field::Field (const Field &obj )
: _name(0), _defaultValue(0), _defaultHeader(0), _description(0), _header(0)
{
	*this = obj;
}

//----------------------------------------------------------------------
// Method: ~Field
// Author: jbehr
// Date:   Thu Jan  8 19:55:06 1998
// Description:
//         Class Descructor
//----------------------------------------------------------------------
Field::~Field (void )
{
	setName(0);
	setDescription(0);
	setDefaultValue(0);
	setDefaultHeader(0);
	setHeader(0);
}

//----------------------------------------------------------------------
// Method: loadDefaultFieldTypeList
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
int Field::loadDefaultFieldTypeList(void)
{
	int i, n = sizeof(_defaultTypeName)/sizeof(char*);

	_typeName.clear();
	for (i = 0; i < n; ++i) 
		_typeName.push_back(_defaultTypeName[i]);
	
	return _typeName.size();
}

//----------------------------------------------------------------------
// Method: loadFileTypeList
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
int Field::loadFieldTypeList(const char *fileName)
{
	ifstream sin(fileName);
	std::string str;

	if (sin) {
		_typeName.clear();
		while (true) {
			sin >> str;
			if (sin.eof()) 
				break;
			else 
				_typeName.push_back(str);
		}
	}

	return _typeName.size();
}

//----------------------------------------------------------------------
// Method: type
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
const char *Field::typeStr(int i)
{
	int vecSize = _typeName.size();

	return (i >= 0 && i < vecSize) ? _typeName[i].c_str() : 0;
}

//----------------------------------------------------------------------
// Method: cardinality
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
const char *Field::cardinalityStr(int i)
{
	int vecSize = sizeof(_cardinalityName )/ sizeof(char*);

	return (i >= 0 && i < vecSize) ? _cardinalityName[i] : 0;
}

//----------------------------------------------------------------------
// Method: visibility
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
const char *Field::visibilityStr(int i)
{
	int vecSize = sizeof(_visibilityName )/ sizeof(char*);

	return (i >= 0 && i < vecSize) ? _visibilityName[i] : 0;
}

//----------------------------------------------------------------------
// Method: access
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
const char *Field::accessStr(int i)
{
	int vecSize = sizeof(_accessName )/ sizeof(char*);

	return (i >= 0 && i < vecSize) ? _accessName[i] : 0;
}

//----------------------------------------------------------------------
// Method: type
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
const char *Field::typeStr(void)
{
	return typeStr(_type);
}

//----------------------------------------------------------------------
// Method: cardinality
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
const char *Field::cardinalityStr(void)
{
	return cardinalityStr(_cardinality);
}

//----------------------------------------------------------------------
// Method: visibility
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
const char *Field::visibilityStr(void)
{
	return visibilityStr(_visibility);
}

//----------------------------------------------------------------------
// Method: access
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
const char *Field::accessStr(void)
{
	return accessStr(_access);
}

//----------------------------------------------------------------------
// Method: setName
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         set method for attribute name
//----------------------------------------------------------------------
void Field::setName (const char* name )
{
	delete _name;
	
	if (name && *name && strcmp(name,FieldContainer::_nil)) {
		_name = new char [strlen(name)+1];
		strcpy(_name,name);
	}
	else
		_name = 0;
}

//----------------------------------------------------------------------
// Method: setDefaultValue
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         set method for attribute description
//----------------------------------------------------------------------
void Field::setDefaultValue (const char* defaultValue )
{
	delete _defaultValue;
	
	if (defaultValue && *defaultValue && strcmp(defaultValue,FieldContainer::_nil)) {
		_defaultValue = new char [strlen(defaultValue)+1];
		strcpy(_defaultValue,defaultValue);
	}
	else 
		_defaultValue = 0;
}

//----------------------------------------------------------------------
// Method: setDefaultHeader
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// DefaultHeader:
//         set method for attribute defaultHeader
//----------------------------------------------------------------------
void Field::setDefaultHeader ( const char* defaultHeader )
{
	delete _defaultHeader;
	
	if (defaultHeader && *defaultHeader && strcmp(defaultHeader,FieldContainer::_nil)) 
	{
		_defaultHeader = new char [strlen(defaultHeader)+1];
		strcpy(_defaultHeader,defaultHeader);
	}
	else
		_defaultHeader = 0;
}

//----------------------------------------------------------------------
// Method: setDescription
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         set method for attribute description
//----------------------------------------------------------------------
void Field::setDescription ( const char* description )
{
	delete _description;
	
	if (description && *description && strcmp(description,FieldContainer::_nil)) {
		_description = new char [strlen(description)+1];
		strcpy(_description,description);
	}
	else
		_description = 0;
}

//----------------------------------------------------------------------
// Method: setHeader
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// header:
//         set method for attribute header
//----------------------------------------------------------------------
void Field::setHeader ( const char* header )
{
	delete _header;
	
	if (header && *header && strcmp(header,FieldContainer::_nil) &&
		strcmp(header,"auto") ) 
	{
		_header = new char [strlen(header)+1];
		strcpy(_header,header);
	}
	else
		_header = 0;
}

//----------------------------------------------------------------------
// Method: setType
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         set method for attribute type
//----------------------------------------------------------------------
void Field::setType ( const char* typeStr ) 
{
	int type = -1, i, n = _typeName.size();
	string str(typeStr);
	
	for (i = 0; i < n; ++i) 
		if (_typeName[i] == str) {
			type = i;
			break;
		}

	if (type == -1) {
		type = n;
		_typeName.push_back(str);
	}
	
	_type = type;
}

//----------------------------------------------------------------------
// Method: setCardinality
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         set method for attribute cardinality
//----------------------------------------------------------------------
void Field::setCardinality ( const char* cardinalityStr ) 
{
	int i, n = sizeof(_cardinalityName)/sizeof(char*);

	for (i = 0; i < n; ++i) 
		if (!strcasecmp(cardinalityStr, _cardinalityName[i]))
		{
			_cardinality = i;
			break;
		}

	if ( i == n )
	{
		cerr << "Field::setCardinality: string '" << cardinalityStr << "' is unknown!" 
		     << endl;
		_cardinality = 0;
	}
}

//----------------------------------------------------------------------
// Method: setVisibility
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         set method for attribute visibility
//----------------------------------------------------------------------
void Field::setVisibility ( const char* visibilityStr )
{
	int i, n = sizeof(_visibilityName)/sizeof(char*);

	for (i = 0; i < n; ++i) 
		if (!strcasecmp(visibilityStr, _visibilityName[i]))
		{
			_visibility = i;
			break;
		}

	if ( i == n )
	{
		cerr << "Field::setVisibility: string '" << visibilityStr << "' is unknown!" 
		     << endl;
		_visibility = 0;
	}
}

//----------------------------------------------------------------------
// Method: setAccess
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         set method for attribute cardinality
//----------------------------------------------------------------------
void Field::setAccess ( const char* accessStr ) 
{
	int i, n = sizeof(_accessName)/sizeof(char*);

	for (i = 0; i < n; ++i) 
		if (!strcasecmp(accessStr, _accessName[i]))
		{
			_access = i;
			break;
		}

	if ( i == n )
	{
		cerr << "Field::setAccess: string '" << accessStr << "' is unknown!" << endl;
		_access = 0;
	}
}

//----------------------------------------------------------------------
// Method: getLine
// Author: jbehr
// Date:   Thu Jan  8 19:55:06 1998
// Description:
//         
//----------------------------------------------------------------------
bool Field::getLine (char *line)
{
	char * def;
	def = new char [ (_defaultValue ? strlen( _defaultValue) : 0 ) + 
	                  (_defaultHeader ? strlen( _defaultHeader) : 0 ) +
					  3
					];
	if ( _defaultHeader && *_defaultHeader )
	{
		if ( _defaultValue && *_defaultValue )
			sprintf( def, "%s (%s)", _defaultValue, _defaultHeader );
		else
			sprintf( def, "None" );
	}
	else				
	{
		if ( _defaultValue && *_defaultValue )
			sprintf( def, "%s", _defaultValue );
		else
			sprintf( def, "None" );
	}	
				
	sprintf ( line, "%s %s %s %s %s %s %s, %s" , 
						(_name && *_name) ? _name : "None",
						cardinalityStr(), typeStr(), 
						visibilityStr(), accessStr(), 
						(_header && *_header) ? _header : "auto", 
						def, 
						(_description	&& *_description) ? _description : "None");

	delete [] def;
	return true;
}

//----------------------------------------------------------------------
// Method: operator=
// Author: jbehr
// Date:   Thu Jan  8 19:55:06 1998
// Description:
//         
//----------------------------------------------------------------------
Field &Field::operator= (const Field &obj)
{
	setName(obj._name);
	_type = obj._type;
	setDescription(obj._description);
	setDefaultValue(obj._defaultValue);
	setDefaultHeader(obj._defaultHeader);
	setHeader(obj._header);
	_access = obj._access;
	_cardinality = obj._cardinality;
	
	return *this;
}

//----------------------------------------------------------------------
// Method: operator== 
// Author: jbehr
// Date:   Thu Jan  8 19:55:06 1998
// Description:
//         
//----------------------------------------------------------------------
bool Field::operator== (const Field &obj)
{
	return 	(	!strcmp(_name, obj._name) &&
						!strcmp(_description, obj._description) &&
						!strcmp(_defaultValue, obj._defaultValue) &&
						!strcmp(_defaultHeader, obj._defaultHeader) &&
						_type == obj._type &&
						_cardinality == obj._cardinality &&
						_access == obj._access &&
						!strcmp(_header, obj._header)
					);
}
