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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------


#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <stdlib.h>
#include <assert.h>

#ifndef WIN32
#include <unistd.h>
#endif


OSG_USING_OSG_NAMESPACE

/** \enum OSGVecBase::VectorSizeE
 *  \brief 
 */

/** \var OSGVecBase::VectorSizeE OSGVecBase::_iSize
 * 
 */

/** \fn const char *OSGVecBase::getClassname(void)
 *  \brief Classname
 */

/** \var OSGValueTypeT OSGVecBase::_values[iSize];
 *  \brief Value store
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

template <class OSGValueTypeT>
char OSGColor3<OSGValueTypeT>::cvsid[] = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/



/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


template <class OSGValueTypeT>
void OSGColor3<OSGValueTypeT>::convertFromHSV(OSGValueType *rgbP, 
                                              OSGReal32 h,
                                              OSGReal32 s,
                                              OSGReal32 v)
{
	OSGInt32  i;
	OSGReal32 f;
	OSGReal32 p, q, t;

	if(s) 
    {
		h = (h == 360) ? 0.0 : (h / 60.0); 
		i = int(h);
		f = h - float(i);
		p = v * (1.0 - s);
		q = v * (1.0 - (s * f));
		t = v * (1.0 - (s * (1 - f)));
		switch (i) 
        {
            case 0:
                rgbP[0] = OSGTypeConstants<OSGValueTypeT>::getPortion(v); 
                rgbP[1] = OSGTypeConstants<OSGValueTypeT>::getPortion(t); 
                rgbP[2] = OSGTypeConstants<OSGValueTypeT>::getPortion(p);
                break;
            case 1:
                rgbP[0] = OSGTypeConstants<OSGValueTypeT>::getPortion(q); 
                rgbP[1] = OSGTypeConstants<OSGValueTypeT>::getPortion(v); 
                rgbP[2] = OSGTypeConstants<OSGValueTypeT>::getPortion(p);
                break;
            case 2:
                rgbP[0] = OSGTypeConstants<OSGValueTypeT>::getPortion(p); 
                rgbP[1] = OSGTypeConstants<OSGValueTypeT>::getPortion(v); 
                rgbP[2] = OSGTypeConstants<OSGValueTypeT>::getPortion(t);
                break;
            case 3:
                rgbP[0] = OSGTypeConstants<OSGValueTypeT>::getPortion(p); 
                rgbP[1] = OSGTypeConstants<OSGValueTypeT>::getPortion(q); 
                rgbP[2] = OSGTypeConstants<OSGValueTypeT>::getPortion(v);
                break;
            case 4:
                rgbP[0] = OSGTypeConstants<OSGValueTypeT>::getPortion(t); 
                rgbP[1] = OSGTypeConstants<OSGValueTypeT>::getPortion(p); 
                rgbP[2] = OSGTypeConstants<OSGValueTypeT>::getPortion(v);
                break;
            case 5:
                rgbP[0] = OSGTypeConstants<OSGValueTypeT>::getPortion(v); 
                rgbP[1] = OSGTypeConstants<OSGValueTypeT>::getPortion(p); 
                rgbP[2] = OSGTypeConstants<OSGValueTypeT>::getPortion(q);
                break;
            default:
                cerr << "ERROR i not in [0, 5] in OSGColor::setHSV()!"
                     << endl;
		}
	}
	else
    {
		rgbP[0] = rgbP[1] = rgbP[2] = 
            OSGTypeConstants<OSGValueTypeT>::getPortion(v);
    }
}

template <class OSGValueTypeT>
void OSGColor3<OSGValueTypeT>::convertToHSV(const OSGValueType *rgbP, 
                                            OSGReal32 &h,
                                            OSGReal32 &s,
                                            OSGReal32 &v)
{
	const OSGReal32 r = OSGTypeConstants<OSGValueTypeT>::getFraction(rgbP[0]);
	const OSGReal32 g = OSGTypeConstants<OSGValueTypeT>::getFraction(rgbP[1]);
	const OSGReal32 b = OSGTypeConstants<OSGValueTypeT>::getFraction(rgbP[2]);

	const OSGInt32 maxIndex = maxPart(rgbP);
	const OSGInt32 minIndex = minPart(rgbP);

	const OSGReal32 max = OSGTypeConstants<OSGValueTypeT>::getFraction(
        rgbP[maxIndex]);
	const OSGReal32 min = OSGTypeConstants<OSGValueTypeT>::getFraction(
        rgbP[minIndex]);

	const OSGReal32 delta = max - min;

	v = max;
	s = max ? (max - min) / max : 0.0;

	if(s) 
    {
		switch (maxIndex) 
        {
            case 0: // red part is max;
                h = (( g - b) / delta) * 60.0;
                break;
            case 1: // green part is max;
                h = (2.0 + (( b - r) / delta)) * 60.0;
                break;
            case 2: // blue part is max
                h = (4.0 + (( r - g) / delta)) * 60.0;
                break;
		}

		if (h < 0.0)
			h += 360.0;
	}
	else
    {
		h = 0.0;
    }
}

template <class OSGValueTypeT>
OSGUInt32 OSGColor3<OSGValueTypeT>::maxPart(const OSGValueType *rgbP)
{
	if(rgbP[0] > rgbP[1])
    {
		if(rgbP[2] > rgbP[0])
        {
			return 2;
        }
		else
        {
			return 0;
        }
    }
	else
    {
		if (rgbP[2] > rgbP[1])
        {
			return 2;
        }
		else
        {
			return 1;
        }
    }
}


template <class OSGValueTypeT>
OSGUInt32 OSGColor3<OSGValueTypeT>::minPart(const OSGValueType *rgbP)
{
	if(rgbP[0] < rgbP[1])
    {
		if(rgbP[2] < rgbP[0])
        {
			return 2;
        }
		else
        {
			return 0;
        }
    }
	else
    {
		if(rgbP[2] < rgbP[1])
        {
			return 2;
        }
		else
        {
			return 1;
        }
    }
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

template <class OSGValueTypeT> inline
OSGColor3<OSGValueTypeT>::OSGColor3(void)
{
    _rgb[0] = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
    _rgb[1] = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
    _rgb[2] = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
}

/** \brief Copy Constructor
 */

