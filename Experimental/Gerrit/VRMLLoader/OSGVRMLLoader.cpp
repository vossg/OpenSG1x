/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

#include "OSGVRMLLoader.h"
#include "OSGLog.h"
#include "OSGVRMLObjectType.h"
#include "OSGVRMLObjectFactory.h"
#include "OSGVRMLNode.h"
#include "OSGVRMLGroup.h"

#include "OSGSFSysTypes.h"
#include "OSGMFSysTypes.h"
#include "OSGSFBaseTypes.h"
#include "OSGMFBaseTypes.h"
#include "OSGSFVecTypes.h"
#include "OSGMFVecTypes.h"
#include "OSGSFMathTypes.h"
#include "OSGMFMathTypes.h"

#include "OSGDataElementDesc.h"
//#include "OSGVRMLRouteTask.h"

//#define DEBUG_WRL

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGVRMLLOADER_HEADER_CVSID;
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

UInt32  VRMLLoader::_uiIndent      = 0;
UInt32  VRMLLoader::_uiIndentIndex = 0;
UInt32  VRMLLoader::_uiMaxIndent   = 0;

Char8  *VRMLLoader::_szIndents     = "-\\|/";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

void VRMLLoader::incIndent(void)
{
    _uiIndent += 4;

    if(_uiMaxIndent < _uiIndent)
    {
        _uiMaxIndent = _uiIndent;
    }
}

void VRMLLoader::decIndent(void)
{
    if(_uiIndent < 4)
    {
        PWARNING << "Indent smaller 4 decremented" << endl;

        _uiIndent = 4;
    }

    _uiIndent -= 4;
}

void VRMLLoader::doIndent(ostream &outstream)
{
#ifdef DEBUG_WRL
    indentLog(_uiIndent, outstream);
#else
#if 0
    Log::indent(_uiIndent, outstream);

    for(UInt32 i = 0; i < _uiIndent; i++)
    {
        outstream << "-";
    }
#endif
    
    outstream << _szIndents[_uiIndentIndex] << "\r";
    
#if 0 
   for(UInt32 j = _uiIndent; j < _uiMaxIndent + 2; j++)
    {
        outstream << " ";
    }

    outstream << "\r";
#endif

    _uiIndentIndex = (++_uiIndentIndex) % 4;
#endif
}

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

void VRMLLoader::initFieldTypeMapper(void)
{
    setIntExtMapping(SFBool::getClassType().getId(),
                     ScanParseSkel::OSGsfBool);

    setIntExtMapping(SFColor3f::getClassType().getId(),
                     ScanParseSkel::OSGsfColor);

    setIntExtMapping(SFInt32::getClassType().getId(),
                     ScanParseSkel::OSGsfInt32);

    setIntExtMapping(SFPnt3f::getClassType().getId(),
                     ScanParseSkel::OSGsfVec3f);

    setIntExtMapping(SFQuaternion::getClassType().getId(),
                     ScanParseSkel::OSGsfRotation);

    setIntExtMapping(SFReal32::getClassType().getId(),
                     ScanParseSkel::OSGsfFloat);

    setIntExtMapping(SFReal64::getClassType().getId(),
                     ScanParseSkel::OSGsfTime);

    setIntExtMapping(SFString::getClassType().getId(),
                     ScanParseSkel::OSGsfString);

    setIntExtMapping(SFVec2f::getClassType().getId(),
                     ScanParseSkel::OSGsfVec2f);

    setIntExtMapping(SFVec3f::getClassType().getId(),
                     ScanParseSkel::OSGsfVec3f);

    setIntExtMapping(SFVRMLNode::getClassType().getId(),
                     ScanParseSkel::OSGsfNode);



    setIntExtMapping(MFColor3f::getClassType().getId(),
                     ScanParseSkel::OSGmfColor);

    setIntExtMapping(MFInt32::getClassType().getId(),
                     ScanParseSkel::OSGmfInt32);

    setIntExtMapping(MFPnt3f::getClassType().getId(),
                     ScanParseSkel::OSGmfVec3f);

    setIntExtMapping(MFQuaternion::getClassType().getId(),
                     ScanParseSkel::OSGmfRotation);

    setIntExtMapping(MFReal32::getClassType().getId(),
                     ScanParseSkel::OSGmfFloat);

    setIntExtMapping(MFString::getClassType().getId(),
                     ScanParseSkel::OSGmfString);

    setIntExtMapping(MFUInt32::getClassType().getId(),
                     ScanParseSkel::OSGsfImage);

    setIntExtMapping(MFVec2f::getClassType().getId(),
                     ScanParseSkel::OSGmfVec2f);

    setIntExtMapping(MFVec3f::getClassType().getId(),
                     ScanParseSkel::OSGmfVec3f);

    setIntExtMapping(MFVRMLNode::getClassType().getId(),
                     ScanParseSkel::OSGmfNode);
}

