
// System declarations

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif


#include <assert.h>


// Application declarations

#include <OSGVolume.h>

// Class declarations
#include "OSGCylinderVolume.h"

OSG_USING_NAMESPACE

// Static Class Variable implementations: 

//----------------------------------------------------------------------
// Method: getCenter
// Author: pdaehne
// Date:   Mon Dec 5 14:20:20 1999
// Description:
//         Change the axis and radius
//----------------------------------------------------------------------
void OSGCylinderVolume::getCenter(OSGVec3f &center) const 
{ 
	assert(false);
}

//----------------------------------------------------------------------
// Method: getVolume
// Author: pdaehne
// Date:   Mon Dec 5 14:20:20 1999
// Description:
//         Change the axis and radius
//----------------------------------------------------------------------
float OSGCylinderVolume::getVolume(void) const
{ 
	assert(false);
    return 0.;
}

//----------------------------------------------------------------------
// Method: initEnclose
// Author: pdaehne
// Date:   Mon Dec 5 14:20:20 1999
// Description:
//----------------------------------------------------------------------
void OSGCylinderVolume::initEnclose (const OSGVolume &volume)
{
	assert(false);
}

//----------------------------------------------------------------------
// Method: initInside
// Author: pdaehne
// Date:   Mon Dec 5 14:20:20 1999
// Description:
//----------------------------------------------------------------------
void OSGCylinderVolume::initInside (const OSGVolume &volume)
{
	assert(false);
}

//----------------------------------------------------------------------
// Method: intersect
// Author: pdaehne
// Date:   Mon Dec 5 14:20:20 1999
// Description:
//         TODOC
//----------------------------------------------------------------------
OSGBool OSGCylinderVolume::intersect (const OSGVec3f &point) const
{
	assert(false);
	return false;
}


//----------------------------------------------------------------------
// Method: intersect
// Author: pdaehne
// Date:   Mon Dec 5 14:20:20 1999
// Description:
//         TODOC
//----------------------------------------------------------------------
OSGBool OSGCylinderVolume::intersect ( const OSGLine &line ) const
{
  // TODO
  assert(false);
  return false;
}

//----------------------------------------------------------------------
// Method: intersect
// Author: pdaehne
// Date:   Mon Dec 5 14:20:20 1999
// Description:
//         TODOC
//----------------------------------------------------------------------
OSGBool OSGCylinderVolume::intersect ( const OSGLine &line,
																			 OSGVec3f &min, OSGVec3f &max ) const
{
  // TODO
  assert(false);
  return false;
}

//----------------------------------------------------------------------
// Method: intersect
// Author: pdaehne
// Date:   Mon Dec 5 14:20:20 1999
// Description:
//         TODOC
//----------------------------------------------------------------------
OSGBool OSGCylinderVolume::intersect (const OSGVolume &volume) const
{
	// TODO; not impl.
	assert(false);
	return false;
}

//----------------------------------------------------------------------
// Method: intersect
// Author: pdaehne
// Date:   Mon Dec 5 14:20:20 1999
// Description:
//         TODOC
//----------------------------------------------------------------------
OSGBool OSGCylinderVolume::intersect (const OSGCylinderVolume &volume) const
{
	// TODO; not impl.
	assert(false);
	return false;
}


//----------------------------------------------------------------------
// Method: extendBy
// Author: pdaehne
// Date:   Mon Dec 5 14:20:20 1999
// Description:
//         TODOC
//----------------------------------------------------------------------
void OSGCylinderVolume::extendBy (const OSGPnt3f &pt)
{
}

//----------------------------------------------------------------------
// Method: extendBy
// Author: pdaehne
// Date:   Mon Dec 5 14:20:20 1999
// Description:
//         TODOC
//----------------------------------------------------------------------
void OSGCylinderVolume::extendBy (const OSGVolume &volume)
{
}


//----------------------------------------------------------------------
// Method: transform
// Author: pdaehne
// Date:   Mon Dec 5 14:20:20 1999
// Description:
//         TODOC
//----------------------------------------------------------------------
void OSGCylinderVolume::transform (const OSGMatrix &mat)
{
	;
}
