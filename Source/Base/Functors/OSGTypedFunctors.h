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

#ifndef _OSGTYPEDFUNCTORS_H_
#define _OSGTYPEDFUNCTORS_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGTypedFunctorBase.h>

#include <OSGTypedFunctors1.h>
#include <OSGTypedFunctors2.h>

OSG_BEGIN_NAMESPACE

#ifndef OSG_MICROSOFT_COMPILER_ALERT

//---------------------------------------------------------------------------
//  osgTypedFunctionFunctor1Ptr
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
 */

template <class RetT, class Arg1T> inline
TypedFunctionFunctor1<RetT, PtrCallArg<Arg1T> > osgTypedFunctionFunctor1Ptr   (
    RetT (*pFunc)(Arg1T *));

/*! \ingroup GrpBaseFunctors
 */

template <class Arg1T> inline
TypedFunctionVoidFunctor1< PtrCallArg<Arg1T> > osgTypedFunctionVoidFunctor1Ptr(
    void (*pFunc)(Arg1T *));

//---------------------------------------------------------------------------
//  osgTypedFunctionFunctor1Ref
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
 */

template <class RetT, class Arg1T> inline
TypedFunctionFunctor1<RetT, RefCallArg<Arg1T> > osgTypedFunctionFunctor1Ref   (
    RetT (*pFunc)(Arg1T &));

/*! \ingroup GrpBaseFunctors
 */

template <class Arg1T> inline
TypedFunctionVoidFunctor1< RefCallArg<Arg1T> > osgTypedFunctionVoidFunctor1Ref(
    void (*pFunc)(Arg1T &));

//---------------------------------------------------------------------------
//  osgTypedFunctionFunctor1CPtr
//---------------------------------------------------------------------------

template <class RetT, class Arg1T>
inline TypedFunctionFunctor1<RetT, CPtrCallArg<Arg1T> >
osgTypedFunctionFunctor1CPtr(RetT (*pFunc)(Arg1T));

/*! \ingroup GrpBaseFunctors
 */

template <class Arg1T> inline
TypedFunctionVoidFunctor1< CPtrCallArg<Arg1T> >
    osgTypedFunctionVoidFunctor1CPtr(void (*pFunc)(Arg1T));

//---------------------------------------------------------------------------
//  osgTypedFunctionFunctor1CPtrRef
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
 */

template <class RetT, class Arg1T> inline
TypedFunctionFunctor1<RetT, CPtrRefCallArg<Arg1T> >
    osgTypedFunctionFunctor1CPtrRef(RetT (*pFunc)(Arg1T &));

//---------------------------------------------------------------------------
//  osgTypedFunctionVoidFunctor1CPtrRef
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
 */

template <class Arg1T> inline
TypedFunctionVoidFunctor1< CPtrRefCallArg<Arg1T> >
    osgTypedFunctionVoidFunctor1CPtrRef(void (*pFunc)(Arg1T &));


//---------------------------------------------------------------------------
//  osgTypedMethodFunctor1Ref
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
 */

template <class RetT, class Arg1T> inline
TypedObjectFunctor1<RetT, RefCallArg<Arg1T> > osgTypedMethodFunctor1Ref   (
    RetT (Arg1T::*pFunc)());

/*! \ingroup GrpBaseFunctors
 */

template <class Arg1T> inline
TypedObjectVoidFunctor1< RefCallArg<Arg1T> > osgTypedMethodVoidFunctor1Ref(
    void (Arg1T::*pFunc)());

//---------------------------------------------------------------------------
//  osgTypedMethodFunctor1Ptr
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
 */

template <class RetT, class Arg1T> inline
TypedObjectFunctor1<RetT, PtrCallArg<Arg1T> > osgTypedMethodFunctor1Ptr   (
    RetT (Arg1T::*pFunc)());

/*! \ingroup GrpBaseFunctors
 */

template <class Arg1T> inline
TypedObjectVoidFunctor1< PtrCallArg<Arg1T> > osgTypedMethodVoidFunctor1Ptr(
    void (Arg1T::*pFunc)());

//---------------------------------------------------------------------------
//  osgTypedMethodFunctor1ObjPtr
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
 */

template <class RetT, class ObjectT, class Arg1T> inline
TypedStoredObjectFunctor1<RetT,
                          PtrCallArg<ObjectT>,
                          PtrCallArg<Arg1T  > >
    osgTypedMethodFunctor1ObjPtr(      ObjectT  *pObj,
                                 RetT (ObjectT::*pFunc)(Arg1T *));

