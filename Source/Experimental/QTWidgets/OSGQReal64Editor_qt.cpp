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

#include "OSGQReal64Editor_qt.h"

#include <OSGSysFieldDataType.h>
#include <OSGQOSGWidgetFactoryHelper.h>

OSG_USING_NAMESPACE

ValueEditorRegistrator _regReal64( FieldDataTraits<Real64>::getType(),
                                  &QReal64Editor          ::create    );

QAbstractValueEditor *
QReal64Editor::create(QWidget *pParent, const char *name)
{
    return new QReal64Editor(pParent, name);
}

QReal64Editor::QReal64Editor(QWidget *pParent, const char *name)
    : Inherited  (pParent, name),
      _editHelper(this         )
{
    initSelf();
}

QReal64Editor::~QReal64Editor(void)
{
}

void
QReal64Editor::setLabelsVisible(bool bLabels)
{
    Inherited::setLabelsVisible(bLabels);
    
    _editHelper.setLabelsVisible(bLabels);
}

void
QReal64Editor::setReadOnly(bool bReadOnly)
{
    Inherited::setReadOnly(bReadOnly);
    
    _editHelper.setReadOnly(bReadOnly);
}

void
QReal64Editor::readField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                         UInt32            uiValueIndex, UInt32 uiAspect  )
{
    _editHelper.readField(pFC, uiFieldId, uiValueIndex, uiAspect);
}

void
QReal64Editor::readField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                         UInt32            uiValueIndex                   )
{
    _editHelper.readField(pFC, uiFieldId, uiValueIndex);
}

void
QReal64Editor::writeField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                          UInt32            uiValueIndex                   )
{
    _editHelper.writeField(pFC, uiFieldId, uiValueIndex);
}

void
QReal64Editor::addFieldElem(FieldContainerPtr pFC,          UInt32 uiFieldId,
                            UInt32            uiValueIndex                   )
{
    _editHelper.addFieldElem(pFC, uiFieldId, uiValueIndex);
}

void
QReal64Editor::removeFieldElem(FieldContainerPtr pFC,          UInt32 uiFieldId,
                              UInt32            uiValueIndex                   )
{
    _editHelper.removeFieldElem(pFC, uiFieldId, uiValueIndex);
}

void
QReal64Editor::slotSpinBoxChanged(void)
{
    emit valueChanged();
}

void
QReal64Editor::initSelf(void)
{
    connect(_editHelper.getSpinBox(), SIGNAL(valueChanged      (void)),
            this,                     SLOT  (slotSpinBoxChanged(void)) );
}

// include generated files
#include "OSGQReal64Editor_qt_moc.cpp"

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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGQReal64Editor_qt.cpp,v 1.3 2004/11/01 12:24:29 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGQREAL64EDITORQT_HEADER_CVSID;
//    static Char8 cvsid_inl       [] = OSGQREAL64EDITORQT_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
