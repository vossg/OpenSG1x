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

#include "OSGQMFieldEditor_qt.h"

#include <OSGQOSGWidgetFactory.h>
#include <OSGQOSGWidgetFactoryHelper.h>
#include <OSGQAbstractValueEditor_qt.h>
#include <OSGBaseFunctions.h>
#include <OSGFieldType.h>

#include <qbuttongroup.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qsignalmapper.h>

OSG_USING_NAMESPACE

FieldEditorRegistrator _regDefaultMF(&QMFieldEditor::create,
                                      FieldType    ::MULTI_FIELD);

QAbstractFieldEditor *
QMFieldEditor::create(QWidget *pParent, const char *name)
{
    return new QMFieldEditor(pParent, name);
}

QMFieldEditor::QMFieldEditor(QWidget *pParent, const char *name)
    : Inherited           (pParent, name),
      _uiBeginIndex       (0            ),
      _uiEndIndex         (0            ),
      _uiNumRows          (5            ),
      _pGrid              (NULL         ),
      _pButtonBox         (NULL         ),
      _pButtonUp          (NULL         ),
      _pButtonDown        (NULL         ),
      _pValueChangedMapper(NULL         ),
      _pActionButtonGroup (NULL         ),
      _labels             (             ),
      _editors            (             )
{
    createChildWidgets();
    layoutChildWidgets();
    initSelf          ();
}

QMFieldEditor::~QMFieldEditor(void)
{
    delete _pActionButtonGroup;
}

const QAbstractValueEditor *
QMFieldEditor::getEditor(UInt32 uiValueIndex) const
{
    QAbstractValueEditor *pEditor = NULL;

    if(isValidValueIndex(uiValueIndex) == true)
    {
        pEditor = _editors[mapValueIndex(uiValueIndex)];
    }

    return pEditor;
}

QAbstractValueEditor *
QMFieldEditor::getEditor(UInt32 uiValueIndex)
{
    QAbstractValueEditor *pEditor = NULL;

    if(isValidValueIndex(uiValueIndex) == true)
    {
        pEditor = _editors[mapValueIndex(uiValueIndex)];
    }

    return pEditor;
}

void
QMFieldEditor::setField(FieldContainerPtr pFC, UInt32 uiFieldId)
{
    Inherited::setField(pFC, uiFieldId);

    deleteEditorWidgets();
    createEditorWidgets();

    autoEnableScrollButtons();
    readField              ();
}

void
QMFieldEditor::setReadOnly(bool bReadOnly)
{
    Inherited::setReadOnly(bReadOnly);

    EditorListIt itEditors  = _editors.begin();
    EditorListIt endEditors = _editors.end  ();

    for(; itEditors != endEditors; ++itEditors)
    {
        (*itEditors)->setReadOnly(bReadOnly);
    }
}

void
QMFieldEditor::setLabelsVisible(bool bVisible)
{
    Inherited::setLabelsVisible(bVisible);

    EditorListIt itEditors  = _editors.begin();
    EditorListIt endEditors = _editors.end  ();

    for(; itEditors != endEditors; ++itEditors)
    {
        (*itEditors)->setLabelsVisible(bVisible);
    }
}

void
QMFieldEditor::setActionButtonsVisible(bool bVisible)
{
    Inherited::setActionButtonsVisible(bVisible);

    EditorListIt itEditors  = _editors.begin();
    EditorListIt endEditors = _editors.end  ();

    for(; itEditors != endEditors; ++itEditors)
    {
        (*itEditors)->setButtonVisible(bVisible);
    }
}

void
QMFieldEditor::readField(void)
{
    std::string strLabel;

    for(UInt32 valueIdx = _uiBeginIndex; valueIdx < _uiEndIndex; ++valueIdx)
    {
        strLabel.assign(TypeTraits<UInt32>::putToString(valueIdx));
        strLabel.append("."                                      );

        _labels [mapValueIndex(valueIdx)]->setText  (strLabel);
        _editors[mapValueIndex(valueIdx)]->readField(
            getFieldContainer(), getFieldId(), valueIdx      );
    }
}

