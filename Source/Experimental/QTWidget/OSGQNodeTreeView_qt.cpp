


#include "OSGQNodeTreeView_qt.h"
#include "OSGQWidgetFunctions.h"

#include <OSGNode.h>
#include <OSGNodeCore.h>
#include <OSGSimpleAttachments.h>

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGQNodeTreeView_qt.cpp,v 1.1 2003/05/07 14:03:40 neumannc Exp $";
    static Char8 cvsid_hpp[] = OSGQNODETREEVIEW_HEADER_CVSID;
//    static Char8 cvsid_inl[] = OSGQNODETREEVIEW_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

//
// QHeaderItem
//

QHeaderItem::QHeaderItem(QFCItem *parent, const QString &strText)
    : Inherited(parent, strText)
{
}

QHeaderItem::~QHeaderItem(void)
{
}

QHeaderItem *
QHeaderItem::dcast(QListViewItem *pItem)
{
    return dynamic_cast<QHeaderItem *>(pItem);
}

//
// QSceneGraphItem
//

QSceneGraphItem::QSceneGraphItem(QListView *parent)
    : Inherited(parent)
{
}

QSceneGraphItem::QSceneGraphItem(QListViewItem *parent)
    : Inherited(parent)
{
}

QSceneGraphItem::~QSceneGraphItem(void)
{
}

QSceneGraphItem *
QSceneGraphItem::dcast(QListViewItem *pItem)
{
    return dynamic_cast<QSceneGraphItem *>(pItem);
}

void
QSceneGraphItem::setOpen(bool bOpen)
{
    if(bOpen)
        expand();
    else
        collapse();

    Inherited::setOpen(bOpen);
}

UInt32
QSceneGraphItem::getAspect(void)
{
    if(!this->listView())
        return 0;

    QNodeTreeView *pView = QNodeTreeView::dcast(this->listView());

    if(!pView)
        return 0;

    return pView->getAspect();
}

//
// QFCItem
//

QFCItem::QFCItem(QListView *parent, const FieldContainerPtr &pFC)
    : Inherited(parent),
      _pFC     (pFC   )
{
    if(getFC() != NullFC)
    {
        setText(0, QString(getFC()->getType().getCName()));

        if(getName(AttachmentContainerPtr::dcast(getFC())))
            setText(1, 
                    QString(getName(AttachmentContainerPtr::dcast(getFC()))));
        else
            setText(1, QString("unnamed")       );
    }
}

QFCItem::QFCItem(QListViewItem *parent, const FieldContainerPtr &pFC)
    : Inherited(parent),
      _pFC     (pFC   )
{
    if(getFC() != NullFC)
    {
        setText(0, QString(getFC()->getType().getCName()));

        if(getName(AttachmentContainerPtr::dcast(getFC())))
            setText(1, 
                    QString(getName(AttachmentContainerPtr::dcast(getFC()))));
        else
            setText(1, QString("unnamed")       );
    }
}

QFCItem::~QFCItem(void)
{
}

QFCItem *
QFCItem::dcast(QListViewItem *pItem)
{
    return dynamic_cast<QFCItem *>(pItem);
}

FieldContainerPtr
QFCItem::getFC(void) const
{
    return _pFC;
}

void
QFCItem::setup(void)
{
    FieldContainer *pFCAsp = getFC().getAspectCPtr(getAspect());

    if(!pFCAsp)
        return;

    UInt32 uiNumFields = pFCAsp->getType().getNumFieldDescs();
    
    for(UInt32  fieldId = 1; fieldId <= uiNumFields; ++fieldId)
    {
        FieldDescription *pDesc     = 
            pFCAsp->getType().getFieldDescription     (fieldId);
        Field            *pField    = pFCAsp->getField(fieldId);
        const FieldType  &fieldType = pField->getType (       );
        
        if(isSFFieldContainerPtr(pField))
        {
            if(stringcmp(pDesc->getCName(), "parent" ) == 0)
                continue;

            SFFieldContainerPtr *pSFFCPtr = 
                reinterpret_cast<SFFieldContainerPtr *>(pField);

            if(pSFFCPtr->getValue() != NullFC)
            {
                setExpandable(this);
                break;
            }
        }
        else if(isMFFieldContainerPtr(pField))
        {
            MFFieldContainerPtr *pMFFCPtr =
                reinterpret_cast<MFFieldContainerPtr *>(pField);

            if(stringcmp(pDesc->getCName(), "parents") == 0)
            {
                if(pMFFCPtr->size() > 1)
                {
                    setExpandable(this);
                    break;
                }
            }
            else
            {
                if(pMFFCPtr->size() > 0)
                {
                    setExpandable(this);
                    break;
                }
            }
        }
    }

    Inherited::setup();
}

