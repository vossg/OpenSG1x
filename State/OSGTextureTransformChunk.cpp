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

#include <GL/gl.h>

#include "OSGTextureTransformChunk.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: OSGTextureTransformChunk.cpp,v 1.4 2001/12/17 15:41:18 dirk Exp $";
    static char cvsid_hpp[] = OSGTEXTURETRANSFORMCHUNK_HEADER_CVSID;
    static char cvsid_inl[] = OSGTEXTURETRANSFORMCHUNK_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/*! \class osg::TextureTransformChunk

*/

StateChunkClass TextureTransformChunk::_class("TextureTransform");

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

TextureTransformChunk::TextureTransformChunk(void) :
    Inherited()
{
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

void TextureTransformChunk::activate ( DrawActionBase *,  UInt32 )
{
    glMatrixMode(GL_TEXTURE);
    glLoadMatrixf(getMatrix().getValues());
    glMatrixMode(GL_MODELVIEW);
}

void TextureTransformChunk::changeFrom( DrawActionBase *,  StateChunk * old, UInt32 )
{
    // change from me to me?
    // this assumes I haven't changed in the meantime. is that a valid assumption?
    if ( old == this )
        return;

    glMatrixMode(GL_TEXTURE);
    glLoadMatrixf(getMatrix().getValues());
    glMatrixMode(GL_MODELVIEW);
}

void TextureTransformChunk::deactivate ( DrawActionBase *,  UInt32 )
{
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
}


