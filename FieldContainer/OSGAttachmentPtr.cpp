/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGAttachmentPtr.h"
#include "OSGAttachment.h"
#include "OSGThread.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: $";
    static char cvsid_hpp[] = OSGATTACHMENTPTR_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/** \typedef AttachmentPtr::Inherited
 *  \brief Parent type
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

AttachmentPtr::AttachmentPtr(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

AttachmentPtr::AttachmentPtr(const AttachmentPtr &source) :

    Inherited(source)
{
}

/** \brief NullPtr Constructor
 */

AttachmentPtr::AttachmentPtr(const NullFieldContainerPtr &source) :

    Inherited(source)
{
}

/** \brief Destructor
 */

AttachmentPtr::~AttachmentPtr(void)
{
}

/*-------------------------- pointer operators ------------------------------*/

/** \brief Arrow operator
 */

Attachment *AttachmentPtr::operator->(void)
{
    return (Attachment *) getElemP(Thread::getAspect());
}

/** \brief Const arrow operator
 */

Attachment *AttachmentPtr::operator->(void) const
{
    return (Attachment *) getElemP(Thread::getAspect());
}

/** \brief Dereference operator
 */

Attachment &AttachmentPtr::operator *(void)
{
    return *((Attachment *) getElemP(Thread::getAspect()));
}

/** \brief Const dereference operator
 */

Attachment &AttachmentPtr::operator *(void) const
{
    return *((Attachment *) getElemP(Thread::getAspect()));
}

Attachment *AttachmentPtr::getCPtr(void)
{
    return (Attachment *) getElemP(Thread::getAspect());
}

Attachment *AttachmentPtr::getCPtr(void) const
{
    return (Attachment *) getElemP(Thread::getAspect());
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

void AttachmentPtr::operator = (const AttachmentPtr &source)
{
    // copy parts inherited from parent
    *(static_cast<Inherited *>(this)) = source;
}

/** \brief NullPtr assignment
 */

void AttachmentPtr::operator = (const NullFieldContainerPtr &source)
{
    // copy parts inherited from parent
    *(static_cast<Inherited *>(this)) = source;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/** \brief Construct a pointer from a give node.
 */

AttachmentPtr::AttachmentPtr(const Attachment &source) :

    Inherited(source)
{
}

AttachmentPtr::AttachmentPtr(const Attachment *source) :

    Inherited(source)
{
}

AttachmentPtr::AttachmentPtr(const Attachment *source,
                             const UInt16      uiSize,
                             const UInt16      uiParentPos) :

    Inherited(source, uiSize, uiParentPos)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


/** \brief Write FC to the given stream
 */

OSG_SYSTEMLIB_DLLMAPPING
ostream &OSG::operator <<(      ostream        &os,
                          const AttachmentPtr  &fc)
{
    if(fc == NullFC)
    {
        os << hex << "NodePtr 0x" << &fc << dec << ":NullFC";
    }
    else
    {
        os << hex << "NodePtr 0x"
           << &fc << dec << ":" << fc->getType().getName() << "Ptr(0x"
           << hex << (&(*fc)) << dec << ")";
    }

    return os;
}

///---------------------------------------------------------------------------
///  FUNCTION:
///---------------------------------------------------------------------------
//:  Example for the head comment of a function
///---------------------------------------------------------------------------
///
//p: Paramaters:
//p:
///
//g: GlobalVars:
//g:
///
//r: Return:
//r:
///
//c: Caution:
//c:
///
//a: Assumptions:
//a:
///
//d: Description:
//d:
///
//s: SeeAlso:
//s:
///---------------------------------------------------------------------------




