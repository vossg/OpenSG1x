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

inline FieldContainerPtr
QFieldContainerEditor::getFieldContainer(void) const
{
    return _fcPtr;
}

inline const QOSGWidgetFactory *
QFieldContainerEditor::getFactory(void) const
{
    return _pFactory;
}

inline QOSGWidgetFactory *
QFieldContainerEditor::getFactory(void)
{
    return _pFactory;
}

inline void
QFieldContainerEditor::setFactory(QOSGWidgetFactory *pFactory)
{
    _pFactory = pFactory;

    // TODO: recreate widgets...
}

inline const QAbstractFieldEditor *
QFieldContainerEditor::getEditor(UInt32 uiFieldId) const
{
    return _editors[uiFieldId];
}

inline QAbstractFieldEditor *
QFieldContainerEditor::getEditor(UInt32 uiFieldId)
{
    return _editors[uiFieldId];
}

inline const QAbstractValueEditor *
QFieldContainerEditor::getEditor(UInt32 uiFieldId, UInt32 uiValueIndex) const
{
    return _editors[uiFieldId]->getEditor(uiValueIndex);
}

inline QAbstractValueEditor *
QFieldContainerEditor::getEditor(UInt32 uiFieldId, UInt32 uiValueIndex)
{
    return _editors[uiFieldId]->getEditor(uiValueIndex);
}

inline bool
QFieldContainerEditor::getReadOnly(void) const
{
    return _bReadOnly;
}

inline bool
QFieldContainerEditor::getLabelsVisible(void) const
{
    return _bLabelsVisible;
}

OSG_END_NAMESPACE

#define OSGQFIELDCONTAINEREDITORQT_INLINE_CVSID "@(#)$Id: OSGQFieldContainerEditor_qt.inl,v 1.1 2004/07/30 15:31:57 neumannc Exp $"
