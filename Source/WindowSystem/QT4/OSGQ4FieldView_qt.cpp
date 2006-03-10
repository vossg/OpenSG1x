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

#include "OSGQ4FieldView_qt.h"

#include "OSGQ4FieldValueLabel.h"
#include "OSGQ4FieldLabelFactory.h"
#include "OSGQ4FieldEditor_qt.h"
#include "OSGQ4FieldEditorFactory.h"

#include <OSGBaseFunctions.h>

#include <qpainter.h>
#include <qscrollbar.h>
#include <qrect.h>
#include <qfontmetrics.h>
//Added by qt3to4:
#include <QWheelEvent>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QMouseEvent>

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGQ4FieldView_qt.cpp,v 1.1 2006/03/10 18:30:35 a-m-z Exp $";
    static Char8 cvsid_hpp[] = OSGQFIELDVIEWBASE_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGQFIELDVIEWBASE_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

QFieldViewBase::QFieldViewBase(FieldContainerPtr  pFC,          
                               UInt32             uiFieldId,
                               UInt32             uiAspect,
                               QWidget           *parent,    const char  *name)
    : Inherited (parent, name),
      _pFieldCon(pFC         ),
      _uiFieldId(uiFieldId   ),
      _uiAspect (uiAspect    )
{
}

QFieldViewBase::~QFieldViewBase(void)
{
}

void
QFieldViewBase::setAll(FieldContainerPtr pFC,     UInt32 uiFieldId, 
                       UInt32            uiAspect                  )
{
    _pFieldCon = pFC;
    _uiFieldId = uiFieldId;
    _uiAspect  = uiAspect;
}

void
QFieldViewBase::setFieldContainer(FieldContainerPtr pFC)
{
    _pFieldCon = pFC;
}


void
QFieldViewBase::setFieldId(UInt32 uiFieldId)
{
    _uiFieldId = uiFieldId;
}

void
QFieldViewBase::setAspect(UInt32 uiAspect)
{
    _uiAspect = uiAspect;
}

//
// QSFFieldView
//

QSFieldView::QSFieldView(FieldContainerPtr  pFC,          
                         UInt32             uiFieldId,
                         UInt32             uiAspect,
                         QWidget           *parent,   const char   *name      )
    : Inherited(pFC, uiFieldId, uiAspect, parent, name),
      _pLabel  (NULL                                  ),
      _pEditor (NULL                                  )
{
	setBackgroundMode(Qt::NoBackground);

    initSelf();
}

QSFieldView::~QSFieldView(void)
{
    endEdit();

    delete _pLabel;
    delete _pEditor;
}

void
QSFieldView::setAll(FieldContainerPtr pFC, UInt32 uiFieldId, UInt32 uiAspect)
{
    endEdit();

    delete _pLabel;
    delete _pEditor;

    Inherited::setAll(pFC, uiFieldId, uiAspect);

    initSelf();
}

void
QSFieldView::setFieldContainer(FieldContainerPtr pFC)
{
    if(pFC == getFieldContainer())
        return;

    endEdit();

    delete _pLabel;
    delete _pEditor;

    Inherited::setFieldContainer(pFC);

    initSelf();
}

void
QSFieldView::setFieldId(UInt32 uiFieldId)
{
    if(uiFieldId == getFieldId())
        return;

    endEdit();

    delete _pLabel;
    delete _pEditor;

    Inherited::setFieldId(uiFieldId);

    initSelf();
}

void
QSFieldView::setAspect(UInt32 uiAspect)
{
    if(uiAspect == getAspect())
        return;

    endEdit();

    delete _pLabel;
    delete _pEditor;

    Inherited::setAspect(uiAspect);

    initSelf();
}

QSize
QSFieldView::sizeHint(void) const
{
    return _pLabel->sizeHint();
}

QSize
QSFieldView::minimumSizeHint(void) const
{
    return _pLabel->minimumSizeHint();
}

QSizePolicy
QSFieldView::sizePolicy(void) const
{
    return QSizePolicy(QSizePolicy::MinimumExpanding, 
                       QSizePolicy::Fixed            );
}

void
QSFieldView::beginEdit(UInt32 uiIndex)
{
    if(uiIndex != 0)
        return;

    endEdit();

    _pEditor->setIndex(uiIndex);
    _pEditor->activate(       );

    update();
}

