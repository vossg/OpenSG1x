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

#ifndef _OSGQVECTORPOINTEDITOR_H_
#define _OSGQVECTORPOINTEDITOR_H_
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
          unsigned int uiDimension       = VectorPointTypeT::_iSize>
class OSG_WINDOWQTLIB_DLLMAPPING QVectorPointEditor : public QAbstractValueEditor
{
  public:
    typedef          VectorPointTypeT                      VectorPointType;
    typedef typename VectorPointTypeT::ValueType           ValueType;
    typedef typename SpinBoxMapper<ValueType>::SpinBoxType SpinBoxType;

    QVectorPointEditor(QWidget *pParent, const char *name);

    virtual ~QVectorPointEditor(void);

    inline void getValue(      VectorPointType &value) const;
    inline void setValue(const VectorPointType &value);

  protected:
    inline void priv_setLabelsVisible(bool bLabels  );
    inline void priv_setReadOnly     (bool bReadOnly);

    inline void priv_readField (FieldContainerPtr pFC,
                                UInt32            uiFieldId,
                                UInt32            uiValueIndex,
                                UInt32            uiAspect     );
    inline void priv_readField (FieldContainerPtr pFC,
                                UInt32            uiFieldId,
                                UInt32            uiValueIndex );

    inline void priv_writeField(FieldContainerPtr pFC,
                                UInt32            uiFieldId,
                                UInt32            uiValueIndex );

    inline const SpinBoxType *getSpinBox(UInt32 uiIndex) const;
    inline       SpinBoxType *getSpinBox(UInt32 uiIndex);

    inline const QLabel      *getLabel  (UInt32 uiIndex) const;
    inline       QLabel      *getLabel  (UInt32 uiIndex);

  private:
    typedef QAbstractValueEditor Inherited;

    void createChildWidgets(void);
    void layoutChildWidgets(void);
    void initSelf          (void);

    QHBoxLayout *_pHBox;
    SpinBoxType *_pSpinBoxes[uiDimension];
    QLabel      *_pLabels   [uiDimension];
};

OSG_END_NAMESPACE

#include "OSGQVectorPointEditor.inl"

#define OSGQVECTORPOINTEDITOR_HEADER_CVSID "@(#)$Id: OSGQVectorPointEditor.h,v 1.1 2004/07/30 15:32:15 neumannc Exp $"

#endif /* _OSGQVECTORPOINTEDITOR_H_ */
