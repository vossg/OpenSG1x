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

#ifndef _OSGACTORBASE_H_
#define _OSGACTORBASE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGNewActionBase.h"
#include "OSGNewAction.h"
#include "OSGActiveNodeList.h"

#include <OSGBaseTypes.h>
#include <OSGNodePtr.h>

OSG_BEGIN_NAMESPACE

/* \brief ActorBase class.
          Provides common functionality for all actors.
*/

class OSG_SYSTEMLIB_DLLMAPPING ActorBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /* \brief ActorStateBase class.
              All actor state classes are derived from this.
    */
    class ActorStateBase
    {
        /*======================  PUBLIC  =================================*/
      public:
        /*-----------------------------------------------------------------*/
        /*! \name                Constructors                              */
        /*! \{                                                             */

                 ActorStateBase(      void                  );
                 ActorStateBase(const ActorStateBase &source);
        
        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
        /*! \name                    Destructor                            */
        /*! \{                                                             */

        virtual ~ActorStateBase(      void                  );

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
        /*! \name                     Clone                                */
        /*! \{                                                             */

        virtual ActorStateBase *clone(void);

        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
        /*! \name                     Empty                                */
        /*! \{                                                             */

        enum
        {
            bHasStateElems = 0
        };
        
        /*! \}                                                             */
        /*-----------------------------------------------------------------*/
    };

    typedef ActorStateBase          StateType;

    typedef NewActionBase::Functor  Functor;
    typedef NewActionBase::ResultE  ResultE;
    typedef NewActionBase::RootList RootList;

    /*---------------------------------------------------------------------*/
    /*! \name                    Destructor                                */
    /*! \{                                                                 */

    virtual ~ActorBase             (void                 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Apply                                  */
    /*! \{                                                                 */

    virtual ResultE applyEnter     (NodeCorePtr pNodeCore);
    virtual ResultE applyLeave     (NodeCorePtr pNodeCore);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Start/Stop                               */
    /*! \{                                                                 */

    virtual ResultE start          (void                 );
    virtual ResultE stop           (void                 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Property Queries                           */
    /*! \{                                                                 */

    virtual bool    hasEnterMethod (void                   ) const;
    virtual bool    hasLeaveMethod (void                   ) const;

    virtual bool    hasOrderedState(void                   ) const;   
    
    virtual bool    acceptsIterator(IteratorBase *pIterator) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Action Interface                         */
    /*! \{                                                                 */

    inline       void       addRoot    (      NodePtr      pRoot  );
    inline       void       addRoot    (const RootList    &roots  );
    
    inline const RootList  &getRoots   (      void                ) const;
    inline       RootList  &getRoots   (      void                );

    inline       NodePtr    getCurrNode(      void                ) const;

    inline       void                   setUseNodeList(void);
    inline       bool                   getUseNodeList(void) const;

    inline       ActiveNodeListIt       beginNodes    (void);
    inline       ActiveNodeListIt       endNodes      (void);

    inline       ActiveNodeListConstIt  beginNodes    (void) const;
    inline       ActiveNodeListConstIt  endNodes      (void) const;

    inline       ActiveNodeList        &getNodeList   (void);
    inline const ActiveNodeList        &getNodeList   (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Receive Signals                          */
    /*! \{                                                                 */

    virtual      void receiveIteratorSet(IteratorBase *pIterator);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Get Identification                        */
    /*! \{                                                                 */

    inline        NewAction *getAction (void);
    inline  const NewAction *getAction (void) const;
    inline        UInt32     getActorId(void) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
protected:
    friend class OSG::NewAction;

    typedef ActorBase Self;

    enum
    {
	bHasEnterMethod  = 0,
	bHasLeaveMethod  = 0,
        
        bHasOrderedState = 0
    };

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructor                                 */
    /*! \{                                                                 */

    ActorBase                                (void                     );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     State                                    */
    /*! \{                                                                 */

    virtual       void            createState(void                     );

    inline  const ActorStateBase *getState   (void                     ) const;
    inline        ActorStateBase *getState   (void                     );

    inline        void            setState   (ActorStateBase *pState   );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Emit Signals                              */
    /*! \{                                                                 */

    inline        void            emitStateRead   (void) const;
    inline        void            emitStateWrite  (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Set Identification                        */
    /*! \{                                                                 */
    
    inline        void            setAction  (NewAction      *pAction  );
    inline        void            setActorId (UInt32          uiActorId);

    /*! \}                                                                 */ 
    /*==========================  PRIVATE  ================================*/
private:
    NewAction               *_pAction;
    UInt32                   _uiActorId;

    ActorStateBase          *_pState;
};

OSG_END_NAMESPACE

#include "OSGActorBase.inl"

#define OSGACTORBASE_HEADER_CVSID "@(#)$Id: OSGActorBase.h,v 1.1 2003/10/10 13:51:06 neumannc Exp $"

#endif /* _OSGACTORBASE_H_ */
