// System declarations

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <string.h>
#include <ctype.h>

// Application declarations


// Class declarations
#include "OSGString.h"

OSG_USING_NAMESPACE

// Static Class Variable implementations: 


//----------------------------------------------------------------------
// Method: String
// Author: jbehr
// Date:   Sat Dec 20 20:39:24 1997
// Description:
//         Class default Constructor
//----------------------------------------------------------------------
String::String(unsigned size)
: _str(0), _memType(COPY)
{
	setLength(size);
}

//----------------------------------------------------------------------
// Method: String
// Author: jbehr
// Date:   Sat Dec 20 20:39:24 1997
// Description:
//         Class Constructor
//----------------------------------------------------------------------
String::String(const char *str, MemType memType)
: _str(0), _memType(memType)
{
	set(str, memType);
}

//----------------------------------------------------------------------
// Method: String
// Author: jbehr
// Date:   Sat Dec 20 20:39:24 1997
// Description:
//         Class Copy Constructor
//----------------------------------------------------------------------
String::String(const String &obj, MemType memType)
: _str(0), _memType(memType)
{
	set(obj._str, memType);
}

//----------------------------------------------------------------------
// Method: ~String
// Author: jbehr
// Date:   Sat Dec 20 20:39:24 1997
// Description:
//         Class Destructor
//----------------------------------------------------------------------
String::~String()
{
	/*
	cerr << "In String::~String() for " << (_str ? _str : "NULL")
			 << ", memType: " << (_memType == COPY ? "COPY" : "LINK")
			 << endl;
			 */

	if (_str && _memType == COPY)
		delete [] _str; 
}

//----------------------------------------------------------------------
// Method: toupper
// Author: jbehr
// Date:   Sat Dec 20 20:39:24 1997
// Description:
//        
//----------------------------------------------------------------------
void String::toupper(void) 
{
	int i, l = length();

	for (i = 0; i < l; i++) 
		_str[i] = ::toupper(_str[i]);

}

//----------------------------------------------------------------------
// Method: tolower
// Author: jbehr
// Date:   Sat Dec 20 20:39:24 1997
// Description:
//        
//----------------------------------------------------------------------
void String::tolower(void) 
{
	int i, l = length();

	for (i = 0; i < l; i++) 
		_str[i] = ::tolower(_str[i]);

}

//----------------------------------------------------------------------
// Method: length
// Author: jbehr
// Date:   Sat Dec 20 20:39:24 1997
// Description:
//         get the str length
//----------------------------------------------------------------------
unsigned String::length(void) const
{
	return _str ? strlen(_str) : 0;
}

//----------------------------------------------------------------------
// Method: setLength
// Author: jbehr
// Date:   Sat Dec 20 20:39:24 1997
// Description:
//         TODOC
//----------------------------------------------------------------------
void String::setLength(unsigned length)
{
	if (_str && _memType == COPY)
		delete [] _str;

	if (length) {
		_str = new char[length];
		*_str = 0;
	}
	else
		_str = 0;

	_memType = COPY;
}

//----------------------------------------------------------------------
// Method: set
// Author: jbehr
// Date:   Sat Dec 20 20:39:24 1997
// Description:
//         set method for attribute str
//----------------------------------------------------------------------
void String::set(const Char8 *str, MemType memType)
{
	if (_str && _memType == COPY)
		delete [] _str;

	if (memType == COPY) {
		if (str) {
			// cerr << "INFO: Try to buffer for " << str; 
			_str = new char[strlen(str) + 1];
			// cerr << " ... done" << endl; 
			strcpy(_str, str);
		}
		else 
			_str = 0;
	}
	else
		_str = const_cast<char*>(str);

	_memType = memType;
}

//----------------------------------------------------------------------
// Method: output stream operator
// Author: jbehr
// Date:   Mon Dec 22 14:20:20 1997
// Description:
//          write str value in stream
//----------------------------------------------------------------------

OSG_BEGIN_NAMESPACE

ostream &operator <<(ostream &os, const String &obj)
{
	return os << (obj.str() ? obj.str() : "0 String");
} 

OSG_END_NAMESPACE
