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
 * WITHOUT ANY WARRANTY; without even the impclied warranty of               *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*//*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#define OSG_COMPILEBASE

#include "OSGVolume.h"
#include "OSGBoxVolume.h"
#include "OSGSphereVolume.h"
#include "OSGCylinderVolume.h"
#include "OSGFrustumVolume.h"
#include "OSGDynamicVolume.h"

OSG_BEGIN_NAMESPACE

// ###################################################################
// # Volume Interesect Functions #####################################
// ###################################################################

OSG_BASE_DLLMAPPING Bool intersect ( const Volume &vol1, 
													    			 const Volume &vol2)
{
	// imp;
	return false;
}
	
// # Box #############################################################

OSG_BASE_DLLMAPPING Bool intersect ( const BoxVolume &box1, 
															       const BoxVolume &box2)
{
	Bool retCode = false;

	if (box1.isEmpty() || box2.isEmpty())
		retCode = false;
	else
		if (box1.isInfinite() || box2.isInfinite())
			retCode = true;
		else
			retCode = 
				(box1.getMin()[0] <= box2.getMax()[0] && 
				 box1.getMax()[0] >= box2.getMin()[0]) &&
				(box1.getMin()[1] <= box2.getMax()[1] && 
				 box1.getMax()[1] >= box2.getMin()[1]) &&
				(box1.getMin()[2] <= box2.getMax()[2] && 
				 box1.getMax()[2] >= box2.getMin()[2]);

	return retCode;
}

OSG_BASE_DLLMAPPING Bool intersect ( const BoxVolume &box, 
																     const SphereVolume &sphere)
{
	// source: 
	// J. Arvo. A simple method for box-sphere intersection testing. 
	// In A. Glassner, editor, Graphics Gems, pp. 335-339, 
	// Academic Press, Boston, MA, 1990

	Bool retCode;
	Real32 s, d = 0; 
	Int32 i;

	if (box.isEmpty() || sphere.isEmpty())
		retCode = false;
	else
		if (box.isInfinite() || sphere.isInfinite())
			retCode = true;
		else {
			//find the square of the distance from the sphere to the box
			for( i=0; i<3; i++ ) {  
				if (sphere.getCenter()[i] < box.getMin()[i]) {
					s = sphere.getCenter()[i] - box.getMin()[i];
					d += s*s; 
				}
				else 
					if( sphere.getCenter()[i] > box.getMax()[i] ) {
						s = sphere.getCenter()[i] - box.getMax()[i];
						d += s*s; 
					}
			}
	    retCode = (d <= (sphere.getRadius() * sphere.getRadius()));
		}

	return retCode;
}

OSG_BASE_DLLMAPPING Bool intersect ( const BoxVolume &box, 
																		 const CylinderVolume &cylinder)
{

  Bool retCode;
  Real32 s1=0, s2=0, s3=0, s4=0, d=0, d1=0, d2=0;
  Pnt3f c,p,p1,p2, apos ;
  Vec3f adir, u, u1, u2;
  
  cylinder.getAxis(apos,adir);
  
  if (box.isEmpty() || cylinder.isEmpty())
    retCode = false;

  else
    if (box.isInfinite() || cylinder.isInfinite())
      retCode = true;

    else {


	s1 = (apos - box.getMin()).length();
	s2 = (apos - box.getMax()).length();
	s3 = (apos + adir - box.getMin()).length();
	s4 = (apos + adir - box.getMax()).length();
      
      if (s1 <= s2) { 
       d1 = s1;
       p1 = box.getMin();
      }

      else {
	d1 = s2;
	p1 = box.getMax();
      }

      if (s3 <= s4) {
       d2 = s3;
       p2 = box.getMin();
      }

      else {
	d2 = s4;
	p2 = box.getMax();
      }
      
      if (d1 <= d2) {
	d = d1;
	c = apos;
	p = p1;
      }

      else {
	d = d2;
	c = apos + adir;
	p = p2;
      }

      u = p-c;
      u1 = (u[0]*adir[0] + u[1]*adir[1] +u[2]*adir[2]) 
           / (adir.length()*adir.length())*adir;

      u2 = u - u1;

      if (u1.length()<=10e-6)
	retCode = true;
      else if (u2.length() <= 10e-6)
	retCode = (d <= 10e-6);
      else
	retCode = (u2.length() <=cylinder.getRadius());

    }

  return retCode;
}



OSG_BASE_DLLMAPPING Bool intersect ( const BoxVolume &box, 
																		 const FrustumVolume &frustum)
{
	// imp;
	return false;
}

