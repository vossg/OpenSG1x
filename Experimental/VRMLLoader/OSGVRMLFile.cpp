/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#define OSG_COMPILESYSTEMLIB
#define OSG_COMPILEVRMLLOADERINST

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include "OSGVRMLFile.h"

#include <OSGFieldType.h>

#include <OSGSFSysTypes.h>
#include <OSGMFSysTypes.h>

#include <OSGSFBaseTypes.h>
#include <OSGMFBaseTypes.h>

#include <OSGSFMathTypes.h>
#include <OSGMFMathTypes.h>

#include <OSGSFVecTypes.h>
#include <OSGMFVecTypes.h>

#include <OSGMFFieldContainerTypes.h>
#include <OSGSFFieldContainerTypes.h>

#include <OSGSFImageTypes.h>

#include <OSGGeoProperty.h>

OSG_USING_NAMESPACE

#ifndef __sgi
template OSG_SYSTEMLIB_DLLMAPPING 
ScanParseFieldTypeMapper<ScanParseSkel>;

template OSG_SYSTEMLIB_DLLMAPPING 
VRMLNodeFactory<ScanParseFieldTypeMapper<ScanParseSkel> >;
#endif

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char VRMLFile::cvsid[] = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

void VRMLFile::initIntExtFieldTypeMapper(void)
{
    setIntExtMapping(SFBool::getClassType().getId(),
                     ScanParseSkel::OSGsfBool);

    setIntExtMapping(SFColor3f::getClassType().getId(),
                     ScanParseSkel::OSGsfColor);

    setIntExtMapping(SFReal32::getClassType().getId(), 
                     ScanParseSkel::OSGsfFloat);

    setIntExtMapping(SFImageP::getClassType().getId(),
                     ScanParseSkel::OSGsfImage);

    setIntExtMapping(SFInt32::getClassType().getId(),
                     ScanParseSkel::OSGsfInt32);

    setIntExtMapping(SFQuaternion::getClassType().getId(),
                     ScanParseSkel::OSGsfRotation);

    setIntExtMapping(SFString::getClassType().getId(),
                     ScanParseSkel::OSGsfString);

    setIntExtMapping(SFTime::getClassType().getId(),
                     ScanParseSkel::OSGsfTime);

    setIntExtMapping(SFVec2f::getClassType().getId(),
                     ScanParseSkel::OSGsfVec2f);

    setIntExtMapping(SFVec3f::getClassType().getId(),
                     ScanParseSkel::OSGsfVec3f);



    setIntExtMapping(MFColor3f::getClassType().getId(),
                     ScanParseSkel::OSGmfColor);

    setIntExtMapping(MFReal32::getClassType().getId(),
                     ScanParseSkel::OSGmfFloat);

    setIntExtMapping(MFInt32::getClassType().getId(),
                     ScanParseSkel::OSGmfInt32);

    setIntExtMapping(MFQuaternion::getClassType().getId(),
                     ScanParseSkel::OSGmfRotation);

    setIntExtMapping(MFString::getClassType().getId(),
                     ScanParseSkel::OSGmfString);

    setIntExtMapping(MFTime::getClassType().getId(),
                     ScanParseSkel::OSGmfTime);

    setIntExtMapping(MFVec3f::getClassType().getId(),
                     ScanParseSkel::OSGmfVec3f);

    setIntExtMapping(MFVec2f::getClassType().getId(),
                     ScanParseSkel::OSGmfVec2f);


    setIntExtMapping(SFNodePtr::getClassType().getId(),
                     ScanParseSkel::OSGsfNode);

    setIntExtMapping(MFNodePtr::getClassType().getId(),
                     ScanParseSkel::OSGmfNode);

    /* To Base Type Mappings */

    setIntExtMapping(SFUInt8::getClassType().getId(),
                     ScanParseSkel::OSGsfInt32);

    setIntExtMapping(MFUInt8::getClassType().getId(),
                     ScanParseSkel::OSGmfInt32);

    setIntExtMapping(SFUInt32::getClassType().getId(),
                     ScanParseSkel::OSGsfInt32);

    setIntExtMapping(MFUInt32::getClassType().getId(),
                     ScanParseSkel::OSGmfInt32);

    /* To Node Mappings */

    setIntExtMapping(SFNodeCorePtr::getClassType().getId(),
                     ScanParseSkel::OSGsfNode);

    setIntExtMapping(SFMaterialPtr::getClassType().getId(),
                     ScanParseSkel::OSGsfNode);
    
    setIntExtMapping(SFGeoPTypePtr::getClassType().getId(),
                     ScanParseSkel::OSGsfNode);

    setIntExtMapping(SFGeoIndexPtr::getClassType().getId(),
                     ScanParseSkel::OSGsfNode);

    setIntExtMapping(SFGeoPLengthPtr::getClassType().getId(),
                     ScanParseSkel::OSGsfNode);

    setIntExtMapping(SFGeoColorPtr::getClassType().getId(),
                     ScanParseSkel::OSGsfNode);

    setIntExtMapping(SFGeoPositionPtr::getClassType().getId(),
                     ScanParseSkel::OSGsfNode);

    setIntExtMapping(SFGeoNormalPtr::getClassType().getId(),
                     ScanParseSkel::OSGsfNode);

    setIntExtMapping(SFGeoTexCoordsPtr::getClassType().getId(),
                     ScanParseSkel::OSGsfNode);

    setIntExtMapping(SFAttachmentMap::getClassType().getId(),
                     ScanParseSkel::OSGmfNode);

    setIntExtMapping(SFFieldContainerPtr::getClassType().getId(),
                     ScanParseSkel::OSGsfNode);

    /* extended types */

    setIntExtMapping(SFMatrix::getClassType().getId(),
                     ScanParseSkel::OSGsfMatrix);

    setIntExtMapping(SFPnt3f::getClassType().getId(),
                     ScanParseSkel::OSGsfPnt3f);

    setIntExtMapping(MFPnt3f::getClassType().getId(),
                     ScanParseSkel::OSGmfPnt3f);
}


