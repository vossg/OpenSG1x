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

#include "OSGQUInt32Editor_qt.h"

#include <OSGSysFieldDataType.h>
#include <OSGQOSGWidgetFactoryHelper.h>

OSG_USING_NAMESPACE

ValueEditorRegistrator _regUInt32( FieldDataTraits<UInt32>::getType(),
                                  &QUInt32Editor          ::create    );

QAbstractValueEditor *
QUInt32Editor::create(QWidget *pParent, const char *name)
{
    return new QUInt32Editor(pParent, name);
}

QUInt32Editor::QUInt32Editor(QWidget *pParent, const char *name)
    : Inherited(pParent, name)
{
    initSelf();
}

QUInt32Editor::~QUInt32Editor(void)
{
}

void
QUInt32Editor::setLabelsVisible(bool bLabels)
{
    Inherited::setLabelsVisibleImpl(bLabels);
}

void
QUInt32Editor::setReadOnly(bool bReadOnly)
{
    Inherited::setReadOnlyImpl(bReadOnly);
}

void
QUInt32Editor::readField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                        UInt32            uiValueIndex, UInt32 uiAspect  )
{
    Inherited::readFieldImpl(pFC, uiFieldId, uiValueIndex, uiAspect);
}

void
QUInt32Editor::readField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                         UInt32            uiValueIndex                   )
{
    Inherited::readFieldImpl(pFC, uiFieldId, uiValueIndex);
}

void
QUInt32Editor::writeField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                          UInt32            uiValueIndex                   )
{
    Inherited::writeFieldImpl(pFC, uiFieldId, uiValueIndex);
}

void
QUInt32Editor::addFieldElem(FieldContainerPtr pFC,          UInt32 uiFieldId,
                            UInt32            uiValueIndex                   )
{
    Inherited::addFieldElemImpl(pFC, uiFieldId, uiValueIndex);
}

void
QUInt32Editor::removeFieldElem(FieldContainerPtr pFC,         UInt32 uiFieldId,
                               UInt32            uiValueIndex                  )
{
    Inherited::removeFieldElemImpl(pFC, uiFieldId, uiValueIndex);
}

void
QUInt32Editor::slotSpinBoxChanged(void)
{
    emit valueChanged();
}

void
QUInt32Editor::initSelf(void)
{
    connect(getSpinBox(), SIGNAL(valueChanged      (void)),
            this,         SLOT  (slotSpinBoxChanged(void)) );
}

// include generated files
#include "OSGQUInt32Editor_qt_moc.cpp"

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGQUInt32Editor_qt.cpp,v 1.2 2004/08/06 16:16:03 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGQUINT32EDITORQT_HEADER_CVSID;
//    static Char8 cvsid_inl       [] = OSGQUINT32EDITORQT_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
