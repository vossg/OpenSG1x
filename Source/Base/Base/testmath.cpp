

#include <stdio.h>

#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>
#include <OSGVector.h>
#include <OSGMatrix.h>
#include <OSGMatrixUtility.h>
#include <OSGQuaternion.h>

using OSG::Vec2f;
using OSG::Vec3f;
using OSG::Vec4f;

using OSG::Vec2s;

using OSG::Pnt2f;
using OSG::Pnt3f;
using OSG::Pnt4f;

using OSG::Matrix4f;
using OSG::Matrix;
using OSG::Quaternion;
using OSG::TransformationMatrix;

using OSG::UInt8;
using OSG::UInt16;
using OSG::UInt32;
using OSG::Int32;

using OSG::Real32;
using OSG::Real64;
using OSG::Real128;

using OSG::osgcos;
using OSG::osgsin;
using OSG::Pi;

using OSG::MatrixOrthogonal;
using OSG::MatrixFrustum;
using OSG::MatrixPerspective;
using OSG::MatrixStereoPerspective;
using OSG::MatrixLookAt;
using OSG::MatrixProjection;

// instantiate all classes to find compile problems

using OSG::VectorInterface;
using OSG::PointInterface;
using OSG::VecStorage2;
using OSG::VecStorage3;
using OSG::VecStorage4;

OSG_USING_NAMESPACE

template class VectorInterface<Real32, VecStorage2<Real32> >;
template class VectorInterface<Real32, VecStorage3<Real32> >;
template class VectorInterface<Real32, VecStorage4<Real32> >;

template class VectorInterface<UInt16, VecStorage2<UInt16> >;
template class VectorInterface<UInt16, VecStorage3<UInt16> >;
template class VectorInterface<UInt16, VecStorage4<UInt16> >;

template class VectorInterface<UInt8, VecStorage2<UInt8> >;
template class VectorInterface<UInt8, VecStorage3<UInt8> >;
template class VectorInterface<UInt8, VecStorage4<UInt8> >;

//template class PointInterface<Real32, VecStorage2<Real32> >;
//template class PointInterface<Real32, VecStorage3<Real32> >;
//template class PointInterface<Real32, VecStorage4<Real32> >;

//template class PointInterface<UInt16, VecStorage2<UInt16> >;
//template class PointInterface<UInt16, VecStorage3<UInt16> >;
//template class PointInterface<UInt16, VecStorage4<UInt16> >;

//template class PointInterface<UInt8, VecStorage2<UInt8> >;
//template class PointInterface<UInt8, VecStorage3<UInt8> >;
//template class PointInterface<UInt8, VecStorage4<UInt8> >;


using OSG::osgInit;

template <class VecT>
void printVec(VecT &vec)
{
    std::cerr << vec << "\n";
}

Real32 pValsI[] = { 10., 11., 12., 13., 14 };

void vectorTestConstructAndSetTest(void)
{
    Real32 *pVals = pValsI;

    std::cerr << "vectorTestConstructAndSetTest\n";

    Vec2f v2f;
    Vec3f v3f;
    Vec4f v4f;

    Pnt2f p2f(-1., -2.);
    Pnt3f p3f(-1., -2., -3.);
    Pnt4f p4f(-1., -2., -3., -4.);

    p3f = p3f - v3f;

    Vec2f v2f2(2., 1.);
    Vec2f v2f3(3., 2., 1.);
    Vec2f v2f4(4., 3., 2., 1.);

    Vec3f v3f2(2., 1.);
    Vec3f v3f3(3., 2., 1.);
    Vec3f v3f4(4., 3., 2., 1.);

    Vec4f v4f2(2., 1.);
    Vec4f v4f3(3., 2., 1.);
    Vec4f v4f4(4., 3., 2., 1.);

    std::cerr << "construct (void);\n";

    printVec(v2f);
    printVec(v3f);
    printVec(v4f);

    std::cerr << "construct (2 val);\n";

    printVec(v2f2);
    printVec(v3f2);
    printVec(v4f2);

    std::cerr << "construct (3 val);\n";

    printVec(v2f3);
    printVec(v3f3);
    printVec(v4f3);

    std::cerr << "construct (4 val);\n";

    printVec(v2f4);
    printVec(v3f4);
    printVec(v4f4);


    Vec2f v2f5(v2f4);
    Vec2f v2f6(v3f4);
    Vec2f v2f7(v4f4);

    Vec2f v2fp5(p2f);
    Vec2f v2fp6(p3f);
    Vec2f v2fp7(p4f);

    Vec3f v3f5(v2f4);
    Vec3f v3f6(v3f4);
    Vec3f v3f7(v4f4);

    Vec3f v3fp5(p2f);
    Vec3f v3fp6(p3f);
    Vec3f v3fp7(p4f);

    Vec4f v4f5(v2f4);
    Vec4f v4f6(v3f4);
    Vec4f v4f7(v4f4);

    Vec4f v4fp5(p2f);
    Vec4f v4fp6(p3f);
    Vec4f v4fp7(p4f);

    std::cerr << "construct (cp size 2) " << v2f4 << "\n";
    printVec(v2f5);
    printVec(v3f5);
    printVec(v4f5);

    std::cerr << "construct (cp size 3) " << v3f4 << "\n";
    printVec(v2f6);
    printVec(v3f6);
    printVec(v4f6);

    std::cerr << "construct (cp size 4) " << v4f4 << "\n";
    printVec(v2f7);
    printVec(v3f7);
    printVec(v4f7);

    std::cerr << "construct (cp size p2) " << p2f << "\n";
    printVec(v2fp5);
    printVec(v3fp5);
    printVec(v4fp5);

    std::cerr << "construct (cp size p3) " << p3f << "\n";
    printVec(v2fp6);
    printVec(v3fp6);
    printVec(v4fp6);

    std::cerr << "construct (cp size p4) " << p4f << "\n";
    printVec(v2fp7);
    printVec(v3fp7);
    printVec(v4fp7);




    Vec2f v2f8(pVals);
    Vec3f v3f8(pVals);
    Vec4f v4f8(pVals);

    std::cerr << "construct (array)\n";
    printVec(v2f8);
    printVec(v3f8);
    printVec(v4f8);

    v2f8.setNull();
    v3f8.setNull();
    v4f8.setNull();

    std::cerr << "set Null\n";
    printVec(v2f8);
    printVec(v3f8);
    printVec(v4f8);

    v2f8.setValues( 20.f, 30.f);
//    v3f8.setValue(20., 30.);
//    v4f8.setValue(20., 30.);

    std::cerr << "set 2 vals\n";

    printVec(v2f8);
    printVec(v3f8);
    printVec(v4f8);

//    v2f8.setValue(20., 30., 40.);
    v3f8.setValues(20., 30., 40.);
//    v4f8.setValue(20., 30., 40.);

    std::cerr << "set 3 vals\n";

    printVec(v2f8);
    printVec(v3f8);
    printVec(v4f8);

//    v2f8.setValue(20., 30., 40., 50.);
//    v3f8.setValue(20., 30., 40., 50.);
    v4f8.setValues(20., 30., 40., 50.);

    std::cerr << "set 4 vals\n";

    printVec(v2f8);
    printVec(v3f8);
    printVec(v4f8);


//    v2f8.setValue(v2f4);
    v3f8.setValue(v2f4);
    v4f8.setValue(v2f4);

    std::cerr << "set vec size 2 " << v2f4 << "\n";;
    printVec(v2f8);
    printVec(v3f8);
    printVec(v4f8);

//    v2f8.setValue(20., 30., 40., 50.);
//    v3f8.setValues(20., 30., 40., 50.);
//    v4f8.setValue(20., 30., 40., 50.);

    v2f8.setValue(v3f4);
//    v3f8.setValue(v3f4);
    v4f8.setValue(v3f4);

    std::cerr << "set vec size 3 " << v3f4 << "\n";
    printVec(v2f8);
    printVec(v3f8);
    printVec(v4f8);

//    v2f8.setValue(20., 30., 40., 50.);
//    v3f8.setValues(20., 30., 40., 50.);
//    v4f8.setValue(20., 30., 40., 50.);

    v2f8.setValue(v4f4);
    v3f8.setValue(v4f4);
//    v4f8.setValue(v4f4);

    std::cerr << "set vec size 4 " << v4f4 << "\n";

    printVec(v2f8);
    printVec(v3f8);
    printVec(v4f8);


//    v2f8.setValue(20., 30., 40., 50.);
//    v3f8.setValues(20., 30., 40., 50.);
//    v4f8.setValue(20., 30., 40., 50.);

#ifndef OSG_DISABLE_DEPRECATED
    v2f8.setValue((char *) NULL);
    v3f8.setValue((char *) NULL);
    v4f8.setValue((char *) NULL);

    std::cerr << "set vec from string NULL \n";

    printVec(v2f8);
    printVec(v3f8);
    printVec(v4f8);


//    v2f8.setValue(20., 30., 40., 50.);
//    v3f8.setValues(20., 30., 40., 50.);
//    v4f8.setValue(20., 30., 40., 50.);

    v2f8.setValue("");
    v3f8.setValue("");
    v4f8.setValue("");

    std::cerr << "set vec from string \"\" \n";

    printVec(v2f8);
    printVec(v3f8);
    printVec(v4f8);



    v2f8.setNull();
    v3f8.setNull();
    v4f8.setNull();

    v2f8.setValue("1");
    v3f8.setValue("1 ");
    v4f8.setValue("1");

    std::cerr << "set vec from string 1 \n";

    printVec(v2f8);
    printVec(v3f8);
    printVec(v4f8);



    v2f8.setNull();
    v3f8.setNull();
    v4f8.setNull();

    v2f8.setValue("1 2");
    v3f8.setValue("1 2");
    v4f8.setValue("1 2 ");

    std::cerr << "set vec from string 2\n";

    printVec(v2f8);
    printVec(v3f8);
    printVec(v4f8);



    v2f8.setNull();
    v3f8.setNull();
    v4f8.setNull();

    v2f8.setValue("1 2 3 ");
    v3f8.setValue("1 2 3");
    v4f8.setValue("1 2 3");

    std::cerr << "set vec from string 3\n";

    printVec(v2f8);
    printVec(v3f8);
    printVec(v4f8);



    v2f8.setNull();
    v3f8.setNull();
    v4f8.setNull();

    v2f8.setValue("1 2 3 4");
    v3f8.setValue("1 2 3 4 ");
    v4f8.setValue("1 2 3 4");

    std::cerr << "set vec from string 4\n";

    printVec(v2f8);
    printVec(v3f8);
    printVec(v4f8);


    v2f8.setNull();
    v3f8.setNull();
    v4f8.setNull();

    v2f8.setValue("1 2 3 4 5 6");
    v3f8.setValue("1 2 3 4 5 6");
    v4f8.setValue("1 2 3 4 5 6");

    std::cerr << "set vec from string 4\n";

    printVec(v2f8);
    printVec(v3f8);
    printVec(v4f8);

#endif


    v2f8.setNull();
    v3f8.setNull();
    v4f8.setNull();

    v2f8.setValue(pVals);
    v3f8.setValue(pVals);
    v4f8.setValue(pVals);

    std::cerr << "set vec from Real32\n";

    printVec(v2f8);
    printVec(v3f8);
    printVec(v4f8);

}

