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
#include <OSGTime.h>

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

/*! \class osg::VRMLFile
 */

#ifndef __sgi
template OSG_SYSTEMLIB_DLLMAPPING
ScanParseFieldTypeMapper<ScanParseSkel>;
template OSG_SYSTEMLIB_DLLMAPPING
VRMLNodeFactory<ScanParseFieldTypeMapper<ScanParseSkel> >;
#endif

OSG::Time startTime = 0.;
OSG::Time useTime   = 0.;
OSG::Time findTime  = 0.;

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

VRMLFile::VRMLFile(void) :
    Inherited(),

//    _pRootNode         (NullFC),
    _pSceneRootNode     (NullFC),

    _pLightRoot         (NullFC),
    _pCurrentGlobalLight(NullFC),

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

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

VRMLFile::~VRMLFile(void)
{
}

/*-------------------------------------------------------------------------*/
/*                           Skel Replacements                             */

void VRMLFile::scanFile(const Char8 *szFilename, UInt32 uiOptions)
{
    startTime = getSystemTime();

//    _pRootNode           = NullFC;
    _pSceneRootNode      = NullFC;
    _pLightRoot          = NullFC;
    _pCurrentGlobalLight = NullFC;

#ifdef OSG_DEBUG_VRML
    VRMLNodeDesc::resetIndent();
#endif

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

    fprintf(stderr, "Full Time : %lf | Use Time %lf\n", 
            getSystemTime() - startTime,
            useTime);
}

void VRMLFile::scanFile(const Char8  *szFilename, 
                              UInt32  uiAddOptions,
                              UInt32  uiSubOptions)
{
    startTime = getSystemTime();

//    _pRootNode           = NullFC;

    _pSceneRootNode      = NullFC;
    _pLightRoot          = NullFC;
    _pCurrentGlobalLight = NullFC;

#ifdef OSG_DEBUG_VRML
    VRMLNodeDesc::resetIndent();
#endif

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

    fprintf(stderr, "Full Time : %lf | Use Time %lf\n", 
            getSystemTime() - startTime,
            useTime);
}

void VRMLFile::beginNode(const Char8 *szNodeTypename,
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

#ifdef OSG_DEBUG_VRML
    indentLog(VRMLNodeDesc::getIndent(), PINFO);
    PINFO << "Begin Node " << szNodeTypename << endl;

    VRMLNodeDesc::incIndent();
#endif

    if(szNodename != NULL)
    {
        if(pNewNode != NullFC)
        {
            if(pNewNode->getType().isNode() == true)
            {
#ifdef OSG_DEBUG_VRML
                indentLog(VRMLNodeDesc::getIndent(), PINFO);
                PINFO << "Node named : " << szNodename << endl;
#endif

                NodePtr pNode     = NodePtr::dcast(pNewNode);
                NamePtr pNodename = Name::create();

                beginEditCP(pNodename);
                beginEditCP(pNode,Node::AttachmentsFieldMask);

                pNodename->getFieldPtr()->getValue().assign(szNodename);
                pNode->addAttachment(pNodename);

                endEditCP(pNode,Node::AttachmentsFieldMask);
                endEditCP(pNodename);

                NameContainerMap::iterator mIt = 
                    _nameFCMap.find(IDStringLink(szNodename));
                
                if(mIt == _nameFCMap.end())
                {
                    _nameFCMap[IDString(szNodename)] = pNewNode;
                    
#ifdef OSG_DEBUG_VRML
                    indentLog(VRMLNodeDesc::getIndent(), PINFO);
                    PINFO << "Fieldcontainer " << szNodename 
                          << " added to map " << endl;
#endif
                }
            }
            else if(pNewNode->getType().isNodeCore() == true)
            {
#ifdef OSG_DEBUG_VRML
                indentLog(VRMLNodeDesc::getIndent(), PINFO);
                PINFO << "Nodecore named : " << szNodename << endl;
#endif
                NodeCorePtr pNodeCore = NodeCorePtr::dcast(pNewNode);
                NamePtr     pNodename = Name::create();
                
                beginEditCP(pNodename);
                beginEditCP(pNodeCore,NodeCore::AttachmentsFieldMask);

                pNodename->getFieldPtr()->getValue().assign(szNodename);
                pNodeCore->addAttachment(pNodename);           

                endEditCP(pNodeCore,NodeCore::AttachmentsFieldMask);
                endEditCP(pNodename);

                NameContainerMap::iterator mIt = 
                    _nameFCMap.find(IDStringLink(szNodename));
                
                if(mIt == _nameFCMap.end())
                {
                    _nameFCMap[IDString(szNodename)] = pNewNode;
                    
#ifdef OSG_DEBUG_VRML
                    indentLog(VRMLNodeDesc::getIndent(), PINFO);
                    PINFO << "Fieldcontainer " << szNodename 
                          << " added to map " << endl;
#endif
                }
            }
            else
            {
#ifdef OSG_DEBUG_VRML
                indentLog(VRMLNodeDesc::getIndent(), PINFO);
                PINFO << "Fieldcontainer " << szNodeTypename 
                      << " is neither node nor nodecore " << endl;
#endif
                
                NameContainerMap::iterator mIt = 
                    _nameFCMap.find(IDStringLink(szNodename));
                
                if(mIt == _nameFCMap.end())
                {
                    _nameFCMap[IDString(szNodename)] = pNewNode;
                    
#ifdef OSG_DEBUG_VRML
                    indentLog(VRMLNodeDesc::getIndent(), PINFO);
                    PINFO << "Fieldcontainer " << szNodename 
                          << " added to map " << endl;
#endif
                }
                
            }

            _nameDescMap[IDString(szNodename)] = _pCurrNodeDesc;
            
#ifdef OSG_DEBUG_VRML
            indentLog(VRMLNodeDesc::getIndent(), PINFO);
            PINFO << "Desc for " << szNodename << " added to map " << endl;
#endif
        }
        else
        {
#ifdef OSG_DEBUG_VRML
            indentLog(VRMLNodeDesc::getIndent(), PINFO);
            PINFO << "Fieldcontainer " 
                  << szNodeTypename 
                  << "is empty, save on end " 
                  << endl;
#endif

            if(_pCurrNodeDesc != NULL)
                _pCurrNodeDesc->setOnEndSave(szNodename);
            
            _nameDescMap[IDString(szNodename)] = _pCurrNodeDesc;
            
#ifdef OSG_DEBUG_VRML
            indentLog(VRMLNodeDesc::getIndent(), PINFO);
            PINFO << "Desc for " << szNodename << " added to map " << endl;
#endif
        }
    }

    setContainerFieldValue(pNewNode);

    _pCurrentFC = pNewNode;

    _fcStack.push(_pCurrentFC);

    if(_fcStack.size() == 1)
    {
        NodePtr pNode = NodePtr::dcast(_pCurrentFC);

        if(_pSceneRootNode == NullFC)
        {
            GroupPtr pGroup = Group::create();

            _pSceneRootNode = Node::create();

            beginEditCP(_pSceneRootNode, Node::CoreFieldMask);
            {
                _pSceneRootNode->setCore(pGroup);
            }
            endEditCP  (_pSceneRootNode, Node::CoreFieldMask);
        }

        beginEditCP(_pSceneRootNode, Node::ChildrenFieldMask);
        {
            _pSceneRootNode->addChild(pNode);
        }
        endEditCP  (_pSceneRootNode, Node::ChildrenFieldMask);
    }
}
   
