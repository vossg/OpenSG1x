/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
 *                                                                           *
 *          contact: {reiners|vossg}@igd.fhg.de, jbehr@zgdv.de               *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

template <class OSGSizeTraitsT>
char OSGFunctorBase<OSGSizeTraitsT>::cvsid[] = "@(#)$Id: $";

template <class OSGSizeTraitsT>
const OSGUInt8 OSGFunctorBase<OSGSizeTraitsT>::OSGObjectValid  = 0x01;

template <class OSGSizeTraitsT>
const OSGUInt8 OSGFunctorBase<OSGSizeTraitsT>::OSGFuncPtrValid = 0x02;

template <class OSGSizeTraitsT>
const OSGUInt8 OSGFunctorBase<OSGSizeTraitsT>::OSGFunctorActive = 0x80;

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

template <class OSGSizeTraitsT> inline
OSGFunctorBase<OSGSizeTraitsT>::OSGFunctorBase(void) :
    _flags(0)
{
}

/** \brief Copy Constructor
 */

template <class OSGSizeTraitsT> inline
OSGFunctorBase<OSGSizeTraitsT>::OSGFunctorBase(const OSGFunctorBase &) 
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Destructor
 */

template <class OSGSizeTraitsT> inline
OSGFunctorBase<OSGSizeTraitsT>::~OSGFunctorBase(void) 
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

template <class OSGRetT, class OSGArg1T, class OSGSizeTraitsT>
char OSGFunctor1Base<OSGRetT, OSGArg1T, OSGSizeTraitsT>::cvsid[] = "@(#)$Id: $";

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

template <class OSGRetT, class OSGArg1T, class OSGSizeTraitsT> inline
OSGFunctor1Base<OSGRetT, OSGArg1T, OSGSizeTraitsT>::OSGFunctor1Base(void) : 
    Inherited()
{
}

template <class OSGRetT, class OSGArg1T, class OSGSizeTraitsT> inline
OSGFunctor1Base<OSGRetT, OSGArg1T, OSGSizeTraitsT>::OSGFunctor1Base(
    const OSGFunctor1Base &source) :

    Inherited()
{
    memcpy(this, &source, 
           sizeof(OSGFunctor1Base<OSGRetT, OSGArg1T, OSGSizeTraitsT>)); 
}


/** \brief Destructor
 */

template <class OSGRetT, class OSGArg1T, class OSGSizeTraitsT> inline
OSGFunctor1Base<OSGRetT, OSGArg1T, OSGSizeTraitsT>::~OSGFunctor1Base(void) 
{
}


/*-------------------------- your_category---------------------------------*/

// turn of returnValue used before set warning

#ifdef __sgi
#pragma set woff 1551 
#endif

template <class OSGRetT, class OSGArg1T, class OSGSizeTraitsT> inline
OSGRetT OSGFunctor1Base<OSGRetT, OSGArg1T, OSGSizeTraitsT>::call(OSGArg1T) 
{ 
    OSGRetT returnValue;

    FWARNING(("OSGFunctor1Base::call called, undefined behaviour might " 
              "be the consequence\n"));

    return returnValue;
}

#ifdef __sgi
#pragma reset woff 1551 
#endif

/*-------------------------- assignment -----------------------------------*/

