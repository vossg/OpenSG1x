

#include <OSGQFieldView_qt.h>

#include <OSGField.h>
#include <OSGSField.h>
#include <OSGMField.h>
#include <OSGBaseTypes.h>

#include <qpainter.h>
#include <qrect.h>
#include <qpalette.h>

OSG_BEGIN_NAMESPACE

template <class PointTypeT>
QPointFieldValueLabel<PointTypeT>::QPointFieldValueLabel(
    QFieldViewBase *pView, UInt32 uiIndex)
    : Inherited   (pView, uiIndex),
      _cachedSize (              ),
      _bCacheValid(false         )
{
}

template <class PointTypeT>
QPointFieldValueLabel<PointTypeT>::~QPointFieldValueLabel(void)
{
}

template <class PointTypeT>
QFieldValueLabelBase *
QPointFieldValueLabel<PointTypeT>::create(QFieldViewBase *pView, 
                                          UInt32          uiIndex)
{
    return new QPointFieldValueLabel<PointTypeT>(pView, uiIndex);
}

template <class PointTypeT>
void
QPointFieldValueLabel<PointTypeT>::paint(
    QPainter *pPainter, const QColorGroup &colGrp, const QRect &rect)
{
    QRect drawRect(0, 0, rect.width()/PointType::_iSize, rect.height());

    pPainter->save();

    pPainter->setBrush(colGrp.base());

    pPainter->translate(rect.x(), rect.y());

    for(UInt32 i=0; i < PointType::_iSize; ++i)
    {
        pPainter->setPen  (colGrp.background());
        pPainter->drawRect(drawRect           );
        pPainter->setPen  (colGrp.text()      );  

        pPainter->drawText(drawRect, AlignVCenter, getCachedValue(i));

        pPainter->translate(rect.width()/PointType::_iSize, 0);
    }

    pPainter->restore();
}

template <class PointTypeT>
QSize
QPointFieldValueLabel<PointTypeT>::sizeHint(void)
{
    return QSize(getCachedSize().width()  + 8,
                 getCachedSize().height() + 8 );
}

template <class PointTypeT>
QSize
QPointFieldValueLabel<PointTypeT>::minimumSizeHint(void)
{
    return getCachedSize();
}

template <class PointTypeT>
void
QPointFieldValueLabel<PointTypeT>::valueChanged(void)
{
    _bCacheValid = false;
}

template <class PointTypeT>
const QString &
QPointFieldValueLabel<PointTypeT>::getCachedValue(UInt32 uiCoordinate)
{
    updateCache();

    return _strCachedValues[uiCoordinate];
}

template <class PointTypeT>
const QSize &
QPointFieldValueLabel<PointTypeT>::getCachedSize(void)
{
    updateCache();

    return _cachedSize;
}

template <class PointTypeT>
void
QPointFieldValueLabel<PointTypeT>::updateCache(void)
{
    typedef TypeTraits<ValueType> TTraits;

    if(_bCacheValid)
        return;

    _cachedSize.setWidth (0                                     );
    _cachedSize.setHeight(getFieldView()->fontMetrics().height());

    if(getIndex() >= getFieldPtr()->getSize())
    {
        SWARNING << "QPointFieldValueLabel<>::updateCache(): "
                 << "getIndex >= getFieldPtr()->getSize()" << endLog;

        for(UInt32 i = 0; i < PointType::_iSize; ++i)
        {
            _strCachedValues[i] = "";
            _cachedSize.setWidth(_cachedSize.width() + 10);
        }
        
        _bCacheValid = true;

        return;
    }    

    if(getFieldPtr()->getCardinality() == FieldType::SINGLE_FIELD)
    {
        SField<PointType> *pSF =
            dynamic_cast<SField<PointType> *>(getFieldPtr());

        for(UInt32 i=0; i < PointType::_iSize; ++i)
        {
            _strCachedValues[i] = 
                TTraits::putToString(
                    pSF->getValue().getValues()[i]).c_str();

            _cachedSize.setWidth(_cachedSize.width() + 
                                 getFieldView()->fontMetrics().width(
                                     _strCachedValues[i]));
        }
    }
    else
    {
        MField<PointType> *pMF =
            dynamic_cast<MField<PointType> *>(getFieldPtr());

        for(UInt32 i=0; i < PointType::_iSize; ++i)
        {
            _strCachedValues[i] =
                TTraits::putToString(
                    pMF->getValue(getIndex()).getValues()[i]).c_str();

            _cachedSize.setWidth(_cachedSize.width() + 
                                 getFieldView()->fontMetrics().width(
                                     _strCachedValues[i]));
        }
    }

    _bCacheValid = true;
}

OSG_END_NAMESPACE

#define OSGQPOINTFIELDVALUELABEL_INLINE_CVSID "@(#)$Id: OSGQPointFieldValueLabel.inl,v 1.1 2003/05/07 14:03:40 neumannc Exp $"
