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
#include "OSGChunkMaterial.h"
#include "OSGSimpleMaterial.h"


OSG_USING_NAMESPACE


DrawAction * dact;

NodePtr plane,torus;
ChunkMaterialPtr pm;
SimpleMaterialPtr tmat;	

void 
display(void)
{
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
	glTranslatef( 0,0,fabs(sinf(a/3000 * Pi))*2 );
	glRotatef( (a/3000) * 360 / 2, 1,0,0 );

	dact->apply( torus );

	// do some OpenGL rendering

	StatePtr st = pm->makeState();

	addRefCP( st );
	
	st->activate( dact );
	glutSolidSphere( .4, 8, 8 );
	st->deactivate( dact );

	subRefCP( st );
	
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
	plane_geo = dcast<GeometryPtr>(plane->getCore());
	torus_geo = dcast<GeometryPtr>(torus->getCore());
	
	
	pm = ChunkMaterial::create();

	MaterialChunkPtr pmc = MaterialChunk::create();
	pmc->setDiffuse( Color4f( 1,0,0,0 ) );
	pmc->setAmbient( Color4f( 1,0,0,0 ) );
	pmc->setSpecular( Color4f( 1,1,1,0 ) );
	pmc->setShininess( 20 );
	
	pm->addChunk( pmc );
	
	plane_geo->setMaterial( pm );
	
	
	tmat = SimpleMaterial::create();

	tmat->setDiffuse( Color3f( 0,1,0 ) );
	tmat->setAmbient( Color3f( 0,1,0 ) );
	
	torus_geo->setMaterial( tmat );
	
	
	dact = DrawAction::create();
	
	glutMainLoop();
	
    return 0;
}

