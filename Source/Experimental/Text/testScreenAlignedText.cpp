//
// This example shows how to use the ScreenAlignedText class
//
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

#include <OSGGLUT.h>
#include <OSGConfig.h>
#include "OSGLog.h"

// Headers
#include <OSGSimpleGeometry.h>
#include <OSGSimpleTexturedMaterial.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGBaseFunctions.h>
#include <OSGTransform.h>
#include <OSGGroup.h>
#include <OSGGeometry.h>
#include <OSGPathHandler.h>

#include <OSGScreenAlignedText.h>

#include <OSGFontStyleFactory.h>
#include <OSGTXFFont.h>
#include <OSGTXFFontStyle.h>
#include <OSGTTFontStyle.h>
#include <OSGText.h>
#include <OSGOSGWriter.h>
#include <OSGSharedFontStyle.h>
#include <OSGVRMLWriteAction.h>
#include <OSGSharedFontStyleWrapper.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The pointer to the transformation
//TransformPtr        trans;

// The SimpleSceneManager to manage simple applications
SimpleSceneManager  *mgr;

// forward declaration so we can have the interesting stuff upfront
int                 setupGLUT(int *argc, char *argv[]);

NodePtr             scene;
NodePtr             n[3];
UInt8               numNodes = 0, currentNode = 0;
//Text                fontText;

std::vector<std::string> lineVec;
Real32                   lastT;

GeometryPtr txfGeo;

// redraw the window
void display(void)
{
    mgr->redraw();
}

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
	cout << "Testing screen aligned text generation and file-IO." << endl;
	
    if(argc == 1)
    {
        FFATAL(("Need *.txf or *.ttf font file\n"));
        return -1;
    }

    // OSG init
    osgInit(argc, argv);

    // GLUT init
    int             winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr   gwin = GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();

    PathHandler paths;

    paths.push_backPath(".");

    //paths.push_backPath("/home/elmi/wrk/development/texFont");
    // create the scene
    FontStyle   *fontStyle = FontStyleFactory::the().create( paths, argv[1], 
															 0.25);
	cout << fontStyle->getFontName() << endl;

    // create the scene
    NodePtr pTorus = makeTorus( 0.02, 0.55, 16, 16);
	ChunkMaterialPtr mat = ChunkMaterial::create();

    MaterialChunkPtr pmc = MaterialChunk::create();
    pmc->setDiffuse( Color4f( 1,0,0,0.5 ) );
    pmc->setAmbient( Color4f( 0,1,0,0.5 ) );
    pmc->setSpecular( Color4f( 0,0,1,0.5 ) );
	pmc->setLit( true );
    pmc->setShininess( 20 );

	beginEditCP(mat);
	{
	mat->addChunk( pmc );
	}
	endEditCP(mat);

    scene = Node::create();
	GroupPtr group = Group::create();
    beginEditCP( scene );
    {
        scene->setCore( group );
	}
    endEditCP( scene );

	SharedFontStylePtr sfs = SharedFontStyle::create(); 
	sfs->setContainedFontStyle( fontStyle );

	for( int x=0; x<100; x += 20 )
	{
		for( int y=0; y<100; y += 20 )
		{
			for( int z=0; z<100; z += 20 )
			{
				ScreenAlignedTextPtr scaText = ScreenAlignedText::create();
				if( scaText == NullFC )
				{
					exit (2);
				}
				SharedFontStyleWrapperPtr pFSWrapper = SharedFontStyleWrapper::create();
				pFSWrapper->setFStyleContainer( sfs );
				ostringstream cString;
				cString << '(' 
						<< x 
						<< ',' 
						<< y
						<< ','
						<< z
						<< ')'
						<< endl;

				beginEditCP(scaText);
				{
					scaText->setPosition( Vec3f ( x, y, z ) );
					scaText->setFont( pFSWrapper );
					scaText->setVerticalLineDistance( 0.20 );
					scaText->setAlignment( 0 );
					scaText->getText().push_back( cString.str() );
					scaText->setMaterial( mat );
				}
				endEditCP(scaText);
				NodePtr pTextNode = Node::create();
				beginEditCP( pTextNode );
				{
					pTextNode->setCore( scaText );
				}
				beginEditCP( scene );
				{
					scene->addChild( pTextNode );
				}
				endEditCP( scene );	
				cout << "Erzeugt : " 
					 << cString.str() 
					 << endl;
			}
		}
    }

	//NodePtr pCopied = scene;

#if 1
	{
		ofstream outFileStream( "/tmp/text.osg" );

		if( !outFileStream )
		{
			cerr << "cannot open file" << endl;
			exit(2);
		}
		//FILE *pFile = fopen( "isolinien.osg","w" );
		//BINWriter writer( pFile );
		OSGWriter writer( outFileStream );
		writer.write( scene );
	}
#endif

#if 0
	VRMLWriteAction *pWriter = VRMLWriteAction::create();
	scene->dump();
	pWriter->open("allesscheisse.wrl");
	pWriter->write( scene);
	pWriter->close();
	delete pWriter;
#endif

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin);
    mgr->setRoot( scene );

    // show the whole scene
    mgr->showAll();

    // GLUT main loop
    glutMainLoop();

    return 0;
}

//

// GLUT callback functions

//

// react to size changes
void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
    if(state)
    {
        mgr->mouseButtonRelease(button, x, y);
    }
    else
    {
        mgr->mouseButtonPress(button, x, y);
    }

    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE | GLUT_ALPHA	);

    int winid = glutCreateWindow("OpenSG");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    // call the redraw function whenever there's nothing else to do
    glutIdleFunc(display);

    return winid;
}

