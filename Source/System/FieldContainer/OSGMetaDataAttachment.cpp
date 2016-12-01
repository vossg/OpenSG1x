/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#include "OSGMetaDataAttachment.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::MetaDataAttachment
An attachment that stores a string-to-string mapping of keys to values. User
code can store any key and value pair and interpret the string value in
whatever ways are appropriate.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MetaDataAttachment::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

MetaDataAttachment::MetaDataAttachment(void) :
    Inherited()
{
}

MetaDataAttachment::MetaDataAttachment(const MetaDataAttachment &source) :
    Inherited(source)
{
}

MetaDataAttachment::~MetaDataAttachment(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MetaDataAttachment::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void MetaDataAttachment::dump(      UInt32    , 
                              const BitVector ) const
{
    SLOG << "Dump MetaDataAttachment NI" << std::endl;
}

/*! Sets the value associated with the named key in this attribute map.
    If this attribute map does not include the named key, then the key is
    added and assigned the given value. Otherwise, the value previously
    associated with the named key is changed to \p value.

    It is the responsibility of the caller to use OSG::beginEditCP() and
    OSG::endEditCP() accordingly. Both fields of this container (Keys and
    Values) are edited by this method.
 */

void MetaDataAttachment::setAttribute(const std::string& key,
                                      const std::string& value)
{
    MFString& keys   = *this->MetaDataAttachmentBase::editMFKeys();
    MFString& values = *this->MetaDataAttachmentBase::editMFValues();

    unsigned int index(0);

    // Find the index of key in _mfKeys. This index will be the index of the
    // value associated with key in _mfValues.
    for ( MFString::iterator i = keys.begin(); i != keys.end(); ++i, ++index )
    {
        if ( *i == key )
        {
           values[index] = value;
           return;
        }
    }

    // key was not found in _mfKeys, so we add key to _mfKeys and value to
    // _mfValues.
    keys.push_back(key);
    values.push_back(value);
}

/*! Attempts to look up the value associated with the named key in this
    attribute map. If this attribute map does not include \p key, then
    false is returned. Otherwise, \p value is set to the value associated
    with the named key, and true is returned.
 */
 
bool MetaDataAttachment::getAttribute(const std::string& key,
                                            std::string& value)
    const
{
    if ( hasAttribute(key) )
    {
        const MFString& keys   = *this->MetaDataAttachmentBase::getMFKeys();
        const MFString& values = *this->MetaDataAttachmentBase::getMFValues();

        // Find the index of key in _mfKeys. This index will be the index of
        // the value associated with key in _mfValues.
        unsigned int index(0);
        MFString::const_iterator i;
        for ( i = keys.begin(); i != keys.end(); ++i, ++index )
        {
            if ( *i == key )
            {
                // Assign the value associated with key.
                value = values[index];
                return true;
            }
        }
    }

    // _mfKeys does not contain key.
    return false;
}

/*-------------------------------------------------------------------------*/
/*           String Attribute Map Attachment Utility Functions             */

OSG_BEGIN_NAMESPACE

/*! Gets the string-to-string attribute map associated with the given
    attachment container. If the container does not already have a
    string-to-string attribute map attached, a new one is created and
    attached as a side effect of this function. Otherwise, the existing
    string-to-string attribute map is returned. If \p container is
    NullFC, then NullFC is returned. Otherwise, the newly created and
    attached OSG::MetaDataAttachmentPtr is returned.
 */

MetaDataAttachmentPtr metaData(AttachmentContainerPtr container)
{
    if ( NullFC == container )
    {
        FFATAL(("metadata: no container?!?\n"));
        return NullFC;
    }

    MetaDataAttachmentPtr attr_map = NullFC;
    AttachmentPtr attach_ptr =
        container->findAttachment(
            MetaDataAttachment::getClassType().getGroupId());

    if ( NullFC == attach_ptr )
    {
        attr_map = MetaDataAttachment::create();
        beginEditCP(container, AttachmentContainer::AttachmentsFieldMask);
            container->addAttachment(attr_map);
        endEditCP(container, AttachmentContainer::AttachmentsFieldMask);
    }
    else
    {
        attr_map = MetaDataAttachmentPtr::dcast(attach_ptr);

        if ( NullFC == attr_map )
        {
            FFATAL(("metaData: MetaData Attachment is not castable to MetaDataAttachment?!?\n"));
            return NullFC;
        }
    }

    return attr_map;
}

OSG_END_NAMESPACE

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGMetaDataAttachment.cpp,v 1.3 2008/06/09 07:30:36 vossg Exp $";
    static Char8 cvsid_hpp       [] = OSGMETADATAATTACHMENTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGMETADATAATTACHMENTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGMETADATAATTACHMENTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

