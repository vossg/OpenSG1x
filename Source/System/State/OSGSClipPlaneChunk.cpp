/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include <OSGDrawActionBase.h>
#include <OSGRenderAction.h>
#include <OSGCamera.h>

#include "OSGSClipPlaneChunk.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SClipPlaneChunk
    \ingroup GrpSystemState
    
See \ref PageSystemSClipPlaneChunk for a description.

This chunk wraps glCLipPlane() (osg::SClipPlaneChunk::_sfEquation) and
glEnable(GL_CLIP_PLANEi) (osg::SClipPlaneChunk::_sfEnable). The coordinate
system the plane is in is defined by osg::SClipPlaneChunk::_sfBeacon.

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/
   
StateChunkClass SClipPlaneChunk::_class("SClipPlane", 6);

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/
   
/*----------------------- constructors & destructors ----------------------*/

SClipPlaneChunk::SClipPlaneChunk(void) :
    Inherited()
{
}

SClipPlaneChunk::SClipPlaneChunk(const SClipPlaneChunk &source) :
    Inherited(source)
{
}

SClipPlaneChunk::~SClipPlaneChunk(void)
{
}

/*----------------------- Chunk Class Access -----------------------------*/

const StateChunkClass *SClipPlaneChunk::getClass(void) const
{
     return &_class;
}

/*------------------------------- Sync -----------------------------------*/

void SClipPlaneChunk::changed(BitVector, UInt32)
{
}

/*------------------------------ Output ----------------------------------*/

void SClipPlaneChunk::dump(      UInt32    , 
                          const BitVector) const
{
    SLOG << "Dump SClipPlaneChunk NI" << std::endl;
}


/*------------------------------ State ------------------------------------*/

void SClipPlaneChunk::activate(DrawActionBase *action, UInt32 idx)
{
    RenderAction *ra = dynamic_cast<RenderAction *>(action);

    GLdouble glEq[4];
    Vec4f   & eq = getEquation();
    glEq[0] = eq[0];
    glEq[1] = eq[1];
    glEq[2] = eq[2];
    glEq[3] = eq[3];

    glClipPlane( GL_CLIP_PLANE0 + idx, glEq);
    glEnable( GL_CLIP_PLANE0 + idx);
}




void SClipPlaneChunk::changeFrom(DrawActionBase *action, StateChunk * old_chunk, 
                                UInt32 idx)
{
    SClipPlaneChunk const *old = dynamic_cast<SClipPlaneChunk const*>(old_chunk);

    // change from me to me?
    // this assumes I haven't changed in the meantime. is that a valid assumption?
    if(old == this)
        return;

    RenderAction *ra = dynamic_cast<RenderAction *>(action);

    GLdouble glEq[4];
    Vec4f   & eq = getEquation();
    glEq[0] = eq[0];
    glEq[1] = eq[1];
    glEq[2] = eq[2];
    glEq[3] = eq[3];

    glClipPlane( GL_CLIP_PLANE0 + idx, glEq);
}


void SClipPlaneChunk::deactivate(DrawActionBase *, UInt32 idx)
{
    glDisable( GL_CLIP_PLANE0 + idx);
}


/*-------------------------- Comparison -----------------------------------*/

Real32 SClipPlaneChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool SClipPlaneChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool SClipPlaneChunk::operator == (const StateChunk &other) const
{
    SClipPlaneChunk const *tother = dynamic_cast<SClipPlaneChunk const*>(&other);

    if(!tother)
        return false;

    if(getEquation() != tother->getEquation())
        return false;

    return true;
}

bool SClipPlaneChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177)
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGSClipPlaneChunk.cpp,v 1.1 2007/04/26 15:22:01 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGSCLIPPLANECHUNK_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSCLIPPLANECHUNK_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSCLIPPLANECHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

