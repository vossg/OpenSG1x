/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <OSGLog.h>
#include <OSGThread.h>

OSG_BEGIN_NAMESPACE

/** \fn const char *FCPtr::getClassname(void)
 *  \brief Classname
 */

/** \typedef FCPtr::Inherited
 *  \brief Parent type
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

template <class BaseFieldContainerTypeT, class FieldContainerTypeT>
char FCPtr<BaseFieldContainerTypeT,
              FieldContainerTypeT    >::cvsid[] = "@(#)$Id: $";

template <class BasePtrTypeT, class FieldContainerTypeT> 
const FCPtr<BasePtrTypeT, FieldContainerTypeT>
    FCPtr<BasePtrTypeT, FieldContainerTypeT>::NullPtr;


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

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FCPtr<BasePtrTypeT, FieldContainerTypeT>::FCPtr(void) :
	Inherited()
{
}

/** \brief Copy Constructor
 */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FCPtr<BasePtrTypeT, FieldContainerTypeT>::FCPtr(
    const FCPtr &source) :
	Inherited(source)
{
}

/** \brief Construct a pointer from a give node.
 */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FCPtr<BasePtrTypeT, FieldContainerTypeT>::FCPtr(
    const FieldContainerTypeT &source) :

    Inherited()
{
    _containerSize = source.getSize();
    _storeP        = (UInt8 *) &source;
    _storeP       -= getElemOff(Thread::getAspect());
}

/** \brief Destructor
 */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FCPtr<BasePtrTypeT, FieldContainerTypeT>::~FCPtr(void)
{
}

/*-------------------------- pointer operators ------------------------------*/

/** \brief Arrow operator
 */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FieldContainerTypeT *FCPtr<BasePtrTypeT, 
                           FieldContainerTypeT>::operator ->(void)
{
    return (FieldContainerTypeT *) getElemP(Thread::getAspect());
}

/** \brief Const arrow operator
 */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
const FieldContainerTypeT *FCPtr<BasePtrTypeT, 
                                 FieldContainerTypeT>::operator ->(
                                     void) const
{
    return (FieldContainerTypeT *) getElemP(Thread::getAspect());
}

/** \brief Dereference operator
 */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FieldContainerTypeT &FCPtr<BasePtrTypeT, 
                           FieldContainerTypeT>::operator *(void)
{
    return *((FieldContainerTypeT *) getElemP(Thread::getAspect()));
}

/** \brief Const dereference operator
 */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
const FieldContainerTypeT &FCPtr<BasePtrTypeT, 
                                 FieldContainerTypeT>::operator *(void) const
{
    return *((FieldContainerTypeT *) getElemP(Thread::getAspect()));
}


template <class BasePtrTypeT, class FieldContainerTypeT> inline
FieldContainerTypeT *FCPtr<BasePtrTypeT, 
                           FieldContainerTypeT>::getCPtr(void)

{
    return (FieldContainerTypeT *) getElemP(Thread::getAspect());
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
const FieldContainerTypeT *
    FCPtr<BasePtrTypeT, FieldContainerTypeT>::getCPtr(void) const
{
    return (FieldContainerTypeT *) getElemP(Thread::getAspect());
}


#ifdef _FCPTR_HAS_CAST_OPERATOR
/** \brief FieldContainerTypeT * cast operator
 */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FCPtr<BasePtrTypeT, 
         FieldContainerTypeT>::operator FieldContainerTypeT *(void)
{
    return (FieldContainerTypeT *) getElemP(Thread::getAspect());
}
#endif

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FCPtr<BasePtrTypeT, FieldContainerTypeT> & 
    FCPtr<BasePtrTypeT, 
          FieldContainerTypeT>::operator = (const FCPtr &source)
{
	if (this == &source)
		return *this;

	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = source;

    return *this;
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
void FCPtr<BasePtrTypeT, 
           FieldContainerTypeT>::dump(void) const
{
    if(_storeP != NULL)
    {
        SDEBUG << "CFC Dump" << endl;
        
        dumpContent();
    }
    else
    {
        SDEBUG << "CFC Dump : (NULL)" << endl;
    }
}

/*
template <class BasePtr, class ContainerType>
    OSG_FIELDCONTAINER_DLLMAPPING
	inline ostream &operator 
			<<(ostream &os, const FCPtr<BasePtr, ContainerType> &fc)
{
}
*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


///---------------------------------------------------------------------------
///  FUNCTION: 
///---------------------------------------------------------------------------
//:  Example for the head comment of a function
///---------------------------------------------------------------------------
///
//p: Paramaters: 
//p: 
///
//g: GlobalVars:
//g: 
///
//r: Return:
//r: 
///
//c: Caution:
//c: 
///
//a: Assumptions:
//a: 
///
//d: Description:
//d: 
///
//s: SeeAlso:
//s: 
///---------------------------------------------------------------------------

OSG_END_NAMESPACE

