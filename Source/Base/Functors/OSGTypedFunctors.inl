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
//  osgTypedFunctionFunctor1Ptr
//---------------------------------------------------------------------------


template <class RetT, class Arg1T> inline
TypedFunctionFunctor1<RetT, PtrCallArg<Arg1T> > osgTypedFunctionFunctor1Ptr   (
    RetT (*pFunc)(Arg1T *))
{
    TypedFunctionFunctor1<RetT, PtrCallArg<Arg1T> > returnValue;

    returnValue.setMethod(pFunc);

    return returnValue;
}


template <class Arg1T> inline
TypedFunctionVoidFunctor1< PtrCallArg<Arg1T> > osgTypedFunctionVoidFunctor1Ptr(
    void (*pFunc)(Arg1T *))
{
    TypedFunctionVoidFunctor1< PtrCallArg<Arg1T> > returnValue;

    returnValue.setMethod(pFunc);

    return returnValue;
}


//---------------------------------------------------------------------------
//  osgTypedFunctionFunctor1Ref
//---------------------------------------------------------------------------


template <class RetT, class Arg1T> inline
TypedFunctionFunctor1<RetT, RefCallArg<Arg1T> > osgTypedFunctionFunctor1Ref   (
    RetT (*pFunc)(Arg1T &))
{
    TypedFunctionFunctor1<RetT, RefCallArg<Arg1T> > returnValue;

    returnValue.setMethod(pFunc);

    return returnValue;
}


template <class Arg1T> inline
TypedFunctionVoidFunctor1< RefCallArg<Arg1T> > osgTypedFunctionVoidFunctor1Ref(
    void (*pFunc)(Arg1T &))
{
    TypedFunctionVoidFunctor1< RefCallArg<Arg1T> > returnValue;

    returnValue.setMethod(pFunc);

    return returnValue;
}


//---------------------------------------------------------------------------
//  osgTypedFunctionFunctor1CPtr
//---------------------------------------------------------------------------

template <class RetT, class Arg1T>
inline TypedFunctionFunctor1<RetT, CPtrCallArg<Arg1T> >
osgTypedFunctionFunctor1CPtr(RetT (*pFunc)(Arg1T))
{
    TypedFunctionFunctor1<RetT, CPtrCallArg<Arg1T> > returnValue;

    returnValue.setMethod(pFunc);

    return returnValue;
}

template <class Arg1T> inline
TypedFunctionVoidFunctor1< CPtrCallArg<Arg1T> >
    osgTypedFunctionVoidFunctor1CPtr(void (*pFunc)(Arg1T))
{
    TypedFunctionVoidFunctor1< CPtrCallArg<Arg1T> > returnValue;

    returnValue.setMethod(pFunc);

    return returnValue;
}


//---------------------------------------------------------------------------
//  osgTypedFunctionFunctor1CPtrRef
//---------------------------------------------------------------------------


template <class RetT, class Arg1T> inline
TypedFunctionFunctor1<RetT, CPtrRefCallArg<Arg1T> >
    osgTypedFunctionFunctor1CPtrRef(RetT (*pFunc)(Arg1T &))
{
    TypedFunctionFunctor1<RetT, CPtrRefCallArg<Arg1T> > returnValue;

    returnValue.setMethod(pFunc);

    return returnValue;
}


//---------------------------------------------------------------------------
//  osgTypedFunctionVoidFunctor1CPtrRef
//---------------------------------------------------------------------------


template <class Arg1T> inline
TypedFunctionVoidFunctor1< CPtrRefCallArg<Arg1T> >
    osgTypedFunctionVoidFunctor1CPtrRef(void (*pFunc)(Arg1T &))
{
    TypedFunctionVoidFunctor1< CPtrRefCallArg<Arg1T> > returnValue;

    returnValue.setMethod(pFunc);

    return returnValue;
}


//---------------------------------------------------------------------------
//  osgTypedMethodFunctor1Ref
//---------------------------------------------------------------------------


template <class RetT, class Arg1T> inline
TypedObjectFunctor1<RetT, RefCallArg<Arg1T> > osgTypedMethodFunctor1Ref(
    RetT (Arg1T::*pFunc)())
{
    typedef TypedObjectFunctor1<RetT, RefCallArg<Arg1T> > OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);

    return returnValue;
}

template <class Arg1T> inline
TypedObjectVoidFunctor1< RefCallArg<Arg1T> > osgTypedMethodVoidFunctor1Ref(
    void (Arg1T::*pFunc)())
{
    typedef TypedObjectVoidFunctor1< RefCallArg<Arg1T> > OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);

    return returnValue;
}


