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

#include "OSGQFieldEditor_qt.h"

#include "OSGQFieldView_qt.h"

#include <qlineedit.h>
#include <qevent.h>

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGQFieldEditor_qt.cpp,v 1.2 2003/05/19 07:36:41 neumannc Exp $";
    static Char8 cvsid_hpp[] = OSGQFIELDEDITOR_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGQFIELDEDITOR_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

QFieldEditorBase::QFieldEditorBase(      QFieldViewBase *pView,
                                   const char           *name  )
    : Inherited(pView, name),
      _pView   (pView      ),
      _uiIndex (0          ),
      _bActive (false      )
{
}

QFieldEditorBase::QFieldEditorBase(UInt32          uiIndex,
                                   QFieldViewBase *pView,   const char *name)
    : Inherited(pView, name),
      _pView   (pView      ),
      _uiIndex (uiIndex    ),
      _bActive (false      )
{
}

QFieldEditorBase::~QFieldEditorBase(void)
{
}

void
QFieldEditorBase::activate(void)
{
    _bActive = true;

    show();
}

void
QFieldEditorBase::deactivate(void)
{
    hide();

    _bActive = false;
}

void
QFieldEditorBase::setIndex(UInt32 uiIndex)
{
    _uiIndex = uiIndex;
}

//
// QGenericFieldEditor
//

QGenericFieldEditor::QGenericFieldEditor(      QFieldViewBase *pView,
                                         const char           *name  )
    : Inherited(pView, name)
{
    _pLineEdit = new QLineEdit(this, "QGenericFieldEditor::_pLineEdit");

    connect(_pLineEdit, SIGNAL(returnPressed  (void)),
            this,       SLOT  (onReturnPressed(void)));

    hide();
}

QGenericFieldEditor::QGenericFieldEditor(      UInt32          uiIndex,
                                               QFieldViewBase *pView, 
                                         const char           *name    )
    : Inherited(uiIndex, pView, name)
{
    _pLineEdit = new QLineEdit(this, "QGenericFieldEditor::_pLineEdit");

    connect(_pLineEdit, SIGNAL(returnPressed  (void)),
            this,       SLOT  (onReturnPressed(void)));

    hide();
}

QGenericFieldEditor::~QGenericFieldEditor(void)
{
}

void
QGenericFieldEditor::updateField(void)
{
    // TODO: fix for MFields

    getFieldPtr()->pushValueByStr(_pLineEdit->text().latin1());

    emit fieldUpdated(getIndex());
}

void
QGenericFieldEditor::updateEditor(void)
{
    std::string strTmpVal;

    getFieldPtr()->getValueByStr(strTmpVal, getIndex());

    _pLineEdit->setText(QString(strTmpVal.c_str()));
}

void
QGenericFieldEditor::activate(void)
{
    Inherited::activate();

    updateEditor();

    _pLineEdit->setActiveWindow();
    _pLineEdit->setFocus();
}

void
QGenericFieldEditor::deactivate(void)
{
    updateField();

    Inherited::deactivate();
}

void
QGenericFieldEditor::resizeEvent(QResizeEvent *pEvent)
{
    _pLineEdit->resize(pEvent->size());
}

void
QGenericFieldEditor::onReturnPressed(void)
{
    emit editorDone();
}


#include "OSGQFieldEditor_qt_moc.cpp"
