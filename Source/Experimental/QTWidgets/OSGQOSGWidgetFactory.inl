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

OSG_BEGIN_NAMESPACE

inline
QOSGWidgetFactory::FieldEditorMapEntry::FieldEditorMapEntry(void)

    : _fName        (NULL),
      _cfFieldEditor(NULL)
{
}

inline
QOSGWidgetFactory::FieldEditorMapEntry::FieldEditorMapEntry(
    const Char8 *fName, FieldEditorCF cFunc)

    : _fName        (fName  ),
      _cfFieldEditor(cFunc  )
{
}

inline
QOSGWidgetFactory::FieldEditorMapEntry::~FieldEditorMapEntry(void)
{
}

inline const Char8 *
QOSGWidgetFactory::FieldEditorMapEntry::getFieldName(void) const
{
    return _fName;
}

inline void
QOSGWidgetFactory::FieldEditorMapEntry::setFieldName(const Char8 *fName)
{
    _fName = fName;
}

inline QOSGWidgetFactory::FieldEditorCF
QOSGWidgetFactory::FieldEditorMapEntry::getCreateFunc(void) const
{
    return _cfFieldEditor;
}

inline void
QOSGWidgetFactory::FieldEditorMapEntry::setCreateFunc(FieldEditorCF cFunc)
{
    _cfFieldEditor = cFunc;
}

inline UInt64
QOSGWidgetFactory::getIndex(UInt32 fcTypeId, UInt32 fTypeId)
{
    UInt64 index = fcTypeId;

    index <<= 32;
    index  += fTypeId;

    return index;
}

inline UInt32
QOSGWidgetFactory::getFCTypeId(UInt64 index)
{
    return static_cast<UInt32>(index >> 32);
}

inline UInt32
QOSGWidgetFactory::getFTypeId(UInt64 index)
{
    return static_cast<UInt32>(index & 0x00000000FFFFFFFF);
}

OSG_END_NAMESPACE

#define OSGQOSGWIDGETFACTORY_INLINE_CVSID "@(#)$Id: OSGQOSGWidgetFactory.inl,v 1.1 2004/07/30 15:31:57 neumannc Exp $"
