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

#include <OSGSField.h>
#include <OSGMField.h>
#include <OSGSFSysTypes.h>
#include <OSGMFSysTypes.h>

#include <qlayout.h>
#include <qlabel.h>

OSG_BEGIN_NAMESPACE

template <class ScalarTypeT>
QScalarTypeEditor<ScalarTypeT>::QScalarTypeEditor(
    QWidget *pParent, const char *name)

    : Inherited(pParent, name),
      _pHBox   (NULL         ),
      _pLabel  (NULL         ),
      _pSpinBox(NULL         )
{
    createChildWidgets();
    layoutChildWidgets();
    initSelf          ();
}

template <class ScalarTypeT>
QScalarTypeEditor<ScalarTypeT>::~QScalarTypeEditor(void)
{
}

template <class ScalarTypeT>
inline void
QScalarTypeEditor<ScalarTypeT>::getValue(ScalarType &value) const
{
    value = _pSpinBox->getValue();
}

template <class ScalarTypeT>
inline void
QScalarTypeEditor<ScalarTypeT>::setValue(const ScalarType &value)
{
    _pSpinBox->setValue(value);
}

template <class ScalarTypeT>
inline void
QScalarTypeEditor<ScalarTypeT>::setLabelsVisibleImpl(bool bLabels)
{
    Inherited::setLabelsVisible(bLabels);

    if(bLabels == true)
    {
        _pLabel->show();
    }
    else
    {
        _pLabel->hide();
    }
}

template <class ScalarTypeT>
inline void
QScalarTypeEditor<ScalarTypeT>::setReadOnlyImpl(bool bReadOnly)
{
    _pSpinBox->setReadOnly(bReadOnly);
}

template <class ScalarTypeT>
inline void
QScalarTypeEditor<ScalarTypeT>::readFieldImpl(
    FieldContainerPtr pFC,          UInt32 uiFieldId,
    UInt32            uiValueIndex, UInt32 uiAspect  )
{
    if(pFC->getField(uiFieldId)->getCardinality() == FieldType::SINGLE_FIELD)
    {
        const SField<ScalarType> *pSF =
            dynamic_cast<const SField<ScalarType> *>(
                pFC.getAspectCPtr(uiAspect)->getField(uiFieldId));

        _pSpinBox->blockSignals(true           );
        _pSpinBox->setValue    (pSF->getValue());
        _pSpinBox->blockSignals(false          );
    }
    else
    {
        const MField<ScalarType> *pMF =
            dynamic_cast<const MField<ScalarType> *>(
                pFC.getAspectCPtr(uiAspect)->getField(uiFieldId));

        _pSpinBox->blockSignals(true                );
        _pSpinBox->setValue    ((*pMF)[uiValueIndex]);
        _pSpinBox->blockSignals(false               );
    }
}

template <class ScalarTypeT>
inline void
QScalarTypeEditor<ScalarTypeT>::readFieldImpl(
    FieldContainerPtr pFC,          UInt32 uiFieldId,
    UInt32            uiValueIndex                   )
{
    readFieldImpl(pFC, uiFieldId, uiValueIndex,
                  Thread::getCurrent()->getAspect());
}

template <class ScalarTypeT>
inline void
QScalarTypeEditor<ScalarTypeT>::writeFieldImpl(
    FieldContainerPtr pFC,          UInt32 uiFieldId,
    UInt32            uiValueIndex                   )
{
    if(pFC->getField(uiFieldId)->getCardinality() == FieldType::SINGLE_FIELD)
    {
        SField<ScalarType> *pSF =
            dynamic_cast<SField<ScalarType> *>(pFC->getField(uiFieldId));

        pSF->getValue() = _pSpinBox->getValue();
    }
    else
    {
        MField<ScalarType> *pMF =
            dynamic_cast<MField<ScalarType> *>(pFC->getField(uiFieldId));

        (*pMF)[uiValueIndex] = _pSpinBox->getValue();
    }
}

template <class ScalarTypeT>
inline void
QScalarTypeEditor<ScalarTypeT>::addFieldElemImpl(
    FieldContainerPtr pFC,          UInt32 uiFieldId,
    UInt32            uiValueIndex                   )
{
    if(pFC->getField(uiFieldId)->getCardinality() == FieldType::SINGLE_FIELD)
    {
        SWARNING << "QScalarTypeEditor::addFieldElem: can no add to SField."
                 << endLog;
    }
    else
    {
        MField<ScalarType> *pMF           =
            dynamic_cast<MField<ScalarType> *>(pFC->getField(uiFieldId));
        UInt32              uiInsertIndex = osgMin(uiValueIndex, pMF->size());

        pMF->insert(pMF->begin() + uiInsertIndex, ScalarType());
    }
}

template <class ScalarTypeT>
inline void
QScalarTypeEditor<ScalarTypeT>::removeFieldElemImpl(
    FieldContainerPtr pFC,          UInt32 uiFieldId,
    UInt32            uiValueIndex                   )
{
    if(pFC->getField(uiFieldId)->getCardinality() == FieldType::SINGLE_FIELD)
    {
        SWARNING << "QScalarTypeEditor::addFieldElem: can no remove "
                 << "from SField."
                 << endLog;
    }
    else
    {
        MField<ScalarType> *pMF          =
            dynamic_cast<MField<ScalarType> *>(pFC->getField(uiFieldId));
        UInt32              uiEraseIndex =
            osgMin(uiValueIndex, pMF->empty() ? 0 : pMF->size() - 1);

        pMF->erase(pMF->begin() + uiEraseIndex);
    }
}

template <class ScalarTypeT>
inline const typename QScalarTypeEditor<ScalarTypeT>::SpinBoxType *
QScalarTypeEditor<ScalarTypeT>::getSpinBox(void) const
{
    return _pSpinBox;
}

template <class ScalarTypeT>
inline typename QScalarTypeEditor<ScalarTypeT>::SpinBoxType *
QScalarTypeEditor<ScalarTypeT>::getSpinBox(void)
{
    return _pSpinBox;
}

template <class ScalarTypeT>
inline const QLabel *
QScalarTypeEditor<ScalarTypeT>::getLabel(void) const
{
    return _pLabel;
}

template <class ScalarTypeT>
inline QLabel *
QScalarTypeEditor<ScalarTypeT>::getLabel(void)
{
    return _pLabel;
}

template <class ScalarTypeT>
void
QScalarTypeEditor<ScalarTypeT>::createChildWidgets(void)
{
    _pHBox    = new QHBoxLayout(this, 0, 1, "QScalarTypeEditor::_pHBox"   );

    _pLabel   = new QLabel     (this,       "QScalarTypeEditor::_pLabel"  );
    _pSpinBox = new SpinBoxType(this,       "QScalarTypeEditor::_pSpinBox");
}

template <class ScalarTypeT>
void
QScalarTypeEditor<ScalarTypeT>::layoutChildWidgets(void)
{
    _pHBox->addWidget(_pLabel,                  0);
    _pHBox->addWidget(_pSpinBox,               10);

    _pHBox->addWidget(this->getActionButton(), 10);
}

template <class ScalarTypeT>
void
QScalarTypeEditor<ScalarTypeT>::initSelf(void)
{
    _pLabel->setText("Scalar value");
}


OSG_END_NAMESPACE

#define OSGQSCALARTYPEEDITOR_INLINE_CVSID "@(#)$Id: OSGQScalarTypeEditor.inl,v 1.2 2004/08/06 16:16:03 neumannc Exp $"
