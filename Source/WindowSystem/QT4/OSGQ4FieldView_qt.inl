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

OSG_BEGIN_NAMESPACE

inline FieldContainerPtr &
QFieldViewBase::getFieldContainer(void)
{
    return _pFieldCon;
}

inline const FieldContainerPtr &
QFieldViewBase::getFieldContainer(void) const
{
    return _pFieldCon;
}

inline UInt32
QFieldViewBase::getFieldId(void) const
{
    return _uiFieldId;
}

inline UInt32
QFieldViewBase::getAspect(void) const
{
    return _uiAspect;
}

inline Field *
QFieldViewBase::getFieldPtr(void)
{
    FieldContainer *pFCAsp = _pFieldCon.getAspectCPtr(_uiAspect);

    return pFCAsp->getField(_uiFieldId);
}

inline const Field *
QFieldViewBase::getFieldPtr(void) const
{
    FieldContainer *pFCAsp = _pFieldCon.getAspectCPtr(_uiAspect);

    return pFCAsp->getField(_uiFieldId);
}

OSG_END_NAMESPACE

#define OSGQFIELDVIEWBASE_INLINE_CVSID "@(#)$Id: OSGQ4FieldView_qt.inl,v 1.1 2006/03/10 18:30:35 a-m-z Exp $"
