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

#ifndef _OSGMATRIX_H_
#define _OSGMATRIX_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGVector.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

template <class ValueTypeT> class QuaternionBase;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseMathMatrices
 *  \brief TransformationMatrix, for details about the vector, point and
 *  matrix desing see \ref vecpointmat
 */

template<class ValueTypeT>
class OSG_BASE_DLLMAPPING TransformationMatrix
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef                 ValueTypeT                ValueType;
    typedef VectorInterface<ValueTypeT, 
                            VecStorage4<ValueTypeT> > VectorType;

    typedef QuaternionBase <ValueType>                QuaternionType;

    typedef VectorInterface<ValueTypeT, 
                            VecStorage3<ValueTypeT> > VectorType3f;

    typedef PointInterface<ValueTypeT, 
                           VecStorage3<ValueTypeT> > PointType3f;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "TransformationMatrix";};

	static const TransformationMatrix &identity(void);

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    TransformationMatrix(void);

    TransformationMatrix(const TransformationMatrix &source);

    TransformationMatrix(const VectorType3f &vector1,
                         const VectorType3f &vector2,
                         const VectorType3f &vector3);
    
    TransformationMatrix(const VectorType3f &vector1,
                         const VectorType3f &vector2,
                         const VectorType3f &vector3,
                         const VectorType3f &vector4);
    
    TransformationMatrix(const ValueTypeT rVal00,
                         const ValueTypeT rVal10,
                         const ValueTypeT rVal20,
                         const ValueTypeT rVal30,
                         
                         const ValueTypeT rVal01,
                         const ValueTypeT rVal11,
                         const ValueTypeT rVal21,
                         const ValueTypeT rVal31,
                         
                         const ValueTypeT rVal02,
                         const ValueTypeT rVal12,
                         const ValueTypeT rVal22,
                         const ValueTypeT rVal32,
                         
                         const ValueTypeT rVal03,
                         const ValueTypeT rVal13,
                         const ValueTypeT rVal23,
                         const ValueTypeT rVal33);
    
    ~TransformationMatrix(void); 

    /*------------------------- set functions -------------------------------*/

	void setIdentity(void);

    void setValue(const TransformationMatrix &mat);

    void setValue(const VectorType3f &vector1,
                  const VectorType3f &vector2,
                  const VectorType3f &vector3);
    
    void setValue(const VectorType3f &vector1,
                  const VectorType3f &vector2,
                  const VectorType3f &vector3,
                  const VectorType3f &vector4);

    void setValue(const ValueTypeT rVal00,
                  const ValueTypeT rVal10,
                  const ValueTypeT rVal20,
                  const ValueTypeT rVal30,
                  
                  const ValueTypeT rVal01,
                  const ValueTypeT rVal11,
                  const ValueTypeT rVal21,
                  const ValueTypeT rVal31,
                  
                  const ValueTypeT rVal02,
                  const ValueTypeT rVal12,
                  const ValueTypeT rVal22,
                  const ValueTypeT rVal32,
                  
                  const ValueTypeT rVal03,
                  const ValueTypeT rVal13,
                  const ValueTypeT rVal23,
                  const ValueTypeT rVal33);


    void setValueTransposed(const ValueTypeT rVal00,
                            const ValueTypeT rVal01,
                            const ValueTypeT rVal02,
                            const ValueTypeT rVal03,
                            
                            const ValueTypeT rVal10,
                            const ValueTypeT rVal11,
                            const ValueTypeT rVal12,
                            const ValueTypeT rVal13,
                            
                            const ValueTypeT rVal20,
                            const ValueTypeT rVal21,
                            const ValueTypeT rVal22,
                            const ValueTypeT rVal23,
                            
                            const ValueTypeT rVal30,
                            const ValueTypeT rVal31,
                            const ValueTypeT rVal32,
                            const ValueTypeT rVal33);
    
    void setValue(const ValueTypeT   *pMat, Bool bTransposed = true);
    void setValue(const VectorType   *pMat);
#ifndef WIN32
    void setValue(const VectorType3f *pMat);
