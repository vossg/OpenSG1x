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
    \ingroup GrpSystemState

See \ref PageSystemBlendChunk for details.

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass BlendChunk::_class("Blend");

UInt32 BlendChunk::_extBlend;
UInt32 BlendChunk::_extImaging;
UInt32 BlendChunk::_extBlendSubtract;
UInt32 BlendChunk::_extBlendMinMax;
UInt32 BlendChunk::_extBlendLogicOp;
UInt32 BlendChunk::_funcBlendColor;
UInt32 BlendChunk::_funcBlendEquation;
UInt32 BlendChunk::_funcBlendEquationExt;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void BlendChunk::initMethod (void)
{
    Inherited::initMethod();
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

BlendChunk::BlendChunk(void) :
    Inherited()
{
    _extBlend             =
        Window::registerExtension("GL_EXT_blend_color");
    _extImaging           =
        Window::registerExtension("GL_ARB_imaging");
    _extBlendSubtract     =
        Window::registerExtension("GL_EXT_blend_subtract");
    _extBlendMinMax       =
        Window::registerExtension("GL_EXT_blend_minmax");
    _extBlendLogicOp      =
        Window::registerExtension("GL_EXT_blend_logic_op");
    _funcBlendColor       =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glBlendColorEXT");
    _funcBlendEquation    =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glBlendEquation");
    _funcBlendEquationExt =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glBlendEquationEXT");
}

BlendChunk::BlendChunk(const BlendChunk &source) :
    Inherited(source)
{
}

BlendChunk::~BlendChunk(void)
{
}

/*------------------------------- Sync -----------------------------------*/

void BlendChunk::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

/*------------------------------ Output ----------------------------------*/

void BlendChunk::dump(      UInt32    OSG_CHECK_ARG(uiIndent),
                      const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump BlendChunk NI" << std::endl;
}

/*------------------------------ State ------------------------------------*/

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
                void (OSG_APIENTRY*blendcolor)(GLclampf red,GLclampf green,GLclampf blue,
                     GLclampf alpha ) =
                    (void (OSG_APIENTRY*)(GLclampf red,GLclampf green,GLclampf blue,
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

    if(_sfEquation.getValue() != GL_NONE)
    {
#if defined(GL_ARB_imaging)
        if(action->getWindow()->hasExtension(_extImaging))
        {
            // get "glBlendEquation" function pointer
            void (OSG_APIENTRY* blendeq)(GLenum mode) =
                (void (OSG_APIENTRY*)(GLenum mode))
                action->getWindow()->getFunction(_funcBlendEquation);

             blendeq(_sfEquation.getValue());
        }

#elif defined(GL_EXT_blend_subtract) || defined(GL_EXT_blend_minmax) || \
    defined(GL_EXT_blend_logic_op)
        if(action->getWindow()->hasExtension(_extBlendSubtract) ||
           action->getWindow()->hasExtension(_extBlendMinMax) ||
           action->getWindow()->hasExtension(_extBlendLogicOp))
        {
            // get "glBlendEquationEXT" function pointer
            void (OSG_APIENTRY* blendeq)(GLenum mode) =
                (void (OSG_APIENTRY*)(GLenum mode))
                action->getWindow()->getFunction(_funcBlendEquationExt);

             blendeq(_sfEquation.getValue());
        }
#endif
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
                void (OSG_APIENTRY*blendcolor)(GLclampf red,GLclampf green,GLclampf blue,
                     GLclampf alpha ) =
                    (void (OSG_APIENTRY*)(GLclampf red,GLclampf green,GLclampf blue,
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

    if(_sfEquation.getValue() != old->_sfEquation.getValue())
    {
#if defined(GL_ARB_imaging)
        if(action->getWindow()->hasExtension(_extImaging))
        {
            // get "glBlendEquation" function pointer
            void (OSG_APIENTRY* blendeq)(GLenum mode) =
                (void (OSG_APIENTRY*)(GLenum mode))
                action->getWindow()->getFunction(_funcBlendEquation);

             blendeq(_sfEquation.getValue());
        }

#elif defined(GL_EXT_blend_subtract) || defined(GL_EXT_blend_minmax) || \
    defined(GL_EXT_blend_logic_op)
        if(action->getWindow()->hasExtension(_extBlendSubtract) ||
           action->getWindow()->hasExtension(_extBlendMinMax) ||
           action->getWindow()->hasExtension(_extBlendLogicOp))
        {
            // get "glBlendEquationEXT" function pointer
            void (OSG_APIENTRY* blendeq)(GLenum mode) =
                (void (OSG_APIENTRY*)(GLenum mode))
                action->getWindow()->getFunction(_funcBlendEquationExt);

             blendeq(_sfEquation.getValue());
        }
#endif
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

void BlendChunk::deactivate ( DrawActionBase *action, UInt32 )
{
    if(_sfSrcFactor.getValue() != GL_NONE)
    {
        glDisable(GL_BLEND);
    }

    if(_sfEquation.getValue() != GL_NONE)
    {
#if defined(GL_ARB_imaging)
        if(action->getWindow()->hasExtension(_extImaging))
        {
            // get "glBlendEquation" function pointer
            void (OSG_APIENTRY* blendeq)(GLenum mode) =
                (void (OSG_APIENTRY*)(GLenum mode))
                action->getWindow()->getFunction(_funcBlendEquation);

             blendeq(GL_FUNC_ADD);
        }

#elif defined(GL_EXT_blend_subtract) || defined(GL_EXT_blend_minmax) || \
    defined(GL_EXT_blend_logic_op)
        if(action->getWindow()->hasExtension(_extBlendSubtract) ||
           action->getWindow()->hasExtension(_extBlendMinMax) ||
           action->getWindow()->hasExtension(_extBlendLogicOp))
        {
            // get "glBlendEquationEXT" function pointer
            void (OSG_APIENTRY* blendeq)(GLenum mode) =
                (void (OSG_APIENTRY*)(GLenum mode))
                action->getWindow()->getFunction(_funcBlendEquationExt);

             blendeq(GL_FUNC_ADD_EXT);
        }
#endif
    }
    
    if(_sfAlphaFunc.getValue() != GL_NONE)
    {
        glDisable(GL_ALPHA_TEST);
    }
}

/*-------------------------- Comparison -----------------------------------*/

Real32 BlendChunk::switchCost(StateChunk *)
{
    return 0;
}

bool BlendChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool BlendChunk::operator == (const StateChunk &other) const
{
    BlendChunk const *tother = dynamic_cast<BlendChunk const*>(&other);

    if(!tother)
        return false;

    if(tother == this)
        return true;

    if(getSrcFactor()  != tother->getSrcFactor()  ||
       getDestFactor() != tother->getDestFactor() ||
       getEquation()   != tother->getEquation()   ||
       getColor()      != tother->getColor()      ||
       getAlphaFunc()  != tother->getAlphaFunc()  ||
       getAlphaValue() != tother->getAlphaValue()   )
        return false;

    return true;
}

bool BlendChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.13 2002/06/01 10:37:25 vossg Exp $";
    static Char8 cvsid_hpp       [] = OSGBLENDCHUNK_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGBLENDCHUNK_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGBLENDCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif


