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

#include "OSGPrintNameActor.h"

#include <OSGLog.h>
#include <OSGSimpleAttachments.h>


OSG_USING_NAMESPACE

PrintNameActor *
PrintNameActor::create(void)
{
    PrintNameActor *pActor = new PrintNameActor();

    pActor->createState();

    return pActor;
}

PrintNameActor::~PrintNameActor(void)
{
}

PrintNameActor::ResultE
PrintNameActor::applyEnter(NodeCorePtr pNodeCore)
{
    if(getPrintOnEnter() == true)
    {
        NodePtr pNode = this->getCurrNode();
        
        if(getName(pNode) != NULL)
        {
            FNOTICE(("ENTER Node: %s ", getName(pNode)));
        }
        else
        {
            FNOTICE(("ENTER Node: unnamed "));
        }

        if(getName(pNodeCore) != NULL)
        {
            FPNOTICE(("Core: %s.\n", getName(pNodeCore)));
        }
        else
        {
            FPNOTICE(("Core: unnamed.\n"));
        }
    }

    return NewActionBase::Continue;
}

PrintNameActor::ResultE
PrintNameActor::applyLeave(NodeCorePtr pNodeCore)
{
    if(getPrintOnLeave() == true)
    {
        NodePtr pNode = this->getCurrNode();

        if(getName(pNode) != NULL)
        {
            FNOTICE(("LEAVE Node: %s ", getName(pNode)));
        }
        else
        {
            FNOTICE(("LEAVE Node: unnamed "));
        }

        if(getName(pNodeCore) != NULL)
        {
            FPNOTICE(("Core: %s.\n", getName(pNodeCore)));
        }
        else
        {
            FPNOTICE(("Core: unnamed.\n"));
        }
    }

    return NewActionBase::Continue;
}

bool
PrintNameActor::hasEnterMethod(void) const
{
    return getPrintOnEnter();
}

bool
PrintNameActor::hasLeaveMethod(void) const
{
    return getPrintOnLeave();
}

PrintNameActor::PrintNameActor(void)
    : Inherited()
{
}                    

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8 cvsid_cpp     [] = "@(#)$Id: OSGPrintNameActor.cpp,v 1.1 2003/10/10 13:51:07 neumannc Exp $";
    static Char8 cvsid_hpp     [] = OSGPRINTNAMEACTOR_HEADER_CVSID;
    static Char8 cvsid_inl     [] = OSGPRINTNAMEACTOR_INLINE_CVSID;
}
