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

#include <OSGGL.h>

#include <OSGDrawAction.h>
#include <OSGRenderAction.h>
#include "OSGStateSortingGroup.h"

OSG_USING_NAMESPACE


/*-------------------------------------------------------------------------*/
/*                             Sync                                     */

void StateSortingGroup::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}


/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void StateSortingGroup::dump(      UInt32    uiIndent, 
                     const BitVector bvFlags) const
{
   Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

StateSortingGroup::StateSortingGroup(void) :
     Inherited(),
    _sorting_state(false)
{
}

StateSortingGroup::StateSortingGroup(const StateSortingGroup &source) :
     Inherited(source),
    _sorting_state(source._sorting_state)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

StateSortingGroup::~StateSortingGroup(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Drawing                                   */
    
Action::ResultE StateSortingGroup::drawEnter(Action *OSG_CHECK_ARG(action))
{
    return Action::Continue;
}
    
Action::ResultE StateSortingGroup::drawLeave(Action *OSG_CHECK_ARG(action))
{
    return Action::Continue;
}

/*-------------------------------------------------------------------------*/
/*                             Rendering                                   */

Action::ResultE StateSortingGroup::renderEnter(Action *action)
{
    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    _sorting_state = pAction->getStateSorting();
    pAction->setStateSorting(getSorting());

    return Action::Continue;
}

Action::ResultE StateSortingGroup::renderLeave(Action *action)
{
    RenderAction *pAction = dynamic_cast<RenderAction *>(action);

    pAction->setStateSorting(_sorting_state);

    return Action::Continue;
}

/*-------------------------------------------------------------------------*/
/*                               Init                                      */

//! initialize the static features of the class, e.g. action callbacks

void StateSortingGroup::initMethod(void)
{
    DrawAction::registerEnterDefault( 
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            StateSortingGroupPtr  , 
            CNodePtr          ,  
            Action           *>(&StateSortingGroup::drawEnter));

    DrawAction::registerLeaveDefault( 
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            StateSortingGroupPtr  , 
            CNodePtr          ,  
            Action           *>(&StateSortingGroup::drawLeave));

    RenderAction::registerEnterDefault(
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            StateSortingGroupPtr  , 
            CNodePtr          ,  
            Action           *>(&StateSortingGroup::renderEnter));

    RenderAction::registerLeaveDefault(
        getClassType(), 
        osgTypedMethodFunctor2BaseCPtrRef<
            Action::ResultE,
            StateSortingGroupPtr  , 
            CNodePtr          ,  
            Action           *>(&StateSortingGroup::renderLeave));
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
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGStateSortingGroup.cpp,v 1.1 2005/04/06 09:35:00 a-m-z Exp $";
    static Char8 cvsid_hpp[] = OSGSTATESORTINGGROUP_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGSTATESORTINGGROUP_INLINE_CVSID;
}
