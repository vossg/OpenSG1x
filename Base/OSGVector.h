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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGConfig.h>
#include <OSGBase.h>
#include <OSGBaseTypes.h>

#include <iostream>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

template<class ValueTypeT, class StorageInterfaceT>
class VectorInterface;

template<class ValueTypeT, class StorageInterfaceT>
class PointInterface;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseMathVectors
 *  \brief Vector storage holding 2 elements, for details about how vectors,
 *         points and matrices are actually build see \ref vecpointmat.
 */

template <class ValueTypeT>
class OSG_BASE_DLLMAPPING VecStorage2 
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    enum VectorSizeE { _iSize = 2 };

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "VecStorage2"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    VecStorage2(void);

    ~VecStorage2(void); 

    /*----------------------------- access ----------------------------------*/

    void setValues(const ValueTypeT &rVal1, const ValueTypeT &rVal2);

    void getValues(ValueTypeT &rVal1, ValueTypeT &rVal2) const;

    ValueTypeT x(void) const;
    ValueTypeT y(void) const;

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

    ValueTypeT _values[_iSize];

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

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

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

    VecStorage2(const VecStorage2 &source);
    void operator =(const VecStorage2 &source);
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseMathVectors
 *  \brief Vector storage holding 3 elements, for details about how vectors,
 *         points and matrices are actually build see \ref vecpointmat.
 */

template <class ValueTypeT>
class OSG_BASE_DLLMAPPING VecStorage3
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    enum VectorSizeE { _iSize = 3 };

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "VecStorage3"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    VecStorage3(void);

    ~VecStorage3(void); 

    /*----------------------------- access ---------------------------------*/

    void setValues(const ValueTypeT &rVal1, 
                   const ValueTypeT &rVal2, 
                   const ValueTypeT &rVal3);

    void getValues(ValueTypeT &rVal1, 
                   ValueTypeT &rVal2, 
                   ValueTypeT &rVal3) const;

    ValueTypeT x(void) const;
    ValueTypeT y(void) const;
    ValueTypeT z(void) const;

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

    ValueTypeT _values[_iSize];

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

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

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

    VecStorage3(const VecStorage3 &source);
    void operator =(const VecStorage3 &source);
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseMathVectors
 *  \brief Vector storage holding 4 elements, for details about how vectors,
 *         points and matrices are actually build see \ref vecpointmat.
 */

template <class ValueTypeT>
class OSG_BASE_DLLMAPPING VecStorage4
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    enum VectorSizeE { _iSize = 4 };

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "VecStorage4"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    VecStorage4(void);

    ~VecStorage4(void); 

    /*----------------------------- access ----------------------------------*/

    void setValues(const ValueTypeT &rVal1, 
                   const ValueTypeT &rVal2, 
                   const ValueTypeT &rVal3, 
                   const ValueTypeT &rVal4);

    void getValues(ValueTypeT &rVal1, 
                   ValueTypeT &rVal2, 
                   ValueTypeT &rVal3, 
                   ValueTypeT &rVal4) const;

    ValueTypeT x(void) const;
    ValueTypeT y(void) const;
    ValueTypeT z(void) const;
    ValueTypeT w(void) const;

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

    ValueTypeT _values[_iSize];

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

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

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

    VecStorage4(const VecStorage4 &source);
    void operator =(const VecStorage4 &source);
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseMathVectors
 *  \brief Point Interface, for details about how vectors, points and matrices
 *   are actually build see \ref vecpointmat. 
 */

#ifdef __sgi
#pragma set woff 1375
#endif

template<class ValueTypeT, class StorageInterfaceT>
class OSG_BASE_DLLMAPPING PointInterface : public StorageInterfaceT
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------
    
    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef StorageInterfaceT Inherited;

    typedef typename TypeConstants<ValueTypeT>::RealReturnType RealReturnType;

    typedef                        ValueTypeT                  ValueType;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "PointInterface"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*------------ constructors & destructors -------------------------------*/

    PointInterface(void);

	explicit PointInterface(const ValueTypeT *pVals);
	explicit PointInterface(      ValueTypeT *pVals);

	/** \brief Constructor which take a lot of types as it's argument :-).
	 *
	 * The argument type must provide a _iSize enum entry, a *getValueRef(void)
	 *  function and the value types must be convertable to the current one. 
	 *  The main problem is that through the constructor 
	 *  VecBase(const ValueTypeT *pVals); and the following cast
	 *  operator const ValueTypeT * (void); you are able to to the
	 *  following :
	 *  \code
	 *  void foo(void)
	 *  {
	 *      ClassWithValueTypeT_*_Cast v2f;
	 *      Vec4f v4f(v2f);
	 *  }              
	 *  \endcode
	 *  This will at least give you some array read out of bounds erros;       
	 *  So this constructor make the things a little bit more save, but you
	 *  will get nasty error messages from the compiler if the argument does
	 *  not satisfy the requirements given above. 
	 *
	 *	Thanks to that ****** MS Compiler the code must be included within
	 *  the header file, but at least it seems work ;-) (GV)
	 */

