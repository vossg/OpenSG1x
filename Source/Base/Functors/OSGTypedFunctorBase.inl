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
//  TypedFunctorBase
//---------------------------------------------------------------------------


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


template <class SizeTraitsT> inline
TypedFunctorBase<SizeTraitsT>::~TypedFunctorBase(void)
{
}


template <class SizeTraitsT> inline
void TypedFunctorBase<SizeTraitsT>::operator =(const TypedFunctorBase &source)
{
    if(this != &source)
    {
        memcpy(this, &source, 
               sizeof(TypedFunctorBase<SizeTraitsT>)); 
    }
}


template <class SizeTraitsT> inline
void TypedFunctorBase<SizeTraitsT>::postCopyConstruct(
    const TypedFunctorBase &source)
{
    memcpy(this, &source, 
           sizeof(TypedFunctorBase<SizeTraitsT>)); 
}




//---------------------------------------------------------------------------
//  TypedFunctionFunctorBase
//---------------------------------------------------------------------------


template <class Parent, class Params> inline
TypedFunctionFunctorBase<Parent, Params>::TypedFunctionFunctorBase(void)  :
    Inherited()
{
}


template <class Parent, class Params> inline
TypedFunctionFunctorBase<Parent, Params>::TypedFunctionFunctorBase(
    const TypedFunctionFunctorBase &source) : 

    Inherited(source) 
{
}
    

template <class Parent, class Params> inline
TypedFunctionFunctorBase<Parent, Params>::~TypedFunctionFunctorBase(void) 
{
}


template <class Parent, class Params> inline
void TypedFunctionFunctorBase<Parent, Params>::setMethod(FunctionF pFunc)
{
    Self::_flags |=  Self::FuncPtrValid;

    *((FunctionF *) Self::_data2) = pFunc; 
}




//---------------------------------------------------------------------------
//  TypedObjectFunctorBase
//---------------------------------------------------------------------------


template <class Parent, class Params> inline
TypedObjectFunctorBase<Parent, Params>::TypedObjectFunctorBase(void)  :
    Inherited()
{
}


template <class Parent, class Params> inline
TypedObjectFunctorBase<Parent, Params>::TypedObjectFunctorBase(
    const TypedObjectFunctorBase &source) : 

    Inherited(source) 
{
}
    

template <class Parent, class Params> inline
TypedObjectFunctorBase<Parent, Params>::~TypedObjectFunctorBase(void) 
{
}


template <class Parent, class Params> inline
void TypedObjectFunctorBase<Parent, Params>::setMethod(ObjMethodF pFunc)
{
    Self::_flags |=  Self::FuncPtrValid;

    *((ObjMethodF *) Self::_data2) = pFunc; 
}




//---------------------------------------------------------------------------
//  TypedStoredObjectFunctorBase
//---------------------------------------------------------------------------


template <class Parent, class Params> inline
TypedStoredObjectFunctorBase<Parent, Params>::TypedStoredObjectFunctorBase(
    void) :

    Inherited()
{
}


template <class Parent, class Params> inline
TypedStoredObjectFunctorBase<Parent, Params>::TypedStoredObjectFunctorBase(
    const TypedStoredObjectFunctorBase &source) : 

    Inherited(source) 
{
}
    

template <class Parent, class Params> inline
TypedStoredObjectFunctorBase<Parent, Params>::~TypedStoredObjectFunctorBase(
                                   void) 
{
}


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

