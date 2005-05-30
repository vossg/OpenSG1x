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

#include "OSGQFieldContainerView_qt.h"
#include "OSGQFieldView_qt.h"

#include <OSGField.h>

#include <qpalette.h>
#include <qevent.h>
#include <qrect.h>
#include <qsize.h>

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGQFieldContainerView_qt.cpp,v 1.2 2003/05/11 10:33:26 dirk Exp $";
    static Char8 cvsid_hpp[] = OSGQFIELDCONTAINERVIEW_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGQFIELDCONTAINERVIEW_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

QFieldContainerView::QFieldContainerView(QWidget *parent, const char *name)
    : Inherited       (parent, name                     ),
      _pFC            (NullFC                           ),
      _uiAspect       (Thread::getCurrent()->getAspect()),
      _bShowTypeColumn(true                             )
{
    _pTable = new QTable(this, "QFieldContainerView::_pTable");

    _pTable->setNumCols      (3                  );
    _pTable->setReadOnly     (true               );
    _pTable->setSelectionMode(QTable::NoSelection);
}

QFieldContainerView::QFieldContainerView(      FieldContainerPtr  pFC,
                                               UInt32             uiAspect,
                                               QWidget           *parent,
                                         const char              *name   )
    : Inherited       (parent, name                     ),
      _pFC            (NullFC                           ),
      _uiAspect       (uiAspect                         ),
      _bShowTypeColumn(true                             )
{
    _pTable = new QTable(this, "QFieldContainerView::_pTable");

    _pTable->setNumCols      (3                  );
    _pTable->setReadOnly     (true               );
    _pTable->setSelectionMode(QTable::NoSelection);

    setFieldContainer(pFC);
}

QFieldContainerView::~QFieldContainerView(void)
{
}

void
QFieldContainerView::setFieldContainer(FieldContainerPtr pFC)
{
    clearTable();

    fillTable(pFC, _uiAspect);

    _pFC = pFC;
}

void
QFieldContainerView::setAspect(UInt32 uiAspect)
{
    // TODO: check if this can be done smarter

    _uiAspect = uiAspect;

    clearTable();

    fillTable(getFieldContainer(), _uiAspect);
}

void
QFieldContainerView::setShowTypeColumn(bool bShowTypeColumn)
{
    _bShowTypeColumn = bShowTypeColumn;

    if(_bShowTypeColumn)
    {
        _pTable->showColumn  (TypeColumn);
        _pTable->adjustColumn(TypeColumn);
    }
    else
    {
        _pTable->hideColumn(TypeColumn);
    }
}

void
QFieldContainerView::beginEdit(UInt32 uiFieldId, UInt32 uiIndex)
{
    if((uiFieldId < 1) || (uiFieldId > _pFC->getType().getNumFieldDescs()))
        return;

    QFieldViewBase *pFView =
        dynamic_cast<QFieldViewBase *>(_pTable->cellWidget(uiFieldId-1,
                                                           ValueColumn ));

    if(pFView)
        pFView->beginEdit(uiIndex);
}

void
QFieldContainerView::endEdit(void)
{
    int numRows = _pTable->numRows();

    for(int i=0; i < numRows; ++i)
    {
        QFieldViewBase *pFView =
            dynamic_cast<QFieldViewBase *>(
                _pTable->cellWidget(i, ValueColumn));

        if(pFView)
            pFView->endEdit();
    }
}

void
QFieldContainerView::endEdit(UInt32 uiFieldId)
{
    if((uiFieldId < 1) || (uiFieldId > _pFC->getType().getNumFieldDescs()))
        return;

    QFieldViewBase *pFView =
        dynamic_cast<QFieldViewBase *>(_pTable->cellWidget(uiFieldId - 1,
                                                           ValueColumn   ));

    if(pFView)
        pFView->endEdit();
}

void
QFieldContainerView::resizeEvent(QResizeEvent *pEvent)
{
    _pTable->resize(pEvent->size());
}

void
QFieldContainerView::onClicked(FieldContainerPtr pFC,
                               UInt32            uiFieldId,
                               UInt32            uiIndex,
                               ButtonState       button    )
{
    emit clicked(pFC, uiFieldId, uiIndex, button);
}

void
QFieldContainerView::onDoubleClicked(FieldContainerPtr pFC,
                                     UInt32            uiFieldId,
                                     UInt32            uiIndex,
                                     ButtonState       button    )
{
    emit doubleClicked(pFC, uiFieldId, uiIndex, button);
}

