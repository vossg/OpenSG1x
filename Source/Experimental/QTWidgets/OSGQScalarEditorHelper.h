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

#ifndef _OSGQSCALAREDITORHELPER_QT_H_
#define _OSGQSCALAREDITORHELPER_QT_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGWindowQTDef.h>

#include "OSGQAbstractValueEditor_qt.h"
#include "OSGQSpinBoxes_qt.h"
#include "OSGSpinBoxMapper.h"

class QLabel;
class QHBoxLayout;

OSG_BEGIN_NAMESPACE

template <class ScalarTypeT>
class OSG_WINDOWQTLIB_DLLMAPPING QScalarEditorHelper
{
  public:
    typedef          ScalarTypeT                            ScalarType;
    typedef typename SpinBoxMapper<ScalarType>::SpinBoxType SpinBoxType;

            QScalarEditorHelper(QAbstractValueEditor *pParent);
    inline ~QScalarEditorHelper(void                         );

    inline void getValue(      ScalarType &value) const;
    inline void setValue(const ScalarType &value);
    
    inline void setLabelsVisible(bool              bLabels      );
    inline void setReadOnly     (bool              bReadOnly    );

    inline void readField       (FieldContainerPtr pFC,
                                 UInt32            uiFieldId,
                                 UInt32            uiValueIndex,
                                 UInt32            uiAspect     );
    inline void readField       (FieldContainerPtr pFC,
                                 UInt32            uiFieldId,
                                 UInt32            uiValueIndex );

    inline void writeField      (FieldContainerPtr pFC,
                                 UInt32            uiFieldId,
                                 UInt32            uiValueIndex );

    inline void addFieldElem    (FieldContainerPtr pFC,
                                 UInt32            uiFieldId,
                                 UInt32            uiValueIndex );
    inline void removeFieldElem (FieldContainerPtr pFC,
                                 UInt32            uiFieldId,
                                 UInt32            uiValueIndex );

    inline const SpinBoxType *getSpinBox(void) const;
    inline       SpinBoxType *getSpinBox(void);

    inline const QLabel      *getLabel  (void) const;
    inline       QLabel      *getLabel  (void);

  private:
    void createChildWidgets(QAbstractValueEditor *pParent);
    void layoutChildWidgets(QAbstractValueEditor *pParent);
    void initSelf          (QAbstractValueEditor *pParent);

    QHBoxLayout *_pHBox;
    QLabel      *_pLabel;
    SpinBoxType *_pSpinBox;
};

OSG_END_NAMESPACE

#include "OSGQScalarEditorHelper.inl"

#define OSGQSCALAREDITORHELPER_HEADER_CVSID "@(#)$Id: OSGQScalarEditorHelper.h,v 1.1 2004/11/01 12:24:29 neumannc Exp $"

#endif /* _OSGQSCALAREDITORHELPER_H_ */