void VRMLFile::endNode(void)
{
    if(_pCurrNodeDesc == NULL)
    {
#ifdef OSG_DEBUG_VRML
        VRMLNodeDesc::decIndent();

        indentLog(VRMLNodeDesc::getIndent(), PINFO);
        PINFO << "End Node " << endl;
#endif
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

#ifdef OSG_DEBUG_VRML
    VRMLNodeDesc::decIndent();

    indentLog(VRMLNodeDesc::getIndent(), PINFO);
    PINFO << "End Node " << endl;
#endif
}

void VRMLFile::beginScript(const Char8 *szNodename)
{
    beginNode("Script", szNodename);
}

void VRMLFile::endScript(void)
{
    endNode();
}

void VRMLFile::beginField(const Char8  *szFieldname,
                          const UInt32  OSG_VRML_ARG(uiFieldTypeId))
{
    if(szFieldname == NULL)
        return;

#ifdef OSG_DEBUG_VRML
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
#endif

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

#ifdef OSG_DEBUG_VRML
    VRMLNodeDesc::decIndent();

    indentLog(VRMLNodeDesc::getIndent(), PINFO);
    PINFO << "VRMLFile::endField " << endl;
#endif
}


void VRMLFile::addFieldValue(const Char8 *szFieldVal)
{
    Inherited::addFieldValue(szFieldVal);

    if(_pCurrNodeDesc != NULL)
    {
        _pCurrNodeDesc->addFieldValue(_pCurrentField, szFieldVal);
    }
}

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

#ifdef OSG_DEBUG_VRML
    indentLog(VRMLNodeDesc::getIndent(), PINFO);
    PINFO << "VRMLFile::getFieldType : Got Field and type "
          << returnValue        << " " 
          << _pCurrentField     << " " 
          << _pCurrentFieldDesc << " ";
    
    if(_pCurrentField != NULL)
        PINFO << _pCurrentField->getType().getName() << endl;
    else
        PINFO << endl;
#endif

    return returnValue;
}

void VRMLFile::use(const Char8 *szName)
{
    Time beginUse = getSystemTime();

    FieldContainerPtr pUsedFC;

    // try to find a container with the given name attachment

#ifdef OSG_DEBUG_VRML
    indentLog(VRMLNodeDesc::getIndent(), PINFO);
    PINFO << "VRMLFile::use : looking for " 
          << szName 
          << endl;

    VRMLNodeDesc::incIndent();
#endif

    

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

#ifdef OSG_DEBUG_VRML
    VRMLNodeDesc::decIndent();
#endif

    useTime += (getSystemTime() - beginUse);
}

/*-------------------------------------------------------------------------*/
/*                          Helper                                         */

void VRMLFile::scanStandardPrototypes(const Char8  *szFilename, 
                                            UInt32  uiOptions)
{
#ifdef OSG_DEBUG_VRML
    VRMLNodeDesc::resetIndent();
#endif

    preStandardProtos();
    scanFile(szFilename, uiOptions);
    postStandardProtos();

//    dumpTable();
}

void VRMLFile::createStandardPrototypes(void)
{
#ifdef OSG_DEBUG_VRML
    VRMLNodeDesc::resetIndent();
#endif

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
 
 beginProto   ("Anchor"); 
 {
     addEventInDecl       ("MFNode", "addChildren");
     addEventInDecl       ("MFNode", "removeChildren");
     
     beginExposedFieldDecl("MFNode",   OSGmfNode,   "children");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFString", OSGsfString, "description");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFString", OSGmfString, "parameter");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFString", OSGmfString, "url");
     endExposedFieldDecl  ();
     
     beginFieldDecl       ("SFVec3f",  OSGsfVec3f, "bboxCenter");
     addFieldValue        ("0 0 0");
     endFieldDecl         ();

     beginFieldDecl       ("SFVec3f",  OSGsfVec3f, "bboxSize");
     addFieldValue        ("-1 -1 -1");
     endFieldDecl         ();
 }
 endProto     ();

    
#if 0
PROTO Appearance [
  exposedField SFNode material          NULL
  exposedField SFNode texture           NULL
  exposedField SFNode textureTransform  NULL
] { }
#endif

 beginProto("Appearance");
 {
     beginExposedFieldDecl("SFNode", OSGsfNode, "material");
//     addFieldValue         ("NULL");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFNode", OSGsfNode, "texture");
//     addFieldValue         ("NULL");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFNode", OSGsfNode, "textureTransform");
//     addFieldValue         ("NULL");
     endExposedFieldDecl  ();
 }
 endProto  ();

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

 beginProto("AudioClip");
 {
     beginExposedFieldDecl("SFString", OSGsfString, "description");
     addFieldValue        ("");
     endExposedFieldDecl  ();
     
     beginExposedFieldDecl("SFBool", OSGsfbool, "loop");
     addFieldValue        ("FALSE");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", OSGsfFloat, "pitch");
     addFieldValue        ("1.0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFTime", OSGsfTime, "startTime");
     addFieldValue        ("0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFTime", OSGsfTime, "stopTime");
     addFieldValue        ("0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFString", OSGmfString, "url");
     endExposedFieldDecl  ();

     addEventOutDecl      ("SFTime", "duration_changed");
     addEventOutDecl      ("SFBool", "isActive");
 }
 endProto  ();

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

 beginProto("Background");
 {
     addEventInDecl       ("SFBool", "set_bind");
     
     beginExposedFieldDecl("MFFloat", OSGmfFloat, "groundAngle");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFColor", OSGmfColor, "groundColor");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFString", OSGmfString, "backUrl");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFString", OSGmfString, "bottomUrl");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFString", OSGmfString, "frontUrl");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFString", OSGmfString, "leftUrl");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFString", OSGmfString, "rightUrl");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFString", OSGmfString, "topUrl");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFFloat", OSGmfFloat, "skyAngle");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFColor", OSGmfColor, "skyColor");
     addFieldValue        ("0 0 0");
     endExposedFieldDecl  ();

     addEventOutDecl      ("SFBool", "isBound");
 }
 endProto  ();


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

 beginProto("Billboard");
 {
     addEventInDecl       ("MFNode", "addChildren");
     addEventInDecl       ("MFNode", "removeChildren");
     
     beginExposedFieldDecl("SFVec3f", OSGsfVec3f, "axisOfRotation");
     addFieldValue        ("0 1 0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFNode", OSGmfNode, "children");
     endExposedFieldDecl  ();
     
     beginFieldDecl       ("SFVec3f", OSGsfVec3f, "bboxCenter");
     addFieldValue        ("0 0 0");
     endFieldDecl         ();

     beginFieldDecl       ("SFVec3f", OSGsfVec3f, "bboxSize");
     addFieldValue        ("-1 -1 -1");
     endFieldDecl         ();
 }
 endProto  ();

