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
 \*--------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
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

#define OSG_COMPILEBASELIB

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
	Bool retCode = false;
	const DynamicVolume *dv = dynamic_cast<const DynamicVolume *>(&vol1);
	const Volume *v = dv ? &(dv->getInstance()) : &vol1;
	const BoxVolume *bv;
	const SphereVolume *sv;
	const CylinderVolume *cv;
	const FrustumVolume *fv;

	if ((bv = dynamic_cast<const BoxVolume*>(v)))
		retCode = intersect(*bv,vol2);
	else
		if ((sv = dynamic_cast<const SphereVolume*>(v)))
			retCode = intersect(*sv,vol2);
		else
			if ((cv = dynamic_cast<const CylinderVolume*>(v)))
				retCode = intersect(*cv,vol2);
			else
				if ((fv = dynamic_cast<const FrustumVolume*>(v)))
					retCode = intersect(*fv,vol2);

	return retCode;
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
      
      // find the distance between the min and the max of the box 
      //with the lower point and the upper point of the cylinder respectively
     
	s1 = (apos - box.getMin()).length();
	s2 = (apos - box.getMax()).length();
	s3 = (apos + adir - box.getMin()).length();
	s4 = (apos + adir - box.getMax()).length();

	//Check the minimum of the above distances
 
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

      //set the value of the vector corresponding to the shortest distance

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
      //decompose the vector in u1 and u2 which are parallel and perpendicular to the cylinder axis respectively


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
  int i;
  const Pnt3f &min = box.getMin();
  const Pnt3f &max = box.getMax();
 
  Plane frust[] = {frustum.getNear(),
		   frustum.getFar(),
		   frustum.getLeft(), 
		   frustum.getRight(),
		   frustum.getTop(),
		   frustum.getBottom()};

  // check each point of the box to the 6 planes

  for (i=0; i<6; i++){
    if(frust[i].getNormal().x()*min.x()+
       frust[i].getNormal().y()*min.y()+
       frust[i].getNormal().z()*min.z()-
       frust[i].getDistanceFromOrigin()<0)
      continue;

    if(frust[i].getNormal().x()*min.x()+
       frust[i].getNormal().y()*min.y()+
       frust[i].getNormal().z()*max.z()-
       frust[i].getDistanceFromOrigin()<0)
      continue;

    if(frust[i].getNormal().x()*min.x()+
       frust[i].getNormal().y()*max.y()+
       frust[i].getNormal().z()*min.z()-
       frust[i].getDistanceFromOrigin()<0)
      continue;

    if(frust[i].getNormal().x()*min.x()+
       frust[i].getNormal().y()*max.y()+
       frust[i].getNormal().z()*max.z()-
       frust[i].getDistanceFromOrigin()<0)
      continue;

    if(frust[i].getNormal().x()*max.x()+
       frust[i].getNormal().y()*min.y()+
       frust[i].getNormal().z()*min.z()-
       frust[i].getDistanceFromOrigin()<0)
      continue;

    if(frust[i].getNormal().x()*max.x()+
       frust[i].getNormal().y()*min.y()+
       frust[i].getNormal().z()*max.z()-
       frust[i].getDistanceFromOrigin()<0)
      continue;

    if(frust[i].getNormal().x()*max.x()+
       frust[i].getNormal().y()*max.y()+
       frust[i].getNormal().z()*min.z()-
       frust[i].getDistanceFromOrigin()<0)
      continue;

    if(frust[i].getNormal().x()*max.x()+
       frust[i].getNormal().y()*max.y()+
       frust[i].getNormal().z()*max.z()-
       frust[i].getDistanceFromOrigin()<0)
      continue;


    return false;
  }

  return true;

	
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

	//check if the distance between the center of the 2 spheres is bigger than the sum of the 2 radiuses

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

  //get the distance between the upper and lower point of the cylinder and the sphere center

    else {
      s1 = (apos - sphere.getCenter()).length();
      s2 = (apos +adir - sphere.getCenter()).length();

      //check the smallest distance and set the vector coordinate

      if (s1<=s2) {
	d = s1;
	c = apos;
      }
      else {
	d = s2;
	c = apos + adir;
      }
      
       //decompose the vector in u1 and u2 which are parallel and perpendicular to the cylinder axis respectively

      u = ((d-sphere.getRadius())/d)*(c-sphere.getCenter());
      u1 = (u[0]*adir[0] + u[1]*adir[1] + u[2]*adir[2])/(adir.length()*adir.length())* adir;
      u2 = u - u1;
          
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
	int i;
	Plane frust[6] = { frustum.getNear(), frustum.getFar(), 
                     frustum.getLeft(), frustum.getRight(), 
                     frustum.getTop(), frustum.getBottom()};

	//check the center of the sphere with each plane of the frustum
	for (i=0;i<6;i++){
	  if (frust[i].getNormal().x()*sphere.getCenter().x() +
	      frust[i].getNormal().y()*sphere.getCenter().y() +
	      frust[i].getNormal().z()*sphere.getCenter().z() - 
	      frust[i].getDistanceFromOrigin()<=-sphere.getRadius())
	    return false;
	}	
	return true;
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


  Vec3f adir1, adir2,n;
  Pnt3f apos1, apos2, p;
  double d;
  Bool retCode = false;
  cylinder1.getAxis(apos1,adir1);
  cylinder2.getAxis(apos2,adir2);

  //get the shortest distance between the two axes of the cylinders

  n = adir1.cross(adir2);
  n.normalize();
  p = apos1 - apos2;
  d = fabs(n.dot(p));
  
  if (cylinder1.isEmpty() || cylinder2.isEmpty())
    retCode = false;

  else

    if (cylinder1.isInfinite() || cylinder2.isInfinite())
      retCode = true;

    else 

      //check whether the distance is smaller than the sum of the 2 radiuses
      if(d <=cylinder1.getRadius()+cylinder2.getRadius())
	   retCode = true;

  return retCode;
  
  
}

