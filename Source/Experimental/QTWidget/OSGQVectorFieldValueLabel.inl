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

#include <OSGQFieldView_qt.h>

#include <OSGField.h>
#include <OSGSField.h>
#include <OSGMField.h>
#include <OSGBaseTypeTraits.h>

#include <qpainter.h>
#include <qrect.h>
#include <qpalette.h>

OSG_BEGIN_NAMESPACE

template <class VectorTypeT>
QVectorFieldValueLabel<VectorTypeT>::QVectorFieldValueLabel(
    QFieldViewBase *pView, UInt32 uiIndex)
    : Inherited   (pView, uiIndex),
      _cachedSize (              ),
      _bCacheValid(false         )
{
}

template <class VectorTypeT>
QVectorFieldValueLabel<VectorTypeT>::~QVectorFieldValueLabel(void)
{
}

template <class VectorTypeT>
QFieldValueLabelBase *
QVectorFieldValueLabel<VectorTypeT>::create(QFieldViewBase *pView, 
                                            UInt32          uiIndex)
{
    return new QVectorFieldValueLabel<VectorType>(pView, uiIndex);
}

template <class VectorTypeT>
void
QVectorFieldValueLabel<VectorTypeT>::paint(
    QPainter *pPainter, const QColorGroup &colGrp, const QRect &rect)
{
    QRect drawRect(0, 0, rect.width()/VectorType::_iSize, rect.height());

    pPainter->save();

    pPainter->setBrush(colGrp.base());

    pPainter->translate(rect.x(), rect.y());

    for(UInt32 i=0; i < VectorType::_iSize; ++i)
    {
        pPainter->setPen  (colGrp.background());
        pPainter->drawRect(drawRect           );
        pPainter->setPen  (colGrp.text()      );  

        pPainter->drawText(drawRect, AlignVCenter, getCachedValue(i));

        pPainter->translate(rect.width()/VectorType::_iSize, 0);
    }

    pPainter->restore();
}

template <class VectorTypeT>
QSize
QVectorFieldValueLabel<VectorTypeT>::sizeHint(void)
{
    return QSize(getCachedSize().width()  + 8,
                 getCachedSize().height() + 8 );
}

template <class VectorTypeT>
QSize
QVectorFieldValueLabel<VectorTypeT>::minimumSizeHint(void)
{
    return getCachedSize();
}

template <class VectorTypeT>
void
QVectorFieldValueLabel<VectorTypeT>::valueChanged(void)
{
    _bCacheValid = false;
}

template <class VectorTypeT>
const QString &
QVectorFieldValueLabel<VectorTypeT>::getCachedValue(UInt32 uiCoordinate)
{
    updateCache();

    return _strCachedValues[uiCoordinate];
}

template <class VectorTypeT>
const QSize &
QVectorFieldValueLabel<VectorTypeT>::getCachedSize(void)
{
    updateCache();

    return _cachedSize;
}

template <class VectorTypeT>
void
QVectorFieldValueLabel<VectorTypeT>::updateCache(void)
{
    typedef TypeTraits<ValueType> TTraits;

    if(_bCacheValid)
        return;

    _cachedSize.setWidth (0                                     );
    _cachedSize.setHeight(getFieldView()->fontMetrics().height());

    if(getIndex() >= getFieldPtr()->getSize())
    {
        SWARNING << "QVectorFieldValueLabel<>::updateCache(): "
                 << "getIndex >= getFieldPtr()->getSize()" << endLog;

        for(UInt32 i = 0; i < VectorType::_iSize; ++i)
        {
            _strCachedValues[i] = "";
            _cachedSize.setWidth(_cachedSize.width() + 10);
        }
        
        _bCacheValid = true;

        return;
    }    

    if(getFieldPtr()->getCardinality() == FieldType::SINGLE_FIELD)
    {
        SField<VectorType> *pSF = 
            dynamic_cast<SField<VectorType> *>(getFieldPtr());

        for(UInt32 i=0; i < VectorType::_iSize; ++i)
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
        MField<VectorType> *pMF =
            dynamic_cast<MField<VectorType> *>(getFieldPtr());

        for(UInt32 i=0; i < VectorType::_iSize; ++i)
        {
            _strCachedValues[i] =
                TTraits::putToString(
                    (*pMF)[getIndex()].getValues()[i]).c_str();
            
            _cachedSize.setWidth(_cachedSize.width() + 
                                 getFieldView()->fontMetrics().width(
                                     _strCachedValues[i]));
        }
    }

    _bCacheValid = true;
}
        
OSG_END_NAMESPACE

#define OSGQVECTORFIELDVALUELABEL_INLINE_CVSID "@(#)$Id: OSGQVectorFieldValueLabel.inl,v 1.3 2003/05/19 07:36:41 neumannc Exp $"