#if 0
PROTO Box [
  field    SFVec3f size  2 2 2 
] { }
#endif

 beginProto("Box");
 {
     beginFieldDecl("SFVec3f", OSGsfVec3f, "size");
     addFieldValue ("2 2 2");
     endFieldDecl  ();
 }
 endProto  ();

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

 beginProto("Collision");
 {
     addEventInDecl      ("MFNode", "addChildren");
     addEventInDecl      ("MFNode", "removeChildren");

     beginExposedFieldDecl("MFNode", OSGmfNode, "children");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFBool", OSGsfbool, "collide");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();

     beginFieldDecl       ("SFVec3f", OSGsfVec3f, "bboxCenter");
     addFieldValue        ("0 0 0");
     endFieldDecl         ();

     beginFieldDecl       ("SFVec3f", OSGsfVec3f, "bboxSize");
     addFieldValue        ("-1 -1 -1");
     endFieldDecl         ();

     beginFieldDecl       ("SFNode", OSGsfNode, "proxy");
     endFieldDecl         ();
     
     addEventOutDecl      ("SFTime", "collideTime");
 }
 endProto  ();

#if 0
PROTO Color [
  exposedField MFColor color     []
] { }
#endif

 beginProto("Color");
 {
     beginExposedFieldDecl("MFColor", OSGmfColor, "color");
     endExposedFieldDecl  ();
 }
 endProto  ();

#if 0
PROTO ColorInterpolator [
  eventIn      SFFloat set_fraction
  exposedField MFFloat key       []
  exposedField MFColor keyValue  []
  eventOut     SFColor value_changed
] { }
#endif

 beginProto("ColorInterpolator");
 {
     addEventInDecl       ("SFFloat", "set_fraction");

     beginExposedFieldDecl("MFFloat", OSGmfFloat, "key");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFColor", OSGmfColor, "keyValue");
     endExposedFieldDecl  ();

     addEventOutDecl      ("SFColor", "value_changed");
 }
 endProto  ();

#if 0
PROTO Cone [
  field     SFFloat   bottomRadius 1
  field     SFFloat   height       2
  field     SFBool    side         TRUE
  field     SFBool    bottom       TRUE
] { }
#endif

 beginProto("Cone");
 {
     beginFieldDecl("SFFloat", OSGsfFloat, "bottomRadius");
     addFieldValue ("1");
     endFieldDecl  ();

     beginFieldDecl("SFFloat", OSGsfFloat, "height");
     addFieldValue ("2");
     endFieldDecl  ();

     beginFieldDecl("SFBool", OSGsfbool, "side");
     addFieldValue ("TRUE");
     endFieldDecl  ();

     beginFieldDecl("SFBool", OSGsfbool, "bottom");
     addFieldValue ("TRUE");
     endFieldDecl  ();
 }
 endProto  ();

#if 0
PROTO Coordinate [
  exposedField MFVec3f point  []
] { }
#endif

 beginProto("Coordinate");
 {
     beginExposedFieldDecl("MFVec3f", OSGmfVec3f, "point");
     endExposedFieldDecl  ();
 }
 endProto  ();

#if 0
PROTO CoordinateInterpolator [
  eventIn      SFFloat set_fraction
  exposedField MFFloat key       []
  exposedField MFVec3f keyValue  []
  eventOut     MFVec3f value_changed
] { }
#endif

 beginProto("CoordinateInterpolator");
 {
     addEventInDecl       ("SFFloat", "set_fraction");
     
     beginExposedFieldDecl("MFFloat", OSGmfFloat, "key");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFVec3f", OSGmfVec3f, "keyValue");
     endExposedFieldDecl  ();

     addEventOutDecl      ("MFVec3f", "value_changed");
 }
 endProto  ();

#if 0
PROTO Cylinder [
  field    SFBool    bottom  TRUE
  field    SFFloat   height  2
  field    SFFloat   radius  1
  field    SFBool    side    TRUE
  field    SFBool    top     TRUE
] { }
#endif

 beginProto("Cylinder");
 {
     beginFieldDecl("SFBool", OSGsfbool, "bottom");
     addFieldValue ("TRUE");
     endFieldDecl  ();

     beginFieldDecl("SFFloat", OSGsfFloat, "height");
     addFieldValue ("2");
     endFieldDecl  ();

     beginFieldDecl("SFFloat", OSGsfFloat, "radius");
     addFieldValue ("1");
     endFieldDecl  ();

     beginFieldDecl("SFBool", OSGsfbool, "side");
     addFieldValue ("TRUE");
     endFieldDecl  ();

     beginFieldDecl("SFBool", OSGsfbool, "top");
     addFieldValue ("TRUE");
     endFieldDecl  ();
 }
 endProto  ();

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

 beginProto("CylinderSensor");
 {
     beginExposedFieldDecl("SFBool", OSGsfbool, "autoOffset");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", OSGsfFloat, "diskAngle");
     addFieldValue        ("0.262");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFBool", OSGsfbool, "enabled");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", OSGsfFloat, "maxAngle");
     addFieldValue        ("-1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", OSGsfFloat, "minAngle");
     addFieldValue        ("0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", OSGsfFloat, "offset");
     addFieldValue        ("0");
     endExposedFieldDecl  ();
     
     addEventOutDecl      ("SFBool", "isActive");
     addEventOutDecl      ("SFRotation", "rotation_changed");
     addEventOutDecl      ("SFVec3f", "trackPoint_changed");
 }
 endProto  ();

