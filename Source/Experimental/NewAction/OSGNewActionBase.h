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

#ifndef _OSGNEWACTIONBASE_H_
#define _OSGNEWACTIONBASE_H_
#ifdef __sgi
#pragma once
#endif

//----------------------------------------------------------------------------
//    Includes
//----------------------------------------------------------------------------

#include <OSGConfig.h>
#include <OSGSystemDef.h>
#include <OSGStatCollector.h>
#include <OSGStatElemTypes.h>

#include "OSGChildrenList.h"
#include "OSGExtraChildrenList.h"

OSG_BEGIN_NAMESPACE

class ActorBase;
class ExtendActorBase;
class BasicActorBase;

class OSG_SYSTEMLIB_DLLMAPPING NewActionBase
{
    /*==== PUBLIC ===========================================================*/
  public:
    /*-----------------------------------------------------------------------*/
    /*! \name    Types                                                       */
    /*! \{                                                                   */

    typedef NewActionTypes::ResultE             ResultE;
    typedef NewActionTypes::PriorityType        PriorityType;
    typedef NewActionTypes::PriorityTypeTraits  PriorityTypeTraits;
    typedef NewActionTypes::Functor             Functor;
    typedef NewActionTypes::FunctorArgumentType FunctorArgumentType;

#ifdef OSG_NEWACTION_STATISTICS
    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Statistics                                                  */
    /*! \{                                                                   */

    static StatElemDesc<StatIntElem> statNodesEnter;
    static StatElemDesc<StatIntElem> statNodesLeave;

    inline const StatCollector *getStatistics(void                      ) const;
    inline       StatCollector *getStatistics(void                      );
    inline       void           setStatistics(StatCollector *pStatistics);

#endif /* OSG_NEWACTION_STATISTICS */

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Destructor                                                  */
    /*! \{                                                                   */

    virtual ~NewActionBase(void);

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Apply                                                       */
    /*! \{                                                                   */

    virtual ResultE apply(NodePtr pRoot) = 0;

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Generic Actor Management                                    */
    /*! \{                                                                   */

    UInt32 addActor          (ActorBase       *pActor );
    void   subActor          (ActorBase       *pActor );
    UInt32 findActor         (ActorBase       *pActor ) const;
    UInt32 getNumActors      (void                    ) const;

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Extend Actor Management                                     */
    /*! \{                                                                   */

    UInt32 addExtendActor    (ExtendActorBase *pActor );
    UInt32 addExtendActor    (ExtendActorBase *pActor,
                              UInt32            pos   );
    void   subExtendActor    (UInt32            pos   );
    UInt32 findExtendActor   (ExtendActorBase *pActor ) const;
    UInt32 getNumExtendActors(void                    ) const;

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Basic Actor Management                                      */
    /*! \{                                                                   */

    UInt32 addBasicActor     (BasicActorBase  *pActor );
    UInt32 addBasicActor     (BasicActorBase  *pActor,
                              UInt32           pos    );
    void   subBasicActor     (UInt32           pos    );
    UInt32 findBasicActor    (BasicActorBase  *pActor ) const;
    UInt32 getNumBasicActors (void                    ) const;

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Traversal Mask                                              */
    /*! \{                                                                   */

    inline UInt32 getTravMask (void           ) const;
    inline void   setTravMask (UInt32 travMask);

    /*! \}                                                                   */
    /*==== PROTECTED ========================================================*/
  protected:
    /*-----------------------------------------------------------------------*/
    /*! \name    Types                                                       */
    /*! \{                                                                   */

    typedef std::vector<ExtendActorBase *>   ExtendActorStore;
    typedef ExtendActorStore::iterator       ExtendActorStoreIt;
    typedef ExtendActorStore::const_iterator ExtendActorStoreConstIt;

    typedef std::vector<BasicActorBase  *>   BasicActorStore;
    typedef BasicActorStore::iterator        BasicActorStoreIt;
    typedef BasicActorStore::const_iterator  BasicActorStoreConstIt;

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Friends                                                     */
    /*! \{                                                                   */

    friend class OSG::ActorBase;
    friend class OSG::ExtendActorBase;
    friend class OSG::BasicActorBase;

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Constructor                                                 */
    /*! \{                                                                   */

    NewActionBase(void);

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Events                                                      */
    /*! \{                                                                   */

    virtual void addExtendEvent    (ExtendActorBase   *pActor,
                                    UInt32             actorIndex) = 0;
    virtual void subExtendEvent    (ExtendActorBase   *pActor,
                                    UInt32             actorIndex) = 0;

    virtual void addBasicEvent     (BasicActorBase    *pActor,
                                    UInt32             actorIndex) = 0;
    virtual void subBasicEvent     (BasicActorBase    *pActor,
                                    UInt32             actorIndex) = 0;

    virtual void startEvent         (void                        );
    virtual void stopEvent          (void                        );

    virtual void beginEditStateEvent(ActorBase        *pActor,
                                     UInt32            actorId   ) = 0;
    virtual void endEditStateEvent  (ActorBase        *pActor,
                                     UInt32            actorId   ) = 0;

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    ChildrenList/ExtraChildrenList Access                       */
    /*! \{                                                                   */

    inline       bool               getChildrenListEnabled(void        ) const;
    inline       void               setChildrenListEnabled(bool enabled);

    inline const ChildrenList      &getChildrenList       (void        ) const;
    inline       ChildrenList      &getChildrenList       (void        );

    inline const ExtraChildrenList &getExtraChildrenList  (void        ) const;
    inline       ExtraChildrenList &getExtraChildrenList  (void        );

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    MultiPass Setup                                             */
    /*! \{                                                                   */

    inline UInt32 getNumPasses(void            ) const;
    inline void   setNumPasses(UInt32 numPasses);

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Actor Access                                                */
    /*! \{                                                                   */

    inline ExtendActorStoreConstIt beginExtend(void) const;
    inline ExtendActorStoreIt      beginExtend(void);
    inline ExtendActorStoreConstIt endExtend  (void) const;
    inline ExtendActorStoreIt      endExtend  (void);

    inline BasicActorStoreConstIt  beginBasic (void) const;
    inline BasicActorStoreIt       beginBasic (void);
    inline BasicActorStoreConstIt  endBasic   (void) const;
    inline BasicActorStoreIt       endBasic   (void);

           ResultE                 startActors(void);
           ResultE                 stopActors (void);

    /*! \}                                                                   */
    /*==== PRIVATE ==========================================================*/
  private:
    ExtendActorStore   _extendActors;
    BasicActorStore    _basicActors;

#ifdef OSG_NEWACTION_STATISTICS
    StatCollector     *_pStatistics;
    bool               _ownStatistics;
#endif /* OSG_NEWACTION_STATISTICS */

    UInt32             _travMask;
    UInt32             _numPasses;

    bool               _childrenListEnabled;
    ChildrenList       _childrenList;

    ExtraChildrenList  _extraChildrenList;
};

OSG_END_NAMESPACE

#include "OSGNewActionBase.inl"

#define OSGNEWACTIONBASE_HEADER_CVSID "@(#)$Id: OSGNewActionBase.h,v 1.5 2004/09/17 14:09:43 neumannc Exp $"

#endif /* _OSGNEWACTIONBASE_H_ */
