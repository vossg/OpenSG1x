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

#ifndef _OSGQFIELDCONTAINERVIEW_H_
#define _OSGQFIELDCONTAINERVIEW_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGWindowQT4Def.h"

#include "OSGFieldContainer.h"

#include <qwidget.h>
#include <q3table.h>
//Added by qt3to4:
#include <QResizeEvent>

class QColorGroup;
class QRect;
class QSize;
class QResizeEvent;

OSG_BEGIN_NAMESPACE

class OSG_WINDOWQTLIB_DLLMAPPING QFieldContainerView : public QWidget
{
    Q_OBJECT

public:
    enum ColumnNames {
        NameColumn  = 0,
        ValueColumn = 1,
        TypeColumn  = 2
    };

    QFieldContainerView(      QWidget           *parent, 
                        const char              *name   = NULL);
    QFieldContainerView(      FieldContainerPtr  pFC,
                              UInt32             uiAspect,
                              QWidget           *parent, 
                        const char              *name   = NULL);

    virtual ~QFieldContainerView(void);

          FieldContainerPtr &getFieldContainer(void                    );
    const FieldContainerPtr &getFieldContainer(void                    ) const;

          UInt32             getAspect        (void                    ) const;

          bool               getShowTypeColumn(void                    ) const;

public slots:
          void               setFieldContainer(FieldContainerPtr pFC         );
          void               setAspect        (UInt32            uiAspect    );
          void               setShowTypeColumn(bool              bShowTypeCol);

          void               beginEdit        (UInt32            uiFieldId, 
                                               UInt32            uiIndex     );

          void               endEdit          (void                          );
          void               endEdit          (UInt32            uiFieldId   );

signals:
    void clicked          (FieldContainerPtr pFC,     UInt32       uiFieldId,
                           UInt32            uiIndex, Qt::ButtonState  button    );
    void doubleClicked    (FieldContainerPtr pFC,     UInt32       uiFieldId,
                           UInt32            uiIndex, Qt::ButtonState  button    );
 
protected:
    void resizeEvent      (QResizeEvent     *pEvent);

protected slots:
    void onClicked        (FieldContainerPtr pFC,     UInt32 uiFieldId, 
                           UInt32            uiIndex, Qt::ButtonState button);
    void onDoubleClicked  (FieldContainerPtr pFC,     UInt32 uiFieldId,
                           UInt32            uiIndex, Qt::ButtonState button);

private:
    typedef QWidget Inherited;

    class QWidgetTableItem : public Q3TableItem
    {
    public:
        QWidgetTableItem(Q3Table *pTable);

        virtual ~QWidgetTableItem(void);

        virtual void  paint   (      QPainter    *pPainter, 
                               const QColorGroup &cg,
                               const QRect       &cr,       
                                     bool         selected );
        virtual QSize sizeHint(void                        ) const;

    private:
        typedef Q3TableItem Inherited;
    };

    void clearTable(void                                         );
    void fillTable (const FieldContainerPtr &pFC, UInt32 uiAspect);

    Q3Table            *_pTable;
    FieldContainerPtr  _pFC;
    UInt32             _uiAspect;
 
    bool               _bShowTypeColumn;
};

OSG_END_NAMESPACE

#define OSGQFIELDCONTAINERVIEW_HEADER_CVSID "@(#)$Id: OSGQ4FieldContainerView_qt.h,v 1.1 2006/03/10 18:30:35 a-m-z Exp $"

#include "OSGQ4FieldContainerView_qt.inl"

#endif /* _OSGQFIELDCONTAINERVIEW_H_ */
