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

NodePtr  root;

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
	glRotatef( a / 6, 0,0,1 );

	dact->apply( root );

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
	// glEnable( GL_LIGHTING );

	// OSG

    root = Node::create();
    GroupPtr gr = Group::create();
	root->setCore( gr );

	NodePtr plane;
	plane = makePlane( 2, 2, 2, 2 );

	root->addChild( plane );

	cerr << "Plane Node: " << hex << plane << endl;
	
	dact = new DrawAction;
	
	glutMainLoop();
	
    return 0;
}