void vectorMathTests(void)
{
    Vec2f v2f1;
    Vec2f v2f2(1., 0.);

    Vec3f v3f1;
    Vec3f v3f2(1., 0., 0.5);

    Vec4f v4f1;
    Vec4f v4f2(1., 0., 0., 0.5);

    Real32 rX, rY, rZ, rW;

    std::cout << v2f1 << " : iz : " << v2f1.isZero() << "\n";
    std::cout << v3f1 << " : iz : " << v3f1.isZero() << "\n";
    std::cout << v4f1 << " : iz : " << v4f1.isZero() << "\n";

    std::cout << v2f2 << " : iz : " << v2f2.isZero() << "\n";
    std::cout << v3f2 << " : iz : " << v3f2.isZero() << "\n";
    std::cout << v4f2 << " : iz : " << v4f2.isZero() << "\n";

    v2f1.setValues(3., 4.);
    v3f1.setValues(3., 4., 5.);
    v4f1.setValues(3., 4., 5., 6.);

    std::cout << v2f1 << " l : " << v2f1.length() << " (5)\n";
    std::cout << v3f1 << " l : " << v3f1.length() << " (7.07106)\n";
    std::cout << v4f1 << " l : " << v4f1.length() << " (9.27361)\n";

    v2f1.normalize();
    v3f1.normalize();
    v4f1.normalize();

    std::cout << v2f1 << " l : " << v2f1.length() << " (1)\n";
    std::cout << v3f1 << " l : " << v3f1.length() << " (1)\n";
    std::cout << v4f1 << " l : " << v4f1.length() << " (1)\n";

    v2f1.setValues(0., 1.);
    v3f1.setValues(1., 0., 0.);
    v4f1.setValues(0., 0., 1., 6.);

    v2f2.setValues(1., 0.);
    v3f2.setValues(0., 1., 0.);
    v4f2.setValues(1., 0., 0., 10.);

    std::cout << v2f1.cross(v2f2) << "\n";
    std::cout << v3f1.cross(v3f2) << "\n";
    std::cout << v4f1.cross(v4f2) << "\n";

    v2f1.crossThis(v2f2);
    v3f1.crossThis(v3f2);
    v4f1.crossThis(v4f2);

    std::cout << v2f1 << "\n";
    std::cout << v3f1 << "\n";
    std::cout << v4f1 << "\n";

    v2f1.setValues(1., 2.);
    v3f1.setValues(1., 2., 3.);
    v4f1.setValues(1., 2., 3., 4.);

    v2f2.setValues(10., 20.);
    v3f2.setValues(10., 20., 30.);
    v4f2.setValues(10., 20., 30., 40.);

    std::cout << v2f1.dot(v2f2) << " ( 50) \n";
    std::cout << v3f1.dot(v3f2) << " (140)\n";
    std::cout << v4f1.dot(v4f2) << " (300)\n";

    v2f1.negate();
    v3f1.negate();
    v4f1.negate();

    std::cout << v2f1 << " \n";
    std::cout << v3f1 << " \n";
    std::cout << v4f1 << " \n";

    std::cout << -v2f1 << " \n";
    std::cout << -v3f1 << " \n";
    std::cout << -v4f1 << " \n";

    v2f1.setValues(1., 1.);
    v3f1.setValues(3., 3., 3.);
    v4f1.setValues(1., 2., 3., 4.);

    std::cout << v2f1.equals(v2f2, 0.5) << "\n";
    std::cout << v3f1.equals(v3f2, 0.5) << "\n";
    std::cout << v4f1.equals(v4f2, 0.5) << "\n";

    v2f2.setValues(1.3, 0.9);
    v3f2.setValues(3., 3., 3.6);
    v4f2.setValues(1., 2., 3, 4.);

    std::cout << v2f1.equals(v2f2, 0.5) << "\n";
    std::cout << v3f1.equals(v3f2, 0.5) << "\n";
    std::cout << v4f1.equals(v4f2, 0.5) << "\n";

    std::cout << (v2f1 == v2f2) << "\n";
    std::cout << (v3f1 == v3f2) << "\n";
    std::cout << (v4f1 == v4f2) << "\n";

    std::cout << (v2f1 != v2f2) << "\n";
    std::cout << (v3f1 != v3f2) << "\n";
    std::cout << (v4f1 != v4f2) << "\n";

    v2f1.setValues(1., 2.);
    v3f1.setValues(1., 2., 3.);
    v4f1.setValues(1., 2., 3., 4.);

    v2f2.setValues(10., 20.);
    v3f2.setValues(10., 20., 30.);
    v4f2.setValues(10., 20., 30., 40.);

    v2f1 += v2f2;
    v3f1 += v3f2;
    v4f1 += v4f2;

    std::cout << v2f1 << " \n";
    std::cout << v3f1 << " \n";
    std::cout << v4f1 << " \n";

    v2f1 -= v2f2;
    v3f1 -= v3f2;
    v4f1 -= v4f2;

    std::cout << v2f1 << " \n";
    std::cout << v3f1 << " \n";
    std::cout << v4f1 << " \n";

    v2f1 *= 4.;
    v3f1 *= 4.;
    v4f1 *= 4.;

    std::cout << v2f1 << " \n";
    std::cout << v3f1 << " \n";
    std::cout << v4f1 << " \n";

    v2f1 /= 2.;
    v3f1 /= 2.;
    v4f1 /= 2.;

    std::cout << v2f1 << " \n";
    std::cout << v3f1 << " \n";
    std::cout << v4f1 << " \n";

    fprintf(stderr, "%f %f %f %f\n", v4f1[0], v4f1[1], v4f1[2], v4f1[3]);
    fprintf(stderr, "%f %f %f %f\n",
            v4f1.getValues()[0], v4f1.getValues()[1],
            v4f1.getValues()[2], v4f1.getValues()[3]);

    v4f1.getSeparateValues(rX, rY, rZ, rW);

    std::cout << v2f1 << " \n";
    std::cout << v3f1 << " \n";
    std::cout << v4f1 << " \n";

    std::cout << v2f2 << " \n";
    std::cout << v3f2 << " \n";
    std::cout << v4f2 << " \n";

    v2f1 = v2f2;
    v3f1 = v3f2;
    v4f1 = v4f2;

    std::cout << v2f1 << " \n";
    std::cout << v3f1 << " \n";
    std::cout << v4f1 << " \n";

    std::cout << v2f2 << " \n";
    std::cout << v3f2 << " \n";
    std::cout << v4f2 << " \n";

    v2f1 = v2f2 * 2.f;
    v3f1 = v3f2 * 2.f;
    v4f1 = v4f2 * 2.f;

    std::cout << v2f1 << " \n";
    std::cout << v3f1 << " \n";
    std::cout << v4f1 << " \n";

    v2f1 = 2.f * v2f2;
    v3f1 = 2.f * v3f2;
    v4f1 = 2.f * v4f2;

    std::cout << v2f1 << " \n";
    std::cout << v3f1 << " \n";
    std::cout << v4f1 << " \n";

    std::cout << v2f2 << " \n";
    std::cout << v3f2 << " \n";
    std::cout << v4f2 << " \n";

    v2f1 = 0.5f * v2f2;
    v3f1 = 0.5f * v3f2;
    v4f1 = 0.5f * v4f2;

    std::cout << v2f1 << " \n";
    std::cout << v3f1 << " \n";
    std::cout << v4f1 << " \n";

    v2f1 = v2f2 + v2f2;
    v3f1 = v3f2 + v3f2;
    v4f1 = v4f2 + v4f2;

    std::cout << v2f1 << " \n";
    std::cout << v3f1 << " \n";
    std::cout << v4f1 << " \n";

    v2f1 = v2f2 - v2f1;
    v3f1 = v3f2 - v3f1;
    v4f1 = v4f2 - v4f1;

    std::cout << v2f1 << " \n";
    std::cout << v3f1 << " \n";
    std::cout << v4f1 << " \n";

    std::cout << v2f2 << " \n";
    std::cout << v3f2 << " \n";
    std::cout << v4f2 << " \n";
}

