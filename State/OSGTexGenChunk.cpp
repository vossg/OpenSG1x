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
#include <OSGGLU.h>

#include "OSGDrawActionBase.h"

#include "OSGTextureChunk.h"

#include "OSGTexGenChunk.h"

OSG_USING_NAMESPACE

/*! \class osg::TexGenChunk
    \ingroup StateChunks

Chunk for texture coordinate generation functions.

*/

StateChunkClass TexGenChunk::_class("TexGen", osgMaxTextures);

// this should go somewhere central...

#ifdef OSG_DEBUG
#define glErr(text)                           \
{                                   \
        GLenum glerr;                           \
        glerr=glGetError();                     \
        if(glerr!=GL_NO_ERROR)                     \
        {                               \
                fprintf(stderr, "%s failed: %s (%#x)\n", (text),    \
                                        gluErrorString(glerr), glerr);  \
        }                               \
}
#else
#define glErr(text)
#endif

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

TexGenChunk::TexGenChunk(void) :
    Inherited()
{
}

//! Copy Constructor

TexGenChunk::TexGenChunk(const TexGenChunk &source) :
    Inherited(source)
{
}

//! Destructor

TexGenChunk::~TexGenChunk(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void TexGenChunk::initMethod (void)
{
}

//! react to field changes

void TexGenChunk::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

//! output the instance for debug purposes

void TexGenChunk::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump TexGenChunk NI" << std::endl;
}


// little helper to activate genfuncs

static inline void setGenFunc(GLenum coord, GLenum gen, GLenum func, 
                              Vec4f &plane)
{
    if(func != GL_NONE)                                         
    {                                                                   
        glTexGeni(coord, GL_TEXTURE_GEN_MODE, func);
        if(func == GL_OBJECT_LINEAR)
            glTexGenfv(coord, GL_OBJECT_PLANE, (GLfloat*)plane.getValues());
        else if(func == GL_EYE_LINEAR)
            glTexGenfv(coord, GL_EYE_PLANE, (GLfloat*)plane.getValues());
        glEnable(gen);
    }
}

void TexGenChunk::activate( DrawActionBase *action, UInt32 idx )
{
    glErr("TexGenChunk::activate precheck");
        
    TextureChunk::activateTexture(action->getWindow(), idx);

    FDEBUG(("TexGenChunk::activate\n"));

    // genfuncs
    setGenFunc(GL_S, GL_TEXTURE_GEN_S, getGenFuncS(), getGenFuncSPlane());
    glErr("TexGenChunk::activateS");
    setGenFunc(GL_T, GL_TEXTURE_GEN_T, getGenFuncT(), getGenFuncTPlane());
    glErr("TexGenChunk::activateT");
    setGenFunc(GL_R, GL_TEXTURE_GEN_R, getGenFuncR(), getGenFuncRPlane());
    glErr("TexGenChunk::activateR");
    setGenFunc(GL_Q, GL_TEXTURE_GEN_Q, getGenFuncQ(), getGenFuncQPlane());
    glErr("TexGenChunk::activateQ");
}


static inline void changeGenFunc(GLenum oldfunc, GLenum coord, GLenum gen, 
                                 GLenum func, Vec4f &plane)
{
    if(func != GL_NONE)                                         
    {                                                                   
       glTexGeni(coord, GL_TEXTURE_GEN_MODE, func);
        if(func == GL_OBJECT_LINEAR)
            glTexGenfv(coord, GL_OBJECT_PLANE, (GLfloat*)plane.getValues());
        else if(func == GL_EYE_LINEAR)
            glTexGenfv(coord, GL_EYE_PLANE, (GLfloat*)plane.getValues());
        if(oldfunc == GL_NONE) 
            glEnable(gen);
    }
    else if(oldfunc != GL_NONE) 
        glDisable(gen);  
}

void TexGenChunk::changeFrom(   DrawActionBase *action, 
                                StateChunk     *old   , 
                                UInt32          idx)
{
    // change from me to me?
    // this assumes I haven't changed in the meantime. 
    // is that a valid assumption?
    if(old == this)
        return;

    TexGenChunk *oldp      = dynamic_cast<TexGenChunk *>(old);
    
    // If the old one is not a texgen chunk, deactivate it and activate
    // ourselves
    if(!oldp)
    {
        old->deactivate(action, idx);
        activate(action, idx);
        return;
    }

    glErr("TexGenChunk::changeFrom precheck");
    
    TextureChunk::activateTexture(action->getWindow(), idx);

    changeGenFunc(oldp->getGenFuncS(), GL_S, GL_TEXTURE_GEN_S, 
                        getGenFuncS(), getGenFuncSPlane());
    changeGenFunc(oldp->getGenFuncT(), GL_T, GL_TEXTURE_GEN_T, 
                        getGenFuncT(), getGenFuncTPlane());
    changeGenFunc(oldp->getGenFuncR(), GL_R, GL_TEXTURE_GEN_R, 
                        getGenFuncR(), getGenFuncRPlane());
    changeGenFunc(oldp->getGenFuncQ(), GL_Q, GL_TEXTURE_GEN_Q, 
                        getGenFuncQ(), getGenFuncQPlane());

    glErr("TexGenChunk::changeFrom");
}

void TexGenChunk::deactivate(DrawActionBase *action, UInt32 idx)
{
    glErr("TexGenChunk::deactivate precheck");

    TextureChunk::activateTexture(action->getWindow(), idx);

    if(getGenFuncS() != GL_NONE)
        glDisable(GL_TEXTURE_GEN_S);

    if(getGenFuncS() != GL_NONE)
        glDisable(GL_TEXTURE_GEN_T);

    if(getGenFuncS() != GL_NONE)
        glDisable(GL_TEXTURE_GEN_R);

    if(getGenFuncS() != GL_NONE)
        glDisable(GL_TEXTURE_GEN_Q);

    glErr("TexGenChunk::deactivate");
}

/*-------------------------- comparison -----------------------------------*/

Real32 TexGenChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

/** \brief assignment
 */

bool TexGenChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

/** \brief equal
 */

bool TexGenChunk::operator == (const StateChunk &other) const
{
    TexGenChunk const *tother = dynamic_cast<TexGenChunk const*>(&other);

    if(!tother)
        return false;

    if(tother == this)
        return true;

    return  getGenFuncS()   == tother->getGenFuncS() &&
            getGenFuncT()   == tother->getGenFuncT() &&
            getGenFuncR()   == tother->getGenFuncR() &&
            getGenFuncQ()   == tother->getGenFuncQ() &&
            // not quite right. needs only to be tested for genfuncs using them
            getGenFuncSPlane()  == tother->getGenFuncSPlane() &&
            getGenFuncTPlane()  == tother->getGenFuncTPlane() &&
            getGenFuncRPlane()  == tother->getGenFuncRPlane() &&
            getGenFuncQPlane()  == tother->getGenFuncQPlane() ;
}

/** \brief unequal
 */

bool TexGenChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}


#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGTexGenChunk.cpp,v 1.4 2002/09/02 07:05:07 vossg Exp $";
    static Char8 cvsid_hpp[] = OSGTEXGENCHUNK_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGTEXGENCHUNK_INLINE_CVSID;
}