/*! \ingroup GrpBaseFunctors
 */

template <class ObjectT, class Arg1T> inline
TypedStoredObjectVoidFunctor1<PtrCallArg<ObjectT>,
                              PtrCallArg<Arg1T  > >
    osgTypedMethodVoidFunctor1ObjPtr(      ObjectT  *pObj,
                                     void (ObjectT::*pFunc)(Arg1T *));

//---------------------------------------------------------------------------
//  osgTypedMethodFunctor1ObjPtrCPtrRef
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
 */

template <class RetT, class ObjectT, class Arg1T> inline
TypedStoredObjectFunctor1<RetT,
                          PtrCallArg    <ObjectT>,
                          CPtrRefCallArg<Arg1T  > >
    osgTypedMethodFunctor1ObjPtrCPtrRef(      ObjectT  *pObj,
                                        RetT (ObjectT::*pFunc)(Arg1T &));

/*! \ingroup GrpBaseFunctors
 */

template <class ObjectT, class Arg1T> inline
TypedStoredObjectVoidFunctor1<PtrCallArg    <ObjectT>,
                              CPtrRefCallArg<Arg1T  > >
    osgTypedMethodVoidFunctor1ObjPtrCPtrRef(      ObjectT  *pObj,
                                            void (ObjectT::*pFunc)(Arg1T &));

//---------------------------------------------------------------------------
//  osgTypedMethodFunctor1CPtr
//---------------------------------------------------------------------------

template <class RetT, class Arg1T>
inline TypedObjectFunctor1<RetT, CPtrCallArg<Arg1T> >
osgTypedMethodFunctor1CPtr(
    typename FunctorBuildFuncType1<RetT,
                                   CPtrCallArg<Arg1T> >::ObjFuncType pFunc);


/*! \ingroup GrpBaseFunctors
 */

template <class Arg1T> inline
TypedObjectVoidFunctor1< CPtrCallArg<Arg1T> >
    osgTypedMethodVoidFunctor1CPtr(
        typename FunctorBuildFuncType1<
            void,
            CPtrCallArg<Arg1T> >::ObjFuncType pFunc);


//---------------------------------------------------------------------------
//  osgTypedMethodFunctor1CPtrRef
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
 */

template <class Arg1T> inline
TypedObjectVoidFunctor1< CPtrRefCallArg<Arg1T> >
    osgTypedMethodVoidFunctor1CPtrRef(
        typename FunctorBuildFuncType1<
            void,
            CPtrRefCallArg<Arg1T> >::ObjFuncType pFunc);

#endif

//---------------------------------------------------------------------------
//  osgTypedMethodFunctor1ObjCPtr
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors1Helper
    \hideinhierarchy
 */

template<class T1, class T2, class T3>
struct TypedMethodVoidFunctor1ObjCPtrFGen
{
    typedef          CPtrCallArg<T3>       CAT3;

    typedef typename CAT3::ArgType         Arg1T;

    typedef          ArgsCollector <Arg1T> ArgColl;

    typedef typename ClassMemFunc1<T1,
                                   typename T2::StoredObjectType,
                                   ArgColl                     >::MemFunc Func;
};


#ifndef OSG_MICROSOFT_COMPILER_ALERT

/*! \ingroup GrpBaseFunctors
 */

template <class ObjectT, class Arg1T> inline
TypedStoredObjectVoidFunctor1<
    CPtrCallArg<ObjectT>,
    CPtrCallArg<Arg1T  > > osgTypedMethodVoidFunctor1ObjCPtr(

             ObjectT                                           obj,

    typename TypedMethodVoidFunctor1ObjCPtrFGen<void,
                                                ObjectT,
                                                Arg1T  >::Func pFunc);

#endif

//---------------------------------------------------------------------------
//  osgTypedMethodFunctor1ObjCPtrRef
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors1Helper
    \hideinhierarchy
 */

template<class T1, class T2, class T3>
struct TypedMethodVoidFunctor1ObjCPtrRefFGen
{
    typedef          CPtrRefCallArg<T3>    CAT3;

    typedef typename CAT3::ArgType         Arg1T;

    typedef          ArgsCollector <Arg1T> ArgColl;

    typedef typename ClassMemFunc1<T1,
                                   typename T2::StoredObjectType,
                                   ArgColl                     >::MemFunc Func;
};

