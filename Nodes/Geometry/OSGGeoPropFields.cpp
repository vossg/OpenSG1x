
#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#define OSG_COMPILEGEOMETRY
#define OSG_COMPILEGEOPROPFIELDINST

#include <OSGGeoPropFields.h>

OSG_BEGIN_NAMESPACE

#if defined(__sgi)

#pragma instantiate SField             <GeoPositionPtr           >::_fieldType
#pragma instantiate SField             <GeoNormalPtr             >::_fieldType
#pragma instantiate SField             <GeoColorPtr              >::_fieldType
#pragma instantiate SField             <GeoTexCoordsPtr          >::_fieldType
#pragma instantiate SField             <GeoIndexPtr              >::_fieldType
#pragma instantiate SField             <GeoPTypePtr              >::_fieldType
#pragma instantiate SField             <GeoPLengthPtr            >::_fieldType

#else

OSG_DLLEXPORT_DEF1(SField, GeoPositionPtr , OSG_GEOMETRY_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, GeoNormalPtr   , OSG_GEOMETRY_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, GeoColorPtr    , OSG_GEOMETRY_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, GeoTexCoordsPtr, OSG_GEOMETRY_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, GeoIndexPtr    , OSG_GEOMETRY_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, GeoPTypePtr    , OSG_GEOMETRY_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, GeoPLengthPtr  , OSG_GEOMETRY_DLLTMPLMAPPING)

#endif

OSG_END_NAMESPACE