void matrixTest(void)
{
    Vec3f pVec3Array[4];

    pVec3Array[0].setValues(11., 12., 13.);
    pVec3Array[1].setValues(21., 22., 23.);
    pVec3Array[2].setValues(31., 32., 33.);
    pVec3Array[3].setValues(41., 42., 43.);

    Vec4f pVec4Array[4];

    UInt32 i;

    pVec4Array[0].setValues(11., 12., 13., 14.);
    pVec4Array[1].setValues(21., 22., 23., 24.);
    pVec4Array[2].setValues(31., 32., 33., 34.);
    pVec4Array[3].setValues(41., 42., 43., 44.);

    Real32 pValArray[16] = { 11., 21., 31., 41.,
                                12., 22., 32., 42.,
                                13., 23., 33., 43.,
                                14., 24., 34., 44.};

    Real32 pValArrayT[16] = { 11., 12., 13., 14.,
                                 21., 22., 23., 24.,
                                 31., 32., 33., 34.,
                                 41., 42., 34., 44.};

    Vec3f v1(11., 12., 13.);
    Vec3f v2(21., 22., 23.);
    Vec3f v3(31., 32., 33.);
    Vec3f v4(41., 42., 43.);

    Quaternion q1;
    Quaternion q2;
    Quaternion q3;

    Matrix m1;
    Matrix m2(v1, v2, v3);
    Matrix m3(v1, v2, v3, v4);
    Matrix m4(m3);

    Matrix m5(11., 21., 31., 41.,
                 12., 22., 32., 42,
                 13., 23., 33., 43.,
                 14., 24., 34., 44.);

    Pnt3f p1(1., 0., 0.);
    Pnt3f p2;

    Matrix m6;
    Matrix m7;
    Matrix m8;
    Matrix m9;

    std::cout << std::endl << "Matrix math test " << std::endl;
    std::cout << std::endl << "========================================" << std::endl << std::endl;

    std::cout << "Identity               : " << std::endl
         << Matrix::identity()   << std::endl;

    std::cout << std::endl << "========================================" << std::endl << std::endl;

    std::cout << "Default constructor    : " << std::endl << m1 << std::endl;
    std::cout << "3 vector3f constructor : " << std::endl << m2 << std::endl;
    std::cout << "4 vector3f constructor : " << std::endl << m3 << std::endl;
    std::cout << "Copy consructor        : " << std::endl << m4 << std::endl;
    std::cout << "16f values construtor  : " << std::endl << m5 << std::endl;

    std::cout << std::endl << "========================================" << std::endl << std::endl;


    m1.setValue(v4, v3, v2);

    m2.setIdentity();
    m2.setValue(v1, v2, v3, v4);

    m3.setIdentity();
    m3.setValue(11., 21., 31., 41.,
                12., 22,  32., 42.,
                13., 23., 33., 43.,
                14., 24., 34., 44.);

    m4.setIdentity();
    m4.setValue(m3);

    m5.setValue(pValArrayT);
    m8.setValue(pValArray, false);
    m6.setValue(pVec4Array);
//    m7.setValue(pVec3Array);

    std::cout << "Set      matrix  : " << std::endl << m4 << std::endl;
    std::cout << "Set 3 3f vectors : " << std::endl << m1 << std::endl;
    std::cout << "Set 4 3f vectors : " << std::endl << m2 << std::endl;
    std::cout << "Set 16 f values  : " << std::endl << m3 << std::endl;
    std::cout << "Set valT array   : " << std::endl << m5 << std::endl;
    std::cout << "Set val array    : " << std::endl << m8 << std::endl;
    std::cout << "Set vec4 array   : " << std::endl << m6 << std::endl;
    std::cout << "Set vec3 array   : " << std::endl << m7 << std::endl;

    std::cout << std::endl << "========================================" << std::endl << std::endl;

    std::cout << "Get Values : " << std::endl;

    for(i = 0; i < 4; i++)
    {
        for(UInt32 j = 0; j < 4; j++)
        {
            fprintf(stderr, "% 5.3f ", (m5.getValues())[j * 4 + i]);
        }

        fprintf(stderr, "\n");
    }

    std::cout << std::endl << "========================================" << std::endl << std::endl;

    m1.setIdentity();
    m1.setScale(10.);

    m2.setIdentity();
    m2.setScale(v3);

    m3.setIdentity();
    m3.setTranslate(v4);

    m4.setIdentity();
    m4.setTranslate(41., 42., 43.);

    std::cout << "Set scale val       : " << std::endl << m1 << std::endl;
    std::cout << "Set scale vec3f     : " << std::endl << m2 << std::endl;
    std::cout << "Set translate val   : " << std::endl << m4 << std::endl;
    std::cout << "Set translate vec3f : " << std::endl << m3 << std::endl;

    std::cout << std::endl << "========================================" << std::endl << std::endl;

    q1.setValueAsAxisDeg(1., 0., 0., 60.);
    q2.setValueAsAxisDeg(0., 1., 0., 60.);
    q3.setValueAsAxisDeg(0., 0., 1., 60.);


    m1.setRotate(q1);
    m2.setRotate(q2);
    m3.setRotate(q3);

    std::cout << "Set rotate X/60     : " << std::endl << m1 << std::endl;
    std::cout << "Set rotate Y/60     : " << std::endl << m2 << std::endl;
    std::cout << "Set rotate Z/60     : " << std::endl << m3 << std::endl;

    std::cout << std::endl << "========================================" << std::endl << std::endl;

    m1.setIdentity();
    m1.setTranslate(41., 42., 43);

    std::cout << m1 << std::endl;

    m2.setIdentity();
    m2.setRotate(q1);

    m1.mult(m2);

    std::cout << "mult trans * rot : " << std::endl << m1 << std::endl;
    std::cout << std::endl << "========================================" << std::endl << std::endl;

    m1.setIdentity();
    m1.setTranslate(41., 42., 43);

    m2.setIdentity();
    m2.setRotate(q1);

    m1.multLeft(m2);

    std::cout << "multLeft rot * trans : " << std::endl << m1 << std::endl;
    std::cout << std::endl << "========================================" << std::endl << std::endl;

    m1.setIdentity();
    m1.setTranslate(41., 42., 43);

    m2.setIdentity();
    m2.setRotate(q1);

    m1.mult(m2);

    m4 = m1;

    std::cout << m1.inverse(m3) << std::endl;
    std::cout << "Inverse trans * rot : " << std::endl << m3 << std::endl;

    std::cout << m3.invertFrom(m1) << std::endl;
    std::cout << "InverseFrom trans * rot : " << std::endl << m3 << std::endl;

    m3 = m1;

    std::cout << m3.invert();
    std::cout << "Invert trans * rot : " << std::endl << m3 << std::endl;

    m4.mult(m3);
    std::cout << "Invert m-1 * m : " << std::endl << m4 << std::endl;

    m4 = m1;
    m3.mult(m4);

    std::cout << "Invert m * m-1 : " << std::endl << m3 << std::endl;

    std::cout << std::endl << "========================================" << std::endl << std::endl;


    m1.setIdentity();
    m1.setTranslate(41., 42., 43);

    m2.setIdentity();
    m2.setRotate(q1);

    m1.mult(m2);

    m4 = m1;

    std::cout << m1.inverse3(m3) << std::endl;
    std::cout << "Inverse trans * rot : " << std::endl << m3 << std::endl;

    std::cout << m3.invertFrom3(m1) << std::endl;
    std::cout << "InverseFrom trans * rot : " << std::endl << m3 << std::endl;

    m3 = m1;

    std::cout << m3.invert3() << std::endl;
    std::cout << "Invert trans * rot : " << std::endl << m3 << std::endl;

    m4.mult(m3);
    std::cout << "Invert m * m-1 : " << std::endl << m4 << std::endl;

    m4 = m1;
    m3.mult(m4);

    std::cout << "Invert m-1 * m : " << std::endl << m3 << std::endl;

    std::cout << std::endl << "========================================" << std::endl << std::endl;

    m1.setIdentity();
    m1.setTranslate(41., 42., 43);

    m2.setIdentity();
    m2.setRotate(q1);

    m1.mult(m2);

    v1.setValues(0., 0., 1.);
    p1.setValues(0., 1., 0.);

    m1.mult(v1, v2);
    m1.mult(p1, p2);

    std::cout << "Transform P : " << std::endl << p2 << std::endl;
    std::cout << "Transform V : " << std::endl << v2 << std::endl;

    std::cout << std::endl << "========================================" << std::endl << std::endl;

    m1.setIdentity();
    m2.setIdentity();
    m3.setIdentity();

    v1.setValues(41., 42., 43);
    q1.setValueAsAxisDeg(1., 0., 1., 60.);
    v2.setValues(5., 6., 7.);

    m1.setTranslate(v1);
    m2.setRotate(q1);
    m3.setScale(v2);

    m4 = m1;

    m4.mult(m2);
    m4.mult(m3);

    m5.setTransform(v1);

    m5.setTransform(q1);

    m5.setTransform(v1, q1);

    m5.setTransform(v1, q1, v2);

    std::cout << "Set Transform t*r*s : " << std::endl << m4 << std::endl;
    std::cout << "Set Transform trs   : " << std::endl << m5 << std::endl;

    std::cout << std::endl << "========================================" << std::endl << std::endl;


    m1.setIdentity();
    m2.setIdentity();
    m3.setIdentity();
    m4.setIdentity();
    m5.setIdentity();
    m6.setIdentity();
    m7.setIdentity();

    v1.setValues(41., 42., 43);
    q1.setValueAsAxisDeg(1., 0., 1., 60.);
    v2.setValues(10., 10., 10.);
    q2.setValueAsAxisDeg(0., 1., 0., 90.);
    v3.setValues(11., 12., 13.);

    m1.setTranslate(v1);
    m2.setRotate(q1);

    m3.setScale(v2);
    m4.setRotate(q2);
    m5.invertFrom(m4);

//    m6.setTranslate(v3);
//    m7.invertFrom(m6);

    m8 = m1;

    m8.mult(m6); // Center

    m8.mult(m2); // R

    m8.mult(m4); // SO
    m8.mult(m3); // S
    m8.mult(m5); // -SO

    m8.mult(m7); // -Center

    m9.setTransform(v1, q1, v2, q2);

    std::cout << "Set Transform t*r*s*so : " << std::endl << m8 << std::endl;
    std::cout << "Set Transform t r s so : " << std::endl << m9 << std::endl;

    std::cout << std::endl << "========================================" << std::endl << std::endl;

    m1.setIdentity();
    m2.setIdentity();
    m3.setIdentity();
    m4.setIdentity();
    m5.setIdentity();
    m6.setIdentity();
    m7.setIdentity();

    v1.setValues(41., 42., 43);
    q1.setValueAsAxisDeg(1., 0., 1., 60.);
    v2.setValues(11., 12., 13.);
    q2.setValueAsAxisDeg(0., 1., 0., 90.);
    v3.setValues(11., 12., 13.);

    m1.setTranslate(v1);
    m2.setRotate(q1);

    m3.setScale(v2);
    m4.setRotate(q2);
    m5.invertFrom(m4);

    m6.setTranslate(v3);
    m7.invertFrom(m6);

    m8 = m1;

    m8.mult(m6); // Center

    m8.mult(m2); // R

    m8.mult(m4); // SO
    m8.mult(m3); // S
    m8.mult(m5); // -SO

    m8.mult(m7); // -Center

    m9.setTransform(v1, q1, v2, q2, v3);

    std::cout << "Set Transform t*r*s*so*c : " << std::endl << m8 << std::endl;
    std::cout << "Set Transform t r s so c : " << std::endl << m9 << std::endl;
}


