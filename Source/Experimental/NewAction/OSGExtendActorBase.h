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

#ifndef _OSGEXTENDACTORBASE_H_
#define _OSGEXTENDACTORBASE_H_
#ifdef __sgi
#pragma once
#endif

//----------------------------------------------------------------------------
//    Includes
//----------------------------------------------------------------------------

#include <OSGConfig.h>
#include <OSGSystemDef.h>

#include "OSGActorBase.h"

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING ExtendActorBase : public ActorBase
{
    /*==== PUBLIC ===========================================================*/
  public:
    /*-----------------------------------------------------------------------*/
    /*! \name    Destructor                                                  */
    /*! \{                                                                   */

    virtual ~ExtendActorBase(void);

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
    /*! \name    Extra Children Management                                   */
    /*! \{                                                                   */

    inline UInt32 addExtraChild(const NodePtr &pNode                   );
    inline UInt32 addExtraChild(const NodePtr &pNode, PriorityType prio);

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Mutli Pass Management                                       */
    /*! \{                                                                   */

    inline void setNumPasses(UInt32 numPasses);
    
    /*! \}                                                                   */
    /*==== PROTECTED ========================================================*/
  protected:
    /*-----------------------------------------------------------------------*/
    /*! \name    Types                                                       */
    /*! \{                                                                   */

    typedef ActorBase            Inherited;
    typedef Inherited::StateType StateType;

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Constructor                                                 */
    /*! \{                                                                   */

    ExtendActorBase(void);

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Add, Sub and Find Helper                                    */
    /*! \{                                                                   */

    virtual UInt32 addHelper (      NewActionBase *pAction);
    virtual void   subHelper (      NewActionBase *pAction);
    virtual UInt32 findHelper(const NewActionBase *pAction);

    /*! \}                                                                   */
};

OSG_END_NAMESPACE

#include "OSGExtendActorBase.inl"

#define OSGEXTENDACTORBASE_HEADER_CVSID "@(#)$Id: OSGExtendActorBase.h,v 1.4 2004/09/17 14:09:43 neumannc Exp $"

#endif /* _OSGEXTENDACTORBASE_H_ */
