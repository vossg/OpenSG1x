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

#ifndef _OSGTYPEDFUNCTORBASE_H_
#define _OSGTYPEDFUNCTORBASE_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>
#include <OSGFunctorBase.h>

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

/*! \ingroup GrpBaseFunctors
    \hideinhierarchy
 */

template <class SizeTraitsT = DefaultFunctorSizeTraits>
class TypedFunctorBase : public FunctorBase<SizeTraitsT>
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TypedFunctorBase(void);
    TypedFunctorBase(const TypedFunctorBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~TypedFunctorBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    void operator =(const TypedFunctorBase &source);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    void postCopyConstruct(const TypedFunctorBase &source);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */

    typedef FunctorBase     <SizeTraitsT> Inherited;

    typedef TypedFunctorBase<SizeTraitsT> Self;

    /*! \}                                                                 */
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
    \hideinhierarchy
 */

template <class Parent, class Params>
class TypedFunctionFunctorBase : public Parent
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    typedef typename Params::FunctionF FunctionF;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TypedFunctionFunctorBase(void);
    TypedFunctionFunctorBase(const TypedFunctionFunctorBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */
    
    virtual ~TypedFunctionFunctorBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Set                                    */
    /*! \{                                                                 */

    void setMethod(FunctionF pFunc);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    void operator =(const TypedFunctionFunctorBase &source);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */

    typedef Parent                                   Inherited;

    typedef TypedFunctionFunctorBase<Parent, Params> Self;

    /*! \}                                                                 */
};



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
    \hideinhierarchy
 */

template <class Parent, class Params>
class TypedObjectFunctorBase : public Parent
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    typedef typename Params::ObjMethodF ObjMethodF;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TypedObjectFunctorBase(void);
    TypedObjectFunctorBase(const TypedObjectFunctorBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */
    
    virtual ~TypedObjectFunctorBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void setMethod(ObjMethodF pFunc);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    void operator =(const TypedObjectFunctorBase &source);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */

    typedef Parent                                 Inherited;

    typedef TypedObjectFunctorBase<Parent, Params> Self;

    /*! \}                                                                 */

};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFunctors
    \hideinhierarchy
 */

template <class Parent,
          class Params>
class TypedStoredObjectFunctorBase : public Parent
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    typedef typename Params::ObjMethodF ObjMethodF;

    typedef typename Params::SetObjectT SetObjectT;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TypedStoredObjectFunctorBase(void);
    TypedStoredObjectFunctorBase(const TypedStoredObjectFunctorBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */
    
    virtual ~TypedStoredObjectFunctorBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Set                                    */
    /*! \{                                                                 */

    void setMethod         (ObjMethodF  pFunc);

    void setCalledObject   (SetObjectT  pObj);
    
    void setObjectAndMethod(SetObjectT  pObj, 
                            ObjMethodF  pFunc);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    void operator =(const TypedStoredObjectFunctorBase &source);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */

    typedef Parent                                       Inherited;

    typedef TypedStoredObjectFunctorBase<Parent, Params> Self;

    /*! \}                                                                 */
};

OSG_END_NAMESPACE

#include <OSGTypedFunctorBase.inl>

#endif /* _OSGTYPEDFUNCTORBASE_H_ */

