
#include <OSGConfig.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include "OSGFieldFactory.h"
#include "OSGSFVecTypes.h"
#include "OSGSFSysTypes.h"
#include "OSGBaseFunctions.h"

using OSG::OSGField;
using OSG::OSGSFVec3f;
using OSG::OSGFieldFactory;
using OSG::OSGSFUInt32;
using OSG::OSGSFInt32;
using OSG::osgInit;

int main (int argc, char **argv)
{
	OSGField *fieldP;
	OSGSFVec3f vec3f, *vec3fP;

	OSGSFInt32  *int32P;
	OSGSFUInt32 *uint32P;

    osgInit(argc, argv);

	fieldP = OSGFieldFactory::the().createField("SFVec3f");
//	vec3fP = dynamic_cast<OSGSFVec3f*>(fieldP);
    vec3fP = (OSGSFVec3f*)(fieldP);

	vec3fP->getValue().setValues(1,2,3);

//	cout << "Vec3f: " << *vec3fP << endl;

 	fieldP = OSGFieldFactory::the().createField("SFUInt32");
   
//	uint32P = dynamic_cast<OSGSFUInt32 *>(fieldP);

    uint32P = (OSGSFUInt32 *)(fieldP);
  
    if(uint32P != NULL)
    {
        cout << "UInt32 : " << (*uint32P).getClassname() << endl;
    }

 	fieldP = OSGFieldFactory::the().createField("SFInt32");
   
//	int32P = dynamic_cast<OSGSFInt32 *>(fieldP);

    int32P = (OSGSFInt32 *)(fieldP);

    if(int32P != NULL)
    {
        cout << "Int32 : " << (*int32P).getClassname() << endl;
    }

	cout << endl << "Some sizes:" << endl;

	cout << "sizeof(OSGSFInt32): " << sizeof( *int32P ) << endl;

	cout << "sizeof(OSGSFVec3f): " << sizeof( vec3f ) << endl;

 	return 0;	
}
