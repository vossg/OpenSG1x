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
#include <OSGNode.h>
#include <OSGGroup.h>

#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGPerspectiveCamera.h"
#include "OSGBackground.h"

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char OSGLoader::cvsid[] = "@(#)$Id: $";

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

/*
    setIntExtMapping(ScanParseSkel::OSGsfImage   , 
               ::getClassType().getId());
*/

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

    setIntExtMapping(SFAttachmentMap::getClassType().getId(),
                     ScanParseSkel::OSGmfNode);

    setIntExtMapping(SFWindowPtr::getClassType().getId(),
                     ScanParseSkel::OSGsfNode);
    setIntExtMapping(MFWindowPtr::getClassType().getId(),
                     ScanParseSkel::OSGmfNode);

    setIntExtMapping(SFViewportPtr::getClassType().getId(),
                     ScanParseSkel::OSGsfNode);
    setIntExtMapping(MFViewportPtr::getClassType().getId(),
                     ScanParseSkel::OSGmfNode);

    setIntExtMapping(SFCameraPtr::getClassType().getId(),
                     ScanParseSkel::OSGsfNode);
    setIntExtMapping(MFCameraPtr::getClassType().getId(),
                     ScanParseSkel::OSGmfNode);
    
    setIntExtMapping(SFPerspectiveCameraPtr::getClassType().getId(),
                     ScanParseSkel::OSGsfNode);
    setIntExtMapping(MFPerspectiveCameraPtr::getClassType().getId(),
                     ScanParseSkel::OSGmfNode);
    
    setIntExtMapping(SFBackgroundPtr::getClassType().getId(),
                     ScanParseSkel::OSGsfNode);
    setIntExtMapping(MFBackgroundPtr::getClassType().getId(),
                     ScanParseSkel::OSGmfNode);
    
    /* extended types */
    
    setIntExtMapping(SFMatrix::getClassType().getId(),
                     ScanParseSkel::OSGsfMatrix);
    
    setIntExtMapping(SFPnt3f::getClassType().getId(),
                     ScanParseSkel::OSGsfPnt3f);
    
    setIntExtMapping(MFPnt3f::getClassType().getId(),
                     ScanParseSkel::OSGmfPnt3f);
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
    nodename = dcast<NamePtr>(
        np->findAttachment(Name::getClassType().getGroupId()));

    if(nodename != NullFC)
    {
        if(strcmp(szName,nodename->getFieldPtr()->getValue().str())==0)
            return np;
    }
    // check if name matches corename
    cp=np->getCore();
    if(cp != NullFC)
    {
        nodename = dcast<NamePtr>(
            cp->findAttachment(Name::getClassType().getGroupId()));

        if(nodename != NullFC)
        {
            if(strcmp(szName,nodename->getFieldPtr()->getValue().str())==0)
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
            NodePtr     pNode = dcast<NodePtr>(_pCurrentFC);
            NodeCorePtr pCore = dcast<NodeCorePtr>(pNewNode);
            
            pNode->setCore(pCore);
        }
        else if(_pCurrentField == _pCurrentFC->getField("children"))
        {
            NodePtr pNode      = dcast<NodePtr>(_pCurrentFC);
            NodePtr pChildNode;
            if(pNewNode->getType().isNode())
            {
                pChildNode=dcast<NodePtr>(pNewNode);
            }
            else if(pNewNode->getType().isNodeCore())
            {
                pChildNode=Node::create();
                pChildNode->setCore(dcast<NodeCorePtr>(pNewNode));
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
                    NodePtr       pNode = dcast<NodePtr      >(_pCurrentFC);
                    AttachmentPtr pAtt  = dcast<AttachmentPtr>(pNewNode);

                    pNode->addAttachment(pAtt);
                }
                else if(_pCurrentFC->getType().isNodeCore() == true)
                {
                    NodeCorePtr   pNodeCore = dcast<NodeCorePtr> (_pCurrentFC);
                    AttachmentPtr pAtt      = dcast<AttachmentPtr>(pNewNode);

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
    _pRootNode    (NullNode),
    _pCurrentField(NULL),
    _fcStack      (),
    _fStack       (),
    _fdStack      ()
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

void OSGLoader::beginNode(const Char8 *szNodeTypename,
                          const Char8 *szNodename)
{
    FieldContainerPtr pNewNode;

    if(szNodeTypename == NULL)
        return;

    PLOG << "Begin node : " << szNodeTypename << " | ";

    if(szNodename == NULL)
    {
        PLOG << "NULL";
    }
    else
    {
        PLOG << szNodename;
    }
        
    PLOG << endl;
    
    pNewNode = 
        FieldContainerFactory::the()->createFieldContainer(szNodeTypename);

    if(szNodename != NULL && pNewNode != NullFC)
    {
        if(pNewNode->getType().isNode() == true)
        {
            NodePtr pNode     = dcast<NodePtr>(pNewNode);
            NamePtr pNodename = Name::create();

            pNodename->getFieldPtr()->getValue().set(szNodename);
  
            pNode->addAttachment(pNodename);
        }
        else if(pNewNode->getType().isNodeCore() == true)
        {
            NodeCorePtr pNodeCore = dcast<NodeCorePtr>(pNewNode);
            NamePtr     pNodename = Name::create();

            pNodename->getFieldPtr()->getValue().set(szNodename);
  
            pNodeCore->addAttachment(pNodename);           
        }
        else
        {
            SLOG << "Fieldcontainer " << szNodeTypename 
                 << "is neither Node nor NodeCore " << endl;
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
            pNode = dcast<NodePtr>(_pCurrentFC);
        }
        else if(_pCurrentFC->getType().isNodeCore())
        {
            pNode = Node::create();
            pNode->setCore(dcast<NodeCorePtr>(_pCurrentFC));
        }
        else
        {
            SLOG << "Fieldcontainer " << szNodeTypename 
                 << "is neither Node nor NodeCore " << endl;
        }

        if(_pRootNode == NullNode)
        {
            GroupPtr pGroup = Group::create();

            _pRootNode = Node::create();
            _pRootNode->setCore(pGroup);
        }

        _pRootNode->addChild(pNode);
    }
}
    
void OSGLoader::endNode(void)
{
    fprintf(stderr, "End Node\n");

    if(_pCurrentFC != NullFC)
    {
        if(_pCurrentFC->getType().isNode() == true)        
        {
            NodePtr pNode = dcast<NodePtr>(_pCurrentFC);
            
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

NodePtr OSGLoader::getRoot(void)
{
    return _pRootNode;
}

void OSGLoader::addFieldValue(const Char8 *szFieldVal)
{
    PLOG << "\t\tFV : " << szFieldVal << endl;

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

        fprintf(stderr, "GF : %s %p\n", szFieldname, pField);

        if(pField != NULL)
        {
            returnValue = pField->getType().getId();
        }    
    }

    return returnValue;
}

void OSGLoader::beginField(const Char8 *szFieldname,
                           const UInt32 uiFieldTypeId)
{
    fprintf(stderr, "BeginField : %s %p\n", szFieldname, _pCurrentField);

    if(szFieldname == NULL)
        return;

    _pCurrentField = NULL;

    if(_pCurrentFC != NullFC)
    {
        _pCurrentField     = _pCurrentFC->getField(szFieldname);

        _pCurrentFieldDesc = 
            _pCurrentFC->getType().findFieldDescription(szFieldname);

        fprintf(stderr, "BF : %s %p %p\n", 
                szFieldname, _pCurrentField, _pCurrentFieldDesc);

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
    fprintf(stderr, "End Field\n");

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
    return findFCByName(szName,getRoot());
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