template <class OSGValueTypeT> inline
OSGColor3<OSGValueTypeT>::OSGColor3(const OSGColor3 &source)
{
    _rgb[0] = source._rgb[0];
    _rgb[1] = source._rgb[1];
    _rgb[2] = source._rgb[2];
}

template <class OSGValueTypeT> inline
OSGColor3<OSGValueTypeT>::OSGColor3(OSGValueType red,
                                    OSGValueType green,
                                    OSGValueType blue)
{
    _rgb[0] = red;
    _rgb[1] = green;
    _rgb[2] = blue;    
}

/** \brief Destructor
 */

template <class OSGValueTypeT> inline
OSGColor3<OSGValueTypeT>::~OSGColor3(void)
{
}

/*------------------------------ access -----------------------------------*/

template <class OSGValueTypeT> inline
void OSGColor3<OSGValueTypeT>::clear(void)
{
    _rgb[0] = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
    _rgb[1] = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
    _rgb[2] = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
}

template <class OSGValueTypeT> inline
void OSGColor3<OSGValueTypeT>::setValuesRGB(OSGValueType red,
                                            OSGValueType green,
                                            OSGValueType blue)
{
    _rgb[0] = red;
    _rgb[1] = green;
    _rgb[2] = blue;    
}

template <class OSGValueTypeT> inline
void OSGColor3<OSGValueTypeT>::setValuesHSV(OSGReal32 h,
                                            OSGReal32 s,
                                            OSGReal32 v)
{
    convertFromHSV(_rgb, h, s, v);
}

template <class OSGValueTypeT> inline
void OSGColor3<OSGValueTypeT>::setRandom(void)
{
 	float rf = 1.0 / float(RAND_MAX);

	setValuesRGB(OSGTypeConstants<OSGValueTypeT>::getPortion(rf * rand()),
                 OSGTypeConstants<OSGValueTypeT>::getPortion(rf * rand()),
                 OSGTypeConstants<OSGValueTypeT>::getPortion(rf * rand()));
}

