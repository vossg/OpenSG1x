
// System declarations

#include "OSGConfig.h"

#include "new.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif


// Application declarations


// Class declarations
#include "OSGDynamicVolume.h"
#include "OSGBoxVolume.h"
#include "OSGSphereVolume.h"
#include "OSGCylinderVolume.h"

OSG_USING_NAMESPACE

// Static Class Varible implementations: 

OSGDynamicVolume::OSGDynamicVolume ( Type type) 
{
	setVolumeType(type);
}

OSGDynamicVolume::OSGDynamicVolume(const OSGDynamicVolume &obj) :
    _type(obj._type)
{
	switch ( _type ) 
	{
        case BOX_VOLUME:
            new (_volumeMem) 
               OSGBoxVolume(*((OSG::OSGBoxVolume*)(obj._volumeMem)));
		break;
        
        case SPHERE_VOLUME:
            new (_volumeMem) 
               OSGSphereVolume(*((OSG::OSGSphereVolume*)(obj._volumeMem)));
		break;

        case CYLINDER_VOLUME:
            new (_volumeMem)
               OSGCylinderVolume(*((OSG::OSGCylinderVolume*)(obj._volumeMem)));
		break;
	}	
}

void OSGDynamicVolume::setVolumeType ( Type type )
{
	_type = type;

	switch (type) {
	case BOX_VOLUME:
		new (_volumeMem) OSGBoxVolume;
		break;
	case SPHERE_VOLUME:
		new (_volumeMem) OSGSphereVolume;
		break;
	case CYLINDER_VOLUME:
		new (_volumeMem) OSGCylinderVolume;
		break;
	}
}

void OSGDynamicVolume::morphToType ( Type type )
{
	// TODO optimize;

	switch (getType()) {
	case BOX_VOLUME:
		new (_volumeMem) OSGBoxVolume;
		break;
	case SPHERE_VOLUME:
		new (_volumeMem) OSGSphereVolume;
		break;
	case CYLINDER_VOLUME:
		new (_volumeMem) OSGCylinderVolume;
		break;
	}
}
		
ostream &OSG::operator <<(ostream &outStream,
                          const OSGDynamicVolume &vol)
{
    return outStream << "DynVol << NI ";
}

OSGDynamicVolume & OSGDynamicVolume::operator = (const OSGDynamicVolume &source)
{
	_type = source._type;

	switch ( _type ) 
	{
	case BOX_VOLUME:
		new (_volumeMem) OSGBoxVolume( *((OSG::OSGBoxVolume*)(source._volumeMem)) );
		break;
	case SPHERE_VOLUME:
		new (_volumeMem) OSGSphereVolume( *((OSG::OSGSphereVolume*)(source._volumeMem)) );
		break;
	case CYLINDER_VOLUME:
		new (_volumeMem) OSGCylinderVolume( *((OSG::OSGCylinderVolume*)(source._volumeMem)) );
		break;
	}	
	
	return *this;
}
