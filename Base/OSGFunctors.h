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

#ifndef _OSGFUNCTORS_H_
#define _OSGFUNCTORS_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>
#include <OSGLog.h>

OSG_BEGIN_NAMESPACE

/*! \ingroup BaseLib
 *  \brief FunctorBase
 */

struct DefaultFunctorSizeTraits
{
    typedef void (*FuncPointerT)(void *);
    typedef void (DefaultFunctorSizeTraits::*InstanceFuncPointerT)(void *);

    enum SizesE
    { 
        _uiFuncPointerSize = 
            osgStaticMax<sizeof(FuncPointerT),
                         sizeof(InstanceFuncPointerT) >::iMax,

        _uiObjectSize      = 64
    };
};

enum FunctorMethodCallTypeE
{
    OnArgument,
    OnStoredObject,
    
    OnStoredCPtr,
    OnCPtrArgument
};

template <class RetT, class ObjectTypeT>
struct FunctorBuildFuncType1
{
    typedef typename ObjectTypeT::ObjectType ObjectType;

    typedef RetT (ObjectType::*FunctionType)();
};

template <class RetT, class Arg1T, class ObjectTypeT>
struct FunctorBuildFuncType2
{
    typedef typename ObjectTypeT::ObjectType ObjectType;

    typedef          RetT (ObjectType::*FunctionType)(Arg1T);
};

template <class RetT, class Arg1T, class Arg2T, class ObjectTypeT>
struct FunctorBuildFuncType3
{
    typedef typename ObjectTypeT::ObjectType ObjectType;

    typedef RetT (ObjectType::*FunctionType)(Arg1T, Arg2T);
};

template <class SizeTraitsT = DefaultFunctorSizeTraits>
class FunctorBase 
{     
    /*==========================  PRIVATE  ================================*/
  private:

	static char cvsid[];

    /*==========================  PRIVATE  ================================*/
  protected:

    static const UInt8 ObjectValid;
    static const UInt8 FuncPtrValid;

    static const UInt8 FunctorActive;

    char     _data1[SizeTraitsT::_uiObjectSize];
    char     _data2[SizeTraitsT::_uiFuncPointerSize];
    UInt8 _flags;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    FunctorBase(void);
    FunctorBase(const FunctorBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Operators                                  */
    /*! \{                                                                 */

    void operator =(const FunctorBase &source);

    /*! \}                                                                 */    
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FunctorBase(void); 
    /*! \}                                                                 */      
};

/*! \ingroup BaseLib
 *  \brief Brief
 */

template <class RetT, 
          class Arg1T, 
          class SizeTraitsT = DefaultFunctorSizeTraits>
class Functor1Base : public FunctorBase<SizeTraitsT>
{
    /*==========================  PRIVATE  ================================*/
  private:

    typedef FunctorBase<SizeTraitsT> Inherited;

