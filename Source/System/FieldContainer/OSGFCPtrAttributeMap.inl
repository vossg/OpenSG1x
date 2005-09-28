/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#include <OSGConfig.h>

OSG_BEGIN_NAMESPACE

/*! Provides read-only access to the keys multi-field of this attribute map.
    Among other things, this can be used for iterating over the contents of
    this attribute map.
 */

inline const MFString& FCPtrAttributeMap::getKeys() const
{
    return FCPtrAttributeMapBase::getKeys();
}

/*! Queries this attribute map attachment to determine if it includes the
    named key. If it does, then true is returned. Otherwise, false is
    returned.
 */

inline bool FCPtrAttributeMap::hasAttribute(const std::string& key) const
{
    return getKeys().find(key) != getKeys().end();
}

/*! Attempts to look up the value associated with the named key in this
    attribute map. If this attribute map does not include \p key, then an
    empty string is returned. Otherwise, a copy of the value associated
    with the named key is returned.
 */
 
inline FieldContainerPtr FCPtrAttributeMap::getAttribute(const std::string& key)
    const
{
    FieldContainerPtr value;
    getAttribute(key, value);
    return value;
}

/*! Provides index access to this attribute map following the semantics of
    the STL map type. If this attribute map contains \p key, a reference to
    the value associated with that key is returned. Otherwise, \p key is
    added to this attribute map with NullFC as the value, and a reference to
    that newly added value is returned. Because NullFC is the default value
    for automatically created entries, users must be careful with this
    operator.

    It is the responsibility of the caller to use OSG::beginEditCP() and
    OSG::endEditCP() accordingly. Both fields of this container (Keys and
    Values) may be edited by this method depending on the usage. In the case
    when a key/value pair is being changed or added, the fields will be
    edited. In the case when an unknown key is used for querying a value,
    both fields will be edited. When this operator is used solely to query an
    existing key's value, then no fields will be edited.

    @see hasAttribute()
    @see setAttribute()
    @see getAttribute()
 */

inline FieldContainerPtr& FCPtrAttributeMap::operator[](const std::string& key)
{
    MFString& keys = this->FCPtrAttributeMapBase::getKeys();
    MFFieldContainerPtr& values = this->FCPtrAttributeMapBase::getValues();

    unsigned int index(0);
    MFString::iterator i;
    for ( i = keys.begin(); i != keys.end(); ++i, ++index )
    {
        if ( *i == key )
        {
            return values[index];
        }
    }

    keys.push_back(key);
    values.push_back(NullFC);

    // The value we want to return is at the end of _mfValues.
    return values[values.size() - 1];
}

OSG_END_NAMESPACE

#define OSGFCPTRATTRIBUTEMAP_INLINE_CVSID "@(#)$Id: OSGFCPtrAttributeMap.inl,v 1.2 2005/09/28 03:01:44 vossg Exp $"