void quattest(void)
{
    UInt32 i;

    Vec3f v1;
    Vec3f v2;
    Vec3f v3;
    Vec3f v4;

    Real32 quatArray[4] = { 0.707, 0., 0., 0.707 };
    Real32 axisArray[4] = { 1., 0., 0., 90. };

    Matrix rotmatInX(
        1.000,    0.000,    0.000,    0.000,
        0.000,    0.500,   -0.866,    0.000,
        0.000,    0.866,    0.500,    0.000,
        0.000,    0.000,    0.000,    1.000);

    Matrix rotmatInY(
        0.500,    0.000,    0.866,    0.000,
        0.000,    1.000,    0.000,    0.000,
       -0.866,    0.000,    0.500,    0.000,
        0.000,    0.000,    0.000,    1.000);

    Matrix rotmatInZ(
        0.500,   -0.866,    0.000,    0.000,
        0.866,    0.500,    0.000,    0.000,
        0.000,    0.000,    1.000,    0.000,
        0.000,    0.000,    0.000,    1.000);

    Matrix rotmatOutX;
    Matrix rotmatOutY;
    Matrix rotmatOutZ;

    Real32 x;
    Real32 y;
    Real32 z;
    Real32 w;

    Vec3f vXX(rotmatInY[3]);

    v1.setValues(1., 0., 0.);

    v2.setValues(1., 0., 0.);
    v3.setValues(0., 1., 0.);

    Quaternion q1;
    Quaternion q2;
    Quaternion q3(q2);

    q2.setValueAsAxisDeg(0., 0., 1., 90.);

    Quaternion q4(v1, 90.);
    Quaternion q5(v2, v3);

    Quaternion q6;
    Quaternion q7;
    Quaternion q8;
    Quaternion q9;


    std::cout << std::endl << "Quaternion math test " << std::endl;
    std::cout << std::endl << "========================================" << std::endl << std::endl;

    std::cout << "Default Constructor         : " << std::endl << q1 << std::endl;
    std::cout << "Construtor Axis3f, Angle    : " << std::endl << q2 << std::endl;
    std::cout << "Copy Constructor            : " << std::endl << q3 << std::endl;
    std::cout << "Constructor AxisVec3f Angle : " << std::endl << q4 << std::endl;
    std::cout << "Constructor FromV3f ToV3f   : " << std::endl << q5 << std::endl;

    std::cout << std::endl << "========================================" << std::endl << std::endl;


    q1.setIdentity();

    q2.setIdentity();
    q2.setValueAsAxisDeg(axisArray);

    q3.setIdentity();
    q3.setValueAsQuat(quatArray);

    q4.setIdentity();
    q4.setValueAsAxisDeg(0., 1., 0., 180.);

    q5.setIdentity();
    q5.setValueAsQuat(0., 0.707, 0., 0.707);

    q6.setIdentity();
    q6.setValueAsAxisDeg(v1, 60.);

    q7.setIdentity();
    q7.setValue(v2, v3);

    q8.setIdentity();
    q8.setValueAsAxisDeg("0.0 1.0 0.0 90.");

    std::cout << "Set Identity                : " << std::endl << q1 << std::endl;
    std::cout << "Set from axis array         : " << std::endl << q2 << std::endl;
    std::cout << "Set from quat array         : " << std::endl << q3 << std::endl;
    std::cout << "Set from value axis         : " << std::endl << q4 << std::endl;
    std::cout << "Set from value quat         : " << std::endl << q5 << std::endl;
    std::cout << "Set from axis angle         : " << std::endl << q6 << std::endl;
    std::cout << "Set from from, to pair      : " << std::endl << q7 << std::endl;
    std::cout << "Set from string             : " << std::endl << q8 << std::endl;

    std::cout << std::endl << "========================================" << std::endl << std::endl;


    q1.setValueAsAxisDeg(1., 0., 0., 60.);
    q2.setValueAsAxisDeg(0., 1., 0., 60.);
    q3.setValueAsAxisDeg(0., 0., 1., 60.);

    std::cout << "Set from axis X/60          : " << std::endl << q1 << std::endl;
    std::cout << "Set from axis Y/60          : " << std::endl << q2 << std::endl;
    std::cout << "Set from axis Z/60          : " << std::endl << q3 << std::endl;
    std::cout << std::endl;

    q4.setValue(rotmatInX);
    q5.setValue(rotmatInY);
    q6.setValue(rotmatInZ);

    std::cout << "Set from matrix X/60        : " << std::endl << q4 << std::endl;
    std::cout << "Set from matrix Y/60        : " << std::endl << q5 << std::endl;
    std::cout << "Set from matrix Z/60        : " << std::endl << q6 << std::endl;
    std::cout << std::endl;

    q1.getValue(rotmatOutX);
    q2.getValue(rotmatOutY);
    q3.getValue(rotmatOutZ);

    std::cout << "Get matrix X/60        : " << std::endl << rotmatOutX << std::endl;
    std::cout << "Get matrix Y/60        : " << std::endl << rotmatOutY << std::endl;
    std::cout << "Get matrix Z/60        : " << std::endl << rotmatOutZ << std::endl;
    std::cout << std::endl;

    std::cout << std::endl << "========================================" << std::endl << std::endl;

    q1.setValueAsQuat(1., 2., 3., 4.); // Just for testing

    printf("Get val pointer\n");

    for(i = 0; i < 4; i++)
    {
        fprintf(stderr, "%5.3f ", q1.getValues()[i]);
    }
    fprintf(stderr, "\n");

    std::cout << std::endl << "========================================" << std::endl << std::endl;

    q2.getValueAsAxisDeg(x, y, z, w);

    printf("Get val as axis\n");
    printf("%5.3f %5.3f %5.3f %5.3f\n", x, y, z, w);

    q1.getValueAsQuat(x, y, z, w);

    printf("Get val as quat\n");
    printf("%5.3f %5.3f %5.3f %5.3f\n", x, y, z, w);

    std::cout << std::endl << "========================================" << std::endl << std::endl;

    q2.getValueAsAxisDeg(v1, w);

    printf("Get val as vec/angle\n");
    std::cout << v1;
    printf(" %5.3f\n", w);

    std::cout << std::endl << "========================================" << std::endl << std::endl;

    printf("Get val as single Real32 vals\n");
    printf("%5.3f %5.3f %5.3f %5.3f\n", q1.x(), q1.y(), q1.z(), q1.w());

    std::cout << std::endl << "========================================" << std::endl << std::endl;

    printf("length\n%5.3f", q1.length());

    q1.normalize();
    printf("norm\n%5.3f\n", q1.length());

    std::cout << std::endl << "========================================" << std::endl << std::endl;

    q2.invert();
    q3 = q2.inverse();

    std::cout << "Invert  :" << std::endl << q2 << std::endl;
    std::cout << "Inverse :" << std::endl << q3 << std::endl;


    q1.setValueAsAxisDeg(1., 0., 0., 60.);
    q2.setValueAsAxisDeg(0., 1., 0., 60.);

    Matrix m1;
    Matrix m2;
    Matrix m3;

    q1.getValue(m1);
    q2.getValue(m2);

    q1.mult(q2);

    q1.getValue(m3);

    m1.mult(m2);

    std::cout << "\n mat(X/60 * Y/60): " << m3;
    std::cout << "\n : " << m1;

#if 1
    q1.setValueAsAxisRad(v1, 0.);
    q2.setValueAsAxisRad(v1, Pi);

    std::cout << "\n X:Pi: " << q2 << "\n";

    q1 = Quaternion::slerp(q1, q2, 0.5);

    std::cout <<  "\n slerp(X:0, X:Pi, .5) " << q1 << "\n";

    q1.setValue(Pi/2.0f, 0.f, 0.f);

    std::cout <<  "\n (Pi/2,0,0) " << q1 << "\n";

    Matrix m;

    q1.getValue(m);

    std::cout <<  "\n Matrix get " << m << "\n";

    q2.setValue(m);

    std::cout <<  "\n Matrix set " << q2 << "\n";

    fprintf(stderr, "\n %f %f %f %f\n",
            q2.getValues()[0],
            q2.getValues()[1],
            q2.getValues()[2],
            q2.getValues()[3]);

    q3 = q1.inverse();

    std::cout << "\n slerp^-1 " << q3 << "\n";


    q1.setValueAsAxisRad(1., 0., 0., Pi);
    q1.normalize();

    std::cout << "\n norm(X:Pi) " << q1 << "\n\n";

    v1.setValues(1., 0., 0.);

    q1.setValueAsAxisRad(0.f, 1.f, 0.f, Pi/2.f);

    q1.multVec(v1, v2);

    std::cout << v1 << " * Y:Pi/2 = " << v2 << "\n";

    q1.scaleAngle(2.);

    q1.multVec(v1, v2);

    std::cout << v1 << " * Y:Pi   = " << v2 << "\n\n";

    q1.setValueAsAxisRad(0.f, 1.f, 0.f, Pi/2.f);
    q2.setValueAsAxisRad(0.f, 0.f, 1.f, Pi/2.f);

    q3 = q1;
    q3.mult(q2);

    std::cout << " Y:Pi/2 * Z:Pi/2 = "<< q3 << "\n";

    q1.multVec(v1, v2);
    q2.multVec(v2, v3);
    q3.multVec(v1, v4);

    std::cout << "  X                    = " << v1 
              << "\n  Y:Pi/2 * X           = " << v2
              << "\n (Y:Pi/2 * X) * Z:Pi/2 = " << v3 
              << "\n (Y:Pi/2 * Z:Pi/2) * X = " << v4 << "\n\n";

    q1.setValueAsAxisRad(0.f, 1.f, 0.f, Pi/2.f);
    q2.setValueAsAxisRad(0.f, 0.f, 1.f, Pi/2.f);

    q3 = q1;
    q3.multLeft(q2);

    std::cout << " Z:Pi/2 * Y:Pi/2 = " << q3 << "\n";

    q1.multVec(v1, v2);
    q2.multVec(v2, v3);
    q3.multVec(v1, v4);

    std::cout << " X                     = " << v1 
              << "\n Y:Pi/2 * X            = " << v2
              << "\n (Y:Pi/2 * X) * Z:Pi/2 = " << v3 
              << "\n (Z:Pi/2 * Y:Pi/2) * X = " << v4 << "\n";

#endif
}