#ifndef OSG_MICROSOFT_COMPILER_ALERT

/*! \ingroup GrpBaseFunctors
 */

template <class ObjectT, class Arg1T> inline
TypedStoredObjectVoidFunctor1<
    CPtrRefCallArg<ObjectT>,
    CPtrRefCallArg<Arg1T  > > osgTypedMethodVoidFunctor1ObjCPtrRef(

             ObjectT                                              obj,

    typename TypedMethodVoidFunctor1ObjCPtrRefFGen<void,
                                                   ObjectT,
                                                   Arg1T  >::Func pFunc);


//---------------------------------------------------------------------------
//  osgTypedFunctionFunctor2Ptr
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
 */

template <class RetT, class ObjectT, class Arg2T> inline
TypedFunctionFunctor2<RetT,
                      PtrCallArg<ObjectT>,
                      ArgsCollector<Arg2T> >
    osgTypedFunctionFunctor2Ptr    (RetT (*pFunc)(ObjectT *, Arg2T));

/*! \ingroup GrpBaseFunctors
 */

template <class ObjectT, class Arg2T> inline
TypedFunctionVoidFunctor2<PtrCallArg <ObjectT>,
                          ArgsCollector<Arg2T> >
    osgTypedFunctionVoidFunctor2Ptr(void (*pFunc)(ObjectT *, Arg2T));

//---------------------------------------------------------------------------
//  osgTypedFunctionFunctor2Ref
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
 */

template <class RetT, class ObjectT, class Arg2T> inline
TypedFunctionFunctor2<RetT,
                      RefCallArg<ObjectT>,
                      ArgsCollector<Arg2T> >
    osgTypedFunctionFunctor2Ref    (RetT (*pFunc)(ObjectT &, Arg2T));


/*! \ingroup GrpBaseFunctors
 */

template <class ObjectT, class Arg2T> inline
TypedFunctionVoidFunctor2<RefCallArg <ObjectT>,
                          ArgsCollector<Arg2T> >
    osgTypedFunctionVoidFunctor2Ref(void (*pFunc)(ObjectT &, Arg2T));

//---------------------------------------------------------------------------
//  osgTypedFunctionFunctor2CPtr
//---------------------------------------------------------------------------

template <class RetT, class ObjectT, class Arg2T>
inline TypedFunctionFunctor2<RetT, CPtrCallArg<ObjectT>, ArgsCollector<Arg2T> >
osgTypedFunctionFunctor2CPtr    (RetT (*pFunc)(ObjectT, Arg2T));

template <class ObjectT, class Arg2T>
inline TypedFunctionVoidFunctor2<CPtrCallArg<ObjectT>, ArgsCollector<Arg2T> >
osgTypedFunctionVoidFunctor2Cptr(void (*pFunc)(ObjectT, Arg2T));

//---------------------------------------------------------------------------
//  osgTypedFunctionFunctor2CPtrRef
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
 */

template <class RetT, class ObjectT, class Arg2T> inline
TypedFunctionFunctor2<RetT,
                      CPtrRefCallArg <ObjectT>,
                      ArgsCollector  <Arg2T> >
    osgTypedFunctionFunctor2CPtrRef    (RetT (*pFunc)(ObjectT &, Arg2T));

/*! \ingroup GrpBaseFunctors
 */

template <class ObjectT, class Arg2T> inline
TypedFunctionVoidFunctor2<CPtrRefCallArg <ObjectT>,
                          ArgsCollector  <Arg2T> >
    osgTypedFunctionVoidFunctor2CPtrRef(void (*pFunc)(ObjectT &, Arg2T));

//---------------------------------------------------------------------------
//  osgTypedMethodFunctor2Ref
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
 */

template <class RetT, class Arg1T, class Arg2T> inline
TypedObjectFunctor2<RetT,
                    RefCallArg   <Arg1T>,
                    ArgsCollector<Arg2T> >
    osgTypedMethodFunctor2Ref(RetT (Arg1T::*pFunc)(Arg2T));

/*! \ingroup GrpBaseFunctors
 */

template <class Arg1T, class Arg2T> inline
TypedObjectVoidFunctor2<RefCallArg   <Arg1T>,
                        ArgsCollector<Arg2T> >
    osgTypedMethodVoidFunctor2Ref(void (Arg1T::*pFunc)(Arg2T));

//---------------------------------------------------------------------------
//  osgTypedMethodFunctor2Ptr
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
 */