OSG_BASE_DLLMAPPING Bool intersect ( const CylinderVolume &cylinder, 
                                     const FrustumVolume &frustum )
{
 int i;
 Pnt3f min, max;
 cylinder.getBounds(min, max);

  Plane frust[] = { frustum.getNear(), frustum.getFar(), frustum.getLeft(), 
                    frustum.getRight(), frustum.getTop(), frustum.getBottom()};

  //check the boundaries of the cylinder with each plane of the frustum

  for (i=0; i<6; i++){
    if(frust[i].getNormal().x()*min.x()+
       frust[i].getNormal().y()*min.y()+
       frust[i].getNormal().z()*min.z()-
       frust[i].getDistanceFromOrigin()>0)
      continue;

    if(frust[i].getNormal().x()*min.x()+
       frust[i].getNormal().y()*min.y()+
       frust[i].getNormal().z()*max.z()-
       frust[i].getDistanceFromOrigin()>0)
      continue;

    if(frust[i].getNormal().x()*min.x()+
       frust[i].getNormal().y()*max.y()+
       frust[i].getNormal().z()*min.z()-
       frust[i].getDistanceFromOrigin()>0)
      continue;

    if(frust[i].getNormal().x()*min.x()+
       frust[i].getNormal().y()*max.y()+
       frust[i].getNormal().z()*max.z()-
       frust[i].getDistanceFromOrigin()>0)
      continue;

    if(frust[i].getNormal().x()*max.x()+
       frust[i].getNormal().y()*min.y()+
       frust[i].getNormal().z()*min.z()-
       frust[i].getDistanceFromOrigin()>0)
      continue;

    if(frust[i].getNormal().x()*max.x()+
       frust[i].getNormal().y()*min.y()+
       frust[i].getNormal().z()*max.z()-
       frust[i].getDistanceFromOrigin()>0)
      continue;

    if(frust[i].getNormal().x()*max.x()+
       frust[i].getNormal().y()*max.y()+
       frust[i].getNormal().z()*min.z()-
       frust[i].getDistanceFromOrigin()>0)
      continue;

    if(frust[i].getNormal().x()*max.x()+
       frust[i].getNormal().y()*max.y()+
       frust[i].getNormal().z()*max.z()-
       frust[i].getDistanceFromOrigin()>0)
      continue;

    return false;
  }
  return true;
}

