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

#ifndef _OSGQGENERICVALUEEDITOR_QT_H_
#define _OSGQGENERICVALUEEDITOR_QT_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGWindowQTDef.h>
#include <OSGQAbstractValueEditor_qt.h>

#include <string>

class QHBoxLayout;
class QLabel;
class QLineEdit;

OSG_BEGIN_NAMESPACE

class OSG_WINDOWQTLIB_DLLMAPPING QGenericValueEditor : public QAbstractValueEditor
{
    Q_OBJECT;

  public:
    static QAbstractValueEditor *create(QWidget *pParent, const char *name);

    QGenericValueEditor(QWidget *pParent, const char *name);

    virtual ~QGenericValueEditor(void);

    inline void getValue(      std::string &value) const;
    inline void setValue(const std::string &value);

  public slots:
    virtual void setLabelsVisible(bool bLabelsVisible);
    virtual void setReadOnly     (bool bReadOnly     );

    virtual void readField (FieldContainerPtr pFC,          UInt32 uiFieldId,
                            UInt32            uiValueIndex, UInt32 uiAspect  );
    virtual void readField (FieldContainerPtr pFC,          UInt32 uiFieldId,
                            UInt32            uiValueIndex                   );

    virtual void writeField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                            UInt32            uiValueIndex                   );

  protected slots:
    void slotLineEditValueChanged(void);

  private:
    typedef QAbstractValueEditor Inherited;

    void createChildWidgets(void);
    void layoutChildWidgets(void);
    void initSelf          (void);

    QHBoxLayout *_pHBox;
    QLabel      *_pLabel;
    QLineEdit   *_pLineEdit;
};

OSG_END_NAMESPACE

#include "OSGQGenericValueEditor_qt.inl"

#define OSGQGENERICVALUEEDITORQT_HEADER_CVSID "@(#)$Id: OSGQGenericValueEditor_qt.h,v 1.1 2004/07/30 15:31:57 neumannc Exp $"

#endif /* _OSGQGENERICVALUEEDITOR_QT_H_ */
