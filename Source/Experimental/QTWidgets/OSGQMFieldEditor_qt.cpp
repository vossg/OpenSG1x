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

#include <OSGAddAfter.xpm>
#include <OSGAddBefore.xpm>
#include <OSGSub.xpm>
#include <OSGLeft.xpm>
#include <OSGRight.xpm>

#include <OSGQSpinBoxUInt32_qt.h>

#include <qbuttongroup.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qpixmap.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qsignalmapper.h>
#include <qtooltip.h>

OSG_USING_NAMESPACE

FieldEditorRegistrator _regDefaultMF(&QMFieldEditor::create,
                                      FieldType    ::MULTI_FIELD);

QPixmap *QMFieldEditor::_pPixmapAddAfter  = NULL;
QPixmap *QMFieldEditor::_pPixmapAddBefore = NULL;
QPixmap *QMFieldEditor::_pPixmapSub       = NULL;
QPixmap *QMFieldEditor::_pPixmapLeft      = NULL;
QPixmap *QMFieldEditor::_pPixmapRight     = NULL;

QAbstractFieldEditor *
QMFieldEditor::create(QWidget *pParent, const char *name)
{
    return new QMFieldEditor(pParent, name);
}

QMFieldEditor::QMFieldEditor(QWidget *pParent, const char *name)
    : Inherited            (pParent, name),
      _uiBeginIndex        (0            ),
      _uiEndIndex          (0            ),
      _uiNumRows           (5            ),
      _pVBox               (NULL         ),
      _pButtonBox          (NULL         ),
      _pEditorGrid         (NULL         ),
      _pButtonPrev         (NULL         ),
      _pButtonNext         (NULL         ),
      _pButtonCommit       (NULL         ),
      _pButtonRevert       (NULL         ),
      _pButtonAddAfter     (NULL         ),
      _pButtonAddBefore    (NULL         ),
      _pButtonSub          (NULL         ),
      _pValueChangedMapper (NULL         ),
      _pActionButtonGroup  (NULL         ),
      _pSelectorButtonGroup(NULL         ),
      _labels              (             ),
      _editors             (             )
{
    initStatic        ();
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
    autoEnableEditButtons  ();
    readField              ();
}

void
QMFieldEditor::setReadOnly(bool bReadOnly)
{
    Inherited::setReadOnly(bReadOnly);

    if(bReadOnly == false)
    {
        _pButtonCommit   ->show();
        _pButtonRevert   ->show();

        _pButtonAddAfter ->show();
        _pButtonAddBefore->show();
        _pButtonSub      ->show();
    }
    else
    {
        _pButtonCommit   ->hide();
        _pButtonRevert   ->hide();

        _pButtonAddAfter ->hide();
        _pButtonAddBefore->hide();
        _pButtonSub      ->hide();
    }

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

    for(UInt32 i = _uiBeginIndex; i < (_uiBeginIndex + getNumRows()); ++i)
    {
        if(i < _uiEndIndex)
        {
            strLabel.assign(TypeTraits<UInt32>::putToString(i));
            strLabel.append("."                               );

            _labels   [mapValueIndex(i)]->setText  (strLabel.c_str());
            _labels   [mapValueIndex(i)]->show     (                );
            _selectors[mapValueIndex(i)]->show     (                );
            _editors  [mapValueIndex(i)]->readField(
                getFieldContainer(), getFieldId(), i                );
            _editors  [mapValueIndex(i)]->show     (                );
        }
        else
        {
            _labels   [mapValueIndex(i)]->hide();
            _selectors[mapValueIndex(i)]->hide();
            _editors  [mapValueIndex(i)]->hide();
        }
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

        _labels [mapValueIndex(uiValueIndex)]->setText  (strLabel.c_str());
        _editors[mapValueIndex(uiValueIndex)]->readField(
            getFieldContainer(), getFieldId(), uiValueIndex      );
    }
}

