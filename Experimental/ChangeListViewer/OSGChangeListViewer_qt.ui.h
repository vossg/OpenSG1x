/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename slots use Qt Designer which will
** update this file, preserving your code. Create an init() slot in place of
** a constructor, and a destroy() slot in place of a destructor.
*****************************************************************************/


// QListViewItem which holds a FieldContainerPtr
class ChangedTreeItem : public QListViewItem
{
  public:
    osg::ChangeList::ChangeEntry _changeEntry;
    
    ChangedTreeItem(QListViewItem *parent, osg::ChangeList::ChangeEntry ce,
                    QString fcName, QString fcTypeName)
        : QListViewItem(parent, fcName, fcTypeName), _changeEntry(ce)
        {;}
    
    ChangedTreeItem(QListView *parent, osg::ChangeList::ChangeEntry ce,
                    QString fcName, QString fcTypeName)
        : QListViewItem(parent, fcName, fcTypeName), _changeEntry(ce)
        {;}
    
    virtual ~ChangedTreeItem(void)
        {;}
};

class IdRefTreeItem : public QListViewItem
{
  public:
    osg::ChangeList::IdRefEntry _idRefEntry;
    
    IdRefTreeItem(QListViewItem *parent, osg::ChangeList::IdRefEntry ire,
                  QString fcName, QString fcTypeName)
        : QListViewItem(parent, fcName, fcTypeName), _idRefEntry(ire)
        {;}
    
    IdRefTreeItem(QListView *parent, osg::ChangeList::IdRefEntry ire,
                  QString fcName, QString fcTypeName)
        : QListViewItem(parent, fcName, fcTypeName), _idRefEntry(ire)
        {;}
    
    virtual ~IdRefTreeItem(void)
        {;}
};


class ColorTableItem : public QTableItem
{
  public:
    ColorTableItem(QColor &color, QTable * table, EditType et,
                   const QString & text)
        : QTableItem(table, et, text), _color(color)
        {;}
    
    virtual ~ColorTableItem(void)
        {;}
    
    virtual void paint ( QPainter * p, const QColorGroup & cg,
                         const QRect & cr, bool selected       )
        {
            QColorGroup newcg(cg);
            newcg.setColor(QColorGroup::Text, _color);
            QTableItem::paint(p, newcg, cr, selected);
        }
        
    void setColor(QColor color)
        {
            _color = color;
        }
        
  private:
    QColor _color;
};
            

