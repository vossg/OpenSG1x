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

#ifndef _OSGTYPEDFUNCTORS1_H_
#define _OSGTYPEDFUNCTORS1_H_
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

/*! \ingroup GrpBaseFunctors1Helper
    \hideinhierarchy
 */

template <class RetT, 
          class CallArgT> 
struct TypedTraits1
{
    typedef typename CallArgT::ObjType ObjType;
    typedef typename CallArgT::ArgType ArgType;

    typedef typename
        FunctorBuildFuncType1<RetT, CallArgT>::FuncFunctionType FunctionF;

    typedef typename
        FunctorBuildFuncType1<RetT, CallArgT>::ObjFuncType      ObjMethodF;

    static void callObjectMethodVoid(UInt8 *pData2, ArgType arg1)
    {
        ObjMethodF  pFunc = *((ObjMethodF *) pData2);
        ObjType    *pObj  = CallArgT::getPtr(arg1); 

        (pObj->*pFunc)();
    }

    static RetT callObjectMethod(UInt8 *pData2, ArgType arg1)
    {
        ObjMethodF  pFunc = *((ObjMethodF *) pData2);
        ObjType    *pObj  = CallArgT::getPtr(arg1); 

        return (pObj->*pFunc)();
    }
};




/*! \ingroup GrpBaseFunctors1Helper
    \hideinhierarchy
 */

template <class RetT, 
          class StoredObjCallArgT,
          class ArgsT> 
struct TypedSOTraits1
{
    typedef typename StoredObjCallArgT::ObjType  ObjType;

    typedef typename ArgsT::ArgType              ArgType;

    typedef          ObjType                    *SetObjectT;
    typedef          ObjType                    *StoredObjectT;

    typedef typename
        FunctorBuildObjFuncType1<RetT, 
                                 StoredObjCallArgT,
                                 ArgsT            >::ObjFuncType ObjMethodF;


    static void setCalledObject(Char8 *pData, SetObjectT obj)
    {
        *((ObjType **) pData) = obj;
    }

    static void callObjectMethodVoid(UInt8   *pData1, 
                                     UInt8   *pData2, 
                                     ArgType  arg1  )
    {
        StoredObjectT pObj  = *((StoredObjectT *) pData1);

        ObjMethodF    pFunc = *((ObjMethodF     *) pData2);
        
        (pObj->*pFunc)(arg1);
    }

