
#include <OSGConfig.h>

#include <iostream>
#ifdef __sgi
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#else
#include <cmath>
#include <cstdlib>
#include <cstdio>
#endif
#include <assert.h>

#include <OSGLog.h>

#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGBaseFunctions.h>
#include <OSGGeometry.h>
#include <OSGColor.h>
#include <OSGImage.h>

#include <OSGSimpleTexturedMaterial.h>

#include "OSGText.h"
#include "OSGFontStyle.h"
#include "OSGVectorFontGlyph.h"
#include "OSGImageFontGlyph.h"
#include "OSGTXFGlyphInfo.h"

OSG_USING_NAMESPACE

Text::Text(void) :
    _horizontal  (true    ),
    _justifyMajor(BEGIN_JT),
    _justifyMinor(FIRST_JT),
    _leftToRight (true    ),
    _language    (        ),
    _size        (1.f     ),
    _precision   (1.f     ),
    _spacing     (1.f     ),
    _style       (PLAIN_ST),
    _topToBottom (true    ),
    _fontInstance(NULL    ),
    _smoothing   (false   )
{
}

Text::~Text(void)
{
}

bool Text::horizontal(void)
{
    return _horizontal;
}

void Text::setHorizontal(bool horizontal)
{
    _horizontal = horizontal;
}

TEXT_JUSTIFY_TYPE Text::justifyMajor(void)
{
    return _justifyMajor;
}

void Text::setJustifyMajor(TEXT_JUSTIFY_TYPE justify)
{
    _justifyMajor = justify;
}

TEXT_JUSTIFY_TYPE Text::justifyMinor(void)
{
    return _justifyMinor;
}

void Text::setJustifyMinor(TEXT_JUSTIFY_TYPE justify)
{
    _justifyMinor = justify;
}

bool Text::leftToRight(void)
{
    return _leftToRight;
}

void Text::setLeftToRight(bool leftToRight)
{
    _leftToRight = leftToRight;
}

std::string &Text::language(void)
{
    return _language;
}

void Text::setLanguage(std::string language)
{
    _language = std::string(language);
}

Real32 Text::size(void)
{
    return _size;
}

void Text::setSize(Real32 size)
{
    _size = size;
}

Real32 Text::spacing(void)
{
    return _spacing;
}

void Text::setSpacing(Real32 spacing)
{
    _spacing = spacing;
}

FONT_STYLE_TYPE Text::style(void)
{
    return _style;
}

void Text::setStyle(FONT_STYLE_TYPE style)
{
    _style = style;
}

bool Text::topToBottom(void)
{
    return _topToBottom;
}

void Text::setTopToBottom(bool topToBottom)
{
    _topToBottom = topToBottom;
}

void Text::setFontStyle(FontStyle *fi)
{
    _fontInstance = fi;
}

FontStyle *Text::getFontStyle(void)
{
    return _fontInstance;
}

bool Text::fillTXFImage(ImagePtr &image)
{
    Int32   width, height;
    UChar8  *imageMap = NULL;

    if(!_fontInstance)
        return false;

    if(!(imageMap = _fontInstance->getTXFImageMap()))
        return false;

    _fontInstance->getTXFImageSizes(width, height);

    image->set(Image::OSG_LA_PF, width, height, 1, 1, 1, 0.0, imageMap);

    return true;
}

bool Text::fillTXFGeo(Geometry &mesh, bool isNew, 
                      std::vector<std::string> &lineVec)
{
    Int32             numVerts;
    GeoPositions3fPtr pos;
    GeoTexCoords2fPtr tex;

    numVerts = getTXFNVertices(lineVec);

    if(isNew)
    {
        GeoNormals3fPtr  normals = GeoNormals3f::create();
        GeoPTypesUI8Ptr  ftypes  = GeoPTypesUI8::create();

        pos = GeoPositions3f::create();
        tex = GeoTexCoords2f::create();
        
        ftypes->addValue(GL_QUADS);
        normals->addValue(Vec3f(0.0, 0.0, -1.0));

        mesh.setPositions(pos);
        mesh.setTexCoords(tex);
        mesh.setNormals(normals);
        mesh.setTypes(ftypes);
    }
    else
    {
        pos = GeoPositions3fPtr::dcast(mesh.getPositions());
        tex = GeoTexCoords2fPtr::dcast(mesh.getTexCoords());
    }
    
    pos->resize(numVerts);
    tex->resize(numVerts);

    fillTXFArrays(lineVec, &pos->getField()[0], &tex->getField()[0]);
    
    return true;
}


