
#include <stdio.h>
#include <OSGVecFieldDataType.h>
#include <OSGSysFieldDataType.h>
#include <OSGMathFieldDataType.h>
#include <OSGBaseFieldDataType.h>

int main(void)
{
    char memblock[2048];

    OSG::MemoryHandle pMem = (OSG::MemoryHandle) memblock;

    fprintf(stderr, "TestStart\n");

    OSG::Vec2f  v2;
    OSG::Vec3f  v3;
    OSG::Vec4f  v4;
    OSG::Vec4ub v4ub;

    OSG::Pnt2f p2;
    OSG::Pnt3f p3;
    OSG::Pnt4f p4;

    OSG::FieldDataTraits<OSG::Vec2f >::copyToBin(pMem, v2);
    OSG::FieldDataTraits<OSG::Vec3f >::copyToBin(pMem, v3);
    OSG::FieldDataTraits<OSG::Vec4f >::copyToBin(pMem, v4);
    OSG::FieldDataTraits<OSG::Vec4ub>::copyToBin(pMem, v4ub);

    OSG::FieldDataTraits<OSG::Vec2f >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::Vec3f >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::Vec4f >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::Vec4ub>::copyToBin(pMem, NULL, 0);

    OSG::FieldDataTraits<OSG::Pnt2f>::copyToBin(pMem, p2);
    OSG::FieldDataTraits<OSG::Pnt3f>::copyToBin(pMem, p3);
    OSG::FieldDataTraits<OSG::Pnt4f>::copyToBin(pMem, p4);

    OSG::FieldDataTraits<OSG::Pnt2f>::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::Pnt3f>::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::Pnt4f>::copyToBin(pMem, NULL, 0);


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


    OSG::FieldDataTraits2<OSG::Bool>::copyToBin(pMem, b);

    OSG::FieldDataTraits<OSG:: Int8>::copyToBin(pMem, i8);
    OSG::FieldDataTraits<OSG::UInt8>::copyToBin(pMem, ui8);

    OSG::FieldDataTraits<OSG:: Int16>::copyToBin(pMem, i16);
    OSG::FieldDataTraits<OSG::UInt16>::copyToBin(pMem, ui16);

    OSG::FieldDataTraits<OSG:: Int32>::copyToBin(pMem, i32);
    OSG::FieldDataTraits<OSG::UInt32>::copyToBin(pMem, ui32);

    OSG::FieldDataTraits<OSG:: Int64>::copyToBin(pMem, i64);
    OSG::FieldDataTraits<OSG::UInt64>::copyToBin(pMem, ui64);

    OSG::FieldDataTraits<OSG::Real32>::copyToBin(pMem, r32);
    OSG::FieldDataTraits<OSG::Real64>::copyToBin(pMem, r64);


    OSG::FieldDataTraits2<OSG::Bool>::copyToBin(pMem, NULL, 0);

    OSG::FieldDataTraits<OSG:: Int8>::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::UInt8>::copyToBin(pMem, NULL, 0);

    OSG::FieldDataTraits<OSG:: Int16>::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::UInt16>::copyToBin(pMem, NULL, 0);

    OSG::FieldDataTraits<OSG:: Int32>::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::UInt32>::copyToBin(pMem, NULL, 0);

    OSG::FieldDataTraits<OSG:: Int64>::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::UInt64>::copyToBin(pMem, NULL, 0);

    OSG::FieldDataTraits<OSG::Real32>::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::Real64>::copyToBin(pMem, NULL, 0);

    OSG::Matrix     mat;
    OSG::Quaternion quat;

    OSG::FieldDataTraits<OSG::Matrix    >::copyToBin(pMem, mat);
    OSG::FieldDataTraits<OSG::Quaternion>::copyToBin(pMem, quat);


    OSG::FieldDataTraits<OSG::Matrix    >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits<OSG::Quaternion>::copyToBin(pMem, NULL, 0);


    OSG::String        str("xxx");;
    OSG::Time          tim;
    OSG::Color3f       c3;
    OSG::Color4f       c4;
    OSG::Color3ub      c3ub;
    OSG::Color4ub      c4ub;
    OSG::DynamicVolume dv;
    OSG::BitVector     bv;


    OSG::FieldDataTraits <OSG::String       >::copyToBin(pMem, str);
    OSG::FieldDataTraits1<OSG::Time         >::copyToBin(pMem, tim);
    OSG::FieldDataTraits <OSG::Color3f      >::copyToBin(pMem, c3);
    OSG::FieldDataTraits <OSG::Color4f      >::copyToBin(pMem, c4);
    OSG::FieldDataTraits <OSG::Color3ub     >::copyToBin(pMem, c3ub);
    OSG::FieldDataTraits <OSG::Color4ub     >::copyToBin(pMem, c4ub);
    OSG::FieldDataTraits <OSG::DynamicVolume>::copyToBin(pMem, dv);
    OSG::FieldDataTraits1<OSG::BitVector    >::copyToBin(pMem, bv);


    OSG::FieldDataTraits <OSG::String       >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits1<OSG::Time         >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits <OSG::Color3f      >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits <OSG::Color4f      >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits <OSG::Color3ub     >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits <OSG::Color4ub     >::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits <OSG::DynamicVolume>::copyToBin(pMem, NULL, 0);
    OSG::FieldDataTraits1<OSG::BitVector    >::copyToBin(pMem, NULL, 0);

    return 0;
}
