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

#include "OSGQFieldView_qt.h"

#include <OSGFieldContainer.h>

OSG_BEGIN_NAMESPACE

inline bool
QFieldEditorBase::getActive(void) const
{
    return _bActive;
}

inline UInt32
QFieldEditorBase::getIndex(void) const
{
    return _uiIndex;
}

inline QFieldViewBase *
QFieldEditorBase::getFieldView(void)
{
    return _pView;
}

inline const QFieldViewBase *
QFieldEditorBase::getFieldView(void) const
{
    return _pView;
}

inline Field *
QFieldEditorBase::getFieldPtr(void)
{
    FieldContainer *pFCAsp = getFieldView()->getFieldContainer().getAspectCPtr(
                                                  getFieldView()->getAspect());

    return pFCAsp->getField(getFieldView()->getFieldId());
}

inline const Field *
QFieldEditorBase::getFieldPtr(void) const
{
    FieldContainer *pFCAsp = getFieldView()->getFieldContainer().getAspectCPtr(
                                                  getFieldView()->getAspect());

    return pFCAsp->getField(getFieldView()->getFieldId());
}

OSG_END_NAMESPACE

#define OSGQFIELDEDITOR_INLINE_CVSID "@(#)$Id: OSGQFieldEditor_qt.inl,v 1.1 2003/05/07 14:03:40 neumannc Exp $"
