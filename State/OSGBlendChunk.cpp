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

#include "OSGConfig.h"

#include <OSGGL.h>

#include "OSGDrawActionBase.h"
#include "OSGWindow.h"

#include "OSGBlendChunk.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::BlendChunk
    \ingroup StateChunks

The blending chunk handles OpenGL blending, i.e. the definition how incoming
pixel are combined with the pixel already in the frame buffer.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char BlendChunk::cvsid[] = "@(#)$Id: OSGBlendChunk.cpp,v 1.15 2002/03/19 18:08:16 dirk Exp $";

StateChunkClass BlendChunk::_class("Blend");

UInt32 BlendChunk::_extBlend;
UInt32 BlendChunk::_funcBlendColor;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/** \brief initialize the static features of the class, e.g. action callbacks
 */

void BlendChunk::initMethod (void)
{
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

BlendChunk::BlendChunk(void) :
    Inherited()
{
    _extBlend      =Window::registerExtension("GL_EXT_blend_color");
    _funcBlendColor=Window::registerFunction ("glBlendColorEXT");
}

/** \brief Copy Constructor
 */

BlendChunk::BlendChunk(const BlendChunk &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

BlendChunk::~BlendChunk(void)
{
}


/** \brief react to field changes
 */

void BlendChunk::changed(BitVector, ChangeMode)
{
}

/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void BlendChunk::dump(      UInt32    OSG_CHECK_ARG(uiIndent),
                      const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump BlendChunk NI" << endl;
}

/*-------------------------- your_category---------------------------------*/

void BlendChunk::activate(DrawActionBase *action, UInt32)
{
    if(_sfSrcFactor.getValue() != GL_NONE)
    {
        GLenum src  = _sfSrcFactor.getValue();
        GLenum dest = _sfDestFactor.getValue();
        
        glBlendFunc(src, dest);

#if GL_EXT_blend_color
        // This is not nice, but efficient
        // As the OpenGL constants are fixed it should be safe
        if((src  >= GL_CONSTANT_COLOR_EXT && 
            src  <= GL_ONE_MINUS_CONSTANT_ALPHA_EXT ) ||
           (dest >= GL_CONSTANT_COLOR_EXT && 
            dest <= GL_ONE_MINUS_CONSTANT_ALPHA_EXT )
          )
        {
            if ( action->getWindow()->hasExtension(_extBlend ))
            {
                // get "glBlendColorEXT" function pointer
                void (*blendcolor)(GLclampf red,GLclampf green,GLclampf blue,
                     GLclampf alpha ) =
                    (void (*)(GLclampf red,GLclampf green,GLclampf blue,
                     GLclampf alpha))
                    action->getWindow()->getFunction( _funcBlendColor );

                 blendcolor(_sfColor.getValue().red(),
                            _sfColor.getValue().green(),
                            _sfColor.getValue().blue(),
                            _sfColor.getValue().alpha());
            }
        }
#endif
        glEnable(GL_BLEND);
    }
    
    if(_sfAlphaFunc.getValue() != GL_NONE)
    {
        glAlphaFunc(_sfAlphaFunc.getValue(), _sfAlphaValue.getValue());
        glEnable(GL_ALPHA_TEST);
    }
}

void BlendChunk::changeFrom( DrawActionBase *action, 
                             StateChunk * old_chunk, 
                             UInt32 )
{
    BlendChunk *old = dynamic_cast<BlendChunk *>(old_chunk);
    
    if(_sfSrcFactor.getValue() != GL_NONE)
    {
        GLenum src  = _sfSrcFactor.getValue();
        GLenum dest = _sfDestFactor.getValue();
        
        if(old->_sfSrcFactor.getValue()  != src ||
           old->_sfDestFactor.getValue() != dest)
            glBlendFunc(src, dest);

#if GL_EXT_blend_color
        // This is not nice, but efficient
        // As the OpenGL constants are fixed it should be safe
        if((src  >= GL_CONSTANT_COLOR_EXT && 
            src  <= GL_ONE_MINUS_CONSTANT_ALPHA_EXT ) ||
           (dest >= GL_CONSTANT_COLOR_EXT && 
            dest <= GL_ONE_MINUS_CONSTANT_ALPHA_EXT )
          )
        {
            if ( action->getWindow()->hasExtension(_extBlend ))
            {
                // get "glBlendColorEXT" function pointer
                void (*blendcolor)(GLclampf red,GLclampf green,GLclampf blue,
                     GLclampf alpha ) =
                    (void (*)(GLclampf red,GLclampf green,GLclampf blue,
                     GLclampf alpha))
                    action->getWindow()->getFunction( _funcBlendColor );

                 blendcolor(_sfColor.getValue().red(),
                            _sfColor.getValue().green(),
                            _sfColor.getValue().blue(),
                            _sfColor.getValue().alpha());
            }
        }
#endif
        if(old->_sfSrcFactor.getValue() == GL_NONE)
            glEnable(GL_BLEND);
    }
    else
    {
        if(old->_sfSrcFactor.getValue() != GL_NONE)
            glDisable(GL_BLEND);
    }
    
    if(_sfAlphaFunc.getValue() != GL_NONE)
    {
        if(old->_sfAlphaFunc.getValue()  != _sfAlphaFunc.getValue() ||
           old->_sfAlphaValue.getValue() != _sfAlphaValue.getValue())
            glAlphaFunc(_sfAlphaFunc.getValue(), _sfAlphaValue.getValue());
        
        if(old->_sfAlphaFunc.getValue() == GL_NONE)
            glEnable(GL_ALPHA_TEST);
    }
    else
    {
        if(old->_sfAlphaFunc.getValue() != GL_NONE)
            glDisable(GL_ALPHA_TEST);        
    }
    
}

void BlendChunk::deactivate ( DrawActionBase *, UInt32 )
{
    if(_sfSrcFactor.getValue() != GL_NONE)
    {
        glDisable(GL_BLEND);
    }
    
    if(_sfAlphaFunc.getValue() != GL_NONE)
    {
        glDisable(GL_ALPHA_TEST);
    }
}

/*-------------------------- comparison -----------------------------------*/

Real32 BlendChunk::switchCost(StateChunk *)
{
    return 0;
}

/** \brief assignment
 */

bool BlendChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

/** \brief equal
 */

bool BlendChunk::operator == (const StateChunk &other) const
{
    BlendChunk const *tother = dynamic_cast<BlendChunk const*>(&other);

    if ( !tother )
        return false;

    return true;
}

/** \brief unequal
 */

bool BlendChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}



/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

