#include <OSGConfig.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <GL/glut.h>

#include <OSGFieldContainerFactory.h>
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
#include <OSGMatrix.h>
#include <OSGQuaternion.h>
#include <OSGBaseFunctions.h>

using namespace OSG;

OSGDrawAction * dact;

OSGNodePtr  root;

OSGMatrix accumM;
OSGMatrix stepM;

void 
display(void)
{
	static float a = 0;

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glPushMatrix();
	glRotatef( a, 0,1,0 );
//    glMultMatrixf(accumM.getValues());
	dact->apply( root );

	glPopMatrix();

	a+=1;

    accumM.mult(stepM);

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
	gluLookAt( 3, 3, 3,  0, 0, 0,   0, 1, 0 );
	
	glEnable( GL_DEPTH_TEST );
	// glEnable( GL_LIGHTING );

	// OSG

    OSGQuaternion stepQ(0., 1., 0., 1.);

    stepM.setRotate(stepQ);

    root = OSGNode::create();
    OSGGeometryPtr g1 = OSGGeometry::create();

	root->setCore( g1 );

	cerr << "Geometry Node: " << hex << (OSGGeometry*) g1.getCPtr() << endl;

	OSGGeoPosition3f::OSGPtrType pnts = OSGGeoPosition3f::create();
	g1->setPositions( pnts );

	cerr << "Points property: " << hex << pnts << endl;

	cerr << "Geometry Points: " << hex << g1->getPositions() << endl;

	OSGMFPnt3f* p = pnts->getFieldPtr();

	osgBeginEditCP(pnts);
	p->addValue( OSGPnt3f( -1, -1, -1) );
	p->addValue( OSGPnt3f(  1, -1, -1) );
	p->addValue( OSGPnt3f(  1,  1, -1) );
	p->addValue( OSGPnt3f( -1,  1, -1) );
	p->addValue( OSGPnt3f( -1, -1,  1) );
	p->addValue( OSGPnt3f(  1, -1,  1) );
	p->addValue( OSGPnt3f(  1,  1,  1) );
	p->addValue( OSGPnt3f( -1,  1,  1) );
	osgEndEditCP(pnts);


	OSGGeoColor4ub::OSGPtrType cols = OSGGeoColor4ub::create();
	g1->setColors( cols );
	g1->setColorPerVertex( true );
	osgBeginEditCP(cols);
	cols->getFieldPtr()->addValue( OSGVec4ub( 255, 255, 255, 255) );
	cols->getFieldPtr()->addValue( OSGVec4ub( 255, 255, 255, 255) );
	cols->getFieldPtr()->addValue( OSGVec4ub(   0, 255, 255, 255) );
	cols->getFieldPtr()->addValue( OSGVec4ub(   0, 255, 255, 255) );
	cols->getFieldPtr()->addValue( OSGVec4ub( 255,   0, 255, 255) );
	cols->getFieldPtr()->addValue( OSGVec4ub( 255, 255,   0, 255) );
	cols->getFieldPtr()->addValue( OSGVec4ub( 255,   0,   0, 255) );
	cols->getFieldPtr()->addValue( OSGVec4ub(   0, 255,   0, 255) );
	osgEndEditCP(cols);


	OSGGeoIndexUI32Ptr index = OSGGeoIndexUI32::create();	
	g1->setIndex( index );
	osgBeginEditCP(index);
	index->getFieldPtr()->addValue( 0 );
	index->getFieldPtr()->addValue( 1 );
	index->getFieldPtr()->addValue( 2 );
	index->getFieldPtr()->addValue( 3 );
	index->getFieldPtr()->addValue( 4 );
	index->getFieldPtr()->addValue( 5 );
	index->getFieldPtr()->addValue( 6 );
	index->getFieldPtr()->addValue( 7 );
	osgEndEditCP(index);


	OSGGeoPLengthPtr lens = OSGGeoPLength::create();	
	g1->setLengths( lens );
	osgBeginEditCP(lens);
	lens->getFieldPtr()->addValue( 4 );
	lens->getFieldPtr()->addValue( 4 );
	osgEndEditCP(lens);


	OSGGeoPTypePtr type = OSGGeoPType::create();	
	g1->setTypes( type );
	osgBeginEditCP(type);
	type->getFieldPtr()->addValue( GL_POLYGON );
	type->getFieldPtr()->addValue( GL_POLYGON );
	osgEndEditCP(type);

	cerr << "Geometry type " << g1->getType().getId() << endl;
	
	dact = new OSGDrawAction;
	
	glutMainLoop();
	
    return 0;
}

