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
QScalarEditorHelper<ScalarTypeT>::QScalarEditorHelper(
    QAbstractValueEditor *pParent)

    : _pHBox   (NULL),
      _pLabel  (NULL),
      _pSpinBox(NULL)
{
    createChildWidgets(pParent);
    layoutChildWidgets(pParent);
    initSelf          (pParent);
}

template <class ScalarTypeT>
QScalarEditorHelper<ScalarTypeT>::~QScalarEditorHelper(void)
{
}

template <class ScalarTypeT>
inline void
QScalarEditorHelper<ScalarTypeT>::getValue(ScalarType &value) const
{
    value = _pSpinBox->getValue();
}

template <class ScalarTypeT>
inline void
QScalarEditorHelper<ScalarTypeT>::setValue(const ScalarType &value)
{
    _pSpinBox->setValue(value);
}

template <class ScalarTypeT>
inline void
QScalarEditorHelper<ScalarTypeT>::setLabelsVisible(bool bLabels)
{
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
QScalarEditorHelper<ScalarTypeT>::setReadOnly(bool bReadOnly)
{
    _pSpinBox->setReadOnly(bReadOnly);
}

template <class ScalarTypeT>
inline void
QScalarEditorHelper<ScalarTypeT>::readField(
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
QScalarEditorHelper<ScalarTypeT>::readField(
    FieldContainerPtr pFC,          UInt32 uiFieldId,
    UInt32            uiValueIndex                   )
{
    readField(pFC, uiFieldId, uiValueIndex,
                  Thread::getCurrent()->getAspect());
}

template <class ScalarTypeT>
inline void
QScalarEditorHelper<ScalarTypeT>::writeField(
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
QScalarEditorHelper<ScalarTypeT>::addFieldElem(
    FieldContainerPtr pFC,          UInt32 uiFieldId,
    UInt32            uiValueIndex                   )
{
    if(pFC->getField(uiFieldId)->getCardinality() == FieldType::SINGLE_FIELD)
    {
        SWARNING << "QScalarEditorHelper::addFieldElem: can no add to SField."
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
QScalarEditorHelper<ScalarTypeT>::removeFieldElem(
    FieldContainerPtr pFC,          UInt32 uiFieldId,
    UInt32            uiValueIndex                   )
{
    if(pFC->getField(uiFieldId)->getCardinality() == FieldType::SINGLE_FIELD)
    {
        SWARNING << "QScalarEditorHelper::addFieldElem: can no remove "
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
inline const typename QScalarEditorHelper<ScalarTypeT>::SpinBoxType *
QScalarEditorHelper<ScalarTypeT>::getSpinBox(void) const
{
    return _pSpinBox;
}

template <class ScalarTypeT>
inline typename QScalarEditorHelper<ScalarTypeT>::SpinBoxType *
QScalarEditorHelper<ScalarTypeT>::getSpinBox(void)
{
    return _pSpinBox;
}

template <class ScalarTypeT>
inline const QLabel *
QScalarEditorHelper<ScalarTypeT>::getLabel(void) const
{
    return _pLabel;
}

template <class ScalarTypeT>
inline QLabel *
QScalarEditorHelper<ScalarTypeT>::getLabel(void)
{
    return _pLabel;
}

template <class ScalarTypeT>
void
QScalarEditorHelper<ScalarTypeT>::createChildWidgets(
    QAbstractValueEditor *pParent)
{
    _pHBox    = new QHBoxLayout(pParent, 0, 1, "QScalarEditorHelper::_pHBox");

    _pLabel   = new QLabel     (pParent,    "QScalarEditorHelper::_pLabel"  );
    _pSpinBox = new SpinBoxType(pParent,    "QScalarEditorHelper::_pSpinBox");
}

template <class ScalarTypeT>
void
QScalarEditorHelper<ScalarTypeT>::layoutChildWidgets(
    QAbstractValueEditor *pParent)
{
    _pHBox->addWidget(_pLabel,    0);
    _pHBox->addWidget(_pSpinBox, 10);
}

template <class ScalarTypeT>
void
QScalarEditorHelper<ScalarTypeT>::initSelf(
    QAbstractValueEditor *pParent)
{
    _pLabel->setText("Scalar value");
}


OSG_END_NAMESPACE

#define OSGQSCALAREDITORHELPER_INLINE_CVSID "@(#)$Id: OSGQScalarEditorHelper.inl,v 1.2 2004/12/20 11:09:54 neumannc Exp $"
