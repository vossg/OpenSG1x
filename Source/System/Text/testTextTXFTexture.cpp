#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGBaseFunctions.h>
#include <OSGTransform.h>
#include <OSGGroup.h>
#include <OSGSimpleStatisticsForeground.h>
#include <OSGSolidBackground.h>
#include <OSGImage.h>
#include <OSGMaterialChunk.h>
#include <OSGTextureTransformChunk.h>
#include <OSGSolidBackground.h>
#include <OSGGeometry.h>

#include "OSGTextTXFFace.h"
#include "OSGTextTXFGlyph.h"
#include "OSGTextFaceFactory.h"

#include <sstream>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE
using namespace std;

#define COMMAND_FAMILY_SANS 701
#define COMMAND_FAMILY_SERIF 702
#define COMMAND_FAMILY_TYPEWRITER 703
#define COMMAND_FAMILY_BASE 704
#define COMMAND_STYLE_PLAIN 301
#define COMMAND_STYLE_BOLD 302
#define COMMAND_STYLE_ITALIC 303
#define COMMAND_STYLE_BOLDITALIC 304
#define COMMAND_SIZE_INC1 401
#define COMMAND_SIZE_INC10 402
#define COMMAND_SIZE_DEC1 403
#define COMMAND_SIZE_DEC10 404
#define COMMAND_GAP_INC1 501
#define COMMAND_GAP_DEC1 502
#define COMMAND_TEXTUREWIDTH_AUTO 601
#define COMMAND_TEXTUREWIDTH_64 602
#define COMMAND_TEXTUREWIDTH_128 603
#define COMMAND_TEXTUREWIDTH_256 604
#define COMMAND_TEXTUREWIDTH_512 605
#define COMMAND_TEXTUREWIDTH_1024 606
#define COMMAND_TEXTUREWIDTH_2048 607
#define COMMAND_TEXTUREWIDTH_4096 608
#define COMMAND_WRITE_TO_FILE 901

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

NodePtr scene;

SimpleStatisticsForegroundPtr statfg;
StatElemDesc<OSG::StatStringElem> familyDesc("family", "The font family");
StatElemDesc<OSG::StatStringElem> styleDesc("style", "The font style");
StatElemDesc<OSG::StatIntElem> sizeDesc("size", "The height of the characters");
StatElemDesc<OSG::StatIntElem> gapDesc("gap", "The gap between characters");
StatElemDesc<OSG::StatStringElem> textureSizeDesc("textureSize", "The size of the texture");

TextTXFFace *face = 0;
string family;
vector<string> families;
TextFace::Style style = TextFace::STYLE_PLAIN;
TextTXFParam param;
string filename;

int mainMenuID;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

