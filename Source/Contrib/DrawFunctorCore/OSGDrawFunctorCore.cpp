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

#include <OSGAction.h>
#include <OSGDrawAction.h>
#include <OSGRenderAction.h>
#include <OSGState.h>
#include <OSGMaterial.h>

#include "OSGDrawFunctorCore.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DrawFunctorCore
A NodeCore that uses two Functors to define the geometry to be drawn.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DrawFunctorCore::initMethod (void)
{
    DrawAction::registerEnterDefault( getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, MaterialDrawablePtr,
              CNodePtr, Action *>(&MaterialDrawable::drawActionHandler));
  
    RenderAction::registerEnterDefault( getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, MaterialDrawablePtr,
              CNodePtr, Action *>(&MaterialDrawable::renderActionHandler));
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DrawFunctorCore::DrawFunctorCore(void) :
    Inherited()
{
}

DrawFunctorCore::DrawFunctorCore(const DrawFunctorCore &source) :
    Inherited(source)
{
}

DrawFunctorCore::~DrawFunctorCore(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DrawFunctorCore::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DrawFunctorCore::dump(      UInt32    , 
                           const BitVector ) const
{
    SLOG << "Dump DrawFunctorCore NI" << std::endl;
}

   
Action::ResultE DrawFunctorCore::drawPrimitives(DrawActionBase *action)
{
    getDraw().call(action);
    
    return Action::Continue;
}


void DrawFunctorCore::adjustVolume(Volume & volume)
{   
    volume.setValid();
    volume.setEmpty();

    getVolumeUpdate().call(&volume);
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
    static Char8 cvsid_hpp       [] = OSGDRAWFUNCTORCOREBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDRAWFUNCTORCOREBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDRAWFUNCTORCOREFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

