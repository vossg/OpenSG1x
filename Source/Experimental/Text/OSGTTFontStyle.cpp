
#include <OSGConfig.h>

#ifdef OSG_WITH_FREETYPE1
#ifdef __sgi
#include <math.h>
#else
#include <cmath>
#endif
#include <iostream>

#include <stdio.h>
#include <string.h>

#include <OSGLog.h>
#include <OSGBaseFunctions.h>

#include "OSGTTVectorFontGlyph.h"
#include "OSGTTImageFontGlyph.h"
#include "OSGTXFGlyphInfo.h"

#include "OSGTTFontStyle.h"

#include <assert.h>

OSG_USING_NAMESPACE


bool TTFontStyle::processChange(void)
{
    return false;
}

TTFontStyle::TTFontStyle(void) :
     Inherited (    ),
    _ttInstance(NULL),
    _ttFace    (NULL),
    _ttError   (0L  )
{
}

TTFontStyle::~TTFontStyle(void)
{
}

VectorFontGlyph *TTFontStyle::getVectorGlyph(UInt8 ascii)
{
    return _vectorGlyphs[ascii];
}

ImageFontGlyph *TTFontStyle::getImageGlyph(UInt8 ascii)
{
    return _imageGlyphs[ascii];
}

TXFGlyphInfo *TTFontStyle::getTXFGlyphInfo(UInt8 which)
{
    if(!_txfImageMap)
        createTXFMap();

    if(which >= _txfGlyphInfos.size())
    {
        return _txfGlyphInfos[_txfGlyphInfos[0]->remapped()];
    }

    if(_txfGlyphInfos[which]->remapped())
    {
        return _txfGlyphInfos[_txfGlyphInfos[which]->remapped()];
    }

    return _txfGlyphInfos[which];
}

bool TTFontStyle::set_ttInstance(TT_Instance *ttInstance, TT_Face *ttFace)
{
    TT_UShort           ttPlatformID = 0, ttEncodingID = 0;
    TT_CharMap          ttCharMap;
    TT_Face_Properties  ttFaceProps;
    TT_Instance_Metrics ttInstMetrics;
    Int32               i;
    Real32              scaling;

    _ttError = TT_New_Instance(*ttFace, ttInstance);

    if(_ttError)
    {
        FWARNING(("Create TT_New_Instance failed with TT_Error= %d", 
                  _ttError));

        return false;
    }

    _ttError = TT_Set_Instance_Resolutions(*ttInstance, getXRes(), getYRes());
    if(_ttError)
    {
        FWARNING((
            "Create TT_Set_Instance_Resolutions failed with TT_Error= %d",
            _ttError));

        return false;
    }

    _ttError = TT_Set_Instance_PointSize(*ttInstance, 
                                         (Int32) osgfloor(64 * getSize()));
    if(_ttError)
    {
        FWARNING((
            "Create Create TT_Set_Instance_PointSize failed with TT_Error= %d",
            _ttError));

        return false;
    }

    TT_Get_Face_Properties(*ttFace, &ttFaceProps);

    TT_Get_Instance_Metrics(*ttInstance, &ttInstMetrics);

    setMaxAscent((ttFaceProps.os2->sTypoAscender *
                         (((Real32) ttInstMetrics.y_scale) / 65536)) / 4096);

    setMaxDescent((ttFaceProps.os2->sTypoDescender *
                          (((Real32) ttInstMetrics.y_scale) / 65536)) / 4096);

    //     setBaselineSkip(getMaxAscent() - getMaxDescent() +
    // 		    (Real32)ttFaceProps.os2->sTypoLineGap/4096);
    //     scaling = getBaselineSkip()*getYRes();

    setBaselineSkip(getSize());

    scaling = getBaselineSkip();

    for(i = 0; i < ttFaceProps.num_CharMaps; i++)
    {
        TT_Get_CharMap_ID(*ttFace, i, &ttPlatformID, &ttEncodingID);
        if((ttPlatformID == 3 && ttEncodingID == 1) ||
                   (!ttPlatformID && !ttEncodingID))
        {
            TT_Get_CharMap(*ttFace, i, &ttCharMap);
            break;
        }
    }

    if(i == ttFaceProps.num_CharMaps)
    {
        FWARNING(("Font does not contain a unicode-character-map."));
        return false;
    }

    TTVectorFontGlyph   *vGlyphs = new TTVectorFontGlyph[256];
    TTImageFontGlyph    *iGlyphs = new TTImageFontGlyph[256];
    for(Int32 i = 0; i < 256; i++)
    {
        vGlyphs[i].setup(VGLYPH_FACE, i, TT_Char_Index(ttCharMap, i));
        vGlyphs[i].setFontDefs(ttFace, ttInstance);
        vGlyphs[i].setDepth(getSize());
        vGlyphs[i].setSize(getSize());
        vGlyphs[i].setScaleFactor(scaling);
        _vectorGlyphs.push_back(&vGlyphs[i]);

        iGlyphs[i].setup(IGLYPH_PIXMAP, i, TT_Char_Index(ttCharMap, i));
        iGlyphs[i].setFontDefs(ttFace, ttInstance);
        iGlyphs[i].setSize(getSize());
        _imageGlyphs.push_back(&iGlyphs[i]);
    }

    _ttInstance = ttInstance;
    _ttFace = ttFace;

    return true;
}

