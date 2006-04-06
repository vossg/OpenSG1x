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

#include <OSGBaseFunctions.h>
#include <OSGImage.h>

#include <OSGShaderParameter.h>
#include <OSGShaderParameterBool.h>
#include <OSGShaderParameterInt.h>
#include <OSGShaderParameterReal.h>
#include <OSGShaderParameterVec2f.h>
#include <OSGShaderParameterVec3f.h>
#include <OSGShaderParameterVec4f.h>
#include <OSGShaderParameterMatrix.h>
#include <OSGShaderParameterString.h>

#include "OSGCGFXMaterial.h"

OSG_USING_NAMESPACE

/*! \class osg::CGFXMaterial

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CGFXMaterial::timercbfp CGFXMaterial::_timerFP = NULL;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CGFXMaterial::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CGFXMaterial::CGFXMaterial(void) :
    Inherited(),
    _cgfxChunk(NullFC),
    _parameter_access(NULL)
{
}

CGFXMaterial::CGFXMaterial(const CGFXMaterial &source) :
    Inherited(source),
    _cgfxChunk(source._cgfxChunk),
    _parameter_access(source._parameter_access)
{
}

CGFXMaterial::~CGFXMaterial(void)
{
}

void CGFXMaterial::onCreate(const CGFXMaterial *source)
{
    Inherited::onCreate(source);

    // ignore prototypes.
    if(GlobalSystemState == Startup)
        return;

#if 0
    CGFXMaterialPtr tmpPtr(*this);
    beginEditCP(tmpPtr, CGFXMaterial::SortKeyFieldMask);
        setSortKey(Material::NoStateSorting);
    endEditCP(tmpPtr, CGFXMaterial::SortKeyFieldMask);
#endif

    _cgfxChunk = CGFXChunk::create();
    addRefCP(_cgfxChunk);

    _parameter_access = new ShaderParameterAccess(getParameters());

    CGFXMaterialPtr tmpPtr(*this);
    _cgfxChunk->setParentMaterial(tmpPtr);
}

void CGFXMaterial::onDestroy(void)
{
    Inherited::onDestroy();

    if(_cgfxChunk != NullFC)
        subRefCP(_cgfxChunk);

    if(_parameter_access != NULL)
        delete _parameter_access;
}

StatePtr CGFXMaterial::makeState(void)
{
    StatePtr state = State::create();

    if(_cgfxChunk != NullFC)
        state->addChunk(_cgfxChunk);

    return state;
}

void CGFXMaterial::rebuildState(void)
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

    if(_cgfxChunk != NullFC)
        _pState->addChunk(_cgfxChunk);
}

StatePtr CGFXMaterial::getState(UInt32 OSG_CHECK_ARG(index))
{
    return _pState;
}

UInt32 CGFXMaterial::getNPasses(void) const
{
    return _cgfxChunk->getNPasses();
}

bool CGFXMaterial::isTransparent(void) const
{
    return _cgfxChunk->isTransparent();
}

bool CGFXMaterial::isTextureParameter(const std::string &name)
{
    return _cgfxChunk->isTextureParameter(name);
}

ImagePtr CGFXMaterial::findImage(const std::string &name)
{
    std::string name2 = name;
    for(UInt32 i=0;i<name2.size();++i)
    {
        if(name2[i] == '\\')
            name2[i] = '/';
    }

    MFImagePtr images = getImages();
    for(UInt32 i=0;i<images.size();++i)
    {
        std::string iname = images[i]->getName();
        for(UInt32 j=0;j<iname.size();++j)
        {
            if(iname[j] == '\\')
                iname[j] = '/';
        }

        if(iname == name2)
            return images[i];
    }
    return NullFC; // not found
}

Int32 CGFXMaterial::findImage(const ImagePtr &img)
{
    if(img == NullFC)
        return -1;

    MFImagePtr images = getImages();
    for(UInt32 i=0;i<images.size();++i)
    {
        if(images[i] == img)
            return i;
    }

    return -1; // not found
}

std::string CGFXMaterial::getTechniqueString(Int32 index)
{
    return _cgfxChunk->getTechniqueString(index);
}

void CGFXMaterial::setTimerCB(CGFXMaterial::timercbfp fp)
{
    _timerFP = fp;
}

CGFXMaterial::timercbfp CGFXMaterial::getTimerCB(void)
{
    return _timerFP;
}

/*----------------------------- class specific ----------------------------*/

void CGFXMaterial::changed(BitVector whichField, UInt32 origin)
{
    if(origin & ChangedOrigin::Abstract)
    {
        MFImagePtr::iterator imgIt  = _mfImages.begin();
        MFImagePtr::iterator imgEnd = _mfImages.end ();
        
        while(imgIt != imgEnd)
        {
            addRefCP(*imgIt);
            ++imgIt;
        }
    }

    if(whichField & EffectFileFieldMask)
    {
        //printf("CGFXMaterial::changed: effectFile '%s'\n", getEffectFile().c_str());
        _cgfxChunk->setEffectFile(getEffectFile());
    }

    if(whichField & EffectStringFieldMask)
    {
        //printf("CGFXMaterial::changed: effectString\n");
        _cgfxChunk->setEffectString(getEffectString());
    }

    if(whichField & TechniqueFieldMask)
    {
        //printf("CGFXMaterial::changed: technique %d\n", getTechnique());
        _cgfxChunk->setTechnique(getTechnique());
    }

    if(whichField & ParametersFieldMask)
    {
        //printf("CGFXMaterial::changed: parameters\n");
        Window::refreshGLObject(_cgfxChunk->getGLId());
    }

    Inherited::changed(whichField, origin);
}

void CGFXMaterial::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CGFXMaterial NI" << std::endl;
}


/*---------------------------------- Access -------------------------------*/


/*------------------------------------ Set --------------------------------*/

bool CGFXMaterial::setParameter(const char *name, bool value)
{
    return _parameter_access->setParameter<ShaderParameterBool>(name, value);
}

bool CGFXMaterial::setParameter(const char *name, Int32 value)
{
    return _parameter_access->setParameter<ShaderParameterInt>(name, value);
}

bool CGFXMaterial::setParameter(const char *name, Real32 value)
{
    return _parameter_access->setParameter<ShaderParameterReal>(name, value);
}

bool CGFXMaterial::setParameter(const char *name, const Vec2f &value)
{
    return _parameter_access->setParameter<ShaderParameterVec2f>(name, value);
}

bool CGFXMaterial::setParameter(const char *name, const Vec3f &value)
{
    return _parameter_access->setParameter<ShaderParameterVec3f>(name, value);
}

bool CGFXMaterial::setParameter(const char *name, const Vec4f &value)
{
    return _parameter_access->setParameter<ShaderParameterVec4f>(name, value);
}

bool CGFXMaterial::setParameter(const char *name, const Matrix &value)
{
    return _parameter_access->setParameter<ShaderParameterMatrix>(name, value);
}

bool CGFXMaterial::setParameter(const char *name, const std::string &value)
{
    return _parameter_access->setParameter<ShaderParameterString>(name, value);
}

/*------------------------------------ Get --------------------------------*/

bool CGFXMaterial::getParameter(const char *name, bool &value)
{
    return _parameter_access->getParameter<ShaderParameterBool>(name, value);
}

bool CGFXMaterial::getParameter(const char *name, Int32 &value)
{
    return _parameter_access->getParameter<ShaderParameterInt>(name, value);
}

bool CGFXMaterial::getParameter(const char *name, Real32 &value)
{
    return _parameter_access->getParameter<ShaderParameterReal>(name, value);
}

bool CGFXMaterial::getParameter(const char *name, Vec2f &value)
{
    return _parameter_access->getParameter<ShaderParameterVec2f>(name, value);
}

bool CGFXMaterial::getParameter(const char *name, Vec3f &value)
{
    return _parameter_access->getParameter<ShaderParameterVec3f>(name, value);
}

bool CGFXMaterial::getParameter(const char *name, Vec4f &value)
{
    return _parameter_access->getParameter<ShaderParameterVec4f>(name, value);
}

bool CGFXMaterial::getParameter(const char *name, Matrix &value)
{
    return _parameter_access->getParameter<ShaderParameterMatrix>(name, value);
}

bool CGFXMaterial::getParameter(const char *name, std::string &value)
{
    return _parameter_access->getParameter<ShaderParameterString>(name, value);
}

bool CGFXMaterial::subParameter(const char *name)
{
    return _parameter_access->subParameter(name);
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGCGFXMaterial.cpp,v 1.2 2006/04/06 16:56:08 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGCGFXMATERIAL_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCGFXMATERIAL_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCGFXMATERIALFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
