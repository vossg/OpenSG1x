
#include <OSGConfig.h>

#include <iostream>

#include "OSGFieldFactory.h"
#include "OSGSFVecTypes.h"
#include "OSGSFSysTypes.h"
#include "OSGBaseFunctions.h"
#include "OSGSFBaseTypes.h"
#include "OSGMFBaseTypes.h"
#include "OSGSFMathTypes.h"
#include "OSGMFMathTypes.h"
#include "OSGMFSysTypes.h"
//#include "OSGMFReal32MF.h"

OSG_USING_NAMESPACE

int main (int argc, char **argv)
{
    osgInit(argc, argv);

//    vector<Real32> foo;

//    MFMFReal32 vvR;
//    MFReal32   vR;

//    MFReal32   vR1;

//    vR.push_back(1.f);
//    vR.push_back(2.f);

//    vvR.push_back(vR);

//    vR1 = vR;

//    MFReal32 vR2(vR1);

//    foo.push_back(1.f);
//    foo.push_back(2.f);

//    vector<Real32> bar(foo);

//    fprintf(stderr, "%f %f %f %f\n", vR[0], vR1[0], vR2[0], bar[0]);

    Field *fieldP;
    SFVec3f vec3f, *vec3fP;

    SFQuaternion sfquad;
    MFQuaternion mfquad;

    if (mfquad.empty() == false)
        std::cerr << "new mfquad field is not empty" << std::endl;

    SFInt32  *int32P;
    SFUInt32 *uint32P;

//    MFTime *timem;
//    SFTime *times;

    fieldP = FieldFactory::the().createField("SFVec3f");
//  vec3fP = dynamic_cast<OSGSFVec3f*>(fieldP);
    vec3fP = (SFVec3f*)(fieldP);

    vec3fP->getValue().setValues(1,2,3);

//  std::cout << "Vec3f: " << *vec3fP << std::endl;

    fieldP = FieldFactory::the().createField("SFUInt32");
   
//  uint32P = dynamic_cast<SFUInt32 *>(fieldP);

    uint32P = (SFUInt32 *)(fieldP);
  
    if(uint32P != NULL)
    {
        std::cout << "UInt32 : " << (*uint32P).getType().getCName() << std::endl;
    }

    fieldP = FieldFactory::the().createField("SFInt32");
   
//  int32P = dynamic_cast<SFInt32 *>(fieldP);

    int32P = (SFInt32 *)(fieldP);

    if(int32P != NULL)
    {
        std::cout << "Int32 : " << (*int32P).getType().getCName() << std::endl;
    }

    std::cout << std::endl << "Some sizes:" << std::endl;

    std::cout << "sizeof(SFInt32): " << sizeof( *int32P ) << std::endl;

    std::cout << "sizeof(SFVec3f): " << sizeof( vec3f ) << std::endl;

    SFBitVector *pSB = 
        (SFBitVector *) FieldFactory::the().createField("SFBitVector");

    MFBitVector *pMB = 
        (MFBitVector *) FieldFactory::the().createField("MFBitVector");

    SFTime      *pST = 
        (SFTime *) FieldFactory::the().createField("SFTime");

    MFTime      *pMT = 
        (MFTime *) FieldFactory::the().createField("MFTime");

    fprintf(stderr, "Got Field %p %p %p %p\n", pSB, pMB, pST, pMT);

    MFBool testBField;
    
    testBField.resize(10);

    testBField[0] = true;
    testBField[1] = false;

#ifndef OSG_DISABLE_DEPRECATED
    testBField.getValue(0);
    testBField.setValue(true, 0);

    testBField.addValue(true);
    testBField.getSize();
#endif

    return 0;   
}
