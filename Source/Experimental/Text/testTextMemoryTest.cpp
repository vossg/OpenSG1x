// OpenSG Tutorial Example: Text Geometry
//
// This example shows how to use TrueType(tm) Fonts with OSGText
//

#include <OSGConfig.h>

#include <fstream>

#ifdef OSG_HAS_SSTREAM
# include <sstream>
#else
# include <strstream>
#endif

#include <string>
#include <OSGGLUT.h>
#include "OSGLog.h"

#ifndef WIN32

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

#ifdef OSG_WITH_FREETYPE1
#include "OSGFontStyleFactory.h"
#include "OSGTXFFont.h"
#include "OSGTXFFontStyle.h"
#include "OSGTTFontStyle.h"
#include "OSGText.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The pointer to the transformation
TransformPtr        trans;

// The SimpleSceneManager to manage simple applications
SimpleSceneManager  *mgr;

// forward declaration so we can have the interesting stuff upfront
int                 setupGLUT(int *argc, char *argv[]);

NodePtr             scene;
NodePtr             n;
Text                fontText;

std::vector<std::string> lineVec;
Real32                   lastT;

GeometryPtr         txfGeo;

// redraw the window
void display(void)
{
    Real32  t = glutGet(GLUT_ELAPSED_TIME);

    char    frameText[256];
    Real32  fps = 1000 / (t - lastT);

    lastT = t;

    sprintf(frameText, "%4.2f fps", fps);

    lineVec[0].assign(frameText);

    beginEditCP(txfGeo, Geometry::TypesFieldMask | Geometry::LengthsFieldMask |
                    Geometry::IndicesFieldMask |
                    Geometry::IndexMappingFieldMask |
                    Geometry::PositionsFieldMask | Geometry::NormalsFieldMask);
    {
        fontText.fillTXFGeo(*txfGeo, false, lineVec);
    }

    endEditCP(txfGeo, Geometry::TypesFieldMask | Geometry::LengthsFieldMask |
                  Geometry::IndicesFieldMask | Geometry::IndexMappingFieldMask |
                  Geometry::PositionsFieldMask | Geometry::NormalsFieldMask);

    mgr->redraw();
}

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    if(argc == 1)
    {
        FFATAL(("Need *.ttf font file \n"));
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

    // create the scene
    // build a special txf-font with only a small set of characters
    FontStyle   *fontStyle = FontStyleFactory::the().create(paths, argv[1], 1);
    assert(fontStyle);
    ((TTFontStyle *) fontStyle)->createTXFMap((UChar8 *) ". fps0123456789");

    // write it somewhere
#ifdef OSG_HAS_SSTREAM
    std::ostringstream  target;
#else
    std::ostrstream     target;
#endif

    fontStyle->dump(target);

    // stream from memory
#ifdef OSG_HAS_SSTREAM
    std::istringstream source(target.str());
#else
    std::istrstream    source(target.str(), target.pcount());
    FLOG(("Font size: %d byte\n", target.pcount()));
#endif


    // create some font
    TXFFont *font = new TXFFont("whatever", source);

    // prepare fontText...
    fontText.setSize(1);
    font->createInstance(&fontText);

    fontText.setJustifyMajor(MIDDLE_JT);

    lineVec.push_back("0000.00 fps");

    // TXF-Style Texture+Geometry
    n = Node::create();
    txfGeo = Geometry::create();

    ImagePtr   pTxfImg = Image::create();
    if(fontText.fillTXFGeo(*txfGeo, true, lineVec))
    {
        fontText.fillTXFImage(pTxfImg);

        SimpleTexturedMaterialPtr   mat = SimpleTexturedMaterial::create();
        beginEditCP(mat);
        {
            mat->setImage(pTxfImg);
        }

        endEditCP(mat);
        txfGeo->setMaterial(mat);
        beginEditCP(n, Node::CoreFieldMask);
        {
            n->setCore(txfGeo);
        }
    }

    scene = Node::create();

    // add a transformation to make it move
    trans = Transform::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        scene->setCore(trans);
        scene->addChild(n);
    }

    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin);
    mgr->setRoot(scene);

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

// react to keys
void keyboard(unsigned char k, int, int)
{
    switch(k)
    {
    case 27:
        exit(1);
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

/* */
int main(int argc, char **argv)
{
    FFATAL(("Need freeType 1 lib\n"));

    return -1;
}
#endif
#else

/* */
int main(int argc, char **argv)
{
    FFATAL(("Text doesn't work on Windows yet\n"));

    return -1;
}
#endif
