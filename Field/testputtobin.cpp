
#include <stdio.h>
#include <OSGVecFieldDataType.h>
#include <OSGSysFieldDataType.h>
#include <OSGMathFieldDataType.h>
#include <OSGBaseFieldDataType.h>

void main(void)
{
    fprintf(stderr, "TestStart\n");

    OSG::Vec2f  v2;
    OSG::Vec3f  v3;
    OSG::Vec4f  v4;
    OSG::Vec4ub v4ub;

    OSG::Pnt2f p2;
    OSG::Pnt3f p3;
    OSG::Pnt4f p4;

    OSG::FieldDataTraits<OSG::Vec2f >::copyToBin(NULL, v2);
    OSG::FieldDataTraits<OSG::Vec3f >::copyToBin(NULL, v3);
    OSG::FieldDataTraits<OSG::Vec4f >::copyToBin(NULL, v4);
    OSG::FieldDataTraits<OSG::Vec4ub>::copyToBin(NULL, v4ub);

    OSG::FieldDataTraits<OSG::Vec2f >::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits<OSG::Vec3f >::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits<OSG::Vec4f >::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits<OSG::Vec4ub>::copyToBin(NULL, NULL, 0);

    OSG::FieldDataTraits<OSG::Pnt2f>::copyToBin(NULL, p2);
    OSG::FieldDataTraits<OSG::Pnt3f>::copyToBin(NULL, p3);
    OSG::FieldDataTraits<OSG::Pnt4f>::copyToBin(NULL, p4);

    OSG::FieldDataTraits<OSG::Pnt2f>::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits<OSG::Pnt3f>::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits<OSG::Pnt4f>::copyToBin(NULL, NULL, 0);


    OSG::Bool b;

    OSG:: Int8  i8;
    OSG::UInt8 ui8;

    OSG:: Int16  i16;
    OSG::UInt16 ui16;

    OSG:: Int32  i32;
    OSG::UInt32 ui32;

    OSG:: Int64  i64;
    OSG::UInt64 ui64;

    OSG::Real32  r32;
    OSG::Real64  r64;


    OSG::FieldDataTraits2<OSG::Bool>::copyToBin(NULL, b);

    OSG::FieldDataTraits<OSG:: Int8>::copyToBin(NULL, i8);
    OSG::FieldDataTraits<OSG::UInt8>::copyToBin(NULL, ui8);

    OSG::FieldDataTraits<OSG:: Int16>::copyToBin(NULL, i16);
    OSG::FieldDataTraits<OSG::UInt16>::copyToBin(NULL, ui16);

    OSG::FieldDataTraits<OSG:: Int32>::copyToBin(NULL, i32);
    OSG::FieldDataTraits<OSG::UInt32>::copyToBin(NULL, ui32);

    OSG::FieldDataTraits<OSG:: Int64>::copyToBin(NULL, i64);
    OSG::FieldDataTraits<OSG::UInt64>::copyToBin(NULL, ui64);

    OSG::FieldDataTraits<OSG::Real32>::copyToBin(NULL, r32);
    OSG::FieldDataTraits<OSG::Real64>::copyToBin(NULL, r64);


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

    OSG::Matrix     mat;
    OSG::Quaternion quat;

    OSG::FieldDataTraits<OSG::Matrix    >::copyToBin(NULL, mat);
    OSG::FieldDataTraits<OSG::Quaternion>::copyToBin(NULL, quat);


    OSG::FieldDataTraits<OSG::Matrix    >::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits<OSG::Quaternion>::copyToBin(NULL, NULL, 0);


    OSG::String        str;
    OSG::Time          tim;
    OSG::Color3f       c3;
    OSG::Color4f       c4;
    OSG::Color3ub      c3ub;
    OSG::Color4ub      c4ub;
    OSG::DynamicVolume dv;
    OSG::BitVector     bv;


    OSG::FieldDataTraits <OSG::String       >::copyToBin(NULL, str);
    OSG::FieldDataTraits1<OSG::Time         >::copyToBin(NULL, tim);
    OSG::FieldDataTraits <OSG::Color3f      >::copyToBin(NULL, c3);
    OSG::FieldDataTraits <OSG::Color4f      >::copyToBin(NULL, c4);
    OSG::FieldDataTraits <OSG::Color3ub     >::copyToBin(NULL, c3ub);
    OSG::FieldDataTraits <OSG::Color4ub     >::copyToBin(NULL, c4ub);
    OSG::FieldDataTraits <OSG::DynamicVolume>::copyToBin(NULL, dv);
    OSG::FieldDataTraits1<OSG::BitVector    >::copyToBin(NULL, bv);


    OSG::FieldDataTraits <OSG::String       >::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits1<OSG::Time         >::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits <OSG::Color3f      >::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits <OSG::Color4f      >::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits <OSG::Color3ub     >::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits <OSG::Color4ub     >::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits <OSG::DynamicVolume>::copyToBin(NULL, NULL, 0);
    OSG::FieldDataTraits1<OSG::BitVector    >::copyToBin(NULL, NULL, 0);
}
