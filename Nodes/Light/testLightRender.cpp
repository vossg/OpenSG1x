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
#include <OSGMatrix.h>
#include <OSGQuaternion.h>

#include <OSGDirectionalLight.h>
#include <OSGPointLight.h>
#include <OSGSpotLight.h>


OSG_USING_NAMESPACE


DrawAction * dact;

NodePtr  root, dlight, plight, slight;

TransformPtr tr;

void 
display(void)
{
	float a = glutGet( GLUT_ELAPSED_TIME );

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	Matrix m;

	m.setTranslate( sin(a/1500), cos(a/1500), 1 );

	beginEditCP(tr);
	tr->getSFMatrix()->setValue( m );
	endEditCP(tr);
	

	dact->apply( root );

	glutSwapBuffers();
}

void key( unsigned char key, int x, int y )
{
    printf("Key: %d\n", key );

	switch (key )
	{
	case 27:	exit(1);	
				break;
	case 'z':	beginEditCP(root);
				root->replaceChild( 1, dlight );
				endEditCP(root);
				break;
	case 'x':	beginEditCP(root);
				root->replaceChild( 1, plight );
				endEditCP(root);
				break;
	case 'c':	beginEditCP(root);
				root->replaceChild( 1, slight );
				endEditCP(root);
				break;
	}
}

int main (int argc, char **argv)
{
	// GLUT init

    osgInit(argc, argv);

	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow("OpenSG");
	glutKeyboardFunc(key);
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

	// Geometry

	NodePtr g1;
	g1 = makePlane( 3, 3, 20, 20 );

	// Light Position Inidcator
	NodePtr g2;
	g2 = makePlane( .2, .2, 1, 1 );

	// Transform

    NodePtr tnode = Node::create();
	tr = Transform::create();
	beginEditCP(tnode);
	tnode->setCore( tr );
	tnode->addChild( g2 );
	endEditCP(tnode);

	// Create Lights

	dlight = Node::create();
	DirectionalLightPtr dl = DirectionalLight::create();

	beginEditCP(dlight);
	dlight->setCore( dl );
	dlight->addChild( g1 );
	endEditCP(dlight);
	
	beginEditCP(dl);
	dl->setAmbientColor( .2, .2, .2, .2 );
	dl->setDiffuseColor( 1, 1, 1, 1 );
	dl->setDirection(0,0,1);
	dl->setBeacon( tnode );
	endEditCP(dl);


	plight = Node::create();
	PointLightPtr pl = PointLight::create();

	beginEditCP(plight);
	plight->setCore( pl );
	plight->addChild( g1 );
	endEditCP(plight);
	
	beginEditCP(pl);
	pl->setAmbientColor( .2, .2, .2, .2 );
	pl->setDiffuseColor( 1, 1, 1, 1 );
	pl->setPosition(0,0,0);
	pl->setBeacon( tnode );
	endEditCP(pl);


	slight = Node::create();
	SpotLightPtr sl = SpotLight::create();

	beginEditCP(slight);
	slight->setCore( sl );
	slight->addChild( g1 );
	endEditCP(slight);
	
	beginEditCP(sl);
	sl->setAmbientColor( .2, .2, .2, .2 );
	sl->setDiffuseColor( 1, 1, 1, 1 );
	sl->setPosition(0,0,0);
	sl->setSpotDirection(0,0,-1);
	sl->setSpotExponent(10);
	sl->setSpotCutOff(45);
	sl->setBeacon( tnode );
	endEditCP(sl);


	//

    root = Node::create();
    GroupPtr gr = Group::create();
	beginEditCP(root);
	root->setCore( gr );
	root->addChild( tnode );
	root->addChild( slight );
	endEditCP(root);
	
	
	


	dact = DrawAction::create();
	
	glutMainLoop();
	
    return 0;
}

