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


#ifndef _OSG_MATRIX_UTILITY_H_
#define _OSG_MATRIX_UTILITY_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGConfig.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

template<class OSGValueTypeT>class OSGTransformationMatrix;
typedef OSGTransformationMatrix<OSGReal32> OSGMatrix;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseLib
 *  \brief Matrix utility functions to create and analyze special kinds of matrices
 */


OSGBool OSGMatrixOrthogonal(OSGMatrix &result, 
							OSGReal32  rLeft, 
							OSGReal32  rRight, 
							OSGReal32  rBottom, 
							OSGReal32  rTop, 
							OSGReal32  rNear, 
							OSGReal32  rFar);


OSGBool OSGMatrixFrustum(OSGMatrix &result, 
						 OSGReal32  rLeft, 
						 OSGReal32  rRight,
						 OSGReal32  rBottom, 
						 OSGReal32  rTop, 
						 OSGReal32  rNear, 
						 OSGReal32  rFar);


/** fovy is vertical fov/2 in degrees, aspect is width/height */

OSGBool OSGMatrixPerspective(OSGMatrix &result, 
							 OSGReal32  rFovy, 
							 OSGReal32  rAspect,
							 OSGReal32  rNear, 
							 OSGReal32  rFar);


/** fovy is vertical fov/2 in degrees, aspect is width/height, ... */

OSGBool OSGMatrixStereoPerspective(OSGMatrix &projection, 
								   OSGMatrix &projtrans, 
								   OSGReal32  rFovy, 
								   OSGReal32  rAspect, 
								   OSGReal32  rNear, 
								   OSGReal32  rFfar, 
								   OSGReal32  rZeroparallax, 
								   OSGReal32  rEyedistance, 
								   OSGReal32  rWhicheye, 
								   OSGReal32  rOverlap );


/** creates a matrix that transforms the given pos/ori into the origin */

OSGBool OSGMatrixLookAt( OSGMatrix & result, 
	OSGReal32 fromx, OSGReal32 fromy, OSGReal32 fromz, 
	OSGReal32 atx, OSGReal32 aty, OSGReal32 atz, 
	OSGReal32 upx, OSGReal32 upy, OSGReal32 upz );

OSGBool OSGMatrixLookAt( OSGMatrix & result, OSGPnt3f from, OSGPnt3f at, OSGVec3f up );


OSGBool OSGMatrixProjection( OSGMatrix & result, OSGReal32 left, OSGReal32 right, OSGReal32 bottom, 
	OSGReal32 top, OSGReal32 near, OSGReal32 dar );

OSG_END_NAMESPACE

#endif /* _OSG_MATRIX_UTILITY_H_ */


