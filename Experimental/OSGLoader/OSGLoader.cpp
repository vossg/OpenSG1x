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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include "OSGLoader.h"
#include <OSGLog.h>


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

#include <OSGFieldContainerFactory.h>
#include <OSGFieldContainer.h>

#include <OSGGeoProperty.h>
#include <OSGMaterialFields.h>
#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGImagePFields.h>

#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGPerspectiveCamera.h"
#include "OSGBackground.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGLOADER_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
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

void OSGLoader::initFieldTypeMapper(void)
{
    setIntExtMapping(SFBool::getClassType().getId(),
                     ScanParseSkel::OSGsfBool);

/*
    setIntExtMapping(ScanParseSkel::OSGsfColor, 
               ::getClassType().getId());
*/

    setIntExtMapping(SFReal32::getClassType().getId(),
                     ScanParseSkel::OSGsfFloat);

    setIntExtMapping(SFImageP::getClassType().getId(),
                     ScanParseSkel::OSGsfString);

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

    setIntExtMapping(SFVec4f::getClassType().getId(),
                     ScanParseSkel::OSGsfVec4f);

    setIntExtMapping(SFColor4f::getClassType().getId(),
                     ScanParseSkel::OSGsfColor4f);
    
    setIntExtMapping(SFColor3f::getClassType().getId(),
                     ScanParseSkel::OSGsfColor3f);

/*
    setIntExtMapping(ScanParseSkel::OSGmfColor, 
               ::getClassType().getId());
*/

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


    setIntExtMapping(MFVec2f::getClassType().getId(),
                     ScanParseSkel::OSGmfVec2f);

    setIntExtMapping(MFVec3f::getClassType().getId(),
                     ScanParseSkel::OSGmfVec3f);

    setIntExtMapping(MFVec4f::getClassType().getId(),
                     ScanParseSkel::OSGmfVec4f);

    setIntExtMapping(MFColor4f::getClassType().getId(),
                     ScanParseSkel::OSGmfColor4f);
    
    setIntExtMapping(MFColor3f::getClassType().getId(),
                     ScanParseSkel::OSGmfColor3f);

    setIntExtMapping(SFNodePtr::getClassType().getId(),
                     ScanParseSkel::OSGsfNode);
    setIntExtMapping(MFNodePtr::getClassType().getId(),
                     ScanParseSkel::OSGmfNode);


    /* To Base Type Mappings */

    setIntExtMapping(SFUInt8::getClassType().getId(),
                     ScanParseSkel::OSGsfInt32);
    setIntExtMapping(MFUInt8::getClassType().getId(),
                     ScanParseSkel::OSGmfInt32);
    
    setIntExtMapping(SFUInt16::getClassType().getId(),
                     ScanParseSkel::OSGsfInt32);
    setIntExtMapping(MFUInt16::getClassType().getId(),
                     ScanParseSkel::OSGmfInt32);

    setIntExtMapping(SFUInt32::getClassType().getId(),
                     ScanParseSkel::OSGsfInt32);
    setIntExtMapping(MFUInt32::getClassType().getId(),
                     ScanParseSkel::OSGmfInt32);


    /* To Node Mappings */

    setIntExtMapping(SFAttachmentMap::getClassType().getId(),
                     ScanParseSkel::OSGmfNode);

    /* extended types */
    
    setIntExtMapping(SFMatrix::getClassType().getId(),
                     ScanParseSkel::OSGsfMatrix);
    
    setIntExtMapping(SFPnt3f::getClassType().getId(),
                     ScanParseSkel::OSGsfPnt3f);
    
    setIntExtMapping(MFPnt3f::getClassType().getId(),
                     ScanParseSkel::OSGmfPnt3f);
    setIntExtMapping(SFDynamicVolume::getClassType().getId(),
                     ScanParseSkel::OSGmfFloat);
    
    setIntExtMapping(SFPlane::getClassType().getId(),
                     ScanParseSkel::OSGsfPlane);
    setIntExtMapping(MFPlane::getClassType().getId(),
                     ScanParseSkel::OSGmfPlane);

    setIntExtMapping(SFDynamicVolume::getClassType().getId(),
                     ScanParseSkel::OSGsfVolume);
}

