
#ifndef _OSGQVECTORFIELDVALUELABEL_H_
#define _OSGQVECTORFIELDVALUELABEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGQFieldValueLabel.h"

OSG_BEGIN_NAMESPACE

/*! \brief Flyweight label, specialized for Vector fields.
 */

template <class VectorTypeT>
class QVectorFieldValueLabel : public QFieldValueLabelBase
{
public:
    typedef          VectorTypeT            VectorType;
    typedef typename VectorTypeT::ValueType ValueType;

    QVectorFieldValueLabel(QFieldViewBase *pView, UInt32 uiIndex);

    virtual ~QVectorFieldValueLabel(void);

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

    QString _strCachedValues[VectorType::_iSize];
    QSize   _cachedSize;
    bool    _bCacheValid;
};

OSG_END_NAMESPACE

#define OSGQVECTORFIELDVALUELABEL_HEADER_CVSID "@(#)$Id: OSGQVectorFieldValueLabel.h,v 1.1 2003/05/07 14:03:40 neumannc Exp $"

#include "OSGQVectorFieldValueLabel.inl"

#endif /* _OSGQVECTORFIELDVALUELABEL_H_ */
