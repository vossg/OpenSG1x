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

#ifndef _OSGQABSTRACTFIELDEDITOR_QT_H_
#define _OSGQABSTRACTFIELDEDITOR_QT_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGWindowQTDef.h>
#include <OSGFieldContainer.h>

#include <qwidget.h>

OSG_BEGIN_NAMESPACE

class QAbstractValueEditor;
class QOSGWidgetFactory;

class OSG_WINDOWQTLIB_DLLMAPPING QAbstractFieldEditor : public QWidget
{
    Q_OBJECT;

  public:
    virtual ~QAbstractFieldEditor(void) = 0;

    inline FieldContainerPtr getFieldContainer(void) const;
    inline UInt32            getFieldId       (void) const;

    inline const QOSGWidgetFactory *getFactory (void                       ) const;
    inline       QOSGWidgetFactory *getFactory (void                       );
    inline       void               setFactory (QOSGWidgetFactory *pFactory);

    inline bool getReadOnly            (void) const;
    inline bool getLabelsVisible       (void) const;
    inline bool getActionButtonsVisible(void) const;

    virtual const QAbstractValueEditor *getEditor(UInt32 uiValueIndex) const = 0;
    virtual       QAbstractValueEditor *getEditor(UInt32 uiValueIndex)       = 0;

  signals:
    void valueChanged        (QAbstractFieldEditor *pSender, UInt32 uiValueIndex);

    void actionButtonClicked (QAbstractFieldEditor *pSender, UInt32 uiValueIndex);
    void actionButtonPressed (QAbstractFieldEditor *pSender, UInt32 uiValueIndex);
    void actionButtonReleased(QAbstractFieldEditor *pSender, UInt32 uiValueIndex);

  public slots:
    virtual void setField               (FieldContainerPtr fcPtr,
                                         UInt32            uiFieldId);
    virtual void setReadOnly            (bool              bReadOnly);
    virtual void setLabelsVisible       (bool              bVisible );
    virtual void setActionButtonsVisible(bool              bVisible );

    virtual void readField (void               ) = 0;
    virtual void readField (UInt32 uiValueIndex) = 0;

    virtual void writeField(void               ) = 0;
    virtual void writeField(UInt32 uiValueIndex) = 0;

  protected:
    QAbstractFieldEditor(QWidget *pParent, const char *name);

    inline Field *getField(void) const;

  private:
    typedef QWidget Inherited;

    FieldContainerPtr  _fcPtr;
    UInt32             _uiFieldId;
    bool               _bReadOnly;
    bool               _bLabelsVisible;
    bool               _bActionButtonsVisible;

    QOSGWidgetFactory *_pFactory;
};

OSG_END_NAMESPACE

#include "OSGQAbstractFieldEditor_qt.inl"

#define OSGQABSTRACTFIELDEDITORQT_HEADER_CVSID "@(#)$Id: OSGQAbstractFieldEditor_qt.h,v 1.1 2004/07/30 15:31:57 neumannc Exp $"

#endif /* _OSGQABSTRACTFIELDEDITOR_QT_H_ */

