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

#include "OSGQFieldValueLabel.h"
#include "OSGQFieldView_qt.h"

#include <qpainter.h>
#include <qpalette.h>
#include <qrect.h>

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGQFieldValueLabel.cpp,v 1.1 2003/05/07 14:03:40 neumannc Exp $";
    static Char8 cvsid_hpp[] = OSGQFIELDVALUELABEL_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGQFIELDVALUELABEL_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/*! Constructor
 */

QFieldValueLabelBase::QFieldValueLabelBase(QFieldViewBase *pView, 
                                           UInt32          uiIndex)
    : _pView  (pView),
      _uiIndex(uiIndex)
{
}

/*! Destructor
 */

QFieldValueLabelBase::~QFieldValueLabelBase(void)
{
}

void
QFieldValueLabelBase::setIndex(UInt32 uiIndex)
{
    _uiIndex = uiIndex;

    valueChanged();
}

//***************************************************************************
// QGenericFieldValueLabel
//***************************************************************************

/*! Constructor
 */

QGenericFieldValueLabel::QGenericFieldValueLabel(QFieldViewBase *pView,
                                                 UInt32          uiIndex)
    : Inherited    (pView, uiIndex),
      _strCachedVal(              ),
      _cachedSize  (              ),
      _bCacheValid (false         )
{
}

/*! Create function, which is registered at the QFieldLabelFactory.
 */

QFieldValueLabelBase *
QGenericFieldValueLabel::create(QFieldViewBase *pView, UInt32 uiIndex)
{
    return new QGenericFieldValueLabel(pView, uiIndex);
}

/*! Destructor
 */

QGenericFieldValueLabel::~QGenericFieldValueLabel(void)
{
}

/*! Draws the text representation of a field value.
 */

void
QGenericFieldValueLabel::paint(QPainter *pPainter, const QColorGroup &colGrp,
                                                   const QRect       &rect)
{
    if(!rect.isValid())
        return;

    pPainter->save();

    pPainter->setPen  (colGrp.text());
    pPainter->setBrush(colGrp.base());

    if( (rect.width() < sizeHint().width())   || 
        (rect.height() < sizeHint().height())   )
    {
        pPainter->drawRect(rect);

        pPainter->drawText(rect, AlignVCenter, getCachedValue());
    }
    else
    {
        QRect rectText(rect.x()    +4, rect.y()     +4, 
                       rect.width()-8, rect.height()-8 );

        pPainter->drawRect(rect);

        pPainter->drawText(rectText, AlignVCenter, getCachedValue());
    }

    pPainter->restore();
}

/*! Get the best size for this label.
 */

QSize
QGenericFieldValueLabel::sizeHint(void)
{
    return QSize(getCachedSize().width()  + 8,
                 getCachedSize().height() + 8);
}

/*! Get the minimal size for this label.
 */

QSize
QGenericFieldValueLabel::minimumSizeHint(void)
{
    return getCachedSize();
}

/*! Tell the label, that the shown field's value has changed. 
 */

void
QGenericFieldValueLabel::valueChanged(void)
{
    _bCacheValid = false;
}

const QString &
QGenericFieldValueLabel::getCachedValue(void)
{
    updateCache();

    return _strCachedVal;
}

const QSize &
QGenericFieldValueLabel::getCachedSize(void)
{
    updateCache();

    return _cachedSize;
}

/*! If necessary the cached text representation of the field's 
 *  value is updated.
 */

void
QGenericFieldValueLabel::updateCache(void)
{
    if(_bCacheValid)
        return;

    if(getIndex() >= getFieldPtr()->getSize())
    {
        _strCachedVal = "";
        _cachedSize   = QSize(10, getFieldView()->fontMetrics().height());
        _bCacheValid  = true;

        return;
    }

    std::string strTemp;

    getFieldPtr()->getValueByStr(strTemp, getIndex());
    
    _strCachedVal = strTemp.c_str();
    
    _cachedSize   = QSize(getFieldView()->fontMetrics().width (_strCachedVal),
                          getFieldView()->fontMetrics().height(             ));
    
    _bCacheValid = true;
}
