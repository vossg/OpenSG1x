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

#ifndef _OSGCOLOR_H_
#define _OSGCOLOR_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBase.h>
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
 *  \brief Color3
 */

template <class ValueTypeT>
class OSG_BASE_DLLMAPPING Color3
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef ValueTypeT ValueType;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "Color3"; };

    static void convertFromHSV(ValueType *rgbP, 
                               Real32 h,
                               Real32 s,
                               Real32 v);


    static void convertToHSV(const ValueType *rgbP, 
                             Real32 &h,
                             Real32 &s,
                             Real32 &v);

    static UInt32 minPart(const ValueType *rgbP);
    static UInt32 maxPart(const ValueType *rgbP);
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    Color3(void);
    Color3(const Color3 &source);
    Color3(ValueType red,
           ValueType green,
           ValueType blue);
    ~Color3(void); 

    /*------------------------- your_category -------------------------------*/

    void clear(void);

    void setValuesRGB(ValueType red,
                      ValueType green,
                      ValueType blue);

    void setValuesHSV(Real32 h,
                      Real32 s,
                      Real32 v);

    void setRandom(void);

    UInt32 getRGB(void) const;

    void setRGB(UInt32 rgbPack);


    void getValuesRGB(ValueType &red,
                      ValueType &green,
                      ValueType &blue);

    void getValuesHSV(Real32 &h,
                      Real32 &s,
                      Real32 &v);

    ValueType red  (void) const;
    ValueType green(void) const;
    ValueType blue (void) const;        

          ValueType *getValueRef(void);
    const ValueType *getValueRef(void) const;


    void setValue(const char *szString);
    void setValue(      char *szString);


    /*------------------------- your_operators ------------------------------*/

    Color3 operator *(const ValueType val);

          ValueType &operator[] (UInt32 uiIndex);
    const ValueType &operator[] (UInt32 uiIndex) const;

    /*------------------------- assignment ----------------------------------*/

    Color3 &operator =(const Color3 &source);

    /*------------------------- comparison ----------------------------------*/

	Bool equals (const Color3 &other, ValueType tolerance) const;
	
	Bool operator == (const Color3 &other) const;
	Bool operator != (const Color3 &other) const;

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

    ValueType _rgb[3];

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
 *  \brief Color4
 */

template <class ValueTypeT>
class OSG_BASE_DLLMAPPING Color4
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef ValueTypeT ValueType;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "Color4"; };
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    Color4(void);
    Color4(const Color4 &source);
    Color4(ValueType red,
           ValueType green,
           ValueType blue,
           ValueType alpha);
    ~Color4(void); 

    /*------------------------- your_category -------------------------------*/

    void clear(void);

    void setValuesRGBA(ValueType red,
                       ValueType green,
                       ValueType blue,
                       ValueType alpha);

    void setValuesHSV(Real32 h,
                      Real32 s,
                      Real32 v);

    void setRandom(void);

    /// method to get a packed rgb value (AABBGGRR)
    UInt32 getRGBA(void) const;

    /// method to set the rgb values (AABBGGRR)
    void setRGBA(UInt32 rgbPack);


    void getValuesRGBA(ValueType &red,
                       ValueType &green,
                       ValueType &blue,
                       ValueType &alpha);

    void getValuesHSV(Real32 &h,
                      Real32 &s,
                      Real32 &v);

    ValueType red  (void) const;
    ValueType green(void) const;
    ValueType blue (void) const;        
    ValueType alpha(void) const;

          ValueType *getValueRef(void);
    const ValueType *getValueRef(void) const;


    void setValue(const char *szString);
    void setValue(      char *szString);


    /*------------------------- your_operators ------------------------------*/

    Color4 operator *(const ValueType val);

          ValueType &operator[] (UInt32 uiIndex);
    const ValueType &operator[] (UInt32 uiIndex) const;

    /*------------------------- assignment ----------------------------------*/

    Color4 &operator =(const Color4 &source);

    /*------------------------- comparison ----------------------------------*/

	Bool equals (const Color4 &other, ValueType tolerance) const;
    
	Bool operator == (const Color4 &other) const;
	Bool operator != (const Color4 &other) const;

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

    ValueType _rgba[4];

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


template <class ValueTypeT>
ostream &operator <<(      ostream            &outStream,
                     const Color3<ValueTypeT> &color);

template <class ValueTypeT>
ostream &operator <<(      ostream            &outStream,
                     const Color4<ValueTypeT> &color);

/*! \var Color3<Real32> Color3f;
 *  \ingroup BaseColors
 *  \brief Color3f
 */

typedef Color3<Real32> Color3f;

extern OSG_BASE_DLLMAPPING Color3f NullColor3f;

/*! \var Color4<Real32> Color4f;
 *  \ingroup BaseColors
 *  \brief Color4f
 */

typedef Color4<Real32> Color4f;

extern OSG_BASE_DLLMAPPING Color4f NullColor4f;

/*! \var Color3<UInt8> Color3ub;
 *  \ingroup BaseColors
 *  \brief Color3ub
 */

typedef Color3<UInt8> Color3ub;

extern OSG_BASE_DLLMAPPING Color3ub NullColor3ub;

/*! \var Color4<UInt8> Color4ub;
 *  \ingroup BaseColors
 *  \brief Color4ub
 */

typedef Color4<UInt8> Color4ub;

extern OSG_BASE_DLLMAPPING Color4ub NullColor4ub;

OSG_END_NAMESPACE

#include <OSGColor.inl>

#endif /* OSG_COLOR */
