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

#ifndef _OSG@!CLASSNAME!@_H_
#define _OSG@!CLASSNAME!@_H_
#ifdef __sgi
#pragma once
#endif

#include <@!HeaderPrefix!@OSGConfig.h>

@@if UseLocalIncludes
#include "OSG@!Classname!@Base.h"
@@else
#include <OSG@!Classname!@Base.h>
@@endif

OSG_BEGIN_NAMESPACE

class OSG_@!LIBNAME!@LIB_DLLMAPPING @!Classname!@ : public @!Classname!@Base
{
    /*================================= PUBLIC ==============================*/
  public:
    /*-----------------------------------------------------------------------*/
    /*! \name                       Create                                   */
    /*! \{                                                                   */

    static @!Classname!@ *create(void);

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name                       Destructor                               */
    /*! \{                                                                   */

    virtual ~@!Classname!@(void);

    /*! \}                                                                   */
    /*=============================== PROTECTED =============================*/
  protected:
    /*-----------------------------------------------------------------------*/
    /*! \name                       Constructor                              */
    /*! \{                                                                   */

    @!Classname!@(void);

    /*! \}                                                                   */
    /*================================ PRIVATE ==============================*/
  private:

    typedef @!Classname!@Base Inherited;
};

OSG_END_NAMESPACE

@@if UseLocalIncludes
#include "OSG@!Classname!@.inl"
@@else
#inlcude <OSG@!Classname!@.inl>
@@endif

#define OSG@!CLASSNAME!@_HEADER_CVSID "@(#)$Id: ActorTemplate_h.h,v 1.1 2003/10/10 13:51:07 neumannc Exp $"

#endif /* _OSG@!CLASSNAME!@_H_ */

