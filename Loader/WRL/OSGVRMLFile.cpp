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

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGVRMLFILE_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif


#ifndef __sgi
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
    
    setIntExtMapping(SFGeoPTypesPtr::getClassType().getId(),
                     ScanParseSkel::OSGsfNode);

    setIntExtMapping(SFGeoIndicesPtr::getClassType().getId(),
                     ScanParseSkel::OSGsfNode);

    setIntExtMapping(SFGeoPLengthsPtr::getClassType().getId(),
                     ScanParseSkel::OSGsfNode);

    setIntExtMapping(SFGeoColorsPtr::getClassType().getId(),
                     ScanParseSkel::OSGsfNode);

    setIntExtMapping(SFGeoPositionsPtr::getClassType().getId(),
                     ScanParseSkel::OSGsfNode);

    setIntExtMapping(SFGeoNormalsPtr::getClassType().getId(),
                     ScanParseSkel::OSGsfNode);

    setIntExtMapping(SFGeoTexCoordsPtr::getClassType().getId(),
                     ScanParseSkel::OSGsfNode);

    setIntExtMapping(MFStateChunkPtr::getClassType().getId(),
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
        if(strcmp(szName, pNodename->getFieldPtr()->getValue().c_str())==0)
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
            if(strcmp(szName, pNodename->getFieldPtr()->getValue().c_str())==0)
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
        _nameFCMap.find(IDStringLink(szName));

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
            indentLog(VRMLNodeDesc::getIndent(), PINFO);
            PINFO << "Add Child "
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
            indentLog(VRMLNodeDesc::getIndent(), PINFO);
            PINFO << "Add Core "
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

    _pRootNode    (NullFC),

    _pCurrNodeDesc(NULL),
    _sNodeDescs   (),

    _pCurrentFC       (NullFC),
    _pCurrentField    (NULL),
    _pCurrentFieldDesc(NULL),

    _fcStack  (),
    _fStack   (),
    _fdStack  (),

    _nameFCMap  (),
    _nameDescMap(),

    _pathHandler()
{
    setReferenceHeader("#VRML V2.0 ");

    setDefaultOptions (VRMLFile::StripeGeometry |
                       VRMLFile::CreateNormals  );

    initIntExtFieldTypeMapper();
    initExtIntFieldTypeMapper();

    _pathHandler.push_frontCurrentDir();
}

/** \brief Destructor
 */

VRMLFile::~VRMLFile(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLFile::scanFile(const Char8 *szFilename, UInt32 uiOptions)
{
    _pRootNode = NullFC;

    VRMLNodeDesc::resetIndent();

    if(szFilename != NULL)
    {
        string tmpName;

        _pathHandler.setBaseFile(szFilename);

        tmpName = _pathHandler.findFile(szFilename);

        if(tmpName.size() != 0)
        {
            Inherited::scanFile(tmpName.c_str(), 
                                uiOptions);
        }
    }
}

void VRMLFile::scanFile(const Char8  *szFilename, 
                              UInt32  uiAddOptions,
                              UInt32  uiSubOptions)
{
    _pRootNode = NullFC;

    VRMLNodeDesc::resetIndent();

    if(szFilename != NULL)
    {
        string tmpName;

        _pathHandler.setBaseFile(szFilename);

        tmpName = _pathHandler.findFile(szFilename);

        if(tmpName.size() != 0)
        {
            Inherited::scanFile(tmpName.c_str(),
                                uiAddOptions, 
                                uiSubOptions);
        }
    }
}

void VRMLFile::beginNode(
    const Char8 *szNodeTypename,
    const Char8 *szNodename)
{
    FieldContainerPtr pNewNode;

    _pCurrNodeDesc = findNodeDesc(szNodeTypename);

    if(_pCurrNodeDesc == NULL)
        return;
    
    _pCurrNodeDesc->setOptions    ( _uiCurrOptions);
    _pCurrNodeDesc->setPathHandler(&_pathHandler);

    _sNodeDescs.push(_pCurrNodeDesc);

    _pCurrNodeDesc->reset();

    pNewNode = _pCurrNodeDesc->beginNode(szNodeTypename, 
                                         szNodename,
                                         _pCurrentFC);

    indentLog(VRMLNodeDesc::getIndent(), PINFO);
    PINFO << "Begin Node " << szNodeTypename << endl;

    VRMLNodeDesc::incIndent();

    if(szNodename != NULL)
    {
        if(pNewNode != NullFC)
        {
            if(pNewNode->getType().isNode() == true)
            {
                indentLog(VRMLNodeDesc::getIndent(), PINFO);
                PINFO << "Node named : " << szNodename << endl;

                NodePtr pNode     = NodePtr::dcast(pNewNode);
                NamePtr pNodename = Name::create();

                beginEditCP(pNodename);
                beginEditCP(pNode,Node::AttachmentsFieldMask);

                pNodename->getFieldPtr()->getValue().assign(szNodename);
                pNode->addAttachment(pNodename);

                endEditCP(pNode,Node::AttachmentsFieldMask);
                endEditCP(pNodename);
            }
            else if(pNewNode->getType().isNodeCore() == true)
            {
                indentLog(VRMLNodeDesc::getIndent(), PINFO);
                PINFO << "Nodecore named : " << szNodename << endl;

                NodeCorePtr pNodeCore = NodeCorePtr::dcast(pNewNode);
                NamePtr     pNodename = Name::create();
                
                beginEditCP(pNodename);
                beginEditCP(pNodeCore,NodeCore::AttachmentsFieldMask);

                pNodename->getFieldPtr()->getValue().assign(szNodename);
                pNodeCore->addAttachment(pNodename);           

                endEditCP(pNodeCore,NodeCore::AttachmentsFieldMask);
                endEditCP(pNodename);
            }
            else
            {
                indentLog(VRMLNodeDesc::getIndent(), PINFO);
                PINFO << "Fieldcontainer " << szNodeTypename 
                      << " is neither node nor nodecore " << endl;

                
                NameContainerMap::iterator mIt = 
                    _nameFCMap.find(IDStringLink(szNodename));
                
                if(mIt == _nameFCMap.end())
                {
                    _nameFCMap[IDString(szNodename)] = pNewNode;
                    
                    indentLog(VRMLNodeDesc::getIndent(), PINFO);
                    PINFO << "Fieldcontainer " << szNodename 
                          << " added to map " << endl;
                }
                
            }

            _nameDescMap[IDString(szNodename)] = _pCurrNodeDesc;
            
            indentLog(VRMLNodeDesc::getIndent(), PINFO);
            PINFO << "Desc for " << szNodename << " added to map " << endl;
        }
        else
        {
            indentLog(VRMLNodeDesc::getIndent(), PINFO);
            PINFO << "Fieldcontainer " 
                  << szNodeTypename 
                  << "is empty, save on end " 
                  << endl;
            
            if(_pCurrNodeDesc != NULL)
                _pCurrNodeDesc->setOnEndSave(szNodename);
            
            _nameDescMap[IDString(szNodename)] = _pCurrNodeDesc;
            
            indentLog(VRMLNodeDesc::getIndent(), PINFO);
            PINFO << "Desc for " << szNodename << " added to map " << endl;
        }
    }

    setContainerFieldValue(pNewNode);

    _pCurrentFC = pNewNode;

    _fcStack.push(_pCurrentFC);

    if(_fcStack.size() == 1)
    {
        NodePtr pNode = NodePtr::dcast(_pCurrentFC);

        if(_pRootNode == NullFC)
        {
            GroupPtr pGroup = Group::create();

            _pRootNode = Node::create();
            beginEditCP(_pRootNode,Node::CoreFieldMask);
            _pRootNode->setCore(pGroup);
            endEditCP(_pRootNode,Node::CoreFieldMask);
        }

        beginEditCP(_pRootNode,Node::ChildrenFieldMask);
        _pRootNode->addChild(pNode);
        endEditCP(_pRootNode,Node::ChildrenFieldMask);
    }
}
   
void VRMLFile::endNode(void)
{
    if(_pCurrNodeDesc == NULL)
    {
        VRMLNodeDesc::decIndent();

        indentLog(VRMLNodeDesc::getIndent(), PINFO);
        PINFO << "End Node " << endl;

        return;
    }

    _pCurrNodeDesc->endNode(_pCurrentFC);

    if(_pCurrNodeDesc->getOnEndSave() == true)
    {
        SLOG << "Fieldcontainer " <<  _pCurrNodeDesc->getSavename()
             << " on end Save " << endl;

        NameContainerMap::iterator mIt = 
            _nameFCMap.find(IDStringLink(_pCurrNodeDesc->getSavename()));
        
        if(mIt == _nameFCMap.end())
        {
            _nameFCMap[IDString(_pCurrNodeDesc->getSavename())] = 
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
            
            if(pNode->getCore() == NullFC)
            {
                GroupPtr pGroup = Group::create();

                beginEditCP(pNode);
                pNode->setCore(pGroup);
                beginEditCP(pNode);
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

    indentLog(VRMLNodeDesc::getIndent(), PINFO);
    PINFO << "End Node " << endl;
}

void VRMLFile::beginField(const Char8  *szFieldname,
                          const UInt32  uiFieldTypeId)
{
    if(szFieldname == NULL)
        return;

    indentLog(VRMLNodeDesc::getIndent(), PINFO);
    PINFO << "VRMLFile::beginField : looking for " 
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

    indentLog(VRMLNodeDesc::getIndent(), PINFO);
    PINFO << "VRMLFile::endField " << endl;
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

    indentLog(VRMLNodeDesc::getIndent(), PINFO);
    PINFO << "VRMLFile::getFieldType : Got Field and type "
          << returnValue        << " " 
          << _pCurrentField     << " " 
          << _pCurrentFieldDesc << " ";
    
    if(_pCurrentField != NULL)
        PINFO << _pCurrentField->getType().getName() << endl;
    else
        PINFO << endl;

    return returnValue;
}

/*-------------------------- your_category---------------------------------*/

void VRMLFile::use(const Char8 *szName)
{
    FieldContainerPtr pUsedFC;

    // try to find a container with the given name attachment

    indentLog(VRMLNodeDesc::getIndent(), PINFO);
    PINFO << "VRMLFile::use : looking for " 
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
            _nameDescMap.find(IDStringLink(szName));

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

void VRMLFile::createStandardPrototypes(void)
{
    VRMLNodeDesc::resetIndent();

    preStandardProtos();

#if 0
PROTO Anchor [
    eventIn      MFNode   addChildren
    eventIn      MFNode   removeChildren
    exposedField MFNode   children        []
    exposedField SFString description     "" 
    exposedField MFString parameter       []
    exposedField MFString url             []
    field        SFVec3f  bboxCenter      0 0 0
    field        SFVec3f  bboxSize        -1 -1 -1
    ] { }
#endif
 
 beginProtoInterface   ("Anchor"); 
 {
     addProtoEventIn       ("MFNode", "addChildren");
     addProtoEventIn       ("MFNode", "removeChildren");
     
     beginProtoExposedField("MFNode",   OSGmfNode,   "children");
     endProtoExposedField  ();

     beginProtoExposedField("SFString", OSGsfString, "description");
     endProtoExposedField  ();

     beginProtoExposedField("MFString", OSGmfString, "parameter");
     endProtoExposedField  ();

     beginProtoExposedField("MFString", OSGmfString, "url");
     endProtoExposedField  ();
     
     beginProtoField       ("SFVec3f",  OSGsfVec3f, "bboxCenter");
     addFieldValue         ("0 0 0");
     endProtoField         ();

     beginProtoField       ("SFVec3f",  OSGsfVec3f, "bboxSize");
     addFieldValue         ("-1 -1 -1");
     endProtoField         ();
 }
 endProtoInterface     ();

    
#if 0
PROTO Appearance [
  exposedField SFNode material          NULL
  exposedField SFNode texture           NULL
  exposedField SFNode textureTransform  NULL
] { }
#endif

 beginProtoInterface("Appearance");
 {
     beginProtoExposedField("SFNode", OSGsfNode, "material");
//     addFieldValue         ("NULL");
     endProtoExposedField  ();

     beginProtoExposedField("SFNode", OSGsfNode, "texture");
//     addFieldValue         ("NULL");
     endProtoExposedField  ();

     beginProtoExposedField("SFNode", OSGsfNode, "textureTransform");
//     addFieldValue         ("NULL");
     endProtoExposedField  ();
 }
 endProtoInterface  ();

#if 0
PROTO AudioClip [
  exposedField   SFString description  ""
  exposedField   SFBool   loop         FALSE
  exposedField   SFFloat  pitch        1.0
  exposedField   SFTime   startTime    0
  exposedField   SFTime   stopTime     0
  exposedField   MFString url          []
  eventOut       SFTime   duration_changed
  eventOut       SFBool   isActive
] { }
#endif

 beginProtoInterface("AudioClip");
 {
     beginProtoExposedField("SFString", OSGsfString, "description");
     addFieldValue         ("");
     endProtoExposedField  ();
     
     beginProtoExposedField("SFBool", OSGsfBool, "loop");
     addFieldValue         ("FALSE");
     endProtoExposedField  ();

     beginProtoExposedField("SFFloat", OSGsfFloat, "pitch");
     addFieldValue         ("1.0");
     endProtoExposedField  ();

     beginProtoExposedField("SFTime", OSGsfTime, "startTime");
     addFieldValue         ("0");
     endProtoExposedField  ();

     beginProtoExposedField("SFTime", OSGsfTime, "stopTime");
     addFieldValue         ("0");
     endProtoExposedField  ();

     beginProtoExposedField("MFString", OSGmfString, "url");
     endProtoExposedField  ();

     addProtoEventOut      ("SFTime", "duration_changed");
     addProtoEventOut      ("SFBool", "isActive");
 }
 endProtoInterface  ();

#if 0
PROTO Background [
  eventIn      SFBool   set_bind
  exposedField MFFloat  groundAngle  []
  exposedField MFColor  groundColor  []
  exposedField MFString backUrl      []
  exposedField MFString bottomUrl    []
  exposedField MFString frontUrl     []
  exposedField MFString leftUrl      []
  exposedField MFString rightUrl     []
  exposedField MFString topUrl       []
  exposedField MFFloat  skyAngle     []
  exposedField MFColor  skyColor     [ 0 0 0  ]
  eventOut     SFBool   isBound
] { }
#endif

 beginProtoInterface("Background");
 {
     addProtoEventIn       ("SFBool", "set_bind");
     
     beginProtoExposedField("MFFloat", OSGmfFloat, "groundAngle");
     endProtoExposedField  ();

     beginProtoExposedField("MFColor", OSGmfColor, "groundColor");
     endProtoExposedField  ();

     beginProtoExposedField("MFString", OSGmfString, "backUrl");
     endProtoExposedField  ();

     beginProtoExposedField("MFString", OSGmfString, "bottomUrl");
     endProtoExposedField  ();

     beginProtoExposedField("MFString", OSGmfString, "frontUrl");
     endProtoExposedField  ();

     beginProtoExposedField("MFString", OSGmfString, "leftUrl");
     endProtoExposedField  ();

     beginProtoExposedField("MFString", OSGmfString, "rightUrl");
     endProtoExposedField  ();

     beginProtoExposedField("MFString", OSGmfString, "topUrl");
     endProtoExposedField  ();

     beginProtoExposedField("MFFloat", OSGmfFloat, "skyAngle");
     endProtoExposedField  ();

     beginProtoExposedField("MFColor", OSGmfColor, "skyColor");
     addFieldValue         ("0 0 0");
     endProtoExposedField  ();

     addProtoEventOut      ("SFBool", "isBound");
 }
 endProtoInterface  ();


#if 0
PROTO Billboard [
  eventIn      MFNode   addChildren
  eventIn      MFNode   removeChildren
  exposedField SFVec3f  axisOfRotation  0 1 0
  exposedField MFNode   children        []
  field        SFVec3f  bboxCenter      0 0 0
  field        SFVec3f  bboxSize        -1 -1 -1
] { }
#endif

 beginProtoInterface("Billboard");
 {
     addProtoEventIn       ("MFNode", "addChildren");
     addProtoEventIn       ("MFNode", "removeChildren");
     
     beginProtoExposedField("SFVec3f", OSGsfVec3f, "axisOfRotation");
     addFieldValue         ("0 1 0");
     endProtoExposedField  ();

     beginProtoExposedField("MFNode", OSGmfNode, "children");
     endProtoExposedField  ();
     
     beginProtoField       ("SFVec3f", OSGsfVec3f, "bboxCenter");
     addFieldValue         ("0 0 0");
     endProtoField         ();

     beginProtoField       ("SFVec3f", OSGsfVec3f, "bboxSize");
     addFieldValue         ("-1 -1 -1");
     endProtoField         ();
 }
 endProtoInterface  ();

#if 0
PROTO Box [
  field    SFVec3f size  2 2 2 
] { }
#endif

 beginProtoInterface("Box");
 {
     beginProtoField("SFVec3f", OSGsfVec3f, "size");
     addFieldValue  ("2 2 2");
     endProtoField  ();
 }
 endProtoInterface  ();

#if 0
PROTO Collision [ 
  eventIn      MFNode   addChildren
  eventIn      MFNode   removeChildren
  exposedField MFNode   children        []
  exposedField SFBool   collide         TRUE
  field        SFVec3f  bboxCenter      0 0 0
  field        SFVec3f  bboxSize        -1 -1 -1
  field        SFNode   proxy           NULL
  eventOut     SFTime   collideTime
] { }
#endif

 beginProtoInterface("Collision");
 {
     addProtoEventIn      ("MFNode", "addChildren");
     addProtoEventIn      ("MFNode", "removeChildren");

     beginProtoExposedField("MFNode", OSGmfNode, "children");
     endProtoExposedField  ();

     beginProtoExposedField("SFBool", OSGsfBool, "collide");
     addFieldValue         ("TRUE");
     endProtoExposedField  ();

     beginProtoField       ("SFVec3f", OSGsfVec3f, "bboxCenter");
     addFieldValue         ("0 0 0");
     endProtoField         ();

     beginProtoField       ("SFVec3f", OSGsfVec3f, "bboxSize");
     addFieldValue         ("-1 -1 -1");
     endProtoField         ();

     beginProtoField       ("SFNode", OSGsfNode, "proxy");
     endProtoField         ();
     
     addProtoEventOut      ("SFTime", "collideTime");
 }
 endProtoInterface  ();

#if 0
PROTO Color [
  exposedField MFColor color     []
] { }
#endif

 beginProtoInterface("Color");
 {
     beginProtoExposedField("MFColor", OSGmfColor, "color");
     endProtoExposedField  ();
 }
 endProtoInterface  ();

#if 0
PROTO ColorInterpolator [
  eventIn      SFFloat set_fraction
  exposedField MFFloat key       []
  exposedField MFColor keyValue  []
  eventOut     SFColor value_changed
] { }
#endif

 beginProtoInterface("ColorInterpolator");
 {
     addProtoEventIn       ("SFFloat", "set_fraction");

     beginProtoExposedField("MFFloat", OSGmfFloat, "key");
     endProtoExposedField  ();

     beginProtoExposedField("MFColor", OSGmfColor, "keyValue");
     endProtoExposedField  ();

     addProtoEventOut      ("SFColor", "value_changed");
 }
 endProtoInterface  ();

#if 0
PROTO Cone [
  field     SFFloat   bottomRadius 1
  field     SFFloat   height       2
  field     SFBool    side         TRUE
  field     SFBool    bottom       TRUE
] { }
#endif

 beginProtoInterface("Cone");
 {
     beginProtoField("SFFloat", OSGsfFloat, "bottomRadius");
     addFieldValue  ("1");
     endProtoField  ();

     beginProtoField("SFFloat", OSGsfFloat, "height");
     addFieldValue  ("2");
     endProtoField  ();

     beginProtoField("SFBool", OSGsfBool, "side");
     addFieldValue  ("TRUE");
     endProtoField  ();

     beginProtoField("SFBool", OSGsfBool, "bottom");
     addFieldValue  ("TRUE");
     endProtoField  ();
 }
 endProtoInterface  ();

#if 0
PROTO Coordinate [
  exposedField MFVec3f point  []
] { }
#endif

 beginProtoInterface("Coordinate");
 {
     beginProtoExposedField("MFVec3f", OSGmfVec3f, "point");
     endProtoExposedField  ();
 }
 endProtoInterface  ();

#if 0
PROTO CoordinateInterpolator [
  eventIn      SFFloat set_fraction
  exposedField MFFloat key       []
  exposedField MFVec3f keyValue  []
  eventOut     MFVec3f value_changed
] { }
#endif

 beginProtoInterface("CoordinateInterpolator");
 {
     addProtoEventIn       ("SFFloat", "set_fraction");
     
     beginProtoExposedField("MFFloat", OSGmfFloat, "key");
     endProtoExposedField  ();

     beginProtoExposedField("MFVec3f", OSGmfVec3f, "keyValue");
     endProtoExposedField  ();

     addProtoEventOut      ("MFVec3f", "value_changed");
 }
 endProtoInterface  ();

#if 0
PROTO Cylinder [
  field    SFBool    bottom  TRUE
  field    SFFloat   height  2
  field    SFFloat   radius  1
  field    SFBool    side    TRUE
  field    SFBool    top     TRUE
] { }
#endif

 beginProtoInterface("Cylinder");
 {
     beginProtoField("SFBool", OSGsfBool, "bottom");
     addFieldValue  ("TRUE");
     endProtoField  ();

     beginProtoField("SFFloat", OSGsfFloat, "height");
     addFieldValue  ("2");
     endProtoField  ();

     beginProtoField("SFFloat", OSGsfFloat, "radius");
     addFieldValue  ("1");
     endProtoField  ();

     beginProtoField("SFBool", OSGsfBool, "side");
     addFieldValue  ("TRUE");
     endProtoField  ();

     beginProtoField("SFBool", OSGsfBool, "top");
     addFieldValue  ("TRUE");
     endProtoField  ();
 }
 endProtoInterface  ();

#if 0
PROTO CylinderSensor [
  exposedField SFBool     autoOffset TRUE
  exposedField SFFloat    diskAngle  0.262
  exposedField SFBool     enabled    TRUE
  exposedField SFFloat    maxAngle   -1
  exposedField SFFloat    minAngle   0
  exposedField SFFloat    offset     0
  eventOut     SFBool     isActive
  eventOut     SFRotation rotation_changed
  eventOut     SFVec3f    trackPoint_changed
] { }
#endif

 beginProtoInterface("CylinderSensor");
 {
     beginProtoExposedField("SFBool", OSGsfBool, "autoOffset");
     addFieldValue         ("TRUE");
     endProtoExposedField  ();

     beginProtoExposedField("SFFloat", OSGsfFloat, "diskAngle");
     addFieldValue         ("0.262");
     endProtoExposedField  ();

     beginProtoExposedField("SFBool", OSGsfBool, "enabled");
     addFieldValue         ("TRUE");
     endProtoExposedField  ();

     beginProtoExposedField("SFFloat", OSGsfFloat, "maxAngle");
     addFieldValue         ("-1");
     endProtoExposedField  ();

     beginProtoExposedField("SFFloat", OSGsfFloat, "minAngle");
     addFieldValue         ("0");
     endProtoExposedField  ();

     beginProtoExposedField("SFFloat", OSGsfFloat, "offset");
     addFieldValue         ("0");
     endProtoExposedField  ();
     
     addProtoEventOut      ("SFBool", "isActive");
     addProtoEventOut      ("SFRotation", "rotation_changed");
     addProtoEventOut      ("SFVec3f", "trackPoint_changed");
 }
 endProtoInterface  ();

#if 0
PROTO DirectionalLight [
  exposedField SFFloat ambientIntensity  0 
  exposedField SFColor color             1 1 1
  exposedField SFVec3f direction         0 0 -1
  exposedField SFFloat intensity         1 
  exposedField SFBool  on                TRUE 
] { }
#endif

 beginProtoInterface("DirectionalLight");
 {
     beginProtoExposedField("SFFloat", OSGsfFloat, "ambientIntensity");
     addFieldValue         ("0"); 
     endProtoExposedField  ();

     beginProtoExposedField("SFColor", OSGsfColor, "color");
     addFieldValue         ("1 1 1");
     endProtoExposedField  ();

     beginProtoExposedField("SFVec3f", OSGsfVec3f, "direction");
     addFieldValue         ("0 0 -1");
     endProtoExposedField  ();

     beginProtoExposedField("SFFloat", OSGsfFloat, "intensity");
     addFieldValue         ("1"); 
     endProtoExposedField  ();

     beginProtoExposedField("SFBool", OSGsfBool, "on");
     addFieldValue         ("TRUE");
     endProtoExposedField  ();
 }
 endProtoInterface  ();

#if 0
PROTO ElevationGrid [
  eventIn      MFFloat  set_height
  exposedField SFNode   color             NULL
  exposedField SFNode   normal            NULL
  exposedField SFNode   texCoord          NULL
  field        SFBool   ccw               TRUE
  field        SFBool   colorPerVertex    TRUE
  field        SFFloat  creaseAngle       0
  field        MFFloat  height            []
  field        SFBool   normalPerVertex   TRUE
  field        SFBool   solid             TRUE
  field        SFInt32  xDimension        0
  field        SFFloat  xSpacing          0.0
  field        SFInt32  zDimension        0
  field        SFFloat  zSpacing          0.0

] { }
#endif

 beginProtoInterface("ElevationGrid");
 {
     addProtoEventIn       ("MFFloat", "set_height");

     beginProtoExposedField("SFNode", OSGsfNode, "color");
//     addFieldValue         ("NULL");
     endProtoExposedField  ();

     beginProtoExposedField("SFNode", OSGsfNode, "normal");
//     addFieldValue         ("NULL");
     endProtoExposedField  ();

     beginProtoExposedField("SFNode", OSGsfNode, "texCoord");
//     addFieldValue         ("NULL");
     endProtoExposedField  ();

     beginProtoField       ("SFBool", OSGsfBool, "ccw");
     addFieldValue         ("TRUE");
     endProtoField         ();

     beginProtoField       ("SFBool", OSGsfBool, "colorPerVertex");
     addFieldValue         ("TRUE");
     endProtoField         ();

     beginProtoField       ("SFFloat", OSGsfFloat, "creaseAngle");
     addFieldValue         ("0");
     endProtoField         ();

     beginProtoField       ("MFFloat", OSGsfFloat, "height");
     endProtoField         ();

     beginProtoField       ("SFBool", OSGsfBool, "normalPerVertex");
     addFieldValue         ("TRUE");
     endProtoField         ();

     beginProtoField       ("SFBool", OSGsfBool, "solid");
     addFieldValue         ("TRUE");
     endProtoField         ();

     beginProtoField       ("SFInt32", OSGsfInt32, "xDimension");
     addFieldValue         ("0");
     endProtoField         ();

     beginProtoField       ("SFFloat", OSGsfFloat, "xSpacing");
     addFieldValue         ("0.0");
     endProtoField         ();

     beginProtoField       ("SFInt32", OSGsfInt32, "zDimension");
     addFieldValue         ("0");
     endProtoField         ();

     beginProtoField       ("SFFloat", OSGsfFloat, "zSpacing");
     addFieldValue         ("0.0");
     endProtoField         ();
 }
 endProtoInterface  ();

#if 0
PROTO Extrusion [
  eventIn MFVec2f    set_crossSection
  eventIn MFRotation set_orientation
  eventIn MFVec2f    set_scale
  eventIn MFVec3f    set_spine
  field   SFBool     beginCap         TRUE
  field   SFBool     ccw              TRUE
  field   SFBool     convex           TRUE
  field   SFFloat    creaseAngle      0
  field   MFVec2f    crossSection     [ 1 1, 1 -1, -1 -1, -1 1, 1 1 ]
  field   SFBool     endCap           TRUE
  field   MFRotation orientation      0 0 1 0
  field   MFVec2f    scale            1 1
  field   SFBool     solid            TRUE
  field   MFVec3f    spine            [ 0 0 0, 0 1 0 ]
] { }
#endif

 beginProtoInterface("Extrusion");
 {
     addProtoEventIn("MFVec2f", "set_crossSection");
     addProtoEventIn("MFRotation", "set_orientation");
     addProtoEventIn("MFVec2f", "set_scale");
     addProtoEventIn("MFVec3f", "set_spine");

     beginProtoField("SFBool", OSGsfBool, "beginCap");
     addFieldValue  ("TRUE");
     endProtoField  ();

     beginProtoField("SFBool", OSGsfBool, "ccw");
     addFieldValue  ("TRUE");
     endProtoField  ();

     beginProtoField("SFBool", OSGsfBool, "convex");
     addFieldValue  ("TRUE");
     endProtoField  ();

     beginProtoField("SFFloat", OSGsfFloat, "creaseAngle");
     addFieldValue  ("0");
     endProtoField  ();

     beginProtoField("MFVec2f", OSGmfVec2f, "crossSection");
     addFieldValue  (" 1  1");
     addFieldValue  (" 1 -1");
     addFieldValue  ("-1 -1");
     addFieldValue  ("-1  1");
     addFieldValue  (" 1  1");
     endProtoField  ();

     beginProtoField("SFBool", OSGsfBool, "endCap");
     addFieldValue  ("TRUE");
     endProtoField  ();

     beginProtoField("MFRotation", OSGmfRotation, "orientation");
     addFieldValue  ("0 0 1 0");
     endProtoField  ();

     beginProtoField("MFVec2f", OSGmfVec2f, "scale");
     addFieldValue  ("1 1");
     endProtoField  ();
     
     beginProtoField("SFBool", OSGsfBool, "solid");
     addFieldValue  ("TRUE");
     endProtoField  ();
     
     beginProtoField("MFVec3f", OSGmfVec3f, "spine");
     addFieldValue  ("0 0 0");
     addFieldValue  ("0 1 0");
     endProtoField  ();
 }
 endProtoInterface  ();

#if 0
PROTO Fog [
  exposedField SFColor  color            1 1 1
  exposedField SFString fogType          "LINEAR"
  exposedField SFFloat  visibilityRange  0
  eventIn      SFBool   set_bind
  eventOut     SFBool   isBound
] { }
#endif

 beginProtoInterface("Fog");
 {
     beginProtoExposedField("SFColor", OSGsfColor, "color");
     addFieldValue         ("1 1 1");
     endProtoExposedField  ();

     beginProtoExposedField("SFString", OSGsfString, "fogType");
     addFieldValue         ("LINEAR");
     endProtoExposedField  ();

     beginProtoExposedField("SFFloat", OSGsfFloat, "visibilityRange");
     addFieldValue         ("0");
     endProtoExposedField  ();

     addProtoEventIn       ("SFBool", "set_bind");
     addProtoEventOut      ("SFBool", "isBound");
 }
 endProtoInterface  ();

#if 0
PROTO FontStyle [
  field SFString family     "SERIF"
  field SFBool   horizontal  TRUE
  field MFString justify     "BEGIN"
  field SFString language    ""
  field SFBool   leftToRight TRUE
  field SFFloat  size       1.0
  field SFFloat  spacing     1.0
  field SFString style       "PLAIN"
  field SFBool   topToBottom TRUE
] { }
#endif

 beginProtoInterface("FontStyle");
 {
     beginProtoField("SFString", OSGsfString, "family");
     addFieldValue  ("SERIF");
     endProtoField  ();

     beginProtoField("SFBool", OSGsfBool, "horizontal");
     addFieldValue  ("TRUE");
     endProtoField  ();
     
     beginProtoField("MFString", OSGmfString, "justify");
     addFieldValue  ("BEGIN");
     endProtoField  ();

     beginProtoField("SFString", OSGsfString, "language");
     addFieldValue  ("");
     endProtoField  ();

     beginProtoField("SFBool", OSGsfBool, "leftToRight");
     addFieldValue  ("TRUE");
     endProtoField  ();

     beginProtoField("SFFloat", OSGsfFloat, "size");
     addFieldValue  ("1.0");
     endProtoField  ();

     beginProtoField("SFFloat", OSGsfFloat, "spacing");
     addFieldValue  ("1.0");
     endProtoField  ();

     beginProtoField("SFString", OSGsfString, "style");
     addFieldValue  ("PLAIN");
     endProtoField  ();

     beginProtoField("SFBool", OSGsfBool, "topToBottom");
     addFieldValue  ("TRUE");
     endProtoField  ();
 }
 endProtoInterface   ();

#if 0
PROTO Group [
  eventIn      MFNode  addChildren
  eventIn      MFNode  removeChildren
  exposedField MFNode  children   []
  field        SFVec3f bboxCenter 0 0 0
  field        SFVec3f bboxSize   -1 -1 -1
] { }
#endif

 beginProtoInterface("Group");
 {
     addProtoEventIn    ("MFNode", "addChildren");
     addProtoEventIn    ("MFNode", "removeChildren");
 
     beginProtoExposedField("MFNode", OSGmfNode, "children");
     endProtoExposedField  ();

     beginProtoField       ("SFVec3f", OSGsfVec3f, "bboxCenter");
     addFieldValue         ("0 0 0");
     endProtoField         ();

     beginProtoField       ("SFVec3f", OSGsfVec3f, "bboxSize");
     addFieldValue         ("-1 -1 -1");
     endProtoField         ();
 }
 endProtoInterface  ();

#if 0
PROTO ImageTexture [
  exposedField MFString url     []
  field        SFBool   repeatS TRUE
  field        SFBool   repeatT TRUE
] { }
#endif

 beginProtoInterface("ImageTexture");
 {
     beginProtoExposedField("MFString", OSGmfString, "url");
     endProtoExposedField  ();

     beginProtoField       ("SFBool", OSGsfBool, "repeatS");
     addFieldValue         ("TRUE");
     endProtoField         ();

     beginProtoField       ("SFBool", OSGsfBool, "repeatT");
     addFieldValue         ("TRUE");
     endProtoField         ();
 }
 endProtoInterface  ();

#if 0
PROTO IndexedFaceSet [ 
  eventIn       MFInt32 set_colorIndex
  eventIn       MFInt32 set_coordIndex
  eventIn       MFInt32 set_normalIndex
  eventIn       MFInt32 set_texCoordIndex
  exposedField  SFNode  color             NULL
  exposedField  SFNode  coord             NULL
  exposedField  SFNode  normal            NULL
  exposedField  SFNode  texCoord          NULL
  field         SFBool  ccw               TRUE
  field         MFInt32 colorIndex        []
  field         SFBool  colorPerVertex    TRUE
  field         SFBool  convex            TRUE
  field         MFInt32 coordIndex        []
  field         SFFloat creaseAngle       0
  field         MFInt32 normalIndex       []
  field         SFBool  normalPerVertex   TRUE
  field         SFBool  solid             TRUE
  field         MFInt32 texCoordIndex     []
] { }
#endif

 beginProtoInterface("IndexedFaceSet");
 { 
     addProtoEventIn       ("MFInt32", "set_colorIndex");
     addProtoEventIn       ("MFInt32", "set_coordIndex");
     addProtoEventIn       ("MFInt32", "set_normalIndex");
     addProtoEventIn       ("MFInt32", "set_texCoordIndex");
     
     beginProtoExposedField("SFNode", OSGsfNode, "color");
//     addFieldValue         ("NULL");
     endProtoExposedField  ();
     
     beginProtoExposedField("SFNode", OSGsfNode, "coord");
//     addFieldValue         ("NULL");
     endProtoExposedField  ();

     beginProtoExposedField("SFNode", OSGsfNode, "normal");
//     addFieldValue         ("NULL");
     endProtoExposedField  ();

     beginProtoExposedField("SFNode", OSGsfNode, "texCoord");
//     addFieldValue         ("NULL");
     endProtoExposedField  ();

     beginProtoField       ("SFBool", OSGsfBool, "ccw");
     addFieldValue         ("TRUE");
     endProtoField         ();

     beginProtoField       ("MFInt32", OSGmfInt32, "colorIndex");
     endProtoField         ();

     beginProtoField       ("SFBool", OSGsfBool, "colorPerVertex");
     addFieldValue         ("TRUE");
     endProtoField         ();

     beginProtoField       ("SFBool", OSGsfBool, "convex");
     addFieldValue         ("TRUE");
     endProtoField         ();

     beginProtoField       ("MFInt32", OSGmfInt32, "coordIndex");
     endProtoField         ();
     
     beginProtoField       ("SFFloat", OSGsfFloat, "creaseAngle");
     addFieldValue         ("0");
     endProtoField         ();

     beginProtoField       ("MFInt32", OSGmfInt32, "normalIndex");
     endProtoField         ();

     beginProtoField       ("SFBool",  OSGsfBool, "normalPerVertex");
     addFieldValue         ("TRUE");
     endProtoField         ();

     beginProtoField       ("SFBool",  OSGsfBool, "solid");
     addFieldValue         ("TRUE");
     endProtoField         ();
     
     beginProtoField       ("MFInt32", OSGmfInt32, "texCoordIndex");
     endProtoField();
 }
 endProtoInterface  ();

#if 0
PROTO IndexedLineSet [
  eventIn       MFInt32 set_colorIndex
  eventIn       MFInt32 set_coordIndex
  exposedField  SFNode  color             NULL
  exposedField  SFNode  coord             NULL
  field         MFInt32 colorIndex        []
  field         SFBool  colorPerVertex    TRUE
  field         MFInt32 coordIndex        []
] { }
#endif

 beginProtoInterface("IndexedLineSet");
 {
     addProtoEventIn       ("MFInt32", "set_colorIndex");
     addProtoEventIn       ("MFInt32", "set_coordIndex");

     beginProtoExposedField("SFNode", OSGsfNode, "color");
//     addFieldValue         ("NULL");
     endProtoExposedField  ();

     beginProtoExposedField("SFNode", OSGsfNode, "coord");
//     addFieldValue         ("NULL");
     endProtoExposedField  ();

     beginProtoField       ("MFInt32", OSGmfInt32, "colorIndex");
     endProtoField         ();

     beginProtoField       ("SFBool", OSGsfBool, "colorPerVertex");
     addFieldValue         ("TRUE");
     endProtoField         ();
     
     beginProtoField       ("MFInt32", OSGmfInt32, "coordIndex");
     endProtoField         ();
 }
 endProtoInterface  ();

#if 0
PROTO Inline [
  exposedField MFString url        []
  field        SFVec3f  bboxCenter 0 0 0
  field        SFVec3f  bboxSize   -1 -1 -1
] { }
#endif

 beginProtoInterface("Inline");
 {
     beginProtoExposedField("MFString", OSGmfString, "url");
     endProtoExposedField  ();

     beginProtoField       ("SFVec3f", OSGsfVec3f, "bboxCenter");
     addFieldValue         ("0 0 0");
     endProtoField         ();

     beginProtoField       ("SFVec3f", OSGsfVec3f, "bboxSize");
     addFieldValue         ("-1 -1 -1");
     endProtoField         ();
 }
 endProtoInterface  ();
   
#if 0
PROTO LOD [
  exposedField MFNode  level    [] 
  field        SFVec3f center   0 0 0
  field        MFFloat range    [] 
] { }
#endif

 beginProtoInterface("LOD");
 {
     beginProtoExposedField("MFNode", OSGmfNode, "level");
     endProtoExposedField  ();
     
     beginProtoField       ("SFVec3f", OSGsfVec3f, "center");
     addFieldValue         ("0 0 0");
     endProtoField         ();

     beginProtoField       ("MFFloat", OSGmfFloat, "range");
     endProtoField         ();
 }
 endProtoInterface  ();

#if 0
PROTO Material [
  exposedField SFFloat ambientIntensity  0.2
  exposedField SFColor diffuseColor      0.8 0.8 0.8
  exposedField SFColor emissiveColor     0 0 0
  exposedField SFFloat shininess         0.2
  exposedField SFColor specularColor     0 0 0
  exposedField SFFloat transparency      0
] { }
#endif

 beginProtoInterface("Material");
 {
     beginProtoExposedField("SFFloat", OSGsfFloat, "ambientIntensity");
     addFieldValue         ("0.2");
     endProtoExposedField  ();

     beginProtoExposedField("SFColor", OSGsfColor, "diffuseColor");
     addFieldValue         ("0.8 0.8 0.8");
     endProtoExposedField  ();
     
     beginProtoExposedField("SFColor", OSGsfColor, "emissiveColor");
     addFieldValue         ("0 0 0");
     endProtoExposedField  ();

     beginProtoExposedField("SFFloat", OSGsfFloat, "shininess");
     addFieldValue         ("0.2");
     endProtoExposedField  ();

     beginProtoExposedField("SFColor", OSGsfColor, "specularColor");
     addFieldValue         ("0 0 0");
     endProtoExposedField  ();

     beginProtoExposedField("SFFloat", OSGsfFloat, "transparency");
     addFieldValue         ("0");
     endProtoExposedField  ();
 }
 endProtoInterface  ();

#if 0
PROTO MovieTexture [
  exposedField SFBool   loop       FALSE
  exposedField SFFloat  speed      1
  exposedField SFTime   startTime  0
  exposedField SFTime   stopTime   0
  exposedField MFString url       []
  field        SFBool   repeatS    TRUE
  field        SFBool   repeatT    TRUE
  eventOut     SFFloat  duration_changed
  eventOut     SFBool   isActive
] { }
#endif

 beginProtoInterface("MovieTexture");
 {
     beginProtoExposedField("SFBool", OSGsfBool, "loop");
     addFieldValue         ("FALSE");
     endProtoExposedField  ();

     beginProtoExposedField("SFFloat", OSGsfFloat, "speed");
     addFieldValue         ("1");
     endProtoExposedField  ();

     beginProtoExposedField("SFTime", OSGsfTime, "startTime");
     addFieldValue         ("0");
     endProtoExposedField  ();

     beginProtoExposedField("SFTime", OSGsfTime, "stopTime");
     addFieldValue         ("0");
     endProtoExposedField  ();

     beginProtoExposedField("MFString", OSGmfString, "url");
     endProtoExposedField  ();

     beginProtoField       ("SFBool", OSGsfBool, "repeatS");
     addFieldValue         ("TRUE");
     endProtoField         ();

     beginProtoField       ("SFBool", OSGsfBool, "repeatT");
     addFieldValue         ("TRUE");
     endProtoField         ();

     addProtoEventOut      ("SFFloat", "duration_changed");
     addProtoEventOut      ("SFBool", "isActive");
 }
 endProtoInterface  ();

#if 0
PROTO NavigationInfo [
  eventIn      SFBool   set_bind
  exposedField MFFloat  avatarSize       [ 0.25, 1.6, 0.75 ]
  exposedField SFBool   headlight        TRUE
  exposedField SFFloat  speed            1.0 
  exposedField MFString type             "WALK" 
  exposedField SFFloat  visibilityLimit  0.0 
  eventOut     SFBool   isBound
] { }
#endif

 beginProtoInterface("NavigationInfo");
 {
     addProtoEventIn       ("SFBool", "set_bind");
     
     beginProtoExposedField("MFFloat", OSGmfFloat, "avatarSize");
     addFieldValue         ("0.25");
     addFieldValue         ("1.6 ");
     addFieldValue         ("0.75");
     endProtoExposedField  ();

     beginProtoExposedField("SFBool", OSGsfBool, "headlight");
     addFieldValue         ("TRUE");
     endProtoExposedField  ();

     beginProtoExposedField("SFFloat", OSGsfFloat, "speed");
     addFieldValue         ("1.0");
     endProtoExposedField  ();

     beginProtoExposedField("MFString", OSGmfString, "type");
     addFieldValue         ("WALK");
     endProtoExposedField  ();

     beginProtoExposedField("SFFloat", OSGsfFloat, "visibilityLimit");
     addFieldValue         ("0.0");
     endProtoExposedField  ();

     addProtoEventOut      ("SFBool", "isBound");
 }
 endProtoInterface  ();

#if 0
PROTO Normal [
  exposedField MFVec3f vector []
] { }
#endif

 beginProtoInterface("Normal");
 {
     beginProtoExposedField("MFVec3f", OSGmfVec3f, "vector");
     endProtoExposedField  ();
 }
 endProtoInterface  ();

#if 0
PROTO NormalInterpolator [
  eventIn      SFFloat set_fraction
  exposedField MFFloat key       []
  exposedField MFVec3f keyValue  []
  eventOut     MFVec3f value_changed
] { }
#endif

 beginProtoInterface("NormalInterpolator");
 {
     addProtoEventIn       ("SFFloat", "set_fraction");
     
     beginProtoExposedField("MFFloat", OSGmfFloat, "key");
     endProtoExposedField  ();

     beginProtoExposedField("MFVec3f", OSGmfVec3f, "keyValue");
     endProtoExposedField  ();

     addProtoEventOut      ("MFVec3f",  "value_changed");
 }
 endProtoInterface  ();

#if 0
PROTO OrientationInterpolator [
  eventIn      SFFloat    set_fraction
  exposedField MFFloat    key       []
  exposedField MFRotation keyValue  []
  eventOut     SFRotation value_changed
] { }
#endif

 beginProtoInterface("OrientationInterpolator");
 {
     addProtoEventIn       ("SFFloat", "set_fraction");

     beginProtoExposedField("MFFloat", OSGmfFloat, "key");
     endProtoExposedField  ();

     beginProtoExposedField("MFRotation", OSGmfRotation, "keyValue");
     endProtoExposedField  ();
     
     addProtoEventOut      ("SFRotation", "value_changed");
 }
 endProtoInterface  ();

#if 0
PROTO PixelTexture [
  exposedField SFImage  image      0 0 0
  field        SFBool   repeatS    TRUE
  field        SFBool   repeatT    TRUE
] { }
#endif

 beginProtoInterface("PixelTexture");
 {
     beginProtoExposedField("SFImage", OSGsfImage, "image");
     addFieldValue         ("0 0 0");
     endProtoExposedField  ();

     beginProtoField       ("SFBool", OSGsfBool, "repeatS");
     addFieldValue         ("TRUE");
     endProtoField         ();

     beginProtoField       ("SFBool", OSGsfBool, "repeatT");
     addFieldValue         ("TRUE");
     endProtoField         ();
 }
 endProtoInterface  ();

#if 0
PROTO PlaneSensor [
  exposedField SFBool  autoOffset  TRUE
  exposedField SFBool  enabled     TRUE
  exposedField SFVec2f maxPosition -1 -1
  exposedField SFVec2f minPosition 0 0
  exposedField SFVec3f offset      0 0 0
  eventOut     SFBool  isActive
  eventOut     SFVec3f trackPoint_changed
  eventOut     SFVec3f translation_changed
] { }
#endif

 beginProtoInterface("PlaneSensor");
 {
     beginProtoExposedField("SFBool", OSGsfBool, "autoOffset");
     addFieldValue         ("TRUE");
     endProtoExposedField  ();

     beginProtoExposedField("SFBool", OSGsfBool, "enabled");
     addFieldValue         ("TRUE");
     endProtoExposedField  ();

     beginProtoExposedField("SFVec2f", OSGsfVec2f, "maxPosition");
     addFieldValue         ("-1 -1");
     endProtoExposedField  ();

     beginProtoExposedField("SFVec2f", OSGsfVec2f, "minPosition");
     addFieldValue         ("0 0");
     endProtoExposedField  ();

     beginProtoExposedField("SFVec3f", OSGsfVec3f, "offset");
     addFieldValue         ("0 0 0");
     endProtoExposedField  ();

     addProtoEventOut      ("SFBool", "isActive");
     addProtoEventOut      ("SFVec3f", "trackPoint_changed");
     addProtoEventOut      ("SFVec3f", "translation_changed");
 }
 endProtoInterface  ();


#if 0
PROTO PointLight [
  exposedField SFFloat ambientIntensity  0 
  exposedField SFVec3f attenuation       1 0 0
  exposedField SFColor color             1 1 1 
  exposedField SFFloat intensity         1
  exposedField SFVec3f location          0 0 0
  exposedField SFBool  on                TRUE 
  exposedField SFFloat radius            100
] { }
#endif

 beginProtoInterface("PointLight");
 {
     beginProtoExposedField("SFFloat", OSGsfFloat, "ambientIntensity");
     addFieldValue         ("0");
     endProtoExposedField  ();

     beginProtoExposedField("SFVec3f", OSGsfVec3f, "attenuation");
     addFieldValue         ("1 0 0");
     endProtoExposedField  ();

     beginProtoExposedField("SFColor", OSGsfColor, "color");
     addFieldValue         ("1 1 1");
     endProtoExposedField  ();

     beginProtoExposedField("SFFloat", OSGsfFloat, "intensity");
     addFieldValue         ("1");
     endProtoExposedField  ();

     beginProtoExposedField("SFVec3f", OSGsfVec3f, "location");
     addFieldValue         ("0 0 0");
     endProtoExposedField  ();

     beginProtoExposedField("SFBool", OSGsfBool, "on");
     addFieldValue         ("TRUE");
     endProtoExposedField  ();

     beginProtoExposedField("SFFloat", OSGsfFloat, "radius");
     addFieldValue         ("100");
     endProtoExposedField  ();
 }
 endProtoInterface  ();

#if 0
PROTO PointSet [
  exposedField  SFNode  color      NULL
  exposedField  SFNode  coord      NULL
] { }
#endif

 beginProtoInterface("PointSet");
 {
     beginProtoExposedField("SFNode", OSGsfNode, "color");
//     addFieldValue         ("NULL");
     endProtoField         ();

     beginProtoExposedField("SFNode", OSGsfNode, "coord");
//     addFieldValue         ("NULL");
     endProtoField         ();
 }
 endProtoInterface  ();

#if 0
PROTO PositionInterpolator [
  eventIn      SFFloat set_fraction
  exposedField MFFloat key       []
  exposedField MFVec3f keyValue  []
  eventOut     SFVec3f value_changed
] { }
#endif

 beginProtoInterface("PositionInterpolator");
 {
     addProtoEventIn       ("SFFloat", "set_fraction");
     
     beginProtoExposedField("MFFloat", OSGmfFloat, "key");
     endProtoExposedField();

     beginProtoExposedField("MFVec3f", OSGmfVec3f, "keyValue");
     endProtoExposedField  ();

     addProtoEventOut      ("SFVec3f", "value_changed");
 }
 endProtoInterface  ();

#if 0
PROTO ProximitySensor [
  exposedField SFVec3f    center      0 0 0
  exposedField SFVec3f    size        0 0 0
  exposedField SFBool     enabled     TRUE
  eventOut     SFBool     isActive
  eventOut     SFVec3f    position_changed
  eventOut     SFRotation orientation_changed
  eventOut     SFTime     enterTime
  eventOut     SFTime     exitTime
] { }
#endif

 beginProtoInterface("ProximitySensor");
 {
     beginProtoExposedField("SFVec3f", OSGsfVec3f, "center");
     addFieldValue         ("0 0 0");
     endProtoExposedField  ();

     beginProtoExposedField("SFVec3f", OSGsfVec3f, "size");
     addFieldValue         ("0 0 0");
     endProtoExposedField  ();

     beginProtoExposedField("SFBool", OSGsfBool, "enabled");
     addFieldValue         ("TRUE");
     endProtoExposedField  ();

     addProtoEventOut      ("SFBool", "isActive");
     addProtoEventOut      ("SFVec3f", "position_changed");
     addProtoEventOut      ("SFRotation", "orientation_changed");
     addProtoEventOut      ("SFTime", "enterTime");
     addProtoEventOut      ("SFTime", "exitTime");
 }
 endProtoInterface  ();

#if 0
PROTO ScalarInterpolator [
  eventIn      SFFloat set_fraction
  exposedField MFFloat key       []
  exposedField MFFloat keyValue  []
  eventOut     SFFloat value_changed
] { }
#endif

 beginProtoInterface("ScalarInterpolator");
 {
     addProtoEventIn       ("SFFloat", "set_fraction");

     beginProtoExposedField("MFFloat", OSGmfFloat, "key");
     endProtoExposedField  ();

     beginProtoExposedField("MFFloat", OSGmfFloat, "keyValue");
     endProtoExposedField  ();
     
     addProtoEventOut      ("SFFloat", "value_changed");
 }
 endProtoInterface  ();

#if 0
PROTO Script [
  exposedField MFString url           [ ] 
  field        SFBool   directOutput  FALSE
  field        SFBool   mustEvaluate  FALSE
] { }
#endif

 beginProtoInterface("Script");
 {
     beginProtoExposedField("MFString", OSGmfString, "url");
     endProtoExposedField  ();

     beginProtoField       ("SFBool", OSGsfBool, "directOutput");
     addFieldValue         ("FALSE");
     endProtoField         ();

     beginProtoField       ("SFBool", OSGsfBool, "mustEvaluate");
     addFieldValue         ("FALSE");
     endProtoField         ();
 }
 endProtoInterface  ();

#if 0
PROTO Shape [
  field SFNode appearance NULL
  field SFNode geometry   NULL
] { }
#endif

 beginProtoInterface("Shape");
 {
     beginProtoField("SFNode", OSGsfNode, "appearance");
//     addFieldValue  ("NULL");
     endProtoField  ();

     beginProtoField("SFNode", OSGsfNode, "geometry");
//     addFieldValue  ("NULL");
     endProtoField  ();
 }
 endProtoInterface  ();

#if 0
PROTO Sound [
  exposedField SFVec3f  direction     0 0 1
  exposedField SFFloat  intensity     1
  exposedField SFVec3f  location      0 0 0
  exposedField SFFloat  maxBack       10
  exposedField SFFloat  maxFront      10
  exposedField SFFloat  minBack       1
  exposedField SFFloat  minFront      1
  exposedField SFFloat  priority      0
  exposedField SFNode   source        NULL
  field        SFBool   spatialize    TRUE
] { }
#endif

 beginProtoInterface("Sound");
 {
     beginProtoExposedField("SFVec3f", OSGsfVec3f, "direction");
     addFieldValue         ("0 0 1");
     endProtoExposedField  ();

     beginProtoExposedField("SFFloat", OSGsfFloat, "intensity");
     addFieldValue         ("1");
     endProtoExposedField  ();

     beginProtoExposedField("SFVec3f", OSGsfVec3f, "location");
     addFieldValue         ("0 0 0");
     endProtoExposedField  ();

     beginProtoExposedField("SFFloat", OSGsfFloat, "maxBack");
     addFieldValue         ("10");
     endProtoExposedField  ();

     beginProtoExposedField("SFFloat", OSGsfFloat, "maxFront");
     addFieldValue         ("10");
     endProtoExposedField  ();

     beginProtoExposedField("SFFloat", OSGsfFloat, "minBack");
     addFieldValue         ("1");
     endProtoExposedField  ();

     beginProtoExposedField("SFFloat", OSGsfFloat, "minFront");
     addFieldValue         ("1");
     endProtoExposedField  ();

     beginProtoExposedField("SFFloat", OSGsfFloat, "priority");
     addFieldValue         ("0");
     endProtoExposedField  ();
     
     beginProtoExposedField("SFNode", OSGsfNode, "source");
//     addFieldValue         ("NULL");
     endProtoExposedField  ();
     
     beginProtoField       ("SFBool", OSGsfBool, "spatialize");
     addFieldValue         ("TRUE");
     endProtoField         ();
 }
 endProtoInterface  ();

#if 0
PROTO Sphere [
  field SFFloat radius  1
] { }
#endif

 beginProtoInterface("Sphere");
 {
     beginProtoField("SFFloat", OSGsfFloat, "radius");
     addFieldValue  ("1");
     endProtoField  ();
 }
 endProtoInterface  ();

#if 0
PROTO SphereSensor [
  exposedField SFBool     autoOffset TRUE
  exposedField SFBool     enabled    TRUE
  exposedField SFRotation offset     0 1 0 0
  eventOut     SFBool     isActive
  eventOut     SFRotation rotation_changed
  eventOut     SFVec3f    trackPoint_changed
] { }
#endif

 beginProtoInterface("SphereSensor");
 {
     beginProtoExposedField("SFBool", OSGsfBool, "autoOffset");
     addFieldValue         ("TRUE");
     endProtoExposedField  ();

     beginProtoExposedField("SFBool", OSGsfBool, "enabled");
     addFieldValue         ("TRUE");
     endProtoExposedField  ();

     beginProtoExposedField("SFRotation", OSGsfRotation, "offset");
     addFieldValue         ("0 1 0 0");
     endProtoExposedField  ();

     addProtoEventOut      ("SFBool", "isActive");
     addProtoEventOut      ("SFRotation", "rotation_changed");
     addProtoEventOut      ("SFVec3f", "trackPoint_changed");
 }
 endProtoInterface  ();

#if 0
PROTO SpotLight [
  exposedField SFFloat ambientIntensity  0 
  exposedField SFVec3f attenuation       1 0 0
  exposedField SFFloat beamWidth         1.570796
  exposedField SFColor color             1 1 1 
  exposedField SFFloat cutOffAngle       0.785398 
  exposedField SFVec3f direction         0 0 -1
  exposedField SFFloat intensity         1  
  exposedField SFVec3f location          0 0 0  
  exposedField SFBool  on                TRUE
  exposedField SFFloat radius            100
] { }
#endif

 beginProtoInterface("SpotLight");
 {
     beginProtoExposedField("SFFloat", OSGsfFloat, "ambientIntensity");
     addFieldValue         ("0"); 
     endProtoExposedField  ();

     beginProtoExposedField("SFVec3f", OSGsfVec3f, "attenuation");
     addFieldValue         ("1 0 0");
     endProtoExposedField  ();

     beginProtoExposedField("SFFloat", OSGsfFloat, "beamWidth");
     addFieldValue         ("1.570796");
     endProtoExposedField  ();

     beginProtoExposedField("SFColor", OSGsfColor, "color");
     addFieldValue         ("1 1 1");
     endProtoExposedField  ();

     beginProtoExposedField("SFFloat", OSGsfFloat, "cutOffAngle");
     addFieldValue         ("0.785398");
     endProtoExposedField  ();

     beginProtoExposedField("SFVec3f", OSGsfVec3f, "direction");
     addFieldValue         ("0 0 -1");
     endProtoExposedField  ();

     beginProtoExposedField("SFFloat", OSGsfFloat, "intensity");
     addFieldValue         ("1");
     endProtoExposedField  ();

     beginProtoExposedField("SFVec3f", OSGsfVec3f, "location");
     addFieldValue         ("0 0 0");
     endProtoExposedField  ();

     beginProtoExposedField("SFBool", OSGsfBool, "on");
     addFieldValue         ("TRUE");
     endProtoExposedField  ();

     beginProtoExposedField("SFFloat", OSGsfFloat, "radius");
     addFieldValue         ("100");
     endProtoExposedField  ();
 }
 endProtoInterface  ();

#if 0
PROTO Switch [
  exposedField    MFNode  choice      []
  exposedField    SFInt32 whichChoice -1
] { }
#endif

 beginProtoInterface("Switch");
 {
     beginProtoExposedField("MFNode", OSGmfNode, "choice");
     endProtoExposedField  ();

     beginProtoExposedField("SFInt32", OSGsfInt32, "whichChoice");
     addFieldValue         ("-1");
     endProtoExposedField  ();
 }
 endProtoInterface  ();

#if 0
PROTO Text [
  exposedField  MFString string    []
  field         SFNode   fontStyle NULL
  field         MFFloat  length    []
  field         SFFloat  maxExtent 0.0
] { }
#endif

 beginProtoInterface("Text");
 {
     beginProtoExposedField("MFString", OSGmfString, "string");
     endProtoExposedField  ();

     beginProtoField       ("SFNode", OSGsfNode, "fontStyle");
     addFieldValue         ("NULL");
     endProtoField         ();

     beginProtoField       ("MFFloat", OSGmfFloat, "length");
     endProtoField         ();

     beginProtoField       ("SFFloat", OSGsfFloat, "maxExtent");
     addFieldValue         ("0.0");
     endProtoField         ();
 }
 endProtoInterface  ();

#if 0
PROTO TextureCoordinate [
  exposedField MFVec2f point []
] { }
#endif

 beginProtoInterface("TextureCoordinate");
 {
     beginProtoExposedField("MFVec2f", OSGmfVec2f, "point");
     endProtoExposedField  ();
 }
 endProtoInterface  ();

#if 0
PROTO TextureTransform [
  exposedField SFVec2f center      0 0
  exposedField SFFloat rotation    0
  exposedField SFVec2f scale       1 1
  exposedField SFVec2f translation 0 0
] { }
#endif

 beginProtoInterface("TextureTransform");
 {
     beginProtoExposedField("SFVec2f", OSGsfVec2f, "center");
     addFieldValue         ("0 0");
     endProtoExposedField  ();
     
     beginProtoExposedField("SFFloat", OSGsfFloat, "rotation");
     addFieldValue         ("0");
     endProtoExposedField  ();

     beginProtoExposedField("SFVec2f", OSGsfVec2f, "scale");
     addFieldValue         ("1 1");
     endProtoExposedField  ();

     beginProtoExposedField("SFVec2f", OSGsfVec2f, "translation");
     addFieldValue         ("0 0");
     endProtoExposedField  ();
 }
 endProtoInterface  ();

#if 0
PROTO TimeSensor [
  exposedField SFTime   cycleInterval 1
  exposedField SFBool   enabled       TRUE
  exposedField SFBool   loop          FALSE
  exposedField SFTime   startTime     0
  exposedField SFTime   stopTime      0
  eventOut     SFTime   cycleTime
  eventOut     SFFloat  fraction_changed
  eventOut     SFBool   isActive
  eventOut     SFTime   time
] { }
#endif

 beginProtoInterface("TimeSensor");
 {
     beginProtoExposedField("SFTime", OSGsfTime, "cycleInterval");
     addFieldValue         ("1");
     endProtoExposedField  ();

     beginProtoExposedField("SFBool", OSGsfBool, "enabled");
     addFieldValue         ("TRUE");
     endProtoExposedField  ();

     beginProtoExposedField("SFBool", OSGsfBool, "loop");
     addFieldValue         ("FALSE");
     endProtoExposedField  ();

     beginProtoExposedField("SFTime", OSGsfTime, "startTime");
     addFieldValue         ("0");
     endProtoExposedField  ();

     beginProtoExposedField("SFTime", OSGsfTime, "stopTime");
     addFieldValue         ("0");
     endProtoExposedField  ();

     addProtoEventOut      ("SFTime", "cycleTime");
     addProtoEventOut      ("SFFloat", "fraction_changed");
     addProtoEventOut      ("SFBool", "isActive");
     addProtoEventOut      ("SFTime", "time");
 }
 endProtoInterface  ();
 
#if 0
PROTO TouchSensor [
  exposedField SFBool  enabled TRUE
  eventOut     SFVec3f hitNormal_changed
  eventOut     SFVec3f hitPoint_changed
  eventOut     SFVec2f hitTexCoord_changed
  eventOut     SFBool  isActive
  eventOut     SFBool  isOver
  eventOut     SFTime  touchTime
] { }
#endif

 beginProtoInterface("TouchSensor");
 {
     beginProtoExposedField("SFBool", OSGsfBool, "enabled");
     addFieldValue         ("TRUE");
     endProtoExposedField  ();

     addProtoEventOut      ("SFVec3f", "hitNormal_changed");
     addProtoEventOut      ("SFVec3f", "hitPoint_changed");
     addProtoEventOut      ("SFVec2f", "hitTexCoord_changed");
     addProtoEventOut      ("SFBool", "isActive");
     addProtoEventOut      ("SFBool", "isOver");
     addProtoEventOut      ("SFTime", "touchTime");
 }
 endProtoInterface  ();

#if 0
PROTO Transform [
  eventIn      MFNode      addChildren
  eventIn      MFNode      removeChildren
  exposedField SFVec3f     center           0 0 0
  exposedField MFNode      children         []
  exposedField SFRotation  rotation         0 0 1  0
  exposedField SFVec3f     scale            1 1 1
  exposedField SFRotation  scaleOrientation 0 0 1  0
  exposedField SFVec3f     translation      0 0 0
  field        SFVec3f     bboxCenter       0 0 0
  field        SFVec3f     bboxSize         -1 -1 -1
] { }
#endif

 beginProtoInterface("Transform");
 {
     addProtoEventIn       ("MFNode", "addChildren");
     addProtoEventIn       ("MFNode", "removeChildren");
     
     beginProtoExposedField("SFVec3f", OSGsfVec3f, "center");
     addFieldValue         ("0 0 0");
     endProtoExposedField  ();

     beginProtoExposedField("MFNode", OSGmfNode, "children");
     endProtoExposedField  ();

     beginProtoExposedField("SFRotation", OSGsfRotation, "rotation");
     addFieldValue         ("0 0 1  0");
     endProtoExposedField  ();

     beginProtoExposedField("SFVec3f", OSGsfVec3f, "scale");
     addFieldValue         ("1 1 1");
     endProtoExposedField  ();

     beginProtoExposedField("SFRotation", OSGsfRotation, "scaleOrientation");
     addFieldValue         ("0 0 1  0");
     endProtoExposedField  ();

     beginProtoExposedField("SFVec3f", OSGsfVec3f, "translation");
     addFieldValue         ("0 0 0");
     endProtoExposedField  ();

     beginProtoField       ("SFVec3f", OSGsfVec3f, "bboxCenter");
     addFieldValue         ("0 0 0");
     endProtoField         ();

     beginProtoField       ("SFVec3f", OSGsfVec3f, "bboxSize");
     addFieldValue         ("-1 -1 -1");
     endProtoField         ();
 }
 endProtoInterface  ();

#if 0
PROTO Viewpoint [
  eventIn      SFBool     set_bind
  exposedField SFFloat    fieldOfView    0.785398
  exposedField SFBool     jump           TRUE
  exposedField SFRotation orientation    0 0 1  0
  exposedField SFVec3f    position       0 0 10
  field        SFString   description    ""
  eventOut     SFTime     bindTime
  eventOut     SFBool     isBound
] { }
#endif

 beginProtoInterface("Viewpoint");
 {
     addProtoEventIn       ("SFBool", "set_bind");
     
     beginProtoExposedField("SFFloat", OSGsfFloat, "fieldOfView");
     addFieldValue         ("0.785398");
     endProtoExposedField  ();

     beginProtoExposedField("SFBool", OSGsfBool, "jump");
     addFieldValue         ("TRUE");
     endProtoExposedField  ();

     beginProtoExposedField("SFRotation", OSGsfRotation, "orientation");
     addFieldValue         ("0 0 1  0");
     endProtoExposedField  ();

     beginProtoExposedField("SFVec3f", OSGsfVec3f, "position");
     addFieldValue         ("0 0 10");
     endProtoExposedField  ();

     beginProtoField       ("SFString", OSGsfString, "description");
     addFieldValue         ("");
     endProtoField         ();

     addProtoEventOut      ("SFTime", "bindTime");
     addProtoEventOut      ("SFBool", "isBound" );
 }
 endProtoInterface  ();

#if 0
PROTO VisibilitySensor [
  exposedField SFVec3f center   0 0 0
  exposedField SFBool  enabled  TRUE
  exposedField SFVec3f size     0 0 0
  eventOut     SFTime  enterTime
  eventOut     SFTime  exitTime
  eventOut     SFBool  isActive
] { }
#endif

 beginProtoInterface("VisibilitySensor");
 {
     beginProtoExposedField("SFVec3f", OSGsfVec3f, "center");
     addFieldValue         ("0 0 0");
     endProtoExposedField  ();

     beginProtoExposedField("SFBool", OSGsfBool, "enabled");
     addFieldValue         ("TRUE");
     endProtoExposedField  ();

     beginProtoExposedField("SFVec3f", OSGsfVec3f, "size");
     addFieldValue         ("0 0 0");
     endProtoExposedField  ();

     addProtoEventOut      ("SFTime", "enterTime");
     addProtoEventOut      ("SFTime", "exitTime" );
     addProtoEventOut      ("SFBool", "isActive" );
 }
 endProtoInterface  ();

#if 0
PROTO WorldInfo [
  field MFString info  []
  field SFString title ""
] { }
#endif

 beginProtoInterface("WorldInfo");
 {
     beginProtoField("MFString", OSGmfString, "info");
     endProtoField  ();
     
     beginProtoField("SFString", OSGsfString, "title");
     addFieldValue("");
     endProtoField();
 }
 endProtoInterface  ();

 postStandardProtos();
}

NodePtr VRMLFile::getRoot(void)
{
    return _pRootNode;
}

NodePtr VRMLFile::cloneTree(NodePtr pRootNode)
{
    NodePtr returnValue = NullFC;

    if(pRootNode != NullFC)
    {
        NodePtr pChildClone = NullFC;

        returnValue = Node::create();

        beginEditCP(returnValue);
        returnValue->setCore(pRootNode->getCore());

        for(UInt32 i = 0; i < pRootNode->getNChildren(); i++)
        {
            pChildClone = cloneTree(pRootNode->getChild(i));
            
            returnValue->addChild(pChildClone);
        }
        endEditCP(returnValue);
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

