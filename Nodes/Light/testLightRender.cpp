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


OSGDrawAction * dact;

OSGNodePtr  root, dlight, plight, slight;

OSGTransformPtr tr;

void 
display(void)
{
	float a = glutGet( GLUT_ELAPSED_TIME );

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	OSGMatrix m;

	m.setTranslate( sin(a/1500), cos(a/1500), 1 );

	osgBeginEditCP(tr);
	tr->getSFMatrix()->setValue( m );
	osgEndEditCP(tr);
	

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
	case 'z':	osgBeginEditCP(root);
				root->replaceChild( 1, dlight );
				osgEndEditCP(root);
				break;
	case 'x':	osgBeginEditCP(root);
				root->replaceChild( 1, plight );
				osgEndEditCP(root);
				break;
	case 'c':	osgBeginEditCP(root);
				root->replaceChild( 1, slight );
				osgEndEditCP(root);
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

	OSGNodePtr g1;
	g1 = osgMakePlane( 3, 3, 20, 20 );

	// Light Position Inidcator
	OSGNodePtr g2;
	g2 = osgMakePlane( .2, .2, 1, 1 );

	// Transform

    OSGNodePtr tnode = OSGNode::create();
	tr = OSGTransform::create();
	osgBeginEditCP(tnode);
	tnode->setCore( tr );
	tnode->addChild( g2 );
	osgEndEditCP(tnode);

	// Create Lights

	dlight = OSGNode::create();
	OSGDirectionalLightPtr dl = OSGDirectionalLight::create();

	osgBeginEditCP(dlight);
	dlight->setCore( dl );
	dlight->addChild( g1 );
	osgEndEditCP(dlight);
	
	osgBeginEditCP(dl);
	dl->setAmbientColor( .2, .2, .2, .2 );
	dl->setDiffuseColor( 1, 1, 1, 1 );
	dl->setDirection(0,0,1);
	dl->setBeacon( tnode );
	osgEndEditCP(dl);


	plight = OSGNode::create();
	OSGPointLightPtr pl = OSGPointLight::create();

	osgBeginEditCP(plight);
	plight->setCore( pl );
	plight->addChild( g1 );
	osgEndEditCP(plight);
	
	osgBeginEditCP(pl);
	pl->setAmbientColor( .2, .2, .2, .2 );
	pl->setDiffuseColor( 1, 1, 1, 1 );
	pl->setPosition(0,0,0);
	pl->setBeacon( tnode );
	osgEndEditCP(pl);


	slight = OSGNode::create();
	OSGSpotLightPtr sl = OSGSpotLight::create();

	osgBeginEditCP(slight);
	slight->setCore( sl );
	slight->addChild( g1 );
	osgEndEditCP(slight);
	
	osgBeginEditCP(sl);
	sl->setAmbientColor( .2, .2, .2, .2 );
	sl->setDiffuseColor( 1, 1, 1, 1 );
	sl->setPosition(0,0,0);
	sl->setSpotDirection(0,0,-1);
	sl->setSpotExponent(10);
	sl->setSpotCutOff(45);
	sl->setBeacon( tnode );
	osgEndEditCP(sl);


	//

    root = OSGNode::create();
    OSGGroupPtr gr = OSGGroup::create();
	osgBeginEditCP(root);
	root->setCore( gr );
	root->addChild( tnode );
	root->addChild( slight );
	osgEndEditCP(root);
	
	
	


	dact = new OSGDrawAction;
	
	glutMainLoop();
	
    return 0;
}

