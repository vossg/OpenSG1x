
#ifndef _OSGQFIELDVIEW_H_
#define _OSGQFIELDVIEW_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGField.h>
#include <OSGFieldContainerPtr.h>

#include <qwidget.h>
#include <qevent.h>
#include <qsizepolicy.h>

#include <map>

class QScrollBar;

OSG_BEGIN_NAMESPACE

class QFieldValueLabelBase;
class QFieldEditorBase;

/*! \brief Base class for the field display widgets
*/

class QFieldViewBase : public QWidget
{
    Q_OBJECT

public:
    QFieldViewBase(FieldContainerPtr  pFC,
                   UInt32             uiFieldId,
                   UInt32             uiAspect,
                   QWidget           *parent,    const char   *name=NULL);
    
    virtual ~QFieldViewBase(void) = 0;

    virtual void               setAll           (FieldContainerPtr pFC, 
                                                 UInt32   uiFieldId,
                                                 UInt32   uiAspect  );

    virtual void               setFieldContainer(FieldContainerPtr pFC);
            FieldContainerPtr &getFieldContainer(void              );
    const   FieldContainerPtr &getFieldContainer(void              ) const;

    virtual void               setFieldId       (UInt32   uiFieldId);
            UInt32             getFieldId       (void              ) const;

    virtual void               setAspect        (UInt32   uiAspect );
            UInt32             getAspect        (void              ) const;

            Field             *getFieldPtr      (void              );
    const   Field             *getFieldPtr      (void              ) const;

    virtual QSize              sizeHint         (void              ) const = 0;
    virtual QSize              minimumSizeHint  (void              ) const = 0;
    virtual QSizePolicy        sizePolicy       (void              ) const = 0;

public slots:
    virtual void               beginEdit      (UInt32       uiIndex)       = 0;
    virtual void               endEdit        (void                )       = 0;

signals:
    void clicked      (FieldContainerPtr pFC,     UInt32 uiFieldId, 
                       UInt32            uiIndex, ButtonState button);
    void doubleClicked(FieldContainerPtr pFC,     UInt32 uiFieldId,
                       UInt32            uiIndex, ButtonState button);

protected:
    virtual void paintEvent     (QPaintEvent *pEvent ) = 0;

protected slots:
    virtual void onEditorDone   (void                ) = 0;
    virtual void onFieldUpdated (UInt32       uiIndex) = 0;

private:
    typedef QWidget Inherited;

    FieldContainerPtr _pFieldCon;
    UInt32            _uiFieldId;
    UInt32            _uiAspect;
};

/*! \brief The QT Widget to display an OpenSG SField
 */

class QSFieldView : public QFieldViewBase
{
    Q_OBJECT

public:
    QSFieldView(FieldContainerPtr  pFC,          
                UInt32             uiFieldId,
                UInt32             uiAspect,
                QWidget           *parent,    const char   *name=NULL);

    virtual ~QSFieldView(void);
 
    virtual void        setAll           (FieldContainerPtr pFC,
                                          UInt32            uiFieldId,
                                          UInt32            uiAspect  );
    virtual void        setFieldContainer(FieldContainerPtr pFC      );
    virtual void        setFieldId       (UInt32            uiFieldId);
    virtual void        setAspect        (UInt32            uiAspect );

    virtual QSize       sizeHint         (void                        ) const;
    virtual QSize       minimumSizeHint  (void                        ) const;
    virtual QSizePolicy sizePolicy       (void                        ) const;

public slots:
    virtual void beginEdit(UInt32 uiIndex);
    virtual void endEdit  (void          );

protected:
    virtual void mousePressEvent      (QMouseEvent  *pEvent);
    virtual void mouseDoubleClickEvent(QMouseEvent  *pEvent);
    virtual void paintEvent           (QPaintEvent  *pEvent);
    virtual void resizeEvent          (QResizeEvent *pEvent);

protected slots:
    virtual void onEditorDone         (void          );
    virtual void onFieldUpdated       (UInt32 uiIndex);

private:
    typedef QFieldViewBase Inherited;

    void initSelf(void);

