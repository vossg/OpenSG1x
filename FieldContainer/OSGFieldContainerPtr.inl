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

#include <iostream>

#include <OSGThread.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

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
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------------------------- cast ------------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

template <class BasePtrTypeT, class FieldContainerTypeT>
char FCPtr<BasePtrTypeT, FieldContainerTypeT>::cvsid[] = "@(#)$Id: $";

template <class BasePtrTypeT, class FieldContainerTypeT> 
const FCPtr<BasePtrTypeT, FieldContainerTypeT>
    FCPtr<BasePtrTypeT, FieldContainerTypeT>::NullPtr;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/** \brief Construct a pointer from a give node.
 */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FCPtr<BasePtrTypeT, FieldContainerTypeT>::FCPtr(
    const FieldContainerTypeT &source) :

    Inherited(source)
{
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FCPtr<BasePtrTypeT, FieldContainerTypeT>::FCPtr(
    const FieldContainerTypeT *source) :

    Inherited(source)
{
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FCPtr<BasePtrTypeT, FieldContainerTypeT>::FCPtr(
    const FieldContainerTypeT *source,
    const UInt16               uiSize,
    const UInt16               uiParentEPos) :

    Inherited(source, uiSize, uiParentEPos)
{
}

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
FCPtr<BasePtrTypeT, FieldContainerTypeT>::FCPtr(const FCPtr &source):
	Inherited(source)
{
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
FieldContainerTypeT *FCPtr<BasePtrTypeT, FieldContainerTypeT>::operator ->(
    void)
{
    return (FieldContainerTypeT *) getElemP(Thread::getAspect());
}

/** \brief Const arrow operator
 */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FieldContainerTypeT *FCPtr<BasePtrTypeT, 
                            FieldContainerTypeT>::operator ->(void) const
{
    return (FieldContainerTypeT *) getElemP(Thread::getAspect());
}

/** \brief Dereference operator
 */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FieldContainerTypeT &FCPtr<BasePtrTypeT, FieldContainerTypeT>::operator *(
    void)
{
    return *((FieldContainerTypeT *) getElemP(Thread::getAspect()));
}

/** \brief Const dereference operator
 */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FieldContainerTypeT &FCPtr<BasePtrTypeT, 
                            FieldContainerTypeT>::operator *(void) const
{
    return *((FieldContainerTypeT *) getElemP(Thread::getAspect()));
}


template <class BasePtrTypeT, class FieldContainerTypeT> inline
FieldContainerTypeT *FCPtr<BasePtrTypeT, FieldContainerTypeT>::getCPtr(void)

{
    return (FieldContainerTypeT *) getElemP(Thread::getAspect());
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FieldContainerTypeT *
    FCPtr<BasePtrTypeT, FieldContainerTypeT>::getCPtr(void) const
{
    return (FieldContainerTypeT *) getElemP(Thread::getAspect());
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
void FCPtr<BasePtrTypeT, FieldContainerTypeT>::operator = (
    const FCPtr &source)
{
	if (this == &source)
		return;

	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = source;
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/





//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

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
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------------------------- cast ------------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

template <class BasePtrTypeT, class FieldContainerTypeT>
char ConstFCPtr<BasePtrTypeT, FieldContainerTypeT>::cvsid[] = "@(#)$Id: $";

template <class BasePtrTypeT, class FieldContainerTypeT> 
const ConstFCPtr<BasePtrTypeT, FieldContainerTypeT>
    ConstFCPtr<BasePtrTypeT, FieldContainerTypeT>::NullPtr;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/** \brief Construct a pointer from a give node.
 */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
ConstFCPtr<BasePtrTypeT, FieldContainerTypeT>::ConstFCPtr(
    const FieldContainerTypeT &source) :

    Inherited(source)
{
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
ConstFCPtr<BasePtrTypeT, FieldContainerTypeT>::ConstFCPtr(
    const FieldContainerTypeT *source) :
    
    Inherited(source)
{
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
ConstFCPtr<BasePtrTypeT, FieldContainerTypeT>::ConstFCPtr(
    const FieldContainerTypeT *source, 
    const UInt16               uiSize,
    const UInt16               uiParentEPos) :
    
    Inherited(source, uiSize, uiParentEPos)
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
ConstFCPtr<BasePtrTypeT, FieldContainerTypeT>::ConstFCPtr(void) :
	Inherited()
{
}

/** \brief Copy Constructor
 */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
ConstFCPtr<BasePtrTypeT, FieldContainerTypeT>::ConstFCPtr(
    const NCFCPtr &source):
	Inherited(source)
{
}

/** \brief Copy Constructor
 */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
ConstFCPtr<BasePtrTypeT, FieldContainerTypeT>::ConstFCPtr(
    const ConstFCPtr &source):
	Inherited(source)
{
}

/** \brief Destructor
 */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
ConstFCPtr<BasePtrTypeT, FieldContainerTypeT>::~ConstFCPtr(void)
{
}

/*-------------------------- pointer operators ------------------------------*/

/** \brief Arrow operator
 */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
const FieldContainerTypeT *ConstFCPtr<BasePtrTypeT, 
                                       FieldContainerTypeT>::operator ->(void)
{
    return (FieldContainerTypeT *) getElemP(Thread::getAspect());
}

/** \brief Const arrow operator
 */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
const FieldContainerTypeT *ConstFCPtr<BasePtrTypeT, 
                                       FieldContainerTypeT>::operator ->(
                                           void) const
{
    return (FieldContainerTypeT *) getElemP(Thread::getAspect());
}

/** \brief Dereference operator
 */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
const FieldContainerTypeT &ConstFCPtr<BasePtrTypeT, 
                                       FieldContainerTypeT>::operator *(void)
{
    return *((FieldContainerTypeT *) getElemP(Thread::getAspect()));
}

/** \brief Const dereference operator
 */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
const FieldContainerTypeT &ConstFCPtr<BasePtrTypeT, 
                                       FieldContainerTypeT>::operator *(
                                           void) const
{
    return *((FieldContainerTypeT *) getElemP(Thread::getAspect()));
}


template <class BasePtrTypeT, class FieldContainerTypeT> inline
const FieldContainerTypeT *ConstFCPtr<BasePtrTypeT, 
                                       FieldContainerTypeT>::getCPtr(void)

{
    return (FieldContainerTypeT *) getElemP(Thread::getAspect());
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
const FieldContainerTypeT *
    ConstFCPtr<BasePtrTypeT, FieldContainerTypeT>::getCPtr(void) const
{
    return (FieldContainerTypeT *) getElemP(Thread::getAspect());
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
void ConstFCPtr<BasePtrTypeT, FieldContainerTypeT>::operator = (
    const NCFCPtr &source)
{
	if (static_cast<FieldContainerPtrBase *>(this) == 
        static_cast<const FieldContainerPtrBase *> (&source))
    {
		return;
    }

	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = source;
}

/** \brief assignment
 */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
void ConstFCPtr<BasePtrTypeT, FieldContainerTypeT>::operator = (
    const ConstFCPtr &source)
{
	if (this == &source)
		return;

	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = source;
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/




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

#ifdef __sgi
#pragma set woff 1424
#endif

template <class RetTypeT, class InTypeT> inline
RetTypeT dcast(const InTypeT oIn)
{
    return RetTypeT(
        (dynamic_cast<const typename RetTypeT::ObjectType *>(oIn.getCPtr())),
        oIn._containerSize,
        oIn._uiParentEPos);
}

#ifdef __sgi
#pragma reset woff 1424
#endif

OSG_END_NAMESPACE
