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
          class ArgsT,
          class SizeTraitsT> inline
TypedFunctor2Base<RetT, 
                  CallArgT,
                  ArgsT,
                  SizeTraitsT>::TypedFunctor2Base(void) :
    Inherited()
{
}

template <class RetT,
          class CallArgT,
          class ArgsT,
          class SizeTraitsT> inline
TypedFunctor2Base<RetT, 
                  CallArgT,
                  ArgsT, 
                  SizeTraitsT>::TypedFunctor2Base(
    const TypedFunctor2Base &source) :

    Inherited(source)
{
    postCopyConstruct(source);
}


/** \brief Destructor
 */

template <class RetT,
          class CallArgT,
          class ArgsT,
          class SizeTraitsT> inline
TypedFunctor2Base<RetT, 
                  CallArgT,
                  ArgsT, 
                  SizeTraitsT>::~TypedFunctor2Base(void)
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
          class ArgsT,
          class SizeTraitsT> inline
RetT TypedFunctor2Base<RetT, 
                       CallArgT,
                       ArgsT,
                       SizeTraitsT>::call(CallArgType, Arg1Type)
{
    RetT returnValue;

    FWARNING(("TypedFunctor2Base::call called, undefined behaviour "
                 "might be the consequence\n"));

    return returnValue;
}

#ifdef __sgi
#pragma reset woff 1551 
#endif

template <class RetT,
          class CallArgT,
          class ArgsT,
          class SizeTraitsT> inline