#if 0
PROTO DirectionalLight [
  exposedField SFFloat ambientIntensity  0 
  exposedField SFColor color             1 1 1
  exposedField SFVec3f direction         0 0 -1
  exposedField SFFloat intensity         1 
  exposedField SFBool  on                TRUE 
] { }
#endif

 beginProto("DirectionalLight");
 {
     beginExposedFieldDecl("SFFloat", OSGsfFloat, "ambientIntensity");
     addFieldValue        ("0"); 
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFColor", OSGsfColor, "color");
     addFieldValue        ("1 1 1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec3f", OSGsfVec3f, "direction");
     addFieldValue        ("0 0 -1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", OSGsfFloat, "intensity");
     addFieldValue        ("1"); 
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFBool", OSGsfbool, "on");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();
 }
 endProto  ();

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

 beginProto("ElevationGrid");
 {
     addEventInDecl       ("MFFloat", "set_height");

     beginExposedFieldDecl("SFNode", OSGsfNode, "color");
//     addFieldValue        ("NULL");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFNode", OSGsfNode, "normal");
//     addFieldValue        ("NULL");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFNode", OSGsfNode, "texCoord");
//     addFieldValue        ("NULL");
     endExposedFieldDecl  ();

     beginFieldDecl       ("SFBool", OSGsfbool, "ccw");
     addFieldValue        ("TRUE");
     endFieldDecl         ();

     beginFieldDecl       ("SFBool", OSGsfbool, "colorPerVertex");
     addFieldValue        ("TRUE");
     endFieldDecl         ();

     beginFieldDecl       ("SFFloat", OSGsfFloat, "creaseAngle");
     addFieldValue        ("0");
     endFieldDecl         ();

     beginFieldDecl       ("MFFloat", OSGsfFloat, "height");
     endFieldDecl         ();

     beginFieldDecl       ("SFBool", OSGsfbool, "normalPerVertex");
     addFieldValue        ("TRUE");
     endFieldDecl         ();

     beginFieldDecl       ("SFBool", OSGsfbool, "solid");
     addFieldValue        ("TRUE");
     endFieldDecl         ();

     beginFieldDecl       ("SFInt32", OSGsfInt32, "xDimension");
     addFieldValue        ("0");
     endFieldDecl         ();

     beginFieldDecl       ("SFFloat", OSGsfFloat, "xSpacing");
     addFieldValue        ("0.0");
     endFieldDecl         ();

     beginFieldDecl       ("SFInt32", OSGsfInt32, "zDimension");
     addFieldValue        ("0");
     endFieldDecl         ();

     beginFieldDecl       ("SFFloat", OSGsfFloat, "zSpacing");
     addFieldValue        ("0.0");
     endFieldDecl         ();
 }
 endProto  ();

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

 beginProto("Extrusion");
 {
     addEventInDecl("MFVec2f", "set_crossSection");
     addEventInDecl("MFRotation", "set_orientation");
     addEventInDecl("MFVec2f", "set_scale");
     addEventInDecl("MFVec3f", "set_spine");

     beginFieldDecl("SFBool", OSGsfbool, "beginCap");
     addFieldValue ("TRUE");
     endFieldDecl  ();

     beginFieldDecl("SFBool", OSGsfbool, "ccw");
     addFieldValue ("TRUE");
     endFieldDecl  ();

     beginFieldDecl("SFBool", OSGsfbool, "convex");
     addFieldValue ("TRUE");
     endFieldDecl  ();

     beginFieldDecl("SFFloat", OSGsfFloat, "creaseAngle");
     addFieldValue ("0");
     endFieldDecl  ();

     beginFieldDecl("MFVec2f", OSGmfVec2f, "crossSection");
     addFieldValue (" 1  1");
     addFieldValue (" 1 -1");
     addFieldValue ("-1 -1");
     addFieldValue ("-1  1");
     addFieldValue (" 1  1");
     endFieldDecl  ();

     beginFieldDecl("SFBool", OSGsfbool, "endCap");
     addFieldValue ("TRUE");
     endFieldDecl  ();

     beginFieldDecl("MFRotation", OSGmfRotation, "orientation");
     addFieldValue ("0 0 1 0");
     endFieldDecl  ();

     beginFieldDecl("MFVec2f", OSGmfVec2f, "scale");
     addFieldValue ("1 1");
     endFieldDecl  ();
     
     beginFieldDecl("SFBool", OSGsfbool, "solid");
     addFieldValue ("TRUE");
     endFieldDecl  ();
     
     beginFieldDecl("MFVec3f", OSGmfVec3f, "spine");
     addFieldValue ("0 0 0");
     addFieldValue ("0 1 0");
     endFieldDecl  ();
 }
 endProto  ();

#if 0
PROTO Fog [
  exposedField SFColor  color            1 1 1
  exposedField SFString fogType          "LINEAR"
  exposedField SFFloat  visibilityRange  0
  eventIn      SFBool   set_bind
  eventOut     SFBool   isBound
] { }
#endif

 beginProto("Fog");
 {
     beginExposedFieldDecl("SFColor", OSGsfColor, "color");
     addFieldValue        ("1 1 1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFString", OSGsfString, "fogType");
     addFieldValue        ("LINEAR");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", OSGsfFloat, "visibilityRange");
     addFieldValue        ("0");
     endExposedFieldDecl  ();

     addEventInDecl       ("SFBool", "set_bind");
     addEventOutDecl      ("SFBool", "isBound");
 }
 endProto  ();

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

 beginProto("FontStyle");
 {
     beginFieldDecl("SFString", OSGsfString, "family");
     addFieldValue ("SERIF");
     endFieldDecl  ();

     beginFieldDecl("SFBool", OSGsfbool, "horizontal");
     addFieldValue ("TRUE");
     endFieldDecl  ();
     
     beginFieldDecl("MFString", OSGmfString, "justify");
     addFieldValue ("BEGIN");
     endFieldDecl  ();

     beginFieldDecl("SFString", OSGsfString, "language");
     addFieldValue ("");
     endFieldDecl  ();

     beginFieldDecl("SFBool", OSGsfbool, "leftToRight");
     addFieldValue ("TRUE");
     endFieldDecl  ();

     beginFieldDecl("SFFloat", OSGsfFloat, "size");
     addFieldValue ("1.0");
     endFieldDecl  ();

     beginFieldDecl("SFFloat", OSGsfFloat, "spacing");
     addFieldValue ("1.0");
     endFieldDecl  ();

     beginFieldDecl("SFString", OSGsfString, "style");
     addFieldValue ("PLAIN");
     endFieldDecl  ();

     beginFieldDecl("SFBool", OSGsfbool, "topToBottom");
     addFieldValue ("TRUE");
     endFieldDecl  ();
 }
 endProto   ();

