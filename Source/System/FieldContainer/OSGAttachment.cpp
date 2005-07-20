/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000-2002 by OpenSG Forum                   *
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

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGAttachment.cpp
    \ingroup GrpSystemFieldContainer
 */
#endif

#define OSG_COMPILEATTACHMENTINST

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGAttachment.h"
#include "OSGAttachmentContainer.h"
#include "OSGNodePtr.h"
#include "OSGNodeFields.h"

OSG_USING_NAMESPACE


const BitVector 
    Attachment::InternalFieldMask  = (1 << Attachment::InternalFieldId);
const BitVector 
    Attachment::ParentsFieldMask  = (1 << Attachment::ParentsFieldId);

FieldDescription *Attachment::_desc[] =
{
    new FieldDescription(
        SFBool::getClassType(),
        "internal",
        OSG_FC_FIELD_IDM_DESC(InternalField),
        false,
        (FieldAccessMethod) &Attachment::getSFInternal,
        "true"),

    new FieldDescription(
        MFNodePtr::getClassType(),
        "parents",
        OSG_FC_FIELD_IDM_DESC(ParentsField),
        true,
        (FieldAccessMethod) &Attachment::getMFParents,
        "test")
};

FieldContainerType Attachment::_type("Attachment",
                                     "FieldContainer",
                                      NULL,
                                      NULL,
                                      NULL,
                                     _desc,
                                      sizeof(_desc));

OSG_FIELD_CONTAINER_DEF(Attachment, AttachmentPtr)

/*-------------------------------------------------------------------------*/
/*                               Parents                                   */

MFFieldContainerPtr &Attachment::getParents(void)
{
    return _parents;
}

const MFFieldContainerPtr &Attachment::getParents(void) const
{
    return _parents;
}

MFFieldContainerPtr *Attachment::getMFParents(void)
{
    return &_parents;
}

void Attachment::addParent(FieldContainerPtr parent)
{
    _parents.push_back(parent);
}

void Attachment::subParent(FieldContainerPtr parent)
{
    MFFieldContainerPtr::iterator parentIt = _parents.find(parent);

    if(parentIt != _parents.end())
    {
        _parents.erase(parentIt);
    }
}

Int32 Attachment::findParent(FieldContainerPtr parent)
{
    MFFieldContainerPtr::iterator parentIt = _parents.find(parent);

    if(parentIt != _parents.end())
    {
        return parentIt - _parents.begin();
    }
    else
    {
        return -1;
    }
}

/*-------------------------------------------------------------------------*/
/*                            Binary Access                                */

SFBool &Attachment::getInternal(void)
{
    return _sfInternal;
}

const SFBool &Attachment::getInternal(void) const
{
    return _sfInternal;
}

SFBool *Attachment::getSFInternal(void)
{
    return &_sfInternal;
}

void Attachment::setInternal(bool bVal)
{
    _sfInternal.setValue(bVal);
}

/*-------------------------------------------------------------------------*/
/*                            Binary Access                                */

UInt32 Attachment::getBinSize(const BitVector &whichField)
{
    UInt32 returnValue = 0;

    if(FieldBits::NoField != (InternalFieldMask & whichField))
    {
        returnValue += _sfInternal.getBinSize();
    }

    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        returnValue += _parents.getBinSize();
    }

    return returnValue;
}

void Attachment::copyToBin(      BinaryDataHandler &pMem,
                           const BitVector         &whichField)
{
    if(FieldBits::NoField != (InternalFieldMask & whichField))
    {
        _sfInternal.copyToBin(pMem);
    }

    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        _parents.copyToBin(pMem);
    }
}

