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

//#include <OSGFragmentProgramChunk.h>
//#include <OSGRegisterCombinersChunk.h>

#include "OSGPhongMaterial.h"

OSG_USING_NAMESPACE

/*! \class osg::PhongMaterial

*/

static std::string _vp_prg =
"!!ARBvp1.0\n"
"OPTION ARB_position_invariant;\n"
"\n"
"PARAM m[4]={state.matrix.modelview};\n"
"PARAM mvp[4]={state.matrix.mvp};\n"
"PARAM mvinv[4]={state.matrix.modelview.invtrans};\n"
"PARAM MA=state.material.ambient;\n"
"PARAM MD=state.material.diffuse;\n"
"PARAM ME=state.material.emission;\n"
"PARAM MS=state.material.specular;\n"
"PARAM MSh=state.material.shininess;\n"
"PARAM AmbientColor0=state.lightprod[0].ambient;\n"
"PARAM DiffuseColor0=state.lightprod[0].diffuse;\n"
"PARAM SpecularColor0=state.lightprod[0].specular;\n"
"PARAM Attenuation0=state.light[0].attenuation;\n"
"PARAM SceneColor=state.lightmodel.scenecolor;\n"
"PARAM LP0=state.light[0].position;\n"
"PARAM CamPos=program.local[0];\n"
"PARAM two={2.0,2.0,2.0,2.0};\n"
"PARAM one={1.0,1.0,1.0,1.0};\n"
"PARAM zero={0.0,0.0,0.0,0.0};\n"
"\n"
"ATTRIB iPos=vertex.position;\n"
"ATTRIB iNormal=vertex.normal;\n"
"ATTRIB iTex0=vertex.texcoord[0];\n"
"\n"
"OUTPUT oColor=result.color;\n"
"OUTPUT oTex0=result.texcoord[0];\n"
"\n"
"TEMP r0, r1, r2, r3, EyeVertex, Len, att, ViewVector, r4, EyeCam;\n"
"\n"
"#Transform the vertex to eye space.\n"
"DP4	EyeVertex.x, m[0], iPos;\n"
"DP4	EyeVertex.y, m[1], iPos;\n"
"DP4	EyeVertex.z, m[2], iPos;\n"
"\n"
"#Transform the normal to eye space.\n"
"DP3	r0.x, mvinv[0], iNormal;\n"
"DP3	r0.y, mvinv[1], iNormal;\n"
"DP3	r0.z, mvinv[2], iNormal;\n"
"\n"
"#Transform Campos to eyespace\n"
"DP4 EyeCam.x, m[0], CamPos;\n"
"DP4 EyeCam.y, m[1], CamPos;\n"
"DP4 EyeCam.z, m[2], CamPos;\n"
"\n"
"#Compute the view vector\n"
"SUB ViewVector, EyeCam, EyeVertex;\n"
"#Normalize.\n"
"DP3 ViewVector.w, ViewVector, ViewVector;\n"
"RSQ ViewVector.w, ViewVector.w;\n"
"MUL ViewVector, ViewVector, ViewVector.w;\n"
"\n"
"#Renormalize the normal.\n"
"DP3 r0.w, r0, r0;\n"
"RSQ r0.w, r0.w;\n"
"MUL r0, r0, r0.w;\n"
"\n"
"#Compute lighting by light 0\n"
"#NOTE: The LIT instruction accelerates per-vertex lighting by computing lighting\n"
"#      coefficients for ambient, diffuse, and specular light contributions.\n"
"SUB	Len, LP0, EyeVertex;\n"
"DP3	Len.w, Len, Len;\n"
"RSQ	r1.w, Len.w;\n"
"MUL	r1, Len, r1.w;			# r1 = normalized light vector\n"
"DP3	r2.x, r0, r1;			# r2.x = normal dot lvec\n"
"DP3 r3, r1, r0;\n"
"MUL r3, r3, two;\n"
"MAD r3, r3, r0, -r1;\n"
"DP3 r2.y, r3, ViewVector;\n"
"MOV	r2.w, MSh.x;\n"
"LIT	r2, r2;\n"
"\n"
"#Attenuation\n"
"MAD att, Attenuation0.z, Len.w, Attenuation0.x;\n"
"RSQ Len.w, Len.w;\n"
"RCP Len.w, Len.w;\n"
"MAD att, Len.w, Attenuation0.y, att.x;\n"
"RCP att, att.x;\n"
"\n"
"#Sum it up!\n"
"MUL	r0.xyz, DiffuseColor0, r2.y;\n"
"MAD r2, SpecularColor0, r2.z, AmbientColor0;\n"
"ADD r0, r0, r2;\n"
"MUL r0, r0, att.x;\n"
"ADD r0, r0, SceneColor;\n"
"ADD oColor.xyz, r0, ME;\n"
"MOV oColor.w, MD.w;			# MOV transparency\n"
"\n"
"#Tex coord 0\n"
"MOV	oTex0, iTex0;\n"
"END\n";

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

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
    _vpChunk(NullFC)
{
}

