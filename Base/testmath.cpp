

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

using OSG::Pnt3f;
 
using OSG::Matrix4f;
using OSG::Matrix;
using OSG::Quaternion;

using OSG::UInt32;

using OSG::Real32;

using OSG::osgcos;
using OSG::osgsin;
using OSG::Pi;

using OSG::MatrixOrthogonal;
using OSG::MatrixFrustum;
using OSG::MatrixPerspective;
using OSG::MatrixStereoPerspective;
using OSG::MatrixLookAt;
using OSG::MatrixProjection;

using OSG::osgInit;

template <class VecT>
void printVec(VecT &vec)
{
    cerr << vec << "\n";
}

Real32 pValsI[] = { 10., 11., 12., 13., 14 };

void vectorTestConstructAndSetTest(void)
{
    Real32 *pVals = pValsI;

    cerr << "vectorTestConstructAndSetTest\n";

    Vec2f v2f;
    Vec3f v3f;
    Vec4f v4f;

    Vec2f v2f2(2., 1.);
    Vec2f v2f3(3., 2., 1.);
    Vec2f v2f4(4., 3., 2., 1.);

    Vec3f v3f2(2., 1.);
    Vec3f v3f3(3., 2., 1.);
    Vec3f v3f4(4., 3., 2., 1.);

    Vec4f v4f2(2., 1.);
    Vec4f v4f3(3., 2., 1.);
    Vec4f v4f4(4., 3., 2., 1.);

    cerr << "construct (void);\n";

    printVec(v2f);
    printVec(v3f);
    printVec(v4f);

    cerr << "construct (2 val);\n";

    printVec(v2f2);
    printVec(v3f2);
    printVec(v4f2);

    cerr << "construct (3 val);\n";

    printVec(v2f3);
    printVec(v3f3);
    printVec(v4f3);

    cerr << "construct (4 val);\n";
        
    printVec(v2f4);
    printVec(v3f4);
    printVec(v4f4);


    Vec2f v2f5(v2f4);
    Vec2f v2f6(v3f4);
    Vec2f v2f7(v4f4);

    Vec3f v3f5(v2f4);
    Vec3f v3f6(v3f4);
    Vec3f v3f7(v4f4);

    Vec4f v4f5(v2f4);
    Vec4f v4f6(v3f4);
    Vec4f v4f7(v4f4);

    cerr << "construct (cp size 2) " << v2f4 << "\n";
    printVec(v2f5);
    printVec(v3f5);
    printVec(v4f5);

    cerr << "construct (cp size 3) " << v3f4 << "\n";
    printVec(v2f6);
    printVec(v3f6);
    printVec(v4f6);

    cerr << "construct (cp size 4) " << v4f4 << "\n";
    printVec(v2f7);
    printVec(v3f7);
    printVec(v4f7);

    Vec2f v2f8(pVals);
    Vec3f v3f8(pVals);
    Vec4f v4f8(pVals);

    cerr << "construct (array)\n";
    printVec(v2f8);
    printVec(v3f8);
    printVec(v4f8);    

    v2f8.setNull();
    v3f8.setNull();
    v4f8.setNull();

    cerr << "set Null\n";
    printVec(v2f8);
    printVec(v3f8);
    printVec(v4f8);    

    v2f8.setValues( 20.f, 30.f);
//    v3f8.setValue(20., 30.);
//    v4f8.setValue(20., 30.);

    cerr << "set 2 vals\n";

    printVec(v2f8);
    printVec(v3f8);
    printVec(v4f8);    

//    v2f8.setValue(20., 30., 40.);
    v3f8.setValues(20., 30., 40.);
//    v4f8.setValue(20., 30., 40.);

    cerr << "set 3 vals\n";

    printVec(v2f8);
    printVec(v3f8);
    printVec(v4f8);    

//    v2f8.setValue(20., 30., 40., 50.);
//    v3f8.setValue(20., 30., 40., 50.);
    v4f8.setValues(20., 30., 40., 50.);

    cerr << "set 4 vals\n";

    printVec(v2f8);
    printVec(v3f8);
    printVec(v4f8);    


//    v2f8.setValue(v2f4);
    v3f8.setValue(v2f4);
    v4f8.setValue(v2f4);

    cerr << "set vec size 2 " << v2f4 << "\n";;
    printVec(v2f8);
    printVec(v3f8);
    printVec(v4f8);    

//    v2f8.setValue(20., 30., 40., 50.);
//    v3f8.setValues(20., 30., 40., 50.);
//    v4f8.setValue(20., 30., 40., 50.);

    v2f8.setValue(v3f4);
//    v3f8.setValue(v3f4);
    v4f8.setValue(v3f4);

    cerr << "set vec size 3 " << v3f4 << "\n";
    printVec(v2f8);
    printVec(v3f8);
    printVec(v4f8);    
    
//    v2f8.setValue(20., 30., 40., 50.);
//    v3f8.setValues(20., 30., 40., 50.);
//    v4f8.setValue(20., 30., 40., 50.);

    v2f8.setValue(v4f4);
    v3f8.setValue(v4f4);
//    v4f8.setValue(v4f4);

    cerr << "set vec size 4 " << v4f4 << "\n";

    printVec(v2f8);
    printVec(v3f8);
    printVec(v4f8);        


//    v2f8.setValue(20., 30., 40., 50.);
//    v3f8.setValues(20., 30., 40., 50.);
//    v4f8.setValue(20., 30., 40., 50.);

    v2f8.setValue((char *) NULL);
    v3f8.setValue((char *) NULL);
    v4f8.setValue((char *) NULL);

    cerr << "set vec from string NULL \n";

    printVec(v2f8);
    printVec(v3f8);
    printVec(v4f8);        


//    v2f8.setValue(20., 30., 40., 50.);
//    v3f8.setValues(20., 30., 40., 50.);
//    v4f8.setValue(20., 30., 40., 50.);

    v2f8.setValue("");
    v3f8.setValue("");
    v4f8.setValue("");

    cerr << "set vec from string \"\" \n";

    printVec(v2f8);
    printVec(v3f8);
    printVec(v4f8);        



    v2f8.setNull();
    v3f8.setNull();
    v4f8.setNull();

    v2f8.setValue("1");
    v3f8.setValue("1 ");
    v4f8.setValue("1");

    cerr << "set vec from string 1 \n";

    printVec(v2f8);
    printVec(v3f8);
    printVec(v4f8);        


    
    v2f8.setNull();
    v3f8.setNull();
    v4f8.setNull();

    v2f8.setValue("1 2");
    v3f8.setValue("1 2");
    v4f8.setValue("1 2 ");

    cerr << "set vec from string 2\n";

    printVec(v2f8);
    printVec(v3f8);
    printVec(v4f8);        



    v2f8.setNull();
    v3f8.setNull();
    v4f8.setNull();

    v2f8.setValue("1 2 3 ");
    v3f8.setValue("1 2 3");
    v4f8.setValue("1 2 3");

    cerr << "set vec from string 3\n";

    printVec(v2f8);
    printVec(v3f8);
    printVec(v4f8);        



    v2f8.setNull();
    v3f8.setNull();
    v4f8.setNull();

    v2f8.setValue("1 2 3 4");
    v3f8.setValue("1 2 3 4 ");
    v4f8.setValue("1 2 3 4");

    cerr << "set vec from string 4\n";

    printVec(v2f8);
    printVec(v3f8);
    printVec(v4f8);        


    v2f8.setNull();
    v3f8.setNull();
    v4f8.setNull();

    v2f8.setValue("1 2 3 4 5 6");
    v3f8.setValue("1 2 3 4 5 6");
    v4f8.setValue("1 2 3 4 5 6");

    cerr << "set vec from string 4\n";

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

    cout << v2f1 << " : iz : " << v2f1.isZero() << "\n";
    cout << v3f1 << " : iz : " << v3f1.isZero() << "\n";
    cout << v4f1 << " : iz : " << v4f1.isZero() << "\n";

    cout << v2f2 << " : iz : " << v2f2.isZero() << "\n";
    cout << v3f2 << " : iz : " << v3f2.isZero() << "\n";
    cout << v4f2 << " : iz : " << v4f2.isZero() << "\n";

    v2f1.setValues(3., 4.);
    v3f1.setValues(3., 4., 5.);
    v4f1.setValues(3., 4., 5., 6.);

    cout << v2f1 << " l : " << v2f1.length() << " (5)\n";
    cout << v3f1 << " l : " << v3f1.length() << " (7.07106)\n";
    cout << v4f1 << " l : " << v4f1.length() << " (9.27361)\n";

    v2f1.normalize();
    v3f1.normalize();
    v4f1.normalize();

    cout << v2f1 << " l : " << v2f1.length() << " (1)\n";
    cout << v3f1 << " l : " << v3f1.length() << " (1)\n";
    cout << v4f1 << " l : " << v4f1.length() << " (1)\n";

    v2f1.setValues(0., 1.);
    v3f1.setValues(1., 0., 0.);
    v4f1.setValues(0., 0., 1., 6.);

    v2f2.setValues(1., 0.);
    v3f2.setValues(0., 1., 0.);
    v4f2.setValues(1., 0., 0., 10.);

    cout << v2f1.cross(v2f2) << "\n";
    cout << v3f1.cross(v3f2) << "\n";
    cout << v4f1.cross(v4f2) << "\n";

    v2f1.crossThis(v2f2);
    v3f1.crossThis(v3f2);
    v4f1.crossThis(v4f2);

    cout << v2f1 << "\n";
    cout << v3f1 << "\n";
    cout << v4f1 << "\n";

    v2f1.setValues(1., 2.);
    v3f1.setValues(1., 2., 3.);
    v4f1.setValues(1., 2., 3., 4.);

    v2f2.setValues(10., 20.);
    v3f2.setValues(10., 20., 30.);
    v4f2.setValues(10., 20., 30., 40.);
   
    cout << v2f1.dot(v2f2) << " ( 50) \n";
    cout << v3f1.dot(v3f2) << " (140)\n";
    cout << v4f1.dot(v4f2) << " (300)\n";

    v2f1.negate();
    v3f1.negate();
    v4f1.negate();

    cout << v2f1 << " \n";
    cout << v3f1 << " \n";
    cout << v4f1 << " \n";

    cout << -v2f1 << " \n";
    cout << -v3f1 << " \n";
    cout << -v4f1 << " \n";

    v2f1.setValues(1., 1.);
    v3f1.setValues(3., 3., 3.);
    v4f1.setValues(1., 2., 3., 4.);

    cout << v2f1.equals(v2f2, 0.5) << "\n";
    cout << v3f1.equals(v3f2, 0.5) << "\n";
    cout << v4f1.equals(v4f2, 0.5) << "\n";

    v2f2.setValues(1.3, 0.9);
    v3f2.setValues(3., 3., 3.6);
    v4f2.setValues(1., 2., 3, 4.);

    cout << v2f1.equals(v2f2, 0.5) << "\n";
    cout << v3f1.equals(v3f2, 0.5) << "\n";
    cout << v4f1.equals(v4f2, 0.5) << "\n";

    cout << (v2f1 == v2f2) << "\n";
    cout << (v3f1 == v3f2) << "\n";
    cout << (v4f1 == v4f2) << "\n";

    cout << (v2f1 != v2f2) << "\n";
    cout << (v3f1 != v3f2) << "\n";
    cout << (v4f1 != v4f2) << "\n";

    v2f1.setValues(1., 2.);
    v3f1.setValues(1., 2., 3.);
    v4f1.setValues(1., 2., 3., 4.);

    v2f2.setValues(10., 20.);
    v3f2.setValues(10., 20., 30.);
    v4f2.setValues(10., 20., 30., 40.);

    v2f1 += v2f2;
    v3f1 += v3f2;
    v4f1 += v4f2;

    cout << v2f1 << " \n";
    cout << v3f1 << " \n";
    cout << v4f1 << " \n";

    v2f1 -= v2f2;
    v3f1 -= v3f2;
    v4f1 -= v4f2;

    cout << v2f1 << " \n";
    cout << v3f1 << " \n";
    cout << v4f1 << " \n";

    v2f1 *= 4.;
    v3f1 *= 4.;
    v4f1 *= 4.;

    cout << v2f1 << " \n";
    cout << v3f1 << " \n";
    cout << v4f1 << " \n";

    v2f1 /= 2.;
    v3f1 /= 2.;
    v4f1 /= 2.;

    cout << v2f1 << " \n";
    cout << v3f1 << " \n";
    cout << v4f1 << " \n";

    fprintf(stderr, "%f %f %f %f\n", v4f1[0], v4f1[1], v4f1[2], v4f1[3]);
    fprintf(stderr, "%f %f %f %f\n", 
            v4f1.getValueRef()[0], v4f1.getValueRef()[1], 
            v4f1.getValueRef()[2], v4f1.getValueRef()[3]);

    cout << v2f1 << " \n";
    cout << v3f1 << " \n";
    cout << v4f1 << " \n";

    cout << v2f2 << " \n";
    cout << v3f2 << " \n";
    cout << v4f2 << " \n";

    v2f1 = v2f2;
    v3f1 = v3f2;
    v4f1 = v4f2;

    cout << v2f1 << " \n";
    cout << v3f1 << " \n";
    cout << v4f1 << " \n";

    cout << v2f2 << " \n";
    cout << v3f2 << " \n";
    cout << v4f2 << " \n";

    v2f1 = v2f2 * 2.f;
    v3f1 = v3f2 * 2.f;
    v4f1 = v4f2 * 2.f;

    cout << v2f1 << " \n";
    cout << v3f1 << " \n";
    cout << v4f1 << " \n";

    v2f1 = 0.5f * v2f2;
    v3f1 = 0.5f * v3f2;
    v4f1 = 0.5f * v4f2;

    cout << v2f1 << " \n";
    cout << v3f1 << " \n";
    cout << v4f1 << " \n";

    v2f1 = v2f2 + v2f2;
    v3f1 = v3f2 + v3f2;
    v4f1 = v4f2 + v4f2;

    cout << v2f1 << " \n";
    cout << v3f1 << " \n";
    cout << v4f1 << " \n";

    v2f1 = v2f2 - v2f1;
    v3f1 = v3f2 - v3f1;
    v4f1 = v4f2 - v4f1;

    cout << v2f1 << " \n";
    cout << v3f1 << " \n";
    cout << v4f1 << " \n";

    cout << v2f2 << " \n";
    cout << v3f2 << " \n";
    cout << v4f2 << " \n";
}

