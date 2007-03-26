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

#include <OSGGeometry.h>
#include <OSGCamera.h>
#include <OSGTextureChunk.h>
#include <OSGWindow.h>

#include "OSGPhongMaterial.h"

OSG_USING_NAMESPACE

/*! \class osg::PhongMaterial

*/

// works only with one point light!
static std::string _phong_vp_prg =
"!!ARBvp1.0\n"
"OPTION ARB_position_invariant;\n"
"\n"
"PARAM lightPos  = state.light[0].position;\n"
"# using now -m[3] for camera position.\n"
"#PARAM cameraPos = program.local[0];\n"
"PARAM m[4]={state.matrix.modelview};\n"
"PARAM mvinv[4]={state.matrix.modelview.invtrans};\n"
"\n"
"TEMP EyeCamPos, EyeNormal, EyeVertex;\n"
"\n"
"#Vertex position in eye space...\n"
"DP4    EyeVertex.x, m[0], vertex.position;\n"
"DP4    EyeVertex.y, m[1], vertex.position;\n"
"DP4    EyeVertex.z, m[2], vertex.position;\n"
"\n"
"#Transform the camera pos to eye space.\n"
"DP4    EyeCamPos.x, m[0], -m[3];\n"
"DP4    EyeCamPos.y, m[1], -m[3];\n"
"DP4    EyeCamPos.z, m[2], -m[3];\n"
"\n"
"#Transform the normal to eye space.\n"
"DP3    EyeNormal.x, mvinv[0], vertex.normal;\n"
"DP3    EyeNormal.y, mvinv[1], vertex.normal;\n"
"DP3    EyeNormal.z, mvinv[2], vertex.normal;\n"
"\n"
"#Normalize\n"
"DP3 EyeNormal.w, EyeNormal, EyeNormal;\n"
"RSQ EyeNormal.w, EyeNormal.w;\n"
"MUL EyeNormal, EyeNormal, EyeNormal.w;\n"
"\n"
"MOV    result.texcoord[0], vertex.texcoord[0];\n"
"SUB    result.texcoord[1], state.light[0].position, EyeVertex;\n"
"SUB    result.texcoord[2], EyeCamPos, EyeVertex;\n"
"MOV result.texcoord[3], EyeNormal;\n"
"END\n";

static std::string _phong_fp_begin_prg =
"!!ARBfp1.0\n"
"TEMP lightVec, viewVec, reflVec, normal, attenuation, Len, finalCol, lightContrib, tex;\n"
"PARAM two = {2.0, 2.0, 2.0, 2.0};\n"
"PARAM m_one = {-1.0, -1.0, -1.0, -1.0};\n"
"\n"
"TEX        tex, fragment.texcoord[0], texture[0], 2D;\n"
"\n"
"#Normalize normal, lightvec and viewvec.\n"
"DP3        Len.w, fragment.texcoord[1], fragment.texcoord[1];\n"
"RSQ        lightVec.w, Len.w;\n"
"MUL        lightVec.xyz, fragment.texcoord[1], lightVec.w;\n"
"\n"
"DP3        viewVec.w, fragment.texcoord[2], fragment.texcoord[2];\n"
"RSQ        viewVec.w, viewVec.w;\n"
"MUL        viewVec.xyz, fragment.texcoord[2], viewVec.w;\n"
"\n"
"DP3        normal.w, fragment.texcoord[3], fragment.texcoord[3];\n"
"RSQ        normal.w, normal.w;\n"
"MUL        normal.xyz, fragment.texcoord[3], normal.w;\n"
"\n"
"#Calculate attenuation.\n"
"MAD        attenuation, state.light[0].attenuation.z, Len.w, state.light[0].attenuation.x;\n"
"RCP        Len, lightVec.w;\n"
"MAD        attenuation, Len.w, state.light[0].attenuation.y, attenuation.x;\n"
"RCP        attenuation.x, attenuation.x;\n"
"\n"
"#Diffuse\n"
"DP3_SAT    lightContrib.x, normal, lightVec;\n"
"\n"
"#Specular\n"
"# Phong:\n"
"DP3        reflVec, lightVec, normal;\n"
"MUL        reflVec, reflVec, two;\n"
"MAD        reflVec, reflVec, normal, -lightVec;\n"
"\n"
"DP3_SAT    lightContrib.y, reflVec, viewVec;\n"
"\n"
"# Blinn:\n"
"#    ADD        reflVec, lightVec, viewVec;    # reflVec == Half-angle.\n"
"#    DP3        reflVec.w, reflVec, reflVec;\n"
"#    RSQ        reflVec.w, reflVec.w;\n"
"#    MUL        reflVec.xyz, reflVec, reflVec.w;\n"
"#    DP3        lightContrib.y, reflVec, normal;\n"
"\n"
"MOV        lightContrib.w, state.material.shininess.x;\n"
"\n"
"#Accelerates lighting computations\n"
"LIT_SAT    lightContrib, lightContrib;\n"
"\n"
"MAD        finalCol, lightContrib.y, state.lightprod[0].diffuse, state.lightprod[0].ambient;\n"
"\n"
"# Enable this line for textured models\n";
static std::string _phong_fp_tex_prg =
"MUL        finalCol, finalCol, tex;    # Texture?\n";

