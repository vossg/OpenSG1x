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
#include <OSGGeometry.h>
#include <OSGSimpleGeometry.h>

#include <OSGMaterialChunk.h>

#include "OSGMaterial.h"
#include "OSGSimpleMaterial.h"


OSG_USING_NAMESPACE


DrawAction * dact;

NodePtr plane,torus;

void 
display(void)
{
	// do the motion in OpenGl, to stay independent of the ransform node
	// use the draw action to check the material
	
	float a = glutGet( GLUT_ELAPSED_TIME );

	if ( (int) ( a / 2000 ) & 1 )	
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	else
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glPushMatrix();
	glRotatef( a / 20, 0,0,1 );

	dact->apply( plane );

	glPushMatrix();
	glTranslatef( 0,0,fabs(sinf(a/3000 * M_PI))*2 );
	glRotatef( (a/3000) * 360 / 2, 1,0,0 );

	dact->apply( torus );

	glPopMatrix();
	
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

	plane = makePlane( 2, 2, 8, 8 );
	torus = makeTorus( .2, 1, 16, 8 );

	GeometryPtr plane_geo, torus_geo;
	plane_geo = plane->getCore().dcast<GeometryPtr>();
	torus_geo = torus->getCore().dcast<GeometryPtr>();
	
	
	SimpleMaterialPtr pm, tm;	
	
	pm = SimpleMaterial::create();

	pm->setDiffuse( Color3f( 1,0,0 ) );
	pm->setAmbient( Color3f( 1,0,0 ) );
	pm->setSpecular( Color3f( 1,1,1 ) );
	pm->setShininess( 10 );
	
	plane_geo->setMaterial( pm );
	
	
	tm = SimpleMaterial::create();

	tm->setDiffuse( Color3f( 0,1,0 ) );
	tm->setAmbient( Color3f( 0,1,0 ) );
	
	torus_geo->setMaterial( tm );
	
	// as there no useful except Material yet adding Chunks will 
	// have to wait a little...
	
	dact = new DrawAction;
	
	glutMainLoop();
	
    return 0;
}