//---------------------------------------------------------------------------
//  osgTypedMethodFunctor1Ptr
//---------------------------------------------------------------------------


template <class RetT, class Arg1T> inline
TypedObjectFunctor1<RetT, PtrCallArg<Arg1T> > osgTypedMethodFunctor1Ptr(
    RetT (Arg1T::*pFunc)())
{
    typedef TypedObjectFunctor1<RetT, PtrCallArg<Arg1T> > OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);

    return returnValue;
}

template <class Arg1T> inline
TypedObjectVoidFunctor1< PtrCallArg<Arg1T> > osgTypedMethodVoidFunctor1Ptr(
    void (Arg1T::*pFunc)())
{
    typedef TypedObjectVoidFunctor1< PtrCallArg<Arg1T> > OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);

    return returnValue;
}


//---------------------------------------------------------------------------
//  osgTypedMethodFunctor1ObjPtr
//---------------------------------------------------------------------------


template <class RetT, class ObjectT, class Arg1T> inline
TypedStoredObjectFunctor1<RetT,
                          PtrCallArg<ObjectT>,
                          PtrCallArg<Arg1T  > >
    osgTypedMethodFunctor1ObjPtr(      ObjectT  *pObj,
                                 RetT (ObjectT::*pFunc)(Arg1T *))
{
    typedef TypedStoredObjectFunctor1<RetT,
                                      PtrCallArg<ObjectT>,
                                      PtrCallArg<Arg1T  > > OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);
    returnValue.setCalledObject(pObj);

    return returnValue;
}


template <class ObjectT, class Arg1T> inline
TypedStoredObjectVoidFunctor1<PtrCallArg<ObjectT>,
                              PtrCallArg<Arg1T  > >
    osgTypedMethodVoidFunctor1ObjPtr(      ObjectT  *pObj,
                                     void (ObjectT::*pFunc)(Arg1T *))
{
    typedef TypedStoredObjectVoidFunctor1<PtrCallArg<ObjectT>,
                                          PtrCallArg<Arg1T  > > OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);
    returnValue.setCalledObject(pObj);

    return returnValue;
}


//---------------------------------------------------------------------------
//  osgTypedMethodFunctor1ObjPtrCPtrRef
//---------------------------------------------------------------------------


template <class RetT, class ObjectT, class Arg1T> inline
TypedStoredObjectFunctor1<RetT,
                          PtrCallArg    <ObjectT>,
                          CPtrRefCallArg<Arg1T  > >
    osgTypedMethodFunctor1ObjPtrCPtrRef(      ObjectT  *pObj,
                                        RetT (ObjectT::*pFunc)(Arg1T &))
{
    typedef TypedStoredObjectFunctor1<RetT,
                                      PtrCallArg    <ObjectT>,
                                      CPtrRefCallArg<Arg1T  > > OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);
    returnValue.setCalledObject(pObj);

    return returnValue;
}


template <class ObjectT, class Arg1T> inline
TypedStoredObjectVoidFunctor1<PtrCallArg    <ObjectT>,
                              CPtrRefCallArg<Arg1T  > >
    osgTypedMethodVoidFunctor1ObjPtrCPtrRef(      ObjectT  *pObj,
                                            void (ObjectT::*pFunc)(Arg1T &))
{
    typedef TypedStoredObjectVoidFunctor1<PtrCallArg    <ObjectT>,
                                          CPtrRefCallArg<Arg1T  > > OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);
    returnValue.setCalledObject(pObj);

    return returnValue;
}


//---------------------------------------------------------------------------
//  osgTypedMethodFunctor1CPtr
//---------------------------------------------------------------------------

template <class RetT, class Arg1T>
inline TypedObjectFunctor1<RetT, CPtrCallArg<Arg1T> >
osgTypedMethodFunctor1CPtr(
    typename FunctorBuildFuncType1<RetT,
                                   CPtrCallArg<Arg1T> >::ObjFuncType pFunc)
{
    typedef TypedObjectFunctor1<RetT, CPtrCallArg<Arg1T> > OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);

    return returnValue;
}

template <class Arg1T> inline
TypedObjectVoidFunctor1< CPtrCallArg<Arg1T> >
    osgTypedMethodVoidFunctor1CPtr(
        typename FunctorBuildFuncType1<
            void, CPtrCallArg<Arg1T> >::ObjFuncType pFunc)
{
    typedef TypedObjectVoidFunctor1< CPtrCallArg<Arg1T> > OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);

    return returnValue;
}


