/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
 *                                                                           *
 *          contact: {reiners|vossg}@igd.fhg.de, jbehr@zgdv.de               *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#define OSG_COMPILEBASE

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <string.h>
#include <ctype.h>


// Class declarations
#include "OSGString.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*-------------------------- constructor ----------------------------------*/

/** Class default Constructor
*/
String::String(unsigned size)
: _str(0), _memType(COPY)
{
	setLength(size);
}

String::String(const char *str, MemType memType)
: _str(0), _memType(memType)
{
	set(str, memType);
}

/** Class Copy Constructor
*/
String::String(const String &obj, MemType memType)
: _str(0), _memType(memType)
{
	set(obj._str, memType);
}


/*-------------------------- destructor -----------------------------------*/

/** Class Destructor
*/
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


/*------------------------------ access -----------------------------------*/

void String::toupper(void) 
{
	int i, l = length();

	for (i = 0; i < l; i++) 
		_str[i] = ::toupper(_str[i]);

}

void String::tolower(void) 
{
	int i, l = length();

	for (i = 0; i < l; i++) 
		_str[i] = ::tolower(_str[i]);

}

/** get the str length
*/
unsigned String::length(void) const
{
	return _str ? strlen(_str) : 0;
}

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

/** set method for attribute str
*/
void String::set(const char *str, MemType memType)
{
	if ( str == _str )	// set to itself? 
	{
		// !!! can you change _memType here? I think not. IMHO
		return;
	}

	if (_str && _memType == COPY)
		delete [] _str;

	if (memType == COPY) 
	{
		if (str) 
		{
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
// Method: tokenize
// Author: cholzhae
// Date:   Mo Oct 09 13:00:00 2000
// Description:
//         
//----------------------------------------------------------------------
void String::tokenize( vector <String*> &v)
{
	int l        = length(),
		oldpos   = 0,
		pos      = 0,
		inQuotes = 0,
		inToken  = 0;

	if ( l > 0 ) 
	{

		char *buf = (char *)malloc( (l+1) * sizeof(char) );
	
		for ( pos = 0; pos <= l; pos++) 	
		{
			
			if ( !inQuotes )
			{
				if ( !inToken )
				{
					if ( _str[pos] == '"' )
					{
						inQuotes = 1;
						oldpos = pos+1;				
					}
					else if ( _str[pos] != ' ' )
					{
						inToken = 1;
						oldpos = pos;			
					} 
				}
				else if ( inToken )
				{			
					if ( _str[pos] == '"' )
					{
						inToken = 0;

						strncpy( buf, _str + oldpos, pos - oldpos );
						buf [ pos - oldpos ] = '\0';						
						v.push_back( new String( buf ) );
						
						inQuotes = 1;
						oldpos = pos;
						
					}
					else if ( _str[pos] == ' ' )
					{
						inToken = 0;
						
						strncpy( buf, _str + oldpos, pos - oldpos );
						buf [ pos - oldpos ] = '\0';						
						v.push_back( new String( buf ) );	
					}
					else if ( pos == l ) 
					{
						strncpy( buf, _str + oldpos, pos - oldpos );
						buf [ pos - oldpos ] = '\0';						
						v.push_back( new String( buf ) );	
					}
					
				}
				
			}
			else if ( inQuotes ) 
			{
				if ( _str[pos] == '"' )
				{
					inQuotes = 0;
						
					if ( pos > oldpos )
					{	
						strncpy( buf, _str + oldpos, pos - oldpos );
						buf [ pos - oldpos ] = '\0';						
						v.push_back( new String( buf ) );
					}
				}
				else if ( pos == l )
				{
					if ( pos > oldpos )
					{
						strncpy( buf, _str + oldpos, pos - oldpos );
						buf [ pos - oldpos ] = '\0';						
						v.push_back( new String( buf ) );
					}
				}
			}		
		}
		free(buf);
	}
}

//----------------------------------------------------------------------
// Method: output stream operator
// Author: jbehr
// Date:   Mon Dec 22 14:20:20 1997
// Description:
//          write str value in stream
//----------------------------------------------------------------------

OSG_BEGIN_NAMESPACE

OSG_BASE_DLLMAPPING ostream &operator <<(ostream &os, const String &obj)
{
	return os << (obj.str() ? obj.str() : "0 String");
} 

OSG_END_NAMESPACE
