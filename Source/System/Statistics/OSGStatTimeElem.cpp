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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>
#include <OSGBaseFieldDataType.h>

#include "OSGStatTimeElem.h"

OSG_USING_NAMESPACE

/** \enum OSGVecBase::VectorSizeE
 *  \brief 
 */

/** \var OSGVecBase::VectorSizeE OSGVecBase::_iSize
 * 
 */

/** \fn const char *OSGVecBase::getClassname(void)
 *  \brief Classname
 */

/** \var OSGValueTypeT OSGVecBase::_values[iSize];
 *  \brief Value store
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char StatTimeElem::cvsid[] = "@(#)$Id: $";

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

StatTimeElem::StatTimeElem(StatElemDescBase *desc)
  : StatElem(desc)
{
}

StatElem *StatTimeElem::create ( StatElemDescBase *desc)
{
    return new StatTimeElem(desc);
}


//StatTimeElem::StatTimeElem(const StatTimeElem &source) :
//  Inherited(source),
//    // TODO: initialize members
//{
//}

/** \brief Destructor
 */

StatTimeElem::~StatTimeElem(void)
{
}

/*------------------------------ access -----------------------------------*/

void StatTimeElem::putToString(std::string &str, const char *format)
{
    if(!format)
    {
        FieldDataTraits1<Time>::putToString(_time, str);
    }
    else
    {
        const char *proc = strchr(format,'%');        
              char *temp = new char [strlen(format) + 40];

        if(proc)
        {
            if(! strncmp(proc, "%ms", 3))
            {
                std::string fcopy(format);
                fcopy.insert((proc - format) + 1,".2f ");
                sprintf(temp, fcopy.c_str(), ((double)_time)*1000.);
            }
            else if(! strncmp(proc, "%r", 2))
            {
                std::string fcopy(format);
                fcopy.erase((proc - format) + 1, 1);
                sprintf(temp, fcopy.c_str(), 1./(double)_time);
            }
            else
            {
                sprintf(temp, format, (double)_time);
            }
           
        }
        else
        {
            sprintf(temp, format, (double)_time);
        }
        
        str = temp;
        delete [] temp;
    }
}

bool StatTimeElem::getFromString(const Char8 *&inVal)
{
    return FieldDataTraits1<Time>::getFromString(_time, inVal);
}

Real64 StatTimeElem::getValue(void)
{
    return static_cast<Real64>(getTime());
}

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

StatTimeElem& StatTimeElem::operator = (const StatTimeElem &source)
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

bool StatTimeElem::operator < (const StatTimeElem &other) const
{
    return this < &other;
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
    static Char8 cvsid_hpp[] = OSGSTATTIMEELEM_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGSTATTIMEELEM_INLINE_CVSID;
}