void matcheck( Matrix & mat, Pnt3f * vec, int nelem )
{
    Pnt3f p1,p2;
    int i;

    for ( i = 0; i < nelem; i++ )
    {
        mat.multFullMatrixPnt( vec[i],p2 );
        std::cout << "transforms " << vec[i] << " to " << p2 << std::endl;

    }

    std::cout << std::endl;
}

void matutilitytest( void )
{
    Matrix res;

    Pnt3f p1,p2;
    Vec3f v;

    Pnt3f testvec1[] = { Pnt3f( 0,0,0 ), Pnt3f( 1,0,0 ), Pnt3f( 2,0,0 ),
        Pnt3f( 0,1,0 ), Pnt3f( 0,0,1 ), Pnt3f( 1,1,1 )  };

    // check the lookat matrix

    MatrixLookAt( res,  0.f,0.f,0.f, 0.f,0.f,-1.f, 0.f,1.f,0.f );
    std::cout << "Lookat (0,0,0)-(0,0,-1)-(0,1,0): " << std::endl << res << std::endl;
    matcheck( res, testvec1, sizeof(testvec1)/sizeof(Pnt3f) );

    p1.setValues( 0,0,0);
    p2.setValues( 0,0,-1);
    v.setValues( 0,1,0);
    MatrixLookAt( res,  p1, p2, v );
    std::cout << "Lookat ("<<p1<<"):("<<p2<<"):("<<v<< "): " << std::endl << res << std::endl;
    matcheck( res, testvec1, sizeof(testvec1)/sizeof(Pnt3f) );

    MatrixLookAt( res,  0.f,0.f,2.f, 0.f,0.f,0.f, 0.f,1.f,0.f );
    std::cout << "Lookat (0,0,2)-(0,0,0)-(0,1,0): " << std::endl << res << std::endl;
    matcheck( res, testvec1, sizeof(testvec1)/sizeof(Pnt3f) );

    MatrixLookAt( res,  2.f,0.f,0.f, 0.f,0.f,0.f, 0.f,1.f,0.f );
    std::cout << "Lookat (2,0,0)-(0,0,0)-(0,1,0): " << std::endl << res << std::endl;
    matcheck( res, testvec1, sizeof(testvec1)/sizeof(Pnt3f) );

    if ( MatrixLookAt( res,  0.f,3.f,0.f, 0.f,0.f,0.f, 0.f,1.f,0.f ) )
    {
        std::cout << "MatrixLookAt failed: illegal conf correctly detected." << std::endl;
    }
    else
    {
        std::cout << "MatrixLookAt succeeded: illegal conf not detected!!!" << std::endl;
    }
    MatrixLookAt( res,  0.f,3.f,0.f, 0.f,0.f,0.f, 0.f,0.f,1.f );
    std::cout << "Lookat (0,3,0)-(0,1,0)-(0,0,1): " << std::endl << res << std::endl;
    matcheck( res, testvec1, sizeof(testvec1)/sizeof(Pnt3f) );

    p1.setValues( 1,1,1);
    p2.setValues( 0,0,0);
    v.setValues( 0,2,0);
    MatrixLookAt( res,  p1,p2,v );
    std::cout << "Lookat ("<<p1<<"):("<<p2<<"):("<<v<< "): " << std::endl << res << std::endl;
    matcheck( res, testvec1, sizeof(testvec1)/sizeof(Pnt3f) );

    // check window

    Pnt3f testvec2[] = { Pnt3f( 0,0,0 ), Pnt3f( 0,0,.5 ),
        Pnt3f( 0,0,1 ), Pnt3f( 0,0,-.5 ), Pnt3f( 0,0,-1 ), Pnt3f( 0,0,-1.5 ),
        Pnt3f( 0,0,-2 ), Pnt3f( .5,.5,-.5 ), Pnt3f( 1,1,-1 )  };

    MatrixFrustum( res, -1, 1, -1, 1, .1, 1 );
    std::cout << "Frustum (-1, 1, -1, 1, .1, 1): " << std::endl << res << std::endl;
    matcheck( res, testvec2, sizeof(testvec2)/sizeof(Pnt3f) );

    MatrixFrustum( res, 0, 1, 0, 1, 0.1, 1 );
    std::cout << "Frustum (0, 1, 0, 1, 0.1, 1): " << std::endl << res << std::endl;
    matcheck( res, testvec2, sizeof(testvec2)/sizeof(Pnt3f) );

    // check orthogonal projection

    MatrixOrthogonal( res, -1, 1, -1, 1, -1, 1 );
    std::cout << "Orthogonal (-1, 1, -1, 1, -1, 1): " << std::endl << res << std::endl;
    matcheck( res, testvec2, sizeof(testvec2)/sizeof(Pnt3f) );

    MatrixOrthogonal( res, -4, -1, 1, 3, -2, 2 );
    std::cout << "Orthogonal (-4, -1, 1, 3, -2, 2): " << std::endl << res << std::endl;
    matcheck( res, testvec2, sizeof(testvec2)/sizeof(Pnt3f) );

    // check perspective projection

    MatrixPerspective( res, 45, 1, 0.1, 1 );
    std::cout << "Perspective (45, 1, 0.1, 1): " << std::endl << res << std::endl;
    matcheck( res, testvec2, sizeof(testvec2)/sizeof(Pnt3f) );

    MatrixPerspective( res, 45, 2, 0.1, 1 );
    std::cout << "Perspective (45, 2, 0.1, 1): " << std::endl << res << std::endl;
    matcheck( res, testvec2, sizeof(testvec2)/sizeof(Pnt3f) );


    // TODO: check stereo projection

    // TODO: check general projection

}

