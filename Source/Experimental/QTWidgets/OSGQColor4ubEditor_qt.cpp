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

#include "OSGQColor4ubEditor_qt.h"

#include <OSGColor.h>
#include <OSGColor4ubFields.h>

#include <OSGQColorButton_qt.h>

#include <qlayout.h>
#include <qlabel.h>
#include <qcolordialog.h>

#include <OSGBaseFieldDataType.h>
#include <OSGQOSGWidgetFactoryHelper.h>

OSG_USING_NAMESPACE

ValueEditorRegistrator _regColor4ub( FieldDataTraits<Color4ub>::getType(),
                                    &QColor4ubEditor          ::create    );

QAbstractValueEditor *
QColor4ubEditor::create(QWidget *pParent, const char *name)
{
    return new QColor4ubEditor(pParent, name);
}

QColor4ubEditor::QColor4ubEditor(QWidget *pParent, const char *name)
    : Inherited(pParent, name)
{
    createChildWidgets();
    layoutChildWidgets();
    initSelf          ();
}

QColor4ubEditor::~QColor4ubEditor(void)
{
}

void
QColor4ubEditor::setLabelsVisible(bool bLabels)
{
    Inherited::setLabelsVisible(bLabels);

    if(bLabels == true)
    {
        _pLabels[0]->show();
        _pLabels[1]->show();
        _pLabels[2]->show();
        _pLabels[3]->show();
    }
    else
    {
        _pLabels[0]->hide();
        _pLabels[1]->hide();
        _pLabels[2]->hide();
        _pLabels[3]->hide();
    }
}

void
QColor4ubEditor::setReadOnly(bool bReadOnly)
{
    Inherited::setReadOnly(bReadOnly);

    _pSpinBoxes[0]->setReadOnly(bReadOnly);
    _pSpinBoxes[1]->setReadOnly(bReadOnly);
    _pSpinBoxes[2]->setReadOnly(bReadOnly);
    _pSpinBoxes[3]->setReadOnly(bReadOnly);
}

void
QColor4ubEditor::readField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                           UInt32            uiValueIndex, UInt32 uiAspect  )
{
    if(pFC->getField(uiFieldId)->getCardinality() == FieldType::SINGLE_FIELD)
    {
        const SFColor4ub *pSF = dynamic_cast<const SFColor4ub *>(
            pFC.getAspectCPtr(uiAspect)->getField(uiFieldId));

        for(UInt32 i = 0; i < 4; ++i)
        {
            _pSpinBoxes[i]->blockSignals(true              );
            _pSpinBoxes[i]->setValue    (pSF->getValue()[i]);
            _pSpinBoxes[i]->blockSignals(false             );
        }
    }
    else
    {
        const MFColor4ub *pMF = dynamic_cast<const MFColor4ub *>(
            pFC.getAspectCPtr(uiAspect)->getField(uiFieldId));

        for(UInt32 i = 0; i < 4; ++i)
        {
            _pSpinBoxes[i]->blockSignals(true                   );
            _pSpinBoxes[i]->setValue    ((*pMF)[uiValueIndex][i]);
            _pSpinBoxes[i]->blockSignals(false                  );
        }
    }
}

void
QColor4ubEditor::readField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                           UInt32            uiValueIndex                   )
{
    readField(pFC, uiFieldId, uiValueIndex, Thread::getCurrent()->getAspect());
}

void
QColor4ubEditor::writeField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                            UInt32            uiValueIndex                   )
{
    if(pFC->getField(uiFieldId)->getCardinality() == FieldType::SINGLE_FIELD)
    {
        SFColor4ub *pSF =
            dynamic_cast<SFColor4ub *>(pFC->getField(uiFieldId));

        pSF->getValue()[0] = _pSpinBoxes[0]->getValue();
        pSF->getValue()[1] = _pSpinBoxes[1]->getValue();
        pSF->getValue()[2] = _pSpinBoxes[2]->getValue();
        pSF->getValue()[3] = _pSpinBoxes[3]->getValue();
    }
    else
    {
        MFColor4ub *pMF =
            dynamic_cast<MFColor4ub *>(pFC->getField(uiFieldId));

        (*pMF)[uiValueIndex][0] = _pSpinBoxes[0]->getValue();
        (*pMF)[uiValueIndex][1] = _pSpinBoxes[1]->getValue();
        (*pMF)[uiValueIndex][2] = _pSpinBoxes[2]->getValue();
        (*pMF)[uiValueIndex][3] = _pSpinBoxes[3]->getValue();
    }
}

void
QColor4ubEditor::slotSBValueChanged(void)
{
    Color4ub tmpColor(_pSpinBoxes[0]->getValue(), _pSpinBoxes[1]->getValue(),
                      _pSpinBoxes[2]->getValue(), _pSpinBoxes[3]->getValue() );

    _pColorButton->setPackedColor(tmpColor.getRGBA());
    _pColorButton->update        (                  );

    emit valueChanged();
}