#if 0
PROTO Group [
  eventIn      MFNode  addChildren
  eventIn      MFNode  removeChildren
  exposedField MFNode  children   []
  field        SFVec3f bboxCenter 0 0 0
  field        SFVec3f bboxSize   -1 -1 -1
] { }
#endif

 beginProto("Group");
 {
     addEventInDecl    ("MFNode", "addChildren");
     addEventInDecl    ("MFNode", "removeChildren");
 
     beginExposedFieldDecl("MFNode", OSGmfNode, "children");
     endExposedFieldDecl  ();

     beginFieldDecl       ("SFVec3f", OSGsfVec3f, "bboxCenter");
     addFieldValue        ("0 0 0");
     endFieldDecl         ();

     beginFieldDecl       ("SFVec3f", OSGsfVec3f, "bboxSize");
     addFieldValue        ("-1 -1 -1");
     endFieldDecl         ();
 }
 endProto  ();

#if 0
PROTO ImageTexture [
  exposedField MFString url     []
  field        SFBool   repeatS TRUE
  field        SFBool   repeatT TRUE
] { }
#endif

 beginProto("ImageTexture");
 {
     beginExposedFieldDecl("MFString", OSGmfString, "url");
     endExposedFieldDecl  ();

     beginFieldDecl       ("SFBool", OSGsfbool, "repeatS");
     addFieldValue        ("TRUE");
     endFieldDecl         ();

     beginFieldDecl       ("SFBool", OSGsfbool, "repeatT");
     addFieldValue        ("TRUE");
     endFieldDecl         ();
 }
 endProto  ();

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

 beginProto("IndexedFaceSet");
 { 
     addEventInDecl       ("MFInt32", "set_colorIndex");
     addEventInDecl       ("MFInt32", "set_coordIndex");
     addEventInDecl       ("MFInt32", "set_normalIndex");
     addEventInDecl       ("MFInt32", "set_texCoordIndex");
     
     beginExposedFieldDecl("SFNode", OSGsfNode, "color");
//     addFieldValue        ("NULL");
     endExposedFieldDecl  ();
     
     beginExposedFieldDecl("SFNode", OSGsfNode, "coord");
//     addFieldValue        ("NULL");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFNode", OSGsfNode, "normal");
//     addFieldValue        ("NULL");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFNode", OSGsfNode, "texCoord");
//     addFieldValue        ("NULL");
     endExposedFieldDecl  ();

     beginFieldDecl       ("SFBool", OSGsfbool, "ccw");
     addFieldValue        ("TRUE");
     endFieldDecl         ();

     beginFieldDecl       ("MFInt32", OSGmfInt32, "colorIndex");
     endFieldDecl         ();

     beginFieldDecl       ("SFBool", OSGsfbool, "colorPerVertex");
     addFieldValue        ("TRUE");
     endFieldDecl         ();

     beginFieldDecl       ("SFBool", OSGsfbool, "convex");
     addFieldValue        ("TRUE");
     endFieldDecl         ();

     beginFieldDecl       ("MFInt32", OSGmfInt32, "coordIndex");
     endFieldDecl         ();
     
     beginFieldDecl       ("SFFloat", OSGsfFloat, "creaseAngle");
     addFieldValue        ("0");
     endFieldDecl         ();

     beginFieldDecl       ("MFInt32", OSGmfInt32, "normalIndex");
     endFieldDecl         ();

     beginFieldDecl       ("SFBool",  OSGsfbool, "normalPerVertex");
     addFieldValue        ("TRUE");
     endFieldDecl         ();

     beginFieldDecl       ("SFBool",  OSGsfbool, "solid");
     addFieldValue        ("TRUE");
     endFieldDecl         ();
     
     beginFieldDecl       ("MFInt32", OSGmfInt32, "texCoordIndex");
     endFieldDecl();
 }
 endProto  ();

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

 beginProto("IndexedLineSet");
 {
     addEventInDecl       ("MFInt32", "set_colorIndex");
     addEventInDecl       ("MFInt32", "set_coordIndex");

     beginExposedFieldDecl("SFNode", OSGsfNode, "color");
//     addFieldValue        ("NULL");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFNode", OSGsfNode, "coord");
//     addFieldValue        ("NULL");
     endExposedFieldDecl  ();

     beginFieldDecl       ("MFInt32", OSGmfInt32, "colorIndex");
     endFieldDecl         ();

     beginFieldDecl       ("SFBool", OSGsfbool, "colorPerVertex");
     addFieldValue        ("TRUE");
     endFieldDecl         ();
     
     beginFieldDecl       ("MFInt32", OSGmfInt32, "coordIndex");
     endFieldDecl         ();
 }
 endProto  ();

#if 0
PROTO Inline [
  exposedField MFString url        []
  field        SFVec3f  bboxCenter 0 0 0
  field        SFVec3f  bboxSize   -1 -1 -1
] { }
#endif

 beginProto("Inline");
 {
     beginExposedFieldDecl("MFString", OSGmfString, "url");
     endExposedFieldDecl  ();

     beginFieldDecl       ("SFVec3f", OSGsfVec3f, "bboxCenter");
     addFieldValue        ("0 0 0");
     endFieldDecl         ();

     beginFieldDecl       ("SFVec3f", OSGsfVec3f, "bboxSize");
     addFieldValue        ("-1 -1 -1");
     endFieldDecl         ();
 }
 endProto  ();
   