OSG_BASE_DLLMAPPING Bool intersect ( const CylinderVolume &cylinder, 
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
		retCode = intersect(cylinder,*bv);
	else
		if (sv = dynamic_cast<const SphereVolume*>(v))
			retCode = intersect(cylinder,*sv);
		else
			if (cv = dynamic_cast<const CylinderVolume*>(v))
				retCode = intersect(cylinder,*cv);
			else
				if (fv = dynamic_cast<const FrustumVolume*>(v))
					retCode = intersect(cylinder,*fv);
			
	return retCode;


}


// # Frustum ########################################################

OSG_BASE_DLLMAPPING Bool intersect ( const FrustumVolume &frustum1, 
																		 const FrustumVolume &frustum2)
{
	FFATAL (("intersect (frustum/frustum) is not impl.\n"));
	return false;
}

OSG_BASE_DLLMAPPING Bool intersect ( const FrustumVolume &frustum, 
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
		retCode = intersect(frustum,*bv);
	else
		if (sv = dynamic_cast<const SphereVolume*>(v))
			retCode = intersect(frustum,*sv);
		else
			if (cv = dynamic_cast<const CylinderVolume*>(v))
				retCode = intersect(frustum,*cv);
			else
				if (fv = dynamic_cast<const FrustumVolume*>(v))
					retCode = intersect(frustum,*fv);
			
	return retCode;
}

// ###################################################################
// # Volume Extend Functions #########################################
// ###################################################################

OSG_BASE_DLLMAPPING void extend ( Volume &srcVol, 
                                  const Volume &vol)
{
	FFATAL (("extend (frustum/volume) is not impl.\n"));
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

Pnt3f min, max;
	
  if ( (! srcVol.isValid() && ! srcVol.isEmpty()) || 
       srcVol.isInfinite() || srcVol.isStatic() )
    return;

  if ( ! vol.isValid() )
    return;

  if (srcVol.isEmpty())
    if (vol.isEmpty())
      return;
    else {
       vol.getBounds(min,max);
       srcVol.setBounds(min,max);
      return;
    }
  else
    if (vol.isEmpty())
      return;
vol.getBounds(min, max);

srcVol.setBounds ( osgMin(min.x(),srcVol.getMin().x()),
		   osgMin(min.y(),srcVol.getMin().y()),
		   osgMin(min.z(),srcVol.getMin().z()),
		   osgMax(max.x(),srcVol.getMax().x()),
		   osgMax(max.y(),srcVol.getMax().y()),
		   osgMax(max.z(),srcVol.getMax().z()));

	if (vol.isInfinite())
		srcVol.setInfinite(true);

	return;
}

OSG_BASE_DLLMAPPING void extend ( BoxVolume &srcVol, 
																	const CylinderVolume &vol)
{

Pnt3f min, max;
	
  if ( (! srcVol.isValid() && ! srcVol.isEmpty()) || 
       srcVol.isInfinite() || srcVol.isStatic() )
    return;

  if ( ! vol.isValid() )
    return;

  if (srcVol.isEmpty())
    if (vol.isEmpty())
      return;
    else {
       vol.getBounds(min,max);
       srcVol.setBounds(min,max);
      return;
    }
  else
    if (vol.isEmpty())
      return;
vol.getBounds(min, max);

srcVol.setBounds ( osgMin(min.x(),srcVol.getMin().x()),
		   osgMin(min.y(),srcVol.getMin().y()),
		   osgMin(min.z(),srcVol.getMin().z()),
		   osgMax(max.x(),srcVol.getMax().x()),
		   osgMax(max.y(),srcVol.getMax().y()),
		   osgMax(max.z(),srcVol.getMax().z()));

	if (vol.isInfinite())
		srcVol.setInfinite(true);

	return;
}