/** \brief method to get a packed rgb value (AABBGGRR)
 */

template <class OSGValueTypeT> inline
OSGUInt32 OSGColor3<OSGValueTypeT>::getRGB(void) const
{
	OSGInt32  i;
	OSGUInt32 pack = 0;

	for(i = 2; i >= 0; --i)
    {
		pack = 
            (pack << 8) | int(
                OSGTypeConstants<OSGValueTypeT>::getFraction(_rgb[i]) * 
                255.0                                                 + 
                0.5);
    }

	return pack;
}

/** \brief method to set the rgb values (AABBGGRR)
 */
template <class OSGValueTypeT> inline
void OSGColor3<OSGValueTypeT>::setRGB(OSGUInt32 rgbPack)
{
	OSGInt32  i;

	for(i = 0; i < 3; ++i) 
    {
        OSGReal32 rTmp = float(rgbPack & 255) / 255.0;

		_rgb[i] = OSGTypeConstants<OSGValueTypeT>::getPortion(rTmp);

		rgbPack >>= 8;
	}
}


template <class OSGValueTypeT> inline
void OSGColor3<OSGValueTypeT>::getValuesRGB(OSGValueType &red,
                                            OSGValueType &green,
                                            OSGValueType &blue)
{
    red   = _rgb[0];
    green = _rgb[1];
    blue  = _rgb[2];    
}

template <class OSGValueTypeT> inline
void OSGColor3<OSGValueTypeT>::getValuesHSV(OSGReal32 &h,
                                            OSGReal32 &s,
                                            OSGReal32 &v)
{
    convertToHSV(_rgb, h, s, v);
}

template <class OSGValueTypeT> inline
OSGColor3<OSGValueTypeT>::OSGValueType 
    OSGColor3<OSGValueTypeT>::red  (void) const
{
    return _rgb[0];
}

template <class OSGValueTypeT> inline
OSGColor3<OSGValueTypeT>::OSGValueType 
    OSGColor3<OSGValueTypeT>::green(void) const
{
    return _rgb[1];
}

template <class OSGValueTypeT> inline
OSGColor3<OSGValueTypeT>::OSGValueType 
    OSGColor3<OSGValueTypeT>::blue (void) const
{
    return _rgb[2];
}


template <class OSGValueTypeT> inline
OSGColor3<OSGValueTypeT>::OSGValueType *
    OSGColor3<OSGValueTypeT>::getValueRef(void)
{
    return _rgb;
}

template <class OSGValueTypeT> inline
const OSGColor3<OSGValueTypeT>::OSGValueType *
    OSGColor3<OSGValueTypeT>::getValueRef(void) const
{
    return _rgb;
}



/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

template <class OSGValueTypeT> inline
OSGColor3<OSGValueTypeT> &OSGColor3<OSGValueTypeT>::operator = (
     const OSGColor3 &other)
{
	if (this == &other)
		return *this;

    _rgb[0] = other._rgb[0];
    _rgb[1] = other._rgb[1];
    _rgb[2] = other._rgb[2];

    return *this;
}

/*-------------------------- comparison -----------------------------------*/

/** \brief equal
 */

template <class OSGValueTypeT> inline
OSGBool OSGColor3<OSGValueTypeT>::operator == (const OSGColor3 &other) const
{
    OSGBool returnValue = true;

    for(OSGUInt32 i = 0; i < 3; i++)
    {
        returnValue &= ( (      _rgb[i] - other._rgb[i] <= osgEps) && 
                         (other._rgb[i] -       _rgb[i] <= osgEps));
    }

    return returnValue;
}

/** \brief unequal
 */

