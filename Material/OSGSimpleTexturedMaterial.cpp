/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#include <OSGGL.h>

#include <OSGAction.h>
#include <OSGDrawAction.h>
#include <OSGGeometry.h>

#include <OSGStateChunk.h>
#include <OSGState.h>
#include <OSGMaterialChunk.h>

#include "OSGSimpleTexturedMaterial.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: OSGSimpleTexturedMaterial.cpp,v 1.8 2002/02/26 06:10:16 vossg Exp $";
    static char cvsid_hpp[] = OSGTEXTUREDSIMPLEMATERIAL_HEADER_CVSID;
    static char cvsid_inl[] = OSGTEXTUREDSIMPLEMATERIAL_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/*! \class osg::SimpleTexturedMaterial
    \ingroup MaterialLib

A SimpleMaterial with an added texture. It doesn't expose all features of the
texture, just the ones needed most often.

*/

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

SimpleTexturedMaterial::SimpleTexturedMaterial(void) :
    Inherited()
{
    _textureChunk = TextureChunk::create();
}

//! Copy Constructor

SimpleTexturedMaterial::SimpleTexturedMaterial(const SimpleTexturedMaterial &source) :
    Inherited(source)
{
    _textureChunk = TextureChunk::create();
}

//! Destructor

SimpleTexturedMaterial::~SimpleTexturedMaterial(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void SimpleTexturedMaterial::initMethod (void)
{
}

//! react to field changes

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning (disable : 383)
#endif

void SimpleTexturedMaterial::changed(BitVector whichField, ChangeMode from)
{
    Inherited::changed(whichField, from);

    // these two are very expensive, as they need to regenerate the
    // texture object, do only if really needed
    if(whichField & ImageFieldMask)
    {
        _textureChunk->setImage( getImage() );
    }
    if(whichField & MinFilterFieldMask || whichField & MagFilterFieldMask)
    {
        _textureChunk->setMinFilter( getMinFilter() );
        _textureChunk->setMagFilter( getMagFilter() );
    }
    // this is not as expensive, but why do it more often then needed?
    if(whichField & EnvModeFieldMask)
    {
        _textureChunk->setEnvMode( getEnvMode() );
    }
    if(whichField & EnvMapFieldMask)
    {
        if ( getEnvMap() )
        {
            _textureChunk->setGenFuncS( GL_SPHERE_MAP );
            _textureChunk->setGenFuncT( GL_SPHERE_MAP );
        }
        else
        {
            _textureChunk->setGenFuncS( GL_NONE );
            _textureChunk->setGenFuncT( GL_NONE );
        }
    }

}

#if defined(OSG_WIN32_ICL) && !defined(OSG_CHECK_FIELDSETARG)
#pragma warning (default : 383)
#endif

StatePtr SimpleTexturedMaterial::makeState( void )
{
    StatePtr state = Inherited::makeState();

    state->addChunk( _textureChunk );

    return state;
}

void SimpleTexturedMaterial::rebuildState(void)
{
    Inherited::rebuildState();

    _pState->addChunk(_textureChunk);
}

bool SimpleTexturedMaterial::isTransparent(void) const
{
    return Inherited::isTransparent() ||
           ( getImage() &&
             (getImage()->hasAlphaChannel() && getEnvMode() != GL_DECAL)
           );
}

//! output the instance for debug purposes

void SimpleTexturedMaterial::dump(      UInt32    OSG_CHECK_ARG(uiIndent),
                                  const BitVector OSG_CHECK_ARG(bvFlags)) const
{
    SLOG << "Dump SimpleTexturedMaterial NI" << endl;
}

