/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                *
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
 *  initial version: based on code from P. Reuter (preuter@labri.fr)         *
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

#include "OSGNormalQuantifier.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGNormalQuantifier.cpp,v 1.4 2002/04/25 03:55:09 vossg Exp $";
    static Char8 cvsid_hpp[] = OSG_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSG_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/*! \class osg::NormalQuantifier
    NormalQuantifier documentation,
 */


/*! \enum NormalQuantifier::ENUMNAME
  
 */


/*! \var VARTYPE NormalQuantifier::_VARNAME
    variable documentation
 */


/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

/*! Constructor documentation
 */
NormalQuantifier::NormalQuantifier(UInt32 numberSubdivisions)
{
  build(numberSubdivisions);
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

/*! Destructor documentation
 */
NormalQuantifier::~NormalQuantifier(void)
{
  ;
}

/*-------------------------------------------------------------------------*/
/*                             build                                       */

void NormalQuantifier::build (UInt32 numberSubdivisions)
{
  Vec3f point1, point2, point3;
  UInt32 octant, xoctant, yoctant, zoctant;
  UInt32 index = 0, nN = ((1<<(2*numberSubdivisions))*8);
  
  _numberSubdivisions = numberSubdivisions;
  _normalTable.resize(nN);
  
  if (_numberSubdivisions) 
    {
      for (octant = 0; octant<8; octant++) 
        {
          xoctant = (octant & 4)>0?-1:1;
          yoctant = (octant & 2)>0?-1:1;
          zoctant = (octant & 1)>0?-1:1;
          
          point1.setValues(0 * xoctant, 0*yoctant, 1*zoctant);
          point2.setValues(1 * xoctant, 0*yoctant, 0*zoctant);
          point3.setValues(0 * xoctant, 1*yoctant, 0*zoctant);
          
          subdivide(point1, point2, point3, _numberSubdivisions+1, index);
        }
    }  
}


/*-------------------------------------------------------------------------*/
/*                             helper                                      */

void NormalQuantifier::subdivide ( Vec3f point1, Vec3f point2, Vec3f point3, 
                                   UInt32 number, UInt32 &index) 
{
  Vec3f newPoint1, newPoint2, newPoint3;
  Vec3f newPoint;
  
  number--;
  
  if (number == 0) 
    {
      newPoint = point1;
      newPoint += point2;
      newPoint += point3;
      newPoint /= 3;
      
      newPoint.normalize();
      _normalTable[index] = newPoint;
      ++index; 
    }
  else 
    {  
      newPoint1 = point1;
      newPoint1 += point2;
      newPoint1 /= 2;
      newPoint1.normalize();

      newPoint2 = point1;
      newPoint2 += point3;
      newPoint2 /= 2; 
      newPoint2.normalize();

      newPoint3 = point2;
      newPoint3 += point3;
      newPoint3 /= 2;
      newPoint3.normalize();
      
      subdivide(point1, newPoint1, newPoint2, number, index);
      subdivide(newPoint1, point2, newPoint3, number, index);
      subdivide(newPoint1, newPoint2, newPoint3, number, index);
      subdivide(newPoint2, newPoint3, point3, number, index);
    }
}

UInt32 NormalQuantifier::getSubIndex ( Vec3f point, 
                                       Vec3f point1, Vec3f point2, Vec3f point3, 
                                       UInt32 number ) const
{
  Vec3f newPoint1, newPoint2, newPoint3;
  Vec3f midPoint0, midPoint1, midPoint2, midPoint3;
  Real32 dot0, dot1, dot2, dot3;
  Real32 max01, max23;
  UInt32 index = 0, gate, gate01, gate23;
  
  number--;
  
  newPoint1 = point1;
  newPoint1 += point2;
  newPoint1 /= 2; 
  newPoint1.normalize();

  newPoint2 = point1;
  newPoint2 += point3;
  newPoint2 /=2; 
  newPoint2.normalize();
  
  newPoint3 = point2;
  newPoint3 += point3;
  newPoint3 /= 2; 
  newPoint3.normalize();
  
  midPoint0 = point1;
  midPoint0 += newPoint1;
  midPoint0 += newPoint2; 
  midPoint0.normalize();

  midPoint1 = newPoint1;
  midPoint1 += point2;
  midPoint1 += newPoint3; 
  midPoint1.normalize();

  midPoint2 = newPoint1;
  midPoint2 += newPoint2;
  midPoint2 += newPoint3; 
  midPoint2.normalize();

  midPoint3 = newPoint2;
  midPoint3 += newPoint3;
  midPoint3 += point3; 
  midPoint3.normalize();
  
  dot0 = point.dot(midPoint0);
  dot1 = point.dot(midPoint1);
  dot2 = point.dot(midPoint2);
  dot3 = point.dot(midPoint3);
  
  if (dot0 > dot1)
    {
      gate01 = 0;
      max01  = dot0;
    }
  else
    {
      gate01 = 1;
      max01  = dot1;
    }

  if (dot2 > dot3)
    {
      gate23 = 2;
      max23  = dot2;
    }
  else
    { 
      gate23 = 3;
      max23  = dot3;
    }

  if (max01 > max23)
    {
      gate = gate01;
    }
  else
    {
      gate = gate23;
    }

  if (number > 0)
    {
      index = gate << (number*2);
  
      switch (gate) {
      case 0:
        index += getSubIndex(point, point1, newPoint1, newPoint2, number);
        break;
      case 1:
        index += getSubIndex(point, newPoint1, point2, newPoint3, number);
        break;
      case 2:
        index += getSubIndex(point, newPoint1, newPoint2, newPoint3, number);
        break;
      case 3:
        index += getSubIndex(point, newPoint2, newPoint3, point3, number);
        break;
      }
    }
  
  return index;
}

/*-------------------------------------------------------------------------*/
/*                             get                                         */
UInt32 NormalQuantifier::getIndex  ( Vec3f &normal, 
                                     UInt32 numberSubdivisions ) const
{
  UInt32 index, octant, xoctant, yoctant, zoctant;
  Vec3f point1, point2, point3;
  
  if (numberSubdivisions == 0)
    numberSubdivisions = _numberSubdivisions;
  else
    if (numberSubdivisions > _numberSubdivisions)
      numberSubdivisions = _numberSubdivisions;
  
  octant = 
    ((normal.x()>=0?0:1)<<2) | 
    ((normal.y()>=0?0:1)<<1) | 
    (normal.z()>=0?0:1);

  xoctant = (octant & 4)>0?-1:1;
  yoctant = (octant & 2)>0?-1:1;
  zoctant = (octant & 1)>0?-1:1;
  
  point1.setValues(0 * xoctant, 0*yoctant, 1*zoctant);
  point2.setValues(1 * xoctant, 0*yoctant, 0*zoctant);
  point3.setValues(0 * xoctant, 1*yoctant, 0*zoctant);
   index = getSubIndex(normal, point1, point2, point3, numberSubdivisions);
  
  index = (octant<<(2*numberSubdivisions)) + index;
  
  return index;
}


/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

/*! assignment
 */
NormalQuantifier& NormalQuantifier::operator = (const NormalQuantifier &source)
{
  _numberSubdivisions = source._numberSubdivisions;
  _normalTable = source._normalTable;

  return *this;
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

/*! less
 */

bool NormalQuantifier::operator < (const NormalQuantifier &other) const
{
    return (this->_numberSubdivisions < other._numberSubdivisions);
}

/*! equal
 */

bool NormalQuantifier::operator == (const NormalQuantifier &other) const
{
  return (this->_numberSubdivisions == other._numberSubdivisions);
}

/*! unequal
 */

bool NormalQuantifier::operator != (const NormalQuantifier &other) const
{
    return ! (*this == other);
}



