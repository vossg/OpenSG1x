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

#include <qlayout.h>
#include <qlabel.h>

OSG_BEGIN_NAMESPACE

template <class VectorPointTypeT, UInt32 uiDimension>
QVectorPointEditor<VectorPointTypeT, uiDimension>::QVectorPointEditor(
    QWidget *pParent, const char *name)

    : Inherited(pParent, name)
{
    createChildWidgets();
    layoutChildWidgets();
    initSelf          ();
}

template <class VectorPointTypeT, UInt32 uiDimension>
QVectorPointEditor<VectorPointTypeT, uiDimension>::~QVectorPointEditor(void)
{
}

template <class VectorPointTypeT, UInt32 uiDimension>
inline void
QVectorPointEditor<VectorPointTypeT, uiDimension>::getValue(
    VectorPointType &value) const
{
    for(UInt32 i = 0; i < uiDimension; ++i)
    {
        value[i] = _pSpinBoxes[i]->getValue();
    }
}

template <class VectorPointTypeT, UInt32 uiDimension>
inline void
QVectorPointEditor<VectorPointTypeT, uiDimension>::setValue(
    const VectorPointType &value)
{
    for(UInt32 i = 0; i < uiDimension; ++i)
    {
        _pSpinBoxes[i]->setValue(value[i]);
    }
}


template <class VectorPointTypeT, UInt32 uiDimension>
inline void
QVectorPointEditor<VectorPointTypeT, uiDimension>::priv_setLabelsVisible(
    bool bLabels)
{
    Inherited::setLabelsVisible(bLabels);

    if(bLabels == true)
    {
        for(UInt32 i = 0; i < uiDimension; ++i)
        {
            _pLabels[i]->show();
        }
    }
    else
    {
        for(UInt32 i = 0; i < uiDimension; ++i)
        {
            _pLabels[i]->hide();
        }
    }
}

template <class VectorPointTypeT, UInt32 uiDimension>
inline void
QVectorPointEditor<VectorPointTypeT, uiDimension>::priv_setReadOnly(bool bReadOnly)
{
    Inherited::setReadOnly(bReadOnly);

    for(UInt32 i = 0; i < uiDimension; ++i)
    {
        _pSpinBoxes[i]->setReadOnly(bReadOnly);
    }
}

template <class VectorPointTypeT, UInt32 uiDimension>
inline void
QVectorPointEditor<VectorPointTypeT, uiDimension>::priv_readField(
    FieldContainerPtr pFC,          UInt32 uiFieldId,
    UInt32            uiValueIndex, UInt32 uiAspect  )
{
    if(pFC->getField(uiFieldId)->getCardinality() == FieldType::SINGLE_FIELD)
    {
        const SField<VectorPointType> *pSF =
            dynamic_cast<const SField<VectorPointType> *>(
                pFC.getAspectCPtr(uiAspect)->getField(uiFieldId));

        for(UInt32 i = 0; i < uiDimension; ++i)
        {
            _pSpinBoxes[i]->blockSignals(true              );
            _pSpinBoxes[i]->setValue    (pSF->getValue()[i]);
            _pSpinBoxes[i]->blockSignals(false             );
        }
    }
    else
    {
        const MField<VectorPointType> *pMF =
            dynamic_cast<const MField<VectorPointType> *>(
                pFC.getAspectCPtr(uiAspect)->getField(uiFieldId));

        for(UInt32 i = 0; i < uiDimension; ++i)
        {
            _pSpinBoxes[i]->blockSignals(true                   );
            _pSpinBoxes[i]->setValue    ((*pMF)[uiValueIndex][i]);
            _pSpinBoxes[i]->blockSignals(false                  );
        }
    }
}

template <class VectorPointTypeT, UInt32 uiDimension>
inline void
QVectorPointEditor<VectorPointTypeT, uiDimension>::priv_readField(
    FieldContainerPtr pFC,          UInt32 uiFieldId,
    UInt32            uiValueIndex                   )
{
    priv_readField(pFC, uiFieldId, uiValueIndex,
                   Thread::getCurrent()->getAspect());
}

