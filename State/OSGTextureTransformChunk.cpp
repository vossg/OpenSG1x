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

#include "OSGTextureTransformChunk.h"
#include <OSGWindow.h>
#include <OSGDrawActionBase.h>

OSG_USING_NAMESPACE

/*! \class osg::TextureTransformChunk

*/

StateChunkClass TextureTransformChunk::_class("TextureTransform");

UInt32 TextureTransformChunk::_arbMultiTex;

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

TextureTransformChunk::TextureTransformChunk(void) :
    Inherited()
{
    _arbMultiTex       = Window::registerExtension( "GL_ARB_multitexture" );
}

//! Copy Constructor

TextureTransformChunk::TextureTransformChunk(const TextureTransformChunk &source) :
    Inherited(source)
{
}

//! Destructor

TextureTransformChunk::~TextureTransformChunk(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void TextureTransformChunk::initMethod (void)
{
}

//! react to field changes

void TextureTransformChunk::changed(BitVector, ChangeMode)
{
}

//! output the instance for debug purposes

void TextureTransformChunk::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump TextureTransformChunk NI" << endl;
}


//! activate the matrix

#if defined(GL_ARB_multitexture)
void TextureTransformChunk::activate ( DrawActionBase * action, UInt32 idx )
#else
void TextureTransformChunk::activate ( DrawActionBase *, UInt32 )
#endif
{
#if defined(GL_ARB_multitexture)
    if ( action->getWindow()->hasExtension( _arbMultiTex ) )
          glActiveTextureARB( GL_TEXTURE0_ARB + idx );
#endif
  
    glMatrixMode(GL_TEXTURE);
    glLoadMatrixf(getMatrix().getValues());
    glMatrixMode(GL_MODELVIEW);
}

#if defined(GL_ARB_multitexture)
void TextureTransformChunk::changeFrom( DrawActionBase * action, StateChunk * old, UInt32 idx )
#else
void TextureTransformChunk::changeFrom( DrawActionBase *, StateChunk * old, UInt32 )
#endif
{
    // change from me to me?
    // this assumes I haven't changed in the meantime. is that a valid assumption?
    if ( old == this )
        return;

#if defined(GL_ARB_multitexture)
    if ( action->getWindow()->hasExtension( _arbMultiTex ) )
        glActiveTextureARB( GL_TEXTURE0_ARB + idx );
#endif

    glMatrixMode(GL_TEXTURE);
    glLoadMatrixf(getMatrix().getValues());
    glMatrixMode(GL_MODELVIEW);
}

#if defined(GL_ARB_multitexture)
void TextureTransformChunk::deactivate ( DrawActionBase * action, UInt32 idx )
#else
void TextureTransformChunk::deactivate ( DrawActionBase *, UInt32 )
#endif
{
#if defined(GL_ARB_multitexture)
    if ( action->getWindow()->hasExtension( _arbMultiTex ) )
          glActiveTextureARB( GL_TEXTURE0_ARB + idx );
#endif

    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: OSGTextureTransformChunk.cpp,v 1.7 2002/04/30 09:29:12 vossg Exp $";
    static char cvsid_hpp[] = OSGTEXTURETRANSFORMCHUNK_HEADER_CVSID;
    static char cvsid_inl[] = OSGTEXTURETRANSFORMCHUNK_INLINE_CVSID;
}
