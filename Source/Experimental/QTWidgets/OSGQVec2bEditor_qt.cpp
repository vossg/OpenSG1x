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

#include "OSGQVec2bEditor_qt.h"

#include <OSGVecFieldDataType.h>
#include <OSGQOSGWidgetFactoryHelper.h>

OSG_USING_NAMESPACE

ValueEditorRegistrator _regVec2b( FieldDataTraits<Vec2b>::getType(),
                                 &QVec2bEditor          ::create    );

QAbstractValueEditor *
QVec2bEditor::create(QWidget *pParent, const char *name)
{
    return new QVec2bEditor(pParent, name);
}

QVec2bEditor::QVec2bEditor(QWidget *pParent, const char *name)
    : Inherited(pParent, name)
{
    initSelf();
}

QVec2bEditor::~QVec2bEditor(void)
{
}

void
QVec2bEditor::setLabelsVisible(bool bLabels)
{
    Inherited::setLabelsVisibleImpl(bLabels);
}

void
QVec2bEditor::setReadOnly(bool bReadOnly)
{
    Inherited::setReadOnlyImpl(bReadOnly);
}

void
QVec2bEditor::readField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                        UInt32            uiValueIndex, UInt32 uiAspect  )
{
    Inherited::readFieldImpl(pFC, uiFieldId, uiValueIndex, uiAspect);
}

void
QVec2bEditor::readField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                        UInt32            uiValueIndex                   )
{
    Inherited::readFieldImpl(pFC, uiFieldId, uiValueIndex,
                            Thread::getCurrent()->getAspect());
}

void
QVec2bEditor::writeField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                         UInt32            uiValueIndex                   )
{
    Inherited::writeFieldImpl(pFC, uiFieldId, uiValueIndex);
}

void
QVec2bEditor::addFieldElem(FieldContainerPtr pFC,          UInt32 uiFieldId,
                           UInt32            uiValueIndex                   )
{
    Inherited::addFieldElemImpl(pFC, uiFieldId, uiValueIndex);
}

void
QVec2bEditor::removeFieldElem(FieldContainerPtr pFC,          UInt32 uiFieldId,
                              UInt32            uiValueIndex                   )
{
    Inherited::removeFieldElem(pFC, uiFieldId, uiValueIndex);
}

void
QVec2bEditor::slotSpinBoxChanged(void)
{
    emit valueChanged();
}

void
QVec2bEditor::initSelf(void)
{
    connect(getSpinBox(0), SIGNAL(valueChanged      (void)),
            this,          SLOT  (slotSpinBoxChanged(void)) );
    connect(getSpinBox(1), SIGNAL(valueChanged      (void)),
            this,          SLOT  (slotSpinBoxChanged(void)) );
}

// include generated files
#include "OSGQVec2bEditor_qt_moc.cpp"

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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGQVec2bEditor_qt.cpp,v 1.2 2004/08/06 16:16:03 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGQVEC2BEDITORQT_HEADER_CVSID;
//    static Char8 cvsid_inl       [] = OSGQVEC2BEDITORQT_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