static std::string _phong_fp_end_prg =
"MAD        finalCol, lightContrib.z, state.lightprod[0].specular, finalCol;\n"
"MAD        finalCol, finalCol, attenuation.x, state.material.emission;\n"
"ADD        result.color.xyz, finalCol, state.lightmodel.scenecolor;\n"
"MOV        result.color.w, state.material.diffuse.w;\n"
"END\n";


/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

UInt32 PhongMaterial::_arbFragmentProgram;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhongMaterial::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhongMaterial::PhongMaterial(void) :
    Inherited(),
    _materialChunk(NullFC),
    _blendChunk(NullFC),
    _vpChunk(NullFC),
    _fpChunk(NullFC)
{
}

PhongMaterial::PhongMaterial(const PhongMaterial &source) :
    Inherited(source),
    _materialChunk(source._materialChunk),
    _blendChunk(source._blendChunk),
    _vpChunk(source._vpChunk),
    _fpChunk(source._fpChunk)
{
    _arbFragmentProgram = Window::registerExtension("GL_ARB_fragment_program");
}

PhongMaterial::~PhongMaterial(void)
{
    subRefCP(_materialChunk);
    subRefCP(_blendChunk);
    subRefCP(_vpChunk);
    subRefCP(_fpChunk);
}

void PhongMaterial::prepareLocalChunks(void)
{
    if(_materialChunk != NullFC)
        return;

    _materialChunk = MaterialChunk::create();
    addRefCP(_materialChunk);

    _blendChunk = BlendChunk::create();
    addRefCP(_blendChunk);
    beginEditCP(_blendChunk);
        _blendChunk->setSrcFactor (GL_SRC_ALPHA);
        _blendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
    endEditCP  (_blendChunk);
    
    // phong shading without a fragment shader looks quite black ;-)
    // all cards with a fragment shader should also have a vertex shader.
    // calling hasCommonExtension() here is not a good idea as this works
    // only for a initialized window, I added a check to hasCommonExtension()
    // so this won't crash anymore.
    if(Window::hasCommonExtension(_arbFragmentProgram))
    {
        _vpChunk = VertexProgramChunk::create();
        addRefCP(_vpChunk);
        beginEditCP(_vpChunk);
            _vpChunk->setProgram(_phong_vp_prg);
        endEditCP(_vpChunk);
        
        _fpChunk = FragmentProgramChunk::create();
        addRefCP(_fpChunk);
        createFragmentProgram();
    }
}

void PhongMaterial::createFragmentProgram(void)
{
    if(_fpChunk == NullFC)
        return;

    bool has_tex_chunk = false;
    for(MFStateChunkPtr::iterator i  = _mfChunks.begin();
                                  i != _mfChunks.end(); 
                                ++i)
    {
        if(TextureChunkPtr::dcast(*i) != NullFC)
        {
            has_tex_chunk = true;
            break;
        }
    }
    
    std::string phong_fp_prg;
    beginEditCP(_fpChunk);
        if(has_tex_chunk)
            phong_fp_prg = _phong_fp_begin_prg + _phong_fp_tex_prg + _phong_fp_end_prg;
        else
            phong_fp_prg = _phong_fp_begin_prg + _phong_fp_end_prg;
        _fpChunk->setProgram(phong_fp_prg);
    endEditCP(_fpChunk);
}

/*----------------------------- class specific ----------------------------*/

void PhongMaterial::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PhongMaterial::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump PhongMaterial NI" << std::endl;
}

