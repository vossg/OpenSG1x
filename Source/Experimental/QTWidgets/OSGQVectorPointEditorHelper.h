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

#ifndef _OSGQVECTORPOINTEDITORHELPER_H_
#define _OSGQVECTORPOINTEDITORHELPER_H_
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
    
template <class        VectorPointTypeT, 
          unsigned int SizeArgT         = VectorPointTypeT::_iSize>
class OSG_WINDOWQTLIB_DLLMAPPING QVectorPointEditorHelper
{
  public:
    typedef          VectorPointTypeT                      VectorPointType;
    typedef typename VectorPointTypeT::ValueType           ValueType;
    typedef typename SpinBoxMapper<ValueType>::SpinBoxType SpinBoxType;
  
            QVectorPointEditorHelper(QAbstractValueEditor *pParent);
    inline ~QVectorPointEditorHelper(void                         );
    
    inline void getValue(      VectorPointType &value) const;
    inline void setValue(const VectorPointType &value);    
    
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

    inline const SpinBoxType *getSpinBox(UInt32 uiIndex) const;
    inline       SpinBoxType *getSpinBox(UInt32 uiIndex);

    inline const QLabel      *getLabel  (UInt32 uiIndex) const;
    inline       QLabel      *getLabel  (UInt32 uiIndex);
    
  private:
    void createChildWidgets(QAbstractValueEditor *pParent);
    void layoutChildWidgets(QAbstractValueEditor *pParent);
    void initSelf          (QAbstractValueEditor *pParent);
      
    QHBoxLayout *_pHBox;
    SpinBoxType *_pSpinBoxes[SizeArgT];
    QLabel      *_pLabels   [SizeArgT];
};

OSG_END_NAMESPACE

#include "OSGQVectorPointEditorHelper.inl"

#define OSGQVECTORPOINTEDITORHELPER_HEADER_CVSID "@(#)$Id: OSGQVectorPointEditorHelper.h,v 1.1 2004/11/01 12:24:30 neumannc Exp $"

#endif /* _OSGQVECTORPOINTEDITORHELPER_H_ */

