
#ifndef _OSGQPOINTFIELDVALUELABEL_H_
#define _OSGQPOINTFIELDVALUELABEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGQFieldValueLabel.h"

OSG_BEGIN_NAMESPACE

/*! \brief Flyweight label, specialized for Point (e.g. Pnt3f) fields.
 */

template <class PointTypeT>
class OSG_QTWIDGETLIB_DLLTMPLMAPPING QPointFieldValueLabel : 
    public QFieldValueLabelBase
{
public:
    typedef          PointTypeT            PointType;
    typedef typename PointTypeT::ValueType ValueType;

    QPointFieldValueLabel(QFieldViewBase *pView, UInt32 uiIndex);

    virtual ~QPointFieldValueLabel(void);

    static  QFieldValueLabelBase *create(QFieldViewBase *pView, 
                                         UInt32          uiIndex);

    virtual void  paint          (      QPainter    *pPainer,
                                  const QColorGroup &colGrp,   
                                  const QRect       &rect    );

    virtual QSize sizeHint       (void                       );
    virtual QSize minimumSizeHint(void                       );

    virtual void valueChanged    (void                       );

protected:
    const QString &getCachedValue(UInt32 uiCoordinate);
    
    const QSize   &getCachedSize (void               );

private:
    typedef QFieldValueLabelBase Inherited;
 
    void updateCache(void);

    QString _strCachedValues[PointType::_iSize];
    QSize   _cachedSize;
    bool    _bCacheValid;
};

OSG_END_NAMESPACE

#define OSGQPOINTFIELDVALUELABEL_HEADER_CVSID "@(#)$Id: OSGQPointFieldValueLabel.h,v 1.2 2003/05/16 13:54:29 neumannc Exp $"

#include "OSGQPointFieldValueLabel.inl"

#endif /* _OSGQPOINTFIELDVALUELABEL_H_ */
