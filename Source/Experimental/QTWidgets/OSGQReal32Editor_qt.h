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

#ifndef _OSGQREAL32EDITOR_QT_H_
#define _OSGQREAL32EDITOR_QT_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGWindowQTDef.h>

#include <OSGBaseTypes.h>
#include <OSGQScalarTypeEditor.h>

OSG_BEGIN_NAMESPACE

class OSG_WINDOWQTLIB_DLLMAPPING QReal32Editor :
    public QScalarTypeEditor<Real32>
{
    Q_OBJECT

  public:
    static QAbstractValueEditor *create(QWidget *pParent, const char *name);

    QReal32Editor(QWidget *pParent, const char *name);

    virtual ~QReal32Editor(void);

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
    typedef QScalarTypeEditor<Real32> Inherited;

    void initSelf(void);
};

OSG_END_NAMESPACE

//#include "OSGQReal32Editor.inl"

#define OSGQREAL32EDITORQT_HEADER_CVSID "@(#)$Id: OSGQReal32Editor_qt.h,v 1.1 2004/07/30 15:32:15 neumannc Exp $"

#endif /* _OSGQREAL32EDITOR_QT_H_ */
