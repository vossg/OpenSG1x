#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGBaseFunctions.h>
#include <OSGTransform.h>
#include <OSGGroup.h>
#include <OSGScreenGroup.h>
#include <OSGBillboard.h>
#include <OSGSolidBackground.h>
#include <OSGImage.h>
#include <OSGGeometry.h>
#include <OSGGeoFunctions.h>
#include <OSGStatisticsDefaultFont.h>

#include "OSGTextTXFFace.h"
#include "OSGTextTXFGlyph.h"
#include "OSGTextLayoutParam.h"
#include "OSGTextLayoutResult.h"
#include "OSGTextFaceFactory.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE
using namespace std;

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

NodePtr scene;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

NodePtr createRose()
{
    GeometryPtr geoPtr = Geometry::create();
    beginEditCP(geoPtr);
    {
        GeoPTypesUI8Ptr typesPtr = GeoPTypesUI8::create();
        typesPtr->push_back(GL_QUADS);
        geoPtr->setTypes(typesPtr);

        GeoPLengthsUI32Ptr lensPtr = GeoPLengthsUI32::create();
        lensPtr->push_back(96);
        geoPtr->setLengths(lensPtr);

        GeoPositions3fPtr posPtr = GeoPositions3f::create();

        // top
        posPtr->push_back(Vec3f( 0.00f,  1.00f,  0.00f));
        posPtr->push_back(Vec3f( 0.00f,  0.10f,  0.10f));
        posPtr->push_back(Vec3f( 0.05f,  0.05f,  0.05f));
        posPtr->push_back(Vec3f( 0.10f,  0.10f,  0.00f));

        posPtr->push_back(Vec3f( 0.00f,  1.00f,  0.00f));
        posPtr->push_back(Vec3f( 0.10f,  0.10f,  0.00f));
        posPtr->push_back(Vec3f( 0.05f,  0.05f, -0.05f));
        posPtr->push_back(Vec3f( 0.00f,  0.10f, -0.10f));

        posPtr->push_back(Vec3f( 0.00f,  1.00f,  0.00f));
        posPtr->push_back(Vec3f( 0.00f,  0.10f, -0.10f));
        posPtr->push_back(Vec3f(-0.05f,  0.05f, -0.05f));
        posPtr->push_back(Vec3f(-0.10f,  0.10f,  0.00f));

        posPtr->push_back(Vec3f( 0.00f,  1.00f,  0.00f));
        posPtr->push_back(Vec3f(-0.10f,  0.10f,  0.00f));
        posPtr->push_back(Vec3f(-0.05f,  0.05f,  0.05f));
        posPtr->push_back(Vec3f( 0.00f,  0.10f,  0.10f));

        // bottom
        posPtr->push_back(Vec3f( 0.00f, -1.00f,  0.00f));
        posPtr->push_back(Vec3f( 0.10f, -0.10f,  0.00f));
        posPtr->push_back(Vec3f( 0.05f, -0.05f,  0.05f));
        posPtr->push_back(Vec3f( 0.00f, -0.10f,  0.10f));

        posPtr->push_back(Vec3f( 0.00f, -1.00f,  0.00f));
        posPtr->push_back(Vec3f( 0.00f, -0.10f,  0.10f));
        posPtr->push_back(Vec3f(-0.05f, -0.05f,  0.05f));
        posPtr->push_back(Vec3f(-0.10f, -0.10f,  0.00f));

        posPtr->push_back(Vec3f( 0.00f, -1.00f,  0.00f));
        posPtr->push_back(Vec3f(-0.10f, -0.10f,  0.00f));
        posPtr->push_back(Vec3f(-0.05f, -0.05f, -0.05f));
        posPtr->push_back(Vec3f( 0.00f, -0.10f, -0.10f));

        posPtr->push_back(Vec3f( 0.00f, -1.00f,  0.00f));
        posPtr->push_back(Vec3f( 0.00f, -0.10f, -0.10f));
        posPtr->push_back(Vec3f( 0.05f, -0.05f, -0.05f));
        posPtr->push_back(Vec3f( 0.10f, -0.10f,  0.00f));

        // left
        posPtr->push_back(Vec3f(-1.00f,  0.00f,  0.00f));
        posPtr->push_back(Vec3f(-0.10f, -0.10f,  0.00f));
        posPtr->push_back(Vec3f(-0.05f, -0.05f,  0.05f));
        posPtr->push_back(Vec3f(-0.10f,  0.00f,  0.10f));

        posPtr->push_back(Vec3f(-1.00f,  0.00f,  0.00f));
        posPtr->push_back(Vec3f(-0.10f,  0.00f,  0.10f));
        posPtr->push_back(Vec3f(-0.05f,  0.05f,  0.05f));
        posPtr->push_back(Vec3f(-0.10f,  0.10f,  0.00f));

        posPtr->push_back(Vec3f(-1.00f,  0.00f,  0.00f));
        posPtr->push_back(Vec3f(-0.10f,  0.10f,  0.00f));
        posPtr->push_back(Vec3f(-0.05f,  0.05f, -0.05f));
        posPtr->push_back(Vec3f(-0.10f,  0.00f, -0.10f));

        posPtr->push_back(Vec3f(-1.00f,  0.00f,  0.00f));
        posPtr->push_back(Vec3f(-0.10f,  0.00f, -0.10f));
        posPtr->push_back(Vec3f(-0.05f, -0.05f, -0.05f));
        posPtr->push_back(Vec3f(-0.10f, -0.10f,  0.00f));

        // right
        posPtr->push_back(Vec3f( 1.00f,  0.00f,  0.00f));
        posPtr->push_back(Vec3f( 0.10f,  0.00f,  0.10f));
        posPtr->push_back(Vec3f( 0.05f, -0.05f,  0.05f));
        posPtr->push_back(Vec3f( 0.10f, -0.10f,  0.00f));

        posPtr->push_back(Vec3f( 1.00f,  0.00f,  0.00f));
        posPtr->push_back(Vec3f( 0.10f, -0.10f,  0.00f));
        posPtr->push_back(Vec3f( 0.05f, -0.05f, -0.05f));
        posPtr->push_back(Vec3f( 0.10f,  0.00f, -0.10f));

        posPtr->push_back(Vec3f( 1.00f,  0.00f,  0.00f));
        posPtr->push_back(Vec3f( 0.10f,  0.00f, -0.10f));
        posPtr->push_back(Vec3f( 0.05f,  0.05f, -0.05f));
        posPtr->push_back(Vec3f( 0.10f,  0.10f,  0.00f));

        posPtr->push_back(Vec3f( 1.00f,  0.00f,  0.00f));
        posPtr->push_back(Vec3f( 0.10f,  0.10f,  0.00f));
        posPtr->push_back(Vec3f( 0.05f,  0.05f,  0.05f));
        posPtr->push_back(Vec3f( 0.10f,  0.00f,  0.10f));

        // front
        posPtr->push_back(Vec3f( 0.00f,  0.00f,  1.00f));
        posPtr->push_back(Vec3f( 0.10f,  0.00f,  0.10f));
        posPtr->push_back(Vec3f( 0.05f,  0.05f,  0.05f));
        posPtr->push_back(Vec3f( 0.00f,  0.10f,  0.10f));

        posPtr->push_back(Vec3f( 0.00f,  0.00f,  1.00f));
        posPtr->push_back(Vec3f( 0.00f,  0.10f,  0.10f));
        posPtr->push_back(Vec3f(-0.05f,  0.05f,  0.05f));
        posPtr->push_back(Vec3f(-0.10f,  0.00f,  0.10f));

        posPtr->push_back(Vec3f( 0.00f,  0.00f,  1.00f));
        posPtr->push_back(Vec3f(-0.10f,  0.00f,  0.10f));
        posPtr->push_back(Vec3f(-0.05f, -0.05f,  0.05f));
        posPtr->push_back(Vec3f( 0.00f, -0.10f,  0.10f));

        posPtr->push_back(Vec3f( 0.00f,  0.00f,  1.00f));
        posPtr->push_back(Vec3f( 0.00f, -0.10f,  0.10f));
        posPtr->push_back(Vec3f( 0.05f, -0.05f,  0.05f));
        posPtr->push_back(Vec3f( 0.10f,  0.00f,  0.10f));

        // back
        posPtr->push_back(Vec3f( 0.00f,  0.00f, -1.00f));
        posPtr->push_back(Vec3f(-0.10f,  0.00f, -0.10f));
        posPtr->push_back(Vec3f(-0.05f,  0.05f, -0.05f));
        posPtr->push_back(Vec3f( 0.00f,  0.10f, -0.10f));

        posPtr->push_back(Vec3f( 0.00f,  0.00f, -1.00f));
        posPtr->push_back(Vec3f( 0.00f,  0.10f, -0.10f));
        posPtr->push_back(Vec3f( 0.05f,  0.05f, -0.05f));
        posPtr->push_back(Vec3f( 0.10f,  0.00f, -0.10f));

        posPtr->push_back(Vec3f( 0.00f,  0.00f, -1.00f));
        posPtr->push_back(Vec3f( 0.10f,  0.00f, -0.10f));
        posPtr->push_back(Vec3f( 0.05f, -0.05f, -0.05f));
        posPtr->push_back(Vec3f( 0.00f, -0.10f, -0.10f));

        posPtr->push_back(Vec3f( 0.00f,  0.00f, -1.00f));
        posPtr->push_back(Vec3f( 0.00f, -0.10f, -0.10f));
        posPtr->push_back(Vec3f(-0.05f, -0.05f, -0.05f));
        posPtr->push_back(Vec3f(-0.10f,  0.00f, -0.10f));

        geoPtr->setPositions(posPtr);

        SimpleMaterialPtr matPtr = SimpleMaterial::create();
        beginEditCP(matPtr);
        {
            matPtr->setDiffuse(Color3f(1, 0, 0));
        }
        endEditCP(matPtr);
        geoPtr->setMaterial(matPtr);
    }
    endEditCP(geoPtr);

    calcFaceNormals(geoPtr);

    NodePtr nodePtr = Node::create();
    beginEditCP(nodePtr, Node::CoreFieldMask);
    {
        nodePtr->setCore(geoPtr);
    }
    endEditCP(nodePtr, Node::CoreFieldMask);

    return nodePtr;
}

