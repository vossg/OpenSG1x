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

#ifndef _OSGQMFIELDEDITOR_QT_H_
#define _OSGQMFIELDEDITOR_QT_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGWindowQTDef.h>
#include <OSGField.h>
#include <OSGFieldContainer.h>

#include <OSGQAbstractFieldEditor_qt.h>

#include <qwidget.h>
#include <qevent.h>

class QButtonGroup;
class QGridLayout;
class QVBoxLayout;
class QLabel;
class QPushButton;
class QSignalMapper;

OSG_BEGIN_NAMESPACE

class OSG_WINDOWQTLIB_DLLMAPPING QMFieldEditor : public QAbstractFieldEditor
{
    Q_OBJECT;

  public:
    static QAbstractFieldEditor *create(QWidget *pParent, const char *name);

    QMFieldEditor(QWidget *pParent, const char *name);

    virtual ~QMFieldEditor(void);

    inline UInt32 getBeginIndex(void) const;
    inline UInt32 getEndIndex  (void) const;

    inline UInt32 getNumRows   (void            ) const;
    inline void   setNumRows   (UInt32 uiNumRows);

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

  protected:
    virtual void keyPressEvent(QKeyEvent *pEvent);

  private slots:
    void slotButtonUpClicked     (void         );
    void slotButtonDownClicked   (void         );

    void slotButtonWriteClicked  (void         );
    void slotButtonCancelClicked (void         );

    void slotEditorValueChanged  (int  editorId);

    void slotActionButtonClicked (int  buttonId);
    void slotActionButtonPressed (int  buttonId);
    void slotActionButtonReleased(int  buttonId);

  private:
    typedef QAbstractFieldEditor Inherited;

    typedef std::vector<QLabel               *> LabelList;
    typedef LabelList::iterator                 LabelListIt;
    typedef LabelList::const_iterator           LabelListConstIt;

    typedef std::vector<QAbstractValueEditor *> EditorList;
    typedef EditorList::iterator                EditorListIt;
    typedef EditorList::const_iterator          EditorListConstIt;

    inline bool   isValidValueIndex      (UInt32 uiValueIndex ) const;
    inline bool   isValidWidgetIndex     (UInt32 uiWidgetIndex) const;
    inline UInt32 mapValueIndex          (UInt32 uiValueIndex ) const;
    inline UInt32 mapWidgetIndex         (UInt32 uiWidgetIndex) const;

    inline void   autoEnableScrollButtons(void                );

    void createChildWidgets (void);
    void layoutChildWidgets (void);
    void initSelf           (void);

    void createEditorWidgets(void);
    void deleteEditorWidgets(void);

    void scrollUp           (UInt32 uiAmount);
    void scrollDown         (UInt32 uiAmount);

    UInt32                           _uiBeginIndex;
    UInt32                           _uiEndIndex;
    UInt32                           _uiNumRows;

    QGridLayout                         *_pGrid;
    QVBoxLayout                         *_pButtonBox;
    QPushButton                         *_pButtonUp;
    QPushButton                         *_pButtonDown;
    QPushButton                         *_pButtonWrite;
    QPushButton                         *_pButtonCancel;
    QSignalMapper                       *_pValueChangedMapper;
    QButtonGroup                        *_pActionButtonGroup;

    std::vector<QLabel           *>      _labels;
    std::vector<QAbstractValueEditor *>  _editors;
};

OSG_END_NAMESPACE

#include "OSGQMFieldEditor_qt.inl"

#define OSGQMFIELDEDITORQT_HEADER_CVSID "@(#)$Id: OSGQMFieldEditor_qt.h,v 1.1 2004/07/30 15:31:57 neumannc Exp $"

#endif /* _OSGQMFIELDEDITOR_QT_H_ */
