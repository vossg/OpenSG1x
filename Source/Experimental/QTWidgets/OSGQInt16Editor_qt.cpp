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

#include "OSGQInt16Editor_qt.h"

#include <OSGSysFieldDataType.h>
#include <OSGQOSGWidgetFactoryHelper.h>

OSG_USING_NAMESPACE

ValueEditorRegistrator _regInt16( FieldDataTraits<Int16>::getType(),
                                 &QInt16Editor          ::create    );

QAbstractValueEditor *
QInt16Editor::create(QWidget *pParent, const char *name)
{
    return new QInt16Editor(pParent, name);
}

QInt16Editor::QInt16Editor(QWidget *pParent, const char *name)
    : Inherited(pParent, name)
{
    initSelf();
}

QInt16Editor::~QInt16Editor(void)
{
}

void
QInt16Editor::setLabelsVisible(bool bLabels)
{
    Inherited::priv_setLabelsVisible(bLabels);
}

void
QInt16Editor::setReadOnly(bool bReadOnly)
{
    Inherited::priv_setReadOnly(bReadOnly);
}

void
QInt16Editor::readField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                        UInt32            uiValueIndex, UInt32 uiAspect  )
{
    Inherited::priv_readField(pFC, uiFieldId, uiValueIndex, uiAspect);
}

void
QInt16Editor::readField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                        UInt32            uiValueIndex                   )
{
    Inherited::priv_readField(pFC, uiFieldId, uiValueIndex);
}

void
QInt16Editor::writeField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                         UInt32            uiValueIndex                   )
{
    Inherited::priv_writeField(pFC, uiFieldId, uiValueIndex);
}

void
QInt16Editor::slotSpinBoxChanged(void)
{
    emit valueChanged();
}

void
QInt16Editor::initSelf(void)
{
    connect(getSpinBox(), SIGNAL(valueChanged      (void)),
            this,         SLOT  (slotSpinBoxChanged(void)) );
}

// include generated files
#include "OSGQInt16Editor_qt_moc.cpp"

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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGQInt16Editor_qt.cpp,v 1.1 2004/07/30 15:31:57 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGQINT16EDITORQT_HEADER_CVSID;
//    static Char8 cvsid_inl       [] = OSGQINT16EDITORQT_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