void ChangeListViewer::updateFCList()
{
    if(_changeList == NULL)
    {
        return;
    }
    
    cerr << " Changed : " << _changeList->sizeChanged()
         << " Added : " << _changeList->sizeAddRefd()
         << " Subtracted : " << _changeList->sizeSubRefd()
         << " Created : " << _changeList->sizeCreated()
         << " Destroyed : " << _changeList->sizeDestroyed()
         << endl;
    
    osg::FieldContainerPtr fcPtr;
    osg::AttachmentContainerPtr attConPtr;
    osg::NamePtr namePtr;
    QListViewItem* tempItem;
    const osg::Char8 *pFCTypeName, *pFCName, *notSet = "Not set";
    
    //CHANGED
    //Empty the list
    tempItem = _changedRoot->firstChild();
    while(tempItem)
    {
        delete tempItem;
        tempItem = _changedRoot->firstChild();
    }
    
    osg::ChangeList::changed_const_iterator
        chStart = _changeList->beginChanged();
    osg::ChangeList::changed_const_iterator
        chEnd   = _changeList->endChanged();
    //Refill the list
    for(; chStart != chEnd; ++chStart)
    {
        fcPtr = osg::FieldContainerFactory::the()->getContainer(
            (*chStart).first);
        if(fcPtr == osg::NullFC)
            continue;
        
        pFCTypeName = fcPtr->getTypeName();
        attConPtr = osg::AttachmentContainerPtr::dcast(fcPtr);
        if(attConPtr != osg::NullFC)
        {
            namePtr = osg::NamePtr::dcast(attConPtr->findAttachment(
                osg::Name::getClassType().getGroupId()));
            if(namePtr != osg::NullFC)
            {
                pFCName = namePtr->getFieldPtr()->getValue().c_str();
            }
            else
            {
                pFCName = notSet;
            }
        }
        else
            pFCName = notSet;
        
        tempItem = new ChangedTreeItem(_changedRoot, (*chStart),
                                       pFCName, pFCTypeName);
    }
    
    //ADDED REFERECE
    tempItem = _addrefRoot->firstChild();
    while(tempItem)
    {
        delete tempItem;
        tempItem = _addrefRoot->firstChild();
    }
    
    osg::ChangeList::idrefd_const_iterator arStart = _changeList->beginAddRefd();
    osg::ChangeList::idrefd_const_iterator arEnd   = _changeList->endAddRefd();
    //Refill the list
    for(; arStart != arEnd; ++arStart)
    {
        fcPtr = osg::FieldContainerFactory::the()->getContainer(*arStart);
        if(fcPtr == osg::NullFC)
            continue;
        
        pFCTypeName = fcPtr->getTypeName();
        attConPtr = osg::AttachmentContainerPtr::dcast(fcPtr);
        if(attConPtr != osg::NullFC)
        {
            namePtr = osg::NamePtr::dcast(attConPtr->findAttachment(
                osg::Name::getClassType().getGroupId()));
            if(namePtr != osg::NullFC)
            {
                pFCName = namePtr->getFieldPtr()->getValue().c_str();
            }
            else
            {
                pFCName = notSet;
            }
        }
        else
            pFCName = notSet;
        
        tempItem = new IdRefTreeItem(_addrefRoot, (*arStart),
                                     pFCName, pFCTypeName);
    }
    
    //SUBTRACTED REFERECE
    //Empty the List
    tempItem = _subrefRoot->firstChild();
    while(tempItem)
    {
        delete tempItem;
        tempItem = _subrefRoot->firstChild();
    }
    
    osg::ChangeList::idrefd_const_iterator srStart = _changeList->beginSubRefd();
    osg::ChangeList::idrefd_const_iterator srEnd   = _changeList->endSubRefd();
    //Refill the list
    for(; srStart != srEnd; ++srStart)
    {
        fcPtr = osg::FieldContainerFactory::the()->getContainer(*srStart);
        if(fcPtr == osg::NullFC)
            continue;
        
        pFCTypeName = fcPtr->getTypeName();
        attConPtr = osg::AttachmentContainerPtr::dcast(fcPtr);
        if(attConPtr != osg::NullFC)
        {
            namePtr = osg::NamePtr::dcast(attConPtr->findAttachment(
                osg::Name::getClassType().getGroupId()));
            if( namePtr != osg::NullFC )
            {
                pFCName = namePtr->getFieldPtr()->getValue().c_str();
            }
            else
            {
                pFCName = notSet;
            }
        }
        else
            pFCName = notSet;
        
        tempItem = new IdRefTreeItem(_subrefRoot, (*srStart),
                                     pFCName, pFCTypeName);
    }
    
    //CREATED
    //Empty the List
    tempItem = _createdRoot->firstChild();
    while(tempItem)
    {
        delete tempItem;
        tempItem = _createdRoot->firstChild();
    }
    
    osg::ChangeList::refd_const_iterator
        createdStart = _changeList->beginCreated();
    osg::ChangeList::refd_const_iterator
        createdEnd   = _changeList->endCreated();
    //Refill the list
    for(; createdStart != createdEnd; ++createdStart)
    {
        fcPtr = osg::FieldContainerFactory::the()->getContainer(*createdStart);
        if(fcPtr == osg::NullFC)
            continue;
        
        pFCTypeName = fcPtr->getTypeName();
        attConPtr = osg::AttachmentContainerPtr::dcast(fcPtr);
        if(attConPtr != osg::NullFC)
        {
            namePtr = osg::NamePtr::dcast(attConPtr->findAttachment(
                osg::Name::getClassType().getGroupId()));
            if(namePtr != osg::NullFC)
            {
                pFCName = namePtr->getFieldPtr()->getValue().c_str();
            }
            else
            {
                pFCName = notSet;
            }
        }
        else
            pFCName = notSet;
        
        tempItem = new IdRefTreeItem(_createdRoot, (*createdStart),
                                     pFCName, pFCTypeName);
    }
    
    //DESTROYED
    //Empty the List
    tempItem = _destroyedRoot->firstChild();
    while(tempItem)
    {
        delete tempItem;
        tempItem = _destroyedRoot->firstChild();
    }
    
    osg::ChangeList::refd_const_iterator
        destroyedStart = _changeList->beginDestroyed();
    osg::ChangeList::refd_const_iterator
        destroyedEnd   = _changeList->endDestroyed();
    //Refill the list
    for(; destroyedStart != destroyedEnd; ++destroyedStart)
    {
        fcPtr = osg::FieldContainerFactory::the()->getContainer(*destroyedStart);
        if(fcPtr == osg::NullFC)
            continue;
        
        pFCTypeName = fcPtr->getTypeName();
        attConPtr = osg::AttachmentContainerPtr::dcast(fcPtr);
        if(attConPtr != osg::NullFC)
        {
            namePtr = osg::NamePtr::dcast(attConPtr->findAttachment(
                osg::Name::getClassType().getGroupId()));
            if(namePtr != osg::NullFC)
            {
                pFCName = namePtr->getFieldPtr()->getValue().c_str();
            }
            else
            {
                pFCName = notSet;
            }
        }
        else
            pFCName = notSet;
        
        tempItem = new IdRefTreeItem(_destroyedRoot, (*createdStart),
                                     pFCName, pFCTypeName);
    }
    //update the view
    FCListView->triggerUpdate();
}