void VRMLFile::initExtIntFieldTypeMapper(void)
{
    setExtIntMapping(ScanParseSkel::OSGsfBool, 
                     SFBool::getClassType().getId());

    setExtIntMapping(ScanParseSkel::OSGsfColor, 
                     SFColor3f::getClassType().getId());

    setExtIntMapping(ScanParseSkel::OSGsfFloat, 
                     SFReal32::getClassType().getId());

/*
    setExtIntMapping(SFImage::getClassType().getId(),
                     ScanParseSkel::OSGsfInt32);
                     */

    setExtIntMapping(ScanParseSkel::OSGsfImage, 
                     SFImageP::getClassType().getId());

    setExtIntMapping(ScanParseSkel::OSGsfInt32, 
                     SFInt32::getClassType().getId());
    

    setExtIntMapping(ScanParseSkel::OSGsfRotation, 
                     SFQuaternion::getClassType().getId());

    setExtIntMapping(ScanParseSkel::OSGsfString, 
                     SFString::getClassType().getId());

    setExtIntMapping(ScanParseSkel::OSGsfTime, 
                     SFTime::getClassType().getId());

    setExtIntMapping(ScanParseSkel::OSGsfVec2f, 
                     SFVec2f::getClassType().getId());

    setExtIntMapping(ScanParseSkel::OSGsfVec3f, 
                     SFVec3f::getClassType().getId());



    setExtIntMapping(ScanParseSkel::OSGmfColor, 
                     MFColor3f::getClassType().getId());

    setExtIntMapping(ScanParseSkel::OSGmfFloat, 
                     MFReal32::getClassType().getId());

    setExtIntMapping(ScanParseSkel::OSGmfInt32, 
                     MFInt32::getClassType().getId());

    setExtIntMapping(ScanParseSkel::OSGmfRotation, 
                     MFQuaternion::getClassType().getId());

    setExtIntMapping(ScanParseSkel::OSGmfString, 
                     MFString::getClassType().getId());

    setExtIntMapping(ScanParseSkel::OSGmfTime, 
                     MFTime::getClassType().getId());


    setExtIntMapping(ScanParseSkel::OSGmfVec3f, 
                     MFVec3f::getClassType().getId());

    setExtIntMapping(ScanParseSkel::OSGmfVec2f, 
                     MFVec2f::getClassType().getId());


    setExtIntMapping(ScanParseSkel::OSGsfNode,
                     SFNodePtr::getClassType().getId());

    setExtIntMapping(ScanParseSkel::OSGmfNode,
                     MFNodePtr::getClassType().getId());

    /* extended types */

    setExtIntMapping(ScanParseSkel::OSGsfMatrix, 
                     SFMatrix::getClassType().getId());

    setExtIntMapping(ScanParseSkel::OSGsfPnt3f, 
                     SFPnt3f::getClassType().getId());

    setExtIntMapping(ScanParseSkel::OSGmfPnt3f, 
                     MFPnt3f::getClassType().getId());
}