OSG_BASE_DLLMAPPING Bool intersect ( const BoxVolume &box, 
																		 const Volume &vol)
{
	Bool retCode = false;
	const DynamicVolume *dv = dynamic_cast<const DynamicVolume *>(&vol);
	const Volume *v = dv ? &(dv->getInstance()) : &vol;
	const BoxVolume *bv;
	const SphereVolume *sv;
	const CylinderVolume *cv;
	const FrustumVolume *fv;

	if ((bv = dynamic_cast<const BoxVolume*>(v)))
		retCode = intersect(box,*bv);
	else
		if ((sv = dynamic_cast<const SphereVolume*>(v)))
			retCode = intersect(box,*sv);
		else
			if ((cv = dynamic_cast<const CylinderVolume*>(v)))
				retCode = intersect(box,*cv);
			else
				if ((fv = dynamic_cast<const FrustumVolume*>(v)))
					retCode = intersect(box,*fv);
			
	return retCode;
}


// # Sphere ###########################################################

OSG_BASE_DLLMAPPING Bool intersect ( const SphereVolume &sphere1, 
																		      const SphereVolume &sphere2)
{
	Bool retCode = false;
	Real32 dist = (sphere2.getCenter() - sphere1.getCenter()).length();
	
	if (sphere1.isEmpty() || sphere2.isEmpty())
		retCode = false;
	else
		if (sphere1.isInfinite() || sphere2.isInfinite())
			retCode = true;
		else
			if ( dist < sphere1.getRadius() + sphere2.getRadius())
				retCode = true;

	return retCode;
}


OSG_BASE_DLLMAPPING Bool intersect (const SphereVolume &sphere,
																		 const CylinderVolume &cylinder)
{
  Bool retCode;
  Real32 d=0 ,s1=0, s2=0; 
  Pnt3f apos,c;
  Vec3f adir, u, u1, u2;

  cylinder.getAxis(apos,adir);
  if (sphere.isEmpty() || cylinder.isEmpty())
    retCode = false;

  else
    if (sphere.isInfinite() || cylinder.isInfinite())
      retCode = true;

    else {
      s1 = (apos - sphere.getCenter()).length();
      s2 = (apos +adir - sphere.getCenter()).length();

      if (s1<=s2) {
	d = s1;
	c = apos;
      }
      else {
	d = s2;
	c = apos + adir;
      }
      
      
      u = ((d-sphere.getRadius())/d)*(c-sphere.getCenter());
      u1 = (u[0]*adir[0] + u[1]*adir[1] + u[2]*adir[2])/(adir.length()*adir.length())* adir;
      u2 = (u-u1);
      
      if (u2.length()<=10e-6)
	retCode = (d <=sphere.getRadius());

      else
	retCode = (u2.length() <= cylinder.getRadius());

    }

  return retCode;
}


OSG_BASE_DLLMAPPING Bool intersect ( const SphereVolume &sphere, 
																		 const FrustumVolume &frustum)
{
	// imp;
	return false;
}


OSG_BASE_DLLMAPPING Bool intersect ( const SphereVolume &sphere, 
																		 const Volume &vol)
{
	Bool retCode = false;
	const DynamicVolume *dv = dynamic_cast<const DynamicVolume *>(&vol);
	const Volume *v = dv ? &(dv->getInstance()) : &vol;
	const BoxVolume *bv;
	const SphereVolume *sv;
	const CylinderVolume *cv;
	const FrustumVolume *fv;

	if ((bv = dynamic_cast<const BoxVolume*>(v)))
		retCode = intersect(sphere,*bv);
	else
		if ((sv = dynamic_cast<const SphereVolume*>(v)))
			retCode = intersect(sphere,*sv);
		else
			if ((cv = dynamic_cast<const CylinderVolume*>(v)))
				retCode = intersect(sphere,*cv);
			else
				if ((fv = dynamic_cast<const FrustumVolume*>(v)))
					retCode = intersect(sphere,*fv);
			
	return retCode;
}

// # Cylinder ########################################################

OSG_BASE_DLLMAPPING Bool intersect ( const CylinderVolume &cylinder1, 
																		 const CylinderVolume &cylinder2)
{
	// imp;
	return false;
}

OSG_BASE_DLLMAPPING Bool intersect ( const CylinderVolume &cylinder, 
															
			 const FrustumVolume &frustum)
{
	// imp;
	return false;
}

OSG_BASE_DLLMAPPING Bool intersect ( const CylinderVolume &cylinder, 
																		 const Volume &vol)
{
	// imp;
	return false;
}


// # Frustum ########################################################

OSG_BASE_DLLMAPPING Bool intersect ( const FrustumVolume &frustum1, 
																		 const FrustumVolume &frustum2)
{
	// imp;
	return false;
}

OSG_BASE_DLLMAPPING Bool intersect ( const FrustumVolume &frustum, 
																		 const Volume &vol)
{
	// imp;
	return false;
}

// ###################################################################
// # Volume Extend Functions #########################################
// ###################################################################

OSG_BASE_DLLMAPPING void extend ( Volume &srcVol, 
                                  const Volume &vol)
{
	// imp;
	return;
}