//---------------------------------------------------------------------------
//  osgTypedMethodFunctor1CPtrRef
//---------------------------------------------------------------------------


template <class Arg1T> inline
TypedObjectVoidFunctor1< CPtrRefCallArg<Arg1T> >
    osgTypedMethodVoidFunctor1CPtrRef(
        typename FunctorBuildFuncType1<
            void, CPtrRefCallArg<Arg1T> >::ObjFuncType pFunc)
{
    typedef TypedObjectVoidFunctor1< CPtrRefCallArg<Arg1T> > OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);

    return returnValue;
}


//---------------------------------------------------------------------------
//  osgTypedMethodFunctor1ObjCPtr
//---------------------------------------------------------------------------


template <class ObjectT, class Arg1T> inline
TypedStoredObjectVoidFunctor1<
    CPtrCallArg<ObjectT>,
    CPtrCallArg<Arg1T  > > osgTypedMethodVoidFunctor1ObjCPtr(

             ObjectT                                              obj,

    typename TypedMethodVoidFunctor1ObjCPtrFGen<void,
                                                ObjectT,
                                                Arg1T  >::Func pFunc)

{
    typedef TypedStoredObjectVoidFunctor1<CPtrCallArg<ObjectT>,
                                          CPtrCallArg<Arg1T  > > OFunctor;

    OFunctor returnValue;

    returnValue.setMethod      (pFunc);
    returnValue.setCalledObject(obj  );

    return returnValue;
}


//---------------------------------------------------------------------------
//  osgTypedMethodFunctor1ObjCPtrRef
//---------------------------------------------------------------------------


template <class ObjectT, class Arg1T> inline
TypedStoredObjectVoidFunctor1<
    CPtrRefCallArg<ObjectT>,
    CPtrRefCallArg<Arg1T  > > osgTypedMethodVoidFunctor1ObjCPtrRef(

             ObjectT                                              obj,

    typename TypedMethodVoidFunctor1ObjCPtrRefFGen<void,
                                                   ObjectT,
                                                   Arg1T  >::Func pFunc)

{
    typedef TypedStoredObjectVoidFunctor1<CPtrRefCallArg<ObjectT>,
                                          CPtrRefCallArg<Arg1T  > > OFunctor;

    OFunctor returnValue;

    returnValue.setMethod      (pFunc);
    returnValue.setCalledObject(obj  );

    return returnValue;
}


//---------------------------------------------------------------------------
//  osgTypedFunctionFunctor2Ptr
//---------------------------------------------------------------------------


template <class RetT, class ObjectT, class Arg2T> inline
TypedFunctionFunctor2<RetT,
                      PtrCallArg<ObjectT>,
                      ArgsCollector<Arg2T> >
    osgTypedFunctionFunctor2Ptr    (RetT (*pFunc)(ObjectT *, Arg2T))
{
    TypedFunctionFunctor2<RetT,
                          PtrCallArg   <ObjectT>,
                          ArgsCollector<Arg2T  > > returnValue;

    returnValue.setMethod(pFunc);

    return returnValue;
}

template <class ObjectT, class Arg2T> inline
TypedFunctionVoidFunctor2<PtrCallArg <ObjectT>,
                          ArgsCollector<Arg2T> >
    osgTypedFunctionVoidFunctor2Ptr(void (*pFunc)(ObjectT *, Arg2T))
{
    TypedFunctionVoidFunctor2<PtrCallArg   <ObjectT>,
                              ArgsCollector<Arg2T  > > returnValue;

    returnValue.setMethod(pFunc);

    return returnValue;
}


//---------------------------------------------------------------------------
//  osgTypedFunctionFunctor2Ref
//---------------------------------------------------------------------------


template <class RetT, class ObjectT, class Arg2T> inline
TypedFunctionFunctor2<RetT,
                      RefCallArg   <ObjectT>,
                      ArgsCollector<Arg2T  > >
    osgTypedFunctionFunctor2Ref    (RetT (*pFunc)(ObjectT &, Arg2T))
{
    TypedFunctionFunctor2<RetT,
                          RefCallArg<ObjectT>,
                          ArgsCollector<Arg2T> > returnValue;

    returnValue.setMethod(pFunc);

    return returnValue;
}