/* remove this, if there is a general methode to find containers */
FieldContainerPtr VRMLFile::findFCByName(const Char8  *szName,
                                               NodePtr pNode)
{
    MFNodePtr::iterator i;

    NamePtr           pNodename;
    NodeCorePtr       pCore;
    FieldContainerPtr pFC;

    // check if name matches nodename

    pNodename = 
        NamePtr::dcast(
            pNode->findAttachment(Name::getClassType().getGroupId()));

    if(pNodename != NullFC)
    {
        if(strcmp(szName, pNodename->getFieldPtr()->getValue().str())==0)
            return pNode;
    }
    // check if name matches corename
    
    pCore = pNode->getCore();

    if(pCore != NullFC)
    {
        pNodename = NamePtr::dcast(
            pCore->findAttachment(Name::getClassType().getGroupId()));

        if(pNodename != NullFC)
        {
            if(strcmp(szName, pNodename->getFieldPtr()->getValue().str())==0)
                return pCore;
        }
    }

    // matching for children
    for(i  = pNode->getMFChildren()->begin();
        i != pNode->getMFChildren()->end();
        i++)
    {
        pFC = findFCByName(szName, *i);

        if(pFC != NullFC)
        {
            return pFC;
        }
    }
    return pFC;
}

FieldContainerPtr VRMLFile::findReference(const Char8 *szName)
{
    // search reference in this file
    FieldContainerPtr          returnValue = NullFC;

    NameContainerMap::iterator mIt         = 
        _nameFCMap.find(StringLink(szName));

    if(mIt != _nameFCMap.end())
    {
        returnValue = mIt->second;
    }
    else
    {
        returnValue = findFCByName(szName, _pRootNode);
    }
    
    return returnValue;
}

