// Little test for matrxi compose/decompose...

#include <stdio.h>

#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>
#include <OSGVector.h>
#include <OSGQuaternion.h>
#include <OSGMatrix.h>

OSG_USING_NAMESPACE

bool test(Vec3f trans, Quaternion rotation, Vec3f scale, 
          Quaternion scaleOrientation, Vec3f center)
{
    Matrix m1;

    m1.setTransform(trans,rotation,scale,scaleOrientation,center);

    Vec3f       descale;
    Quaternion  descaleOrientation,derotation;
    Vec3f       detrans,decenter(0,0,0);

    m1.getTransform(detrans,derotation,descale,descaleOrientation,decenter);

    Matrix m2;

    m2.setTransform(detrans,derotation,descale,descaleOrientation,decenter);

    Vec3f       descale2;
    Quaternion  descaleOrientation2,derotation2;
    Vec3f       detrans2,decenter2(0,0,0);

    m2.getTransform(detrans2,derotation2,descale2,descaleOrientation2,
                    decenter2);

    if(!m1.equals(m2, 1e-5))
    {
        std::cerr << "Matrix 1: " << m1 << std::endl;
        std::cerr << "Matrix 2: " << m2 << std::endl;
        std::cerr << "Scale: "<< scale << " : " << descale << std::endl;
        std::cerr << "ScaleOrientation: "<< scaleOrientation << " : " 
                  << descaleOrientation << std::endl;
        std::cerr << "Rotation: "<< rotation << " : " << derotation << std::endl;
        std::cerr << "Trans: "<< trans << " : " << detrans << std::endl;
        std::cerr << "Center: "<< center << " : " << decenter << std::endl;

        return false;
    }
   return true;
}

int main(int argc, char *argv[])
{
    osgInit(argc, argv);

    for(UInt32 i = 0; i < 100000; ++i)
    {   
        Vec3f scale(osgrand()*200-100, osgrand()*200-100, osgrand()*200-100);
        Quaternion scaleOrientation, rotation;

        scaleOrientation.setValueAsAxisRad(Vec3f(osgrand()*2-1, osgrand()*2-1, 
                osgrand()*2-1), osgrand()*200);

        rotation.setValueAsAxisRad(Vec3f(osgrand()*2-1, osgrand()*2-1, 
                osgrand()*2-1), osgrand()*200);

        Vec3f trans (osgrand()*200-100, osgrand()*200-100, osgrand()*200-100),
              center(osgrand()*200-100, osgrand()*200-100, osgrand()*200-100);

        std::cerr << i << " ";
        if (!test(Vec3f(0,0,0), rotation, scale, 
             Quaternion(Vec3f(1,0,0),0), Vec3f(0,0,0)))
             break;
    }
    
    osgExit();
}