void
QSFieldView::endEdit(void)
{
    if(_pEditor && _pEditor->getActive())
        _pEditor->deactivate();

    update();
}

void
QSFieldView::mousePressEvent(QMouseEvent *pEvent)
{
    emit clicked(getFieldContainer(), getFieldId(), 0, pEvent->button());
}

void
QSFieldView::mouseDoubleClickEvent(QMouseEvent *pEvent)
{
    emit doubleClicked(getFieldContainer(), getFieldId(), 0, pEvent->button());
}

void
QSFieldView::onEditorDone(void)
{
    endEdit();
}

void
QSFieldView::onFieldUpdated(UInt32 OSG_CHECK_ARG(uiIndex))
{
    _pLabel->valueChanged();
}

void
QSFieldView::paintEvent(QPaintEvent *pEvent)
{
    if(_pEditor && _pEditor->getActive())
        return;

    QPainter painter;
    QRect    rectSelf = rect();

    painter.begin(this);

    painter.setClipRect(rectSelf.intersect(pEvent->rect()));

    _pLabel->paint(&painter, palette().active(), rectSelf);

    painter.end();
}

void
QSFieldView::resizeEvent(QResizeEvent *pEvent)
{
    if(_pEditor)
        _pEditor->resize(pEvent->size());
}

void
QSFieldView::initSelf(void)
{
    _pLabel  = QFieldLabelFactory::the().createLabel  (this, 0);
    _pEditor = QFieldEditorFactory::the().createEditor(
        0, this, "QSFieldView::_pEditor");

    connect(_pEditor, SIGNAL(editorDone    (void  )),
            this,     SLOT  (onEditorDone  (void  )));

    connect(_pEditor, SIGNAL(fieldUpdated  (UInt32)),
            this,     SLOT  (onFieldUpdated(UInt32)));
}

//
// MFieldView
//

QMFieldView::QMFieldView(FieldContainerPtr  pFC,
                         UInt32             uiFieldId,
                         UInt32             uiAspect,
                         QWidget           *parent,   const char   *name      )
    : Inherited        (pFC, uiFieldId, uiAspect, parent, name),
      _pScrollbar      (NULL                                  ),
      _pEditor         (NULL                                  ),
      _poolLabels      (                                      ),
      _usedLabels      (                                      ),
      _bContentsChanged(true                                  ),
      _uiBeginIndex    (0                                     ),
      _uiEndIndex      (0                                     )
{
    initSelf     ();
    initScrollbar();

    connect(_pScrollbar, SIGNAL(valueChanged(int)),
            this,        SLOT  (onSBValueChanged(int)));
}

QMFieldView::~QMFieldView(void)
{
    endEdit();

    deleteAllLabels();
}

void
QMFieldView::setAll(FieldContainerPtr pFC, UInt32 uiFieldId, UInt32 uiAspect)
{
    endEdit();

    deleteAllLabels();
    delete _pEditor;

    Inherited::setAll(pFC, uiFieldId, uiAspect);

    initSelf     ();
    initScrollbar();
    
    _bContentsChanged = true;
}

void
QMFieldView::setFieldContainer(FieldContainerPtr pFC)
{
    if(pFC == getFieldContainer())
        return;

    endEdit();

    deleteAllLabels();
    delete _pEditor;

    Inherited::setFieldContainer(pFC);

    initSelf     ();
    initScrollbar();

    _bContentsChanged = true;
}

void
QMFieldView::setFieldId(UInt32 uiFieldId)
{
    if(uiFieldId == getFieldId())
        return;

    endEdit();

    deleteAllLabels();
    delete _pEditor;

    Inherited::setFieldId(uiFieldId);

    initSelf     ();
    initScrollbar();

    _bContentsChanged = true;
}

void
QMFieldView::setAspect(UInt32 uiAspect)
{
    if(uiAspect == getAspect())
        return;

    endEdit();

    deleteAllLabels();
    delete _pEditor;

    Inherited::setAspect(uiAspect);

    initSelf     ();
    initScrollbar();

    _bContentsChanged = true;
}