void
QFCItem::expand(void)
{
    if(childCount() != 0)
        return;

    FieldContainer *pFCAsp = getFC().getAspectCPtr(getAspect());

    if(!pFCAsp)
        return;

    FieldContainerType &fcType      = pFCAsp->getType();
    UInt32              uiNumFields = fcType.getNumFieldDescs();

    for(UInt32 fieldId = 1; fieldId <= uiNumFields; ++fieldId)
    {
        FieldDescription *pFieldDesc = fcType.getFieldDescription(fieldId);
        Field            *pField     = pFCAsp->getField          (fieldId);
        const FieldType  &fieldType  = pField->getType           (       ); 
        
        //add Items for all referenced containers (except parents)
        if(isSFFieldContainerPtr(pField))
        {
            if(stringcmp(pFieldDesc->getCName(), "parent" ) == 0)
                continue;

            addRefedContainer(
                reinterpret_cast<SFFieldContainerPtr *>(pField));
        }
        else if(isMFFieldContainerPtr(pField))
        {
            if(stringcmp(pFieldDesc->getCName(), "parents") == 0)
            {
                addParents(
                    reinterpret_cast<MFFieldContainerPtr *>(pField));
            }
            else
            {
                addRefedContainer(
                    reinterpret_cast<MFFieldContainerPtr *>(pField), 
                    pFieldDesc   );
            }
        }

        //add attachments
        if(stringcmp(pFieldDesc->getCName(), "attachments") == 0)
        {
            addAttachments(dynamic_cast<SFAttachmentMap *>(pField));
        }
    }

    PNOTICE << endLog;
}

void
QFCItem::collapse(void)
{
}

void
QFCItem::addRefedContainer(SFFieldContainerPtr *pSFFCPtr)
{
    if(!pSFFCPtr || (pSFFCPtr->getValue() == NullFC))
        return;

    if(pSFFCPtr->getValue()->getType().isNode())
    {
        new QNodeItem(this, NodePtr::dcast(pSFFCPtr->getValue()));
    }
    else if(pSFFCPtr->getValue()->getType().isNodeCore())
    {
        new QNodeCoreItem(this, NodeCorePtr::dcast(pSFFCPtr->getValue()));
    }
    else
    {
        new QFCItem(this, pSFFCPtr->getValue());
    }
}

void
QFCItem::addRefedContainer(MFFieldContainerPtr *pMFFCPtr, 
                           FieldDescription    *pFieldDesc)
{
    if(!pMFFCPtr || !pFieldDesc)
        return;

    MFFieldContainerPtr::reverse_iterator mfIter = pMFFCPtr->rbegin();
    MFFieldContainerPtr::reverse_iterator mfEnd  = pMFFCPtr->rend();

    QHeaderItem *pHeaderItem;

    if(mfIter != mfEnd)
        pHeaderItem = new QHeaderItem(this, pFieldDesc->getCName());

    for(; mfIter != mfEnd; ++mfIter)
    {
        if((*mfIter)->getType().isNode())
        {
            new QNodeItem(pHeaderItem, NodePtr::dcast(*mfIter));
        }
        else if((*mfIter)->getType().isNodeCore())
        {
            new QNodeCoreItem(pHeaderItem, NodeCorePtr::dcast(*mfIter));
        }
        else
        {
            new QFCItem(pHeaderItem, *mfIter);
        }
    }
}

void
QFCItem::addAttachments(SFAttachmentMap *pSFAttMap)
{
    AttachmentMap::reverse_iterator mapIter = pSFAttMap->getValue().rbegin();
    AttachmentMap::reverse_iterator mapEnd  = pSFAttMap->getValue().rend();

    if(mapIter == mapEnd)
        return;
        
    QHeaderItem *pHeaderItem = new QHeaderItem(this, "attachments");

    for(; mapIter != mapEnd; ++mapIter)
    {
        new QFCItem(pHeaderItem, (*mapIter).second);
    }
}