void matNSMTest(void)
{


    Matrix m1,m2,m3;
    TransformationMatrix<Real64> md1,md2,md3;

        // first single precision floats


        std::cout << "====================================================" << std::endl
             << "  Testing the matrix functions sqrt, exp, and log" << std::endl
             << "====================================================" << std::endl
             << std::endl
             << "32 bit float types" << std::endl;

        m1.setIdentity();

        std::cout << std::endl << "Test matrix is identity!"  << std::endl;

        m1.sqrt(m2);
        m3.sqrtOf(m1);

        std::cout << "A.sqrt():" << std::endl << m2 << std::endl
             << "sqrtOf(A):" << std::endl << m3 << std::endl;

        m1.exp(m2);
        m3.expOf(m1);

        std::cout << "A.exp():" << std::endl << m2 << std::endl
             << "expOf(A):" << std::endl << m3 << std::endl;

        std::cout << "A.log():" << m1.log(m2) << std::endl << m2 << std::endl
             << "logOf(A):" << m3.logOf(m1) << std::endl << m3 << std::endl << std::endl;


        do
                for (int i=0;i<4;i++)
                        for (int j=0;j<4;j++)
                                m1[i][j] = Real32(rand())/Real32(RAND_MAX);
        while (m1.det() < 0);

        std::cout << std::endl << "Test matrix (A):" << std::endl << m1 << std::endl;

        m1.sqrt(m2);
        m3.sqrtOf(m1);

        std::cout << "A.sqrt():" << std::endl << m2 << std::endl
             << "sqrtOf(A):" << std::endl << m3 << std::endl;

        m2.mult(m2);
        m3.mult(m3);
        m2.addScaled(m1,-1.0);
        m3.addScaled(m1,-1.0);

        std::cout << "Accuracy:" << std::endl
             << "|A.sqrt()*A.sqrt()-A|:  " << m2.norm2() << std::endl
             << "|sqrtOf(A)*A.sqrtOf(A)-A|:  " << m3.norm2() << std::endl << std::endl;

        m1.exp(m2);
        m3.expOf(m1);

        std::cout << "A.exp():" << std::endl << m2 << std::endl
             << "expOf(A):" << std::endl << m3 << std::endl;

        std::cout << "A.log():" << m1.log(m2) << std::endl << m2 << std::endl
             << "logOf(A):" << m3.logOf(m1) << std::endl << m3 << std::endl;

        m1.exp(m2);
        m2.log(m3);
        m2.setValue(m3);
        m3.addScaled(m1,-1.0);

        std::cout << "A.exp.log():" << std::endl << m2 << std::endl
             << "|A.exp().log()-A|):  " << m3.norm2() << std::endl;


        // now double precision floats


        std::cout << std::endl
             << "64 bit float types (accuracies only)" << std::endl << std::endl;

        for (int i=0;i<4;i++)
                for (int j=0;j<4;j++)
                        md1[i][j] = Real64(m1[i][j]);


        md1.sqrt(md2);
        md3.sqrtOf(md1);
        md2.mult(md2);
        md3.mult(md3);
        md2.addScaled(md1,-1.0);
        md3.addScaled(md1,-1.0);

        std::cout << "|A.sqrt()*A.sqrt()-A|:  " << md2.norm2() << std::endl
             << "|sqrtOf(A)*A.sqrtOf(A)-A|:  " << md3.norm2() << std::endl;

        md1.exp(md2);
        md2.log(md3);
        md3.addScaled(md1,-1.0);

        std::cout << "|A.exp().log()-A|:  " << md3.norm2() << std::endl << std::endl;

}


