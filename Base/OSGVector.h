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


#ifndef _OSGVECTOR_H_
#define _OSGVECTOR_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGConfig.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif /* OSG_STREAM_IN_STD_NAMESPACE */

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

template<class OSGValueTypeT, class OSGStorageInterfaceT>
class OSGVectorInterface;

template<class OSGValueTypeT, class OSGStorageInterfaceT>
class OSGPointInterface;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseLib
 *  \brief Vector storage holding 2 elements, for details about how vectors,
 *         points and matrices are actually build see \ref vecpointmat.
 */

template <class OSGValueTypeT>
class OSGVecStorage2 
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

    static const char *getClassname(void) { return "OSGVecStorage2"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGVecStorage2(void);

    ~OSGVecStorage2(void); 

    /*----------------------------- access ----------------------------------*/

    void setValues(const OSGValueTypeT &rVal1, const OSGValueTypeT &rVal2);

    void getValues(OSGValueTypeT &rVal1, OSGValueTypeT &rVal2) const;

    OSGValueTypeT x(void) const;
    OSGValueTypeT y(void) const;

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

    OSGValueTypeT _values[_iSize];

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

    OSGVecStorage2(const OSGVecStorage2 &source);
    void operator =(const OSGVecStorage2 &source);
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseLib
 *  \brief Vector storage holding 3 elements, for details about how vectors,
 *         points and matrices are actually build see \ref vecpointmat.
 */

template <class OSGValueTypeT>
class OSGVecStorage3
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

    static const char *getClassname(void) { return "OSGVecStorage3"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGVecStorage3(void);

    ~OSGVecStorage3(void); 

    /*----------------------------- access ---------------------------------*/

    void setValues(const OSGValueTypeT &rVal1, 
                   const OSGValueTypeT &rVal2, 
                   const OSGValueTypeT &rVal3);

    void getValues(OSGValueTypeT &rVal1, 
                   OSGValueTypeT &rVal2, 
                   OSGValueTypeT &rVal3) const;

    OSGValueTypeT x(void) const;
    OSGValueTypeT y(void) const;
    OSGValueTypeT z(void) const;

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

    OSGValueTypeT _values[_iSize];

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

    OSGVecStorage3(const OSGVecStorage3 &source);
    void operator =(const OSGVecStorage3 &source);
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseLib
 *  \brief Vector storage holding 4 elements, for details about how vectors,
 *         points and matrices are actually build see \ref vecpointmat.
 */

template <class OSGValueTypeT>
class OSGVecStorage4
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

    static const char *getClassname(void) { return "OSGVecStorage4"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGVecStorage4(void);

    ~OSGVecStorage4(void); 

    /*----------------------------- access ----------------------------------*/

    void setValues(const OSGValueTypeT &rVal1, 
                   const OSGValueTypeT &rVal2, 
                   const OSGValueTypeT &rVal3, 
                   const OSGValueTypeT &rVal4);

    void getValues(OSGValueTypeT &rVal1, 
                   OSGValueTypeT &rVal2, 
                   OSGValueTypeT &rVal3, 
                   OSGValueTypeT &rVal4) const;

    OSGValueTypeT x(void) const;
    OSGValueTypeT y(void) const;
    OSGValueTypeT z(void) const;
    OSGValueTypeT w(void) const;

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

    OSGValueTypeT _values[_iSize];

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

    OSGVecStorage4(const OSGVecStorage4 &source);
    void operator =(const OSGVecStorage4 &source);
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseLib
 *  \brief Point Interface, for details about how vectors, points and matrices
 *   are actually build see \ref vecpointmat. 
 */

#ifdef __sgi
#pragma set woff 1375
#endif

template<class OSGValueTypeT, class OSGStorageInterfaceT>
class OSGPointInterface : public OSGStorageInterfaceT
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------
    
    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef typename OSGTypeConstants<OSGValueTypeT>::OSGRealReturnType 
        OSGRealReturnType;

    typedef          OSGValueTypeT OSGValueType;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "OSGPointInterface"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

   /*------------ constructors & destructors -------------------------------*/

    OSGPointInterface(void);

	explicit OSGPointInterface(const OSGValueTypeT *pVals);
	explicit OSGPointInterface(      OSGValueTypeT *pVals);

	/** \brief Constructor which take a lot of types as it's argument :-).
	 *
	 * The argument type must provide a _iSize enum entry, a *getValueRef(void)
	 *  function and the value types must be convertable to the current one. 
	 *  The main problem is that through the constructor 
	 *  OSGVecBase(const OSGValueTypeT *pVals); and the following cast
	 *  operator const OSGValueTypeT * (void); you are able to to the
	 *  following :
	 *  \code
	 *  void foo(void)
	 *  {
	 *      ClassWithOSGValueTypeT_*_Cast v2f;
	 *      OSGVec4f v4f(v2f);
	 *  }              
	 *  \endcode
	 *  This will at least give you some array read out of bounce erros;       
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

    template<class OSGVectorT> explicit OSGPointInterface(
        const OSGVectorT &vec) : Inherited()
	{
        OSGUInt32 i;

	    if(_iSize < OSGVectorT::_iSize)
		{
	        for(i = 0; i < _iSize; i++)
		    {
			    _values[i] = vec.getValueRef()[i];
			}
		}
		else	
		{
			for(i = 0; i < OSGVectorT::_iSize; i++)
			{
	            _values[i] = vec.getValueRef()[i];
			}
			for(i = OSGVectorT::_iSize; i < _iSize; i++)
			{
	            _values[i] = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
			}
		}
	}

    #ifdef __sgi
    #pragma reset woff 1209
    #endif

    OSGPointInterface(const OSGPointInterface &source);    

#if 0
    /* Constructor which takes one value, remaining entries will be zero;
       Actually this one collides with the template constuctor above, 
       so I do not implement this one, any problems with that (GV) 
    */

    OSGPointInterface(const OSGValueTypeT rVal1);
#endif

    /* Found so far no way to move these constructors to the memory
       interface :-(. I still find them a little bit wrong placed (GV)
    */

    OSGPointInterface(const OSGValueTypeT rVal1, const OSGValueTypeT rVal2);

    OSGPointInterface(const OSGValueTypeT rVal1, const OSGValueTypeT rVal2, 
                      const OSGValueTypeT rVal3);
    
    OSGPointInterface(const OSGValueTypeT rVal1, const OSGValueTypeT rVal2, 
                      const OSGValueTypeT rVal3, const OSGValueTypeT rVal4);

    ~OSGPointInterface(void); 

    /*------------------------- set values -------------------------------*/
    
    void setNull(void);

#if 0
    /* set first values, remaining entries will not change;
       Actually this one collides with the template set function below, 
       so I do not implement this one, any problems with that (GV) 
    */

    void setValue(const OSGValueTypeT &rVal1);
#endif

    void setValue(const OSGPointInterface &vec);

	/** \brief Set function which take a lot of types as it's argument :-).
	 *
	 * The argument type must provide a _iSize enum entry, a *getValueRef(void)
	 *  function and the value types must be convertable to the current one. 
	 *  The main problem is that through the set function
	 *  void setValue(const OSGValueTypeT *pVals); and the following cast
	 *  operator const OSGValueTypeT * (void); you are able to to the
	 * following :
	 * \code
	 *  void foo(void)
	 *  {
	 *      ClassWithOSGValueTypeT_*_Cast v2f;
	 *      OSGVec4f v4f;
	 *
	 *      v4f.setValue(v2f);
	 *  }              
	 *  \endcode
	 *  This will at least give you some array read out of bounce erros;       
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

    template<class OSGVectorT>
    void setValue(const OSGVectorT &vec)
	{
		OSGUInt32 i;

		for(i = 0; 
			i < (_iSize < OSGVectorT::_iSize ? _iSize : OSGVectorT::_iSize); 
			i++)
		{
	        _values[i] = vec.getValueRef()[i];
	    }
	}

    #ifdef __sgi
    #pragma reset woff 1209
    #endif

    void setValue(const OSGValueTypeT *pVals);

    void setValue(const char *szString);
    void setValue(      char *szString);

    /*------------------------- get values -------------------------------*/

          OSGValueTypeT *getValueRef(void);
    const OSGValueTypeT *getValueRef(void) const;

    /*--------------------------- common math -------------------------------*/

    OSGBool            isZero   (void) const;

    void               negate   (void);

    OSGBool            equals   (const OSGPointInterface &vec, 
                                 const OSGValueTypeT       tolerance) const;

    /*------------------------------ math -----------------------------------*/

    void       operator *=(const OSGValueTypeT  val);
    void       operator /=(const OSGValueTypeT  val);

    OSGVectorInterface<OSGValueTypeT, 
                       OSGStorageInterfaceT> operator - (
                           const OSGPointInterface &vec) const;

    OSGPointInterface operator * (const OSGValueTypeT rVal) const;

    OSGPointInterface operator -  (void);

    /*------------------------- element access ------------------------------*/

           OSGValueTypeT &operator[](const OSGUInt32 uiVal);
    const  OSGValueTypeT &operator[](const OSGUInt32 uiVal) const;   

    /* Cast operator, cast OSGVecBase to OSGValueTypeT *
       Bad Bad idea, in my opion to buggy to be used, use getValues
       Const cast operator, cast OSGVecBase to OSGValueTypeT *

    operator       OSGValueTypeT *(void);
    operator const OSGValueTypeT *(void);
    */

    /*------------------------- assignment ----------------------------------*/

    OSGPointInterface &operator =(const OSGPointInterface &source);

    /*------------------------- comparison ----------------------------------*/

    OSGBool operator < (const OSGPointInterface &other)  const;

	OSGBool operator == (const OSGPointInterface &other) const;
	OSGBool operator != (const OSGPointInterface &other) const;

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

    typedef OSGStorageInterfaceT Inherited;

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

/*! \ingroup BaseLib
 *  \brief Vector Interface, for details about how vectors, points and matrices
 *   are actually build see \ref vecpointmat. 
 */

template<class OSGValueTypeT, class OSGStorageInterfaceT>
class OSGVectorInterface : 
    public OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------
    
    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef typename OSGTypeConstants<OSGValueTypeT>::OSGRealReturnType 
        OSGRealReturnType;

    typedef          OSGValueTypeT OSGValueType;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "OSGVectorInterface"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

   /*------------ constructors & destructors -------------------------------*/

    OSGVectorInterface(void);

	explicit OSGVectorInterface(const OSGValueTypeT *pVals);
	explicit OSGVectorInterface(      OSGValueTypeT *pVals);

	/** \brief Constructor which take a lot of types as it's argument :-).
	 *
	 * The argument type must provide a _iSize enum entry, a *getValueRef(void)
	 *  function and the value types must be convertable to the current one. 
	 *  The main problem is that through the constructor 
	 *  OSGVecBase(const OSGValueTypeT *pVals); and the following cast
	 *  operator const OSGValueTypeT * (void); you are able to to the
	 *  following :
	 *  \code
	 *  void foo(void)
	 *  {
	 *      ClassWithOSGValueTypeT_*_Cast v2f;
	 *      OSGVec4f v4f(v2f);
	 *  }              
	 *  \endcode
	 *  This will at least give you some array read out of bounce erros;       
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

    template<class OSGVectorT> explicit OSGVectorInterface(
        const OSGVectorT &vec) : Inherited()
	{
        OSGUInt32 i;

	    if(_iSize < OSGVectorT::_iSize)
		{
	        for(i = 0; i < _iSize; i++)
		    {
			    _values[i] = vec.getValueRef()[i];
			}
		}
		else	
		{
			for(i = 0; i < OSGVectorT::_iSize; i++)
			{
	            _values[i] = vec.getValueRef()[i];
			}
			for(i = OSGVectorT::_iSize; i < _iSize; i++)
			{
	            _values[i] = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
			}
		}
	}

    #ifdef __sgi
    #pragma reset woff 1209
    #endif

    OSGVectorInterface(const OSGVectorInterface &source);    

#if 0
    /* Constructor which takes one value, remaining entries will be zero;
       Actually this one collides with the template constuctor above, 
       so I do not implement this one, any problems with that (GV) 
    */

    OSGVectorInterface(const OSGValueTypeT rVal1);
#endif

    /* Found so far no way to move these constructors to the memory
       interface :-(. I still find them a little bit wrong placed (GV)
    */

    OSGVectorInterface(const OSGValueTypeT rVal1, const OSGValueTypeT rVal2);

    OSGVectorInterface(const OSGValueTypeT rVal1, const OSGValueTypeT rVal2, 
                       const OSGValueTypeT rVal3);

    OSGVectorInterface(const OSGValueTypeT rVal1, const OSGValueTypeT rVal2, 
                       const OSGValueTypeT rVal3, const OSGValueTypeT rVal4);

    ~OSGVectorInterface(void); 

    /*--------------------------- common math -------------------------------*/

    OSGRealReturnType  length   (void) const;

    void               normalize(void);

    OSGVectorInterface cross    (const OSGVectorInterface &vec) const;

    void               crossThis(const OSGVectorInterface &vec);

    OSGValueTypeT      dot      (const OSGVectorInterface &vec) const;

    OSGRealReturnType  enclosedAngle(const OSGVectorInterface &vec) const;

    /*------------------------------ math -----------------------------------*/

    void       operator +=(const OSGVectorInterface    &vec);
    void       operator -=(const OSGVectorInterface    &vec);

    OSGVectorInterface operator - (const OSGVectorInterface &vec) const;
    OSGVectorInterface operator + (const OSGVectorInterface &vec) const;

    OSGVectorInterface operator * (const OSGValueTypeT rVal) const;

    OSGVectorInterface operator -  (void);

    /*------------------------- assignment ----------------------------------*/

    OSGVectorInterface &operator =(const OSGVectorInterface &source);

    /*------------------------- comparison ----------------------------------*/

    OSGBool operator < (const OSGVectorInterface &other)  const;

	OSGBool operator == (const OSGVectorInterface &other) const;
	OSGBool operator != (const OSGVectorInterface &other) const;

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

    typedef OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT> Inherited;

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

/** OSGVec2f
 */
typedef OSGVectorInterface<OSGReal32, OSGVecStorage2<OSGReal32> > OSGVec2f;

/** OSGVec2fP
 */
typedef OSGVec2f *OSGVec2fP;

/** OSGVec3f
 */
typedef OSGVectorInterface<OSGReal32, OSGVecStorage3<OSGReal32> > OSGVec3f;

/** OSGVec3fP
 */
typedef OSGVec3f *OSGVec3fP;

/** OSGVec4f
 */
typedef OSGVectorInterface<OSGReal32, OSGVecStorage4<OSGReal32> > OSGVec4f;

/** OSGVec4fP
 */
typedef OSGVec4f *OSGVec4fP;

/** OSGVec2s
 */
typedef OSGVectorInterface<OSGUInt16, OSGVecStorage2<OSGUInt16> > OSGVec2s;

/** OSGVec2sP
 */
typedef OSGVec2s *OSGVec2sP;

/** OSGVec4ub
 */
typedef OSGVectorInterface<OSGUInt8, OSGVecStorage4<OSGUInt8> > OSGVec4ub;

/** OSGVec4ubP
 */
typedef OSGVec4ub *OSGVec4ubP;


/** OSGVec2f
 */
typedef OSGPointInterface<OSGReal32, OSGVecStorage2<OSGReal32> > OSGPnt2f;

/** OSGVec2fP
 */
typedef OSGPnt2f *OSGPnt2fP;

/** OSGVec3f
 */
typedef OSGPointInterface<OSGReal32, OSGVecStorage3<OSGReal32> > OSGPnt3f;

/** OSGVec3fP
 */
typedef OSGPnt3f *OSGPnt3fP;

/** OSGVec4f
 */
typedef OSGPointInterface<OSGReal32, OSGVecStorage4<OSGReal32> > OSGPnt4f;

/** OSGVec4fP
 */
typedef OSGPnt4f *OSGPnt4fP;

/** OSGVec2s
 */
typedef OSGPointInterface<OSGUInt16, OSGVecStorage2<OSGUInt16> > OSGPnt2s;

/** OSGVec2sP
 */

typedef OSGVec2s *OSGVec2sP;

OSG_END_NAMESPACE

#include <OSGVector.inl>

#endif /* OSGVECTOR_H */


