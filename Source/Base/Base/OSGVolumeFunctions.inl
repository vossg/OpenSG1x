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
//   Inl :   Inline implementation
//
//           |Box     |Sphere  |Cylinder|Frustum |Volume
//   --------+--------+--------+--------+--------+------
//   Box     |Func    |Func    |Func    |Func    |Func
//   Sphere  |Inl     |Func    |Func    |Func    |Func
//   Cylinder|Inl     |Inl     |Func    |Func    |Func
//   Frustum |Inl     |Inl     |Inl     |Func    |Func
//   Volume  |Inl     |Inl     |Inl     |Inl     |Func

// # Box ##############################################################

// all implementation in cpp file


// # Sphere ###########################################################

inline 
bool intersect(const SphereVolume &sphere, const BoxVolume &box)
{
    return intersect(box, sphere);
}


// # Cylinder ########################################################

inline
bool intersect(const CylinderVolume &cylinder, const BoxVolume &box)
{
    return intersect(box, cylinder);
}

inline
bool intersect(const CylinderVolume &cylinder, const SphereVolume &sphere)
{
    return intersect(sphere, cylinder);
}


// # Frustum ########################################################


inline
bool intersect(const FrustumVolume &frustum, const BoxVolume      &box)
{
    return intersect(box, frustum);
}

inline
bool intersect(const FrustumVolume &frustum, const SphereVolume   &sphere)
{
    return intersect(sphere,frustum);
}

inline 
bool intersect(const FrustumVolume &frustum, const CylinderVolume &cylinder)
{
    return intersect(cylinder,frustum);
}


// # Volume ########################################################

inline 
bool intersect(const Volume &srcVol, const BoxVolume      &vol)
{
    return intersect(vol,srcVol);
}

inline 
bool intersect(const Volume &srcVol, const SphereVolume   &vol)
{
    return intersect(vol,srcVol);
}

inline 
bool intersect(const Volume &srcVol, const CylinderVolume &vol)
{
    return intersect(vol,srcVol);
}

inline 
bool intersect(const Volume &srcVol, const FrustumVolume  &vol)
{
    return intersect(vol,srcVol);
}

OSG_END_NAMESPACE

