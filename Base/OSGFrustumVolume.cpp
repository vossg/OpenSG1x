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

// System declarations

#ifdef WIN32
//#include <iosfwd>
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGConfig.h"

#define OSG_COMPILEBASELIB

#include <OSGLog.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <assert.h>

#include <OSGLine.h>
#include <OSGMatrix.h>

#include "OSGFrustumVolume.h"
#include "OSGPlane.h"

// Application declarations


// Class declarations

OSG_USING_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/


/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------------------------ feature ----------------------------------*/


/// set method
void FrustumVolume::setPlanes(const Plane &pnear, const Plane &pfar,
                              const Plane &left,  const Plane &right,
                              const Plane &top,   const Plane &bottom)
{
    _planeVec[0] = pnear;
    _planeVec[1] = pfar;
    _planeVec[2] = left;
    _planeVec[3] = right;
    _planeVec[4] = top;
    _planeVec[5] = bottom;
}

void FrustumVolume::setPlanes(const Pnt3f &nlt, const Pnt3f &nlb,
                              const Pnt3f &nrt, const Pnt3f &nrb,
                              const Pnt3f &flt, const Pnt3f &flb,
                              const Pnt3f &frt, const Pnt3f &frb)
{

    Plane pnear  (nlb,nlt,nrb);
    Plane pfar   (frb,frt,flb);
    Plane pleft  (flb,flt,nlb);
    Plane pright (nrb,nrt,frb);
    Plane ptop   (frt,nrt,flt);
    Plane pbottom(nlb,nrb,flb);


    _planeVec[0] = pnear;
    _planeVec[1] = pfar;
    _planeVec[2] = pleft;
    _planeVec[3] = pright;
    _planeVec[4] = ptop;
    _planeVec[5] = pbottom;

}

void FrustumVolume::setPlanes(const Matrix &objectClipMat)
{
    Vec4f planeEquation[6];
    Real32 vectorLength;
    Int32 i;
    Vec3f normal;

    planeEquation[0][0] = objectClipMat[0][3]-objectClipMat[0][0];
    planeEquation[0][1] = objectClipMat[1][3]-objectClipMat[1][0];
    planeEquation[0][2] = objectClipMat[2][3]-objectClipMat[2][0];
    planeEquation[0][3] = objectClipMat[3][3]-objectClipMat[3][0];

    planeEquation[1][0] = objectClipMat[0][3]+objectClipMat[0][0];
    planeEquation[1][1] = objectClipMat[1][3]+objectClipMat[1][0];
    planeEquation[1][2] = objectClipMat[2][3]+objectClipMat[2][0];
    planeEquation[1][3] = objectClipMat[3][3]+objectClipMat[3][0];

    planeEquation[2][0] = objectClipMat[0][3]+objectClipMat[0][1];
    planeEquation[2][1] = objectClipMat[1][3]+objectClipMat[1][1];
    planeEquation[2][2] = objectClipMat[2][3]+objectClipMat[2][1];
    planeEquation[2][3] = objectClipMat[3][3]+objectClipMat[3][1];

    planeEquation[3][0] = objectClipMat[0][3]-objectClipMat[0][1];
    planeEquation[3][1] = objectClipMat[1][3]-objectClipMat[1][1];
    planeEquation[3][2] = objectClipMat[2][3]-objectClipMat[2][1];
    planeEquation[3][3] = objectClipMat[3][3]-objectClipMat[3][1];

    planeEquation[4][0] = objectClipMat[0][3]+objectClipMat[0][2];
    planeEquation[4][1] = objectClipMat[1][3]+objectClipMat[1][2];
    planeEquation[4][2] = objectClipMat[2][3]+objectClipMat[2][2];
    planeEquation[4][3] = objectClipMat[3][3]+objectClipMat[3][2];

    planeEquation[5][0] = objectClipMat[0][3]-objectClipMat[0][2];
    planeEquation[5][1] = objectClipMat[1][3]-objectClipMat[1][2];
    planeEquation[5][2] = objectClipMat[2][3]-objectClipMat[2][2];
    planeEquation[5][3] = objectClipMat[3][3]-objectClipMat[3][2];

    for (i = 0; i < 6; i++) {
        vectorLength = osgsqrt(
                    planeEquation[i][0] * planeEquation[i][0] +
                    planeEquation[i][1] * planeEquation[i][1] +
                    planeEquation[i][2] * planeEquation[i][2]);
 
        planeEquation[i][0] /= -vectorLength;
        planeEquation[i][1] /= -vectorLength;
        planeEquation[i][2] /= -vectorLength;
        planeEquation[i][3] /= vectorLength;

    }

  // right
  _planeVec[3].set(planeEquation[0]);

  // left
  _planeVec[2].set(planeEquation[1]);

  // bottom
  _planeVec[5].set(planeEquation[2]);

  // top
  _planeVec[4].set(planeEquation[3]);

  // near
  _planeVec[0].set(planeEquation[4]);

  // far
  _planeVec[1].set(planeEquation[5]);
}

/// Returns the center of a box
void FrustumVolume::getCenter(Pnt3f &center) const
{
    // not implemented !!!
    return;
}

/// Gives the volume of the box (0 for an empty box)
float FrustumVolume::getScalarVolume() const
{
    return 0;
    // not implemented !!!
}

/// Gives the boundaries of the volume
void FrustumVolume::getBounds( Pnt3f &minPnt, Pnt3f &maxPnt ) const
{
    // not implemented !!!
    return;
}

/*-------------------------- extending ------------------------------------*/

/// Extends Frustum3f (if necessary) to contain given 3D point
void FrustumVolume::extendBy(const Pnt3f &pt)
{
    // not implemented !!!
    return;
}

/*-------------------------- intersection ---------------------------------*/

/// Returns true if intersection of given point and Frustum3f is not empty
Bool FrustumVolume::intersect(const Pnt3f &point) const
{
    int i;
    Bool retCode = true;

  for (i = 0; i < 6; i++) {
    if ( ( _planeVec[i].getNormal().x() * point.x() +
                     _planeVec[i].getNormal().y() * point.x() +
                     _planeVec[i].getNormal().z() * point.x() +
                     _planeVec[i].getDistanceFromOrigin()) < 0 ) {
      retCode = false;
      break;
    }
  }

  return retCode;
}


/** intersect the box with the given Line */
Bool FrustumVolume::intersect (const Line &line) const
{
    return line.intersect(*this);
}



/** intersect the box with the given Line */
Bool FrustumVolume::intersect ( const Line &line,
                                Real32 &minDist, Real32 &maxDist ) const
{
    return line.intersect(*this,minDist,maxDist);
}


Bool FrustumVolume::isOnSurface (const Pnt3f &point) const
{
    // not implemented
    return false;
}


/// Transforms Frustum3f by matrix, enlarging Frustum3f to contain result
void FrustumVolume::transform(const Matrix &m)
{
    // not implemented
    return;
}

/// Assignment operator
const FrustumVolume &FrustumVolume::operator =(const FrustumVolume &b1)
{
    for (int i = 0; i < 5; i++)
        _planeVec[i] = b1._planeVec[i];
    _state = b1._state;

    return *this;
}

/// print the volume */
void FrustumVolume::dump( UInt32 uiIndent, const BitVector &bvFlags) const
{
    // not implemented !!!
    /*
    PLOG << "Frustum("
             << _planeVec[0] << "|"
             << _planeVec[1] << "|"
             << _planeVec[2] << "|"
             << _planeVec[3] << "|"
             << _planeVec[4] << "|"
             << _planeVec[5] <<
             << ")";
    */
}


OSG_BEGIN_NAMESPACE

/// Equality comparisons
OSG_BASE_DLLMAPPING
Bool operator ==(const FrustumVolume &b1, const FrustumVolume &b2)
{
    return ((b1._planeVec[0] == b2._planeVec[0]) &&
                    (b1._planeVec[1] == b2._planeVec[1]) &&
                    (b1._planeVec[2] == b2._planeVec[2]) &&
                    (b1._planeVec[3] == b2._planeVec[3]) &&
                    (b1._planeVec[4] == b2._planeVec[4]) &&
                    (b1._planeVec[5] == b2._planeVec[5]) &&
                    b1._state == b2._state );
}


OSG_END_NAMESPACE