template <class OSGValueTypeT> inline
OSGBool OSGColor3<OSGValueTypeT>::operator != (const OSGColor3 &other) const
{
	return ! (*this == other);
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/






/** \enum OSGVecBase::VectorSizeE
 *  \brief 
 */

/** \var OSGVecBase::VectorSizeE OSGVecBase::_iSize
 * 
 */

/** \fn const char *OSGVecBase::getClassname(void)
 *  \brief Classname
 */

/** \var OSGValueTypeT OSGVecBase::_values[iSize];
 *  \brief Value store
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

template <class OSGValueTypeT>
char OSGColor4<OSGValueTypeT>::cvsid[] = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/



/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

template <class OSGValueTypeT> inline
OSGColor4<OSGValueTypeT>::OSGColor4(void)
{
    _rgba[0] = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
    _rgba[1] = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
    _rgba[2] = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
    _rgba[3] = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
}

/** \brief Copy Constructor
 */

template <class OSGValueTypeT> inline
OSGColor4<OSGValueTypeT>::OSGColor4(const OSGColor4 &source)
{
    _rgba[0] = source._rgba[0];
    _rgba[1] = source._rgba[1];
    _rgba[2] = source._rgba[2];
    _rgba[3] = source._rgba[3];
}

template <class OSGValueTypeT> inline
OSGColor4<OSGValueTypeT>::OSGColor4(OSGValueType red,
                                    OSGValueType green,
                                    OSGValueType blue,
                                    OSGValueType alpha)
{
    _rgba[0] = red;
    _rgba[1] = green;
    _rgba[2] = blue;    
    _rgba[3] = alpha;    
}

/** \brief Destructor
 */

template <class OSGValueTypeT> inline
OSGColor4<OSGValueTypeT>::~OSGColor4(void)
{
}

/*------------------------------ access -----------------------------------*/

template <class OSGValueTypeT> inline
void OSGColor4<OSGValueTypeT>::clear(void)
{
    _rgba[0] = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
    _rgba[1] = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
    _rgba[2] = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
    _rgba[3] = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
}

template <class OSGValueTypeT> inline
void OSGColor4<OSGValueTypeT>::setValuesRGBA(OSGValueType red,
                                             OSGValueType green,
                                             OSGValueType blue,
                                             OSGValueType alpha)
{
    _rgba[0] = red;
    _rgba[1] = green;
    _rgba[2] = blue;    
    _rgba[3] = alpha;    
}

template <class OSGValueTypeT> inline
void OSGColor4<OSGValueTypeT>::setValuesHSV(OSGReal32 h,
                                            OSGReal32 s,
                                            OSGReal32 v)
{
    OSGColor3<OSGValueType>::convertFromHSV(_rgba, h, s, v);
    _rgba[3] = OSGTypeConstants<OSGValueTypeT>::getOneElement();
}


template <class OSGValueTypeT> inline
void OSGColor4<OSGValueTypeT>::setRandom(void)
{
 	float rf = 1.0 / float(RAND_MAX);

	setValuesRGBA(OSGTypeConstants<OSGValueTypeT>::getPortion(rf * rand()),
                  OSGTypeConstants<OSGValueTypeT>::getPortion(rf * rand()),
                  OSGTypeConstants<OSGValueTypeT>::getPortion(rf * rand()),
                  OSGTypeConstants<OSGValueTypeT>::getPortion(rf * rand()));
}

    /// method to get a packed rgb value (AOSGBGGRR)
template <class OSGValueTypeT> inline
OSGUInt32 OSGColor4<OSGValueTypeT>::getRGBA(void) const
{
	OSGInt32  i;
	OSGUInt32 pack = 0;

	for(i = 3; i >= 0; --i)
    {
		pack = 
            (pack << 8) | int(
                OSGTypeConstants<OSGValueTypeT>::getFraction(_rgba[i]) * 
                255.0                                                  + 
                0.5);
    }

	return pack;
}

    /// method to set the rgb values (AOSGBGGRR)
template <class OSGValueTypeT> inline
void OSGColor4<OSGValueTypeT>::setRGBA(OSGUInt32 rgbPack)
{
	OSGInt32 i;

	for(i = 0; i < 4; ++i) 
    {
        OSGReal32 rTmp = float(rgbPack & 255) / 255.0;

		_rgba[i] = OSGTypeConstants<OSGValueTypeT>::getPortion(rTmp);

		rgbPack >>= 8;
	}
}


template <class OSGValueTypeT> inline
void OSGColor4<OSGValueTypeT>::getValuesRGBA(OSGValueType &red,
                                             OSGValueType &green,
                                             OSGValueType &blue,
                                             OSGValueType &alpha)
{
    red   = _rgba[0];
    green = _rgba[1];
    blue  = _rgba[2];    
    alpha = _rgba[3];    
}

template <class OSGValueTypeT> inline
void OSGColor4<OSGValueTypeT>::getValuesHSV(OSGReal32 &h,
                                            OSGReal32 &s,
                                            OSGReal32 &v)
{
    OSGColor3<OSGValueType>::convertToHSV(_rgba, h, s, v);
}

template <class OSGValueTypeT> inline
OSGColor4<OSGValueTypeT>::OSGValueType 
    OSGColor4<OSGValueTypeT>::red  (void) const
{
    return _rgba[0];
}

template <class OSGValueTypeT> inline
OSGColor4<OSGValueTypeT>::OSGValueType 
    OSGColor4<OSGValueTypeT>::green(void) const
{
    return _rgba[1];
}

template <class OSGValueTypeT> inline
OSGColor4<OSGValueTypeT>::OSGValueType 
    OSGColor4<OSGValueTypeT>::blue (void) const
{
    return _rgba[2];
}

template <class OSGValueTypeT> inline
OSGColor4<OSGValueTypeT>::OSGValueType 
    OSGColor4<OSGValueTypeT>::alpha (void) const
{
    return _rgba[3];
}


template <class OSGValueTypeT> inline
OSGColor4<OSGValueTypeT>::OSGValueType *
    OSGColor4<OSGValueTypeT>::getValueRef(void)
{
    return _rgba;
}

template <class OSGValueTypeT> inline
const OSGColor4<OSGValueTypeT>::OSGValueType *
    OSGColor4<OSGValueTypeT>::getValueRef(void) const
{
    return _rgba;
}



/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

template <class OSGValueTypeT> inline
OSGColor4<OSGValueTypeT> &OSGColor4<OSGValueTypeT>::operator = (
     const OSGColor4 &other)
{
	if (this == &other)
		return *this;

    _rgba[0] = other._rgba[0];
    _rgba[1] = other._rgba[1];
    _rgba[2] = other._rgba[2];
    _rgba[3] = other._rgba[3];

    return *this;
}

/*-------------------------- comparison -----------------------------------*/

/** \brief equal
 */

template <class OSGValueTypeT> inline
OSGBool OSGColor4<OSGValueTypeT>::operator == (const OSGColor4 &other) const
{
    OSGBool returnValue = true;

    for(OSGUInt32 i = 0; i < 4; i++)
    {
        returnValue &= ( (      _rgba[i] - other._rgba[i] <= osgEps) && 
                         (other._rgba[i] -       _rgba[i] <= osgEps));
    }

    return returnValue;
}

/** \brief unequal
 */

template <class OSGValueTypeT> inline
OSGBool OSGColor4<OSGValueTypeT>::operator != (const OSGColor4 &other) const
{
	return ! (*this == other);
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/










///---------------------------------------------------------------------------
///  FUNCTION: 
///---------------------------------------------------------------------------
//:  Example for the head comment of a function
///---------------------------------------------------------------------------
///
//p: Paramaters: 
//p: 
///
//g: GlobalVars:
//g: 
///
//r: Return:
//r: 
///
//c: Caution:
//c: 
///
//a: Assumptions:
//a: 
///
//d: Description:
//d: 
///
//s: SeeAlso:
//s: 
///---------------------------------------------------------------------------

template <class OSGValueTypeT> inline
ostream &OSG::operator <<(ostream                        &outStream,
                          const OSGColor3<OSGValueTypeT> &color)
{
    return outStream << color.red()   << ' ' 
                     << color.green() << ' ' 
                     << color.blue();
}

template <class OSGValueTypeT> inline
ostream &OSG::operator <<(ostream                        &outStream,
                          const OSGColor4<OSGValueTypeT> &color)
{
    return outStream << color.red()   << ' ' 
                     << color.green() << ' ' 
                     << color.blue()  << ' ' 
                     << color.alpha();
}