void matrixTest(void)
{
    Vec3f pVec3Array[4];

    pVec3Array[0].setValues(11., 12., 13.);
    pVec3Array[1].setValues(21., 22., 23.);
    pVec3Array[2].setValues(31., 32., 33.);
    pVec3Array[3].setValues(41., 42., 43.);

    Vec4f pVec4Array[4];

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

    cout << endl << "Matrix math test " << endl;
    cout << endl << "========================================" << endl << endl;

    cout << "Identity               : " << endl 
         << Matrix::identity()   << endl;

    cout << endl << "========================================" << endl << endl;

    cout << "Default constructor    : " << endl << m1 << endl;
    cout << "3 vector3f constructor : " << endl << m2 << endl;
    cout << "4 vector3f constructor : " << endl << m3 << endl;
    cout << "Copy consructor        : " << endl << m4 << endl;
    cout << "16f values construtor  : " << endl << m5 << endl;
    
    cout << endl << "========================================" << endl << endl;
    

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
    m7.setValue(pVec3Array);

    cout << "Set      matrix  : " << endl << m4 << endl;
    cout << "Set 3 3f vectors : " << endl << m1 << endl;
    cout << "Set 4 3f vectors : " << endl << m2 << endl;
    cout << "Set 16 f values  : " << endl << m3 << endl;
    cout << "Set valT array   : " << endl << m5 << endl;
    cout << "Set val array    : " << endl << m8 << endl;
    cout << "Set vec4 array   : " << endl << m6 << endl;
    cout << "Set vec3 array   : " << endl << m7 << endl;

    cout << endl << "========================================" << endl << endl;

    cout << "Get Values : " << endl;

    for(UInt32 i = 0; i < 4; i++)
    {
        for(UInt32 j = 0; j < 4; j++)
        {
            fprintf(stderr, "% 5.3f ", (m5.getValues())[j * 4 + i]);
        }
        
        fprintf(stderr, "\n");
    }

    cout << endl << "========================================" << endl << endl;

    m1.setIdentity();
    m1.setScale(10.);
    
    m2.setIdentity();
    m2.setScale(v3);
    
    m3.setIdentity();
    m3.setTranslate(v4);

    m4.setIdentity();
    m4.setTranslate(41., 42., 43.);

    cout << "Set scale val       : " << endl << m1 << endl;
    cout << "Set scale vec3f     : " << endl << m2 << endl;
    cout << "Set translate val   : " << endl << m4 << endl;
    cout << "Set translate vec3f : " << endl << m3 << endl;

    cout << endl << "========================================" << endl << endl;

    q1.setValueAsAxis(1., 0., 0., 60.);
    q2.setValueAsAxis(0., 1., 0., 60.);
    q3.setValueAsAxis(0., 0., 1., 60.);


    m1.setRotate(q1);
    m2.setRotate(q2);
    m3.setRotate(q3);
   
    cout << "Set rotate X/60     : " << endl << m1 << endl;
    cout << "Set rotate Y/60     : " << endl << m2 << endl;
    cout << "Set rotate Z/60     : " << endl << m3 << endl;
    
    cout << endl << "========================================" << endl << endl;

    m1.setIdentity();
    m1.setTranslate(41., 42., 43);

    cout << m1 << endl;

    m2.setIdentity();
    m2.setRotate(q1);

    m1.mult(m2);

    cout << "mult trans * rot : " << endl << m1 << endl;
    cout << endl << "========================================" << endl << endl;

    m1.setIdentity();
    m1.setTranslate(41., 42., 43);

    m2.setIdentity();
    m2.setRotate(q1);

    m1.multLeft(m2);

    cout << "multLeft rot * trans : " << endl << m1 << endl;
    cout << endl << "========================================" << endl << endl;

    m1.setIdentity();
    m1.setTranslate(41., 42., 43);

    m2.setIdentity();
    m2.setRotate(q1);

    m1.mult(m2);

    m4 = m1;

    cout << m1.inverse(m3) << endl;
    cout << "Inverse trans * rot : " << endl << m3 << endl;

    cout << m3.invertFrom(m1) << endl;
    cout << "InverseFrom trans * rot : " << endl << m3 << endl;
 
    m3 = m1;

    cout << m3.invert();
    cout << "Invert trans * rot : " << endl << m3 << endl;

    m4.mult(m3);
    cout << "Invert m-1 * m : " << endl << m4 << endl;

    m4 = m1;
    m3.mult(m4);

    cout << "Invert m * m-1 : " << endl << m3 << endl;

    cout << endl << "========================================" << endl << endl;


    m1.setIdentity();
    m1.setTranslate(41., 42., 43);

    m2.setIdentity();
    m2.setRotate(q1);

    m1.mult(m2);

    m4 = m1;

    cout << m1.inverse3(m3) << endl;
    cout << "Inverse trans * rot : " << endl << m3 << endl;

    cout << m3.invertFrom3(m1) << endl;
    cout << "InverseFrom trans * rot : " << endl << m3 << endl;
 
    m3 = m1;

    cout << m3.invert3() << endl;
    cout << "Invert trans * rot : " << endl << m3 << endl;

    m4.mult(m3);
    cout << "Invert m * m-1 : " << endl << m4 << endl;

    m4 = m1;
    m3.mult(m4);

    cout << "Invert m-1 * m : " << endl << m3 << endl;

    cout << endl << "========================================" << endl << endl;

    m1.setIdentity();
    m1.setTranslate(41., 42., 43);

    m2.setIdentity();
    m2.setRotate(q1);

    m1.mult(m2);

    v1.setValues(0., 0., 1.);
    p1.setValues(0., 1., 0.);    

    m1.transform(v1, v2);
    m1.transform(p1, p2);

    cout << "Transform P : " << endl << p2 << endl;
    cout << "Transform V : " << endl << v2 << endl;

    cout << endl << "========================================" << endl << endl;

    m1.setIdentity();
    m2.setIdentity();
    m3.setIdentity();

    v1.setValues(41., 42., 43);
    q1.setValueAsAxis(1., 0., 1., 60.);
    v2.setValues(5., 6., 7.);

    m1.setTranslate(v1);
    m2.setRotate(q1);
    m3.setScale(v2);

    m4 = m1;

    m4.mult(m2);
    m4.mult(m3);

    m5.setTransform(v1, q1, v2);

    cout << "Set Transform t*r*s : " << endl << m4 << endl;
    cout << "Set Transform trs   : " << endl << m5 << endl;

    cout << endl << "========================================" << endl << endl;


    m1.setIdentity();
    m2.setIdentity();
    m3.setIdentity();
    m4.setIdentity();
    m5.setIdentity();
    m6.setIdentity();
    m7.setIdentity();

    v1.setValues(41., 42., 43);
    q1.setValueAsAxis(1., 0., 1., 60.);
    v2.setValues(10., 10., 10.);
    q2.setValueAsAxis(0., 1., 0., 90.);
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

    cout << "Set Transform t*r*s*so : " << endl << m8 << endl;
    cout << "Set Transform t r s so : " << endl << m9 << endl;

    cout << endl << "========================================" << endl << endl;

    m1.setIdentity();
    m2.setIdentity();
    m3.setIdentity();
    m4.setIdentity();
    m5.setIdentity();
    m6.setIdentity();
    m7.setIdentity();

    v1.setValues(41., 42., 43);
    q1.setValueAsAxis(1., 0., 1., 60.);
    v2.setValues(11., 12., 13.);
    q2.setValueAsAxis(0., 1., 0., 90.);
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

    cout << "Set Transform t*r*s*so*c : " << endl << m8 << endl;
    cout << "Set Transform t r s so c : " << endl << m9 << endl;
}


