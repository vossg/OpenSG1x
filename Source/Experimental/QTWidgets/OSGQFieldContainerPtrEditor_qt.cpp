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

#include "OSGQFieldContainerPtrEditor_qt.h"
#include <OSGQSpinBoxUInt32_qt.h>

#include <OSGFieldContainerPtr.h>
#include <OSGSField.h>
#include <OSGMField.h>
#include <OSGSFFieldContainerPtr.h>
#include <OSGMFFieldContainerPtr.h>
#include <OSGSysFieldDataType.h>
#include <OSGQOSGWidgetFactoryHelper.h>

#include <qlayout.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qstrlist.h>
#include <qpixmap.h>
#include <qtooltip.h>

#include <OSGNew.xpm>
#include <OSGTarget.xpm>

OSG_USING_NAMESPACE

QPixmap *QFieldContainerPtrEditor::_pPixmapNew    = NULL;
QPixmap *QFieldContainerPtrEditor::_pPixmapTarget = NULL;

ValueEditorRegistrator _regFCPtr( ValueEditorRegistrator  ::FCPtrEditor,
                                 &QFieldContainerPtrEditor::create      );

QStrList *QFieldContainerPtrEditor::_pTypeNames = NULL;

QAbstractValueEditor *
QFieldContainerPtrEditor::create(QWidget *pParent, const char *name)
{
    return new QFieldContainerPtrEditor(pParent, name);
}

QFieldContainerPtrEditor::QFieldContainerPtrEditor(
    QWidget *pParent, const char *name)

    : Inherited(pParent, name)
{
    initStatic();
    updateStaticTypeList();

    createChildWidgets  ();
    layoutChildWidgets  ();
    initSelf            ();
}

QFieldContainerPtrEditor::~QFieldContainerPtrEditor(void)
{
}

void
QFieldContainerPtrEditor::setLabelsVisible(bool bLabels)
{
    Inherited::setLabelsVisible(bLabels);

    if(bLabels == true)
    {
        _pLabelId  ->show();
        _pLabelType->show();
    }
    else
    {
        _pLabelId  ->hide();
        _pLabelType->hide();
    }
}

void
QFieldContainerPtrEditor::setReadOnly(bool bReadOnly)
{
    Inherited::setReadOnly(bReadOnly);

    _pSpinBoxId->setReadOnly( bReadOnly);
    _pCBoxType ->setEnabled (!bReadOnly);
    
    if(bReadOnly == true)
    {
        _pButtonCreateNew->hide();
    }
    else
    {
        _pButtonCreateNew->show();
    }
}

void
QFieldContainerPtrEditor::readField(
    FieldContainerPtr pFC,          UInt32 uiFieldId,
    UInt32            uiValueIndex, UInt32 uiAspect  )
{
    if(pFC->getField(uiFieldId)->getCardinality() == FieldType::SINGLE_FIELD)
    {
        SFFieldContainerPtr *pSF =
            reinterpret_cast<SFFieldContainerPtr *>(
                pFC.getAspectCPtr(uiAspect)->getField(uiFieldId));

        updateDisplay(pSF->getValue());
    }
    else
    {
        MFFieldContainerPtr *pMF =
            reinterpret_cast<MFFieldContainerPtr *>(
                pFC.getAspectCPtr(uiAspect)->getField(uiFieldId));

        updateDisplay((*pMF)[uiValueIndex]);
    }
}


void
QFieldContainerPtrEditor::readField(
    FieldContainerPtr pFC, UInt32 uiFieldId, UInt32 uiValueIndex)
{
    readField(pFC, uiFieldId, uiValueIndex, Thread::getCurrent()->getAspect());
}

void
QFieldContainerPtrEditor::writeField(
    FieldContainerPtr pFC,          UInt32 uiFieldId,
    UInt32            uiValueIndex                   )
{
    if(pFC->getField(uiFieldId)->getCardinality() == FieldType::SINGLE_FIELD)
    {
        SFFieldContainerPtr *pSF =
            reinterpret_cast<SFFieldContainerPtr *>(
                pFC->getField(uiFieldId));

        updateData(pSF->getValue());
    }
    else
    {
        MFFieldContainerPtr *pMF =
            reinterpret_cast<MFFieldContainerPtr *>(
                pFC->getField(uiFieldId));

        updateData((*pMF)[uiValueIndex]);
    }
}

