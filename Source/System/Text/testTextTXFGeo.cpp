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
#include <OSGGeometry.h>

#include "OSGTextTXFFace.h"
#include "OSGTextTXFGlyph.h"
#include "OSGTextLayoutParam.h"
#include "OSGTextLayoutResult.h"
#include "OSGTextFaceFactory.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE
using namespace std;

#define COMMAND_FAMILY_SANS 801
#define COMMAND_FAMILY_SERIF 802
#define COMMAND_FAMILY_TYPEWRITER 803
#define COMMAND_FAMILY_BASE 804
#define COMMAND_STYLE_PLAIN 301
#define COMMAND_STYLE_BOLD 302
#define COMMAND_STYLE_ITALIC 303
#define COMMAND_STYLE_BOLDITALIC 304
#define COMMAND_MAJORALIGNMENT_FIRST 101
#define COMMAND_MAJORALIGNMENT_BEGIN 102
#define COMMAND_MAJORALIGNMENT_MIDDLE 103
#define COMMAND_MAJORALIGNMENT_END 104
#define COMMAND_MINORALIGNMENT_FIRST 201
#define COMMAND_MINORALIGNMENT_BEGIN 202
#define COMMAND_MINORALIGNMENT_MIDDLE 203
#define COMMAND_MINORALIGNMENT_END 204
#define COMMAND_HORIZONTAL 401
#define COMMAND_VERTICAL 402
#define COMMAND_LEFTTORIGHT 501
#define COMMAND_RIGHTTOLEFT 502
#define COMMAND_TOPTOBOTTOM 601
#define COMMAND_BOTTOMTOTOP 602
#define COMMAND_WRITE_TO_FILE 701

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

NodePtr scene;

SimpleStatisticsForegroundPtr statfg;
StatElemDesc<OSG::StatStringElem> familyDesc("family", "The font family");
StatElemDesc<OSG::StatStringElem> styleDesc("style", "The font style");
StatElemDesc<OSG::StatStringElem> majorAlignDesc("majorAlignment", "The major alignment");
StatElemDesc<OSG::StatStringElem> minorAlignDesc("minorAlignment", "The minor alignment");
StatElemDesc<OSG::StatStringElem> dirDesc("direction", "The direction (horizontal or vertical)");
StatElemDesc<OSG::StatStringElem> horiDirDesc("horizontal direction", "The horizontal direction (left-to-right or right-to-left)");
StatElemDesc<OSG::StatStringElem> vertDirDesc("vertical direction", "The vertical direction (top-to-bottom or bottom-to-top)");

TextTXFFace *face = 0;
string family= "SANS";
vector<string> families;
TextFace::Style style = TextFace::STYLE_PLAIN;
TextLayoutParam layoutParam;
vector<string> lines;
string filename;

int mainMenuID;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );

// Create the coordinate cross
NodePtr createCoordinateCross()
{
    GeometryPtr geoPtr = Geometry::create();
    beginEditCP(geoPtr);
    {
        GeoPTypesUI8Ptr typesPtr = GeoPTypesUI8::create();
        typesPtr->push_back(GL_LINES);
        geoPtr->setTypes(typesPtr);

        GeoPLengthsUI32Ptr lensPtr = GeoPLengthsUI32::create();
        lensPtr->push_back(6);
        geoPtr->setLengths(lensPtr);

        GeoPositions3fPtr posPtr = GeoPositions3f::create();
        posPtr->push_back(Vec3f(-0.1f, 0.f, 0.f));
        posPtr->push_back(Vec3f(1.f, 0.f, 0.f));
        posPtr->push_back(Vec3f(0.f, -0.1f, 0.f));
        posPtr->push_back(Vec3f(0.f, 1.f, 0.f));
        posPtr->push_back(Vec3f(0.f, 0.f, -0.1f));
        posPtr->push_back(Vec3f(0.f, 0.f, 1.f));
        geoPtr->setPositions(posPtr);

        GeoColors3fPtr colorsPtr = GeoColors3f::create();
        colorsPtr->push_back(Color3f(1.f, 0.f, 0.f));
        colorsPtr->push_back(Color3f(0.f, 1.f, 0.f));
        colorsPtr->push_back(Color3f(0.f, 0.f, 1.f));
        geoPtr->setColors(colorsPtr);

        GeoIndicesUI32Ptr indicesPtr = GeoIndicesUI32::create();
        // X Axis
        indicesPtr->push_back(0);
        indicesPtr->push_back(0);
        indicesPtr->push_back(1);
        indicesPtr->push_back(0);
        // Y Axis
        indicesPtr->push_back(2);
        indicesPtr->push_back(1);
        indicesPtr->push_back(3);
        indicesPtr->push_back(1);
        // Z Axis
        indicesPtr->push_back(4);
        indicesPtr->push_back(2);
        indicesPtr->push_back(5);
        indicesPtr->push_back(2);
        geoPtr->setIndices(indicesPtr);

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

// Create the metrics
NodePtr createMetrics(TextFace *face, Real32 scale, const TextLayoutParam &layoutParam,
                      const TextLayoutResult &layoutResult)
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
        colorsPtr->push_back(Color3f(0.f, 1.f, 0.f));
        colorsPtr->push_back(Color3f(1.f, 1.f, 0.f));
        geoPtr->setColors(colorsPtr);

        GeoIndicesUI32Ptr indicesPtr = GeoIndicesUI32::create();
        geoPtr->setIndices(indicesPtr);

        UInt32 i, numGlyphs = layoutResult.getNumGlyphs();
        for (i = 0; i < numGlyphs; ++i)
        {
            const TextGlyph &glyph = face->getGlyph(layoutResult.indices[i]);
            typesPtr->push_back(GL_LINE_LOOP);
            lensPtr->push_back(4);
            const Vec2f &pos = layoutResult.positions[i];
            Real32 left = pos.x() * scale;
            Real32 right = (pos.x() + glyph.getWidth()) * scale;
            Real32 top = pos.y() * scale;
            Real32 bottom = (pos.y() - glyph.getHeight()) * scale;
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
        Vec2f lowerLeft, upperRight;
        face->calculateBoundingBox(layoutResult, lowerLeft, upperRight);
        typesPtr->push_back(GL_LINE_LOOP);
        lensPtr->push_back(4);
        Real32 left = lowerLeft.x() * scale;
        Real32 right = upperRight.x() * scale;
        Real32 top = upperRight.y() * scale;
        Real32 bottom = lowerLeft.y() * scale;
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

        // Text bounds & Line bounds
        Vec2f pos, textPos, offset;
        if (layoutParam.horizontal == true)
        {
            Real32 lineHeight = face->getHoriAscent() - face->getHoriDescent();
            Real32 spacing = layoutParam.spacing * lineHeight;
            if (layoutParam.topToBottom == true)
            {
                switch (layoutParam.minorAlignment)
                {
                    case TextLayoutParam::ALIGN_BEGIN:
                        break;
                    case TextLayoutParam::ALIGN_FIRST:
                        pos[1] = textPos[1] = face->getHoriAscent();
                        break;
                    case TextLayoutParam::ALIGN_MIDDLE:
                        pos[1] = textPos[1] = (spacing * (layoutResult.lineBounds.size() - 1) + lineHeight) / 2.f;
                        break;
                    case TextLayoutParam::ALIGN_END:
                        pos[1] = textPos[1] = spacing * (layoutResult.lineBounds.size() - 1) + lineHeight;
                        break;
                }
                offset.setValues(0.f, -spacing);
            }
            else
            {
                switch (layoutParam.minorAlignment)
                {
                    case TextLayoutParam::ALIGN_BEGIN:
                        pos[1] = lineHeight;
                        textPos[1] = spacing * (layoutResult.lineBounds.size() - 1) + lineHeight;
                        break;
                    case TextLayoutParam::ALIGN_FIRST:
                        pos[1] = face->getHoriAscent();
                        textPos[1] = spacing * (layoutResult.lineBounds.size() - 1) + face->getHoriAscent();
                        break;
                    case TextLayoutParam::ALIGN_MIDDLE:
                        pos[1] = -(spacing * (layoutResult.lineBounds.size() - 1) + lineHeight) / 2.f + lineHeight;
                        textPos[1] = (spacing * (layoutResult.lineBounds.size() - 1) + lineHeight) / 2.f;
                        break;
                    case TextLayoutParam::ALIGN_END:
                        pos[1] = -spacing * (layoutResult.lineBounds.size() - 1);
                        break;
                }
                offset.setValues(0.f, spacing);
            }
        }
        else
        {
            Real32 lineHeight = face->getVertDescent() - face->getVertAscent();
            Real32 spacing = layoutParam.spacing * lineHeight;
            if (layoutParam.leftToRight == true)
            {
                switch (layoutParam.minorAlignment)
                {
                    case TextLayoutParam::ALIGN_BEGIN:
                        break;
                    case TextLayoutParam::ALIGN_FIRST:
                        pos[0] = textPos[0] = face->getVertAscent();
                        break;
                    case TextLayoutParam::ALIGN_MIDDLE:
                        pos[0] = textPos[0] = -(spacing * (layoutResult.lineBounds.size() - 1) + lineHeight) / 2.f;
                        break;
                    case TextLayoutParam::ALIGN_END:
                        pos[0] = textPos[0] = -spacing * (layoutResult.lineBounds.size() - 1) - lineHeight;
                        break;
                }
                offset.setValues(spacing, 0.f);
            }
            else
            {
                switch (layoutParam.minorAlignment)
                {
                    case TextLayoutParam::ALIGN_BEGIN:
                        pos[0] = -lineHeight;
                        textPos[0] = -spacing * (layoutResult.lineBounds.size() - 1) - lineHeight;
                        break;
                    case TextLayoutParam::ALIGN_FIRST:
                        pos[0] = -face->getVertDescent();
                        textPos[0] = -spacing * (layoutResult.lineBounds.size() - 1) -face->getVertDescent();
                        break;
                    case TextLayoutParam::ALIGN_MIDDLE:
                        pos[0] = (spacing * (layoutResult.lineBounds.size() - 1) + lineHeight) / 2.f - lineHeight;
                        textPos[0] = -(spacing * (layoutResult.lineBounds.size() - 1) + lineHeight) / 2.f;
                        break;
                    case TextLayoutParam::ALIGN_END:
                        pos[0] = spacing * (layoutResult.lineBounds.size() - 1);
                        break;
                }
                offset.setValues(-spacing, 0.f);
            }
        }

        typesPtr->push_back(GL_LINE_LOOP);
        lensPtr->push_back(4);
        left = textPos.x();
        top = textPos.y();
        if (layoutParam.horizontal == true)
            if (layoutParam.leftToRight == true)
                switch (layoutParam.majorAlignment)
                {
                    case TextLayoutParam::ALIGN_BEGIN:
                    case TextLayoutParam::ALIGN_FIRST:
                        break;
                    case TextLayoutParam::ALIGN_MIDDLE:
                        left -= layoutResult.textBounds.x() / 2.f;
                        break;
                    case TextLayoutParam::ALIGN_END:
                        left -= layoutResult.textBounds.x();
                        break;
                }
            else
                switch (layoutParam.majorAlignment)
                {
                    case TextLayoutParam::ALIGN_BEGIN:
                    case TextLayoutParam::ALIGN_FIRST:
                        left -= layoutResult.textBounds.x();
                        break;
                    case TextLayoutParam::ALIGN_MIDDLE:
                        left -= layoutResult.textBounds.x() / 2.f;
                        break;
                    case TextLayoutParam::ALIGN_END:
                        break;
                }
        else
            if (layoutParam.topToBottom == true)
                switch (layoutParam.majorAlignment)
                {
                    case TextLayoutParam::ALIGN_BEGIN:
                    case TextLayoutParam::ALIGN_FIRST:
                        break;
                    case TextLayoutParam::ALIGN_MIDDLE:
                        top += layoutResult.textBounds.y() / 2.f;
                        break;
                    case TextLayoutParam::ALIGN_END:
                        top += layoutResult.textBounds.y();
                        break;
                }
            else
                switch (layoutParam.majorAlignment)
                {
                    case TextLayoutParam::ALIGN_BEGIN:
                    case TextLayoutParam::ALIGN_FIRST:
                        top += layoutResult.textBounds.y();
                        break;
                    case TextLayoutParam::ALIGN_MIDDLE:
                        top += layoutResult.textBounds.y() / 2.f;
                        break;
                    case TextLayoutParam::ALIGN_END:
                        break;
                }
        left *= scale;
        right = left + layoutResult.textBounds.x() * scale;
        top *= scale;
        bottom = top - layoutResult.textBounds.y() * scale;
        posOffset = posPtr->size();
        posPtr->push_back(Vec3f(left, bottom, 0.f));
        posPtr->push_back(Vec3f(right, bottom, 0.f));
        posPtr->push_back(Vec3f(right, top, 0.f));
        posPtr->push_back(Vec3f(left, top, 0.f));
        indicesPtr->push_back(posOffset);
        indicesPtr->push_back(3);
        indicesPtr->push_back(posOffset + 1);
        indicesPtr->push_back(3);
        indicesPtr->push_back(posOffset + 2);
        indicesPtr->push_back(3);
        indicesPtr->push_back(posOffset + 3);
        indicesPtr->push_back(3);

        vector<Vec2f>::const_iterator lbIt;
        for (lbIt = layoutResult.lineBounds.begin(); lbIt != layoutResult.lineBounds.end(); ++lbIt)
        {
            typesPtr->push_back(GL_LINE_LOOP);
            lensPtr->push_back(4);
            Real32 left = pos.x();
            Real32 top = pos.y();
            if (layoutParam.horizontal == true)
                if (layoutParam.leftToRight == true)
                    switch (layoutParam.majorAlignment)
                    {
                        case TextLayoutParam::ALIGN_BEGIN:
                        case TextLayoutParam::ALIGN_FIRST:
                            break;
                        case TextLayoutParam::ALIGN_MIDDLE:
                            left -= lbIt->x() / 2.f;
                            break;
                        case TextLayoutParam::ALIGN_END:
                            left -= lbIt->x();
                            break;
                    }
                else
                    switch (layoutParam.majorAlignment)
                    {
                        case TextLayoutParam::ALIGN_BEGIN:
                        case TextLayoutParam::ALIGN_FIRST:
                            left -= lbIt->x();
                            break;
                        case TextLayoutParam::ALIGN_MIDDLE:
                            left -= lbIt->x() / 2.f;
                            break;
                        case TextLayoutParam::ALIGN_END:
                            break;
                    }
            else
                if (layoutParam.topToBottom == true)
                    switch (layoutParam.majorAlignment)
                    {
                        case TextLayoutParam::ALIGN_BEGIN:
                        case TextLayoutParam::ALIGN_FIRST:
                            break;
                        case TextLayoutParam::ALIGN_MIDDLE:
                            top += lbIt->y() / 2.f;
                            break;
                        case TextLayoutParam::ALIGN_END:
                            top += lbIt->y();
                            break;
                    }
                else
                    switch (layoutParam.majorAlignment)
                    {
                        case TextLayoutParam::ALIGN_BEGIN:
                        case TextLayoutParam::ALIGN_FIRST:
                            top += lbIt->y();
                            break;
                        case TextLayoutParam::ALIGN_MIDDLE:
                            top += lbIt->y() / 2.f;
                            break;
                        case TextLayoutParam::ALIGN_END:
                            break;
                    }
            left *= scale;
            Real32 right = left + lbIt->x() * scale;
            top *= scale;
            Real32 bottom = top - lbIt->y() * scale;
            UInt32 posOffset = posPtr->size();
            posPtr->push_back(Vec3f(left, bottom, 0.f));
            posPtr->push_back(Vec3f(right, bottom, 0.f));
            posPtr->push_back(Vec3f(right, top, 0.f));
            posPtr->push_back(Vec3f(left, top, 0.f));
            indicesPtr->push_back(posOffset);
            indicesPtr->push_back(2);
            indicesPtr->push_back(posOffset + 1);
            indicesPtr->push_back(2);
            indicesPtr->push_back(posOffset + 2);
            indicesPtr->push_back(2);
            indicesPtr->push_back(posOffset + 3);
            indicesPtr->push_back(2);

            typesPtr->push_back(GL_LINE_STRIP);
            lensPtr->push_back(2);
            posOffset = posPtr->size();
            if (layoutParam.horizontal == true)
            {
                Real32 base = top - face->getHoriAscent() * scale;
                posPtr->push_back(Vec3f(left, base, 0.f));
                posPtr->push_back(Vec3f(right, base, 0.f));
            }
            else
            {
                Real32 base = left - face->getVertAscent() * scale;
                posPtr->push_back(Vec3f(base, top, 0.f));
                posPtr->push_back(Vec3f(base, bottom, 0.f));
            }
            indicesPtr->push_back(posOffset);
            indicesPtr->push_back(2);
            indicesPtr->push_back(posOffset + 1);
            indicesPtr->push_back(2);
            pos += offset;
        }

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
    //TextTXFFace *newFace = TextTXFFace::createFromFile("./haeberli.txf");
    TextTXFFace *newFace = TextTXFFace::create(family, style);
    if (newFace == 0)
        return;
    subRefP(face);
    face = newFace;
    addRefP(face);

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
    glutSetMenu(mainMenuID);
    glutChangeToMenuEntry(8, (string("Write to ") + filename).c_str(), COMMAND_WRITE_TO_FILE);
}

const char *alignmentToString(TextLayoutParam::Alignment alignment)
{
    switch (alignment)
    {
        case TextLayoutParam::ALIGN_FIRST:
            return "First";
        case TextLayoutParam::ALIGN_BEGIN:
            return "Begin";
        case TextLayoutParam::ALIGN_MIDDLE:
            return "Middle";
        case TextLayoutParam::ALIGN_END:
            return "End";
        default:
            return "???";
    }
}

void updateScene()
{
    statfg->getCollector().getElem(majorAlignDesc)->set(alignmentToString(layoutParam.majorAlignment));
    statfg->getCollector().getElem(minorAlignDesc)->set(alignmentToString(layoutParam.minorAlignment));
    statfg->getCollector().getElem(dirDesc)->set(layoutParam.horizontal ? "Horizontal" : "Vertical");
    statfg->getCollector().getElem(horiDirDesc)->set(layoutParam.leftToRight ? "Left to right" : "Right to left");
    statfg->getCollector().getElem(vertDirDesc)->set(layoutParam.topToBottom ? "Top to bottom" : "Bottom to top");

    if(face == NULL)
        return;

    // Put it all together into a Geometry NodeCore.
    TextLayoutResult layoutResult;
    Real32 scale = 2.f;
    face->layout(lines, layoutParam, layoutResult);
#if 0
    GeometryPtr geo = Geometry::create();
    face->fillGeo(geo, layoutResult, scale);
    NodePtr textNode = Node::create();
    beginEditCP(textNode, Node::CoreFieldMask);
    {
        textNode->setCore(geo);
    }
    endEditCP(textNode, Node::CoreFieldMask);
#else
    NodePtr textNode = face->makeNode(layoutResult, scale);
    GeometryPtr geo = GeometryPtr::dcast(textNode->getCore());
#endif
    NodePtr transNodePtr = Node::create();
    TransformPtr transPtr = Transform::create();
    Matrix transMatrix;
    transMatrix.setTranslate(0.f, 0.f, -0.03f);
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

    ImagePtr imagePtr = face->getTexture();
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
        scene->addChild(createCoordinateCross());
        scene->addChild(createMetrics(face, scale, layoutParam, layoutResult));
        scene->addChild(transNodePtr);
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

    lines.push_back(argc >= 2 ? argv[1] : "Hello World!");
    lines.push_back("Powered by OpenSG");
    lines.push_back("3rd line");
    layoutParam.spacing = 1.5f;
    //layoutParam.length.push_back(10.f);
    //layoutParam.length.push_back(7.f);
    //layoutParam.length.push_back(-1.f);

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

    statfg = SimpleStatisticsForeground::create();
    beginEditCP(statfg);
    statfg->setSize(25);
    statfg->setColor(Color4f(0,1,0,0.9));
    statfg->addElement(familyDesc, "Family: %s");
    statfg->addElement(styleDesc, "Style: %s");
    statfg->addElement(majorAlignDesc, "Major Alignment: %s");
    statfg->addElement(minorAlignDesc, "Minor Alignment: %s");
    statfg->addElement(dirDesc, "%s");
    statfg->addElement(horiDirDesc, "%s");
    statfg->addElement(vertDirDesc, "%s");
    endEditCP(statfg);

    // Create the background
    SolidBackgroundPtr bg = SolidBackground::create();
    beginEditCP(bg);
    bg->setColor(Color3f(0.1, 0.1, 0.5));
    endEditCP(bg);

    updateFace();
    updateScene();

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
            updateScene();
            break;
        case COMMAND_FAMILY_SERIF:
            family = "SERIF";
            updateFace();
            updateScene();
            break;
        case COMMAND_FAMILY_TYPEWRITER:
            family = "TYPEWRITER";
            updateFace();
            updateScene();
            break;
        case COMMAND_STYLE_PLAIN:
            style = TextFace::STYLE_PLAIN;
            updateFace();
            updateScene();
            break;
        case COMMAND_STYLE_BOLD:
            style = TextFace::STYLE_BOLD;
            updateFace();
            updateScene();
            break;
        case COMMAND_STYLE_ITALIC:
            style = TextFace::STYLE_ITALIC;
            updateFace();
            updateScene();
            break;
        case COMMAND_STYLE_BOLDITALIC:
            style = TextFace::STYLE_BOLDITALIC;
            updateFace();
            updateScene();
            break;
        case COMMAND_MAJORALIGNMENT_FIRST:
            layoutParam.majorAlignment = TextLayoutParam::ALIGN_FIRST;
            updateScene();
            break;
        case COMMAND_MAJORALIGNMENT_BEGIN:
            layoutParam.majorAlignment = TextLayoutParam::ALIGN_BEGIN;
            updateScene();
            break;
        case COMMAND_MAJORALIGNMENT_MIDDLE:
            layoutParam.majorAlignment = TextLayoutParam::ALIGN_MIDDLE;
            updateScene();
            break;
        case COMMAND_MAJORALIGNMENT_END:
            layoutParam.majorAlignment = TextLayoutParam::ALIGN_END;
            updateScene();
            break;
        case COMMAND_MINORALIGNMENT_FIRST:
            layoutParam.minorAlignment = TextLayoutParam::ALIGN_FIRST;
            updateScene();
            break;
        case COMMAND_MINORALIGNMENT_BEGIN:
            layoutParam.minorAlignment = TextLayoutParam::ALIGN_BEGIN;
            updateScene();
            break;
        case COMMAND_MINORALIGNMENT_MIDDLE:
            layoutParam.minorAlignment = TextLayoutParam::ALIGN_MIDDLE;
            updateScene();
            break;
        case COMMAND_MINORALIGNMENT_END:
            layoutParam.minorAlignment = TextLayoutParam::ALIGN_END;
            updateScene();
            break;
        case COMMAND_HORIZONTAL:
            layoutParam.horizontal = true;
            glutSetMenu(mainMenuID);
            glutChangeToMenuEntry(5, "Vertical", COMMAND_VERTICAL);
            updateScene();
            break;
        case COMMAND_VERTICAL:
            layoutParam.horizontal = false;
            glutSetMenu(mainMenuID);
            glutChangeToMenuEntry(5, "Horizontal", COMMAND_HORIZONTAL);
            updateScene();
            break;
        case COMMAND_LEFTTORIGHT:
            layoutParam.leftToRight = true;
            glutSetMenu(mainMenuID);
            glutChangeToMenuEntry(6, "Right to left", COMMAND_RIGHTTOLEFT);
            updateScene();
            break;
        case COMMAND_RIGHTTOLEFT:
            layoutParam.leftToRight = false;
            glutSetMenu(mainMenuID);
            glutChangeToMenuEntry(6, "Left to right", COMMAND_LEFTTORIGHT);
            updateScene();
            break;
        case COMMAND_TOPTOBOTTOM:
            layoutParam.topToBottom = true;
            glutSetMenu(mainMenuID);
            glutChangeToMenuEntry(7, "Bottom to top", COMMAND_BOTTOMTOTOP);
            updateScene();
            break;
        case COMMAND_BOTTOMTOTOP:
            layoutParam.topToBottom = false;
            glutSetMenu(mainMenuID);
            glutChangeToMenuEntry(7, "Top to bottom", COMMAND_TOPTOBOTTOM);
            updateScene();
            break;
        case COMMAND_WRITE_TO_FILE:
            face->writeToFile(filename);
            break;
        default:
            if (command < COMMAND_FAMILY_BASE)
                return;
            family = families[command - COMMAND_FAMILY_BASE];
            updateFace();
            updateScene();
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
    int majorAlignmentMenuID = glutCreateMenu(menu);
    glutSetMenu(majorAlignmentMenuID);
    glutAddMenuEntry("First", COMMAND_MAJORALIGNMENT_FIRST);
    glutAddMenuEntry("Begin", COMMAND_MAJORALIGNMENT_BEGIN);
    glutAddMenuEntry("Middle", COMMAND_MAJORALIGNMENT_MIDDLE);
    glutAddMenuEntry("End", COMMAND_MAJORALIGNMENT_END);
    int minorAlignmentMenuID = glutCreateMenu(menu);
    glutSetMenu(minorAlignmentMenuID);
    glutAddMenuEntry("First", COMMAND_MINORALIGNMENT_FIRST);
    glutAddMenuEntry("Begin", COMMAND_MINORALIGNMENT_BEGIN);
    glutAddMenuEntry("Middle", COMMAND_MINORALIGNMENT_MIDDLE);
    glutAddMenuEntry("End", COMMAND_MINORALIGNMENT_END);
    mainMenuID = glutCreateMenu(menu);
    glutSetMenu(mainMenuID);
    glutAddSubMenu("Family", familyMenuID);
    glutAddSubMenu("Style", styleMenuID);
    glutAddSubMenu("Major Alignment", majorAlignmentMenuID);
    glutAddSubMenu("Minor Alignment", minorAlignmentMenuID);
    glutAddMenuEntry("Vertical", COMMAND_VERTICAL);
    glutAddMenuEntry("Right to left", COMMAND_RIGHTTOLEFT);
    glutAddMenuEntry("Bottom to top", COMMAND_BOTTOMTOTOP);
    glutAddMenuEntry("Write to ", COMMAND_WRITE_TO_FILE);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    return winid;
}