void ChangeListViewer::setActiveFC(QListViewItem* activeItem)
{
    osg::FieldContainerPtr fcPtr;
    IdRefTreeItem *idItem = dynamic_cast<IdRefTreeItem*>(activeItem);
    if(idItem)
    {
	fcPtr = osg::FieldContainerFactory::the()->getContainer(
	    idItem->_idRefEntry);
	//displayFC(fcPtr, 0x0);
	displayDynFieldAtt(fcPtr, 0x0);
	return;
    }
        
    ChangedTreeItem *chItem = dynamic_cast<ChangedTreeItem*>(activeItem);
    if(chItem)
    {
	fcPtr= osg::FieldContainerFactory::the()->getContainer(
	    chItem->_changeEntry.first);
	//displayFC(fcPtr, chItem->_changeEntry.second);
	displayDynFieldAtt(fcPtr, chItem->_changeEntry.second);
	return;
    }
}


void ChangeListViewer::setChangeList(osg::ChangeList* list)
{
    if( list != NULL )
    {
	_changeList = list;
        updateFCList();
    }
}

void ChangeListViewer::init()
{
    _changeList    = NULL;
    _changedRoot   = new QListViewItem(FCListView, "Changed");
    _addrefRoot    = new QListViewItem(FCListView, "Added Reference");
    _subrefRoot    = new QListViewItem(FCListView, "Removed Referece");
    _createdRoot   = new QListViewItem(FCListView, "Created");
    _destroyedRoot = new QListViewItem(FCListView, "Destroyed");
    _numAspects    = osg::ThreadManager::getNumAspects();
    _changedColor  = red;
    _normalColor   = black;
    
    FCListView->setSorting(-1);
}


/*
void ChangeListViewer::displayFC( osg::FieldContainerPtr fcPtr,
                                osg::BitVector changeMask, bool allFlag=true )
{
    ;
}
*/

void ChangeListViewer::displayFC( osg::FieldContainerPtr fcPtr,
                                osg::BitVector changeMask, bool allFlag )
{
    const osg::Char8 *notSet = "Not set";
    osg::FieldContainerType& fcType = fcPtr->getType();
    osg::FieldContainer* fcCPtr;
    osg::FieldDescription* pFieldDesc;
    std::string fieldName;
    std::string fieldTypeName;
    std::string fieldVal;
    QColor textColor;

    FCDetailView->setNumCols(3+_numAspects);
    FCDetailView->horizontalHeader()->setLabel(0, "Id");
    FCDetailView->horizontalHeader()->setLabel(1, "FieldName");
    FCDetailView->horizontalHeader()->setLabel(2, "FieldType");

    for(osg::UInt32 i=0; i<_numAspects; i++)
    {
	FCDetailView->horizontalHeader()->setLabel(3+i,
                                                   "Value (Aspect: "+
                                                   QString::number(i+1)+")" );
    }
        
    int numFields = fcType.getNumFieldDescs();
    int numRows   = numFields;
    if(!allFlag)
    {
        numRows = 0;
        for(int i=1; i<=numFields; i++)
        {
            if(changeMask & (1<<i))
                numRows++;
        }
    }
    FCDetailView->setNumRows(numRows);
    
    osg::UInt32 fieldID=1, row=0;
    while(fieldID<=numFields && row<numRows)
    {
        cerr << "Field: " << fieldID << " Row: " << row << endl;
        if(changeMask & (1<<fieldID))
        {
            textColor = _changedColor;
        }
        else
        {
            textColor = _normalColor;
            if(!allFlag)
            {
                cerr << "skipping" << endl;
                fieldID++;
                continue;
            }
        }

        pFieldDesc = fcType.getFieldDescription(fieldID);
        if(pFieldDesc != NULL )
        {
            fieldName = pFieldDesc->getName().str();
            fieldTypeName = osg::FieldFactory::the().getFieldTypeName(
                pFieldDesc->getTypeId());
        }
        else
        {
            fieldName = notSet;
            fieldTypeName = notSet;
        }

        FCDetailView->setItem(row, 0,
                              new ColorTableItem(textColor,
                                                 FCDetailView,
                                                 QTableItem::Never,
                                                 QString::number(fieldID)));
        FCDetailView->setItem(row, 1,
                              new ColorTableItem(textColor,
                                                 FCDetailView,
                                                 QTableItem::Never,
                                                 fieldName.c_str()));
	FCDetailView->setItem(row, 2,
                              new ColorTableItem(textColor,
                                                 FCDetailView,
                                                 QTableItem::Never,
                                                 fieldTypeName.c_str()));
        for(osg::UInt32 aspect=0; aspect<_numAspects; aspect++)
        {
            OSG::UInt8 *tmpPtr = 
                ((OSG::UInt8 *) &(*fcPtr))+aspect*(fcPtr->getContainerSize());
            fcCPtr = (OSG::FieldContainer *) tmpPtr;
            fieldVal.erase();
            fcCPtr->getField(fieldID)->getValueByStr(fieldVal);
            if(fieldVal.empty())
                fieldVal = notSet;
            FCDetailView->setItem(row, 3+aspect,
                                  new ColorTableItem(textColor,
                                                     FCDetailView,
                                                     QTableItem::Never,
                                                     fieldVal.c_str()));
            FCDetailView->item(row,3+aspect)->setWordWrap(true);            
        }
        FCDetailView->adjustRow(row);
        fieldID++;
        row++;       
    }
    FCDetailView->adjustColumn(0);
    return;
}

