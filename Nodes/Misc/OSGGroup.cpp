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

#include "OSGConfig.h"

#include <OSGDrawAction.h>
#include <OSGRenderAction.h>
#include <OSGIntersectAction.h>

#include "OSGGroup.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGGROUP_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGGROUP_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/*! \class osg::Group

  Group is the simplest form of a NodeCore. A group
  carries no predefined data and most actions will only traverse the
  children list. So usually the group does nothing.

*/

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void Group::changed(BitVector, ChangeMode)
{
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void Group::dump(      UInt32    uiIndent, 
                 const BitVector bvFlags) const
{
   Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                       Static Action Callbacks                           */

#ifdef OSG_NOFUNCTORS
OSG::Action::ResultE Group::GroupDrawEnter(CNodePtr &cnode, 
                                           Action   *pAction)
{
    NodeCore *pNC = cnode.getCPtr();
    Group    *pSC = dynamic_cast<Group *>(pNC);

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

OSG::Action::ResultE Group::GroupDrawLeave(CNodePtr &cnode, 
                                           Action   *pAction)
{
    NodeCore *pNC = cnode.getCPtr();
    Group    *pSC = dynamic_cast<Group *>(pNC);

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

OSG::Action::ResultE Group::GroupIntEnter(CNodePtr &cnode,
                                          Action   *pAction)
{
    NodeCore *pNC = cnode.getCPtr();
    Group    *pSC = dynamic_cast<Group *>(pNC);
    
    if(pSC == NULL)
    {
        fprintf(stderr, "MDIE: core NULL\n");
        return Action::Skip;
    }
    else
    {
        return pSC->intersect(pAction);
    }
}
#endif

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

Group::Group(void) :
    Inherited()
{
}

Group::Group(const Group &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

Group::~Group(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Draw                                      */

Action::ResultE Group::drawEnter(Action *action)
{
    DrawActionBase *da = dynamic_cast<DrawActionBase *>(action);

    if(da->selectVisibles() == 0)
        return Action::Skip;
    
    return Action::Continue;
}

Action::ResultE Group::drawLeave(Action *)
{
    return Action::Continue;
}

/*-------------------------------------------------------------------------*/
/*                             Intersect                                   */

Action::ResultE Group::intersect(Action *action)
{
          IntersectAction *ia = dynamic_cast<IntersectAction *>(action);
    const DynamicVolume   &dv = ia->getActNode()->getVolume();
    
    if(dv.isValid() && ! dv.intersect(ia->getLine()))
    {
        return Action::Skip;  //bv missed -> can not hit children
    }
    
    return Action::Continue;
}

/*-------------------------------------------------------------------------*/
/*                                Init                                     */

void Group::initMethod (void)
{
#ifndef OSG_NOFUNCTORS
    DrawAction::registerEnterDefault( 
        getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                  CNodePtr,  
                                  GroupPtr, 
                                  Action *>(&Group::drawEnter));
    DrawAction::registerLeaveDefault( 
        getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                  CNodePtr,  
                                  GroupPtr, 
                                  Action *>(&Group::drawLeave));

    RenderAction::registerEnterDefault( 
        getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                  CNodePtr,  
                                  GroupPtr, 
                                  Action *>(&Group::drawEnter));
    RenderAction::registerLeaveDefault( 
        getClassType(), 
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                  CNodePtr,  
                                  GroupPtr, 
                                  Action *>(&Group::drawLeave));
    
    IntersectAction::registerEnterDefault( 
        getClassType(),
        osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
                                  CNodePtr,
                                  GroupPtr,
                                  Action *>(&Group::intersect));
#else

    DrawAction::registerEnterDefault(
        getClassType(), 
        Action::osgFunctionFunctor2(Group::GroupDrawEnter));

    DrawAction::registerLeaveDefault(
        getClassType(), 
        Action::osgFunctionFunctor2(Group::GroupDrawLeave));

    RenderAction::registerEnterDefault(
        getClassType(), 
        Action::osgFunctionFunctor2(Group::GroupDrawEnter));

    RenderAction::registerLeaveDefault(
        getClassType(), 
        Action::osgFunctionFunctor2(Group::GroupDrawLeave));

    IntersectAction::registerEnterDefault(
        getClassType(),
        Action::osgFunctionFunctor2(Group::GroupIntEnter));

#endif
}







