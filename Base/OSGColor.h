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

#ifndef _OSGCOLOR_H_
#define _OSGCOLOR_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseColors
 *  \brief OSGColor3
 */

template <class OSGValueTypeT>
class OSGColor3
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGValueTypeT OSGValueType;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "OSGColor3"; };

    static void convertFromHSV(OSGValueType *rgbP, 
                               OSGReal32 h,
                               OSGReal32 s,
                               OSGReal32 v);


    static void convertToHSV(const OSGValueType *rgbP, 
                             OSGReal32 &h,
                             OSGReal32 &s,
                             OSGReal32 &v);

    static OSGUInt32 minPart(const OSGValueType *rgbP);
    static OSGUInt32 maxPart(const OSGValueType *rgbP);
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGColor3(void);
    OSGColor3(const OSGColor3 &source);
    OSGColor3(OSGValueType red,
              OSGValueType green,
              OSGValueType blue);
    virtual ~OSGColor3(void); 

    /*------------------------- your_category -------------------------------*/

    void clear(void);

    void setValuesRGB(OSGValueType red,
                      OSGValueType green,
                      OSGValueType blue);

    void setValuesHSV(OSGReal32 h,
                      OSGReal32 s,
                      OSGReal32 v);

    void setRandom(void);

    OSGUInt32 getRGB(void) const;

    void setRGB(OSGUInt32 rgbPack);


    void getValuesRGB(OSGValueType &red,
                      OSGValueType &green,
                      OSGValueType &blue);

    void getValuesHSV(OSGReal32 &h,
                      OSGReal32 &s,
                      OSGReal32 &v);

    OSGValueType red  (void) const;
    OSGValueType green(void) const;
    OSGValueType blue (void) const;        

          OSGValueType *getValueRef(void);
    const OSGValueType *getValueRef(void) const;


    /*------------------------- your_operators ------------------------------*/


    /*------------------------- assignment ----------------------------------*/

    OSGColor3 &operator =(const OSGColor3 &source);

    /*------------------------- comparison ----------------------------------*/

	OSGBool operator == (const OSGColor3 &other) const;
	OSGBool operator != (const OSGColor3 &other) const;

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

    OSGValueType _rgb[3];

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
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseColors
 *  \brief OSGColor4
 */

template <class OSGValueTypeT>
class OSGColor4
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGValueTypeT OSGValueType;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "OSGColor4"; };
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGColor4(void);
    OSGColor4(const OSGColor4 &source);
    OSGColor4(OSGValueType red,
              OSGValueType green,
              OSGValueType blue,
              OSGValueType alpha);
    virtual ~OSGColor4(void); 

    /*------------------------- your_category -------------------------------*/

    void clear(void);

    void setValuesRGBA(OSGValueType red,
                       OSGValueType green,
                       OSGValueType blue,
                       OSGValueType alpha);

    void setValuesHSV(OSGReal32 h,
                      OSGReal32 s,
                      OSGReal32 v);

    void setRandom(void);

    /// method to get a packed rgb value (AABBGGRR)
    OSGUInt32 getRGBA(void) const;

    /// method to set the rgb values (AABBGGRR)
    void setRGBA(OSGUInt32 rgbPack);


    void getValuesRGBA(OSGValueType &red,
                       OSGValueType &green,
                       OSGValueType &blue,
                       OSGValueType &alpha);

    void getValuesHSV(OSGReal32 &h,
                      OSGReal32 &s,
                      OSGReal32 &v);

    OSGValueType red  (void) const;
    OSGValueType green(void) const;
    OSGValueType blue (void) const;        
    OSGValueType alpha(void) const;

          OSGValueType *getValueRef(void);
    const OSGValueType *getValueRef(void) const;


    /*------------------------- your_operators ------------------------------*/


    /*------------------------- assignment ----------------------------------*/

    OSGColor4 &operator =(const OSGColor4 &source);

    /*------------------------- comparison ----------------------------------*/
    
	OSGBool operator == (const OSGColor4 &other) const;
	OSGBool operator != (const OSGColor4 &other) const;

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

    OSGValueType _rgba[4];

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
};


template <class OSGValueTypeT>
ostream &operator <<(ostream                        &outStream,
                     const OSGColor3<OSGValueTypeT> &color);

template <class OSGValueTypeT>
ostream &operator <<(ostream                        &outStream,
                     const OSGColor4<OSGValueTypeT> &color);

/*! \var OSGColor3<OSGReal32> OSGColor3f;
 *  \ingroup BaseColors
 *  \brief OSGColor3f
 */

typedef OSGColor3<OSGReal32> OSGColor3f;

/*! \var OSGColor4<OSGReal32> OSGColor4f;
 *  \ingroup BaseColors
 *  \brief OSGColor4f
 */

typedef OSGColor4<OSGReal32> OSGColor4f;

/*! \var OSGColor3<OSGUInt8> OSGColor3ub;
 *  \ingroup BaseColors
 *  \brief OSGColor3ub
 */

typedef OSGColor3<OSGUInt8> OSGColor3ub;

/*! \var OSGColor4<OSGUInt8> OSGColor4ub;
 *  \ingroup BaseColors
 *  \brief OSGColor4ub
 */

typedef OSGColor4<OSGUInt8> OSGColor4ub;

OSG_END_NAMESPACE

#include <OSGColor.inl>

#endif /* OSG_COLOR */
