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

#ifndef _OSG@!CLASSNAME!@_H_
#define _OSG@!CLASSNAME!@_H_
#ifdef __sgi
#pragma once
#endif

//----------------------------------------------------------------------------
//    Includes
//----------------------------------------------------------------------------

#include <@!HeaderPrefix!@OSGConfig.h>

@@if UseLocalIncludes
#include "OSG@!Classname!@Base.h"
@@else
#include <OSG@!Classname!@Base.h>
@@endif

OSG_BEGIN_NAMESPACE

@@if Library
class OSG_@!LIBNAME!@LIB_DLLMAPPING @!Classname!@ : public @!Classname!@Base
@@else
class @!Classname!@ : public @!ClassName!@Base
@@endif
{
    /*====  PUBLIC  =========================================================*/
  public:
    /*-----------------------------------------------------------------------*/
    /*! \name    Types                                                       */
    /*! \{                                                                   */

    typedef @!ParentName!@::ResultE ResultE;
    typedef @!ParentName!@::Functor Functor;

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Create                                                      */
    /*! \{                                                                   */

    static @!Classname!@ *create(void);

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Destructor                                                  */
    /*! \{                                                                   */

    virtual ~@!Classname!@(void);

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Enter/Leave                                                 */
    /*! \{                                                                   */

@@if EnterStore_IS_Empty
    virtual ResultE enterNode(const NodePtr &pNode);
@@endif
@@if LeaveStore_IS_Empty
    virtual ResultE leaveNode(const NodePtr &pNode);
@@endif

    /*! \}                                                                   */
    /*==== PROTECTED ========================================================*/
  protected:
    /*-----------------------------------------------------------------------*/
    /*! \name    Constructor                                                 */
    /*! \{                                                                   */

    @!Classname!@(void);

    /*! \}                                                                   */
    /*==== PRIVATE ==========================================================*/
  private:
    typedef @!Classname!@Base Inherited;
};

OSG_END_NAMESPACE

@@if UseLocalIncludes
#include "OSG@!Classname!@.inl"
@@else
#include <OSG@!Classname!@.inl>
@@endif

#define OSG@!CLASSNAME!@_HEADER_CVSID "@(#)$Id:"

#endif /* _OSG@!CLASSNAME!@_H_ */
