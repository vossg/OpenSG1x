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

#ifndef _OSGQFIELDCONTAINEREDITOR_QT_H_
#define _OSGQFIELDCONTAINEREDITOR_QT_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGWindowQTDef.h>
#include <OSGQAbstractFieldEditor_qt.h>
#include <OSGFieldContainer.h>
#include <OSGQOSGWidgetFactory.h>

#include <qwidget.h>

#include <vector>

class QLabel;
class QTable;
class QHBoxLayout;
class QVBoxLayout;

OSG_BEGIN_NAMESPACE

class QOSGWidgetFactory;

class OSG_WINDOWQTLIB_DLLMAPPING QFieldContainerEditor : public QWidget
{
    Q_OBJECT;

  public:
    QFieldContainerEditor(QWidget *pParent, const char *name);

    virtual ~QFieldContainerEditor(void);

    inline FieldContainerPtr getFieldContainer(void) const;

    inline const QOSGWidgetFactory *getFactory(void                       ) const;
    inline       QOSGWidgetFactory *getFactory(void                       );
    inline       void               setFactory(QOSGWidgetFactory *pFactory);

    inline const QAbstractFieldEditor *getEditor(UInt32 uiFieldId   ) const;
    inline       QAbstractFieldEditor *getEditor(UInt32 uiFieldId   );

    inline const QAbstractValueEditor *getEditor(UInt32 uiFieldId,
                                                 UInt32 uiValueIndex) const;
    inline       QAbstractValueEditor *getEditor(UInt32 uiFieldId,
                                                 UInt32 uiValueIndex);

    inline bool getReadOnly     (void) const;
    inline bool getLabelsVisible(void) const;

  signals:
    void valueChanged(UInt32 uiFieldId, UInt32 uiValueIndex);

    void actionButtonClicked (UInt32 uiFieldId, UInt32 uiValueIndex);
    void actionButtonPressed (UInt32 uiFieldId, UInt32 uiValueIndex);
    void actionButtonReleased(UInt32 uiFieldId, UInt32 uiValueIndex);

  public slots:
    virtual void setFieldContainer(FieldContainerPtr pFC      );

    virtual void setReadOnly      (bool              bReadOnly);
    virtual void setLabelsVisible (bool              bVisible );

  protected slots:
    virtual void slotActionButtonClicked (QAbstractFieldEditor *pSender,
                                          UInt32                uiValueIndex);
    virtual void slotActionButtonPressed (QAbstractFieldEditor *pSender,
                                          UInt32                uiValueIndex);
    virtual void slotActionButtonReleased(QAbstractFieldEditor *pSender,
                                          UInt32                uiValueIndex);

  private:
    typedef QWidget                             Inherited;

    typedef std::vector<QAbstractFieldEditor *> EditorList;
    typedef EditorList::iterator                EditorListIt;
    typedef EditorList::const_iterator          EditorListConstIt;

    enum TableColNames
    {
        FieldNameCol   = 0,
        FieldValueCol  = 1
    };

    void populateTable  (void);
    void depopulateTable(void);

    void createChildWidgets(void);
    void layoutChildWidgets(void);
    void initSelf          (void);

    FieldContainerPtr  _fcPtr;

    QOSGWidgetFactory *_pFactory;

    QVBoxLayout       *_pVBox;
    QHBoxLayout       *_pHBoxLabels;

    QLabel            *_pLabelFCType;
    QLabel            *_pLabelFCName;

    QTable            *_pTable;

    EditorList         _editors;
    bool               _bReadOnly;
    bool               _bLabelsVisible;
};

OSG_END_NAMESPACE

#include "OSGQFieldContainerEditor_qt.inl"

#define OSGQFIELDCONTAINEREDITORQT_HEADER_CVSID "@(#)$Id: OSGQFieldContainerEditor_qt.h,v 1.1 2004/07/30 15:31:57 neumannc Exp $";

#endif /* _OSGQFIELDCONTAINEREDITOR_QT_H_ */