// # Box #############################################################
OSG_BASE_DLLMAPPING void extend ( BoxVolume &srcVol, 
																	const BoxVolume &vol)
{
	if ( (! srcVol.isValid() && ! srcVol.isEmpty()) || 
			 srcVol.isInfinite() || srcVol.isStatic() )
		return;

	if ( ! vol.isValid() )
		return;
	
	if (srcVol.isEmpty())
		if (vol.isEmpty())
			return;
		else {
			srcVol = vol;
			return;
		}
	else
		if (vol.isEmpty())
			return;

	srcVol.setBounds ( osgMin(vol.getMin().x(),srcVol.getMin().x()),
										 osgMin(vol.getMin().y(),srcVol.getMin().y()),
										 osgMin(vol.getMin().z(),srcVol.getMin().z()),
										 osgMax(vol.getMax().x(),srcVol.getMax().x()),
										 osgMax(vol.getMax().y(),srcVol.getMax().y()),
										 osgMax(vol.getMax().z(),srcVol.getMax().z()));

	if (vol.isInfinite())
		srcVol.setInfinite(true);

	return;
}

OSG_BASE_DLLMAPPING void extend ( BoxVolume &srcVol, 
																	const SphereVolume &vol)
{
	// imp;
	return;
}

OSG_BASE_DLLMAPPING void extend ( BoxVolume &srcVol, 
																	const CylinderVolume &vol)
{
	// imp;
	return;
}

OSG_BASE_DLLMAPPING void extend ( BoxVolume &srcVol, 
																	const FrustumVolume &vol)
{
	// imp;
	return;
}

#ifdef __sgi
#pragma set woff 1174,1552
#endif

OSG_BASE_DLLMAPPING void extend ( BoxVolume &srcVol, 
																	const Volume &vol)
{
	const Volume *v = &vol;
	const BoxVolume *box;
	const SphereVolume *sphere;
	const CylinderVolume *cylinder;
	const DynamicVolume *dynamic = dynamic_cast<const DynamicVolume*>(v);

	if (dynamic)
		v = &(dynamic->getInstance());
	
	if ((box = dynamic_cast<const BoxVolume*>(v)))
		osg::extend(srcVol,*box);
	else {
		BoxVolume localBox;
		Pnt3f min,max;
		v->getBounds(min,max);
		localBox.setBounds(min,max);
		osg::extend(srcVol,localBox);
	}
}

#ifdef __sgi
#pragma reset woff 1174,1552
#endif

// # Sphere ###########################################################
OSG_BASE_DLLMAPPING void extend ( SphereVolume &srcVol, 
																	const BoxVolume &vol)
{
	// imp;
	return;
}

OSG_BASE_DLLMAPPING void extend ( SphereVolume &srcVol, 
																	const SphereVolume &vol)
{
	// imp;
	return;
}
OSG_BASE_DLLMAPPING void extend ( SphereVolume &srcVol, 
																	const CylinderVolume &vol)
{
	// imp;
	return;
}

OSG_BASE_DLLMAPPING void extend ( SphereVolume &srcVol, 
																	const FrustumVolume &vol)
{
	// imp;
	return;
}

OSG_BASE_DLLMAPPING void extend ( SphereVolume &srcVol, 
																	const Volume &vol )
{
	// imp;
	return;
}

// # Cylinder ########################################################
OSG_BASE_DLLMAPPING void extend ( CylinderVolume &srcVol, 
																	const BoxVolume &vol)
{
	// imp;
	return;
}

OSG_BASE_DLLMAPPING void extend ( CylinderVolume &srcVol, 
																	const SphereVolume &vol)
{
	// imp;
	return;
}

OSG_BASE_DLLMAPPING void extend ( CylinderVolume &srcVol, 
																	const CylinderVolume &vol)
{
	// imp;
	return;
}

OSG_BASE_DLLMAPPING void extend ( CylinderVolume &srcVol, 
																	const FrustumVolume &vol)
{
	// imp;
	return;
}

OSG_BASE_DLLMAPPING void extend ( CylinderVolume &srcVol, 
																	const Volume &vol)
{
	// imp;
	return;
}

// # Frustum ########################################################
OSG_BASE_DLLMAPPING void extend ( FrustumVolume &srcVol, 
																	const BoxVolume &vol)
{
	// imp;
	return;
}

OSG_BASE_DLLMAPPING void extend ( FrustumVolume &srcVol, 
																	const SphereVolume &vol)
{
	// imp;
	return;
}

OSG_BASE_DLLMAPPING void extend ( FrustumVolume &srcVol, 
																	const CylinderVolume &vol)
{
	// imp;
	return;
}

OSG_BASE_DLLMAPPING void extend ( FrustumVolume &srcVol, 
																	const FrustumVolume &vol)
{
	// imp;
	return;
}

OSG_BASE_DLLMAPPING void extend ( FrustumVolume &srcVol, 
																	const Volume &vol)
{
	// imp;
	return;
}

OSG_END_NAMESPACE
