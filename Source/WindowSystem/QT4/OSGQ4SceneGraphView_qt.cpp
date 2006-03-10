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

#include "OSGQ4SceneGraphView_qt.h"

#include "OSGQ4NodeTreeView_qt.h"
#include "OSGQ4FieldContainerView_qt.h"
#include "OSGQ4WidgetFunctions.h"

#include <OSGSimpleAttachments.h>
#include <OSGLog.h>
#include <OSGFieldContainerFactory.h>
#include <OSGThreadManager.h>

#include <qsplitter.h>
#include <qlayout.h>
#include <q3combobox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qstring.h>
//Added by qt3to4:
#include <Q3VBoxLayout>
#include <Q3HBoxLayout>

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGQ4SceneGraphView_qt.cpp,v 1.1 2006/03/10 18:30:35 a-m-z Exp $";
    static Char8 cvsid_hpp[] = OSGQSCENEGRAPHVIEW_HEADER_CVSID;
//    static Char8 cvsid_inl[] = OSGQSCENEGRAPHVIEW_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

QSceneGraphView::QSceneGraphView(QWidget *parent, const char *name)
    : Inherited           (parent, name  ),
      _pRootFC            (NullFC        ),
      _pSelectedFC        (NullFC        ),
      _uiAspect           (0             ),
      _history            (              ),
      _uiMaxHistorySize   (10            ),
      _currentHistoryEntry(_history.end()),
      _bRestoringHistory  (false         ),
      _pGlobalLayout      (NULL          ),
      _pSplitter          (NULL          ),
      _pVBoxLeft          (NULL          ),
      _pCBAspect          (NULL          ),
      _pTreeView          (NULL          ),
      _pLabelRawAddress   (NULL          ),
      _pLERawAddress      (NULL          ),
      _pPBUpdate          (NULL          ),
      _pHBoxHistoryButtons(NULL          ),
      _pPBBackward        (NULL          ),
      _pPBForward         (NULL          ),
      _pVBoxRight         (NULL          ),
      _pFCView            (NULL          ),
      _pHBoxFCHeader      (NULL          ),
      _pLabelFCName       (NULL          ),
      _pPBShowTypeColumn  (NULL          )
{
    _uiAspect  = Thread::getCurrent()->getAspect();
    _pTreeView = new QNodeTreeView *[ThreadManager::getNumAspects()];

    createChildWidgets();
    connectChildWidgets();
}

QSceneGraphView::QSceneGraphView(const FieldContainerPtr &pRoot,
                                       QWidget           *parent, 
                                 const char              *name)
    : Inherited           (parent, name  ),
      _pRootFC            (NullFC        ),
      _pSelectedFC        (NullFC        ),
      _uiAspect           (0             ),
      _history            (              ),
      _uiMaxHistorySize   (10            ),
      _currentHistoryEntry(_history.end()),
      _bRestoringHistory  (false         ),
      _pGlobalLayout      (NULL          ),
      _pSplitter          (NULL          ),
      _pVBoxLeft          (NULL          ),
      _pCBAspect          (NULL          ),
      _pTreeView          (NULL          ),
      _pLabelRawAddress   (NULL          ),
      _pLERawAddress      (NULL          ),
      _pPBUpdate          (NULL          ),
      _pHBoxHistoryButtons(NULL          ),
      _pPBBackward        (NULL          ),
      _pPBForward         (NULL          ),
      _pVBoxRight         (NULL          ),
      _pFCView            (NULL          ),
      _pHBoxFCHeader      (NULL          ),
      _pLabelFCName       (NULL          ),
      _pPBShowTypeColumn  (NULL          )
{
    _uiAspect  = Thread::getCurrent()->getAspect();
    _pTreeView = new QNodeTreeView *[ThreadManager::getNumAspects()];
    
    createChildWidgets();
    connectChildWidgets();

    setRoot(pRoot);
}

QSceneGraphView::~QSceneGraphView(void)
{
}

void
QSceneGraphView::setRoot(const FieldContainerPtr &pRootFC)
{
    doSetRoot(pRootFC);

    if(!_bRestoringHistory)
        appendHistoryEntry();
}
 
void
QSceneGraphView::showAspect(UInt32 uiAspect)
{
    if(_pCBAspect->currentItem() != uiAspect)
        _pCBAspect->setCurrentItem(uiAspect);
}

