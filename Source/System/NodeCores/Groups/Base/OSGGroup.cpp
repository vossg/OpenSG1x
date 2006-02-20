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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <OSGDrawAction.h>
#include <OSGRenderAction.h>
#include <OSGIntersectAction.h>

#include "OSGGroup.h"

OSG_USING_NAMESPACE

/*! \class osg::Group

  Group is the simplest form of a NodeCore. A group
  carries no predefined data and most actions will only traverse the
  children list. So usually the group does nothing.

*/

/*-------------------------------------------------------------------------*/
/*                               Sync                                      */

void Group::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void Group::dump(      UInt32    uiIndent, 
                 const BitVector bvFlags) const
{
   Inherited::dump(uiIndent, bvFlags);
}

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
/*                              Render                                     */

Action::ResultE Group::renderEnter(Action *action)
{
    RenderAction *ra = dynamic_cast<RenderAction *>(action);

    if (ra->pushVisibility())
    {
        if(ra->selectVisibles() == 0)
        {
            ra->popVisibility();
            return Action::Skip;
        }
    }

    return Action::Continue;
}

Action::ResultE Group::renderLeave(Action *action)
{
    RenderAction *ra = dynamic_cast<RenderAction *>(action);

    ra->popVisibility();
    
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
    DrawAction::registerEnterDefault( 
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          GroupPtr  , 
                                          CNodePtr  ,  
                                          Action   *>(&Group::drawEnter));
    DrawAction::registerLeaveDefault( 
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          GroupPtr  , 
                                          CNodePtr  ,  
                                          Action   *>(&Group::drawLeave));

    RenderAction::registerEnterDefault( 
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          GroupPtr  , 
                                          CNodePtr  ,  
                                          Action   *>(&Group::renderEnter));

    RenderAction::registerLeaveDefault( 
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          GroupPtr  , 
                                          CNodePtr  ,  
                                          Action   *>(&Group::renderLeave));
    
    IntersectAction::registerEnterDefault( 
        getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          GroupPtr  ,
                                          CNodePtr  ,
                                          Action   *>(&Group::intersect));
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGGROUP_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGGROUP_INLINE_CVSID;
}





