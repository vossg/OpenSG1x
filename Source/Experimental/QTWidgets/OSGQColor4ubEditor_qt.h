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

#ifndef _OSGQCOLOR4UBEDITOR_QT_H_
#define _OSGQCOLOR4UBEDITOR_QT_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGWindowQTDef.h>
#include <OSGColor.h>

#include "OSGQAbstractValueEditor_qt.h"
#include "OSGQSpinBoxUInt8_qt.h"

class QLabel;
class QHBoxLayout;

OSG_BEGIN_NAMESPACE

class QColorButton;

class OSG_WINDOWQTLIB_DLLMAPPING QColor4ubEditor : public QAbstractValueEditor
{
    Q_OBJECT

  public:
    static QAbstractValueEditor *create(QWidget *pParent, const char *name);

    QColor4ubEditor(QWidget *pParent, const char *name);

    virtual ~QColor4ubEditor(void);

    inline void getValue(      Color4ub &color) const;
    inline void setValue(const Color4ub &color);

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

    void createChildWidgets(void);
    void layoutChildWidgets(void);
    void initSelf          (void);

    QHBoxLayout    *_pHBox;
    QLabel         *_pLabels   [4];
    QSpinBoxUInt8  *_pSpinBoxes[4];
    QColorButton   *_pColorButton;
};

OSG_END_NAMESPACE

#include "OSGQColor4ubEditor_qt.inl"

#define OSGQCOLOR4UBEDITORQT_HEADER_CVSID "@(#)$Id: OSGQColor4ubEditor_qt.h,v 1.2 2004/08/06 16:16:02 neumannc Exp $"

#endif /* _OSGQCOLOR4UBEDITOR_QT_H_ */