    static RetT callObjectMethod(UInt8   *pData1, 
                                 UInt8   *pData2, 
                                 ArgType  arg1  )
    {
        StoredObjectT pObj  = *((StoredObjectT *) pData1);

        ObjMethodF    pFunc = *((ObjMethodF     *) pData2);
        
        return (pObj->*pFunc)(arg1);
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
          class SizeTraitsT = DefaultFunctorSizeTraits>
class TypedFunctor1Base : public TypedFunctorBase<SizeTraitsT>
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    typedef typename CallArgT::ArgType CallArgType;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TypedFunctor1Base(void);
    TypedFunctor1Base(const TypedFunctor1Base &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~TypedFunctor1Base(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Call                                    */
    /*! \{                                                                 */

    virtual RetT call(CallArgType obj);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    void operator =(const TypedFunctor1Base &source);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */

    typedef TypedFunctorBase<                 SizeTraitsT> Inherited;

    typedef TypedFunctor1Base<RetT, CallArgT, SizeTraitsT> Self;

    /*! \}                                                                 */
};



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
    \hideinhierarchy
 */

template <class CallArgT, class SizeTraitsT = DefaultFunctorSizeTraits>
class TypedVoidFunctor1Base : public TypedFunctorBase<SizeTraitsT>
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    typedef typename CallArgT::ArgType CallArgType;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TypedVoidFunctor1Base(void);
    TypedVoidFunctor1Base(const TypedVoidFunctor1Base &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~TypedVoidFunctor1Base(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Call                                    */
    /*! \{                                                                 */

    virtual void call(CallArgType obj);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    void operator =(const TypedVoidFunctor1Base &source);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */

    typedef TypedFunctorBase     <          SizeTraitsT> Inherited;

    typedef TypedVoidFunctor1Base<CallArgT, SizeTraitsT> Self;

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
          class SizeTraitsT = DefaultFunctorSizeTraits>
class TypedFunctionFunctor1 : 
    public TypedFunctionFunctorBase<TypedFunctor1Base<RetT,  
                                                      CallArgT,
                                                      SizeTraitsT>,
                                    TypedTraits1<     RetT, 
                                                      CallArgT> >
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    typedef typename CallArgT::ArgType CallArgType;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TypedFunctionFunctor1(void);
    TypedFunctionFunctor1(const TypedFunctionFunctor1 &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~TypedFunctionFunctor1(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Call                                    */
    /*! \{                                                                 */

    virtual RetT call(CallArgType pObj);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */

    typedef 
        TypedFunctionFunctorBase <TypedFunctor1Base<RetT, 
                                                    CallArgT,
                                                    SizeTraitsT>,
                                  TypedTraits1     <RetT, 
                                                    CallArgT>  > Inherited;

    typedef TypedFunctionFunctor1<RetT, CallArgT, SizeTraitsT  > Self;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const TypedFunctionFunctor1 &source);

    /*! \}                                                                 */
};

/*! \class TypedFunctionFunctorBase< TypedFunctor1Base< RetT, 
                                                        CallArgT, 
                                                        SizeTraitsT >, 
                                     TypedTraits1     < RetT, 
                                                        CallArgT > > 
    \hideinhierarchy
 */


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
    \hideinhierarchy
 */

template <class CallArgT, 
          class SizeTraitsT = DefaultFunctorSizeTraits>
class TypedFunctionVoidFunctor1 : 
    public TypedFunctionFunctorBase<TypedVoidFunctor1Base<CallArgT,
                                                          SizeTraitsT>,
                                    TypedTraits1         <void, 
                                                          CallArgT> >
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    typedef typename CallArgT::ArgType CallArgType;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TypedFunctionVoidFunctor1(void);
    TypedFunctionVoidFunctor1(const TypedFunctionVoidFunctor1 &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */
    
    virtual ~TypedFunctionVoidFunctor1(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Call                                    */
    /*! \{                                                                 */

    virtual void call(CallArgType pObj);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */

    typedef 
        TypedFunctionFunctorBase <TypedVoidFunctor1Base<CallArgT,
                                                        SizeTraitsT>,
                                  TypedTraits1         <void, 
                                                        CallArgT>  > Inherited;

    typedef 
        TypedFunctionVoidFunctor1<CallArgT, SizeTraitsT            > Self;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const TypedFunctionVoidFunctor1 &source);

    /*! \}                                                                 */
};

/*! \class TypedFunctionFunctorBase<TypedVoidFunctor1Base<CallArgT,
                                                          SizeTraitsT>,
                                    TypedTraits1         <void, 
                                                          CallArgT> >
    \hideinhierarchy
 */


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseAnonFunctors
    \hideinhierarchy
     AnonObjectFunctor1
 */

template <class RetT, 
          class CallArgT,
          class SizeTraitsT = DefaultFunctorSizeTraits>
class TypedObjectFunctor1 : 
    public TypedObjectFunctorBase<TypedFunctor1Base<RetT, 
                                                    CallArgT,
                                                    SizeTraitsT>,
                                   TypedTraits1<    RetT, 
                                                    CallArgT> >
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    typedef typename CallArgT::ArgType CallArgType;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TypedObjectFunctor1(void);
    TypedObjectFunctor1(const TypedObjectFunctor1 &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~TypedObjectFunctor1(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Call                                    */
    /*! \{                                                                 */

    virtual RetT call(CallArgType pObj);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */

    typedef TypedTraits1<RetT, CallArgT> TypeTraits;

    typedef 
        TypedObjectFunctorBase<
            TypedFunctor1Base<RetT, 
                              CallArgT,
                              SizeTraitsT>,
            TypedTraits1<     RetT, 
                              CallArgT   > > Inherited;

    typedef 
        TypedObjectFunctor1   <RetT, 
                               CallArgT    > Self;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const TypedObjectFunctor1 &source);

    /*! \}                                                                 */
};

/*! \class TypedObjectFunctorBase<TypedFunctor1Base<RetT, 
                                                    CallArgT,
                                                    SizeTraitsT>,
                                   TypedTraits1<    RetT, 
                                                    CallArgT> >
    \hideinhierarchy
 */

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
    \hideinhierarchy
 */

template <class CallArgT, 
          class SizeTraitsT = DefaultFunctorSizeTraits>
class TypedObjectVoidFunctor1 : 
    public TypedObjectFunctorBase<TypedVoidFunctor1Base<CallArgT,
                                                        SizeTraitsT>,
                                  TypedTraits1         <void, 
                                                        CallArgT> >
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    typedef typename CallArgT::ArgType CallArgType;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TypedObjectVoidFunctor1(void);
    TypedObjectVoidFunctor1(const TypedObjectVoidFunctor1 &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~TypedObjectVoidFunctor1(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Call                                    */
    /*! \{                                                                 */

    virtual void call(CallArgType obj);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */

    typedef TypedTraits1<void, CallArgT> TypeTraits;

    typedef 
        TypedObjectFunctorBase<
            TypedVoidFunctor1Base<CallArgT,
                                  SizeTraitsT>,
            TypedTraits1         <void, 
                                  CallArgT> > Inherited;

    typedef 
        TypedObjectVoidFunctor1<CallArgT, 
                                SizeTraitsT > Self;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const TypedObjectVoidFunctor1 &source);

    /*! \}                                                                 */
};

/*! \class TypedObjectFunctorBase<TypedVoidFunctor1Base<CallArgT,
                                                        SizeTraitsT>,
                                  TypedTraits1         <void, 
                                                        CallArgT> >
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
          class ArgsT,
          class SizeTraitsT = DefaultFunctorSizeTraits>
class TypedStoredObjectFunctor1 : 
    public TypedStoredObjectFunctorBase<
        TypedFunctor1Base<RetT, 
                          ArgsT,
                          SizeTraitsT>,
        TypedSOTraits1   <RetT, 
                          StoredObjectT,
                          typename ArgsT::ArgsC> >
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    typedef typename ArgsT::ArgType CallArgType;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TypedStoredObjectFunctor1(void);
    TypedStoredObjectFunctor1(const TypedStoredObjectFunctor1 &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~TypedStoredObjectFunctor1(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Call                                    */
    /*! \{                                                                 */

    virtual RetT call(CallArgType obj);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */

    typedef TypedSOTraits1<RetT, 
                           StoredObjectT, 
                           typename ArgsT::ArgsC> TypeTraits;

    typedef 
        TypedStoredObjectFunctorBase<
            TypedFunctor1Base<RetT, 
                              ArgsT,
                              SizeTraitsT>,
            TypedSOTraits1   <RetT, 
                              StoredObjectT,
                              typename ArgsT::ArgsC> > Inherited;

    typedef 
        TypedStoredObjectFunctor1<RetT, 
                                  StoredObjectT, 
                                  ArgsT, 
                                  SizeTraitsT        > Self;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const TypedStoredObjectFunctor1 &source);

    /*! \}                                                                 */
};

/*! \class TypedStoredObjectFunctorBase<
        TypedFunctor1Base<RetT, 
                          ArgsT,
                          SizeTraitsT>,
        TypedSOTraits1   <RetT, 
                          StoredObjectT,
                          ArgsT::ArgsC> >
    \hideinhierarchy
 */

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
    \hideinhierarchy
 */

template <class StoredObjectT, 
          class ArgsT,
          class SizeTraitsT  = DefaultFunctorSizeTraits>
class TypedStoredObjectVoidFunctor1 : 
    public TypedStoredObjectFunctorBase<TypedVoidFunctor1Base<ArgsT,
                                                              SizeTraitsT>,
                                        TypedSOTraits1       <void, 
                                                              StoredObjectT,
                                                     typename ArgsT::ArgsC> >
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    typedef typename ArgsT::ArgType CallArgType;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TypedStoredObjectVoidFunctor1(void);
    TypedStoredObjectVoidFunctor1(const TypedStoredObjectVoidFunctor1 &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~TypedStoredObjectVoidFunctor1(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Call                                    */
    /*! \{                                                                 */

    virtual void call(CallArgType pObj);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */

    typedef TypedSOTraits1<void, 
                           StoredObjectT, 
                           typename ArgsT::ArgsC> TypeTraits;

    typedef 
        TypedStoredObjectFunctorBase<
            TypedVoidFunctor1Base<ArgsT,
                                  SizeTraitsT>,
            TypedSOTraits1       <void, 
                                  StoredObjectT,
                                  typename ArgsT::ArgsC> > Inherited;

    typedef 
    TypedStoredObjectVoidFunctor1<StoredObjectT,
                                  ArgsT,
                                  SizeTraitsT            > Self;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const TypedStoredObjectVoidFunctor1 &source);

    /*! \}                                                                 */
};

/*! \class TypedStoredObjectFunctorBase<TypedVoidFunctor1Base<ArgsT,
                                                              SizeTraitsT>,
                                        TypedSOTraits1       <void, 
                                                              StoredObjectT,
                                                              ArgsT::ArgsC> >
    \hideinhierarchy
 */

OSG_END_NAMESPACE

#include <OSGTypedFunctors1.inl>

#endif /* _OSGTYPEDFUNCTORS1_H_ */





