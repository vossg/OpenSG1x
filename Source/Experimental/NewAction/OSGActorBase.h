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
#include <OSGBaseTypes.h>
#include "OSGNewActionTypes.h"

OSG_BEGIN_NAMESPACE

class NewAction;

/*! \class Abstract Actor base class. See \ref PageSystemNewActionActorBase
    for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING ActorBase
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name    Types                                                     */
    /*! \{                                                                 */

    typedef NewActionTypes::ResultE ResultE;
    typedef NewActionTypes::Functor Functor;

    class ActorBaseState
    {
      public:
        inline   ActorBaseState(void                        );
        inline   ActorBaseState(const ActorBaseState &source);

        virtual ~ActorBaseState(void                        ) = 0;

        virtual ActorBaseState *clone(MemoryHandle pMemHandle) const;

        virtual bool            empty(void                   ) const;
        virtual UInt32          size (void                   ) const;
    };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Destructor                                                */
    /*! \{                                                                 */

    virtual ~ActorBase(void) = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Start/Stop                                                */
    /*! \{                                                                 */

    virtual ResultE start(void);
    virtual ResultE stop (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Apply                                                     */
    /*! \{                                                                 */

    virtual ResultE applyEnter(const NodePtr &pNode );
    virtual ResultE applyLeave(const NodePtr &pNode );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Memeber Access                                            */
    /*! \{                                                                 */

    inline const NewAction *getAction    (void            ) const;
    inline       NewAction *getAction    (void            );

    inline       UInt32     getActorId   (void            ) const;

    inline       bool       getApplyEnter(void            ) const;
    inline       bool       getApplyLeave(void            ) const;

    inline       void       setApplyEnter(bool bApplyEnter);
    inline       void       setApplyLeave(bool bApplyLeave);

    inline       NodePtr    getCurrNode  (void            ) const;
    inline       NodePtr    getCurrNode  (void            );

    /*! \}                                                                  */
    /*----------------------------------------------------------------------*/
    /*! \name    State Access                                               */
    /*! \{                                                                  */

    inline       void            beginEditState(void                   );
    inline       void            endEditState  (void                   );

    inline const ActorBaseState *getStatePtr (void                     ) const;
    inline       ActorBaseState *getStatePtr (void                     );

    inline       void            setStatePtr (ActorBaseState *pStatePtr);

    inline       UInt32          getStateSize(void                     ) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    /*----------------------------------------------------------------------*/
    /*! \name    Friends / Types                                            */
    /*! \{                                                                  */

    friend class OSG::NewAction;

    typedef ActorBaseState StateType;

    /*! \}                                                                  */
    /*----------------------------------------------------------------------*/
    /*! \name    Constructor                                                */
    /*! \{                                                                  */

    ActorBase(void);

    /*! \}                                                                  */
    /*----------------------------------------------------------------------*/
    /*! \name    Events                                                     */
    /*! \{                                                                  */

    virtual void attachEvent(NewAction *pAction, UInt32 uiActorId);
    virtual void detachEvent(NewAction *pAction, UInt32 uiActorId);

    /*! \}                                                                  */
    /*----------------------------------------------------------------------*/
    /*! \name    State Create / Delete                                      */
    /*! \{                                                                  */

    virtual void createState  (void) = 0;
    virtual void deleteState  (void) = 0;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    /*!\brief prohibit default function (move to 'public' of needed) */
    ActorBase      (const ActorBase &source);
    /*!\brief prohibit default function (move to 'public' of needed) */
    void operator =(const ActorBase &source);

    NewAction      *_pAction;
    UInt32          _uiActorId;

    bool            _bApplyEnter;
    bool            _bApplyLeave;

    ActorBaseState *_pStatePtr;
};

OSG_END_NAMESPACE

#include "OSGActorBase.inl"

#define OSGACTORBASE_HEADER_CVSID "@(#)$Id: OSGActorBase.h,v 1.3 2004/04/20 13:47:08 neumannc Exp $"

#endif /*_OSGACTORBASE_H_ */