void
QColor4ubEditor::slotColorButtonClicked(void)
{
    bool valid         = false;
    QRgb initColor     = _pColorButton->getPackedColor();
    QRgb selectedColor;

    selectedColor = QColorDialog::getRgba(initColor, &valid,
                                          this,      "QColor4ubEditor");

    if(valid == true)
    {
        _pSpinBoxes[0]->setValue((selectedColor & 0x000000FF) >> 0 );
        _pSpinBoxes[1]->setValue((selectedColor & 0x0000FF00) >> 8 );
        _pSpinBoxes[2]->setValue((selectedColor & 0x00FF0000) >> 16);
        _pSpinBoxes[3]->setValue((selectedColor & 0xFF000000) >> 24);
    }
}

void
QColor4ubEditor::createChildWidgets(void)
{
    _pHBox         = new QHBoxLayout  (this, 0, 1, "QColor4ubEditor::_pHBox");

    _pLabels[0]    = new QLabel  ("R", this, "QColor4ubEditor::_pLabels[0]");
    _pLabels[1]    = new QLabel  ("G", this, "QColor4ubEditor::_pLabels[1]");
    _pLabels[2]    = new QLabel  ("B", this, "QColor4ubEditor::_pLabels[2]");
    _pLabels[3]    = new QLabel  ("A", this, "QColor4ubEditor::_pLabels[3]");

    _pSpinBoxes[0] = new QSpinBoxUInt8(this, "QColor4ubEditor::_pSpinBoxes[0]");
    _pSpinBoxes[1] = new QSpinBoxUInt8(this, "QColor4ubEditor::_pSpinBoxes[1]");
    _pSpinBoxes[2] = new QSpinBoxUInt8(this, "QColor4ubEditor::_pSpinBoxes[2]");
    _pSpinBoxes[3] = new QSpinBoxUInt8(this, "QColor4ubEditor::_pSpinBoxes[3]");

    _pColorButton  = new QColorButton (this, "QColor4ubEditor::_pColorButton" );
}

void
QColor4ubEditor::layoutChildWidgets(void)
{
    _pHBox->addWidget(_pLabels[0],              0);
    _pHBox->addWidget(_pSpinBoxes[0],          10);
    _pHBox->addWidget(_pLabels[1],              0);
    _pHBox->addWidget(_pSpinBoxes[1],          10);
    _pHBox->addWidget(_pLabels[2],              0);
    _pHBox->addWidget(_pSpinBoxes[2],          10);
    _pHBox->addWidget(_pLabels[3],              0);
    _pHBox->addWidget(_pSpinBoxes[3],          10);

    _pHBox->addWidget(_pColorButton,           10);
    _pHBox->addWidget(this->getActionButton(), 10);

}

void
QColor4ubEditor::initSelf(void)
{
    _pSpinBoxes[0]->setLowerBound  (TypeTraits<UInt8>::getZeroElement()     );
    _pSpinBoxes[0]->setUpperBound  (TypeTraits<UInt8>::getMax        ()     );
    _pSpinBoxes[0]->setStepSize    (TypeTraits<UInt8>::getOneElement ()     );
    _pSpinBoxes[0]->setPageStepSize(TypeTraits<UInt8>::getOneElement () * 10);

    _pSpinBoxes[1]->setLowerBound  (TypeTraits<UInt8>::getZeroElement()     );
    _pSpinBoxes[1]->setUpperBound  (TypeTraits<UInt8>::getMax        ()     );
    _pSpinBoxes[1]->setStepSize    (TypeTraits<UInt8>::getOneElement ()     );
    _pSpinBoxes[1]->setPageStepSize(TypeTraits<UInt8>::getOneElement () * 10);

    _pSpinBoxes[2]->setLowerBound  (TypeTraits<UInt8>::getZeroElement()     );
    _pSpinBoxes[2]->setUpperBound  (TypeTraits<UInt8>::getMax        ()     );
    _pSpinBoxes[2]->setStepSize    (TypeTraits<UInt8>::getOneElement ()     );
    _pSpinBoxes[2]->setPageStepSize(TypeTraits<UInt8>::getOneElement () * 10);

    _pSpinBoxes[3]->setLowerBound  (TypeTraits<UInt8>::getZeroElement()     );
    _pSpinBoxes[3]->setUpperBound  (TypeTraits<UInt8>::getMax        ()     );
    _pSpinBoxes[3]->setStepSize    (TypeTraits<UInt8>::getOneElement ()     );
    _pSpinBoxes[3]->setPageStepSize(TypeTraits<UInt8>::getOneElement () * 10);

    _pColorButton ->setTransparency(true);

    connect(_pSpinBoxes[0], SIGNAL(valueChanged      (void)),
            this,           SLOT  (slotSBValueChanged(void)) );
    connect(_pSpinBoxes[1], SIGNAL(valueChanged      (void)),
            this,           SLOT  (slotSBValueChanged(void)) );
    connect(_pSpinBoxes[2], SIGNAL(valueChanged      (void)),
            this,           SLOT  (slotSBValueChanged(void)) );
    connect(_pSpinBoxes[3], SIGNAL(valueChanged      (void)),
            this,           SLOT  (slotSBValueChanged(void)) );

    connect(_pColorButton,  SIGNAL(clicked               (void)),
            this,           SLOT  (slotColorButtonClicked(void)) );
}

// include generated file
#include "OSGQColor4ubEditor_qt_moc.cpp"

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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGQColor4ubEditor_qt.cpp,v 1.1 2004/07/30 15:31:57 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGQCOLOR4UBEDITORQT_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGQCOLOR4UBEDITORQT_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