void
QMFieldEditor::readField(UInt32 uiValueIndex)
{
    std::string strLabel;

    if(isValidValueIndex(uiValueIndex) == true)
    {
        strLabel.assign(TypeTraits<UInt32>::putToString(uiValueIndex));
        strLabel.append("."                                          );

        _labels [mapValueIndex(uiValueIndex)]->setText  (strLabel);
        _editors[mapValueIndex(uiValueIndex)]->readField(
            getFieldContainer(), getFieldId(), uiValueIndex      );
    }
}

void
QMFieldEditor::writeField(void)
{
    for(UInt32 valueIdx = _uiBeginIndex; valueIdx < _uiEndIndex; ++valueIdx)
    {
        _editors[mapValueIndex(valueIdx)]->writeField(
            getFieldContainer(), getFieldId(), valueIdx);
    }
}

void
QMFieldEditor::writeField(UInt32 uiValueIndex)
{
    if(isValidValueIndex(uiValueIndex) == true)
    {
        _editors[mapValueIndex(uiValueIndex)]->writeField(
            getFieldContainer(), getFieldId(), uiValueIndex);
    }
}

void
QMFieldEditor::keyPressEvent(QKeyEvent *pEvent)
{
    switch(pEvent->key())
    {
    case Qt::Key_Up:
        scrollUp(1);
        break;

    case Qt::Key_Down:
        scrollDown(1);
        break;

    case Qt::Key_PageUp:
        scrollUp(_uiNumRows);
        break;

    case Qt::Key_PageDown:
        scrollDown(_uiNumRows);
        break;

    default:
        pEvent->ignore();
        break;
    };
}

void
QMFieldEditor::slotButtonUpClicked(void)
{
    scrollUp(_uiNumRows);
}

void
QMFieldEditor::slotButtonDownClicked(void)
{
    scrollDown(_uiNumRows);
}

void
QMFieldEditor::slotButtonWriteClicked(void)
{
    _pButtonWrite ->setEnabled(false);
    _pButtonCancel->setEnabled(false);

    autoEnableScrollButtons();

    writeField();
}

void
QMFieldEditor::slotButtonCancelClicked(void)
{
    _pButtonWrite ->setEnabled(false);
    _pButtonCancel->setEnabled(false);

    autoEnableScrollButtons();

    readField();
}

void
QMFieldEditor::slotEditorValueChanged(int editorId)
{
    _pButtonWrite ->setEnabled(true );
    _pButtonCancel->setEnabled(true );

    _pButtonUp    ->setEnabled(false);
    _pButtonDown  ->setEnabled(false);

    if(isValidWidgetIndex(editorId) == true)
    {
        emit valueChanged(
            this, mapWidgetIndex(static_cast<UInt32>(editorId)));
    }
}

void
QMFieldEditor::slotActionButtonClicked(int buttonId)
{
    if(isValidWidgetIndex(buttonId) == true)
    {
        emit actionButtonClicked(
            this, mapWidgetIndex(static_cast<UInt32>(buttonId)));
    }
}

void
QMFieldEditor::slotActionButtonPressed(int buttonId)
{
    if(isValidWidgetIndex(buttonId) == true)
    {
        emit actionButtonPressed(
            this, mapWidgetIndex(static_cast<UInt32>(buttonId)));
    }
}

void
QMFieldEditor::slotActionButtonReleased(int buttonId)
{
    if(isValidWidgetIndex(buttonId) == true)
    {
        emit actionButtonReleased(
            this, mapWidgetIndex(static_cast<UInt32>(buttonId)));
    }
}