Int32 cmpIGlyphs(void *g1, void *g2)
{
    return 
        ((ImageFontGlyph *) g2)->getImageSize()[1] - 
        ((ImageFontGlyph *) g1)->getImageSize()[1];
}

void qsortIGlyphs(Int32                          numGlyphs, 
                  UChar8                        *indices,
                  std::vector<ImageFontGlyph *>  iGlyphs)
{
    UChar8  split, *upper, *lower, up = 1;

    if(numGlyphs <= 1)
        return;

    lower = indices;
    upper = lower + numGlyphs - 1;
    split = *upper;

    while(lower != upper)
    {
        if(up)
        {
            if(cmpIGlyphs(iGlyphs[*lower], iGlyphs[split]) > 0)
            {
                *upper = *lower;
                up = 0;
            }
        }
        else
        {
            if(cmpIGlyphs(iGlyphs[*upper], iGlyphs[split]) < 0)
            {
                *lower = *upper;
                up = 1;
            }
        }

        if(up)
            lower++;
        else
            upper--;
    }

    *upper++ = split;

    qsortIGlyphs(lower - indices, indices, iGlyphs);
    qsortIGlyphs(indices + numGlyphs - upper, upper, iGlyphs);
}

bool TTFontStyle::createTXFMap(UChar8 *characters, Int32 gap)
{
    Int32           i, j, k, numChars, numCreated = 0, width, height, x, y;
    Int32           start, current, rowHeight, spaceLeft, numSorted;
    const Int32     *res, *bb;
    UChar8          *createdIndices = NULL, *sortedIndices = NULL, *
        imageBuffer = NULL;
    UChar8          *img, *srcPixel, *dstPixel;
    TXFGlyphInfo    *glyph = NULL;
    Real32          x_f, y_f, xstep, ystep, scale;
    bool            retVal;
    Int16           *dims;

    if(characters)
    {
        numChars = strlen(reinterpret_cast < char * > (characters));
        start = 0;
    }
    else
    {
        numChars = 256;
        start = 1;
    }

    createdIndices = new UChar8[numChars];

    for(i = start; i < numChars; i++)
    {
        retVal = _imageGlyphs[characters ? characters[i] : i]->create();

        if(retVal)
        {
            createdIndices[numCreated++] = 
                (UChar8) (characters ? characters[i] : i);
        }
    }

    qsortIGlyphs(numCreated, createdIndices, _imageGlyphs);

    for(i = 0; i < 256; i++)
    {
        glyph = new TXFGlyphInfo;
        glyph->remap('?');
        _txfGlyphInfos.push_back(glyph);
    }

    width = 512;
    i = 0;
    x = gap;
    y = gap;

    sortedIndices = new UChar8[numCreated];
    numSorted = 0;
    while(true)
    {
        current = createdIndices[i];
        if(!current)
        {
            if(++i >= numCreated)
                break;
            continue;
        }

        res = _imageGlyphs[current]->getImageSize();

        if(res[0] && res[1] || current == ' ')
        {
            if(res[0] + x >= width)
            {
                spaceLeft = width - x;
                for(j = i + 1; j < numCreated; j++)
                {
                    if(createdIndices[j] &&
                       _imageGlyphs[createdIndices[j]]->getImageSize()[0] < 
                            spaceLeft)
                    {
                        current = createdIndices[j];
                        createdIndices[j] = 0;
                        res = _imageGlyphs[current]->getImageSize();
                        i--;
                        break;
                    }
                }

                if(current == createdIndices[i])
                    x = gap;
            }

            if(x == gap)
            {
                if(i)
                    y += rowHeight + gap;
                rowHeight = res[1];
            }

            sortedIndices[numSorted++] = current;

            x += res[0] + gap;
        }

        if(current == createdIndices[i])
            createdIndices[i] = 0;
        if(++i >= numCreated)
            break;
    }

    height = 1;
    while(height < y + rowHeight + gap)
        height *= 2;
    imageBuffer = new UChar8[width * height * 2];
    memset(imageBuffer, 0, width * height * 2);

    i = 0;
    x = gap;
    y = gap;
    xstep = 0.5 / width;
    ystep = 0.5 / height;
    scale = (Real32) getMaxAscent() - (Real32) getMaxDescent();

    for(i = 0; i < numSorted; i++)
    {
        current = sortedIndices[i];

        res = _imageGlyphs[current]->getImageSize();

        if(res[0] + x >= width)
            x = gap;

        if(x == gap)
        {
            if(i)
                y += rowHeight + gap;
            rowHeight = res[1];
        }

        // copy image
        img = _imageGlyphs[current]->getImage();
        for(j = res[1] - 1; j >= 0; j--)
        {
            srcPixel = img + ((res[1] - j - 1) * res[2]);
            dstPixel = imageBuffer + ((y + j) * width + x) * 2;

            for(k = 0; k < res[0]; k++, srcPixel++, dstPixel += 2)
            {
                if(!(*srcPixel))
                    continue;
                *dstPixel = *(dstPixel + 1) = (255 * (*srcPixel)) >> 2;
            }
        }

        glyph = _txfGlyphInfos[current];
        glyph->remap(0);

        dims = new Int16[2];
        dims[0] = (Int16) x;
        dims[1] = (Int16) y;
        glyph->setOffset(dims);

        x_f = ((Real32) (x)) / width + xstep;
        y_f = ((Real32) (y)) / height + ystep;
        glyph->setTextureCoords(0, x_f, y_f);

        x_f += ((Real32) (res[0])) / width;
        glyph->setTextureCoords(1, x_f, y_f);

        y_f += ((Real32) (res[1])) / height;
        glyph->setTextureCoords(2, x_f, y_f);

        x_f = ((Real32) (x)) / width + xstep;
        glyph->setTextureCoords(3, x_f, y_f);

        bb = _imageGlyphs[current]->getBoundingBox();

        x_f = (Real32) bb[0] / scale;
        y_f = (Real32) bb[2] / scale;
        glyph->setVertexCoords(0, x_f, y_f);

        x_f = (Real32) bb[1] / scale;
        glyph->setVertexCoords(1, x_f, y_f);

        y_f = (Real32) bb[3] / scale;
        glyph->setVertexCoords(2, x_f, y_f);

        x_f = (Real32) bb[0] / scale;
        glyph->setVertexCoords(3, x_f, y_f);

        glyph->setAdvance((Real32) _imageGlyphs[current]->getAdvance() / 
                          scale);

        x += res[0] + gap;
    }

    _txfImageMap = imageBuffer;
    _txfFontWidth = width;
    _txfFontHeight = height;

    delete[] createdIndices;
    delete[] sortedIndices;

    return retVal;
}

