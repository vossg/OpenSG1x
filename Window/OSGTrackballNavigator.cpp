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

/*------------------------- constructors ----------------------------------*/

/*! Constructor
 */

TrackballNavigator::TrackballNavigator(Real32 rSize): _rRadius(rSize)
{
    _finalMatrix.setIdentity();
    _tMatrix.setIdentity();
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

/*------------------------------ set --------------------------------------*/

/*! sets the center of the trackball in real coordinates
 */

void TrackballNavigator::setCenter(Pnt3f new_center)
{
    _tMatrix.setTranslate(new_center[0],new_center[1],new_center[2]);    
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
    Pnt3f from(_tMatrix[3][0],_tMatrix[3][1],_tMatrix[3][2]);
    Pnt3f to=from; to[2]-=1;
    MatrixLookAt(_tMatrix,from,to,new_up);
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGTrackballNavigator.cpp,v 1.2 2002/04/30 09:29:14 vossg Exp $";
    static Char8 cvsid_hpp       [] = OSGTRACKBALLNAVIGATOR_HEADER_CVSID;
    //static Char8 cvsid_inl       [] = OSGNAVIGATOR_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGTRACKBALLNAVIGATOR_HEADER_CVSID;
}
