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
//  TypedFunctor1Base
//---------------------------------------------------------------------------


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
    Self::postCopyConstruct(source);
}


template <class RetT,
          class CallArgT,
          class SizeTraitsT> inline
TypedFunctor1Base<RetT, 
                  CallArgT,
                  SizeTraitsT>::~TypedFunctor1Base(void)
{
}


#ifdef __sgi
#pragma set woff 1551 
#endif

#if defined(OSG_WIN32_CL_NET70) 
#pragma warning (disable : 4700)
#endif

template <class RetT,
          class CallArgT,
          class SizeTraitsT> inline
RetT TypedFunctor1Base<RetT, 
                       CallArgT,
                       SizeTraitsT>::call(CallArgType)
{
    FWARNING(("TypedFunctor1Base::call called, undefined behaviour "
                 "might be the consequence\n"));

    return RetT();
}

#if defined(OSG_WIN32_CL_NET70) 
#pragma warning (default : 4700)
#endif

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




//---------------------------------------------------------------------------
//  TypedVoidFunctor1Base
//---------------------------------------------------------------------------


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
    Self::postCopyConstruct(source);
}


template <class CallArgT, class SizeTraitsT> inline
TypedVoidFunctor1Base<CallArgT, 
                      SizeTraitsT>::~TypedVoidFunctor1Base(void)
{
}


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




//---------------------------------------------------------------------------
//  TypedFunctionFunctor1
//---------------------------------------------------------------------------


template <class RetT, 
          class CallArgT, 
          class SizeTraitsT> inline
TypedFunctionFunctor1<RetT, 
                      CallArgT,
                      SizeTraitsT>::TypedFunctionFunctor1(void)  :
    Inherited()
{
}


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
    

template <class RetT, 
          class CallArgT, 
          class SizeTraitsT> inline
TypedFunctionFunctor1<RetT,
                      CallArgT,
                      SizeTraitsT>::~TypedFunctionFunctor1(void) 
{
}


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
    typedef typename Self::FunctionF FuncF;

    if(Self::_flags & Self::FuncPtrValid)
    {
        FuncF pFunc = *((FuncF *) Self::_data2);
        
        return pFunc(pObj);
    }
	else
	{
		return RetT();
	}
}

#ifdef __sgi
#pragma reset woff 1551 
#endif




//---------------------------------------------------------------------------
//  TypedFunctionVoidFunctor1
//---------------------------------------------------------------------------


template <class CallArgT, 
          class SizeTraitsT> inline
TypedFunctionVoidFunctor1<CallArgT,
                          SizeTraitsT>::TypedFunctionVoidFunctor1(void)  :
    Inherited()
{
}


template <class CallArgT, 
          class SizeTraitsT> inline
TypedFunctionVoidFunctor1<CallArgT,
                          SizeTraitsT>::TypedFunctionVoidFunctor1(
                              const TypedFunctionVoidFunctor1 &source) : 

    Inherited(source) 
{
}
    

template <class CallArgT, 
          class SizeTraitsT> inline
TypedFunctionVoidFunctor1<CallArgT,
                          SizeTraitsT>::~TypedFunctionVoidFunctor1(void) 
{
}


template <class CallArgT, 
          class SizeTraitsT> inline
void TypedFunctionVoidFunctor1<CallArgT,
                               SizeTraitsT>::call(CallArgType pObj) 
{ 
    typedef typename Self::FunctionF FuncF;

    if(Self::_flags & Self::FuncPtrValid)
    {
        FuncF pFunc = *((FuncF *) Self::_data2);
        
        pFunc(pObj);
    }
}




//---------------------------------------------------------------------------
//  TypedObjectFunctor1
//---------------------------------------------------------------------------


template <class RetT, 
          class CallArgT, 
          class SizeTraitsT> inline
TypedObjectFunctor1<RetT, 
                    CallArgT,
                    SizeTraitsT>::TypedObjectFunctor1(void)  :
    Inherited()
{
}


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


template <class RetT, 
          class CallArgT, 
          class SizeTraitsT> inline
TypedObjectFunctor1<RetT,
                    CallArgT,
                    SizeTraitsT>::~TypedObjectFunctor1(void) 
{
}


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
    if(Self::_flags & Self::FuncPtrValid)
    {
        return TypeTraits::callObjectMethod(Self::_data2, obj);
    }
	else
	{
		return RetT();
	}
}

#ifdef __sgi
#pragma reset woff 1551 
#endif




//---------------------------------------------------------------------------
//  TypedObjectVoidFunctor1
//---------------------------------------------------------------------------


template <class CallArgT, 
          class SizeTraitsT> inline
TypedObjectVoidFunctor1<CallArgT,
                        SizeTraitsT>::TypedObjectVoidFunctor1(void)  :
    Inherited()
{
}


template <class CallArgT, 
          class SizeTraitsT> inline
TypedObjectVoidFunctor1<CallArgT,
                        SizeTraitsT>::TypedObjectVoidFunctor1(
    const TypedObjectVoidFunctor1 &source) : 

    Inherited(source) 
{
}
    

template <class CallArgT, 
          class SizeTraitsT> inline
TypedObjectVoidFunctor1<CallArgT,
                        SizeTraitsT>::~TypedObjectVoidFunctor1(void) 
{
}


template <class CallArgT, 
          class SizeTraitsT> inline
void TypedObjectVoidFunctor1<CallArgT,
                             SizeTraitsT>::call(CallArgType obj) 
{ 
    if(Self::_flags & Self::FuncPtrValid)
    {
        TypeTraits::callObjectMethodVoid(Self::_data2, obj);
    }
}




//---------------------------------------------------------------------------
//  TypedStoredObjectFunctor1
//---------------------------------------------------------------------------


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
    if(Self::_flags & Self::FuncPtrValid &&
       Self::_flags & Self::ObjectValid)
    {
        return TypeTraits::callObjectMethod(Self::_data1, Self::_data2, obj);
    }
	else
	{
		return RetT();
	}
}

#ifdef __sgi
#pragma reset woff 1551 
#endif




//---------------------------------------------------------------------------
//  TypedStoredObjectVoidFunctor1
//---------------------------------------------------------------------------


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


template <class StoredObjectT, 
          class ArgsT,
          class SizeTraitsT> inline
TypedStoredObjectVoidFunctor1<StoredObjectT,
                              ArgsT,
                              SizeTraitsT>::~TypedStoredObjectVoidFunctor1(
    void) 
{
}


template <class StoredObjectT, 
          class ArgsT,
          class SizeTraitsT> inline
void TypedStoredObjectVoidFunctor1<StoredObjectT,
                                   ArgsT,
                                   SizeTraitsT>::call(CallArgType obj) 
{ 
    if(Self::_flags & Self::FuncPtrValid &&
       Self::_flags & Self::ObjectValid)
    {
        TypeTraits::callObjectMethodVoid(Self::_data1, Self::_data2, obj);
    }
}

OSG_END_NAMESPACE






