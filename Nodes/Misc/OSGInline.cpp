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

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>
#include <OSGDrawAction.h>

#include "OSGInline.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGINLINE_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGINLINE_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/*! \class osg::Inline
*/

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void Inline::changed(BitVector, ChangeMode)
{
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void Inline::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                  const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump Inline NI" << endl;
}

/*-------------------------------------------------------------------------*/
/*                              Inline Draw                                */

#ifdef OSG_NOFUNCTORS
OSG::Action::ResultE Inline::InlineDrawEnter(CNodePtr &cnode, 
                                             Action   *pAction)
{
    NodeCore *pNC = cnode.getCPtr();
    Inline   *pSC = dynamic_cast<Inline *>(pNC);

    if(pSC == NULL)
    {
        fprintf(stderr, "MGDE: core NULL\n");
        return Action::Skip;
    }
    else
    {
        return pSC->drawEnter(pAction);
    }
}

OSG::Action::ResultE Inline::InlineDrawLeave(CNodePtr &cnode, 
                                             Action  *pAction)
{
    NodeCore *pNC = cnode.getCPtr();
    Inline   *pSC = dynamic_cast<Inline *>(pNC);

    if(pSC == NULL)
    {
        fprintf(stderr, "MGDL: core NULL\n");
        return Action::Skip;
    }
    else
    {
        return pSC->drawLeave(pAction);
    }
}
#endif

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

Inline::Inline(void) :
    Inherited()
{
}

Inline::Inline(const Inline &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

Inline::~Inline(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Draw                                     */

Action::ResultE Inline::drawEnter(Action *action)
{
    DrawAction *da = dynamic_cast<DrawAction *>(action);

    if(da->selectVisibles() == 0)
        return Action::Skip;
    
    return Action::Continue;
}

Action::ResultE Inline::drawLeave(Action *)
{
    return Action::Continue;
}

/*-------------------------------------------------------------------------*/
/*                                Init                                     */

void Inline::initMethod(void)
{
#ifndef OSG_NOFUNCTORS
    DrawAction::registerEnterDefault( 
        getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                  CNodePtr,  
                                  InlinePtr, 
                                  Action *>(&Inline::drawEnter));

    DrawAction::registerLeaveDefault( 
        getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                  CNodePtr,  
                                  InlinePtr, 
                                  Action *>(&Inline::drawLeave));
#else
    DrawAction::registerEnterDefault(
        getClassType(), 
        Action::osgFunctionFunctor2(Inline::InlineDrawEnter));

    DrawAction::registerLeaveDefault(
        getClassType(), 
        Action::osgFunctionFunctor2(Inline::InlineDrawLeave));
#endif
}
