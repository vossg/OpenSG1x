
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

inline void
QAttachmentMapEditor::getValue(AttachmentMap &attMap) const
{
    updateData(attMap);
}

inline void
QAttachmentMapEditor::setValue(const AttachmentMap &attMap)
{
    updateDisplay(attMap);
}

inline const QFieldContainerPtrEditor *
QAttachmentMapEditor::getEditor(UInt32 index) const
{
    return _attachmentEditors[index];
}

inline QFieldContainerPtrEditor *
QAttachmentMapEditor::getEditor(UInt32 index)
{
    return _attachmentEditors[index];
}

OSG_END_NAMESPACE

#define OSGQATTACHMENTMAPEDITORQT_INLINE_CVSID "@(#)$Id: OSGQAttachmentMapEditor_qt.inl,v 1.1 2004/12/20 11:09:52 neumannc Exp $"
