// OpenSG Tutorial Example: Text Geometry
//
// This example shows how to use TrueType(tm) Fonts with OSGText
//

#ifndef WIN32

// Headers
#include <fstream>
#include <string>
#include <GL/glut.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGSimpleTexturedMaterial.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGBaseFunctions.h>
#include <OSGTransform.h>
#include <OSGGroup.h>
#include <OSGGeometry.h>
#include <OSGPathHandler.h>


#include "OSGLog.h"

#include "OSGFontStyleFactory.h"
#include "OSGFontStyle.h"
#include "OSGText.h"
#include "OSGFontFactory.h"


// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The pointer to the transformation
TransformPtr trans;

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );


NodePtr scene;
NodePtr n[3];
UInt8 numNodes=0, currentNode=0;
Text fontText;
string *textLine;
vector<string *> lineVec;
Real32 lastT;


void next_child()
{
  UInt8 nextNode = (currentNode+1)%numNodes;

  scene->replaceChildBy(n[currentNode], n[nextNode]);

  currentNode = nextNode;
}


// redraw the window
void display( void )
{

  if(currentNode==numNodes-1) {
    Real32 t = glutGet(GLUT_ELAPSED_TIME );

    char frameText[256];
    Real32 fps = 1000/(t-lastT);

    lastT = t;

    sprintf(frameText,"%4.2f fps", fps);

    lineVec[0]->assign(frameText);
    fontText.fillTxfNode(n[currentNode], lineVec);
  }

  mgr->redraw();
}

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
	
		if (argc == 1) {
			FFATAL (("Need *.txf or *.ttf font file\n"));	
			return -1;
		}

    // OSG init
    osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setWinID(winid);
    gwin->init();

    PathHandler paths;

    paths.push_backPath(".");
    //paths.push_backPath("/home/elmi/wrk/development/texFont");


    // create the scene
     

    FontStyle *fontStyle = FontStyleFactory::the().create(paths, argv[1], 1);
    assert(fontStyle);
    fontText.setFontStyle(fontStyle);
    fontText.setJustifyMajor(MIDDLE_JT);

    textLine = new string;
    textLine->assign("OpenSG");
    lineVec.push_back(textLine);


    // 3D-Glyphs
    GeometryPtr geo=Geometry::create();
    if(fontText.fillGeo(geo, lineVec, 0.5, 1, 0, FILL_TEX_CHAR_MCM)) {
      n[numNodes] = Node::create();
      beginEditCP(n[numNodes], Node::CoreFieldMask);
      {
	n[numNodes]->setCore(geo);
      }
      endEditCP  (n[numNodes], Node::CoreFieldMask);
      numNodes++;
    }




    // Textured - Text
    Color4ub col1(102,175,250,0);
    Color4ub col2(255,225,41,0);
    Image img;
    
    if(fontText.fillImage(img, lineVec, &col1, &col2)) {
      geo = makeBoxGeo(4,1,0.001, 1, 1, 1);
      SimpleTexturedMaterialPtr mat = SimpleTexturedMaterial::create();
      beginEditCP(mat);
      {
	mat->setImage(&img);
      }
      endEditCP(mat);
      geo->setMaterial(mat);
      n[numNodes] = Node::create();
      beginEditCP(n[numNodes], Node::CoreFieldMask);
      {
	n[numNodes]->setCore(geo);
	
      }
      endEditCP  (n[numNodes], Node::CoreFieldMask);
      numNodes++;
    }


    // TXF-Style Texture+Geometry
    n[numNodes] = Node::create();
    if(fontText.fillTxfNode(n[numNodes], lineVec)) numNodes++;

    if(!numNodes) {
      cerr << "FATAL: could not create anything." << endl;
      exit(1);
    }
    
    scene = Node::create();  
    // add a transformation to make it move     
    trans = Transform::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask  );
    {
        scene->setCore(trans);
        scene->addChild(n[0]);
    }
    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask  );
 

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);

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
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

// react to keys
void keyboard(unsigned char k, int , int )
{
    switch(k)
    {
    case 27:    exit(1);
    case 32:    next_child();
    }
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    // call the redraw function whenever there's nothing else to do
    glutIdleFunc(display);

    return winid;
}
#endif
