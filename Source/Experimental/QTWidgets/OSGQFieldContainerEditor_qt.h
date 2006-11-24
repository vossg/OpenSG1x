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

#include <qstring.h>
#include <qwidget.h>

#include <vector>
#include <stack>

class QLabel;
class QPushButton;
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
    void valueChanged  (UInt32 fieldId, UInt32 valueIndex                 );
    void genericRequest(UInt32 fieldId, UInt32 valueIndex, QString request);
    void changeCommited(UInt32 fieldId                                    );

  public slots:
    virtual void setFieldContainer(FieldContainerPtr pFC      );

    virtual void setReadOnly      (bool              bReadOnly);
    virtual void setLabelsVisible (bool              bVisible );

  protected slots:
    virtual void slotValueChanged  (QAbstractFieldEditor *pSender,
                                    UInt32                valueIndex  );
    virtual void slotGenericRequest(QAbstractFieldEditor *pSender,
                                    UInt32                valueIndex,
                                    QString               request     );
    virtual void slotChangeCommited(QAbstractFieldEditor *pSender     );

  private slots:
    void slotButtonBackClicked(void);

  private:
    typedef QWidget                             Inherited;

    typedef std::vector<QAbstractFieldEditor *> EditorList;
    typedef EditorList::iterator                EditorListIt;
    typedef EditorList::const_iterator          EditorListConstIt;

    typedef std::stack<FieldContainerPtr>       HistoryStack;

    enum TableColNames
    {
        FieldNameCol   = 0,
        FieldValueCol  = 1
    };

    void populateTable  (void);
    void depopulateTable(void);

    void initStatic        (void);
    void createChildWidgets(void);
    void layoutChildWidgets(void);
    void initSelf          (void);

    static QPixmap     *_pPixmapLeft;

    FieldContainerPtr  _fcPtr;

    QOSGWidgetFactory *_pFactory;

    QVBoxLayout       *_pVBox;
    QHBoxLayout       *_pHBoxLabels;

    QPushButton       *_pButtonBack;
    QLabel            *_pLabelFCType;
    QLabel            *_pLabelFCName;

    QTable            *_pTable;

    EditorList         _editors;
    bool               _bReadOnly;
    bool               _bLabelsVisible;

    HistoryStack       _history;
};

OSG_END_NAMESPACE

#include "OSGQFieldContainerEditor_qt.inl"

#define OSGQFIELDCONTAINEREDITORQT_HEADER_CVSID "@(#)$Id: OSGQFieldContainerEditor_qt.h,v 1.4 2006/11/24 13:54:26 a-m-z Exp $";

#endif /* _OSGQFIELDCONTAINEREDITOR_QT_H_ */
