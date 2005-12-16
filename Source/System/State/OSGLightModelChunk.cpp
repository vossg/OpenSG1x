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

#include <OSGGLEXT.h>

#include "OSGLightModelChunk.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::LightModelChunk
The LightModelChunk wraps most of glLightModel. It does not wrap GL_LIGHT_MODEL_TWO_SIDE, which is wrapped by TwoSidedLightingChunk.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass LightModelChunk::_class("LightModel");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void LightModelChunk::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

LightModelChunk::LightModelChunk(void) :
    Inherited()
{
}

LightModelChunk::LightModelChunk(const LightModelChunk &source) :
    Inherited(source)
{
}

LightModelChunk::~LightModelChunk(void)
{
}

/*----------------------------- class specific ----------------------------*/

const StateChunkClass *LightModelChunk::getClass(void) const
{
    return &_class;
}

void LightModelChunk::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void LightModelChunk::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump LightModelChunk NI" << std::endl;
}

/*------------------------------ State ------------------------------------*/

void LightModelChunk::activate ( DrawActionBase * action, UInt32 idx )
{
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, _sfAmbient.getValue().getValuesRGBA());

    const GLenum color_control = _sfColorControl.getValue();
    if(color_control == GL_SINGLE_COLOR ||
        color_control == GL_SEPARATE_SPECULAR_COLOR)
    {
        glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, color_control);
    }

    if(_sfLocalViewer.getValue())
    {
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
    }
    else
    {
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 0);
    }
}

void LightModelChunk::changeFrom( DrawActionBase *action, StateChunk *old_chunk, UInt32 idx )
{
    LightModelChunk *old = dynamic_cast<LightModelChunk *>(old_chunk);

    if(old == NULL)
    {
        FWARNING(( "LightModelChunk::changeFrom: caught non-LightModelChunk!\n"));
        return;
    }

    // LightModelChunk didn't change so do nothing.
    if(old == this)
        return;

    if(old->_sfAmbient.getValue() != _sfAmbient.getValue())
    {
       glLightModelfv(GL_LIGHT_MODEL_AMBIENT, _sfAmbient.getValue().getValuesRGBA());
    }

    const GLenum color_control = _sfColorControl.getValue();
    if(color_control == GL_SINGLE_COLOR ||
        color_control == GL_SEPARATE_SPECULAR_COLOR &&
        color_control != old->_sfColorControl.getValue())
    {
        glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, color_control);
    }

    if(_sfLocalViewer.getValue() != old->_sfLocalViewer.getValue())
    {
        if(_sfLocalViewer.getValue())
        {
            glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
        }
        else
        {
            glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 0);
        }
    }
}

void LightModelChunk::deactivate ( DrawActionBase * action, UInt32 idx )
{
    GLfloat ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

    if(_sfColorControl.getValue() != GL_SINGLE_COLOR)
    {
        glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SINGLE_COLOR);
    }

    if(_sfLocalViewer.getValue())
    {
       glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 0);
    }
}

/*-------------------------- Comparison -----------------------------------*/

Real32 LightModelChunk::switchCost(StateChunk *)
{
    return 0;
}

bool LightModelChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool LightModelChunk::operator == (const StateChunk &other) const
{
    LightModelChunk const *tother = dynamic_cast<LightModelChunk const*>(&other);

    if(!tother)
        return false;

    if(tother == this)
        return true;

    if(getAmbient()  != tother->getAmbient()  ||
       getColorControl() != tother->getColorControl() ||
       getLocalViewer()   != tother->getLocalViewer()   )
        return false;

    return true;
}

bool LightModelChunk::operator != (const StateChunk &other) const
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGLightModelChunk.cpp,v 1.2 2005/12/16 11:05:45 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGLIGHTMODELCHUNKBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGLIGHTMODELCHUNKBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGLIGHTMODELCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