template <class RetT, class Arg1T, class Arg2T> inline
TypedObjectFunctor2<RetT,
                    PtrCallArg   <Arg1T>,
                    ArgsCollector<Arg2T> >
    osgTypedMethodFunctor2Ptr    (RetT (Arg1T::*pFunc)(Arg2T));

/*! \ingroup GrpBaseFunctors
 */

template <class Arg1T, class Arg2T> inline
TypedObjectVoidFunctor2<PtrCallArg   <Arg1T>,
                        ArgsCollector<Arg2T> >
    osgTypedMethodVoidFunctor2Ptr(void (Arg1T::*pFunc)(Arg2T));

//---------------------------------------------------------------------------
//  osgTypedMethodFunctor2ObjPtr
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
 */

template <class RetT,  class ObjectT,
          class Arg1T, class Arg2T  > inline
TypedStoredObjectFunctor2<RetT,
                          PtrCallArg   <ObjectT>,
                          PtrCallArg   <Arg1T  >,
                          ArgsCollector<Arg2T  > >
    osgTypedMethodFunctor2ObjPtr    (      ObjectT  *pObj,
                                     RetT (ObjectT::*pFunc)(Arg1T *, Arg2T));

/*! \ingroup GrpBaseFunctors
 */

template <class ObjectT, class Arg1T, class Arg2T> inline
TypedStoredObjectVoidFunctor2<PtrCallArg   <ObjectT>,
                              PtrCallArg   <Arg1T  >,
                              ArgsCollector<Arg2T  > >
    osgTypedMethodVoidFunctor2ObjPtr(      ObjectT  *pObj,
                                     void (ObjectT::*pFunc)(Arg1T *, Arg2T));

//---------------------------------------------------------------------------
//  osgTypedMethodFunctor2ObjPtrCPtrRef
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
 */

template <class RetT,  class ObjectT,
          class Arg1T, class Arg2T  > inline
TypedStoredObjectFunctor2<RetT,
                          PtrCallArg    <ObjectT>,
                          CPtrRefCallArg<Arg1T  >,
                          ArgsCollector <Arg2T  > >
    osgTypedMethodFunctor2ObjPtrCPtrRef(
          ObjectT  *pObj,
    RetT (ObjectT::*pFunc)(Arg1T &, Arg2T));

/*! \ingroup GrpBaseFunctors
 */

template <class ObjectT, class Arg1T, class Arg2T> inline
TypedStoredObjectVoidFunctor2<PtrCallArg    <ObjectT>,
                              CPtrRefCallArg<Arg1T  >,
                              ArgsCollector <Arg2T  > >
    osgTypedMethodVoidFunctor2ObjPtrCPtrRef(
          ObjectT  *pObj,
    void (ObjectT::*pFunc)(Arg1T &, Arg2T));

//---------------------------------------------------------------------------
//  osgTypedMethodFunctor2CPtr
//---------------------------------------------------------------------------

template <class RetT, class ObjectT, class Arg2T>
inline TypedObjectFunctor2<RetT, CPtrCallArg<ObjectT>, ArgsCollector<Arg2T> >
osgTypedMethodFunctor2CPtr(
    typename FunctorBuildFuncType2<RetT,
                                   CPtrCallArg<ObjectT>,
                                   ArgsCollector<Arg2T> >::ObjFuncType pFunc);

template <class ObjectT, class Arg2T>
inline TypedObjectVoidFunctor2<CPtrCallArg<ObjectT>, ArgsCollector<Arg2T> >
osgTypedMethodVoidFunctor2CPtr(
    typename FunctorBuildFuncType2<void,
                                   CPtrCallArg<ObjectT>,
                                   ArgsCollector<Arg2T> >::ObjFuncType pFunc);

//---------------------------------------------------------------------------
//  osgTypedMethodVoidFunctor2CPtrRef
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
 */

template <class ObjectT, class Arg1T> inline
TypedObjectVoidFunctor2<CPtrRefCallArg<ObjectT>,
                        ArgsCollector <Arg1T  > >
    osgTypedMethodVoidFunctor2CPtrRef(

        typename FunctorBuildFuncType2<
            void,
            CPtrRefCallArg<ObjectT>,
            ArgsCollector <Arg1T  >   >::ObjFuncType pFunc);

#endif

//---------------------------------------------------------------------------
//  osgTypedMethodFunctor2ObjCPtrRef
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors2Helper
    \hideinhierarchy
 */