UChar8 *TTFontStyle::getTXFImageMap(void)
{
    if(!_txfImageMap)
        createTXFMap();

    return _txfImageMap;
}

bool TTFontStyle::dump(std::ostream &out)
{
    const Int32 *bb;
    UInt32      swapit = 0x12345678;
    UInt32      zero = 0, buffer, nc = 0;
    Int16       sbuffer;
    UChar8      *oBuffer;

    out << (UChar8) 0xff << "txf";
    out.write(reinterpret_cast < char * > (&swapit), 4);
    out.write(reinterpret_cast < char * > (&zero), 4);
    out.write(reinterpret_cast < char * > (&_txfFontWidth), 4);
    out.write(reinterpret_cast < char * > (&_txfFontHeight), 4);
    buffer = (Int32) osgfloor(getMaxAscent() * 72);
    out.write(reinterpret_cast < char * > (&buffer), 4);
    buffer = (Int32) osgfloor(getMaxDescent() * 72);
    out.write(reinterpret_cast < char * > (&buffer), 4);

    for(Int16 i = 0; i < _txfGlyphInfos.size(); i++)
    {
        if(!(_txfGlyphInfos[i]->remapped()))
            nc++;
    }

    out.write(reinterpret_cast < char * > (&nc), 4);

    for(Int16 i = 0; i < _txfGlyphInfos.size(); i++)
    {
        if(!(_txfGlyphInfos[i]->remapped()))
        {
            bb = _imageGlyphs[i]->getBoundingBox();
            out.write(reinterpret_cast < char * > (&i), 2);
            out << (Int8) (bb[1] - bb[0]);
            out << (Int8) (bb[3] - bb[2]);
            out << (Int8) bb[0] << (Char8) bb[2];
            out << (Int8) _imageGlyphs[i]->getAdvance();
            out << (Int8) 0;
            sbuffer = _txfGlyphInfos[i]->getOffset()[0];
            out.write(reinterpret_cast < char * > (&sbuffer), 2);
            sbuffer = _txfGlyphInfos[i]->getOffset()[1];
            out.write(reinterpret_cast < char * > (&sbuffer), 2);
        }
    }

    oBuffer = new UChar8[_txfFontWidth * _txfFontHeight];
    for(Int32 j = 0; j < _txfFontWidth * _txfFontHeight; j++)
        oBuffer[j] = _txfImageMap[2 * j];
    out.write(reinterpret_cast < Char8 * > (oBuffer),
                  _txfFontWidth * _txfFontHeight);

    delete oBuffer;

    return true;
}
#endif // OSG_WITH_FREETYPE1
