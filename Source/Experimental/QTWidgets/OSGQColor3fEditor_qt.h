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

#ifndef _OSGQCOLOR3FEDITOR_QT_H_
#define _OSGQCOLOR3FEDITOR_QT_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGWindowQTDef.h>
#include <OSGColor.h>

#include "OSGQAbstractValueEditor_qt.h"
#include "OSGQSpinBoxReal32_qt.h"

class QLabel;
class QHBoxLayout;

OSG_BEGIN_NAMESPACE

class QColorButton;

class OSG_WINDOWQTLIB_DLLMAPPING QColor3fEditor : public QAbstractValueEditor
{
    Q_OBJECT

  public:
    static QAbstractValueEditor *create(QWidget *pParent, const char *name);

             QColor3fEditor(QWidget *pParent, const char *name);
    virtual ~QColor3fEditor(void                              );

    inline void getValue(      Color3f &color) const;
    inline void setValue(const Color3f &color);

  public slots:
    virtual void setLabelsVisible(bool bLabels  );
    virtual void setReadOnly     (bool bReadOnly);

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

  protected slots:
    virtual void slotSBValueChanged    (void);
    virtual void slotColorButtonClicked(void);

  private:
    typedef QAbstractValueEditor Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    QColor3fEditor (const QColor3fEditor &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator= (const QColor3fEditor &source);

    void createChildWidgets(void);
    void layoutChildWidgets(void);
    void initSelf          (void);

    QHBoxLayout    *_pHBox;
    QLabel         *_pLabels   [3];
    QSpinBoxReal32 *_pSpinBoxes[3];
    QColorButton   *_pColorButton;
};

OSG_END_NAMESPACE

#include "OSGQColor3fEditor_qt.inl"

#define OSGQCOLOR3FEDITORQT_HEADER_CVSID "@(#)$Id: OSGQColor3fEditor_qt.h,v 1.3 2004/12/20 11:09:52 neumannc Exp $"

#endif /* _OSGQCOLOR3FEDITOR_QT_H_ */
