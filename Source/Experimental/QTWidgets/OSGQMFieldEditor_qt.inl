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

#include <qlayout.h>
#include <qpushbutton.h>

OSG_BEGIN_NAMESPACE

inline UInt32
QMFieldEditor::getBeginIndex(void) const
{
    return _uiBeginIndex;
}

inline UInt32
QMFieldEditor::getEndIndex(void) const
{
    return _uiEndIndex;
}

inline UInt32
QMFieldEditor::getNumRows(void) const
{
    return _uiNumRows;
}

inline void
QMFieldEditor::setNumRows(UInt32 uiNumRows)
{
    _uiNumRows = uiNumRows;

    deleteEditorWidgets();
    createEditorWidgets();
}

inline bool
QMFieldEditor::isValidValueIndex(UInt32 uiValueIndex) const
{
    return ((_uiBeginIndex <= uiValueIndex) && (uiValueIndex < _uiEndIndex));
}

inline bool
QMFieldEditor::isValidWidgetIndex(UInt32 uiWidgetIndex) const
{
    return (uiWidgetIndex < _editors.size());
}

inline UInt32
QMFieldEditor::mapValueIndex(UInt32 uiValueIndex) const
{
    return uiValueIndex - _uiBeginIndex;
}

inline UInt32
QMFieldEditor::mapWidgetIndex(UInt32 uiWidgetIndex) const
{
    return _uiBeginIndex + uiWidgetIndex;
}

inline void
QMFieldEditor::autoEnableScrollButtons(void)
{
    _pButtonPrev->setEnabled(
        (_uiBeginIndex != 0                    ) ? true : false);
    _pButtonNext->setEnabled(
        (_uiEndIndex   != getField()->getSize()) ? true : false);
}

OSG_END_NAMESPACE

#define OSGQMFIELDEDITORQT_INLINE_CVSID "@(#)$Id: OSGQMFieldEditor_qt.inl,v 1.2 2004/08/06 16:16:02 neumannc Exp $"