void
QSceneGraphView::onAspectSelected(int index)
{
    doShowAspect(index);

    if(!_bRestoringHistory)
        appendHistoryEntry();
}

void
QSceneGraphView::onUpdateClicked(void)
{
    SNOTICE << "onUpdateClicked" << endLog;

    UInt32            uiNumAspects = ThreadManager::the()->getNumAspects();
    FieldContainerPtr pFC          = _pSelectedFC;

    for(UInt32 i = 0; i < uiNumAspects; ++i)
    {
        _pTreeView[i]->rereadTree();
    }
    
    _pTreeView[_uiAspect]->setSelectedFC(pFC);
}

void
QSceneGraphView::onForwardClicked(void)
{
    selectNextHistoryEntry();
}

void
QSceneGraphView::onBackwardClicked(void)
{
    selectPrevHistoryEntry();
}

void
QSceneGraphView::onRawAddressEntered(void)
{
    SNOTICE << "onRawAddressEntered" << endLog;

    typedef std::vector<FieldContainerPtr>      FieldContainerStore;
    typedef FieldContainerStore::const_iterator FieldContainerStoreConstIt;

    void           *pAddress   = NULL;
    FieldContainer *pAddressFC = NULL;

    FieldContainerPtr pFC      = NullFC;
    UInt32            uiAspect = 0;

    FieldDataTraits<void *>::getFromString(pAddress, _pLERawAddress->text());

    if(pAddress == NULL)
    {
        std::cout << _pLERawAddress->text().latin1() << std::endl;
        FWARNING(("Raw Address '%s' not understood\n",
            _pLERawAddress->text().latin1()));
        return;
    }
    
    pAddressFC = reinterpret_cast<FieldContainer *>(pAddress);

    const FieldContainerStore *pFCStore = 
        FieldContainerFactory::the()->getFieldContainerStore();

    FieldContainerStoreConstIt fcStoreIter  = pFCStore->begin();
    FieldContainerStoreConstIt fcStoreEnd   = pFCStore->end  ();
    
    UInt32                     uiNumAspects = ThreadManager::getNumAspects();
    bool                       bFoundFC     = false;

    SNOTICE << "FCStore.size() == " << pFCStore->size() << " ";

    for(; (fcStoreIter != fcStoreEnd) && !bFoundFC; ++fcStoreIter)
    {
        PNOTICE << ".";

        for(UInt32 uiAsp=0; (uiAsp < uiNumAspects) && !bFoundFC; ++uiAsp)
        {
            FieldContainer *pTestFC = (*fcStoreIter).getAspectCPtr(uiAsp);

            if(pTestFC == pAddressFC)
            {
                SNOTICE << "onRawAddressEntered: found valid FieldContainer."
                     << endLog;

                pFC      = *fcStoreIter;
                uiAspect = uiAsp;

                bFoundFC = true;

                break;
            }
        }
    }

    PNOTICE << endLog;

    if(!bFoundFC)
    {
        SWARNING << "Could NOT find a FieldContainer at address: "
                 << pAddress
                 << endLog;
        
        return;
    }

    _pTreeView[uiAspect]->setSelectedFC(pFC);
    
    showAspect(uiAspect);
}


void
QSceneGraphView::onFieldClicked(FieldContainerPtr OSG_CHECK_ARG(pFC),
                                UInt32            OSG_CHECK_ARG(uiFieldId),
                                UInt32            OSG_CHECK_ARG(uiIndex),  
                                Qt::ButtonState       OSG_CHECK_ARG(button)    )
{
}

void
QSceneGraphView::onFieldDoubleClicked(FieldContainerPtr pFC,     
                                      UInt32            uiFieldId,
                                      UInt32            uiIndex, 
                                      Qt::ButtonState       button    )
{
    Field *pField = pFC->getField(uiFieldId);

    switch(button)
    {
    case Qt::LeftButton: 
        {
        if(isSFFieldContainerPtr(pField))
        {
            SFFieldContainerPtr *pSFFCPtr = 
                reinterpret_cast<SFFieldContainerPtr *>(pField);
                
            _pTreeView[_uiAspect]->setSelectedFC(pSFFCPtr->getValue()       );
        }
        else if(isMFFieldContainerPtr(pField))
        {
            MFFieldContainerPtr *pMFFCPtr =
                reinterpret_cast<MFFieldContainerPtr *>(pField);

            _pTreeView[_uiAspect]->setSelectedFC((*pMFFCPtr)[uiIndex]);
        }
        
        }
        break;
    case Qt::RightButton:
        {
            _pFCView->beginEdit(uiFieldId, uiIndex);
        }
        break;
    default:
        break;
    }
}

void
QSceneGraphView::onSelectionChanged(Q3ListViewItem *pItem)
{
    QSceneGraphItem *pSGItem = QSceneGraphItem::dcast(pItem);

    if(pSGItem)
    {
        AttachmentContainerPtr pAttCon   = 
            AttachmentContainerPtr::dcast(pSGItem->getFC());
        const FieldContainerType &fcType = pSGItem->getFC()->getType();

        if((pAttCon != NullFC) && (getName(pAttCon) != NULL))
        {
            _pLabelFCName->setText(QString(fcType.getCName() ) +
                                   QString(": "              ) +
                                   QString(getName(pAttCon)  )  );
        }
        else
        {
            _pLabelFCName->setText(QString(fcType.getCName())  );
        }

        _pFCView->setFieldContainer(pSGItem->getFC());

        _pSelectedFC = pSGItem->getFC();

        if(!_bRestoringHistory)
            appendHistoryEntry();
    }      
}

void
QSceneGraphView::createChildWidgets(void)
{
    UInt32  numAspects = ThreadManager::getNumAspects();
    QString strAspect;

    _pGlobalLayout = new Q3HBoxLayout(this, 10, 5, 
                                     "QSceneGraphView::_pGlobalLayout");

    _pSplitter     = new QSplitter  (Qt::Horizontal, this, 
                                     "QSceneGraphView::_pSplitter");

    QWidget *pSplitterHelper1 = new QWidget(_pSplitter, "pSplitterHelper1");
    QWidget *pSplitterHelper2 = new QWidget(_pSplitter, "pSplitterHelper2");

    _pVBoxLeft = new Q3VBoxLayout(pSplitterHelper1, 5, 5, 
                                 "QSceneGraphView::_pVBoxLeft");
    
    _pCBAspect = new Q3ComboBox  (false, pSplitterHelper1, 
                                 "QSceneGraphView::_pCBAspect");
    
    for(UInt32 i=0; i < numAspects; ++i)
    {
        strAspect.setNum(i);

        _pCBAspect->insertItem("Aspect " + strAspect);
    }

    _pVBoxLeft->addWidget(_pCBAspect);

    _pHBoxHistoryButtons = new Q3HBoxLayout(
        NULL, 0, 5, "QSceneGraphView::_pHBoxHistoryButtons");
    _pPBBackward         = new QPushButton("<<", pSplitterHelper1, 
                                           "QSceneGraphView::_pPBBackward");
    _pPBBackward->setEnabled(false);
    _pHBoxHistoryButtons->addWidget(_pPBBackward);

    _pPBForward          = new QPushButton(">>", pSplitterHelper1,
                                           "QSceneGraphView::_pPBForward");
    _pPBForward->setEnabled(false);
    _pHBoxHistoryButtons->addWidget(_pPBForward);

    _pVBoxLeft->addLayout(_pHBoxHistoryButtons);

    for(UInt32 i=0; i < numAspects; ++i)
    {
        _pTreeView[i] = new QNodeTreeView(pSplitterHelper1, 
                                          "QSceneGraphView::_pTreeView");

        _pTreeView[i]->setAspect(i);

        if(i != _uiAspect)
        {
            _pTreeView[i]->hide();
        }
        else
        {
            _pTreeView[i]->show();
        }

        _pVBoxLeft->addWidget(_pTreeView[i]);
    }

    _pLabelRawAddress  = new QLabel("Display FC at address:", pSplitterHelper1,
                                    "QSceneGraphView::_pLabelRawAddress");
    _pVBoxLeft->addWidget(_pLabelRawAddress);

    _pLERawAddress     = new QLineEdit(pSplitterHelper1, 
                                       "QSceneGraphView::_pLERawAddress");
    _pVBoxLeft->addWidget(_pLERawAddress);

    _pPBUpdate         = new QPushButton("Update", pSplitterHelper1,
                                         "QSceneGraphView::_pPBUpdate");
    _pVBoxLeft->addWidget(_pPBUpdate);

    _pVBoxRight        = new Q3VBoxLayout(pSplitterHelper2, 5, 5, 
                                         "QSceneGraphView::_pVBoxRight");

    _pHBoxFCHeader     = new Q3HBoxLayout(NULL, 0, 5, 
                                         "QSceneGraphView::_pHBoxFCHeader");
    _pLabelFCName      = new QLabel(pSplitterHelper2, 
                                    "QSceneGraphView::_pLabelFCName");
    _pHBoxFCHeader->addWidget(_pLabelFCName);
    
    _pPBShowTypeColumn = new QPushButton("Show Types", pSplitterHelper2,
                                        "QSceneGraphView::_pPBShowTypeColumn");
    _pPBShowTypeColumn->setToggleButton(true);
    _pPBShowTypeColumn->setOn          (true);
    _pHBoxFCHeader->addWidget(_pPBShowTypeColumn);

    _pVBoxRight->addLayout(_pHBoxFCHeader);

    _pFCView           = new QFieldContainerView(pSplitterHelper2, 
                                                 "QSceneGraphView::_pFCView");
    _pVBoxRight->addWidget   (_pFCView  );

    _pGlobalLayout->addWidget(_pSplitter);
}

