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

#ifndef _OSGTYPEDFUNCTORS2_H_
#define _OSGTYPEDFUNCTORS2_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGTypedFunctorBase.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors2Helper
    \hideinhierarchy
 */

template <class RetT, 
          class CallArgT,
          class ArgsT   > 
struct TypedTraits2
{
    typedef typename CallArgT::ObjType ObjType;
    typedef typename CallArgT::ArgType ArgType;

    typedef typename ArgsT::Arg1T      Arg1T;

    typedef typename
        FunctorBuildFuncType2<RetT, 
                              CallArgT, 
                              ArgsT   >::FuncFunctionType         FunctionF;

    typedef typename
        FunctorBuildFuncType2<RetT, CallArgT, ArgsT>::ObjFuncType ObjMethodF;

    static void callObjectMethodVoid(UInt8   *pData2, 
                                     ArgType  arg1, 
                                     Arg1T    arg2)
    {
        ObjMethodF  pFunc = *((ObjMethodF *) pData2);
        ObjType    *pObj  = CallArgT::getPtr(arg1); 

        (pObj->*pFunc)(arg2);
    }

    static RetT callObjectMethod(UInt8   *pData2, 
                                 ArgType  arg1, 
                                 Arg1T    arg2)
    {
        ObjMethodF  pFunc = *((ObjMethodF *) pData2);
        ObjType    *pObj  = CallArgT::getPtr(arg1); 

        return (pObj->*pFunc)(arg2);
    }
};




/*! \ingroup GrpBaseFunctors1Helper
    \hideinhierarchy
 */

template <class RetT, 
          class StoredObjCallArgT,
          class CallArgT,
          class ArgsT> 
struct TypedSOTraits2
{
    typedef typename StoredObjCallArgT::ObjType  ObjType;

    typedef typename CallArgT::ArgType           ArgType;

    typedef typename StoredObjCallArgT::ArgType  SetObjectT;
    typedef          ObjType                    *StoredObjectT;

    typedef typename ArgsT::Arg1T                Arg2T;

    typedef typename
        FunctorBuildObjFuncType2<RetT, 
                                 StoredObjCallArgT,
                                 CallArgT,
                                 ArgsT            >::ObjFuncType ObjMethodF;


    static void setCalledObject(Char8 *pData, SetObjectT obj)
    {
        *((ObjType **) pData) = &(*obj);
    }


    static void callObjectMethodVoid(UInt8   *pData1, 
                                     UInt8   *pData2, 
                                     ArgType  arg1  ,
                                     Arg2T    arg2  )
    {
        StoredObjectT pObj  = *((StoredObjectT *) pData1);

        ObjMethodF    pFunc = *((ObjMethodF     *) pData2);
        
        (pObj->*pFunc)(arg1, arg2);
    }

