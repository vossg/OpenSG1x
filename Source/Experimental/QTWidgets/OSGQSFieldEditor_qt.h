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

#ifndef _OSGQSFIELDEDITOR_QT_H_
#define _OSGQSFIELDEDITOR_QT_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGWindowQTDef.h>
#include <OSGQAbstractFieldEditor_qt.h>

class QHBoxLayout;
class QPushButton;

OSG_BEGIN_NAMESPACE

class QAbstractValueEditor;

class OSG_WINDOWQTLIB_DLLMAPPING QSFieldEditor : public QAbstractFieldEditor
{
    Q_OBJECT;

  public:
    static QAbstractFieldEditor *create(QWidget *pParent, const char *name);

    QSFieldEditor(QWidget *pParent, const char *name);

    virtual ~QSFieldEditor(void);

    virtual const QAbstractValueEditor *getEditor(UInt32 uiValueIndex) const;
    virtual       QAbstractValueEditor *getEditor(UInt32 uiValueIndex);

  public slots:
    virtual void setField               (FieldContainerPtr fcPtr,
                                         UInt32            uiFieldId);
    virtual void setReadOnly            (bool              bReadOnly);
    virtual void setLabelsVisible       (bool              bVisible );
    virtual void setActionButtonsVisible(bool              bVisible );

    virtual void readField (void               );
    virtual void readField (UInt32 uiValueIndex);

    virtual void writeField(void               );
    virtual void writeField(UInt32 uiValueIndex);

  protected slots:
    virtual void slotEditorValueChanged  (void);

    virtual void slotButtonCommitClicked (void);
    virtual void slotButtonRevertClicked (void);

    virtual void slotActionButtonClicked (void);
    virtual void slotActionButtonPressed (void);
    virtual void slotActionButtonReleased(void);

  private:
    typedef QAbstractFieldEditor Inherited;

    void createChildWidgets(void);
    void layoutChildWidgets(void);
    void initSelf          (void);

    QHBoxLayout          *_pHBox;
    QPushButton          *_pButtonCommit;
    QPushButton          *_pButtonRevert;
    QAbstractValueEditor *_pEditor;
};

OSG_END_NAMESPACE

//#include "OSGQSFieldEditor_qt.inl"

#define OSGQSFIELDEDITORQT_HEADER_CVSID "@(#)$Id: OSGQSFieldEditor_qt.h,v 1.2 2004/08/06 16:16:03 neumannc Exp $"

#endif /* _OSGQSFIELDEDITOR_QT_H_ */

