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

#ifndef _OSGQFIELDVALUELABEL_H_
#define _OSGQFIELDVALUELABEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGQTWidgetDef.h"

#include <OSGBaseTypes.h>
#include <OSGVector.h>
#include <OSGFieldContainerPtr.h>

#include <qnamespace.h>
#include <qsize.h>
#include <qstring.h>

class QPainter;
class QColorGroup;
class QRect;

OSG_BEGIN_NAMESPACE

/*! \brief The base class for the FieldValueLabel flyweights.
 */

class QFieldViewBase;

class OSG_QTWIDGETLIB_DLLMAPPING QFieldValueLabelBase : public Qt
{
public:
    QFieldValueLabelBase(QFieldViewBase *pView, UInt32 uiIndex);
    
    virtual ~QFieldValueLabelBase(void);
    
    virtual void   paint(      QPainter    *pPainter, 
                         const QColorGroup &colGrp,   const QRect &rect) = 0;

    virtual QSize  sizeHint       (void          ) = 0;
    virtual QSize  minimumSizeHint(void          ) = 0;

            void   setIndex       (UInt32 uiIndex);
            UInt32 getIndex       (void          ) const;

    virtual void   valueChanged   (void          ) = 0;
 
protected:
          QFieldViewBase    *getFieldView     (void);
    const QFieldViewBase    *getFieldView     (void) const;

          FieldContainerPtr &getFieldContainer(void);
    const FieldContainerPtr &getFieldContainer(void) const;

          UInt32             getFieldId       (void) const;
    
          UInt32             getAspect        (void) const;
    
          Field             *getFieldPtr      (void);
    const Field             *getFieldPtr      (void) const;

private:
    QFieldViewBase *_pView;
    UInt32          _uiIndex;
};

/*! \brief Flyweight label, that uses the text representation of the fields.
 */

class OSG_QTWIDGETLIB_DLLMAPPING QGenericFieldValueLabel : 
    public QFieldValueLabelBase
{
public:
    QGenericFieldValueLabel(QFieldViewBase *pView, UInt32 uiIndex);
    
    static QFieldValueLabelBase *create(QFieldViewBase *pView, UInt32 uiIndex);

    virtual ~QGenericFieldValueLabel(void);

    virtual void paint(      QPainter    *pPainter, 
                       const QColorGroup &colGrp,   const QRect &rect);
    
    virtual QSize sizeHint       (void);
    virtual QSize minimumSizeHint(void);

    virtual void  valueChanged   (void);

protected:
    const QString &getCachedValue(void);
    const QSize   &getCachedSize (void);

private:
    typedef QFieldValueLabelBase Inherited;

          void     updateCache   (void);

    QString _strCachedVal;
    QSize   _cachedSize;
    bool    _bCacheValid;
};

OSG_END_NAMESPACE

#define OSGQFIELDVALUELABEL_HEADER_CVSID "@(#)$Id: OSGQFieldValueLabel.h,v 1.3 2003/05/19 07:36:41 neumannc Exp $"

#include "OSGQFieldValueLabel.inl"

#endif /* _OSGQFIELDVALUELABEL_H_ */