void quattest(void)
{
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

    v1.setValues(1., 0., 0.);

    v2.setValues(1., 0., 0.);
    v3.setValues(0., 1., 0.);

    Quaternion q1;
    Quaternion q2(0., 0., 1., 90.);
    Quaternion q3(q2);

    Quaternion q4(v1, 90.);
    Quaternion q5(v2, v3);

    Quaternion q6;
    Quaternion q7;
    Quaternion q8;
    Quaternion q9;
    

    cout << endl << "Quaternion math test " << endl;
    cout << endl << "========================================" << endl << endl;
    
    cout << "Default Constructor         : " << endl << q1 << endl;
    cout << "Construtor Axis3f, Angle    : " << endl << q2 << endl;
    cout << "Copy Constructor            : " << endl << q3 << endl;
    cout << "Constructor AxisVec3f Angle : " << endl << q4 << endl;
    cout << "Constructor FromV3f ToV3f   : " << endl << q5 << endl;

    cout << endl << "========================================" << endl << endl;


    q1.setIdentity();

    q2.setIdentity();
    q2.setValueAsAxis(axisArray);

    q3.setIdentity();
    q3.setValueAsQuat(quatArray);

    q4.setIdentity();
    q4.setValueAsAxis(0., 1., 0., 180.);

    q5.setIdentity();
    q5.setValueAsQuat(0., 0.707, 0., 0.707);
    
    q6.setIdentity();
    q6.setValue(v1, 60.);

    q7.setIdentity();
    q7.setValue(v2, v3);

    q8.setIdentity();
    q8.setValue("0.0 1.0 0.0 90.");

    cout << "Set Identity                : " << endl << q1 << endl;
    cout << "Set from axis array         : " << endl << q2 << endl;
    cout << "Set from quat array         : " << endl << q3 << endl;
    cout << "Set from value axis         : " << endl << q4 << endl;
    cout << "Set from value quat         : " << endl << q5 << endl;
    cout << "Set from axis angle         : " << endl << q6 << endl;
    cout << "Set from from, to pair      : " << endl << q7 << endl;
    cout << "Set from string             : " << endl << q8 << endl;

    cout << endl << "========================================" << endl << endl;


    q1.setValueAsAxis(1., 0., 0., 60.);
    q2.setValueAsAxis(0., 1., 0., 60.);
    q3.setValueAsAxis(0., 0., 1., 60.);

    cout << "Set from axis X/60          : " << endl << q1 << endl;
    cout << "Set from axis Y/60          : " << endl << q2 << endl;
    cout << "Set from axis Z/60          : " << endl << q3 << endl;
    cout << endl;

    q4.setValue(rotmatInX);
    q5.setValue(rotmatInY);
    q6.setValue(rotmatInZ);

    cout << "Set from matrix X/60        : " << endl << q4 << endl;
    cout << "Set from matrix Y/60        : " << endl << q5 << endl;
    cout << "Set from matrix Z/60        : " << endl << q6 << endl;
    cout << endl;

    q1.getValue(rotmatOutX);
    q2.getValue(rotmatOutY);
    q3.getValue(rotmatOutZ);

    cout << "Get matrix X/60        : " << endl << rotmatOutX << endl;
    cout << "Get matrix Y/60        : " << endl << rotmatOutY << endl;
    cout << "Get matrix Z/60        : " << endl << rotmatOutZ << endl;
    cout << endl;

    cout << endl << "========================================" << endl << endl;

    q1.setValueAsQuat(1., 2., 3., 4.); // Just for testing

    printf("Get val pointer\n");

    for(UInt32 i = 0; i < 4; i++)
    {
        fprintf(stderr, "%5.3f ", q1.getValues()[i]);
    }
    fprintf(stderr, "\n");

    cout << endl << "========================================" << endl << endl;

    q2.getValueAsAxis(x, y, z, w);
    
    printf("Get val as axis\n");
    printf("%5.3f %5.3f %5.3f %5.3f\n", x, y, z, w);

    q1.getValueAsQuat(x, y, z, w);
    
    printf("Get val as quat\n");
    printf("%5.3f %5.3f %5.3f %5.3f\n", x, y, z, w);

    cout << endl << "========================================" << endl << endl;

    q2.getValue(v1, w);

    printf("Get val as vec/angle\n");
    cout << v1;
    printf(" %5.3f\n", w);

    cout << endl << "========================================" << endl << endl;

    printf("Get val as single Real32 vals\n");
    printf("%5.3f %5.3f %5.3f %5.3f\n", q1.x(), q1.y(), q1.z(), q1.w());

    cout << endl << "========================================" << endl << endl;

    printf("length\n%5.3f", q1.length());
    
    q1.normalize();
    printf("norm\n%5.3f\n", q1.length());

    cout << endl << "========================================" << endl << endl;

    q2.invert();
    q3 = q2.inverse();

    cout << "Invert  :" << endl << q2 << endl;
    cout << "Inverse :" << endl << q3 << endl;


    q1.setValueAsAxis(1., 0., 0., 60.);
    q2.setValueAsAxis(0., 1., 0., 60.);

    Matrix m1;
    Matrix m2;
    Matrix m3;

    q1.getValue(m1);
    q2.getValue(m2);

    q1.mult(q2);

    q1.getValue(m3);

    m1.mult(m2);

    cout << m3;
    cout << m1;

    return;

#if 0
    q1.setValue(v1, 0.);
    q2.setValue(v1, Pi);

    cout << "\n" << q2 << "\n";

    q1 = Quaternion::slerp(q1, q2, 0.5);

    cout <<  "\n" << q1 << "\n";

    q1.setValue(Pi/2., 0., 0.);

    cout <<  "\n" << q1 << "\n";

    Matrix m;

    q1.getValue(m);

    cout <<  "\n" << m << "\n";
    
    q2.setValue(m);

    cout <<  "\n" << q2 << "\n";

    fprintf(stderr, "\n %f %f %f %f\n", 
            q2.getValues()[0],
            q2.getValues()[1],
            q2.getValues()[2],
            q2.getValues()[3]);

    q3 = q1.inverse();

    cout << q3 << "\n";


    q1.setValue(1., 0., 0., Pi);
    q1.normalize();

    cout << q1 << "\n";

    v1.setValues(1., 0., 0.);
    
    q1.setValue(0., 1., 0., Pi/2.);

    q1.multVec(v1, v2);

    cout << v1 << "\n" << v2 << "\n";

    q1.scaleAngle(2.);

    q1.transform(v1, v2);
    
    cout << v1 << "\n" << v2 << "\n";

    q1.setValue(0., 1., 0., Pi/2.);
    q2.setValue(0., 0., 1., Pi/2.);

    q3 = q1;
    q3.mult(q2);

    cout << q3 << "\n";

    q1.multVec(v1, v2);
    q2.multVec(v2, v3);
    q3.multVec(v1, v4);

    cout << "\n" << v1 << "\n" << v2 << "\n" << v3 << "\n" << v4 << "\n";

    q1.setValue(0., 1., 0., Pi/2.);
    q2.setValue(0., 0., 1., Pi/2.);

    q3 = q1;
    q3.multLeft(q2);

    cout << q3 << "\n";

    q1.multVec(v1, v2);
    q2.multVec(v2, v3);
    q3.multVec(v1, v4);

    cout << "\n" << v1 << "\n" << v2 << "\n" << v3 << "\n" << v4 << "\n";
#endif
}

