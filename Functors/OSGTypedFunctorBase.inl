/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2002 by the OpenSG Forum                        *
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

#include <OSGLog.h>

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

template <class SizeTraitsT> inline
void TypedFunctorBase<SizeTraitsT>::postCopyConstruct(
    const TypedFunctorBase &source)
{
    memcpy(this, &source, 
           sizeof(TypedFunctorBase<SizeTraitsT>)); 
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

template <class SizeTraitsT> inline
TypedFunctorBase<SizeTraitsT>::TypedFunctorBase(void) :
    Inherited()
{
}

template <class SizeTraitsT> inline
TypedFunctorBase<SizeTraitsT>::TypedFunctorBase(
    const TypedFunctorBase &source) :

    Inherited(source)
{
}


/** \brief Destructor
 */

template <class SizeTraitsT> inline
TypedFunctorBase<SizeTraitsT>::~TypedFunctorBase(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

template <class SizeTraitsT> inline
void TypedFunctorBase<SizeTraitsT>::operator =(
    const TypedFunctorBase &source)
{
    if(this != &source)
    {
        memcpy(this, &source, 
               sizeof(TypedFunctorBase<SizeTraitsT>)); 
    }
}

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

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

template <class Parent, class Params> inline
TypedFunctionFunctorBase<Parent, Params>::TypedFunctionFunctorBase(void)  :
    Inherited()
{
}

/** \brief Copy Constructor
 */


template <class Parent, class Params> inline
TypedFunctionFunctorBase<Parent, Params>::TypedFunctionFunctorBase(
    const TypedFunctionFunctorBase &source) : 

    Inherited(source) 
{
}
    

/** \brief Destructor
 */


template <class Parent, class Params> inline
TypedFunctionFunctorBase<Parent, Params>::~TypedFunctionFunctorBase(void) 
{
}

/*------------------------------ access -----------------------------------*/

template <class Parent, class Params> inline
void TypedFunctionFunctorBase<Parent, Params>::setMethod(FunctionF pFunc)
{
    Self::_flags |=  Self::FuncPtrValid;

    *((FunctionF *) Self::_data2) = pFunc; 
}







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

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

template <class Parent, class Params> inline
TypedObjectFunctorBase<Parent, Params>::TypedObjectFunctorBase(void)  :
    Inherited()
{
}

/** \brief Copy Constructor
 */


template <class Parent, class Params> inline
TypedObjectFunctorBase<Parent, Params>::TypedObjectFunctorBase(
    const TypedObjectFunctorBase &source) : 

    Inherited(source) 
{
}
    

/** \brief Destructor
 */


template <class Parent, class Params> inline
TypedObjectFunctorBase<Parent, Params>::~TypedObjectFunctorBase(void) 
{
}

/*------------------------------ access -----------------------------------*/


template <class Parent, class Params> inline
void TypedObjectFunctorBase<Parent, Params>::setMethod(ObjMethodF pFunc)
{
    Self::_flags |=  Self::FuncPtrValid;

    *((ObjMethodF *) Self::_data2) = pFunc; 
}




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

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

template <class Parent, class Params> inline
TypedStoredObjectFunctorBase<Parent, Params>::TypedStoredObjectFunctorBase(
    void) :

    Inherited()
{
}

/** \brief Copy Constructor
 */


template <class Parent, class Params> inline
TypedStoredObjectFunctorBase<Parent, Params>::TypedStoredObjectFunctorBase(
    const TypedStoredObjectFunctorBase &source) : 

    Inherited(source) 
{
}
    

/** \brief Destructor
 */


template <class Parent, class Params> inline
TypedStoredObjectFunctorBase<Parent, Params>::~TypedStoredObjectFunctorBase(
                                   void) 
{
}

/*------------------------------ access -----------------------------------*/


template <class Parent, class Params> inline
void TypedStoredObjectFunctorBase<Parent, Params>::setMethod(ObjMethodF pFunc)
{
    Self::_flags |=  Self::FuncPtrValid;

    *((ObjMethodF *) Self::_data2) = pFunc; 
}

template <class Parent, class Params> inline
void TypedStoredObjectFunctorBase<Parent, Params>::setCalledObject(
    SetObjectT pObj)
{
    Self::_flags |= Self::ObjectValid;

    Params::setCalledObject(reinterpret_cast<Char8 *>(Self::_data1), pObj);
}

template <class Parent, class Params> inline
void TypedStoredObjectFunctorBase<Parent, Params>::setObjectAndMethod(
    SetObjectT pObj, 
    ObjMethodF pFunc)
{
    Self::_flags |=  Self::FuncPtrValid;
    Self::_flags |=  Self::ObjectValid;
     
    Params::setCalledObject(reinterpret_cast<Char8 *>(Self::_data1), pObj);

    *((ObjMethodF *) Self::_data2) = pFunc; 
}

OSG_END_NAMESPACE
