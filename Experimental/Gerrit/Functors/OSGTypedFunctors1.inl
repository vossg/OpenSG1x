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

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

template <class RetT,
          class CallArgT,
          class SizeTraitsT> inline
TypedFunctor1Base<RetT, 
                  CallArgT,
                  SizeTraitsT>::TypedFunctor1Base(void) :
    Inherited()
{
}

template <class RetT,
          class CallArgT,
          class SizeTraitsT> inline
TypedFunctor1Base<RetT, 
                  CallArgT, 
                  SizeTraitsT>::TypedFunctor1Base(
    const TypedFunctor1Base &source) :

    Inherited(source)
{
    postCopyConstruct(source);
}


/** \brief Destructor
 */

template <class RetT,
          class CallArgT,
          class SizeTraitsT> inline
TypedFunctor1Base<RetT, 
                  CallArgT,
                  SizeTraitsT>::~TypedFunctor1Base(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

#ifdef __sgi
#pragma set woff 1551 
#endif

template <class RetT,
          class CallArgT,
          class SizeTraitsT> inline
RetT TypedFunctor1Base<RetT, 
                       CallArgT,
                       SizeTraitsT>::call(CallArgType)
{
    RetT returnValue;

    FWARNING(("TypedFunctor1Base::call called, undefined behaviour "
                 "might be the consequence\n"));

    return returnValue;
}

#ifdef __sgi
#pragma reset woff 1551 
#endif

template <class RetT,
          class CallArgT,
          class SizeTraitsT> inline
void TypedFunctor1Base<RetT, 
                       CallArgT,
                       SizeTraitsT>::operator =(
                              const TypedFunctor1Base &source)
{
    if (this != &source)
    {
        *(static_cast<Inherited *>(this)) = source;
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

template <class CallArgT, class SizeTraitsT> inline
TypedVoidFunctor1Base<CallArgT,
                      SizeTraitsT>::TypedVoidFunctor1Base(void) :
    Inherited()
{
}

template <class CallArgT, class SizeTraitsT> inline
TypedVoidFunctor1Base<CallArgT, SizeTraitsT>::TypedVoidFunctor1Base(
    const TypedVoidFunctor1Base &source) :

    Inherited(source)
{
    postCopyConstruct(source);
}


/** \brief Destructor
 */

template <class CallArgT, class SizeTraitsT> inline
TypedVoidFunctor1Base<CallArgT, 
                      SizeTraitsT>::~TypedVoidFunctor1Base(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

template <class CallArgT, class SizeTraitsT> inline
void TypedVoidFunctor1Base<CallArgT, 
                           SizeTraitsT>::call(CallArgType)
{
    FWARNING(("TypedFunctor1Base::call called, undefined behaviour " 
                 "might be the consequence\n"));
}

template <class CallArgT,
          class SizeTraitsT> inline
void TypedVoidFunctor1Base<CallArgT,
                           SizeTraitsT>::operator =(
                               const TypedVoidFunctor1Base &source)
{
    if (this != &source)
    {
        *(static_cast<Inherited *>(this)) = source;
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

template <class RetT, 
          class CallArgT, 
          class SizeTraitsT> inline
TypedFunctionFunctor1<RetT, 
                      CallArgT,
                      SizeTraitsT>::TypedFunctionFunctor1(void)  :
    Inherited()
{
}

/** \brief Copy Constructor
 */


template <class RetT, 
          class CallArgT, 
          class SizeTraitsT> inline
TypedFunctionFunctor1<RetT,
                      CallArgT,
                      SizeTraitsT>::TypedFunctionFunctor1(
    const TypedFunctionFunctor1 &source) : 

    Inherited(source) 
{
}
    

/** \brief Destructor
 */


template <class RetT, 
          class CallArgT, 
          class SizeTraitsT> inline
TypedFunctionFunctor1<RetT,
                      CallArgT,
                      SizeTraitsT>::~TypedFunctionFunctor1(void) 
{
}

/*-------------------------- your_category---------------------------------*/

#ifdef __sgi
#pragma set woff 1551 
#endif

template <class RetT, 
          class CallArgT, 
          class SizeTraitsT> inline
RetT TypedFunctionFunctor1<RetT, 
                           CallArgT,
                           SizeTraitsT>::call(CallArgType pObj) 
{ 
    RetT returnValue;

    if(_flags & FuncPtrValid)
    {
        FunctionF pFunc = *((FunctionF *) _data2);
        
        return pFunc(pObj);
    }
    
    return returnValue;
}

#ifdef __sgi
#pragma reset woff 1551 
#endif





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

template <class CallArgT, 
          class SizeTraitsT> inline
TypedFunctionVoidFunctor1<CallArgT,
                          SizeTraitsT>::TypedFunctionVoidFunctor1(void)  :
    Inherited()
{
}

/** \brief Copy Constructor
 */


template <class CallArgT, 
          class SizeTraitsT> inline
TypedFunctionVoidFunctor1<CallArgT,
                          SizeTraitsT>::TypedFunctionVoidFunctor1(
                              const TypedFunctionVoidFunctor1 &source) : 

    Inherited(source) 
{
}
    

/** \brief Destructor
 */


template <class CallArgT, 
          class SizeTraitsT> inline
TypedFunctionVoidFunctor1<CallArgT,
                          SizeTraitsT>::~TypedFunctionVoidFunctor1(void) 
{
}

/*-------------------------- your_category---------------------------------*/

template <class CallArgT, 
          class SizeTraitsT> inline
void TypedFunctionVoidFunctor1<CallArgT,
                               SizeTraitsT>::call(CallArgType pObj) 
{ 
    if(_flags & FuncPtrValid)
    {
        FunctionF pFunc = *((FunctionF *) _data2);
        
        pFunc(pObj);
    }
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

template <class RetT, 
          class CallArgT, 
          class SizeTraitsT> inline
TypedObjectFunctor1<RetT, 
                    CallArgT,
                    SizeTraitsT>::TypedObjectFunctor1(void)  :
    Inherited()
{
}

/** \brief Copy Constructor
 */


template <class RetT, 
          class CallArgT, 
          class SizeTraitsT> inline
TypedObjectFunctor1<RetT,
                    CallArgT,
                    SizeTraitsT>::TypedObjectFunctor1(
    const TypedObjectFunctor1 &source) : 

    Inherited(source) 
{
}
    

/** \brief Destructor
 */


template <class RetT, 
          class CallArgT, 
          class SizeTraitsT> inline
TypedObjectFunctor1<RetT,
                    CallArgT,
                    SizeTraitsT>::~TypedObjectFunctor1(void) 
{
}

/*-------------------------- your_category---------------------------------*/

#ifdef __sgi
#pragma set woff 1551 
#endif

template <class RetT, 
          class CallArgT, 
          class SizeTraitsT> inline
RetT TypedObjectFunctor1<RetT, 
                         CallArgT,
                         SizeTraitsT>::call(CallArgType obj) 
{ 
    RetT returnValue;

    if(_flags & FuncPtrValid)
    {
        return TypeTraits::callObjectMethod(_data2, obj);
    }
    

    return returnValue;
}

#ifdef __sgi
#pragma reset woff 1551 
#endif


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

template <class CallArgT, 
          class SizeTraitsT> inline
TypedObjectVoidFunctor1<CallArgT,
                        SizeTraitsT>::TypedObjectVoidFunctor1(void)  :
    Inherited()
{
}

/** \brief Copy Constructor
 */


template <class CallArgT, 
          class SizeTraitsT> inline
TypedObjectVoidFunctor1<CallArgT,
                        SizeTraitsT>::TypedObjectVoidFunctor1(
    const TypedObjectVoidFunctor1 &source) : 

    Inherited(source) 
{
}
    

/** \brief Destructor
 */


template <class CallArgT, 
          class SizeTraitsT> inline
TypedObjectVoidFunctor1<CallArgT,
                        SizeTraitsT>::~TypedObjectVoidFunctor1(void) 
{
}


/*-------------------------- your_category---------------------------------*/

template <class CallArgT, 
          class SizeTraitsT> inline
void TypedObjectVoidFunctor1<CallArgT,
                             SizeTraitsT>::call(CallArgType obj) 
{ 
    if(_flags & FuncPtrValid)
    {
        TypeTraits::callObjectMethodVoid(_data2, obj);
    }
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

template <class RetT, 
          class StoredObjectT,
          class ArgsT, 
          class SizeTraitsT> inline
TypedStoredObjectFunctor1<RetT, 
                          StoredObjectT,
                          ArgsT,
                          SizeTraitsT>::TypedStoredObjectFunctor1(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */


template <class RetT, 
          class StoredObjectT,
          class ArgsT, 
          class SizeTraitsT> inline
TypedStoredObjectFunctor1<RetT,
                          StoredObjectT,
                          ArgsT,
                          SizeTraitsT>::TypedStoredObjectFunctor1(
    const TypedStoredObjectFunctor1 &source) : 

    Inherited(source) 
{
}
    

/** \brief Destructor
 */


template <class RetT, 
          class StoredObjectT,
          class ArgsT, 
          class SizeTraitsT> inline
TypedStoredObjectFunctor1<RetT,
                          StoredObjectT,
                          ArgsT,
                          SizeTraitsT>::~TypedStoredObjectFunctor1(void) 
{
}

/*-------------------------- your_category---------------------------------*/

#ifdef __sgi
#pragma set woff 1551 
#endif

template <class RetT, 
          class StoredObjectT,
          class ArgsT, 
          class SizeTraitsT> inline
RetT TypedStoredObjectFunctor1<RetT, 
                               StoredObjectT,
                               ArgsT,
                               SizeTraitsT>::call(CallArgType obj) 
{ 
    RetT returnValue;

    if(_flags & FuncPtrValid &&
       _flags & ObjectValid)
    {
        return TypeTraits::callObjectMethod(_data1, _data2, obj);
    }

    return returnValue;
}

#ifdef __sgi
#pragma reset woff 1551 
#endif






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

template <class StoredObjectT, 
          class ArgsT,
          class SizeTraitsT> inline
TypedStoredObjectVoidFunctor1<StoredObjectT,
                              ArgsT,
                              SizeTraitsT>::TypedStoredObjectVoidFunctor1(
                                  void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */


template <class StoredObjectT, 
          class ArgsT,
          class SizeTraitsT> inline
TypedStoredObjectVoidFunctor1<StoredObjectT,
                              ArgsT,
                              SizeTraitsT>::TypedStoredObjectVoidFunctor1(
    const TypedStoredObjectVoidFunctor1 &source) : 

    Inherited(source) 
{
}
    

/** \brief Destructor
 */


template <class StoredObjectT, 
          class ArgsT,
          class SizeTraitsT> inline
TypedStoredObjectVoidFunctor1<StoredObjectT,
                              ArgsT,
                              SizeTraitsT>::~TypedStoredObjectVoidFunctor1(
    void) 
{
}

/*-------------------------- your_category---------------------------------*/

template <class StoredObjectT, 
          class ArgsT,
          class SizeTraitsT> inline
void TypedStoredObjectVoidFunctor1<StoredObjectT,
                                   ArgsT,
                                   SizeTraitsT>::call(CallArgType obj) 
{ 
    if(_flags & FuncPtrValid &&
       _flags & ObjectValid)
    {
        TypeTraits::callObjectMethodVoid(_data1, _data2, obj);
    }
}

OSG_END_NAMESPACE






