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

#ifndef _OSGQVECTORFIELDVALUELABEL_H_
#define _OSGQVECTORFIELDVALUELABEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGQTWidgetDef.h"
#include "OSGQFieldValueLabel.h"

OSG_BEGIN_NAMESPACE

/*! \brief Flyweight label, specialized for Vector fields.
 */

template <class VectorTypeT>
class OSG_QTWIDGETLIB_DLLTMPLMAPPING QVectorFieldValueLabel : 
    public QFieldValueLabelBase
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

#define OSGQVECTORFIELDVALUELABEL_HEADER_CVSID "@(#)$Id: OSGQVectorFieldValueLabel.h,v 1.3 2003/05/19 07:36:41 neumannc Exp $"

#include "OSGQVectorFieldValueLabel.inl"

#endif /* _OSGQVECTORFIELDVALUELABEL_H_ */
