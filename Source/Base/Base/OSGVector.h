/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include "OSGConfig.h"
#include "OSGBase.h"
#include "OSGBaseTypes.h"
#include "OSGBaseFunctions.h"

#include <iostream>

OSG_BEGIN_NAMESPACE

template<class ValueTypeT, UInt32 SizeI>
class Vector;

template<class ValueTypeT, UInt32 SizeI>
class Point;


#ifdef __sgi
#pragma set woff 1209
#endif

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! Vector storage holding 2 elements, for details about how vectors,
    points and matrices are actually build see \ref PageBaseMath.
    \ingroup GrpBaseBaseMathObj
 */

template <class ValueTypeT>
class VecStorage2
{
    /*==========================  PUBLIC  =================================*/

  public:

    static const UInt32 _iSize = 2;

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

/*! Vector storage holding 3 elements, for details about how vectors,
    points and matrices are actually build see \ref PageBaseMath.
    \ingroup GrpBaseBaseMathObj
 */

template <class ValueTypeT>
class VecStorage3
{
    /*==========================  PUBLIC  =================================*/

  public:

    static const UInt32 _iSize = 3;

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

/*! Vector storage holding 4 elements, for details about how vectors,
    points and matrices are actually build see \ref PageBaseMath.
    \ingroup GrpBaseBaseMathObj
 */

template <class ValueTypeT>
class VecStorage4
{
    /*==========================  PUBLIC  =================================*/

  public:

    static const UInt32 _iSize = 4;

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


/*! \struct SelectVecStorage<ValueTypeT,SizeI>
    \brief Helper struct to select the correct storage class for vector types.
 */

template <class ValueTypeT, UInt32 SizeI>
struct SelectVecStorage;

template <class ValueTypeT>
struct SelectVecStorage<ValueTypeT, 2>
{
    typedef VecStorage2<ValueTypeT> type;
};

template <class ValueTypeT>
struct SelectVecStorage<ValueTypeT, 3>
{
    typedef VecStorage3<ValueTypeT> type;
};

template <class ValueTypeT>
struct SelectVecStorage<ValueTypeT, 4>
{
    typedef VecStorage4<ValueTypeT> type;
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! Point , for details about how vectors, points and matrices
    are actually build see \ref PageBaseMath.
    \ingroup GrpBaseBaseMathObj
 */

#ifdef __sgi
#pragma set woff 1375
#endif

template<class ValueTypeT, UInt32 SizeI>
class Vector;

template<class ValueTypeT, UInt32 SizeI>
class Point : public SelectVecStorage<ValueTypeT, SizeI>::type
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef typename SelectVecStorage<ValueTypeT, 
                                      SizeI     >::type     Inherited;

    typedef typename TypeTraits<ValueTypeT>::RealReturnType RealReturnType;

    typedef          ValueTypeT                             ValueType;

    typedef          Vector    <ValueTypeT, 
                                SizeI     >                 VectorType;
    typedef          Point     <ValueTypeT, 
                                SizeI     >                 PointType;


    typedef          Point     <ValueTypeT, 
                                SizeI     >                 Self;

    static  const    PointType                              Null;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Point(      void                  );
    
    Point(const ValueTypeT     *pVals );
    Point(      ValueTypeT     *pVals );

    template <class ValueType2T, UInt32 Size2I> 
    Point(const Point<ValueType2T, Size2I> &vec);

    template <class ValueType2T, UInt32 Size2I> 
    Point(const Vector<ValueType2T, Size2I> &vec);

    Point(const Point &source);

    Point(const ValueTypeT rVal1);

    /* Found so far no way to move these constructors to the memory
       interface :-(. I still find them a little bit wrong placed (GV)
    */

    Point(const ValueTypeT rVal1, const ValueTypeT rVal2);

    Point(const ValueTypeT rVal1, const ValueTypeT rVal2,
          const ValueTypeT rVal3);

