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

#include <OSGConfig.h>

#include "OSGSwitch.h"

#include <OSGDrawAction.h>
#include <OSGRenderAction.h>
#include <OSGIntersectAction.h>

OSG_USING_NAMESPACE

/*! \class osg::Switch
*/

/*-------------------------------------------------------------------------*/
/*                                Sync                                     */

void Switch::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void Switch::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                  const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump Switch NI" << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

Switch::Switch(void) :
    Inherited()
{
}

Switch::Switch(const Switch &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

Switch::~Switch(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Draw                                      */

Action::ResultE Switch::draw(Action *action)
{
    Action::ResultE  returnValue = Action::Continue;

    DrawActionBase  *da          = dynamic_cast<DrawActionBase *>(action);

    if((getChoice() >= 0                          ) && 
       (UInt32(getChoice()) < action->getNNodes()))
    {
        da->useNodeList();

        if(da->isVisible(action->getNode(getChoice()).getCPtr()))
        {
            da->addNode(action->getNode(getChoice()));
        }
    }
    else if(getChoice() == ALL)
    {
        if(da->selectVisibles() == 0)
            returnValue = Action::Skip;
    }
    else
    {
        returnValue = Action::Skip;
    }

    return returnValue;
}

Action::ResultE Switch::intersect(Action *action)
{
    Action::ResultE  returnValue = Action::Continue;

    IntersectAction  *da          = dynamic_cast<IntersectAction *>(action);

    if((getChoice() >= 0                          ) && 
       (UInt32(getChoice()) < action->getNNodes()))
    {
        da->addNode(action->getNode(getChoice()));
    }
    else if(getChoice() == ALL)
    {
        returnValue = Action::Continue;
    }
    else
    {
        returnValue = Action::Skip;
    }

    return returnValue;
}
 
/*-------------------------------------------------------------------------*/
/*                                Init                                     */

void Switch::initMethod(void)
{
    DrawAction::registerEnterDefault(
        getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          SwitchPtr       ,
                                          CNodePtr        ,
                                          Action         *>(&Switch::draw));

    RenderAction::registerEnterDefault(
        getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          SwitchPtr       ,
                                          CNodePtr        ,
                                          Action         *>(&Switch::draw));

    IntersectAction::registerEnterDefault(
        getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                          SwitchPtr       ,
                                          CNodePtr        ,
                                          Action         *>(&Switch::intersect));
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
    static Char8 cvsid_hpp[] = OSGSWITCH_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGSWITCH_INLINE_CVSID;
}
