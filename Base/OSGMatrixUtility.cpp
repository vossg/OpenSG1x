
// System declarations

#include <math.h>
#include <OSGConfig.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif


#include <OSGBaseFunctions.h>
#include <OSGBaseTypes.h>
#include <OSGVector.h>
#include <OSGMatrix.h>
#include <OSGLog.h>
#include <OSGMatrixUtility.h>

OSG_BEGIN_NAMESPACE


OSGBool OSGMatrixOrthogonal(OSGMatrix &result, 
							OSGReal32 rLeft, 
							OSGReal32 rRight, 
							OSGReal32 rBottom, 
							OSGReal32 rTop, 
							OSGReal32 rNear, 
							OSGReal32 rFar)
{
	result.setValueTransposed( 
		2. / ( rRight - rLeft ), 0., 0., 0.,
		0., 2. / ( rTop - rBottom ), 0., 0.,
		0., 0., -2. / ( rFar - rNear ), 0.,
		-( rRight + rLeft ) / ( rRight - rLeft ), -( rTop + rBottom ) / ( rTop - rBottom ),
		-( rFar + rNear ) / ( rFar - rNear ), 1. );

	return false;
}


OSGBool OSGMatrixFrustum(OSGMatrix &result, 
						 OSGReal32 rLeft, 
						 OSGReal32 rRight, 
						 OSGReal32 rBottom, 
						 OSGReal32 rTop, 
						 OSGReal32 rNear, 
						 OSGReal32 rFar)
{
	OSGReal32	dz = rFar - rNear,
			dx = rRight - rLeft,
			dy = rTop - rBottom,
			n2 = 2 * rNear;

	result.setValueTransposed( 
		n2 / dx, 0, 0, 0,
		0, n2 / dy, 0, 0,
		( rRight + rLeft ) / dx, ( rTop + rBottom ) / dy, -( rFar + rNear ) / dz, -1,
		0, 0, -( rFar * n2 ) / dz, 0 );

	return false;
}


OSGBool OSGMatrixPerspective(OSGMatrix &result, 
							 OSGReal32 rFovy, 
							 OSGReal32 rAspect, 
							 OSGReal32 rNear, 
							 OSGReal32 rFar )
{
	OSGReal32	ct = osgtan( osgdegree2rad(rFovy) );

	if ( rNear > rFar )
	{
		SWARNING << "OSGMatrixPerspective: near " << rNear << " > far " << rFar 
				<< "!\n" << endl;
	}
	if(rFovy <= osgEps)
	{
		SWARNING << "OSGMatrixPerspective: fovy " << rFovy << " very small!\n" << endl;
	}
	if(osgabs(rNear - rFar) < osgEps)
	{
		SWARNING << "OSGMatrixPerspective: near " << rNear << " ~= far " << rFar 
				<< "!\n" << endl;
	}
	if(rAspect < osgEps)
	{
		SWARNING << "OSGMatrixPerspective: aspect ratio " << rAspect 
				<< " very small!\n" << endl;
	}

	OSGMatrixFrustum(result, - rNear * ct * rAspect, rNear * ct * rAspect, 
							 - rNear * ct , rNear * ct, 
							   rNear, rFar );

	return false;
}


OSGBool OSGMatrixStereoPerspective(OSGMatrix &projection, 
								   OSGMatrix &projtrans,
								   OSGReal32 rFovy, 
								   OSGReal32 rAspect, 
								   OSGReal32 rNear, 
								   OSGReal32 rFar, 
								   OSGReal32 rZeroparallax, 
								   OSGReal32 rEyedistance, 
								   OSGReal32 rWhicheye, 
								   OSGReal32 rOverlap )
{
	OSGReal32	rLeft,
			rRight,
			rTop,
			rBottom;
	
	OSGReal32	gltan,
			rEye = - rEyedistance * ( rWhicheye - .5 ), 
			d;

	if ( rNear > rFar )
	{
		SWARNING << "OSGMatrixPerspective: near " << rNear << " > far " << rFar 
				<< "!\n" << endl;
	}
	if ( rFovy <= osgEps )
	{
		SWARNING << "OSGMatrixPerspective: fovy " << rFovy << " very small!\n" << endl;
	}
	if ( osgabs( rNear - rFar ) < osgEps )
	{
		SWARNING << "OSGMatrixPerspective: near " << rNear << " ~= far " << rFar 
				<< "!\n" << endl;
	}
	if ( rAspect < osgEps )
	{
		SWARNING << "OSGMatrixPerspective: aspect ratio " << rAspect 
				<< " very small!\n" << endl;
	}
	if ( rZeroparallax < osgEps )
	{
		SWARNING << "OSGMatrixPerspective: zero parallax " << rZeroparallax 
				<< " very small, setting to 1!\n" << endl;
		rZeroparallax = 1;
	}

	rTop = osgtan( rFovy ) * rNear;	/* Calculate upper and lower clipping planes */
	rBottom = -rTop;


	gltan = osgtan( rFovy * rAspect );	/* Calculate left and right clipping planes */
	rLeft =  ( -gltan + rEye / rZeroparallax ) * rNear;
	rRight = (  gltan + rEye / rZeroparallax ) * rNear;
	
	d = rRight - rLeft;
	
	rLeft += d * ( 1  - rOverlap ) * ( rWhicheye - .5 );
	rRight += d * ( 1  - rOverlap ) * ( rWhicheye - .5 );

	OSGMatrixFrustum( projection, rLeft, rRight, rBottom, rTop, rNear, rFar );

	projtrans.setIdentity();
	projtrans[0][3] = rEye;

	return false;
}

OSGBool OSGMatrixLookAt( OSGMatrix & result, 
	OSGReal32 fromx, OSGReal32 fromy, OSGReal32 fromz, 
	OSGReal32 atx, OSGReal32 aty, OSGReal32 atz, 
	OSGReal32 upx, OSGReal32 upy, OSGReal32 upz )
{
	OSGVec3f view, right, newup,up;

	view.setValues( fromx - atx , fromy - aty, fromz - atz );
	view.normalize();

	up.setValues( upx, upy, upz );
	right = up.cross( view );
	if ( right.dot(right) < osgEps )
	{
		return true;
	}
	
	right.normalize();
	
	newup = view.cross( right );
	
	result.setIdentity();
	result.setTranslate( fromx, fromy, fromz );

	OSGMatrix tmpm;
	tmpm.setValue( right, newup, view );

	result.mult( tmpm );

	return false;
}

OSGBool OSGMatrixLookAt( OSGMatrix & result, OSGPnt3f from, OSGPnt3f at, OSGVec3f up )
{
	OSGVec3f view, right, newup;
	OSGVec3f tmp;
	
	view = from - at;
	view.normalize();

	right = up.cross( view );
	if ( right.dot(right) < osgEps )
	{
		return true;
	}

	right.normalize();
	
	newup = view.cross( right );
	
	result.setIdentity();
	result.setTranslate( from[0], from[1], from[2] );

	OSGMatrix tmpm;
	tmpm.setValue( right, newup, view );

	result.mult( tmpm );

	return false;
}



OSGBool OSGMatrixProjection( OSGMatrix & result, OSGReal32 left, OSGReal32 right, OSGReal32 bottom, 
	OSGReal32 top, OSGReal32 near, OSGReal32 far )
{
	SFATAL << "OSGMatrixProjection: Not yet implemented!" << endl;
	abort();
}

OSG_END_NAMESPACE
