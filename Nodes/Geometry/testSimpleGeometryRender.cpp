#include <OSGConfig.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <ctype.h>
#include <GL/glut.h>

#include <OSGBaseFunctions.h>
#include <OSGSFSysTypes.h>
#include <OSGMFVecTypes.h>
#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGThread.h>
#include <OSGTransform.h>
#include <OSGAttachment.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>

#include <OSGSimpleMaterial.h>
#include <OSGTextureChunk.h>

#include <OSGWindow.h>
#include <OSGGLUTWindow.h>

#include "OSGGeometry.h"
#include "OSGSimpleGeometry.h"
#include "OSGGeoFunctions.h"


OSG_USING_NAMESPACE

DrawAction * dact;

const int nobjects = 7;
NodePtr  objects[nobjects];
NodePtr  normalobjects[nobjects];

Bool autoswitch = true;
Bool autowire = true;
Bool shownormals = true;
int obj = 0;

void 
display(void)
{
	float a = glutGet( GLUT_ELAPSED_TIME );

	if ( autowire )
		switch ( (int) ( a / 2000 ) % 3 )	
		{
		case 0:	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); break;
		case 1:	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); break;
		case 2:	glPolygonMode( GL_FRONT_AND_BACK, GL_POINT ); break;
		}

	if ( autoswitch )
		obj = (int) ( a / 5000 ) % nobjects ;  

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	glPushMatrix();
	glRotatef( a / 36, 0,0,1 );

	dact->apply( objects[ obj ] );
	if ( shownormals )
		dact->apply( normalobjects[ obj ] );

	glPopMatrix();

	glutSwapBuffers();
}

void key( unsigned char key, int x, int y )
{
	switch ( tolower( key ) )
	{
	case 27: 	exit(0);
	case ' ':	autoswitch = ! autoswitch;
				cerr << "autoswitch " << (autoswitch?"on":"off") << endl;
				break;
	case 'w':	autowire = ! autowire;
				cerr << "autowire " << (autowire?"on":"off") << endl;
				break;
	case 'a':	obj = ( ++ obj ) % nobjects;
				cerr << "object now " << obj << endl;
				break;
	case 'n':	shownormals = ! shownormals;
				cerr << "shownormals " << (shownormals?"on":"off") << endl;
				break;
	case 's':	obj = ( -- obj + nobjects ) % nobjects;
				cerr << "object now " << obj << endl;
				break;

	case 'c':	if ( glIsEnabled( GL_CULL_FACE ) )
				{
					glDisable( GL_CULL_FACE );
					cerr << "cullface disabled" << endl;
				}
				else
				{
					glEnable( GL_CULL_FACE );
					cerr << "cullface enabled" << endl;
				}
	}
}

void resize( int w, int h )
{
	glViewport( 0,0,w,h);
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 60, w / (float)h, 0.1, 10 );
	glMatrixMode( GL_MODELVIEW );	
}

int main (int argc, char **argv)
{
	// GLUT init

    osgInit(argc, argv);

	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow("OpenSG");
	glutKeyboardFunc(key);
	glutReshapeFunc(resize);
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
	
	glPointSize( 3 );
	
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	glClearColor( .3, .3, .8, 1 );

	// OSG
	
	// create a material (need that to test textures)
	
	SimpleMaterialPtr mat;	
	
	mat = SimpleMaterial::create();

	mat->setDiffuse( Color3f( 1,.8,.8 ) );
	mat->setAmbient( Color3f( 0.1,0.1,0.1 ) );
	mat->setSpecular( Color3f( 1,1,1 ) );
	mat->setShininess( 20 );

	// Texture chunk
	
	UChar8 imgdata[] = 
		{  255,0,0,0,  0,255,0,0,  0,0,255,255,  255,255,255,255 };
	Image image( Image::OSG_RGBA_PF, 2, 2, 1, 1, 1, 0, imgdata );

	if ( argc > 1 )
		image.read( argv[1] );
	
	TextureChunkPtr xchunk;
	xchunk = TextureChunk::create();
	xchunk->setImage( &image );
	xchunk->setMinFilter( GL_NEAREST );
	xchunk->setMagFilter( GL_NEAREST );
	xchunk->setWrapS( GL_REPEAT );
	xchunk->setWrapT( GL_REPEAT );
	xchunk->setEnvMode( GL_MODULATE );

	mat->addChunk( xchunk );


	// create the objects

	objects[0] = makePlane( 2, 2, 2, 2 );
	GeometryPtr::dcast(objects[0]->getCore())->setMaterial( mat );
	cerr << "Plane Node: " << hex << objects[0] << endl;

	objects[1] = makeCone( 2.5, 2, 20, true, true );
	GeometryPtr::dcast(objects[1]->getCore())->setMaterial( mat );
	cerr << "Cone Node: " << hex << objects[1] << endl;

	objects[2] = makeTorus( .6, 2, 8, 16 );
	GeometryPtr::dcast(objects[2]->getCore())->setMaterial( mat );
	cerr << "Torus Node: " << hex << objects[2] << endl;

	objects[3] = makeSphere( 1, 2 );
	GeometryPtr::dcast(objects[3]->getCore())->setMaterial( mat );
	cerr << "Sphere Node: " << hex << objects[3] << endl;

	
	objects[4] = makeCylinder( 3, 2, 20, true, true, true );
	GeometryPtr::dcast(objects[4]->getCore())->setMaterial( mat );
	cerr << "Cylinder Node: " << hex << objects[4] << endl;
	
	objects[5] = makeConicalFrustum( 3, 2, 1, 20, true, true, true );
	GeometryPtr::dcast(objects[5]->getCore())->setMaterial( mat );
	cerr << "Frustum Node: " << hex << objects[5] << endl;

	objects[6] = makeBox( 4, 3, 2, 4, 3, 2 );
	GeometryPtr::dcast(objects[6]->getCore())->setMaterial( mat );
	cerr << "Box Node: " << hex << objects[0] << endl;
	
	// try the vertex normal calc
    //OSG::GeometryPtr pGeo = dcast<GeometryPtr>(objects[3]->getCore());
	//calcVertexNormals(pGeo);

	// Normals
	
	// normals material
	
	SimpleMaterialPtr nmat;	
	
	nmat = SimpleMaterial::create();
	nmat->setEmission( Color3f( 0,1,0 ) );
	
	for ( UInt16 i = 0; i < nobjects; i++ )
	{
		normalobjects[i] = getNormals(
            GeometryPtr::dcast(objects[i]->getCore()), .5);

		GeometryPtr::dcast(normalobjects[i]->getCore())->setMaterial(nmat);
	}
	
	// 
	// The action

	WindowPtr win = GLUTWindow::create();

	dact = DrawAction::create();
	dact->setWindow( win.getCPtr() );
	dact->setFrustumCulling( false );

	glutMainLoop();
	
    return 0;
}

