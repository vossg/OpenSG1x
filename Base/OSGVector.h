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

#ifndef _OSGVECTOR_H_
#define _OSGVECTOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGBase.h>
#include <OSGBaseTypes.h>

#include <iostream>

OSG_BEGIN_NAMESPACE

template<class ValueTypeT, class StorageInterfaceT>
class VectorInterface;

template<class ValueTypeT, class StorageInterfaceT>
class PointInterface;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! Vector storage holding 2 elements, for details about how vectors,
//! points and matrices are actually build see \ref vecpointmat.
//! \ingroup BaseMathVectors

template <class ValueTypeT>
class OSG_BASE_DLLMAPPING VecStorage2
{
    /*==========================  PUBLIC  =================================*/
  public:

    enum VectorSizeE { _iSize = 2 };

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    VecStorage2(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~VecStorage2(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */

    void       setValues        (const ValueTypeT  rVal1, 
                                 const ValueTypeT  rVal2);

    void       getSeparateValues(      ValueTypeT &rVal1, 
                                       ValueTypeT &rVal2) const;

    ValueTypeT x                (void                   ) const;
    ValueTypeT y                (void                   ) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    ValueTypeT _values[_iSize];

    /*==========================  PRIVATE  ================================*/
  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    VecStorage2(const VecStorage2 &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VecStorage2 &source);
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! Vector storage holding 3 elements, for details about how vectors,
//! points and matrices are actually build see \ref vecpointmat.
//! \ingroup BaseMathVectors

template <class ValueTypeT>
class OSG_BASE_DLLMAPPING VecStorage3
{
    /*==========================  PUBLIC  =================================*/
  public:

    enum VectorSizeE { _iSize = 3 };

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    VecStorage3(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~VecStorage3(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */

    void       setValues        (const ValueTypeT  rVal1,
                                 const ValueTypeT  rVal2,
                                 const ValueTypeT  rVal3);

    void       getSeparateValues(      ValueTypeT &rVal1,
                                       ValueTypeT &rVal2,
                                       ValueTypeT &rVal3) const;

    ValueTypeT x                (void                   ) const;
    ValueTypeT y                (void                   ) const;
    ValueTypeT z                (void                   ) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    ValueTypeT _values[_iSize];

    /*==========================  PRIVATE  ================================*/
  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    VecStorage3(const VecStorage3 &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VecStorage3 &source);
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! Vector storage holding 4 elements, for details about how vectors,
//! points and matrices are actually build see \ref vecpointmat.
//! \ingroup BaseMathVectors

template <class ValueTypeT>
class OSG_BASE_DLLMAPPING VecStorage4
{
    /*==========================  PUBLIC  =================================*/
  public:

    enum VectorSizeE { _iSize = 4 };

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    VecStorage4(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~VecStorage4(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */

    void       setValues        (const ValueTypeT  rVal1,
                                 const ValueTypeT  rVal2,
                                 const ValueTypeT  rVal3,
                                 const ValueTypeT  rVal4);

    void       getSeparateValues(      ValueTypeT &rVal1,
                                       ValueTypeT &rVal2,
                                       ValueTypeT &rVal3,
                                       ValueTypeT &rVal4) const;

    ValueTypeT x                (void                   ) const;
    ValueTypeT y                (void                   ) const;
    ValueTypeT z                (void                   ) const;
    ValueTypeT w                (void                   ) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    ValueTypeT _values[_iSize];

    /*==========================  PRIVATE  ================================*/
  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    VecStorage4(const VecStorage4 &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const VecStorage4 &source);
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! Point Interface, for details about how vectors, points and matrices
//! are actually build see \ref vecpointmat.
//! \ingroup BaseMathVectors

#ifdef __sgi
#pragma set woff 1375
#endif

template<class ValueTypeT, class StorageInterfaceT>
class OSG_BASE_DLLMAPPING PointInterface : public StorageInterfaceT
{
    /*==========================  PUBLIC  =================================*/
  public:

    typedef          StorageInterfaceT                         Inherited;

    typedef typename TypeConstants<ValueTypeT>::RealReturnType RealReturnType;

    typedef          ValueTypeT                                ValueType;

    typedef          VectorInterface<ValueTypeT, 
                                     StorageInterfaceT>        VecInterface;


    static  const    PointInterface                            Null;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    PointInterface(void);

    explicit PointInterface(const ValueTypeT *pVals);
    explicit PointInterface(      ValueTypeT *pVals);

    /*! \brief Constructor which take a lot of types as it's argument :-).
     
       The argument type must provide a _iSize enum entry, a *getValueRef(void)
       function and the value types must be convertable to the current one.
       The main problem is that through the constructor
       VecBase(const ValueTypeT *pVals); and the following cast
       operator const ValueTypeT * (void); you are able to to the
       following :
       \code
       void foo(void)
       {
           ClassWithValueTypeT_*_Cast v2f;
           Vec4f v4f(v2f);
       }
       \endcode
       This will at least give you some array read out of bounds erros;
       So this constructor make the things a little bit more save, but you
       will get nasty error messages from the compiler if the argument does
       not satisfy the requirements given above.
     
       Thanks to that ****** MS Compiler the code must be included within
       the header file, but at least it seems work ;-) (GV)
    */

#ifdef __sgi
#pragma set woff 1209
#endif

    template<class VectorT> 
    explicit PointInterface(const VectorT &vec) : 
        Inherited()
    {
        UInt32 i;
        
        if(_iSize < VectorT::_iSize)
        {
            for(i = 0; i < _iSize; i++)
            {
                _values[i] = vec.getValues()[i];
            }
        }
        else
        {
            for(i = 0; i < VectorT::_iSize; i++)
            {
                _values[i] = vec.getValues()[i];
            }
            for(i = VectorT::_iSize; i < _iSize; i++)
            {
                _values[i] = TypeConstants<ValueTypeT>::getZeroElement();
            }
        }
    }

#ifdef __sgi
#pragma reset woff 1209
#endif

    PointInterface(const PointInterface &source);

#if 0
    /* Constructor which takes one value, remaining entries will be zero;
       Actually this one collides with the template constuctor above,
       so I do not implement this one, any problems with that (GV)
    */

    PointInterface(const ValueTypeT rVal1);
#endif

    /* Found so far no way to move these constructors to the memory
       interface :-(. I still find them a little bit wrong placed (GV)
    */

    PointInterface(const ValueTypeT rVal1, const ValueTypeT rVal2);

    PointInterface(const ValueTypeT rVal1, const ValueTypeT rVal2,
                   const ValueTypeT rVal3);

    PointInterface(const ValueTypeT rVal1, const ValueTypeT rVal2,
                   const ValueTypeT rVal3, const ValueTypeT rVal4);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~PointInterface(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Set Values                                */
    /*! \{                                                                 */

    void setNull (void);

#if 0
    /* set first values, remaining entries will not change;
       Actually this one collides with the template set function below,
       so I do not implement this one, any problems with that (GV)
    */

    void setValue(const ValueTypeT &rVal1);
#endif

    void setValue(const PointInterface &vec);

    /*! \brief Set function which take a lot of types as it's argument :-).
     
       The argument type must provide a _iSize enum entry, a *getValueRef(void)
       function and the value types must be convertable to the current one.
       The main problem is that through the set function
       void setValue(const ValueTypeT *pVals); and the following cast
       operator const ValueTypeT * (void); you are able to to the
       following :
       \code
       void foo(void)
       {
           ClassWithValueTypeT_*_Cast v2f;
           Vec4f v4f;
     
           v4f.setValue(v2f);
       }
       \endcode
       This will at least give you some array read out of bounds erros;
       So this function make the things a little bit more save, but you
       will get nasty error messages from the compiler if the argument does
       not satisfy the requirements given above.
     
       Thanks to that ****** MS Compiler the code must be included within
       the header file, but at least it seems to work ;-) (GV)
    */

#ifdef __sgi
#pragma set woff 1209
#endif

    template<class VectorT>
    void setValue(const VectorT &vec)
    {
        UInt32 i;
        
        for(i = 0;
            i < (_iSize < VectorT::_iSize ? _iSize : VectorT::_iSize);
            i++)
        {
            _values[i] = vec.getValues()[i];
        }
    }

#ifdef __sgi
#pragma reset woff 1209
#endif

    void setValue(const ValueTypeT *pVals);

    void setValue(const Char8      *szString);
    void setValue(      Char8      *szString);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Get Values                                  */
    /*! \{                                                                 */

          ValueTypeT *getValues(void);
    const ValueTypeT *getValues(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Common Math                                */
    /*! \{                                                                 */

          Bool          isZero (void                           ) const;

          void          negate (void                           );

          Bool          equals (const PointInterface &vec,
                                const ValueTypeT      tolerance) const;

          VecInterface &subZero(void                           );
    const VecInterface &subZero(void                           ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Math                                    */
    /*! \{                                                                 */

    void           operator *=(const ValueTypeT      val);
    void           operator /=(const ValueTypeT      val);

    VecInterface   operator - (const PointInterface &vec ) const;

    PointInterface operator + (const VecInterface   &vec ) const;

    PointInterface operator - (const VecInterface   &vec ) const;

    PointInterface operator * (const ValueTypeT      rVal) const;

    PointInterface operator - (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Element Access                             */
    /*! \{                                                                 */

           ValueTypeT &operator[](const UInt32 uiVal);
    const  ValueTypeT &operator[](const UInt32 uiVal) const;

    /* Cast operator, cast VecBase to ValueTypeT *
       Bad Bad idea, in my opion to buggy to be used, use getValues
       Const cast operator, cast VecBase to ValueTypeT *

       operator       ValueTypeT *(void);
       operator const ValueTypeT *(void);
    */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Assignment                                 */
    /*! \{                                                                 */

    PointInterface &operator =(const PointInterface &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Comparison                                 */
    /*! \{                                                                 */

    Bool operator <  (const PointInterface &other)  const;

    Bool operator == (const PointInterface &other) const;
    Bool operator != (const PointInterface &other) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*==========================  PRIVATE  ================================*/
  private:
};


template <class ValueTypeT,
          class StorageInterfaceT> inline
PointInterface<ValueTypeT, StorageInterfaceT>
    operator *(const ValueTypeT                         val,
               const PointInterface<ValueTypeT,
                                    StorageInterfaceT> &vec);

template <class ValueTypeT,
          class StorageInterfaceT> inline
ostream &operator <<(ostream                                   &os,
                     const   PointInterface<ValueTypeT,
                                            StorageInterfaceT> &obj);

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! Vector Interface, for details about how vectors, points and matrices
//! are actually build see \ref vecpointmat.
//! \ingroup BaseMathVectors

template<class ValueTypeT, class StorageInterfaceT>
class OSG_BASE_DLLMAPPING VectorInterface :
    public PointInterface<ValueTypeT, StorageInterfaceT>
{
    /*==========================  PUBLIC  =================================*/
  public:

    typedef          PointInterface<ValueTypeT,
                                    StorageInterfaceT>         Inherited;

    typedef typename TypeConstants<ValueTypeT>::RealReturnType RealReturnType;

    typedef                        ValueTypeT                  ValueType;

    typedef          Inherited                                 PntInterface;


    static  const    VectorInterface                           Null;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    VectorInterface(void);

    explicit VectorInterface(const ValueTypeT *pVals);
    explicit VectorInterface(      ValueTypeT *pVals);

    /*! \brief Constructor which take a lot of types as it's argument :-).
     
       The argument type must provide a _iSize enum entry, a *getValueRef(void)
       function and the value types must be convertable to the current one.
       The main problem is that through the constructor
       VecBase(const ValueTypeT *pVals); and the following cast
       operator const ValueTypeT * (void); you are able to to the
       following :
       \code
       void foo(void)
       {
           ClassWithValueTypeT_*_Cast v2f;
           Vec4f v4f(v2f);
       }
       \endcode
       This will at least give you some array read out of bounds erros;
       So this constructor make the things a little bit more save, but you
       will get nasty error messages from the compiler if the argument does
       not satisfy the requirements given above.
     
       Thanks to that ****** MS Compiler the code must be included within
       the header file, but at least it seems work ;-) (GV)
    */

#ifdef __sgi
#pragma set woff 1209
#endif

    template<class VectorT> 
    explicit VectorInterface(const VectorT &vec) : Inherited()
    {
        UInt32 i;
        
        if(_iSize < VectorT::_iSize)
        {
            for(i = 0; i < _iSize; i++)
            {
                _values[i] = vec.getValues()[i];
            }
        }
        else
        {
            for(i = 0; i < VectorT::_iSize; i++)
            {
                _values[i] = vec.getValues()[i];
            }
            for(i = VectorT::_iSize; i < _iSize; i++)
            {
                _values[i] = TypeConstants<ValueTypeT>::getZeroElement();
            }
        }
    }

#ifdef __sgi
#pragma reset woff 1209
#endif

    VectorInterface(const VectorInterface &source);

#if 0
    /* Constructor which takes one value, remaining entries will be zero;
       Actually this one collides with the template constuctor above,
       so I do not implement this one, any problems with that (GV)
    */

    VectorInterface(const ValueTypeT rVal1);
#endif

    /* Found so far no way to move these constructors to the memory
       interface :-(. I still find them a little bit wrong placed (GV)
    */

    VectorInterface(const ValueTypeT rVal1, const ValueTypeT rVal2);

    VectorInterface(const ValueTypeT rVal1, const ValueTypeT rVal2,
                    const ValueTypeT rVal3);

    VectorInterface(const ValueTypeT rVal1, const ValueTypeT rVal2,
                    const ValueTypeT rVal3, const ValueTypeT rVal4);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~VectorInterface(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Common Math                                */
    /*! \{                                                                 */

    RealReturnType  length       (void)                         const;

    void            normalize    (void);

    VectorInterface cross        (const VectorInterface &vec  ) const;
    VectorInterface operator %   (const VectorInterface &vec  ) const;

    void            crossThis    (const VectorInterface &vec  );

    ValueTypeT      dot          (const VectorInterface &vec  ) const;
    ValueTypeT      operator *   (const VectorInterface &vec  ) const;
    ValueTypeT      dot          (const PntInterface    &pnt  ) const;
    ValueTypeT      operator *   (const PntInterface    &pnt  ) const;

    RealReturnType  enclosedAngle(const VectorInterface &vec  ) const;

    RealReturnType  projectTo    (const VectorInterface &toVec);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Math                                    */
    /*! \{                                                                 */

    void            operator +=(const VectorInterface &vec );
    void            operator -=(const VectorInterface &vec );

    VectorInterface operator - (const VectorInterface &vec ) const;
    VectorInterface operator + (const VectorInterface &vec ) const;

    VectorInterface operator * (const ValueTypeT       rVal) const;

    VectorInterface operator - (void)                        const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Assignment                                 */
    /*! \{                                                                 */

    VectorInterface &operator =(const VectorInterface &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Comparison                                 */
    /*! \{                                                                 */

    Bool operator <  (const VectorInterface &other) const;

    Bool operator == (const VectorInterface &other) const;
    Bool operator != (const VectorInterface &other) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*==========================  PRIVATE  ================================*/
  private:
};

#ifdef __sgi
#pragma reset woff 1375
#endif

template <class ValueTypeT,
          class StorageInterfaceT> inline
VectorInterface<ValueTypeT, StorageInterfaceT>
    operator *(const ValueTypeT                          val,
               const VectorInterface<ValueTypeT,
                                     StorageInterfaceT> &vec);

template <class ValueTypeT,
          class StorageInterfaceT> inline
ostream &operator <<(        ostream                            &os,
                     const   VectorInterface<ValueTypeT,
                                             StorageInterfaceT> &obj);


/*! \var typedef VectorInterface<Real32, VecStorage2<Real32> > Vec2f;
    \brief Vec2f
    \ingroup BaseMathVectors
*/

typedef VectorInterface<Real32, VecStorage2<Real32> > Vec2f;

/*! \var typedef Vec2f *Vec2fP;
    \brief Vec2fP
    \ingroup BaseMathVectors
*/

typedef Vec2f *Vec2fP;

/*! \var typedef VectorInterface<Real32, VecStorage3<Real32> > Vec3f;
    \brief Vec3f
    \ingroup BaseMathVectors
*/

typedef VectorInterface<Real32, VecStorage3<Real32> > Vec3f;

/*! \var typedef Vec3f *Vec3fP;
    \brief Vec3fP
    \ingroup BaseMathVectors
*/
typedef Vec3f *Vec3fP;

/*! \var typedef VectorInterface<Real32, VecStorage4<Real32> > Vec4f;
    \brief Vec4f
    \ingroup BaseMathVectors
*/

typedef VectorInterface<Real32, VecStorage4<Real32> > Vec4f;

/*! \var typedef Vec4f *Vec4fP;
    \brief Vec4fP
    \ingroup BaseMathVectors
*/

typedef Vec4f *Vec4fP;

/*! \var typedef VectorInterface<UInt16, VecStorage2<UInt16> > Vec2s;
    \brief Vec2s
    \ingroup BaseMathVectors
*/

typedef VectorInterface<UInt16, VecStorage2<UInt16> > Vec2s;

/*! \var typedef Vec2s *Vec2sP;
    \brief Vec2sP
    \ingroup BaseMathVectors
*/

typedef Vec2s *Vec2sP;

/*! \var typedef VectorInterface<UInt8, VecStorage4<UInt8> > Vec4ub;
    \brief Vec4ub
    \ingroup BaseMathVectors
*/

typedef VectorInterface<UInt8, VecStorage4<UInt8> > Vec4ub;

/*! \var typedef Vec4ub *Vec4ubP;
    \brief Vec4ubP
    \ingroup BaseMathVectors
*/
typedef Vec4ub *Vec4ubP;


/*! \var typedef PointInterface<Real32, VecStorage2<Real32> > Pnt2f;
    \brief Vec2f
    \ingroup BaseMathVectors
*/

typedef PointInterface<Real32, VecStorage2<Real32> > Pnt2f;

/*! \var typedef Pnt2f *Pnt2fP;
    \brief Vec2fP
    \ingroup BaseMathVectors
*/

typedef Pnt2f *Pnt2fP;

/*! \var typedef PointInterface<Real32, VecStorage3<Real32> > Pnt3f;
    \brief Vec3f
    \ingroup BaseMathVectors
*/

typedef PointInterface<Real32, VecStorage3<Real32> > Pnt3f;

/*! \var typedef Pnt3f *Pnt3fP;
    \brief Vec3fP
    \ingroup BaseMathVectors
*/

typedef Pnt3f *Pnt3fP;

/*! \var typedef PointInterface<Real64, VecStorage3<Real64> > Pnt3d;
    \brief Vec3d
    \ingroup BaseMathVectors
*/

typedef PointInterface<Real64, VecStorage3<Real64> > Pnt3d;

/*! \var typedef Pnt3d *Pnt3dP;
    \brief Vec3dP
    \ingroup BaseMathVectors
*/

typedef Pnt3d *Pnt3dP;

/*! \var typedef PointInterface<Real32, VecStorage4<Real32> > Pnt4f;
    \brief Vec4f
    \ingroup BaseMathVectors
*/

typedef PointInterface<Real32, VecStorage4<Real32> > Pnt4f;

/*! \var typedef Pnt4f *Pnt4fP;
    \brief Vec4fP
    \ingroup BaseMathVectors
*/

typedef Pnt4f *Pnt4fP;

/*! \var typedef PointInterface<UInt16, VecStorage2<UInt16> > Pnt2s;
    \brief Vec2s
    \ingroup BaseMathVectors
*/

typedef PointInterface<UInt16, VecStorage2<UInt16> > Pnt2s;

/*! \var typedef Vec2s *Vec2sP;
    \brief Vec2sP
    \ingroup BaseMathVectors
*/

typedef Vec2s *Vec2sP;

OSG_END_NAMESPACE

#include <OSGVector.inl>

#define OSGVECTOR_HEADER_CVSID "@(#)$Id: $"

#endif /* OSGVECTOR_H */


