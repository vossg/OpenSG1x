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
 * by the Free Software Foundation, version 2.             
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

#define OSG_COMPILESYSTEMLIB

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGStatElemDesc.h"

#include "OSGLog.h"

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
vector<StatElemDesc*> *StatElemDesc::_descVec = 0;
  
char StatElemDesc::cvsid[] = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/



/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/
StatElemDesc *StatElemDesc::findDescByName (const Char8 *name)
{
  Int32 i,n = _descVec ? _descVec->size() : 0;
  StatElemDesc *desc = 0;

  if (name && *name && n)
    for (i = 0; i < n; i++)
      if (!strcmp(name,(*_descVec)[i]->_name.str())) {
        desc = (*_descVec)[i];
        break;
      }
  
  return desc;
}

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
StatElemDesc::StatElemDesc ( const Char8 *name, const Char8 *description,
                             CreateStatElemMethod createMethod )
  :_ID(-1), _name(name), _description(description), 
   _createMethod(createMethod)
{
  StatElemDesc *desc = 0;

  if (_descVec) 
    desc = findDescByName (name);
  else
    _descVec = new vector<StatElemDesc*>;
  
  if (desc) {
    FFATAL (( "Try to register the StatElemDesc name %s a second time\n",
              name ));
  }
  else {
    _ID = _descVec->size();
    _descVec->push_back(this);
  }
}  

//StatElemDesc::StatElemDesc(const StatElemDesc &source) :
//	Inherited(source),
//	  // TODO: initialize members
//{
//}

/** \brief Destructor
 */

StatElemDesc::~StatElemDesc(void)
{
}

void StatElemDesc::printAll(void)
{
  Int32 i,n = _descVec ? _descVec->size() : 0;

  for (i = 0; i < n; i++)
    (*_descVec)[i]->print();
}

void StatElemDesc::print(void)
{
  FLOG (( "StatElemDesc: ID/Name/Description: %d/%s/%s\n",
          _ID, _name.str(), _description.str() ));
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

StatElemDesc& StatElemDesc::operator = (const StatElemDesc &source)
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

Bool StatElemDesc::operator < (const StatElemDesc &other) const
{
    return this < &other;
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