    static RetT callObjectMethod(UInt8   *pData1, 
                                 UInt8   *pData2, 
                                 ArgType  arg1  ,
                                 Arg2T    arg2  )
    {
        StoredObjectT pObj  = *((StoredObjectT *) pData1);

        ObjMethodF    pFunc = *((ObjMethodF     *) pData2);
        
        return (pObj->*pFunc)(arg1, arg2);
    }
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
    \hideinhierarchy
 */

template <class RetT,
          class CallArgT,
          class ArgsT,
          class SizeTraitsT = DefaultFunctorSizeTraits>
class TypedFunctor2Base : public TypedFunctorBase<SizeTraitsT>
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    typedef typename CallArgT::ArgType CallArgType;
    typedef typename ArgsT   ::Arg1T   Arg1Type;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TypedFunctor2Base(void);
    TypedFunctor2Base(const TypedFunctor2Base &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~TypedFunctor2Base(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Call                                    */
    /*! \{                                                                 */

    virtual RetT call(CallArgType obj,
                      Arg1Type    arg1);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    void operator =(const TypedFunctor2Base &source);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */

    typedef TypedFunctorBase <                       SizeTraitsT> Inherited;

    typedef TypedFunctor2Base<RetT, CallArgT, ArgsT, SizeTraitsT> Self;

    /*! \}                                                                 */
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
    \hideinhierarchy
 */

template <class CallArgT, 
          class ArgsT, 
          class SizeTraitsT = DefaultFunctorSizeTraits>
class TypedVoidFunctor2Base : public TypedFunctorBase<SizeTraitsT>
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    typedef typename CallArgT::ArgType CallArgType;
    typedef typename ArgsT   ::Arg1T   Arg1Type;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TypedVoidFunctor2Base(void);
    TypedVoidFunctor2Base(const TypedVoidFunctor2Base &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~TypedVoidFunctor2Base(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Call                                    */
    /*! \{                                                                 */

    virtual void call(CallArgType obj,
                      Arg1Type    arg1);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    void operator =(const TypedVoidFunctor2Base &source);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */

    typedef TypedFunctorBase     <                 SizeTraitsT> Inherited;
    
    typedef TypedVoidFunctor2Base<CallArgT, ArgsT, SizeTraitsT> Self;
    
    /*! \}                                                                 */
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
    \hideinhierarchy
 */

template <class RetT, 
          class CallArgT, 
          class ArgsT,
          class SizeTraitsT = DefaultFunctorSizeTraits>
class TypedFunctionFunctor2 : 
    public TypedFunctionFunctorBase<TypedFunctor2Base<RetT, 
                                                      CallArgT,
                                                      ArgsT,
                                                      SizeTraitsT>,
                                    TypedTraits2     <RetT, 
                                                      CallArgT,
                                                      ArgsT> >
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    typedef typename CallArgT::ArgType CallArgType;
    typedef typename ArgsT   ::Arg1T   Arg1;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TypedFunctionFunctor2(void);
    TypedFunctionFunctor2(const TypedFunctionFunctor2 &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~TypedFunctionFunctor2(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Call                                    */
    /*! \{                                                                 */

    virtual RetT call(CallArgType obj, 
                      Arg1        oArg1);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */

    typedef TypedTraits2<RetT, CallArgT, ArgsT> TypeTraits;

    typedef 
        TypedFunctionFunctorBase<TypedFunctor2Base<RetT, 
                                                   CallArgT,
                                                   ArgsT,
                                                   SizeTraitsT>,
                                 TypedTraits2     <RetT, 
                                                   CallArgT,
                                                   ArgsT>     > Inherited;

    typedef 
        TypedFunctionFunctor2   <RetT,
                                 CallArgT,
                                 ArgsT,
                                 SizeTraitsT                  > Self;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const TypedFunctionFunctor2 &source);

    /*! \}                                                                 */
};

/*! \class TypedFunctionFunctorBase<TypedFunctor2Base<RetT, 
                                                      CallArgT,
                                                      ArgsT,
                                                      SizeTraitsT>,
                                    TypedTraits2     <RetT, 
                                                      CallArgT,
                                                      ArgsT> >
    \hideinhierarchy
 */

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
    \hideinhierarchy
 */

template <class CallArgT, 
          class ArgsT,
          class SizeTraitsT = DefaultFunctorSizeTraits>
class TypedFunctionVoidFunctor2 : 
    public TypedFunctionFunctorBase<TypedVoidFunctor2Base<CallArgT,
                                                          ArgsT,
                                                          SizeTraitsT>,
                                    TypedTraits2         <void, 
                                                          CallArgT,
                                                          ArgsT> >
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    typedef typename CallArgT::ArgType CallArgType;
    typedef typename ArgsT   ::Arg1T   Arg1;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TypedFunctionVoidFunctor2(void);
    TypedFunctionVoidFunctor2(const TypedFunctionVoidFunctor2 &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */
    
    virtual ~TypedFunctionVoidFunctor2(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Call                                    */
    /*! \{                                                                 */

    virtual void call(CallArgType obj,
                      Arg1        oArg1);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */

    typedef TypedTraits2<void, CallArgT, ArgsT> TypeTraits;

    typedef 
        TypedFunctionFunctorBase <TypedVoidFunctor2Base<CallArgT,
                                                        ArgsT,
                                                        SizeTraitsT>,
                                  TypedTraits2         <void, 
                                                        CallArgT,
                                                        ArgsT>     > Inherited;

    typedef
        TypedFunctionVoidFunctor2<CallArgT,
                                  ArgsT,
                                  SizeTraitsT                      > Self;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const TypedFunctionVoidFunctor2 &source);

    /*! \}                                                                 */
};

/*! \class TypedFunctionFunctorBase<TypedVoidFunctor2Base<CallArgT,
                                                          ArgsT,
                                                          SizeTraitsT>,
                                    TypedTraits2         <void, 
                                                          CallArgT,
                                                          ArgsT> >
    \hideinhierarchy
 */

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
    \hideinhierarchy
 */

template <class RetT, 
          class CallArgT,
          class ArgsT,
          class SizeTraitsT = DefaultFunctorSizeTraits>
class TypedObjectFunctor2 : 
    public TypedObjectFunctorBase<TypedFunctor2Base<RetT, 
                                                    CallArgT,
                                                    ArgsT,
                                                    SizeTraitsT>,
                                  TypedTraits2     <RetT, 
                                                    CallArgT,
                                                    ArgsT> >
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    typedef typename CallArgT::ArgType CallArgType;
    typedef typename ArgsT   ::Arg1T   Arg1;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TypedObjectFunctor2(void);
    TypedObjectFunctor2(const TypedObjectFunctor2 &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */
    
    virtual ~TypedObjectFunctor2(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Call                                    */
    /*! \{                                                                 */

    virtual RetT call(CallArgType obj,
                      Arg1        oArg1);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */

    typedef TypedTraits2<RetT, CallArgT, ArgsT> TypeTraits;

    typedef 
        TypedObjectFunctorBase<
            TypedFunctor2Base<RetT, 
                              CallArgT,
                              ArgsT,
                              SizeTraitsT>,
            TypedTraits2     <RetT, 
                              CallArgT,
                              ArgsT>   > Inherited;

    typedef
        TypedObjectFunctor2<RetT,
                            CallArgT,
                            ArgsT,
                            SizeTraitsT> Self;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const TypedObjectFunctor2 &source);

    /*! \}                                                                 */
};

/*! \class TypedObjectFunctorBase<TypedFunctor2Base<RetT, 
                                                    CallArgT,
                                                    ArgsT,
                                                    SizeTraitsT>,
                                  TypedTraits2     <RetT, 
                                                    CallArgT,
                                                    ArgsT> >
    \hideinhierarchy
 */


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
    \hideinhierarchy
 */

template <class CallArgT, 
          class ArgsT,
          class SizeTraitsT = DefaultFunctorSizeTraits>
class TypedObjectVoidFunctor2 : 
    public TypedObjectFunctorBase<TypedVoidFunctor2Base<CallArgT, 
                                                        ArgsT,
                                                        SizeTraitsT>,
                                  TypedTraits2         <void, 
                                                        CallArgT,
                                                        ArgsT> >
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    typedef typename CallArgT::ArgType CallArgType;
    typedef typename ArgsT   ::Arg1T   Arg1;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TypedObjectVoidFunctor2(void);
    TypedObjectVoidFunctor2(const TypedObjectVoidFunctor2 &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~TypedObjectVoidFunctor2(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Call                                    */
    /*! \{                                                                 */

    virtual void call(CallArgType obj,
                      Arg1        oArg1);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */

    typedef TypedTraits2<void, CallArgT, ArgsT> TypeTraits;

    typedef 
        TypedObjectFunctorBase<
            TypedVoidFunctor2Base<CallArgT,
                                  ArgsT,
                                  SizeTraitsT>,
            TypedTraits2         <void, 
                                  CallArgT,
                                  ArgsT>     > Inherited;

    typedef
        TypedObjectVoidFunctor2  <CallArgT,
                                  ArgsT,
                                  SizeTraitsT> Self;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const TypedObjectVoidFunctor2 &source);

    /*! \}                                                                 */
};

/*! \class TypedObjectFunctorBase<TypedVoidFunctor2Base<CallArgT, 
                                                        ArgsT,
                                                        SizeTraitsT>,
                                  TypedTraits2         <void, 
                                                        CallArgT,
                                                        ArgsT> >
    \hideinhierarchy
 */


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
    \hideinhierarchy
 */

template <class RetT, 
          class StoredObjectT,
          class ArgObjectT,
          class ArgsT,
          class SizeTraitsT = DefaultFunctorSizeTraits>
class TypedStoredObjectFunctor2 : 
    public TypedStoredObjectFunctorBase<TypedFunctor2Base<RetT, 
                                                          ArgObjectT,
                                                          ArgsT,
                                                          SizeTraitsT>,
                                        TypedSOTraits2   <RetT, 
                                                          StoredObjectT,
                                                 typename ArgObjectT::ArgsC,
                                                          ArgsT> >
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    typedef typename ArgObjectT::ArgType CallArgType;
    typedef typename ArgsT     ::Arg1T   Arg1;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TypedStoredObjectFunctor2(void);
    TypedStoredObjectFunctor2(const TypedStoredObjectFunctor2 &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~TypedStoredObjectFunctor2(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Call                                    */
    /*! \{                                                                 */

    virtual RetT call(CallArgType obj,
                      Arg1        oArg1);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */

    typedef TypedSOTraits2<RetT, 
                           StoredObjectT,
                           typename ArgObjectT::ArgsC,
                           ArgsT            > TypeSOTraits; 

    typedef 
        TypedStoredObjectFunctorBase<
            TypedFunctor2Base<RetT, 
                              ArgObjectT, 
                              ArgsT, 
                              SizeTraitsT>,
            TypedSOTraits2   <RetT, 
                              StoredObjectT,
                              typename ArgObjectT::ArgsC,
                              ArgsT            >        > Inherited;

    typedef
        TypedStoredObjectFunctor2<RetT, 
                                  StoredObjectT,
                                  ArgObjectT,
                                  ArgsT,
                                  SizeTraitsT           > Self;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const TypedStoredObjectFunctor2 &source);

    /*! \}                                                                 */
};

/*! \class TypedStoredObjectFunctorBase<TypedFunctor2Base<RetT, 
                                                          ArgObjectT,
                                                          ArgsT,
                                                          SizeTraitsT>,
                                        TypedSOTraits2   <RetT, 
                                                          StoredObjectT,
                                                          ArgObjectT::ArgsC,
                                                          ArgsT> >
    \hideinhierarchy
 */


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
    \hideinhierarchy
 */

template <class StoredObjectT, 
          class ArgObjectT,
          class ArgsT,
          class SizeTraitsT = DefaultFunctorSizeTraits>
class TypedStoredObjectVoidFunctor2 : 
    public TypedStoredObjectFunctorBase<TypedVoidFunctor2Base<ArgObjectT,
                                                              ArgsT,
                                                              SizeTraitsT>,
                                        TypedSOTraits2      <void, 
                                                             StoredObjectT,
                                                    typename ArgObjectT::ArgsC,
                                                             ArgsT> >
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    typedef typename ArgsT     ::Arg1T   Arg1;
    typedef typename ArgObjectT::ArgType CallArgType;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TypedStoredObjectVoidFunctor2(void);
    TypedStoredObjectVoidFunctor2(const TypedStoredObjectVoidFunctor2 &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~TypedStoredObjectVoidFunctor2(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Call                                    */
    /*! \{                                                                 */

    virtual void call(CallArgType obj,
                      Arg1        oArg1);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */

    typedef TypedSOTraits2<void, 
                           StoredObjectT,
                           typename ArgObjectT::ArgsC,
                           ArgsT                     > TypeSOTraits;
    typedef 
        TypedStoredObjectFunctorBase<
            TypedVoidFunctor2Base<ArgObjectT,
                                  ArgsT,
                                  SizeTraitsT>,
            TypedSOTraits2       <void, 
                                  StoredObjectT,
                                  typename ArgObjectT::ArgsC,
                                  ArgsT                     > > Inherited;

    typedef 
        TypedStoredObjectVoidFunctor2<StoredObjectT, 
                                      ArgObjectT,
                                      ArgsT,
                                      SizeTraitsT             > Self;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const TypedStoredObjectVoidFunctor2 &source);

    /*! \}                                                                 */
};

/*! \class TypedStoredObjectFunctorBase<TypedVoidFunctor2Base<ArgObjectT,
                                                              ArgsT,
                                                              SizeTraitsT>,
                                        TypedSOTraits2      <void, 
                                                             StoredObjectT,
                                                             ArgObjectT::ArgsC,
                                                             ArgsT> >
    \hideinhierarchy
 */

OSG_END_NAMESPACE

#include <OSGTypedFunctors2.inl>

#endif /* _OSGTYPEDFUNCTORS2_HPP_ */





