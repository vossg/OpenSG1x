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

#ifndef _OSGDEPTHFIRSTACTION_H_
#define _OSGDEPTHFIRSTACTION_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGSystemDef.h>
#include "OSGNewAction.h"

#include <deque>

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING DepthFirstAction : public NewAction
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name    Create                                                    */
    /*! \{                                                                 */

    static  DepthFirstAction *create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Destructor                                                */
    /*! \{                                                                 */

    virtual ~DepthFirstAction(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Apply                                                     */
    /*! \{                                                                 */

    virtual ResultE apply(const NodePtr         &pRootNode,
                                PriorityType     priority );
    virtual ResultE apply(      NodeListConstIt  begin,
                                NodeListConstIt  end      );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name    Constructors                                              */
    /*! \{                                                                 */

    DepthFirstAction(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Events                                                    */
    /*! \{                                                                 */

    virtual void attachEvent(ActorBase *pActor, UInt32 uiActorId);
    virtual void detachEvent(ActorBase *pActor, UInt32 uiActorId);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    /*---------------------------------------------------------------------*/
    /*! \name    Types                                                     */
    /*! \{                                                                 */

    typedef NewAction                       Inherited;

    typedef std::vector<ActorBase *>        ActorApplyStore;
    typedef ActorApplyStore::iterator       ActorApplyStoreIt;
    typedef ActorApplyStore::const_iterator ActorApplyStoreConstIt;

    class NodeStackEntry
    {
      public:
        inline NodeStackEntry(const NodePtr &pNode                 );
        inline NodeStackEntry(const NodePtr &pNode, bool bEnterNode);

        inline NodePtr getNode     (      void           ) const;
        inline void    setNode     (const NodePtr &pNode );

        inline bool    getEnterNode(      void           ) const;
        inline void    setEnterNode(      bool bEnterNode);

      private:
        NodePtr _pNode;
        bool    _bEnterNode;
    };

    typedef std::deque<NodeStackEntry> NodeStack;

    /*!\brief prohibit default function (move to 'public' of needed) */
    DepthFirstAction(const DepthFirstAction &source);
    /*!\brief prohibit default function (move to 'public' of needed) */
    void operator =(const DepthFirstAction &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Helper Methods                                            */
    /*! \{                                                                 */

           ResultE applyEnter     (void                                );
           ResultE applyEnterLeave(void                                );

    inline ResultE callEnter      (const NodePtr &pNode                );
    inline ResultE callLeave      (const NodePtr &pNode                );

    inline void    pushChildren   (const NodePtr &pNode, ResultE result);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    NodeStack       _nodeStack;
    ActorApplyStore _actorsEnter;
    ActorApplyStore _actorsLeave;
};

OSG_END_NAMESPACE

#include "OSGDepthFirstAction.inl"

#define OSGDEPTHFIRSTACTION_HEADER_CVSID "@(#)$Id: OSGDepthFirstAction.h,v 1.1 2004/04/20 13:47:08 neumannc Exp $"

#endif /* _OSGDEPTHFIRSTACTION_H_ */
