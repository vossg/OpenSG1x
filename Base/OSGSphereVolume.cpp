
// System declarations

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <assert.h>

// Application declarations
#include "OSGLine.h"
#include "OSGBoxVolume.h"

// Class declarations
#include "OSGSphereVolume.h"

OSG_USING_NAMESPACE

// Static Class Variable implementations: 


/*
//----------------------------------------------------------------------
// Method: circumscribe
// Author: steschne
// Date:   Mon Dec 22 17:38:03 1997
// Description:
//         Return a sphere containing a given box
//----------------------------------------------------------------------
void OSGSphereVolume::circumscribe(const OSGBoxVolume &box)
{
	float radius = 0.5 * (box.getMax() - box.getMin()).length();
	OSGVec3f center;

	box.getCenter(center);

	setValue(center, radius);
}
*/


//----------------------------------------------------------------------
// Method: initEnclose
// Author: pdaehne
// Date:   Mon Dec 5 14:20:20 1999
// Description:
//----------------------------------------------------------------------
void OSGSphereVolume::initEnclose (const OSGVolume &volume)
{
	assert(false);
}

//----------------------------------------------------------------------
// Method: initInside
// Author: pdaehne
// Date:   Mon Dec 5 14:20:20 1999
// Description:
//----------------------------------------------------------------------
void OSGSphereVolume::initInside (const OSGVolume &volume)
{
	assert(false);
}

//----------------------------------------------------------------------
// Method: getVolume
// Author: steschne
// Date:   Mon Dec 22 17:38:03 1997
// Description:
//----------------------------------------------------------------------
float OSGSphereVolume::getVolume (void) const
{
	return 0;
}

//----------------------------------------------------------------------
// Method: extendBy
// Author: steschne
// Date:   Mon Dec 22 17:38:03 1997
// Description:
//----------------------------------------------------------------------
void OSGSphereVolume::extendBy (const OSGPnt3f &pt)
{
	return;
}

//----------------------------------------------------------------------
// Method: extendBy
// Author: steschne
// Date:   Mon Dec 22 17:38:03 1997
// Description:
//----------------------------------------------------------------------
void OSGSphereVolume::extendBy (const OSGVolume &volume)
{
	return;
}

//----------------------------------------------------------------------
// Method: extendBy
// Author: steschne
// Date:   Mon Dec 22 17:38:03 1997
// Description:
//----------------------------------------------------------------------
void OSGSphereVolume::extendBy (const OSGSphereVolume &volume)
{
	return;
}

//----------------------------------------------------------------------
// Method: intersect
// Author: steschne
// Date:   Mon Dec 22 17:38:03 1997
// Description:
//----------------------------------------------------------------------
OSGBool OSGSphereVolume::intersect (const OSGVec3f &point) const
{
	// TODO; not impl.
	assert(false);
	return false;
}

//----------------------------------------------------------------------
// Method: intersect
// Author: steschne
// Date:   Mon Dec 22 17:38:03 1997
// Description:
//          Intersect line and sphere, 
//          returning true if there is an intersection
//----------------------------------------------------------------------
OSGBool OSGSphereVolume::intersect( const OSGLine &line ) const
{
	// TODO; not impl.
	assert(false);
	return false;
}

//----------------------------------------------------------------------
// Method: intersect
// Author: steschne
// Date:   Mon Dec 22 17:38:03 1997
// Description:
//          Intersect line and sphere, 
//          returning true if there is an intersection
//----------------------------------------------------------------------
OSGBool OSGSphereVolume::intersect( const OSGLine &line, 
																	  OSGVec3f &min, 
																	  OSGVec3f &max ) const
{
	// TODO; not impl.
	assert(false);
	return false;
}

//----------------------------------------------------------------------
// Method: intersect
// Author: steschne
// Date:   Mon Dec 22 17:38:03 1997
// Description:
//----------------------------------------------------------------------
OSGBool OSGSphereVolume::intersect (const OSGVolume &volume) const
{
	// TODO; not impl.
	assert(false);
	return false;
}

//----------------------------------------------------------------------
// Method: intersect
// Author: steschne
// Date:   Mon Dec 22 17:38:03 1997
// Description:
//----------------------------------------------------------------------
OSGBool OSGSphereVolume::intersect(const OSGSphereVolume &sphere) const
{
	float distance = getRadius() + sphere.getRadius();
	float currentDistance = 0; // (sphere.getCenter() - getCenter()).length();

	if (currentDistance < distance)
		return true;
	else
		return false;
}

//----------------------------------------------------------------------
// Method: transform
// Author: steschne
// Date:   Mon Dec 22 17:38:03 1997
// Description:
//----------------------------------------------------------------------
void OSGSphereVolume::transform (const OSGMatrix &mat)
{
	// TODO; not impl.
	assert(false);
}
