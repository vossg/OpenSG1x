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

#include "OSGQFieldContainerEditor_qt.h"
#include <OSGQFieldContainerPtrEditor_qt.h>
#include <OSGQAttachmentMapEditor_qt.h>
#include <OSGSField.h>
#include <OSGMField.h>
#include <OSGFieldContainer.h>
#include <OSGSFFieldContainerPtr.h>
#include <OSGMFFieldContainerPtr.h>
#include <OSGAttachmentContainerPtr.h>
#include <OSGSimpleAttachments.h>

#include <OSGLeft.xpm>
#include <OSGRight.xpm>

#include <qlabel.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtable.h>
#include <qtooltip.h>

OSG_USING_NAMESPACE

QPixmap *QFieldContainerEditor::_pPixmapLeft      = NULL;

QFieldContainerEditor::QFieldContainerEditor(
    QWidget *pParent, const char *name)

    : Inherited      (pParent, name           ),
      _fcPtr         (NullFC                  ),
      _pFactory      (QOSGWidgetFactory::the()),
      _pVBox         (NULL                    ),
      _pHBoxLabels   (NULL                    ),
      _pButtonBack   (NULL                    ),
      _pLabelFCType  (NULL                    ),
      _pLabelFCName  (NULL                    ),
      _pTable        (NULL                    ),
      _editors       (                        ),
      _bReadOnly     (true                    ),
      _bLabelsVisible(true                    ),
      _history       (                        )
{
    initStatic        ();
    createChildWidgets();
    layoutChildWidgets();
    initSelf          ();
}

QFieldContainerEditor::~QFieldContainerEditor(void)
{
}

void
QFieldContainerEditor::setFieldContainer(FieldContainerPtr fcPtr)
{
    _pButtonBack->setEnabled(!_history.empty());
    if(fcPtr == NullFC)
    {
        _pLabelFCType->setText("");
        _pLabelFCName->setText("");
        depopulateTable();
        return;
    }

    AttachmentContainerPtr pAttCon = AttachmentContainerPtr::dcast(fcPtr);

    _fcPtr = fcPtr;

    QString text;
    text.sprintf("%s (%u)", _fcPtr->getType().getCName(),
                            _fcPtr.getFieldContainerId());
    _pLabelFCType->setText(text);

    if((pAttCon != NullFC) && (getName(pAttCon) != NULL))
    {
        _pLabelFCName->setText(getName(pAttCon));
    }
    else
    {
        _pLabelFCName->setText("<unnamed>");
    }

    depopulateTable();
    populateTable  ();
}

void
QFieldContainerEditor::slotButtonBackClicked(void)
{
    if(_history.empty())
        return;

    FieldContainerPtr fcPtr = _history.top();
    _history.pop();
    setFieldContainer(fcPtr);
}

void
QFieldContainerEditor::setReadOnly(bool bReadOnly)
{
    _bReadOnly = bReadOnly;

    EditorListIt itEditors  = _editors.begin();
    EditorListIt endEditors = _editors.end  ();

    for(; itEditors != endEditors; ++itEditors)
    {
        (*itEditors)->setReadOnly(bReadOnly);
    }
}

void
QFieldContainerEditor::setLabelsVisible(bool bVisible)
{
    _bLabelsVisible = bVisible;

    EditorListIt itEditors  = _editors.begin();
    EditorListIt endEditors = _editors.end  ();

    for(; itEditors != endEditors; ++itEditors)
    {
        (*itEditors)->setLabelsVisible(bVisible);
    }
}

void
QFieldContainerEditor::slotValueChanged(
    QAbstractFieldEditor *pSender, UInt32 valueIndex)
{
    emit valueChanged(pSender->getFieldId(), valueIndex);
}

void
QFieldContainerEditor::slotGenericRequest(
    QAbstractFieldEditor *pSender, UInt32 valueIndex, QString request)
{
    SLOG << "QFieldContainerEditor::slotGenericRequest: " << request << endLog;

    if(request.startsWith("QFieldContainerPtrEditor::ShowTarget") == true)
    {
        QFieldContainerPtrEditor *pEditor = 
            dynamic_cast<QFieldContainerPtrEditor *>(pSender->getEditor(valueIndex));
        FieldContainerPtr         fcPtr   = NullFC;

        if(pEditor != NULL)
        {
            pEditor->getValue(fcPtr);
        }

        if(fcPtr != NullFC)
        {
            _history.push    (_fcPtr);
            setFieldContainer(fcPtr );
        }
    }
    else if(request.startsWith("QAttachmentMapEditor::ShowTarget:") == true)
    {
        bool                  ok      = false;
        QAttachmentMapEditor *pEditor =
            dynamic_cast<QAttachmentMapEditor *>(pSender->getEditor(valueIndex));
        FieldContainerPtr     fcPtr   = NullFC;

        UInt32 index = request.remove("QAttachmentMapEditor::ShowTarget:").toUInt(&ok);

        if((pEditor != NULL) && (ok == true))
        {
            pEditor->getEditor(index)->getValue(fcPtr);
        }

        if(fcPtr != NullFC)
        {
            _history.push    (_fcPtr);
            setFieldContainer(fcPtr );
        }
    }

    emit genericRequest(pSender->getFieldId(), valueIndex, request);
}