OSG_BASE_DLLMAPPING void extend ( BoxVolume &srcVol, 
																	const FrustumVolume &vol)
{
  FFATAL (("extend (box/frustum) is not impl.\n"));
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
  Pnt3f min,max,min1,max1, c;
  float r;
  BoxVolume vol1;

  vol.getBounds(min,max);

	if ( (! srcVol.isValid() && ! srcVol.isEmpty()) || 
			 srcVol.isInfinite() || srcVol.isStatic() )
		return;

	if ( ! vol.isValid() )
		return;
	
	if (srcVol.isEmpty())
		if (vol.isEmpty())
			return;
		else {
		  c=Pnt3f( (min.x()+max.x())*0.5,
               (min.y()+max.y())*0.5,
               (min.z()+max.z())*0.5);
		    r=((max-min).length())/2;
		    
			srcVol.setValue(c,r);
			return;
		}
	else
		if (vol.isEmpty())
			return;

  srcVol.getBounds(min1,max1);
  vol1.setBounds ( osgMin(min.x(),min1.x()),
                   osgMin(min.y(),min1.y()),
                   osgMin(min.z(),min1.z()),
                   osgMax(max.x(),max1.x()),
                   osgMax(max.y(),max1.y()),
                   osgMax(max.z(),max1.z()));
  
  vol1.getBounds(min,max);
  
  c = Pnt3f ( (min.x()+max.x())*0.5,
              (min.y()+max.y())*0.5,
              (min.z()+max.z())*0.5);
  r = ((max-min).length())/2;
  
  srcVol.setValue(c,r);

	return;
}

OSG_BASE_DLLMAPPING void extend ( SphereVolume &srcVol, 
																	const SphereVolume &vol)
{

Pnt3f min, max, min1, max1, min2, max2,c;
float r;
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
	srcVol.getBounds(min,max);
	vol.getBounds(min1,max1);

	min2 = Pnt3f (osgMin(min.x(),min1.x()), 
                osgMin(min.y(),min1.y()), 
                osgMin(min.z(),min1.z()));
 	max2 = Pnt3f (osgMax(max.x(),max1.x()),
                osgMax(max.y(),max1.y()),
                osgMax(max.z(),max1.z()));
				     
	c = Pnt3f    ((min2.x()+max2.x())*0.5,
                (min2.y()+max2.y())*0.5,
                (min2.z()+max2.z())*0.5);
	r=((max2-min2).length())*0.5;
	
	srcVol.setValue(c,r);										 
	
	return;
}


OSG_BASE_DLLMAPPING void extend ( SphereVolume &srcVol, 
																	const CylinderVolume &vol)
{

	Pnt3f min, max, min1, max1,min2, max2, c ;
	float r;
	
  if ( (! srcVol.isValid() && ! srcVol.isEmpty()) || 
       srcVol.isInfinite() || srcVol.isStatic() )
    return;

  if ( ! vol.isValid() )
    return;

  if (srcVol.isEmpty())
    if (vol.isEmpty())
      return;
    else {
       vol.getBounds(min,max);
       vol.getCenter(c);
       r = (min-c).length();
       srcVol.setValue(c,r);
       return;
    }
  else
    if (vol.isEmpty())
      return;

  srcVol.getBounds(min, max);
  vol.getBounds(min1, max1);
  
  min2 = Pnt3f ( osgMin(min.x(),min1.x()),
                 osgMin(min.y(),min1.y()),
                 osgMin(min.z(),min1.z()));

  max2 = Pnt3f ( osgMax(max.x(),max1.x()),
                 osgMax(max.y(),max1.y()),
                 osgMax(max.z(),max1.z()));
  
  c = Pnt3f    ( (min2.x()+max2.x())*0.5,
                 (min2.y()+max2.y())*0.5,
                 (min2.z()+max2.z())*0.5);
  r=((max2-min2).length())*0.5;
  
  srcVol.setValue(c,r);
  
  return;
  

}

