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
QAbstractFieldEditor::getFieldContainer(void) const
{
    return _fcPtr;
}

inline UInt32
QAbstractFieldEditor::getFieldId(void) const
{
    return _uiFieldId;
}

inline const QOSGWidgetFactory *
QAbstractFieldEditor::getFactory(void) const
{
    return _pFactory;
}

inline QOSGWidgetFactory *
QAbstractFieldEditor::getFactory(void)
{
    return _pFactory;
}

inline void
QAbstractFieldEditor::setFactory(QOSGWidgetFactory *pFactory)
{
    _pFactory = pFactory;
}

inline bool
QAbstractFieldEditor::getReadOnly(void) const
{
    return _bReadOnly;
}

inline bool
QAbstractFieldEditor::getLabelsVisible(void) const
{
    return _bLabelsVisible;
}

inline bool
QAbstractFieldEditor::getActionButtonsVisible(void) const
{
    return _bActionButtonsVisible;
}

inline Field *
QAbstractFieldEditor::getField(void) const
{
    return _fcPtr->getField(_uiFieldId);
}

OSG_END_NAMESPACE

#define OSGQABSTRACTFIELDEDITORQT_INLINE_CVSID "@(#)$Id: OSGQAbstractFieldEditor_qt.inl,v 1.1 2004/07/30 15:31:57 neumannc Exp $"
