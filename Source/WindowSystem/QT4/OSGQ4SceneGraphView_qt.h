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

#ifndef _OSGQSCENEGRAPHVIEW_H_
#define _OSGQSCENEGRAPHVIEW_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGWindowQT4Def.h"

#include <OSGNode.h>

#include <qwidget.h>
//Added by qt3to4:
#include <Q3VBoxLayout>
#include <Q3HBoxLayout>
#include <QLabel>

class Q3HBoxLayout;
class Q3VBoxLayout;
class QSplitter;
class Q3ComboBox;
class QLabel;
class QLineEdit;
class QPushButton;
class Q3ListViewItem;

OSG_BEGIN_NAMESPACE

class QNodeTreeView;
class QSceneGraphItem;
class QFieldContainerView;

class OSG_WINDOWQTLIB_DLLMAPPING QSceneGraphView : public QWidget
{
    Q_OBJECT

public:
    QSceneGraphView(      QWidget           *parent, const char *name=NULL);
    QSceneGraphView(const FieldContainerPtr &pRoot, 
                          QWidget           *parent, const char *name=NULL);

    virtual ~QSceneGraphView(void);

public slots:
    void setRoot   (const FieldContainerPtr &pRoot   );
    void showAspect(      UInt32             uiAspect); 

protected slots:
    void onAspectSelected    (int  index);
    void onUpdateClicked     (void      );
    void onForwardClicked    (void      );
    void onBackwardClicked   (void      );
    void onRawAddressEntered (void      );

    void onFieldClicked      (FieldContainerPtr pFC,     UInt32    uiFieldId,
                              UInt32            uiIndex, Qt::ButtonState  button );
    void onFieldDoubleClicked(FieldContainerPtr pFC,     UInt32    uiFieldId,
                              UInt32            uiIndex, Qt::ButtonState  button );
    
    void onSelectionChanged  (Q3ListViewItem    *pItem                        );

private:
    typedef QWidget Inherited;

    struct HistoryEntry
    {
        HistoryEntry(const FieldContainerPtr &pRootFC, 
                     const FieldContainerPtr &pSelectedFC, UInt32 uiAspect);

        FieldContainerPtr _pRootFC;
        FieldContainerPtr _pSelectedFC;
        UInt32            _uiAspect;
    };

    typedef std::list<HistoryEntry>     HistoryList;
    typedef HistoryList::iterator       HistoryListIt;
    typedef HistoryList::const_iterator HistoryListConstIt;

    void createChildWidgets (void);
    void connectChildWidgets(void);
  
    void doSetRoot                   (const FieldContainerPtr &pRootFC );
    void doShowAspect                (      UInt32             uiAspect);

    void appendHistoryEntry          (void);
    void clearHistory                (void);
    void selectPrevHistoryEntry      (void);
    void selectNextHistoryEntry      (void);
    void enableHistoryButtons        (void);

    FieldContainerPtr    _pRootFC;
    FieldContainerPtr    _pSelectedFC;
    UInt32               _uiAspect;

    HistoryList          _history;
    UInt32               _uiMaxHistorySize;
    HistoryListIt        _currentHistoryEntry;
    bool                 _bRestoringHistory;

    Q3HBoxLayout         *_pGlobalLayout;

    QSplitter           *_pSplitter;
    
    Q3VBoxLayout         *_pVBoxLeft;
    Q3ComboBox           *_pCBAspect;
    QNodeTreeView      **_pTreeView;
    QLabel              *_pLabelRawAddress;
    QLineEdit           *_pLERawAddress;
    QPushButton         *_pPBUpdate;
    Q3HBoxLayout         *_pHBoxHistoryButtons;
    QPushButton         *_pPBBackward;
    QPushButton         *_pPBForward;

    Q3VBoxLayout         *_pVBoxRight;
    QFieldContainerView *_pFCView;
    Q3HBoxLayout         *_pHBoxFCHeader;
    QLabel              *_pLabelFCName;
    QPushButton         *_pPBShowTypeColumn;
};

OSG_END_NAMESPACE

#define OSGQSCENEGRAPHVIEW_HEADER_CVSID "@(#)$Id: OSGQ4SceneGraphView_qt.h,v 1.1 2006/03/10 18:30:35 a-m-z Exp $"

// #include "OSGQSceneGraphView_qt.inl"

#endif /* _OSGQSCENEGRAPHVIEW_H_ */
