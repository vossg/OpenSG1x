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

#ifndef _OSGNEWACTION_H_
#define _OSGNEWACTION_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include "OSGNewActionTypes.h"
#include "OSGActiveChildrenList.h"

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING NewAction
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name    Types                                                     */
    /*! \{                                                                 */

    typedef NewActionTypes::ResultE         ResultE;
    typedef NewActionTypes::PriorityType    PriorityType;

    typedef NewActionTypes::NodeList        NodeList;
    typedef NewActionTypes::NodeListIt      NodeListIt;
    typedef NewActionTypes::NodeListConstIt NodeListConstIt;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Destructor                                                */
    /*! \{                                                                 */

    virtual ~NewAction(void) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Actor Handling                                            */
    /*! \{                                                                 */

    UInt32     attachActor (ActorBase *pActor                );
    UInt32     attachActor (ActorBase *pActor, UInt32 uiIndex);

    ActorBase *detachActor (UInt32     uiIndex               );
    ActorBase *detachActor (ActorBase *pActor                );

    inline UInt32     findActor   (ActorBase *pActor    ) const;
    inline ActorBase *getActor    (UInt32     uiIndex   ) const;

    inline UInt32     getNumActors(void                 ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Apply                                                     */
    /*! \{                                                                 */

            ResultE apply(const NodePtr         &pRootNode );
    virtual ResultE apply(const NodePtr         &pRootNode,
                                PriorityType     priority  ) = 0;
    virtual ResultE apply(      NodeListConstIt  begin,
                                NodeListConstIt  end       ) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Root Nodes                                                */
    /*! \{                                                                 */

    inline NodeListConstIt beginRootNodes(void) const;
    inline NodeListIt      beginRootNodes(void);

    inline NodeListConstIt endRootNodes  (void) const;
    inline NodeListIt      endRootNodes  (void);

    inline const NodeList &getRootNodes  (void) const;
    inline       NodeList &getRootNodes  (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Traversal Mask                                            */
    /*! \{                                                                 */

    inline UInt32   getTravMask (void                 ) const;
    inline void     setTravMask (UInt32     uiTravMask);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Active Children                                           */
    /*! \{                                                                 */

    inline const ActiveChildrenList *getActiveChildrenList(void) const;
    inline       ActiveChildrenList *getActiveChildrenList(void);

    inline bool getUseActiveChildrenList(void                       ) const;
    inline void setUseActiveChildrenList(bool bUseActiveChildrenList);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*---------------------------------------------------------------------*/
    /*! \name    Friends                                                   */
    /*! \{                                                                 */

    friend class OSG::ActorBase;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Types                                                     */
    /*! \{                                                                 */

    class ActorData
    {
      public:
        inline ActorData(ActorBase *pActor,
                         UInt32     uiActorId,
                         UInt32     uiStateSize);

        inline ActorBase *getActor    (void                  ) const;
        inline void       setActor    (ActorBase *pActor     );

        inline UInt32     getActorId  (void                  ) const;
        inline void       setActorId  (UInt32     uiActorId  );

        inline UInt32     getStateSize(void                  ) const;
        inline void       setStateSize(UInt32     uiStateSize);

      private:
        ActorBase *_pActor;
        UInt32     _uiActorId;
        UInt32     _uiStateSize;
    };

    typedef std::vector<ActorData>     ActorStore;
    typedef ActorStore::iterator       ActorStoreIt;
    typedef ActorStore::const_iterator ActorStoreConstIt;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Constructors                                              */
    /*! \{                                                                 */

    NewAction(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Events                                                    */
    /*! \{                                                                 */

    virtual void attachEvent        (ActorBase *pActor, UInt32 uiActorId);
    virtual void detachEvent        (ActorBase *pActor, UInt32 uiActorId);

    virtual void beginEditStateEvent(ActorBase *pActor, UInt32 uiActorId);
    virtual void endEditStateEvent  (ActorBase *pActor, UInt32 uiActorId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Actor Storage Access                                      */
    /*! \{                                                                 */

    inline ActorStoreConstIt beginActors(void) const;
    inline ActorStoreIt      beginActors(void);

    inline ActorStoreConstIt endActors  (void) const;
    inline ActorStoreIt      endActors  (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Helper Methods                                            */
    /*! \{                                                                 */

    ResultE startActors(void);
    ResultE stopActors (void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    /*!\brief prohibit default function (move to 'public' of needed) */
    NewAction      (const NewAction &source);
    /*!\brief prohibit default function (move to 'public' of needed) */
    void operator =(const NewAction &source);

    ActorStore         _actors;
    UInt32             _uiTravMask;

    NodeList           _rootNodes;

    bool               _bUseActiveChildrenList;
    ActiveChildrenList _activeChildrenList;
};

OSG_END_NAMESPACE

#include "OSGNewAction.inl"

#define OSGNEWACTION_HEADER_CVSID "@(#)$Id: OSGNewAction.h,v 1.4 2004/04/20 13:47:08 neumannc Exp $"

#endif /* _OSGNEWACTION_H_ */

