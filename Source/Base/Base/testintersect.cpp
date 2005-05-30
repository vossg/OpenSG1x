#include <OSGConfig.h>

#include <iostream>

#include <OSGLine.h>
#include <OSGVector.h>
#include <OSGMatrix.h>
#include <OSGBoxVolume.h>
#include <OSGSphereVolume.h>
#include <OSGCylinderVolume.h>
#include <OSGPlane.h>
#include <OSGFrustumVolume.h>

using namespace OSG;



int main (int argc, char **argv) {

    Real32 ent, ex;
    int i;

    //Lines:

    const int nlines = 10;

    Line lines[nlines];
    Pnt3f pnts[nlines * 2] = {
                        Pnt3f(0,0,0), Pnt3f(0,1,0),
                        Pnt3f(0,0,0), Pnt3f(2,1,0),
                        Pnt3f(2,0,0), Pnt3f(2,1,0),
                        Pnt3f(-2,0,0), Pnt3f(0,2,0),
                        Pnt3f(-4,2,0), Pnt3f(0,2,0),
                        Pnt3f(-3,0,0), Pnt3f(-2,1,0),
                        Pnt3f(3,4,0), Pnt3f(1,3,0),
                        Pnt3f(-1,0,0), Pnt3f(-1,1,0),
                        Pnt3f(-4,0,0), Pnt3f(-3,1,0),
                        Pnt3f(-4,6,0), Pnt3f(0,6,0)
                        };

    for ( i = 0; i < nlines; i++ )
        lines[i].setValue( pnts[i*2], pnts[i*2+1] );


    BoxVolume b;

    float xmin, ymin, zmin, xmax, ymax, zmax;

    xmin = 0;
    ymin = 0.5;
    zmin = 0;
    xmax = 1;
    ymax = .5;
    zmax = 1;

    b.setBounds(xmin, ymin, zmin, xmax, ymax, zmax);

    std::cout << std::endl;
    b.dump();
    std::cout << std::endl;

    for ( i = 0 ; i < nlines; i++ )
    {
        std::cout << "Line: (" << lines[i].getPosition() << ") ("
             << lines[i].getDirection() << ")" << std::endl;

        bool res = lines[i].intersect( b, ent, ex );
        Pnt3f   ep = lines[i].getPosition() + ent * lines[i].getDirection(),
                xp = lines[i].getPosition() + ex * lines[i].getDirection();

        std::cout << "Result: " << res;

        if ( res )
        {
            std::cout << " enter " << ent << "=(" << ep << ") ";

            bool es = ( b.isOnSurface( ep ) || b.intersect( ep ) ),
                 xs = b.isOnSurface( xp );

            if ( ( res && es ) || !res )    std::cout << "ok";
            else                            std::cout << "**BAD**";

            std::cout << ";  exit " << ex << "=(" << xp << ") ";

            if ( ( res && xs ) || !res )    std::cout << "ok";
            else                            std::cout << "**BAD**";
        }

        std::cout << std::endl;
    }

    return 0;

    SphereVolume s;

    float radius;
    Vec3f center;

    center[0] = 0;
    center[1] = 0;
    center[2] = 0;

    radius = 1;

    s.setCenter(center);
    s.setRadius(radius);

    std::cout << std::endl;
    s.dump();
    std::cout << std::endl;


    for ( i = 0 ; i < nlines; i++ )
    {
        std::cout << "Line: (" << lines[i].getPosition() << ") ("
                  << lines[i].getDirection() << ")" << std::endl;

        bool res = lines[i].intersect( s, ent, ex );
        Pnt3f   ep = lines[i].getPosition() + ent * lines[i].getDirection(),
                xp = lines[i].getPosition() + ex * lines[i].getDirection();

        std::cout << "Result: " << res;

        if ( res )
        {
            std::cout << " enter " << ent << "=(" << ep << ") ";

            bool es = ( s.isOnSurface( ep ) || s.intersect( ep ) ),
                 xs = s.isOnSurface( xp );

            if ( ( res && es ) || !res )    std::cout << "ok";
            else                            std::cout << "**BAD**";

            std::cout << ";  exit " << ex << "=(" << xp << ") ";

            if ( ( res && xs ) || !res )    std::cout << "ok";
            else                            std::cout << "**BAD**";
        }

        std::cout << std::endl;
    }

//  Intersect the line with a cylinder.


    Pnt3f p;
    Vec3f d;
    float rad;

    p[0] = 0;
    p[1] = 1;
    p[2] = 0;

    d[0] = 0;
    d[1] = 4;
    d[2] = 0;

    rad = 2;

    CylinderVolume c;

    c.setValue(p, d, rad);

//  c.setAxis(p, d);
//  c.setRadius(rad);

    std::cout << std::endl;
    c.dump();
    std::cout << std::endl;


    for ( i = 0 ; i < nlines; i++ )
    {
        std::cout << "Line: (" << lines[i].getPosition() << ") ("
             << lines[i].getDirection() << ")" << std::endl;

        bool res = lines[i].intersect( c, ent, ex );
        Pnt3f   ep = lines[i].getPosition() + ent * lines[i].getDirection(),
                xp = lines[i].getPosition() + ex * lines[i].getDirection();

        std::cout << "Result: " << res;

        if ( res )
        {
            std::cout << " enter " << ent << "=(" << ep << ") ";

            bool es = ( c.isOnSurface( ep ) || c.intersect( ep ) ),
                 xs = c.isOnSurface( xp );

            if ( ( res && es ) || !res )    std::cout << "ok";
            else                            std::cout << "**BAD**";

            std::cout << ";  exit " << ex << "=(" << xp << ") ";

            if ( ( res && xs ) || !res )    std::cout << "ok";
            else                            std::cout << "**BAD**";
        }

        std::cout << std::endl;
    }

    //### volume intersection ##############################################


    std::cout << "### volume intersection test ###" << std::endl;

    BoxVolume box(-1,-1,-1,1,1,1);
    BoxVolume boxOut (5,5,5,10,10,10);
    BoxVolume boxIn(-1,-1,-1,2,2,2);

    SphereVolume sphere(Pnt3f(0,0,0),2);
    SphereVolume sphereOut(Pnt3f(2,2,2),1);
    SphereVolume sphereIn(Pnt3f(1,0,0),1);

    CylinderVolume cylinder(Pnt3f(0,0,0),Vec3f(1,1,1),1);
    CylinderVolume cylinderOut(Pnt3f(0,9,9),Vec3f(0,0,1),1);
    CylinderVolume cylinderIn(Pnt3f(1,0,0),Vec3f(0,1,0),1);


    // Frustum defined by normal vector and distance

    Plane pnear(Vec3f(0,0,-1),2);
    Plane pfar(Vec3f(0,0,1),7);
    Plane pright(Vec3f(-0.7071,0,-0.7071),0);
    Plane pleft(Vec3f(0.7071,0,-0.7071),0);
    Plane ptop(Vec3f(0,-0.7071,-0.7071),0);
    Plane pbottom(Vec3f(0,0.7071,-0.7071),0);

    FrustumVolume frustum(pnear, pfar, pleft, pright, ptop, pbottom);

    //Frustum defined by a clipMatrix

    Matrix matrix;
    matrix.setValue(0.7071,0,0,0,
            0,0.7071,0,0,
            0,0,-1.27,-3.959,
            0,0,-0.7071,0);

    FrustumVolume frustum1;
    frustum1.setPlanes(matrix);

    // Frustum defined by 8 points

    Pnt3f nlt(-2,2,-2);
    Pnt3f nlb(-2,-2,-2);
    Pnt3f nrt(2,2,-2);
    Pnt3f nrb(2,-2,-2);
    Pnt3f flt(-7,7,-7);
    Pnt3f flb(-7,-7,-7);
    Pnt3f frt(7,7,-7);
    Pnt3f frb(7,-7,-7);

    FrustumVolume frustum2;
    frustum2.setPlanes(nlt, nlb, nrt, nrb, flt, flb, frt, frb);


        //Tests

    std::cout << "Box/box outside test: " << std::flush;
    std::cout << (box.intersect(boxOut) ? "**BAD**" : "ok") << std::endl;

    std::cout << "Box/box inside test: " << std::flush;
    std::cout << (box.intersect(boxIn) ? "ok" : "**BAD**") << std::endl;

    std::cout << "Box/sphere outside test: " << std::flush;
    std::cout << (box.intersect(sphereOut) ? "**BAD**" : "ok") << std::endl;

    std::cout << "Box/sphere inside test: " << std::flush;
    std::cout << (box.intersect(sphereIn) ? "ok" : "**BAD**")<< std::endl;

    std::cout << "Sphere/sphere outside test: " << std::flush;
    std::cout << (sphere.intersect(sphereOut) ? "**BAD**" : "ok") << std::endl;

    std::cout << "Sphere/sphere inside test: " << std::flush;
    std::cout << (sphere.intersect(sphereIn) ? "ok" : "**BAD**") << std::endl;

    std::cout << "Box/cylinder outside test: " << std::flush;
    std::cout << (box.intersect(cylinderOut) ? "**BAD**" : "ok") << std::endl;

    std::cout << "Box/cylinder inside test: " << std::flush;
    std::cout << (box.intersect(cylinderIn) ? "ok" : "**BAD**") << std::endl;

    std::cout << "Sphere/cylinder outside test: " << std::flush;
    std::cout << (sphere.intersect(cylinderOut) ? "**BAD**" : "ok") << std::endl;

    std::cout << "Sphere/cylinder inside test: " << std::flush;
    std::cout << (sphere.intersect(cylinderIn) ? "ok" : " **BAD**") << std::endl;

    std::cout << "Cylinder/cylinder outside test: "<<std::flush;
    std::cout << (cylinder.intersect(cylinderOut) ? "**BAD**" : "ok")<<std::endl;

    std::cout << "Cylinder/cylinder inside test: "<<std::flush;
    std::cout << (cylinder.intersect(cylinderIn) ? "ok" : " **BAD** ")<<std::endl;

    std::cout << "Box/Frustum outside test : " << std::flush;
    std::cout << (boxOut.intersect(frustum) ? "**BAD**" : "ok") << std::endl;

    std::cout << "Box/Frustum inside test : " << std::flush;
    std::cout << (boxIn.intersect(frustum) ? "ok" : "**BAD**") << std::endl;

    std::cout << "Sphere/Frustum outside test : " << std::flush;
    std::cout << (sphereOut.intersect(frustum) ? "**BAD**" : "ok") << std::endl;

    std::cout << "Sphere/Frustum inside test : " << std::flush;
    std::cout << (sphereIn.intersect(frustum) ? "ok" : "**BAD**") << std::endl;


    std::cout << "Cylinder/Frustum outside test : " << std::flush;
    std::cout << (cylinderOut.intersect(frustum) ? "**BAD**" : "ok") << std::endl;

    std::cout << "Cylinder/Frustum inside test : " << std::flush;
    std::cout << (cylinderIn.intersect(frustum) ? "ok" : "**BAD**") << std::endl;

    std::cout << "Cylinder/Sphere outside test: " << std::flush;
    std::cout << (cylinderOut.intersect(sphere) ? "**BAD**" : "ok") << std::endl;

    //###VOLUME EXTENSION################################################

    std::cout << "### volume extension test ###" << std::endl;

    Pnt3f min,max;

    //Box extension

    extend(box, boxIn);
    box.getBounds(min,max);
    std::cout<< "min of the box : " <<min<<std::endl;
    std::cout<< "max of the box : " <<max<<std::endl;

    extend(box,sphere);
    box.getBounds(min,max);
    std::cout<< "min of the box : " <<min<<std::endl;
    std::cout<< "max of the box : " <<max<<std::endl;

    extend(box,cylinder);
    box.getBounds(min,max);
    std::cout<< "min of the box : " <<min<<std::endl;
    std::cout<< "max of the box : " <<max<<std::endl;

    //Sphere extension

    extend(sphere, box);
    std::cout<<"Center of the sphere : " <<sphere.getCenter()<<std::endl;
    std::cout<<"Radius of the sphere : " <<sphere.getRadius()<<std::endl;

    extend(sphere, sphereOut);
    std::cout<<"Center of the sphere : " <<sphere.getCenter()<<std::endl;
    std::cout<<"Radius of the sphere : " <<sphere.getRadius()<<std::endl;

    extend(sphere, cylinder);
    std::cout<<"Center of the sphere : " <<sphere.getCenter()<<std::endl;
    std::cout<<"Radius of the sphere : " <<sphere.getRadius()<<std::endl;

    //Cylinder extension

    extend (cylinder, box);
    cylinder.getBounds(min,max);
    std::cout<< "min of the cylinder : " <<min<<std::endl;
    std::cout<< "max of the cylinder : " <<max<<std::endl;

    extend (cylinder, sphere);
    cylinder.getBounds(min,max);
    std::cout<< "min of the cylinder : " <<min<<std::endl;
    std::cout<< "max of the cylinder : " <<max<<std::endl;

    extend (cylinder, cylinder);
    cylinder.getBounds(min,max);
    std::cout<< "min of the cylinder : " <<min<<std::endl;
    std::cout<< "max of the cylinder : " <<max<<std::endl;


    return 0;


}



