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

#include "OSGStatElemDesc.h"
#include "OSGStatElem.h"

#include "OSGStatCollector.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGSTATCOLLECTOR_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGSTATCOLLECTOR_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

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

char StatCollector::cvsid[] = "@(#)$Id: $";

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

StatCollector::StatCollector(void)
{
  _elemVec.resize(StatElemDescBase::getNumOfDescs());
}


//StatCollector::StatCollector(const StatCollector &source) :
//  Inherited(source),
//    // TODO: initialize members
//{
//}

/** \brief Destructor
 */

StatCollector::~StatCollector(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

void StatCollector::putToString(string &str) const
{
    vector<StatElem*>::const_iterator it;
    Bool first = true;
     
    str = "{";
    
    for(it = _elemVec.begin(); it != _elemVec.end(); ++it)
    {
        if(*it != NULL)
        {
            std::string elem;
            
            if(!first)
                str.append("|");
            str.append((*it)->getDesc()->getName().str());
            str.append(":");
            (*it)->putToString(elem);
            str.append(elem);
            first = false;
        }
    }
    str.append("}");
}
     
Bool StatCollector::getFromString(const Char8 *&inVal)
{
    const Char8 *c = inVal;
    
    if(*c++ != '{')
        return false;

    StatElemDescBase *desc;
    StatElem *elem;
    
    clearElems();
    
    while(*c && *c != '}')
    {
        const Char8 *end = c;
        
        while(*end != 0 && *end != ':' && *end != '}' && *end != '|')
            end++;
            
        if(*end == 0 || *end == '}' || *end == '|')
            return false;
        
        string name(c, end - c);
        desc = StatElemDescBase::findDescByName(name.c_str());
        
        if(!desc)
            return false;
        
        elem = getElem(*desc);

        c = end = end + 1;       
        while(*end != 0 && *end != '}' && *end != '|')
            end++;
            
        if(*end == 0)
            return false;

        string val(c, end - c);
        const Char8 *valp = val.c_str();
        if(!elem->getFromString(valp))
            return false;
 
        c = end + 1;
    }
    return true;
}

void StatCollector::clearElems(void)
{
    for(vector<StatElem*>::iterator i = _elemVec.begin(); 
        i != _elemVec.end();
        ++i)
    {
        delete *i;
        *i = NULL;
    }
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

StatCollector& StatCollector::operator = (const StatCollector &source)
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

Bool StatCollector::operator < (const StatCollector &other) const
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