void
QFCItem::addParents(MFFieldContainerPtr *pMFFCPtr)
{
    if(!pMFFCPtr)
        return;

    MFFieldContainerPtr::reverse_iterator mfIter = pMFFCPtr->rbegin();
    MFFieldContainerPtr::reverse_iterator mfEnd  = pMFFCPtr->rend();

    if((mfIter == mfEnd) || (pMFFCPtr->size() <= 1))
        return;

    QHeaderItem *pHeaderItem = new QHeaderItem(this, "parents");  

    for( ; mfIter != mfEnd; ++mfIter)
    {
        if(*mfIter == getFC())
            continue;
        
        if((*mfIter)->getType().isNode())
        {
            new QNodeItem(pHeaderItem, NodePtr::dcast(*mfIter));
        }
        else if((*mfIter)->getType().isNodeCore())
        {
            new QNodeCoreItem(pHeaderItem, NodeCorePtr::dcast(*mfIter));
        }
        else
        {
            new QFCItem(pHeaderItem, *mfIter);
        }
    }   
}    
     
//
// QNodeItem
//

QNodeItem::QNodeItem(QListView *parent, const NodePtr &pNode)
    : Inherited(parent, pNode)
{
}

QNodeItem::QNodeItem(QListViewItem *parent, const NodePtr &pNode)
    : Inherited(parent, pNode)
{
}

QNodeItem::~QNodeItem(void)
{
}

QNodeItem *
QNodeItem::dcast(QListViewItem *pItem)
{
    return dynamic_cast<QNodeItem *>(pItem);
}

//
// QNodeCoreItem
//

QNodeCoreItem::QNodeCoreItem(      QListView   *parent, 
                             const NodeCorePtr &pNodeCore)
    : Inherited (parent, pNodeCore)
{
    if(pNodeCore != NullFC)
    {
        setText(0, QString(pNodeCore->getType().getCName()) + 
                   QString(" NodeCore")                      );

        if(getName(pNodeCore))
            setText(1, QString(getName(pNodeCore)));
        else
            setText(1, QString("unnamed")         );
    }
}

QNodeCoreItem::QNodeCoreItem(      QListViewItem *parent, 
                             const NodeCorePtr   &pNodeCore)
    : Inherited (parent, pNodeCore)
{
    if(pNodeCore != NullFC)
    {
        setText(0, QString(pNodeCore->getType().getCName()) + 
                   QString(" NodeCore")                      );

        if(getName(pNodeCore))
            setText(1, QString(getName(pNodeCore)));
        else
            setText(1, QString("unnamed")         );
    }
}

QNodeCoreItem::~QNodeCoreItem(void)
{
}

QNodeCoreItem *
QNodeCoreItem::dcast(QListViewItem *pItem)
{
    return dynamic_cast<QNodeCoreItem *>(pItem);
}

//
// QNodeTreeView
//

QNodeTreeView::QNodeTreeView(QWidget *parent, const char *name)
    : Inherited      (parent, name                     ),
      _pRoot         (NullFC                           ),
      _uiAspect      (Thread::getCurrent()->getAspect())
{
    setRootIsDecorated    (true              );
    setAllColumnsShowFocus(true              );
    setSorting            (-1                );
    addColumn             (QString("FC Type"));
    addColumn             (QString("FC Name"));
}

QNodeTreeView::~QNodeTreeView(void)
{
}

QNodeTreeView *
QNodeTreeView::dcast(QListView *pView)
{
    return dynamic_cast<QNodeTreeView *>(pView);
}

FieldContainerPtr
QNodeTreeView::getRoot(void)
{
    return _pRoot;
}

const FieldContainerPtr
QNodeTreeView::getRoot(void) const
{
    return _pRoot;
}

UInt32
QNodeTreeView::getAspect(void) const
{
    return _uiAspect;
}

FieldContainerPtr
QNodeTreeView::getSelectedFC(void) const
{
    if(!selectedItem())
        return NullFC;

    QSceneGraphItem *pSGItem = dynamic_cast<QSceneGraphItem *>(selectedItem());

    if(pSGItem)
        return pSGItem->getFC();
    else
        return NullFC;
}

QFCItem *
QNodeTreeView::rereadTree(void)
{
    removeChildren(firstChild());
    
    delete firstChild();

    return new QFCItem(this, _pRoot);
}

void
QNodeTreeView::setRoot(const FieldContainerPtr &pRoot)
{
    if(_pRoot != pRoot)
    {
        _pRoot = pRoot;

        QFCItem *pRootItem = rereadTree();
 
        setSelected(pRootItem, true);
    }
}

void
QNodeTreeView::setAspect(UInt32 uiAspect)
{
    _uiAspect = uiAspect;

    QFCItem *pRootItem = rereadTree();

    setSelected(pRootItem, true);
}

void
QNodeTreeView::setSelectedFC(const FieldContainerPtr &pFC)
{
    doSelectFC(pFC);
}

void
QNodeTreeView::removeChildren(QListViewItem *pItem)
{
    if(!pItem)
        return;
    
    for(QListViewItem *pChild = pItem->firstChild(); pChild; 
        pChild = pItem->firstChild())
    {
        delete pChild;
    }
}