UInt32 Text::getTXFNVertices(std::vector<std::string> &lineVec)
{
    UInt32 numChars = 0;
    
    for(Int32 i = 0; i < lineVec.size(); i++)
    {
        numChars += strlen(lineVec[i].c_str());
    }
    
    return numChars * 4;
}

bool Text::fillTXFArrays(std::vector<std::string> &lineVec, 
                         Pnt3f *points, Vec2f *texcoords)
{
    Int32           i, j, k;
    Int32           sStart, sStop, sStep, lStart, lStop, lStep;
    Int32           numChars, numLineChars;
    Real32          xOff, yOff, scale, tmpWidth, oaWidth;
    TXFGlyphInfo    *currentGlyph;

    numChars = 0;
    for(i = 0; i < lineVec.size(); i++)
    {
        numChars += strlen(lineVec[i].c_str());
    }

    scale = ( (Real32) _fontInstance->getBaselineSkip() *
              _fontInstance->getYRes() );

    oaWidth = 0.f;
    tmpWidth = 0.f;
    for(i = 0; i < lineVec.size(); i++)
    {
        const Char8 *text = lineVec[i].c_str();
        numLineChars = strlen(text);
        for(j = 0; j < numLineChars; j++)
        {
            tmpWidth += _fontInstance->getTXFGlyphInfo(text[j])->getAdvance() / 
                        scale;
        }

        oaWidth = tmpWidth > oaWidth ? tmpWidth : oaWidth;
        tmpWidth = 0;
    }

    yOff = 0.0;
    if(_topToBottom)
    {
        lStart = 0;
        lStop = lineVec.size();
        lStep = 1;
    }
    else
    {
        lStart = lineVec.size() - 1;
        lStop = -1;
        lStep = -1;
    }

    for(k = lStart; k != lStop; k += lStep)
    {
        numLineChars = strlen(lineVec[k].c_str());

        const Char8 *text = lineVec[k].c_str();

        if(_justifyMajor == MIDDLE_JT || _justifyMajor == END_JT)
        {
            for(j = 0; j < numLineChars; j++)
            {
                tmpWidth += 
                        _fontInstance->getTXFGlyphInfo(text[j])->getAdvance() /
                        scale;
            }
        }

        switch(_justifyMajor)
        {
        case FIRST_JT:
        case BEGIN_JT:
            xOff = 0.0;
            break;
        case MIDDLE_JT:
            xOff = tmpWidth / -2;
            break;
        case END_JT:
            xOff = -tmpWidth;
            break;
        default:
            FFATAL(("Invalid _jusifyMajor entry\n"));
            xOff = 0;
        }

        tmpWidth = 0;

        if(_leftToRight)
        {
            sStart = 0;
            sStop = numLineChars;
            sStep = 1;
        }
        else
        {
            sStart = numLineChars - 1;
            sStop = -1;
            sStep = -1;
        }

        for(i = sStart; i != sStop; i += sStep)
        {
            for(j = 0; j < 4; j++, points++, texcoords++)
            {
                currentGlyph = _fontInstance->getTXFGlyphInfo(text[i]);
                points->setValues(currentGlyph->getVertexCoords(j)[0] /
                                                 scale + xOff,
                                  currentGlyph->getVertexCoords(j)[1] /
                                                 scale + yOff, 0.0);

                texcoords->setValues(currentGlyph->getTextureCoords(j)[0],
                                     currentGlyph->getTextureCoords(j)[1]);
            }

            xOff += currentGlyph->getAdvance() / scale;
        }

        yOff -= (Real32) _fontInstance->getBaselineSkip();
    }

    return true;
}