void
QMFieldEditor::createChildWidgets(void)
{
    _pGrid         = new QGridLayout(this, _uiNumRows, 3, 1, 0,
                                           "QMFieldEditor::_pGrid"        );
    _pButtonBox    = new QVBoxLayout(1,    "QMFieldEditor::_pButtonBox"   );
    _pButtonUp     = new QPushButton(this, "QMFieldEditor::_pButtonUp"    );
    _pButtonDown   = new QPushButton(this, "QMFieldEditor::_pButtonDown"  );
    _pButtonWrite  = new QPushButton(this, "QMFieldEditor::_pButtonWrite" );
    _pButtonCancel = new QPushButton(this, "QMFieldEditor::_pButtonCancel");

    _pValueChangedMapper = new QSignalMapper(
        this, "QMFieldEditor::_pValueChangedSignalMapper");
    _pActionButtonGroup  = new QButtonGroup(
        NULL, "QMFieldEditor::_pActionButtonGroup");
}

void
QMFieldEditor::layoutChildWidgets(void)
{
    _pButtonBox->addWidget(_pButtonUp    );
    _pButtonBox->addWidget(_pButtonDown  );
    _pButtonBox->addWidget(_pButtonWrite );
    _pButtonBox->addWidget(_pButtonCancel);

    _pGrid->addMultiCellLayout(_pButtonBox, 0, 4, 0, 0);
}

void
QMFieldEditor::initSelf(void)
{
    _pButtonUp    ->setText("Up"    );
    _pButtonDown  ->setText("Down"  );

    _pButtonWrite ->setText   ("Write" );
    _pButtonWrite ->setEnabled(false   );
    _pButtonCancel->setText   ("Cancel");
    _pButtonCancel->setEnabled(false   );

    _pGrid->setColStretch(0, 10);
    _pGrid->setColStretch(1,  1);
    _pGrid->setColStretch(2, 80);

    connect(_pButtonUp,     SIGNAL(clicked                (void)),
            this,           SLOT  (slotButtonUpClicked    (void)) );
    connect(_pButtonDown,   SIGNAL(clicked                (void)),
            this,           SLOT  (slotButtonDownClicked  (void)) );

    connect(_pButtonWrite,  SIGNAL(clicked                (void)),
            this,           SLOT  (slotButtonWriteClicked (void)) );
    connect(_pButtonCancel, SIGNAL(clicked                (void)),
            this,           SLOT  (slotButtonCancelClicked(void)) );

    connect(_pValueChangedMapper, SIGNAL(mapped                (int)),
            this,                 SLOT  (slotEditorValueChanged(int)) );

    connect(_pActionButtonGroup, SIGNAL(clicked                 (int)),
            this,                SLOT  (slotActionButtonClicked (int)) );
    connect(_pActionButtonGroup, SIGNAL(pressed                 (int)),
            this,                SLOT  (slotActionButtonPressed (int)) );
    connect(_pActionButtonGroup, SIGNAL(released                (int)),
            this,                SLOT  (slotActionButtonReleased(int)) );
}

void
QMFieldEditor::createEditorWidgets(void)
{
    typedef QOSGWidgetFactory::ValueEditorCF CreateFunc;

          Field      *pField   = this        ->getField      (        );
    const DataType   &dataType = pField      ->getContentType(        );
          CreateFunc  cFunc    = getFactory()->getValueEditor(dataType);

    _uiBeginIndex = 0;
    _uiEndIndex   = osgMin(getNumRows(), pField->getSize());

    for(UInt32 i = _uiBeginIndex; i < _uiEndIndex; ++i)
    {
        QLabel           *pLabel  = new QLabel("", this);
        QAbstractValueEditor *pEditor = NULL;

        if(cFunc != NULL)
        {
            pEditor = (*cFunc)(this, "QMFieldEditor::_editors");
        }

        if(pEditor != NULL)
        {
            _editors            . push_back (pEditor                      );
            _pGrid              ->addWidget (pEditor, i, 2                );
            _pValueChangedMapper->setMapping(pEditor, i                   );
            _pActionButtonGroup ->insert    (pEditor->getActionButton(), i);

            pEditor->setReadOnly     (getReadOnly            ());
            pEditor->setLabelsVisible(getLabelsVisible       ());
            pEditor->setButtonVisible(getActionButtonsVisible());

            connect(pEditor,              SIGNAL(valueChanged(void)),
                    _pValueChangedMapper, SLOT  (map         (void)) );
        }
        else
        {
            SWARNING << "pEditor == NULL" << endLog;
        }

        pLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

        _labels. push_back(pLabel      );
        _pGrid ->addWidget(pLabel, i, 1);
    }

    autoEnableScrollButtons();
}

