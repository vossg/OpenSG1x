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

#ifndef _OSGACTORBASE_H_
#define _OSGACTORBASE_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGSystemDef.h>

#include "OSGNewActionTypes.h"

OSG_BEGIN_NAMESPACE

class NewActionBase;

/*! \brief Actor base class. See \ref PageExperimentalNewActionActorBase
 *  for a description.
 */

class OSG_SYSTEMLIB_DLLMAPPING ActorBase
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

    class OSG_SYSTEMLIB_DLLMAPPING ActorBaseState
    {
      public:
        inline ActorBaseState(void                        );
        inline ActorBaseState(const ActorBaseState &source);

        virtual ~ActorBaseState(void) = 0;
    };

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Destructor                                                  */
    /*! \{                                                                   */

    virtual ~ActorBase(void) = 0;

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Start/Stop                                                  */
    /*! \{                                                                   */

    virtual ResultE start(void) = 0;
    virtual ResultE stop (void) = 0;

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Enter/Leave Callback                                        */
    /*! \{                                                                   */

    virtual ResultE enterNode(FunctorArgumentType &funcArg) = 0;
    virtual ResultE leaveNode(FunctorArgumentType &funcArg) = 0;

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Config                                                      */
    /*! \{                                                                   */

    inline bool getEnterNodeFlag(void) const;
    inline bool getLeaveNodeFlag(void) const;

    inline void setEnterNodeFlag(bool enter);
    inline void setLeaveNodeFlag(bool leave);

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Action Access                                               */
    /*! \{                                                                   */

    inline const NewActionBase *getAction (void) const;
    inline       NewActionBase *getAction (void);

    inline       UInt32         getActorId(void) const;

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Children Management                                         */
    /*! \{                                                                   */

    inline bool getChildrenListEnabled(void) const;
    inline void setChildrenListEnabled(bool enabled);

    inline NodePtr      getNode         (void                    ) const;

    inline UInt32       getNumChildren  (void                    ) const;
    inline NodePtr      getChild        (UInt32       childIndex ) const;

    inline bool         getChildActive  (UInt32       childIndex ) const;
    inline void         setChildActive  (UInt32       childIndex,
                                         bool         active     );

    inline PriorityType getChildPriority(UInt32       childIndex ) const;
    inline void         setChildPriority(UInt32       childIndex,
                                         PriorityType prio       );

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Extra Children Management                                   */
    /*! \{                                                                   */

    inline UInt32       getNumExtraChildren  (void                    ) const;
    inline NodePtr      getExtraChild        (UInt32       childIndex ) const;

    inline bool         getExtraChildActive  (UInt32       childIndex ) const;
    inline void         setExtraChildActive  (UInt32       childIndex,
                                              bool         active     );

    inline PriorityType getExtraChildPriority(UInt32       childIndex ) const;
    inline void         setExtraChildPriority(UInt32       childIndex,
                                              PriorityType prio       );

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Multi Pass Management                                       */
    /*! \{                                                                   */

    inline UInt32 getNumPasses(void) const;

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    State Management                                            */
    /*! \{                                                                   */

#ifdef OSG_NEWACTION_STATESLOTINTERFACE
    virtual UInt32          createStateClone  (void                       ) = 0;
    virtual void            destroyStateClone (UInt32          slotId     ) = 0;
#else
    virtual ActorBaseState *createStateClone  (void                       ) = 0;
    virtual void            destroyStateClone (ActorBaseState *pStateClone) = 0;
#endif

    virtual void            createInitialState(void                       ) = 0;
    virtual void            deleteInitialState(void                       ) = 0;

    inline        void            beginEditState(void                  );
    inline        void            endEditState  (void                  );

    inline  const ActorBaseState *getState      (void                  ) const;
    inline        ActorBaseState *getState      (void                  );

    inline        void            setState      (ActorBaseState *pState);

    /*! \}                                                                   */
    /*==== PROTECTED ========================================================*/
  protected:
    /*-----------------------------------------------------------------------*/
    /*! \name    Types                                                       */
    /*! \{                                                                   */

    typedef ActorBaseState                StateType;

#ifdef OSG_NEWACTION_STATESLOTINTERFACE
    typedef std::vector<ActorBaseState *> StateSlotMap;

    inline const StateSlotMap &getSlotMap(void) const;
    inline       StateSlotMap &getSlotMap(void);
#endif

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Friends                                                     */
    /*! \{                                                                   */

    friend class OSG::NewActionBase;

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Constructor                                                 */
    /*! \{                                                                   */

    ActorBase(void);

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Add, Sub and Find Helper                                    */
    /*! \{                                                                   */

    virtual UInt32 addHelper (      NewActionBase *pAction) = 0;
    virtual void   subHelper (      NewActionBase *pAction) = 0;
    virtual UInt32 findHelper(const NewActionBase *pAction) = 0;

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Event Notification                                          */
    /*! \{                                                                   */

    virtual void addEvent(NewActionBase *pAction, UInt32 actorId);
    virtual void subEvent(NewActionBase *pAction, UInt32 actorId);

    /*! \}                                                                   */
    /*==== PRIVATE ==========================================================*/
  private:
    NewActionBase  *_pAction;
    UInt32          _actorId;

    bool            _enterNodeFlag;
    bool            _leaveNodeFlag;

#ifdef OSG_NEWACTION_STATESLOTINTERFACE
    StateSlotMap    _stateSlotMap;
#endif

    ActorBaseState *_pState;
};

OSG_END_NAMESPACE

#include "OSGActorBase.inl"

#define OSGACTORBASE_HEADER_CVSID "@(#)$Id: OSGActorBase.h,v 1.8 2005/03/31 19:50:56 dirk Exp $"

#endif /* _OSGACTORBASE_H_ */