void
QFieldContainerPtrEditor::addFieldElem(
    FieldContainerPtr pFC,          UInt32 uiFieldId,
    UInt32            uiValueIndex                   )
{
    if(pFC->getField(uiFieldId)->getCardinality() == FieldType::SINGLE_FIELD)
    {
        SWARNING << "QFieldContainerPtrEditor::addFieldElem: "
                 << "can not add to SField."
                 << endLog;
    }
    else
    {
        MFFieldContainerPtr *pMF =
            reinterpret_cast<MFFieldContainerPtr *>(
                pFC->getField(uiFieldId));
        UInt32 uiInsertIndex = osgMin(uiValueIndex, pMF->size());

        pMF->insert(pMF->begin() + uiInsertIndex, NullFC);
    }
}

void
QFieldContainerPtrEditor::removeFieldElem(
    FieldContainerPtr pFC,          UInt32 uiFieldId,
    UInt32            uiValueIndex                   )
{
    if(pFC->getField(uiFieldId)->getCardinality() == FieldType::SINGLE_FIELD)
    {
        SWARNING << "QFieldContainerPtrEditor::removeFieldElem: "
                 << "can not remove from SField."
                 << endLog;
    }
    else
    {
        MFFieldContainerPtr *pMF =
            reinterpret_cast<MFFieldContainerPtr *>(
                pFC->getField(uiFieldId));
        UInt32 uiRemoveIndex = osgMin(uiValueIndex,
                                      pMF->empty() ? 0 : pMF->size() - 1);

        pMF->erase(pMF->begin() + uiRemoveIndex);
    }
}

void
QFieldContainerPtrEditor::slotIdChanged(void)
{
    UInt32            newId    = _pSpinBoxId->getValue();
    FieldContainerPtr newFCPtr = 
        FieldContainerFactory::the()->getContainer(newId);
    
    if(newFCPtr != NullFC)
    {
        _pCBoxType->setEditText(newFCPtr->getTypeName());
    }    
    else
    {
        _pCBoxType->setEditText("NullFC");
    }

    emit valueChanged(this);
}

void
QFieldContainerPtrEditor::slotButtonCreateNewClicked(void)
{
    QString             newTypeName = _pCBoxType->currentText();
    FieldContainerPtr   newFC       = NullFC;
    FieldContainerType *pNewType    =
        FieldContainerFactory::the()->findType(newTypeName.latin1());

    if(pNewType != NULL)
    {
        newFC = pNewType->createFieldContainer();

        if(newFC != NullFC)
        {
            _pSpinBoxId->setValue(newFC.getFieldContainerId());
        }
        else
        {
            _pSpinBoxId->setValue(0);
        }
    }
}

void
QFieldContainerPtrEditor::slotButtonShowTargetClicked(void)
{
    emit genericRequest(this, "QFieldContainerPtrEditor::ShowTarget");
}

void
QFieldContainerPtrEditor::initStatic(void)
{
    if(_pPixmapNew == NULL)
        _pPixmapNew = new QPixmap(XPMNew);

    if(_pPixmapTarget == NULL)
        _pPixmapTarget = new QPixmap(XPMTarget);
}

void
QFieldContainerPtrEditor::createChildWidgets(void)
{
    _pHBox      = new QHBoxLayout   (this, 0, 2,
                    "QFieldContainerPtrEditor::_pHBox");
    _pLabelId   = new QLabel        ("Id", this,
                    "QFieldContainerPtrEditor::_pLabelId");
    _pSpinBoxId = new QSpinBoxUInt32(this, 
                    "QFieldContainerPtrEditor::_pCBoxId");
    _pLabelType = new QLabel        ("Type", this,
                    "QFieldContainerPtrEditor::_pLabelType");
    _pCBoxType  = new QComboBox     (true, this,
                    "QFieldContainerPtrEditor::_pCBoxType");
        
    _pButtonCreateNew  = new QPushButton(this, "QFieldContainerPtrEditor::_pButtonCreateNew");
    _pButtonShowTarget = new QPushButton(this, "QFieldContainerPtrEditor::_pButtonShowTarget");
}