TextTXFFace *face;
ChunkMaterialPtr textMaterial;

NodePtr createTag(const std::string &label, const Vec3f &translation)
{
    TextLayoutParam layoutParam;
    layoutParam.majorAlignment = TextLayoutParam::ALIGN_MIDDLE;
    layoutParam.minorAlignment = TextLayoutParam::ALIGN_MIDDLE;
    TextLayoutResult layoutResult;
    face->layout(label, layoutParam, layoutResult);

    GeometryPtr geo = Geometry::create();
    Real32 size = face->getParam().size;
    face->fillGeo(geo, layoutResult, size);
    NodePtr textNode = Node::create();
    beginEditCP(textNode, Node::CoreFieldMask);
    {
        textNode->setCore(geo);
    }
    endEditCP(textNode, Node::CoreFieldMask);
    beginEditCP(geo, Geometry::MaterialFieldMask);
    {
        geo->setMaterial(textMaterial);
    }
    endEditCP(geo, Geometry::MaterialFieldMask);

    NodePtr screenGroupNodePtr = Node::create();
    GroupPtr screenGroupPtr = ScreenGroup::create();
    beginEditCP(screenGroupNodePtr, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        screenGroupNodePtr->setCore(screenGroupPtr);
        screenGroupNodePtr->addChild(textNode);
    }
    endEditCP(screenGroupNodePtr, Node::CoreFieldMask | Node::ChildrenFieldMask);

    NodePtr billboardNodePtr = Node::create();
    BillboardPtr billboardPtr = Billboard::create();
    beginEditCP(billboardPtr);
    {
        billboardPtr->setAxisOfRotation(Vec3f(0, 0, 0));
        billboardPtr->setFocusOnCamera(false);
        billboardPtr->setAlignToScreen(true);
    }
    endEditCP(billboardPtr);
    beginEditCP(billboardNodePtr, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        billboardNodePtr->setCore(billboardPtr);
        billboardNodePtr->addChild(screenGroupNodePtr);
    }
    endEditCP(billboardNodePtr, Node::CoreFieldMask | Node::ChildrenFieldMask);

    NodePtr nodePtr = Node::create();
    TransformPtr transPtr = Transform::create();
    Matrix transMatrix;
    transMatrix.setTranslate(translation);
    beginEditCP(transPtr);
    {
        transPtr->setMatrix(transMatrix);
    }
    endEditCP(transPtr);
    beginEditCP(nodePtr, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        nodePtr->setCore(transPtr);
        nodePtr->addChild(billboardNodePtr);
    }
    endEditCP(nodePtr, Node::CoreFieldMask | Node::ChildrenFieldMask);

    return nodePtr;
}

