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


OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                     Volume intersection Functions                        *
\***************************************************************************/

// Intersect implementation maxtrix: 
//   Func:   Function implementation
//   Temp:   Template implementation
//
//           |Box     |Sphere  |Cylinder|Frustum |Volume
//   --------+--------+--------+--------+--------+------
//   Box     |Func    |Func    |Func    |Func    |Func
//   Sphere  |Temp    |Func    |Func    |Func    |Func
//   Cylinder|Temp    |Temp    |Func    |Func    |Func
//   Frustum |Temp    |Temp    |Temp    |Func    |Func
//   Volume  |Temp    |Temp    |Temp    |Temp    |Func

// # Box ##############################################################

// all implementation in cpp file


// # Sphere ###########################################################
inline
OSG_BASE_DLLMAPPING Bool intersect ( const SphereVolume &sphere, 
		                  							 const BoxVolume &box )	
{
	return intersect(box,sphere);
}

// # Cylinder ########################################################

inline
OSG_BASE_DLLMAPPING Bool intersect ( const CylinderVolume &cylinder, 
																		 const BoxVolume &box)
{
	return intersect(box,cylinder);
}

inline
OSG_BASE_DLLMAPPING Bool intersect ( const CylinderVolume &cylinder, 
																		 const SphereVolume &sphere)
{
	return intersect(sphere,cylinder);
}

// # Frustum ########################################################

inline
OSG_BASE_DLLMAPPING Bool intersect ( const FrustumVolume &frustum, 
																		 const BoxVolume &box)
{
	return intersect(box,frustum);
}

inline
OSG_BASE_DLLMAPPING Bool intersect ( const FrustumVolume &frustum,
																		 const SphereVolume &sphere)
{
	return intersect(sphere,frustum);
}

inline
OSG_BASE_DLLMAPPING Bool intersect ( const FrustumVolume &frustum, 
																		 const CylinderVolume &cylinder)
{
	return intersect(cylinder,frustum);
}

OSG_END_NAMESPACE