bool Text::fillImage(ImagePtr & image, 
                     std::vector<std::string> &lineVec, 
                     Color4ub *fg,
                     Color4ub *bg, 
                     bool forcePower2, 
                     Real32 *maxX,
                     Real32 *maxY,
                     ImageCreationMode OSG_CHECK_ARG(creationMode),
                     MergeMode OSG_CHECK_ARG(mergeMode), 
                     Int32 pixelDepth,
					 bool bConvertToBitmap ) const
{
    ImageFontGlyph  ***g;
    UChar8          *img = 0;
    const Int32     *res;
    const Char8     *text;
    Int32           pen_x, pen_y, line, xoff, yoff;
    Int32           width = 0, overallWidth = 0, height = 0, overallHeight = 0;
    Int32           i, j, k, l, tmpMinY, tmpMaxY, strStart, strEnd, strStep;
    Int32           p, tmpWidth;
    UChar8          *srcPixel, *imageBuffer = 0, *row = 0, *dstPixel;
    bool            retVal;

    if(forcePower2 && (!maxX || !maxY))
        return false;

    if(_fontInstance)
    {
        g = new ImageFontGlyph **[lineVec.size()];
        for(line = 0; line < (Int32) lineVec.size(); line++)
        {
            text = lineVec[line].c_str();
            g[line] = new ImageFontGlyph *[strlen(text)];
            tmpMinY = INT_MAX;
            tmpMaxY = -INT_MAX;
            for(i = 0; i < (Int32) strlen(text); i++)
            {
                g[line][i] = _fontInstance->getImageGlyph(text[i]);
                if(g[line][i])
                {
                    retVal = g[line][i]->create();
                    if(!retVal)
                    {
                        FWARNING(("Glyph generation failed."));
                        for(line = 0; line < (Int32) lineVec.size(); line++)
                            delete[] g[line];
                        delete[] g;
                    }

                    width += (i + 1 == (Int32) strlen(text) ? 
                                g[line][i]->getImageSize()[0] : 
                                g[line][i]->getAdvance());
                    tmpMinY = g[line][i]->getBoundingBox()[2] < tmpMinY ? 
                                g[line][i]->getBoundingBox()[2] : 
                                tmpMinY;
                    tmpMaxY = g[line][i]->getBoundingBox()[3] > tmpMaxY ? 
                                g[line][i]->getBoundingBox()[3] : 
                                tmpMaxY;
                }
            }

            if(width > overallWidth)
                overallWidth = width;

            if(!tmpMinY && !tmpMaxY)
            {   // TXF-character not present -> all blanks..
                tmpMaxY = 
                    (Int32)osgfloor((Real32)_fontInstance->getBaselineSkip());
            }

            overallHeight += ( line + 1 == lineVec.size() ? 
                   (Int32) osgfloor((abs(tmpMaxY) + abs(tmpMinY)) * _spacing) :
                   (Int32) osgfloor((Real32) _fontInstance->getBaselineSkip() *
                        (Real32) _fontInstance->getYRes() * _spacing));
            width = 0;
        }

        if(forcePower2)
        {
            height = 1;
            while(height < overallHeight)
                height *= 2;
            *maxY = ((Real32)height) / ((Real32)overallHeight);
            overallHeight = height;

            width = 1;
            while(width < overallWidth)
                width *= 2;
            *maxX = ((Real32)width) / ((Real32)overallWidth);
            overallWidth = width;
        }

        imageBuffer = new UChar8[overallWidth * overallHeight * pixelDepth];
        row = new UChar8[overallWidth * pixelDepth];

        for(i = 0; i < overallWidth * pixelDepth;)
        {
            for(l = 0; l < pixelDepth; l++, i++)
                row[i] = (*bg)[l];
        }

        for(i = 0; i < overallHeight; i++)
        {
            memcpy(imageBuffer + i * overallWidth * pixelDepth, row,
                               overallWidth * pixelDepth);
        }

        delete[] row;

        tmpMinY = INT_MAX;
        tmpMaxY = -INT_MAX;

        tmpWidth = 0;
        line = 0;
        for(i = 0; i != (Int32) strlen(lineVec[line].c_str()); i++)
        {
            tmpMinY = g[line][i]->getBoundingBox()[2] < tmpMinY ? 
                        g[line][i]->getBoundingBox()[2] : 
                        tmpMinY;
            tmpMaxY = g[line][i]->getBoundingBox()[3] > tmpMaxY ? 
                        g[line][i]->getBoundingBox()[3] : 
                        tmpMaxY;
            tmpWidth += (i + 1 == (Int32) strlen(text) ? 
                            g[line][i]->getImageSize()[0] : 
                            g[line][i]->getAdvance());
        }

        height = abs(tmpMaxY) + abs(tmpMinY);
        yoff = _topToBottom ? overallHeight - height : 0;

        switch(_justifyMajor)
        {
        case FIRST_JT:
        case BEGIN_JT:
            xoff = 0;
            break;
        case MIDDLE_JT:
            xoff = (overallWidth - tmpWidth) / 2 * pixelDepth;
            break;
        case END_JT:
            xoff = (overallWidth - tmpWidth) * pixelDepth;
            break;
        default:
            FFATAL(("Invalid _justifyMajor entry (%d)\n", _justifyMajor));
            xoff = 0;
        }

        xoff -= g[line][0]->getBoundingBox()[0] * pixelDepth;

        tmpWidth = 0;

        for(line = 0; line < (Int32) lineVec.size(); line++)
        {
            text = lineVec[line].c_str();

            if(_leftToRight)
            {
                strStart = 0;
                strEnd = strlen(text);
                strStep = 1;
            }
            else
            {
                strStart = strlen(text) - 1;
                strEnd = -1;
                strStep = -1;
            }

            for(i = strStart; i != strEnd; i += strStep)
            {
                pen_y = yoff + abs(tmpMinY) + g[line][i]->getBoundingBox()[2];
                pen_x = xoff + (g[line][i]->getBoundingBox()[0] * pixelDepth);
                img = g[line][i]->getImage();
                res = g[line][i]->getImageSize();

                for(j = res[1] - 1; j >= 0; j--)
                {
                    srcPixel = img + ((res[1] - j - 1) * res[2]);

                    dstPixel = imageBuffer + ((pen_y + j) * overallWidth * 
                                    pixelDepth) + pen_x;

                    for(k = 0; k < res[0]; k++, srcPixel++)
                    {
                        if(!(p = *(srcPixel)))
                        {
                            dstPixel += pixelDepth;
                            continue;
                        }

                        for(l = 0; l < pixelDepth; l++, dstPixel++)
                        {
                            *(dstPixel) =
                                    (
                                        (*fg)[l] *
                                        p +
                                        (*bg)[l] *
                                        (4 - p)
                                    ) >>
                                    2;
                        }
                    }
                }

                xoff += (g[line][i]->getAdvance() * pixelDepth);
            }

            if(line + 1 < (Int32) lineVec.size())
            {
                tmpWidth = 0;
                if(_justifyMajor == MIDDLE_JT || _justifyMajor == END_JT)
                {
                    for(i = 0; i != (Int32) strlen(lineVec[line + 1].c_str());
                                            i++)
                    {
                        tmpWidth += 
                            (Int32) osgfloor(g[line + 1][i]->getAdvance());
                    }
                }

                switch(_justifyMajor)
                {
                case FIRST_JT:
                case BEGIN_JT:
                    xoff = 0;
                    break;
                case MIDDLE_JT:
                    xoff = (overallWidth - tmpWidth) / 2 * pixelDepth;
                    break;
                case END_JT:
                    xoff = (overallWidth - tmpWidth) * pixelDepth;
                    break;
                }

                if(line + 1 == (Int32) lineVec.size() - 1)
                {
                    yoff = _topToBottom ? 0 : overallHeight - height;
                }
                else
                {
                    yoff += (_topToBottom ? -1 : 1) * 
                        (Int32) osgfloor(
                            (Real32) _fontInstance->getBaselineSkip()*
                            _fontInstance->getYRes() * _spacing);
                }
            }
        }

        for(line = 0; line < (Int32) lineVec.size(); line++)
            delete[] g[line];
        delete[] g;


		// AT: Convert Image Buffer for usage with glBitmap
		Image::PixelFormat pixelFormat;
		if( bConvertToBitmap )
		{		
			pixelFormat = Image::OSG_L_PF;
#if 1
			//Int32 newOverallWidth = ceil(((float)(overallWidth))/8.0);

			UChar8* bitmapBuffer = new UChar8[ overallWidth * overallHeight ];
			memset( bitmapBuffer, '\0', overallWidth * overallHeight );

			for( int nY=0; nY<overallHeight; nY++ )
			{
				for( int nX=0; nX<overallWidth; nX +=8 )
				{	
					for( int nXplus = 0; (nXplus < 8) && (nXplus+nX < overallWidth); nXplus++ )
					{
						if( (imageBuffer[ ( nY*overallWidth*pixelDepth ) + nX + nXplus ] > 0) )
							bitmapBuffer[ ( nY*overallWidth ) + nX/8 ] += (128 >> nXplus) ;
					}
				}
			}
			delete imageBuffer;
			imageBuffer = bitmapBuffer;
			//overallWidth = newOverallWidth;
#endif

			// AT's conversion ready
		}
		else
		{
			pixelFormat = Image::OSG_RGBA_PF;
		}
		
        return image->set( pixelFormat, // Image::OSG_RGB_PF, 
                           overallWidth, overallHeight, 1, 
                           1, 
                           1, 0.0, imageBuffer);
    }

    return false;
}