void
QFieldContainerView::clearTable(void)
{
    UInt32 rows = _pTable->numRows();

    for(UInt32 i = rows; i > 0; --i)
    {
        _pTable->removeRow(i-1);
    }
}

void
QFieldContainerView::fillTable(const FieldContainerPtr &pFC, UInt32 uiAspect)
{
    UInt32  uiNumFields = pFC->getType().getNumFieldDescs();

    _pTable->setNumRows(uiNumFields);

    for(UInt32 i = 0; i < uiNumFields; ++i)
    {

        if(pFC->getField(i+1)->getCardinality() == FieldType::SINGLE_FIELD)
        {
            QSFieldView *pSFView = new QSFieldView(pFC, i+1, uiAspect, this);

            _pTable->setCellWidget(i, ValueColumn, pSFView      );

#if (QT_VERSION < 0x030301) || (QT_VERSION < 304)
            _pTable->setItem      (i, ValueColumn,
                                   new QWidgetTableItem(_pTable));
#endif

            connect(pSFView,
                    SIGNAL(clicked        (FieldContainerPtr, UInt32,
                                           UInt32,            ButtonState)),
                    this,
                    SLOT  (onClicked      (FieldContainerPtr, UInt32,
                                           UInt32,            ButtonState)));
            connect(pSFView,
                    SIGNAL(doubleClicked  (FieldContainerPtr, UInt32,
                                           UInt32,            ButtonState)),
                    this,
                    SLOT  (onDoubleClicked(FieldContainerPtr, UInt32,
                                           UInt32,            ButtonState)));
            _pTable->setText(i, NameColumn,
                             pFC->getType().getFieldDescription(i+1)->getCName());
        }
        else
        {
            QMFieldView *pMFView = new QMFieldView(pFC, i+1, uiAspect, this);

            _pTable->setCellWidget(i, ValueColumn, pMFView      );

#if (QT_VERSION < 0x030302) || (QT_VERSION < 304)
            _pTable->setItem      (i, ValueColumn,
                                   new QWidgetTableItem(_pTable));
#endif

             connect(pMFView,
                     SIGNAL(clicked        (FieldContainerPtr, UInt32,
                                            UInt32,            ButtonState)),
                     this,
                     SLOT  (onClicked      (FieldContainerPtr, UInt32,
                                            UInt32,            ButtonState)));
             connect(pMFView,
                     SIGNAL(doubleClicked  (FieldContainerPtr, UInt32,
                                            UInt32,            ButtonState)),
                     this,
                     SLOT  (onDoubleClicked(FieldContainerPtr, UInt32,
                                            UInt32,            ButtonState)));

            QString s(pFC->getType().getFieldDescription(i+1)->getCName());

            if(pMFView->getFieldPtr()->getSize() >= 2)
            {
                s += "\n";

                QString num;
                num.setNum(pMFView->getFieldPtr()->getSize());
                s += num;
            }
            _pTable->setText(i, NameColumn, s);
        }

        _pTable->setText(i, TypeColumn,
                         pFC->getField(i+1)->getType().getCName());
    }

    for(UInt32 i=0; i<uiNumFields; ++i)
        _pTable->adjustRow(i);

    _pTable->adjustColumn(NameColumn );
    _pTable->adjustColumn(ValueColumn);

    if(_bShowTypeColumn)
    {
        _pTable->showColumn  (TypeColumn);
        _pTable->adjustColumn(TypeColumn);
    }
    else
    {
        _pTable->hideColumn(TypeColumn);
    }
}

//
// QWidgetTableItem
//

QFieldContainerView::QWidgetTableItem::QWidgetTableItem(QTable  *pTable)
    : Inherited(pTable, Never, "")
{
    setEnabled(false);
}

QFieldContainerView::QWidgetTableItem::~QWidgetTableItem(void)
{
}

void
QFieldContainerView::QWidgetTableItem::paint(
                           QPainter    *OSG_CHECK_ARG(pPainter),
                     const QColorGroup &OSG_CHECK_ARG(cg),
                     const QRect       &OSG_CHECK_ARG(cr),
                           bool         OSG_CHECK_ARG(selected))
{
    QWidget *pWidget = table()->cellWidget(row(), col());

    if(pWidget)
        pWidget->repaint();
}

QSize
QFieldContainerView::QWidgetTableItem::sizeHint(void) const
{
    QWidget *pWidget = table()->cellWidget(row(), col());

    if(pWidget)
        return pWidget->sizeHint();
    else
        return QSize(10, 10);
}

#include "OSGQFieldContainerView_qt_moc.cpp"