void ChangeListViewer::displayDynFieldAtt(osg::FieldContainerPtr fcPtr,
					osg::BitVector changeMask, 
					bool allFlag)
{

    FCDetailView->setNumCols(4*_numAspects);
    OSG::UInt8 *tmpPtr;
    OSG::FieldContainer* fcCPtr = &(*fcPtr);
    osg::FieldDescription* pFieldDesc;
    OSG::UInt32 numRows = 0; 
    OSG::UInt32 numFields;
    const osg::Char8 *notSet = "Not set";
    std::string fieldName;
    std::string fieldTypeName;
    std::string fieldVal;
    QColor textColor = black;

    for(osg::UInt32 asp=0; asp<_numAspects; asp++)
    {
	FCDetailView->horizontalHeader()->setLabel(4*asp,   "Id");
	FCDetailView->horizontalHeader()->setLabel(4*asp+1, "FieldName");
	FCDetailView->horizontalHeader()->setLabel(4*asp+2, "FieldType");
        FCDetailView->horizontalHeader()->setLabel(4*asp+3, "Value");

        OSG::SLOG << "fcCPtr: " << fcCPtr << endl;
    
	OSG::FieldContainerType &fcType = fcCPtr->getType();
	numFields = fcType.getNumFieldDescs();
	if(numRows<numFields)
	{
	    numRows = numFields;
	    FCDetailView->setNumRows(numRows);
	}

	for(OSG::UInt32 fieldID=1; fieldID<=numFields; fieldID++){
	    
	    if(changeMask & (1<<fieldID))
	    {
		textColor = _changedColor;
	    }
	    else
	    {
		textColor = _normalColor;
	    }

	    pFieldDesc = fcType.getFieldDescription(fieldID);
	    if(pFieldDesc != NULL )
	    {
		fieldName = pFieldDesc->getName().str();
		fieldTypeName = osg::FieldFactory::the().getFieldTypeName(
		    pFieldDesc->getTypeId());
	    }
	    else
	    {
		fieldName = notSet;
		fieldTypeName = notSet;
	    }
	    
	    FCDetailView->setItem(fieldID-1, 4*asp,
				  new ColorTableItem(textColor, FCDetailView,
                                                     QTableItem::Never, 
                                                     QString::number(fieldID)));
	    FCDetailView->setItem(fieldID-1, 4*asp+1,
				  new ColorTableItem(textColor, FCDetailView,
						     QTableItem::Never,
						     fieldName.c_str())      );
	    FCDetailView->setItem(fieldID-1, 4*asp+2,
				  new ColorTableItem(textColor, FCDetailView,
						     QTableItem::Never,
						     fieldTypeName.c_str())  );
	    fieldVal.erase();
	    fcCPtr->getField(fieldID)->getValueByStr(fieldVal);
	    if(fieldVal.empty())
		fieldVal = notSet;
	    FCDetailView->setItem(fieldID-1,4*asp+3,
				  new ColorTableItem(textColor, FCDetailView,
						     QTableItem::Never,
						     fieldVal.c_str())       );
	    FCDetailView->item(fieldID-1,4*asp+3)->setWordWrap(true);
	    FCDetailView->adjustRow(fieldID-1);
	}

	for(OSG::UInt32 i=numFields; i<numRows; i++)
	{
	    FCDetailView->clearCell(i,4*asp);
	    FCDetailView->clearCell(i,4*asp+1);
	    FCDetailView->clearCell(i,4*asp+2);
	    FCDetailView->clearCell(i,4*asp+3);
	}
				 
	
	FCDetailView->adjustColumn(4*asp);
	FCDetailView->adjustColumn(4*asp+1);
	FCDetailView->adjustColumn(4*asp+2);
	FCDetailView->adjustColumn(4*asp+3);
        /* set fcCPtr to next aspect */
	tmpPtr = ((OSG::UInt8*)fcCPtr)+(fcCPtr->getContainerSize());
	fcCPtr = (OSG::FieldContainer*)tmpPtr;
    }
    return;
}