StatePtr PhongMaterial::makeState(void)
{
    StatePtr state = State::create();
    
    prepareLocalChunks();
    
    Color3f v3;
    Color4f v4;
    float alpha = 1.f - getTransparency();

    prepareLocalChunks();

    beginEditCP(_materialChunk);
         v3 = getAmbient(); 
         v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
        _materialChunk->setAmbient(v4);

         v3 = getDiffuse(); 
         v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
        _materialChunk->setDiffuse(v4);

         v3 = getSpecular(); 
         v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
        _materialChunk->setSpecular(v4);

        _materialChunk->setShininess(getShininess());

         v3 = getEmission(); 
         v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
        _materialChunk->setEmission(v4);
        
        _materialChunk->setLit(getLit());
        _materialChunk->setColorMaterial(getColorMaterial());
    endEditCP  (_materialChunk);
    state->addChunk(_materialChunk);

    if(isTransparent())
        state->addChunk(_blendChunk);
    
    if(_vpChunk != NullFC)
        state->addChunk(_vpChunk);
    
    createFragmentProgram();
    
    if(_fpChunk != NullFC)
        state->addChunk(_fpChunk);
    
    for(MFStateChunkPtr::iterator i  = _mfChunks.begin();
                                  i != _mfChunks.end(); 
                                ++i)
    {
        state->addChunk(*i);
    }

    return state;
}

void PhongMaterial::rebuildState(void)
{
    if(_pState != NullFC)
    {
        _pState->clearChunks();
    }
    else
    {
        _pState = State::create();

        addRefCP(_pState);
    }

    prepareLocalChunks();

    Color3f v3;
    Color4f v4;
    float alpha = 1.f - getTransparency();

    beginEditCP(_materialChunk);
         v3 = getAmbient(); 
         v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
        _materialChunk->setAmbient(v4);

         v3 = getDiffuse(); 
         v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
        _materialChunk->setDiffuse(v4);

         v3 = getSpecular(); 
         v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
        _materialChunk->setSpecular(v4);

        _materialChunk->setShininess(getShininess());

         v3 = getEmission(); 
         v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
        _materialChunk->setEmission(v4);
        
        _materialChunk->setLit(getLit());
        _materialChunk->setColorMaterial(getColorMaterial());
    endEditCP(_materialChunk);
    _pState->addChunk(_materialChunk);
    
    if(isTransparent())
        _pState->addChunk(_blendChunk);
    
    if(_vpChunk != NullFC)
        _pState->addChunk(_vpChunk);
    
    createFragmentProgram();

    if(_fpChunk != NullFC)
        _pState->addChunk(_fpChunk);
    
    for(MFStateChunkPtr::iterator i  = _mfChunks.begin();
                                  i != _mfChunks.end(); 
                                ++i)
    {
        _pState->addChunk(*i);
    }
}

bool PhongMaterial::isTransparent(void) const
{
    return ((getTransparency() > Eps) || (Inherited::isTransparent()));
}

ChunkMaterialPtr PhongMaterial::createChunkMaterial(void)
{
    _arbFragmentProgram = Window::registerExtension("GL_ARB_fragment_program");

    ChunkMaterialPtr cmat = ChunkMaterial::create();
    
    MaterialChunkPtr matc = MaterialChunk::create();
    beginEditCP(matc);
        matc->setAmbient(Color4f(0.1, 0.1, 0.2, 1.0));
        matc->setDiffuse(Color4f(0.2, 0.2, 0.8, 1.0));
        matc->setSpecular(Color4f(0.8, 0.8, 0.8, 1.0));
        matc->setShininess(100);
    endEditCP(matc);
    
    beginEditCP(cmat, ChunksFieldMask);
        cmat->addChunk(matc);
    endEditCP(cmat, ChunksFieldMask);
    
    // phong shading without a fragment shader looks quite black ;-)
    // all cards with a fragment shader should also have a vertex shader.
    if(Window::hasCommonExtension(_arbFragmentProgram))
    {
        VertexProgramChunkPtr vpc = VertexProgramChunk::create();
        beginEditCP(vpc);
            vpc->setProgram(_phong_vp_prg);
        endEditCP(vpc);
        
        FragmentProgramChunkPtr fpc = FragmentProgramChunk::create();
        std::string phong_fp_prg = _phong_fp_begin_prg + _phong_fp_end_prg;
        beginEditCP(fpc);
            fpc->setProgram(phong_fp_prg);
        endEditCP(fpc);
        
        beginEditCP(cmat, ChunksFieldMask);
            cmat->addChunk(vpc);
            cmat->addChunk(fpc);
        endEditCP(cmat, ChunksFieldMask);
    }
    return cmat;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGPhongMaterial.cpp,v 1.7 2003/10/17 16:02:46 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGPHONGMATERIAL_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPHONGMATERIAL_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPHONGMATERIALFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
