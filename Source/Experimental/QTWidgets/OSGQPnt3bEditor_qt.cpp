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

#include "OSGQPnt3bEditor_qt.h"

#include <OSGVecFieldDataType.h>
#include <OSGQOSGWidgetFactoryHelper.h>

OSG_USING_NAMESPACE

ValueEditorRegistrator _regPnt3b( FieldDataTraits<Pnt3b>::getType(),
                                 &QPnt3bEditor          ::create    );

QAbstractValueEditor *
QPnt3bEditor::create(QWidget *pParent, const char *name)
{
    return new QPnt3bEditor(pParent, name);
}

QPnt3bEditor::QPnt3bEditor(QWidget *pParent, const char *name)
    : Inherited(pParent, name)
{
    initSelf();
}

QPnt3bEditor::~QPnt3bEditor(void)
{
}

void
QPnt3bEditor::setLabelsVisible(bool bLabels)
{
    Inherited::priv_setLabelsVisible(bLabels);
}

void
QPnt3bEditor::setReadOnly(bool bReadOnly)
{
    Inherited::priv_setReadOnly(bReadOnly);
}

void
QPnt3bEditor::readField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                        UInt32            uiValueIndex, UInt32 uiAspect  )
{
    Inherited::priv_readField(pFC, uiFieldId, uiValueIndex, uiAspect);
}

void
QPnt3bEditor::readField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                        UInt32            uiValueIndex                   )
{
    Inherited::priv_readField(pFC, uiFieldId, uiValueIndex,
                              Thread::getCurrent()->getAspect());
}

void
QPnt3bEditor::writeField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                         UInt32            uiValueIndex                   )
{
    Inherited::priv_writeField(pFC, uiFieldId, uiValueIndex);
}

void
QPnt3bEditor::slotSpinBoxChanged(void)
{
    emit valueChanged();
}

void
QPnt3bEditor::initSelf(void)
{
    connect(getSpinBox(0), SIGNAL(valueChanged      (void)),
            this,          SLOT  (slotSpinBoxChanged(void)) );
    connect(getSpinBox(1), SIGNAL(valueChanged      (void)),
            this,          SLOT  (slotSpinBoxChanged(void)) );
    connect(getSpinBox(2), SIGNAL(valueChanged      (void)),
            this,          SLOT  (slotSpinBoxChanged(void)) );
}

// include generated files
#include "OSGQPnt3bEditor_qt_moc.cpp"

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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGQPnt3bEditor_qt.cpp,v 1.1 2004/07/30 15:32:14 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGQPNT3BEDITORQT_HEADER_CVSID;
//    static Char8 cvsid_inl       [] = OSGQPNT3BEDITORQT_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
