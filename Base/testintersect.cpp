#include <OSGConfig.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

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
    ymin = 0;
    zmin = 0;
    xmax = 1;
    ymax = 1;
    zmax = 1;

    b.setBounds(xmin, ymin, zmin, xmax, ymax, zmax);

    cout << endl;
    b.dump();
    cout << endl;

    for ( i = 0 ; i < nlines; i++ )
    {
        cout << "Line: (" << lines[i].getPosition() << ") ("
             << lines[i].getDirection() << ")" << endl;

        Bool res = lines[i].intersect( b, ent, ex );
        Pnt3f   ep = lines[i].getPosition() + ent * lines[i].getDirection(),
                xp = lines[i].getPosition() + ex * lines[i].getDirection();

        cout << "Result: " << res;

        if ( res )
        {
            cout << " enter " << ent << "=(" << ep << ") ";

            Bool es = ( b.isOnSurface( ep ) || b.intersect( ep ) ),
                 xs = b.isOnSurface( xp );

            if ( ( res && es ) || !res )    cout << "ok";
            else                            cout << "**BAD**";

            cout << ";  exit " << ex << "=(" << xp << ") ";

            if ( ( res && xs ) || !res )    cout << "ok";
            else                            cout << "**BAD**";
        }

        cout << endl;
    }


    SphereVolume s;

    float radius;
    Vec3f center;

    center[0] = 0;
    center[1] = 0;
    center[2] = 0;

    radius = 1;

    s.setCenter(center);
    s.setRadius(radius);

    cout << endl;
    s.dump();
    cout << endl;


    for ( i = 0 ; i < nlines; i++ )
    {
        cout << "Line: (" << lines[i].getPosition() << ") ("
             << lines[i].getDirection() << ")" << endl;

        Bool res = lines[i].intersect( s, ent, ex );
        Pnt3f   ep = lines[i].getPosition() + ent * lines[i].getDirection(),
                xp = lines[i].getPosition() + ex * lines[i].getDirection();

        cout << "Result: " << res;

        if ( res )
        {
            cout << " enter " << ent << "=(" << ep << ") ";

            Bool es = ( s.isOnSurface( ep ) || s.intersect( ep ) ),
                 xs = s.isOnSurface( xp );

            if ( ( res && es ) || !res )    cout << "ok";
            else                            cout << "**BAD**";

            cout << ";  exit " << ex << "=(" << xp << ") ";

            if ( ( res && xs ) || !res )    cout << "ok";
            else                            cout << "**BAD**";
        }

        cout << endl;
    }

    /*
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

    cout << endl;
    c.dump();
    cout << endl;


    for ( i = 0 ; i < nlines; i++ )
    {
        cout << "Line: (" << lines[i].getPosition() << ") ("
             << lines[i].getDirection() << ")" << endl;

        Bool res = lines[i].intersect( c, ent, ex );
        Pnt3f   ep = lines[i].getPosition() + ent * lines[i].getDirection(),
                xp = lines[i].getPosition() + ex * lines[i].getDirection();

        cout << "Result: " << res;

        if ( res )
        {
            cout << " enter " << ent << "=(" << ep << ") ";

            Bool es = ( c.isOnSurface( ep ) || c.intersect( ep ) ),
                 xs = c.isOnSurface( xp );

            if ( ( res && es ) || !res )    cout << "ok";
            else                            cout << "**BAD**";

            cout << ";  exit " << ex << "=(" << xp << ") ";

            if ( ( res && xs ) || !res )    cout << "ok";
            else                            cout << "**BAD**";
        }

        cout << endl;
    }
    */

    //### volume intersection ##############################################


    cout << "### volume intersection test ###" << endl;

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

    cout << "Box/box outside test: " << flush;
    cout << (box.intersect(boxOut) ? "**BAD**" : "ok") << endl;

    cout << "Box/box inside test: " << flush;
    cout << (box.intersect(boxIn) ? "ok" : "**BAD**") << endl;

    cout << "Box/sphere outside test: " << flush;
    cout << (box.intersect(sphereOut) ? "**BAD**" : "ok") << endl;

    cout << "Box/sphere inside test: " << flush;
    cout << (box.intersect(sphereIn) ? "ok" : "**BAD**")<< endl;

    cout << "Sphere/sphere outside test: " << flush;
    cout << (sphere.intersect(sphereOut) ? "**BAD**" : "ok") << endl;

    cout << "Sphere/sphere inside test: " << flush;
    cout << (sphere.intersect(sphereIn) ? "ok" : "**BAD**") << endl;

    cout << "Box/cylinder outside test: " << flush;
    cout << (box.intersect(cylinderOut) ? "**BAD**" : "ok") << endl;

    cout << "Box/cylinder inside test: " << flush;
    cout << (box.intersect(cylinderIn) ? "ok" : "**BAD**") << endl;

    cout << "Sphere/cylinder outside test: " << flush;
    cout << (sphere.intersect(cylinderOut) ? "**BAD**" : "ok") << endl;

    cout << "Sphere/cylinder inside test: " << flush;
    cout << (sphere.intersect(cylinderIn) ? "ok" : " **BAD**") << endl;

    cout << "Cylinder/cylinder outside test: "<<flush;
    cout << (cylinder.intersect(cylinderOut) ? "**BAD**" : "ok")<<endl;

    cout << "Cylinder/cylinder inside test: "<<flush;
    cout << (cylinder.intersect(cylinderIn) ? "ok" : " **BAD** ")<<endl;

    cout << "Box/Frustum outside test : " << flush;
    cout << (boxOut.intersect(frustum) ? "**BAD**" : "ok") << endl;

    cout << "Box/Frustum inside test : " << flush;
    cout << (boxIn.intersect(frustum) ? "ok" : "**BAD**") << endl;

    cout << "Sphere/Frustum outside test : " << flush;
    cout << (sphereOut.intersect(frustum) ? "**BAD**" : "ok") << endl;

    cout << "Sphere/Frustum inside test : " << flush;
    cout << (sphereIn.intersect(frustum) ? "ok" : "**BAD**") << endl;


    cout << "Cylinder/Frustum outside test : " << flush;
    cout << (cylinderOut.intersect(frustum) ? "**BAD**" : "ok") << endl;

    cout << "Cylinder/Frustum inside test : " << flush;
    cout << (cylinderIn.intersect(frustum) ? "ok" : "**BAD**") << endl;

    //###VOLUME EXTENSION################################################

    cout << "### volume extension test ###" << endl;

    Pnt3f min,max;

    //Box extension

    extend(box, boxIn);
    box.getBounds(min,max);
    cout<< "min of the box : " <<min<<endl;
    cout<< "max of the box : " <<max<<endl;

    extend(box,sphere);
    box.getBounds(min,max);
    cout<< "min of the box : " <<min<<endl;
    cout<< "max of the box : " <<max<<endl;

    extend(box,cylinder);
    box.getBounds(min,max);
    cout<< "min of the box : " <<min<<endl;
    cout<< "max of the box : " <<max<<endl;

    //Sphere extension

    extend(sphere, box);
    cout<<"Center of the sphere : " <<sphere.getCenter()<<endl;
    cout<<"Radius of the sphere : " <<sphere.getRadius()<<endl;

    extend(sphere, sphereOut);
    cout<<"Center of the sphere : " <<sphere.getCenter()<<endl;
    cout<<"Radius of the sphere : " <<sphere.getRadius()<<endl;

    extend(sphere, cylinder);
    cout<<"Center of the sphere : " <<sphere.getCenter()<<endl;
    cout<<"Radius of the sphere : " <<sphere.getRadius()<<endl;

    //Cylinder extension

    extend (cylinder, box);
    cylinder.getBounds(min,max);
    cout<< "min of the cylinder : " <<min<<endl;
    cout<< "max of the cylinder : " <<max<<endl;

    extend (cylinder, sphere);
    cylinder.getBounds(min,max);
    cout<< "min of the cylinder : " <<min<<endl;
    cout<< "max of the cylinder : " <<max<<endl;

    extend (cylinder, cylinder);
    cylinder.getBounds(min,max);
    cout<< "min of the cylinder : " <<min<<endl;
    cout<< "max of the cylinder : " <<max<<endl;


    return 0;


}