PhongMaterial::PhongMaterial(const PhongMaterial &source) :
    Inherited(source),
    _materialChunk(source._materialChunk),
    _blendChunk(source._blendChunk),
    _vpChunk(source._vpChunk)
{
}

PhongMaterial::~PhongMaterial(void)
{
    subRefCP(_blendChunk);
}

void PhongMaterial::prepareLocalChunks(void)
{
    if(_materialChunk == NullFC)
    {
        _materialChunk = MaterialChunk::create();
        // so everybody can set the attributes using the ChunkMaterial class
        // iterating over the chunks.
        addChunk(_materialChunk);
    }

    if(_blendChunk == NullFC)
    {
        _blendChunk = BlendChunk::create();
        beginEditCP(_blendChunk);
            _blendChunk->setSrcFactor (GL_SRC_ALPHA);
            _blendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
        endEditCP  (_blendChunk);
        // can't do a addChunk(_blendChunk) cause we only want to add it to the state
        // if it is really transparent.
        addRefCP(_blendChunk);
    }
    
    if(_vpChunk == NullFC)
    {
        _vpChunk = VertexProgramChunk::create();
        addChunk(_vpChunk);
        beginEditCP(_vpChunk);
            _vpChunk->setProgram(_vp_prg);
            _vpChunk->addParameter("camPos", 0, Vec4f(0, 0, 0, 0));
        endEditCP(_vpChunk);
    }
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

#if 0
void PhongMaterial::draw(Geometry* geo, DrawActionBase *action)
{
    Inherited::draw(geo, action);
    CameraPtr cam = action->getCamera();
    NodePtr beacon = cam->getBeacon();
    Matrix m = beacon->getToWorld();
    beginEditCP(_vpChunk, VertexProgramChunk::ParamValuesFieldId);
        _vpChunk->setParameter("camPos", Vec4f(m[3][0], m[3][1], m[3][2], 0));
    endEditCP(_vpChunk, VertexProgramChunk::ParamValuesFieldId);
    printf("PhongMaterial::draw (%f %f %f)\n", m[3][0], m[3][1], m[3][2]);
}
#endif

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
    
    if(isTransparent())
        state->addChunk(_blendChunk);
    
    beginEditCP(_vpChunk, VertexProgramChunk::ParamValuesFieldMask);
        const Vec3f &cpos = getCameraPos();
        Vec4f pos(cpos[0], cpos[1], cpos[2], 0);
        _vpChunk->setParameter((Int16) 0 /*"camPos"*/, pos);
    endEditCP(_vpChunk, VertexProgramChunk::ParamValuesFieldMask);

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
    
    if(isTransparent())
        _pState->addChunk(_blendChunk);

    beginEditCP(_vpChunk, VertexProgramChunk::ParamValuesFieldMask);
        const Vec3f &cpos = getCameraPos();
        Vec4f pos(cpos[0], cpos[1], cpos[2], 0);
        _vpChunk->setParameter((Int16) 0 /*"camPos"*/, pos);
    endEditCP(_vpChunk, VertexProgramChunk::ParamValuesFieldMask);
    
    for(MFStateChunkPtr::iterator i  = _mfChunks.begin();
                                  i != _mfChunks.end(); 
                                ++i)
    {
        _pState->addChunk(*i);
    }
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
    static Char8 cvsid_cpp       [] = "@(#)$Id:$";
    static Char8 cvsid_hpp       [] = OSGPHONGMATERIAL_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPHONGMATERIAL_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPHONGMATERIALFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
