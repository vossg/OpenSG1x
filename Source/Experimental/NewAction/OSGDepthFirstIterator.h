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

#ifndef _OSGDEPTHFIRSTITERATOR_H_
#define _OSGDEPTHFIRSTITERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGStateUnawareIterator.h"
#include "OSGActiveNodeList.h"

#include <deque>

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING DepthFirstIterator : public StateUnawareIterator
{
public:
    typedef NewActionBase::PriorityType PriorityType;
    typedef NewActionBase::ResultE      ResultE;

    static   DepthFirstIterator *create(void);

    virtual ~DepthFirstIterator        (void); 
    
    /*---------------------------------------------------------------------*/
    /*! \name                     Traverse                                 */
    /*! \{                                                                 */

    virtual ResultE  start             (      void               );
    virtual void     stop              (      void               );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Receive Signals                          */
    /*! \{                                                                 */

    virtual void receiveActorAdd   (ActorBase *pActor,   UInt32 uiActorId);
    virtual void receiveActorSub   (ActorBase *pActor,   UInt32 uiActorId);
    virtual void receiveActorsClear(void                                 );

    virtual void receiveStateRead  (UInt32     uiActorId                 );
    virtual void receiveStateWrite (UInt32     uiActorId                 );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

private:
    typedef StateUnawareIterator Inherited;

    class StackEntry
    {
    public:
        inline StackEntry(const NodePtr &pNode, bool bLeave = false);

        inline NodePtr getNode (void              ) const;

        inline bool    getLeave(void              ) const;
        inline void    setLeave(bool bLeave = true);

    private:
        NodePtr _pNode;
        bool    _bLeave;
    };

    typedef std::deque<StackEntry> NodeStack;
    typedef ResultE (DepthFirstIterator::*TraverseFuncP)(NodePtr &);

    DepthFirstIterator(void);

    ResultE traverseEnter     (NodePtr &pNode);
    ResultE traverseEnterLeave(NodePtr &pNode);

    void    pushChildren      (void          );
    
    ResultE       _result;
    NodeStack     _stack;
    TraverseFuncP _traverseFunc;
};

OSG_END_NAMESPACE

#include "OSGDepthFirstIterator.inl"

#define OSGDEPTHFIRSTITERATOR_HEADER_CVSID "@(#)$Id: OSGDepthFirstIterator.h,v 1.1 2003/10/10 13:51:06 neumannc Exp $"

#endif /* _OSGDEPTHFIRSTITERATOR_H_ */