void updateScene()
{
    NodePtr roseNodePtr = createRose();

    NodePtr topNodePtr = createTag("top", Vec3f(0, 1, 0));
    NodePtr bottomNodePtr = createTag("bottom", Vec3f(0, -1, 0));
    NodePtr leftNodePtr = createTag("left", Vec3f(-1, 0, 0));
    NodePtr rightNodePtr = createTag("right", Vec3f(1, 0, 0));
    NodePtr frontNodePtr = createTag("front", Vec3f(0, 0, 1));
    NodePtr backNodePtr = createTag("back", Vec3f(0, 0, -1));

    beginEditCP(scene, Node::ChildrenFieldMask);
    {
        scene->addChild(topNodePtr);
        scene->addChild(bottomNodePtr);
        scene->addChild(leftNodePtr);
        scene->addChild(rightNodePtr);
        scene->addChild(frontNodePtr);
        scene->addChild(backNodePtr);
        scene->addChild(roseNodePtr);
    }
    endEditCP(scene, Node::ChildrenFieldMask);

    mgr->showAll();
    glutPostRedisplay();
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
    gwin->setId(winid);
    gwin->init();

    // put the geometry core into a node
    scene = Node::create();
    GroupPtr groupPtr = Group::create();
    beginEditCP(scene, Node::CoreFieldMask);
    {
        scene->setCore(groupPtr);
    }
    endEditCP(scene, Node::CoreFieldMask);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);
    //mgr->getAction()->setFrustumCulling(false);

    // Create the background
    SolidBackgroundPtr bg = SolidBackground::create();
    beginEditCP(bg);
    bg->setColor(Color3f(0.1, 0.1, 0.5));
    endEditCP(bg);

    face = getStatisticsDefaultFont();
    TextureChunkPtr texChunk = getStatisticsDefaultFontTexture();
    MaterialChunkPtr matChunk = MaterialChunk::create();
    beginEditCP(matChunk);
    {
        matChunk->setAmbient(Color4f(1.f, 1.f, 1.f, 1.f));
        matChunk->setDiffuse(Color4f(1.f, 1.f, 1.f, 1.f));
        matChunk->setEmission(Color4f(0.f, 0.f, 0.f, 1.f));
        matChunk->setSpecular(Color4f(0.f, 0.f, 0.f, 1.f));
        matChunk->setShininess(0);
    }
    endEditCP(matChunk);
    BlendChunkPtr blendChunk = BlendChunk::create();
    beginEditCP(blendChunk, BlendChunk::DestFactorFieldMask);
    {
        blendChunk->setSrcFactor(GL_SRC_ALPHA);
        blendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
    }
    endEditCP(blendChunk, BlendChunk::DestFactorFieldMask);
    textMaterial = ChunkMaterial::create();
    beginEditCP(textMaterial);
    {
        textMaterial->addChunk(texChunk);
        textMaterial->addChunk(matChunk);
        textMaterial->addChunk(blendChunk);
    }
    endEditCP(textMaterial);

    updateScene();

    beginEditCP(gwin->getPort(0));
    gwin->getPort(0)->setBackground(bg);
    endEditCP(gwin->getPort(0));

    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

// redraw the window
void display( void )
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    mgr->redraw();
}

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
        case 27:
        {
            osgExit();
            exit(0);
        }
        break;
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

    return winid;
}