template <class ObjectT, class Arg2T> inline
TypedFunctionVoidFunctor2<RefCallArg   <ObjectT>,
                          ArgsCollector<Arg2T  > >
    osgTypedFunctionVoidFunctor2Ref(void (*pFunc)(ObjectT &, Arg2T))
{
    TypedFunctionVoidFunctor2<RefCallArg<ObjectT>,
                              ArgsCollector<Arg2T> > returnValue;

    returnValue.setMethod(pFunc);

    return returnValue;
}

//---------------------------------------------------------------------------
//  osgTypedFunctionFunctor2CPtr
//---------------------------------------------------------------------------

template <class RetT, class ObjectT, class Arg2T>
inline TypedFunctionFunctor2<RetT, CPtrCallArg<ObjectT>, ArgsCollector<Arg2T> >
osgTypedFunctionFunctor2CPtr    (RetT (*pFunc)(ObjectT, Arg2T))
{
    TypedFunctionFunctor2<RetT,
                          CPtrCallArg<ObjectT>,
                          ArgsCollector<Arg2T> > returnValue;

    returnValue.setMethod(pFunc);

    return returnValue;
}

template <class ObjectT, class Arg2T>
inline TypedFunctionVoidFunctor2<CPtrCallArg<ObjectT>, ArgsCollector<Arg2T> >
osgTypedFunctionVoidFunctor2Cptr(void (*pFunc)(ObjectT, Arg2T))
{
    TypedFunctionVoidFunctor2<CPtrCallArg<ObjectT>,
                              ArgsCollector<Arg2T> > returnValue;

    returnValue.setMethod(pFunc);

    return returnValue;
}

//---------------------------------------------------------------------------
//  osgTypedFunctionFunctor2CPtrRef
//---------------------------------------------------------------------------

template <class RetT, class ObjectT, class Arg2T> inline
TypedFunctionFunctor2<RetT,
                      CPtrRefCallArg <ObjectT>,
                      ArgsCollector  <Arg2T> >
    osgTypedFunctionFunctor2CPtrRef(RetT (*pFunc)(ObjectT &, Arg2T))
{
    TypedFunctionFunctor2<RetT,
                          CPtrRefCallArg<ObjectT>,
                          ArgsCollector<Arg2T>   > returnValue;

    returnValue.setMethod(pFunc);

    return returnValue;
}

template <class ObjectT, class Arg2T> inline
TypedFunctionVoidFunctor2<CPtrRefCallArg <ObjectT>,
                          ArgsCollector  <Arg2T> >
    osgTypedFunctionVoidFunctor2CPtrRef(void (*pFunc)(ObjectT &, Arg2T))
{
    TypedFunctionVoidFunctor2<CPtrRefCallArg<ObjectT>,
                              ArgsCollector<Arg2T> > returnValue;

    returnValue.setMethod(pFunc);

    return returnValue;
}


//---------------------------------------------------------------------------
//  osgTypedFunctionFunctor2Ref
//---------------------------------------------------------------------------

template <class RetT, class Arg1T, class Arg2T> inline
TypedObjectFunctor2<RetT,
                    RefCallArg   <Arg1T>,
                    ArgsCollector<Arg2T> >
    osgTypedMethodFunctor2Ref(RetT (Arg1T::*pFunc)(Arg2T))
{
    typedef TypedObjectFunctor2<RetT,
                                RefCallArg   <Arg1T>,
                                ArgsCollector<Arg2T> > OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);

    return returnValue;
}

template <class Arg1T, class Arg2T> inline
TypedObjectVoidFunctor2<RefCallArg   <Arg1T>,
                        ArgsCollector<Arg2T> >
    osgTypedMethodVoidFunctor2Ref(void (Arg1T::*pFunc)(Arg2T))
{
    typedef TypedObjectVoidFunctor2<RefCallArg   <Arg1T>,
                                    ArgsCollector<Arg2T> > OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);

    return returnValue;
}


//---------------------------------------------------------------------------
//  osgTypedMethodFunctor2Ptr
//---------------------------------------------------------------------------


template <class RetT, class Arg1T, class Arg2T> inline
TypedObjectFunctor2<RetT,
                    PtrCallArg   <Arg1T>,
                    ArgsCollector<Arg2T> >
    osgTypedMethodFunctor2Ptr(RetT (Arg1T::*pFunc)(Arg2T))
{
    typedef TypedObjectFunctor2<RetT,
                                PtrCallArg   <Arg1T>,
                                ArgsCollector<Arg2T> > OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);

    return returnValue;
}

template <class Arg1T, class Arg2T> inline
TypedObjectVoidFunctor2<PtrCallArg   <Arg1T>,
                        ArgsCollector<Arg2T> >
    osgTypedMethodVoidFunctor2Ptr(void (Arg1T::*pFunc)(Arg2T))
{
    typedef TypedObjectVoidFunctor2<PtrCallArg   <Arg1T>,
                                    ArgsCollector<Arg2T> > OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);

    return returnValue;
}


//---------------------------------------------------------------------------
//  osgTypedMethodFunctor2ObjPtr
//---------------------------------------------------------------------------


template <class RetT,  class ObjectT,
          class Arg1T, class Arg2T  > inline
TypedStoredObjectFunctor2<RetT,
                          PtrCallArg   <ObjectT>,
                          PtrCallArg   <Arg1T  >,
                          ArgsCollector<Arg2T  > >
    osgTypedMethodFunctor2ObjPtr(      ObjectT  *pObj,
                                 RetT (ObjectT::*pFunc)(Arg1T *, Arg2T))
{
    typedef TypedStoredObjectFunctor2<RetT,
                                      PtrCallArg   <ObjectT>,
                                      PtrCallArg   <Arg1T  >,
                                      ArgsCollector<Arg2T  > > OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);
    returnValue.setCalledObject(pObj);

    return returnValue;
}

template <class ObjectT, class Arg1T, class Arg2T> inline
TypedStoredObjectVoidFunctor2<PtrCallArg   <ObjectT>,
                              PtrCallArg   <Arg1T  >,
                              ArgsCollector<Arg2T  > >
    osgTypedMethodVoidFunctor2ObjPtr(      ObjectT  *pObj,
                                     void (ObjectT::*pFunc)(Arg1T *, Arg2T))
{
    typedef TypedStoredObjectVoidFunctor2<PtrCallArg   <ObjectT>,
                                          PtrCallArg   <Arg1T  >,
                                          ArgsCollector<Arg2T  > > OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);
    returnValue.setCalledObject(pObj);

    return returnValue;
}


//---------------------------------------------------------------------------
//  osgTypedMethodFunctor2ObjPtrCPtrRef
//---------------------------------------------------------------------------


template <class RetT,  class ObjectT,
          class Arg1T, class Arg2T  > inline
TypedStoredObjectFunctor2<RetT,
                          PtrCallArg    <ObjectT>,
                          CPtrRefCallArg<Arg1T  >,
                          ArgsCollector <Arg2T  > >
    osgTypedMethodFunctor2ObjPtrCPtrRef(
              ObjectT  *pObj,
        RetT (ObjectT::*pFunc)(Arg1T &, Arg2T))
{
    typedef TypedStoredObjectFunctor2<RetT,
                                      PtrCallArg    <ObjectT>,
                                      CPtrRefCallArg<Arg1T  >,
                                      ArgsCollector <Arg2T  > > OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);
    returnValue.setCalledObject(pObj);

    return returnValue;
}

template <class ObjectT, class Arg1T, class Arg2T> inline
TypedStoredObjectVoidFunctor2<PtrCallArg    <ObjectT>,
                              CPtrRefCallArg<Arg1T  >,
                              ArgsCollector <Arg2T  > >
    osgTypedMethodVoidFunctor2ObjPtrCPtrRef(
              ObjectT  *pObj,
        void (ObjectT::*pFunc)(Arg1T &, Arg2T))
{
    typedef TypedStoredObjectVoidFunctor2<PtrCallArg    <ObjectT>,
                                          CPtrRefCallArg<Arg1T  >,
                                          ArgsCollector <Arg2T  > > OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);
    returnValue.setCalledObject(pObj);

    return returnValue;
}

//---------------------------------------------------------------------------
//  osgTypedMethodFunctor2CPtr
//---------------------------------------------------------------------------

template <class RetT, class ObjectT, class Arg2T>
inline TypedObjectFunctor2<RetT, CPtrCallArg<ObjectT>, ArgsCollector<Arg2T> >
osgTypedMethodFunctor2CPtr(
    typename FunctorBuildFuncType2<RetT,
                                   CPtrCallArg<ObjectT>,
                                   ArgsCollector<Arg2T> >::ObjFuncType pFunc)
{
    typedef TypedObjectFunctor2<RetT,
                                CPtrCallArg<ObjectT>,
                                ArgsCollector<Arg2T> > OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);

    return returnValue;
}

