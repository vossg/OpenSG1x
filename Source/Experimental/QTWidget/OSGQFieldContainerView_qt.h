
#ifndef _OSGQFIELDCONTAINERVIEW_H_
#define _OSGQFIELDCONTAINERVIEW_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGQTWidgetDef.h"

#include <OSGFieldContainer.h>

#include <qwidget.h>
#include <qtable.h>

class QColorGroup;
class QRect;
class QSize;
class QResizeEvent;

OSG_BEGIN_NAMESPACE

class OSG_QTWIDGETLIB_DLLMAPPING QFieldContainerView : public QWidget
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
                           UInt32            uiIndex, ButtonState  button    );
    void doubleClicked    (FieldContainerPtr pFC,     UInt32       uiFieldId,
                           UInt32            uiIndex, ButtonState  button    );
 
protected:
    void resizeEvent      (QResizeEvent     *pEvent);

protected slots:
    void onClicked        (FieldContainerPtr pFC,     UInt32 uiFieldId, 
                           UInt32            uiIndex, ButtonState button);
    void onDoubleClicked  (FieldContainerPtr pFC,     UInt32 uiFieldId,
                           UInt32            uiIndex, ButtonState button);

private:
    typedef QWidget Inherited;

    class QWidgetTableItem : public QTableItem
    {
    public:
        QWidgetTableItem(QTable *pTable);

        virtual ~QWidgetTableItem(void);

        virtual void  paint   (      QPainter    *pPainter, 
                               const QColorGroup &cg,
                               const QRect       &cr,       
                                     bool         selected );
        virtual QSize sizeHint(void                        ) const;

    private:
        typedef QTableItem Inherited;
    };

    void clearTable(void                                         );
    void fillTable (const FieldContainerPtr &pFC, UInt32 uiAspect);

    QTable            *_pTable;
    FieldContainerPtr  _pFC;
    UInt32             _uiAspect;
 
    bool               _bShowTypeColumn;
};

OSG_END_NAMESPACE

#define OSGQFIELDCONTAINERVIEW_HEADER_CVSID "@(#)$Id: OSGQFieldContainerView_qt.h,v 1.2 2003/05/16 13:54:29 neumannc Exp $"

#include "OSGQFieldContainerView_qt.inl"

#endif /* _OSGQFIELDCONTAINERVIEW_H_ */
