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

#include "OSGQAttachmentMapEditor_qt.h"

#include <OSGAttachmentMapFields.h>
#include <OSGQFieldContainerPtrEditor_qt.h>
#include <OSGQOSGWidgetFactoryHelper.h>

#include <qlayout.h>
#include <qlabel.h>

OSG_USING_NAMESPACE

ValueEditorRegistrator _regAttachmentMap(
     FieldDataTraits<AttachmentMap>::getType(),
    &QAttachmentMapEditor          ::create    );

QAbstractValueEditor *
QAttachmentMapEditor::create(QWidget *pParent, const char *name)
{
    return new QAttachmentMapEditor(pParent, name);
}

QAttachmentMapEditor::QAttachmentMapEditor(QWidget *pParent, const char *name)
    : Inherited(pParent, name)
{
    createChildWidgets();
    layoutChildWidgets();
    initSelf          ();
}

QAttachmentMapEditor::~QAttachmentMapEditor(void)
{
}

void
QAttachmentMapEditor::setLabelsVisible(bool bLabels)
{
    Inherited::setLabelsVisible(bLabels);

    if(bLabels == true)
    {
        for(UInt32 i = 0, size = _indexLabels.size(); i < size; ++i)
        {
            _indexLabels[i]->show();
        }
    }
    else
    {
        for(UInt32 i = 0, size = _indexLabels.size(); i < size; ++i)
        {
            _indexLabels[i]->hide();
        }
    }
}

void
QAttachmentMapEditor::setReadOnly(bool bReadOnly)
{
    Inherited::setReadOnly(bReadOnly);

    for(UInt32 i = 0, size = _indexLabels.size(); i < size; ++i)
    {
        _attachmentEditors[i]->setReadOnly( bReadOnly);
    }
}

void
QAttachmentMapEditor::readField(FieldContainerPtr pFC,          
                                UInt32            uiFieldId,
                                UInt32            uiValueIndex,
                                UInt32            uiAspect     )
{
    
    if(pFC->getField(uiFieldId)->getCardinality() == FieldType::SINGLE_FIELD)
    {
        const SFAttachmentMap *pSF = dynamic_cast<const SFAttachmentMap *>(
            pFC.getAspectCPtr(uiAspect)->getField(uiFieldId));
        
        updateDisplay(pSF->getValue());
    }
    else
    {
        const MFAttachmentMap *pMF = dynamic_cast<const MFAttachmentMap *>(
            pFC.getAspectCPtr(uiAspect)->getField(uiFieldId));
        
        updateDisplay((*pMF)[uiValueIndex]);
    }
}

void
QAttachmentMapEditor::readField(FieldContainerPtr pFC,          
                                UInt32            uiFieldId,
                                UInt32            uiValueIndex)
{
    readField(pFC, uiFieldId, uiValueIndex, Thread::getCurrent()->getAspect());
}

void
QAttachmentMapEditor::writeField(FieldContainerPtr pFC,          
                                 UInt32            uiFieldId,
                                 UInt32            uiValueIndex)
{
    BitVector mask = pFC->getType().getFieldDescription(uiFieldId)->getFieldMask();
    beginEditCP(pFC, mask);
    if(pFC->getField(uiFieldId)->getCardinality() == FieldType::SINGLE_FIELD)
    {
        SFAttachmentMap *pSF = 
            dynamic_cast<SFAttachmentMap *>(pFC->getField(uiFieldId));
        
        updateData(pSF->getValue());
    }
    else
    {
        MFAttachmentMap *pMF =
            dynamic_cast<MFAttachmentMap *>(pFC->getField(uiFieldId));
        
        updateData((*pMF)[uiValueIndex]);
    }
    endEditCP(pFC, mask);
}

void
QAttachmentMapEditor::addFieldElem(FieldContainerPtr pFC,
                                   UInt32            uiFieldId,
                                   UInt32            uiValueIndex)
{
    if(pFC->getField(uiFieldId)->getCardinality() == FieldType::SINGLE_FIELD)
    {
        SWARNING << "QAttachmentMapEditor::addFieldElem: can not add to SField."
                 << endLog;
    }
    else
    {
        MFAttachmentMap *pMF           =
            dynamic_cast<MFAttachmentMap *>(pFC->getField(uiFieldId));
        UInt32     uiInsertIndex = osgMin(uiValueIndex, pMF->size());

        pMF->insert(pMF->begin() + uiInsertIndex, AttachmentMap());
    }
}

void
QAttachmentMapEditor::removeFieldElem(FieldContainerPtr pFC,
                                      UInt32            uiFieldId,
                                      UInt32            uiValueIndex)
{
    if(pFC->getField(uiFieldId)->getCardinality() == FieldType::SINGLE_FIELD)
    {
        SWARNING << "QAttachmentMapEditor::removeFieldElem: "
                 << "can not remove from SField."
                 << endLog;
    }
    else
    {
        MFAttachmentMap *pMF           =
            dynamic_cast<MFAttachmentMap *>(pFC->getField(uiFieldId));
        UInt32     uiEraseIndex  = osgMin(uiValueIndex,
                                          pMF->empty() ? 0 : pMF->size() - 1);

        pMF->erase(pMF->begin() + uiEraseIndex);
    }
}