void
QSceneGraphView::connectChildWidgets(void)
{
    connect(_pCBAspect,     SIGNAL(highlighted         (int )),
            this,           SLOT  (onAspectSelected    (int )));

    connect(_pPBForward,    SIGNAL(clicked             (void)),
            this,           SLOT  (onForwardClicked    (void)));

    connect(_pPBBackward,   SIGNAL(clicked             (void)),
            this,           SLOT  (onBackwardClicked   (void)));

    connect(_pLERawAddress, SIGNAL(returnPressed       (void)),
            this,           SLOT  (onRawAddressEntered (void)));

    connect(_pPBUpdate,     SIGNAL(clicked             (void)),
            this,           SLOT  (onUpdateClicked     (void)));

    connect(_pFCView, SIGNAL(clicked       (FieldContainerPtr, UInt32, 
                                            UInt32,            Qt::ButtonState)),
            this,     SLOT  (onFieldClicked(FieldContainerPtr, UInt32, 
                                            UInt32,            Qt::ButtonState)));

    connect(_pFCView, 
            SIGNAL(doubleClicked       (FieldContainerPtr, UInt32, 
                                        UInt32,            Qt::ButtonState)),
            this,     
            SLOT  (onFieldDoubleClicked(FieldContainerPtr, UInt32, 
                                        UInt32,            Qt::ButtonState))
           );

    connect(_pPBShowTypeColumn, SIGNAL(toggled             (bool)),
            _pFCView,           SLOT  (setShowTypeColumn   (bool)));

    connect(_pTreeView[_uiAspect],
            SIGNAL(selectionChanged  (Q3ListViewItem *)),
            this,
            SLOT  (onSelectionChanged(Q3ListViewItem *)));
}

void
QSceneGraphView::doSetRoot(const FieldContainerPtr &pRootFC)
{
    UInt32 uiNumAspects = ThreadManager::getNumAspects();

    _pRootFC = pRootFC;

    for(UInt32 i=0; i < uiNumAspects; ++i)
        _pTreeView[i]->setRoot(pRootFC);
}

void
QSceneGraphView::doShowAspect(UInt32 uiAspect)
{
    disconnect(_pTreeView[_uiAspect],
               SIGNAL(selectionChanged  (Q3ListViewItem *)),
               this,
               SLOT  (onSelectionChanged(Q3ListViewItem *)));

    _pTreeView[_uiAspect]->hide();

    _uiAspect = uiAspect;

    _pTreeView[uiAspect]->setSelectedFC(_pSelectedFC);
    _pTreeView[uiAspect]->show         (            );

    _pFCView->setAspect(uiAspect);

    connect(_pTreeView[uiAspect], SIGNAL(selectionChanged  (Q3ListViewItem *)),
            this,                 SLOT  (onSelectionChanged(Q3ListViewItem *)));
}

void
QSceneGraphView::appendHistoryEntry(void)
{
    SNOTICE << "QSceneGraphView::appendHistoryEntry "
            << "_history.size(): " << _history.size();
    
    if(_uiMaxHistorySize == 0)
    {
        PNOTICE << " _uiMaxHistorySize == 0" << endLog;
        return;
    }

    if(_history.size() == 0)
    {
        PNOTICE << " _history.size() == 0" << endLog;

        _history.push_back(HistoryEntry(_pRootFC, _pSelectedFC, _uiAspect));
        
        _currentHistoryEntry = _history.begin();
    }
    else
    {
        HistoryListIt histIter = _currentHistoryEntry;

        if( ((*_currentHistoryEntry)._pRootFC     == _pRootFC    ) &&
            ((*_currentHistoryEntry)._pSelectedFC == _pSelectedFC) &&
            ((*_currentHistoryEntry)._uiAspect    == _uiAspect   )   )
        {
            PNOTICE << " _currentHistoryEntry == \"internal state\"" << endLog;
            return;
        }

        PNOTICE << " deleting obsolete parts of history and adding new" 
                << endLog;

        _history.erase(++histIter, _history.end());

        while(_history.size() >= _uiMaxHistorySize)
        {
            _history.pop_front();
        }

        _history.push_back(HistoryEntry(_pRootFC, _pSelectedFC, _uiAspect));
    
        _currentHistoryEntry = --(_history.end());
    }

    enableHistoryButtons();
}

void
QSceneGraphView::selectPrevHistoryEntry(void)
{
    SNOTICE << "select PREV history:\n "
            << "CURRENT: " << _currentHistoryEntry->_pRootFC
            << " "         << _currentHistoryEntry->_pSelectedFC
            << " "         << _currentHistoryEntry->_uiAspect;

    HistoryListIt histIter = _currentHistoryEntry;

    if((_history.size() == 0) || (histIter == _history.begin()))
        return;

    --histIter;

    PNOTICE << "\n NEW: " << histIter->_pRootFC
            << " "        << histIter->_pSelectedFC
            << " "        << histIter->_uiAspect
            << endLog;

    _bRestoringHistory = true;

    if((*histIter)._pRootFC != _pRootFC)
        doSetRoot((*histIter)._pRootFC);

    if((*histIter)._pSelectedFC != _pSelectedFC)
        _pTreeView[_uiAspect]->setSelectedFC((*histIter)._pSelectedFC);

    if((*histIter)._uiAspect != _uiAspect)
        showAspect((*histIter)._uiAspect);

    _currentHistoryEntry = histIter;
    
    enableHistoryButtons();

    _bRestoringHistory = false;
}

void
QSceneGraphView::selectNextHistoryEntry(void)
{
    SNOTICE << "select NEXT history:\n "
            << "CURRENT: " << _currentHistoryEntry->_pRootFC
            << " "         << _currentHistoryEntry->_pSelectedFC
            << " "         << _currentHistoryEntry->_uiAspect;

    HistoryListIt histIter = _currentHistoryEntry;

    if((_history.size() == 0) || (++histIter == _history.end()))
        return;

    PNOTICE << "\n NEW: " << histIter->_pRootFC
            << " "        << histIter->_pSelectedFC
            << " "        << histIter->_uiAspect
            << endLog;

    _bRestoringHistory = true;

    if((*histIter)._pRootFC != _pRootFC)
        doSetRoot((*histIter)._pRootFC);

    if((*histIter)._pSelectedFC != _pSelectedFC)
        _pTreeView[_uiAspect]->setSelectedFC((*histIter)._pSelectedFC);

    if((*histIter)._uiAspect != _uiAspect)
        showAspect((*histIter)._uiAspect);

    _currentHistoryEntry = histIter;

    enableHistoryButtons();

    _bRestoringHistory = false;
}

void
QSceneGraphView::enableHistoryButtons(void)
{
    if(_history.size() <= 1)
    {
        _pPBBackward->setEnabled(false);
        _pPBForward ->setEnabled(false);
    }
    else if(_currentHistoryEntry == _history.begin())
    {
        _pPBBackward->setEnabled(false);
        _pPBForward ->setEnabled(true );
    }
    else if(_currentHistoryEntry == (--_history.end()))
    {
        _pPBBackward->setEnabled(true );
        _pPBForward ->setEnabled(false);
    }
    else
    {
        _pPBBackward->setEnabled(true );
        _pPBForward ->setEnabled(true );
    }
}

QSceneGraphView::HistoryEntry::HistoryEntry(
    const FieldContainerPtr &pRootFC, const FieldContainerPtr &pSelectedFC,
          UInt32             uiAspect                                      )
    : _pRootFC    (pRootFC    ),
      _pSelectedFC(pSelectedFC),
      _uiAspect   (uiAspect   )
{
}

#include "OSGQ4SceneGraphView_qt_moc.cpp"