// Instantiation Tests

Real32 nonFloatTest(void)
{
    Real32 rVal = osgsqrt(90.f);

    rVal = osgcos(90);
    rVal = osgsin(90);
    rVal = osgtan(90);

    rVal = osgacos(90);
    rVal = osgasin(90);
    rVal = osgatan(90);

    rVal = osgatan2(90, 90);

    rVal = osgdegree2rad(90);
    rVal = osgrad2degree(90);

    rVal = deg2rad(90);
    rVal = rad2deg(90);

    rVal = Real32(osgabs(90));
    rVal = osgpow(90, 10);
    rVal = osglog(90);
    rVal = osgexp(90);
    rVal = osgfloor(90);


    rVal = osgcos(90.f);
    rVal = osgsin(90.f);
    rVal = osgtan(90.f);

    rVal = osgacos(90.f);
    rVal = osgasin(90.f);
    rVal = osgatan(90.f);

    rVal = osgatan2(90.f, 90.f);

    rVal = osgdegree2rad(90.f);
    rVal = osgrad2degree(90.f);

    rVal = deg2rad(90.f);
    rVal = rad2deg(90.f);

    rVal = osgabs(90.f);
    rVal = osgpow(90.f, 10.f);
    rVal = osglog(90.f);
    rVal = osgexp(90.f);
    rVal = osgfloor(90.f);

    return rVal;
}


