
#include <OSGSField.h>
#include <OSGMField.h>
#include <OSGSFVecTypes.h>
#include <OSGMFVecTypes.h>

#include <qlayout.h>
#include <qlabel.h>

OSG_BEGIN_NAMESPACE

template <class        VectorPointTypeT, 
          unsigned int SizeArgT         >
QVectorPointEditorHelper<VectorPointTypeT, SizeArgT>::QVectorPointEditorHelper(
    QAbstractValueEditor *pParent)
{
    createChildWidgets(pParent);
    layoutChildWidgets(pParent);
    initSelf          (pParent);
}

template <class        VectorPointTypeT, 
          unsigned int SizeArgT         >
inline
QVectorPointEditorHelper<VectorPointTypeT, SizeArgT>::~QVectorPointEditorHelper(
    void)
{
}

template <class        VectorPointTypeT, 
          unsigned int SizeArgT         >
inline void
QVectorPointEditorHelper<VectorPointTypeT, SizeArgT>::getValue(
    VectorPointType &value) const
{
    for(UInt32 i = 0; i < SizeArgT; ++i)
    {
        value[i] = _pSpinBoxes[i]->getValue();
    }
}

template <class        VectorPointTypeT, 
          unsigned int SizeArgT         >
inline void
QVectorPointEditorHelper<VectorPointTypeT, SizeArgT>::setValue(
    const VectorPointType &value)
{
    for(UInt32 i = 0; i < SizeArgT; ++i)
    {
        _pSpinBoxes[i]->setValue(value[i]);
    }
}


template <class        VectorPointTypeT, 
          unsigned int SizeArgT         >
inline void
QVectorPointEditorHelper<VectorPointTypeT, SizeArgT>::setLabelsVisible(
    bool bLabels)
{
    if(bLabels == true)
    {
        for(UInt32 i = 0; i < SizeArgT; ++i)
        {
            _pLabels[i]->show();
        }
    }
    else
    {
        for(UInt32 i = 0; i < SizeArgT; ++i)
        {
            _pLabels[i]->hide();
        }
    }
}

template <class        VectorPointTypeT, 
          unsigned int SizeArgT         >
inline void
QVectorPointEditorHelper<VectorPointTypeT, SizeArgT>::setReadOnly(
    bool bReadOnly)
{
    for(UInt32 i = 0; i < SizeArgT; ++i)
    {
        _pSpinBoxes[i]->setReadOnly(bReadOnly);
    }
}

template <class        VectorPointTypeT, 
          unsigned int SizeArgT         >
inline void
QVectorPointEditorHelper<VectorPointTypeT, SizeArgT>::readField(
    FieldContainerPtr pFC,          UInt32 uiFieldId,
    UInt32            uiValueIndex, UInt32 uiAspect  )
{
    if(pFC->getField(uiFieldId)->getCardinality() == FieldType::SINGLE_FIELD)
    {
        const SField<VectorPointType> *pSF =
            dynamic_cast<const SField<VectorPointType> *>(
                pFC.getAspectCPtr(uiAspect)->getField(uiFieldId));

        for(UInt32 i = 0; i < SizeArgT; ++i)
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

        for(UInt32 i = 0; i < SizeArgT; ++i)
        {
            _pSpinBoxes[i]->blockSignals(true                   );
            _pSpinBoxes[i]->setValue    ((*pMF)[uiValueIndex][i]);
            _pSpinBoxes[i]->blockSignals(false                  );
        }
    }
}

template <class        VectorPointTypeT, 
          unsigned int SizeArgT         >
inline void
QVectorPointEditorHelper<VectorPointTypeT, SizeArgT>::readField(
    FieldContainerPtr pFC,          UInt32 uiFieldId,
    UInt32            uiValueIndex                   )
{
    readField(pFC, uiFieldId, uiValueIndex,
              Thread::getCurrent()->getAspect());
}

template <class        VectorPointTypeT, 
          unsigned int SizeArgT         >
inline void
QVectorPointEditorHelper<VectorPointTypeT, SizeArgT>::writeField(
    FieldContainerPtr pFC,          UInt32 uiFieldId,
    UInt32            uiValueIndex                   )
{
    if(pFC->getField(uiFieldId)->getCardinality() == FieldType::SINGLE_FIELD)
    {
        SField<VectorPointType> *pSF =
            dynamic_cast<SField<VectorPointType> *>(pFC->getField(uiFieldId));

        for(UInt32 i = 0; i < SizeArgT; ++i)
        {
            pSF->getValue()[i] = _pSpinBoxes[i]->getValue();
        }
    }
    else
    {
        MField<VectorPointType> *pMF =
            dynamic_cast<MField<VectorPointType> *>(pFC->getField(uiFieldId));

        for(UInt32 i = 0; i < SizeArgT; ++i)
        {
            (*pMF)[uiValueIndex][i] = _pSpinBoxes[i]->getValue();
        }
    }
}

