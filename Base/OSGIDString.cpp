/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
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

#include "OSGConfig.h"

#include <string.h>
#include <ctype.h>


// Class declarations
#include "OSGIDString.h"

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
IDString::IDString(UInt32 size)
: _str(0), _memType(COPY)
{
    setLength(size);
}

IDString::IDString(const Char8 *str, MemType memType)
: _str(0), _memType(memType)
{
    set(str, memType);
}

/** Class Copy Constructor
*/
IDString::IDString(const IDString &obj, MemType memType)
: _str(0), _memType(memType)
{
    set(obj._str, memType);
}


/*-------------------------- destructor -----------------------------------*/

/** Class Destructor
*/
IDString::~IDString()
{
    /*
    cerr << "In IDString::~IDString() for " << (_str ? _str : "NULL")
             << ", memType: " << (_memType == COPY ? "COPY" : "LINK")
             << endl;
             */

    if (_str && _memType == COPY)
        delete [] _str;
}


/*------------------------------ access -----------------------------------*/

#ifdef OSG_WIN32_ICL
#pragma warning ( disable : 810 )
#endif

void IDString::toUpper(void)
{
    int i, l = getLength();

    for (i = 0; i < l; i++)
        _str[i] = toupper(_str[i]);

}

void IDString::toLower(void)
{
    int i, l = getLength();

    for (i = 0; i < l; i++)
        _str[i] = tolower(_str[i]);

}

#ifdef OSG_WIN32_ICL
#pragma warning ( default : 810 )
#endif

/** get the str getLength
*/
unsigned IDString::getLength(void) const
{
    return _str ? strlen(_str) : 0;
}

void IDString::setLength(UInt32 length)
{
    if (_str && _memType == COPY)
        delete [] _str;

    if (length) {
        _str = new Char8[length];
        *_str = 0;
    }
    else
        _str = 0;

    _memType = COPY;
}

/** set method for attribute str
*/
void IDString::set(const Char8 *str, MemType memType)
{
    if ( str == _str )  // set to itself?
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
            _str = new Char8[strlen(str) + 1];
            // cerr << " ... done" << endl;
            strcpy(_str, str);
        }
        else
            _str = 0;
    }
    else
        _str = const_cast<Char8 *>(str);

    _memType = memType;
}

//----------------------------------------------------------------------
// Method: tokenize
// Author: cholzhae
// Date:   Mo Oct 09 13:00:00 2000
// Description:
//
//----------------------------------------------------------------------
void IDString::tokenize(std::vector <IDString*> &v)
{
    int l             = getLength(),
        oldpos        = 0,
        pos           = 0,
        inQuotes      = 0,
        inToken       = 0;

    IDString *pString = NULL;

    if ( l > 0 )
    {

        Char8 *buf = (Char8 *)malloc( (l+1) * sizeof(Char8) );

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

                        pString =  new IDString(buf);
                        v.push_back(pString);

                        inQuotes = 1;
                        oldpos = pos;

                    }
                    else if ( _str[pos] == ' ' )
                    {
                        inToken = 0;

                        strncpy( buf, _str + oldpos, pos - oldpos );
                        buf [ pos - oldpos ] = '\0';

                        pString =  new IDString(buf);
                        v.push_back(pString);
                    }
                    else if ( pos == l )
                    {
                        strncpy( buf, _str + oldpos, pos - oldpos );
                        buf [ pos - oldpos ] = '\0';

                        pString =  new IDString(buf);
                        v.push_back(pString);
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

                        pString =  new IDString(buf);
                        v.push_back(pString);
                    }
                }
                else if ( pos == l )
                {
                    if ( pos > oldpos )
                    {
                        strncpy( buf, _str + oldpos, pos - oldpos );
                        buf [ pos - oldpos ] = '\0';

                        pString =  new IDString(buf);
                        v.push_back(pString);
                    }
                }
            }
        }
        free(buf);
    }
}

void IDString::tokenize(std::vector <IDString> &v)
{
    int l        = getLength(),
        oldpos   = 0,
        pos      = 0,
        inQuotes = 0,
        inToken  = 0;

    if ( l > 0 )
    {

        Char8 *buf = (Char8 *)malloc( (l+1) * sizeof(Char8) );

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
                        v.push_back( IDString( buf ) );

                        inQuotes = 1;
                        oldpos = pos;

                    }
                    else if ( _str[pos] == ' ' )
                    {
                        inToken = 0;

                        strncpy( buf, _str + oldpos, pos - oldpos );
                        buf [ pos - oldpos ] = '\0';
                        v.push_back( IDString( buf ) );
                    }
                    else if ( pos == l )
                    {
                        strncpy( buf, _str + oldpos, pos - oldpos );
                        buf [ pos - oldpos ] = '\0';
                        v.push_back( IDString( buf ) );
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
                        v.push_back( IDString( buf ) );
                    }
                }
                else if ( pos == l )
                {
                    if ( pos > oldpos )
                    {
                        strncpy( buf, _str + oldpos, pos - oldpos );
                        buf [ pos - oldpos ] = '\0';
                        v.push_back( IDString( buf ) );
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

OSG_BASE_DLLMAPPING std::ostream &operator <<(      std::ostream &os, 
                                              const IDString     &obj)
{
    return os << (obj.str() ? obj.str() : "0 IDString");
}

OSG_END_NAMESPACE
