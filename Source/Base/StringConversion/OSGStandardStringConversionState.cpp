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
/*! \file OSGStandardStringConversionState.cpp
    \ingroup GrpBaseStringConversion
 */
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGStandardStringConversionState.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */


StandardStringConversionState::StandardStringConversionState(UInt32 indent,
                                                             UInt32 width  ) :
     Inherited      (      ),

    _indent         (indent),
    _width          (width ), 
    
    _lineLength     (     0),
    _noLineBreakHint(false ), 
    _multiFieldHint (false ), 
    _mfSeparator    (", "  ),
    _mfSepLength    (     2),
    _lastMFSepStart (      0)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

StandardStringConversionState::~StandardStringConversionState(void)
{
}


/*-------------------------------------------------------------------------*/
/*                             Handle Fields                               */

/*! beginField. StandardStringConversionState adds _indent many spaces
    before the values of a field. 
*/

std::string &StandardStringConversionState::beginField(
    const Field       *pF, 
          std::string &outStr)
{
    _lineLength     = 0;
    _lastMFSepStart = 0;

    if(pF->getCardinality() == FieldType::MULTI_FIELD)
    {
        _multiFieldHint = true;
    }
    else
    {
        _multiFieldHint = false;
    }

    if(strstr(pF->getContentType().getCName(), "String") != NULL)
    {
        _noLineBreakHint = true;
    }
    else
    {
        _noLineBreakHint = false;
    }

    outStr.append(_indent.str());
    return outStr;
}

/*! addValueStr. StandardStringConversionState formats fields with indention
    and a limitation on the width of the rows.
*/

std::string &StandardStringConversionState::addValueStr(std::string &value, 
                                                        std::string &outStr)
{
    UInt32 valLength = value.length();

    if(_noLineBreakHint)
    {
        if(_lineLength+valLength > _width)
        {
            outStr.append("\n");
            _lineLength = 0;
            outStr.append(_indent.str());
        }
        
        outStr.append(value);
        _lineLength += valLength;
    }
    else
    {
        StringTokenizer tokens(value);
        std::string     token;

        bool first = true;

        while(tokens.hasNext() == true)
        {
                        token       = tokens.getNext();
            UInt32      tokenLength = token.length();

            if(_lineLength + tokenLength > _width)
            {
                outStr.append("\n");
                _lineLength = 0;
                outStr.append(_indent.str());
                first = true; 
            }

            if(first == true)
            {
                first = false;
            }
            else
            {
                outStr.append(" ");
            }

            outStr.append(token);

            _lineLength += tokenLength+1;
        }
     }
    
    if(_multiFieldHint == true)
    {
        _lastMFSepStart = outStr.length();
        outStr.append(_mfSeparator);
        _lineLength += _mfSepLength;
    }

    return outStr;
}


/*! endField. StandardStringConversionState removes the last MultiField-
    Separator-String appended to outStr.
*/

std::string &StandardStringConversionState::endField(
    const      Field  *OSG_CHECK_ARG(pF),
          std::string &outStr)
{
    if(_multiFieldHint == true)
    {
        outStr = outStr.erase(_lastMFSepStart, _mfSepLength);
    }

    return outStr;
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
    static Char8 cvsid_hpp[] = OSGSTANDARDSTRINGCONVERSIONSTATE_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGSTANDARDSTRINGCONVERSIONSTATE_INLINE_CVSID;
}
