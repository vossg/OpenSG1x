// Little test for matrxi compose/decompose...

#define  __STDC_LIMIT_MACROS

#include <stdio.h>

#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>
#include <OSGVector.h>
#include <OSGQuaternion.h>
#include <OSGMatrix.h>

#if defined(__sgi)
#include <inttypes.h>
#else
#if !defined(WIN32)
#include <stdint.h>
#endif
#endif

#include <limits>

#define UINT8_MIN 0
#define UINT16_MIN 0
#define UINT32_MIN 0
#define UINT64_MIN (0LL)

OSG_USING_NAMESPACE

int main(int argc, char *argv[])
{
    osgInit(argc, argv);

    UInt8 ui8;
    Int8   i8;

    UInt16 ui16;
    Int16   i16;

    UInt32 ui32;
    Int32   i32;

    UInt64 ui64;
    Int64   i64;

    Real32  r32;
    Real64  r64;
    Real128 r128;
        

#if !defined(WIN32)
    fprintf(stderr, "%hhu | %02hhx\n", UINT8_MIN, UINT8_MIN);
    fprintf(stderr, "%hhu | %02hhx\n", UINT8_MAX, UINT8_MAX);

    ui8 = TypeTraits<UInt8>::getFromString("255");
    fprintf(stderr, "%hhu         \n", ui8);

    ui8 = TypeTraits<UInt8>::getFromString("0");
    fprintf(stderr, "%hhu         \n", ui8);

    ui8 = TypeTraits<UInt8>::getFromString("-128");
    fprintf(stderr, "%hhu         \n", ui8);


    fprintf(stderr, "%hhd | %02hhx\n", INT8_MIN, INT8_MIN);
    fprintf(stderr, "%hhd | %02hhx\n", INT8_MAX, INT8_MAX);

    i8  = TypeTraits<Int8>::getFromString("127");
    fprintf(stderr, "%hhd         \n", i8);

    i8  = TypeTraits<Int8>::getFromString("-128");
    fprintf(stderr, "%hhd         \n", i8);


    fprintf(stderr, "%hu | %04hx\n", UINT16_MIN, UINT16_MIN);
    fprintf(stderr, "%hu | %04hx\n", UINT16_MAX, UINT16_MAX);

    ui16 = TypeTraits<UInt16>::getFromString("65535");
    fprintf(stderr, "%hu\n", ui16);

    ui16 = TypeTraits<UInt16>::getFromString("0");
    fprintf(stderr, "%hu\n", ui16);

    fprintf(stderr, "%hd | %04hx\n", INT16_MIN, INT16_MIN);
    fprintf(stderr, "%hd | %04hx\n", INT16_MAX, INT16_MAX);

    i16 = TypeTraits<Int16>::getFromString("32767");
    fprintf(stderr, "%hd\n", i16);

    i16 = TypeTraits<Int16>::getFromString("-32768");
    fprintf(stderr, "%hd\n", i16);


    fprintf(stderr, "%u | %08x\n", UINT32_MIN, UINT32_MIN);
    fprintf(stderr, "%u | %08x\n", UINT32_MAX, UINT32_MAX);

    ui32 = TypeTraits<UInt32>::getFromString("4294967295");
    fprintf(stderr, "%u\n", ui32);

    ui32 = TypeTraits<UInt32>::getFromString("0");
    fprintf(stderr, "%u\n", ui32);



    fprintf(stderr, "%d | %08x\n", INT32_MIN, INT32_MIN);
    fprintf(stderr, "%d | %08x\n", INT32_MAX, INT32_MAX);

    i32 = TypeTraits<Int32>::getFromString("2147483647");
    fprintf(stderr, "%d\n", i32);

    i32 = TypeTraits<Int32>::getFromString("-2147483648");
    fprintf(stderr, "%d\n", i32);



    fprintf(stderr, "%llu | %016llx\n", UINT64_MIN, UINT64_MIN);
    fprintf(stderr, "%llu | %016llx\n", UINT64_MAX, UINT64_MAX);

    ui64 = TypeTraits<UInt64>::getFromString("18446744073709551615");
    fprintf(stderr, "%llu\n", ui64);

    ui64 = TypeTraits<UInt64>::getFromString("0");
    fprintf(stderr, "%llu\n", ui64);



    fprintf(stderr, "%lld | %016llx\n", INT64_MIN, INT64_MIN);
    fprintf(stderr, "%lld | %016llx\n", INT64_MAX, INT64_MAX);

    i64 = TypeTraits<Int64>::getFromString("9223372036854775807");
    fprintf(stderr, "%lld\n", i64);

    i64 = TypeTraits<Int64>::getFromString("-9223372036854775808");
    fprintf(stderr, "%lld\n", i64);
#endif


    fprintf(stderr, "%e |\n", FLT_MIN);
    fprintf(stderr, "%e |\n", FLT_MAX);

    r32 = TypeTraits<Real32>::getFromString("1.17549435e-38");
    fprintf(stderr, "%e\n", r32);

    r32 = TypeTraits<Real32>::getFromString("3.40282347e+38");
    fprintf(stderr, "%e\n", r32);

    fprintf(stderr, "%le |\n", DBL_MIN);
    fprintf(stderr, "%le |\n", DBL_MAX);

    r64 = TypeTraits<Real64>::getFromString("2.2250738585072014e-308");
    fprintf(stderr, "%le\n", r64);

    r64 = TypeTraits<Real64>::getFromString("1.7976931348623157e+308");
    fprintf(stderr, "%le\n", r64);

    fprintf(stderr, "%Le |\n", LDBL_MIN);
    fprintf(stderr, "%Le |\n", LDBL_MAX);

#if defined(__sgi) || defined(WIN32)
    r128 = TypeTraits<Real128>::getFromString("2.2250738585072014e-308");
    fprintf(stderr, "%Le\n", r128);

    r128 = TypeTraits<Real128>::getFromString("1.7976931348623157e+308");
    fprintf(stderr, "%Le\n", r128);
#else
    r128 = TypeTraits<Real128>::getFromString("3.36210314311209350626e-4932");
    fprintf(stderr, "%Le\n", r128);

    r128 = TypeTraits<Real128>::getFromString("1.18973149535723176502e+4932");
    fprintf(stderr, "%Le\n", r128);
#endif

    fprintf(stderr, "Real32  (%u)\n", sizeof(Real32 ));
    fprintf(stderr, "Real64  (%u)\n", sizeof(Real64 ));
    fprintf(stderr, "Real128 (%u)\n", sizeof(Real128));

    fprintf(stderr, "%e |\n", std::numeric_limits<Real32>::min());
    fprintf(stderr, "%e |\n", std::numeric_limits<Real32>::max());

    fprintf(stderr, "%le |\n", std::numeric_limits<Real64>::min());
    fprintf(stderr, "%le |\n", std::numeric_limits<Real64>::max());

    fprintf(stderr, "%Le |\n", std::numeric_limits<Real128>::min());
    fprintf(stderr, "%Le |\n", std::numeric_limits<Real128>::max());

    osgExit();
}
