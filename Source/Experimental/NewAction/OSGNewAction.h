
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

#define OSGNEWACTION_HEADER_CVSID "@(#)$Id: OSGNewAction.h,v 1.1 2003/10/10 13:51:06 neumannc Exp $"

#endif /* _OSGNEWACTION_H_ */