QSize
QMFieldView::sizeHint(void) const
{
    QMFieldView          *pThis         = const_cast<QMFieldView *>(this);
    QFieldValueLabelBase *pLabel;
    QSize                 labelSize( 0,  0);
    QSize                 retSize  (10, 10);
    bool                  bReleaseLabel = false;

    if(_usedLabels.size() != 0)
    {
        pLabel = (*_usedLabels.begin()).second.getLabel();
    }
    else
    {
        pLabel        = QFieldLabelFactory::the().createLabel(pThis, 0);
        bReleaseLabel = true;
    }

    labelSize = pLabel->sizeHint();

    retSize.setHeight(
        osgMin<UInt32>(5, getFieldPtr()->getSize()) * labelSize.height());

    retSize.setWidth(
        osgMax(retSize.width(), labelSize.width() + _pScrollbar->width()));

    
    retSize.setWidth (osgMax(retSize.width(),  10*fontMetrics().width("W")));
    
    retSize.setHeight(osgMax(retSize.height(),    fontMetrics().height()  ));

    if(bReleaseLabel)
        delete pLabel;

    return retSize;
}

QSize
QMFieldView::minimumSizeHint(void) const
{
    return sizeHint();
}

QSizePolicy
QMFieldView::sizePolicy(void) const
{
    return QSizePolicy(QSizePolicy::MinimumExpanding, 
                       QSizePolicy::MinimumExpanding );
}

void
QMFieldView::beginEdit(UInt32 uiIndex)
{
    if(uiIndex >= getFieldPtr()->getSize())
        return;

    endEdit();

    _pEditor->setIndex(uiIndex);
    _pEditor->activate(       );

    update();
}

void
QMFieldView::endEdit(void)
{
    if(_pEditor && _pEditor->getActive())
        _pEditor->deactivate();

    update();
}

void
QMFieldView::paintEvent(QPaintEvent *pEvent)
{
    SNOTICE << "QMFieldView::paintEvent()" << endLog;

    QPainter painter;

    painter.begin(this);

    if(_bContentsChanged)
        redrawChanged  (pEvent, &painter);
    else
        redrawUnchanged(pEvent, &painter);

    painter.end();
}

void
QMFieldView::resizeEvent(QResizeEvent *OSG_CHECK_ARG(pEvent))
{
//    SNOTICE << "QMFieldView::resizeEvent()" << endLog;

    _bContentsChanged = true;

    _pScrollbar->setGeometry(
        width() - _pScrollbar->sizeHint().width(), 0,
        _pScrollbar->sizeHint().width(),           height());

//    _pScrollbar->move  (width()-_pScrollbar->sizeHint().width(), 0);
//    _pScrollbar->resize(_pScrollbar->sizeHint().width(),height()); 
}

void
QMFieldView::wheelEvent(QWheelEvent *pEvent)
{
    if(_pScrollbar->isEnabled())
    {
        _pScrollbar->setValue(
            static_cast<int>(-pEvent->delta() / 60) + _pScrollbar->value());
    }
}

void
QMFieldView::mousePressEvent(QMouseEvent *pEvent)
{
    bool   bValid  = false;
    UInt32 uiIndex = pointToIndex(pEvent->pos(), bValid);
    
    if(bValid && (uiIndex < getFieldPtr()->getSize()))
    {
        emit clicked(getFieldContainer(), getFieldId(),
                     uiIndex,             pEvent->button());
    }
}

void
QMFieldView::mouseDoubleClickEvent(QMouseEvent *pEvent)
{
    bool   bValid  = false;
    UInt32 uiIndex = pointToIndex(pEvent->pos(), bValid);

    if(bValid && (uiIndex < getFieldPtr()->getSize()))
    {
        emit doubleClicked(getFieldContainer(), getFieldId(), 
                           uiIndex,             pEvent->button());
    }
}

void
QMFieldView::onEditorDone(void)
{
    endEdit();
}

void
QMFieldView::onFieldUpdated(UInt32 uiIndex)
{
    IndexLabelMapIt iterLabel = _usedLabels.find(uiIndex);

    if(iterLabel != _usedLabels.end())
        (*iterLabel).second.getLabel()->valueChanged();
}

void
QMFieldView::onSBValueChanged(int OSG_CHECK_ARG(value))
{
    _bContentsChanged = true;
    
    update();
}

void
QMFieldView::initSelf(void)
{
    _pEditor = QFieldEditorFactory::the().createEditor(
        this, "QMFieldView::_pEditor");

    connect(_pEditor, SIGNAL(editorDone    (void  )),
            this,     SLOT  (onEditorDone  (void  )));

    connect(_pEditor, SIGNAL(fieldUpdated  (UInt32)),
            this,     SLOT  (onFieldUpdated(UInt32)));
}

