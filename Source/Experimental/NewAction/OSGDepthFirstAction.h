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

//----------------------------------------------------------------------------
//    Includes
//----------------------------------------------------------------------------

#include <OSGConfig.h>
#include <OSGSystemDef.h>

#include "OSGNewActionBase.h"

#include <deque>

OSG_BEGIN_NAMESPACE

class ExtendActorBase;
class BasicActorBase;

class OSG_SYSTEMLIB_DLLMAPPING DepthFirstAction : public NewActionBase
{
    /*==== PUBLIC ===========================================================*/
  public:
    /*-----------------------------------------------------------------------*/
    /*! \name    Destructor                                                  */
    /*! \{                                                                   */

    virtual ~DepthFirstAction(void);

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Create                                                      */
    /*! \{                                                                   */

    static DepthFirstAction *create(void);

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Apply                                                       */
    /*! \{                                                                   */

    virtual ResultE apply(NodePtr pRoot);

    /*! \}                                                                   */
    /*==== PROTECTED ========================================================*/
  protected:
    /*-----------------------------------------------------------------------*/
    /*! \name    Constructors                                                */
    /*! \{                                                                   */

    DepthFirstAction(void);

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Events                                                      */
    /*! \{                                                                   */

    virtual void addExtendEvent     (ExtendActorBase *pActor,
                                     UInt32           actorIndex);
    virtual void subExtendEvent     (ExtendActorBase *pActor,
                                     UInt32           actorIndex);

    virtual void addBasicEvent      (BasicActorBase  *pActor,
                                     UInt32           actorIndex);
    virtual void subBasicEvent      (BasicActorBase  *pActor,
                                     UInt32           actorIndex);

    virtual void beginEditStateEvent(ActorBase       *pActor,
                                     UInt32           actorId   );
    virtual void endEditStateEvent  (ActorBase       *pActor,
                                     UInt32           actorId   );

    /*! \}                                                                   */
    /*==== PRIVATE ==========================================================*/
  private:
    /*-----------------------------------------------------------------------*/
    /*! \name    Types                                                       */
    /*! \{                                                                   */

    typedef NewActionBase Inherited;

    class NodeStackEntry
    {
      public:
        inline NodeStackEntry(      void                                  );
        inline NodeStackEntry(const NodeStackEntry &source                );
        inline NodeStackEntry(const NodePtr        &pNode, Int32 passCount);

        inline NodePtr getNode     (      void              ) const;
        inline void    setNode     (const NodePtr &pNode    );

        inline Int32   getPassCount(      void              ) const;
        inline void    setPassCount(      Int32    passCount);

      private:
        NodePtr _pNode;
        Int32   _passCount;
    };

    typedef std::deque<NodeStackEntry> NodeStack;

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Helper Methods                                              */
    /*! \{                                                                   */

           ResultE traverseEnter     (      void                          );
           ResultE traverseEnterLeave(      void                          );

           void    pushChildren      (const NodePtr &pNode, ResultE result);

    inline ResultE enterNode         (const NodePtr &pNode, UInt32  pass  );
    inline ResultE leaveNode         (const NodePtr &pNode, UInt32  pass  );

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/

    NodeStack        _nodeStack;

    ExtendActorStore _extendEnterActors;
    ExtendActorStore _extendLeaveActors;

    BasicActorStore  _basicEnterActors;
    BasicActorStore  _basicLeaveActors;
};

OSG_END_NAMESPACE

#include "OSGDepthFirstAction.inl"

#define OSGDEPTHFIRSTACTION_HEADER_CVSID "@(#)$Id: OSGDepthFirstAction.h,v 1.3 2004/09/17 14:09:42 neumannc Exp $"

#endif /* _OSGDEPTHFIRSTACTION_H_ */