#if 0
PROTO LOD [
  exposedField MFNode  level    [] 
  field        SFVec3f center   0 0 0
  field        MFFloat range    [] 
] { }
#endif

 beginProto("LOD");
 {
     beginExposedFieldDecl("MFNode", OSGmfNode, "level");
     endExposedFieldDecl  ();
     
     beginFieldDecl       ("SFVec3f", OSGsfVec3f, "center");
     addFieldValue        ("0 0 0");
     endFieldDecl         ();

     beginFieldDecl       ("MFFloat", OSGmfFloat, "range");
     endFieldDecl         ();
 }
 endProto  ();

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

 beginProto("Material");
 {
     beginExposedFieldDecl("SFFloat", OSGsfFloat, "ambientIntensity");
     addFieldValue        ("0.2");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFColor", OSGsfColor, "diffuseColor");
     addFieldValue        ("0.8 0.8 0.8");
     endExposedFieldDecl  ();
     
     beginExposedFieldDecl("SFColor", OSGsfColor, "emissiveColor");
     addFieldValue        ("0 0 0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", OSGsfFloat, "shininess");
     addFieldValue        ("0.2");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFColor", OSGsfColor, "specularColor");
     addFieldValue        ("0 0 0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", OSGsfFloat, "transparency");
     addFieldValue        ("0");
     endExposedFieldDecl  ();
 }
 endProto  ();

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

 beginProto("MovieTexture");
 {
     beginExposedFieldDecl("SFBool", OSGsfbool, "loop");
     addFieldValue        ("FALSE");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", OSGsfFloat, "speed");
     addFieldValue        ("1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFTime", OSGsfTime, "startTime");
     addFieldValue        ("0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFTime", OSGsfTime, "stopTime");
     addFieldValue        ("0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFString", OSGmfString, "url");
     endExposedFieldDecl  ();

     beginFieldDecl       ("SFBool", OSGsfbool, "repeatS");
     addFieldValue        ("TRUE");
     endFieldDecl         ();

     beginFieldDecl       ("SFBool", OSGsfbool, "repeatT");
     addFieldValue        ("TRUE");
     endFieldDecl         ();

     addEventOutDecl      ("SFFloat", "duration_changed");
     addEventOutDecl      ("SFBool", "isActive");
 }
 endProto  ();

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

 beginProto("NavigationInfo");
 {
     addEventInDecl       ("SFBool", "set_bind");
     
     beginExposedFieldDecl("MFFloat", OSGmfFloat, "avatarSize");
     addFieldValue        ("0.25");
     addFieldValue        ("1.6 ");
     addFieldValue        ("0.75");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFBool", OSGsfbool, "headlight");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", OSGsfFloat, "speed");
     addFieldValue        ("1.0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFString", OSGmfString, "type");
     addFieldValue        ("WALK");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", OSGsfFloat, "visibilityLimit");
     addFieldValue        ("0.0");
     endExposedFieldDecl  ();

     addEventOutDecl      ("SFBool", "isBound");
 }
 endProto  ();

#if 0
PROTO Normal [
  exposedField MFVec3f vector []
] { }
#endif

 beginProto("Normal");
 {
     beginExposedFieldDecl("MFVec3f", OSGmfVec3f, "vector");
     endExposedFieldDecl  ();
 }
 endProto  ();

#if 0
PROTO NormalInterpolator [
  eventIn      SFFloat set_fraction
  exposedField MFFloat key       []
  exposedField MFVec3f keyValue  []
  eventOut     MFVec3f value_changed
] { }
#endif

 beginProto("NormalInterpolator");
 {
     addEventInDecl       ("SFFloat", "set_fraction");
     
     beginExposedFieldDecl("MFFloat", OSGmfFloat, "key");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFVec3f", OSGmfVec3f, "keyValue");
     endExposedFieldDecl  ();

     addEventOutDecl      ("MFVec3f",  "value_changed");
 }
 endProto  ();

#if 0
PROTO OrientationInterpolator [
  eventIn      SFFloat    set_fraction
  exposedField MFFloat    key       []
  exposedField MFRotation keyValue  []
  eventOut     SFRotation value_changed
] { }
#endif

 beginProto("OrientationInterpolator");
 {
     addEventInDecl       ("SFFloat", "set_fraction");

     beginExposedFieldDecl("MFFloat", OSGmfFloat, "key");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFRotation", OSGmfRotation, "keyValue");
     endExposedFieldDecl  ();
     
     addEventOutDecl      ("SFRotation", "value_changed");
 }
 endProto  ();

#if 0
PROTO PixelTexture [
  exposedField SFImage  image      0 0 0
  field        SFBool   repeatS    TRUE
  field        SFBool   repeatT    TRUE
] { }
#endif

 beginProto("PixelTexture");
 {
     beginExposedFieldDecl("SFImage", OSGsfImage, "image");
//     addFieldValue        ("0 0 0");
     endExposedFieldDecl  ();

     beginFieldDecl       ("SFBool", OSGsfbool, "repeatS");
     addFieldValue        ("TRUE");
     endFieldDecl         ();

     beginFieldDecl       ("SFBool", OSGsfbool, "repeatT");
     addFieldValue        ("TRUE");
     endFieldDecl         ();
 }
 endProto  ();

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

 beginProto("PlaneSensor");
 {
     beginExposedFieldDecl("SFBool", OSGsfbool, "autoOffset");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFBool", OSGsfbool, "enabled");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec2f", OSGsfVec2f, "maxPosition");
     addFieldValue        ("-1 -1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec2f", OSGsfVec2f, "minPosition");
     addFieldValue        ("0 0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec3f", OSGsfVec3f, "offset");
     addFieldValue        ("0 0 0");
     endExposedFieldDecl  ();

     addEventOutDecl      ("SFBool", "isActive");
     addEventOutDecl      ("SFVec3f", "trackPoint_changed");
     addEventOutDecl      ("SFVec3f", "translation_changed");
 }
 endProto  ();


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

 beginProto("PointLight");
 {
     beginExposedFieldDecl("SFFloat", OSGsfFloat, "ambientIntensity");
     addFieldValue        ("0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec3f", OSGsfVec3f, "attenuation");
     addFieldValue        ("1 0 0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFColor", OSGsfColor, "color");
     addFieldValue        ("1 1 1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", OSGsfFloat, "intensity");
     addFieldValue        ("1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec3f", OSGsfVec3f, "location");
     addFieldValue        ("0 0 0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFBool", OSGsfbool, "on");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", OSGsfFloat, "radius");
     addFieldValue        ("100");
     endExposedFieldDecl  ();
 }
 endProto  ();

#if 0
PROTO PointSet [
  exposedField  SFNode  color      NULL
  exposedField  SFNode  coord      NULL
] { }
#endif

 beginProto("PointSet");
 {
     beginExposedFieldDecl("SFNode", OSGsfNode, "color");
//     addFieldValue        ("NULL");
     endFieldDecl         ();

     beginExposedFieldDecl("SFNode", OSGsfNode, "coord");
//     addFieldValue        ("NULL");
     endFieldDecl         ();
 }
 endProto  ();

#if 0
PROTO PositionInterpolator [
  eventIn      SFFloat set_fraction
  exposedField MFFloat key       []
  exposedField MFVec3f keyValue  []
  eventOut     SFVec3f value_changed
] { }
#endif

 beginProto("PositionInterpolator");
 {
     addEventInDecl       ("SFFloat", "set_fraction");
     
     beginExposedFieldDecl("MFFloat", OSGmfFloat, "key");
     endExposedFieldDecl();

     beginExposedFieldDecl("MFVec3f", OSGmfVec3f, "keyValue");
     endExposedFieldDecl  ();

     addEventOutDecl      ("SFVec3f", "value_changed");
 }
 endProto  ();

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

 beginProto("ProximitySensor");
 {
     beginExposedFieldDecl("SFVec3f", OSGsfVec3f, "center");
     addFieldValue        ("0 0 0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec3f", OSGsfVec3f, "size");
     addFieldValue        ("0 0 0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFBool", OSGsfbool, "enabled");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();

     addEventOutDecl      ("SFBool", "isActive");
     addEventOutDecl      ("SFVec3f", "position_changed");
     addEventOutDecl      ("SFRotation", "orientation_changed");
     addEventOutDecl      ("SFTime", "enterTime");
     addEventOutDecl      ("SFTime", "exitTime");
 }
 endProto  ();

