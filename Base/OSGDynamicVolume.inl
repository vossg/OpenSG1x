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

#ifndef _OSGDYNAMICVOLUME_INL_
#define _OSGDYNAMICVOLUME_INL_

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>

#include "OSGVector.h"
#include "OSGMatrix.h"
#include "OSGLine.h"

OSG_BEGIN_NAMESPACE


/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/



/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*------------------------- get values -------------------------------*/

/** gives the center of the volume */
inline 
void DynamicVolume::getCenter (Pnt3f &center) const
{
	getInstance().getCenter(center);
}

/** gives the scalar volume of the volume */
inline 
float DynamicVolume::getScalarVolume (void) const
{
	return getInstance().getScalarVolume();
}
	
/** gives the boundaries of the volume */
inline
void DynamicVolume::getBounds( Pnt3f &min, Pnt3f &max ) const
{
	getInstance().getBounds(min,max);
}


/*-------------------------- extending ------------------------------------*/

/** extends (if necessary) to contain the given 3D point */
inline 
void DynamicVolume::extendBy (const Pnt3f &pt)
{
	getInstance().extendBy(pt);
}

/** extend the volume by the given volume */
inline
void DynamicVolume::extendBy (const Volume &volume)
{
	getInstance().extendBy(volume);
}

/*-------------------------- intersection ---------------------------------*/

/** Returns true if intersection of given point and Volume is not empty */
inline 
Bool DynamicVolume::intersect (const Pnt3f &point) const
{
	return getInstance().intersect(point);
}

/** intersect the volume with the given Line */
inline 
Bool DynamicVolume::intersect (const Line &line ) const
{
	return getInstance().intersect(line);
}

/** intersect the volume with the given Line */
inline 
Bool DynamicVolume::intersect ( const Line &line, 
												Real32 &enter, Real32 &exit  ) const
{
	return getInstance().intersect(line,enter,exit);
}

/** intersect the volume with another volume */
inline 
Bool DynamicVolume::intersect (const Volume &volume) const
{
	return getInstance().intersect(volume);
}

/** check if the point is on the volume's surface */
inline 
Bool DynamicVolume::isOnSurface (const Pnt3f &point) const
{
	return getInstance().isOnSurface(point);
}

/*-------------------------- transformation -------------------------------*/

/** transform the volume bye the given matrix*/
inline 
void DynamicVolume::transform (const Matrix &matrix)
{
	getInstance().transform(matrix);
}


OSG_END_NAMESPACE

#endif // DYNAMICVOLUME_CLASS_DECLARATION