OSG_BASE_DLLMAPPING void extend ( SphereVolume &srcVol, 
																	const FrustumVolume &vol)
{
  FFATAL (("extend (sphere/frustum) is not impl.\n"));
	return;

}

OSG_BASE_DLLMAPPING void extend ( SphereVolume &srcVol, 
																	const Volume &vol )
{
	const Volume *v = &vol;
	const SphereVolume *sphere;
	const DynamicVolume *dynamic = dynamic_cast<const DynamicVolume*>(v);

	if (dynamic)
		v = &(dynamic->getInstance());
	
	if ((sphere = dynamic_cast<const SphereVolume*>(v)))
		osg::extend(srcVol,*sphere);
	else {
		SphereVolume localSphere;
		Pnt3f min,max,c;
		float r;
		v->getBounds(min,max);
		c = Pnt3f( (min.x()+max.x())*0.5,
               (min.y()+max.y())*0.5,
               (min.z()+max.z())*0.5);
		r = ((max-min).length())*0.5;
		localSphere.setValue(c,r);
		osg::extend(srcVol,localSphere);
	}

	return;
}

// # Cylinder ########################################################

OSG_BASE_DLLMAPPING void extend ( CylinderVolume &srcVol, 
																	const BoxVolume &vol)
{
  Pnt3f min,max,min1,max1,min2,max2,apos;
  Vec2f p;
  Vec3f adir;
  float r;
	
  if ( (! srcVol.isValid() && ! srcVol.isEmpty()) || 
       srcVol.isInfinite() || srcVol.isStatic() )
    return;

  if ( ! vol.isValid() )
    return;

  if (srcVol.isEmpty())
    if (vol.isEmpty())
      return;
    else {
       vol.getBounds(min,max);
       p = Vec2f(max.x()-min.x(),max.y()-min.y());
       r = (p.length())*0.5;
       
       adir = Vec3f(0,0,max.z()-min.z());
       apos = Pnt3f(p.x(),p.y(),min.z());

       srcVol.setValue(apos,adir,r);
       return;
    }
  else
    if (vol.isEmpty())
      return;

  srcVol.getBounds(min,max);
  vol.getBounds(min1,max1);

  min2 = Pnt3f ( osgMin(min.x(),min1.x()),
                 osgMin(min.y(),min1.y()),
                 osgMin(min.z(),min1.z()));
  max2 = Pnt3f ( osgMax(max.x(),max1.x()),
                 osgMax(max.y(),max1.y()),
                 osgMax(max.z(),max1.z()));
 
  p = Vec2f(max2.x()-min2.x(),max2.y()-min2.y());
  r = (p.length())*0.5;
  
  adir = Vec3f(0,0,max2.z()-min2.z());
  apos = Pnt3f(p.x(),p.y(),min2.z());
  
  srcVol.setValue(apos,adir,r);
  return;
  
}

OSG_BASE_DLLMAPPING void extend ( CylinderVolume &srcVol, 
																	const SphereVolume &vol)
{
 Pnt3f min,max,min1,max1,min2,max2,apos;
  Vec2f p;
  Vec3f adir;
  float r;
	
  if ( (! srcVol.isValid() && ! srcVol.isEmpty()) || 
       srcVol.isInfinite() || srcVol.isStatic() )
    return;

  if ( ! vol.isValid() )
    return;

  if (srcVol.isEmpty())
    if (vol.isEmpty())
      return;
    else {
      r = vol.getRadius();
      apos = Pnt3f ( vol.getCenter().x()-r, 
                     vol.getCenter().y()-r, 
                     vol.getCenter().z()-r);
      adir = Vec3f ( vol.getCenter().x()+r-apos.x(), 
                     vol.getCenter().y()+r-apos.y(), 
                     vol.getCenter().z()+r-apos.z());
      
       srcVol.setValue(apos,adir,r);
       return;
    }
  else
    if (vol.isEmpty())
      return;

  srcVol.getBounds(min,max);
  vol.getBounds(min1,max1);

  min2 = Pnt3f ( osgMin(min.x(),min1.x()),
                 osgMin(min.y(),min1.y()),
                 osgMin(min.z(),min1.z()));
  max2 = Pnt3f ( osgMax(max.x(),max1.x()),
                 osgMax(max.y(),max1.y()),
                 osgMax(max.z(),max1.z()));
 
  p = Vec2f(max2.x()-min2.x(),max2.y()-min2.y());
  r = (p.length())*0.5;
  
  adir = Vec3f(0,0,max2.z()-min2.z());
  apos = Pnt3f(p.x(),p.y(),min2.z());
  
  srcVol.setValue(apos,adir,r);
  return;

}

