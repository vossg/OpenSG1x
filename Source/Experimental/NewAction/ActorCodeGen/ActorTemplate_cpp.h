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

#include <@!HeaderPrefix!@OSGConfig.h>

#include "OSG@!Classname!@.h"

OSG_USING_NAMESPACE

/*------------------------------ create -------------------------------------*/

@!Classname!@ *
@!Classname!@::create(void)
{
    @!Classname!@ *pActor = new @!Classname!@();

    pActor->createState();

    return pActor;
}

/*----------------------------- destructor ----------------------------------*/

@!Classname!@::~@!Classname!@(void)
{
}

/*---------------------------- constructor ----------------------------------*/

@!Classname!@::@!Classname!@(void)
{
}

/*--------------------------------------------------------------------------*/
/*                               cvs id's                                   */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8 cvsid_cpp     [] = "@(#)$Id: ActorTemplate_cpp.h,v 1.1 2003/10/10 13:51:07 neumannc Exp $";
    static Char8 cvsid_hpp     [] = OSG@!CLASSNAME!@_HEADER_CVSID;
    static Char8 cvsid_inl     [] = OSG@!CLASSNAME!@_INLINE_CVSID;
}
