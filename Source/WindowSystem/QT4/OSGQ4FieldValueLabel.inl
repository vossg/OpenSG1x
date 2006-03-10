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

#include "OSGQ4FieldView_qt.h"

OSG_BEGIN_NAMESPACE

inline UInt32
QFieldValueLabelBase::getIndex(void) const
{
    return _uiIndex;
}

inline QFieldViewBase *
QFieldValueLabelBase::getFieldView(void)
{
    return _pView;
}

inline const QFieldViewBase *
QFieldValueLabelBase::getFieldView(void) const
{
    return _pView;
}

inline FieldContainerPtr &
QFieldValueLabelBase::getFieldContainer(void)
{
    return _pView->getFieldContainer();
}

inline const FieldContainerPtr &
QFieldValueLabelBase::getFieldContainer(void) const
{
    return _pView->getFieldContainer();
}

inline UInt32
QFieldValueLabelBase::getFieldId(void) const
{
    return _pView->getFieldId();
}

inline UInt32
QFieldValueLabelBase::getAspect(void) const
{
    return _pView->getAspect();
}

inline Field *
QFieldValueLabelBase::getFieldPtr(void)
{
    return _pView->getFieldPtr();
}

inline const Field *
QFieldValueLabelBase::getFieldPtr(void) const
{
    return _pView->getFieldPtr();
}

OSG_END_NAMESPACE

#define OSGQFIELDVALUELABEL_INLINE_CVSID "@(#)$Id: OSGQ4FieldValueLabel.inl,v 1.1 2006/03/10 18:30:35 a-m-z Exp $"