void TypedFunctor2Base<RetT, 
                       CallArgT, 
                       ArgsT, 
                       SizeTraitsT>::operator =(
    const TypedFunctor2Base &source)
{
    if(this != &source)
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

template <class CallArgT, class ArgsT, class SizeTraitsT> inline
TypedVoidFunctor2Base<CallArgT,
                      ArgsT, 
                      SizeTraitsT>::TypedVoidFunctor2Base(void) :
    Inherited()
{
}

template <class CallArgT, class ArgsT, class SizeTraitsT> inline
TypedVoidFunctor2Base<CallArgT, 
                      ArgsT, 
                      SizeTraitsT>::TypedVoidFunctor2Base(
    const TypedVoidFunctor2Base &source) :

    Inherited(source)
{
    postCopyConstruct(source);
}


/** \brief Destructor
 */

template <class CallArgT, class ArgsT, class SizeTraitsT> inline
TypedVoidFunctor2Base<CallArgT,
                      ArgsT, 
                      SizeTraitsT>::~TypedVoidFunctor2Base(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

template <class CallArgT, class ArgsT, class SizeTraitsT> inline
void TypedVoidFunctor2Base<CallArgT, 
                           ArgsT, 
                           SizeTraitsT>::call(CallArgType, Arg1Type)
{
    FWARNING(("TypedFunctor2Base::call called, undefined behaviour "
              "might be the consequence\n"));
}

template <class CallArgT, class ArgsT, class SizeTraitsT> inline
void TypedVoidFunctor2Base<CallArgT,
                           ArgsT, 
                           SizeTraitsT>::operator =(
    const TypedVoidFunctor2Base &source)
{
    if(this != &source)
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
          class ArgsT,
          class SizeTraitsT> inline
TypedFunctionFunctor2<RetT, 
                      CallArgT,
                      ArgsT,
                      SizeTraitsT>::TypedFunctionFunctor2(void)  :
    Inherited()
{
}

/** \brief Copy Constructor
 */


template <class RetT, 
          class CallArgT, 
          class ArgsT,
          class SizeTraitsT> inline
TypedFunctionFunctor2<RetT,
                      CallArgT,
                      ArgsT,
                      SizeTraitsT>::TypedFunctionFunctor2(
    const TypedFunctionFunctor2 &source) : 

    Inherited(source) 
{
}
    

/** \brief Destructor
 */


template <class RetT, 
          class CallArgT, 
          class ArgsT,
          class SizeTraitsT> inline
TypedFunctionFunctor2<RetT,
                      CallArgT,
                      ArgsT,
                      SizeTraitsT>::~TypedFunctionFunctor2(void) 
{
}

/*-------------------------- your_category---------------------------------*/

#ifdef __sgi
#pragma set woff 1551 
#endif

template <class RetT, 
          class CallArgT, 
          class ArgsT,
          class SizeTraitsT> inline
RetT TypedFunctionFunctor2<RetT, 
                           CallArgT,
                           ArgsT,
                           SizeTraitsT>::call(CallArgType obj,
                                              Arg1        oArg1) 
{ 
    RetT returnValue;

    if(_flags & FuncPtrValid)
    {
        FunctionF pFunc = *((FunctionF *) _data2);
        
        return pFunc(obj, oArg1);
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
          class ArgsT,
          class SizeTraitsT> inline
TypedFunctionVoidFunctor2<CallArgT,
                          ArgsT,
                          SizeTraitsT>::TypedFunctionVoidFunctor2(void)  :
    Inherited()
{
}

/** \brief Copy Constructor
 */


template <class CallArgT, 
          class ArgsT,
          class SizeTraitsT> inline
TypedFunctionVoidFunctor2<CallArgT,
                          ArgsT,
                          SizeTraitsT>::TypedFunctionVoidFunctor2(
    const TypedFunctionVoidFunctor2 &source) : 

    Inherited(source) 
{
}
    

/** \brief Destructor
 */


template <class CallArgT, 
          class ArgsT,
          class SizeTraitsT> inline
TypedFunctionVoidFunctor2<CallArgT,
                          ArgsT,
                          SizeTraitsT>::~TypedFunctionVoidFunctor2(void) 
{
}

/*-------------------------- your_category---------------------------------*/

template <class CallArgT, 
          class ArgsT,
          class SizeTraitsT> inline
void TypedFunctionVoidFunctor2<CallArgT,
                               ArgsT,
                               SizeTraitsT>::call(CallArgType obj,
                                                  Arg1        oArg1) 
{ 
    if(_flags & FuncPtrValid)
    {
        FunctionF pFunc = *((FunctionF *) _data2);
        
        pFunc(obj, oArg1);
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
          class ArgsT,
          class SizeTraitsT> inline
TypedObjectFunctor2<RetT, 
                    CallArgT,
                    ArgsT,
                    SizeTraitsT>::TypedObjectFunctor2(void)  :
    Inherited()
{
}

/** \brief Copy Constructor
 */


template <class RetT, 
          class CallArgT, 
          class ArgsT,
          class SizeTraitsT> inline
TypedObjectFunctor2<RetT,
                    CallArgT,
                    ArgsT,
                    SizeTraitsT>::TypedObjectFunctor2(
    const TypedObjectFunctor2 &source) : 

    Inherited(source) 
{
}
    

/** \brief Destructor
 */


template <class RetT, 
          class CallArgT, 
          class ArgsT,
          class SizeTraitsT> inline
TypedObjectFunctor2<RetT,
                    CallArgT,
                    ArgsT,
                    SizeTraitsT>::~TypedObjectFunctor2(void) 
{
}

/*-------------------------- your_category---------------------------------*/

#ifdef __sgi
#pragma set woff 1551 
#endif

template <class RetT, 
          class CallArgT, 
          class ArgsT,
          class SizeTraitsT> inline
RetT TypedObjectFunctor2<RetT, 
                         CallArgT,
                         ArgsT,
                         SizeTraitsT>::call(CallArgType obj,
                                            Arg1        oArg1) 
{ 
    RetT returnValue;

    if(_flags & FuncPtrValid)
    {
        return TypeTraits::callObjectMethod(_data2, obj, oArg1);
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
          class ArgsT,
          class SizeTraitsT> inline
TypedObjectVoidFunctor2<CallArgT,
                        ArgsT,
                        SizeTraitsT>::TypedObjectVoidFunctor2(void)  :
    Inherited()
{
}

/** \brief Copy Constructor
 */


template <class CallArgT, 
          class ArgsT,
          class SizeTraitsT> inline
TypedObjectVoidFunctor2<CallArgT,
                        ArgsT,
                        SizeTraitsT>::TypedObjectVoidFunctor2(
    const TypedObjectVoidFunctor2 &source) : 

    Inherited(source) 
{
}
    

/** \brief Destructor
 */


template <class CallArgT, 
          class ArgsT,
          class SizeTraitsT> inline
TypedObjectVoidFunctor2<CallArgT,
                        ArgsT,
                        SizeTraitsT>::~TypedObjectVoidFunctor2(void) 
{
}


/*-------------------------- your_category---------------------------------*/

template <class CallArgT, 
          class ArgsT,
          class SizeTraitsT> inline
void TypedObjectVoidFunctor2<CallArgT,
                             ArgsT,
                             SizeTraitsT>::call(CallArgType obj,
                                                Arg1        oArg1) 
{ 
    if(_flags & FuncPtrValid)
    {
        TypeTraits::callObjectMethodVoid(_data2, obj, oArg1);
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
          class ArgObjectT, 
          class ArgsT,
          class SizeTraitsT> inline
TypedStoredObjectFunctor2<RetT, 
                          StoredObjectT,
                          ArgObjectT,
                          ArgsT,
                          SizeTraitsT>::TypedStoredObjectFunctor2(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */


template <class RetT, 
          class StoredObjectT,
          class ArgObjectT, 
          class ArgsT,
          class SizeTraitsT> inline
TypedStoredObjectFunctor2<RetT,
                          StoredObjectT,
                          ArgObjectT,
                          ArgsT,
                          SizeTraitsT>::TypedStoredObjectFunctor2(
    const TypedStoredObjectFunctor2 &source) : 

    Inherited(source) 
{
}
    

/** \brief Destructor
 */


template <class RetT, 
          class StoredObjectT,
          class ArgObjectT, 
          class ArgsT,
          class SizeTraitsT> inline
TypedStoredObjectFunctor2<RetT,
                          StoredObjectT,
                          ArgObjectT,
                          ArgsT, 
                          SizeTraitsT>::~TypedStoredObjectFunctor2(void) 
{
}

/*-------------------------- your_category---------------------------------*/

#ifdef __sgi
#pragma set woff 1551 
#endif

template <class RetT, 
          class StoredObjectT,
          class ArgObjectT, 
          class ArgsT,
          class SizeTraitsT> inline
RetT TypedStoredObjectFunctor2<RetT, 
                               StoredObjectT,
                               ArgObjectT,
                               ArgsT,
                               SizeTraitsT>::call(CallArgType obj,
                                                  Arg1        oArg1) 
{ 
    RetT returnValue;

    if(_flags & FuncPtrValid &&
       _flags & ObjectValid)
    {
        return TypeSOTraits::callObjectMethod(_data1, 
                                              _data2, 
                                               obj,
                                               oArg1);
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
          class ArgObjectT,
          class ArgsT,
          class SizeTraitsT> inline
TypedStoredObjectVoidFunctor2<StoredObjectT,
                              ArgObjectT,
                              ArgsT,
                              SizeTraitsT>::TypedStoredObjectVoidFunctor2(
                                  void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */


template <class StoredObjectT, 
          class ArgObjectT,
          class ArgsT,
          class SizeTraitsT> inline
TypedStoredObjectVoidFunctor2<StoredObjectT,
                              ArgObjectT,
                              ArgsT,
                              SizeTraitsT>::TypedStoredObjectVoidFunctor2(
    const TypedStoredObjectVoidFunctor2 &source) : 

    Inherited(source) 
{
}
    

/** \brief Destructor
 */


template <class StoredObjectT, 
          class ArgObjectT,
          class ArgsT,
          class SizeTraitsT> inline
TypedStoredObjectVoidFunctor2<StoredObjectT,
                              ArgObjectT,
                              ArgsT,
                              SizeTraitsT>::~TypedStoredObjectVoidFunctor2(
    void) 
{
}

/*-------------------------- your_category---------------------------------*/

template <class StoredObjectT, 
          class ArgObjectT,
          class ArgsT,
          class SizeTraitsT> inline
void TypedStoredObjectVoidFunctor2<StoredObjectT,
                                   ArgObjectT,
                                   ArgsT,
                                   SizeTraitsT>::call(CallArgType obj,
                                                      Arg1        oArg1) 
{ 
    if(_flags & FuncPtrValid &&
       _flags & ObjectValid)
    {
        TypeSOTraits::callObjectMethodVoid(_data1, 
                                           _data2, 
                                            obj,
                                            oArg1);
    }
}

OSG_END_NAMESPACE





