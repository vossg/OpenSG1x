
#include <GL/glut.h>
#include <OSGLog.h>

#include "OSGState.h"
#include "OSGStateChunk.h"
#include "OSGTransformChunk.h"
#include "OSGMaterialChunk.h"
#include "OSGLightChunk.h"

OSG_USING_NAMESPACE

TransformChunkPtr tchunk1, tchunk2;

GLint dlid;

StatePtr state1, state2;

void 
display(void)
{
	float t = glutGet( GLUT_ELAPSED_TIME );

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	state1->activate();

	glCallList( dlid );

	Matrix m;
	m.setTranslate( cos(t/1000), 0, sin(t/1000) );
	tchunk2->setMatrix( m );

	state2->changeFrom( state1.getCPtr() );

	glCallList( dlid );

	state2->deactivate();

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

	Matrix m;

	tchunk1 = TransformChunk::create();
	m.setTranslate( 0, 1, 0 );
	tchunk1->setMatrix( m );

	state1 = State::create();
	state1->addChunk( tchunk1 );

	tchunk2 = TransformChunk::create();
	tchunk2->setMatrix( Matrix::identity() );

	state2 = State::create();
	state2->addChunk( tchunk2 );

	MaterialChunkPtr mchunk1, mchunk2;

	mchunk1 = MaterialChunk::create();
	mchunk1->setDiffuse( Vec4f( 1,0,0,0 ) );
	mchunk1->setAmbient( Vec4f( 1,0,0,0 ) );
	mchunk1->setShininess( 20 );
	state1->addChunk( mchunk1 );

	mchunk2 = MaterialChunk::create();
	mchunk2->setDiffuse( Vec4f( 0,1,0,0 ) );
	mchunk2->setAmbient( Vec4f( 0,1,0,0 ) );
	mchunk2->setShininess( 50 );
	state2->addChunk( mchunk2 );

	LightChunkPtr lchunk1, lchunk2;

	lchunk1 = LightChunk::create();
	lchunk1->setDiffuse( Vec4f( 1,1,1,1 ) );
	lchunk1->setPosition( Vec4f( 0,1,0,0 ) );
	state1->addChunk( lchunk1 );

	lchunk2 = LightChunk::create();
	lchunk2->setDiffuse( Vec4f( 1,0,0,1 ) );
	lchunk2->setPosition( Vec4f( 0,0,-2,1 ) );
	state2->addChunk( lchunk2 );

	cerr << "State1:" << endl;
	state1->print();

	cerr << "State2:" << endl;
	state2->print();

	glutMainLoop();

	return 0;
}