void
QMFieldEditor::deleteEditorWidgets(void)
{
    EditorListIt itEditors  = _editors.begin();
    EditorListIt endEditors = _editors.end  ();

    for(; itEditors != endEditors; ++itEditors)
    {
        _pValueChangedMapper->removeMappings( *itEditors                    );
        _pActionButtonGroup ->remove        ((*itEditors)->getActionButton());
        _pGrid              ->remove        ( *itEditors                    );

        disconnect(*itEditors,           SIGNAL(valueChanged(void)),
                   _pValueChangedMapper, SLOT  (map         (void)) );

        delete *itEditors;
    }

    LabelListIt itLabels  = _labels.begin();
    LabelListIt endLabels = _labels.end  ();

    for(; itLabels != endLabels; ++itLabels)
    {
        _pGrid->remove(*itLabels);

        delete *itLabels;
    }

    _editors.clear();
    _labels .clear();
}

void
QMFieldEditor::scrollUp(UInt32 uiAmount)
{
    if(_pButtonUp->isEnabled() == false)
        return;

    _uiBeginIndex = osgMax(static_cast<Int64>(_uiBeginIndex) -
                           static_cast<Int64>( uiAmount    ),
                           TypeTraits<Int64>::getZeroElement()              );
    _uiEndIndex   = osgMin(_uiBeginIndex + _uiNumRows, getField()->getSize());

    readField();

    for(UInt32 i = _uiBeginIndex; i < (_uiBeginIndex + _uiNumRows); ++i)
    {
        if(i < _uiEndIndex)
        {
            _labels [mapValueIndex(i)]->show();
            _editors[mapValueIndex(i)]->show();
        }
        else
        {
            _labels [mapValueIndex(i)]->hide();
            _editors[mapValueIndex(i)]->hide();
        }
    }

    autoEnableScrollButtons();
}

void
QMFieldEditor::scrollDown(UInt32 uiAmount)
{
    if(_pButtonDown->isEnabled() == false)
        return;

    UInt32 oldBegin = _uiBeginIndex;
    UInt32 oldEnd   = _uiEndIndex;

    _uiBeginIndex = osgMin(_uiBeginIndex + uiAmount,   getField()->getSize());
    _uiEndIndex   = osgMin(_uiBeginIndex + _uiNumRows, getField()->getSize());

    if(_uiBeginIndex == _uiEndIndex)
    {
        _uiBeginIndex = oldBegin;
        _uiEndIndex   = oldEnd;
    }

    readField();

    for(UInt32 i = _uiBeginIndex; i < (_uiBeginIndex + _uiNumRows); ++i)
    {
        if(i < _uiEndIndex)
        {
            _labels [mapValueIndex(i)]->show();
            _editors[mapValueIndex(i)]->show();
        }
        else
        {
            _labels [mapValueIndex(i)]->hide();
            _editors[mapValueIndex(i)]->hide();
        }
    }

    autoEnableScrollButtons();
}

// include generated file
#include "OSGQMFieldEditor_qt_moc.cpp"

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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGQMFieldEditor_qt.cpp,v 1.1 2004/07/30 15:31:57 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGQMFIELDEDITORQT_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGQMFIELDEDITORQT_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