template <class ObjectT, class Arg2T>
inline TypedObjectVoidFunctor2<CPtrCallArg<ObjectT>, ArgsCollector<Arg2T> >
osgTypedMethodVoidFunctor2CPtr(
    typename FunctorBuildFuncType2<void,
                                   CPtrCallArg<ObjectT>,
                                   ArgsCollector<Arg2T> >::ObjFuncType pFunc)
{
    typedef TypedObjectVoidFunctor2<CPtrCallArg<ObjectT>,
                                    ArgsCollector<Arg2T> > OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);

    return returnValue;
}

//---------------------------------------------------------------------------
//  osgTypedMethodVoidFunctor2CPtrRef
//---------------------------------------------------------------------------


template <class ObjectT, class Arg1T> inline
TypedObjectVoidFunctor2<CPtrRefCallArg<ObjectT>,
                        ArgsCollector <Arg1T  > >
    osgTypedMethodVoidFunctor2CPtrRef(

        typename FunctorBuildFuncType2<
            void,
            CPtrRefCallArg<ObjectT>,
            ArgsCollector <Arg1T  >   >::ObjFuncType pFunc)
{
    typedef TypedObjectVoidFunctor2<CPtrRefCallArg<ObjectT>,
                                    ArgsCollector <Arg1T  > > OFunctor;

    OFunctor returnValue;

    returnValue.setMethod(pFunc);

    return returnValue;
}


//---------------------------------------------------------------------------
//  osgTypedMethodFunctor2ObjCPtrPtr
//---------------------------------------------------------------------------

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
                                                   Arg2T  >::Func  pFunc)
{
    typedef TypedStoredObjectVoidFunctor2<CPtrRefCallArg<ObjectT>,
                                          PtrCallArg    <Arg1T  >,
                                          ArgsCollector <Arg2T  > > OFunctor;

    OFunctor returnValue;

    returnValue.setMethod      (pFunc);
    returnValue.setCalledObject(pObj);

    return returnValue;
}


//---------------------------------------------------------------------------
//  osgTypedMethodFunctor2ObjCPtrRef
//---------------------------------------------------------------------------

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
                                                   Arg2T  >::Func  pFunc)
{
    typedef TypedStoredObjectVoidFunctor2<CPtrRefCallArg<ObjectT>,
                                          CPtrRefCallArg<Arg1T  >,
                                          ArgsCollector <Arg2T  > > OFunctor;

    OFunctor returnValue;

    returnValue.setMethod      (pFunc);
    returnValue.setCalledObject(pObj);

    return returnValue;
}


//---------------------------------------------------------------------------
//  osgTypedMethodFunctor2BaseCPtrRef
//---------------------------------------------------------------------------

#ifdef __sgi
#pragma set woff 1424
#endif

template <class RetT,  class ObjectT,
          class Arg1T, class Arg2T> inline
TypedObjectFunctor2<RetT,
                    CPtrRefCallArg<Arg1T>,
                    ArgsCollector <Arg2T> >
    osgTypedMethodFunctor2BaseCPtrRef(

    typename TypedMethodFunctor2BaseCPtrRefFGen<RetT,
                                                ObjectT,
                                                Arg2T  >::Func pFunc)
{
    typedef TypedObjectFunctor2<RetT,
                                CPtrRefCallArg<Arg1T>,
                                ArgsCollector <Arg2T> > OFunctor;

    typedef typename
        FunctorBuildObjFuncType1<RetT,
                                 CPtrRefCallArg<Arg1T>,
                                 ArgsCollector <Arg2T> >::ObjFuncType FuncT;


    OFunctor returnValue;

    returnValue.setMethod(reinterpret_cast<FuncT>(pFunc));

    return returnValue;
}

template <class RetT,  class ObjectT,
          class Arg1T, class Arg2T   >
inline TypedObjectFunctor2<RetT, CPtrCallArg<Arg1T>, ArgsCollector<Arg2T> >
osgTypedMethodFunctor2BaseCPtr(
    typename TypedMethodFunctor2BaseCPtrRefFGen<RetT,
                                                ObjectT,
                                                Arg2T   >::Func pFunc)
{
    typedef TypedObjectFunctor2< RetT,
                                 CPtrCallArg  <Arg1T>,
                                 ArgsCollector<Arg2T> >              OFunctor;

    typedef typename
        FunctorBuildObjFuncType1<RetT,
                                 CPtrCallArg  <Arg1T>,
                                 ArgsCollector<Arg2T> >::ObjFuncType FuncT;

    OFunctor returnValue;

    returnValue.setMethod(reinterpret_cast<FuncT>(pFunc));

    return returnValue;
}

#ifdef __sgi
#pragma reset woff 1424
#endif

OSG_END_NAMESPACE
