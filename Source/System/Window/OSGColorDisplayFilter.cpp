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
    Inherited(),
    _group(NULL)
{
}

ColorDisplayFilter::ColorDisplayFilter(const ColorDisplayFilter &source) :
    Inherited(source),
    _group(NULL)
{
}

ColorDisplayFilter::~ColorDisplayFilter(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ColorDisplayFilter::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if(whichField & MatrixFieldMask) 
    {
        if(getEnabled() && _group)
        {
            // reset
            UInt32 c;
            for(c = 0 ; c < _chunks.size() ; ++c)
                _group->getMaterial()->subChunk(_chunks[c]);
            _chunks.clear();
            createChunks();
        }
    }

}

void ColorDisplayFilter::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ColorDisplayFilter NI" << std::endl;
}

void ColorDisplayFilter::createChunks()
{
    WindowPtr window = _port->getParent();

    int extension;
    extension = osg::Window::registerExtension("GL_ARB_fragment_program");
    if(window->hasExtension(extension))
        createFragmentProgramm();
    else
        createRegisterCombiner();
}

void ColorDisplayFilter::createFragmentProgramm()
{
    // Texture Chunks for gamma mapping
        
    UChar8 rgammadata[] =
        {  0, 80, 160, 255 };
        
    ImagePtr rgammaimg = Image::create();
    beginEditCP(rgammaimg);
    rgammaimg->set(Image::OSG_L_PF,4,1,1,1,1,0,rgammadata);
    endEditCP(rgammaimg);
        
    TextureChunkPtr rgammachunk = TextureChunk::create();    
    beginEditCP(rgammachunk);
    rgammachunk->setImage(rgammaimg);
    rgammachunk->setMinFilter(GL_LINEAR);
    rgammachunk->setMagFilter(GL_LINEAR);
    rgammachunk->setWrapS(GL_CLAMP_TO_EDGE);
    rgammachunk->setWrapT(GL_CLAMP_TO_EDGE);
    endEditCP  (rgammachunk);
        
    UChar8 ggammadata[] =
        {  0, 80, 160, 255 };
        
    ImagePtr ggammaimg = Image::create();
    beginEditCP(ggammaimg);
    ggammaimg->set(Image::OSG_L_PF,4,1,1,1,1,0,ggammadata);
    endEditCP(ggammaimg);
        
    TextureChunkPtr ggammachunk = TextureChunk::create();    
    beginEditCP(ggammachunk);
    ggammachunk->setImage(ggammaimg);
    ggammachunk->setMinFilter(GL_LINEAR);
    ggammachunk->setMagFilter(GL_LINEAR);
    ggammachunk->setWrapS(GL_CLAMP_TO_EDGE);
    ggammachunk->setWrapT(GL_CLAMP_TO_EDGE);
    endEditCP  (ggammachunk);

    UChar8 bgammadata[] =
        {  0, 80, 160, 255 };
        
    ImagePtr bgammaimg = Image::create();
    beginEditCP(bgammaimg);
    bgammaimg->set(Image::OSG_L_PF,4,1,1,1,1,0,bgammadata);
    endEditCP(bgammaimg);
    
    TextureChunkPtr bgammachunk = TextureChunk::create();    
    beginEditCP(bgammachunk);
    bgammachunk->setImage(bgammaimg);
    bgammachunk->setMinFilter(GL_LINEAR);
    bgammachunk->setMagFilter(GL_LINEAR);
    bgammachunk->setWrapS(GL_CLAMP_TO_EDGE);
    bgammachunk->setWrapT(GL_CLAMP_TO_EDGE);
    endEditCP  (bgammachunk);

    // set gamma table
    for(int j=0; j < 3; ++j)
    {
        ImagePtr img;
        switch(j)
        {
            case 0: img = rgammaimg; break;
            case 1: img = ggammaimg; break;
            case 2: img = bgammaimg; break;
        }
        beginEditCP(img);
        if(getRamp().size() == 0)
        {
            img->set(Image::OSG_L_PF, 256, 1);
            UInt8 *data = img->getData();
            for(int i=0; i < 256; i++)
            {
                data[i] = (UInt8)(pow(i/255.0,1.0)*255);
            }
        }
        else
        {
            img->set(Image::OSG_L_PF, getRamp().size(), 1);
            UInt8 *data = img->getData();
            for(unsigned int i=0; i < getRamp().size(); i++)
            {
                data[i] = (UInt8)(getRamp()[i][j] * 255);
            }
        }
        endEditCP(img);
    }

    // Step 3: FragmentProgram Chunk for color matrix multiply
    FragmentProgramChunkPtr fragProgram = FragmentProgramChunk::create();
    std::string prog(
        "!!ARBfp1.0\n"
        "PARAM mat0 = program.local[1];\n"
        "PARAM mat1 = program.local[2];\n"
        "PARAM mat2 = program.local[3];\n"
        "PARAM mat3 = program.local[4];\n"
        "PARAM gamma = program.local[5];\n"
        "TEMP source;\n"
        "TEMP target;\n"
        "\n"
        "# get the grabbed texture's color\n"
        "TEX source, fragment.texcoord[0], texture[0], 2D;\n"
        "\n"
        "# gamma map it\n"
        "POW source.r, source.r, gamma.r;\n"
        "POW source.g, source.g, gamma.r;\n"
        "POW source.b, source.b, gamma.r;\n"
        "\n"
        "# do the matrix transform\n"
        "DP4 target.x, mat0, source;\n"
        "DP4 target.y, mat1, source;\n"
        "DP4 target.z, mat2, source;\n"
        "\n"
        "# map it through the target gamma\n"
        "TEX target.r, target.r, texture[1], 1D;\n"
        "TEX target.g, target.g, texture[2], 1D;\n"
        "TEX target.b, target.b, texture[3], 1D;\n"
        "\n"
        "# mov it to the output\n"
        "MOV result.color, target;\n"
        "END\n");

    beginEditCP(fragProgram);
    fragProgram->setProgram(prog);
    fragProgram->setParameter(1, getMatrix()[0]);
    fragProgram->setParameter(2, getMatrix()[1]);
    fragProgram->setParameter(3, getMatrix()[2]);
    fragProgram->setParameter(4, getMatrix()[3]);
    fragProgram->setParameter(5, Vec4f(getGamma(),getGamma(),getGamma(),0));   
    endEditCP(fragProgram);

    _chunks.push_back(rgammachunk);
    _chunks.push_back(ggammachunk);
    _chunks.push_back(bgammachunk);
    _chunks.push_back(fragProgram);
    beginEditCP(_group->getMaterial());
    _group->getMaterial()->addChunk(rgammachunk);
    _group->getMaterial()->addChunk(ggammachunk);
    _group->getMaterial()->addChunk(bgammachunk);
    _group->getMaterial()->addChunk(fragProgram);
    endEditCP(_group->getMaterial());
}

