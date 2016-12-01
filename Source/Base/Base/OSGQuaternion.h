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

#ifndef _OSGQUATERNION_H_
#define _OSGQUATERNION_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGBaseFunctions.h"

#include "OSGVector.h"
#include "OSGMatrix.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseBaseMathObj
 */

template <class ValueTypeT>
class QuaternionBase
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Types                                     */
    /*! \{                                                                 */

    typedef Vector              <ValueTypeT, 3> VectorType;
    typedef Point               <ValueTypeT, 3> PointType;
    typedef TransformationMatrix<ValueTypeT   > MatrixType;


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const QuaternionBase &identity(void                          );

    static       QuaternionBase slerp    (const QuaternionBase &rot0,
                                          const QuaternionBase &rot1,
                                          const ValueTypeT      t       );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

                QuaternionBase(      void                               );
                QuaternionBase(const QuaternionBase &source             );
    explicit    QuaternionBase(const MatrixType     &matrix             );
                QuaternionBase(const VectorType     &axis,
                               const ValueTypeT      angle              );
                QuaternionBase(const VectorType     &rotateFrom,
                               const VectorType     &rotateTo           );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~QuaternionBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Set                                        */
    /*! \{                                                                 */

    void setIdentity      (       void                  );

    void setValueAsAxisRad(const  ValueTypeT *valsP     );
    void setValueAsAxisDeg(const  ValueTypeT *valsP     );
    void setValueAsQuat   (const  ValueTypeT *valsP     );

    void setValueAsAxisRad(const  ValueTypeT  x,
                           const  ValueTypeT  y,
                           const  ValueTypeT  z,
                           const  ValueTypeT  w         );
    void setValueAsAxisDeg(const  ValueTypeT  x,
                           const  ValueTypeT  y,
                           const  ValueTypeT  z,
                           const  ValueTypeT  w         );
    void setValueAsQuat   (const  ValueTypeT  x,
                           const  ValueTypeT  y,
                           const  ValueTypeT  z,
                           const  ValueTypeT  w         );

    void setValue         (const  MatrixType &matrix    );

    void setValueAsAxisRad(const  VectorType &axis,    
                                  ValueTypeT  angle     );
    void setValueAsAxisDeg(const  VectorType &axis,
                                  ValueTypeT  angle     );

    void setValue         (const  VectorType &rotateFrom,
                           const  VectorType &rotateTo  );

    void setValueAsAxisRad(const  Char8       *str      );
    void setValueAsAxisDeg(const  Char8       *str      );
    void setValueAsQuat   (const  Char8       *str      );

    void setValue         (const  ValueTypeT alpha,
                           const  ValueTypeT beta,
                           const  ValueTypeT gamma      );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Get                                        */
    /*! \{                                                                 */

    const ValueTypeT *getValues        (void               ) const;

          void        getValueAsAxisDeg(ValueTypeT &x,
                                        ValueTypeT &y,
                                        ValueTypeT &z,
                                        ValueTypeT &w      ) const;
          void        getValueAsAxisRad(ValueTypeT &x,
                                        ValueTypeT &y,
                                        ValueTypeT &z,
                                        ValueTypeT &w      ) const;
          void        getValueAsQuat   (ValueTypeT &x,
                                        ValueTypeT &y,
                                        ValueTypeT &z,
                                        ValueTypeT &w      ) const;

          void       getValueAsAxisRad (VectorType &axis, 
                                        ValueTypeT &radians) const;
          void       getValueAsAxisDeg (VectorType &axis, 
                                        ValueTypeT &degrees) const;
          void       getValue          (MatrixType &matrix ) const;
          void       getValuesOnly     (MatrixType &matrix ) const;

          ValueTypeT x                 (void               ) const;
          ValueTypeT y                 (void               ) const;
          ValueTypeT z                 (void               ) const;
          ValueTypeT w                 (void               ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Simple Math                               */
    /*! \{                                                                 */

          ValueTypeT      length    (void                        ) const;
          void            normalize (void                        );

          void            invert    (void                        );
    const QuaternionBase  inverse   (void                        ) const;

          void            multVec   (const PointType &src,
                                           PointType &dst        ) const;

          void            scaleAngle(      ValueTypeT scaleFactor);

          void            slerpThis (const QuaternionBase &rot0,
                                     const QuaternionBase &rot1,
                                     const ValueTypeT      t     );

          void            mult      (const QuaternionBase &other );
          void            multLeft  (const QuaternionBase &other );

          bool            equals    (const QuaternionBase &rot,
                                     const ValueTypeT tolerance  ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Element Access                              */
    /*! \{                                                                 */

          ValueTypeT &operator [](const UInt32 index);
    const ValueTypeT &operator [](const UInt32 index) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Math Operators                             */
    /*! \{                                                                 */

    void operator *=(const QuaternionBase &other);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Assignment                                 */
    /*! \{                                                                 */

    QuaternionBase& operator = (const QuaternionBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Comparison                                 */
    /*! \{                                                                 */

    bool operator == (const QuaternionBase &other) const;
    bool operator != (const QuaternionBase &other) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    static void slerp(const QuaternionBase &rot0,
                      const QuaternionBase &rot1,
                            QuaternionBase &result,
                      const ValueTypeT      t);

           void mult (const ValueTypeT rVal1[4],
                      const ValueTypeT rVal2[4]);

    /*==========================  PRIVATE  ================================*/

  private:

    enum ElementIndices
    {
        Q_X = 0,
        Q_Y = 1,
        Q_Z = 2,
        Q_W = 3
    };

    static QuaternionBase _identity;

           ValueTypeT     _quat[4];
};

template <class ValueTypeT> 
OSG_BASE_DLLMAPPING std::ostream &operator <<(
          std::ostream               &os,
    const QuaternionBase<ValueTypeT> &obj);

template <class ValueTypeT> 
OSG_BASE_DLLMAPPING std::istream &operator >>(
    std::istream               &is,
    QuaternionBase<ValueTypeT> &obj);

/*! \var typedef QuaternionBase<Real32> Quaternion;
    \brief Quaternion
    \ingroup GrpBaseBaseMathObj
 */

typedef QuaternionBase<Real32> Quaternion;

OSG_END_NAMESPACE

#include "OSGQuaternion.inl"

#define OSGQUATERNION_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGQUATERNION_H_ */
