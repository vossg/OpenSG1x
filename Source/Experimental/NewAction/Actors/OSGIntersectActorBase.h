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

#ifndef _OSGINTERSECTACTORBASE_H_
#define _OSGINTERSECTACTORBASE_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGSystemDef.h>

#include <OSGActorBase.h>               // Parent
#include <OSGMultiFunctorStore.h>      // EnterStore
#include <OSGEmptyFunctorStore.h>      // LeaveStore

#include <OSGLine.h>   // Line type
#include <OSGBaseTypes.h>   // MaxDist type
#include <OSGBaseTypes.h>   // ScaleFactor type
#include <OSGBaseTypes.h>   // HitDist type
#include <OSGNodePtr.h>   // HitObject type
#include <OSGBaseTypes.h>   // HitTriangle type
#include <OSGBaseTypes.h>   // Hit type

OSG_BEGIN_NAMESPACE

#ifdef __sgi
#pragma set woff 1375
#endif

class OSG_SYSTEMLIB_DLLMAPPING IntersectActorBase : 
    public  ActorBase,
    private MultiFunctorStore<EnterTag>,
    private EmptyFunctorStore<LeaveTag>
{
    /*==========================  PUBLIC  =================================*/
  public:
    typedef ActorBase     Inherited;
    typedef Inherited::Functor Functor;

    /*---------------------------------------------------------------------*/
    /*! \name                       Destructor                             */
    /*! \{                                                                 */

    virtual ~IntersectActorBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Enter Registration                        */
    /*! \{                                                                 */

    static void regClassEnter         (const Functor            &refFunc,
                                       const FieldContainerType &refType );
           void regEnter              (const Functor            &refFunc,
                                       const FieldContainerType &refType );
    static void regDefaultClassEnter  (const Functor            &refFunc );
           void regDefaultEnter       (const Functor            &refFunc );

    static void unregClassEnter       (const FieldContainerType &refType );
           void unregEnter            (const FieldContainerType &refType );
    static void unregDefaultClassEnter(void                              );
           void unregDefaultEnter     (void                              );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Apply Enter                             */
    /*! \{                                                                 */

    virtual ResultE applyEnter(NodeCorePtr pNodeCore);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Property Queries                          */
    /*! \{                                                                 */

    virtual bool hasEnterMethod (void                   ) const;
    virtual bool hasLeaveMethod (void                   ) const;

    virtual bool hasOrderedState(void                   ) const;

    virtual bool acceptsIterator(IteratorBase *pIterator) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Public State Access                         */
    /*! \{                                                                 */

    inline const Line &getLine(void) const;
    inline       void               setLine(const Line &stateVal);
    inline const Real32 &getMaxDist(void) const;
    inline       void               setMaxDist(const Real32 &stateVal);
    inline const Real32 &getScaleFactor(void) const;
    inline       void               setScaleFactor(const Real32 &stateVal);
    inline const Real32 &getHitDist(void) const;
    inline       void               setHitDist(const Real32 &stateVal);
    inline const NodePtr &getHitObject(void) const;
    inline       void               setHitObject(const NodePtr &stateVal);
    inline const Int32 &getHitTriangle(void) const;
    inline       void               setHitTriangle(const Int32 &stateVal);
    inline const bool &getHit(void) const;
    inline       void               setHit(const bool &stateVal);

    /*! \}                                                                  */
    /*=========================  PROTECTED  ================================*/
  protected:
    class IntersectActorStateBase;

    typedef IntersectActorStateBase               StateType;
    typedef MultiFunctorStore<EnterTag> EnterStoreType;
    typedef EmptyFunctorStore<LeaveTag> LeaveStoreType;

    /*---------------------------------------------------------------------*/
    /*! \name                    State Class                               */
    /*! \{                                                                 */

    class OSG_SYSTEMLIB_DLLMAPPING IntersectActorStateBase : public Inherited::StateType
    {
      public:
        IntersectActorStateBase(void                                );
        IntersectActorStateBase(const IntersectActorStateBase &source);

        virtual ~IntersectActorStateBase(void);

        virtual ActorStateBase *clone(void);
        
        inline const Line &getLine(void) const;
        inline       Line &getLine(void);
        inline const Real32 &getScaleFactor(void) const;
        inline       Real32 &getScaleFactor(void);

        enum
        {
            bHasStateElems = 1
        };

      private:
        Line _asLine;
        Real32 _asScaleFactor;
    };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    enum
    {
        bHasEnterMethod  = Inherited     ::bHasEnterMethod  |
                           EnterStoreType::bHasFunctors,
        bHasLeaveMethod  = Inherited     ::bHasLeaveMethod  |
                           LeaveStoreType::bHasFunctors,
        bHasOrderedState = Inherited     ::bHasOrderedState |
                           StateType     ::bHasStateElems
    };

    /*---------------------------------------------------------------------*/
    /*! \name                    Constructor                               */
    /*! \{                                                                 */
    
    IntersectActorBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    StatePtr Access                           */
    /*! \{                                                                 */

    inline const IntersectActorStateBase *getCastStatePtr(void) const;
    inline       IntersectActorStateBase *getCastStatePtr(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Create State                            */
    /*! \{                                                                 */

    virtual void createState(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Protected State Access                      */
    /*! \{                                                                 */


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    static EnterStoreType *_pClassEnterStore;
    static LeaveStoreType *_pClassLeaveStore;

    Real32 _asMaxDist;
    Real32 _asHitDist;
    NodePtr _asHitObject;
    Int32 _asHitTriangle;
    bool _asHit;
};

#ifdef __sgi
#pragma reset woff 1375
#endif

OSG_END_NAMESPACE

#include <OSGIntersectActorBase.inl>

#define OSGINTERSECTACTORBASE_HEADER_CVSID "@(#)$Id:"

#endif /* _OSGINTERSECTACTORBASE_H_ */
