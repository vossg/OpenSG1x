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
NodePtr             n[3];
UInt8               numNodes = 0, currentNode = 0;
Text                fontText;

std::vector<std::string> lineVec;
Real32                   lastT;

/* */
void next_child(void)
{
    UInt8   nextNode = (currentNode + 1) % numNodes;

    scene->replaceChildBy(n[currentNode], n[nextNode]);

    currentNode = nextNode;
}

GeometryPtr txfGeo;

// redraw the window
void display(void)
{
    if(currentNode == numNodes - 1)
    {
        Real32  t = glutGet(GLUT_ELAPSED_TIME);

        char    frameText[256];
        Real32  fps = 1000 / (t - lastT);

        lastT = t;

        sprintf(frameText, "%4.2f fps", fps);

        lineVec[0].assign(frameText);

        beginEditCP(txfGeo, Geometry::PositionsFieldMask |
                            Geometry::TexCoordsFieldMask);
        {
            GeoPositions3fPtr  pos =
                                GeoPositions3fPtr::dcast(txfGeo->getPositions());
            GeoTexCoords2fPtr tex =
                                GeoTexCoords2fPtr::dcast(txfGeo->getTexCoords());
           
            UInt32 n = fontText.getTXFNVertices(lineVec);
            
            pos->resize(n);
            tex->resize(n);
            
            fontText.fillTXFArrays(lineVec, &pos->getField()[0], 
                                            &tex->getField()[0]);
        }

        endEditCP(txfGeo, Geometry::PositionsFieldMask |
                          Geometry::TexCoordsFieldMask);
    }

    mgr->redraw();
}

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
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
    FontStyle   *fontStyle = FontStyleFactory::the().create(paths, argv[1], 1);
    assert(fontStyle);
    fontText.setFontStyle(fontStyle);
    fontText.setJustifyMajor(MIDDLE_JT);

    lineVec.push_back("OpenSG");
    lineVec.push_back("rules");
#if 1
    lineVec.push_back("rules");
    lineVec.push_back("rules");
    lineVec.push_back("rules");
#endif

    // 3D-Glyphs
    GeometryPtr geo = Geometry::create();
    if(fontText.fillGeo(*geo, lineVec, 0.5, 1, 0, FILL_TEX_CHAR_MCM))
    {
        n[numNodes] = Node::create();
        beginEditCP(n[numNodes], Node::CoreFieldMask);
        {
            n[numNodes]->setCore(geo);
        }

        endEditCP(n[numNodes], Node::CoreFieldMask);
        numNodes++;
    }

    // Textured - Text
    Color4ub    col1(102, 175, 250, 0);
    Color4ub    col2(255, 225, 41, 0);
    ImagePtr    pImg = Image::create();

#if 0
    if(fontText.fillImage(pImg, lineVec, &col1, &col2))
    {
        geo = makeBoxGeo(4, 1, 0.001, 1, 1, 1);

        SimpleTexturedMaterialPtr   mat = SimpleTexturedMaterial::create();
        beginEditCP(mat);
        {
            mat->setImage(pImg);
        }

        endEditCP(mat);
        geo->setMaterial(mat);
        n[numNodes] = Node::create();
        beginEditCP(n[numNodes], Node::CoreFieldMask);
        {
            n[numNodes]->setCore(geo);
        }

        endEditCP(n[numNodes], Node::CoreFieldMask);
        numNodes++;
    }
#endif

    // TXF-Style Texture+Geometry
    n[numNodes] = Node::create();
    txfGeo = Geometry::create();

    ImagePtr pTxfImg = Image::create();

    if(fontText.fillTXFGeo(*txfGeo, true, lineVec))
    {
        fontText.fillTXFImage(pTxfImg);

        BlendChunkPtr   bl = BlendChunk::create();
        beginEditCP(bl);
        {
            bl->setAlphaFunc(GL_NOTEQUAL);
            bl->setAlphaValue(0);
        }

        endEditCP(bl);

        SimpleTexturedMaterialPtr   mat = SimpleTexturedMaterial::create();
        beginEditCP(mat);
        {
            mat->setImage(pTxfImg);
            mat->addChunk(bl);
        }

        endEditCP(mat);
        txfGeo->setMaterial(mat);
        beginEditCP(n[numNodes], Node::CoreFieldMask);
        {
            n[numNodes]->setCore(txfGeo);
        }

        numNodes++;
    }

    if(!numNodes)
    {
        std::cerr << "FATAL: could not create anything." << std::endl;
        exit(1);
    }

    scene = Node::create();

    // add a transformation to make it move
    trans = Transform::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        scene->setCore(trans);
        scene->addChild(n[0]);
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
    case 32:
        next_child();
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
    FFATAL(("Freetype1 lib needed\n"));

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