template <class OSGRetT, class OSGArg1T, class OSGSizeTraitsT> inline
void OSGFunctor1Base<OSGRetT, OSGArg1T, OSGSizeTraitsT>::operator =(
    const OSGFunctor1Base &source) 
{
    if(this != &source)
    {
        memcpy(this, &source, 
               sizeof(OSGFunctor1Base<OSGRetT, OSGArg1T, OSGSizeTraitsT>)); 
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

template <class OSGArg1T, class OSGSizeTraitsT>
char OSGFunctor1Base<void, OSGArg1T, OSGSizeTraitsT>::cvsid[] = 
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

template <class OSGArg1T, class OSGSizeTraitsT> inline
OSGFunctor1Base<void, OSGArg1T, OSGSizeTraitsT>::OSGFunctor1Base(void) : 
    Inherited()
{
}

template <class OSGArg1T, class OSGSizeTraitsT> inline
OSGFunctor1Base<void, OSGArg1T, OSGSizeTraitsT>::OSGFunctor1Base(
    const OSGFunctor1Base &source) :

    Inherited()
{
    memcpy(this, &source, 
           sizeof(OSGFunctor1Base<void, OSGArg1T, OSGSizeTraitsT>)); 
}


/** \brief Destructor
 */

template <class OSGArg1T, class OSGSizeTraitsT> inline
OSGFunctor1Base<void, OSGArg1T, OSGSizeTraitsT>::~OSGFunctor1Base(void) 
{
}


/*-------------------------- your_category---------------------------------*/

// turn of returnValue used before set warning

#ifdef __sgi
#pragma set woff 1551 
#endif

template <class OSGArg1T, class OSGSizeTraitsT> inline
void OSGFunctor1Base<void, OSGArg1T, OSGSizeTraitsT>::call(OSGArg1T) 
{ 
    FWARNING(("OSGFunctor1Base::call called, undefined behaviour might " 
              "be the consequence\n"));
}

#ifdef __sgi
#pragma reset woff 1551 
#endif

/*-------------------------- assignment -----------------------------------*/

template <class OSGArg1T, class OSGSizeTraitsT> inline
void OSGFunctor1Base<void, OSGArg1T, OSGSizeTraitsT>::operator =(
    const OSGFunctor1Base &source) 
{
    if(this != &source)
    {
        memcpy(this, &source, 
               sizeof(OSGFunctor1Base<void, OSGArg1T, OSGSizeTraitsT>)); 
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

template <class OSGRetT, class OSGArg1T, class OSGSizeTraitsT>
char OSGFunctionFunctor1<OSGRetT, OSGArg1T, OSGSizeTraitsT>::cvsid[] = 
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

template <class OSGRetT, class OSGArg1T, class OSGSizeTraitsT> inline
OSGFunctionFunctor1<OSGRetT, OSGArg1T, OSGSizeTraitsT>::OSGFunctionFunctor1(
    void) :

    Inherited()
{
}

/** \brief Copy Constructor
 */

template <class OSGRetT, class OSGArg1T, class OSGSizeTraitsT> inline
OSGFunctionFunctor1<OSGRetT, OSGArg1T, OSGSizeTraitsT>::OSGFunctionFunctor1(
    const OSGFunctionFunctor1 &source) : 
    
    Inherited(source) 
{
}
    
/** \brief Destructor
 */

template <class OSGRetT, class OSGArg1T, class OSGSizeTraitsT> inline
OSGFunctionFunctor1<OSGRetT, OSGArg1T, OSGSizeTraitsT>::~OSGFunctionFunctor1(
    void)
{
}

/*------------------------------ access -----------------------------------*/

template <class OSGRetT, class OSGArg1T, class OSGSizeTraitsT> inline
void OSGFunctionFunctor1<OSGRetT, OSGArg1T, OSGSizeTraitsT>::setFunction(
    OSGFunctionP pFunc)
{
    *((OSGFunctionP *) _data2) = pFunc;
}

/*-------------------------- your_category---------------------------------*/

template <class OSGRetT, class OSGArg1T, class OSGSizeTraitsT> inline
OSGRetT OSGFunctionFunctor1<OSGRetT, OSGArg1T, OSGSizeTraitsT>::call(
    OSGArg1T arg1)
{
    OSGFunctionP pFunc = *((OSGFunctionP *) _data2);

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

template <class OSGArg1T, class OSGSizeTraitsT>
char OSGFunctionFunctor1<void, OSGArg1T, OSGSizeTraitsT>::cvsid[] = 
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

template <class OSGArg1T, class OSGSizeTraitsT> inline
OSGFunctionFunctor1<void, OSGArg1T, OSGSizeTraitsT>::OSGFunctionFunctor1(
    void) :

    Inherited()
{
}

/** \brief Copy Constructor
 */

template <class OSGArg1T, class OSGSizeTraitsT> inline
OSGFunctionFunctor1<void, OSGArg1T, OSGSizeTraitsT>::OSGFunctionFunctor1(
    const OSGFunctionFunctor1 &source) : 
    
    Inherited(source) 
{
}
    
/** \brief Destructor
 */

template <class OSGArg1T, class OSGSizeTraitsT> inline
OSGFunctionFunctor1<void, OSGArg1T, OSGSizeTraitsT>::~OSGFunctionFunctor1(
    void)
{
}

/*------------------------------ access -----------------------------------*/

template <class OSGArg1T, class OSGSizeTraitsT> inline
void OSGFunctionFunctor1<void, OSGArg1T, OSGSizeTraitsT>::setFunction(
    OSGFunctionP pFunc)
{
    *((OSGFunctionP *) _data2) = pFunc;
}

/*-------------------------- your_category---------------------------------*/

template <class OSGArg1T, class OSGSizeTraitsT> inline
void OSGFunctionFunctor1<void, OSGArg1T, OSGSizeTraitsT>::call(
    OSGArg1T arg1)
{
    OSGFunctionP pFunc = *((OSGFunctionP *) _data2);

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

template <class OSGRetT, 
          class OSGArg1T, 
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT>
char OSGObjectFunctor1<OSGRetT,    OSGArg1T,
                       OSGObjectT, osgMethodCallType,
                       OSGSizeTraitsT>::cvsid[] = "@(#)$Id: $";

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

template <class OSGRetT, 
          class OSGArg1T, 
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
OSGObjectFunctor1<OSGRetT, 
                  OSGArg1T,
                  OSGObjectT,
                  osgMethodCallType,
                  OSGSizeTraitsT>::OSGObjectFunctor1(void)  :
    Inherited()
{
}

/** \brief Copy Constructor
 */


template <class OSGRetT, 
          class OSGArg1T, 
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
OSGObjectFunctor1<OSGRetT,
                  OSGArg1T,
                  OSGObjectT,
                  osgMethodCallType,
                  OSGSizeTraitsT>::OSGObjectFunctor1(
    const OSGObjectFunctor1 &source) : 

    Inherited(source) 
{
}
    

/** \brief Destructor
 */


template <class OSGRetT, 
          class OSGArg1T, 
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
OSGObjectFunctor1<OSGRetT,
                  OSGArg1T,
                  OSGObjectT,
                  osgMethodCallType,
                  OSGSizeTraitsT>::~OSGObjectFunctor1(void) 
{
}

/*------------------------------ access -----------------------------------*/


template <class OSGRetT, 
          class OSGArg1T, 
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
void OSGObjectFunctor1<OSGRetT, 
                       OSGArg1T,
                       OSGObjectT,
                       osgMethodCallType,
                       OSGSizeTraitsT>::setMethod(OSGObjectMethodT pFunc)
{
    _flags |= OSGFuncPtrValid;

    *((OSGObjectMethodT *) _data2) = pFunc; 
}


template <class OSGRetT, 
          class OSGArg1T, 
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
void OSGObjectFunctor1<OSGRetT, 
                       OSGArg1T,
                       OSGObjectT,
                       osgMethodCallType,
                       OSGSizeTraitsT>::setMethod(OSGObjectMethodPtrT pFunc)
{
    _flags |= OSGFuncPtrValid;
  
    *((OSGObjectMethodPtrT *) _data2) = pFunc; 
}


template <class OSGRetT, 
          class OSGArg1T, 
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
void OSGObjectFunctor1<OSGRetT, 
                       OSGArg1T,
                       OSGObjectT,
                       osgMethodCallType,
                       OSGSizeTraitsT>::setCalledObject(OSGSetObjectT pObj)
{
    _flags |= OSGObjectValid;

    OSGFunctorTrait::setCalledObject(_data1, pObj);
}


template <class OSGRetT, 
          class OSGArg1T, 
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
void OSGObjectFunctor1<OSGRetT, 
                       OSGArg1T,
                       OSGObjectT,
                       osgMethodCallType,
                       OSGSizeTraitsT>::setObjectAndMethod(
    OSGSetObjectT       pObj, 
    OSGObjectMethodPtrT pFunc)
{
    _flags |= OSGFuncPtrValid;
    _flags |= OSGObjectValid;
     
    OSGFunctorTrait::setCalledObject(_data1, pObj);
    *((OSGObjectMethodPtrT *) _data2) = pFunc; 
}

/*-------------------------- your_category---------------------------------*/

#ifdef __sgi
#pragma set woff 1551 
#endif

template <class OSGRetT, 
          class OSGArg1T, 
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
OSGRetT OSGObjectFunctor1<OSGRetT, 
                          OSGArg1T,
                          OSGObjectT,
                          osgMethodCallType,
                          OSGSizeTraitsT>::call(OSGArg1T arg1) 
{ 
    OSGRetT returnValue;

    if(_flags & OSGFuncPtrValid)
    {
        if(_flags & OSGObjectValid)
        {
            return OSGFunctorTrait::callObjectMethod(_data1, _data2, arg1);
        }
        else
        {
            return OSGFunctorTrait::callObjectMethod(_data2, arg1);
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

template <class OSGArg1T, 
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT>
char OSGObjectFunctor1<void, 
                       OSGArg1T,
                       OSGObjectT,
                       osgMethodCallType,
                       OSGSizeTraitsT>::cvsid[] = "@(#)$Id: $";

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

template <class OSGArg1T, 
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
OSGObjectFunctor1<void, 
                  OSGArg1T,
                  OSGObjectT,
                  osgMethodCallType,
                  OSGSizeTraitsT>::OSGObjectFunctor1(void)  :
    Inherited()
{
}

/** \brief Copy Constructor
 */


template <class OSGArg1T, 
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
OSGObjectFunctor1<void,
                  OSGArg1T,
                  OSGObjectT,
                  osgMethodCallType,
                  OSGSizeTraitsT>::OSGObjectFunctor1(
    const OSGObjectFunctor1 &source) : 

    Inherited(source) 
{
}
    

/** \brief Destructor
 */


template <class OSGArg1T, 
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
OSGObjectFunctor1<void, 
                  OSGArg1T,
                  OSGObjectT,
                  osgMethodCallType,
                  OSGSizeTraitsT>::~OSGObjectFunctor1(void) 
{
}

/*------------------------------ access -----------------------------------*/


template <class OSGArg1T, 
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
void OSGObjectFunctor1<void, 
                       OSGArg1T,
                       OSGObjectT,
                       osgMethodCallType,
                       OSGSizeTraitsT>::setMethod(
    OSGObjectMethodT pFunc)
{
    _flags |= OSGFuncPtrValid;

    *((OSGObjectMethodT *) _data2) = pFunc; 
}


template <class OSGArg1T, 
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
void OSGObjectFunctor1<void, 
                       OSGArg1T,
                       OSGObjectT,
                       osgMethodCallType,
                       OSGSizeTraitsT>::setMethod(
    OSGObjectMethodPtrT pFunc)
{
    _flags |= OSGFuncPtrValid;
  
    *((OSGObjectMethodPtrT *) _data2) = pFunc; 
}


template <class OSGArg1T, 
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
void OSGObjectFunctor1<void, 
                       OSGArg1T,
                       OSGObjectT,
                       osgMethodCallType,
                       OSGSizeTraitsT>::setCalledObject(
    OSGSetObjectT pObj)
{
    _flags |= OSGObjectValid;

    OSGFunctorTrait::setCalledObject(_data1, pObj);
}


template <class OSGArg1T, 
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
void OSGObjectFunctor1<void, 
                       OSGArg1T,
                       OSGObjectT,
                       osgMethodCallType,
                       OSGSizeTraitsT>::setObjectAndMethod(
    OSGSetObjectT       pObj, 
    OSGObjectMethodPtrT pFunc)
{
    _flags |= OSGFuncPtrValid;
    _flags |= OSGObjectValid;
     
    OSGFunctorTrait::setCalledObject(_data1, pObj);

    *((OSGObjectMethodPtrT *) _data2) = pFunc; 
}

/*-------------------------- your_category---------------------------------*/

template <class OSGArg1T, 
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
void OSGObjectFunctor1<void, 
                       OSGArg1T,
                       OSGObjectT,
                       osgMethodCallType,
                       OSGSizeTraitsT>::call(OSGArg1T arg1) 
{ 
    if(_flags & OSGFuncPtrValid)
    {
        if(_flags & OSGObjectValid)
        {
            OSGFunctorTrait::callObjectMethodVoid(_data1, _data2, arg1);
        }
        else
        {
            OSGFunctorTrait::callObjectMethodVoid(_data2, arg1);
        }
    }
}


template <class OSGRetT, class OSGArg1T> inline
OSGFunctionFunctor1<OSGRetT, OSGArg1T> osgFunctionFunctor1( 
    OSGRetT (*pFunc)(OSGArg1T)) 
{ 
    OSGFunctionFunctor1<OSGRetT, OSGArg1T> returnValue; 

    returnValue.setFunction(pFunc); 

    return returnValue; 
} 

template <class OSGRetT, class OSGArg1T> inline
OSGObjectFunctor1<OSGRetT, 
                  OSGArg1T &, 
                  OSGArg1T,
                  OSGOnArgument> osgMethodFunctor1Ref(
    OSGRetT (OSGArg1T::*pFunc)())
{
    typedef OSGObjectFunctor1<OSGRetT, 
                              OSGArg1T &, 
                              OSGArg1T,
                              OSGOnArgument> OSGOFunctor;

    OSGOFunctor returnValue;

    returnValue.setMethod(pFunc);    
    
    return returnValue;
} 


template <class OSGRetT, class OSGArg1T, class OSGObjectT> inline
OSGObjectFunctor1<OSGRetT, 
                  OSGArg1T, 
                  OSGObjectT &,
                  OSGOnStoredObject> osgMethodFunctor1Ref(
    OSGObjectT &obj, OSGRetT (OSGObjectT::*pFunc)(OSGArg1T))
{
    typedef OSGObjectFunctor1<OSGRetT, 
                              OSGArg1T, 
                              OSGObjectT &,
                              OSGOnStoredObject> OSGOFunctor;

    OSGOFunctor returnValue;

    returnValue.setMethod(pFunc);    
    returnValue.setCalledObject(obj);

    return returnValue;
} 



template <class OSGRetT, class OSGArg1T> inline
OSGObjectFunctor1<OSGRetT, 
                  OSGArg1T *, 
                  OSGArg1T,
                  OSGOnArgument> osgMethodFunctor1Ptr(
    OSGRetT (OSGArg1T::*pFunc)())
{
    typedef OSGObjectFunctor1<OSGRetT, 
                              OSGArg1T *, 
                              OSGArg1T,
                              OSGOnArgument> OSGOFunctor;

    OSGOFunctor returnValue;

    returnValue.setMethod(pFunc);    
    
    return returnValue;
} 


template <class OSGRetT, class OSGArg1T, class OSGObjectT> inline
OSGObjectFunctor1<OSGRetT, 
                  OSGArg1T, 
                  OSGObjectT *,
                  OSGOnStoredObject> osgMethodFunctor1Ptr(
    OSGObjectT *pObj, OSGRetT (OSGObjectT::*pFunc)(OSGArg1T))
{
    typedef OSGObjectFunctor1<OSGRetT, 
                              OSGArg1T, 
                              OSGObjectT *,
                              OSGOnStoredObject> OSGOFunctor;

    OSGOFunctor returnValue;

    returnValue.setMethod(pFunc);    
    returnValue.setCalledObject(pObj);

    return returnValue;
}


template <class OSGRetT, class OSGArg1T> inline
OSGObjectFunctor1<OSGRetT, 
                  OSGArg1T &, 
                  OSGArg1T,
                  OSGOnCPtrArgument> osgMethodFunctor1CPtr(
   typename OSGFunctorBuildFuncType1<OSGRetT, OSGArg1T>::OSGFunctionType pFunc)
{
    typedef OSGObjectFunctor1<OSGRetT, 
                              OSGArg1T &, 
                              OSGArg1T,
                              OSGOnCPtrArgument> OSGOFunctor;

    OSGOFunctor returnValue;

    returnValue.setMethod(pFunc);    
   
    return returnValue;
} 

template <class OSGRetT, class OSGArg1T, class OSGObjectT> inline
OSGObjectFunctor1<OSGRetT, 
                  OSGArg1T, 
                  OSGObjectT &,
                  OSGOnStoredCPtr> osgMethodFunctor1CPtr(
    OSGObjectT &obj, 
    typename OSGFunctorBuildFuncType2<OSGRetT, 
                                      OSGArg1T, 
                                      OSGObjectT>::OSGFunctionType pFunc)
{
    typedef OSGObjectFunctor1<OSGRetT, 
                              OSGArg1T, 
                              OSGObjectT &,
                              OSGOnStoredCPtr> OSGOFunctor;

    OSGOFunctor returnValue;

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

template <class OSGRetT, class OSGArg1T, class OSGArg2T, class OSGSizeTraitsT>
char OSGFunctor2Base<OSGRetT,  OSGArg1T, 
                     OSGArg2T, OSGSizeTraitsT>::cvsid[] = "@(#)$Id: $";

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

template <class OSGRetT,  class OSGArg1T, 
          class OSGArg2T, class OSGSizeTraitsT> inline
OSGFunctor2Base<OSGRetT, OSGArg1T, OSGArg2T, OSGSizeTraitsT>::OSGFunctor2Base(
    void) : 

    Inherited()
{
}

template <class OSGRetT,  class OSGArg1T,
          class OSGArg2T, class OSGSizeTraitsT> inline
OSGFunctor2Base<OSGRetT, OSGArg1T, OSGArg2T, OSGSizeTraitsT>::OSGFunctor2Base(
    const OSGFunctor2Base &source) :

    Inherited()
{
    memcpy(this, &source, 
           sizeof(OSGFunctor2Base<OSGRetT, OSGArg1T, 
                                  OSGArg2T, OSGSizeTraitsT>)); 
}


/** \brief Destructor
 */

template <class OSGRetT,  class OSGArg1T,
          class OSGArg2T, class OSGSizeTraitsT> inline
OSGFunctor2Base<OSGRetT, OSGArg1T, OSGArg2T, OSGSizeTraitsT>::~OSGFunctor2Base(
    void) 
{
}


/*-------------------------- your_category---------------------------------*/

// turn of returnValue used before set warning

#ifdef __sgi
#pragma set woff 1551 
#endif

template <class OSGRetT,  class OSGArg1T,
          class OSGArg2T, class OSGSizeTraitsT> inline
OSGRetT OSGFunctor2Base<OSGRetT, OSGArg1T, OSGArg2T, OSGSizeTraitsT>::call(
    OSGArg1T, OSGArg2T) 
{ 
    OSGRetT returnValue;

    FWARNING(("OSGFunctor2Base::call called, undefined behaviour might " 
              "be the consequence\n"));

    return returnValue;
}

#ifdef __sgi
#pragma reset woff 1551 
#endif

/*-------------------------- assignment -----------------------------------*/

template <class OSGRetT,  class OSGArg1T,
          class OSGArg2T, class OSGSizeTraitsT> inline
void OSGFunctor2Base<OSGRetT, OSGArg1T, OSGArg2T, OSGSizeTraitsT>::operator =(
    const OSGFunctor2Base &source) 
{
    if(this != &source)
    {
        memcpy(this, &source, 
               sizeof(OSGFunctor2Base<OSGRetT,  OSGArg1T, 
                                      OSGArg2T, OSGSizeTraitsT>)); 
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

template <class OSGArg1T, class OSGArg2T, class OSGSizeTraitsT>
char OSGFunctor2Base<void, OSGArg1T, OSGArg2T, OSGSizeTraitsT>::cvsid[] = 
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

template <class OSGArg1T, class OSGArg2T, class OSGSizeTraitsT> inline
OSGFunctor2Base<void, OSGArg1T, OSGArg2T, OSGSizeTraitsT>::OSGFunctor2Base(
    void) : 

    Inherited()
{
}

template <class OSGArg1T, class OSGArg2T, class OSGSizeTraitsT> inline
OSGFunctor2Base<void, OSGArg1T, OSGArg2T, OSGSizeTraitsT>::OSGFunctor2Base(
    const OSGFunctor2Base &source) :

    Inherited()
{
    memcpy(this, &source, 
           sizeof(OSGFunctor2Base<void, OSGArg1T, OSGArg2T, OSGSizeTraitsT>)); 
}


/** \brief Destructor
 */

template <class OSGArg1T, class OSGArg2T, class OSGSizeTraitsT> inline
OSGFunctor2Base<void, OSGArg1T, OSGArg2T, OSGSizeTraitsT>::~OSGFunctor2Base(
    void) 
{
}


/*-------------------------- your_category---------------------------------*/

// turn of returnValue used before set warning

#ifdef __sgi
#pragma set woff 1551 
#endif

template <class OSGArg1T, class OSGArg2T, class OSGSizeTraitsT> inline
void OSGFunctor2Base<void, OSGArg1T, OSGArg2T, OSGSizeTraitsT>::call(
    OSGArg1T, OSGArg2T) 
{ 
    FWARNING(("OSGFunctor2Base::call called, undefined behaviour might " 
              "be the consequence\n"));
}

#ifdef __sgi
#pragma reset woff 1551 
#endif

/*-------------------------- assignment -----------------------------------*/

template <class OSGArg1T, class OSGArg2T, class OSGSizeTraitsT> inline
void OSGFunctor2Base<void, OSGArg1T, OSGArg2T, OSGSizeTraitsT>::operator =(
    const OSGFunctor2Base &source) 
{
    if(this != &source)
    {
        memcpy(this, &source, 
               sizeof(OSGFunctor2Base<void,     OSGArg1T, 
                                      OSGArg2T, OSGSizeTraitsT>)); 
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

template <class OSGRetT,  class OSGArg1T,
          class OSGArg2T, class OSGSizeTraitsT>
char OSGFunctionFunctor2<OSGRetT, OSGArg1T, OSGArg2T, OSGSizeTraitsT>::cvsid[]=
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

template <class OSGRetT,  class OSGArg1T, 
          class OSGArg2T, class OSGSizeTraitsT> inline
OSGFunctionFunctor2<OSGRetT,  OSGArg1T, 
                    OSGArg2T, OSGSizeTraitsT>::OSGFunctionFunctor2(void) :

    Inherited()
{
}

/** \brief Copy Constructor
 */

template <class OSGRetT,  class OSGArg1T,
          class OSGArg2T, class OSGSizeTraitsT> inline
OSGFunctionFunctor2<OSGRetT,  OSGArg1T, 
                    OSGArg2T, OSGSizeTraitsT>::OSGFunctionFunctor2(
    const OSGFunctionFunctor2 &source) : 
    
    Inherited(source) 
{
}
    
/** \brief Destructor
 */

template <class OSGRetT,  class OSGArg1T,
          class OSGArg2T, class OSGSizeTraitsT> inline
OSGFunctionFunctor2<OSGRetT, OSGArg1T, 
                    OSGArg2T, OSGSizeTraitsT>::~OSGFunctionFunctor2(void)
{
}

/*------------------------------ access -----------------------------------*/

template <class OSGRetT,  class OSGArg1T,
          class OSGArg2T, class OSGSizeTraitsT> inline
void OSGFunctionFunctor2<OSGRetT,  OSGArg1T, 
                         OSGArg2T, OSGSizeTraitsT>::setFunction(
    OSGFunctionP pFunc)
{
    *((OSGFunctionP *) _data2) = pFunc;
}

/*-------------------------- your_category---------------------------------*/

template <class OSGRetT,  class OSGArg1T,
          class OSGArg2T, class OSGSizeTraitsT> inline
OSGRetT OSGFunctionFunctor2<OSGRetT, OSGArg1T, OSGArg2T, OSGSizeTraitsT>::call(
    OSGArg1T arg1, OSGArg2T arg2)
{
    OSGFunctionP pFunc = *((OSGFunctionP *) _data2);

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

template <class OSGArg1T, class OSGArg2T, class OSGSizeTraitsT>
char OSGFunctionFunctor2<void, OSGArg1T, OSGArg2T, OSGSizeTraitsT>::cvsid[] = 
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

template <class OSGArg1T, class OSGArg2T, class OSGSizeTraitsT> inline
OSGFunctionFunctor2<void,     OSGArg1T, 
                    OSGArg2T, OSGSizeTraitsT>::OSGFunctionFunctor2(void) :

    Inherited()
{
}

/** \brief Copy Constructor
 */

template <class OSGArg1T, class OSGArg2T, class OSGSizeTraitsT> inline
OSGFunctionFunctor2<void,     OSGArg1T, 
                    OSGArg2T, OSGSizeTraitsT>::OSGFunctionFunctor2(
    const OSGFunctionFunctor2 &source) : 
    
    Inherited(source) 
{
}
    
/** \brief Destructor
 */

template <class OSGArg1T, class OSGArg2T, class OSGSizeTraitsT> inline
OSGFunctionFunctor2<void,     OSGArg1T, 
                    OSGArg2T, OSGSizeTraitsT>::~OSGFunctionFunctor2(
    void)
{
}

/*------------------------------ access -----------------------------------*/

template <class OSGArg1T, class OSGArg2T, class OSGSizeTraitsT> inline
void OSGFunctionFunctor2<void,     OSGArg1T, 
                         OSGArg2T, OSGSizeTraitsT>::setFunction(
    OSGFunctionP pFunc)
{
    *((OSGFunctionP *) _data2) = pFunc;
}

/*-------------------------- your_category---------------------------------*/

template <class OSGArg1T, class OSGArg2T, class OSGSizeTraitsT> inline
void OSGFunctionFunctor2<void, OSGArg1T, OSGArg2T, OSGSizeTraitsT>::call(
    OSGArg1T arg1, OSGArg2T arg2)
{
    OSGFunctionP pFunc = *((OSGFunctionP *) _data2);

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

template <class OSGRetT, 
          class OSGArg1T, 
          class OSGArg2T,
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT>
char OSGObjectFunctor2<OSGRetT,    
                       OSGArg1T,
                       OSGArg2T,
                       OSGObjectT, 
                       osgMethodCallType,
                       OSGSizeTraitsT>::cvsid[] = "@(#)$Id: $";

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

template <class OSGRetT, 
          class OSGArg1T, 
          class OSGArg2T,
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
OSGObjectFunctor2<OSGRetT, 
                  OSGArg1T,
                  OSGArg2T,
                  OSGObjectT,
                  osgMethodCallType,
                  OSGSizeTraitsT>::OSGObjectFunctor2(void)  :
    Inherited()
{
}

/** \brief Copy Constructor
 */


template <class OSGRetT, 
          class OSGArg1T, 
          class OSGArg2T, 
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
OSGObjectFunctor2<OSGRetT,
                  OSGArg1T,
                  OSGArg2T,
                  OSGObjectT,
                  osgMethodCallType,
                  OSGSizeTraitsT>::OSGObjectFunctor2(
    const OSGObjectFunctor2 &source) : 

    Inherited(source) 
{
}
    

/** \brief Destructor
 */


template <class OSGRetT, 
          class OSGArg1T, 
          class OSGArg2T,
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
OSGObjectFunctor2<OSGRetT,
                  OSGArg1T,
                  OSGArg2T,
                  OSGObjectT,
                  osgMethodCallType,
                  OSGSizeTraitsT>::~OSGObjectFunctor2(void) 
{
}

/*------------------------------ access -----------------------------------*/


template <class OSGRetT, 
          class OSGArg1T, 
          class OSGArg2T,
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
void OSGObjectFunctor2<OSGRetT, 
                       OSGArg1T,
                       OSGArg2T,
                       OSGObjectT,
                       osgMethodCallType,
                       OSGSizeTraitsT>::setMethod(OSGObjectMethodT pFunc)
{
    _flags |= OSGFuncPtrValid;

    *((OSGObjectMethodT *) _data2) = pFunc; 
}


template <class OSGRetT, 
          class OSGArg1T, 
          class OSGArg2T,
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
void OSGObjectFunctor2<OSGRetT, 
                       OSGArg1T,
                       OSGArg2T,
                       OSGObjectT,
                       osgMethodCallType,
                       OSGSizeTraitsT>::setMethod(OSGObjectMethodPtrT pFunc)
{
    _flags |= OSGFuncPtrValid;
  
    *((OSGObjectMethodPtrT *) _data2) = pFunc; 
}


template <class OSGRetT, 
          class OSGArg1T, 
          class OSGArg2T,
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
void OSGObjectFunctor2<OSGRetT, 
                       OSGArg1T,
                       OSGArg2T,
                       OSGObjectT,
                       osgMethodCallType,
                       OSGSizeTraitsT>::setCalledObject(OSGSetObjectT pObj)
{
    _flags |= OSGObjectValid;

    OSGFunctorTrait::setCalledObject(_data1, pObj);
}


template <class OSGRetT, 
          class OSGArg1T, 
          class OSGArg2T,
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
void OSGObjectFunctor2<OSGRetT, 
                       OSGArg1T,
                       OSGArg2T,
                       OSGObjectT,
                       osgMethodCallType,
                       OSGSizeTraitsT>::setObjectAndMethod(
    OSGSetObjectT       pObj, 
    OSGObjectMethodPtrT pFunc)
{
    _flags |= OSGFuncPtrValid;
    _flags |= OSGObjectValid;
     
    OSGFunctorTrait::setCalledObject(_data1, pObj);
    *((OSGObjectMethodPtrT *) _data2) = pFunc; 
}

/*-------------------------- your_category---------------------------------*/

#ifdef __sgi
#pragma set woff 1551 
#endif

template <class OSGRetT, 
          class OSGArg1T, 
          class OSGArg2T,
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
OSGRetT OSGObjectFunctor2<OSGRetT, 
                          OSGArg1T,
                          OSGArg2T,
                          OSGObjectT,
                          osgMethodCallType,
                          OSGSizeTraitsT>::call(OSGArg1T arg1, OSGArg2T arg2) 
{ 
    OSGRetT returnValue;
    
    if(_flags & OSGFuncPtrValid)
    {
        if(_flags & OSGObjectValid)
        {
            return OSGFunctorTrait::callObjectMethod(_data1, _data2, 
                                                      arg1,   arg2);
        }
        else
        {
            return OSGFunctorTrait::callObjectMethod(_data2, arg1, arg2);
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

template <class OSGArg1T, 
          class OSGArg2T,
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT>
char OSGObjectFunctor2<void, 
                       OSGArg1T,
                       OSGArg2T,
                       OSGObjectT,
                       osgMethodCallType,
                       OSGSizeTraitsT>::cvsid[] = "@(#)$Id: $";

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

template <class OSGArg1T, 
          class OSGArg2T,
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
OSGObjectFunctor2<void, 
                  OSGArg1T,
                  OSGArg2T,
                  OSGObjectT,
                  osgMethodCallType,
                  OSGSizeTraitsT>::OSGObjectFunctor2(void)  :
    Inherited()
{
}

/** \brief Copy Constructor
 */


template <class OSGArg1T, 
          class OSGArg2T,
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
OSGObjectFunctor2<void,
                  OSGArg1T,
                  OSGArg2T,
                  OSGObjectT,
                  osgMethodCallType,
                  OSGSizeTraitsT>::OSGObjectFunctor2(
    const OSGObjectFunctor2 &source) : 

    Inherited(source) 
{
}
    

/** \brief Destructor
 */


template <class OSGArg1T, 
          class OSGArg2T,
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
OSGObjectFunctor2<void, 
                  OSGArg1T,
                  OSGArg2T,
                  OSGObjectT,
                  osgMethodCallType,
                  OSGSizeTraitsT>::~OSGObjectFunctor2(void) 
{
}

/*------------------------------ access -----------------------------------*/


template <class OSGArg1T, 
          class OSGArg2T,
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
void OSGObjectFunctor2<void, 
                       OSGArg1T,
                       OSGArg2T,
                       OSGObjectT,
                       osgMethodCallType,
                       OSGSizeTraitsT>::setMethod(
    OSGObjectMethodT pFunc)
{
    _flags |= OSGFuncPtrValid;

    *((OSGObjectMethodT *) _data2) = pFunc; 
}


template <class OSGArg1T, 
          class OSGArg2T,
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
void OSGObjectFunctor2<void, 
                       OSGArg1T,
                       OSGArg2T,
                       OSGObjectT,
                       osgMethodCallType,
                       OSGSizeTraitsT>::setMethod(
    OSGObjectMethodPtrT pFunc)
{
    _flags |= OSGFuncPtrValid;
  
    *((OSGObjectMethodPtrT *) _data2) = pFunc; 
}


template <class OSGArg1T, 
          class OSGArg2T,
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
void OSGObjectFunctor2<void, 
                       OSGArg1T,
                       OSGArg2T,
                       OSGObjectT,
                       osgMethodCallType,
                       OSGSizeTraitsT>::setCalledObject(
    OSGSetObjectT pObj)
{
    _flags |= OSGObjectValid;

    OSGFunctorTrait::setCalledObject(_data1, pObj);
}


template <class OSGArg1T, 
          class OSGArg2T,
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
void OSGObjectFunctor2<void, 
                       OSGArg1T,
                       OSGArg2T,
                       OSGObjectT,
                       osgMethodCallType,
                       OSGSizeTraitsT>::setObjectAndMethod(
    OSGSetObjectT       pObj, 
    OSGObjectMethodPtrT pFunc)
{
    _flags |= OSGFuncPtrValid;
    _flags |= OSGObjectValid;
     
    OSGFunctorTrait::setCalledObject(_data1, pObj);

    *((OSGObjectMethodPtrT *) _data2) = pFunc; 
}

/*-------------------------- your_category---------------------------------*/

template <class OSGArg1T, 
          class OSGArg2T,
          class OSGObjectT, 
          enum  OSGFunctorMethodCallTypeE osgMethodCallType,
          class OSGSizeTraitsT> inline
void OSGObjectFunctor2<void, 
                       OSGArg1T,
                       OSGArg2T,
                       OSGObjectT,
                       osgMethodCallType,
                       OSGSizeTraitsT>::call(OSGArg1T arg1, OSGArg2T arg2) 
{ 
    if(_flags & OSGFuncPtrValid)
    {
        if(_flags & OSGObjectValid)
        {
            OSGFunctorTrait::callObjectMethodVoid(_data1, _data2, arg1, arg2);
        }
        else
        {
            OSGFunctorTrait::callObjectMethodVoid(_data2, arg1, arg2);
        }
    }
}


template <class OSGRetT, class OSGArg1T, class OSGArg2T> inline
OSGFunctionFunctor2<OSGRetT, OSGArg1T, OSGArg2T> osgFunctionFunctor2( 
    OSGRetT (*pFunc)(OSGArg1T, OSGArg2T)) 
{ 
    OSGFunctionFunctor2<OSGRetT, OSGArg1T, OSGArg2T> returnValue; 

    returnValue.setFunction(pFunc); 

    return returnValue; 
} 



template <class OSGRetT, class OSGArg1T, class OSGArg2T> inline
OSGObjectFunctor2<OSGRetT, 
                  OSGArg1T &, 
                  OSGArg2T,
                  OSGArg1T,
                  OSGOnArgument> osgMethodFunctor2Ref(
    OSGRetT (OSGArg1T::*pFunc)(OSGArg2T))
{
    typedef OSGObjectFunctor2<OSGRetT, 
                              OSGArg1T &, 
                              OSGArg2T,
                              OSGArg1T,
                              OSGOnArgument> OSGOFunctor;

    OSGOFunctor returnValue;

    returnValue.setMethod(pFunc);    
    
    return returnValue;
} 

template <class OSGRetT, class OSGArg1T, 
          class OSGArg2T, class OSGObjectT> inline
OSGObjectFunctor2<OSGRetT, 
                  OSGArg1T, 
                  OSGArg2T,
                  OSGObjectT &,
                  OSGOnStoredObject> osgMethodFunctor2Ref(
    OSGObjectT &obj, OSGRetT (OSGObjectT::*pFunc)(OSGArg1T, OSGArg2T))
{
    typedef OSGObjectFunctor2<OSGRetT, 
                              OSGArg1T, 
                              OSGArg2T,
                              OSGObjectT &,
                              OSGOnStoredObject> OSGOFunctor;

    OSGOFunctor returnValue;

    returnValue.setMethod(pFunc);    
    returnValue.setCalledObject(obj);

    return returnValue;
} 



template <class OSGRetT, class OSGArg1T, class OSGArg2T> inline
OSGObjectFunctor2<OSGRetT, 
                  OSGArg1T *, 
                  OSGArg2T,
                  OSGArg1T,
                  OSGOnArgument> osgMethodFunctor2Ptr(
    OSGRetT (OSGArg1T::*pFunc)(OSGArg2T))
{
    typedef OSGObjectFunctor2<OSGRetT, 
                              OSGArg1T *, 
                              OSGArg2T,
                              OSGArg1T,
                              OSGOnArgument> OSGOFunctor;

    OSGOFunctor returnValue;

    returnValue.setMethod(pFunc);    
    
    return returnValue;
} 


template <class OSGRetT,  class OSGArg1T, 
          class OSGArg2T, class OSGObjectT> inline
OSGObjectFunctor2<OSGRetT, 
                  OSGArg1T, 
                  OSGArg2T,
                  OSGObjectT *,
                  OSGOnStoredObject> osgMethodFunctor2Ptr(
    OSGObjectT *pObj, OSGRetT (OSGObjectT::*pFunc)(OSGArg1T, OSGArg2T))
{
    typedef OSGObjectFunctor2<OSGRetT, 
                              OSGArg1T, 
                              OSGArg2T,
                              OSGObjectT *,
                              OSGOnStoredObject> OSGOFunctor;

    OSGOFunctor returnValue;

    returnValue.setMethod(pFunc);    
    returnValue.setCalledObject(pObj);

    return returnValue;
} 


template <class OSGRetT, class OSGArg1T, class OSGArg2T> inline
OSGObjectFunctor2<OSGRetT, 
                  OSGArg1T &, 
                  OSGArg2T, 
                  OSGArg1T,
                  OSGOnCPtrArgument> osgMethodFunctor2CPtr(
    typename OSGFunctorBuildFuncType2<OSGRetT, 
                                      OSGArg2T,
                                      OSGArg1T>::OSGFunctionType pFunc)
{
    typedef OSGObjectFunctor2<OSGRetT, 
                              OSGArg1T &, 
                              OSGArg2T,
                              OSGArg1T,
                              OSGOnCPtrArgument> OSGOFunctor;

    OSGOFunctor returnValue;

    returnValue.setMethod(pFunc);    
   
    return returnValue;
} 

#ifdef __sgi
#pragma set woff 1424
#endif

template <class OSGRetT,    class OSGArg1T, 
          class OSGObjectT, class OSGArg2T> inline
OSGObjectFunctor2<OSGRetT, 
                  OSGArg1T &, 
                  OSGArg2T, 
                  OSGObjectT,
                  OSGOnCPtrArgument> osgMethodFunctor2BaseCPtr(
    typename OSGFunctorBuildFuncType2<OSGRetT, 
                                      OSGArg2T,
                                      OSGObjectT>::OSGFunctionType pFunc)
{
    typedef OSGObjectFunctor2<OSGRetT, 
                              OSGArg1T &, 
                              OSGArg2T,
                              OSGObjectT,
                              OSGOnCPtrArgument> OSGOFunctor;

    OSGOFunctor returnValue;

    returnValue.setMethod(pFunc);    
   
    return returnValue;
} 

#ifdef __sgi
#pragma reset woff 1424
#endif

template <class OSGRetT,  class OSGArg1T, 
          class OSGArg2T, class OSGObjectT> inline
OSGObjectFunctor2<OSGRetT, 
                  OSGArg1T, 
                  OSGArg2T,
                  OSGObjectT &,
                  OSGOnStoredCPtr> osgMethodFunctor2CPtr(
    OSGObjectT &obj,
    typename OSGFunctorBuildFuncType3<OSGRetT, 
                                      OSGArg1T, 
                                      OSGArg2T, 
                                      OSGObjectT>::OSGFunctionType pFunc)
{
    typedef OSGObjectFunctor2<OSGRetT, 
                              OSGArg1T, 
                              OSGArg2T,
                              OSGObjectT &,
                              OSGOnStoredCPtr> OSGOFunctor;

    OSGOFunctor returnValue;

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