OSG_BASE_DLLMAPPING void extend ( CylinderVolume &srcVol, 
																	const CylinderVolume &vol)
{

  Pnt3f min,max,min1,max1,min2,max2,apos;
  Vec2f p;
  Vec3f adir;
  float r;

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

	srcVol.getBounds(min,max);
	vol.getBounds(min1,max1);
	
	min2 = Pnt3f ( osgMin(min.x(),min1.x()),
                 osgMin(min.y(),min1.y()),
                 osgMin(min.z(),min1.z()));
	max2 = Pnt3f ( osgMax(max.x(),max1.x()),
                 osgMax(max.y(),max1.y()),
                 osgMax(max.z(),max1.z()));
 
	p = Vec2f(max2.x()-min2.x(),max2.y()-min2.y());
	r = (p.length())*0.5;
  
	adir = Vec3f(0,0,max2.z()-min2.z());
	apos = Pnt3f(p.x(),p.y(),min2.z());
  
	srcVol.setValue(apos,adir,r);
	return;
}

OSG_BASE_DLLMAPPING void extend ( CylinderVolume &srcVol, 
																	const FrustumVolume &vol)
{
  FFATAL (("extend (cylinder/frustum) is not impl.\n"));
	return;

}

OSG_BASE_DLLMAPPING void extend ( CylinderVolume &srcVol, 
																	const Volume &vol)
{
	const Volume *v = &vol;
	const CylinderVolume *cylinder;
	const DynamicVolume *dynamic = dynamic_cast<const DynamicVolume*>(v);

	if (dynamic)
		v = &(dynamic->getInstance());
	
	if ((cylinder = dynamic_cast<const CylinderVolume*>(v)))
	  osg::extend(srcVol,*cylinder);
	else {
		CylinderVolume localCylinder;
		Pnt3f min,max,apos;
		Vec3f adir;
		float r;
		Vec2f p;

		v->getBounds(min,max);
		p = Vec2f(max.x()-min.x(),max.y()-min.y());
		r = (p.length())*0.5;
		adir = Vec3f(0,0,max.z()-min.z());
		apos = Pnt3f(p.x(),p.y(),min.z());
		localCylinder.setValue(apos,adir,r);
		osg::extend(srcVol,localCylinder);
	}
	return;
}

// # Frustum ########################################################

OSG_BASE_DLLMAPPING void extend ( FrustumVolume &srcVol, 
																	const BoxVolume &vol)
{

  FFATAL (("extend (frustum/box) is not impl.\n"));
  return;

}

OSG_BASE_DLLMAPPING void extend ( FrustumVolume &srcVol, 
																	const SphereVolume &vol)
{
  FFATAL (("extend (frustum/sphere) is not impl.\n"));
  return;

}

OSG_BASE_DLLMAPPING void extend ( FrustumVolume &srcVol, 
																	const CylinderVolume &vol)
{
  FFATAL (("extend (frustum/cylinder) is not impl.\n"));
  return;


}

OSG_BASE_DLLMAPPING void extend ( FrustumVolume &srcVol, 
																	const FrustumVolume &vol)
{

  FFATAL (("extend (frustum/frustum) is not impl.\n"));
  return;

}

OSG_BASE_DLLMAPPING void extend ( FrustumVolume &srcVol, 
																	const Volume &vol)
{
  FFATAL (("extend (frustum/volume) is not impl.\n"));
  return;

}

OSG_END_NAMESPACE
