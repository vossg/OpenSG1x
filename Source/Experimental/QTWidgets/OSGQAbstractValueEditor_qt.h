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

#ifndef _OSGQABSTRACTVALUEEDITOR_QT_H_
#define _OSGQABSTRACTVALUEEDITOR_QT_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGWindowQTDef.h>
#include <OSGFieldContainer.h>

#include <qwidget.h>

class QPushButton;

OSG_BEGIN_NAMESPACE

class OSG_WINDOWQTLIB_DLLMAPPING QAbstractValueEditor : public QWidget
{
    Q_OBJECT

  public:
    QAbstractValueEditor(QWidget *pParent, const char *name);

    virtual ~QAbstractValueEditor(void);

    inline       bool         getLabelsVisible(void        ) const;
    inline       bool         getReadOnly     (void        ) const;

    inline       bool         getButtonVisible(void        ) const;
    inline       void         setButtonVisible(bool visible);

    inline const QPushButton *getActionButton (void        ) const;
    inline       QPushButton *getActionButton (void        );

  signals:
    void valueChanged       (void);

  public slots:
    virtual void setLabelsVisible(bool bLabelsVisible);
    virtual void setReadOnly     (bool bReadOnly     );

    virtual void readField (FieldContainerPtr pFC,          UInt32 uiFieldId,
                            UInt32            uiValueIndex, UInt32 uiAspect  );
    virtual void readField (FieldContainerPtr pFC,          UInt32 uiFieldId,
                            UInt32            uiValueIndex                   );

    virtual void writeField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                            UInt32            uiValueIndex                   );

    virtual void addFieldElem   (FieldContainerPtr pFC,
                                 UInt32            uiFieldId,
                                 UInt32            uiValueIndex);
    virtual void removeFieldElem(FieldContainerPtr pFC,
                                 UInt32            uiFieldId,
                                 UInt32            uiValueIndex);

  private:
    typedef QWidget Inherited;

    QPushButton *_pActionButton;

    bool         _bLabelsVisible;
    bool         _bReadOnly;
};

OSG_END_NAMESPACE

#include "OSGQAbstractValueEditor_qt.inl"

#define OSGQABSTRACTVALUEEDITORQT_HEADER_CVSID "@(#)$Id: OSGQAbstractValueEditor_qt.h,v 1.2 2004/08/06 16:16:02 neumannc Exp $"

#endif /* _OSGQABSTRACTVALUEEDITOR_QT_H_ */