bool Text::fillGeo(Geometry & mesh, std::vector<std::string> &lineVec,
                   Real32 precision, Real32 extFac,
                   Real32 OSG_CHECK_ARG(maxExtend),
                   MeshCreationMode creationMode,
                   MergeMode OSG_CHECK_ARG(mergeMode))
{
    Int32           i, j, line, f_norm = 1;;
    Int32           vertOff = 0, faceOff = 0, strOff = 0, glyphOff = 0;
    Int32           diff = 0, numVertices = 0, numFaces = 0;
    Int32           numFrontFaces = 0, numNormals = 0;
    Int32           strStart, strEnd, strStep;
    Int32           lastVert = 0, lastFace = 0, lastNormal = 0, normalOff = 0;
    Int32           glyphNOff = 2, reuseNormals, nstride, facestride = 2;
    bool            retVal = false;
    Real32          zCoord, bb[4], trX = 0.0, trY = 0.0;
    Real32          maxWidth = 0.0, tmpMinY = HUGE_VAL, tmpMaxY = -HUGE_VAL;
    Real32          lineOff = 0.f, off = 0.f, localWidth, localHeight, descent;
    VectorFontGlyph ***g = 0;
    const Char8     *text;

    if (creationMode != FILL_TEX_CHAR_MCM &&
        creationMode != FILL_TEX_ALL_MCM &&
        creationMode != FILL_MCM)
        return false;

    GeoPositions3fPtr points;
	points = GeoPositions3fPtr::dcast(mesh.getPositions());
	if (points == NullFC)
	    points = GeoPositions3f::create();

    GeoNormals3fPtr normals;
	normals = GeoNormals3fPtr::dcast(mesh.getNormals());
	if (normals == NullFC)
	    normals = GeoNormals3f::create();

    GeoTexCoords2fPtr texCoords;
	texCoords = GeoTexCoords2fPtr::dcast(mesh.getTexCoords());
    if (creationMode == FILL_TEX_CHAR_MCM || creationMode == FILL_TEX_ALL_MCM) {
        if (texCoords == NullFC)
		    texCoords = GeoTexCoords2f::create();
    }

    GeoPTypesPtr ftypes;
	ftypes = GeoPTypesPtr::dcast(mesh.getTypes());
	if (ftypes == NullFC)
	    ftypes = GeoPTypesUI8::create();

    GeoPLengthsPtr flengths;
    flengths = GeoPLengthsPtr::dcast(mesh.getLengths());
	if (flengths == NullFC)
	    flengths = GeoPLengthsUI32::create();

    GeoIndicesUI32Ptr faces;
	faces = GeoIndicesUI32Ptr::dcast(mesh.getIndices());
    if (faces == NullFC)
	    faces = GeoIndicesUI32::create();

	beginEditCP(points, FieldBits::AllFields);
    beginEditCP(normals, FieldBits::AllFields);
	if (creationMode == FILL_TEX_CHAR_MCM || creationMode == FILL_TEX_ALL_MCM)
	    beginEditCP(texCoords, FieldBits::AllFields);
	beginEditCP(ftypes, FieldBits::AllFields);
	beginEditCP(flengths, FieldBits::AllFields);
	beginEditCP(faces, FieldBits::AllFields);

	points->clear();
	normals->clear();
	texCoords->clear();
	ftypes->clear();
	flengths->clear();
	faces->clear();

    if(_fontInstance)
    {
        bb[2] = 0;
        bb[3] = 0;
        g = new VectorFontGlyph **[lineVec.size()];

        for(line = 0; line < (Int32) lineVec.size(); line++)
        {
            text = lineVec[line].c_str();
            g[line] = new VectorFontGlyph *[strlen(text)];

            for(i = 0; i < (Int32) strlen(text); i++)
            {
                g[line][i] = _fontInstance->getVectorGlyph(text[i]);
                if(g[line][i])
                {
                    g[line][i]->setPrecision(precision * 2);
                    g[line][i]->setDepth(extFac * g[line][i]->getDepth());
                    retVal = g[line][i]->create();
                    if(!retVal)
                    {
                        FWARNING(("Glyph generation failed."));
                        for(line = 0; line < (Int32) lineVec.size(); line++)
                            delete[] g[line];
                        delete[] g;
                    }

                    numVertices += g[line][i]->getNumPoints() * 
                                    (extFac != 0.0 ? 2 : 1);
                    if(extFac != 0.0)
                    {
                        numFaces += (g[line][i]->getNumIndices()) / 3;
                    }
                    else
                    {
                        numFaces += g[line][i]->getNumFrontFaces();
                    }

                    numFrontFaces += g[line][i]->getNumFrontFaces();
                    if(extFac != 0.0)
                    {
                        numNormals += g[line][i]->getNumNormals();
                    }
                }
                else
                    return false;
            }

            if(_leftToRight)
            {
                strStart = 0;
                strEnd = strlen(text);
                strStep = 1;
            }
            else
            {
                strStart = strlen(text) - 1;
                strEnd = -1;
                strStep = -1;
            }

            if(!line)
                numNormals += 2;

            if(extFac != 0.0)
                numFrontFaces *= 2;

            if(numNormals)
            {
                if(extFac != 0.0)
                {
                    normals->resize(lastNormal + numNormals);
                }
                else if(!line)
                    normals->resize(2);

                if(!line)
                {
                    j = -1;
                    while(!g[line][++j]->getNumPoints());
                    zCoord = g[line][j]->getPoints()[0][2] != 0.0 ? 
                                g[line][j]->getPoints()[0][2] /
                                    fabs(g[line][j]->getPoints()[0][2]) : 
                                -1;

                    if(extFac == 0.0)
                        zCoord *= -1;
                    normals->setValue(Vec3f(0.0, 0.0, zCoord), 0);
                    normals->setValue(Vec3f(0.0, 0.0, zCoord * -1), 1);
                    normalOff = 2;
                }
            }

            faces->resize((lastFace + numFaces) * 3 * facestride);
            flengths->resize(lastFace + numFaces);
            ftypes->resize(lastFace + numFaces);

            points->resize(lastVert + numVertices);

            if (creationMode == FILL_TEX_CHAR_MCM ||
                creationMode == FILL_TEX_ALL_MCM )
            {
                texCoords->resize(lastVert + numVertices);
            }

            bb[0] = g[line][0]->getBoundingBox()[0];
            tmpMinY = g[line][0]->getBoundingBox()[2];
            tmpMaxY = g[line][0]->getBoundingBox()[3];

            for(strOff = strStart; strOff != strEnd; strOff += strStep)
            {
                tmpMinY = g[line][strOff]->getBoundingBox()[2] < tmpMinY ? 
                            g[line][strOff]->getBoundingBox()[2] : 
                            tmpMinY;
                tmpMaxY = g[line][strOff]->getBoundingBox()[3] > tmpMaxY ? 
                            g[line][strOff]->getBoundingBox()[3] : 
                            tmpMaxY;

                if(!g[line][strOff])
                    continue;

                for(i = 0; i < g[line][strOff]->getNumPoints(); i++, vertOff++)
                {
                    points->setValue(
                        Vec3f((g[line][strOff]->getPoints())[i][0] + off,
                              (g[line][strOff]->getPoints())[i][1] + lineOff,
                              (g[line][strOff]->getPoints())[i][2]
                             ), vertOff);
                }

                if(extFac != 0.0)
                {
                    for(i = 0; i < g[line][strOff]->getNumPoints();
                                            i++, vertOff++)
                    {
                        points->setValue(Vec3f(
                            (g[line][strOff]->getPoints())[i][0] + off,
                            (g[line][strOff]->getPoints())[i][1] + lineOff, 
                            (g[line][strOff]->getPoints())[i][2] * -1),
                            vertOff);
                    }

                    for(i = 0; i < g[line][strOff]->getNumNormals();
                                            i++, normalOff++)
                    {
                        normals->setValue(Vec3f(
                            (g[line][strOff]->getNormals())[i][0],
                            (g[line][strOff]->getNormals())[i][1],
                            (g[line][strOff]->getNormals())[i][2]), 
                            normalOff);
                    }
                }

                for(i = lastFace; i < lastFace + numFaces; i++)
                {
                    ftypes->setValue(GL_TRIANGLES, i);
                    flengths->setValue(3, i);
                }

                reuseNormals = g[line][strOff]->getNumNormals();
                for(i = 0; i < g[line][strOff]->getNumIndices();
                                    i++, faceOff += facestride)
                {
                    faces->setValue((g[line][strOff]->getIndices()[i] + 
                                     glyphOff),
                                    faceOff);

                    if(i >= g[line][strOff]->getNumFrontFaces() * 6)
                    {
                        nstride = g[line][strOff]->getNormalIndices()[i];
                        if(nstride >= reuseNormals)
                            nstride -= reuseNormals;
                        faces->setValue(nstride + glyphNOff, faceOff + f_norm);
                    }
                    else
                    {
                        if(i < g[line][strOff]->getNumFrontFaces() * 3)
                        {
                            faces->setValue(0, faceOff + f_norm);
                        }
                        else
                        {
                            faces->setValue(1, faceOff + f_norm);
                        }
                    }
                }

                if(creationMode == FILL_TEX_CHAR_MCM)
                {
                    localWidth = (g[line][strOff]->getAdvance());
                    localHeight = fabs(g[line][strOff]->getBoundingBox()[3]) + 
                                  fabs(g[line][strOff]->getBoundingBox()[2]);
                    descent = fabs(g[line][strOff]->getBoundingBox()[2]);
                    diff = extFac == 0.0 ? 
                                vertOff : 
                                glyphOff + (vertOff - glyphOff) / 2;

                    for(i = glyphOff; i < diff; i++)
                    {
                        texCoords->setValue(Vec2f(
                            (g[line][strOff]->getPoints())[i - glyphOff][0] /
                                localWidth,
                            ((g[line][strOff]->getPoints())[i - glyphOff][1] + 
                                descent) / localHeight), 
                            i);
                    }

                    for(i = diff; i < vertOff; i++)
                    {
                        texCoords->setValue(Vec2f(
                            (g[line][strOff]->getPoints())[i - diff][0] /
                                localWidth,
                            ((g[line][strOff]->getPoints())[i - diff][1] +
                                descent) / localHeight), 
                            i);
                    }
                }

                glyphOff = vertOff;
                glyphNOff = normalOff;
                off += (g[line][strOff]->getAdvance());
            }

            if(_topToBottom)
            {
                bb[3] = line ? bb[3] : tmpMaxY;
                bb[3] = line ? tmpMaxY : bb[3];
                lineOff -= _size * _spacing;
                bb[2] = lineOff;
            }
            else
            {
                bb[2] = line ? tmpMinY : bb[2];;
                lineOff += _size * _spacing;
                bb[3] = lineOff;
            }

            off -= (g[line][strOff - strStep]->getAdvance());
            off += (g[line][strOff - strStep]->getBoundingBox()[1]);
            bb[1] = off;

            switch(_justifyMajor)
            {
            case FIRST_JT:
            case BEGIN_JT:
                trX = 0.0;
                break;
            case MIDDLE_JT:
                trX = -(fabs(bb[0]) + fabs(bb[1])) / 2;
                break;
            case END_JT:
                trX = -bb[1];
                break;
            }

            if(trX != 0.0)
            {
                for(i = 0; i < numVertices; i++)
                {
                    points->setValue(points->getValue(lastVert + i) + 
                                        Vec3f(trX, 0.0, 0.0), 
                                     lastVert + i);
                }
            }

            lastVert += numVertices;
            lastFace += numFaces;
            numVertices = numFaces = 0;

            if(numNormals)
            {
                lastNormal += numNormals;
                numNormals = 0;
            }

            maxWidth = off > maxWidth ? off : maxWidth;
            off = 0;
        }

        if(_topToBottom)
        {
            bb[3] -= (fabs(tmpMaxY) + fabs(tmpMinY)) * _spacing;
        }
        else
        {
            bb[2] += (fabs(tmpMaxY) + fabs(tmpMinY)) * _spacing;
        }

        switch(_justifyMinor)
        {
        case FIRST_JT:
            trY = 0.0;
            break;
        case BEGIN_JT:
            trY = -bb[3];
            break;
        case MIDDLE_JT:
            trY = -(bb[2] + bb[3]) / 2;
            break;
        case END_JT:
            trY = -bb[2];
            break;
        }

        if(trY != 0.0)
        {
            for(i = 0; i < (Int32) points->getSize(); i++)
            {
                points->setValue(points->getValue(lastVert + i) + 
                                    Vec3f(0.0, trY, 0.0),
                                 i);
            }
        }

        if(creationMode == FILL_TEX_ALL_MCM)
        {
            localHeight = fabs(bb[2]) + fabs(bb[3]);

            for(i = 0; i < (Int32) points->getSize(); i++)
            {
                texCoords->setValue(Vec2f(
                    points->getValue(i)[0] / maxWidth,
                    fabs(points->getValue(i)[1] - trY) / localHeight), 
                    i);
            }
        }

        beginEditCP(mesh.getPtr(), FieldBits::AllFields);

		//mesh.invalidateVolume();
		//if (mesh.getDlistCache())
		//	mesh.setDlistCache(false);

        mesh.setPositions(points);
        mesh.setNormals(normals);

        mesh.setTypes(ftypes);
        mesh.setLengths(flengths);
        mesh.setIndices(faces);

        if (creationMode == FILL_TEX_CHAR_MCM || creationMode == FILL_TEX_ALL_MCM)
            mesh.setTexCoords(texCoords);

		mesh.getIndexMapping().clear();

		if(creationMode == FILL_TEX_CHAR_MCM || creationMode == FILL_TEX_ALL_MCM) {
			mesh.getIndexMapping().push_back(Geometry::MapPosition |
											 Geometry::MapTexCoords);
		}
		else {
			mesh.getIndexMapping().push_back(Geometry::MapPosition);
		}
		mesh.getIndexMapping().push_back(Geometry::MapNormal);

        for(line = 0; line < (Int32) lineVec.size(); line++)
            delete[] g[line];
        delete[] g;

        mesh.setMaterial(getDefaultMaterial());

		endEditCP(points, FieldBits::AllFields);
		endEditCP(normals, FieldBits::AllFields);
		if (creationMode == FILL_TEX_CHAR_MCM || creationMode == FILL_TEX_ALL_MCM)
			endEditCP(texCoords, FieldBits::AllFields);
		endEditCP(ftypes, FieldBits::AllFields);
		endEditCP(flengths, FieldBits::AllFields);
		endEditCP(faces, FieldBits::AllFields);

		endEditCP(mesh.getPtr(), FieldBits::AllFields);
        
        return true;
    }

    return false;
}