void Attachment::copyFromBin(      BinaryDataHandler &pMem,
                             const BitVector         &whichField)
{
    if(FieldBits::NoField != (InternalFieldMask & whichField))
    {
        _sfInternal.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        _parents.copyFromBin(pMem);
    }
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

void Attachment::dump(      UInt32                  uiIndent,
                      const BitVector OSG_CHECK_ARG(bvFlags)) const
{
    UInt32 i;

    AttachmentPtr thisP(this);

    indentLog(uiIndent, PLOG);

    PLOG << "Attachment"
         << "(" 
         << std::dec
         << thisP.getFieldContainerId()
         << ") : " 
         << getType().getName()
         << "("       
         << this 
         << ")" 
         << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "[" << std::endl;

    indentLog(uiIndent + 4, PLOG);
    PLOG << "Parents : " << std::endl;

    for(i = 0; i < _parents.size(); i++)
    {
        indentLog(uiIndent + 4, PLOG);
        PLOG << "           " << i << ") " << &(*(_parents[i])) << std::endl;
    }

//    thisP.dump(uiIndent, FCDumpFlags::RefCount);

    indentLog(uiIndent, PLOG);
    PLOG << "]" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << std::endl;

    indentLog(uiIndent, PLOG);
    PLOG << "}" << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

Attachment::Attachment(void) :
     Inherited (     ),
    _sfInternal(false),
    _parents   (     )
{
}

Attachment::Attachment(const Attachment &obj) :
     Inherited (obj            ),
    _sfInternal(obj._sfInternal),
    _parents   (               )
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

Attachment::~Attachment(void)
{
}


/*-------------------------------------------------------------------------*/
/*                          MT Destruction                                 */

void Attachment::onDestroy(void)
{
}

#if defined(OSG_FIXED_MFIELDSYNC)
void Attachment::onDestroyAspect(UInt32 uiId, UInt32 uiAspect)
{
    _parents.terminateShare(uiAspect, this->getContainerSize());
}
#endif

/*-------------------------------------------------------------------------*/
/*                                Sync                                     */

#if !defined(OSG_FIXED_MFIELDSYNC)
void Attachment::executeSync(      FieldContainer &other,
                             const BitVector      &whichField)
{
    this->executeSyncImpl(static_cast<Attachment *>(&other), whichField);
}

void Attachment::executeSyncImpl(      Attachment *pOther,
                                 const BitVector  &whichField)
{
    Inherited::executeSyncImpl(pOther, whichField);

    if(FieldBits::NoField != (InternalFieldMask & whichField))
    {
        _sfInternal.syncWith(pOther->_sfInternal);
    }

    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        _parents.syncWith(pOther->_parents);
    }
}
#else
void Attachment::executeSync(      FieldContainer &other,
                             const BitVector      &whichField,
                             const SyncInfo       &sInfo     )
{
    this->executeSyncImpl(static_cast<Attachment *>(&other), 
                          whichField,
                          sInfo);
}

void Attachment::executeSyncImpl(      Attachment *pOther,
                                 const BitVector  &whichField,
                                 const SyncInfo   &sInfo)
{
    Inherited::executeSyncImpl(pOther, whichField, sInfo);

    if(FieldBits::NoField != (InternalFieldMask & whichField))
    {
        _sfInternal.syncWith(pOther->_sfInternal);
    }

    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        _parents.syncWith(pOther->_parents, sInfo);
    }
}

void Attachment::execBeginEditImpl (const BitVector &whichField, 
                                          UInt32     uiAspect,
                                          UInt32     uiContainerSize)
{
    Inherited::execBeginEditImpl(whichField, uiAspect, uiContainerSize);

    if (FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        _parents.beginEdit(uiAspect, uiContainerSize);
    }
}

void Attachment::execBeginEdit(const BitVector &whichField, 
                               UInt32     uiAspect,
                               UInt32     uiContainerSize) 
{
    this->execBeginEditImpl(whichField, uiAspect, uiContainerSize);
}
#endif

OSG_SYSTEMLIB_DLLMAPPING
std::ostream &OSG::operator <<(      std::ostream  &stream,
                               const AttachmentMap &OSG_CHECK_ARG(amap))
{
    stream << "Attachment << NI" << std::endl;

    return stream;
}



/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif
namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGATTACHMENT_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGATTACHMENT_INLINE_CVSID;
}
