

#ifndef _OSGQMATRIXFIELDVALUELABEL_H_
#define _OSGQMATRIXFIELDVALUELABEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGQTWidgetDef.h"
#include "OSGQFieldValueLabel.h"

OSG_BEGIN_NAMESPACE

/*! \brief Flyweight label, specialized for Matrix fields.
 */

template <class MatrixTypeT>
class OSG_QTWIDGETLIB_DLLTMPLMAPPING QMatrixFieldValueLabel : 
    public QFieldValueLabelBase
{
public:
    typedef          MatrixTypeT            MatrixType;
    typedef typename MatrixTypeT::ValueType ValueType;
    
             QMatrixFieldValueLabel(QFieldViewBase *pView, UInt32 uiIndex);
    virtual ~QMatrixFieldValueLabel(void                                 );

    static   QFieldValueLabelBase *create(QFieldViewBase    *pView, 
                                          UInt32             uiIndex);

    virtual  void paint                  (      QPainter    *pPainter,
                                          const QColorGroup &colGrp,
                                          const QRect       &rect        );

    virtual QSize sizeHint               (void                           );
    virtual QSize minimumSizeHint        (void                           );

    virtual void  valueChanged           (void                           );

protected:
    const   QString &getCachedValue(UInt32 uiRow, UInt32 uiCol);
    const   QSize   &getCachedSize (void                      );

private:
    typedef QFieldValueLabelBase Inherited;

    void updateCache(void);

    QString _strCachedValues[16];
    QSize   _cachedSize;
    bool    _bCacheValid;
};

OSG_END_NAMESPACE

#define OSGQMATRIXFIELDVALUELABEL_HEADER_CVSID "@(#)$Id: OSGQMatrixFieldValueLabel.h,v 1.2 2003/05/16 13:54:29 neumannc Exp $"

#include "OSGQMatrixFieldValueLabel.inl"

#endif /* _OSGQMATRIXFIELDVALUELABEL_H_ */

