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

#include <OSGConfig.h>

#include "OSGFCPtrAttributeMap.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::FCPtrAttributeMap
An attachment that stores a string-to-field container pointer (FCPtr) mapping of keys to values.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FCPtrAttributeMap::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FCPtrAttributeMap::FCPtrAttributeMap(void) :
    Inherited()
{
}

FCPtrAttributeMap::FCPtrAttributeMap(const FCPtrAttributeMap &source) :
    Inherited(source)
{
}

FCPtrAttributeMap::~FCPtrAttributeMap(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FCPtrAttributeMap::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void FCPtrAttributeMap::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump FCPtrAttributeMap NI" << std::endl;
}

/*! Sets the value associated with the named key in this attribute map.
    If this attribute map does not include the named key, then the key is
    added and assigned the given value. Otherwise, the value previously
    associated with the named key is changed to \p value.

    It is the responsibility of the caller to use OSG::beginEditCP() and
    OSG::endEditCP() accordingly. Both fields of this container (Keys and
    Values) are edited by this method.
 */

void FCPtrAttributeMap::setAttribute(const std::string& key,
                                     FieldContainerPtr value)
{
    MFString& keys = this->FCPtrAttributeMapBase::getKeys();
    MFFieldContainerPtr& values = this->FCPtrAttributeMapBase::getValues();

    MFString::iterator i;
    unsigned int index(0);

    // Find the index of key in _mfKeys. This index will be the index of the
    // value associated with key in _mfValues.
    for ( i = keys.begin(); i != keys.end(); ++i, ++index )
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
 
bool FCPtrAttributeMap::getAttribute(const std::string& key,
                                     FieldContainerPtr& value)
    const
{
    if ( hasAttribute(key) )
    {
        const MFString& keys = this->FCPtrAttributeMapBase::getKeys();
        const MFFieldContainerPtr& values =
            this->FCPtrAttributeMapBase::getValues();

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
/*    Field Container Pointer Attribute Map Attachment Utility Functions   */

OSG_BEGIN_NAMESPACE

/*! Gets the string-to-field container pointer (FCPtr) attribute map
    associated with the given attachment container. If the container does not
    already have a string-to-FCPtr attribute map attached, a new one is
    created and attached as a side effect of this function. Otherwise, the
    existing string-to-FCPtr attribute map is returned. If \p container is
    NullFC, then NullFC is returned. Otherwise, the newly created and
    attached OSG::FCPtrAttributeMapPtr is returned.
 */

FCPtrAttributeMapPtr fcptrAttributeMap(AttachmentContainerPtr container)
{
    if ( NullFC == container )
    {
        FFATAL(("stringAttributeMap: no container?!?\n"));
        return NullFC;
    }

    FCPtrAttributeMapPtr attr_map = NullFC;
    AttachmentPtr attach_ptr =
        container->findAttachment(FCPtrAttributeMap::getClassType().getGroupId());

    if ( NullFC == attach_ptr )
    {
        attr_map = FCPtrAttributeMap::create();
        beginEditCP(container, AttachmentContainer::AttachmentsFieldMask);
            container->addAttachment(attr_map);
        endEditCP(container, AttachmentContainer::AttachmentsFieldMask);
    }
    else
    {
        attr_map = FCPtrAttributeMapPtr::dcast(attach_ptr);

        if ( NullFC == attr_map )
        {
            FFATAL(("fcptrAttributeMap: FCPtrAttributeMap Attachment is not castable to FCPtrAttributeMap?!?\n"));
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGFCPtrAttributeMap.cpp,v 1.2 2005/09/28 03:01:44 vossg Exp $";
    static Char8 cvsid_hpp       [] = OSGFCPTRATTRIBUTEMAPBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGFCPTRATTRIBUTEMAPBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGFCPTRATTRIBUTEMAPFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