#if 0
PROTO ScalarInterpolator [
  eventIn      SFFloat set_fraction
  exposedField MFFloat key       []
  exposedField MFFloat keyValue  []
  eventOut     SFFloat value_changed
] { }
#endif

 beginProto("ScalarInterpolator");
 {
     addEventInDecl       ("SFFloat", "set_fraction");

     beginExposedFieldDecl("MFFloat", OSGmfFloat, "key");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFFloat", OSGmfFloat, "keyValue");
     endExposedFieldDecl  ();
     
     addEventOutDecl      ("SFFloat", "value_changed");
 }
 endProto  ();

#if 0
PROTO Script [
  exposedField MFString url           [ ] 
  field        SFBool   directOutput  FALSE
  field        SFBool   mustEvaluate  FALSE
] { }
#endif

 beginProto("Script");
 {
     beginExposedFieldDecl("MFString", OSGmfString, "url");
     endExposedFieldDecl  ();

     beginFieldDecl       ("SFBool", OSGsfbool, "directOutput");
     addFieldValue        ("FALSE");
     endFieldDecl         ();

     beginFieldDecl       ("SFBool", OSGsfbool, "mustEvaluate");
     addFieldValue        ("FALSE");
     endFieldDecl         ();
 }
 endProto  ();

#if 0
PROTO Shape [
  field SFNode appearance NULL
  field SFNode geometry   NULL
] { }
#endif

 beginProto("Shape");
 {
     beginFieldDecl("SFNode", OSGsfNode, "appearance");
//     addFieldValue ("NULL");
     endFieldDecl  ();

     beginFieldDecl("SFNode", OSGsfNode, "geometry");
//     addFieldValue ("NULL");
     endFieldDecl  ();
 }
 endProto  ();

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

 beginProto("Sound");
 {
     beginExposedFieldDecl("SFVec3f", OSGsfVec3f, "direction");
     addFieldValue        ("0 0 1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", OSGsfFloat, "intensity");
     addFieldValue        ("1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec3f", OSGsfVec3f, "location");
     addFieldValue        ("0 0 0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", OSGsfFloat, "maxBack");
     addFieldValue        ("10");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", OSGsfFloat, "maxFront");
     addFieldValue        ("10");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", OSGsfFloat, "minBack");
     addFieldValue        ("1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", OSGsfFloat, "minFront");
     addFieldValue        ("1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", OSGsfFloat, "priority");
     addFieldValue        ("0");
     endExposedFieldDecl  ();
     
     beginExposedFieldDecl("SFNode", OSGsfNode, "source");
//     addFieldValue        ("NULL");
     endExposedFieldDecl  ();
     
     beginFieldDecl       ("SFBool", OSGsfbool, "spatialize");
     addFieldValue        ("TRUE");
     endFieldDecl         ();
 }
 endProto  ();

#if 0
PROTO Sphere [
  field SFFloat radius  1
] { }
#endif

 beginProto("Sphere");
 {
     beginFieldDecl("SFFloat", OSGsfFloat, "radius");
     addFieldValue ("1");
     endFieldDecl  ();
 }
 endProto  ();

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

 beginProto("SphereSensor");
 {
     beginExposedFieldDecl("SFBool", OSGsfbool, "autoOffset");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFBool", OSGsfbool, "enabled");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFRotation", OSGsfRotation, "offset");
     addFieldValue        ("0 1 0 0");
     endExposedFieldDecl  ();

     addEventOutDecl      ("SFBool", "isActive");
     addEventOutDecl      ("SFRotation", "rotation_changed");
     addEventOutDecl      ("SFVec3f", "trackPoint_changed");
 }
 endProto  ();

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

 beginProto("SpotLight");
 {
     beginExposedFieldDecl("SFFloat", OSGsfFloat, "ambientIntensity");
     addFieldValue        ("0"); 
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec3f", OSGsfVec3f, "attenuation");
     addFieldValue        ("1 0 0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", OSGsfFloat, "beamWidth");
     addFieldValue        ("1.570796");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFColor", OSGsfColor, "color");
     addFieldValue        ("1 1 1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", OSGsfFloat, "cutOffAngle");
     addFieldValue        ("0.785398");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec3f", OSGsfVec3f, "direction");
     addFieldValue        ("0 0 -1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", OSGsfFloat, "intensity");
     addFieldValue        ("1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec3f", OSGsfVec3f, "location");
     addFieldValue        ("0 0 0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFBool", OSGsfbool, "on");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFFloat", OSGsfFloat, "radius");
     addFieldValue        ("100");
     endExposedFieldDecl  ();
 }
 endProto  ();

#if 0
PROTO Switch [
  exposedField    MFNode  choice      []
  exposedField    SFInt32 whichChoice -1
] { }
#endif

 beginProto("Switch");
 {
     beginExposedFieldDecl("MFNode", OSGmfNode, "choice");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFInt32", OSGsfInt32, "whichChoice");
     addFieldValue        ("-1");
     endExposedFieldDecl  ();
 }
 endProto  ();

#if 0
PROTO Text [
  exposedField  MFString string    []
  field         SFNode   fontStyle NULL
  field         MFFloat  length    []
  field         SFFloat  maxExtent 0.0
] { }
#endif

 beginProto("Text");
 {
     beginExposedFieldDecl("MFString", OSGmfString, "string");
     endExposedFieldDecl  ();

     beginFieldDecl       ("SFNode", OSGsfNode, "fontStyle");
     addFieldValue        ("NULL");
     endFieldDecl         ();

     beginFieldDecl       ("MFFloat", OSGmfFloat, "length");
     endFieldDecl         ();

     beginFieldDecl       ("SFFloat", OSGsfFloat, "maxExtent");
     addFieldValue        ("0.0");
     endFieldDecl         ();
 }
 endProto  ();

#if 0
PROTO TextureCoordinate [
  exposedField MFVec2f point []
] { }
#endif

 beginProto("TextureCoordinate");
 {
     beginExposedFieldDecl("MFVec2f", OSGmfVec2f, "point");
     endExposedFieldDecl  ();
 }
 endProto  ();

