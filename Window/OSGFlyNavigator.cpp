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

#include "OSGFlyNavigator.h"

OSG_USING_NAMESPACE

/*------------------------- constructors ----------------------------------*/

/*! Constructor
 */
 
FlyNavigator::FlyNavigator()
{
    _rEye=Pnt3f(0,0,1);
    _rCenter=Pnt3f(0,0,0);
    _vUp=Vec3f(0,1,0);
    _tMatrix.setIdentity();
}
 

/*-------------------------- destructors ----------------------------------*/

/*! Destructor
 */

FlyNavigator::~FlyNavigator()
{
}

/*------------------------------ get --------------------------------------*/

/*! get the current transformation matrix
 */

Matrix &FlyNavigator::getMatrix()
{
    MatrixLookAt(_tMatrix,_rEye,_rCenter,_vUp);
    return _tMatrix;
}

/*------------------------------ set --------------------------------------*/

/*! sets the eye point
 */

void FlyNavigator::setFrom(Pnt3f new_eye)
{
    _rEye=new_eye;
}

/*! sets the point at which the eye is looking
 */

void FlyNavigator::setAt(Pnt3f new_center)
{
    _rCenter=new_center;
}

/*! sets the up vector
 */

void FlyNavigator::setUp(Vec3f new_up)
{
    _vUp=new_up;
}

/*---------------------- Flyer Transformations ----------------------------*/

/*! makes a rotation
 */

void FlyNavigator::rotate(Real32 deltaX, Real32 deltaY)
{    
    // rotate around the up vector
    Matrix final,temp;
    Quaternion q;   
    
    q.setValueAsAxisRad(_vUp,-deltaX);
    q.getValue(temp);    
    
    final.setIdentity();
    final.setTranslate(_rEye);
    final.mult(temp);
    
    temp.setIdentity(); 
    temp.setTranslate(-_rEye[0],-_rEye[1],-_rEye[2]);
    
    final.mult(temp);    
    final.multMatrixPnt(_rCenter);
    
    // rotate around the side vector
            
    Vec3f lv=_rCenter-_rEye;
    lv.normalize();                              
            
    Vec3f sv=lv; 
    sv.crossThis(_vUp);
    sv.normalize();            
    q.setValueAsAxisRad(sv,-deltaY);
    q.getValue(temp);

    final.setIdentity();
    final.setTranslate(_rEye);
    final.mult(temp);
        
    temp.setIdentity(); 
    temp.setTranslate(-_rEye[0],-_rEye[1],-_rEye[2]);
    
    final.mult(temp);        
    final.multMatrixPnt(_rCenter);    
}

/*! "flyes" forward, i.e. makes a translation along the view vector
 */

void FlyNavigator::forward(Real32 step)
{
    Vec3f lv;
    lv=_rEye-_rCenter;
    lv.normalize();                                  
    lv*=(step);
    Matrix transl;
    transl.setIdentity();
    transl.setTranslate(lv);                   
    transl.multMatrixPnt(_rCenter);
    transl.multMatrixPnt(_rEye);    
}

/*! "flyes" on the right, i.e. makes a translation along the side vector
 */

void FlyNavigator::right(Real32 step)
{
    Vec3f sv;
    sv=_rEye-_rCenter;
    sv.crossThis(_vUp);
    sv.normalize();            
    sv*=(step);
    Matrix transl;
    transl.setIdentity();
    transl.setTranslate(sv);                   
    transl.multMatrixPnt(_rCenter);
    transl.multMatrixPnt(_rEye); 
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGFlyNavigator.cpp,v 1.2 2002/04/30 09:29:13 vossg Exp $";
    static Char8 cvsid_hpp       [] = OSGFLYNAVIGATOR_HEADER_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGFLYNAVIGATOR_HEADER_CVSID;
}