template <class        VectorPointTypeT, 
          unsigned int SizeArgT         >
inline void
QVectorPointEditorHelper<VectorPointTypeT, SizeArgT>::addFieldElem(
    FieldContainerPtr pFC,          UInt32 uiFieldId,
    UInt32            uiValueIndex                   )
{
    if(pFC->getField(uiFieldId)->getCardinality() == FieldType::SINGLE_FIELD)
    {
        SWARNING << "QVectorPointEditorHelper::addFieldElemImpl: "
                 << "can not add to SField."
                 << endLog;
    }
    else
    {
        MField<VectorPointType> *pMF           =
            dynamic_cast<MField<VectorPointType> *>(pFC->getField(uiFieldId));
        UInt32                   uiInsertIndex = osgMin(uiValueIndex,
                                                        pMF->size()  );

        pMF->insert(pMF->begin() + uiInsertIndex, VectorPointType());
    }
}

template <class        VectorPointTypeT, 
          unsigned int SizeArgT         >
inline void
QVectorPointEditorHelper<VectorPointTypeT, SizeArgT>::removeFieldElem(
    FieldContainerPtr pFC,          UInt32 uiFieldId,
    UInt32            uiValueIndex                   )
{
    if(pFC->getField(uiFieldId)->getCardinality() == FieldType::SINGLE_FIELD)
    {
        SWARNING << "QVectorPointEditorHelper::removeFieldElemImpl: "
                 << "can not remove from SField."
                 << endLog;
    }
    else
    {
        MField<VectorPointType> *pMF          =
            dynamic_cast<MField<VectorPointType> *>(pFC->getField(uiFieldId));
        UInt32                   uiEraseIndex =
            osgMin(uiValueIndex, pMF->empty() ? 0 : (pMF->size() - 1));

        pMF->erase(pMF->begin() + uiEraseIndex);
    }
}

template <class        VectorPointTypeT, 
          unsigned int SizeArgT         >
inline
const typename QVectorPointEditorHelper<VectorPointTypeT, SizeArgT>::SpinBoxType *
QVectorPointEditorHelper<VectorPointTypeT, SizeArgT>::getSpinBox(
    UInt32 uiIndex) const
{
    return _pSpinBoxes[uiIndex];
}

template <class        VectorPointTypeT, 
          unsigned int SizeArgT         >
inline
typename QVectorPointEditorHelper<VectorPointTypeT, SizeArgT>::SpinBoxType *
QVectorPointEditorHelper<VectorPointTypeT, SizeArgT>::getSpinBox(
    UInt32 uiIndex)
{
    return _pSpinBoxes[uiIndex];
}

template <class        VectorPointTypeT, 
          unsigned int SizeArgT         >
inline const QLabel *
QVectorPointEditorHelper<VectorPointTypeT, SizeArgT>::getLabel(
    UInt32 uiIndex) const
{
    return _pLabels[uiIndex];
}

template <class        VectorPointTypeT, 
          unsigned int SizeArgT         >
inline QLabel *
QVectorPointEditorHelper<VectorPointTypeT, SizeArgT>::getLabel(
    UInt32 uiIndex)
{
    return _pLabels[uiIndex];
}

template <class        VectorPointTypeT, 
          unsigned int SizeArgT         >
void
QVectorPointEditorHelper<VectorPointTypeT, SizeArgT>::createChildWidgets(
    QAbstractValueEditor *pParent)
{
    _pHBox = new QHBoxLayout(pParent, 0, 1, "QVectorPointEditorHelper::_pHBox");

    for(UInt32 i = 0; i < SizeArgT; ++i)
    {
        _pLabels[i]    = new QLabel     (pParent, 
                                         "QVectorPointEditorHelper::_pLabels"   );
        _pSpinBoxes[i] = new SpinBoxType(pParent,
                                         "QVectorPointEditorHelper::_pSpinBoxes");
    }
}

template <class        VectorPointTypeT, 
          unsigned int SizeArgT         >
void
QVectorPointEditorHelper<VectorPointTypeT, SizeArgT>::layoutChildWidgets(
    QAbstractValueEditor *pParent)
{
    for(UInt32 i = 0; i < SizeArgT; ++i)
    {
        _pHBox->addWidget(_pLabels[i],     0);
        _pHBox->addWidget(_pSpinBoxes[i], 10);
    }
}

template <class        VectorPointTypeT, 
          unsigned int SizeArgT         >
void
QVectorPointEditorHelper<VectorPointTypeT, SizeArgT>::initSelf(
    QAbstractValueEditor *pParent)
{
    for(UInt32 i = 0; i < SizeArgT; ++i)
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

#define OSGQVECTORPOINTEDITORHELPER_INLINE_CVSID "@(#)$Id: OSGQVectorPointEditorHelper.inl,v 1.2 2004/12/20 11:09:54 neumannc Exp $"   
    
