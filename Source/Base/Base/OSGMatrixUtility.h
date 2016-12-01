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

#ifndef _OSGMATRIXUTILITY_H_
#define _OSGMATRIXUTILITY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGBase.h"
#include "OSGBaseTypes.h"
#include "OSGVector.h"
#include "OSGMatrix.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseBaseMatrixFn
    Matrix utility functions to create and analyze special kinds 
    of matrices.
 */

/*! \name Functions */
/*! @{ */

OSG_BASE_DLLMAPPING bool MatrixOrthogonal        (Matrix &result, 
                                                  Real32  rLeft, 
                                                  Real32  rRight, 
                                                  Real32  rBottom, 
                                                  Real32  rTop, 
                                                  Real32  rNear, 
                                                  Real32  rFar        );

OSG_BASE_DLLMAPPING bool MatrixFrustum           (Matrix &result, 
                                                  Real32  rLeft, 
                                                  Real32  rRight,
                                                  Real32  rBottom, 
                                                  Real32  rTop, 
                                                  Real32  rNear, 
                                                  Real32  rFar        );

OSG_BASE_DLLMAPPING bool MatrixPerspective      (Matrix &result, 
                                                 Real32  rFovy, 
                                                 Real32  rAspect,
                                                 Real32  rNear, 
                                                 Real32  rFar         );

OSG_BASE_DLLMAPPING bool MatrixStereoPerspective(Matrix &projection, 
                                                 Matrix &projtrans, 
                                                 Real32  rFovy, 
                                                 Real32  rAspect, 
                                                 Real32  rNear, 
                                                 Real32  rFfar, 
                                                 Real32  rZeroparallax, 
                                                 Real32  rEyedistance, 
                                                 Real32  rWhicheye, 
                                                 Real32  rOverlap     );

OSG_BASE_DLLMAPPING bool MatrixLookAt           (Matrix &result, 
                                                 Real32  fromx, 
                                                 Real32  fromy, 
                                                 Real32  fromz, 
                                                 Real32  atx,   
                                                 Real32  aty,   
                                                 Real32  atz, 
                                                 Real32  upx,   
                                                 Real32  upy,   
                                                 Real32  upz          );

OSG_BASE_DLLMAPPING bool MatrixLookAt           (Matrix &result, 
                                                 Pnt3f      from,
                                                 Pnt3f  at,
                                                 Vec3f  up            );


OSG_BASE_DLLMAPPING bool MatrixProjection       (Matrix &result, 
                                                 Real32 rLeft,
                                                 Real32 rRight, 
                                                 Real32 rBottom,
                                                 Real32 rTop,  
                                                 Real32 rNear,
                                                 Real32 rFar          );

/*! @} */

OSG_END_NAMESPACE

#endif /* _OSGMATRIXUTILITY_H_ */


