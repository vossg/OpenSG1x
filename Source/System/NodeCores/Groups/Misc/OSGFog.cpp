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
#include <OSGDrawAction.h>
#include <OSGRenderAction.h>

#include "OSGFog.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Fog
The fog chunk contains the parameters that are specific for rendering fog.  
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Fog::initMethod (void)
{
    DrawAction::registerEnterDefault(
        getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            FogPtr,
            CNodePtr,
            Action*>(&Fog::drawEnter));

    DrawAction::registerLeaveDefault(
        getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            FogPtr,
            CNodePtr,
            Action*>(&Fog::drawLeave));
    
    RenderAction::registerEnterDefault( 
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            FogPtr, 
            CNodePtr,  
            Action*>(&Fog::renderEnter));

    RenderAction::registerLeaveDefault(
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<
            OSG::Action::ResultE,
            FogPtr, 
            CNodePtr,  
            Action*>(&Fog::renderLeave));
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Fog::Fog(void) :
    Inherited(),
    _pChunk(NullFC)
{
}

Fog::Fog(const Fog &source) :
    Inherited(source),
    _pChunk(source._pChunk)
{
}

Fog::~Fog(void)
{
    if(_pChunk != NullFC)
        subRefCP(_pChunk);
}

/*-----------------------------Chunk---------------------------------------*/

FogChunkPtr Fog::getChunk(void)
{
    if (_pChunk == NullFC)
    {
        makeChunk();
    }
    
    return _pChunk;
}

void Fog::makeChunk(void)
{
    if (_pChunk == NullFC)
    {
        _pChunk = FogChunk::create();
        
        _pChunk->setMode(getMode());
        _pChunk->setColor(getColor());
        _pChunk->setStart(getStart());
        _pChunk->setEnd(getEnd());
        _pChunk->setDensity(getDensity());
    }
}

/*----------------------------- class specific ----------------------------*/

void Fog::changed(BitVector whichField, UInt32 origin)
{
    // pass through values
    if (whichField & OnFieldMask    || 
        whichField & ModeFieldMask  ||  
        whichField & ColorFieldMask ||  
        whichField & StartFieldMask ||  
        whichField & EndFieldMask   ||  
        whichField & DensityFieldMask)
    {
        FogChunkPtr fog = getChunk();
        
        beginEditCP(fog);
            fog->setMode(getMode());
            fog->setColor(getColor());
            fog->setStart(getStart());
            fog->setEnd(getEnd());
            fog->setDensity(getDensity());
        endEditCP(fog);
    }
    
    Inherited::changed(whichField, origin);
}

void Fog::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Fog NI" << std::endl;
}

/*-----------------------------Rendering-----------------------------------*/
Action::ResultE Fog::drawEnter(Action *action)
{
    DrawActionBase *da = dynamic_cast<DrawActionBase*>(action);
    
    if(getOn())
        getChunk()->activate(da);

    return Action::Continue;
}

Action::ResultE Fog::drawLeave(Action *action)
{
    DrawActionBase *da = dynamic_cast<DrawActionBase*>(action);
    
    if(getOn())
        getChunk()->deactivate(da);

    return Action::Continue;
}

Action::ResultE Fog::renderEnter(Action *action)
{
    if(!getOn())
        return Action::Continue;

    RenderAction *pAction = dynamic_cast<RenderAction *>(action);
    
    if(pAction->pushVisibility())
    {
        if(pAction->selectVisibles() == 0)
        {
            pAction->popVisibility();
            return Action::Skip;
        }
    }

    pAction->dropFog(this);

    return Action::Continue;
}

Action::ResultE Fog::renderLeave(Action *action)
{
    if (!getOn())
        return Action::Continue;

    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    pAction->undropFog(this);

    pAction->popVisibility();

    return Action::Continue;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGFog.cpp,v 1.2 2009/11/13 18:07:01 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGFOGBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGFOGBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGFOGFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

