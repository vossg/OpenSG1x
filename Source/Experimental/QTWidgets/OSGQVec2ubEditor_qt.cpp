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

#include "OSGQVec2ubEditor_qt.h"

#include <OSGVecFieldDataType.h>
#include <OSGQOSGWidgetFactoryHelper.h>

OSG_USING_NAMESPACE

ValueEditorRegistrator _regVec2ub( FieldDataTraits<Vec2ub>::getType(),
                                  &QVec2ubEditor          ::create    );

QAbstractValueEditor *
QVec2ubEditor::create(QWidget *pParent, const char *name)
{
    return new QVec2ubEditor(pParent, name);
}

QVec2ubEditor::QVec2ubEditor(QWidget *pParent, const char *name)
    : Inherited(pParent, name)
{
    initSelf();
}

QVec2ubEditor::~QVec2ubEditor(void)
{
}

void
QVec2ubEditor::setLabelsVisible(bool bLabels)
{
    Inherited::priv_setLabelsVisible(bLabels);
}

void
QVec2ubEditor::setReadOnly(bool bReadOnly)
{
    Inherited::priv_setReadOnly(bReadOnly);
}

void
QVec2ubEditor::readField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                         UInt32            uiValueIndex, UInt32 uiAspect  )
{
    Inherited::priv_readField(pFC, uiFieldId, uiValueIndex, uiAspect);
}

void
QVec2ubEditor::readField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                         UInt32            uiValueIndex                   )
{
    Inherited::priv_readField(pFC, uiFieldId, uiValueIndex);
}

void
QVec2ubEditor::writeField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                          UInt32            uiValueIndex                   )
{
    Inherited::priv_writeField(pFC, uiFieldId, uiValueIndex);
}

void
QVec2ubEditor::slotSpinBoxChanged(void)
{
    emit valueChanged();
}

void
QVec2ubEditor::initSelf(void)
{
    connect(getSpinBox(0), SIGNAL(valueChanged      (void)),
            this,          SLOT  (slotSpinBoxChanged(void)) );
    connect(getSpinBox(1), SIGNAL(valueChanged      (void)),
            this,          SLOT  (slotSpinBoxChanged(void)) );
}

// include generated files
#include "OSGQVec2ubEditor_qt_moc.cpp"

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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGQVec2ubEditor_qt.cpp,v 1.1 2004/07/30 15:32:15 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGQVEC2UBEDITORQT_HEADER_CVSID;
//    static Char8 cvsid_inl       [] = OSGQVEC2UBEDITORQT_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