template<class T1, class T2, class T3, class T4>
struct TypedMethodVoidFunctor2ObjCPtrRefFGen
{
    typedef CPtrRefCallArg<T3> CAT3;
    typedef ArgsCollector <T4> ACT4;

    typedef typename CAT3::ArgType Arg1T;
    typedef typename ACT4::Arg1T   Arg2T;

    typedef ArgsCollector2<Arg1T, T4>  ArgColl;

    typedef typename ClassMemFunc2<T1,
                                   typename T2::StoredObjectType,
                                   ArgColl                     >::MemFunc Func;

};

#ifndef OSG_MICROSOFT_COMPILER_ALERT

/*! \ingroup GrpBaseFunctors
 */

template <class ObjectT,
          class Arg1T,
          class Arg2T> inline
TypedStoredObjectVoidFunctor2<CPtrRefCallArg<ObjectT>,
                              CPtrRefCallArg<Arg1T  >,
                              ArgsCollector <Arg2T  > >
    osgTypedMethodVoidFunctor2ObjCPtrRef(

             ObjectT                                              &pObj,

    typename TypedMethodVoidFunctor2ObjCPtrRefFGen<void,
                                                   ObjectT,
                                                   Arg1T,
                                                   Arg2T  >::Func  pFunc);
#endif

//---------------------------------------------------------------------------
//  osgTypedMethodVoidFunctor2ObjCPtrPtr
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors2Helper
    \hideinhierarchy
 */

template<class T1, class T2, class T3, class T4>
struct TypedMethodVoidFunctor2ObjCPtrPtrFGen
{
    typedef PtrCallArg<T3>     CAT3;
    typedef ArgsCollector <T4> ACT4;

    typedef typename CAT3::ArgType Arg1T;
    typedef typename ACT4::Arg1T   Arg2T;

    typedef ArgsCollector2<Arg1T, T4>  ArgColl;

    typedef typename ClassMemFunc2<T1,
                                   typename T2::StoredObjectType,
                                   ArgColl                     >::MemFunc Func;

};

#ifndef OSG_MICROSOFT_COMPILER_ALERT

/*! \ingroup GrpBaseFunctors
 */

template <class ObjectT,
          class Arg1T,
          class Arg2T> inline
TypedStoredObjectVoidFunctor2<CPtrRefCallArg<ObjectT>,
                              PtrCallArg    <Arg1T  >,
                              ArgsCollector <Arg2T  > >
    osgTypedMethodVoidFunctor2ObjCPtrPtr(

             ObjectT                                              &pObj,

    typename TypedMethodVoidFunctor2ObjCPtrPtrFGen<void,
                                                   ObjectT,
                                                   Arg1T,
                                                   Arg2T  >::Func  pFunc);

#endif

//---------------------------------------------------------------------------
//  osgTypedMethodFunctor2BaseCPtrRef
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors2Helper
    \hideinhierarchy
 */

template<class T1, class T2, class T3>
struct TypedMethodFunctor2BaseCPtrRefFGen
{
    typedef ArgsCollector <T3> ArgColl;

    typedef typename ClassMemFunc1<T1,
                                   typename T2::StoredObjectType,
                                   ArgColl                     >::MemFunc Func;
};

#ifndef OSG_MICROSOFT_COMPILER_ALERT

#ifdef __sgi
#pragma set woff 1424
#endif

/*! \ingroup GrpBaseFunctors
 */

template <class RetT,  class ObjectT,
          class Arg1T, class Arg2T> inline
TypedObjectFunctor2<RetT,
                    CPtrRefCallArg<Arg1T>,
                    ArgsCollector <Arg2T> >
    osgTypedMethodFunctor2BaseCPtrRef(

    typename TypedMethodFunctor2BaseCPtrRefFGen<RetT,
                                                ObjectT,
                                                Arg2T  >::Func pFunc);

template <class RetT,  class ObjectT,
          class Arg1T, class Arg2T   >
inline TypedObjectFunctor2<RetT, CPtrCallArg<Arg1T>, ArgsCollector<Arg2T> >
osgTypedMethodFunctor2BaseCPtr(
    typename TypedMethodFunctor2BaseCPtrRefFGen<RetT,
                                                ObjectT,
                                                Arg2T   >::Func pFunc);

#ifdef __sgi
#pragma reset woff 1424
#endif

#endif

OSG_END_NAMESPACE

#include <OSGTypedFunctors.inl>

#endif /* _OSGTYPEDFUNCTORS_H_ */













