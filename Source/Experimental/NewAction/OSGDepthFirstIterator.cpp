/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     * 
 *                                                                           * 
 *                                                                           * 
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                * 
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

#include <OSGConfig.h>
#include "OSGDepthFirstIterator.h"

#include <OSGLog.h>

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

DepthFirstIterator *
DepthFirstIterator::create(void)
{
    return new DepthFirstIterator();
}

DepthFirstIterator::~DepthFirstIterator(void)
{
}

DepthFirstIterator::ResultE
DepthFirstIterator::start(void)
{
    RootListIt iterRoots = getRoots().begin();
    RootListIt endRoots  = getRoots().end  ();

    _result              = NewActionBase::Continue;

    for(; (iterRoots != endRoots) && (_result == NewActionBase::Continue); 
        ++iterRoots)
    {
        startActors();

        _result = ResultE(_result | (this->*_traverseFunc)(*iterRoots));

        if((_result & NewActionBase::Abort) == 0)
        {
            stopActors();
        }
    }

    return _result;
}


void
DepthFirstIterator::stop(void)
{
    _result = NewActionBase::Stop;
}

void
DepthFirstIterator::receiveActorAdd(ActorBase *pActor, UInt32 uiActorId)
{
    Inherited::receiveActorAdd(pActor, uiActorId);

    if(getNumLeaveActors() > 0)
    {
        _traverseFunc = &DepthFirstIterator::traverseEnterLeave;
    }
    else
    {
        _traverseFunc = &DepthFirstIterator::traverseEnter;
    }
}

void
DepthFirstIterator::receiveActorSub(ActorBase *pActor, UInt32 uiActorId)
{
    Inherited::receiveActorSub(pActor, uiActorId);

    if(getNumLeaveActors() > 0)
    {
        _traverseFunc = &DepthFirstIterator::traverseEnterLeave;
    }
    else
    {
        _traverseFunc = &DepthFirstIterator::traverseEnter;
    }
}

void
DepthFirstIterator::receiveActorsClear(void)
{
    Inherited::receiveActorsClear();
}

void
DepthFirstIterator::receiveStateRead(UInt32)
{
}

void
DepthFirstIterator::receiveStateWrite(UInt32)
{
}

DepthFirstIterator::ResultE
DepthFirstIterator::traverseEnter(NodePtr &pRoot)
{  
    _stack.push_back(StackEntry(pRoot, false));

    while(!_stack.empty())
    {
        resetNodeList();

        _result = ResultE(_result | callEnter(_stack.back().getNode()));

        if(_result != NewActionBase::Continue)
            break;

        _stack.pop_back();

        pushChildren();
    }
        
    return _result;
}

DepthFirstIterator::ResultE
DepthFirstIterator::traverseEnterLeave(NodePtr &pRoot)
{
    _stack.push_back(StackEntry(pRoot, false));

    while(!_stack.empty())
    {
        resetNodeList();

        if(_stack.back().getLeave() == false)
        {
            _result = ResultE(_result | callEnter(_stack.back().getNode()));
            
            if(_result != NewActionBase::Continue)
                break;

            _stack.back().setLeave();

            pushChildren();
        }
        else
        {
            _result = ResultE(_result | callLeave(_stack.back().getNode()));

            if(_result != NewActionBase::Continue)
                break;

            _stack.pop_back();
        }
    }

    return _result;
}

void
DepthFirstIterator::pushChildren(void)
{
    if(getUseNodeList() == true)
    {
        ActiveNodeListIt iterNodes = beginNodes();
        ActiveNodeListIt end       = endNodes  ();

        for(; iterNodes != end; ++iterNodes)
        {
            _stack.push_back(StackEntry(iterNodes.getNode(), false));
        }
    }
    else
    {
        MFNodePtr::iterator iterNodes = 
            getCurrentNode()->getMFChildren()->begin();
        MFNodePtr::iterator end       = 
            getCurrentNode()->getMFChildren()->end  ();

        for(; iterNodes != end; ++iterNodes)
        {
            _stack.push_back(StackEntry(*iterNodes, false));
        }
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


DepthFirstIterator::DepthFirstIterator(void)
    : Inherited    (                                       ),
      _result      (NewActionBase::Continue                ),
      _stack       (                                       ),
      _traverseFunc(&DepthFirstIterator::traverseEnterLeave)
{
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: $";
    static Char8 cvsid_hpp       [] = OSGDEPTHFIRSTITERATOR_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDEPTHFIRSTITERATOR_INLINE_CVSID;
}
