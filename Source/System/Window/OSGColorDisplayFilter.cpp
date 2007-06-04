/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>
#include <OSGViewport.h>
#include <OSGImage.h>
#include <OSGTextureChunk.h>
#include <OSGComponentTransform.h>
#include <OSGGeometry.h>
#include <OSGWindow.h>
#include <OSGChunkMaterial.h>
#include <OSGRegisterCombinersChunk.h>
#include <OSGRenderAction.h>
#include <OSGWindow.h>
#include <OSGSHLChunk.h>

#include "OSGColorDisplayFilter.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ColorDisplayFilter

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ColorDisplayFilter::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ColorDisplayFilter::ColorDisplayFilter(void) :
    Inherited()
{
}

ColorDisplayFilter::ColorDisplayFilter(const ColorDisplayFilter &source) :
    Inherited(source)
{
}

ColorDisplayFilter::~ColorDisplayFilter(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ColorDisplayFilter::updateFilterValues()
{
    UInt32 c;
    std::vector<UChar8> imageData;

    if(_shadingImage == NullFC || _shlChunk == NullFC)
        return;

    // set shading image
    UInt32 size = getWidth() * getHeight() * getDepth();
    UInt32 width = getWidth();
    UInt32 height = getHeight();
    UInt32 depth = getDepth();
    if(size != getTable().size())
    {
        // create default linear table
        FWARNING(("Wrong shanding table size\n"));
        width = height = 1;
        depth = 2;
        size = width * height * depth;
        imageData.push_back(0);
        imageData.push_back(0);
        imageData.push_back(0);
        imageData.push_back(255);
        imageData.push_back(255);
        imageData.push_back(255);
    } 
    else
    {
        imageData.resize(size*3);
        for(c=0 ; c<size ; ++c)
        {
            imageData[c*3 + 0] = (UChar8)(getTable()[c][0]*255);
            imageData[c*3 + 1] = (UChar8)(getTable()[c][1]*255);
            imageData[c*3 + 2] = (UChar8)(getTable()[c][2]*255);
        }
    }
    _shadingImage->set(Image::OSG_RGB_PF,width,height,depth,1,1,0,&imageData[0]);

    beginEditCP(_shlChunk);
    _shlChunk->setUniformParameter("colorMatrix",  getMatrix());
    _shlChunk->setUniformParameter("gamma",        getGamma());
    _shlChunk->setUniformParameter("shadingWidth", (Int32)width);
    _shlChunk->setUniformParameter("shadingHeight", (Int32)height);
    _shlChunk->setUniformParameter("shadingDepth", (Int32)depth);
    endEditCP(_shlChunk);
}

void ColorDisplayFilter::changed(BitVector whichField, UInt32 origin)
{
//    updateFilterValues();
    Inherited::changed(whichField, origin);
}

void ColorDisplayFilter::dump(UInt32, const BitVector ) const
{
    SLOG << "Dump ColorDisplayFilter NI" << std::endl;
}

void ColorDisplayFilter::createFilter(DisplayFilterForeground *fg,
                                        Viewport *port)
{
    DisplayFilterForeground::DisplayFilterGroup *group = 
        fg->findReadbackGroup("ColorDisplayFilter");
    WindowPtr window = port->getParent();

    std::string vp_program =
        "varying vec2 position;\n"
        "varying mat4 shadingTexMat;\n"
        "\n"
        "void main(void)\n"
        "{\n"
        "   gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;\n"
        "   shadingTexMat  = gl_TextureMatrix[1];\n"
        "   gl_Position    = ftransform();\n"
        "   position       = gl_Vertex.xy;\n"
        "}\n";
    
    std::string fp_program =
        "varying vec2 position;\n"
        "varying mat4 shadingTexMat;\n"
        "\n"
        "uniform sampler2D grabTexture;\n"
        "uniform sampler3D shadingTexture;\n"
        "\n"
        "uniform mat4      colorMatrix;\n"
        "uniform float     gamma;\n"
        "uniform int       shadingWidth;\n"
        "uniform int       shadingHeight;\n"
        "uniform int       shadingDepth;\n"
        "\n"
        "void main(void)\n"
        "{\n"
        "   // read color from grab texture\n"
        "   vec4 color=texture2D(grabTexture,gl_TexCoord[0].xy);\n"
        "\n"
        "   // clamp to 0-1\n"
        "   color.rgb = clamp(color.rgb,0.0,1.0);\n"
        "\n"
        "   // make linear\n"
        "   color.r = pow(color.r,gamma);\n"
        "   color.g = pow(color.g,gamma);\n"
        "   color.b = pow(color.b,gamma);\n"
        "\n"
        "   // color matrix transformation\n"
        "   color *= colorMatrix;\n"
        "\n"
        "   // Scale color from the center of the first texel to the center of\n"
        "   // the last texel\n"
        "   float shadingScale  = (float(shadingDepth)-1.0)/float(shadingDepth);\n"
        "   float shadingOffset = (1.0 - shadingScale) / 2.0;\n"
        "   color.rgb *= shadingScale;\n"
        "   color.rgb += vec3(shadingOffset);\n"
        "\n"
        "   shadingScale  = (float(shadingWidth)-1.0)/float(shadingWidth);\n"
        "   shadingOffset = (1.0 - shadingScale) / 2.0;\n"
        "   position.x *= shadingScale;\n"
        "   position.x += shadingOffset;\n"
        "\n"
        "   shadingScale  = (float(shadingHeight)-1.0)/float(shadingHeight);\n"
        "   shadingOffset = (1.0 - shadingScale) / 2.0;\n"
        "   position.y *= shadingScale;\n"
        "   position.y += shadingOffset;\n"
        "\n"
        "   vec4 lutCoordR = vec4(position,color.r,1.0);\n"
        "   lutCoordR = shadingTexMat * lutCoordR;\n"
        "   vec4 lutCoordG = vec4(position,color.g,1.0);\n"
        "   lutCoordG = shadingTexMat * lutCoordG;\n"
        "   vec4 lutCoordB = vec4(position,color.b,1.0);\n"
        "   lutCoordB = shadingTexMat * lutCoordB;\n"
        "\n"   
        "   // shading\n"
        "   color.r = texture3D(shadingTexture,lutCoordR.rgb).r;\n"
        "   color.g = texture3D(shadingTexture,lutCoordG.rgb).g;\n"
        "   color.b = texture3D(shadingTexture,lutCoordB.rgb).b;\n"
        "\n"
        "   gl_FragColor = color;\n"
        "}\n";

    _shlChunk = SHLChunk::create();
    beginEditCP(_shlChunk);
    _shlChunk->setVertexProgram(vp_program);
    _shlChunk->setFragmentProgram(fp_program);
    _shlChunk->setUniformParameter("grabTexture", 0);
    _shlChunk->setUniformParameter("shadingTexture", 1);
    endEditCP(_shlChunk);

    TextureChunkPtr shadingTextureChunk = TextureChunk::create();
    _shadingImage = Image::create();
    beginEditCP(shadingTextureChunk);
    shadingTextureChunk->setImage(_shadingImage);
    shadingTextureChunk->setMinFilter(GL_LINEAR);
    shadingTextureChunk->setMagFilter(GL_LINEAR);
    shadingTextureChunk->setWrapS(GL_CLAMP_TO_EDGE);
    shadingTextureChunk->setWrapT(GL_CLAMP_TO_EDGE);
    shadingTextureChunk->setWrapR(GL_CLAMP_TO_EDGE);
    shadingTextureChunk->setNPOTMatrixScale(true);
    shadingTextureChunk->setScale(false);
//    shadingTextureChunk->setInternalFormat(GL_RGB8);
    endEditCP(shadingTextureChunk);

    beginEditCP(group->getMaterial());
    group->getMaterial()->addChunk(shadingTextureChunk);
    group->getMaterial()->addChunk(_shlChunk);
    endEditCP(group->getMaterial());

    updateFilterValues();
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.19 2003/05/05 10:05:28 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGCOLORDISPLAYFILTERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCOLORDISPLAYFILTERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCOLORDISPLAYFILTERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