void
QFieldContainerEditor::populateTable(void)
{
    typedef QOSGWidgetFactory::FieldEditorCF FieldEditorCF;

    if(_fcPtr == NullFC)
        return;

    const FieldContainerType &fcType    = _fcPtr->getType         ();
          UInt32              numFields = fcType. getNumFieldDescs();

    _pTable ->setNumRows(numFields);
    _editors .resize    (numFields);

    for(UInt32 i = 1; i <= numFields; ++i)
    {
        const FieldType &fType = _fcPtr->getField(i)->getType();
        const Char8     *fName = _fcPtr->getField(i)->getType().getCName();

        FieldEditorCF    cFunc = getFactory()->getFieldEditor(
                                    fcType, fType, fName);

        if(cFunc != NULL)
        {
            _editors[i - 1] = (*cFunc)(this, "QFieldContainerEditor::_editors");
        }

        if(_editors[i - 1] != NULL)
        {
            _editors[i - 1]->setField        (_fcPtr, i         );
            _editors[i - 1]->setReadOnly     (getReadOnly     ());
            _editors[i - 1]->setLabelsVisible(getLabelsVisible());

            _pTable        ->setCellWidget   (i - 1, FieldValueCol,
                                              _editors[i - 1]      );
            connect(
                _editors[i - 1],
                SIGNAL(valueChanged      (QAbstractFieldEditor *, UInt32)),
                this,
                SLOT  (slotValueChanged  (QAbstractFieldEditor *, UInt32)) );

            connect(
                _editors[i - 1],
                SIGNAL(genericRequest    (QAbstractFieldEditor *, UInt32, QString)),
                this,
                SLOT  (slotGenericRequest(QAbstractFieldEditor *, UInt32, QString)) );
        }

        _pTable->setText  (i - 1, FieldNameCol,
                           fcType.getFieldDescription(i)->getCName());
        _pTable->adjustRow(i - 1                                    );
    }

    _pTable->adjustColumn(FieldNameCol );
}

void
QFieldContainerEditor::depopulateTable(void)
{
    _pTable ->setNumRows(0);
    _editors. clear     ( );
}

void
QFieldContainerEditor::initStatic(void)
{
    if(_pPixmapLeft == NULL)
        _pPixmapLeft = new QPixmap(XPMLeft);
}

void
QFieldContainerEditor::createChildWidgets(void)
{
    _pVBox       = new QVBoxLayout(this, 0, 1,
                                   "QFieldContainerEditor::_pVBox"      );
    _pHBoxLabels = new QHBoxLayout(NULL, 0, 2,
                                   "QFieldContainerEditor::_pHBoxLabels");

    _pButtonBack  = new QPushButton(this, "QMFieldEditor::_pButtonBack"      );
    _pLabelFCType = new QLabel(this, "QFieldContainerEditor::_pLabelFCType");
    _pLabelFCName = new QLabel(this, "QFieldContainerEditor::_pLabelFCName");

    _pTable = new QTable(this, "QFieldContainerEditor::_pTable");
}

void
QFieldContainerEditor::layoutChildWidgets(void)
{
    _pHBoxLabels->addWidget(_pButtonBack );
    _pHBoxLabels->addWidget(_pLabelFCType);
    _pHBoxLabels->addWidget(_pLabelFCName);

    _pVBox->addLayout(_pHBoxLabels);
    _pVBox->addWidget(_pTable     );
}

void
QFieldContainerEditor::initSelf(void)
{
    _pButtonBack->setPixmap (*_pPixmapLeft     );
    _pButtonBack->setFixedSize(16, 16          );

    _pTable->setReadOnly     (true               );
    _pTable->setSelectionMode(QTable::NoSelection);
    _pTable->setColumnMovingEnabled(false);
    _pTable->setRowMovingEnabled   (false);

    _pTable->setNumCols(2);
    _pTable->horizontalHeader()->setLabel(FieldNameCol,  "Field Name" );
    _pTable->horizontalHeader()->setLabel(FieldValueCol, "Field Value");
    _pTable->verticalHeader()->hide();
    _pTable->setLeftMargin(0);
    _pTable->setColumnStretchable(FieldValueCol, true);

    connect(_pButtonBack,   SIGNAL(clicked                (void)),
            this,           SLOT  (slotButtonBackClicked  (void)) );

    QToolTip::add(_pButtonBack,      "Back"            );
}


// include generated file
#include "OSGQFieldContainerEditor_qt_moc.cpp"

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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGQFieldContainerEditor_qt.cpp,v 1.6 2004/12/20 11:09:52 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGQFIELDCONTAINEREDITORQT_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGQFIELDCONTAINEREDITORQT_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