void
QMFieldView::initScrollbar(void)
{
    if(_pScrollbar == NULL)
    {
        _pScrollbar = new QScrollBar(Qt::Vertical, this, 
                                     "QMFieldView::_pScrollbar");
    }

    _pScrollbar->setGeometry(
        width()-_pScrollbar->sizeHint().width(), 0,
        _pScrollbar->sizeHint().width(),         height());

    if(getFieldPtr()->getSize() <= 2)
    {
        _pScrollbar->hide       ( );
        _pScrollbar->setMinValue(0);
        _pScrollbar->setMaxValue(0);
    }
    else
    {
        _pScrollbar->show       (                            );
        _pScrollbar->setMinValue(0                           );
        _pScrollbar->setMaxValue(2*getFieldPtr()->getSize()-2);
    }
}

UInt32
QMFieldView::pointToIndex(const QPoint &pos, bool &bValid)
{
    IndexLabelMapIt iter = _usedLabels.begin();
    IndexLabelMapIt end  = _usedLabels.end();

    for(; iter != end; ++iter)
    {
        if( ((*iter).second.getRect().top()     <= pos.y()) &&
            ((*iter).second.getRect().bottom()  >= pos.y())   )
        {
            bValid = true;

            return (*iter).first;
        }
    }

    bValid = false;

    return 0;
}

QFieldValueLabelBase *
QMFieldView::acquireLabel(UInt32 uiIndex)
{
    SNOTICE << "QMFieldView::acquireLabel(" << uiIndex << ")\n";

    QFieldValueLabelBase *retVal    = 0;

    IndexLabelMapIt       iterLabel = _usedLabels.find(uiIndex);

    if(iterLabel != _usedLabels.end())
    {
        PNOTICE << "from usedLabels: " << iterLabel->second.getLabel()
                << endLog;
        
        return iterLabel->second.getLabel();
    }

    if(!_poolLabels.empty())
    {
        retVal = _poolLabels.back    ();
        
        _poolLabels.pop_back();

        PNOTICE << "from pool: " << retVal 
                << "was index "  << retVal->getIndex()
                << endLog;         

        retVal->setIndex(uiIndex);

        return retVal;
    }
    
    retVal = QFieldLabelFactory::the().createLabel(this, uiIndex);

    PNOTICE << "from factory: " << retVal << endLog;

    return retVal;
}

void
QMFieldView::releaseLabel(QFieldValueLabelBase *pLabel)
{
    SNOTICE << "QMFieldView::releaseLabel(" << pLabel << ") "
            << "index : "                   << pLabel->getIndex()
            << endLog;

    IndexLabelMapIt iterLabel = _usedLabels.find(pLabel->getIndex());

    if(iterLabel == _usedLabels.end())
    {
        SWARNING << "QMFieldView::releaseLabel: pLabel is not used." 
                 << endLog;
        return;
    }

    _usedLabels.erase    (iterLabel);
    _poolLabels.push_back(pLabel   );
}

void
QMFieldView::releaseAllLabels(void)
{
    QFieldValueLabelBase *pLabel;
    IndexLabelMapIt       iter = _usedLabels.begin();
    IndexLabelMapIt       end  = _usedLabels.end();

    for(; iter != end; ++iter)
    {
        pLabel = (*iter).second.getLabel();
        _poolLabels.push_back(pLabel);
    }
    _usedLabels.clear();
}

void
QMFieldView::deleteAllLabels(void)
{
    SNOTICE << "QMFieldView::deleteAllLabels():\n";

    QFieldValueLabelBase *pLabel;

    IndexLabelMapIt       usedIter = _usedLabels.begin();
    IndexLabelMapIt       usedEnd  = _usedLabels.end();

    PNOTICE << "used <" << _usedLabels.size() << "> ";

    for(; usedIter != usedEnd; ++usedIter)
    {
        pLabel = (*usedIter).second.getLabel();

        PNOTICE << " iter.first: "       << (*usedIter).first
                << " pLabel->getIndex() " << pLabel->getIndex()
                << " pLabel "            << pLabel
                << "\n";
        delete pLabel;
    }
    _usedLabels.clear();

    PoolLabelListIt poolIter = _poolLabels.begin();
    PoolLabelListIt poolEnd  = _poolLabels.end();
    
    PNOTICE << "pool <" << _poolLabels.size() << "> ";

    for(; poolIter != poolEnd; ++poolIter)
    {
        pLabel = *poolIter;

        PNOTICE << " pLabel->getIndex() " << pLabel->getIndex()
                << " pLabel "            << pLabel
                << "\n";

        delete pLabel;
    }

    _poolLabels.clear();

    PNOTICE << endLog;
}

