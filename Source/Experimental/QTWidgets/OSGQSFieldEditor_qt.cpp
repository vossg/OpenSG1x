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

#include "OSGQSFieldEditor_qt.h"

#include <OSGQOSGWidgetFactory.h>
#include <OSGQOSGWidgetFactoryHelper.h>
#include <OSGQAbstractValueEditor_qt.h>
#include <OSGFieldType.h>

#include <qlayout.h>
#include <qpushbutton.h>

OSG_USING_NAMESPACE

FieldEditorRegistrator _regDefaultSF(&QSFieldEditor::create,
                                      FieldType    ::SINGLE_FIELD);

QAbstractFieldEditor *
QSFieldEditor::create(QWidget *pParent, const char *name)
{
    return new QSFieldEditor(pParent, name);
}

QSFieldEditor::QSFieldEditor(QWidget *pParent, const char *name)
    : Inherited(pParent, name),
      _pHBox        (NULL         ),
      _pButtonCommit(NULL         ),
      _pButtonRevert(NULL         ),
      _pEditor      (NULL         )
{
    createChildWidgets();
    layoutChildWidgets();
    initSelf          ();
}

QSFieldEditor::~QSFieldEditor(void)
{
}

const QAbstractValueEditor *
QSFieldEditor::getEditor(UInt32 uiValueIndex) const
{
    return _pEditor;
}

QAbstractValueEditor *
QSFieldEditor::getEditor(UInt32 uiValueIndex)
{
    return _pEditor;
}

void
QSFieldEditor::setField(FieldContainerPtr fcPtr, UInt32 uiFieldId)
{
    Inherited::setField(fcPtr, uiFieldId);

    typedef QOSGWidgetFactory::ValueEditorCF EditorCF;

          Field    *pField     = this  ->getField      ();
    const DataType &dataType   = pField->getContentType();

    if(_pEditor != NULL)
    {
        disconnect(_pEditor->getActionButton(), 0, this, 0);

        _pHBox->remove(_pEditor);

        delete _pEditor;
    }

    EditorCF cFunc = getFactory()->getValueEditor(dataType);

    if(cFunc != NULL)
    {
        _pEditor = (*cFunc)(this, "QSFieldEditor::_pEditor");
    }

    if(_pEditor != NULL)
    {
        _pEditor->setReadOnly     (getReadOnly            ());
        _pEditor->setButtonVisible(getActionButtonsVisible());

        connect(_pEditor, SIGNAL(valueChanged          (void)),
                this,     SLOT  (slotEditorValueChanged(void)) );

        connect(_pEditor->getActionButton(),
                SIGNAL(clicked                 (void)),
                this,
                SLOT  (slotActionButtonClicked (void)) );
        connect(_pEditor->getActionButton(),
                SIGNAL(pressed                 (void)),
                this,
                SLOT  (slotActionButtonPressed (void)) );
        connect(_pEditor->getActionButton(),
                SIGNAL(released                (void)),
                this,
                SLOT  (slotActionButtonReleased(void)) );

        _pHBox->addWidget(_pEditor, 10);
        this  ->readField(            );
    }
}

void
QSFieldEditor::setReadOnly(bool bReadOnly)
{
    Inherited::setReadOnly(bReadOnly);

    if(bReadOnly == false)
    {
        _pButtonCommit->show();
        _pButtonRevert->show();
    }
    else
    {
        _pButtonCommit->hide();
        _pButtonRevert->hide();
    }

    if(_pEditor != NULL)
    {
        _pEditor->setReadOnly(bReadOnly);
    }
}

void
QSFieldEditor::setLabelsVisible(bool bVisible)
{
    Inherited::setLabelsVisible(bVisible);

    if(_pEditor != NULL)
    {
        _pEditor->setLabelsVisible(bVisible);
    }
}

void
QSFieldEditor::setActionButtonsVisible(bool bVisible)
{
    Inherited::setActionButtonsVisible(bVisible);

    if(_pEditor != NULL)
    {
        _pEditor->setButtonVisible(bVisible);
    }
}

void
QSFieldEditor::readField(void)
{
    _pEditor->readField(getFieldContainer(), getFieldId(), 0);
}

void
QSFieldEditor::readField(UInt32 uiValueIndex)
{
    _pEditor->readField(getFieldContainer(), getFieldId(), uiValueIndex);
}

void
QSFieldEditor::writeField(void)
{
    _pEditor->writeField(getFieldContainer(), getFieldId(), 0);
}

void
QSFieldEditor::writeField(UInt32 uiValueIndex)
{
    _pEditor->writeField(getFieldContainer(), getFieldId(), uiValueIndex);
}

void
QSFieldEditor::slotEditorValueChanged(void)
{
    _pButtonCommit->setEnabled(true);
    _pButtonRevert->setEnabled(true);

    emit valueChanged(this, 0);
}

void
QSFieldEditor::slotButtonCommitClicked(void)
{
    _pButtonCommit->setEnabled(false);
    _pButtonRevert->setEnabled(false);

    writeField();
    readField ();
}

void
QSFieldEditor::slotButtonRevertClicked(void)
{
    _pButtonCommit->setEnabled(false);
    _pButtonRevert->setEnabled(false);

    readField();
}

void
QSFieldEditor::slotActionButtonClicked(void)
{
    emit actionButtonClicked(this, 0);
}

void
QSFieldEditor::slotActionButtonPressed(void)
{
    emit actionButtonPressed(this, 0);
}

void
QSFieldEditor::slotActionButtonReleased(void)
{
    emit actionButtonReleased(this, 0);
}

void
QSFieldEditor::createChildWidgets(void)
{
    _pHBox = new QHBoxLayout(this, 0, 1, "QSFieldEditor::_pHBox");

    _pButtonCommit = new QPushButton(this, "QSFieldEditor::_pButtonCommit");
    _pButtonRevert = new QPushButton(this, "QSFieldEditor::_pButtonRevert");
}

void
QSFieldEditor::layoutChildWidgets(void)
{
    _pHBox->addWidget(_pButtonCommit, 1);
    _pHBox->addWidget(_pButtonRevert, 1);
}

void
QSFieldEditor::initSelf(void)
{
    _pButtonCommit->setPixmap (*(getPixmapYes()));
    _pButtonCommit->setEnabled(false            );
    _pButtonRevert->setPixmap (*(getPixmapNo ()));
    _pButtonRevert->setEnabled(false            );

    if(getReadOnly() == true)
    {
        _pButtonCommit->hide();
        _pButtonRevert->hide();
    }

    connect(_pButtonCommit, SIGNAL(clicked                (void)),
            this,           SLOT  (slotButtonCommitClicked(void)) );
    connect(_pButtonRevert, SIGNAL(clicked                (void)),
            this,           SLOT  (slotButtonRevertClicked(void)) );
}

// include generated file
#include "OSGQSFieldEditor_qt_moc.cpp"

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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGQSFieldEditor_qt.cpp,v 1.3 2004/08/13 12:33:06 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGQSFIELDEDITORQT_HEADER_CVSID;
//    static Char8 cvsid_inl       [] = OSGQSFIELDEDITORQT_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif

