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

#ifndef _OSGPRINTNAMEACTORBASE_H_
#define _OSGPRINTNAMEACTORBASE_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGSystemDef.h>

#include <OSGActorBase.h>               // Parent
#include <OSGEmptyFunctorStore.h>      // EnterStore
#include <OSGEmptyFunctorStore.h>      // LeaveStore


OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING PrintNameActorBase : 
    public  ActorBase,
    private EmptyFunctorStore<EnterTag>,
    private EmptyFunctorStore<LeaveTag>
{
    /*==========================  PUBLIC  =================================*/
  public:
    typedef ActorBase     Inherited;
    typedef Inherited::Functor Functor;

    /*---------------------------------------------------------------------*/
    /*! \name                       Destructor                             */
    /*! \{                                                                 */

    virtual ~PrintNameActorBase(void);




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

    inline const bool &getPrintOnEnter(void) const;
    inline       void               setPrintOnEnter(const bool &stateVal);
    inline const bool &getPrintOnLeave(void) const;
    inline       void               setPrintOnLeave(const bool &stateVal);

    /*! \}                                                                  */
    /*=========================  PROTECTED  ================================*/
  protected:
    class PrintNameActorStateBase;

    typedef PrintNameActorStateBase               StateType;
    typedef EmptyFunctorStore<EnterTag> EnterStoreType;
    typedef EmptyFunctorStore<LeaveTag> LeaveStoreType;

    /*---------------------------------------------------------------------*/
    /*! \name                    State Class                               */
    /*! \{                                                                 */

    class OSG_SYSTEMLIB_DLLMAPPING PrintNameActorStateBase : public Inherited::StateType
    {
      public:
        PrintNameActorStateBase(void                                );
        PrintNameActorStateBase(const PrintNameActorStateBase &source);

        virtual ~PrintNameActorStateBase(void);

        virtual ActorStateBase *clone(void);
        

        enum
        {
            bHasStateElems = Inherited::StateType::bHasStateElems
        };

      private:
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
    
    PrintNameActorBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    StatePtr Access                           */
    /*! \{                                                                 */

    inline const PrintNameActorStateBase *getCastStatePtr(void) const;
    inline       PrintNameActorStateBase *getCastStatePtr(void);

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

    bool _asPrintOnEnter;
    bool _asPrintOnLeave;
};

OSG_END_NAMESPACE

#include <OSGPrintNameActorBase.inl>

#define OSGPRINTNAMEACTORBASE_HEADER_CVSID "@(#)$Id:"

#endif /* _OSGPRINTNAMEACTORBASE_H_ */
