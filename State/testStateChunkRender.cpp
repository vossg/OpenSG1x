
#include <GL/glut.h>
#include <OSGLog.h>

#include "OSGStateChunk.h"
#include "OSGTransformChunk.h"
#include "OSGMaterialChunk.h"

OSG_USING_NAMESPACE

OSGTransformChunkPtr tchunk1, tchunk2;
OSGMaterialChunkPtr mchunk1, mchunk2;

GLint dlid;


void 
display(void)
{
	float t = glutGet( GLUT_ELAPSED_TIME );

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	OSGMatrix m;
	OSGQuaternion q;
	q.setValueAsAxis( 0,1,0, -t/20 );
	m.setRotate( q );
	tchunk1->setMatrix( m );

	tchunk1->activate();
	mchunk1->activate();

	glCallList( dlid );

	m.setIdentity();
	m.setTranslate( cos(t/1000), 0, sin(t/1000) );
	tchunk2->setMatrix( m );

	tchunk2->changeFrom( tchunk1 );
	mchunk2->changeFrom( mchunk1 );

	glCallList( dlid );

	tchunk2->deactivate();
	mchunk2->deactivate();

	glutSwapBuffers();
}


int main( int argc, char *argv[] )
{
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
	gluLookAt( 3, 3, 3,  0, 0, 0,   0, 1, 0 );
	
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );

	dlid = glGenLists( 1 );

	glNewList( dlid, GL_COMPILE );
	glutSolidSphere( .8, 8, 8 );
	glEndList();
	
	OSGMatrix m;

	tchunk1 = OSGTransformChunk::create();
	m.setTranslate( 0, 1, 0 );
	tchunk1->setMatrix( m );

	tchunk2 = OSGTransformChunk::create();
	tchunk2->setMatrix( OSGMatrix::identity() );


	mchunk1 = OSGMaterialChunk::create();
	mchunk1->setDiffuse( OSGVec4f( 1,0,0,0 ) );
	mchunk1->setAmbient( OSGVec4f( 1,0,0,0 ) );
	mchunk1->setShininess( 20 );

	mchunk2 = OSGMaterialChunk::create();
	mchunk2->setDiffuse( OSGVec4f( 0,1,0,0 ) );
	mchunk2->setAmbient( OSGVec4f( 0,1,0,0 ) );
	mchunk2->setShininess( 50 );

	glutMainLoop();

	return 0;
}