#ifdef __sgi
#pragma set woff 1209
#endif

    template<class VectorT> explicit PointInterface(
        const VectorT &vec) : Inherited()
        {
            UInt32 i;

            if(_iSize < VectorT::_iSize)
            {
                for(i = 0; i < _iSize; i++)
                {
                    _values[i] = vec.getValuesRef()[i];
                }
            }
            else	
            {
                for(i = 0; i < VectorT::_iSize; i++)
                {
                    _values[i] = vec.getValuesRef()[i];
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

    ~PointInterface(void); 

    /*------------------------- set values -------------------------------*/
    
    void setNull(void);

#if 0
    /* set first values, remaining entries will not change;
       Actually this one collides with the template set function below, 
       so I do not implement this one, any problems with that (GV) 
    */

    void setValue(const ValueTypeT &rVal1);
#endif

    void setValue(const PointInterface &vec);

	/** \brief Set function which take a lot of types as it's argument :-).
	 *
	 * The argument type must provide a _iSize enum entry, a *getValueRef(void)
	 *  function and the value types must be convertable to the current one. 
	 *  The main problem is that through the set function
	 *  void setValue(const ValueTypeT *pVals); and the following cast
	 *  operator const ValueTypeT * (void); you are able to to the
	 * following :
	 * \code
	 *  void foo(void)
	 *  {
	 *      ClassWithValueTypeT_*_Cast v2f;
	 *      Vec4f v4f;
	 *
	 *      v4f.setValue(v2f);
	 *  }              
	 *  \endcode
	 *  This will at least give you some array read out of bounds erros;       
	 *  So this function make the things a little bit more save, but you
     *  will get nasty error messages from the compiler if the argument does
     *  not satisfy the requirements given above.
	 *
	 *	Thanks to that ****** MS Compiler the code must be included within
	 *  the header file, but at least it seems to work ;-) (GV)
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
                _values[i] = vec.getValuesRef()[i];
            }
        }

#ifdef __sgi
#pragma reset woff 1209
#endif

    void setValue(const ValueTypeT *pVals);

    void setValue(const char *szString);
    void setValue(      char *szString);

    /*------------------------- get values -------------------------------*/

    ValueTypeT *getValuesRef(void);
    const ValueTypeT *getValuesRef(void) const;

    /*--------------------------- common math -------------------------------*/

    Bool            isZero   (void) const;

    void            negate   (void);

    Bool            equals   (const PointInterface &vec, 
                              const ValueTypeT       tolerance) const;

    /*------------------------------ math -----------------------------------*/

    void       operator *=(const ValueTypeT  val);
    void       operator /=(const ValueTypeT  val);

    VectorInterface<ValueTypeT, StorageInterfaceT> operator - (
        const PointInterface &vec) const;

    PointInterface operator + (
        const VectorInterface<ValueTypeT, StorageInterfaceT> &vec) const;	

    PointInterface operator - (
        const VectorInterface<ValueTypeT, StorageInterfaceT> &vec) const;	

    PointInterface operator * (const ValueTypeT rVal) const;

    PointInterface operator -  (void);

    /*------------------------- element access ------------------------------*/

    ValueTypeT &operator[](const UInt32 uiVal);
    const  ValueTypeT &operator[](const UInt32 uiVal) const;   

    /* Cast operator, cast VecBase to ValueTypeT *
       Bad Bad idea, in my opion to buggy to be used, use getValues
       Const cast operator, cast VecBase to ValueTypeT *

       operator       ValueTypeT *(void);
       operator const ValueTypeT *(void);
    */

    /*------------------------- assignment ----------------------------------*/

    PointInterface &operator =(const PointInterface &source);

    /*------------------------- comparison ----------------------------------*/

    Bool operator < (const PointInterface &other)  const;

	Bool operator == (const PointInterface &other) const;
	Bool operator != (const PointInterface &other) const;

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

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

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

	// Could not declare the operators as friends because of that f****** 
	// MS Compiler :-( (GV)

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

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
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseMathVectors
 *  \brief Vector Interface, for details about how vectors, points and matrices
 *   are actually build see \ref vecpointmat. 
 */

template<class ValueTypeT, class StorageInterfaceT>
class OSG_BASE_DLLMAPPING VectorInterface : 
    public PointInterface<ValueTypeT, StorageInterfaceT>
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------
    
    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef          PointInterface<ValueTypeT, 
                                    StorageInterfaceT>         Inherited;

    typedef typename TypeConstants<ValueTypeT>::RealReturnType RealReturnType;

    typedef                        ValueTypeT                  ValueType;

    typedef          Inherited                                 PntInterface;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "VectorInterface"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*------------ constructors & destructors -------------------------------*/

    VectorInterface(void);

	explicit VectorInterface(const ValueTypeT *pVals);
	explicit VectorInterface(      ValueTypeT *pVals);

	/** \brief Constructor which take a lot of types as it's argument :-).
	 *
	 * The argument type must provide a _iSize enum entry, a *getValueRef(void)
	 *  function and the value types must be convertable to the current one. 
	 *  The main problem is that through the constructor 
	 *  VecBase(const ValueTypeT *pVals); and the following cast
	 *  operator const ValueTypeT * (void); you are able to to the
	 *  following :
	 *  \code
	 *  void foo(void)
	 *  {
	 *      ClassWithValueTypeT_*_Cast v2f;
	 *      Vec4f v4f(v2f);
	 *  }              
	 *  \endcode
	 *  This will at least give you some array read out of bounds erros;       
	 *  So this constructor make the things a little bit more save, but you
	 *  will get nasty error messages from the compiler if the argument does
	 *  not satisfy the requirements given above. 
	 *
	 *	Thanks to that ****** MS Compiler the code must be included within
	 *  the header file, but at least it seems work ;-) (GV)
	 */

#ifdef __sgi
#pragma set woff 1209
#endif

    template<class VectorT> explicit VectorInterface(
        const VectorT &vec) : Inherited()
        {
            UInt32 i;

            if(_iSize < VectorT::_iSize)
            {
                for(i = 0; i < _iSize; i++)
                {
                    _values[i] = vec.getValuesRef()[i];
                }
            }
            else	
            {
                for(i = 0; i < VectorT::_iSize; i++)
                {
                    _values[i] = vec.getValuesRef()[i];
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

    ~VectorInterface(void); 

    /*--------------------------- common math -------------------------------*/

    RealReturnType  length   (void) const;

    void            normalize(void);

    VectorInterface cross     (const VectorInterface &vec) const;
    VectorInterface operator %(const VectorInterface &vec) const;

    void            crossThis (const VectorInterface &vec);

    ValueTypeT      dot       (const VectorInterface &vec) const;
    ValueTypeT  	operator *(const VectorInterface &vec) const;
    ValueTypeT      dot       (const PntInterface &pnt   ) const;
    ValueTypeT  	operator *(const PntInterface &pnt   ) const;

    RealReturnType  enclosedAngle(const VectorInterface &vec) const;

    RealReturnType  projectTo    (const VectorInterface &toVec);

    /*------------------------------ math -----------------------------------*/

    void       operator +=(const VectorInterface    &vec);
    void       operator -=(const VectorInterface    &vec);

    VectorInterface operator - (const VectorInterface &vec) const;
    VectorInterface operator + (const VectorInterface &vec) const;

    VectorInterface operator * (const ValueTypeT rVal) const;

    VectorInterface operator -  (void) const;

    /*------------------------- assignment ----------------------------------*/

    VectorInterface &operator =(const VectorInterface &source);

    /*------------------------- comparison ----------------------------------*/

    Bool operator < (const VectorInterface &other)  const;

	Bool operator == (const VectorInterface &other) const;
	Bool operator != (const VectorInterface &other) const;

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

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

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

	// Could not declare the operators as friends because of that f****** 
	// MS Compiler :-( (GV)

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

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

#ifdef __sgi
#pragma reset woff 1375
#endif

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

/** \var typedef VectorInterface<Real32, VecStorage2<Real32> > Vec2f;
 *  \brief Vec2f
 *  \ingroup BaseMathVectors
 */
typedef VectorInterface<Real32, VecStorage2<Real32> > Vec2f;
extern OSG_BASE_DLLMAPPING Vec2f NullVec2f;

/** \var typedef Vec2f *Vec2fP;
 *  \brief Vec2fP
 *  \ingroup BaseMathVectors
 */
typedef Vec2f *Vec2fP;

/** \var typedef VectorInterface<Real32, VecStorage3<Real32> > Vec3f;
 *  \brief Vec3f
 *  \ingroup BaseMathVectors
 */
typedef VectorInterface<Real32, VecStorage3<Real32> > Vec3f;
extern OSG_BASE_DLLMAPPING Vec3f NullVec3f;

/** \var typedef Vec3f *Vec3fP;
 *  \brief Vec3fP
 *  \ingroup BaseMathVectors
 */
typedef Vec3f *Vec3fP;

/** \var typedef VectorInterface<Real32, VecStorage4<Real32> > Vec4f;
 *  \brief Vec4f
 *  \ingroup BaseMathVectors
 */
typedef VectorInterface<Real32, VecStorage4<Real32> > Vec4f;
extern OSG_BASE_DLLMAPPING Vec4f NullVec4f;

/** \var typedef Vec4f *Vec4fP;
 *  \brief Vec4fP
 *  \ingroup BaseMathVectors
 */
typedef Vec4f *Vec4fP;

/** \var typedef VectorInterface<UInt16, VecStorage2<UInt16> > Vec2s;
 *  \brief Vec2s
 *  \ingroup BaseMathVectors
 */
typedef VectorInterface<UInt16, VecStorage2<UInt16> > Vec2s;
extern OSG_BASE_DLLMAPPING Vec2s NullVec2s;

/** \var typedef Vec2s *Vec2sP;
 *  \brief Vec2sP
 *  \ingroup BaseMathVectors
 */
typedef Vec2s *Vec2sP;

/** \var typedef VectorInterface<UInt8, VecStorage4<UInt8> > Vec4ub;
 *  \brief Vec4ub
 *  \ingroup BaseMathVectors
 */
typedef VectorInterface<UInt8, VecStorage4<UInt8> > Vec4ub;
extern OSG_BASE_DLLMAPPING Vec4ub NullVec4ub;

/** \var typedef Vec4ub *Vec4ubP;
 *  \brief Vec4ubP
 *  \ingroup BaseMathVectors
 */
typedef Vec4ub *Vec4ubP;


/** \var typedef PointInterface<Real32, VecStorage2<Real32> > Pnt2f;
 *  \brief Vec2f
 *  \ingroup BaseMathVectors
 */
typedef PointInterface<Real32, VecStorage2<Real32> > Pnt2f;
extern OSG_BASE_DLLMAPPING Pnt2f NullPnt2f;

/** \var typedef Pnt2f *Pnt2fP;
 *  \brief Vec2fP
 *  \ingroup BaseMathVectors
 */
typedef Pnt2f *Pnt2fP;

/** \var typedef PointInterface<Real32, VecStorage3<Real32> > Pnt3f;
 *  \brief Vec3f
 *  \ingroup BaseMathVectors
 */
typedef PointInterface<Real32, VecStorage3<Real32> > Pnt3f;
extern OSG_BASE_DLLMAPPING Pnt3f NullPnt3f;

/** \var typedef Pnt3f *Pnt3fP;
 *  \brief Vec3fP
 *  \ingroup BaseMathVectors
 */
typedef Pnt3f *Pnt3fP;

/** \var typedef PointInterface<Real32, VecStorage4<Real32> > Pnt4f;
 *  \brief Vec4f
 *  \ingroup BaseMathVectors
 */
typedef PointInterface<Real32, VecStorage4<Real32> > Pnt4f;
extern OSG_BASE_DLLMAPPING Pnt4f NullPnt4f;

/** \var typedef Pnt4f *Pnt4fP;
 *  \brief Vec4fP
 *  \ingroup BaseMathVectors
 */
typedef Pnt4f *Pnt4fP;

/** \var typedef PointInterface<UInt16, VecStorage2<UInt16> > Pnt2s;
 *  \brief Vec2s
 *  \ingroup BaseMathVectors
 */
typedef PointInterface<UInt16, VecStorage2<UInt16> > Pnt2s;
extern OSG_BASE_DLLMAPPING Pnt2s NullPnt2s;

/** \var typedef Vec2s *Vec2sP;
 *  \brief Vec2sP
 *  \ingroup BaseMathVectors
 */

typedef Vec2s *Vec2sP;

OSG_END_NAMESPACE

#include <OSGVector.inl>

#endif /* OSGVECTOR_H */


