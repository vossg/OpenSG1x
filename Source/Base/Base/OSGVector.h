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
#include <OSGBaseFunctions.h>

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
//! \ingroup BaseBaseMath

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

//! Vector storage holding 3 elements, for details about how vectors,
//! points and matrices are actually build see \ref vecpointmat.
//! \ingroup BaseBaseMath

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

//! Vector storage holding 4 elements, for details about how vectors,
//! points and matrices are actually build see \ref vecpointmat.
//! \ingroup BaseBaseMath

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




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! Point Interface, for details about how vectors, points and matrices
//! are actually build see \ref vecpointmat.
//! \ingroup BaseBaseMath

#ifdef __sgi
#pragma set woff 1375
#endif

template<class ValueTypeT, class StorageInterfaceT>
class PointInterface : public StorageInterfaceT
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef          StorageInterfaceT                         Inherited;

    typedef typename TypeConstants<ValueTypeT>::RealReturnType RealReturnType;

    typedef          ValueTypeT                                ValueType;

    typedef          VectorInterface<ValueTypeT, 
                                     StorageInterfaceT>        VecInterface;


    typedef          PointInterface <ValueTypeT, 
                                     StorageInterfaceT>        Self;

    static  const    PointInterface                            Null;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

             PointInterface(      void                  );

    explicit PointInterface(const ValueTypeT     *pVals );
    explicit PointInterface(      ValueTypeT     *pVals );

    template<class VectorT> 
#ifndef OSG_MICROSOFT_COMPILER_HACKS
    explicit 
#endif
             PointInterface(const VectorT        &vec   ); 

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

    void setValue(const ValueTypeT     &rVal1);
