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

#include "OSGQColor3fEditor_qt.h"

#include <OSGColor.h>
#include <OSGColor3fFields.h>

#include <OSGQColorButton_qt.h>

#include <qlayout.h>
#include <qlabel.h>
#include <qcolordialog.h>

#include <OSGBaseFieldDataType.h>
#include <OSGQOSGWidgetFactoryHelper.h>

OSG_USING_NAMESPACE

ValueEditorRegistrator _regColor3f( FieldDataTraits<Color3f>::getType(),
                                   &QColor3fEditor          ::create    );

QAbstractValueEditor *
QColor3fEditor::create(QWidget *pParent, const char *name)
{
    return new QColor3fEditor(pParent, name);
}

QColor3fEditor::QColor3fEditor(QWidget *pParent, const char *name)
    : Inherited(pParent, name)
{
    createChildWidgets();
    layoutChildWidgets();
    initSelf          ();
}

QColor3fEditor::~QColor3fEditor(void)
{
}

void
QColor3fEditor::setLabelsVisible(bool bLabels)
{
    Inherited::setLabelsVisible(bLabels);

    if(bLabels == true)
    {
        _pLabels[0]->show();
        _pLabels[1]->show();
        _pLabels[2]->show();
    }
    else
    {
        _pLabels[0]->hide();
        _pLabels[1]->hide();
        _pLabels[2]->hide();
    }
}

void
QColor3fEditor::setReadOnly(bool bReadOnly)
{
    Inherited::setReadOnly(bReadOnly);

    _pSpinBoxes[0]->setReadOnly(bReadOnly);
    _pSpinBoxes[1]->setReadOnly(bReadOnly);
    _pSpinBoxes[2]->setReadOnly(bReadOnly);
}

void
QColor3fEditor::readField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                          UInt32            uiValueIndex, UInt32 uiAspect  )
{
    if(pFC->getField(uiFieldId)->getCardinality() == FieldType::SINGLE_FIELD)
    {
        const SFColor3f *pSF = dynamic_cast<const SFColor3f *>(
            pFC.getAspectCPtr(uiAspect)->getField(uiFieldId));

        for(UInt32 i = 0; i < 3; ++i)
        {
            _pSpinBoxes[i]->blockSignals(true              );
            _pSpinBoxes[i]->setValue    (pSF->getValue()[i]);
            _pSpinBoxes[i]->blockSignals(false             );
        }

        _pColorButton->setPackedColor(pSF->getValue().getRGB());
        _pColorButton->update        (                        );
    }
    else
    {
        const MFColor3f *pMF = dynamic_cast<const MFColor3f *>(
            pFC.getAspectCPtr(uiAspect)->getField(uiFieldId));

        for(UInt32 i = 0; i < 3; ++i)
        {
            _pSpinBoxes[i]->blockSignals(true                   );
            _pSpinBoxes[i]->setValue    ((*pMF)[uiValueIndex][i]);
            _pSpinBoxes[i]->blockSignals(false                  );
        }

        _pColorButton->setPackedColor((*pMF)[uiValueIndex].getRGB());
        _pColorButton->update        (                             );
    }
}

void
QColor3fEditor::readField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                          UInt32            uiValueIndex                   )
{
    readField(pFC, uiFieldId, uiValueIndex, Thread::getCurrent()->getAspect());
}

void
QColor3fEditor::writeField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                           UInt32            uiValueIndex                   )
{
    if(pFC->getField(uiFieldId)->getCardinality() == FieldType::SINGLE_FIELD)
    {
        SFColor3f *pSF =
            dynamic_cast<SFColor3f *>(pFC->getField(uiFieldId));

        pSF->getValue()[0] = _pSpinBoxes[0]->getValue();
        pSF->getValue()[1] = _pSpinBoxes[1]->getValue();
        pSF->getValue()[2] = _pSpinBoxes[2]->getValue();
    }
    else
    {
        MFColor3f *pMF =
            dynamic_cast<MFColor3f *>(pFC->getField(uiFieldId));

        (*pMF)[uiValueIndex][0] = _pSpinBoxes[0]->getValue();
        (*pMF)[uiValueIndex][1] = _pSpinBoxes[1]->getValue();
        (*pMF)[uiValueIndex][2] = _pSpinBoxes[2]->getValue();
    }
}

void
QColor3fEditor::addFieldElem(
    FieldContainerPtr pFC,          UInt32 uiFieldId,
    UInt32            uiValueIndex                   )
{
    if(pFC->getField(uiFieldId)->getCardinality() == FieldType::SINGLE_FIELD)
    {
        SWARNING << "QColor3fEditor::addFieldElem: can not add to SField."
                 << endLog;
    }
    else
    {
        MFColor3f *pMF           =
            dynamic_cast<MFColor3f *>(pFC->getField(uiFieldId));
        UInt32     uiInsertIndex = osgMin(uiValueIndex, pMF->size());

        pMF->insert(pMF->begin() + uiInsertIndex, Color3f());
    }
}

