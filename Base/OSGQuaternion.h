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
 *  \brief OSGQuaternionBase, that's the way how to define rotations.
 */

template <class OSGValueTypeT>
class OSGQuaternionBase
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGVectorInterface     <OSGValueTypeT, 
                                    OSGVecStorage3<OSGValueTypeT> > 
        OSGVectorType;

    typedef OSGTransformationMatrix<OSGValueTypeT>    OSGMatrixType;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "OSGQuaternionBase"; };

	static const OSGQuaternionBase &identity(void);

    static OSGQuaternionBase slerp(const OSGQuaternionBase &rot0,
                                   const OSGQuaternionBase &rot1, 
                                   const OSGValueTypeT      t);
    

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGQuaternionBase(void);

    OSGQuaternionBase(const OSGQuaternionBase &source);

    OSGQuaternionBase(OSGValueTypeT x, 
                      OSGValueTypeT y, 
                      OSGValueTypeT z,
                      OSGValueTypeT w);

    explicit OSGQuaternionBase(const OSGMatrixType &matrix);

    OSGQuaternionBase(const OSGVectorType &axis, 
                      const OSGValueTypeT  angle);

    OSGQuaternionBase(const OSGVectorType &rotateFrom, 
                      const OSGVectorType &rotateTo);

    virtual ~OSGQuaternionBase(void); 

    /*------------------------- set functions -------------------------------*/

    void setIdentity(void);

	void setValueAsAxis(const OSGValueTypeT *valsP);
	void setValueAsQuat(const OSGValueTypeT *valsP);

	void setValueAsAxis(const OSGValueTypeT x, 
                        const OSGValueTypeT y, 
                        const OSGValueTypeT z, 
                        const OSGValueTypeT w);

	void setValueAsQuat(const OSGValueTypeT x, 
                        const OSGValueTypeT y, 
                        const OSGValueTypeT z, 
                        const OSGValueTypeT w);

	void setValue(const OSGMatrixType &matrix);

	void setValue(const OSGVectorType &axis, OSGValueTypeT angle);

	void setValue(const OSGVectorType &rotateFrom, 
                  const OSGVectorType &rotateTo);

	void setValue(const char *str);

	void setValue(const OSGValueTypeT alpha, 
                  const OSGValueTypeT beta,
                  const OSGValueTypeT gamma);

    /*------------------------- get functions -------------------------------*/

	const OSGValueTypeT *getValues(void) const;

	void getValueAsAxis(OSGValueTypeT &x, 
                        OSGValueTypeT &y, 
                        OSGValueTypeT &z,
                        OSGValueTypeT &w) const;

    void getValueAsQuat(OSGValueTypeT &x, 
                        OSGValueTypeT &y, 
                        OSGValueTypeT &z,
                        OSGValueTypeT &w) const;

	void getValue(OSGVectorType &axis, OSGValueTypeT &radians) const;
	void getValue(OSGMatrixType &matrix) const;

	OSGValueTypeT x(void) const;
	OSGValueTypeT y(void) const;
	OSGValueTypeT z(void) const;
	OSGValueTypeT w(void) const;

    /*------------------------- simple math -------------------------------*/

    OSGValueTypeT length   (void);
    void          normalize(void);

    void                     invert (void);
	const OSGQuaternionBase  inverse(void) const;

	void multVec   (const OSGVectorType &src, OSGVectorType &dst) const;

	void transform (const OSGVectorType &src, OSGVectorType &dst) const;

	void scaleAngle(OSGValueTypeT scaleFactor);

    void slerpThis (const OSGQuaternionBase &rot0,
                    const OSGQuaternionBase &rot1, 
                    const OSGValueTypeT      t);

	void mult      (const OSGQuaternionBase &other);
	void multLeft  (const OSGQuaternionBase &other);

	OSGBool equals (const OSGQuaternionBase &rot, 
                    const OSGValueTypeT tolerance) const;

    /*------------------------- element access ------------------------------*/

	      OSGValueTypeT &operator [](const OSGUInt32 index);
	const OSGValueTypeT &operator [](const OSGUInt32 index) const;

    /*------------------------- math operators ------------------------------*/

	void operator *=(const OSGQuaternionBase &other);

    /*------------------------- assignment ----------------------------------*/

    const OSGQuaternionBase& operator = (const OSGQuaternionBase &source);

    /*------------------------- comparison ----------------------------------*/

    bool operator <  (const OSGQuaternionBase &other);
    
	bool operator == (const OSGQuaternionBase &other);
	bool operator != (const OSGQuaternionBase &other);

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

    static void slerp(const OSGQuaternionBase &rot0,
                      const OSGQuaternionBase &rot1, 
                            OSGQuaternionBase &result,
                      const OSGValueTypeT      t);

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    void mult(const OSGValueTypeT rVal1[4], const OSGValueTypeT rVal2[4]);

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    enum OSGElementIndices
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

    static OSGQuaternionBase _identity;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    OSGValueTypeT _quat[4];

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

/** \var typedef OSGQuaternionBase<OSGReal32> OSGQuaternion;
 *  \brief OSGQuaternion
 *  \ingroup BaseMathQuaternions
 */

typedef OSGQuaternionBase<OSGReal32> OSGQuaternion;

OSG_END_NAMESPACE

#include <OSGQuaternion.inl>

#endif /* _OSGQUATERNION_H_ */
