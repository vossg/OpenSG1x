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

#ifndef _OSGMATRIXUTILITY_H_
#define _OSGMATRIXUTILITY_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGBase.h>

OSG_BEGIN_NAMESPACE

template<class ValueTypeT>class TransformationMatrix;
typedef TransformationMatrix<Real32> Matrix;

/*! \ingroup BaseMathMatrices
 *  \brief Matrix utility functions to create and analyze special kinds 
 *         of matrices
 */

/*!@{*/

OSG_BASE_DLLMAPPING Bool MatrixOrthogonal           (Matrix &result, 
                                                     Real32  rLeft, 
                                                     Real32  rRight, 
                                                     Real32  rBottom, 
                                                     Real32  rTop, 
                                                     Real32  rNear, 
                                                     Real32  rFar       );

OSG_BASE_DLLMAPPING Bool MatrixFrustum              (Matrix &result, 
                                                     Real32  rLeft, 
                                                     Real32  rRight,
                                                     Real32  rBottom, 
                                                     Real32  rTop, 
                                                     Real32  rNear, 
                                                     Real32  rFar       );

OSG_BASE_DLLMAPPING Bool MatrixPerspective          (Matrix &result, 
                                                     Real32  rFovy, 
                                                     Real32  rAspect,
                                                     Real32  rNear, 
                                                     Real32  rFar       );

OSG_BASE_DLLMAPPING Bool MatrixStereoPerspective    (Matrix &projection, 
                                                     Matrix &projtrans, 
                                                         Real32  rFovy, 
                                                     Real32  rAspect, 
                                                     Real32  rNear, 
                                                     Real32  rFfar, 
                                                     Real32  rZeroparallax, 
                                                     Real32  rEyedistance, 
                                                     Real32  rWhicheye, 
                                                     Real32  rOverlap   );

OSG_BASE_DLLMAPPING Bool MatrixLookAt               (Matrix &result, 
                                                     Real32  fromx, 
                                                     Real32  fromy, 
                                                     Real32  fromz, 
                                                     Real32  atx,   
                                                     Real32  aty,   
                                                     Real32  atz, 
                                                     Real32  upx,   
                                                     Real32  upy,   
                                                     Real32  upz        );

OSG_BASE_DLLMAPPING Bool MatrixLookAt               (Matrix &result, 
                                                     Pnt3f      from,
                                                     Pnt3f  at,
                                                     Vec3f  up          );


OSG_BASE_DLLMAPPING Bool MatrixProjection           (Matrix &result, 
                                                     Real32 rLeft,
                                                     Real32 rRight, 
                                                     Real32 rBottom,
                                                     Real32 rTop,  
                                                     Real32 rNear,
                                                     Real32 rFar        );

/*!@}*/

OSG_END_NAMESPACE

#endif /* _OSGMATRIXUTILITY_H_ */