void
QMFieldEditor::writeField(void)
{
    for(UInt32 i = _uiBeginIndex; i < _uiEndIndex; ++i)
    {
        _editors[mapValueIndex(i)]->writeField(
            getFieldContainer(), getFieldId(), i);
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
QMFieldEditor::slotButtonPrevClicked(void)
{
    scrollUp(_uiNumRows);
}

void
QMFieldEditor::slotButtonNextClicked(void)
{
    scrollDown(_uiNumRows);
}

void
QMFieldEditor::slotButtonCommitClicked(void)
{
    _pButtonCommit->setEnabled(false);
    _pButtonRevert->setEnabled(false);

    autoEnableScrollButtons();
    autoEnableEditButtons  ();

    writeField();
    readField ();
}

void
QMFieldEditor::slotButtonRevertClicked(void)
{
    _pButtonCommit->setEnabled(false);
    _pButtonRevert->setEnabled(false);

    autoEnableScrollButtons();
    autoEnableEditButtons  ();

    readField();
}

void
QMFieldEditor::slotButtonAddAfterClicked(void)
{
    typedef QOSGWidgetFactory::ValueEditorCF CreateFunc;

    UInt32 uiAddIndex = 0;
    bool   selection  = false;

    for(; uiAddIndex < getNumRows(); ++uiAddIndex)
    {
        if((_selectors[uiAddIndex]->isVisible() == true) &&
           (_selectors[uiAddIndex]->isChecked() == true)   )
        {
            selection = true;

            break;
        }
    }

    if(getField()->getSize() == 0)
    {
        uiAddIndex = 0;
        selection  = true;
    }

    if((selection == true) && (isValidWidgetIndex(uiAddIndex) == true))
    {
        SWARNING << "adding after: "
                 << mapWidgetIndex(uiAddIndex)     << ", i.e. before "
                 << mapWidgetIndex(uiAddIndex) + 1 << endLog;

        const DataType             &dataType = getField  ()->getContentType();
              CreateFunc            cFunc    = getFactory()->getValueEditor(
                                                                      dataType);
              QAbstractValueEditor *pEditor  = NULL;

        if((cFunc != NULL) && ((pEditor = (*cFunc)(this, "")) != NULL))
        {
            pEditor->addFieldElem(getFieldContainer(), getFieldId(),
                                  mapWidgetIndex(uiAddIndex) + 1    );
        }
    }

    scrollDown           (0);
    autoEnableEditButtons( );
}

void
QMFieldEditor::slotButtonAddBeforeClicked(void)
{
    typedef QOSGWidgetFactory::ValueEditorCF CreateFunc;

    UInt32 uiAddIndex = 0;
    bool   selection  = false;

    for(; uiAddIndex < getNumRows(); ++uiAddIndex)
    {
        if((_selectors[uiAddIndex]->isVisible() == true) &&
           (_selectors[uiAddIndex]->isChecked() == true)   )
        {
            selection = true;

            break;
        }
    }

    if(getField()->getSize() == 0)
    {
        uiAddIndex = 0;
        selection  = true;
    }

    if((selection == true) && (isValidWidgetIndex(uiAddIndex) == true))
    {
        SWARNING << "adding before: "
                 << mapWidgetIndex(uiAddIndex) << ", i.e. before "
                 << mapWidgetIndex(uiAddIndex) << endLog;

        const DataType             &dataType = getField  ()->getContentType();
              CreateFunc            cFunc    = getFactory()->getValueEditor(
                                                                      dataType);
              QAbstractValueEditor *pEditor  = NULL;

        if((cFunc != NULL) && ((pEditor = (*cFunc)(this, "")) != NULL))
        {
            pEditor->addFieldElem(getFieldContainer(), getFieldId(),
                                  mapWidgetIndex(uiAddIndex)        );
        }
    }

    scrollDown           (0);
    autoEnableEditButtons( );
}

void
QMFieldEditor::slotButtonSubClicked(void)
{
    typedef QOSGWidgetFactory::ValueEditorCF CreateFunc;

    UInt32 uiSubIndex = 0;
    bool   selection  = false;

    if(getField()->getSize() == 0)
        return;

    for(; uiSubIndex < getNumRows(); ++uiSubIndex)
    {
        if((_selectors[uiSubIndex]->isVisible() == true) &&
           (_selectors[uiSubIndex]->isChecked() == true)   )
        {
            selection = true;

            break;
        }
    }

    if((selection == true) && (isValidWidgetIndex(uiSubIndex) == true))
    {
        SWARNING << "removing at: "
                 << mapWidgetIndex(uiSubIndex) << endLog;

        const DataType             &dataType = getField  ()->getContentType();
              CreateFunc            cFunc    = getFactory()->getValueEditor(
                                                                      dataType);
              QAbstractValueEditor *pEditor  = NULL;

        if((cFunc != NULL) && ((pEditor = (*cFunc)(this, "")) != NULL))
        {
            pEditor->removeFieldElem(getFieldContainer(), getFieldId(),
                                     mapWidgetIndex(uiSubIndex)        );
        }
    }

    scrollUp             (0);
    autoEnableEditButtons( );
}

void
QMFieldEditor::slotEditorValueChanged(int editorId)
{
    _pButtonCommit   ->setEnabled(true );
    _pButtonRevert   ->setEnabled(true );

    _pButtonPrev     ->setEnabled(false);
    _pButtonNext     ->setEnabled(false);
    _pButtonAddAfter ->setEnabled(false);
    _pButtonAddBefore->setEnabled(false);
    _pButtonSub      ->setEnabled(false);

    if(isValidWidgetIndex(static_cast<UInt32>(editorId)) == true)
    {
        emit valueChanged(
            this, mapWidgetIndex(static_cast<UInt32>(editorId)));
    }
}

void
QMFieldEditor::slotActionButtonClicked(int buttonId)
{
    if(isValidWidgetIndex(static_cast<UInt32>(buttonId)) == true)
    {
        emit actionButtonClicked(
            this, mapWidgetIndex(static_cast<UInt32>(buttonId)));
    }
}

void
QMFieldEditor::slotActionButtonPressed(int buttonId)
{
    if(isValidWidgetIndex(static_cast<UInt32>(buttonId)) == true)
    {
        emit actionButtonPressed(
            this, mapWidgetIndex(static_cast<UInt32>(buttonId)));
    }
}

void
QMFieldEditor::slotActionButtonReleased(int buttonId)
{
    if(isValidWidgetIndex(static_cast<UInt32>(buttonId)) == true)
    {
        emit actionButtonReleased(
            this, mapWidgetIndex(static_cast<UInt32>(buttonId)));
    }
}

void
QMFieldEditor::slotSelectorButtonClicked(int buttonId)
{
}

void
QMFieldEditor::initStatic(void)
{
    if(_pPixmapAddAfter == NULL)
        _pPixmapAddAfter = new QPixmap(XPMAddAfter);

    if(_pPixmapAddBefore == NULL)
        _pPixmapAddBefore = new QPixmap(XPMAddBefore);

    if(_pPixmapSub == NULL)
        _pPixmapSub = new QPixmap(XPMSub);

    if(_pPixmapLeft == NULL)
        _pPixmapLeft = new QPixmap(XPMLeft);

    if(_pPixmapRight == NULL)
        _pPixmapRight = new QPixmap(XPMRight);
}

void
QMFieldEditor::createChildWidgets(void)
{
    _pVBox       = new QVBoxLayout(this, 0, 1,
                                   "QMFieldEditor::_pVBox"      );
    _pButtonBox  = new QHBoxLayout(_pVBox, 2,
                                   "QMFieldEditor::_pButtonBox" );
    _pEditorGrid = new QGridLayout(_pVBox, _uiNumRows, 3, 1,
                                   "QMFieldEditor::_pEditorGrid");

    _pButtonPrev      = new QPushButton(this, "QMFieldEditor::_pButtonUp"       );
    _pButtonNext      = new QPushButton(this, "QMFieldEditor::_pButtonDown"     );
    _pButtonCommit    = new QPushButton(this, "QMFieldEditor::_pButtonCommit"   );
    _pButtonRevert    = new QPushButton(this, "QMFieldEditor::_pButtonRevert"   );
    _pButtonAddAfter  = new QPushButton(this, "QMFieldEditor::_pButtonAddAfter" );
    _pButtonAddBefore = new QPushButton(this, "QMFieldEditor::_pButtonAddBefore");
    _pButtonSub       = new QPushButton(this, "QMFieldEditor::_pButtonSub"      );

    _pValueChangedMapper  = new QSignalMapper(
        this, "QMFieldEditor::_pValueChangedSignalMapper");
    _pActionButtonGroup   = new QButtonGroup(
        NULL, "QMFieldEditor::_pActionButtonGroup");
    _pSelectorButtonGroup = new QButtonGroup(
        NULL, "QMFieldEditor::_pSelectorButtonGroup");
}

void
QMFieldEditor::layoutChildWidgets(void)
{
    _pVBox->setStretchFactor(_pButtonBox,   1);
    _pVBox->setStretchFactor(_pEditorGrid, 10);

    _pButtonBox->addWidget(_pButtonPrev     );
    _pButtonBox->addWidget(_pButtonNext     );
    _pButtonBox->addWidget(_pButtonCommit   );
    _pButtonBox->addWidget(_pButtonRevert   );
    _pButtonBox->addWidget(_pButtonAddBefore);
    _pButtonBox->addWidget(_pButtonAddAfter );
    _pButtonBox->addWidget(_pButtonSub      );
    _pButtonBox->addWidget(new QLabel(this) );
}

void
QMFieldEditor::initSelf(void)
{
    _pButtonPrev     ->setPixmap (*_pPixmapLeft     );
    _pButtonPrev     ->setFixedSize(16, 16          );
    _pButtonNext     ->setPixmap (*_pPixmapRight    );
    _pButtonNext     ->setFixedSize(16, 16          );

    _pButtonCommit   ->setPixmap (*(getPixmapYes()) );
    _pButtonCommit   ->setFixedSize(16, 16          );
    _pButtonCommit   ->setEnabled(false             );
    _pButtonRevert   ->setPixmap (*(getPixmapNo ()) );
    _pButtonRevert   ->setFixedSize(16, 16          );
    _pButtonRevert   ->setEnabled(false             );

    _pButtonAddAfter ->setPixmap (*_pPixmapAddAfter );
    _pButtonAddAfter ->setFixedSize(16, 16          );
    _pButtonAddBefore->setPixmap (*_pPixmapAddBefore);
    _pButtonAddBefore->setFixedSize(16, 16          );
    _pButtonSub      ->setPixmap (*_pPixmapSub      );
    _pButtonSub     ->setFixedSize(16, 16           );

    _pEditorGrid->setColStretch(SelectColumn,  0);
    _pEditorGrid->setColStretch(LabelColumn,   1);
    _pEditorGrid->setColStretch(EditorColumn, 10);

    if(getReadOnly() == true)
    {
        _pButtonCommit   ->hide();
        _pButtonRevert   ->hide();

        _pButtonAddAfter ->hide();
        _pButtonAddBefore->hide();
        _pButtonSub      ->hide();
    }

    connect(_pButtonPrev,   SIGNAL(clicked                (void)),
            this,           SLOT  (slotButtonPrevClicked  (void)) );
    connect(_pButtonNext,   SIGNAL(clicked                (void)),
            this,           SLOT  (slotButtonNextClicked  (void)) );

    connect(_pButtonCommit, SIGNAL(clicked                (void)),
            this,           SLOT  (slotButtonCommitClicked(void)) );
    connect(_pButtonRevert, SIGNAL(clicked                (void)),
            this,           SLOT  (slotButtonRevertClicked(void)) );

    connect(_pButtonAddAfter,  SIGNAL(clicked                   (void)),
            this,              SLOT  (slotButtonAddAfterClicked (void)) );
    connect(_pButtonAddBefore, SIGNAL(clicked                   (void)),
            this,              SLOT  (slotButtonAddBeforeClicked(void)) );
    connect(_pButtonSub,       SIGNAL(clicked                   (void)),
            this,              SLOT  (slotButtonSubClicked      (void)) );

    connect(_pValueChangedMapper,  SIGNAL(mapped                   (int)),
            this,                  SLOT  (slotEditorValueChanged   (int)) );

    connect(_pActionButtonGroup,   SIGNAL(clicked                  (int)),
            this,                  SLOT  (slotActionButtonClicked  (int)) );
    connect(_pActionButtonGroup,   SIGNAL(pressed                  (int)),
            this,                  SLOT  (slotActionButtonPressed  (int)) );
    connect(_pActionButtonGroup,   SIGNAL(released                 (int)),
            this,                  SLOT  (slotActionButtonReleased (int)) );

    connect(_pSelectorButtonGroup, SIGNAL(clicked                  (int)),
            this,                  SLOT  (slotSelectorButtonClicked(int)) );


    QToolTip::add(_pButtonPrev,      "Previous page"            );
    QToolTip::add(_pButtonNext,      "Next page"                );
    QToolTip::add(_pButtonCommit,    "Commit changes"           );
    QToolTip::add(_pButtonRevert,    "Revert changes"           );
    QToolTip::add(_pButtonAddAfter,  "Add after selected entry" );
    QToolTip::add(_pButtonAddBefore, "Add before selected entry");
    QToolTip::add(_pButtonSub,       "Remove selected entry"    );
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

    for(UInt32 i = _uiBeginIndex; i < getNumRows(); ++i)
    {
        QLabel               *pLabel    = new QLabel      ("", this);
        QRadioButton         *pSelector = new QRadioButton("", this);
        QAbstractValueEditor *pEditor   = NULL;

        if(cFunc != NULL)
        {
            pEditor = (*cFunc)(this, "QMFieldEditor::_editors");
        }

        if(pEditor != NULL)
        {
            _editors            . push_back (pEditor                      );
            _pEditorGrid        ->addWidget (pEditor, i, EditorColumn     );
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
            SWARNING << "QMFieldEditor::createEditorWidgets: "
                     << "pEditor == NULL"
                     << endLog;
        }

        pLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

        _pSelectorButtonGroup->insert(pSelector, i);

        _labels      .push_back(pLabel                    );
        _selectors   .push_back(pSelector                 );

        _pEditorGrid->addWidget(pLabel,    i, LabelColumn );
        _pEditorGrid->addWidget(pSelector, i, SelectColumn);
    }

    autoEnableScrollButtons();
}

void
QMFieldEditor::deleteEditorWidgets(void)
{
    UInt32 uiUsedRows = _editors.size();

    for(UInt32 i = 0; i < uiUsedRows; ++i)
    {
        _pEditorGrid->remove(_labels   [i]);
        _pEditorGrid->remove(_selectors[i]);
        _pEditorGrid->remove(_editors  [i]);

        _pValueChangedMapper ->removeMappings(_editors  [i]                   );
        _pActionButtonGroup  ->remove        (_editors  [i]->getActionButton());
        _pSelectorButtonGroup->remove        (_selectors[i]                   );

        disconnect(_editors[i],          SIGNAL(valueChanged(void)),
                   _pValueChangedMapper, SLOT  (map         (void)) );

        delete _labels   [i];
        delete _selectors[i];
        delete _editors  [i];
    }

    _labels   .clear();
    _selectors.clear();
    _editors  .clear();
}

void
QMFieldEditor::scrollUp(UInt32 uiAmount)
{
    // call with uiAmount == 0, does a refresh of the editors and labels.
    if((_pButtonPrev->isEnabled() == false) && (uiAmount != 0))
        return;

    _uiBeginIndex = osgMax(static_cast<Int64>(_uiBeginIndex) -
                           static_cast<Int64>( uiAmount    ),
                           TypeTraits<Int64>::getZeroElement());
    _uiEndIndex   = osgMin(_uiBeginIndex + getNumRows(),
                           getField()->getSize()              );

    readField();

    for(UInt32 i = _uiBeginIndex; i < (_uiBeginIndex + getNumRows()); ++i)
    {
        if(i < _uiEndIndex)
        {
            _labels   [mapValueIndex(i)]->show();
            _selectors[mapValueIndex(i)]->show();
            _editors  [mapValueIndex(i)]->show();
        }
        else
        {
            _labels   [mapValueIndex(i)]->hide();
            _selectors[mapValueIndex(i)]->hide();
            _editors  [mapValueIndex(i)]->hide();
        }
    }

    autoEnableScrollButtons();
}

void
QMFieldEditor::scrollDown(UInt32 uiAmount)
{
    // call with uiAmount == 0, does a refresh of the editors and labels.
    if((_pButtonNext->isEnabled() == false) && (uiAmount != 0))
        return;

    UInt32 oldBegin = _uiBeginIndex;
    UInt32 oldEnd   = _uiEndIndex;

    _uiBeginIndex = osgMin(_uiBeginIndex + uiAmount,     getField()->getSize());
    _uiEndIndex   = osgMin(_uiBeginIndex + getNumRows(), getField()->getSize());

    if(_uiBeginIndex == _uiEndIndex)
    {
        _uiBeginIndex = oldBegin;
        _uiEndIndex   = oldEnd;
    }

    readField();

    for(UInt32 i = _uiBeginIndex; i < (_uiBeginIndex + getNumRows()); ++i)
    {
        if(i < _uiEndIndex)
        {
            _labels   [mapValueIndex(i)]->show();
            _selectors[mapValueIndex(i)]->show();
            _editors  [mapValueIndex(i)]->show();
        }
        else
        {
            _labels   [mapValueIndex(i)]->hide();
            _selectors[mapValueIndex(i)]->hide();
            _editors  [mapValueIndex(i)]->hide();
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGQMFieldEditor_qt.cpp,v 1.6 2004/08/14 18:17:01 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGQMFIELDEDITORQT_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGQMFIELDEDITORQT_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