#endif

    /*------------------------- get functions -------------------------------*/

    ValueTypeT *getValues(void);
    
    /*---------------------- create transformation --------------------------*/

	void setScale    (const ValueTypeT s);
	void setScale    (const ValueTypeT sx, const ValueTypeT sy, 
					  const ValueTypeT sz);
	void setScale    (const VectorType3f &s);

    void setTranslate(const ValueTypeT tx,
                      const ValueTypeT ty,
                      const ValueTypeT tz);
	void setTranslate(const VectorType3f &t);
	void setTranslate(const PointType3f &t);

	void setRotate   (const QuaternionType &q);

	void setTransform(const VectorType3f   &translation,
	                  const QuaternionType &rotation,
	                  const VectorType3f   &scaleFactor,
	                  const QuaternionType &scaleOrientation,
	                  const VectorType3f   &center);

	void setTransform(const VectorType3f   &t, 
                      const QuaternionType &r,
	                  const VectorType3f   &s);

	void setTransform(const VectorType3f   &t, 
                      const QuaternionType &r,
	                  const VectorType3f   &s, 
                      const QuaternionType &so);

    /*---------------------- get transformation parts -----------------------*/

	void getTransform(VectorType3f   &translation, 
                      QuaternionType &rotation,
	                  VectorType3f   &scaleFactor, 
                      QuaternionType &scaleOrientation,
	                  VectorType3f   &center) const;

	void getTransform(VectorType3f   &translation, 
                      QuaternionType &rotation,
	                  VectorType3f   &scaleFactor, 
                      QuaternionType &scaleOrientation) const;

	Bool factor(TransformationMatrix &r, 
                VectorType3f         &s, 
                TransformationMatrix &u,
                VectorType3f         &t, 
                TransformationMatrix &proj) const;
    
    /*------------------------ transform objects ---------------------------*/

	void multMatrixPnt(const PointType3f &src, 
                             PointType3f &dst) const;

	void multMatrixPnt(      PointType3f &pnt) const;


	void multFullMatrixPnt(const PointType3f &src, 
								 PointType3f &dst) const;

	void multFullMatrixPnt(      PointType3f &pnt) const;

	void multMatrixVec(const VectorType3f &src, 
                             VectorType3f &dst) const;

	void multMatrixVec(      VectorType3f &vec) const;

    void transform(const PointType3f &src, 
                         PointType3f &dest) const;

    void transform(PointType3f &vec) const;

    void transform(const VectorType3f &src, 
                         VectorType3f &dest) const;

    void transform(VectorType3f &vec) const;


    /*------------------------- simple math ---------------------------------*/

    Bool       equals(const TransformationMatrix &matrix, 
                      const ValueType             tolerance) const;

    ValueTypeT det3(void) const;
    ValueTypeT det (void) const;

    Bool inverse   (TransformationMatrix &result) const;
    Bool invert    (void);
    Bool invertFrom(const TransformationMatrix &matrix);

    Bool inverse3   (TransformationMatrix &result) const;
    Bool invert3    (void);
    Bool invertFrom3(const TransformationMatrix &matrix);

    void mult    (const TransformationMatrix &matrix);
    void multLeft(const TransformationMatrix &matrix);

    Bool transposed   (TransformationMatrix &result) const;
    Bool transpose    (void);
    Bool transposeFrom(const TransformationMatrix &matrix);

    /*------------------------- elemen acess --------------------------------*/

          VectorType &operator [](UInt32 uiIndex);
    const VectorType &operator [](UInt32 uiIndex) const;

    /*------------------------- assignment ----------------------------------*/
    
    TransformationMatrix<ValueTypeT> &operator =(
        const TransformationMatrix &source);

    /*------------------------- comparison ----------------------------------*/

	Bool operator == (const TransformationMatrix &other);
	Bool operator != (const TransformationMatrix &other);

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

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    VectorType _matrix[4];

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    ValueTypeT rowMulCol4(const TransformationMatrix &gRowMat, 
                                 UInt32                iRow, 
                          const TransformationMatrix &gColMat, 
                                 UInt32                iColumn) const;

    ValueTypeT det2(const ValueTypeT a1, 
                    const ValueTypeT a2,
                    const ValueTypeT b1, 
                    const ValueTypeT b2) const;

    ValueTypeT det3(const ValueTypeT a1, 
                    const ValueTypeT a2, 
                    const ValueTypeT a3,
                    const ValueTypeT b1, 
                    const ValueTypeT b2, 
                    const ValueTypeT b3,
                    const ValueTypeT c1, 
                    const ValueTypeT c2, 
                    const ValueTypeT c3) const;

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

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

    static TransformationMatrix _identityMatrix;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

/** \var typedef TransformationMatrix<Real32> Matrix;
 *  \brief Matrix
 *  \ingroup BaseMathMatrices
 */

typedef TransformationMatrix<Real32> Matrix;

/** \var typedef TransformationMatrix<Real32> Matrix4f;
 *  \brief Matrix4f
 *  \ingroup BaseMathMatrices
 */

typedef TransformationMatrix<Real32> Matrix4f;

OSG_END_NAMESPACE

#include <OSGMatrix.inl>

#endif /* _OSGMATRIX_H_ */


