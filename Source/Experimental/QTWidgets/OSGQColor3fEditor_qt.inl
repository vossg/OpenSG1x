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
QColor3fEditor::getValue(Color3f &color) const
{
    color[0] = _pSpinBoxes[0]->getValue();
    color[1] = _pSpinBoxes[1]->getValue();
    color[2] = _pSpinBoxes[2]->getValue();
}

inline void
QColor3fEditor::setValue(const Color3f &color)
{
    _pSpinBoxes[0]->setValue(color[0]);
    _pSpinBoxes[1]->setValue(color[1]);
    _pSpinBoxes[2]->setValue(color[2]);
}

OSG_END_NAMESPACE

#define OSGQCOLOR3FEDITORQT_INLINE_CVSID "@(#)$Id: OSGQColor3fEditor_qt.inl,v 1.1 2004/07/30 15:31:57 neumannc Exp $"