void matcheck( Matrix & mat, Pnt3f * vec, int nelem )
{
	Pnt3f p1,p2;
	int i;
	
	for ( i = 0; i < nelem; i++ )
	{
		mat.multFullMatrixPnt( vec[i],p2 );
		cout << "transforms " << vec[i] << " to " << p2 << endl;
		
	}

	cout << endl;
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
    cout << "Lookat (0,0,0)-(0,0,-1)-(0,1,0): " << endl << res << endl;
	matcheck( res, testvec1, sizeof(testvec1)/sizeof(Pnt3f) );

	p1.setValues( 0,0,0);
	p2.setValues( 0,0,-1);
	v.setValues( 0,1,0);
	MatrixLookAt( res,  p1, p2, v );	
    cout << "Lookat ("<<p1<<"):("<<p2<<"):("<<v<< "): " << endl << res << endl;
	matcheck( res, testvec1, sizeof(testvec1)/sizeof(Pnt3f) );

	MatrixLookAt( res,  0.f,0.f,2.f, 0.f,0.f,0.f, 0.f,1.f,0.f );	
    cout << "Lookat (0,0,2)-(0,0,0)-(0,1,0): " << endl << res << endl;
	matcheck( res, testvec1, sizeof(testvec1)/sizeof(Pnt3f) );

	MatrixLookAt( res,  2.f,0.f,0.f, 0.f,0.f,0.f, 0.f,1.f,0.f );	
    cout << "Lookat (2,0,0)-(0,0,0)-(0,1,0): " << endl << res << endl;
	matcheck( res, testvec1, sizeof(testvec1)/sizeof(Pnt3f) );

	if ( MatrixLookAt( res,  0.f,3.f,0.f, 0.f,0.f,0.f, 0.f,1.f,0.f ) )
	{
		cout << "MatrixLookAt failed: illegal conf correctly detected." << endl;
	}
	else	
	{
		cout << "MatrixLookAt succeeded: illegal conf not detected!!!" << endl;
	}
	MatrixLookAt( res,  0.f,3.f,0.f, 0.f,0.f,0.f, 0.f,0.f,1.f );
    cout << "Lookat (0,3,0)-(0,1,0)-(0,0,1): " << endl << res << endl;
	matcheck( res, testvec1, sizeof(testvec1)/sizeof(Pnt3f) );

	p1.setValues( 1,1,1);
	p2.setValues( 0,0,0);
	v.setValues( 0,2,0);
	MatrixLookAt( res,  p1,p2,v );	
    cout << "Lookat ("<<p1<<"):("<<p2<<"):("<<v<< "): " << endl << res << endl;
	matcheck( res, testvec1, sizeof(testvec1)/sizeof(Pnt3f) );

	// check window

	Pnt3f testvec2[] = { Pnt3f( 0,0,0 ), Pnt3f( 0,0,.5 ), 
		Pnt3f( 0,0,1 ), Pnt3f( 0,0,-.5 ), Pnt3f( 0,0,-1 ), Pnt3f( 0,0,-1.5 ), 
		Pnt3f( 0,0,-2 ), Pnt3f( .5,.5,-.5 ), Pnt3f( 1,1,-1 )  };

	MatrixFrustum( res, -1, 1, -1, 1, .1, 1 );
    cout << "Frustum (-1, 1, -1, 1, .1, 1): " << endl << res << endl;
	matcheck( res, testvec2, sizeof(testvec2)/sizeof(Pnt3f) );

	MatrixFrustum( res, 0, 1, 0, 1, 0.1, 1 );
    cout << "Frustum (0, 1, 0, 1, 0.1, 1): " << endl << res << endl;
	matcheck( res, testvec2, sizeof(testvec2)/sizeof(Pnt3f) );
	
	// check orthogonal projection

	MatrixOrthogonal( res, -1, 1, -1, 1, -1, 1 );
    cout << "Orthogonal (-1, 1, -1, 1, -1, 1): " << endl << res << endl;
	matcheck( res, testvec2, sizeof(testvec2)/sizeof(Pnt3f) );

	MatrixOrthogonal( res, -4, -1, 1, 3, -2, 2 );
    cout << "Orthogonal (-4, -1, 1, 3, -2, 2): " << endl << res << endl;
	matcheck( res, testvec2, sizeof(testvec2)/sizeof(Pnt3f) );

	// check perspective projection

	MatrixPerspective( res, 45, 1, 0.1, 1 );
    cout << "Perspective (45, 1, 0.1, 1): " << endl << res << endl;
	matcheck( res, testvec2, sizeof(testvec2)/sizeof(Pnt3f) );

	MatrixPerspective( res, 45, 2, 0.1, 1 );
    cout << "Perspective (45, 2, 0.1, 1): " << endl << res << endl;
	matcheck( res, testvec2, sizeof(testvec2)/sizeof(Pnt3f) );
	

	// TODO: check stereo projection

	// TODO: check general projection
	
}

void main(void)
{
    osgInit(0, NULL);

//    vectorTestConstructAndSetTest();
    vectorMathTests();
    matrixTest();
   quattest();
//	matutilitytest();
}
