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

#ifndef _OSGQFIELDCONTAINERPTREDITOR_QT_H_
#define _OSGQFIELDCONTAINERPTREDITOR_QT_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGWindowQTDef.h>

#include "OSGQAbstractValueEditor_qt.h"

class QHBoxLayout;
class QLabel;
class QComboBox;
class QPushButton;
class QStrList;

OSG_BEGIN_NAMESPACE

class QSpinBoxUInt32;  
    
class OSG_WINDOWQTLIB_DLLMAPPING QFieldContainerPtrEditor
    : public QAbstractValueEditor
{
    Q_OBJECT

  public:
    static   QAbstractValueEditor *create(QWidget *pParent, const char *name);

             QFieldContainerPtrEditor(QWidget *pParent, const char *name);
    virtual ~QFieldContainerPtrEditor(void                              );

    inline void getValue(      FieldContainerPtr &pFC) const;
    inline void setValue(const FieldContainerPtr &pFC);

  public slots:
    virtual void setLabelsVisible(bool bLabels  );
    virtual void setReadOnly     (bool bReadOnly);

    virtual void readField      (FieldContainerPtr pFC,
                                 UInt32            uiFieldId,
                                 UInt32            uiValueIndex,
                                 UInt32            uiAspect      );
    virtual void readField      (FieldContainerPtr pFC,
                                 UInt32            uiFieldId,
                                 UInt32            uiValueIndex  );

    virtual void writeField     (FieldContainerPtr pFC,
                                 UInt32            uiFieldId,
                                 UInt32            uiValueIndex  );

    virtual void addFieldElem   (FieldContainerPtr pFC,
                                 UInt32            uiFieldId,
                                 UInt32            uiValueIndex  );
    virtual void removeFieldElem(FieldContainerPtr pFC,
                                 UInt32            uiFieldId,
                                 UInt32            uiValueIndex  );

  protected slots:
    virtual void slotIdChanged              (void);
    
    virtual void slotButtonCreateNewClicked (void);
    virtual void slotButtonShowTargetClicked(void);

  private:
    typedef QAbstractValueEditor Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    QFieldContainerPtrEditor(const QFieldContainerPtrEditor &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator=          (const QFieldContainerPtrEditor &source);

    void createChildWidgets  (void);
    void layoutChildWidgets  (void);
    void initSelf            (void);

    void updateStaticTypeList(void);

    void updateDisplay     (FieldContainerPtr  fcPtr);
    void updateData        (FieldContainerPtr &fcPtr) const;
    
    static QStrList *_pTypeNames;

    QHBoxLayout     *_pHBox;

    QLabel          *_pLabelId;
    QSpinBoxUInt32  *_pSpinBoxId;
    QLabel          *_pLabelType;
    QComboBox       *_pCBoxType;
    QPushButton     *_pButtonCreateNew;
    QPushButton     *_pButtonShowTarget;
};

OSG_END_NAMESPACE

#include "OSGQFieldContainerPtrEditor_qt.inl"

#define OSGQFIELDCONTAINERPTREDITORQT_HEADER_CVSID "@(#)$Id: OSGQFieldContainerPtrEditor_qt.h,v 1.4 2004/12/20 11:09:53 neumannc Exp $"

#endif /* _OSGQFIELDCONTAINERPTREDITOR_QT_H_ */