void vec2pnttest(void)
{
          Vec3f v (3.f, 3.f, 3.f);
    const Vec3f cv(2.f, 2.f, 2.f);

          Pnt3f  p(5.f, 5.f, 5.f);
    const Pnt3f cp(8.f, 8.f, 8.f);

    v = p.subZero();

    fprintf(stderr, "%f %f %f\n", v[0], v[1], v[2]);

    v = cp.subZero();

    fprintf(stderr, "%f %f %f\n", v[0], v[1], v[2]);

//    p = v;

//    p = cv;
}

void testfactor(void)
{
    Matrix m;

    Vec3f      t1(0,0,0);
    Vec3f      s1;
    Quaternion r1;

    Vec3f      sR;
    Vec3f      tR;
    Quaternion rR;
    Quaternion rsR;
 
    r1.setValueAsAxisDeg(1.f, 0.2f, 0.4f, 34.f);
    s1.setValues(1.1f, 1.5f, 1.7f);
    t1.setValues(10.f, 11.f, 12.f);

    m.setTransform(t1, r1, s1);

    std::cerr << "r1" << std::endl;
    std::cerr << r1 << std::endl;

    std::cerr << "t1" << std::endl;
    std::cerr << t1 << std::endl;

    std::cerr << "s1" << std::endl;
    std::cerr << s1 << std::endl;

    std::cerr << "Matrix" << std::endl;
    std::cerr << m << std::endl;
    
    m.getTransform(tR, rR, sR, rsR);

    std::cerr << "tR" << std::endl;
    std::cerr << tR << std::endl;

    std::cerr << "rR" << std::endl;
    std::cerr << rR << std::endl;

    std::cerr << "sR" << std::endl;
    std::cerr << sR << std::endl;

    std::cerr << "rsR" << std::endl;
    std::cerr << rsR << std::endl;

    m.getTransform(tR, rR, sR, rsR, t1);

    std::cerr << "tR" << std::endl;
    std::cerr << tR << std::endl;

    std::cerr << "rR" << std::endl;
    std::cerr << rR << std::endl;

    std::cerr << "sR" << std::endl;
    std::cerr << sR << std::endl;

    std::cerr << "rsR" << std::endl;
    std::cerr << rsR << std::endl;
}

void testnextpow2(void)
{
    {
    std::cerr << "osgnextpow2 UInt32" << std::endl;
    UInt32 a,b;
    
    b = 1;
    a = osgnextpower2(b);    
    std::cerr << "npow2(" << b << ") = " << a << std::endl;
    
    b = 0;
    a = osgnextpower2(b);    
    std::cerr << "npow2(" << b << ") = " << a << std::endl;
     
    b = 3;
    a = osgnextpower2(b);    
    std::cerr << "npow2(" << b << ") = " << a << std::endl;
    
    b = (1UL<<30)+1UL;
    a = osgnextpower2(b);    
    std::cerr << "npow2(" << b << ") = " << a << std::endl;
    
    b = (1UL<<31)+1UL;
    a = osgnextpower2(b);    
    std::cerr << "npow2(" << b << ") = " << a << std::endl;
    }
    {
    std::cerr << "osgnextpow2 Int32" << std::endl;
    Int32 a,b;
    
    b = 1;
    a = osgnextpower2(b);    
    std::cerr << "npow2(" << b << ") = " << a << std::endl;
    
    b = 0;
    a = osgnextpower2(b);    
    std::cerr << "npow2(" << b << ") = " << a << std::endl;
     
    b = 3;
    a = osgnextpower2(b);    
    std::cerr << "npow2(" << b << ") = " << a << std::endl;
    
    b = (1L<<29)+1L;
    a = osgnextpower2(b);    
    std::cerr << "npow2(" << b << ") = " << a << std::endl;
    
    b = (1L<<30)+1L;
    a = osgnextpower2(b);    
    std::cerr << "npow2(" << b << ") = " << a << std::endl;
    }
    {
    std::cerr << "osgnextpow2 UInt64" << std::endl;
    UInt64 a,b;
    
    b = 1;
    a = osgnextpower2(b);
    std::cerr << "npow2(" << b << ") = " << a << std::endl;

    b = 0;
    a = osgnextpower2(b);
    std::cerr << "npow2(" << b << ") = " << a << std::endl;

    b = 3;
    a = osgnextpower2(b);
    std::cerr << "npow2(" << b << ") = " << a << std::endl;

    b = (TypeTraits<UInt64>::One << 62) + TypeTraits<UInt64>::One;
    a = osgnextpower2(b);
    std::cerr << "npow2(" << b << ") = " << a << std::endl;

    b = (TypeTraits<UInt64>::One << 63) + TypeTraits<UInt64>::One;
    a = osgnextpower2(b);
    std::cerr << "npow2(" << b << ") = " << a << std::endl;
    }
    

}

void testVectorNewCtor()
{
    osg::Vec2f v2;
    osg::Pnt2f p2;
    osg::Vec3f v3;
    osg::Pnt3f p3;
    osg::Vec2d dv2;
    osg::Pnt2d dp2;
    osg::Vec3d dv3;
    osg::Pnt3d dp3;

    osg::Vec2f x1(v2);
    osg::Vec2f x2(p2);
    osg::Pnt2f x3(v2);
    osg::Pnt2f x4(p2);
    osg::Vec2f x5(v3);
    osg::Vec2f x6(p3);
    osg::Pnt2f x7(v3);
    osg::Pnt2f x8(p3);

    osg::Vec3f y1(v2);
    osg::Vec3f y2(p2);
    osg::Pnt3f y3(v2);
    osg::Pnt3f y4(p2);
    osg::Vec3f y5(v3);
    osg::Vec3f y6(p3);
    osg::Pnt3f y7(v3);
    osg::Pnt3f y8(p3);

    osg::Vec2d dx1(v2);
    osg::Vec2d dx2(p2);
    osg::Pnt2d dx3(v2);
    osg::Pnt2d dx4(p2);
    osg::Vec2d dx5(v3);
    osg::Vec2d dx6(p3);
    osg::Pnt2d dx7(v3);
    osg::Pnt2d dx8(p3);

    osg::Vec3d dy1(v2);
    osg::Vec3d dy2(p2);
    osg::Pnt3d dy3(v2);
    osg::Pnt3d dy4(p2);
    osg::Vec3d dy5(v3);
    osg::Vec3d dy6(p3);
    osg::Pnt3d dy7(v3);
    osg::Pnt3d dy8(p3);

    osg::Vec2f fx1(dv2);
    osg::Vec2f fx2(dp2);
    osg::Pnt2f fx3(dv2);
    osg::Pnt2f fx4(dp2);
    osg::Vec2f fx5(dv3);
    osg::Vec2f fx6(dp3);
    osg::Pnt2f fx7(dv3);
    osg::Pnt2f fx8(dp3);

    osg::Vec3f fy1(dv2);
    osg::Vec3f fy2(dp2);
    osg::Pnt3f fy3(dv2);
    osg::Pnt3f fy4(dp2);
    osg::Vec3f fy5(dv3);
    osg::Vec3f fy6(dp3);
    osg::Pnt3f fy7(dv3);
    osg::Pnt3f fy8(dp3);
}



int main(void)
{
    osgInit(0, NULL);

//    vectorTestConstructAndSetTest();
//    vectorMathTests();
//    matrixTest();
//      quattest();
//    matutilitytest();
//    matNSMTest();

//    nonFloatTest();

//    vec2pnttest();

//    testfactor();
      testnextpow2();

    return 0;
}