    QFieldValueLabelBase *_pLabel;
    QFieldEditorBase     *_pEditor;
};



/*! \brief QT Widget to display an OpenSG MField
 */

class QMFieldView : public QFieldViewBase
{
    Q_OBJECT

public:
    QMFieldView(FieldContainerPtr  pFC,          
                UInt32             uiFieldId,
                UInt32             uiAspect,
                QWidget           *parent,    const char   *name=NULL);

    virtual ~QMFieldView(void);

    virtual void        setAll           (FieldContainerPtr pFC,
                                          UInt32            uiFieldId,
                                          UInt32            uiAspect  );
    virtual void        setFieldContainer(FieldContainerPtr pFC       );
    virtual void        setFieldId       (UInt32            uiFieldId );
    virtual void        setAspect        (UInt32            uiAspect  );

    virtual QSize       sizeHint         (void                       ) const;
    virtual QSize       minimumSizeHint  (void                       ) const;

    virtual QSizePolicy sizePolicy       (void                       ) const;

public slots:
    virtual void beginEdit              (UInt32             uiIndex  );
    virtual void endEdit                (void                        );

protected:
    virtual void paintEvent             (QPaintEvent       *pEvent   );
    virtual void resizeEvent            (QResizeEvent      *pEvent   );
    virtual void wheelEvent             (QWheelEvent       *pEvent   );
    virtual void mousePressEvent        (QMouseEvent       *pEvent   );
    virtual void mouseDoubleClickEvent  (QMouseEvent       *pEvent   );

protected slots:
    virtual void onEditorDone           (void                 );
    virtual void onFieldUpdated         (UInt32        uiIndex);

            void onSBValueChanged       (int           value  );

private:
    typedef QFieldViewBase Inherited;

    class LabelInfo
    {
    public:
        LabelInfo(void);
        LabelInfo(QFieldValueLabelBase *pLabel, const QRect &rectPos);
        
        void                  setLabel(QFieldValueLabelBase *pLabel );
        QFieldValueLabelBase *getLabel(void                         ) const;

        UInt32                getIndex(void                         ) const;

        void                  setRect (const QRect          &rectPos);
        QRect                &getRect (void                         );
        const QRect          &getRect (void                         ) const;

     private:
        QFieldValueLabelBase *_pLabel;
        QRect                 _rectPos;
    };

    typedef std::list<QFieldValueLabelBase *>           PoolLabelList;
    typedef std::list<QFieldValueLabelBase *>::iterator PoolLabelListIt;

    typedef std::map<UInt32, LabelInfo>                 IndexLabelMap;
    typedef std::map<UInt32, LabelInfo>::iterator       IndexLabelMapIt;
    typedef std::map<UInt32, LabelInfo>::const_iterator IndexLabelMapConstIt;

    void                  initSelf        (void                          );
    void                  initScrollbar   (void                          );

    UInt32                pointToIndex    (const QPoint         &pos,
                                                 bool           &bValid  );
   
    QFieldValueLabelBase *acquireLabel    (UInt32                uiIndex );
    void                  releaseLabel    (QFieldValueLabelBase *pLabel  );
    void                  releaseAllLabels(void                          );
    void                  deleteAllLabels (void                          );

    void                  redrawUnchanged (QPaintEvent          *pEvent, 
                                           QPainter             *pPainter);
    void                  redrawChanged   (QPaintEvent          *pEvent,
                                           QPainter             *pPainter);

    QScrollBar       *_pScrollbar;
    QFieldEditorBase *_pEditor;

    PoolLabelList     _poolLabels;
    IndexLabelMap     _usedLabels;
  
    bool              _bContentsChanged;
    UInt32            _uiBeginIndex;
    UInt32            _uiEndIndex;
};


OSG_END_NAMESPACE

#define OSGQFIELDVIEWBASE_HEADER_CVSID "@(#)$Id: OSGQFieldView_qt.h,v 1.1 2003/05/07 14:03:40 neumannc Exp $"

#include "OSGQFieldView_qt.inl"

#endif /* _OSGQFIELDVIEW_H_ */
