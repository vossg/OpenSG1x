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

#include "OSGQPnt4fEditor_qt.h"

#include <OSGVecFieldDataType.h>
#include <OSGQOSGWidgetFactoryHelper.h>

OSG_USING_NAMESPACE

ValueEditorRegistrator _regPnt4f( FieldDataTraits<Pnt4f>::getType(),
                                 &QPnt4fEditor          ::create    );

QAbstractValueEditor *
QPnt4fEditor::create(QWidget *pParent, const char *name)
{
    return new QPnt4fEditor(pParent, name);
}

QPnt4fEditor::QPnt4fEditor(QWidget *pParent, const char *name)
    : Inherited(pParent, name)
{
    initSelf();
}

QPnt4fEditor::~QPnt4fEditor(void)
{
}

void
QPnt4fEditor::setLabelsVisible(bool bLabels)
{
    Inherited::setLabelsVisibleImpl(bLabels);
}

void
QPnt4fEditor::setReadOnly(bool bReadOnly)
{
    Inherited::setReadOnlyImpl(bReadOnly);
}

void
QPnt4fEditor::readField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                        UInt32            uiValueIndex, UInt32 uiAspect  )
{
    Inherited::readFieldImpl(pFC, uiFieldId, uiValueIndex, uiAspect);
}

void
QPnt4fEditor::readField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                        UInt32            uiValueIndex                   )
{
    Inherited::readFieldImpl(pFC, uiFieldId, uiValueIndex,
                             Thread::getCurrent()->getAspect());
}

void
QPnt4fEditor::writeField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                         UInt32            uiValueIndex                   )
{
    Inherited::writeFieldImpl(pFC, uiFieldId, uiValueIndex);
}

void
QPnt4fEditor::addFieldElem(FieldContainerPtr pFC,          UInt32 uiFieldId,
                           UInt32            uiValueIndex                   )
{
    Inherited::addFieldElemImpl(pFC, uiFieldId, uiValueIndex);
}

void
QPnt4fEditor::removeFieldElem(FieldContainerPtr pFC,          UInt32 uiFieldId,
                              UInt32            uiValueIndex                   )
{
    Inherited::removeFieldElem(pFC, uiFieldId, uiValueIndex);
}

void
QPnt4fEditor::slotSpinBoxChanged(void)
{
    emit valueChanged();
}

void
QPnt4fEditor::initSelf(void)
{
    connect(getSpinBox(0), SIGNAL(valueChanged      (void)),
            this,          SLOT  (slotSpinBoxChanged(void)) );
    connect(getSpinBox(1), SIGNAL(valueChanged      (void)),
            this,          SLOT  (slotSpinBoxChanged(void)) );
    connect(getSpinBox(2), SIGNAL(valueChanged      (void)),
            this,          SLOT  (slotSpinBoxChanged(void)) );
    connect(getSpinBox(3), SIGNAL(valueChanged      (void)),
            this,          SLOT  (slotSpinBoxChanged(void)) );
}

// include generated files
#include "OSGQPnt4fEditor_qt_moc.cpp"

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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGQPnt4fEditor_qt.cpp,v 1.2 2004/08/06 16:16:03 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGQPNT4FEDITORQT_HEADER_CVSID;
//    static Char8 cvsid_inl       [] = OSGQPNT4FEDITORQT_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
