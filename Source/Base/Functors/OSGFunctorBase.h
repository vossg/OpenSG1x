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

#ifndef _OSGFUNCTORBASE_H_
#define _OSGFUNCTORBASE_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Enums
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctorsHelper
    \hideinhierarchy
 */

struct DefaultFunctorSizeTraits
{
    typedef 
        void (                          *FuncPointerT        )(void *);
    typedef 
        void (DefaultFunctorSizeTraits::*InstanceFuncPointerT)(void *);

    enum SizesE
    { 
        _uiFuncPointerSize = osgStaticMax<sizeof(FuncPointerT),
                                          sizeof(InstanceFuncPointerT)
                                         >::iMax * 2,
        // !!! The 2 is a nasty kludge to work around problems on Windows :(

        _uiObjectSize      = 64
    };
};

/*! \ingroup GrpBaseFunctorsHelper
    \hideinhierarchy
 */

template <class Argument1T>
struct ArgsCollector
{
    typedef Argument1T ArgType;
    typedef Argument1T Arg1T;
};

/*! \ingroup GrpBaseFunctorsHelper
    \hideinhierarchy
 */

template <class Argument1T, class Argument2T>
struct ArgsCollector2
{
    typedef Argument1T Arg1T;
    typedef Argument2T Arg2T;
};

/*! \ingroup GrpBaseFunctorsHelper
    \hideinhierarchy
 */

template <class ArgT>
struct ObjCallArg
{
    typedef ArgT  ObjType;
    typedef ArgT  ArgType;

    typedef ArgsCollector<ArgType> ArgsC;
};

/*! \ingroup GrpBaseFunctorsHelper
    \hideinhierarchy
 */

template <class ArgT>
struct RefCallArg
{
    typedef ArgT  ObjType;
    typedef ArgT  &ArgType;

    static ObjType *getPtr(ObjType &obj)
    {
        return &obj;
    }
};

/*! \ingroup GrpBaseFunctorsHelper
    \hideinhierarchy
 */

template <class ArgT>
struct PtrCallArg
{
    typedef ArgT                    ObjType;
    typedef ArgT                   *ArgType;

    typedef ArgsCollector<ArgType>  ArgsC;

    static ObjType *getPtr(ObjType *pObj)
    {
        return pObj;
    }
};

/*! \ingroup GrpBaseFunctorsHelper
    \hideinhierarchy
 */

template <class ArgT>
struct CPtrCallArg
{
    typedef typename ArgT::StoredObjectType  ObjType;
    typedef          ArgT                    ArgType;

    typedef          ArgsCollector<ArgType>  ArgsC;

    static ObjType *getPtr(ArgType obj)
    {
        return (&(*obj));
    }
};

/*! \ingroup GrpBaseFunctorsHelper
    \hideinhierarchy
 */

template <class ArgT>
struct CPtrRefCallArg
{
    typedef typename ArgT::StoredObjectType  ObjType;
    typedef          ArgT                   &ArgType;

    typedef          ArgsCollector<ArgType>  ArgsC;

    static ObjType *getPtr(ArgType obj)
    {
        return (&(*obj));
    }
};

/*! \ingroup GrpBaseFunctorsHelper
    \hideinhierarchy
 */

template <class RetT, class ClassT>
struct ClassMemFunc
{
    typedef RetT (ClassT::*MemFunc)(void);
};

/*! \ingroup GrpBaseFunctorsHelper
    \hideinhierarchy
 */

template <class RetT, class ClassT, class ArgsT>
struct ClassMemFunc1
{
    typedef typename ArgsT::Arg1T Arg1T;

    typedef RetT (ClassT::*MemFunc)(Arg1T);
};

/*! \ingroup GrpBaseFunctorsHelper
    \hideinhierarchy
 */

template <class RetT, class ClassT, class ArgsT>
struct ClassMemFunc2
{
    typedef typename ArgsT::Arg1T Arg1T;
    typedef typename ArgsT::Arg2T Arg2T;

    typedef RetT (ClassT::*MemFunc)(Arg1T, Arg2T);
};

/*! \ingroup GrpBaseFunctorsHelper
    \hideinhierarchy
 */

template <class RetT, class CallArgT>
struct FunctorBuildFuncType1
{
    typedef typename CallArgT::ArgType CallArgType;
    typedef typename CallArgT::ObjType ObjType;

    typedef typename ClassMemFunc<RetT, ObjType>::MemFunc ObjFuncType;

    typedef RetT (*FuncFunctionType)(CallArgType);
};

/*! \ingroup GrpBaseFunctorsHelper
    \hideinhierarchy
 */

template <class RetT, class CallArgT, class ArgsT>
struct FunctorBuildObjFuncType1
{
    typedef typename CallArgT              ::ObjType ObjType;
    typedef typename ArgsT                 ::Arg1T   ArgType;

    typedef          ArgsCollector<ArgType>          ArgColl;

    typedef typename ClassMemFunc1<RetT, 
                                   ObjType, 
                                   ArgColl>::MemFunc ObjFuncType;
};

/*! \ingroup GrpBaseFunctorsHelper
    \hideinhierarchy
 */

template <class RetT, class CallArgT, class ArgsT>
struct FunctorBuildFuncType2
{
    typedef typename CallArgT              ::ArgType CallArgType;
    typedef typename CallArgT              ::ObjType ObjType;

    typedef typename ArgsT                 ::Arg1T   ArgType;

    typedef          ArgsCollector<ArgType>          ArgColl;

    typedef typename ClassMemFunc1<RetT, 
                                   ObjType, 
                                   ArgColl>::MemFunc ObjFuncType;

    typedef RetT (*FuncFunctionType)(CallArgType, ArgType);
};

/*! \ingroup GrpBaseFunctorsHelper
    \hideinhierarchy
 */

template <class RetT, class ObjCallArgT, class CallArgT, class ArgsT>
struct FunctorBuildObjFuncType2
{
    typedef typename ObjCallArgT::ObjType ObjType;
    typedef typename CallArgT   ::ArgType Arg1T;
    typedef typename ArgsT      ::Arg1T   Arg2T;

    typedef ArgsCollector2<Arg1T, Arg2T>  ArgColl;

    typedef typename ClassMemFunc2<RetT, 
                                   ObjType, 
                                   ArgColl>::MemFunc ObjFuncType;
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
    \hideinhierarchy
 */

template <class SizeTraitsT = DefaultFunctorSizeTraits>
class FunctorBase 
{     
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~FunctorBase(void); 

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                     Constants                                */
    /*! \{                                                                 */

    static const UInt8 ObjectValid   = 0x01;
    static const UInt8 FuncPtrValid  = 0x02;

    static const UInt8 FunctorActive = 0x80;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Members                                 */
    /*! \{                                                                 */

    UInt8 _data1[SizeTraitsT::_uiObjectSize];
    UInt8 _data2[SizeTraitsT::_uiFuncPointerSize];
    UInt8 _flags;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    FunctorBase(void);
    FunctorBase(const FunctorBase &source);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const FunctorBase &source);
};

OSG_END_NAMESPACE

#include <OSGFunctorBase.inl>

#endif /* _OSGFUNCTORBASE_H_ */