void VRMLLoader::setNodeValue(VRMLNode *pNewNode)
{
    if(pNewNode != NULL)
    {
        SFVRMLNode *pSField = dynamic_cast<SFVRMLNode *>(_pCurrentField);

        if(pSField != NULL)
        {
            pSField->setValue(pNewNode);
        }
        else
        {
            MFVRMLNode *pMField;

            pMField = dynamic_cast<MFVRMLNode *>(_pCurrentField);

            if(pMField != NULL)
            {
                pMField->addValue(pNewNode);
            }
        }
    }
}

void VRMLLoader::insertNamedNode(VRMLNode *pNode)
{
    if(pNode == NULL || pNode->getCName() == NULL)
        return;

    if(_pNameNodeMap == NULL)
    {
        _pNameNodeMap = new NameNodeMap;
    }

    NameNodeMap::iterator mapIt;
    IDStringLink          szNodeName(pNode->getCName());

    mapIt = _pNameNodeMap->find(szNodeName);

    if(mapIt == _pNameNodeMap->end())
    {
        (*_pNameNodeMap)[szNodeName] = pNode;
    }
    else
    {
        doIndent(PLOG);
        PLOG << "Error could not add node named " 
             << pNode->getCName() 
             << " a second time "
             << endl;
    }
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

VRMLLoader::VRMLLoader(void) :
	 Inherited        (),

    _vResultStore     (),
    _pFileTree        (NULL),
    _pCurrentNode     (NULL),

    _pCurrentField    (NULL),
    _pCurrentFieldDesc(NULL),

    _sNodeStack       (),
    _sFieldStack      (),
    _sElementDescStack(),

    _pNameNodeMap     (NULL)
{
    setReferenceHeader("#VRML V2.0");
    initFieldTypeMapper();
}

VRMLLoader::~VRMLLoader(void)
{
}

void VRMLLoader::beginNode(const Char8 *szNodeTypename,
                           const Char8 *szNodename)
{
    if(szNodeTypename == NULL)
        return;

#ifdef DEBUG_WRL
    doIndent(PLOG);
    PLOG << "Begin node : " << szNodeTypename << " | ";
    
    if(szNodename == NULL)
    {
        PLOG << "NULL" << endl;
    }
    else
    {
        PLOG << szNodename << endl;
    }

    doIndent(PLOG);
    PLOG << "{" << endl;
#else
    doIndent(PLOG);
#endif

    incIndent();


    VRMLNode *pNewNode = 
        VRMLObjectFactory::the()->createNode(szNodeTypename);

    setNodeValue(pNewNode);
    
    _pCurrentNode = pNewNode;

    _sNodeStack.push(_pCurrentNode);

    if(pNewNode != NULL)
    {
        if(szNodename != NULL)
        {
            pNewNode->setName(szNodename);

            insertNamedNode  (pNewNode  );
        }

        if(_sNodeStack.size() == 1)
        {
            _vResultStore.push_back(pNewNode);
        }
    }
    else
    {
        PWARNING << "Could not create node with type " 
                 << szNodeTypename 
                 << endl;
    }
}

void VRMLLoader::endNode(void)
{
    decIndent();

#ifdef DEBUG_WRL
    doIndent(PLOG);
    PLOG << "}" << endl;
#else
    doIndent(PLOG);
#endif

    _sNodeStack.pop();

    if(_sNodeStack.size() != 0)
    {
        _pCurrentNode = _sNodeStack.top(); 
    }
    else
    {
        _pCurrentNode = NULL;
    }
}

void VRMLLoader::beginScript(const Char8 *szNodename)
{
    beginNode("Script", szNodename);
}

void VRMLLoader::endScript(void)
{
    endNode();
}

void VRMLLoader::use(const Char8 *szName)
{
#ifdef DEBUG_WRL
    doIndent(PLOG);
    PLOG << "USE : ";

    if(szName != NULL)
    {
        PLOG << szName << endl;
    }
    else
    {
        PLOG << "NULL" << endl;
    }
#else
    doIndent(PLOG);
#endif

    beginNode("Use", NULL);
    {
        beginField("name", 0);
        {
            addFieldValue(szName);
        }
        endField();
    }
    endNode();
}

void VRMLLoader::beginField(const Char8 *szFieldname,
                            const UInt32            )
{
    if(szFieldname == NULL)
        return;

#ifdef DEBUG_WRL
    doIndent(PLOG);
    PLOG << "BeginField : " 
         << szFieldname 
         << " " 
         << _pCurrentField 
         << " | ";
#endif

    _pCurrentField = NULL;

    if(_pCurrentNode != NULL)
    {
        _pCurrentField     =
            (Field *) _pCurrentNode->getElement(szFieldname);

        _pCurrentFieldDesc = 
            _pCurrentNode->getType().findElementDesc(szFieldname);

#ifdef DEBUG_WRL
        PLOG << "BF : "
             << szFieldname
             << " " 
             << _pCurrentField 
             << " " 
             << _pCurrentFieldDesc
             << endl;
#endif

        if(_pCurrentFieldDesc != NULL)
        {
//            beginEditCP(_pCurrentFC, _pCurrentFieldDesc->getFieldMask());
        }
    }

    _sFieldStack      .push (_pCurrentField);
    _sElementDescStack.push(_pCurrentFieldDesc);

#ifdef DEBUG_WRL
    doIndent(PLOG);
    PLOG << "(" << endl;
#else
    doIndent(PLOG);
#endif

    incIndent();
}

void VRMLLoader::endField(void)
{
    decIndent();

#ifdef DEBUG_WRL
    doIndent(PLOG);
    PLOG << "}" << endl;
#else
    doIndent(PLOG);
#endif

    _sFieldStack.pop();

    if(_sFieldStack.size() != 0)
    {
        _pCurrentField = _sFieldStack.top(); 
    }
    else
    {
        _pCurrentField = NULL;
    }


    if(_pCurrentNode != NULL && _pCurrentFieldDesc != NULL)
    {
//        endEditCP(_pCurrentFC, _pCurrentFieldDesc->getFieldMask());
    }

    _sElementDescStack.pop();
    
    if(_sElementDescStack.size() != 0)
    {
        _pCurrentFieldDesc = _sElementDescStack.top();
    }
    else
    {
        _pCurrentFieldDesc = NULL;
    }
}

void VRMLLoader::addFieldValue(const Char8 *szFieldVal)
{
    if(_pCurrentField != NULL)
    {
        _pCurrentField->pushValueByStr(szFieldVal);
    }
}

void VRMLLoader::addRoute(const Char8 */*szOutNodename*/,
                          const Char8 */*szOutFieldname*/,
                          const Char8 */*szInNodename*/,
                          const Char8 */*szInFieldname*/)
{
}

UInt32 VRMLLoader::getFieldType(const Char8 *szFieldname)
{
    UInt32  returnValue = 0;
    Field  *pField      = NULL;

    if(szFieldname == NULL)
        return returnValue;

    if(_pCurrentNode != NULL)
    {
        pField = (Field *) _pCurrentNode->getElement(szFieldname);

#ifdef DEBUG_WRL
        doIndent(PLOG);
        PLOG << "Get field " << szFieldname << " " << pField << " " << endl;
#else
        doIndent(PLOG);
#endif

        if(pField != NULL)
        {
            returnValue = pField->getType().getId();
        }    
    }

    return returnValue;
}

void VRMLLoader::scanFile(const Char8 *szFilename, UInt32 uiOptions)
{
    _vResultStore     .clear();
    _pFileTree         = NULL;

    _pCurrentNode      = NULL;

    _pCurrentField     = NULL;
    _pCurrentFieldDesc = NULL;

    while(_sNodeStack.empty() == false)
    {
        _sNodeStack.pop();
    }

    while(_sFieldStack.empty() == false)
    {
        _sFieldStack.pop();
    }

    while(_sElementDescStack.empty() == false)
    {
        _sElementDescStack.pop();
    }

    Inherited::scanFile(szFilename, uiOptions);
}

void VRMLLoader::scanFile(const Char8  *szFilename, 
                          UInt32  uiAddOptions, 
                          UInt32  uiSubOptions)
{
    fprintf(stderr, "scanFile(name, add, sub) NOT IMPLEMENTEN\n");
}


VRMLLoader::ResultStore &VRMLLoader::getResultStore(void)
{
    return _vResultStore;
}

VRMLNode *VRMLLoader::getFileTree(void)
{
    if(_pFileTree == NULL)
    {
        VRMLGroup *pGroup = VRMLGroup::create();
        
        ResultStore::iterator resIt  = _vResultStore.begin();
        ResultStore::iterator resEnd = _vResultStore.end  ();
        
        while(resIt != resEnd)
        {
            pGroup->addChild((*resIt));

            ++resIt;
        }

        _pFileTree = pGroup;
    }

    return _pFileTree;
}

VRMLLoader::NameNodeMap *VRMLLoader::getNameNodeMap(void)
{
    return _pNameNodeMap;
}
