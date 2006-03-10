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

#ifndef _OSGQNODETREEVIEW_H_
#define _OSGQNODETREEVIEW_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGWindowQT4Def.h"

#include <OSGNode.h>
#include <OSGFieldContainerFields.h>

#include <list>

#include <q3listview.h>

OSG_BEGIN_NAMESPACE

class QFCItem;

class OSG_WINDOWQTLIB_DLLMAPPING QHeaderItem : public Q3ListViewItem
{
public:
             QHeaderItem(QFCItem *parent, const QString &strText);

    virtual ~QHeaderItem(void                                   );

    static   QHeaderItem *dcast(Q3ListViewItem *pItem);

private:
    typedef Q3ListViewItem Inherited;
};

class OSG_WINDOWQTLIB_DLLMAPPING QSceneGraphItem : public Q3ListViewItem
{
public:
             QSceneGraphItem(Q3ListView     *parent);
             QSceneGraphItem(Q3ListViewItem *parent);
    virtual ~QSceneGraphItem(void                 );

    static   QSceneGraphItem   *dcast    (Q3ListViewItem *pItem);

    virtual  FieldContainerPtr  getFC    (void                ) const = 0;
    
    virtual  void               setOpen  (bool bOpen          );

    virtual  void               expand   (void                )       = 0;
    virtual  void               collapse (void                )       = 0;

protected:
             UInt32             getAspect(void                );

private:
    typedef Q3ListViewItem Inherited;
};


class OSG_WINDOWQTLIB_DLLMAPPING QFCItem : public QSceneGraphItem
{
public:
    QFCItem(Q3ListView     *parent, const FieldContainerPtr &pFC);
    QFCItem(Q3ListViewItem *parent, const FieldContainerPtr &pFC);

    virtual ~QFCItem(void);

    static QFCItem *dcast(Q3ListViewItem *pItem);

    virtual FieldContainerPtr  getFC   (void) const;

    virtual void               setup   (void);

    virtual void               expand  (void);
    virtual void               collapse(void);

private:
    typedef QSceneGraphItem Inherited;

    void addRefedContainer(SFFieldContainerPtr *pSFFCPtr  );
    void addRefedContainer(MFFieldContainerPtr *pMFFCPtr, 
                           FieldDescription    *pFieldDesc);
    void addAttachments   (SFAttachmentMap     *pSFAttMap );
    void addParents       (MFFieldContainerPtr *pMFFCPtr  );

    FieldContainerPtr _pFC;
};

class OSG_WINDOWQTLIB_DLLMAPPING QNodeItem : public QFCItem
{
public:
    QNodeItem(Q3ListView     *parent, const NodePtr &pNode);
    QNodeItem(Q3ListViewItem *parent, const NodePtr &pNode);

    virtual ~QNodeItem(void);

    static QNodeItem *dcast(Q3ListViewItem *pItem);

private:
    typedef QFCItem Inherited;
};

class OSG_WINDOWQTLIB_DLLMAPPING QNodeCoreItem : public QFCItem
{
public:
            QNodeCoreItem(Q3ListView     *parent, const NodeCorePtr &pNodeCore);
            QNodeCoreItem(Q3ListViewItem *parent, const NodeCorePtr &pNodeCore);
    virtual ~QNodeCoreItem(void);

    static  QNodeCoreItem *dcast(Q3ListViewItem *pItem);

private:
    typedef QFCItem Inherited;
};

class OSG_WINDOWQTLIB_DLLMAPPING QNodeTreeView : public Q3ListView
{
    Q_OBJECT

public:
    QNodeTreeView(QWidget *parent, const char *name=NULL);
    
    virtual  ~QNodeTreeView(void);

    static QNodeTreeView   *dcast        (      Q3ListView       *pView);

          FieldContainerPtr getRoot      (void                         );
    const FieldContainerPtr getRoot      (void                         ) const;

          UInt32            getAspect    (void                         ) const;

          FieldContainerPtr getSelectedFC(void                         ) const;

          QFCItem          *rereadTree   (void                         );

public slots:
          void              setRoot      (const FieldContainerPtr &pRoot   );
          void              setAspect    (      UInt32             uiAspect);
          void              setSelectedFC(const FieldContainerPtr &pFC     );

private:
    typedef Q3ListView                    Inherited;

    typedef std::list<FieldContainerPtr> BranchType;
    typedef BranchType::iterator         BranchTypeIt;
    typedef BranchType::const_iterator   BranchTypeConstIt;

    void removeChildren    (      Q3ListViewItem     *pItem   );

    void doSelectFC        (const FieldContainerPtr &pFC     );

    bool getBranch         (const FieldContainerPtr &pFromFC, 
                                  BranchType        &branch  );
    bool getBranchRecursion(const FieldContainerPtr &pFC, 
                                  BranchType        &branch  );
    void expandBranch      (const BranchType        &branch  );

    Q3ListViewItem *findItemInChildren(const FieldContainerPtr &pFC,
                                            Q3ListViewItem     *pParentItem);

    FieldContainerPtr _pRoot;
    UInt32            _uiAspect;
};

OSG_END_NAMESPACE

#define OSGQNODETREEVIEW_HEADER_CVSID "@(#)$Id: OSGQ4NodeTreeView_qt.h,v 1.1 2006/03/10 18:30:35 a-m-z Exp $"

// #include "OSGQNodeTreeView_qt.inl"

#endif /* _OSGQNODETREEVIEW_H_ */