void
QNodeTreeView::doSelectFC(const FieldContainerPtr &pFC)
{
    if(pFC == getSelectedFC())
        return;

    BranchType         branch;
    QListViewItem     *pSelectedItem = this->selectedItem ();

    if(getBranch(pFC, branch))
    {
        expandBranch(branch);
    }
    else
    {
        QListViewItem *pItem = findItemInChildren(pFC, pSelectedItem);

        if(pItem)
        {
            this->setSelected      (pItem, true);
            this->ensureItemVisible(pItem      );
        }
    }
}

bool
QNodeTreeView::getBranch(const FieldContainerPtr &pFromFC, BranchType &branch)
{
    branch.clear();

    if(pFromFC == NullFC)
        return false;

    return getBranchRecursion(pFromFC, branch);
}

bool
QNodeTreeView::getBranchRecursion(const FieldContainerPtr &pFromFC, 
                                        BranchType        &branch  )
{
    if(pFromFC == NullFC)
    {
        return false;
    }
    else if(pFromFC == getRoot())
    {
        return true;
    }
    else
    {
        branch.push_front(pFromFC);

        Field *pParentsField = getParentsField(pFromFC, getAspect());

        if(!pParentsField)
        {
            return false;
        }

        if(pParentsField->getCardinality() == FieldType::SINGLE_FIELD)
        {
            SFFieldContainerPtr *pSFParent =
                reinterpret_cast<SFFieldContainerPtr *>(pParentsField);
            
            if(getBranchRecursion(pSFParent->getValue(), branch))
            {
                return true;
            }
            else
            {
                branch.pop_front();

                return false;
            }
        }
        else
        {
            MFFieldContainerPtr *pMFParent =
                reinterpret_cast<MFFieldContainerPtr *>(pParentsField);
            
            MFFieldContainerPtr::iterator mfIter = pMFParent->begin();
            MFFieldContainerPtr::iterator mfEnd  = pMFParent->end();

            for(; mfIter != mfEnd; ++mfIter)
            {
                if(getBranchRecursion(*mfIter, branch))
                {
                    return true;
                }
                else
                {
                    branch.pop_front();
                }
            }
        }
    }

    return false;
}

void
QNodeTreeView::expandBranch(const BranchType &branch)
{
    BranchTypeConstIt  bIter = branch.begin();
    BranchTypeConstIt  bEnd  = branch.end  ();

    QListViewItem     *pPrevItem = NULL;
    QListViewItem     *pCurrItem = this->firstChild();

    for(; bIter != bEnd; ++bIter)
    {
        pPrevItem = pCurrItem;
        pCurrItem = findItemInChildren(*bIter, pCurrItem);

        if(!pCurrItem)
        {
            SWARNING << "QNodeTreeView::expandBranch(): FAILED. " 
                     << "Expanding as far as possible. "
                     << endLog;

            break;
        }
    }

    if(pCurrItem)
    {
        this->setSelected      (pCurrItem, true);
        this->ensureItemVisible(pCurrItem      );
    }
    else if(pPrevItem)
    {
        this->setSelected      (pPrevItem, true);
        this->ensureItemVisible(pPrevItem      );
    }
}

QListViewItem *
QNodeTreeView::findItemInChildren(const FieldContainerPtr &pFC, 
                                        QListViewItem     *pParentItem)
{
    if(!pParentItem || (pFC == NullFC))
        return NULL;

    QSceneGraphItem *pParentSGItem = QSceneGraphItem::dcast(pParentItem);

    if(pParentSGItem)
        pParentSGItem->expand(); // make sure children are created

    for(QListViewItem *pChild = pParentItem->firstChild(); 
        pChild;        pChild = pChild->nextSibling()     )
    {
        QSceneGraphItem *pSGItem = QSceneGraphItem::dcast(pChild);
        QHeaderItem     *pHItem  = QHeaderItem::dcast    (pChild);

        if(pSGItem && pSGItem->getFC() == pFC)
            return pSGItem;

        if(pHItem && (pHItem->childCount() > 0))
        {
            for(QListViewItem *pHChild = pHItem->firstChild();
                pHChild;       pHChild = pHChild->nextSibling())
            {
                QSceneGraphItem *pHSGItem = QSceneGraphItem::dcast(pHChild);

                if(pHSGItem && (pHSGItem->getFC() == pFC))
                    return pHSGItem;
            }
        }
    }

    return NULL;
}

            


#include "OSGQNodeTreeView_qt_moc.cpp"
