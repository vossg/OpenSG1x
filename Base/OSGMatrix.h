/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
 *                                                                           *
 *          contact: {reiners|vossg}@igd.fhg.de, jbehr@zgdv.de               *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

template <class OSGValueTypeT> class OSGQuaternionBase;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseMathMatrices
 *  \brief OSGTransformationMatrix, for details about the vector, point and
 *  matrix desing see \ref vecpointmat
 */

template<class OSGValueTypeT>
class OSGTransformationMatrix
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef            OSGValueTypeT                           OSGValueType;
    typedef OSGVectorInterface<OSGValueTypeT, 
                               OSGVecStorage4<OSGValueTypeT> > OSGVectorType;

    typedef OSGQuaternionBase<OSGValueType>                OSGQuaternionType;

    typedef OSGVectorInterface<OSGValueTypeT, 
                       OSGVecStorage3<OSGValueTypeT> >        OSGVectorType3f;

    typedef OSGPointInterface<OSGValueTypeT, 
                       OSGVecStorage3<OSGValueTypeT> >        OSGPointType3f;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "OSGTransformationMatrix";};

	static const OSGTransformationMatrix &identity(void);

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGTransformationMatrix(void);

    OSGTransformationMatrix(const OSGTransformationMatrix &source);

    OSGTransformationMatrix(const OSGVectorType3f &vector1,
                            const OSGVectorType3f &vector2,
                            const OSGVectorType3f &vector3);
    
    OSGTransformationMatrix(const OSGVectorType3f &vector1,
                            const OSGVectorType3f &vector2,
                            const OSGVectorType3f &vector3,
                            const OSGVectorType3f &vector4);

    OSGTransformationMatrix(const OSGValueTypeT rVal00,
                            const OSGValueTypeT rVal10,
                            const OSGValueTypeT rVal20,
                            const OSGValueTypeT rVal30,
                            
                            const OSGValueTypeT rVal01,
                            const OSGValueTypeT rVal11,
                            const OSGValueTypeT rVal21,
                            const OSGValueTypeT rVal31,
                            
                            const OSGValueTypeT rVal02,
                            const OSGValueTypeT rVal12,
                            const OSGValueTypeT rVal22,
                            const OSGValueTypeT rVal32,
                            
                            const OSGValueTypeT rVal03,
                            const OSGValueTypeT rVal13,
                            const OSGValueTypeT rVal23,
                            const OSGValueTypeT rVal33);
    
    ~OSGTransformationMatrix(void); 

    /*------------------------- set functions -------------------------------*/

	void setIdentity(void);

    void setValue(const OSGTransformationMatrix &mat);

    void setValue(const OSGVectorType3f &vector1,
                  const OSGVectorType3f &vector2,
                  const OSGVectorType3f &vector3);
    
    void setValue(const OSGVectorType3f &vector1,
                  const OSGVectorType3f &vector2,
                  const OSGVectorType3f &vector3,
                  const OSGVectorType3f &vector4);

    void setValue(const OSGValueTypeT rVal00,
                  const OSGValueTypeT rVal10,
                  const OSGValueTypeT rVal20,
                  const OSGValueTypeT rVal30,
                  
                  const OSGValueTypeT rVal01,
                  const OSGValueTypeT rVal11,
                  const OSGValueTypeT rVal21,
                  const OSGValueTypeT rVal31,
                  
                  const OSGValueTypeT rVal02,
                  const OSGValueTypeT rVal12,
                  const OSGValueTypeT rVal22,
                  const OSGValueTypeT rVal32,
                  
                  const OSGValueTypeT rVal03,
                  const OSGValueTypeT rVal13,
                  const OSGValueTypeT rVal23,
                  const OSGValueTypeT rVal33);


    void setValueTransposed(
				  const OSGValueTypeT rVal00,
                  const OSGValueTypeT rVal01,
                  const OSGValueTypeT rVal02,
                  const OSGValueTypeT rVal03,
                  
                  const OSGValueTypeT rVal10,
                  const OSGValueTypeT rVal11,
                  const OSGValueTypeT rVal12,
                  const OSGValueTypeT rVal13,
                  
                  const OSGValueTypeT rVal20,
                  const OSGValueTypeT rVal21,
                  const OSGValueTypeT rVal22,
                  const OSGValueTypeT rVal23,
                  
                  const OSGValueTypeT rVal30,
                  const OSGValueTypeT rVal31,
                  const OSGValueTypeT rVal32,
                  const OSGValueTypeT rVal33);

    void setValue(const OSGValueTypeT   *pMat, OSGBool bTransposed = true);
    void setValue(const OSGVectorType   *pMat);
#ifndef WIN32
    void setValue(const OSGVectorType3f *pMat);
