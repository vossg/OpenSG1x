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

#ifndef _OSGQSPINBOXBASE_QT_H_
#define _OSGQSPINBOXBASE_QT_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGWindowQTDef.h>

#include <qwidget.h>

#include <string>

class QLineEdit;

OSG_BEGIN_NAMESPACE

class OSG_WINDOWQTLIB_DLLMAPPING QSpinBoxBase : public QWidget
{
    Q_OBJECT

  public:
    QSpinBoxBase(QWidget *pParent = NULL, const char *name = NULL);

    virtual ~QSpinBoxBase(void) = 0;

    inline  bool        getReadOnly  (void            ) const;
    virtual std::string getValueByStr(void            ) const = 0;

    virtual bool        getWrapAround(void            ) const = 0;
    virtual void        setWrapAround(bool bWrapAround)       = 0;

  signals:
    void valueChanged(void);

  public slots:
    virtual void setReadOnly  (      bool         bReadOnly);
    virtual void setValueByStr(const std::string &strValue ) = 0;

    virtual void stepUp       (      void                  ) = 0;
    virtual void stepDown     (      void                  ) = 0;

    virtual void stepPageUp   (      void                  ) = 0;
    virtual void stepPageDown (      void                  ) = 0;

  protected:
    inline const QLineEdit *getLineEdit(void) const;
    inline       QLineEdit *getLineEdit(void);

  private:
    typedef QWidget Inherited;

    bool       _bReadOnly;
    QLineEdit *_pLineEdit;
};

OSG_END_NAMESPACE

#include "OSGQSpinBoxBase_qt.inl"

#define OSGQSPINBOXBASEQT_HEADER_CVSID "@(#)$Id: OSGQSpinBoxBase_qt.h,v 1.1 2004/07/30 15:32:15 neumannc Exp $"

#endif /* _OSGQSPINBOXBASE_QT_H_ */