void
QMFieldView::redrawUnchanged(QPaintEvent *pEvent, QPainter *pPainter)
{
    SNOTICE << "QMFieldView::redrawUnchanged()" << endLog;

    IndexLabelMapIt begin = _usedLabels.begin();
    IndexLabelMapIt end   = _usedLabels.end();

    for(; begin != end; ++begin)
    {
        pPainter->setClipRect(
            (*begin).second.getRect().intersect(pEvent->rect()));

        (*begin).second.getLabel()->paint(
            pPainter, palette().active(), (*begin).second.getRect());
    }
}

void
QMFieldView::redrawChanged(QPaintEvent *pEvent, QPainter *pPainter)
{
    SNOTICE << "QMFieldView::redrawChanged()" << endLog;

    UInt32                currIndex;
    Int32                 drawTop;

    QRect                 drawRect;
    QSize                 drawSize;

    bool                  doneDraw = false;

    QFieldValueLabelBase *pLabel;

    _uiBeginIndex = _pScrollbar->value()/2;
    _uiEndIndex   = _uiBeginIndex;
    currIndex     = _uiBeginIndex;

    if(_uiBeginIndex >= getFieldPtr()->getSize())
    {
        releaseAllLabels();
        return;
    }

    pLabel   = acquireLabel   (_uiEndIndex++);
    drawSize = pLabel->sizeHint(             );
    drawTop  = ((_pScrollbar->value() % 2) == 0) ? 0 : -drawSize.height()/2;

    drawRect = QRect(0, drawTop,
                     width()-_pScrollbar->width(), 
                     osgMin(drawSize.height(), height()            ) );

    while(!doneDraw)
    {
        pPainter->setClipRect(drawRect.intersect(pEvent->rect()));

        pLabel->paint(pPainter, palette().active(), drawRect);
        
        _usedLabels[currIndex].setLabel(pLabel  );
        _usedLabels[currIndex].setRect (drawRect);
              
        drawTop += drawRect.height();
        
        if((_uiEndIndex >= getFieldPtr()->getSize()) ||
           (drawTop     >= height()                )   )
        {
            doneDraw = true;
        }
        else
        {
            currIndex = _uiEndIndex++;
            pLabel    = acquireLabel    (currIndex);
            drawSize  = pLabel->sizeHint(         );

            drawRect  = QRect(0, drawTop,
                              width()-_pScrollbar->width(),
                              osgMin(drawSize.height(), height()));
        }
    }

    IndexLabelMapIt   begin = _usedLabels.begin();
    IndexLabelMapIt   end   = _usedLabels.end();

    for(; begin != end; ++begin)
    {
        pLabel = begin->second.getLabel();

        if( (pLabel->getIndex() <  _uiBeginIndex) ||
            (pLabel->getIndex() >= _uiEndIndex  )   )
        {
            releaseLabel(pLabel);
//            _usedLabels.erase(begin);
//            _poolLabels.push_back(pLabel);
        }
    }

    _bContentsChanged = false;
}

//
// QMFieldView::LabelInfo
//

QMFieldView::LabelInfo::LabelInfo(void)
    : _pLabel (NULL),
      _rectPos(    )
{
}

QMFieldView::LabelInfo::LabelInfo(QFieldValueLabelBase *pLabel, 
                                  const QRect          &rectPos)
    : _pLabel (pLabel ),
      _rectPos(rectPos)
{
}

void
QMFieldView::LabelInfo::setLabel(QFieldValueLabelBase *pLabel)
{
    _pLabel = pLabel;
}

QFieldValueLabelBase *
QMFieldView::LabelInfo::getLabel(void) const
{
    return _pLabel;
}

UInt32
QMFieldView::LabelInfo::getIndex(void) const
{
    return _pLabel->getIndex();
}

void
QMFieldView::LabelInfo::setRect(const QRect &rectPos)
{
    _rectPos = rectPos;
}

QRect &
QMFieldView::LabelInfo::getRect(void)
{
    return _rectPos;
}

const QRect &
QMFieldView::LabelInfo::getRect(void) const
{
    return _rectPos;
}

#include "OSGQ4FieldView_qt_moc.cpp"
