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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGStringTokenizer.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGStringTokenizer.cpp,v 1.2 2002/02/22 23:44:24 dirk Exp $";
    static Char8 cvsid_hpp[] = OSG_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSG_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/*! \class osg::StringTokenizer
    StringTokenizer documentation,
 */


/*! \enum StringTokenizer::ENUMNAME
  
 */


/*! \var VARTYPE StringTokenizer::_VARNAME
    variable documentation
 */


/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

/*! Constructor documentation
 */
StringTokenizer::StringTokenizer(string& toTokens) : _tokenString(toTokens)
{
    _currPos = 0;
    string::size_type start, end;
    nextTokenPos(start, end);
    if((start == string::npos) ||
       (end   == string::npos)   )
    {
        _hasNext = false;
    }
    else
    {
        _hasNext   = true;
        _nextToken = _tokenString.substr(start, end-start);
        _currPos   = end;
    }  
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

/*! Destructor documentation
 */
StringTokenizer::~StringTokenizer(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

/*! assignment
 */
void StringTokenizer::operator = (const StringTokenizer &OSG_CHECK_ARG(source))
{
    ;
}


bool StringTokenizer::hasNext(void)
{
    return _hasNext;
}

void StringTokenizer::nextTokenPos(string::size_type& start,
                                   string::size_type& end)
{
    start = _tokenString.find_first_not_of(" \t\n", _currPos);
    if(start == string::npos)
    {
        end = string::npos;
        return;
    }
    end   = _tokenString.find_first_of(" \t\n", start);
    if(end == string::npos)
    {
        end = _tokenString.length();
    }
}


string StringTokenizer::getNext(void)
{
    string retString = _nextToken;
    if(!_hasNext)
    {
        return retString;
    }
    string::size_type start;
    string::size_type end;
    nextTokenPos(start, end);
    if((start == string::npos) ||
       (end   == string::npos)   )
    {
        _hasNext = false;
        return retString;
    }
    _nextToken = _tokenString.substr(start, end-start);
    _currPos   = end;
    return retString; 
} 


void StringTokenizer::setString(string& toTokens)
{
    _currPos = 0;
    _tokenString = toTokens;
    string::size_type start, end;
    nextTokenPos(start, end);
    if((start == string::npos) ||
       (end   == string::npos)   )
    {
        _hasNext = false;
    }
    else
    {
        _hasNext   = true;
        _nextToken = _tokenString.substr(start, end-start);
        _currPos   = end;
    }   
}


UInt32 StringTokenizer::countTokens(void)
{
    string::size_type storePos = _currPos;     //need to save these
    bool              storeHasNext = _hasNext;

    UInt32 count = 0;  //token counter

    string::size_type start;
    string::size_type end;

    _currPos = 0;
    nextTokenPos(start, end);
    if((start == string::npos) ||
       (end   == string::npos)   )
    {
        _hasNext = false;
    }
    else
    {
        _hasNext = true;
        _currPos = end;
    }
    
    while(_hasNext)
    {
        count++;
        nextTokenPos(start, end);
        if((start == string::npos) ||
           (end   == string::npos)   )
        {
            _hasNext = false;
        }
        else
        {
            _hasNext = true;
            _currPos = end;
        }
    }

    _currPos = storePos;
    _hasNext = storeHasNext;

    return count;
}
        
    







