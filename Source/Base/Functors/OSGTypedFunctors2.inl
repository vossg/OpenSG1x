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
//  TypedFunctor2Base
//---------------------------------------------------------------------------


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
    Self::postCopyConstruct(source);
}


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


#ifdef __sgi
#pragma set woff 1551 
#endif

#if defined(OSG_WIN32_CL_NET70) 
#pragma warning (disable : 4700)
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
    FWARNING(("TypedFunctor2Base::call called, undefined behaviour "
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




//---------------------------------------------------------------------------
//  TypedVoidFunctor2Base
//---------------------------------------------------------------------------


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
    Self::postCopyConstruct(source);
}


template <class CallArgT, class ArgsT, class SizeTraitsT> inline
TypedVoidFunctor2Base<CallArgT,
                      ArgsT, 
                      SizeTraitsT>::~TypedVoidFunctor2Base(void)
{
}


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




//---------------------------------------------------------------------------
//  TypedFunctionFunctor2
//---------------------------------------------------------------------------


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
    typedef typename Self::FunctionF FuncF;

    if(Self::_flags & Self::FuncPtrValid)
    {
        FuncF pFunc = *((FuncF *) Self::_data2);
        
        return pFunc(obj, oArg1);
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
//  TypedFunctionVoidFunctor2
//---------------------------------------------------------------------------


template <class CallArgT, 
          class ArgsT,
          class SizeTraitsT> inline
TypedFunctionVoidFunctor2<CallArgT,
                          ArgsT,
                          SizeTraitsT>::TypedFunctionVoidFunctor2(void)  :
    Inherited()
{
}


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


template <class CallArgT, 
          class ArgsT,
          class SizeTraitsT> inline
TypedFunctionVoidFunctor2<CallArgT,
                          ArgsT,
                          SizeTraitsT>::~TypedFunctionVoidFunctor2(void) 
{
}


template <class CallArgT, 
          class ArgsT,
          class SizeTraitsT> inline
void TypedFunctionVoidFunctor2<CallArgT,
                               ArgsT,
                               SizeTraitsT>::call(CallArgType obj,
                                                  Arg1        oArg1) 
{ 
    typedef typename Self::FunctionF FuncF;

    if(Self::_flags & Self::FuncPtrValid)
    {
        FuncF pFunc = *((FuncF *) Self::_data2);
        
        pFunc(obj, oArg1);
    }
}




//---------------------------------------------------------------------------
//  TypedObjectFunctor2
//---------------------------------------------------------------------------


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
    if(Self::_flags & Self::FuncPtrValid)
    {
        return TypeTraits::callObjectMethod(Self::_data2, obj, oArg1);
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
//  TypedObjectVoidFunctor2
//---------------------------------------------------------------------------


template <class CallArgT, 
          class ArgsT,
          class SizeTraitsT> inline
TypedObjectVoidFunctor2<CallArgT,
                        ArgsT,
                        SizeTraitsT>::TypedObjectVoidFunctor2(void)  :
    Inherited()
{
}


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


template <class CallArgT, 
          class ArgsT,
          class SizeTraitsT> inline
TypedObjectVoidFunctor2<CallArgT,
                        ArgsT,
                        SizeTraitsT>::~TypedObjectVoidFunctor2(void) 
{
}


template <class CallArgT, 
          class ArgsT,
          class SizeTraitsT> inline
void TypedObjectVoidFunctor2<CallArgT,
                             ArgsT,
                             SizeTraitsT>::call(CallArgType obj,
                                                Arg1        oArg1) 
{ 
    if(Self::_flags & Self::FuncPtrValid)
    {
        TypeTraits::callObjectMethodVoid(Self::_data2, obj, oArg1);
    }
}




//---------------------------------------------------------------------------
//  TypedStoredObjectFunctor2
//---------------------------------------------------------------------------


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
    if(Self::_flags & Self::FuncPtrValid &&
       Self::_flags & Self::ObjectValid)
    {
        return TypeSOTraits::callObjectMethod(Self::_data1, 
                                              Self::_data2, 
                                               obj,
                                               oArg1);
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
//  TypedStoredObjectVoidFunctor2
//---------------------------------------------------------------------------


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
    if(Self::_flags & Self::FuncPtrValid &&
       Self::_flags & Self::ObjectValid)
    {
        TypeSOTraits::callObjectMethodVoid(Self::_data1, 
                                           Self::_data2, 
                                           obj,
                                           oArg1);
    }
}

OSG_END_NAMESPACE