// Create the metrics
NodePtr createMetrics(TextTXFFace *face, UInt32 width, UInt32 height)
{
    GeometryPtr geoPtr = Geometry::create();
    beginEditCP(geoPtr);
    {
        GeoPTypesUI8Ptr typesPtr = GeoPTypesUI8::create();
        geoPtr->setTypes(typesPtr);

        GeoPLengthsUI32Ptr lensPtr = GeoPLengthsUI32::create();
        geoPtr->setLengths(lensPtr);

        GeoPositions3fPtr posPtr = GeoPositions3f::create();
        geoPtr->setPositions(posPtr);

        GeoColors3fPtr colorsPtr = GeoColors3f::create();
        colorsPtr->push_back(Color3f(0.f, 0.f, 1.f));
        colorsPtr->push_back(Color3f(1.f, 0.f, 0.f));
        geoPtr->setColors(colorsPtr);

        GeoIndicesUI32Ptr indicesPtr = GeoIndicesUI32::create();
        geoPtr->setIndices(indicesPtr);

        wstring characters = face->getParam().getCharacters();
        wstring::const_iterator it;
        for (it = characters.begin(); it != characters.end(); ++it)
        {
            const TextTXFGlyph &glyph = face->getTXFGlyph(*it);
            typesPtr->push_back(GL_LINE_LOOP);
            lensPtr->push_back(4);
            Real32 left = static_cast<Real32>(width) * -0.5f + glyph.getX();
            Real32 right = left + static_cast<Real32>(glyph.getPixmapWidth());
            Real32 bottom = static_cast<Real32>(height) * -0.5f + glyph.getY();
            Real32 top = bottom + static_cast<Real32>(glyph.getPixmapHeight());
            UInt32 posOffset = posPtr->size();
            posPtr->push_back(Vec3f(left, bottom, 0.f));
            posPtr->push_back(Vec3f(right, bottom, 0.f));
            posPtr->push_back(Vec3f(right, top, 0.f));
            posPtr->push_back(Vec3f(left, top, 0.f));
            indicesPtr->push_back(posOffset);
            indicesPtr->push_back(0);
            indicesPtr->push_back(posOffset + 1);
            indicesPtr->push_back(0);
            indicesPtr->push_back(posOffset + 2);
            indicesPtr->push_back(0);
            indicesPtr->push_back(posOffset + 3);
            indicesPtr->push_back(0);
        }

        // Bounding box
        typesPtr->push_back(GL_LINE_LOOP);
        lensPtr->push_back(4);
        Real32 left = static_cast<Real32>(width) * -0.5f;
        Real32 right = static_cast<Real32>(width) * 0.5f;
        Real32 top = static_cast<Real32>(height) * 0.5f;
        Real32 bottom = static_cast<Real32>(height) * -0.5f;
        UInt32 posOffset = posPtr->size();
        posPtr->push_back(Vec3f(left, bottom, 0.f));
        posPtr->push_back(Vec3f(right, bottom, 0.f));
        posPtr->push_back(Vec3f(right, top, 0.f));
        posPtr->push_back(Vec3f(left, top, 0.f));
        indicesPtr->push_back(posOffset);
        indicesPtr->push_back(1);
        indicesPtr->push_back(posOffset + 1);
        indicesPtr->push_back(1);
        indicesPtr->push_back(posOffset + 2);
        indicesPtr->push_back(1);
        indicesPtr->push_back(posOffset + 3);
        indicesPtr->push_back(1);

        geoPtr->getIndexMapping().clear();
        geoPtr->getIndexMapping().push_back(Geometry::MapPosition);
        geoPtr->getIndexMapping().push_back(Geometry::MapColor);

        SimpleMaterialPtr matPtr = SimpleMaterial::create();
        geoPtr->setMaterial(matPtr);
    }
    endEditCP(geoPtr);

    NodePtr nodePtr = Node::create();
    beginEditCP(nodePtr, Node::CoreFieldMask);
    {
        nodePtr->setCore(geoPtr);
    }
    endEditCP(nodePtr, Node::CoreFieldMask);

    return nodePtr;
}

void updateFace()
{
    // Try to create new face
    if (family.empty() == false)
    {
        TextTXFFace *newFace = TextTXFFace::create(family, style, param);
        if (newFace == 0)
            return;
        subRefP(face);
        face = newFace;
        addRefP(face);
    }
    if (face == 0)
        return;

    // Update information on the screen
    family = face->getFamily();
    statfg->getCollector().getElem(familyDesc)->set(family);
    filename = family;
    string::size_type i;
    for (i = 0; i < filename.size(); )
        if (isalnum(filename[i]) == false)
            filename.erase(i, 1);
        else
            ++i;
    style = face->getStyle();
    StatStringElem *statElem = statfg->getCollector().getElem(styleDesc);
    switch (style)
    {
        case TextFace::STYLE_PLAIN:
            statElem->set("Plain");
            filename.append("-Plain.txf");
            break;
        case TextFace::STYLE_BOLD:
            statElem->set("Bold");
            filename.append("-Bold.txf");
            break;
        case TextFace::STYLE_ITALIC:
            statElem->set("Italic");
            filename.append("-Italic.txf");
            break;
        case TextFace::STYLE_BOLDITALIC:
            statElem->set("Bold & Italic");
            filename.append("-BoldItalic.txf");
            break;
    }
    statfg->getCollector().getElem(sizeDesc)->set(face->getParam().size);
    statfg->getCollector().getElem(gapDesc)->set(face->getParam().gap);
    ImagePtr imagePtr = face->getTexture();
    ostringstream os;
    os << imagePtr->getWidth() << 'x' << imagePtr->getHeight();
    statfg->getCollector().getElem(textureSizeDesc)->set(os.str());
    glutSetMenu(mainMenuID);
    glutChangeToMenuEntry(6, (string("Write to ") + filename).c_str(), COMMAND_WRITE_TO_FILE);
}

