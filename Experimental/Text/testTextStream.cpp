// OpenSG Tutorial Example: Text Geometry
//
// This example shows how to use TrueType(tm) Fonts with OSGText
//

#include <OSGLog.h>

#ifdef FREETYPE1_LIB

// Headers
#include <fstream>
#include <strstream>
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


#include "OSGFontStyleFactory.h"
#include "OSGTXFFont.h"
#include "OSGTXFFontStyle.h"
#include "OSGTTFontStyle.h"
#include "OSGText.h"


// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The pointer to the transformation
TransformPtr trans;

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );


NodePtr scene;
NodePtr n;
Text fontText;
string *textLine;
vector<string *> lineVec;
Real32 lastT;


// redraw the window
void display( void )
{
  Real32 t = glutGet(GLUT_ELAPSED_TIME );

  char frameText[256];
  Real32 fps = 1000/(t-lastT);
  
  lastT = t;

  sprintf(frameText,"%4.2f fps", fps);

  lineVec[0]->assign(frameText);
  fontText.fillTxfNode(n, lineVec);

  mgr->redraw();
}

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setWinID(winid);
    gwin->init();

    PathHandler paths;

    //paths.push_backPath("/home/elmi/wrk/development/textMaker/tm_fonts");
    //paths.push_backPath("/home/elmi/wrk/development/texFont");


    // create the scene



    // build a special txf-font with only a little set of characters

    FontStyle *fontStyle = FontStyleFactory::the().create(paths, argv[1], 1);
    assert(fontStyle);
    ((TTFontStyle *)fontStyle)->createTXFMap(". fps0123456789");

    // write it somewhere

#if 0
    ofstream target;
    target.open("statistics.txf");
    fontStyle->dump(target);
    target.close();
#else
    ostrstream target;
    fontStyle->dump(target);
#endif


#if 0
    ifstream source;
    source.open("statistics.txf");

    TXFFont *font = new TXFFont("test.txf", source);

    source.close();
#else
#if 0
    // Hack, to get the stuff into memory
    int bufSize = 100000;
    char *buffer = new char [bufSize];
    int numRead;
    FILE *in = fopen("statistics.txf", "r");

    numRead = fread(buffer, 1, bufSize, in);

    fclose(in);

    istrstream source(buffer, numRead);
#else
    istrstream source(target.str(), target.pcount());
#endif
#endif

    

    TXFFont *font = new TXFFont("test.txf", source);
    font->initFont();


    fontText.setSize(1);
    font->createInstance(&fontText);

    fontText.setJustifyMajor(MIDDLE_JT);

    textLine = new string;
    textLine->assign("0000.00 fps");
    lineVec.push_back(textLine);



    // TXF-Style Texture+Geometry
    n = Node::create();
    if(!fontText.fillTxfNode(n, lineVec)) {
      cerr << "FATAL: could not create anything." << endl;
      exit(1);
    }
    
    scene = Node::create();  
    // add a transformation to make it move     
    trans = Transform::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask  );
    {
        scene->setCore(trans);
        scene->addChild(n);
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
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
    case 27:    exit(1);
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

#else

int main (int argc, char **argv)
{
  FFATAL (("Need freeType 1 lib\n"));
    
  return -1;
}

#endif

