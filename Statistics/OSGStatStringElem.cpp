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

#include <OSGConfig.h>
#include <OSGSysFieldDataType.h>

#include "OSGStatStringElem.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGStatStringElem.cpp,v 1.1 2002/03/19 17:46:17 dirk Exp $";
    static Char8 cvsid_hpp[] = OSGSTATSTRINGELEM_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGSTATSTRINGELEM_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char StatStringElem::cvsid[] = "@(#)$Id: OSGStatStringElem.cpp,v 1.1 2002/03/19 17:46:17 dirk Exp $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/



/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

StatStringElem::StatStringElem(StatElemDescBase *desc)
  : StatElem(desc), _value()
{
}

StatElem *StatStringElem::create(StatElemDescBase *desc)
{
    return new StatStringElem(desc);
}

void StatStringElem::putToString(string &str, const char *format)
{
    if(!format)
    {
        str = _value;
    }
    else
    {
        char *temp = new char [strlen(format) + _value.size() + 10];
        sprintf(temp, format, _value.c_str());
        str = temp;
        delete [] temp;
    }
}

bool StatStringElem::getFromString(const Char8 *&inVal)
{
    if(inVal != 0)
    {
        _value = inVal;
    }

    return true;
}

//StatStringElem::StatStringElem(const StatStringElem &source) :
//  Inherited(source),
//    // TODO: initialize members
//{
//}

/** \brief Destructor
 */

StatStringElem::~StatStringElem(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

StatStringElem& StatStringElem::operator = (const StatStringElem &source)
{
    if (this == &source)
        return *this;

    // copy parts inherited from parent
    //*(static_cast<Inherited *>(this)) = source;

    // free mem alloced by members of 'this'

    // alloc new mem for members

    // copy 

  return *this;
}

/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */

bool StatStringElem::operator < (const StatStringElem &other) const
{
    return this < &other;
}

/** \brief equal
 */

/** \brief unequal
 */


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