void VRMLFile::setContainerFieldValue(const FieldContainerPtr &pFC)
{
    if(_pCurrentField != NULL        &&        
        pFC           != NullFC)
    {
        if(_pCurrentFC   !=   NullFC && 
           _pCurrentField == _pCurrentFC->getField("children"))
        {
            indentLog(VRMLNodeDesc::getIndent(), PNOTICE);
            PNOTICE << "Add Child "
                    << &(*_pCurrentFC)
                    << " "
                    << &(*pFC)
                    << endl;

            NodePtr pNode      = NodePtr::dcast(_pCurrentFC);
            NodePtr pChildNode = NodePtr::dcast(pFC);
            
            pNode->addChild(pChildNode);
        }
        else if(_pCurrentFC   !=   NullFC && 
                _pCurrentField == _pCurrentFC->getField("core"))
        {
            indentLog(VRMLNodeDesc::getIndent(), PNOTICE);
            PNOTICE << "Add Core "
                    << &(*_pCurrentFC)
                    << " "
                    << &(*pFC)
                    << endl;

            NodePtr     pNode = NodePtr    ::dcast(_pCurrentFC);
            NodeCorePtr pCore = NodeCorePtr::dcast(pFC);
            
            pNode->setCore(pCore);
        }

/*
        else if(_pCurrentField == _pCurrentFC->getField("attachments"))
        {
            if(pNewNode->getType().isAttachment() == true)
            {
                if(_pCurrentFC->getType().isNode() == true)
                {
                    NodePtr       pNode = _pCurrentFC.dcast<NodePtr>();
                    AttachmentPtr pAtt  =  pNewNode.dcast<AttachmentPtr>();

                    pNode->addAttachment(pAtt);
                }
                else if(_pCurrentFC->getType().isNodeCore() == true)
                {
                    NodeCorePtr   pNodeCore = _pCurrentFC.dcast<NodeCorePtr>();
                    AttachmentPtr pAtt      =  pNewNode.dcast<AttachmentPtr>();

                    pNodeCore->addAttachment(pAtt); 
                }
            }
            else
            {
                SLOG << "FieldContainer : " << szNodeTypename 
                     << " is no attachment" << endl;
            }
        }
*/
        else if(_pCurrentField->getCardinality() == FieldType::SINGLE_FIELD)
        {
            ((SFFieldContainerPtr *) _pCurrentField)->setValue(pFC);
        }
        else if(_pCurrentField->getCardinality() == FieldType::MULTI_FIELD)
        {
            ((MFFieldContainerPtr *) _pCurrentField)->push_back(pFC);
        }
    }
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

VRMLFile::VRMLFile(void) :
    Inherited(),

    _pRootNode    (NullNode),

    _pCurrNodeDesc(NULL),
    _sNodeDescs   (),

    _pCurrentFC       (NullFC),
    _pCurrentField    (NULL),
    _pCurrentFieldDesc(NULL),

    _fcStack  (),
    _fStack   (),
    _fdStack  (),

    _nameFCMap  (),
    _nameDescMap()
{
    setReferenceHeader("#VRML V2.0 ");

    initIntExtFieldTypeMapper();
    initExtIntFieldTypeMapper();
}

/** \brief Destructor
 */

VRMLFile::~VRMLFile(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLFile::scanFile(const Char8 *szFilename, UInt32 uiOptions)
{
    _pRootNode = NullNode;

    VRMLNodeDesc::resetIndent();

    Inherited::scanFile(szFilename, uiOptions);
}

void VRMLFile::beginNode(
    const Char8 *szNodeTypename,
    const Char8 *szNodename)
{
    FieldContainerPtr pNewNode;

    _pCurrNodeDesc = findNodeDesc(szNodeTypename);

    if(_pCurrNodeDesc == NULL)
        return;
    
    _pCurrNodeDesc->setOptions(_uiOptions);

    _sNodeDescs.push(_pCurrNodeDesc);

    _pCurrNodeDesc->reset();

    pNewNode = _pCurrNodeDesc->beginNode(szNodeTypename, 
                                         szNodename,
                                         _pCurrentFC);

    indentLog(VRMLNodeDesc::getIndent(), PNOTICE);
    PNOTICE << "Begin Node " << szNodeTypename << endl;

    VRMLNodeDesc::incIndent();

    if(szNodename != NULL)
    {
        if(pNewNode != NullFC)
        {
            if(pNewNode->getType().isNode() == true)
            {
                indentLog(VRMLNodeDesc::getIndent(), PNOTICE);
                PNOTICE << "Node named : " << szNodename << endl;

                NodePtr pNode     = NodePtr::dcast(pNewNode);
                NamePtr pNodename = Name::create();
                
                pNodename->getFieldPtr()->getValue().set(szNodename);
                
                pNode->addAttachment(pNodename);
            }
            else if(pNewNode->getType().isNodeCore() == true)
            {
                indentLog(VRMLNodeDesc::getIndent(), PNOTICE);
                PNOTICE << "Nodecore named : " << szNodename << endl;
                
                NodeCorePtr pNodeCore = NodeCorePtr::dcast(pNewNode);
                NamePtr     pNodename = Name::create();
                
                pNodename->getFieldPtr()->getValue().set(szNodename);
                
                pNodeCore->addAttachment(pNodename);           
            }
            else
            {
                indentLog(VRMLNodeDesc::getIndent(), PNOTICE);
                PNOTICE << "Fieldcontainer " << szNodeTypename 
                        << "is neither node nor nodecore " << endl;
                
                NameContainerMap::iterator mIt = 
                    _nameFCMap.find(StringLink(szNodename));
                
                if(mIt == _nameFCMap.end())
                {
                    _nameFCMap[String(szNodename)] = pNewNode;
                    
                    indentLog(VRMLNodeDesc::getIndent(), PNOTICE);
                    PNOTICE << "Fieldcontainer " << szNodename 
                            << " added to map " << endl;
                }
                
            }

            _nameDescMap[String(szNodename)] = _pCurrNodeDesc;
            
            indentLog(VRMLNodeDesc::getIndent(), PNOTICE);
            PNOTICE << "Desc for " << szNodename << " added to map " << endl;
        }
        else
        {
            indentLog(VRMLNodeDesc::getIndent(), PNOTICE);
            PNOTICE << "Fieldcontainer " 
                    << szNodeTypename 
                    << "is empty, save on end " 
                    << endl;
            
            if(_pCurrNodeDesc != NULL)
                _pCurrNodeDesc->setOnEndSave(szNodename);
            
            _nameDescMap[String(szNodename)] = _pCurrNodeDesc;
            
            indentLog(VRMLNodeDesc::getIndent(), PNOTICE);
            PNOTICE << "Desc for " << szNodename << " added to map " << endl;
        }
    }

    setContainerFieldValue(pNewNode);

    _pCurrentFC = pNewNode;

    _fcStack.push(_pCurrentFC);

    if(_fcStack.size() == 1)
    {
        NodePtr pNode = NodePtr::dcast(_pCurrentFC);

        if(_pRootNode == NullNode)
        {
            GroupPtr pGroup = Group::create();

            _pRootNode = Node::create();
            _pRootNode->setCore(pGroup);
        }

        _pRootNode->addChild(pNode);
    }
}
   
void VRMLFile::endNode(void)
{
    if(_pCurrNodeDesc == NULL)
    {
        VRMLNodeDesc::decIndent();

        indentLog(VRMLNodeDesc::getIndent(), PNOTICE);
        PNOTICE << "End Node " << endl;

        return;
    }

    _pCurrNodeDesc->endNode(_pCurrentFC);

    if(_pCurrNodeDesc->getOnEndSave() == true)
    {
        SLOG << "Fieldcontainer " <<  _pCurrNodeDesc->getSavename()
             << " on end Save " << endl;

        NameContainerMap::iterator mIt = 
            _nameFCMap.find(StringLink(_pCurrNodeDesc->getSavename()));
        
        if(mIt == _nameFCMap.end())
        {
            _nameFCMap[String(_pCurrNodeDesc->getSavename())] = 
                _pCurrNodeDesc->getSaveFieldContainer();
            
            SLOG << "Fieldcontainer " << _pCurrNodeDesc->getSavename()
                 << " added to map " << endl;
        }

        _pCurrNodeDesc->clearOnEndSave();
    }

    _sNodeDescs.pop();

    if(_sNodeDescs.size() != 0)
    {
        _pCurrNodeDesc = _sNodeDescs.top();
    }
    else
    {
        _pCurrNodeDesc = NULL;
    }

    if(_pCurrentFC != NullFC)
    {       
        if(_pCurrentFC->getType().isNode() == true)        
        {
            NodePtr pNode = NodePtr::dcast(_pCurrentFC);
            
            if(pNode->getCore() == NullNodeCore)
            {
                GroupPtr pGroup = Group::create();

                pNode->setCore(pGroup);
            }
        }
    }

    _fcStack.pop();

    if(_fcStack.size() != 0)
    {
        _pCurrentFC = _fcStack.top(); 
    }
    else
    {
        _pCurrentFC = NullFC;
    }

    VRMLNodeDesc::decIndent();

    indentLog(VRMLNodeDesc::getIndent(), PNOTICE);
    PNOTICE << "End Node " << endl;
}

void VRMLFile::beginField(const Char8 *szFieldname,
                          const UInt32 uiFieldTypeId)
{
    if(szFieldname == NULL)
        return;

    indentLog(VRMLNodeDesc::getIndent(), PNOTICE);
    PNOTICE << "VRMLFile::beginField : looking for " 
            << szFieldname 
            << " ("
            << uiFieldTypeId
            << " | "
            << _pCurrentField
            << " | "
            << _pCurrentFieldDesc
            << ")"
            << endl;

    VRMLNodeDesc::incIndent();

    if(_pCurrentFieldDesc != NULL)
    {
        NodeCorePtr pCore;
        NodePtr     pNode;

        if(_pCurrentFC != NullFC)
        {
            beginEditCP(_pCurrentFC);

            if(_pCurrentFC->getType().isNode())
            {
                pNode = NodePtr::dcast(_pCurrentFC);

                pCore = pNode->getCore();

                beginEditCP(pCore);
            }
        }
    }

    _fStack.push (_pCurrentField);
    _fdStack.push(_pCurrentFieldDesc);
}

void VRMLFile::endField(void)
{
    _fStack.pop();

    if(_fStack.size() != 0)
    {
        _pCurrentField = _fStack.top(); 
    }
    else
    {
        _pCurrentField = NULL;
    }


    if(_pCurrentFieldDesc != NULL)
    {
        NodeCorePtr pCore;
        NodePtr     pNode;

        if(_pCurrentFC != NullFC)
        {
            endEditCP(_pCurrentFC);

            if(_pCurrentFC->getType().isNode())
            {
                pNode = NodePtr::dcast(_pCurrentFC);

                pCore = pNode->getCore();

                endEditCP(pCore);
            }
        }
    }

    _fdStack.pop();
    
    if(_fdStack.size() != 0)
    {
        _pCurrentFieldDesc = _fdStack.top();
    }
    else
    {
        _pCurrentFieldDesc = NULL;
    }

    VRMLNodeDesc::decIndent();

    indentLog(VRMLNodeDesc::getIndent(), PNOTICE);
    PNOTICE << "VRMLFile::endField " << endl;
}


void VRMLFile::addFieldValue(const Char8 *szFieldVal)
{
    Inherited::addFieldValue(szFieldVal);

    if(_pCurrNodeDesc != NULL)
    {
        _pCurrNodeDesc->addFieldValue(_pCurrentField, szFieldVal);
    }
}

/*---------------------------- properties ---------------------------------*/

UInt32 VRMLFile::getFieldType(const Char8 *szFieldname)
{
    UInt32   returnValue = 0;

    if(_pCurrNodeDesc == 0)
        return returnValue;

    if(szFieldname == NULL)
        return returnValue;

    _pCurrentField     = NULL;
    _pCurrentFieldDesc = NULL;

    _pCurrNodeDesc->getFieldAndDesc(_pCurrentFC, 
                                     szFieldname,
                                    _pCurrentField,
                                    _pCurrentFieldDesc);

    if(_pCurrentField != NULL)
        returnValue = _pCurrentField->getType().getId();

    indentLog(VRMLNodeDesc::getIndent(), PNOTICE);
    PNOTICE << "VRMLFile::getFieldType : Got Field and type "
            << returnValue        << " " 
            << _pCurrentField     << " " 
            << _pCurrentFieldDesc << " ";
    
    if(_pCurrentField != NULL)
        PNOTICE << _pCurrentField->getType().getName() << endl;
    else
        PNOTICE << endl;

    return returnValue;
}

/*-------------------------- your_category---------------------------------*/

void VRMLFile::use(const Char8 *szName)
{
    FieldContainerPtr pUsedFC;

    // try to find a container with the given name attachment

    indentLog(VRMLNodeDesc::getIndent(), PNOTICE);
    PNOTICE << "VRMLFile::use : looking for " 
            << szName 
            << endl;

    VRMLNodeDesc::incIndent();

    pUsedFC = findReference(szName);

    if(pUsedFC == NullFC)
    {
        PWARNING << "No fieldContainer with name found to use" 
                 << szName 
                 << endl; 
    }
    else
    {
        // assign nodepointer to current sf|mf field

        VRMLNodeDesc *pDesc = NULL;

        NameDescriptionMap::iterator mIt         = 
            _nameDescMap.find(StringLink(szName));

        if(mIt != _nameDescMap.end())
        {
            pDesc = mIt->second;
        }
        
        if(pUsedFC->getType().isNode())
        {
            NodePtr pRootNode = NodePtr::dcast(pUsedFC);

            pUsedFC = cloneTree(pRootNode);
        }

        if(pDesc != NULL)
        {
            if(pDesc->use(pUsedFC) == false)
            {
                setContainerFieldValue(pUsedFC);
            }
        }
        else
        {
            setContainerFieldValue(pUsedFC);
        }
    }

    VRMLNodeDesc::decIndent();
}

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

void VRMLFile::scanStandardPrototypes(const Char8  *szFilename, 
                                            UInt32  uiOptions)
{
    VRMLNodeDesc::resetIndent();

    preStandardProtos();
    scanFile(szFilename, uiOptions);
    postStandardProtos();

//    dumpTable();
}

NodePtr VRMLFile::getRoot(void)
{
    return _pRootNode;
}

NodePtr VRMLFile::cloneTree(NodePtr pRootNode)
{
    NodePtr returnValue = NullNode;

    if(pRootNode != NullFC)
    {
        NodePtr pChildClone = NullNode;

        returnValue = Node::create();

        returnValue->setCore(pRootNode->getCore());

        for(UInt32 i = 0; i < pRootNode->getNChildren(); i++)
        {
            pChildClone = cloneTree(pRootNode->getChild(i));
            
            returnValue->addChild(pChildClone);
        }
    }

    return returnValue;
}

//---------------------------------------------------------------------------
//  FUNCTION: 
//---------------------------------------------------------------------------
//:  Example for the head comment of a function
//---------------------------------------------------------------------------
//
//p: Paramaters: 
//p: 
//
//g: GlobalVars:
//g: 
//
//r: Return:
//r: 
//
//c: Caution:
//c: 
//
//a: Assumptions:
//a: 
//
//d: Description:
//d: 
//
//s: SeeAlso:
//s: 
//---------------------------------------------------------------------------