	static char cvsid[];
    
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Functor1Base(void);
    Functor1Base(const Functor1Base &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
    
    virtual ~Functor1Base(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    virtual RetT call(Arg1T arg1);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Operators                                  */
    /*! \{                                                                 */    

    void operator =(const Functor1Base &source);
    
    /*! \}                                                                 */
};

/*! \ingroup BaseLib
 *  \brief Brief
 */

template <class Arg1T, 
          class SizeTraitsT>
class Functor1Base<void, Arg1T, SizeTraitsT> : 
    public FunctorBase<SizeTraitsT>
{
    /*==========================  PRIVATE  ================================*/    
  private:

    typedef FunctorBase<SizeTraitsT> Inherited;

	static char cvsid[];
    
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
          
    Functor1Base(void);
    Functor1Base(const Functor1Base &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
    
    virtual ~Functor1Base(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */
    
    virtual void call(Arg1T arg1);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Operators                                  */
    /*! \{                                                                 */    
    
    void operator =(const Functor1Base &source);
    
    /*! \}                                                                 */    
};

/*! \ingroup BaseLib
 *  \brief Brief
 */

template <class RetT, 
          class Arg1T,
          class SizeTraitsT = DefaultFunctorSizeTraits>
class FunctionFunctor1 : 
    public Functor1Base<RetT, Arg1T, SizeTraitsT>
{
    /*==========================  PUBLIC  =================================*/    
  public:

    typedef RetT (*FunctionP)(Arg1T);
  
    /*==========================  PRIVATE  ================================*/    
  private:

    typedef Functor1Base<RetT, Arg1T, SizeTraitsT> Inherited;

	static char cvsid[];
    
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Operators                                  */
    /*! \{                                                                 */
          
    void operator =(const FunctionFunctor1 &source);
  
    /*! \}                                                                 */  
    /*==========================  PUBLIC  =================================*/    
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    FunctionFunctor1(void);
    FunctionFunctor1(const FunctionFunctor1 &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
    
    virtual ~FunctionFunctor1(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Access                                     */
    /*! \{                                                                 */

    void setFunction(FunctionP pFunc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    virtual RetT call(Arg1T arg1);
    
    /*! \}                                                                 */    
};

/*! \ingroup BaseLib
 *  \brief Brief
 */

template <class Arg1T,
          class SizeTraitsT>
class FunctionFunctor1<void, Arg1T, SizeTraitsT> : 
    public Functor1Base<void, Arg1T, SizeTraitsT>
{
    /*==========================  PUBLIC  =================================*/        
  public:

    typedef void (*FunctionP)(Arg1T);
  
    /*==========================  PRIVATE  ================================*/    
  private:

    typedef Functor1Base<void, Arg1T, SizeTraitsT> Inherited;

	static char cvsid[];

    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Operators                                  */
    /*! \{                                                                 */

    void operator =(const FunctionFunctor1 &source);

    /*! \}                                                                 */  
    /*==========================  PUBLIC  =================================*/    
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    FunctionFunctor1(void);
    FunctionFunctor1(const FunctionFunctor1 &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
    
    virtual ~FunctionFunctor1(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Access                                     */
    /*! \{                                                                 */

    void setFunction(FunctionP pFunc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    virtual void call(Arg1T arg1);
    /*! \}                                                                 */    
};


template <class RetT, 
          class Arg1T,
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType>
struct FunctorTraits1
{
};


template <class RetT, 
          class Arg1T,
          class ObjectT>
struct FunctorTraits1<RetT,
                      Arg1T *, 
                      ObjectT, 
                      OnArgument>
{
    typedef RetT (ObjectT::*ObjectMethodT   )(void);
    typedef RetT (ObjectT::*ObjectMethodPtrT)(Arg1T);

    typedef ObjectT &SetObjectT;

    static void setCalledObject(char *pData, SetObjectT obj)
    {
        *((ObjectT *) pData) = obj;
    }

    static RetT callObjectMethod(char *pData2, Arg1T *arg1)
    {
        ObjectMethodT pFunc = *((ObjectMethodT *) pData2);

        return ((arg1)->*pFunc)();
    }

#ifdef __sgi
#pragma set woff 1551 
#endif

    static RetT callObjectMethod(char *, char *, Arg1T *)
    {
        RetT returnValue;

        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

#ifdef __sgi
#pragma reset woff 1551 
#endif

    static void callObjectMethodVoid(char *pData2, Arg1T *arg1)
    {
        ObjectMethodT pFunc = *((ObjectMethodT *) pData2);

        ((arg1)->*pFunc)();
    }

    static void callObjectMethodVoid(char     *, 
                                     char     *, 
                                     Arg1T *)
    {
        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }
};

template <class RetT, 
          class Arg1T,
          class ObjectT>
struct FunctorTraits1<RetT,
                      Arg1T &, 
                      ObjectT, 
                      OnArgument>
{
    typedef RetT (ObjectT::*ObjectMethodT   )(void);
    typedef RetT (ObjectT::*ObjectMethodPtrT)(Arg1T);

    typedef ObjectT &SetObjectT;

    static void setCalledObject(char *pData, SetObjectT obj)
    {
        *((ObjectT *) pData) = obj;
    }

    static RetT callObjectMethod(char *pData2, Arg1T &arg1)
    {
        ObjectMethodT pFunc = *((ObjectMethodT *) pData2);

        return ((&arg1)->*pFunc)();
    }

#ifdef __sgi
#pragma set woff 1551 
#endif

    static RetT callObjectMethod(char *, char *, Arg1T &)
    {
        RetT returnValue;

        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

#ifdef __sgi
#pragma reset woff 1551 
#endif

    static void callObjectMethodVoid(char *pData2, Arg1T &arg1)
    {
        ObjectMethodT pFunc = *((ObjectMethodT *) pData2);

        ((&arg1)->*pFunc)();
    }

    static void callObjectMethodVoid(char     *, 
                                     char     *, 
                                     Arg1T &)
    {

        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }
};

template <class RetT, 
          class Arg1T,
          class ObjectT>
struct FunctorTraits1<RetT, Arg1T &, ObjectT, OnCPtrArgument>
{
    typedef typename ObjectT::ObjectType ObjectType;

    typedef          RetT (ObjectType::*ObjectMethodT   )(void);
    typedef          RetT (ObjectType::*ObjectMethodPtrT)(Arg1T);

    typedef ObjectT &SetObjectT;

    static void setCalledObject(char *pData, SetObjectT obj)
    {
        *((ObjectT *) pData) = obj;
    }

    static RetT callObjectMethod(char *pData2, Arg1T &arg1)
    {
        ObjectMethodT pFunc = *((ObjectMethodT *) pData2);

        return ((&(*arg1))->*pFunc)();
    }

#ifdef __sgi
#pragma set woff 1551 
#endif

    static RetT callObjectMethod(char *, char *, Arg1T &)
    {
        RetT returnValue;

        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

#ifdef __sgi
#pragma reset woff 1551 
#endif

    static void callObjectMethodVoid(char *pData2, Arg1T &arg1)
    {
        ObjectMethodT pFunc = *((ObjectMethodT *) pData2);

        ((&(*arg1))->*pFunc)();
    }

    static void callObjectMethodVoid(char     *,
                                     char     *, 
                                     Arg1T &)
    {
        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }
};

template <class RetT, 
          class Arg1T,
          class ObjectT>
struct FunctorTraits1<RetT, Arg1T, ObjectT &, OnStoredCPtr>
{
    typedef typename ObjectT::ObjectType ObjectType;

    typedef          RetT (ObjectType::*ObjectMethodT   )(void);
    typedef          RetT (ObjectType::*ObjectMethodPtrT)(Arg1T);

    typedef ObjectT &SetObjectT;

    static void setCalledObject(char *pData, SetObjectT obj)
    {
        *((ObjectT *) pData) = obj;
    }

#ifdef __sgi
#pragma set woff 1551 
#endif

    static RetT callObjectMethod(char *, Arg1T)
    {
        RetT returnValue;

        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

#ifdef __sgi
#pragma reset woff 1551 
#endif

    static RetT callObjectMethod(char *pData1, char *pData2, Arg1T arg1)
    {
        ObjectT *pObj = ((ObjectT *) pData1);
        
        ObjectMethodPtrT pFunc = *((ObjectMethodPtrT *) pData2);
        
        return (&(**pObj)->*pFunc)(arg1);
    }

    static void callObjectMethodVoid(char *, Arg1T)
    {
        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }

    static void callObjectMethodVoid(char *pData1, char *pData2, Arg1T arg1)
    {
        ObjectT *pObj = ((ObjectT *) pData1);
        
        ObjectMethodPtrT pFunc = *((ObjectMethodPtrT *) pData2);
        
        (&(**pObj)->*pFunc)(arg1);
    }
};

template <class RetT, 
          class Arg1T,
          class ObjectT>
struct FunctorTraits1<RetT, Arg1T &, ObjectT *, OnArgument>
{
    typedef RetT (ObjectT::*ObjectMethodT   )(void);
    typedef RetT (ObjectT::*ObjectMethodPtrT)(Arg1T);

    typedef ObjectT *SetObjectT;

    static void setCalledObject(char *pData, SetObjectT obj)
    {
        *((ObjectT **) pData) = obj;
    }

    static RetT callObjectMethod(char *pData2, Arg1T arg1)
    {
        ObjectMethodT pFunc = *((ObjectMethodT *) _data2);

        return ((&arg1)->*pFunc)();
    }

    static RetT callObjectMethod(char *pData1, char *pData2, Arg1T arg1)
    {
        RetT returnValue;

        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

    static void callObjectMethodVoid(char *pData2, Arg1T arg1)
    {
        ObjectMethodT pFunc = *((ObjectMethodT *) _data2);

        ((&arg1)->*pFunc)();
    }

    static void callObjectMethodVoid(char *pData1, char *pData2, Arg1T arg1)
    {
        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }
};

template <class RetT, 
          class Arg1T,
          class ObjectT>
struct FunctorTraits1<RetT, Arg1T *, ObjectT *, OnArgument>
{
    typedef RetT (ObjectT::*ObjectMethodT   )(void);
    typedef RetT (ObjectT::*ObjectMethodPtrT)(Arg1T);

    typedef ObjectT *SetObjectT;

    static void setCalledObject(char *pData, SetObjectT obj)
    {
        *((ObjectT **) pData) = obj;
    }

    static RetT callObjectMethod(char *pData2, Arg1T arg1)
    {
        ObjectMethodT pFunc = *((ObjectMethodT *) _data2);

        return ((arg1)->*pFunc)();
    }

    static RetT callObjectMethod(char *pData1, char *pData2, Arg1T arg1)
    {
        RetT returnValue;

        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

    static void callObjectMethodVoid(char *pData2, Arg1T arg1)
    {
        ObjectMethodT pFunc = *((ObjectMethodT *) _data2);

        ((arg1)->*pFunc)();
    }

    static void callObjectMethodVoid(char *pData1, char *pData2, Arg1T arg1)
    {
        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }
};

template <class RetT, 
          class Arg1T,
          class ObjectT>
struct FunctorTraits1<RetT, Arg1T, ObjectT *, OnStoredObject>
{
    typedef RetT (ObjectT::*ObjectMethodT   )(void);
    typedef RetT (ObjectT::*ObjectMethodPtrT)(Arg1T);

    typedef ObjectT *SetObjectT;

    static void setCalledObject(char *pData, SetObjectT obj)
    {
        *((ObjectT **) pData) = obj;
    }

#ifdef __sgi
#pragma set woff 1551 
#endif

    static RetT callObjectMethod(char *, Arg1T)
    {
        RetT returnValue;

        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

#ifdef __sgi
#pragma reset woff 1551 
#endif

    static RetT callObjectMethod(char *pData1, char *pData2, Arg1T arg1)
    {
        ObjectT *pObj = *((ObjectT **) pData1);

        ObjectMethodPtrT pFunc = *((ObjectMethodPtrT *) pData2);
            
        return (pObj->*pFunc)(arg1);
    }


    static void callObjectMethodVoid(char *, Arg1T)
    {
        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }

    static void callObjectMethodVoid(char *pData1, char *pData2, Arg1T arg1)
    {
        ObjectT *pObj = *((ObjectT **) pData1);

        ObjectMethodPtrT pFunc = *((ObjectMethodPtrT *) pData2);
            
        (pObj->*pFunc)(arg1);
    }
};

template <class RetT, 
          class Arg1T,
          class ObjectT>
struct FunctorTraits1<RetT, Arg1T &, ObjectT &, OnArgument>
{
    typedef RetT (ObjectT::*ObjectMethodT   )(void);
    typedef RetT (ObjectT::*ObjectMethodPtrT)(Arg1T);

    typedef ObjectT &SetObjectT;

    static void setCalledObject(char *pData, SetObjectT obj)
    {
        *((ObjectT *) pData) = obj;
    }

    static RetT callObjectMethod(char *pData2, Arg1T arg1)
    {
        ObjectMethodT pFunc = *((ObjectMethodT *) _data2);

        return ((&arg1)->*pFunc)();
    }

    static RetT callObjectMethod(char *pData1, char *pData2, Arg1T arg1)
    {
        RetT returnValue;

        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

    static void callObjectMethodVoid(char *pData2, Arg1T arg1)
    {
        ObjectMethodT pFunc = *((ObjectMethodT *) _data2);

        ((&arg1)->*pFunc)();
    }

    static void callObjectMethodVoid(char *pData1, char *pData2, Arg1T arg1)
    {
        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }
};

template <class RetT, 
          class Arg1T,
          class ObjectT>
struct FunctorTraits1<RetT, Arg1T *, ObjectT &, OnArgument>
{
    typedef RetT (ObjectT::*ObjectMethodT   )(void);
    typedef RetT (ObjectT::*ObjectMethodPtrT)(Arg1T);

    typedef ObjectT &SetObjectT;

    static void setCalledObject(char *pData, SetObjectT obj)
    {
        *((ObjectT *) pData) = obj;
    }

    static RetT callObjectMethod(char *pData2, Arg1T arg1)
    {
        ObjectMethodT pFunc = *((ObjectMethodT *) _data2);

        return ((arg1)->*pFunc)();
    }

    static RetT callObjectMethod(char *pData1, char *pData2, Arg1T arg1)
    {
        RetT returnValue;

        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

    static void callObjectMethodVoid(char *pData2, Arg1T arg1)
    {
        ObjectMethodT pFunc = *((ObjectMethodT *) _data2);

        ((arg1)->*pFunc)();
    }

    static void callObjectMethodVoid(char *pData1, char *pData2, Arg1T arg1)
    {
        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }
};

template <class RetT, 
          class Arg1T,
          class ObjectT>
struct FunctorTraits1<RetT, Arg1T, ObjectT &, OnStoredObject>
{
    typedef RetT (ObjectT::*ObjectMethodT   )(void);
    typedef RetT (ObjectT::*ObjectMethodPtrT)(Arg1T);

    typedef ObjectT &SetObjectT;

    static void setCalledObject(char *pData, SetObjectT obj)
    {
        *((ObjectT *) pData) = obj;
    }

#ifdef __sgi
#pragma set woff 1551 
#endif

    static RetT callObjectMethod(char *, Arg1T)
    {
        RetT returnValue;

        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

#ifdef __sgi
#pragma reset woff 1551 
#endif

    static RetT callObjectMethod(char *pData1, char *pData2, Arg1T arg1)
    {
        ObjectT *pObj = ((ObjectT *) pData1);

        ObjectMethodPtrT pFunc = *((ObjectMethodPtrT *) pData2);
            
        return (pObj->*pFunc)(arg1);
    }

    static void callObjectMethodVoid(char *, Arg1T)
    {
        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }

    static void callObjectMethodVoid(char *pData1, char *pData2, Arg1T arg1)
    {
        ObjectT *pObj = ((ObjectT *) pData1);

        ObjectMethodPtrT pFunc = *((ObjectMethodPtrT *) pData2);
        
        (pObj->*pFunc)(arg1);
    }
};

/*! \ingroup BaseLib
 *  \brief Brief
 */

template <class RetT, 
          class Arg1T,
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT = DefaultFunctorSizeTraits>
class ObjectFunctor1 : 
    public Functor1Base<RetT, Arg1T, SizeTraitsT>
{
    /*==========================  PUBLIC  =================================*/    
  public:

    typedef
        FunctorTraits1<RetT,
                       Arg1T, 
                       ObjectT, 
                       MethodCallType> FunctorTrait;

    typedef typename FunctorTrait::ObjectMethodT    ObjectMethodT;
    typedef typename FunctorTrait::ObjectMethodPtrT ObjectMethodPtrT;
    typedef typename FunctorTrait::SetObjectT       SetObjectT;

    /*==========================  PRIVATE  ================================*/
  private:

    typedef Functor1Base<RetT, Arg1T, SizeTraitsT> Inherited;

	static char cvsid[];

    /*=========================  PROTECTED  ===============================*/
  protected:
          
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    void operator =(const ObjectFunctor1 &source);
  
    /*! \}                                                                 */
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ObjectFunctor1(void);
    ObjectFunctor1(const ObjectFunctor1 &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
    
    virtual ~ObjectFunctor1(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void setMethod         (ObjectMethodT     pFunc);

    void setMethod         (ObjectMethodPtrT  pFunc);

    void setCalledObject   (SetObjectT        pObj);

    void setObjectAndMethod(SetObjectT        pObj, 
                            ObjectMethodPtrT  pFunc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */
    
    virtual RetT    call(Arg1T             arg1);
    
    /*! \}                                                                 */
};

/*! \ingroup BaseLib
 *  \brief Brief
 */

template <class Arg1T,
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT>
class ObjectFunctor1<void, 
                     Arg1T, 
                     ObjectT, 
                     MethodCallType,
                      SizeTraitsT> : 
    public Functor1Base<void, Arg1T, SizeTraitsT>
{
    /*==========================  PUBLIC  =================================*/        
  public:

    typedef
        FunctorTraits1<void,
                       Arg1T, 
                       ObjectT, 
                       MethodCallType> FunctorTrait;

    typedef typename FunctorTrait::ObjectMethodT    ObjectMethodT;
    typedef typename FunctorTrait::ObjectMethodPtrT ObjectMethodPtrT;
    typedef typename FunctorTrait::SetObjectT       SetObjectT;
    
    /*==========================  PRIVATE  ================================*/
  private:

    typedef Functor1Base<void, Arg1T, SizeTraitsT> Inherited;

	static char cvsid[];

    /*=========================  PROTECTED  ===============================*/    
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */
          
    void operator =(const ObjectFunctor1 &source);

    /*! \}                                                                 */
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ObjectFunctor1(void);
    ObjectFunctor1(const ObjectFunctor1 &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
    
    virtual ~ObjectFunctor1(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void setMethod         (ObjectMethodT     pFunc);

    void setMethod         (ObjectMethodPtrT  pFunc);

    void setCalledObject   (SetObjectT        pObj);

    void setObjectAndMethod(SetObjectT        pObj, 
                            ObjectMethodPtrT  pFunc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */
    
    virtual void    call(Arg1T             arg1);
    
    /*! \}                                                                 */    
};


template <class RetT, class Arg1T> inline
FunctionFunctor1<RetT, Arg1T> osgFunctionFunctor1( 
    RetT (*pFunc)(Arg1T));

template <class RetT, class Arg1T> inline
ObjectFunctor1<RetT, 
               Arg1T &, 
               Arg1T,
               OnArgument> osgMethodFunctor1Ref(
    RetT (Arg1T::*pFunc)());


template <class RetT, class Arg1T, class ObjectT> inline
ObjectFunctor1<RetT, 
               Arg1T, 
               ObjectT &,
               OnStoredObject> osgMethodFunctorRef(
    ObjectT &obj, RetT (ObjectT::*pFunc)(Arg1T));


template <class RetT, class Arg1T> inline
ObjectFunctor1<RetT, 
               Arg1T *, 
               Arg1T,
               OnArgument> osgMethodFunctor1Ptr(
    RetT (Arg1T::*pFunc)());


template <class RetT, class Arg1T, class ObjectT> inline
ObjectFunctor1<RetT, 
               Arg1T, 
               ObjectT *,
               OnStoredObject> osgMethodFunctor1Ptr(
    ObjectT *pObj, RetT (ObjectT::*pFunc)(Arg1T));

template <class RetT, class Arg1T> inline
ObjectFunctor1<RetT, 
               Arg1T &, 
               Arg1T,
               OnCPtrArgument> osgMethodFunctor1CPtr(
   typename FunctorBuildFuncType1<RetT, 
                                  Arg1T>::FunctionType pFunc);

template <class RetT, class Arg1T, class ObjectT> inline
ObjectFunctor1<RetT, 
               Arg1T, 
               ObjectT &,
               OnStoredCPtr> osgMethodFunctor1CPtr(
    ObjectT &obj, 
    typename FunctorBuildFuncType2<RetT, 
                                   Arg1T, 
                                   ObjectT>::FunctionType pFunc);


/*! \ingroup BaseLib
 *  \brief Brief
 */

template <class RetT, 
          class Arg1T, 
          class Arg2T,
          class SizeTraitsT = DefaultFunctorSizeTraits>
class Functor2Base : public FunctorBase<SizeTraitsT>
{
    /*==========================  PRIVATE  ================================*/
  private:

    typedef FunctorBase<SizeTraitsT> Inherited;

	static char cvsid[];
    
    /*==========================  PUBLIC  =================================*/    
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Functor2Base(void);
    Functor2Base(const Functor2Base &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
    
    virtual ~Functor2Base(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    virtual RetT call(Arg1T arg1, Arg2T arg2);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Operators                                  */
    /*! \{                                                                 */
    
    void operator =(const Functor2Base &source);
    
    /*! \}                                                                 */
};

/*! \ingroup BaseLib
 *  \brief Brief
 */

template <class Arg1T, 
          class Arg2T,
          class SizeTraitsT>
class Functor2Base<void, Arg1T, Arg2T, SizeTraitsT> : 
    public FunctorBase<SizeTraitsT>
{
    /*==========================  PRIVATE  ================================*/    
  private:

    typedef FunctorBase<SizeTraitsT> Inherited;

	static char cvsid[];
    
    /*==========================  PUBLIC  =================================*/    
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Functor2Base(void);
    Functor2Base(const Functor2Base &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
    
    virtual ~Functor2Base(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    virtual void call(Arg1T arg1, Arg2T);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Operators                                  */
    /*! \{                                                                 */
    
    void operator =(const Functor2Base &source);
    
    /*! \}                                                                 */    
};

/*! \ingroup BaseLib
 *  \brief Brief
 */

template <class RetT, 
          class Arg1T,
          class Arg2T,
          class SizeTraitsT = DefaultFunctorSizeTraits>
class FunctionFunctor2 : 
    public Functor2Base<RetT, Arg1T, Arg2T, SizeTraitsT>
{
    /*==========================  PUBLIC  =================================*/        
  public:

    typedef RetT (*FunctionP)(Arg1T, Arg2T);
  
    /*==========================  PRIVATE  ================================*/    
  private:

    typedef Functor2Base<RetT, 
                         Arg1T, 
                         Arg2T,
                         SizeTraitsT> Inherited;

	static char cvsid[];

    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Operators                                  */
    /*! \{                                                                 */

    void operator =(const FunctionFunctor2 &source);

    /*! \}                                                                 */    
    /*==========================  PUBLIC  =================================*/    
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    FunctionFunctor2(void);
    FunctionFunctor2(const FunctionFunctor2 &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
    
    virtual ~FunctionFunctor2(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Access                                     */
    /*! \{                                                                 */

    void setFunction(FunctionP pFunc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    virtual RetT call(Arg1T arg1, Arg2T arg2);
    
    /*! \}                                                                 */    
};

/*! \ingroup BaseLib
 *  \brief Brief
 */

template <class Arg1T,
          class Arg2T,
          class SizeTraitsT>
class FunctionFunctor2<void, Arg1T, Arg2T, SizeTraitsT> : 
    public Functor2Base<void, Arg1T, Arg2T, SizeTraitsT>
{
    /*==========================  PUBLIC  =================================*/            
  public:

    typedef void (*FunctionP)(Arg1T, Arg2T);

    /*==========================  PRIVATE  ================================*/      
  private:

    typedef Functor2Base<void, 
                         Arg1T, 
                         Arg2T, 
                         SizeTraitsT> Inherited;

	static char cvsid[];
    
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Operators                                  */
    /*! \{                                                                 */

    void operator =(const FunctionFunctor2 &source);
  
    /*! \}                                                                 */    
    /*==========================  PUBLIC  =================================*/    
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    FunctionFunctor2(void);
    FunctionFunctor2(const FunctionFunctor2 &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
    
    virtual ~FunctionFunctor2(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Access                                     */
    /*! \{                                                                 */

    void setFunction(FunctionP pFunc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */
    
    virtual void call(Arg1T arg1, Arg2T arg2);
    
    /*! \}                                                                 */    
};

template <class RetT, 
          class Arg1T,
          class Arg2T,
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType>
struct FunctorTraits2
{
};


template <class RetT, 
          class Arg1T,
          class Arg2T,
          class ObjectT>
struct FunctorTraits2<RetT,
                      Arg1T *, 
                      Arg2T,
                      ObjectT, 
                      OnArgument>
{
    typedef RetT (ObjectT::*ObjectMethodT   )(Arg2T);
    typedef RetT (ObjectT::*ObjectMethodPtrT)(Arg1T, Arg2T);

    typedef ObjectT &SetObjectT;

    static void setCalledObject(char *pData, SetObjectT obj)
    {
        *((ObjectT *) pData) = obj;
    }

    static RetT callObjectMethod(char *pData2, 
                                 Arg1T *arg1, 
                                 Arg2T  arg2)
    {
        ObjectMethodT pFunc = *((ObjectMethodT *) pData2);

        return ((arg1)->*pFunc)(arg2);
    }

#ifdef __sgi
#pragma set woff 1551 
#endif

    static RetT callObjectMethod(char     *, 
                                 char     *, 
                                 Arg1T *,
                                 Arg2T  )
    {
        RetT returnValue;

        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

#ifdef __sgi
#pragma reset woff 1551 
#endif

    static void callObjectMethodVoid(char     *pData2, 
                                     Arg1T *arg1,
                                     Arg2T  arg2)
    {
        ObjectMethodT pFunc = *((ObjectMethodT *) pData2);

        ((arg1)->*pFunc)(arg2);
    }

    static void callObjectMethodVoid(char     *, 
                                     char     *, 
                                     Arg1T *,
                                     Arg2T)
    {
        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }
};

template <class RetT, 
          class Arg1T,
          class Arg2T,
          class ObjectT>
struct FunctorTraits2<RetT,
                      Arg1T &, 
                      Arg2T,
                      ObjectT, 
                      OnArgument>
{
    typedef RetT (ObjectT::*ObjectMethodT   )(Arg2T);
    typedef RetT (ObjectT::*ObjectMethodPtrT)(Arg1T, Arg2T);

    typedef ObjectT &SetObjectT;

    static void setCalledObject(char *pData, SetObjectT obj)
    {
        *((ObjectT *) pData) = obj;
    }

    static RetT callObjectMethod(char     *pData2, 
                                    Arg1T &arg1,
                                    Arg2T  arg2)
    {
        ObjectMethodT pFunc = *((ObjectMethodT *) pData2);

        return ((&arg1)->*pFunc)(arg2);
    }

#ifdef __sgi
#pragma set woff 1551 
#endif

    static RetT callObjectMethod(char     *, 
                                 char     *, 
                                 Arg1T &,
                                 Arg2T)
    {
        RetT returnValue;

        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

#ifdef __sgi
#pragma reset woff 1551 
#endif

    static void callObjectMethodVoid(char  *pData2, 
                                     Arg1T &arg1,
                                     Arg2T  arg2)
    {
        ObjectMethodT pFunc = *((ObjectMethodT *) pData2);

        ((&arg1)->*pFunc)(arg2);
    }

    static void callObjectMethodVoid(char  *, 
                                     char  *, 
                                     Arg1T &,
                                     Arg2T)
    {

        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }
};

template <class RetT, 
          class Arg1T,
          class Arg2T,
          class ObjectT>
struct FunctorTraits2<RetT,    
                      Arg1T &,      
                      Arg2T,
                      ObjectT, 
                      OnCPtrArgument>
{
    typedef typename ObjectT::ObjectType ObjectType;

    typedef          RetT (ObjectType::*ObjectMethodT   )(Arg2T);
    typedef          RetT (ObjectType::*ObjectMethodPtrT)(Arg1T,
                                                          Arg2T);

    typedef ObjectT &SetObjectT;

    static void setCalledObject(char *pData, SetObjectT obj)
    {
        *((ObjectT *) pData) = obj;
    }

    static RetT callObjectMethod(char     *pData2, 
                                 Arg1T &arg1,
                                 Arg2T  arg2)
    {
        ObjectMethodT pFunc = *((ObjectMethodT *) pData2);
        typedef typename ObjectT::ObjectType ObjectType;

        return (((ObjectType *)(&(*arg1)))->*pFunc)(arg2);
    }

#ifdef __sgi
#pragma set woff 1551 
#endif

    static RetT callObjectMethod(char  *, 
                                 char  *, 
                                 Arg1T &,
                                 Arg2T)
    {
        RetT returnValue;

        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

#ifdef __sgi
#pragma reset woff 1551 
#endif

    static void callObjectMethodVoid(char  *pData2, 
                                     Arg1T &arg1,
                                     Arg2T  arg2)
    {
        ObjectMethodT pFunc = *((ObjectMethodT *) pData2);

        ((&(*arg1))->*pFunc)(arg2);
    }

    static void callObjectMethodVoid(char     *,
                                     char     *, 
                                     Arg1T &,
                                     Arg2T)
    {
        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }
};

template <class RetT, 
          class Arg1T,
          class Arg2T,
          class ObjectT>
struct FunctorTraits2<RetT, 
                      Arg1T, 
                      Arg2T,  
                      ObjectT &, 
                      OnStoredCPtr>
{
    typedef typename ObjectT::ObjectType ObjectType;
    typedef          RetT (ObjectType::*ObjectMethodT   )(Arg2T);
    typedef          RetT (ObjectType::*ObjectMethodPtrT)(Arg1T,
                                                          Arg2T);

    typedef ObjectT &SetObjectT;

    static void setCalledObject(char *pData, SetObjectT obj)
    {
        *((ObjectT *) pData) = obj;
    }

#ifdef __sgi
#pragma set woff 1551 
#endif

    static RetT callObjectMethod(char  *, 
                                 Arg1T  ,
                                 Arg2T  )
    {
        RetT returnValue;

        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

#ifdef __sgi
#pragma reset woff 1551 
#endif

    static RetT callObjectMethod(char  *pData1, 
                                 char  *pData2, 
                                 Arg1T  arg1,
                                 Arg2T  arg2)
    {
        ObjectT *pObj = ((ObjectT *) pData1);
        
        ObjectMethodPtrT pFunc = *((ObjectMethodPtrT *) pData2);
        
        return (&(**pObj)->*pFunc)(arg1, arg2);
    }

    static void callObjectMethodVoid(char     *, 
                                     Arg1T  ,
                                     Arg2T)
    {
        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }

    static void callObjectMethodVoid(char *pData1, 
                                     char *pData2, 
                                     Arg1T arg1,
                                     Arg2T arg2)
    {
        ObjectT *pObj = ((ObjectT *) pData1);
        
        ObjectMethodPtrT pFunc = *((ObjectMethodPtrT *) pData2);
        
        (&(**pObj)->*pFunc)(arg1, arg2);
    }
};

template <class RetT, 
          class Arg1T,
          class Arg2T, 
          class ObjectT>
struct FunctorTraits2<RetT, 
                      Arg1T &, 
                      Arg2T, 
                      ObjectT *, 
                      OnArgument>
{
    typedef RetT (ObjectT::*ObjectMethodT   )(Arg2T);
    typedef RetT (ObjectT::*ObjectMethodPtrT)(Arg1T, Arg2T);

    typedef ObjectT *SetObjectT;

    static void setCalledObject(char *pData, SetObjectT obj)
    {
        *((ObjectT **) pData) = obj;
    }

    static RetT callObjectMethod(char *pData2, Arg1T arg1, Arg2T arg2)
    {
        ObjectMethodT pFunc = *((ObjectMethodT *) _data2);

        return ((&arg1)->*pFunc)();
    }

    static RetT callObjectMethod(char  *, 
                                 char  *, 
                                 Arg1T  ,
                                 Arg2T )
    {
        RetT returnValue;

        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

    static void callObjectMethodVoid(char     *pData2, 
                                     Arg1T  arg1,
                                     Arg2T  arg2)
    {
        ObjectMethodT pFunc = *((ObjectMethodT *) _data2);

        ((&arg1)->*pFunc)(arg2);
    }

    static void callObjectMethodVoid(char     *, 
                                     char     *, 
                                     Arg1T  ,
                                     Arg2T)
    {
        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }
};

template <class RetT, 
          class Arg1T,
          class Arg2T,
          class ObjectT>
struct FunctorTraits2<RetT, 
                      Arg1T *, 
                      Arg2T, 
                      ObjectT *, 
                      OnArgument>
{
    typedef RetT (ObjectT::*ObjectMethodT   )(Arg2T);
    typedef RetT (ObjectT::*ObjectMethodPtrT)(Arg1T, Arg2T);

    typedef ObjectT *SetObjectT;

    static void setCalledObject(char *pData, SetObjectT obj)
    {
        *((ObjectT **) pData) = obj;
    }

    static RetT callObjectMethod(char *pData2, Arg1T arg1, Arg2T arg2)
    {
        ObjectMethodT pFunc = *((ObjectMethodT *) _data2);

        return ((arg1)->*pFunc)(arg2);
    }

    static RetT callObjectMethod(char  *, 
                                 char  *, 
                                 Arg1T  ,
                                 Arg2T )
    {
        RetT returnValue;

        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

    static void callObjectMethodVoid(char  *pData2, 
                                     Arg1T  arg1,
                                     Arg2T  arg2)
    {
        ObjectMethodT pFunc = *((ObjectMethodT *) _data2);

        ((arg1)->*pFunc)(arg2);
    }

    static void callObjectMethodVoid(char  *, 
                                     char  *, 
                                     Arg1T  ,
                                     Arg2T)
    {
        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }
};

template <class RetT, 
          class Arg1T,
          class Arg2T,
          class ObjectT>
struct FunctorTraits2<RetT, 
                      Arg1T, 
                      Arg2T, 
                      ObjectT *, 
                      OnStoredObject>
{
    typedef RetT (ObjectT::*ObjectMethodT   )(Arg2T);
    typedef RetT (ObjectT::*ObjectMethodPtrT)(Arg1T, Arg2T);

    typedef ObjectT *SetObjectT;

    static void setCalledObject(char *pData, SetObjectT obj)
    {
        *((ObjectT **) pData) = obj;
    }

#ifdef __sgi
#pragma set woff 1551 
#endif

    static RetT callObjectMethod(char *, Arg1T , Arg2T)
    {
        RetT returnValue;

        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

#ifdef __sgi
#pragma reset woff 1551 
#endif

    static RetT callObjectMethod(char  *pData1, 
                                 char  *pData2, 
                                 Arg1T  arg1,
                                 Arg2T  arg2)
    {
        ObjectT *pObj = *((ObjectT **) pData1);

        ObjectMethodPtrT pFunc = *((ObjectMethodPtrT *) pData2);
            
        return (pObj->*pFunc)(arg1, arg2);
    }


    static void callObjectMethodVoid(char  *, 
                                     Arg1T  ,
                                     Arg2T)
    {
        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }

    static void callObjectMethodVoid(char     *pData1, 
                                     char     *pData2, 
                                     Arg1T  arg1,
                                     Arg2T  arg2)
    {
        ObjectT *pObj = *((ObjectT **) pData1);

        ObjectMethodPtrT pFunc = *((ObjectMethodPtrT *) pData2);
            
        (pObj->*pFunc)(arg1, arg2);
    }
};

template <class RetT, 
          class Arg1T,
          class Arg2T,
          class ObjectT>
struct FunctorTraits2<RetT, 
                      Arg1T &, 
                      Arg2T,
                      ObjectT &, 
                      OnArgument>
{
    typedef RetT (ObjectT::*ObjectMethodT   )(Arg2T);
    typedef RetT (ObjectT::*ObjectMethodPtrT)(Arg1T, Arg2T);

    typedef ObjectT &SetObjectT;

    static void setCalledObject(char *pData, SetObjectT obj)
    {
        *((ObjectT *) pData) = obj;
    }

    static RetT callObjectMethod(char *pData2, Arg1T arg1, Arg2T arg2)
    {
        ObjectMethodT pFunc = *((ObjectMethodT *) _data2);

        return ((&arg1)->*pFunc)();
    }

    static RetT callObjectMethod(char  *, 
                                 char  *, 
                                 Arg1T  ,
                                 Arg2T)
    {
        RetT returnValue;

        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

    static void callObjectMethodVoid(char     *pData2, 
                                     Arg1T  arg1,
                                     Arg2T  arg2)
    {
        ObjectMethodT pFunc = *((ObjectMethodT *) _data2);

        ((&arg1)->*pFunc)();
    }

    static void callObjectMethodVoid(char  *, 
                                     char  *, 
                                     Arg1T  ,
                                     Arg2T)
    {
        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }
};

template <class RetT, 
          class Arg1T,
          class Arg2T,
          class ObjectT>
struct FunctorTraits2<RetT, 
                      Arg1T *, 
                      Arg2T,
                      ObjectT &, 
                      OnArgument>
{
    typedef RetT (ObjectT::*ObjectMethodT   )(Arg2T);
    typedef RetT (ObjectT::*ObjectMethodPtrT)(Arg1T, Arg2T);

    typedef ObjectT &SetObjectT;

    static void setCalledObject(char *pData, SetObjectT obj)
    {
        *((ObjectT *) pData) = obj;
    }

    static RetT callObjectMethod(char *pData2, Arg1T arg1, Arg2T arg2)
    {
        ObjectMethodT pFunc = *((ObjectMethodT *) _data2);

        return ((arg1)->*pFunc)();
    }

    static RetT callObjectMethod(char     *, 
                                    char     *, 
                                    Arg1T  ,
                                    Arg2T  )
    {
        RetT returnValue;

        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

    static void callObjectMethodVoid(char  *pData2, 
                                     Arg1T  arg1,
                                     Arg2T  arg2)
    {
        ObjectMethodT pFunc = *((ObjectMethodT *) _data2);

        ((arg1)->*pFunc)();
    }

    static void callObjectMethodVoid(char  *, 
                                     char  *, 
                                     Arg1T  ,
                                     Arg2T  )
    {
        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }
};

template <class RetT, 
          class Arg1T,
          class Arg2T,
          class ObjectT>
struct FunctorTraits2<RetT, 
                      Arg1T, 
                      Arg2T,
                      ObjectT &, 
                      OnStoredObject>
{
    typedef RetT (ObjectT::*ObjectMethodT   )(Arg2T);
    typedef RetT (ObjectT::*ObjectMethodPtrT)(Arg1T, Arg2T);

    typedef ObjectT &SetObjectT;

    static void setCalledObject(char *pData, SetObjectT obj)
    {
        *((ObjectT *) pData) = obj;
    }

#ifdef __sgi
#pragma set woff 1551 
#endif

    static RetT callObjectMethod(char *, Arg1T , Arg2T)
    {
        RetT returnValue;

        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;

        return returnValue;
    }

#ifdef __sgi
#pragma reset woff 1551 
#endif

    static RetT callObjectMethod(char  *pData1, 
                                 char  *pData2, 
                                 Arg1T  arg1,
                                 Arg2T  arg2)
    {
        ObjectT *pObj = ((ObjectT *) pData1);

        ObjectMethodPtrT pFunc = *((ObjectMethodPtrT *) pData2);
            
        return (pObj->*pFunc)(arg1, arg2);
    }

    static void callObjectMethodVoid(char  *, 
                                     Arg1T  ,
                                     Arg2T)
    {
        SWARNING << "FunctorTraits::call called, "
                 << "undefined behaviour might " 
                 << "be the consequence\n" << endl;
    }

    static void callObjectMethodVoid(char  *pData1, 
                                     char  *pData2, 
                                     Arg1T  arg1,
                                     Arg2T  arg2)
    {
        ObjectT *pObj = ((ObjectT *) pData1);

        ObjectMethodPtrT pFunc = *((ObjectMethodPtrT *) pData2);
        
        (pObj->*pFunc)(arg1, arg2);
    }
};

/*! \ingroup BaseLib
 *  \brief Brief
 */

template <class RetT, 
          class Arg1T,
          class Arg2T,
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT = DefaultFunctorSizeTraits>
class ObjectFunctor2 : 
    public Functor2Base<RetT, Arg1T, Arg2T, SizeTraitsT>
{
    /*==========================  PUBLIC  =================================*/    
  public:

    typedef
        FunctorTraits2<RetT,
                       Arg1T, 
                       Arg2T,
                       ObjectT, 
                       MethodCallType> FunctorTrait;

    typedef typename FunctorTrait::ObjectMethodT    ObjectMethodT;
    typedef typename FunctorTrait::ObjectMethodPtrT ObjectMethodPtrT;
    typedef typename FunctorTrait::SetObjectT       SetObjectT;

    /*==========================  PRIVATE  ================================*/
  private:

    typedef Functor2Base<RetT, 
                         Arg1T, 
                         Arg2T, 
                         SizeTraitsT> Inherited;

	static char cvsid[];
    
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */
          
    void operator =(const ObjectFunctor2 &source);
  
    /*! \}                                                                 */  
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ObjectFunctor2(void);
    ObjectFunctor2(const ObjectFunctor2 &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
    
    virtual ~ObjectFunctor2(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void setMethod         (ObjectMethodT     pFunc);

    void setMethod         (ObjectMethodPtrT  pFunc);

    void setCalledObject   (SetObjectT        pObj);

    void setObjectAndMethod(SetObjectT        pObj, 
                            ObjectMethodPtrT  pFunc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */
    
    virtual RetT       call(Arg1T             arg1,
                            Arg2T             arg2);
    
    /*! \}                                                                 */    
};

/*! \ingroup BaseLib
 *  \brief Brief
 */

template <class Arg1T,
          class Arg2T,
          class ObjectT, 
          enum  FunctorMethodCallTypeE MethodCallType,
          class SizeTraitsT>
class ObjectFunctor2<void, 
                     Arg1T, 
                     Arg2T,
                     ObjectT, 
                     MethodCallType,
                     SizeTraitsT> : 
    public Functor2Base<void, Arg1T, Arg2T, SizeTraitsT>
{
    /*==========================  PUBLIC  =================================*/        
  public:

    typedef
        FunctorTraits2<void,
                       Arg1T, 
                       Arg2T,
                       ObjectT, 
                       MethodCallType> FunctorTrait;

    typedef typename FunctorTrait::ObjectMethodT    ObjectMethodT;
    typedef typename FunctorTrait::ObjectMethodPtrT ObjectMethodPtrT;
    typedef typename FunctorTrait::SetObjectT       SetObjectT;
    
    /*==========================  PRIVATE  ================================*/
  private:

    typedef Functor2Base<void, 
                         Arg1T, 
                         Arg2T, 
                         SizeTraitsT> Inherited;

	static char cvsid[];
    
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    void operator =(const ObjectFunctor2 &source);
  
    /*! \}                                                                 */  
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ObjectFunctor2(void);
    ObjectFunctor2(const ObjectFunctor2 &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
    
    virtual ~ObjectFunctor2(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void setMethod         (ObjectMethodT     pFunc);

    void setMethod         (ObjectMethodPtrT  pFunc);

    void setCalledObject   (SetObjectT        pObj);

    void setObjectAndMethod(SetObjectT        pObj, 
                            ObjectMethodPtrT  pFunc);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */
    
    virtual void    call(Arg1T             arg1,
                         Arg2T             arg2);
    
    /*! \}                                                                 */    
};

template <class RetT, class Arg1T, class Arg2T> inline
FunctionFunctor2<RetT, Arg1T, Arg2T> osgFunctionFunctor2( 
    RetT (*pFunc)(Arg1T, Arg2T));

template <class RetT, class Arg1T, class Arg2T> inline
ObjectFunctor2<RetT, 
               Arg1T &, 
               Arg2T,
               Arg1T,
               OnArgument> osgMethodFunctor2Ref(
    RetT (Arg1T::*pFunc)(Arg2T));


template <class RetT, class Arg1T, 
          class Arg2T, class ObjectT> inline
ObjectFunctor2<RetT, 
               Arg1T, 
               Arg2T,
               ObjectT &,
               OnStoredObject> osgMethodFunctor2Ref(
    ObjectT &obj, RetT (ObjectT::*pFunc)(Arg1T, Arg2T));


template <class RetT, class Arg1T, class Arg2T> inline
ObjectFunctor2<RetT, 
               Arg1T *, 
               Arg2T,
               Arg1T,
               OnArgument> osgMethodFunctor2Ptr(
    RetT (Arg1T::*pFunc)(Arg2T));


template <class RetT,  class Arg1T, 
          class Arg2T, class ObjectT> inline
ObjectFunctor2<RetT, 
               Arg1T, 
               Arg2T,
               ObjectT *,
               OnStoredObject> osgMethodFunctor2Ptr(
    ObjectT *pObj, RetT (ObjectT::*pFunc)(Arg1T, Arg2T));

template <class RetT, class Arg1T, class Arg2T> inline
ObjectFunctor2<RetT, 
               Arg1T &, 
               Arg2T, 
               Arg1T,
               OnCPtrArgument> osgMethodFunctor2CPtr(
    typename FunctorBuildFuncType2<RetT, 
                                   Arg2T,
                                   Arg1T>::FunctionType pFunc);

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
                                   ObjectT>::FunctionType pFunc);

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
                                   ObjectT>::FunctionType pFunc);

OSG_END_NAMESPACE

#include <OSGFunctors.inl>

#endif /* _OSGFUNCTORS_H_ */