void updateScene()
{
    if(face == NULL)
        return;

    // Put it all together into a Geometry NodeCore.
    ImagePtr imagePtr = face->getTexture();
    GeometryPtr geo = makePlaneGeo(imagePtr->getWidth(), imagePtr->getHeight(), 1, 1);
    NodePtr textNode = Node::create();
    beginEditCP(textNode, Node::CoreFieldMask);
    {
        textNode->setCore(geo);
    }
    endEditCP(textNode, Node::CoreFieldMask);
    NodePtr transNodePtr = Node::create();
    TransformPtr transPtr = Transform::create();
    Matrix transMatrix;
    transMatrix.setTranslate(0.f, 0.f, -1.f);
    beginEditCP(transPtr);
    {
        transPtr->setMatrix(transMatrix);
    }
    endEditCP(transPtr);
    beginEditCP(transNodePtr, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        transNodePtr->setCore(transPtr);
        transNodePtr->addChild(textNode);
    }
    endEditCP(transNodePtr, Node::CoreFieldMask | Node::ChildrenFieldMask);

    TextureChunkPtr texChunk = TextureChunk::create();
    beginEditCP(texChunk);
    {
        texChunk->setImage(imagePtr);
        texChunk->setWrapS(GL_CLAMP);
        texChunk->setWrapT(GL_CLAMP);
        texChunk->setMagFilter(GL_NEAREST);
        texChunk->setMinFilter(GL_NEAREST);
        texChunk->setEnvMode(GL_MODULATE);
    }
    endEditCP(texChunk);

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

    ChunkMaterialPtr m = ChunkMaterial::create();
    beginEditCP(m);
    {
        m->addChunk(texChunk);
        m->addChunk(matChunk);
    }
    endEditCP(m);

    beginEditCP(geo, Geometry::MaterialFieldMask);
    {
        geo->setMaterial(m);
    }
    endEditCP(geo, Geometry::MaterialFieldMask);

    beginEditCP(scene, Node::ChildrenFieldMask);
    {
        scene->getMFChildren()->clear();
        scene->addChild(createMetrics(face, imagePtr->getWidth(), imagePtr->getHeight()));
        scene->addChild(transNodePtr);
    }
    endEditCP(scene, Node::ChildrenFieldMask);
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

    statfg = SimpleStatisticsForeground::create();
    beginEditCP(statfg);
    statfg->setSize(25);
    statfg->setColor(Color4f(0,1,0,0.9));
    statfg->addElement(familyDesc, "Family: %s");
    statfg->addElement(styleDesc, "Style: %s");
    statfg->addElement(sizeDesc, "Size: %i");
    statfg->addElement(gapDesc, "Gap: %i");
    statfg->addElement(textureSizeDesc, "Texture Size: %s");
    endEditCP(statfg);

    // Create the background
    SolidBackgroundPtr bg = SolidBackground::create();
    beginEditCP(bg);
    bg->setColor(Color3f(0.1, 0.1, 0.5));
    endEditCP(bg);

    if (argc > 1)
    {
        face = TextTXFFace::createFromFile(argv[1]);
        if (face == 0)
            family = "SANS";
        else
        {
            addRefP(face);
            family.erase();
        }
    }
    else
        family = "SANS";
    updateFace();
    updateScene();

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();

    // add the statistics forground
    beginEditCP(gwin->getPort(0));
    gwin->getPort(0)->getForegrounds().push_back(statfg);
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

void menu(int command)
{
    switch (command)
    {
        case COMMAND_FAMILY_SANS:
            family = "SANS";
            updateFace();
            break;
        case COMMAND_FAMILY_SERIF:
            family = "SERIF";
            updateFace();
            break;
        case COMMAND_FAMILY_TYPEWRITER:
            family = "TYPEWRITER";
            updateFace();
            break;
        case COMMAND_STYLE_PLAIN:
            style = TextFace::STYLE_PLAIN;
            updateFace();
            break;
        case COMMAND_STYLE_BOLD:
            style = TextFace::STYLE_BOLD;
            updateFace();
            break;
        case COMMAND_STYLE_ITALIC:
            style = TextFace::STYLE_ITALIC;
            updateFace();
            break;
        case COMMAND_STYLE_BOLDITALIC:
            style = TextFace::STYLE_BOLDITALIC;
            updateFace();
            break;
        case COMMAND_SIZE_INC1:
            param.size += 1;
            updateFace();
            break;
        case COMMAND_SIZE_INC10:
            param.size += 10;
            updateFace();
            break;
        case COMMAND_SIZE_DEC1:
            if (param.size <= 1)
                param.size = 1;
            else
                param.size -= 1;
            updateFace();
            break;
        case COMMAND_SIZE_DEC10:
            if (param.size <= 11)
                param.size = 1;
            else
                param.size -= 10;
            updateFace();
            break;
        case COMMAND_GAP_INC1:
            param.gap += 1;
            updateFace();
            break;
        case COMMAND_GAP_DEC1:
            if (param.gap <= 0)
                param.gap = 0;
            else
                param.gap -= 1;
            updateFace();
            break;
        case COMMAND_TEXTUREWIDTH_AUTO:
            param.textureWidth = 0;
            updateFace();
            break;
        case COMMAND_TEXTUREWIDTH_64:
            param.textureWidth = 64;
            updateFace();
            break;
        case COMMAND_TEXTUREWIDTH_128:
            param.textureWidth = 128;
            updateFace();
            break;
        case COMMAND_TEXTUREWIDTH_256:
            param.textureWidth = 256;
            updateFace();
            break;
        case COMMAND_TEXTUREWIDTH_512:
            param.textureWidth = 512;
            updateFace();
            break;
        case COMMAND_TEXTUREWIDTH_1024:
            param.textureWidth = 1024;
            updateFace();
            break;
        case COMMAND_TEXTUREWIDTH_2048:
            param.textureWidth = 2048;
            updateFace();
            break;
        case COMMAND_TEXTUREWIDTH_4096:
            param.textureWidth = 4096;
            updateFace();
            break;
        case COMMAND_WRITE_TO_FILE:
            face->writeToFile(filename);
            break;
        default:
            if (command < COMMAND_FAMILY_BASE)
                return;
            family = families[command - COMMAND_FAMILY_BASE];
            updateFace();
    }
    updateScene();
    mgr->showAll();
    glutPostRedisplay();
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

    int familyMenuID = glutCreateMenu(menu);
    glutSetMenu(familyMenuID);
    glutAddMenuEntry("SANS", COMMAND_FAMILY_SANS);
    glutAddMenuEntry("SERIF", COMMAND_FAMILY_SERIF);
    glutAddMenuEntry("TYPEWRITER", COMMAND_FAMILY_TYPEWRITER);
    TextFaceFactory::the().getFontFamilies(families);
    UInt32 i;
    for (i = 0; i < families.size(); ++i)
        glutAddMenuEntry(families[i].c_str(), COMMAND_FAMILY_BASE + i);
    int styleMenuID = glutCreateMenu(menu);
    glutSetMenu(styleMenuID);
    glutAddMenuEntry("Plain", COMMAND_STYLE_PLAIN);
    glutAddMenuEntry("Bold", COMMAND_STYLE_BOLD);
    glutAddMenuEntry("Italic", COMMAND_STYLE_ITALIC);
    glutAddMenuEntry("Bold + Italic", COMMAND_STYLE_BOLDITALIC);
    int sizeMenuID = glutCreateMenu(menu);
    glutSetMenu(sizeMenuID);
    glutAddMenuEntry("Increment size by 1", COMMAND_SIZE_INC1);
    glutAddMenuEntry("Increment size by 10", COMMAND_SIZE_INC10);
    glutAddMenuEntry("Decrement size by 1", COMMAND_SIZE_DEC1);
    glutAddMenuEntry("Decrement size by 10", COMMAND_SIZE_DEC10);
    int gapMenuID = glutCreateMenu(menu);
    glutSetMenu(gapMenuID);
    glutAddMenuEntry("Increment gap by 1", COMMAND_GAP_INC1);
    glutAddMenuEntry("Decrement gap by 1", COMMAND_GAP_DEC1);
    int textureWidthMenuID = glutCreateMenu(menu);
    glutSetMenu(textureWidthMenuID);
    glutAddMenuEntry("Automatic", COMMAND_TEXTUREWIDTH_AUTO);
    glutAddMenuEntry("64", COMMAND_TEXTUREWIDTH_64);
    glutAddMenuEntry("128", COMMAND_TEXTUREWIDTH_128);
    glutAddMenuEntry("256", COMMAND_TEXTUREWIDTH_256);
    glutAddMenuEntry("512", COMMAND_TEXTUREWIDTH_512);
    glutAddMenuEntry("1024", COMMAND_TEXTUREWIDTH_1024);
    glutAddMenuEntry("2048", COMMAND_TEXTUREWIDTH_2048);
    glutAddMenuEntry("4096", COMMAND_TEXTUREWIDTH_4096);
    mainMenuID = glutCreateMenu(menu);
    glutSetMenu(mainMenuID);
    glutAddSubMenu("Family", familyMenuID);
    glutAddSubMenu("Style", styleMenuID);
    glutAddSubMenu("Size", sizeMenuID);
    glutAddSubMenu("Gap", gapMenuID);
    glutAddSubMenu("TextureWidth", textureWidthMenuID);
    glutAddMenuEntry("Write to ", COMMAND_WRITE_TO_FILE);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    return winid;
}
