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

#include <OSGGL.h>
#include <OSGGLEXT.h>

#include "OSGWindow.h"

#include "OSGVertexProgramChunk.h"

OSG_USING_NAMESPACE

/*! \class osg::VertexProgramChunk
    \ingroup GrpSystemState

See \ref PageSystemVertexProgramChunk for a description. The VertexProgramChunk
implements Vertex Programs as specified in the GL_ARB_vertex_program extension.
It is just a special version of the osg::ProgramChunk, which contains the whole
public interface.

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass VertexProgramChunk::_class("VertexProgram");

UInt32 VertexProgramChunk::_arbVertexProgram;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void VertexProgramChunk::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

VertexProgramChunk::VertexProgramChunk(void) :
    Inherited()
{
    _arbVertexProgram = Window::registerExtension("GL_ARB_vertex_program");
}

VertexProgramChunk::VertexProgramChunk(const VertexProgramChunk &source) :
    Inherited(source)
{
}

VertexProgramChunk::~VertexProgramChunk(void)
{
}

/*----------------------------- onCreate --------------------------------*/

void VertexProgramChunk::onCreate(const VertexProgramChunk *)
{
    if(GlobalSystemState == Startup)
        return;

    // !!! this temporary is needed to work around compiler problems (sgi)
    // CHECK CHECK
    //  VertexProgramChunkPtr tmpPtr = FieldContainer::getPtr<ProgramChunkPtr>(*this);
    VertexProgramChunkPtr tmpPtr(*this);

    beginEditCP(tmpPtr, VertexProgramChunk::GLIdFieldMask);

    setGLId(
        Window::registerGLObject(
            osgTypedMethodVoidFunctor2ObjCPtrPtr<VertexProgramChunkPtr, 
                                                 Window , 
                                                 UInt32>(
                                                     tmpPtr, 
                                                     &VertexProgramChunk::handleGL),
            1));

    endEditCP(tmpPtr, VertexProgramChunk::GLIdFieldMask);
}


/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *VertexProgramChunk::getClass(void) const
{
    return &_class;
}

/*----------------------------- class specific ----------------------------*/

void VertexProgramChunk::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void VertexProgramChunk::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump VertexProgramChunk NI" << std::endl;
}

/*------------------------------ State ------------------------------------*/

/*! GL object handler
    create the program and destroy it
*/
void VertexProgramChunk::handleGL(Window *win, UInt32 idstatus)
{
    Inherited::handleGL(win, idstatus, GL_VERTEX_PROGRAM_ARB, _arbVertexProgram);
}

UInt32 VertexProgramChunk::getExtension(void) const
{
    return _arbVertexProgram;
}

GLenum VertexProgramChunk::getTarget(void) const
{
    return GL_VERTEX_PROGRAM_ARB;
}

const char *VertexProgramChunk::getTargetName(void) const
{
    return "Vertex Program";
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: $";
    static Char8 cvsid_hpp       [] = OSGVERTEXPROGRAMCHUNKBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGVERTEXPROGRAMCHUNKBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGVERTEXPROGRAMCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