void
QColor3fEditor::removeFieldElem(
    FieldContainerPtr pFC,         UInt32 uiFieldId,
    UInt32            uiValueIndex                  )
{
    if(pFC->getField(uiFieldId)->getCardinality() == FieldType::SINGLE_FIELD)
    {
        SWARNING << "QColor3fEditor::removeFieldElem: "
                 << "can not remove from SField."
                 << endLog;
    }
    else
    {
        MFColor3f *pMF           =
            dynamic_cast<MFColor3f *>(pFC->getField(uiFieldId));
        UInt32     uiEraseIndex  = osgMin(uiValueIndex,
                                          pMF->empty() ? 0 : pMF->size() - 1);

        pMF->erase(pMF->begin() + uiEraseIndex);
    }
}

void
QColor3fEditor::slotSBValueChanged(void)
{
    Color3f tmpColor(_pSpinBoxes[0]->getValue(), _pSpinBoxes[1]->getValue(),
                     _pSpinBoxes[2]->getValue()                             );

    _pColorButton->setPackedColor(tmpColor.getRGB());
    _pColorButton->update        (                 );

    emit valueChanged(this);
}

void
QColor3fEditor::slotColorButtonClicked(void)
{
    QColor initColor(TypeTraits<UInt8>::getPortion(_pSpinBoxes[0]->getValue()),
                     TypeTraits<UInt8>::getPortion(_pSpinBoxes[1]->getValue()),
                     TypeTraits<UInt8>::getPortion(_pSpinBoxes[2]->getValue()) );
    QColor selectedColor;

    selectedColor = QColorDialog::getColor(initColor, this, "QColor3fEditor");

    if(selectedColor.isValid() == true)
    {
        _pSpinBoxes[0]->setValue(
            TypeTraits<UInt8>::getFraction(selectedColor.red  ()));
        _pSpinBoxes[1]->setValue(
            TypeTraits<UInt8>::getFraction(selectedColor.green()));
        _pSpinBoxes[2]->setValue(
            TypeTraits<UInt8>::getFraction(selectedColor.blue ()));
    }
}

void
QColor3fEditor::createChildWidgets(void)
{
    _pHBox         = new QHBoxLayout(this, 0, 2, "QColor3fEditor::_pHBox"    );

    _pLabels[0]    = new QLabel     ("R", this, "QColor3fEditor::_pLabels[0]");
    _pLabels[1]    = new QLabel     ("G", this, "QColor3fEditor::_pLabels[1]");
    _pLabels[2]    = new QLabel     ("B", this, "QColor3fEditor::_pLabels[2]");

    _pSpinBoxes[0] = new QSpinBoxReal32(this, "QColor3fEditor::_pSpinBoxes[0]");
    _pSpinBoxes[1] = new QSpinBoxReal32(this, "QColor3fEditor::_pSpinBoxes[1]");
    _pSpinBoxes[2] = new QSpinBoxReal32(this, "QColor3fEditor::_pSpinBoxes[2]");

    _pColorButton  = new QColorButton  (this, "QColor3fEditor::_pColorButton" );
}

void
QColor3fEditor::layoutChildWidgets(void)
{
    _pHBox->addWidget(_pLabels[0],              0);
    _pHBox->addWidget(_pSpinBoxes[0],          10);
    _pHBox->addWidget(_pLabels[1],              0);
    _pHBox->addWidget(_pSpinBoxes[1],          10);
    _pHBox->addWidget(_pLabels[2],              0);
    _pHBox->addWidget(_pSpinBoxes[2],          10);

    _pHBox->addWidget(_pColorButton,           10);
}

void
QColor3fEditor::initSelf(void)
{
    _pSpinBoxes[0]->setLowerBound  (0.0  );
    _pSpinBoxes[0]->setUpperBound  (1.0  );
    _pSpinBoxes[0]->setStepSize    (0.001);
    _pSpinBoxes[0]->setPageStepSize(0.1  );

    _pSpinBoxes[1]->setLowerBound  (0.0  );
    _pSpinBoxes[1]->setUpperBound  (1.0  );
    _pSpinBoxes[1]->setStepSize    (0.001);
    _pSpinBoxes[1]->setPageStepSize(0.1  );

    _pSpinBoxes[2]->setLowerBound  (0.0  );
    _pSpinBoxes[2]->setUpperBound  (1.0  );
    _pSpinBoxes[2]->setStepSize    (0.001);
    _pSpinBoxes[2]->setPageStepSize(0.1  );

    _pColorButton ->setTransparency(false);

    connect(_pSpinBoxes[0], SIGNAL(valueChanged      (void)),
            this,           SLOT  (slotSBValueChanged(void)) );
    connect(_pSpinBoxes[1], SIGNAL(valueChanged      (void)),
            this,           SLOT  (slotSBValueChanged(void)) );
    connect(_pSpinBoxes[2], SIGNAL(valueChanged      (void)),
            this,           SLOT  (slotSBValueChanged(void)) );

    connect(_pColorButton,  SIGNAL(clicked               (void)),
            this,           SLOT  (slotColorButtonClicked(void)) );
}

// include generated file
#include "OSGQColor3fEditor_qt_moc.cpp"

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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGQColor3fEditor_qt.cpp,v 1.5 2004/12/20 11:09:52 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGQCOLOR3FEDITORQT_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGQCOLOR3FEDITORQT_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
