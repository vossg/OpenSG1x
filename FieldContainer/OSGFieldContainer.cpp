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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"
#include "OSGFieldContainer.h"
#include "OSGFieldDescription.h"
#include "OSGThread.h"
#include "OSGThreadManager.h"
#include "OSGChangeList.h"
#include "OSGFieldContainerPtr.h"
#include "OSGBinaryDataHandler.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGFIELDCONTAINER_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGFIELDCONTAINER_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/*! \class osg::FieldContainer
 */

FieldContainerType FieldContainer::_type("FieldContainer");

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

FieldContainerType &FieldContainer::getType(void)
{
    return _type;
}

const FieldContainerType &FieldContainer::getType(void) const
{
    return _type;
}

UInt32 FieldContainer::getTypeId(void) const
{
    return getType().getId();
}

UInt16 FieldContainer::getGroupId(void) const
{
    return getType().getGroupId();
}

const Char8 *FieldContainer::getTypeName(void) const
{
    return getType().getCName();
}

Field *FieldContainer::getField(UInt32 fieldId)
{
    const FieldDescription *desc = getType().getFieldDescription(fieldId);

    return desc ? desc->getField(*this) : NULL;
}

Field *FieldContainer::getField(const Char8 *fieldName)
{
    const FieldDescription *desc =getType().findFieldDescription(fieldName);

    return desc ? desc->getField(*this) : NULL;
}

/*-------------------------------------------------------------------------*/
/*                            Binary Access                                */

UInt32 FieldContainer::getBinSize(const BitVector &)
{
    return 0;
}

void FieldContainer::copyToBin(      BinaryDataHandler &,
                               const BitVector         &)
{
}

void FieldContainer::copyFromBin(      BinaryDataHandler &,
                                 const BitVector         &)
{
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

FieldContainer::FieldContainer(void) :
    _shares(0)
{
}

FieldContainer::FieldContainer(const FieldContainer &) :
    _shares(0)

{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

FieldContainer::~FieldContainer(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Changed                                   */

void FieldContainer::changed(BitVector  OSG_CHECK_ARG(whichField),
                             ChangeMode OSG_CHECK_ARG(from      ))
{
    // fprintf(stderr, "FC Changed %d %d\n", whichField, fromSync);
}

/*-------------------------------------------------------------------------*/
/*                             MT Contruction                              */

void FieldContainer::onCreate(void)
{
}

void FieldContainer::onCreate(const FieldContainer &)
{
}

/*-------------------------------------------------------------------------*/
/*                             MT Destruction                              */

void FieldContainer::onDestroy(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Sync                                     */

void FieldContainer::executeSyncImpl(      FieldContainer *,
                                     const BitVector      &)
{
}

/*-------------------------------------------------------------------------*/
/*                               Functions                                 */

OSG_BEGIN_NAMESPACE

void addRefCP(const FieldContainerPtrBase &objectP)
{
    if(objectP != NullFC)
        objectP.addRef();
}

void subRefCP(const FieldContainerPtrBase &objectP)
{
    if(objectP != NullFC)
        objectP.subRef();
}

void clearRefCP(FieldContainerPtrBase &objectP)
{
    if(objectP != NullFC)
        objectP.subRef();

    objectP = NullFC;
}

void setRefdCP(      FieldContainerPtrBase &objectP,
               const FieldContainerPtrBase &newObjectP)
{
    if(objectP != newObjectP)
    {
        if(objectP != NullFC)
            objectP.subRef();

        objectP = newObjectP;

        if(objectP != NullFC)
            objectP.addRef();
    }
}

void beginEditCP(const FieldContainerPtr &objectP,
                       BitVector         whichField)
{
    if(objectP != NullFC)
        objectP.beginEdit(whichField);
}

void endEditCP(const FieldContainerPtr &objectP,
                     BitVector          whichField)
{
    if(objectP != NullFC)
        objectP.endEdit(whichField);
}

void changedCP(const FieldContainerPtr &objectP,
                     BitVector          whichField)
{
    if(objectP != NullFC)
        objectP.changed(whichField);
}

void endEditNotChangedCP(const FieldContainerPtr &objectP,
                               BitVector          whichField)
{
    if(objectP != NullFC)
        objectP.endEditNotChanged(whichField);
}

OSG_END_NAMESPACE