void ColorDisplayFilter::createRegisterCombiner()
{
    UInt16 x,y;
    UInt16 ncomb = 0;
    TextureChunkPtr tex = _group->getTexture();
    UInt32 res = getRamp().size();
    UInt8 *data;

    if(res == 0)
        res = 256;

    beginEditCP(tex);
    tex->setWrapS(GL_CLAMP_TO_EDGE);
    tex->setWrapT(GL_CLAMP_TO_EDGE);
    tex->setMinFilter(GL_LINEAR);
    tex->setMagFilter(GL_LINEAR);
    tex->setScale(false);
    tex->setEnvMode(GL_REPLACE);
    tex->setShaderOperation(GL_TEXTURE_2D);
    tex->setInternalFormat(GL_RGB8);
    endEditCP  (tex);

    // Step 2: The textures for the initial gamma mapping
    
    // Texture Chunks for gamma mapping

    UChar8 argammadata[] =
        {  0,  0,  0,    0,  0,  0,    0,  0,  0,    0,  0,  0,    
           80,  0,  0,   80,  0,  0,   80,  0,  0,   80,  0,  0,    
           160,  0,  0,  160,  0,  0,  160,  0,  0,  160,  0,  0,    
           255,  0,  0,  255,  0,  0,  255,  0,  0,  255,  0,  0  
        };
    
    ImagePtr argammaimg = Image::create();
    beginEditCP(argammaimg);
    argammaimg->set(GL_RGB,4,4,1,1,1,0,argammadata);
    endEditCP(argammaimg);
    
    TextureChunkPtr argammachunk = TextureChunk::create();    
    beginEditCP(argammachunk);
    argammachunk->setImage(argammaimg);
    argammachunk->setMinFilter(GL_NEAREST);
    argammachunk->setMagFilter(GL_NEAREST);
    argammachunk->setWrapS(GL_CLAMP_TO_EDGE);
    argammachunk->setWrapT(GL_CLAMP_TO_EDGE);
    argammachunk->setShaderOperation(GL_DEPENDENT_AR_TEXTURE_2D_NV);
    argammachunk->setShaderInput    (GL_TEXTURE0_ARB);
    argammachunk->setInternalFormat(GL_RGB8);
    endEditCP  (argammachunk);

    UChar8 gbgammadata[] =
        {  0,  0,  0,     0, 80,  0,     0,160,  0,    0,255,  0,
           0,  0, 80,     0, 80, 80,     0,160, 80,    0,255, 80,
           0,  0,160,     0, 80,160,     0,160,160,    0,255,160,
           0,  0,255,     0, 80,255,     0,160,255,    0,255,255
        };
    
    ImagePtr gbgammaimg = Image::create();
    beginEditCP(gbgammaimg);
    gbgammaimg->set(GL_RGB,4,4,1,1,1,0,gbgammadata);
    endEditCP(gbgammaimg);
    
    TextureChunkPtr gbgammachunk = TextureChunk::create();    
    beginEditCP(gbgammachunk);
    gbgammachunk->setImage(gbgammaimg);
    gbgammachunk->setMinFilter(GL_NEAREST);
    gbgammachunk->setMagFilter(GL_NEAREST);
    gbgammachunk->setWrapS(GL_CLAMP_TO_EDGE);
    gbgammachunk->setWrapT(GL_CLAMP_TO_EDGE);
    gbgammachunk->setShaderOperation(GL_DEPENDENT_GB_TEXTURE_2D_NV);
    gbgammachunk->setShaderInput    (GL_TEXTURE0_ARB);
    gbgammachunk->setInternalFormat(GL_RGB8);
    endEditCP  (gbgammachunk);

    // Step 3: RegisterCombiners Chunk for color matrix multiply
    
    RegisterCombinersChunkPtr regCombiner = RegisterCombinersChunk::create();

    Color4f 
        m1(getMatrix()[0][0]/2+.5,
           getMatrix()[0][1]/2+.5,
           getMatrix()[0][2]/2+.5,0),
        m2(getMatrix()[1][0]/2+.5,
           getMatrix()[1][1]/2+.5,
           getMatrix()[1][2]/2+.5,0),
        m3(getMatrix()[2][0]/2+.5,
           getMatrix()[2][1]/2+.5,
           getMatrix()[2][2]/2+.5,0),
        m4(getMatrix()[3][0]/2+.5,
           getMatrix()[3][1]/2+.5,
           getMatrix()[3][2]/2+.5,0);
    
    Color4f selectR(1,0,0,0), selectG(0,1,0,0), selectB(0,0,1,0);

    beginEditCP(regCombiner);

    regCombiner->setCombinerRGB(ncomb,
                                 GL_TEXTURE1_ARB,       GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable A
                                 GL_ZERO,               GL_UNSIGNED_INVERT_NV,   GL_RGB, // variable B
                                 GL_TEXTURE2_ARB,       GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable C
                                 GL_ZERO,               GL_UNSIGNED_INVERT_NV,   GL_RGB, // variable D
                                 GL_DISCARD_NV, GL_DISCARD_NV, GL_TEXTURE0_ARB,   // ABout, CDout, Sumout
                                 GL_NONE, GL_NONE,                            // scale, bias
                                 GL_FALSE, GL_FALSE, GL_FALSE );                // ABdot, CDdot, muxSum

    ncomb++;

    // first combiner: spare0 = dot(col, m1), spare1 = dot(col,m2)      
        
    regCombiner->setCombinerColors(ncomb, m1, m2);

    regCombiner->setCombinerRGB(
        ncomb,
        GL_TEXTURE0_ARB,       GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable A
        GL_CONSTANT_COLOR0_NV, GL_EXPAND_NORMAL_NV,     GL_RGB, // variable B
        GL_TEXTURE0_ARB,       GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable C
        GL_CONSTANT_COLOR1_NV, GL_EXPAND_NORMAL_NV,     GL_RGB, // variable D
        GL_SPARE0_NV, GL_SPARE1_NV, GL_DISCARD_NV,   // ABout, CDout, Sumout
        GL_NONE, GL_NONE,                            // scale, bias
        GL_TRUE, GL_TRUE, GL_FALSE );                // ABdot, CDdot, muxSum
        
    ncomb++;
    
    // second combiner: tex0 = dot(col, m3), spare0 = spare0.r   
    
    regCombiner->setCombinerColors(ncomb, m3, selectR);

    regCombiner->setCombinerRGB(ncomb,
                                 GL_TEXTURE0_ARB,       GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable A
                                 GL_CONSTANT_COLOR0_NV, GL_EXPAND_NORMAL_NV,     GL_RGB, // variable B
                                 GL_SPARE0_NV,          GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable C
                                 GL_CONSTANT_COLOR1_NV, GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable D
                                 GL_TEXTURE3_ARB, GL_SPARE0_NV, GL_DISCARD_NV, // ABout, CDout, Sumout
                                 GL_NONE, GL_NONE,                             // scale, bias
                                 GL_TRUE, GL_FALSE, GL_FALSE );                 // ABdot, CDdot, muxSum

    ncomb++;
    
    // final combiner 
    
    regCombiner->setColor0(selectG);
    regCombiner->setColor1(selectB);
    
    // RGB = D + AB + (1-A)C
    regCombiner->setFinalCombiner( 
        GL_CONSTANT_COLOR0_NV, GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable A
        GL_SPARE1_NV,          GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable B
        GL_E_TIMES_F_NV,       GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable C
        GL_SPARE0_NV,          GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable D
        GL_CONSTANT_COLOR1_NV, GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable E
        GL_TEXTURE3_ARB,       GL_UNSIGNED_IDENTITY_NV, GL_RGB, // variable F
        GL_PRIMARY_COLOR_NV,   GL_UNSIGNED_IDENTITY_NV, GL_ALPHA );// variable G

    endEditCP(regCombiner);

    argammaimg->set(GL_RGB,res,res);

    beginEditCP(argammaimg);
    data = argammaimg->getData();
    
    memset(data, 0, res * res * 3);
    
    for(y = 0; y < res; ++y)
    {
        UInt8 v = (int)(pow(y/(Real32)(res-1),getGamma())*255+0.5);

        if(getRamp().size() < y)
            v = (UInt8)(getRamp()[y][0] * 255);

        for(x = 0; x < res; ++x)
        {
            *data++ = v;
            *data++ = 0;
            *data++ = 0;           
        }
    }
    endEditCP(argammaimg);

    beginEditCP(argammachunk);
    argammachunk->setImage(argammaimg);
    endEditCP(argammachunk);

    gbgammaimg->set(GL_RGB,res,res);

    beginEditCP(gbgammaimg);
    data = gbgammaimg->getData();
    
    memset(data, 0, res * res * 3);
    
    for(y = 0; y < res; ++y)
    {
        UInt8 vy = (int)(pow(y/(Real32)(res-1),getGamma())*255+0.5);

        if(getRamp().size() < y)
            vy = (UInt8)(getRamp()[y][2] * 255);

        for(x = 0; x < res; ++x)
        {
            UInt8 vx = (int)(pow(x/(Real32)(res-1),getGamma())*255+0.5);

            if(getRamp().size() < x)
                vx = (UInt8)(getRamp()[x][1] * 255);

            *data++ = 0;
            *data++ = vx;
            *data++ = vy;           
        }
    }
    endEditCP(gbgammaimg);

    beginEditCP(gbgammachunk);
    gbgammachunk->setImage(gbgammaimg);
    endEditCP(gbgammachunk);

    _chunks.push_back(argammachunk);
    _chunks.push_back(gbgammachunk);
    _chunks.push_back(regCombiner);
    beginEditCP(_group->getMaterial());
    _group->getMaterial()->addChunk(argammachunk);
    _group->getMaterial()->addChunk(gbgammachunk);
    _group->getMaterial()->addChunk(regCombiner);
    endEditCP(_group->getMaterial());

}

void ColorDisplayFilter::createFilter(DisplayFilterForeground *fg,
                                      Viewport *port)
{
    _group = fg->findReadbackGroup("ColorDisplayFilter");
    _port = port;

    _chunks.clear();
    createChunks();
}

void ColorDisplayFilter::destroyFilter(DisplayFilterForeground *)
{
    _group = NULL;
    _chunks.clear();
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

