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

#include <OSGQ4FieldView_qt.h>

#include <OSGField.h>
#include <OSGSField.h>
#include <OSGMField.h>
#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>
#include <OSGMathFieldDataType.h>

#include <qpainter.h>
#include <qrect.h>
#include <qpalette.h>

OSG_BEGIN_NAMESPACE

template <class MatrixTypeT>
QMatrixFieldValueLabel<MatrixTypeT>::QMatrixFieldValueLabel(
    QFieldViewBase *pView, UInt32 uiIndex)
    : Inherited   (pView, uiIndex),
      _cachedSize (              ),
      _bCacheValid(false         )
{
}

template <class MatrixTypeT>
QMatrixFieldValueLabel<MatrixTypeT>::~QMatrixFieldValueLabel(void)
{
}

template <class MatrixTypeT>
QFieldValueLabelBase *
QMatrixFieldValueLabel<MatrixTypeT>::create(QFieldViewBase *pView,
                                           UInt32          uiIndex)
{
    return (new QMatrixFieldValueLabel<MatrixType>(pView, uiIndex));
}

template <class MatrixTypeT>
void
QMatrixFieldValueLabel<MatrixTypeT>::paint(
    QPainter *pPainter, const QColorGroup &colGrp, const QRect &rect)
{
    QRect drawRect(0, 0, rect.width()/4, rect.height()/4);

    pPainter->save();

    pPainter->setBrush(colGrp.base());

    pPainter->translate(rect.x(), rect.y());

    for(UInt32 row = 0; row < 4; ++row)
    {
        pPainter->save();

        for(UInt32 col = 0; col < 4; ++col)
        {
            pPainter->setPen  (colGrp.background());
            pPainter->drawRect(drawRect           );
            pPainter->setPen  (colGrp.text()      );

			pPainter->drawText (drawRect, Qt::AlignVCenter, 
                                getCachedValue(row, col));
            pPainter->translate(rect.width()/4, 0       );
        }
        
        pPainter->restore  (                    );
        pPainter->translate(0, rect.height() / 4);
    }

    pPainter->restore();
}

template <class MatrixTypeT>
QSize
QMatrixFieldValueLabel<MatrixTypeT>::sizeHint(void)
{
    return QSize(getCachedSize().width()  + 8,
                 getCachedSize().height() + 8 );
}

template <class MatrixTypeT>
QSize
QMatrixFieldValueLabel<MatrixTypeT>::minimumSizeHint(void)
{
    return getCachedSize();
}

template <class MatrixTypeT>
void
QMatrixFieldValueLabel<MatrixTypeT>::valueChanged(void)
{
    _bCacheValid = false;
}

template <class MatrixTypeT>
const QString &
QMatrixFieldValueLabel<MatrixTypeT>::getCachedValue(UInt32 uiRow, UInt32 uiCol)
{
    updateCache();

    return _strCachedValues[4 * uiRow + uiCol];
}

template <class MatrixTypeT>
const QSize &
QMatrixFieldValueLabel<MatrixTypeT>::getCachedSize(void)
{
    updateCache();

    return _cachedSize;
}

template <class MatrixTypeT>
void
QMatrixFieldValueLabel<MatrixTypeT>::updateCache(void)
{
    typedef TypeTraits<ValueType> TTraits;

    if(_bCacheValid)
        return;

    if(getIndex() >= getFieldPtr()->getSize())
    {
        SWARNING << "QMatrixFieldValueLabel<>::updateCache(): "
                 << "getIndex >= getFieldPtr()->getSize()" << endLog;

        for(UInt32 i = 0; i < 16; ++i)
        {
            _strCachedValues[i] = "";
        }

        _cachedSize.setWidth (4 * 10                                );
        _cachedSize.setHeight(getFieldView()->fontMetrics().height());
        
        _bCacheValid = true;

        return;
    }

    Int32 widthOfCol [4] = { 0, 0, 0, 0 };

    if(getFieldPtr()->getCardinality() == FieldType::SINGLE_FIELD)
    {
        SField<MatrixType> *pSF =
            dynamic_cast<SField<MatrixType> *>(getFieldPtr());

        for(UInt32 row = 0; row < 4; ++row)
        {
            for(UInt32 col = 0; col < 4; ++col)
            {
                _strCachedValues[4 * row + col] =
                    TTraits::putToString(
                        pSF->getValue().getValues()[4 * col + row]
                                        ).c_str();

                widthOfCol[col] = osgMax(widthOfCol[col], 
                                         getFieldView()->fontMetrics().width(
                                             _strCachedValues[4 * row + col]));
            }
        }
    }
    else
    {
        MField<MatrixType> *pMF =
            dynamic_cast<MField<MatrixType> *>(getFieldPtr());

       for(UInt32 row = 0; row < 4; ++row)
        {
            for(UInt32 col = 0; col < 4; ++col)
            {
                _strCachedValues[4 * row + col] =
                    TTraits::putToString(
                        (*pMF)[getIndex()].getValues()[4 * col + row]
                                        ).c_str();

                widthOfCol[col] = osgMax(widthOfCol[col], 
                                         getFieldView()->fontMetrics().width(
                                             _strCachedValues[4 * row + col]));
            }
        } 
    }

    _cachedSize.setWidth (    widthOfCol[0] + widthOfCol[1] +
                              widthOfCol[2] + widthOfCol[3]         );
    _cachedSize.setHeight(4 * getFieldView()->fontMetrics().height());
    
    _bCacheValid = true;
}

OSG_END_NAMESPACE

#define OSGQMATRIXFIELDVALUELABEL_INLINE_CVSID "@(#)$Id: OSGQ4MatrixFieldValueLabel.inl,v 1.1 2006/03/10 18:30:35 a-m-z Exp $"

