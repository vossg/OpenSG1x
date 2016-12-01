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

#ifndef _OSGCOLOR_H_
#define _OSGCOLOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBase.h"
#include "OSGBaseTypes.h"
#include <iostream>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseBaseColors
 */

template <class ValueTypeT>
class Color3
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef ValueTypeT ValueType;

    static const Color3 Null;

    /*---------------------------------------------------------------------*/
    /*! \name                      Class Specific                          */
    /*! \{                                                                 */

    static void   convertFromHSV(      ValueType     *rgbP,
                                 const Real32         h,
                                 const Real32         s,
                                 const Real32         v   );


    static void   convertToHSV  (const ValueType     *rgbP,
                                       Real32        &h,
                                       Real32        &s,
                                       Real32        &v   );

    static UInt32 minPart       (const ValueType     *rgbP);
    static UInt32 maxPart       (const ValueType     *rgbP);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Constructors                            */
    /*! \{                                                                 */

    Color3(      void             );
    Color3(const Color3    &source);
    Color3(      ValueType  red,
                 ValueType  green,
                 ValueType  blue  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Destructors                            */
    /*! \{                                                                 */

    ~Color3(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                           Set                                */
    /*! \{                                                                 */

    void clear        (     void               );

    void setValuesRGB(const ValueType  red,
                      const ValueType  green,
                      const ValueType  blue    );

    void setValuesHSV(const Real32     h,
                      const Real32     s,
                      const Real32     v       );

    void setRandom   (      void               );
    void setRGB      (      UInt32     rgbPack );

    void setValue    (const Char8     *szString);
    void setValue    (      Char8     *szString);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                           Get                                */
    /*! \{                                                                 */

          UInt32     getRGB       (void           ) const;

          void       getValuesRGB(ValueType &red,
                                  ValueType &green,
                                  ValueType &blue ) const;

          void       getValuesHSV(Real32    &h,
                                  Real32    &s,
                                  Real32    &v    ) const;

          ValueType  red         (void            ) const;
          ValueType  green       (void            ) const;
          ValueType  blue        (void            ) const;

          ValueType *getValuesRGB(void            );
    const ValueType *getValuesRGB(void            ) const;


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Operators                             */
    /*! \{                                                                 */

          Color3     operator * (const ValueType  val      ) const;
          Color3     operator / (const ValueType  val      ) const;
          Color3     operator + (const ValueType  val      ) const;
          Color3     operator - (const ValueType  val      ) const;

          void       operator *= (const ValueType  val      );
          void       operator /= (const ValueType  val      );
          void       operator += (const ValueType  val      );
          void       operator -= (const ValueType  val      );
          
          Color3     operator * (const Color3    &other    ) const;
          Color3     operator / (const Color3    &other    ) const;
          Color3     operator + (const Color3    &other    ) const;
          Color3     operator - (const Color3    &other    ) const;

          void       operator *=(const Color3   &other );
          void       operator /=(const Color3   &other );
          void       operator +=(const Color3   &other );
          void       operator -=(const Color3   &other );


          ValueType &operator [](const UInt32     uiIndex  );
    const ValueType &operator [](const UInt32     uiIndex  ) const;

           Color3   &operator  =(const Color3    &source   );

           bool      equals     (const Color3    &other, 
                                 const ValueType  tolerance) const;

           bool      operator < (const Color3    &other    ) const;
           bool      operator ==(const Color3    &other    ) const;
           bool      operator !=(const Color3    &other    ) const;
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:
          
    ValueType _rgb[3];
};

/*! \ingroup GrpBaseBaseColors
 */

template <class ValueTypeT>
class Color4
{
    /*==========================  PUBLIC  =================================*/    
  public:

    typedef ValueTypeT ValueType;

    static const Color4 Null;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Color4(      void             );
    Color4(const Color4    &source);
    Color4(const ValueType  red,
           const ValueType  green,
           const ValueType  blue,
           const ValueType  alpha );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Destructors                               */
    /*! \{                                                                 */
    
    ~Color4(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Set                                    */
    /*! \{                                                                 */

    void clear        (      void           );

    void setValuesRGBA(const ValueType red,
                       const ValueType green,
                       const ValueType blue,
                       const ValueType alpha);

    void setValuesHSV (const Real32 h,
                       const Real32 s,
                       const Real32 v       );

    void setRandom    (      void           );
    void setRGBA      (      UInt32 rgbPack );    

    void setValue     (const Char8 *szString);
    void setValue     (      Char8 *szString);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Get                                    */
    /*! \{                                                                 */
    
          UInt32    getRGBA       (void            ) const;

          void      getValuesRGBA (ValueType &red,
                                   ValueType &green,
                                   ValueType &blue,
                                   ValueType &alpha) const;

          void      getValuesHSV  (Real32    &h,
                                   Real32    &s,
                                   Real32    &v    ) const;

          ValueType red           (void            ) const;
          ValueType green         (void            ) const;
          ValueType blue          (void            ) const;
          ValueType alpha         (void            ) const;

          ValueType *getValuesRGBA(void            );
    const ValueType *getValuesRGBA(void            ) const;


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Operators                              */
    /*! \{                                                                 */

          Color4     operator * (const ValueType  val      ) const;
          Color4     operator / (const ValueType  val      ) const;
          Color4     operator + (const ValueType  val      ) const;
          Color4     operator - (const ValueType  val      ) const;

          void       operator *= (const ValueType  val      );
          void       operator /= (const ValueType  val      );
          void       operator += (const ValueType  val      );
          void       operator -= (const ValueType  val      );
          
          Color4     operator * (const Color4    &other    ) const;
          Color4     operator / (const Color4    &other    ) const;
          Color4     operator + (const Color4    &other    ) const;
          Color4     operator - (const Color4    &other    ) const;

          void       operator *=(const Color4   &other );
          void       operator /=(const Color4   &other );
          void       operator +=(const Color4   &other );
          void       operator -=(const Color4   &other );

          ValueType &operator [](const UInt32     uiIndex  );
    const ValueType &operator [](const UInt32     uiIndex  ) const;

          Color4    &operator = (const Color4    &source   );

          bool       equals     (const Color4    &other, 
                                 const ValueType  tolerance) const;

          bool       operator < (const Color4    &other    ) const;
          bool       operator ==(const Color4    &other    ) const;
          bool       operator !=(const Color4    &other    ) const;
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    ValueType _rgba[4];
};


template <class ValueTypeT>
OSG_BASE_DLLMAPPING std::ostream &operator <<(
          std::ostream       &outStream,
    const Color3<ValueTypeT> &color     );

template <class ValueTypeT>
OSG_BASE_DLLMAPPING std::istream &operator >>(
    std::istream       &inStream,
    Color3<ValueTypeT> &color    );

template <class ValueTypeT>
OSG_BASE_DLLMAPPING std::ostream &operator <<(
          std::ostream       &outStream,
    const Color4<ValueTypeT> &color     );

template <class ValueTypeT>
OSG_BASE_DLLMAPPING std::istream &operator >>(
    std::istream       &inStream,
    Color4<ValueTypeT> &color    );

/*! \var Color3<Real32> Color3f;
 *  \ingroup GrpBaseColors
 *  \brief Color3f
 */

typedef Color3<Real32> Color3f;

/*! \var Color4<Real32> Color4f;
 *  \ingroup GrpBaseColors
 *  \brief Color4f
 */

typedef Color4<Real32> Color4f;

/*! \var Color3<UInt8> Color3ub;
 *  \ingroup GrpBaseColors
 *  \brief Color3ub
 */

typedef Color3<UInt8> Color3ub;

/*! \var Color4<UInt8> Color4ub;
 *  \ingroup GrpBaseColors
 *  \brief Color4ub
 */

typedef Color4<UInt8> Color4ub;

OSG_END_NAMESPACE

#include "OSGColor.inl"

#define OSGCOLOR_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSG_COLOR_H_ */
