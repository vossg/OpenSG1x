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

#ifndef _OSGTESTINGEXTENDACTOR_H_
#define _OSGTESTINGEXTENDACTOR_H_
#ifdef __sgi
#pragma once
#endif

//----------------------------------------------------------------------------
//    Includes
//----------------------------------------------------------------------------

#include <OSGConfig.h>

#include <OSGTestingExtendActorBase.h>

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING TestingExtendActor : public TestingExtendActorBase
{
    /*====  PUBLIC  =========================================================*/
  public:
    /*-----------------------------------------------------------------------*/
    /*! \name    Types                                                       */
    /*! \{                                                                   */

    typedef ExtendActorBase::ResultE ResultE;
    typedef ExtendActorBase::Functor Functor;

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Create                                                      */
    /*! \{                                                                   */

    static TestingExtendActor *create(void);

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Destructor                                                  */
    /*! \{                                                                   */

    virtual ~TestingExtendActor(void);

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Enter/Leave                                                 */
    /*! \{                                                                   */


    /*! \}                                                                   */
    /*==== PROTECTED ========================================================*/
  protected:
    /*-----------------------------------------------------------------------*/
    /*! \name    Constructor                                                 */
    /*! \{                                                                   */

    TestingExtendActor(void);

    /*! \}                                                                   */
    /*==== PRIVATE ==========================================================*/
  private:
    typedef TestingExtendActorBase Inherited;
};

OSG_END_NAMESPACE

#include <OSGTestingExtendActor.inl>

#define OSGTESTINGEXTENDACTOR_HEADER_CVSID "@(#)$Id:"

#endif /* _OSGTESTINGEXTENDACTOR_H_ */
