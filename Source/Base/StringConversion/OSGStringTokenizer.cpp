/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGStringTokenizer.cpp
    \ingroup GrpBaseStringConversion
 */
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGStringTokenizer.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

StringTokenizer::StringTokenizer(std::string &toTokens) : 
    _hasNext    (false   ),
    _tokenString(toTokens),
    _nextToken  (        ),
    _currPos    (       0)
{
    std::string::size_type start;
    std::string::size_type end;

    nextTokenPos(start, end);

    if((start == std::string::npos) ||
       (end   == std::string::npos)  )
    {
        _hasNext = false;
    }
    else
    {
        _hasNext   = true;
        _nextToken = _tokenString.substr(start, end - start);
        _currPos   = end;
    }  
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

StringTokenizer::~StringTokenizer(void)
{
}

/*-------------------------------------------------------------------------*/
/*                              Tokenize                                   */

bool StringTokenizer::hasNext(void)
{
    return _hasNext;
}

std::string StringTokenizer::getNext(void)
{
    std::string retString = _nextToken;
    if(!_hasNext)
    {
        return retString;
    }
    std::string::size_type start;
    std::string::size_type end;
    nextTokenPos(start, end);
    if((start == std::string::npos) ||
       (end   == std::string::npos)   )
    {
        _hasNext = false;
        return retString;
    }
    _nextToken = _tokenString.substr(start, end-start);
    _currPos   = end;
    return retString; 
} 


void StringTokenizer::setString(std::string &toTokens)
{
    _currPos     = 0;
    _tokenString = toTokens;

    std::string::size_type start, end;

    nextTokenPos(start, end);

    if((start == std::string::npos) ||
       (end   == std::string::npos)  )
    {
        _hasNext = false;
    }
    else
    {
        _hasNext   = true;
        _nextToken = _tokenString.substr(start, end - start);
        _currPos   = end;
    }   
}

UInt32 StringTokenizer::countTokens(void)
{
    std::string::size_type storePos     = _currPos;
    bool                   storeHasNext = _hasNext;

    UInt32 count = 0;

    std::string::size_type start;
    std::string::size_type end;

    _currPos = 0;

    nextTokenPos(start, end);

    if((start == std::string::npos) ||
       (end   == std::string::npos)  )
    {
        _hasNext = false;
    }
    else
    {
        _hasNext = true;
        _currPos = end;
    }
    
    while(_hasNext == true)
    {
        count++;

        nextTokenPos(start, end);

        if((start == std::string::npos) ||
           (end   == std::string::npos)  )
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

void StringTokenizer::nextTokenPos(std::string::size_type &start,
                                   std::string::size_type &end  )
{
    start = _tokenString.find_first_not_of(" \t\n", _currPos);

    if(start == std::string::npos)
    {
        end = std::string::npos;

        return;
    }

    end = _tokenString.find_first_of(" \t\n", start);

    if(end == std::string::npos)
    {
        end = _tokenString.length();
    }
}
    
/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGSTRINGTOKENIZER_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGSTRINGTOKENIZER_INLINE_CVSID;
}