void
QAttachmentMapEditor::slotValueChanged(QAbstractValueEditor *pSender)
{
    emit valueChanged(this);
}

void
QAttachmentMapEditor::slotGenericRequest(
    QAbstractValueEditor *pSender, QString request)
{
    if(request == "QFieldContainerPtrEditor::ShowTarget")
    {
        for(UInt32 index = 0, size = _attachmentEditors.size();
            index < size; ++index)
        {
            if(_attachmentEditors[index] == pSender)
            {
                emit genericRequest(this, "QAttachmentMapEditor::ShowTarget: " 
                                    + QString::number(index)                   );

                break;
            }
        }
    }
    else
    {
        emit genericRequest(this, request);
    }
}

void
QAttachmentMapEditor::createChildWidgets(void)
{
    _pGrid = new QGridLayout(this, 0, 3, 0, -1, "QAttachmentMapEditor::_pGrid");
}

void
QAttachmentMapEditor::layoutChildWidgets(void)
{
}

void
QAttachmentMapEditor::initSelf(void)
{
}

void
QAttachmentMapEditor::updateDisplay(const AttachmentMap &attMap)
{
    UInt32                        attCount     = 0;
    UInt32                        availEditors = _indexLabels.size();
    
    AttachmentMap::const_iterator itAttMap     = attMap.begin();
    AttachmentMap::const_iterator endAttMap    = attMap.end  ();
        
    for(; itAttMap != endAttMap; ++itAttMap, ++attCount)
    {
        if(attCount >= availEditors)
        {
            _indexLabels      .push_back(new QLabel                  (this, ""));
            _groupLabels      .push_back(new QLabel                  (this, ""));
            _attachmentEditors.push_back(new QFieldContainerPtrEditor(this, ""));

            _pGrid->addWidget(_indexLabels[attCount],       attCount, 0);
            _pGrid->addWidget(_groupLabels[attCount],       attCount, 1);
            _pGrid->addWidget(_attachmentEditors[attCount], attCount, 2);

            connect(_attachmentEditors[attCount], SIGNAL(valueChanged      (QAbstractValueEditor *)),
                    this,                         SLOT  (slotValueChanged  (QAbstractValueEditor *)) );

            connect(_attachmentEditors[attCount], SIGNAL(genericRequest    (QAbstractValueEditor *, QString)),
                    this,                         SLOT  (slotGenericRequest(QAbstractValueEditor *, QString)) );
        }

              UInt16   groupId   = itAttMap->second->getType().getGroupId();
        const Char8   *groupName = FieldContainerFactory::the()->findGroupName(groupId);
              QString  strGroupName;
        
        if(FieldContainerFactory::the()->findGroupName(groupId) == NULL)
        {
            strGroupName =  "(";
            strGroupName += QString::number(groupId);
            strGroupName += ")";
        }
        else
        {
            strGroupName =  groupName;
            strGroupName += " (";
            strGroupName += QString::number(groupId);
            strGroupName += ")";
        }

        //SLOG << " attCount: "         << attCount
        //     << " groupId: "          << groupId
        //     << " itAttMap->second: " << itAttMap->second
        //     << " strGroupName: "     << strGroupName << endLog;

        _indexLabels      [attCount]->setText (QString::number(attCount) + ".");
        _groupLabels      [attCount]->setText (strGroupName                   );
        _attachmentEditors[attCount]->setValue(itAttMap->second               );
    }
    
    while(attCount < _indexLabels.size())
    {
        disconnect(_attachmentEditors.back(),  SIGNAL(valueChanged      (QAbstractValueEditor *)),
                    this,                      SLOT  (slotValueChanged  (QAbstractValueEditor *)) );
        
        disconnect(_attachmentEditors.back(), SIGNAL(genericRequest    (QAbstractValueEditor *, QString)),
                   this,                      SLOT  (slotGenericRequest(QAbstractValueEditor *, QString)) );

        _pGrid->remove(_indexLabels      .back());
        _pGrid->remove(_groupLabels      .back());
        _pGrid->remove(_attachmentEditors.back());

        delete _indexLabels      .back();
        delete _groupLabels      .back();
        delete _attachmentEditors.back();

        _indexLabels      .pop_back();
        _groupLabels      .pop_back();
        _attachmentEditors.pop_back();
    }
}

void
QAttachmentMapEditor::updateData(AttachmentMap &attMap) const
{
    
}

// include generated file
#include "OSGQAttachmentMapEditor_qt_moc.cpp"

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGQAttachmentMapEditor_qt.cpp,v 1.3 2006/07/24 16:00:37 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGQATTACHMENTMAPEDITORQT_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGQATTACHMENTMAPEDITORQT_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif

