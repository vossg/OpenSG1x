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

#include <OSGConfig.h>
#include <OSGBaseTypes.h>
#include <OSGMatrix.h>
#include <OSGMatrixUtility.h>

#include "OSGNodePtr.h"
#include "OSGTrackballNavigator.h"

OSG_USING_NAMESPACE

/*------------------------- constructors ----------------------------------*/

/*! Constructor
 */

TrackballNavigator::TrackballNavigator(Real32 rSize): _rRadius(rSize)
{
    _finalMatrix.setIdentity();
    _tMatrix.setIdentity();
    _pFrom.setValues(0,0,0);
    _pAt.setValues(0,0,1);
    _vUp.setValues(0,1,0);
    _rDistance=(_pAt-_pFrom).length();
}

/*-------------------------- destructors ----------------------------------*/

/*! Destructor
 */

TrackballNavigator::~TrackballNavigator()
{
}

/*------------------------------ get --------------------------------------*/

/*! get the current transformation matrix
 */

Matrix &TrackballNavigator::getMatrix()
{
    updateFinalMatrix();
    return _finalMatrix;
}

Pnt3f &TrackballNavigator::getFrom()
{
    _pFrom=(Pnt3f)_finalMatrix[3];
    return _pFrom;
}

Pnt3f &TrackballNavigator::getAt()
{
    _pAt=(Pnt3f)(_finalMatrix[3] - (_rDistance*_finalMatrix[2]));
    return _pAt;
}

Vec3f &TrackballNavigator::getUp()
{
    _vUp=(Vec3f)_finalMatrix[1];
    return _vUp;
}


/*------------------------------ set --------------------------------------*/


/*! sets the from point. that's the point where the person is (i.e the center of all transformations and the trackball)
 */

void TrackballNavigator::setFrom(Pnt3f new_from)
{
    set(new_from,getAt(),getUp());
}

/*! sets the point the person is looking at
 */

void TrackballNavigator::setAt(Pnt3f new_at)
{
    set(getFrom(),new_at,getUp());
}

/*! Sets the distance from the from in the view direction
 */

void TrackballNavigator::setDistance(Real32 new_distance)
{
    _rDistance=new_distance;
    updateFinalMatrix();
}

/*! sets the up vector
 */

void TrackballNavigator::setUp(Vec3f new_up)
{
    set(getFrom(),getAt(),new_up);
}

void TrackballNavigator::set(Pnt3f new_from, Pnt3f new_at, Vec3f new_up)
{
    bool b=MatrixLookAt(_tMatrix,new_at,new_at+(new_at-new_from),new_up);
    if (!b)
    {
        _rDistance=(new_at-new_from).length();
        updateFinalMatrix();
    }
    else
        FNOTICE(("TrackballNavigator: set(.,.,.), failed")); 
}

void TrackballNavigator::set(Matrix new_matrix)
{
    _pFrom=(Pnt3f)new_matrix[3];
    _pAt=(Pnt3f)(new_matrix[3] - (_rDistance*new_matrix[2]));
    _vUp=(Vec3f)new_matrix[1];
    set(_pFrom,_pAt,_vUp);
}

/*-------------------- Trackball Transformations --------------------------*/

/*! makes a rotation
 */

void TrackballNavigator::rotate(Real32 fromX, Real32 fromY, Real32 toX, Real32 toY)
{
    Quaternion qCurrVal;

    Vec3f vAxis;
    Real32 rPhi;

    Vec3f vP1,vP2,vDiff;

    Real32 rTmp;

    if (osgabs(fromX-toX)>Eps || osgabs(fromY-toY)>Eps)
    {
        vP1.setValues(fromX,fromY,projectToSphere(_rRadius,fromX,fromY));
        vP2.setValues(toX,toY,projectToSphere(_rRadius,toX,toY));

        vAxis=vP2;
        vAxis.crossThis(vP1);

        vDiff=vP1;
        vDiff-=vP2;

        rTmp=vDiff.length()/(2.0f*_rRadius);
        if (rTmp>1.0) rTmp=1.0;
        if (rTmp<-1.0) rTmp=-1.0;

        rPhi=2.0*osgasin(rTmp);
        qCurrVal.setValueAsAxisRad(vAxis,rPhi);

        Matrix temp;
        qCurrVal.getValue(temp);
        //temp.transpose();

        _tMatrix.mult(temp);
    }
}

/*! makes translation in the XY plane
 */

void TrackballNavigator::translateXY(Real32 distanceX, Real32 distanceY)
{
    Matrix temp;
    temp.setIdentity();
    temp.setTranslate(distanceX,distanceY,0);
    _tMatrix.mult(temp);
}

/*! makes a translation along the Z-axis
 */

void TrackballNavigator::translateZ(Real32 distance)
{
    _rDistance+=distance;
}

/*! project a point on the virtual trackball
 */

Real32 TrackballNavigator::projectToSphere(Real32 rRadius, Real32 rX, Real32 rY)
{
    Real32 d, t, z;

    d = sqrt(rX * rX + rY * rY);

    if (d < rRadius * 0.70710678118654752440f)
    {    /* Inside sphere */
        z = sqrt(rRadius * rRadius - d * d);
    }
    else
    {           /* On hyperbola */
        t = rRadius / 1.41421356237309504880f;
        z = t * t / d;
    }

    return z;
}

void TrackballNavigator::updateFinalMatrix()
{
    Matrix temp;
    _finalMatrix=_tMatrix;
    temp.setIdentity();
    temp.setTranslate(0,0,_rDistance);

    _finalMatrix.mult(temp);
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGTrackballNavigator.cpp,v 1.7 2002/08/07 04:04:14 vossg Exp $";
    static Char8 cvsid_hpp       [] = OSGTRACKBALLNAVIGATOR_HEADER_CVSID;
    //static Char8 cvsid_inl       [] = OSGNAVIGATOR_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGTRACKBALLNAVIGATOR_HEADER_CVSID;
}
