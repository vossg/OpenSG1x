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

template <class SizeTraitsT>
char FunctorBase<SizeTraitsT>::cvsid[] = "@(#)$Id: $";

template <class SizeTraitsT>
const UInt8 FunctorBase<SizeTraitsT>::ObjectValid  = 0x01;

template <class SizeTraitsT>
const UInt8 FunctorBase<SizeTraitsT>::FuncPtrValid = 0x02;

template <class SizeTraitsT>
const UInt8 FunctorBase<SizeTraitsT>::FunctorActive = 0x80;

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

/** \brief Constructor
 */

template <class SizeTraitsT> inline
FunctorBase<SizeTraitsT>::FunctorBase(void) :
    _flags(0)
{
}

/** \brief Copy Constructor
 */

template <class SizeTraitsT> inline
FunctorBase<SizeTraitsT>::FunctorBase(const FunctorBase &) 
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Destructor
 */

template <class SizeTraitsT> inline
FunctorBase<SizeTraitsT>::~FunctorBase(void) 
{
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

template <class RetT, class Arg1T, class SizeTraitsT>
char Functor1Base<RetT, Arg1T, SizeTraitsT>::cvsid[] = "@(#)$Id: $";

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

template <class RetT, class Arg1T, class SizeTraitsT> inline
Functor1Base<RetT, Arg1T, SizeTraitsT>::Functor1Base(void) : 
    Inherited()
{
}

template <class RetT, class Arg1T, class SizeTraitsT> inline
Functor1Base<RetT, Arg1T, SizeTraitsT>::Functor1Base(
    const Functor1Base &source) :

    Inherited()
{
    memcpy(this, &source, 
           sizeof(Functor1Base<RetT, Arg1T, SizeTraitsT>)); 
}


/** \brief Destructor
 */

template <class RetT, class Arg1T, class SizeTraitsT> inline
Functor1Base<RetT, Arg1T, SizeTraitsT>::~Functor1Base(void) 
{
}


/*-------------------------- your_category---------------------------------*/

// turn of returnValue used before set warning

#ifdef __sgi
#pragma set woff 1551 
#endif

template <class RetT, class Arg1T, class SizeTraitsT> inline
RetT Functor1Base<RetT, Arg1T, SizeTraitsT>::call(Arg1T) 
{ 
    RetT returnValue;

    FWARNING(("Functor1Base::call called, undefined behaviour might " 
              "be the consequence\n"));

    return returnValue;
}

#ifdef __sgi
#pragma reset woff 1551 
#endif

/*-------------------------- assignment -----------------------------------*/

template <class RetT, class Arg1T, class SizeTraitsT> inline
void Functor1Base<RetT, Arg1T, SizeTraitsT>::operator =(
    const Functor1Base &source) 
{
    if(this != &source)
    {
        memcpy(this, &source, 
               sizeof(Functor1Base<RetT, Arg1T, SizeTraitsT>)); 
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

template <class Arg1T, class SizeTraitsT>
char Functor1Base<void, Arg1T, SizeTraitsT>::cvsid[] = 
    "@(#)$Id: $";

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

template <class Arg1T, class SizeTraitsT> inline
Functor1Base<void, Arg1T, SizeTraitsT>::Functor1Base(void) : 
    Inherited()
{
}

template <class Arg1T, class SizeTraitsT> inline
Functor1Base<void, Arg1T, SizeTraitsT>::Functor1Base(
    const Functor1Base &source) :

    Inherited()
{
    memcpy(this, &source, 
           sizeof(Functor1Base<void, Arg1T, SizeTraitsT>)); 
}


/** \brief Destructor
 */

template <class Arg1T, class SizeTraitsT> inline
Functor1Base<void, Arg1T, SizeTraitsT>::~Functor1Base(void) 
{
}


/*-------------------------- your_category---------------------------------*/

// turn of returnValue used before set warning

#ifdef __sgi
#pragma set woff 1551 
#endif

template <class Arg1T, class SizeTraitsT> inline
void Functor1Base<void, Arg1T, SizeTraitsT>::call(Arg1T) 
{ 
    FWARNING(("Functor1Base::call called, undefined behaviour might " 
              "be the consequence\n"));
}

#ifdef __sgi
#pragma reset woff 1551 
#endif

/*-------------------------- assignment -----------------------------------*/

template <class Arg1T, class SizeTraitsT> inline
void Functor1Base<void, Arg1T, SizeTraitsT>::operator =(
    const Functor1Base &source) 
{
    if(this != &source)
    {
        memcpy(this, &source, 
               sizeof(Functor1Base<void, Arg1T, SizeTraitsT>)); 
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

template <class RetT, class Arg1T, class SizeTraitsT>
char FunctionFunctor1<RetT, Arg1T, SizeTraitsT>::cvsid[] = 
    "@(#)$Id: $";

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

template <class RetT, class Arg1T, class SizeTraitsT> inline
FunctionFunctor1<RetT, Arg1T, SizeTraitsT>::FunctionFunctor1(
    void) :

    Inherited()
{
}

/** \brief Copy Constructor
 */

template <class RetT, class Arg1T, class SizeTraitsT> inline
FunctionFunctor1<RetT, Arg1T, SizeTraitsT>::FunctionFunctor1(
    const FunctionFunctor1 &source) : 
    
    Inherited(source) 
{
}
    
/** \brief Destructor
 */

template <class RetT, class Arg1T, class SizeTraitsT> inline
FunctionFunctor1<RetT, Arg1T, SizeTraitsT>::~FunctionFunctor1(
    void)
{
}

/*------------------------------ access -----------------------------------*/

template <class RetT, class Arg1T, class SizeTraitsT> inline
void FunctionFunctor1<RetT, Arg1T, SizeTraitsT>::setFunction(
    FunctionP pFunc)
{
    *((FunctionP *) _data2) = pFunc;
}

/*-------------------------- your_category---------------------------------*/

template <class RetT, class Arg1T, class SizeTraitsT> inline
RetT FunctionFunctor1<RetT, Arg1T, SizeTraitsT>::call(
    Arg1T arg1)
{
    FunctionP pFunc = *((FunctionP *) _data2);

    return pFunc(arg1);
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

template <class Arg1T, class SizeTraitsT>
char FunctionFunctor1<void, Arg1T, SizeTraitsT>::cvsid[] = 
    "@(#)$Id: $";

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

template <class Arg1T, class SizeTraitsT> inline
FunctionFunctor1<void, Arg1T, SizeTraitsT>::FunctionFunctor1(
    void) :

    Inherited()
{
}

/** \brief Copy Constructor
 */

template <class Arg1T, class SizeTraitsT> inline
FunctionFunctor1<void, Arg1T, SizeTraitsT>::FunctionFunctor1(
    const FunctionFunctor1 &source) : 
    
    Inherited(source) 
{
}
    
/** \brief Destructor
 */

template <class Arg1T, class SizeTraitsT> inline
FunctionFunctor1<void, Arg1T, SizeTraitsT>::~FunctionFunctor1(
    void)
{
}

/*------------------------------ access -----------------------------------*/

template <class Arg1T, class SizeTraitsT> inline
void FunctionFunctor1<void, Arg1T, SizeTraitsT>::setFunction(
    FunctionP pFunc)
{
    *((FunctionP *) _data2) = pFunc;
}

/*-------------------------- your_category---------------------------------*/

template <class Arg1T, class SizeTraitsT> inline
void FunctionFunctor1<void, Arg1T, SizeTraitsT>::call(
    Arg1T arg1)
{
    FunctionP pFunc = *((FunctionP *) _data2);

    pFunc(arg1);
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

template <class RetT, 
          class Arg1T, 
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT>
char ObjectFunctor1<RetT,    Arg1T,
                       ObjectT, MethodCallType,
                       SizeTraitsT>::cvsid[] = "@(#)$Id: $";

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
          class Arg1T, 
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
ObjectFunctor1<RetT, 
                  Arg1T,
                  ObjectT,
                  MethodCallType,
                  SizeTraitsT>::ObjectFunctor1(void)  :
    Inherited()
{
}

/** \brief Copy Constructor
 */


template <class RetT, 
          class Arg1T, 
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
ObjectFunctor1<RetT,
                  Arg1T,
                  ObjectT,
                  MethodCallType,
                  SizeTraitsT>::ObjectFunctor1(
    const ObjectFunctor1 &source) : 

    Inherited(source) 
{
}
    

/** \brief Destructor
 */


template <class RetT, 
          class Arg1T, 
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
ObjectFunctor1<RetT,
                  Arg1T,
                  ObjectT,
                  MethodCallType,
                  SizeTraitsT>::~ObjectFunctor1(void) 
{
}

/*------------------------------ access -----------------------------------*/


template <class RetT, 
          class Arg1T, 
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
void ObjectFunctor1<RetT, 
                       Arg1T,
                       ObjectT,
                       MethodCallType,
                       SizeTraitsT>::setMethod(ObjectMethodT pFunc)
{
    _flags |= FuncPtrValid;

    *((ObjectMethodT *) _data2) = pFunc; 
}


template <class RetT, 
          class Arg1T, 
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
void ObjectFunctor1<RetT, 
                       Arg1T,
                       ObjectT,
                       MethodCallType,
                       SizeTraitsT>::setMethod(ObjectMethodPtrT pFunc)
{
    _flags |= FuncPtrValid;
  
    *((ObjectMethodPtrT *) _data2) = pFunc; 
}


template <class RetT, 
          class Arg1T, 
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
void ObjectFunctor1<RetT, 
                       Arg1T,
                       ObjectT,
                       MethodCallType,
                       SizeTraitsT>::setCalledObject(SetObjectT pObj)
{
    _flags |= ObjectValid;

    FunctorTrait::setCalledObject(_data1, pObj);
}


template <class RetT, 
          class Arg1T, 
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
void ObjectFunctor1<RetT, 
                       Arg1T,
                       ObjectT,
                       MethodCallType,
                       SizeTraitsT>::setObjectAndMethod(
    SetObjectT       pObj, 
    ObjectMethodPtrT pFunc)
{
    _flags |= FuncPtrValid;
    _flags |= ObjectValid;
     
    FunctorTrait::setCalledObject(_data1, pObj);
    *((ObjectMethodPtrT *) _data2) = pFunc; 
}

/*-------------------------- your_category---------------------------------*/

#ifdef __sgi
#pragma set woff 1551 
#endif

template <class RetT, 
          class Arg1T, 
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
RetT ObjectFunctor1<RetT, 
                          Arg1T,
                          ObjectT,
                          MethodCallType,
                          SizeTraitsT>::call(Arg1T arg1) 
{ 
    RetT returnValue;

    if(_flags & FuncPtrValid)
    {
        if(_flags & ObjectValid)
        {
            return FunctorTrait::callObjectMethod(_data1, _data2, arg1);
        }
        else
        {
            return FunctorTrait::callObjectMethod(_data2, arg1);
        }
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

template <class Arg1T, 
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT>
char ObjectFunctor1<void, 
                       Arg1T,
                       ObjectT,
                       MethodCallType,
                       SizeTraitsT>::cvsid[] = "@(#)$Id: $";

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

template <class Arg1T, 
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
ObjectFunctor1<void, 
                  Arg1T,
                  ObjectT,
                  MethodCallType,
                  SizeTraitsT>::ObjectFunctor1(void)  :
    Inherited()
{
}

/** \brief Copy Constructor
 */


template <class Arg1T, 
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
ObjectFunctor1<void,
                  Arg1T,
                  ObjectT,
                  MethodCallType,
                  SizeTraitsT>::ObjectFunctor1(
    const ObjectFunctor1 &source) : 

    Inherited(source) 
{
}
    

/** \brief Destructor
 */


template <class Arg1T, 
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
ObjectFunctor1<void, 
                  Arg1T,
                  ObjectT,
                  MethodCallType,
                  SizeTraitsT>::~ObjectFunctor1(void) 
{
}

/*------------------------------ access -----------------------------------*/


template <class Arg1T, 
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
void ObjectFunctor1<void, 
                       Arg1T,
                       ObjectT,
                       MethodCallType,
                       SizeTraitsT>::setMethod(
    ObjectMethodT pFunc)
{
    _flags |= FuncPtrValid;

    *((ObjectMethodT *) _data2) = pFunc; 
}


template <class Arg1T, 
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
void ObjectFunctor1<void, 
                       Arg1T,
                       ObjectT,
                       MethodCallType,
                       SizeTraitsT>::setMethod(
    ObjectMethodPtrT pFunc)
{
    _flags |= FuncPtrValid;
  
    *((ObjectMethodPtrT *) _data2) = pFunc; 
}


template <class Arg1T, 
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
void ObjectFunctor1<void, 
                       Arg1T,
                       ObjectT,
                       MethodCallType,
                       SizeTraitsT>::setCalledObject(
    SetObjectT pObj)
{
    _flags |= ObjectValid;

    FunctorTrait::setCalledObject(_data1, pObj);
}


template <class Arg1T, 
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
void ObjectFunctor1<void, 
                       Arg1T,
                       ObjectT,
                       MethodCallType,
                       SizeTraitsT>::setObjectAndMethod(
    SetObjectT       pObj, 
    ObjectMethodPtrT pFunc)
{
    _flags |= FuncPtrValid;
    _flags |= ObjectValid;
     
    FunctorTrait::setCalledObject(_data1, pObj);

    *((ObjectMethodPtrT *) _data2) = pFunc; 
}

/*-------------------------- your_category---------------------------------*/

template <class Arg1T, 
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
void ObjectFunctor1<void, 
                       Arg1T,
                       ObjectT,
                       MethodCallType,
                       SizeTraitsT>::call(Arg1T arg1) 
{ 
    if(_flags & FuncPtrValid)
    {
        if(_flags & ObjectValid)
        {
            FunctorTrait::callObjectMethodVoid(_data1, _data2, arg1);
        }
        else
        {
            FunctorTrait::callObjectMethodVoid(_data2, arg1);
        }
    }
}


template <class RetT, class Arg1T> inline
FunctionFunctor1<RetT, Arg1T> osgFunctionFunctor1( 
    RetT (*pFunc)(Arg1T)) 
{ 
    FunctionFunctor1<RetT, Arg1T> returnValue; 

    returnValue.setFunction(pFunc); 

    return returnValue; 
} 

template <class RetT, class Arg1T> inline
ObjectFunctor1<RetT, 
                  Arg1T &, 
                  Arg1T,
                  OnArgument> osgMethodFunctor1Ref(
    RetT (Arg1T::*pFunc)())
{
    typedef ObjectFunctor1<RetT, 
                              Arg1T &, 
                              Arg1T,
                              OnArgument> OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);    
    
    return returnValue;
} 


template <class RetT, class Arg1T, class ObjectT> inline
ObjectFunctor1<RetT, 
                  Arg1T, 
                  ObjectT &,
                  OnStoredObject> osgMethodFunctor1Ref(
    ObjectT &obj, RetT (ObjectT::*pFunc)(Arg1T))
{
    typedef ObjectFunctor1<RetT, 
                              Arg1T, 
                              ObjectT &,
                              OnStoredObject> OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);    
    returnValue.setCalledObject(obj);

    return returnValue;
} 



template <class RetT, class Arg1T> inline
ObjectFunctor1<RetT, 
                  Arg1T *, 
                  Arg1T,
                  OnArgument> osgMethodFunctor1Ptr(
    RetT (Arg1T::*pFunc)())
{
    typedef ObjectFunctor1<RetT, 
                              Arg1T *, 
                              Arg1T,
                              OnArgument> OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);    
    
    return returnValue;
} 


template <class RetT, class Arg1T, class ObjectT> inline
ObjectFunctor1<RetT, 
                  Arg1T, 
                  ObjectT *,
                  OnStoredObject> osgMethodFunctor1Ptr(
    ObjectT *pObj, RetT (ObjectT::*pFunc)(Arg1T))
{
    typedef ObjectFunctor1<RetT, 
                              Arg1T, 
                              ObjectT *,
                              OnStoredObject> OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);    
    returnValue.setCalledObject(pObj);

    return returnValue;
}


template <class RetT, class Arg1T> inline
ObjectFunctor1<RetT, 
                  Arg1T &, 
                  Arg1T,
                  OnCPtrArgument> osgMethodFunctor1CPtr(
   typename FunctorBuildFuncType1<RetT, Arg1T>::FunctionType pFunc)
{
    typedef ObjectFunctor1<RetT, 
                              Arg1T &, 
                              Arg1T,
                              OnCPtrArgument> OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);    
   
    return returnValue;
} 

template <class RetT, class Arg1T, class ObjectT> inline
ObjectFunctor1<RetT, 
                  Arg1T, 
                  ObjectT &,
                  OnStoredCPtr> osgMethodFunctor1CPtr(
    ObjectT &obj, 
    typename FunctorBuildFuncType2<RetT, 
                                      Arg1T, 
                                      ObjectT>::FunctionType pFunc)
{
    typedef ObjectFunctor1<RetT, 
                              Arg1T, 
                              ObjectT &,
                              OnStoredCPtr> OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);    
    returnValue.setCalledObject(obj);

    return returnValue;
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

template <class RetT, class Arg1T, class Arg2T, class SizeTraitsT>
char Functor2Base<RetT,  Arg1T, 
                     Arg2T, SizeTraitsT>::cvsid[] = "@(#)$Id: $";

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

template <class RetT,  class Arg1T, 
          class Arg2T, class SizeTraitsT> inline
Functor2Base<RetT, Arg1T, Arg2T, SizeTraitsT>::Functor2Base(
    void) : 

    Inherited()
{
}

template <class RetT,  class Arg1T,
          class Arg2T, class SizeTraitsT> inline
Functor2Base<RetT, Arg1T, Arg2T, SizeTraitsT>::Functor2Base(
    const Functor2Base &source) :

    Inherited()
{
    memcpy(this, &source, 
           sizeof(Functor2Base<RetT, Arg1T, 
                                  Arg2T, SizeTraitsT>)); 
}


/** \brief Destructor
 */

template <class RetT,  class Arg1T,
          class Arg2T, class SizeTraitsT> inline
Functor2Base<RetT, Arg1T, Arg2T, SizeTraitsT>::~Functor2Base(
    void) 
{
}


/*-------------------------- your_category---------------------------------*/

// turn of returnValue used before set warning

#ifdef __sgi
#pragma set woff 1551 
#endif

template <class RetT,  class Arg1T,
          class Arg2T, class SizeTraitsT> inline
RetT Functor2Base<RetT, Arg1T, Arg2T, SizeTraitsT>::call(
    Arg1T, Arg2T) 
{ 
    RetT returnValue;

    FWARNING(("Functor2Base::call called, undefined behaviour might " 
              "be the consequence\n"));

    return returnValue;
}

#ifdef __sgi
#pragma reset woff 1551 
#endif

/*-------------------------- assignment -----------------------------------*/

template <class RetT,  class Arg1T,
          class Arg2T, class SizeTraitsT> inline
void Functor2Base<RetT, Arg1T, Arg2T, SizeTraitsT>::operator =(
    const Functor2Base &source) 
{
    if(this != &source)
    {
        memcpy(this, &source, 
               sizeof(Functor2Base<RetT,  Arg1T, 
                                      Arg2T, SizeTraitsT>)); 
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

template <class Arg1T, class Arg2T, class SizeTraitsT>
char Functor2Base<void, Arg1T, Arg2T, SizeTraitsT>::cvsid[] = 
    "@(#)$Id: $";

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

template <class Arg1T, class Arg2T, class SizeTraitsT> inline
Functor2Base<void, Arg1T, Arg2T, SizeTraitsT>::Functor2Base(
    void) : 

    Inherited()
{
}

template <class Arg1T, class Arg2T, class SizeTraitsT> inline
Functor2Base<void, Arg1T, Arg2T, SizeTraitsT>::Functor2Base(
    const Functor2Base &source) :

    Inherited()
{
    memcpy(this, &source, 
           sizeof(Functor2Base<void, Arg1T, Arg2T, SizeTraitsT>)); 
}


/** \brief Destructor
 */

template <class Arg1T, class Arg2T, class SizeTraitsT> inline
Functor2Base<void, Arg1T, Arg2T, SizeTraitsT>::~Functor2Base(
    void) 
{
}


/*-------------------------- your_category---------------------------------*/

// turn of returnValue used before set warning

#ifdef __sgi
#pragma set woff 1551 
#endif

template <class Arg1T, class Arg2T, class SizeTraitsT> inline
void Functor2Base<void, Arg1T, Arg2T, SizeTraitsT>::call(
    Arg1T, Arg2T) 
{ 
    FWARNING(("Functor2Base::call called, undefined behaviour might " 
              "be the consequence\n"));
}

#ifdef __sgi
#pragma reset woff 1551 
#endif

/*-------------------------- assignment -----------------------------------*/

template <class Arg1T, class Arg2T, class SizeTraitsT> inline
void Functor2Base<void, Arg1T, Arg2T, SizeTraitsT>::operator =(
    const Functor2Base &source) 
{
    if(this != &source)
    {
        memcpy(this, &source, 
               sizeof(Functor2Base<void,     Arg1T, 
                                      Arg2T, SizeTraitsT>)); 
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

template <class RetT,  class Arg1T,
          class Arg2T, class SizeTraitsT>
char FunctionFunctor2<RetT, Arg1T, Arg2T, SizeTraitsT>::cvsid[]=
    "@(#)$Id: $";

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

template <class RetT,  class Arg1T, 
          class Arg2T, class SizeTraitsT> inline
FunctionFunctor2<RetT,  Arg1T, 
                    Arg2T, SizeTraitsT>::FunctionFunctor2(void) :

    Inherited()
{
}

/** \brief Copy Constructor
 */

template <class RetT,  class Arg1T,
          class Arg2T, class SizeTraitsT> inline
FunctionFunctor2<RetT,  Arg1T, 
                    Arg2T, SizeTraitsT>::FunctionFunctor2(
    const FunctionFunctor2 &source) : 
    
    Inherited(source) 
{
}
    
/** \brief Destructor
 */

template <class RetT,  class Arg1T,
          class Arg2T, class SizeTraitsT> inline
FunctionFunctor2<RetT, Arg1T, 
                    Arg2T, SizeTraitsT>::~FunctionFunctor2(void)
{
}

/*------------------------------ access -----------------------------------*/

template <class RetT,  class Arg1T,
          class Arg2T, class SizeTraitsT> inline
void FunctionFunctor2<RetT,  Arg1T, 
                         Arg2T, SizeTraitsT>::setFunction(
    FunctionP pFunc)
{
    *((FunctionP *) _data2) = pFunc;
}

/*-------------------------- your_category---------------------------------*/

template <class RetT,  class Arg1T,
          class Arg2T, class SizeTraitsT> inline
RetT FunctionFunctor2<RetT, Arg1T, Arg2T, SizeTraitsT>::call(
    Arg1T arg1, Arg2T arg2)
{
    FunctionP pFunc = *((FunctionP *) _data2);

    return pFunc(arg1, arg2);
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

template <class Arg1T, class Arg2T, class SizeTraitsT>
char FunctionFunctor2<void, Arg1T, Arg2T, SizeTraitsT>::cvsid[] = 
    "@(#)$Id: $";

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

template <class Arg1T, class Arg2T, class SizeTraitsT> inline
FunctionFunctor2<void,     Arg1T, 
                    Arg2T, SizeTraitsT>::FunctionFunctor2(void) :

    Inherited()
{
}

/** \brief Copy Constructor
 */

template <class Arg1T, class Arg2T, class SizeTraitsT> inline
FunctionFunctor2<void,     Arg1T, 
                    Arg2T, SizeTraitsT>::FunctionFunctor2(
    const FunctionFunctor2 &source) : 
    
    Inherited(source) 
{
}
    
/** \brief Destructor
 */

template <class Arg1T, class Arg2T, class SizeTraitsT> inline
FunctionFunctor2<void,     Arg1T, 
                    Arg2T, SizeTraitsT>::~FunctionFunctor2(
    void)
{
}

/*------------------------------ access -----------------------------------*/

template <class Arg1T, class Arg2T, class SizeTraitsT> inline
void FunctionFunctor2<void,     Arg1T, 
                         Arg2T, SizeTraitsT>::setFunction(
    FunctionP pFunc)
{
    *((FunctionP *) _data2) = pFunc;
}

/*-------------------------- your_category---------------------------------*/

template <class Arg1T, class Arg2T, class SizeTraitsT> inline
void FunctionFunctor2<void, Arg1T, Arg2T, SizeTraitsT>::call(
    Arg1T arg1, Arg2T arg2)
{
    FunctionP pFunc = *((FunctionP *) _data2);

    pFunc(arg1, arg2);
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

template <class RetT, 
          class Arg1T, 
          class Arg2T,
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT>
char ObjectFunctor2<RetT,    
                       Arg1T,
                       Arg2T,
                       ObjectT, 
                       MethodCallType,
                       SizeTraitsT>::cvsid[] = "@(#)$Id: $";

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
          class Arg1T, 
          class Arg2T,
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
ObjectFunctor2<RetT, 
                  Arg1T,
                  Arg2T,
                  ObjectT,
                  MethodCallType,
                  SizeTraitsT>::ObjectFunctor2(void)  :
    Inherited()
{
}

/** \brief Copy Constructor
 */


template <class RetT, 
          class Arg1T, 
          class Arg2T, 
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
ObjectFunctor2<RetT,
                  Arg1T,
                  Arg2T,
                  ObjectT,
                  MethodCallType,
                  SizeTraitsT>::ObjectFunctor2(
    const ObjectFunctor2 &source) : 

    Inherited(source) 
{
}
    

/** \brief Destructor
 */


template <class RetT, 
          class Arg1T, 
          class Arg2T,
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
ObjectFunctor2<RetT,
                  Arg1T,
                  Arg2T,
                  ObjectT,
                  MethodCallType,
                  SizeTraitsT>::~ObjectFunctor2(void) 
{
}

/*------------------------------ access -----------------------------------*/


template <class RetT, 
          class Arg1T, 
          class Arg2T,
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
void ObjectFunctor2<RetT, 
                       Arg1T,
                       Arg2T,
                       ObjectT,
                       MethodCallType,
                       SizeTraitsT>::setMethod(ObjectMethodT pFunc)
{
    _flags |= FuncPtrValid;

    *((ObjectMethodT *) _data2) = pFunc; 
}


template <class RetT, 
          class Arg1T, 
          class Arg2T,
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
void ObjectFunctor2<RetT, 
                       Arg1T,
                       Arg2T,
                       ObjectT,
                       MethodCallType,
                       SizeTraitsT>::setMethod(ObjectMethodPtrT pFunc)
{
    _flags |= FuncPtrValid;
  
    *((ObjectMethodPtrT *) _data2) = pFunc; 
}


template <class RetT, 
          class Arg1T, 
          class Arg2T,
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
void ObjectFunctor2<RetT, 
                       Arg1T,
                       Arg2T,
                       ObjectT,
                       MethodCallType,
                       SizeTraitsT>::setCalledObject(SetObjectT pObj)
{
    _flags |= ObjectValid;

    FunctorTrait::setCalledObject(_data1, pObj);
}


template <class RetT, 
          class Arg1T, 
          class Arg2T,
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
void ObjectFunctor2<RetT, 
                       Arg1T,
                       Arg2T,
                       ObjectT,
                       MethodCallType,
                       SizeTraitsT>::setObjectAndMethod(
    SetObjectT       pObj, 
    ObjectMethodPtrT pFunc)
{
    _flags |= FuncPtrValid;
    _flags |= ObjectValid;
     
    FunctorTrait::setCalledObject(_data1, pObj);
    *((ObjectMethodPtrT *) _data2) = pFunc; 
}

/*-------------------------- your_category---------------------------------*/

#ifdef __sgi
#pragma set woff 1551 
#endif

template <class RetT, 
          class Arg1T, 
          class Arg2T,
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
RetT ObjectFunctor2<RetT, 
                          Arg1T,
                          Arg2T,
                          ObjectT,
                          MethodCallType,
                          SizeTraitsT>::call(Arg1T arg1, Arg2T arg2) 
{ 
    RetT returnValue;
    
    if(_flags & FuncPtrValid)
    {
        if(_flags & ObjectValid)
        {
            return FunctorTrait::callObjectMethod(_data1, _data2, 
                                                      arg1,   arg2);
        }
        else
        {
            return FunctorTrait::callObjectMethod(_data2, arg1, arg2);
        }
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

template <class Arg1T, 
          class Arg2T,
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT>
char ObjectFunctor2<void, 
                       Arg1T,
                       Arg2T,
                       ObjectT,
                       MethodCallType,
                       SizeTraitsT>::cvsid[] = "@(#)$Id: $";

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

template <class Arg1T, 
          class Arg2T,
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
ObjectFunctor2<void, 
                  Arg1T,
                  Arg2T,
                  ObjectT,
                  MethodCallType,
                  SizeTraitsT>::ObjectFunctor2(void)  :
    Inherited()
{
}

/** \brief Copy Constructor
 */


template <class Arg1T, 
          class Arg2T,
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
ObjectFunctor2<void,
                  Arg1T,
                  Arg2T,
                  ObjectT,
                  MethodCallType,
                  SizeTraitsT>::ObjectFunctor2(
    const ObjectFunctor2 &source) : 

    Inherited(source) 
{
}
    

/** \brief Destructor
 */


template <class Arg1T, 
          class Arg2T,
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
ObjectFunctor2<void, 
                  Arg1T,
                  Arg2T,
                  ObjectT,
                  MethodCallType,
                  SizeTraitsT>::~ObjectFunctor2(void) 
{
}

/*------------------------------ access -----------------------------------*/


template <class Arg1T, 
          class Arg2T,
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
void ObjectFunctor2<void, 
                       Arg1T,
                       Arg2T,
                       ObjectT,
                       MethodCallType,
                       SizeTraitsT>::setMethod(
    ObjectMethodT pFunc)
{
    _flags |= FuncPtrValid;

    *((ObjectMethodT *) _data2) = pFunc; 
}


template <class Arg1T, 
          class Arg2T,
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
void ObjectFunctor2<void, 
                       Arg1T,
                       Arg2T,
                       ObjectT,
                       MethodCallType,
                       SizeTraitsT>::setMethod(
    ObjectMethodPtrT pFunc)
{
    _flags |= FuncPtrValid;
  
    *((ObjectMethodPtrT *) _data2) = pFunc; 
}


template <class Arg1T, 
          class Arg2T,
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
void ObjectFunctor2<void, 
                       Arg1T,
                       Arg2T,
                       ObjectT,
                       MethodCallType,
                       SizeTraitsT>::setCalledObject(
    SetObjectT pObj)
{
    _flags |= ObjectValid;

    FunctorTrait::setCalledObject(_data1, pObj);
}


template <class Arg1T, 
          class Arg2T,
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
void ObjectFunctor2<void, 
                       Arg1T,
                       Arg2T,
                       ObjectT,
                       MethodCallType,
                       SizeTraitsT>::setObjectAndMethod(
    SetObjectT       pObj, 
    ObjectMethodPtrT pFunc)
{
    _flags |= FuncPtrValid;
    _flags |= ObjectValid;
     
    FunctorTrait::setCalledObject(_data1, pObj);

    *((ObjectMethodPtrT *) _data2) = pFunc; 
}

/*-------------------------- your_category---------------------------------*/

template <class Arg1T, 
          class Arg2T,
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT> inline
void ObjectFunctor2<void, 
                       Arg1T,
                       Arg2T,
                       ObjectT,
                       MethodCallType,
                       SizeTraitsT>::call(Arg1T arg1, Arg2T arg2) 
{ 
    if(_flags & FuncPtrValid)
    {
        if(_flags & ObjectValid)
        {
            FunctorTrait::callObjectMethodVoid(_data1, _data2, arg1, arg2);
        }
        else
        {
            FunctorTrait::callObjectMethodVoid(_data2, arg1, arg2);
        }
    }
}


template <class RetT, class Arg1T, class Arg2T> inline
FunctionFunctor2<RetT, Arg1T, Arg2T> osgFunctionFunctor2( 
    RetT (*pFunc)(Arg1T, Arg2T)) 
{ 
    FunctionFunctor2<RetT, Arg1T, Arg2T> returnValue; 

    returnValue.setFunction(pFunc); 

    return returnValue; 
} 



template <class RetT, class Arg1T, class Arg2T> inline
ObjectFunctor2<RetT, 
                  Arg1T &, 
                  Arg2T,
                  Arg1T,
                  OnArgument> osgMethodFunctor2Ref(
    RetT (Arg1T::*pFunc)(Arg2T))
{
    typedef ObjectFunctor2<RetT, 
                              Arg1T &, 
                              Arg2T,
                              Arg1T,
                              OnArgument> OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);    
    
    return returnValue;
} 

template <class RetT, class Arg1T, 
          class Arg2T, class ObjectT> inline
ObjectFunctor2<RetT, 
                  Arg1T, 
                  Arg2T,
                  ObjectT &,
                  OnStoredObject> osgMethodFunctor2Ref(
    ObjectT &obj, RetT (ObjectT::*pFunc)(Arg1T, Arg2T))
{
    typedef ObjectFunctor2<RetT, 
                              Arg1T, 
                              Arg2T,
                              ObjectT &,
                              OnStoredObject> OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);    
    returnValue.setCalledObject(obj);

    return returnValue;
} 



template <class RetT, class Arg1T, class Arg2T> inline
ObjectFunctor2<RetT, 
                  Arg1T *, 
                  Arg2T,
                  Arg1T,
                  OnArgument> osgMethodFunctor2Ptr(
    RetT (Arg1T::*pFunc)(Arg2T))
{
    typedef ObjectFunctor2<RetT, 
                              Arg1T *, 
                              Arg2T,
                              Arg1T,
                              OnArgument> OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);    
    
    return returnValue;
} 


template <class RetT,  class Arg1T, 
          class Arg2T, class ObjectT> inline
ObjectFunctor2<RetT, 
                  Arg1T, 
                  Arg2T,
                  ObjectT *,
                  OnStoredObject> osgMethodFunctor2Ptr(
    ObjectT *pObj, RetT (ObjectT::*pFunc)(Arg1T, Arg2T))
{
    typedef ObjectFunctor2<RetT, 
                              Arg1T, 
                              Arg2T,
                              ObjectT *,
                              OnStoredObject> OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);    
    returnValue.setCalledObject(pObj);

    return returnValue;
} 


template <class RetT, class Arg1T, class Arg2T> inline
ObjectFunctor2<RetT, 
                  Arg1T &, 
                  Arg2T, 
                  Arg1T,
                  OnCPtrArgument> osgMethodFunctor2CPtr(
    typename FunctorBuildFuncType2<RetT, 
                                      Arg2T,
                                      Arg1T>::FunctionType pFunc)
{
    typedef ObjectFunctor2<RetT, 
                              Arg1T &, 
                              Arg2T,
                              Arg1T,
                              OnCPtrArgument> OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);    
   
    return returnValue;
} 

#ifdef __sgi
#pragma set woff 1424
#endif

template <class RetT,    class Arg1T, 
          class ObjectT, class Arg2T> inline
ObjectFunctor2<RetT, 
                  Arg1T &, 
                  Arg2T, 
                  ObjectT,
                  OnCPtrArgument> osgMethodFunctor2BaseCPtr(
    typename FunctorBuildFuncType2<RetT, 
                                      Arg2T,
                                      ObjectT>::FunctionType pFunc)
{
    typedef ObjectFunctor2<RetT, 
                              Arg1T &, 
                              Arg2T,
                              ObjectT,
                              OnCPtrArgument> OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);    
   
    return returnValue;
} 

#ifdef __sgi
#pragma reset woff 1424
#endif

template <class RetT,  class Arg1T, 
          class Arg2T, class ObjectT> inline
ObjectFunctor2<RetT, 
                  Arg1T, 
                  Arg2T,
                  ObjectT &,
                  OnStoredCPtr> osgMethodFunctor2CPtr(
    ObjectT &obj,
    typename FunctorBuildFuncType3<RetT, 
                                      Arg1T, 
                                      Arg2T, 
                                      ObjectT>::FunctionType pFunc)
{
    typedef ObjectFunctor2<RetT, 
                              Arg1T, 
                              Arg2T,
                              ObjectT &,
                              OnStoredCPtr> OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);    
    returnValue.setCalledObject(obj);

    return returnValue;
} 

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
