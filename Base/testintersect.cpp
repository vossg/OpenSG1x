#include <OSGConfig.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include "GL/glut.h"

#include <OSGLine.h>
#include <OSGVector.h>
#include <OSGBoxVolume.h>
#include <OSGSphereVolume.h>
#include <OSGCylinderVolume.h>

using namespace OSG;



int main (int argc, char **argv) {

 	Real32 ent, ex;

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

	for ( int i = 0; i < nlines; i++ )
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

	cout << "Box: (" << xmin << "," << ymin << "," << zmin << ") (" << xmax 
		 << "," << ymax << "," << zmax << ")" << endl;

	for ( int i = 0 ; i < nlines; i++ )
	{
		cout << "Line: (" << lines[i].getPosition() << ") (" 
			 << lines[i].getDirection() << ")" << endl;

		Bool res = lines[i].intersect( b, ent, ex );
		Pnt3f	ep = lines[i].getPosition() + ent * lines[i].getDirection(),
				xp = lines[i].getPosition() + ex * lines[i].getDirection();

		cout << "Result: " << res;
		
		if ( res )
		{
			cout << " enter " << ent << "=(" << ep << ") ";

			Bool es = ( b.isOnSurface( ep ) || b.intersect( ep ) ),
				 xs = b.isOnSurface( xp );

			if ( ( res && es ) || !res )	cout << "ok";
			else							cout << "**BAD**";

			cout << ";  exit " << ex << "=(" << xp << ") ";

			if ( ( res && xs ) || !res )	cout << "ok";
			else							cout << "**BAD**";
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

	cout << endl << "Sphere: " << center << "   " << radius << endl;


	for ( int i = 0 ; i < nlines; i++ )
	{
		cout << "Line: (" << lines[i].getPosition() << ") (" 
			 << lines[i].getDirection() << ")" << endl;

		Bool res = lines[i].intersect( s, ent, ex );
		Pnt3f	ep = lines[i].getPosition() + ent * lines[i].getDirection(),
				xp = lines[i].getPosition() + ex * lines[i].getDirection();

		cout << "Result: " << res;
		
		if ( res )
		{
			cout << " enter " << ent << "=(" << ep << ") ";

			Bool es = ( s.isOnSurface( ep ) || s.intersect( ep ) ),
				 xs = s.isOnSurface( xp );

			if ( ( res && es ) || !res )	cout << "ok";
			else							cout << "**BAD**";

			cout << ";  exit " << ex << "=(" << xp << ") ";

			if ( ( res && xs ) || !res )	cout << "ok";
			else							cout << "**BAD**";
		}
		
		cout << endl;		
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

//	c.setAxis(p, d);
//	c.setRadius(rad);

	cout << endl;
	cout << "Cylinder: " << p << "   " << d << "   " << rad << endl;
//	cout << "La%nge " << l_adir << endl;
//	cout << "Richtung " << n_dir[0] << n_dir[1] << n_dir[2] << endl << endl;


	for ( int i = 0 ; i < nlines; i++ )
	{
		cout << "Line: (" << lines[i].getPosition() << ") (" 
			 << lines[i].getDirection() << ")" << endl;

		Bool res = lines[i].intersect( c, ent, ex );
		Pnt3f	ep = lines[i].getPosition() + ent * lines[i].getDirection(),
				xp = lines[i].getPosition() + ex * lines[i].getDirection();

		cout << "Result: " << res;
		
		if ( res )
		{
			cout << " enter " << ent << "=(" << ep << ") ";

			Bool es = ( c.isOnSurface( ep ) || c.intersect( ep ) ),
				 xs = c.isOnSurface( xp );

			if ( ( res && es ) || !res )	cout << "ok";
			else							cout << "**BAD**";

			cout << ";  exit " << ex << "=(" << xp << ") ";

			if ( ( res && xs ) || !res )	cout << "ok";
			else							cout << "**BAD**";
		}
		
		cout << endl;		
	}

  return 0;
}