#endif

    void setValue(const PointInterface &vec     );

    template<class VectorT>
    void setValue(const VectorT        &vec     );

    void setValue(const ValueTypeT     *pVals   );
    void setValue(const Char8          *szString);
    void setValue(      Char8          *szString);

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

          bool            isZero  (      void                     ) const;

          void            negate  (      void                     );

          bool            equals  (const PointInterface &vec,
                                   const ValueTypeT      tolerance) const;

          VecInterface   &subZero (      void                     );
    const VecInterface   &subZero (      void                     ) const;

          RealReturnType  dist    (const PointInterface &vec      ) const;
          RealReturnType  dist2   (const PointInterface &vec      ) const;

          RealReturnType  maxValue(      void                     ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Math                                    */
    /*! \{                                                                 */

    void            operator *=(const ValueTypeT      val );
    void            operator /=(const ValueTypeT      val );

    VecInterface    operator - (const PointInterface &vec ) const;

    PointInterface  operator + (const VecInterface   &vec ) const;

    PointInterface  operator - (const VecInterface   &vec ) const;

    PointInterface  operator * (const ValueTypeT      rVal) const;

    PointInterface  operator - (      void                );

    void            operator +=(const VecInterface   &vec );
    void            operator -=(const VecInterface   &vec );

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

    bool operator <  (const PointInterface &other)  const;

    bool operator == (const PointInterface &other) const;
    bool operator != (const PointInterface &other) const;

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
std::ostream &operator <<(        std::ostream                 &os,
                          const   PointInterface<ValueTypeT,
                                            StorageInterfaceT> &obj);




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! Vector Interface, for details about how vectors, points and matrices
//! are actually build see \ref vecpointmat.
//! \ingroup BaseBaseMath

template<class ValueTypeT, class StorageInterfaceT>
class VectorInterface :
    public PointInterface<ValueTypeT, StorageInterfaceT>
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef          PointInterface<ValueTypeT,
                                    StorageInterfaceT>         Inherited;

    typedef typename TypeConstants<ValueTypeT>::RealReturnType RealReturnType;

    typedef                        ValueTypeT                  ValueType;

    typedef          Inherited                                 PntInterface;

    typedef          VectorInterface<ValueTypeT, 
                                     StorageInterfaceT>        Self;

    static  const    VectorInterface                           Null;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

             VectorInterface(      void                   );

    explicit VectorInterface(const ValueTypeT      *pVals );
    explicit VectorInterface(      ValueTypeT      *pVals );

    template<class VectorT> 
#ifndef OSG_MICROSOFT_COMPILER_HACKS
    explicit 
#endif
             VectorInterface(const VectorT         &vec   );

             VectorInterface(const VectorInterface &source);

#if 0
    /* Constructor which takes one value, remaining entries will be zero;
       Actually this one collides with the template constuctor above,
       so I do not implement this one, any problems with that (GV)
    */

             VectorInterface(const ValueTypeT       rVal1 );
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

    RealReturnType  length       (      void                  ) const;

    void            normalize    (      void                  );

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
    /*! \name                      Conv                                    */
    /*! \{                                                                 */

          PntInterface   &addToZero (void);
    const PntInterface   &addToZero (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Math                                    */
    /*! \{                                                                 */

    VectorInterface operator - (const VectorInterface &vec ) const;
    VectorInterface operator + (const VectorInterface &vec ) const;

    VectorInterface operator * (const ValueTypeT       rVal) const;

    VectorInterface operator - (      void                 ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Assignment                                 */
    /*! \{                                                                 */

    VectorInterface &operator =(const VectorInterface &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Comparison                                 */
    /*! \{                                                                 */

    bool operator <  (const VectorInterface &other) const;

    bool operator == (const VectorInterface &other) const;
    bool operator != (const VectorInterface &other) const;

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
std::ostream &operator <<(        std::ostream                  &os,
                          const   VectorInterface<ValueTypeT,
                                             StorageInterfaceT> &obj);


/*! \var typedef VectorInterface<Real32, VecStorage2<Real32> > Vec2f;
    \brief Vec2f
    \ingroup BaseBaseMath
*/

typedef VectorInterface<Real32, VecStorage2<Real32> > Vec2f;

/*! \var typedef Vec2f *Vec2fP;
    \brief Vec2fP
    \ingroup BaseBaseMath
*/

typedef Vec2f *Vec2fP;

/*! \var typedef VectorInterface<Real32, VecStorage3<Real32> > Vec3f;
    \brief Vec3f
    \ingroup BaseBaseMath
*/

typedef VectorInterface<Real32, VecStorage3<Real32> > Vec3f;

/*! \var typedef Vec3f *Vec3fP;
    \brief Vec3fP
    \ingroup BaseBaseMath
*/
typedef Vec3f *Vec3fP;

/*! \var typedef VectorInterface<Real32, VecStorage4<Real32> > Vec4f;
    \brief Vec4f
    \ingroup BaseBaseMath
*/

typedef VectorInterface<Real32, VecStorage4<Real32> > Vec4f;

/*! \var typedef Vec4f *Vec4fP;
    \brief Vec4fP
    \ingroup BaseBaseMath
*/

typedef Vec4f *Vec4fP;

/*! \var typedef VectorInterface<UInt16, VecStorage2<UInt16> > Vec2s;
    \brief Vec2s
    \ingroup BaseBaseMath
*/

typedef VectorInterface<UInt16, VecStorage2<UInt16> > Vec2s;

/*! \var typedef Vec2s *Vec2sP;
    \brief Vec2sP
    \ingroup BaseBaseMath
*/

typedef Vec2s *Vec2sP;

/*! \var typedef VectorInterface<UInt8, VecStorage4<UInt8> > Vec4ub;
    \brief Vec4ub
    \ingroup BaseBaseMath
*/

typedef VectorInterface<UInt8, VecStorage4<UInt8> > Vec4ub;

/*! \var typedef Vec4ub *Vec4ubP;
    \brief Vec4ubP
    \ingroup BaseBaseMath
*/
typedef Vec4ub *Vec4ubP;


/*! \var typedef PointInterface<Real32, VecStorage2<Real32> > Pnt2f;
    \brief Vec2f
    \ingroup BaseBaseMath
*/

typedef PointInterface<Real32, VecStorage2<Real32> > Pnt2f;

/*! \var typedef Pnt2f *Pnt2fP;
    \brief Vec2fP
    \ingroup BaseBaseMath
*/

typedef Pnt2f *Pnt2fP;


/*! \var typedef PointInterface<Real64, VecStorage2<Real64> > Pnt2d;
    \brief Pnt2d
    \ingroup BaseBaseMath
*/

typedef PointInterface<Real64, VecStorage2<Real64> > Pnt2d;

/*! \var typedef Pnt2d *Pnt2dP;
    \brief Vec2dP
    \ingroup BaseBaseMath
*/

typedef Pnt2d *Pnt2dP;


/*! \var typedef PointInterface<Real32, VecStorage3<Real32> > Pnt3f;
    \brief Vec3f
    \ingroup BaseBaseMath
*/

typedef PointInterface<Real32, VecStorage3<Real32> > Pnt3f;

/*! \var typedef Pnt3f *Pnt3fP;
    \brief Vec3fP
    \ingroup BaseBaseMath
*/

typedef Pnt3f *Pnt3fP;

/*! \var typedef PointInterface<Real64, VecStorage3<Real64> > Pnt3d;
    \brief Vec3d
    \ingroup BaseBaseMath
*/

typedef PointInterface<Real64, VecStorage3<Real64> > Pnt3d;

/*! \var typedef Pnt3d *Pnt3dP;
    \brief Vec3dP
    \ingroup BaseBaseMath
*/

typedef Pnt3d *Pnt3dP;

/*! \var typedef PointInterface<Real32, VecStorage4<Real32> > Pnt4f;
    \brief Vec4f
    \ingroup BaseBaseMath
*/

typedef PointInterface<Real32, VecStorage4<Real32> > Pnt4f;

/*! \var typedef Pnt4f *Pnt4fP;
    \brief Vec4fP
    \ingroup BaseBaseMath
*/

typedef Pnt4f *Pnt4fP;

/*! \var typedef PointInterface<Real64, VecStorage4<Real64> > Pnt4d;
    \brief Pnt4d
    \ingroup BaseBaseMath
*/

typedef PointInterface<Real64, VecStorage4<Real64> > Pnt4d;

/*! \var typedef Pnt4d *Pnt4dP;
    \brief Vec4dP
    \ingroup BaseBaseMath
*/

typedef Pnt4d *Pnt4dP;

/*! \var typedef PointInterface<UInt16, VecStorage2<UInt16> > Pnt2s;
    \brief Vec2s
    \ingroup BaseBaseMath
*/

typedef PointInterface<UInt16, VecStorage2<UInt16> > Pnt2s;

/*! \var typedef Vec2s *Vec2sP;
    \brief Vec2sP
    \ingroup BaseBaseMath
*/

typedef Vec2s *Vec2sP;

OSG_END_NAMESPACE

#include <OSGVector.inl>

#define OSGVECTOR_HEADER_CVSID "@(#)$Id: $"

#endif /* OSGVECTOR_H */