template <class VectorPointTypeT, UInt32 uiDimension>
inline void
QVectorPointEditor<VectorPointTypeT, uiDimension>::priv_writeField(
    FieldContainerPtr pFC,          UInt32 uiFieldId,
    UInt32            uiValueIndex                   )
{
    if(pFC->getField(uiFieldId)->getCardinality() == FieldType::SINGLE_FIELD)
    {
        SField<VectorPointType> *pSF =
            dynamic_cast<SField<VectorPointType> *>(pFC->getField(uiFieldId));

        for(UInt32 i = 0; i < uiDimension; ++i)
        {
            pSF->getValue()[i] = _pSpinBoxes[i]->getValue();
        }
    }
    else
    {
        MField<VectorPointType> *pMF =
            dynamic_cast<MField<VectorPointType> *>(pFC->getField(uiFieldId));

        for(UInt32 i = 0; i < uiDimension; ++i)
        {
            (*pMF)[uiValueIndex][i] = _pSpinBoxes[i]->getValue();
        }
    }
}

template <class VectorPointTypeT, UInt32 uiDimension>
inline
const typename QVectorPointEditor<VectorPointTypeT, uiDimension>::SpinBoxType *
QVectorPointEditor<VectorPointTypeT, uiDimension>::getSpinBox(
    UInt32 uiIndex) const
{
    return _pSpinBoxes[uiIndex];
}

template <class VectorPointTypeT, UInt32 uiDimension>
inline
typename QVectorPointEditor<VectorPointTypeT, uiDimension>::SpinBoxType *
QVectorPointEditor<VectorPointTypeT, uiDimension>::getSpinBox(
    UInt32 uiIndex)
{
    return _pSpinBoxes[uiIndex];
}

template <class VectorPointTypeT, UInt32 uiDimension>
inline const QLabel *
QVectorPointEditor<VectorPointTypeT, uiDimension>::getLabel(
    UInt32 uiIndex) const
{
    return _pLabels[uiIndex];
}

template <class VectorPointTypeT, UInt32 uiDimension>
inline QLabel *
QVectorPointEditor<VectorPointTypeT, uiDimension>::getLabel(
    UInt32 uiIndex)
{
    return _pLabels[uiIndex];
}

template <class VectorPointTypeT, UInt32 uiDimension>
void
QVectorPointEditor<VectorPointTypeT, uiDimension>::createChildWidgets(void)
{
    _pHBox = new QHBoxLayout(this, 0, 1, "QVectorPointEditor::_pHBox");

    for(UInt32 i = 0; i < uiDimension; ++i)
    {
        _pLabels[i]    = new QLabel     (this, "QVectorPointEditor::_pLabels"   );
        _pSpinBoxes[i] = new SpinBoxType(this, "QVectorPointEditor::_pSpinBoxes");
    }
}

template <class VectorPointTypeT, UInt32 uiDimension>
void
QVectorPointEditor<VectorPointTypeT, uiDimension>::layoutChildWidgets(void)
{
    for(UInt32 i = 0; i < uiDimension; ++i)
    {
        _pHBox->addWidget(_pLabels[i],     0);
        _pHBox->addWidget(_pSpinBoxes[i], 10);
    }

    _pHBox->addWidget(this->getActionButton(), 10);
}

template <class VectorPointTypeT, UInt32 uiDimension>
void
QVectorPointEditor<VectorPointTypeT, uiDimension>::initSelf(void)
{
    for(UInt32 i = 0; i < uiDimension; ++i)
    {
        switch(i)
        {
        case 0:
            _pLabels[i]->setText("X");
            break;

        case 1:
            _pLabels[i]->setText("Y");
            break;

        case 2:
            _pLabels[i]->setText("Z");
            break;

        case 3:
            _pLabels[i]->setText("W");
            break;
        };
    }
}

OSG_END_NAMESPACE

#define OSGQVECTORPOINTEDITOR_INLINE_CVSID "@(#)$Id: OSGQVectorPointEditor.inl,v 1.1 2004/07/30 15:32:15 neumannc Exp $"