/* remove this, if there is a general methode to find containers */
FieldContainerPtr OSGLoader::findFCByName(const Char8 *szName,
                                                 NodePtr np)
{
    MFNodePtr::iterator i;
    NamePtr nodename;
    NodeCorePtr cp;
    FieldContainerPtr fcp;

    // check if name matches nodename
    nodename = NamePtr::dcast(
        np->findAttachment(Name::getClassType().getGroupId()));

    if(nodename != NullFC)
    {
        if(strcmp(szName,nodename->getFieldPtr()->getValue().c_str())==0)
            return np;
    }
    // check if name matches corename
    cp=np->getCore();
    if(cp != NullFC)
    {
        nodename = NamePtr::dcast(
            cp->findAttachment(Name::getClassType().getGroupId()));

        if(nodename != NullFC)
        {
            if(strcmp(szName,nodename->getFieldPtr()->getValue().c_str())==0)
                return cp;
        }
    }
    // matching for children
    for(i =np->getMFChildren()->begin();
        i!=np->getMFChildren()->end();
        i++)
    {
        fcp=findFCByName(szName,*i);
        if(fcp != NullFC)
        {
            return fcp;
        }
    }
    return fcp;
}

void OSGLoader::setFieldContainerValue(FieldContainerPtr pNewNode)
{
    /* Hack attack, the {S|M}FieldContainerPtr * cast is a hack until the 
       type system is fixed to get it right */
    if(_pCurrentField != NULL && _pCurrentFC != NullFC && pNewNode != NullFC)
    {
        if(_pCurrentField == _pCurrentFC->getField("core"))
        {
            NodePtr     pNode = NodePtr    ::dcast(_pCurrentFC);
            NodeCorePtr pCore = NodeCorePtr::dcast( pNewNode);
            
            pNode->setCore(pCore);
        }
        else if(_pCurrentField == _pCurrentFC->getField("children"))
        {
            NodePtr pNode      = NodePtr::dcast(_pCurrentFC);
            NodePtr pChildNode;
            if(pNewNode->getType().isNode())
            {
                pChildNode=NodePtr::dcast(pNewNode);
            }
            else if(pNewNode->getType().isNodeCore())
            {
                pChildNode=Node::create();
                pChildNode->setCore(NodeCorePtr::dcast(pNewNode));
            }
            else
            {
                SLOG << "Fieldcontainer " << pNewNode->getType().getName()
                     << "is neither Node nor NodeCore " << endl;
            }
            pNode->addChild(pChildNode);
        }
        else if(_pCurrentField == _pCurrentFC->getField("attachments"))
        {
            if(pNewNode->getType().isAttachment() == true)
            {
                if(_pCurrentFC->getType().isNode() == true)
                {
                    NodePtr       pNode = NodePtr      ::dcast(_pCurrentFC);
                    AttachmentPtr pAtt  = AttachmentPtr::dcast(pNewNode);

                    pNode->addAttachment(pAtt);
                }
                else if(_pCurrentFC->getType().isNodeCore() == true)
                {
                    NodeCorePtr   pNodeCore = NodeCorePtr ::dcast(_pCurrentFC);
                    AttachmentPtr pAtt      = AttachmentPtr::dcast(pNewNode);

                    pNodeCore->addAttachment(pAtt); 
                }
            }
            else
            {
                SLOG << "FieldContainer : " << _pCurrentFC->getType().getName()
                     << " is no attachment" << endl;
            }
        }
        else if(_pCurrentField->getCardinality() == FieldType::SINGLE_FIELD)
        {
            ((SFFieldContainerPtr *) _pCurrentField)->setValue(pNewNode);
        }
        else if(_pCurrentField->getCardinality() == FieldType::MULTI_FIELD)
        {
            ((MFFieldContainerPtr *) _pCurrentField)->push_back(pNewNode);
        }
    }
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

OSGLoader::OSGLoader(void) :
    Inherited(),
    _pCurrentFC   (NullFC),
    _pRootNode    (NullFC),
    _pCurrentField(NULL),
    _fcStack      (),
    _fStack       (),
    _fdStack      (),
    _pathHandler  ()
{
    setReferenceHeader("#OSG V1.0 ");
    initFieldTypeMapper();
}

/** \brief Destructor
 */

OSGLoader::~OSGLoader(void)
{
}

/*------------------------------ access -----------------------------------*/

void OSGLoader::scanFile(const Char8  *szFilename,
                               UInt32  uiOptions)
{
    if( szFilename != NULL )
    {
        PathHandler *oldPathHandler = ImageFileHandler::the().getPathHandler();
       
        _pathHandler.clearPathList();
        _pathHandler.clearBaseFile();
        _pathHandler.push_frontCurrentDir();
        _pathHandler.setBaseFile(szFilename);
        
        ImageFileHandler::the().setPathHandler(&_pathHandler);
        
        Inherited::scanFile(szFilename, uiOptions);
        
        ImageFileHandler::the().setPathHandler(oldPathHandler);
    }
}


void OSGLoader::scanFile(const Char8   *szFilename, 
                               UInt32  uiAddOptions, 
                               UInt32  uiSubOptions)
{
    if( szFilename != NULL )
    {
        PathHandler *oldPathHandler = ImageFileHandler::the().getPathHandler();
       
        _pathHandler.clearPathList();
        _pathHandler.clearBaseFile();
        _pathHandler.push_frontCurrentDir();
        _pathHandler.setBaseFile(szFilename);
        
        ImageFileHandler::the().setPathHandler(&_pathHandler);
        
        Inherited::scanFile(szFilename, uiAddOptions, uiSubOptions);
        
        ImageFileHandler::the().setPathHandler(oldPathHandler);
    }
}
    
#if defined(OSG_WIN32_ICL)
#pragma warning (disable : 383)
#endif

void OSGLoader::beginNode(const Char8 *szNodeTypename,
                          const Char8 *szNodename)
{
    FieldContainerPtr pNewNode;

    if(szNodeTypename == NULL)
        return;

    PINFO << "Begin node : " << szNodeTypename << " | ";

    if(szNodename == NULL)
    {
        PINFO << "NULL";
    }
    else
    {
        PINFO << szNodename;
    }
        
    PINFO << endl;
    
    pNewNode = 
        FieldContainerFactory::the()->createFieldContainer(szNodeTypename);

    if(szNodename != NULL && pNewNode != NullFC)
    {
        if(pNewNode->getType().isNode() == true)
        {
            NodePtr pNode     = NodePtr::dcast(pNewNode);
            NamePtr pNodename = Name::create();

            pNodename->getFieldPtr()->getValue().assign(szNodename);
  
            pNode->addAttachment(pNodename);
        }
        else if(pNewNode->getType().isNodeCore() == true)
        {
            NodeCorePtr pNodeCore = NodeCorePtr::dcast(pNewNode);
            NamePtr     pNodename = Name::create();

            pNodename->getFieldPtr()->getValue().assign(szNodename);
  
            pNodeCore->addAttachment(pNodename);           
        }
        else
        {
            SLOG << "Fieldcontainer " << szNodeTypename 
                 << " is neither Node nor NodeCore. "
                 << "Can not use attachment to store Nodename " << endl
                 << "Adding to _defMap instead. " << endl;

            if( _defMap.insert(
                make_pair(string(szNodename), pNewNode) ).second == true )
            {
                SLOG << "Success." << endl;
            }
        }
    }

    // assign nodepointer to current sf|mf field
    setFieldContainerValue(pNewNode);

    _pCurrentFC = pNewNode;

    _fcStack.push(_pCurrentFC);

    if(_fcStack.size() == 1)
    {
        NodePtr pNode;
        if(_pCurrentFC->getType().isNode())
        {
            pNode = NodePtr::dcast(_pCurrentFC);
        }
        else if(_pCurrentFC->getType().isNodeCore())
        {
            pNode = Node::create();
            pNode->setCore(NodeCorePtr::dcast(_pCurrentFC));
        }
        else
        {
            SLOG << "Fieldcontainer " << szNodeTypename 
                 << "is neither Node nor NodeCore " << endl;
        }

        if(_pRootNode == NullFC)
        {
            GroupPtr pGroup = Group::create();

            _pRootNode = Node::create();
            _pRootNode->setCore(pGroup);
        }

        _pRootNode->addChild(pNode);
    }
}

#if defined(OSG_WIN32_ICL)
#pragma warning (default : 383)
#endif
    
void OSGLoader::endNode(void)
{
    PINFO << "End Node" << endl;

    if(_pCurrentFC != NullFC)
    {
        if(_pCurrentFC->getType().isNode() == true)        
        {
            NodePtr pNode = NodePtr::dcast(_pCurrentFC);
            
            if(pNode->getCore() == NullFC)
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
}

void OSGLoader::use(const Char8 *szName)
{
    FieldContainerPtr pUseNode;

    // try to find a container with the given name attachment

    pUseNode = getReference(szName);

    if(pUseNode == NullFC)
    {
        SLOG << "No FieldContainer found with name " << szName << endl; 
    }
    else
    {
        // assign nodepointer to current sf|mf field
        setFieldContainerValue(pUseNode);
    }
}

NodePtr OSGLoader::getRootNode(void)
{
    return _pRootNode;
}

vector<FieldContainerPtr> OSGLoader::getRootNodes(void)
{
    vector<FieldContainerPtr> fcVec;

    for( UInt32 i=0; i<_pRootNode->getNChildren(); ++i )
    {
        fcVec.push_back( _pRootNode->getChild(i) );
    }
    return fcVec;
}

void OSGLoader::addFieldValue(const Char8 *szFieldVal)
{
    PINFO << "\t\tFV : " << szFieldVal << endl;

    if(_pCurrentField != NULL)
    {
        _pCurrentField->pushValueByStr(szFieldVal);
    }
}

UInt32 OSGLoader::getFieldType(const Char8 *szFieldname)
{
    UInt32  returnValue = 0;
    Field     *pField      = NULL;

    if(szFieldname == NULL)
        return returnValue;

    if(_pCurrentFC != NullFC)
    {
        pField = _pCurrentFC->getField(szFieldname);

        PINFO << "GF : " << szFieldname << " " << pField << endl;

        if(pField != NULL)
        {
            returnValue = pField->getType().getId();
        }    
    }

    return returnValue;
}

Int32 OSGLoader::mapExtIntFieldType(const Char8 *szFieldname,
                                    const Int32  iFieldTypeId)
{
    Int32 returnValue = Inherited::mapExtIntFieldType(szFieldname,
                                                      iFieldTypeId);

    if(returnValue < 0 && szFieldname != NULL && _pCurrentFC != NullFC)
    {
        Field *pField = _pCurrentFC->getField(szFieldname);

        if(pField != NULL)
        {
            const FieldType &oFieldType = pField->getType();
        
            /* Should be this way 

            if(oFieldType.getContentType().isDerivedFrom(
                FieldDataTraits<FieldContainerPtr>::getType()) == true)
            {
            }
            */

            PINFO << "FieldTypeId invalid, trying to fix. " << endl;
            PINFO << oFieldType.getContentType().getCName()
                  << " comparing with "
                  << FieldDataTraits<FieldContainerPtr>::getType().getCName()
                  << endl;
            
            
            if(strstr(oFieldType.getContentType().getCName(), 
                      "Ptr"                                 ) != NULL)
            {
                PINFO << "FieldContainerPtr or derived class, "
                      << "parsing as Node"
                      << endl;
                
                if(oFieldType.getCardinality() == FieldType::SINGLE_FIELD)
                {
                    returnValue = ScanParseSkel::OSGsfNode;
                }
                else
                {
                    returnValue = ScanParseSkel::OSGmfNode;
                }
            }
        }
    }

    return returnValue;
}

void OSGLoader::beginField(const Char8 *szFieldname,
                           const UInt32 )
{
    PINFO << "BeginField " << szFieldname << " " << _pCurrentField << endl;

    if(szFieldname == NULL)
        return;

    _pCurrentField = NULL;

    if(_pCurrentFC != NullFC)
    {
        _pCurrentField     = _pCurrentFC->getField(szFieldname);

        _pCurrentFieldDesc = 
            _pCurrentFC->getType().findFieldDescription(szFieldname);

        PINFO << "BF : "
              <<  szFieldname       << " " 
              << _pCurrentField     << " " 
              << _pCurrentFieldDesc << endl;

        if(_pCurrentFieldDesc != NULL)
        {
            beginEditCP(_pCurrentFC, _pCurrentFieldDesc->getFieldMask());
        }
    }

    _fStack.push (_pCurrentField);
    _fdStack.push(_pCurrentFieldDesc);
}

void OSGLoader::endField(void)
{
    PINFO << "End Field" << endl;

    _fStack.pop();

    if(_fStack.size() != 0)
    {
        _pCurrentField = _fStack.top(); 
    }
    else
    {
        _pCurrentField = NULL;
    }


    if(_pCurrentFC != NullFC && _pCurrentFieldDesc != NULL)
    {
        endEditCP(_pCurrentFC, _pCurrentFieldDesc->getFieldMask());
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
}

FieldContainerPtr OSGLoader::getReference(const Char8 *szName)
{
    // search reference in this file
    // search the _defMap first then the tree for name attachments
    NamedFCMap::iterator iter = _defMap.find(string(szName));
    if( iter != _defMap.end() )
    {
        return (*iter).second;
    }
    return findFCByName(szName, getRootNode());
}

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/




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