#if 0
PROTO TextureTransform [
  exposedField SFVec2f center      0 0
  exposedField SFFloat rotation    0
  exposedField SFVec2f scale       1 1
  exposedField SFVec2f translation 0 0
] { }
#endif

 beginProto("TextureTransform");
 {
     beginExposedFieldDecl("SFVec2f", OSGsfVec2f, "center");
     addFieldValue        ("0 0");
     endExposedFieldDecl  ();
     
     beginExposedFieldDecl("SFFloat", OSGsfFloat, "rotation");
     addFieldValue        ("0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec2f", OSGsfVec2f, "scale");
     addFieldValue        ("1 1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec2f", OSGsfVec2f, "translation");
     addFieldValue        ("0 0");
     endExposedFieldDecl  ();
 }
 endProto  ();

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

 beginProto("TimeSensor");
 {
     beginExposedFieldDecl("SFTime", OSGsfTime, "cycleInterval");
     addFieldValue        ("1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFBool", OSGsfbool, "enabled");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFBool", OSGsfbool, "loop");
     addFieldValue        ("FALSE");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFTime", OSGsfTime, "startTime");
     addFieldValue        ("0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFTime", OSGsfTime, "stopTime");
     addFieldValue        ("0");
     endExposedFieldDecl  ();

     addEventOutDecl      ("SFTime", "cycleTime");
     addEventOutDecl      ("SFFloat", "fraction_changed");
     addEventOutDecl      ("SFBool", "isActive");
     addEventOutDecl      ("SFTime", "time");
 }
 endProto  ();
 
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

 beginProto("TouchSensor");
 {
     beginExposedFieldDecl("SFBool", OSGsfbool, "enabled");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();

     addEventOutDecl      ("SFVec3f", "hitNormal_changed");
     addEventOutDecl      ("SFVec3f", "hitPoint_changed");
     addEventOutDecl      ("SFVec2f", "hitTexCoord_changed");
     addEventOutDecl      ("SFBool", "isActive");
     addEventOutDecl      ("SFBool", "isOver");
     addEventOutDecl      ("SFTime", "touchTime");
 }
 endProto  ();

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

 beginProto("Transform");
 {
     addEventInDecl       ("MFNode", "addChildren");
     addEventInDecl       ("MFNode", "removeChildren");
     
     beginExposedFieldDecl("SFVec3f", OSGsfVec3f, "center");
     addFieldValue        ("0 0 0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("MFNode", OSGmfNode, "children");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFRotation", OSGsfRotation, "rotation");
     addFieldValue        ("0 0 1  0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec3f", OSGsfVec3f, "scale");
     addFieldValue        ("1 1 1");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFRotation", OSGsfRotation, "scaleOrientation");
     addFieldValue        ("0 0 1  0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec3f", OSGsfVec3f, "translation");
     addFieldValue        ("0 0 0");
     endExposedFieldDecl  ();

     beginFieldDecl       ("SFVec3f", OSGsfVec3f, "bboxCenter");
     addFieldValue        ("0 0 0");
     endFieldDecl         ();

     beginFieldDecl       ("SFVec3f", OSGsfVec3f, "bboxSize");
     addFieldValue        ("-1 -1 -1");
     endFieldDecl         ();
 }
 endProto  ();

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

 beginProto("Viewpoint");
 {
     addEventInDecl       ("SFBool", "set_bind");
     
     beginExposedFieldDecl("SFFloat", OSGsfFloat, "fieldOfView");
     addFieldValue        ("0.785398");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFBool", OSGsfbool, "jump");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFRotation", OSGsfRotation, "orientation");
     addFieldValue        ("0 0 1  0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec3f", OSGsfVec3f, "position");
     addFieldValue        ("0 0 10");
     endExposedFieldDecl  ();

     beginFieldDecl       ("SFString", OSGsfString, "description");
     addFieldValue        ("");
     endFieldDecl         ();

     addEventOutDecl      ("SFTime", "bindTime");
     addEventOutDecl      ("SFBool", "isBound" );
 }
 endProto  ();

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

 beginProto("VisibilitySensor");
 {
     beginExposedFieldDecl("SFVec3f", OSGsfVec3f, "center");
     addFieldValue        ("0 0 0");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFBool", OSGsfbool, "enabled");
     addFieldValue        ("TRUE");
     endExposedFieldDecl  ();

     beginExposedFieldDecl("SFVec3f", OSGsfVec3f, "size");
     addFieldValue        ("0 0 0");
     endExposedFieldDecl  ();

     addEventOutDecl      ("SFTime", "enterTime");
     addEventOutDecl      ("SFTime", "exitTime" );
     addEventOutDecl      ("SFBool", "isActive" );
 }
 endProto  ();

#if 0
PROTO WorldInfo [
  field MFString info  []
  field SFString title ""
] { }
#endif

 beginProto("WorldInfo");
 {
     beginFieldDecl("MFString", OSGmfString, "info");
     endFieldDecl  ();
     
     beginFieldDecl("SFString", OSGsfString, "title");
     addFieldValue("");
     endFieldDecl();
 }
 endProto  ();

 postStandardProtos();
}

NodePtr VRMLFile::getRoot(void)
{
    return _pSceneRootNode;
}

/*-------------------------------------------------------------------------*/
/*                           Member                                        */

void VRMLFile::initIntExtFieldTypeMapper(void)
{
    setIntExtMapping(SFBool::getClassType().getId(),
                     ScanParseSkel::OSGsfbool);

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
    setExtIntMapping(ScanParseSkel::OSGsfbool, 
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
        returnValue = findFCByName(szName, _pSceneRootNode);

        if(returnValue == NullFC && _pLightRoot != NullFC)
        {
            returnValue = findFCByName(szName, _pLightRoot);
        }
    }
    
    return returnValue;
}

void VRMLFile::setContainerFieldValue(const FieldContainerPtr &pFC)
{
    if(_pCurrentField != NULL  &&        
        pFC           != NullFC)
    {
        if(_pCurrentFC   !=   NullFC                        && 
           _pCurrentField == _pCurrentFC->getField("children"))
        {
#ifdef OSG_DEBUG_VRML
            indentLog(VRMLNodeDesc::getIndent(), PINFO);
            PINFO << "Add Child "
                  << &(*_pCurrentFC)
                  << " "
                  << &(*pFC)
                  << endl;
#endif
            NodePtr pNode      = NodePtr::dcast(_pCurrentFC);
            NodePtr pChildNode = NodePtr::dcast(pFC);
            
            pNode->addChild(pChildNode);
        }
        else if(_pCurrentFC   !=   NullFC && 
                _pCurrentField == _pCurrentFC->getField("core"))
        {
#ifdef OSG_DEBUG_VRML
            indentLog(VRMLNodeDesc::getIndent(), PINFO);
            PINFO << "Add Core "
                  << &(*_pCurrentFC)
                  << " "
                  << &(*pFC)
                  << endl;
#endif

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







































