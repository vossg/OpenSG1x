/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2003 by the OpenSG Forum                 *
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

#include "OSGclassname.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class classname
    \ingroup GrpName

classname documentation
 
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/*! \enum classname::ENUMNAME
  
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/*! \var VARTYPE classname::_VARNAME
    variable documentation
 */

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*================================ PUBLIC =================================*/

/*=============================== PROTECTED ===============================*/

/*================================ PRIVATE ================================*/


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*================================ PUBLIC =================================*/

/*=============================== PROTECTED ===============================*/

/*================================ PRIVATE ================================*/

/*-------------------------------------------------------------------------*/

/*------------------------- constructors ----------------------------------*/

/*! Constructor documentation
 */
classname::classname(void) :
    Inherited(),
      // TODO: initialize members
{
}

/*-------------------------- destructor -----------------------------------*/

/*! Destructor documentation
 */
classname::~classname(void)
{
}

/*-------------------------- assignment -----------------------------------*/

/*! assignment
 */
classname& classname::operator = (const classname &source)
{
    if(this == &source)
        return *this;

    // copy parts inherited from parent
    *(static_cast<Inherited *>(this)) = source;

    // free mem alloced by members of 'this'

    // alloc new mem for members

    // copy
}

/*-------------------------- comparison -----------------------------------*/

/*! less
 */

bool classname::operator < (const classname &other) const
{
    return this < &other;
}

/*! equal
 */

bool classname::operator == (const classname &other) const
{
}

/*! unequal
 */

bool classname::operator != (const classname &other) const
{
    return ! (*this == other);
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
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGTemplate.cpp,v 1.1 2004/02/19 16:45:44 a-m-z Exp $";
    static Char8 cvsid_hpp[] = OSGCLASSNAME_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGCLASSNAME_INLINE_CVSID;
}

