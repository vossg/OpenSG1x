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

#ifndef _OSGQSPINBOXINT8_QT_H_
#define _OSGQSPINBOXINT8_QT_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGWindowQTDef.h>
#include <OSGBaseTypes.h>

#include "OSGQSpinBoxBase_qt.h"
#include "OSGSpinBoxHelper.h"

#include <string>

class QObject;
class QEvent;
class QResizeEvent;
class QWheelEvent;
class QSpinWidget;

OSG_BEGIN_NAMESPACE

class OSG_WINDOWQTLIB_DLLMAPPING QSpinBoxInt8 : public QSpinBoxBase
{
    Q_OBJECT

  public:
    QSpinBoxInt8(QWidget *pParent = NULL, const char *name = NULL);

    virtual ~QSpinBoxInt8(void);

    inline  Int8        getValue       (void             ) const;
    inline  void        setValue       (Int8 value       );

    inline  Int8        getLowerBound  (void             ) const;
    inline  void        setLowerBound  (Int8 lowerBound  );

    inline  Int8        getUpperBound  (void             ) const;
    inline  void        setUpperBound  (Int8 upperBound  );

    inline  Int8        getStepSize    (void             ) const;
    inline  void        setStepSize    (Int8 stepSize    );

    inline  Int8        getPageStepSize(void             ) const;
    inline  void        setPageStepSize(Int8 pageStepSize);

    virtual std::string getValueByStr  (void             ) const;

    virtual bool        getWrapAround  (void             ) const;
    virtual void        setWrapAround  (bool bWrapAround );

  public slots:
    virtual void setReadOnly  (      bool         bReadOnly);
    virtual void setValueByStr(const std::string &strValue );

    virtual void stepUp       (void          );
    virtual void stepDown     (void          );

    virtual void stepPageUp   (void);
    virtual void stepPageDown (void);

  protected:
    virtual bool eventFilter(QObject      *pObj,        QEvent *pEvent);
    virtual void resizeEvent(QResizeEvent *pResizeEvent               );
    virtual void wheelEvent (QWheelEvent  *pWheelEvent                );

  protected slots:
    virtual void slotTextChanged  (void);
    virtual void slotReturnPressed(void);

  private:
    typedef QSpinBoxBase Inherited;

    void updateDisplay(void);

    bool                   _bTextChanged;
    SpinBoxHelper<Int8>   _spinHelper;
    QSpinWidget           *_pSpinWidget;
};

OSG_END_NAMESPACE

#include "OSGQSpinBoxInt8_qt.inl"

#define OSGQSPINBOXINT8QT_HEADER_CVSID "@(#)$Id: OSGQSpinBoxInt8_qt.h,v 1.1 2004/07/30 15:32:15 neumannc Exp $"

#endif /* _OSGQSPINBOXINT8_QT_H_ */
