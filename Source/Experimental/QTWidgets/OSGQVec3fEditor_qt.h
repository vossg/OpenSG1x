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

#ifndef _OSGQVEC3FEDITOR_QT_H_
#define _OSGQVEC3FEDITOR_QT_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGWindowQTDef.h>
#include <OSGVector.h>

#include "OSGQVectorPointEditor.h"

OSG_BEGIN_NAMESPACE

class OSG_WINDOWQTLIB_DLLMAPPING QVec3fEditor :
    public QVectorPointEditor<Vec3f>
{
    Q_OBJECT

  public:
    static QAbstractValueEditor *create(QWidget *pParent, const char *name);

    QVec3fEditor(QWidget *pParent, const char *name);

    virtual ~QVec3fEditor(void);

  public slots:
    virtual void setLabelsVisible(bool bLabels  );
    virtual void setReadOnly     (bool bReadOnly);

    virtual void readField (FieldContainerPtr pFC,          UInt32 uiFieldId,
                            UInt32            uiValueIndex, UInt32 uiAspect  );
    virtual void readField (FieldContainerPtr pFC,          UInt32 uiFieldId,
                            UInt32            uiValueIndex                   );

    virtual void writeField(FieldContainerPtr pFC,          UInt32 uiFieldId,
                            UInt32            uiValueIndex                   );

  protected slots:
    virtual void slotSpinBoxChanged(void);

  private:
    typedef QVectorPointEditor<Vec3f> Inherited;

    void initSelf(void);
};

OSG_END_NAMESPACE

//#include "OSGQVec3fEditor.inl"

#define OSGQVEC3FEDITORQT_HEADER_CVSID "@(#)$Id: OSGQVec3fEditor_qt.h,v 1.1 2004/07/30 15:32:15 neumannc Exp $"

#endif /* _OSGQVEC3FEDITOR_QT_H_ */