#endif

    /*------------------------- get functions -------------------------------*/

    OSGValueTypeT *getValues(void);
    
    /*---------------------- create transformation --------------------------*/

	void setScale    (const OSGValueTypeT s);
	void setScale    (const OSGValueTypeT sx, const OSGValueTypeT sy, 
					  const OSGValueTypeT sz);
	void setScale    (const OSGVectorType3f &s);

    void setTranslate(const OSGValueTypeT tx,
                      const OSGValueTypeT ty,
                      const OSGValueTypeT tz);
	void setTranslate(const OSGVectorType3f &t);
	void setTranslate(const OSGPointType3f &t);

	void setRotate   (const OSGQuaternionType &q);

	void setTransform(const OSGVectorType3f   &translation,
	                  const OSGQuaternionType &rotation,
	                  const OSGVectorType3f   &scaleFactor,
	                  const OSGQuaternionType &scaleOrientation,
	                  const OSGVectorType3f   &center);

	void setTransform(const OSGVectorType3f   &t, 
                      const OSGQuaternionType &r,
	                  const OSGVectorType3f   &s);

	void setTransform(const OSGVectorType3f   &t, 
                      const OSGQuaternionType &r,
	                  const OSGVectorType3f   &s, 
                      const OSGQuaternionType &so);

    /*---------------------- get transformation parts -----------------------*/

	void getTransform(OSGVectorType3f   &translation, 
                      OSGQuaternionType &rotation,
	                  OSGVectorType3f   &scaleFactor, 
                      OSGQuaternionType &scaleOrientation,
	                  OSGVectorType3f   &center) const;

	void getTransform(OSGVectorType3f   &translation, 
                      OSGQuaternionType &rotation,
	                  OSGVectorType3f   &scaleFactor, 
                      OSGQuaternionType &scaleOrientation) const;

	OSGBool factor(OSGTransformationMatrix &r, 
                   OSGVectorType3f         &s, 
                   OSGTransformationMatrix &u,
                   OSGVectorType3f         &t, 
                   OSGTransformationMatrix &proj) const;

    /*------------------------ transform objects ---------------------------*/

	void multMatrixPnt(const OSGPointType3f &src, 
                             OSGPointType3f &dst) const;

	void multMatrixPnt(      OSGPointType3f &pnt) const;


	void multFullMatrixPnt(const OSGPointType3f &src, 
								 OSGPointType3f &dst) const;

	void multFullMatrixPnt(      OSGPointType3f &pnt) const;

	void multMatrixVec(const OSGVectorType3f &src, 
                             OSGVectorType3f &dst) const;

	void multMatrixVec(      OSGVectorType3f &vec) const;

    void transform(const OSGPointType3f &src, 
                         OSGPointType3f &dest) const;

    void transform(OSGPointType3f &vec) const;

    void transform(const OSGVectorType3f &src, 
                         OSGVectorType3f &dest) const;

    void transform(OSGVectorType3f &vec) const;


    /*------------------------- simple math ---------------------------------*/

    OSGBool       equals(const OSGTransformationMatrix &matrix, 
                         const OSGValueType             tolerance) const;

    OSGValueTypeT det3(void) const;
    OSGValueTypeT det (void) const;

    OSGBool inverse   (OSGTransformationMatrix &result) const;
    OSGBool invert    (void);
    OSGBool invertFrom(const OSGTransformationMatrix &matrix);

    OSGBool inverse3   (OSGTransformationMatrix &result) const;
    OSGBool invert3    (void);
    OSGBool invertFrom3(const OSGTransformationMatrix &matrix);

    void mult    (const OSGTransformationMatrix &matrix);
    void multLeft(const OSGTransformationMatrix &matrix);

    OSGBool transposed   (OSGTransformationMatrix &result) const;
    OSGBool transpose    (void);
    OSGBool transposeFrom(const OSGTransformationMatrix &matrix);

    /*------------------------- elemen acess --------------------------------*/

          OSGVectorType &operator [](OSGUInt32 uiIndex);
    const OSGVectorType &operator [](OSGUInt32 uiIndex) const;

    /*------------------------- assignment ----------------------------------*/
    
    OSGTransformationMatrix<OSGValueTypeT> &operator =(
        const OSGTransformationMatrix &source);

    /*------------------------- comparison ----------------------------------*/

	OSGBool operator == (const OSGTransformationMatrix &other);
	OSGBool operator != (const OSGTransformationMatrix &other);

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

    OSGVectorType _matrix[4];

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGValueTypeT rowMulCol4(const OSGTransformationMatrix &gRowMat, 
                                   OSGUInt32                iRow, 
                             const OSGTransformationMatrix &gColMat, 
                                   OSGUInt32                iColumn) const;

    OSGValueTypeT det2(const OSGValueTypeT a1, 
                       const OSGValueTypeT a2,
                       const OSGValueTypeT b1, 
                       const OSGValueTypeT b2) const;

    OSGValueTypeT det3(const OSGValueTypeT a1, 
                       const OSGValueTypeT a2, 
                       const OSGValueTypeT a3,
                       const OSGValueTypeT b1, 
                       const OSGValueTypeT b2, 
                       const OSGValueTypeT b3,
                       const OSGValueTypeT c1, 
                       const OSGValueTypeT c2, 
                       const OSGValueTypeT c3) const;

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

    static OSGTransformationMatrix _identityMatrix;

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

/** \var typedef OSGTransformationMatrix<OSGReal32> OSGMatrix;
 *  \brief OSGMatrix
 *  \ingroup BaseMathMatrices
 */

typedef OSGTransformationMatrix<OSGReal32> OSGMatrix;

/** \var typedef OSGTransformationMatrix<OSGReal32> OSGMatrix4f;
 *  \brief OSGMatrix4f
 *  \ingroup BaseMathMatrices
 */

typedef OSGTransformationMatrix<OSGReal32> OSGMatrix4f;

OSG_END_NAMESPACE

#include <OSGMatrix.inl>

#endif /* _OSGMATRIX_H_ */


