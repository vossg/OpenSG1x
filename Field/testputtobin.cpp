
#include <stdio.h>
#include <OSGVecFieldDataType.h>
#include <OSGSysFieldDataType.h>
#include <OSGMathFieldDataType.h>
#include <OSGBaseFieldDataType.h>

void main(void)
{
    fprintf(stderr, "TestStart\n");

    OSG::FieldDataTraits<OSG::Vec2f >::copyToBin(NULL, NULL);
    OSG::FieldDataTraits<OSG::Vec3f >::copyToBin(NULL, NULL);
    OSG::FieldDataTraits<OSG::Vec4f >::copyToBin(NULL, NULL);
    OSG::FieldDataTraits<OSG::Vec4ub>::copyToBin(NULL, NULL);

    OSG::FieldDataTraits<OSG::Vec2f >::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits<OSG::Vec3f >::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits<OSG::Vec4f >::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits<OSG::Vec4ub>::copyToBin(NULL, NULL, 0);

    OSG::FieldDataTraits<OSG::Pnt2f>::copyToBin(NULL, NULL);
    OSG::FieldDataTraits<OSG::Pnt3f>::copyToBin(NULL, NULL);
    OSG::FieldDataTraits<OSG::Pnt4f>::copyToBin(NULL, NULL);

    OSG::FieldDataTraits<OSG::Pnt2f>::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits<OSG::Pnt3f>::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits<OSG::Pnt4f>::copyToBin(NULL, NULL, 0);



    OSG::FieldDataTraits2<OSG::Bool>::copyToBin(NULL, NULL);

    OSG::FieldDataTraits<OSG:: Int8>::copyToBin(NULL, NULL);
    OSG::FieldDataTraits<OSG::UInt8>::copyToBin(NULL, NULL);

    OSG::FieldDataTraits<OSG:: Int16>::copyToBin(NULL, NULL);
    OSG::FieldDataTraits<OSG::UInt16>::copyToBin(NULL, NULL);

    OSG::FieldDataTraits<OSG:: Int32>::copyToBin(NULL, NULL);
    OSG::FieldDataTraits<OSG::UInt32>::copyToBin(NULL, NULL);

    OSG::FieldDataTraits<OSG:: Int64>::copyToBin(NULL, NULL);
    OSG::FieldDataTraits<OSG::UInt64>::copyToBin(NULL, NULL);

    OSG::FieldDataTraits<OSG::Real32>::copyToBin(NULL, NULL);
    OSG::FieldDataTraits<OSG::Real64>::copyToBin(NULL, NULL);


    OSG::FieldDataTraits2<OSG::Bool>::copyToBin(NULL, NULL, 0);

    OSG::FieldDataTraits<OSG:: Int8>::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits<OSG::UInt8>::copyToBin(NULL, NULL, 0);

    OSG::FieldDataTraits<OSG:: Int16>::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits<OSG::UInt16>::copyToBin(NULL, NULL, 0);

    OSG::FieldDataTraits<OSG:: Int32>::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits<OSG::UInt32>::copyToBin(NULL, NULL, 0);

    OSG::FieldDataTraits<OSG:: Int64>::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits<OSG::UInt64>::copyToBin(NULL, NULL, 0);

    OSG::FieldDataTraits<OSG::Real32>::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits<OSG::Real64>::copyToBin(NULL, NULL, 0);


    OSG::FieldDataTraits<OSG::Matrix    >::copyToBin(NULL, NULL);
    OSG::FieldDataTraits<OSG::Quaternion>::copyToBin(NULL, NULL);


    OSG::FieldDataTraits<OSG::Matrix    >::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits<OSG::Quaternion>::copyToBin(NULL, NULL, 0);


    OSG::FieldDataTraits <OSG::String       >::copyToBin(NULL, NULL);
    OSG::FieldDataTraits1<OSG::Time         >::copyToBin(NULL, NULL);
    OSG::FieldDataTraits <OSG::Color3f      >::copyToBin(NULL, NULL);
    OSG::FieldDataTraits <OSG::Color4f      >::copyToBin(NULL, NULL);
    OSG::FieldDataTraits <OSG::Color3ub     >::copyToBin(NULL, NULL);
    OSG::FieldDataTraits <OSG::Color4ub     >::copyToBin(NULL, NULL);
    OSG::FieldDataTraits <OSG::DynamicVolume>::copyToBin(NULL, NULL);
    OSG::FieldDataTraits1<OSG::BitVector    >::copyToBin(NULL, NULL);


    OSG::FieldDataTraits <OSG::String       >::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits1<OSG::Time         >::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits <OSG::Color3f      >::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits <OSG::Color4f      >::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits <OSG::Color3ub     >::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits <OSG::Color4ub     >::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits <OSG::DynamicVolume>::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits1<OSG::BitVector    >::copyToBin(NULL, NULL, 0);
}
