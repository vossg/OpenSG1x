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

#include "OSGTrackballNavigator.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGTrackballNavigator.cpp,v 1.3 2002/05/24 14:45:12 istoynov Exp $";
    static Char8 cvsid_hpp       [] = OSGTRACKBALLNAVIGATOR_HEADER_CVSID;
    //static Char8 cvsid_inl       [] = OSGNAVIGATOR_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGTRACKBALLNAVIGATOR_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

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
    Matrix temp;
    _finalMatrix=_tMatrix;
    temp.setIdentity();
    temp.setTranslate(0,0,_rDistance);
    
    _finalMatrix.mult(temp);            
            
    return _finalMatrix;    
}

Pnt3f &TrackballNavigator::getFrom()
{
	_pFrom.setValues(_tMatrix[3][0],_tMatrix[3][1],_tMatrix[3][2]);
	return _pFrom;
}

Pnt3f &TrackballNavigator::getAt()
{
	return _pAt;
}

Vec3f &TrackballNavigator::getUp()
{
	return _vUp;
}


/*------------------------------ set --------------------------------------*/


/*! sets the from point. that's the point where the person is (i.e the center of all transformations and the trackball)
 */

void TrackballNavigator::setFrom(Pnt3f new_from)
{
    _pFrom=new_from;
	_tMatrix.setTranslate(new_from[0],new_from[1],new_from[2]);    
}

/*! sets the point the person is looking at
 */

void TrackballNavigator::setAt(Pnt3f new_at)
{
	_pAt=new_at;
	_pFrom.setValues(_tMatrix[3][0],_tMatrix[3][1],_tMatrix[3][2]);
    MatrixLookAt(_tMatrix,_pFrom,_pAt,_vUp);
}

/*! sets the distance to the center of the trackball
 */

void TrackballNavigator::setDistance(Real32 new_distance)
{
    _rDistance=new_distance;
}

/*! sets the up vector
 */

void TrackballNavigator::setUp(Vec3f new_up)
{
	_vUp=new_up;
	_pFrom.setValues(_tMatrix[3][0],_tMatrix[3][1],_tMatrix[3][2]);
    MatrixLookAt(_tMatrix,_pFrom,_pAt,_vUp);
}

void TrackballNavigator::set(Pnt3f new_from, Pnt3f new_at, Vec3f new_up)
{
	_pFrom=new_from;
	_pAt=new_at;
	_vUp=new_up;
    MatrixLookAt(_tMatrix,new_from,new_at,new_up);
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
