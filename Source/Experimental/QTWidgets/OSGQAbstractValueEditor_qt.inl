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

#include <qpushbutton.h>

OSG_BEGIN_NAMESPACE

inline bool
QAbstractValueEditor::getLabelsVisible(void) const
{
    return _bLabelsVisible;
}

inline bool
QAbstractValueEditor::getReadOnly(void) const
{
    return _bReadOnly;
}

inline bool
QAbstractValueEditor::getButtonVisible(void) const
{
    return _pActionButton->isVisible();
}

inline void
QAbstractValueEditor::setButtonVisible(bool visible)
{
    if(visible == true)
    {
        _pActionButton->show();
    }
    else
    {
        _pActionButton->hide();
    }
}

inline const QPushButton *
QAbstractValueEditor::getActionButton(void) const
{
    return _pActionButton;
}

inline QPushButton *
QAbstractValueEditor::getActionButton(void)
{
    return _pActionButton;
}

OSG_END_NAMESPACE

#define OSGQABSTRACTVALUEEDITORQT_INLINE_CVSID "@(#)$Id: OSGQAbstractValueEditor_qt.inl,v 1.1 2004/07/30 15:31:57 neumannc Exp $"
