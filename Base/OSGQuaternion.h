/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>

#include <OSGVector.h>
#include <OSGMatrix.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseMathQuaternions
 *  \brief QuaternionBase, that's the way how to define rotations.
 */

template <class ValueTypeT>
class OSG_BASE_DLLMAPPING QuaternionBase
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef VectorInterface     <ValueTypeT, 
                                 VecStorage3<ValueTypeT> > VectorType;

    typedef TransformationMatrix<ValueTypeT>               MatrixType;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "QuaternionBase"; };

	static const QuaternionBase &identity(void);

    static       QuaternionBase slerp    (const QuaternionBase &rot0,
                                          const QuaternionBase &rot1, 
                                          const ValueTypeT      t);
    

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    QuaternionBase(void);

    QuaternionBase(const QuaternionBase &source);

    QuaternionBase(ValueTypeT x, 
                   ValueTypeT y, 
                   ValueTypeT z,
                   ValueTypeT w);

    explicit QuaternionBase(const MatrixType &matrix);

    QuaternionBase(const VectorType &axis, 
                   const ValueTypeT  angle);
    
    QuaternionBase(const VectorType &rotateFrom, 
                   const VectorType &rotateTo);

    virtual ~QuaternionBase(void); 

    /*------------------------- set functions -------------------------------*/

    void setIdentity(void);

	void setValueAsAxis(const ValueTypeT *valsP);
	void setValueAsQuat(const ValueTypeT *valsP);

	void setValueAsAxis(const ValueTypeT x, 
                        const ValueTypeT y, 
                        const ValueTypeT z, 
                        const ValueTypeT w);

	void setValueAsQuat(const ValueTypeT x, 
                        const ValueTypeT y, 
                        const ValueTypeT z, 
                        const ValueTypeT w);

	void setValue(const MatrixType &matrix);

	void setValue(const VectorType &axis, ValueTypeT angle);

	void setValue(const VectorType &rotateFrom, 
                  const VectorType &rotateTo);

	void setValue(const char *str);

	void setValue(const ValueTypeT alpha, 
                  const ValueTypeT beta,
                  const ValueTypeT gamma);

    /*------------------------- get functions -------------------------------*/

	const ValueTypeT *getValues(void) const;

	void getValueAsAxis(ValueTypeT &x, 
                        ValueTypeT &y, 
                        ValueTypeT &z,
                        ValueTypeT &w) const;

    void getValueAsQuat(ValueTypeT &x, 
                        ValueTypeT &y, 
                        ValueTypeT &z,
                        ValueTypeT &w) const;

	void getValue(VectorType &axis, ValueTypeT &radians) const;
	void getValue(MatrixType &matrix) const;

	ValueTypeT x(void) const;
	ValueTypeT y(void) const;
	ValueTypeT z(void) const;
	ValueTypeT w(void) const;

    /*------------------------- simple math -------------------------------*/

    ValueTypeT length   (void);
    void       normalize(void);

    void                  invert (void);
	const QuaternionBase  inverse(void) const;

	void multVec   (const VectorType &src, VectorType &dst) const;

	void transform (const VectorType &src, VectorType &dst) const;

	void scaleAngle(ValueTypeT scaleFactor);

    void slerpThis (const QuaternionBase &rot0,
                    const QuaternionBase &rot1, 
                    const ValueTypeT      t);

	void mult      (const QuaternionBase &other);
	void multLeft  (const QuaternionBase &other);

	Bool equals    (const QuaternionBase &rot, 
                    const ValueTypeT tolerance) const;

    /*------------------------- element access ------------------------------*/

	      ValueTypeT &operator [](const UInt32 index);
	const ValueTypeT &operator [](const UInt32 index) const;

    /*------------------------- math operators ------------------------------*/

	void operator *=(const QuaternionBase &other);

    /*------------------------- assignment ----------------------------------*/

    const QuaternionBase& operator = (const QuaternionBase &source);

    /*------------------------- comparison ----------------------------------*/

    bool operator <  (const QuaternionBase &other);
    
	bool operator == (const QuaternionBase &other);
	bool operator != (const QuaternionBase &other);

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static void slerp(const QuaternionBase &rot0,
                      const QuaternionBase &rot1, 
                            QuaternionBase &result,
                      const ValueTypeT      t);

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    void mult(const ValueTypeT rVal1[4], const ValueTypeT rVal2[4]);

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    enum ElementIndices
    {
        Q_X = 0,
        Q_Y = 1,
        Q_Z = 2,
        Q_W = 3
    };

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

    static QuaternionBase _identity;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    ValueTypeT _quat[4];

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

/** \var typedef QuaternionBase<Real32> Quaternion;
 *  \brief Quaternion
 *  \ingroup BaseMathQuaternions
 */

typedef QuaternionBase<Real32> Quaternion;

OSG_END_NAMESPACE

#include <OSGQuaternion.inl>

#endif /* _OSGQUATERNION_H_ */