void
QFieldContainerPtrEditor::layoutChildWidgets(void)
{
    _pButtonCreateNew ->setFixedSize(64, 16);
    _pButtonShowTarget->setFixedSize(32, 16);

    _pHBox->addWidget(_pLabelId,           0);
    _pHBox->addWidget(_pSpinBoxId,        10);
    _pHBox->addWidget(_pLabelType,         0);
    _pHBox->addWidget(_pCBoxType,          5);
    _pHBox->addWidget(_pButtonCreateNew,  10);
    _pHBox->addWidget(_pButtonShowTarget, 10);
}

void
QFieldContainerPtrEditor::initSelf(void)
{
    _pButtonCreateNew ->setPixmap (*_pPixmapNew );
    _pButtonCreateNew ->setFixedSize(16, 16     );
    
    _pButtonShowTarget ->setPixmap (*_pPixmapTarget );
    _pButtonShowTarget ->setFixedSize(16, 16        );

    connect(_pSpinBoxId, SIGNAL(valueChanged    (void           )),
            this,        SLOT  (slotIdChanged   (void           )) );
   
    connect(_pButtonCreateNew,  SIGNAL(clicked                    (void)),
            this,               SLOT  (slotButtonCreateNewClicked (void)) );
    connect(_pButtonShowTarget, SIGNAL(clicked                    (void)),
            this,               SLOT  (slotButtonShowTargetClicked(void)) );
    
    _pCBoxType->insertStrList(_pTypeNames);

    QToolTip::add(_pButtonCreateNew, "Create new FieldContainer");
    QToolTip::add(_pButtonShowTarget, "Edit FieldContainer");
}

void
QFieldContainerPtrEditor::updateStaticTypeList(void)
{
    if(_pTypeNames == NULL)
    {
        _pTypeNames = new QStrList(false);
    }

    if(_pTypeNames->count() != FieldContainerFactory::the()->getNumTypes())
    {
        _pTypeNames->clear();

        FieldContainerFactory::TypeMapIterator itTypes  = 
            FieldContainerFactory::the()->beginTypes();
        FieldContainerFactory::TypeMapIterator endTypes =
            FieldContainerFactory::the()->endTypes  ();

        for(; itTypes != endTypes; ++itTypes)
        {
            _pTypeNames->append(itTypes->second->getName().str());
        }

// TODO: is this safe ??
        _pTypeNames->append("NullFC");
        _pTypeNames->sort  (        );
    }
}

void
QFieldContainerPtrEditor::updateDisplay(FieldContainerPtr fcPtr)
{   
    if(fcPtr != NullFC)
    {
        _pSpinBoxId->blockSignals(true                        );
        _pSpinBoxId->setValue    (fcPtr .getFieldContainerId());
        _pSpinBoxId->blockSignals(false                       );

        _pCBoxType ->blockSignals(true                        );
        _pCBoxType ->setEditText (fcPtr->getTypeName()        );
        _pCBoxType ->blockSignals(false                       );
    }
    else
    {
        _pSpinBoxId->blockSignals(true    );
        _pSpinBoxId->setValue    (0       );
        _pSpinBoxId->blockSignals(false   );

        _pCBoxType ->blockSignals(true    );
        _pCBoxType ->setEditText ("NullFC");
        _pCBoxType ->blockSignals(false   );
    }
}

void
QFieldContainerPtrEditor::updateData(FieldContainerPtr &fcPtr) const
{
    fcPtr = FieldContainerFactory::the()->getContainer(_pSpinBoxId->getValue());
}

// include generated file
#include "OSGQFieldContainerPtrEditor_qt_moc.cpp"

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
    static Char8 cvsid_cpp     [] = "@(#)$Id: OSGQFieldContainerPtrEditor_qt.cpp,v 1.7 2005/01/03 15:51:44 a-m-z Exp $";
    static Char8 cvsid_hpp     [] = OSGQFIELDCONTAINERPTREDITORQT_HEADER_CVSID;
    static Char8 cvsid_inl     [] = OSGQFIELDCONTAINERPTREDITORQT_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
