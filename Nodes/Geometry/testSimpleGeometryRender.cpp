#include <OSGConfig.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <GL/glut.h>

#include <OSGBaseFunctions.h>
#include <OSGSFSysTypes.h>
#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGThread.h>
#include <OSGTransform.h>
#include <OSGAttachment.h>
#include <OSGMFVecTypes.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>
#include "OSGGeometry.h"
#include "OSGSimpleGeometry.h"


OSG_USING_NAMESPACE


DrawAction * dact;

const int nobjects = 4;
NodePtr  objects[nobjects];

void 
display(void)
{
	float a = glutGet( GLUT_ELAPSED_TIME );

	switch ( (int) ( a / 2000 ) % 3 )	
	{
	case 0:	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); break;
	case 1:	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); break;
	case 2:	glPolygonMode( GL_FRONT_AND_BACK, GL_POINT ); break;
	}

	int obj = (int) ( a / 5000 ) % nobjects ;  

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glPushMatrix();
	glRotatef( a / 36, 0,0,1 );

	dact->apply( objects[ obj ] );

	glPopMatrix();

	glutSwapBuffers();
}

int main (int argc, char **argv)
{
	// GLUT init

    osgInit(argc, argv);

	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow("OpenSG");
	// glutKeyboardFunc(key);
	// glutReshapeFunc(resize);
	glutDisplayFunc(display);       
	// glutMouseFunc(mouse);   
	// glutMotionFunc(motion); 
	
	glutIdleFunc(display);

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 60, 1, 0.1, 10 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	gluLookAt( 3, 3, 3,  0, 0, 0,   0, 0, 1 );
	
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );

	// OSG

	objects[0] = makePlane( 2, 2, 2, 2 );
	cerr << "Plane Node: " << hex << objects[0] << endl;

	objects[1] = makeCone( 2.5, 2, 20 );
	cerr << "Cone Node: " << hex << objects[1] << endl;

	objects[2] = makeTorus( .6, 2, 8, 16 );
	cerr << "Torus Node: " << hex << objects[2] << endl;

	objects[3] = makeSphere( 3, 2 );
	cerr << "Sphere Node: " << hex << objects[3] << endl;
	
	dact = new DrawAction;
	
	glutMainLoop();
	
    return 0;
}

