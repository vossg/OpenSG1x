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

#ifndef _OSGNEWACTION_H_
#define _OSGNEWACTION_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGNewActionBase.h"
#include <OSGBaseTypes.h>

#include <vector>

OSG_BEGIN_NAMESPACE

class ActorBase;
class ActorStateChunk;
class IteratorBase;
class ActiveNodeList;
class ActiveNodeListIt;
class ActiveNodeListConstIt;
class NewActionIterInterface;

/*! \brief NewAction class.
           Basically a container for one iterator and arbitrary number
           of actors.
 */

class OSG_SYSTEMLIB_DLLMAPPING NewAction : public NewActionBase
{
    /*==========================  PUBLIC  =================================*/
  public: 
    /*---------------------------------------------------------------------*/
    /*! \name                     Create                                   */
    /*! \{                                                                 */

    static NewAction *create  (      void                   );
    static NewAction *create  (      IteratorBase *pIterator);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Destructor                                */
    /*! \{                                                                 */

    ~NewAction                (      void                   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Actor Access                              */
    /*! \{                                                                 */

    Int32         addActor    (      ActorBase    *pActor   );
    Int32         insertActor (      ActorBase    *pActor, 
                                     UInt32        uiIndex  );
    
    ActorBase    *subActor    (      UInt32        uiIndex  );
    ActorBase    *subActor    (      ActorBase    *pActor   );

    void          eraseActor  (      UInt32        uiIndex  );
    void          eraseActor  (      ActorBase    *pActor   );

    ActorBase    *getActor    (      UInt32        uiIndex  ) const;
    Int32         findActor   (      ActorBase    *pActor   ) const;

    UInt32        getNumActors(void                         ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Iterator Access                          */
    /*! \{                                                                 */

    bool          setIterator (      IteratorBase *pIterator);
    IteratorBase *getIterator (      void                   ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                          Apply                               */
    /*! \{                                                                 */

    ResultE       apply       (      NodePtr       pRoot    );
    ResultE       apply       (const RootList     &roots    );

    /*! \}                                                                 */  
    /*==========================  PRIVATE  ================================*/
private:
    friend class OSG::IteratorBase;
    friend class OSG::ActorBase;

    typedef NewActionBase::ActorStore        ActorStore;
    typedef NewActionBase::ActorStoreIt      ActorStoreIt;
    typedef NewActionBase::ActorStoreConstIt ActorStoreConstIt;    

    /*---------------------------------------------------------------------*/
    /*! \name                       Constructors                           */
    /*! \{                                                                 */

             NewAction(void                   );
    explicit NewAction(IteratorBase *pIterator);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Iterator Interface                        */
    /*! \{                                                                 */

    ResultE           startActors   (      void                   );
    ResultE           stopActors    (      void                   );

    void              cloneState    (      ActorStateChunk *pChunk);
    void              getState      (      ActorStateChunk *pChunk);
    void              setState      (      ActorStateChunk *pChunk);
  
    ResultE           enterNode     (      NodePtr          pNode,
                                           ActorStoreIt     iter,
                                           ActorStoreIt     end   );
    ResultE           leaveNode     (      NodePtr          pNode,
                                           ActorStoreIt     iter,
                                           ActorStoreIt     end   );

    ActorStoreIt      beginActors   (      void                   );
    ActorStoreIt      endActors     (      void                   );

    ActorStoreConstIt beginActors   (      void                   ) const;
    ActorStoreConstIt endActors     (      void                   ) const;
 
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Actor Interface                         */
    /*! \{                                                                 */

          void                   addRoot        (      NodePtr   pRoot );
          void                   addRoot        (const RootList &roots );

    const RootList              &getRoots       (      void            ) const;
          RootList              &getRoots       (      void            );

          NodePtr                getCurrNode    (      void            ) const;

          void                   setUseNodeList (      void            );
          bool                   getUseNodeList (      void            ) const;

          ActiveNodeListIt       beginNodes     (      void            );
          ActiveNodeListIt       endNodes       (      void            );

          ActiveNodeListConstIt  beginNodes     (      void            ) const;
          ActiveNodeListConstIt  endNodes       (      void            ) const;

          ActiveNodeList        &getNodeList    (      void            );
    const ActiveNodeList        &getNodeList    (      void            ) const;

          void                   emitStateRead  (      UInt32 uiActorId) const;
          void                   emitStateWrite (      UInt32 uiActorId) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                         Helpers                              */
    /*! \{                                                                 */

    void         configureAdd       (      ActorBase   *pActor,
                                           UInt32       uiActorId);
    void         configureSub       (      ActorBase   *pActor   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    ActorStore    _actors;
    IteratorBase *_pIterator;

    bool          _bInTraversal;
};

OSG_END_NAMESPACE

#include "OSGNewAction.inl"

#define OSGNEWACTION_HEADER_CVSID "@(#)$Id: OSGNewAction.h,v 1.2 2003/10/10 14:27:44 neumannc Exp $"

#endif /* _OSGNEWACTION_H_ */
