
#include "OSGConfig.h"

#include <GL/glut.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#include <fstream>
#else
#include <iostream.h>
#include <fstream.h>
#endif


#include <OSGBaseFunctions.h>
#include <OSGQuaternion.h>
#include <OSGMatrix.h>
#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>
#include <OSGGeometry.h>

#include "OSGSceneFileHandler.h"

#ifdef __linux
#include "OSGRAWSceneFileType.h"
#endif

OSG_USING_NAMESPACE


DrawAction * dact;

NodePtr  root;


void 
display(void)
{
	static float a = 0;

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glPushMatrix();
	glRotatef( a, 0,1,0 );
	dact->apply( root );

	glPopMatrix();

	a+=1;

	glutSwapBuffers();
}

int main (int argc, char **argv)
{
    osgInit(argc, argv);

    FieldContainerPtr pProto = Geometry::getClassType().getPrototype();

    GeometryPtr pGeoProto = GeometryPtr::dcast(pProto);

    if(pGeoProto != NullFC)
    {
        pGeoProto->setDlistCache(false);
    }

	const char *fileName = (argc > 1) ? argv[1] : "test.raw";

#ifdef __linux
    RAWSceneFileType *pR = &(RAWSceneFileType::staticThe());
#endif
	
	SceneFileHandler::the().print();

	root = SceneFileHandler::the().read(fileName, 0);

	if ( root == NullFC )
	{
		cerr << "Error loading " << fileName << "!" << endl;
		exit(1);
	}


	cerr << "Tree: " << endl;
	root->dump();

	// GLUT init

 	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow("OpenSG");
	glutDisplayFunc(display);       
	
	glutIdleFunc(display);

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( 60, 1, 0.1, 100 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	gluLookAt( 15,15,15,  0, 0, 0,   0, 1, 0 );
	
	glEnable( GL_DEPTH_TEST );
	// glDrawMode(  );
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
		
	dact = DrawAction::create();
	
	glutMainLoop();
	
	return 0;
}
