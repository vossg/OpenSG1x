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

#include <OSGFieldContainerPtr.h>
#include <OSGSField.h>
#include <OSGMField.h>
#include <OSGSysFieldDataType.h>
#include <OSGQOSGWidgetFactoryHelper.h>

#include <qlayout.h>
#include <qlabel.h>
#include <qlineedit.h>

OSG_USING_NAMESPACE

ValueEditorRegistrator _regFCPtr( ValueEditorRegistrator  ::FCPtrEditor,
                                 &QFieldContainerPtrEditor::create      );

QAbstractValueEditor *
QFieldContainerPtrEditor::create(QWidget *pParent, const char *name)
{
    return new QFieldContainerPtrEditor(pParent, name);
}

QFieldContainerPtrEditor::QFieldContainerPtrEditor(
    QWidget *pParent, const char *name)

    : Inherited(pParent, name)
{
    createChildWidgets();
    layoutChildWidgets();
    initSelf          ();
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
        _pLabelId     ->show();
        _pLabelBasePtr->show();
    }
    else
    {
        _pLabelId     ->hide();
        _pLabelBasePtr->hide();
    }
}

void
QFieldContainerPtrEditor::setReadOnly(bool bReadOnly)
{
    Inherited::setReadOnly(bReadOnly);

    _pLineEditId->setReadOnly(bReadOnly);
}

void
QFieldContainerPtrEditor::readField(
    FieldContainerPtr pFC,          UInt32 uiFieldId,
    UInt32            uiValueIndex, UInt32 uiAspect  )
{
    std::string strBasePtr;

    if(pFC->getField(uiFieldId)->getCardinality() == FieldType::SINGLE_FIELD)
    {
        SField<FieldContainerPtr> *pSF =
            reinterpret_cast<SField<FieldContainerPtr> *>(
                pFC.getAspectCPtr(uiAspect)->getField(uiFieldId));

        if(pSF->getValue() == NullFC)
        {
            _pLineEditId->blockSignals(true    );
            _pLineEditId->setText     ("NullFC");
            _pLineEditId->blockSignals(false   );

            _pLabelBasePtrValue->setText("0x0");
        }
        else
        {
            _pLineEditId->blockSignals(true );
            _pLineEditId->setText(
                TypeTraits<UInt32>::putToString(
                    pSF->getValue().getFieldContainerId()).c_str());
            _pLineEditId->blockSignals(false);

            FieldDataTraits<void *>::putToString(
                pSF->getValue().getBaseCPtr(), strBasePtr);

            _pLabelBasePtrValue->setText(strBasePtr.c_str());
        }
    }
    else
    {
        MField<FieldContainerPtr> *pMF =
            reinterpret_cast<MField<FieldContainerPtr> *>(
                pFC.getAspectCPtr(uiAspect)->getField(uiFieldId));

        if((*pMF)[uiValueIndex] == NullFC)
        {
            _pLineEditId->blockSignals(true    );
            _pLineEditId->setText     ("NullFC");
            _pLineEditId->blockSignals(false   );

            _pLabelBasePtrValue->setText("0x0");
        }
        else
        {
            _pLineEditId->blockSignals(true );
            _pLineEditId->setText(
                TypeTraits<UInt32>::putToString(
                    (*pMF)[uiValueIndex].getFieldContainerId()).c_str());
            _pLineEditId->blockSignals(false);

            FieldDataTraits<void *>::putToString(
                (*pMF)[uiValueIndex].getBaseCPtr(), strBasePtr);

            _pLabelBasePtrValue->setText(strBasePtr.c_str());
        }
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
    UInt32  uiContId =
        TypeTraits<UInt32>::getFromString(_pLineEditId->text().latin1());

    if(pFC->getField(uiFieldId)->getCardinality() == FieldType::SINGLE_FIELD)
    {
        SField<FieldContainerPtr> *pSF =
            reinterpret_cast<SField<FieldContainerPtr> *>(
                pFC->getField(uiFieldId));

        pSF->getValue() = FieldContainerFactory::the()->getContainer(uiContId);
    }
    else
    {
        MField<FieldContainerPtr> *pMF =
            reinterpret_cast<MField<FieldContainerPtr> *>(
                pFC->getField(uiFieldId));

        (*pMF)[uiValueIndex] =
            FieldContainerFactory::the()->getContainer(uiContId);
    }
}

void
QFieldContainerPtrEditor::slotIdChanged(void)
{
    Char8            *szBasePtrBuffer;
    UInt32            uiContId =
        TypeTraits<UInt32>::getFromString(_pLineEditId->text().latin1());

    FieldContainerPtr pCont    =
        FieldContainerFactory::the()->getContainer(uiContId);

    if(pCont != NullFC)
    {
        asprintf(&szBasePtrBuffer, "%p", pCont.getBaseCPtr());

        _pLabelBasePtrValue->setText(szBasePtrBuffer);

        free(szBasePtrBuffer);
    }
    else
    {
        _pLineEditId       ->setText("0"         );
        _pLabelBasePtrValue->setText("NULL (0x0)");
    }

    emit valueChanged();
}

void
QFieldContainerPtrEditor::createChildWidgets(void)
{
    _pHBox              = new QHBoxLayout(this, 0, 1,
                              "QFieldContainerPtrEditor::_pHBox");

    _pLabelId           = new QLabel     ("Id", this,
                              "QFieldContainerPtrEditor::_pLabelId");
    _pLineEditId        = new QLineEdit  ("", this,
                              "QFieldContainerPtrEditor::_pLineEditId");

    _pLabelBasePtr      = new QLabel     ("Base Ptr ", this,
                              "QFieldContainerPtrEditor::_pLabelBasePtr");
    _pLabelBasePtrValue = new QLabel     ("", this,
                              "QFieldContainerPtrEditor::_pLineEditBasePtr");
}

void
QFieldContainerPtrEditor::layoutChildWidgets(void)
{
    _pHBox->addWidget(_pLabelId,                     0);
    _pHBox->addWidget(_pLineEditId,                 10);
    _pHBox->addWidget(_pLabelBasePtr,                0);
    _pHBox->addWidget(_pLabelBasePtrValue,          10);
    _pHBox->addWidget(this->getActionButton(),      10);
}

void
QFieldContainerPtrEditor::initSelf(void)
{
    connect(_pLineEditId, SIGNAL(returnPressed(void)),
            this,         SLOT  (slotIdChanged(void)) );
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
    static Char8 cvsid_cpp     [] = "@(#)$Id: OSGQFieldContainerPtrEditor_qt.cpp,v 1.1 2004/07/30 15:31:57 neumannc Exp $";
    static Char8 cvsid_hpp     [] = OSGQFIELDCONTAINERPTREDITORQT_HEADER_CVSID;
    static Char8 cvsid_inl     [] = OSGQFIELDCONTAINERPTREDITORQT_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