    Point(const ValueTypeT rVal1, const ValueTypeT rVal2,
          const ValueTypeT rVal3, const ValueTypeT rVal4);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~Point(void);

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

    void setValue           (const ValueTypeT         &rVal1   );
#endif

    void setValue           (const Point              &vec     );

    template <class ValueType2T, UInt32 Size2I> 
    void setValue           (const Point<ValueType2T, 
                                         Size2I     > &vec     );

    void setValue           (const ValueTypeT         *pVals   );
    void setValue           (      ValueTypeT         *pVals   );

    void setValueFromCString(const Char8              *szString);
    void setValueFromCString(      Char8              *szString);

#ifndef OSG_DISABLE_DEPRECATED
    void setValue           (const Char8              *szString);
    void setValue           (      Char8              *szString);
#endif


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

          bool            isZero  (      void                 ) const;

          void            negate  (      void                 );

          bool            equals  (const Point      &vec,
                                   const ValueTypeT  tolerance) const;

          VectorType     &subZero (      void                 );
    const VectorType     &subZero (      void                 ) const;

          RealReturnType  dist    (const Point      &vec      ) const;
          RealReturnType  dist2   (const Point      &vec      ) const;

          RealReturnType  maxValue(      void                 ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Math                                    */
    /*! \{                                                                 */

    void       operator *=(const ValueTypeT  val );
    void       operator /=(const ValueTypeT  val );

    VectorType operator - (const Point      &vec ) const;

    Point      operator + (const VectorType &vec ) const;

    Point      operator - (const VectorType &vec ) const;

    Point      operator * (const ValueTypeT  rVal) const;

    Point      operator - (      void            );

    void       operator +=(const VectorType &vec );
    void       operator -=(const VectorType &vec );

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

    Point &operator =(const Point      &source);
    Point &operator =(const VectorType &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Comparison                                 */
    /*! \{                                                                 */

    bool operator <  (const Point &other)  const;

    bool operator == (const Point &other) const;
    bool operator != (const Point &other) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:
};


template <class ValueTypeT,
          UInt32 SizeI    > inline
Point<ValueTypeT, SizeI>
    operator *(const ValueTypeT         val,
               const Point<ValueTypeT,
                           SizeI     > &vec);

template <class  ValueTypeT,
          UInt32 SizeI      >
OSG_BASE_DLLMAPPING std::ostream &operator <<(
    std::ostream             &os,
    const Point<ValueTypeT, SizeI> &pnt);

template <class  ValueTypeT,
          UInt32 SizeI      >
OSG_BASE_DLLMAPPING std::istream &operator >>(std::istream             &is,
                                              Point<ValueTypeT, SizeI> &pnt);

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! Vector , for details about how vectors, points and matrices
    are actually build see \ref PageBaseMath.
    \ingroup GrpBaseBaseMathObj
 */

template<class ValueTypeT, UInt32 SizeI>
class Vector : public Point<ValueTypeT, SizeI>
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef          Point     <ValueTypeT,
                                SizeI     >                 Inherited;

    typedef typename TypeTraits<ValueTypeT>::RealReturnType RealReturnType;

    typedef          ValueTypeT                             ValueType;

    typedef typename Inherited::PointType                   PointType;
    typedef typename Inherited::VectorType                  VectorType;

    typedef          Vector    <ValueTypeT, 
                                SizeI     >                 Self;

    static  const    Vector                                 Null;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Vector(      void                               );

    Vector(const ValueTypeT                  *pVals );
    Vector(      ValueTypeT                  *pVals );

    template <class ValueType2T, UInt32 Size2I> 
    Vector(const Point<ValueType2T, Size2I>  &vec   );

    template <class ValueType2T, UInt32 Size2I> 
    Vector(const Vector<ValueType2T, Size2I> &vec   );

    Vector(const Vector                      &source);

    Vector(const ValueTypeT                   rVal1 );

    /* Found so far no way to move these constructors to the memory
       interface :-(. I still find them a little bit wrong placed (GV)
    */

    Vector(const ValueTypeT rVal1, const ValueTypeT rVal2);

    Vector(const ValueTypeT rVal1, const ValueTypeT rVal2,
           const ValueTypeT rVal3);

    Vector(const ValueTypeT rVal1, const ValueTypeT rVal2,
           const ValueTypeT rVal3, const ValueTypeT rVal4);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~Vector(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Common Math                                */
    /*! \{                                                                 */

    RealReturnType  length       (      void            ) const;
    RealReturnType  squareLength (      void            ) const;

    void            normalize    (      void            );

    Vector          cross        (const Vector    &vec  ) const;
    Vector          operator %   (const Vector    &vec  ) const;

    void            crossThis    (const Vector    &vec  );

    ValueTypeT      dot          (const Vector    &vec  ) const;
    ValueTypeT      operator *   (const Vector    &vec  ) const;
    ValueTypeT      dot          (const PointType &pnt  ) const;
    ValueTypeT      operator *   (const PointType &pnt  ) const;

    RealReturnType  enclosedAngle(const Vector    &vec  ) const;

    RealReturnType  projectTo    (const Vector    &toVec);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Conv                                    */
    /*! \{                                                                 */

          PointType &addToZero (void);
    const PointType &addToZero (void) const;

          Vector    &subZero   (void);
    const Vector    &subZero   (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Math                                    */
    /*! \{                                                                 */

    Vector operator - (const Vector     &vec ) const;
    Vector operator + (const Vector     &vec ) const;

    Vector operator * (const ValueTypeT  rVal) const;

    Vector operator - (      void            ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Assignment                                 */
    /*! \{                                                                 */

    Vector &operator =(const Vector &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Comparison                                 */
    /*! \{                                                                 */

    bool operator <  (const Vector &other) const;

    bool operator == (const Vector &other) const;
    bool operator != (const Vector &other) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:
};

#ifdef __sgi
#pragma reset woff 1375
#endif

template <class  ValueTypeT,
          UInt32 SizeI     > inline
Vector<ValueTypeT, SizeI>
    operator *(const ValueTypeT          val,
               const Vector<ValueTypeT,
                            SizeI     > &vec);

template <class ValueTypeT,
          UInt32 SizeI     >
OSG_BASE_DLLMAPPING std::ostream &operator <<(
    std::ostream              &os,
    const Vector<ValueTypeT, SizeI> &vec);

template <class  ValueTypeT,
          UInt32 SizeI      >
OSG_BASE_DLLMAPPING std::istream &operator >>(std::istream              &is,
                                              Vector<ValueTypeT, SizeI> &vec);

// Actual Types


/*! \var typedef Vector<UInt8, 2> Vec2ub;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector<UInt8, 2> Vec2ub;

/*! \var typedef Vec2ub *Vec2ubP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec2ub *Vec2ubP;

/*! \var typedef Vector<Int8, 2> Vec2b;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Vector<Int8, 2> Vec2b;
#endif

/*! \var typedef Vec2b *Vec2bP;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Vec2b *Vec2bP;
#endif

/*! \var typedef Vector<UInt16, 2> Vec2us;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector<UInt16, 2> Vec2us;

/*! \var typedef Vec2us *Vec2usP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec2us *Vec2usP;

/*! \var typedef Vector<Int16, 2> Vec2s;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector<Int16, 2> Vec2s;

/*! \var typedef Vec2s *Vec2sP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec2s *Vec2sP;

/*! \var typedef Vector<Real32, 2> Vec2f;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector<Real32, 2> Vec2f;

/*! \var typedef Vec2f *Vec2fP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec2f *Vec2fP;

/*! \var typedef Vector<Real64, 2> Vec2d;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector<Real64, 2> Vec2d;

/*! \var typedef Vec2d *Vec2dP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec2d *Vec2dP;

/*! \var typedef Vector<Real128, 2> Vec2ld;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector<Real128, 2> Vec2ld;

/*! \var typedef Vec2ld *Vec2ldP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec2ld *Vec2ldP;


/*! \var typedef Vector<UInt8, 3> Vec3ub;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector<UInt8, 3> Vec3ub;

/*! \var typedef Vec3ub *Vec3ubP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec3ub *Vec3ubP;

/*! \var typedef Vector<Int8, 3> Vec3b;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Vector<Int8, 3> Vec3b;
#endif

/*! \var typedef Vec3b *Vec3bP;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Vec3b *Vec3bP;
#endif

/*! \var typedef Vector<UInt16, 3> Vec3us;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector<UInt16, 3> Vec3us;

/*! \var typedef Vec3us *Vec3usP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec3us *Vec3usP;

/*! \var typedef Vector<Int16, 3> Vec3s;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector<Int16, 3> Vec3s;

/*! \var typedef Vec3s *Vec3sP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec3s *Vec3sP;

/*! \var typedef Vector<Real32, 3> Vec3f;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector<Real32, 3> Vec3f;

/*! \var typedef Vec3f *Vec3fP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec3f *Vec3fP;

/*! \var typedef Vector<Real64, 3> Vec3d;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector<Real64, 3> Vec3d;

/*! \var typedef Vec3d *Vec3dP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec3d *Vec3dP;

/*! \var typedef Vector<Real128, 3> Vec3ld;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector<Real128, 3> Vec3ld;

/*! \var typedef Vec3ld *Vec3ldP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec3ld *Vec3ldP;


/*! \var typedef Vector<UInt8, 4> Vec4ub;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector<UInt8, 4> Vec4ub;

/*! \var typedef Vec4ub *Vec4ubP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec4ub *Vec4ubP;

/*! \var typedef Vector<Int8, 4> Vec4b;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Vector<Int8, 4> Vec4b;
#endif

/*! \var typedef Vec4b *Vec4bP;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Vec4b *Vec4bP;
#endif

/*! \var typedef Vector<UInt16, 4> Vec4us;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector<UInt16, 4> Vec4us;

/*! \var typedef Vec4us *Vec4usP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec4us *Vec4usP;

/*! \var typedef Vector<Int16, 4> Vec4s;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector<Int16, 4> Vec4s;

/*! \var typedef Vec4s *Vec4sP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec4s *Vec4sP;

/*! \var typedef Vector<Real32, 4> Vec4f;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector<Real32, 4> Vec4f;

/*! \var typedef Vec4f *Vec4fP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec4f *Vec4fP;

/*! \var typedef Vector<Real64, 4> Vec4d;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector<Real64, 4> Vec4d;

/*! \var typedef Vec4d *Vec4dP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec4d *Vec4dP;

/*! \var typedef Vector<Real128, 4> Vec4ld;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vector<Real128, 4> Vec4ld;

/*! \var typedef Vec4ld *Vec4ldP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Vec4ld *Vec4ldP;




/*! \var typedef Point<UInt8, 2> Pnt2ub;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point<UInt8, 2> Pnt2ub;

/*! \var typedef Pnt2ub *Pnt2ubP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt2ub *Pnt2ubP;

/*! \var typedef Point<Int8, 2> Pnt2b;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Point<Int8, 2> Pnt2b;
#endif

/*! \var typedef Pnt2b *Pnt2bP;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Pnt2b *Pnt2bP;
#endif

/*! \var typedef Point<UInt16, 2> Pnt2us;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point<UInt16, 2> Pnt2us;

/*! \var typedef Pnt2us *Pnt2usP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt2us *Pnt2usP;

/*! \var typedef Point<Int16, 2> Pnt2s;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point<Int16, 2> Pnt2s;

/*! \var typedef Pnt2s *Pnt2sP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt2s *Pnt2sP;

/*! \var typedef Point<Real32, 2> Pnt2f;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point<Real32, 2> Pnt2f;

/*! \var typedef Pnt2f *Pnt2fP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt2f *Pnt2fP;

/*! \var typedef Point<Real64, 2> Pnt2d;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point<Real64, 2> Pnt2d;

/*! \var typedef Pnt2d *Pnt2dP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt2d *Pnt2dP;

/*! \var typedef Point<Real128, 2> Pnt2ld;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point<Real128, 2> Pnt2ld;

/*! \var typedef Pnt2ld *Pnt2ldP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt2ld *Pnt2ldP;


/*! \var typedef Point<UInt8, 3> Pnt3ub;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point<UInt8, 3> Pnt3ub;

/*! \var typedef Pnt3ub *Pnt3ubP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt3ub *Pnt3ubP;

/*! \var typedef Point<Int8, 3> Pnt3b;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Point<Int8, 3> Pnt3b;
#endif

/*! \var typedef Pnt3b *Pnt3bP;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Pnt3b *Pnt3bP;
#endif

/*! \var typedef Point<UInt16, 3> Pnt3us;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point<UInt16, 3> Pnt3us;

/*! \var typedef Pnt3us *Pnt3usP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt3us *Pnt3usP;

/*! \var typedef Point<Int16, 3> Pnt3s;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point<Int16, 3> Pnt3s;

/*! \var typedef Pnt3s *Pnt3sP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt3s *Pnt3sP;

/*! \var typedef Point<Real32, 3> Pnt3f;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point<Real32, 3> Pnt3f;

/*! \var typedef Pnt3f *Pnt3fP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt3f *Pnt3fP;

/*! \var typedef Point<Real64, 3> Pnt3d;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point<Real64, 3> Pnt3d;

/*! \var typedef Pnt3d *Pnt3dP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt3d *Pnt3dP;

/*! \var typedef Point<Real128, 3> Pnt3ld;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point<Real128, 3> Pnt3ld;

/*! \var typedef Pnt3ld *Pnt3ldP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt3ld *Pnt3ldP;


/*! \var typedef Point<UInt8, 4> Pnt4ub;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point<UInt8, 4> Pnt4ub;

/*! \var typedef Pnt4ub *Pnt4ubP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt4ub *Pnt4ubP;

/*! \var typedef Point<Int8, 4> Pnt4b;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Point<Int8, 4> Pnt4b;
#endif

/*! \var typedef Pnt4b *Pnt4bP;
    \ingroup GrpBaseBaseMathObj
 */

#ifndef OSG_NO_INT8_PNT
typedef Pnt4b *Pnt4bP;
#endif

/*! \var typedef Point<UInt16, 4> Pnt4us;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point<UInt16, 4> Pnt4us;

/*! \var typedef Pnt4us *Pnt4usP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt4us *Pnt4usP;

/*! \var typedef Point<Int16, 4> Pnt4s;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point<Int16, 4> Pnt4s;

/*! \var typedef Pnt4s *Pnt4sP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt4s *Pnt4sP;

/*! \var typedef Point<Real32, 4> Pnt4f;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point<Real32, 4> Pnt4f;

/*! \var typedef Pnt4f *Pnt4fP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt4f *Pnt4fP;

/*! \var typedef Point<Real64, 4> Pnt4d;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point<Real64, 4> Pnt4d;

/*! \var typedef Pnt4d *Pnt4dP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt4d *Pnt4dP;

/*! \var typedef Point<Real128, 4> Pnt4ld;
    \ingroup GrpBaseBaseMathObj
 */

typedef Point<Real128, 4> Pnt4ld;

/*! \var typedef Pnt4ld *Pnt4ldP;
    \ingroup GrpBaseBaseMathObj
 */

typedef Pnt4ld *Pnt4ldP;


OSG_END_NAMESPACE

#include "OSGVector.inl"


#ifdef __sgi
#pragma reset woff 1209
#endif

#define OSGVECTOR_HEADER_CVSID "@(#)$Id: $"

#endif /* OSGVECTOR_H */


