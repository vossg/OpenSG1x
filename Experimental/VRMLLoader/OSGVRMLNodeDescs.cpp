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

#define OSG_COMPILEVRMLNODEDESCINST
#define OSG_COMPILESYSTEMLIB
        
#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include "OSGVRMLNodeDescs.h"
#include <OSGLog.h>

#include <OSGNode.h>
#include <OSGNodeCore.h>
#include <OSGGroup.h>
#include <OSGVRMLTransform.h>
#include <OSGGeometry.h>
#include <OSGMaterialGroup.h>
#include <OSGSimpleGeometry.h>
#include <OSGTextureChunk.h>
#include <OSGGeoFunctions.h>
#include <OSGDistanceLOD.h>
#include <OSGSwitch.h>
#include <OSGInline.h>

#include <OSGVRMLFile.h>

#ifndef OSG_LOG_MODULE
#define OSG_LOG_MODULE "VRMLLoader"
#endif

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

DataType FieldDataTraits<GenericAttPtr>::_type("GenericAttPtr"  , true);

#if defined(__sgi)

#pragma instantiate DynFieldAttachment<GenericAttDesc>::_type

#pragma instantiate SField<GenericAttPtr>::_fieldType
#pragma instantiate MField<GenericAttPtr>::_fieldType

#else

OSG_ABSTR_FC_DLLEXPORT_DEF(DynFieldAttachment, 
                           GenericAttDesc, 
                           OSG_SYSTEMLIB_DLLTMPLMAPPING)

OSG_DLLEXPORT_DEF1(SField, GenericAttPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, GenericAttPtr, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
OSG_END_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char   VRMLNodeDesc::cvsid[] = "@(#)$Id: $";

UInt32 VRMLNodeDesc::_uiIndent = 0;

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

UInt32 VRMLNodeDesc::getIndent  (void)
{
    return _uiIndent;
}

void   VRMLNodeDesc::incIndent  (void)
{
    _uiIndent += 4;
}

void   VRMLNodeDesc::decIndent  (void)
{
    if(_uiIndent < 4)
    {
        PWARNING << "Indent smaller 4 decremented" << endl;
        
        _uiIndent = 4;
    }

    _uiIndent -= 4;
}

void   VRMLNodeDesc::resetIndent(void)
{
    _uiIndent = 0;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

Field *VRMLNodeDesc::getField(      FieldContainerPtr  pFC1, 
                                    FieldContainerPtr  pFC2,
                                    GenericAttPtr      pGenAtt,
                              const Char8             *szFieldname)
{
    Field *returnValue = NULL;

    if(szFieldname == NULL)
    {
        return returnValue;
    }

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "VRMLNodeDesc::getField " << endl;

    incIndent();

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "Trying to find field : " << szFieldname << endl;

    if(pFC1 != NullFC)
    {
        returnValue = pFC1->getField(szFieldname);
    }

    incIndent();

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "Got this from node : " << returnValue << endl;

    if(returnValue != NULL)
        return returnValue;

    if(pFC2 != NullFC)
    {
        returnValue = pFC2->getField(szFieldname);

        indentLog(getIndent(), PNOTICE);
        PNOTICE << "Got this from nodecore : " << returnValue << endl;
    }
    else
    {
        indentLog(getIndent(), PNOTICE);
        PNOTICE << "No core to check" << endl;
    }


    if(returnValue != NULL)
        return returnValue;

    if(pGenAtt != GenericAtt::NullPtr)
    {
        returnValue = pGenAtt->getField(szFieldname);
    }

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "Got this from attachment : " << returnValue << endl;

    decIndent();
    decIndent();

    return returnValue;
}

void VRMLNodeDesc::reset(void)
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

VRMLNodeDesc::VRMLNodeDesc(void) :
    _mFieldTypes(),

    _pGenAtt    (),

    _pNodeProto (NullFC),
    _pCurrField (NULL),

    _szCurrentName (),
    _bSaveOnEnd    (false)
{
}

/** \brief Destructor
 */

VRMLNodeDesc::~VRMLNodeDesc(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLNodeDesc::init(const Char8 *szName)
{
    if(szName == NULL)
    {
        _pNodeCoreProto = Group::create();
    }
    else if(stringcasecmp(szName, "Transform") == 0)
    {
        _pNodeCoreProto = VRMLTransform::create();
    }
    else
    {
        _pNodeCoreProto = Group::create();
    }

    _pNodeProto = Node::create();

    _pGenAtt    = GenericAtt::create();
}

void VRMLNodeDesc::setOptions(UInt32 uiOptions)
{
    _uiOptions = uiOptions;
}

void VRMLNodeDesc::setOnEndSave(const Char8 *szName)
{
    _szCurrentName.set(szName);
    _bSaveOnEnd = true;
}

void VRMLNodeDesc::clearOnEndSave(void)
{
    _bSaveOnEnd = false;
}

Bool VRMLNodeDesc::getOnEndSave(void)
{
    return _bSaveOnEnd;
}

const Char8 *VRMLNodeDesc::getSavename(void)
{
    return _szCurrentName.str();
}

FieldContainerPtr VRMLNodeDesc::getSaveFieldContainer(void)
{
    return NullFC;
}

/*---------------------------- properties ---------------------------------*/

Field *VRMLNodeDesc::getField(const Char8 *szFieldname)
{
    return getField(_pNodeProto, _pNodeCoreProto, _pGenAtt, szFieldname);
}
    
void VRMLNodeDesc::getFieldAndDesc(
    FieldContainerPtr        pFC,
    const Char8            * szFieldname,
    Field                  *&pField,
    const FieldDescription *&pDesc)
{
    FieldContainerPtr pTmpFC    = NullFC;
    NodePtr           pNode     = NullNode;
    NodeCorePtr       pNodeCore = NullNodeCore;

    pField = NULL;
    pDesc  = NULL;

    if(pFC == NullFC)
        return;

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "VRMLNodeDesc::getFieldAndDesc : looking for " 
            << szFieldname 
            << endl;

    incIndent();

    pField = pFC->getField(szFieldname);

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "Got this from fieldcontainer : " << pField << endl;

    if(pField != NULL)
    {
        pDesc = pFC->getType().findFieldDescription(szFieldname);
        decIndent();

        return;
    }

    if(pFC->getType().isNode() == true)
    {
        pNode     = NodePtr::dcast(pFC);

        pNodeCore = pNode->getCore();

        if(pNodeCore != NullFC)
        {
            pField    = pNodeCore->getField(szFieldname);
            
            indentLog(getIndent(), PNOTICE);
            PNOTICE << "Got this from nodecore : " << pField << endl;
        }
        
        if(pField != NULL)
        {
            pDesc = pNodeCore->getType().findFieldDescription(szFieldname);
        }        
        else
        {
            pTmpFC = pNode->findAttachment(
                GenericAtt::getClassType().getGroupId());
            
            if(pTmpFC != NullFC)
            {
                pField = pTmpFC->getField(szFieldname);
            }

            indentLog(getIndent(), PNOTICE);
            PNOTICE << "Got this from node attachment : " << pField << endl;

            if(pField == NULL)
            {
                pTmpFC = 
                    pNodeCore->findAttachment(
                        GenericAtt::getClassType().getGroupId());

                if(pTmpFC != NullFC)
                {
                    pField = pTmpFC->getField(szFieldname);
                }

                indentLog(getIndent(), PNOTICE);
                PNOTICE << "Got this from nodecore attachment : " 
                        << pField << endl;
            }

            if(pField != NULL)
            {
                pDesc = pTmpFC->getType().findFieldDescription(szFieldname);
            }        
        }
    }
    else if(pFC->getType().isNodeCore() == true)
    {
        pNodeCore = NodeCorePtr::dcast(pFC);

        pTmpFC = pNodeCore->findAttachment(
            GenericAtt::getClassType().getGroupId());

        if(pTmpFC != NullFC)
        {
            pField = pTmpFC->getField(szFieldname);
        }
        
        if(pField != NULL)
        {
            pDesc = pTmpFC->getType().findFieldDescription(szFieldname);
        }        

        indentLog(getIndent(), PNOTICE);
        PNOTICE << "Got this from nodecore attachment : " 
                << pField << endl;

    }

    decIndent();
}
 
/*-------------------------- your_category---------------------------------*/

Bool VRMLNodeDesc::prototypeAddField(const Char8  *szFieldType,
                                     const UInt32  uiFieldTypeId,
                                     const Char8  *szFieldName)
{
    FieldDescription *pDesc = NULL;
    FieldType        *pType = NULL;
    
    Field *pField = getField(_pNodeProto, 
                             _pNodeCoreProto,
                             _pGenAtt,
                              szFieldName);

    
    indentLog(getIndent(), PNOTICE);
    PNOTICE << "VRMLNodeDesc::prototypeAddField | getField " 
            << szFieldName
            << "  returned : "
            << pField 
            << endl;

    if(pField == NULL)
    {
        pType = FieldFactory::the().getFieldType(uiFieldTypeId);

        if(pType == NULL)
        {
            PWARNING << "VRMLNodeDesc::prototypeAddField "
                     << "Could not get fieldtype " 
                     << uiFieldTypeId << " " 
                     << endl;
            
            return false;
        }
        
        indentLog(getIndent(), PNOTICE);
        PNOTICE << "VRMLNodeDesc::prototypeAddField | got fieldtype : " 
                << uiFieldTypeId
                << " "
                << pType->getName()
                << " " 
                << pType->getId()
                << endl;
        
        pDesc = new FieldDescription(*pType, 
                                     szFieldName, 
                                     0, 0,
                                     false,
                                     (FieldIndexAccessMethod) 
                                     &GenericAtt::getDynamicField);
        
        _pGenAtt->addField(*pDesc);

        _pCurrField = getField(_pNodeProto, 
                               _pNodeCoreProto, 
                               _pGenAtt, 
                                szFieldName);

        delete pDesc;
    
        indentLog(getIndent(), PNOTICE);
        PNOTICE << "VRMLNodeDesc::prototypeAddField | field added : " 
                << szFieldType 
                << " " 
                << uiFieldTypeId
                << " " 
                << szFieldName 
                << " " 
                << _pCurrField
                << endl;
        
        if(_pCurrField != NULL)
            return true;
        else
            return false;
    }
    else
    {
        if((_pGenAtt != GenericAtt::NullPtr        ) &&
           (_pGenAtt->getField(szFieldName) != NULL))
        {
            PWARNING << "VRMLNodeDesc::prototypeAddField | "
                     << "Could not add field " 
                     << szFieldName 
                     << " a second time"
                     << endl;
        }

        return false;
    }
}
    
void VRMLNodeDesc::prototypeAddFieldValue(const Char8 *szFieldVal)
{
    if(_pCurrField       != NULL)
    {
        _pCurrField->pushValueByStr(szFieldVal);
    }
}

void VRMLNodeDesc::endProtoInterface(void)
{
}

Bool VRMLNodeDesc::use(FieldContainerPtr)
{
    return false;
}

/*-------------------------- assignment -----------------------------------*/

FieldContainerPtr VRMLNodeDesc::beginNode(const Char8      *szTypename,
                                          const Char8      *szName,
                                          FieldContainerPtr)
{
    FieldContainerPtr returnValue = OSG::NullNode;
    NodePtr           pNode       = OSG::NullNode;
    NodeCorePtr       pCore       = OSG::NullNodeCore;
    GenericAttPtr     pAtt        = GenericAttPtr::NullPtr;

    if(_pNodeProto != NullFC)
    {
        returnValue = _pNodeProto->shallowCopy();

        if(_pNodeCoreProto != NullFC)
        {
            FieldContainerPtr pCoreClone = _pNodeCoreProto->shallowCopy();

            pNode = NodePtr    ::dcast(returnValue);
            pCore = NodeCorePtr::dcast(pCoreClone );

            pNode->setCore(pCore);
        }

        if(_pGenAtt != NullFC)
        {
            FieldContainerPtr pAttClone = _pGenAtt->emptyCopy();

            pAtt = GenericAttPtr::dcast(pAttClone);

            if(pCore != NullFC)
            {
                pCore->addAttachment(pAtt);
            }
            else
            {
                pNode->addAttachment(pAtt);
            }
        }
    }

    return returnValue;
}
    
void VRMLNodeDesc::endNode(FieldContainerPtr)
{
}

void VRMLNodeDesc::addFieldValue(      Field *pField,
                                    const Char8   *szFieldVal)
{
    if(pField != NULL)
    {
        pField->pushValueByStr(szFieldVal);
    }
}

/** \brief assignment
 */

/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */

/** \brief equal
 */

/** \brief unequal
 */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char VRMLShapeDesc::cvsid[] = "@(#)$Id: $";

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

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

VRMLShapeDesc::VRMLShapeDesc(void) : 
    Inherited     (),
    
    _pMaterialDesc(NULL)
{
}

/** \brief Destructor
 */

VRMLShapeDesc::~VRMLShapeDesc(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLShapeDesc::init(const Char8 *szName)
{
    indentLog(getIndent(), PNOTICE);
    PNOTICE << "ShapeDesc::init : " << szName << endl;

    _pNodeProto = Node::create();

    _pGenAtt    = GenericAtt::create();
}

void VRMLShapeDesc::setMaterialDesc(VRMLMaterialDesc *pMaterialDesc)
{
    _pMaterialDesc = pMaterialDesc;
}

/*---------------------------- properties ---------------------------------*/

Bool VRMLShapeDesc::prototypeAddField(const Char8  *szFieldType,
                                      const UInt32  uiFieldTypeId,
                                      const Char8  *szFieldname)
{
    Bool returnValue = false;

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "VRMLShapeDesc::prototypeAddField | add request : " 
            << szFieldname
            << endl;

    _pCurrField = NULL;

    if(szFieldname == NULL)
        return false;

    incIndent();

    if(stringcasecmp("geometry", szFieldname) == 0)
    {
        _pCurrField = _pNodeProto->getField("children");
        returnValue = true;

        indentLog(getIndent(), PNOTICE);
        PNOTICE << "VRMLShapeDesc::prototypeAddField | request internal : " 
                << szFieldname 
                << " "
                << _pCurrField
                << endl;
    }

    if(stringcasecmp("apperance", szFieldname) == 0)
    {
        _pCurrField = _pNodeProto->getField("core");
        returnValue = true;

        indentLog(getIndent(), PNOTICE);

        PNOTICE << "VRMLShapeDesc::prototypeAddField | request internal : " 
                << szFieldname 
                << " "
                << _pCurrField
                << endl;
    }

    if(_pCurrField == NULL)
    {
        returnValue =  Inherited::prototypeAddField(szFieldType,
                                                    uiFieldTypeId,
                                                    szFieldname);
    }

    decIndent();

    return returnValue;
}
 
void VRMLShapeDesc::getFieldAndDesc(
          FieldContainerPtr   pFC,
    const Char8             * szFieldname,
          Field             *&pField,
    const FieldDescription  *&pDesc)
{
    if(szFieldname == NULL)
        return;

    if(pFC == NullFC)
        return;

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "VRMLShapeDesc::getFieldAndDesc : looking for " 
            << szFieldname 
            << endl;

    incIndent();

    if(stringcasecmp("geometry", szFieldname) == 0)
    {
        indentLog(getIndent(), PNOTICE);
        PNOTICE << "VRMLShapeDesc::getFieldAndDesc : request internal "
                << szFieldname
                << endl;

        pField = pFC->getField("children");
        
        if(pField != NULL)
            pDesc = pFC->getType().findFieldDescription("children");
    }
    else if(stringcasecmp("appearance", szFieldname) == 0)
    {
        indentLog(getIndent(), PNOTICE);
        PNOTICE << "VRMLShapeDesc::getFieldAndDesc : request internal "
                << szFieldname
                << endl;

        pField = pFC->getField("core");
        
        if(pField != NULL)
            pDesc = pFC->getType().findFieldDescription("core");
    }
    else
    {
        VRMLNodeDesc::getFieldAndDesc(pFC, 
                                      szFieldname, 
                                      pField,
                                      pDesc);
    }

    decIndent();
}

/*-------------------------- your_category---------------------------------*/

FieldContainerPtr VRMLShapeDesc::beginNode(const Char8       *szTypename,
                                           const Char8       *szName,
                                                 FieldContainerPtr)
{
    FieldContainerPtr returnValue = NullFC;
    NodePtr           pNode       = NullNode;
    NodePtr           pGeoNode    = NullNode;
    GenericAttPtr     pAtt        = GenericAttPtr::NullPtr;

    if(_pNodeProto != NullNode)
    {
        returnValue = _pNodeProto->shallowCopy();
    }

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "Begin Shape " << &(*pNode) << endl;

    incIndent();

    return returnValue;
}

void VRMLShapeDesc::endNode(FieldContainerPtr pFC)
{

    if(pFC != NullFC)
    {
        NodePtr pNode = NodePtr::dcast(pFC);

        if(pNode != NullFC && pNode->getCore() == NullFC)
        {
            PWARNING << "warning empty material, using default\n" << endl;

            MaterialGroupPtr pMatGroup = MaterialGroup::create();
            beginEditCP(pMatGroup);
            {
                pMatGroup->setMaterial(_pMaterialDesc->getDefaultMaterial());
            }
            endEditCP(pMatGroup);
            beginEditCP(pNode);
            {
                pNode->setCore(pMatGroup);
            }
            endEditCP(pNode);
        }
    }

    decIndent();

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "End Shape " << &(*pFC) << endl;
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */

/** \brief equal
 */

/** \brief unequal
 */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char VRMLGeometryDesc::cvsid[] = "@(#)$Id: $";

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

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

VRMLGeometryDesc::VRMLGeometryDesc(Bool bIsFaceSet) :
    Inherited     (),

    _bIsFaceSet   (bIsFaceSet),

    _bInIndex     (false),
    _uiNumVertices(0),

    _pTypeField   (GeoPTypePtr::NullPtr  ),
    _pLengthField (GeoPLengthPtr::NullPtr)
{
}


/** \brief Destructor
 */

VRMLGeometryDesc::~VRMLGeometryDesc(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLGeometryDesc::init(const Char8 *szName)
{
    indentLog(getIndent(), PNOTICE);
    PNOTICE << "GeoDesc::init : " << szName << endl;

    _pNodeProto     = Node::create();
    _pNodeCoreProto = Geometry::create();

    _pGenAtt = GenericAtt::create();
}

/*---------------------------- properties ---------------------------------*/

Bool VRMLGeometryDesc::prototypeAddField(const Char8  *szFieldType,
                                         const UInt32  uiFieldTypeId,
                                         const Char8  *szFieldname)
{
    Bool bFound = false;

    _pCurrField = NULL;

    if(szFieldname == NULL)
        return false;

    if(stringcasecmp("coord", szFieldname) == 0)
    {
        bFound = true;
    }
    else if(stringcasecmp("normal", szFieldname) == 0)
    {
        bFound = true;
    }
    else if(stringcasecmp("color", szFieldname) == 0)
    {
        bFound = true;
    }
    else if(stringcasecmp("texCoord", szFieldname) == 0)
    {
        bFound = true;
    }

    if(bFound == true)
    {
        indentLog(getIndent(), PNOTICE);
        PNOTICE << "GeoDesc::prototypeAddField : internal " 
                << szFieldname << endl;

        return true;
    }
    else
    {
        return Inherited::prototypeAddField(szFieldType,
                                            uiFieldTypeId,
                                            szFieldname);
    }
}

 
void VRMLGeometryDesc::getFieldAndDesc(
          FieldContainerPtr   pFC,
    const Char8             * szFieldname,
          Field             *&pField,
    const FieldDescription  *&pDesc)
{
    indentLog(getIndent(), PNOTICE);
    PNOTICE << "GeoDesc::getFieldAndDesc : request " 
            << szFieldname 
            << endl;

    if(szFieldname == NULL)
        return;

    if(pFC == NullFC)
        return;

    NodePtr pNode = NodePtr::dcast(pFC);

    if(pNode == NullFC)
    {
        PWARNING << "GeoDesc::getFieldAndDesc : No Node" << endl;
        return;
    }

    NodeCorePtr pNodeCore = pNode->getCore();

    GeometryPtr pGeo      = GeometryPtr::dcast(pNodeCore);

    if(pGeo == NullFC)
    {
        PWARNING << "GeoDesc::getFieldAndDesc : No Geo" << endl;
        return;
    }

    _bInIndex = false;

    if(stringcasecmp("coord", szFieldname) == 0)
    {
        indentLog(getIndent(), PNOTICE);
        PNOTICE << "GeoDesc::getFieldAndDesc : internal " 
                << szFieldname << endl;

        pField = pGeo->getField("positions");
        
        if(pField != NULL)
            pDesc = pGeo->getType().findFieldDescription("positions");
    }
    else if(stringcasecmp("normal", szFieldname) == 0)
    {
        indentLog(getIndent(), PNOTICE);
        PNOTICE << "GeoDesc::getFieldAndDesc : internal " 
                << szFieldname << endl;

        pField = pGeo->getField("normals");
        
        if(pField != NULL)
            pDesc = pGeo->getType().findFieldDescription("normals");
    }
    else if(stringcasecmp("color", szFieldname) == 0)
    {
        indentLog(getIndent(), PNOTICE);
        PNOTICE << "GeoDesc::getFieldAndDesc : internal " 
                << szFieldname << endl;

        pField = pGeo->getField("colors");
        
        if(pField != NULL)
            pDesc = pGeo->getType().findFieldDescription("colors");
    }
    else if(stringcasecmp("texCoord", szFieldname) == 0)
    {
        indentLog(getIndent(), PNOTICE);
        PNOTICE << "GeoDesc::getFieldAndDesc : internal " 
                << szFieldname << endl;

        pField = pGeo->getField("texCoords");
        
        if(pField != NULL)
            pDesc = pGeo->getType().findFieldDescription("texCoords");
    }
    else
    {
        VRMLNodeDesc::getFieldAndDesc(pGeo, 
                                      szFieldname, 
                                      pField,
                                      pDesc);
    }
}

/*-------------------------- your_category---------------------------------*/

FieldContainerPtr VRMLGeometryDesc::beginNode(
    const Char8       *szTypename,
    const Char8       *szName,
    FieldContainerPtr)
{
    FieldContainerPtr pFC         = NullFC;
    NodePtr           pNode       = NullNode;
    NodeCorePtr       pNodeCore   = NullNodeCore;
    GenericAttPtr     pAtt        = GenericAttPtr::NullPtr;

    if(_pNodeProto != NullNode)
    {
        FieldContainerPtr pAttClone = _pGenAtt->clone();
        
        pAtt = GenericAttPtr::dcast(pAttClone);

        pFC = _pNodeProto->shallowCopy();

        pNode = NodePtr::dcast(pFC);

        pFC = _pNodeCoreProto->shallowCopy();

        pNodeCore = NodeCorePtr::dcast(pFC);
       
        pNode    ->setCore      (pNodeCore);
        pNodeCore->addAttachment(pAtt);
    }

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "Begin Geo " << &(*pNode) << endl;

    incIndent();

    return pNode;
}

void VRMLGeometryDesc::endNode(FieldContainerPtr pFC)
{
    NodePtr     pNode = NullNode;
    GeometryPtr pGeo  = GeometryPtr::NullPtr;

    if(pFC == NullFC)
    {
        return;
    }

    pNode = NodePtr::dcast(pFC);
    
    if(pNode == NullFC)
    {
        return;
    }

    pGeo = GeometryPtr::dcast(pNode->getCore());

    if(pGeo == NullFC)
    {
        return;
    }

          Field            *pField = NULL;
    const FieldDescription *pDesc  = NULL;

    MFInt32 *pCoordIndex           = NULL;
    MFInt32 *pNormalIndex          = NULL;
    MFInt32 *pColorIndex           = NULL;
    MFInt32 *pTexCoordIndex        = NULL;
    SFBool  *pConvex               = NULL;
    SFBool  *pCcw                  = NULL;
    SFBool  *pNormalPerVertex      = NULL;
    SFBool  *pColorPerVertex       = NULL;

    Inherited::getFieldAndDesc(pFC, 
                               "coordIndex", 
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pCoordIndex = static_cast<MFInt32 *>(pField);
    }

    Inherited::getFieldAndDesc(pFC, 
                               "normalIndex", 
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pNormalIndex = static_cast<MFInt32 *>(pField);
    }

    Inherited::getFieldAndDesc(pFC, 
                               "colorIndex", 
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pColorIndex = static_cast<MFInt32 *>(pField);
    }

    Inherited::getFieldAndDesc(pFC, 
                               "texCoordIndex", 
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pTexCoordIndex = static_cast<MFInt32 *>(pField);
    }



    Inherited::getFieldAndDesc(pFC, 
                               "convex", 
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pConvex = static_cast<SFBool *>(pField);
    }

    Inherited::getFieldAndDesc(pFC, 
                               "ccw", 
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pCcw = static_cast<SFBool *>(pField);
    }

    Inherited::getFieldAndDesc(pFC, 
                               "normalPerVertex", 
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pNormalPerVertex = static_cast<SFBool *>(pField);
    }

    Inherited::getFieldAndDesc(pFC, 
                               "colorPerVertex", 
                               pField,
                               pDesc);

    if(pField != NULL)
    {
        pColorPerVertex = static_cast<SFBool *>(pField);
    }

    if(_bIsFaceSet == true)
    {
        if(pCoordIndex      != NULL &&
           pNormalIndex     != NULL &&
           pColorIndex      != NULL &&
           pTexCoordIndex   != NULL &&
           pConvex          != NULL &&
           pCcw             != NULL &&
           pNormalPerVertex != NULL &&
           pColorPerVertex  != NULL)
        {
            indentLog(getIndent(), PNOTICE);
            PNOTICE << "Geo create faceset " << &(*pNode) << endl;

            setIndexFromVRMLData(pGeo,
                                 pCoordIndex     ->getValues(),
                                 pNormalIndex    ->getValues(),
                                 pColorIndex     ->getValues(),
                                 pTexCoordIndex  ->getValues(),
                                 pConvex         ->getValue() ,
                                 pCcw            ->getValue() ,
                                 pNormalPerVertex->getValue() ,
                                 pColorPerVertex ->getValue() ,
                                 false, // create normal; not yet :)
                                 true);

            if((0 != (_uiOptions & VRMLFile::CreateNormals) )    &&
               (pGeo->getNormals() == OSG::GeoNormalPtr::NullPtr))
            {
                indentLog(getIndent(), PNOTICE);
                PNOTICE << "Geo create normals " << &(*pNode) << endl;

                OSG::calcVertexNormals(pGeo);
            }

            if(0 != (_uiOptions & VRMLFile::StripeGeometry) ) 
            {
                createOptimizedPrimitives(pGeo, 1, true, true, 8, false);
            }
        }
    }
    else
    {
        vector<Int32> dummyVec;
        Bool          dummyBool = false;

        if(pCoordIndex      != NULL &&
           pColorIndex      != NULL &&
           pColorPerVertex  != NULL)
        {
            indentLog(getIndent(), PNOTICE);
            PNOTICE << "Geo create lineset " << &(*pNode) << endl;
 
            setIndexFromVRMLData(pGeo,
                                 pCoordIndex    ->getValues(),
                                 dummyVec ,
                                 pColorIndex    ->getValues(),
                                 dummyVec ,
                                 dummyBool,
                                 dummyBool,
                                 dummyBool,
                                 pColorPerVertex->getValue() ,
                                 false,  // create normal; not yet :)
                                 false);
        }
    }

    decIndent();

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "End Geo " << &(*pNode) << endl;
}

void VRMLGeometryDesc::addFieldValue(      Field *pField,
                                     const Char8 *szFieldVal)
{
    if(pField != NULL)
    {
        pField->pushValueByStr(szFieldVal);
    }
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */

/** \brief equal
 */

/** \brief unequal
 */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char VRMLGeometryPartDesc::cvsid[] = "@(#)$Id: $";

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

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

VRMLGeometryPartDesc::VRMLGeometryPartDesc(Char8 *szVRMLPartname,
                                           Char8 *szOSGPartname,
                                           Char8 *szOSGProtoname) :
    Inherited(),

    _szVRMLPartname(NULL),
    _szOSGPartname (NULL),
    _szOSGProtoname(NULL)
{
    stringDup(szVRMLPartname, _szVRMLPartname);
    stringDup(szOSGPartname,  _szOSGPartname );
    stringDup(szOSGProtoname, _szOSGProtoname);
}

/** \brief Destructor
 */

VRMLGeometryPartDesc::~VRMLGeometryPartDesc(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLGeometryPartDesc::init(const Char8 *szName)
{
    indentLog(getIndent(), PNOTICE);
    PNOTICE << "GeoPartDesc::init : " 
            << szName << " "
            << _szVRMLPartname << " "
            << _szOSGPartname << " "
            << _szOSGProtoname << " "
            << endl;

    _pNodeProto =
       FieldContainerFactory::the()->createFieldContainer(_szOSGProtoname);

    if(_pNodeProto == NullFC)
    {
        PWARNING << "ERROR no prototype available for " 
                 << _szOSGProtoname 
                 << endl;
    }

    _pGenAtt = GenericAtt::create();
}

/*---------------------------- properties ---------------------------------*/
 
Bool VRMLGeometryPartDesc::prototypeAddField(const Char8  *szFieldType,
                                             const UInt32  uiFieldTypeId,
                                             const Char8  *szFieldname)
{
    Bool bFound;

    _pCurrField = NULL;

    if(stringcasecmp(_szVRMLPartname, szFieldname) == 0)
    {
        indentLog(getIndent(), PNOTICE);
        PNOTICE << "GeoPartDesc::prototypeAddField : add part " 
                << szFieldname
                << endl;

        bFound = true;
    }


    if(bFound == true)
    {
        return true;
    }
    else
    {
        return VRMLNodeDesc::prototypeAddField(szFieldType,
                                               uiFieldTypeId,
                                               szFieldname);
    }
}

void VRMLGeometryPartDesc::getFieldAndDesc(      
          FieldContainerPtr  pFC,
    const Char8            * szFieldname,
          Field            *&pField,
    const FieldDescription *&pDesc)
{
    indentLog(getIndent(), PNOTICE);
    PNOTICE << "VRMLGeometryPartDesc::getFieldAndDesc : looking for " 
            << szFieldname 
            << endl;

    if(szFieldname == NULL)
        return;

    if(pFC == NullFC)
        return;

    incIndent();

    if(stringcasecmp(_szVRMLPartname, szFieldname) == 0)
    {
        indentLog(getIndent(), PNOTICE);
        PNOTICE << "VRMLGeometryPartDesc::getFieldAndDesc : request internal "
                << szFieldname 
                << " return "
                << _szOSGPartname
            
                << endl;

        pField = pFC->getField(_szOSGPartname);
        
        if(pField != NULL)
            pDesc = pFC->getType().findFieldDescription(_szOSGPartname);

        if(pField == NULL)
        {
            PWARNING << "VRMLGeometryPartDesc::getFieldAndDesc : could not"
                     << " map : "
                     << szFieldname
                     << " to "
                     << _szOSGPartname
                     << endl;
        }
    }
    else
    {
        Inherited::getFieldAndDesc(pFC, 
                                   szFieldname, 
                                   pField,
                                   pDesc);
    }

    decIndent();
}

/*-------------------------- your_category---------------------------------*/

FieldContainerPtr VRMLGeometryPartDesc::beginNode(
    const Char8       *szTypename,
    const Char8       *szName,
    FieldContainerPtr)
{
    FieldContainerPtr returnValue = NullFC;

    if(_pNodeProto != NullFC)
        returnValue = _pNodeProto->shallowCopy();

    return returnValue;
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */

/** \brief equal
 */

/** \brief unequal
 */



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char VRMLGeometryObjectDesc::cvsid[] = "@(#)$Id: $";

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

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

VRMLGeometryObjectDesc::VRMLGeometryObjectDesc(Char8 *szVRMLObjectname) :
    Inherited(),

    _szVRMLObjectname(NULL)
{
    stringDup(szVRMLObjectname, _szVRMLObjectname);
}

/** \brief Destructor
 */

VRMLGeometryObjectDesc::~VRMLGeometryObjectDesc(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLGeometryObjectDesc::init(const Char8 *szName)
{
    indentLog(getIndent(), PNOTICE);
    PNOTICE << "GeoObjDesc::init : " 
            << szName << " "
            << _szVRMLObjectname 
            << endl;

    _pNodeProto = Node::create();

    if(_pNodeProto == NullFC)
    {
        PWARNING << "GeoObjDesc::init : no prototype available" << endl;
    }

    _pGenAtt = GenericAtt::create();
}

/*---------------------------- properties ---------------------------------*/
 
Bool VRMLGeometryObjectDesc::prototypeAddField(const Char8  *szFieldType,
                                               const UInt32  uiFieldTypeId,
                                               const Char8  *szFieldname)
{
    _pCurrField = NULL;

    Bool rc = VRMLNodeDesc::prototypeAddField(szFieldType,
                                              uiFieldTypeId,
                                              szFieldname);

    return rc;
}

void VRMLGeometryObjectDesc::getFieldAndDesc(      
          FieldContainerPtr  pFC,
    const Char8            * szFieldname,
          Field            *&pField,
    const FieldDescription *&pDesc)
{
    indentLog(getIndent(), PNOTICE);
    PNOTICE << "VRMLGeometryObjectDesc::getFieldAndDesc : looking for " 
            << szFieldname 
            << endl;

    if(szFieldname == NULL)
        return;

    if(pFC == NullFC)
        return;

    incIndent();

    Inherited::getFieldAndDesc(pFC, 
                               szFieldname, 
                               pField,
                               pDesc);
    
    decIndent();
}

/*-------------------------- your_category---------------------------------*/

FieldContainerPtr VRMLGeometryObjectDesc::beginNode(
    const Char8       *szTypename,
    const Char8       *szName,
    FieldContainerPtr)
{
    FieldContainerPtr returnValue = NullFC;
    NodePtr           pNode       = NullNode;
    GenericAttPtr     pAtt        = GenericAttPtr::NullPtr;

    if(_pNodeProto != NullFC)
    {
        FieldContainerPtr pAttClone = _pGenAtt->clone();
        
        pAtt = GenericAttPtr::dcast(pAttClone);

        returnValue = _pNodeProto->shallowCopy();

        pNode = NodePtr::dcast(returnValue);

        pNode->addAttachment(pAtt);
    }

    return returnValue;
}

void VRMLGeometryObjectDesc::endNode(FieldContainerPtr pFC)
{
          Field            *pField = NULL;
    const FieldDescription *pDesc  = NULL;
          NodePtr           pNode  = NullNode;

    if(pFC == NullFC)
        return;

    pNode = NodePtr::dcast(pFC);

    if(pNode == NullFC)
        return;
    
    if(     stringcasecmp("Box",      _szVRMLObjectname) == 0)
    {
        Inherited::getFieldAndDesc(pFC, 
                                   "size", 
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            SFVec3f *pVec = static_cast<SFVec3f *>(pField);

            indentLog(getIndent(), PNOTICE);
            PNOTICE << "VRMLGeometryObjectDesc::endNode : Create box"
                    << endl;

            GeometryPtr pGeo = makeBoxGeo(pVec->getValue()[0],
                                          pVec->getValue()[1],
                                          pVec->getValue()[2],
                                          2, 2, 2);

            pNode->setCore(pGeo);
        }
    }
    else if(stringcasecmp("Cone",     _szVRMLObjectname) == 0)
    {
        SFReal32 *pBotRad = NULL;
        SFReal32 *pHeight = NULL;
        SFBool   *pSide   = NULL;
        SFBool   *pBottom = NULL;
            
        Inherited::getFieldAndDesc(pFC, 
                                   "bottomRadius", 
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            pBotRad = static_cast<SFReal32 *>(pField);
        }

        Inherited::getFieldAndDesc(pFC, 
                                   "height", 
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            pHeight = static_cast<SFReal32 *>(pField);
        }

        Inherited::getFieldAndDesc(pFC, 
                                   "side", 
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            pSide = static_cast<SFBool *>(pField);
        }

        Inherited::getFieldAndDesc(pFC, 
                                   "bottom", 
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            pBottom = static_cast<SFBool *>(pField);
        }

        if(pBotRad != NULL &&
           pHeight != NULL &&
           pSide   != NULL &&
           pBottom != NULL)
        {
            indentLog(getIndent(), PNOTICE);
            PNOTICE << "VRMLGeometryObjectDesc::endNode : Create cone"
                    << endl;

            GeometryPtr pGeo = makeConeGeo(pHeight->getValue(),
                                           pBotRad->getValue(),
                                           32,
                                           pHeight->getValue(),
                                           pBottom->getValue());

            pNode->setCore(pGeo);
        }
    }
    else if(stringcasecmp("Cylinder", _szVRMLObjectname) == 0)
    {
        SFBool   *pBottom = NULL;
        SFReal32 *pHeight = NULL;
        SFReal32 *pRadius = NULL;
        SFBool   *pSide   = NULL;
        SFBool   *pTop    = NULL;

        Inherited::getFieldAndDesc(pFC, 
                                   "bottom", 
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            pBottom = static_cast<SFBool *>(pField);
        }

        Inherited::getFieldAndDesc(pFC, 
                                   "height", 
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            pHeight = static_cast<SFReal32 *>(pField);
        }

        Inherited::getFieldAndDesc(pFC, 
                                   "radius", 
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            pRadius = static_cast<SFReal32 *>(pField);
        }

        Inherited::getFieldAndDesc(pFC, 
                                   "side", 
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            pSide = static_cast<SFBool *>(pField);
        }

        Inherited::getFieldAndDesc(pFC, 
                                   "top", 
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            pTop = static_cast<SFBool *>(pField);
        }


        if(pBottom != NULL &&
           pHeight != NULL &&
           pRadius != NULL &&
           pSide   != NULL &&
           pTop    != NULL)
        {
            indentLog(getIndent(), PNOTICE);
            PNOTICE << "VRMLGeometryObjectDesc::endNode : Create cylinder"
                    << endl;

            GeometryPtr pGeo = makeCylinderGeo(pHeight->getValue(),
                                               pRadius->getValue(),
                                               32,
                                               pSide  ->getValue(),
                                               pTop   ->getValue(),
                                               pBottom->getValue());

            pNode->setCore(pGeo);
        }
    }
    else if(stringcasecmp("Sphere",   _szVRMLObjectname) == 0)
    {
        Inherited::getFieldAndDesc(pFC, 
                                   "radius", 
                                   pField,
                                   pDesc);

        if(pField != NULL)
        {
            SFReal32 *pValue = static_cast<SFReal32 *>(pField);
            
            indentLog(getIndent(), PNOTICE);
            PNOTICE << "VRMLGeometryObjectDesc::endNode : Create sphere"
                    << endl;

            GeometryPtr pGeo = makeSphereGeo(3, pValue->getValue());

            pNode->setCore(pGeo);
        }
        
    }
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */

/** \brief equal
 */

/** \brief unequal
 */






//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char VRMLAppearanceDesc::cvsid[] = "@(#)$Id: $";

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

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

VRMLAppearanceDesc::VRMLAppearanceDesc(void) :
    Inherited         (),

    _sfTexture        (),
    _pMaterialDesc    (NULL)
{
}

/** \brief Destructor
 */

VRMLAppearanceDesc::~VRMLAppearanceDesc(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLAppearanceDesc::init(const Char8 *szName)
{
    indentLog(getIndent(), PNOTICE);
    PNOTICE << "ApperanceDesc::init : " << szName << endl;

    _pNodeCoreProto = MaterialGroup::create();

    _pGenAtt    = GenericAtt::create();
}

void VRMLAppearanceDesc::setMaterialDesc(VRMLMaterialDesc *pMaterialDesc)
{
    _pMaterialDesc = pMaterialDesc;
}

FieldContainerPtr VRMLAppearanceDesc::getSaveFieldContainer(void)
{
    return NullFC;
}

/*---------------------------- properties ---------------------------------*/
 
Bool VRMLAppearanceDesc::prototypeAddField(const Char8  *szFieldType,
                                           const UInt32  uiFieldTypeId,
                                           const Char8  *szFieldname)
{
    _pCurrField = NULL;

    if(szFieldname == NULL)
        return false;

    if(stringcasecmp("material", szFieldname) == 0)
    {
        return true;
    }
    else if(stringcasecmp("texture", szFieldname) == 0)
    {
        return true;
    }
    else
    {
        return VRMLNodeDesc::prototypeAddField(szFieldType,
                                               uiFieldTypeId,
                                               szFieldname);
    }
}

void VRMLAppearanceDesc::getFieldAndDesc(      
          FieldContainerPtr  pFC,
    const Char8            * szFieldname,
          Field            *&pField,
    const FieldDescription *&pDesc)
{

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "VRMLAppearanceDesc::getFieldAndDesc : looking for " 
            << szFieldname 
            << endl;

    if(pFC == NullFC)
        return;

    if(szFieldname == NULL)
        return;

    incIndent();

    if(stringcasecmp("material", szFieldname) == 0)
    {
        indentLog(getIndent(), PNOTICE);
        PNOTICE << "VRMLAppearanceDesc::getFieldAndDesc : request internal "
                << szFieldname
                << endl;
        
        pField = pFC->getField("material");
        
        if(pField != NULL)
            pDesc = pFC->getType().findFieldDescription("material");
    }
    else if(stringcasecmp("texture", szFieldname) == 0)
    {
        indentLog(getIndent(), PNOTICE);
        PNOTICE << "VRMLAppearanceDesc::getFieldAndDesc : request internal "
                << szFieldname
                << endl;

        _sfTexture.setValue(NullFC);

        pField = &_sfTexture;
        pDesc  = NULL;
    }
    else
    {
        Inherited::getFieldAndDesc(pFC, 
                                   szFieldname, 
                                   pField,
                                   pDesc);
    }

    decIndent();
}

/*-------------------------- your_category---------------------------------*/

FieldContainerPtr VRMLAppearanceDesc::beginNode(
    const Char8       *szTypename,
    const Char8       *szName,
    FieldContainerPtr  pCurrentFC)
{
    FieldContainerPtr returnValue = NullFC;
    NodeCorePtr       pNodeCore   = NullNodeCore;
    GenericAttPtr     pAtt        = GenericAttPtr::NullPtr;

    if(_pNodeCoreProto != NullFC)
    {
        FieldContainerPtr pAttClone = _pGenAtt->clone();
        
        pAtt = GenericAttPtr::dcast(pAttClone);

        returnValue = _pNodeCoreProto->shallowCopy();

        pNodeCore   = NodeCorePtr::dcast(returnValue);

        pNodeCore->addAttachment(pAtt);
    }    

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "Begin Appearance " << &(*pNodeCore) << endl;

    incIndent();

    return returnValue;
}

void VRMLAppearanceDesc::endNode(FieldContainerPtr pFC)
{
    if(pFC != NullFC)
    {
        MaterialGroupPtr pMatGroup = MaterialGroupPtr::dcast(pFC);

        if(pMatGroup != NullFC)
        {
            ChunkMaterialPtr pChunkMat = 
                ChunkMaterialPtr::dcast(pMatGroup->getMaterial());

            TextureChunkPtr pTexture = 
                TextureChunkPtr::dcast(_sfTexture.getValue());

            if(pChunkMat != NullFC)
            {
                if(pTexture != NullFC)
                {                    
                    beginEditCP(pChunkMat);
                    {
                        pChunkMat->addChunk(pTexture);
                    }
                    endEditCP(pChunkMat);
                }
            }
            else
            {
                if(pTexture != NullFC)
                {     
                    FieldContainerPtr pMat = 
                        _pMaterialDesc->getDefaultMaterial()->shallowCopy();

                    ChunkMaterialPtr pChunkMat = 
                        ChunkMaterialPtr::dcast(pMat);

                    if(pChunkMat != NullFC)
                    {
                        if(pTexture != NullFC)
                        {                    
                            beginEditCP(pChunkMat);
                            {
                                pChunkMat->addChunk(pTexture);
                            }
                            endEditCP(pChunkMat);
                        }

                        beginEditCP(pMatGroup);
                        {
                            pMatGroup->setMaterial(pChunkMat);
                        }
                        endEditCP(pMatGroup);
                    }
                }
                else
                {
                    PWARNING << "No material, adding default" << endl;
                    beginEditCP(pMatGroup);
                    {
                        pMatGroup->setMaterial(
                              _pMaterialDesc->getDefaultMaterial());
                    }
                    endEditCP(pMatGroup);
                }
            }
        }
    }

    decIndent();

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "End Appearance " <<  &(*(_sfTexture.getValue())) << endl;
}

Bool VRMLAppearanceDesc::use(FieldContainerPtr pFC)
{
    return false;
}


/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */

/** \brief equal
 */

/** \brief unequal
 */



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char VRMLMaterialDesc::cvsid[] = "@(#)$Id: $";

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

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

VRMLMaterialDesc::VRMLMaterialDesc(void) :
    Inherited(),

    _defaultAmbientIntensity(),
    _defaultDiffuseColor    (),
    _defaultEmissiveColor   (),
    _defaultShininess       (),
    _defaultSpecularColor   (),
    _defaultTransparency    (),

    _ambientIntensity       (),
    _diffuseColor           (),
    _emissiveColor          (),
    _shininess              (),
    _specularColor          (),
    _transparency           (),

    _pDefMat                (),
    _pMat                   ()
{
}

/** \brief Destructor
 */

VRMLMaterialDesc::~VRMLMaterialDesc(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLMaterialDesc::init(const Char8 *szName)
{
    indentLog(getIndent(), PNOTICE);
    PNOTICE << "MaterialDesc::init : " << szName << endl;
}

void VRMLMaterialDesc::reset(void)
{
    _pMat = SimpleMaterial::NullPtr;

    _ambientIntensity.setValue(_defaultAmbientIntensity);
    _diffuseColor    .setValue(_defaultDiffuseColor);
    _emissiveColor   .setValue(_defaultEmissiveColor);
    _shininess       .setValue(_defaultShininess);
    _specularColor   .setValue(_defaultSpecularColor);
    _transparency    .setValue(_defaultTransparency);
}

MaterialPtr VRMLMaterialDesc::getDefaultMaterial(void)
{
    return _pDefMat;
}

/*---------------------------- properties ---------------------------------*/
 
Bool VRMLMaterialDesc::prototypeAddField(const Char8  *szFieldType,
                                         const UInt32  uiFieldTypeId,
                                         const Char8  *szFieldname)
{
    Bool bFound;

    _pCurrField = NULL;

    if(stringcasecmp("ambientIntensity", szFieldname) == 0)
    {
        _pCurrField = &_defaultAmbientIntensity;

        bFound = true;
    }
    else if(stringcasecmp("diffuseColor", szFieldname) == 0)
    {
        _pCurrField = &_defaultDiffuseColor;

        bFound = true;
    }
    else if(stringcasecmp("emissiveColor", szFieldname) == 0)
    {
        _pCurrField = &_defaultEmissiveColor;

        bFound = true;
    }
    else if(stringcasecmp("shininess", szFieldname) == 0)
    {
        _pCurrField = &_defaultShininess;

        bFound = true;
    }
    else if(stringcasecmp("specularColor", szFieldname) == 0)
    {
        _pCurrField = &_defaultSpecularColor;

        bFound = true;
    }
    else if(stringcasecmp("transparency", szFieldname) == 0)
    {
        _pCurrField = &_defaultTransparency;

        bFound = true;
    }

    if(bFound == true)
    {
        indentLog(getIndent(), PNOTICE);
        PNOTICE << "MaterialDesc::prototypeAddField : add part " 
                << szFieldname
                << endl;
        return true;
    }
    else
    {
        return false;
    }
}

void VRMLMaterialDesc::endProtoInterface(void)
{
    Color3f cAmbient;
    
    cAmbient.setValuesRGB(_defaultDiffuseColor    .getValue().red() *
                          _defaultAmbientIntensity.getValue(),
                          _defaultDiffuseColor    .getValue().green() *
                          _defaultAmbientIntensity.getValue(),
                          _defaultDiffuseColor    .getValue().blue() *
                          _defaultAmbientIntensity.getValue());
    
    _pDefMat = SimpleMaterial::create();

    _pDefMat->setAmbient     ( cAmbient                       );
    _pDefMat->setDiffuse     (_defaultDiffuseColor.getValue() );
    _pDefMat->setSpecular    (_defaultSpecularColor.getValue());
    _pDefMat->setShininess   (_defaultShininess.getValue()    );
    _pDefMat->setEmission    (_defaultEmissiveColor.getValue());
    _pDefMat->setTransparency(_defaultTransparency.getValue() );
}

void VRMLMaterialDesc::getFieldAndDesc(      
          FieldContainerPtr  pFC,
    const Char8            * szFieldname,
          Field            *&pField,
    const FieldDescription *&pDesc)
{
    if(stringcasecmp("ambientIntensity", szFieldname) == 0)
    {
        pField = &_ambientIntensity;
    }
    else if(stringcasecmp("diffuseColor", szFieldname) == 0)
    {
        pField = &_diffuseColor;
    }
    else if(stringcasecmp("emissiveColor", szFieldname) == 0)
    {
        pField = &_emissiveColor;
    }
    else if(stringcasecmp("shininess", szFieldname) == 0)
    {
        pField = &_shininess;
    }
    else if(stringcasecmp("specularColor", szFieldname) == 0)
    {
        pField = &_specularColor;
    }
    else if(stringcasecmp("transparency", szFieldname) == 0)
    {
        pField = &_transparency;
    }

    pDesc = NULL;
}

/*-------------------------- your_category---------------------------------*/

FieldContainerPtr VRMLMaterialDesc::beginNode(
    const Char8       *,
    const Char8       *,
    FieldContainerPtr  pCurrentFC)
{
    reset();

    _pMat = SimpleMaterial::create();

    return _pMat;
}

void VRMLMaterialDesc::endNode(FieldContainerPtr)
{    
    if(_pMat != NullFC)
    {
        Color3f cAmbient;

        cAmbient.setValuesRGB(_diffuseColor    .getValue().red() *
                              _ambientIntensity.getValue(),
                              _diffuseColor    .getValue().green() *
                              _ambientIntensity.getValue(),
                              _diffuseColor    .getValue().blue() *
                              _ambientIntensity.getValue());
        beginEditCP(_pMat);
        _pMat->setAmbient     ( cAmbient                );
        _pMat->setDiffuse     (_diffuseColor.getValue() );
        _pMat->setSpecular    (_specularColor.getValue());
        _pMat->setShininess   (_shininess.getValue()    );
        _pMat->setEmission    (_emissiveColor.getValue());
        _pMat->setTransparency(_transparency.getValue() );
        endEditCP(_pMat);
    }
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */

/** \brief equal
 */

/** \brief unequal
 */





//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char VRMLImageTextureDesc::cvsid[] = "@(#)$Id: $";

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

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

VRMLImageTextureDesc::VRMLImageTextureDesc(void) :
    Inherited(),

    _defaultURL    (),
    _defaultRepeatS(),
    _defaultRepeatT(),

    _url           (),
    _repeatS       (),
    _repeatT       ()
{
}

/** \brief Destructor
 */

VRMLImageTextureDesc::~VRMLImageTextureDesc(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLImageTextureDesc::init(const Char8 *szName)
{
    indentLog(getIndent(), PNOTICE);
    PNOTICE << "ImageTextureDesc::init : " << szName << endl;
}

void VRMLImageTextureDesc::reset(void)
{
}

/*---------------------------- properties ---------------------------------*/
 
Bool VRMLImageTextureDesc::prototypeAddField(const Char8  *szFieldType,
                                             const UInt32  uiFieldTypeId,
                                             const Char8  *szFieldname)
{
    Bool bFound;

    _pCurrField = NULL;

    if(stringcasecmp("url", szFieldname) == 0)
    {
        _pCurrField = &_defaultURL;

        bFound = true;
    }
    else if(stringcasecmp("repeatS", szFieldname) == 0)
    {
        _pCurrField = &_defaultRepeatS;

        bFound = true;
    }
    else if(stringcasecmp("repeatT", szFieldname) == 0)
    {
        _pCurrField = &_defaultRepeatT;

        bFound = true;
    }

    if(bFound == true)
    {
        indentLog(getIndent(), PNOTICE);
        PNOTICE << "ImageTextureDesc::prototypeAddField : add part " 
                << szFieldname
                << endl;

        return true;
    }
    else
    {
        return false;
    }
}

void VRMLImageTextureDesc::endProtoInterface(void)
{
}

void VRMLImageTextureDesc::getFieldAndDesc(      
          FieldContainerPtr  pFC,
    const Char8            * szFieldname,
          Field            *&pField,
    const FieldDescription *&pDesc)
{
    if(stringcasecmp("url", szFieldname) == 0)
    {
        pField = &_url;
    }
    else if(stringcasecmp("repeatS", szFieldname) == 0)
    {
        pField = &_repeatS;
    }
    else if(stringcasecmp("repeatT", szFieldname) == 0)
    {
        pField = &_repeatT;
    }

    pDesc = NULL;
}

/*-------------------------- your_category---------------------------------*/

FieldContainerPtr VRMLImageTextureDesc::beginNode(
    const Char8       *,
    const Char8       *,
    FieldContainerPtr  pCurrentFC)
{
    TextureChunkPtr returnValue = TextureChunk::create();

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "Begin ImageTexture " << &(*returnValue) << endl;

    incIndent();

    _url.clear();

    _repeatS = _defaultRepeatS;
    _repeatT = _defaultRepeatT;

    return returnValue;
}

void VRMLImageTextureDesc::endNode(FieldContainerPtr pFC)
{    
    TextureChunkPtr  pTexture = TextureChunkPtr::NullPtr;

    Image           *pImage   = new Image();

    pTexture = TextureChunkPtr::dcast(pFC);

    if(pTexture != NullFC)
    {
        PNOTICE << "VRMLImageTextureDesc::endNode : Reading texture " 
                << _url.getValue(0).str() << endl;
        
        if(pImage->read(_url.getValue(0).str()))
        {
            beginEditCP(pTexture);
            pTexture->setImage(pImage);
            
            if(_repeatS.getValue() == true)
            {
                pTexture->setWrapS(GL_REPEAT);
            }
            else
            {
                pTexture->setWrapS(GL_CLAMP);
            }

            if(_repeatT.getValue() == true)
            {
                pTexture->setWrapT(GL_REPEAT);
            }
            else
            {
                 pTexture->setWrapS(GL_CLAMP);
            }
            endEditCP(pTexture);
        }
        else
        {
            PWARNING << "VRMLImageTextureDesc::endNode : "
                     << "Couldn't read texture " 
                     << _url.getValue(0).str()  
                     << " !!!" 
                     << endl;
            
            delete pImage;
        }
    }
    else
    {
        PWARNING <<  "VRMLImageTextureDesc::endNode : Invalid texture ptr"
                 << endl;
    }

    decIndent();

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "End ImageTexture " 
            << _url.getValue(0).str() << " "
            << _repeatS.getValue()    << " "
            << _repeatT.getValue()    << " "
            << &(*pFC) << endl;
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */

/** \brief equal
 */

/** \brief unequal
 */



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char VRMLPixelTextureDesc::cvsid[] = "@(#)$Id: $";

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

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

VRMLPixelTextureDesc::VRMLPixelTextureDesc(void) :
    Inherited(),

    _defaultImage  (),
    _defaultRepeatS(),
    _defaultRepeatT(),

    _image         (),
    _repeatS       (),
    _repeatT       ()
{
}

/** \brief Destructor
 */

VRMLPixelTextureDesc::~VRMLPixelTextureDesc(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLPixelTextureDesc::init(const Char8 *szName)
{
    indentLog(getIndent(), PNOTICE);
    PNOTICE << "PixelTextureDesc::init : " << szName << endl;
}

void VRMLPixelTextureDesc::reset(void)
{
}

/*---------------------------- properties ---------------------------------*/
 
Bool VRMLPixelTextureDesc::prototypeAddField(const Char8  *szFieldType,
                                             const UInt32  uiFieldTypeId,
                                             const Char8  *szFieldname)
{
    Bool bFound;

    _pCurrField = NULL;

    if(stringcasecmp("image", szFieldname) == 0)
    {
        _pCurrField = &_defaultImage;

        bFound = true;
    }
    else if(stringcasecmp("repeatS", szFieldname) == 0)
    {
        _pCurrField = &_defaultRepeatS;

        bFound = true;
    }
    else if(stringcasecmp("repeatT", szFieldname) == 0)
    {
        _pCurrField = &_defaultRepeatT;

        bFound = true;
    }

    if(bFound == true)
    {
        indentLog(getIndent(), PNOTICE);
        PNOTICE << "PixelTextureDesc::prototypeAddField : add part " 
                << szFieldname
                << endl;

        return true;
    }
    else
    {
        return false;
    }
}

void VRMLPixelTextureDesc::endProtoInterface(void)
{
}

void VRMLPixelTextureDesc::getFieldAndDesc(      
          FieldContainerPtr  pFC,
    const Char8            * szFieldname,
          Field            *&pField,
    const FieldDescription *&pDesc)
{
    if(stringcasecmp("image", szFieldname) == 0)
    {
        pField = &_image;
    }
    else if(stringcasecmp("repeatS", szFieldname) == 0)
    {
        pField = &_repeatS;
    }
    else if(stringcasecmp("repeatT", szFieldname) == 0)
    {
        pField = &_repeatT;
    }

    pDesc = NULL;
}

/*-------------------------- your_category---------------------------------*/

FieldContainerPtr VRMLPixelTextureDesc::beginNode(
    const Char8       *,
    const Char8       *,
    FieldContainerPtr  pCurrentFC)
{
    TextureChunkPtr returnValue = TextureChunk::create();

    _image.setValue(new Image());

    _repeatS = _defaultRepeatS;
    _repeatT = _defaultRepeatT;

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "Begin PixelTexture " << &(*returnValue) << endl;

    incIndent();

    return returnValue;
}

void VRMLPixelTextureDesc::endNode(FieldContainerPtr pFC)
{    
    TextureChunkPtr  pTexture = TextureChunkPtr::NullPtr;

    pTexture = TextureChunkPtr::dcast(pFC);

    if(pTexture != NullFC)
    {
        if(_image.getValue() != NULL)
        {
            pTexture->setImage(_image.getValue());
            
            if(_repeatS.getValue() == true)
            {
                pTexture->setWrapS(GL_REPEAT);
            }
            else
            {
                pTexture->setWrapS(GL_CLAMP);
            }

            if(_repeatT.getValue() == true)
            {
                pTexture->setWrapT(GL_REPEAT);
            }
            else
            {
                pTexture->setWrapS(GL_CLAMP);
            }
        }
    }
    else
    {
        PWARNING <<  "VRMLPixelTextureDesc::endNode : Invalid texture ptr"
                 << endl;
    }

    decIndent();

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "End PixelTexture " 
            << _repeatS.getValue()    << " "
            << _repeatT.getValue()    << " "
            << &(*pFC) << endl;
}

void VRMLPixelTextureDesc::addFieldValue(      Field *,
                                         const Char8 *szFieldVal)
{
    if(_image.getValue() != NULL)
    {
        _image.getValue()->addValue(szFieldVal);
    }
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */

/** \brief equal
 */

/** \brief unequal
 */



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char VRMLLODDesc::cvsid[] = "@(#)$Id: $";

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

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

VRMLLODDesc::VRMLLODDesc(void) :
    Inherited()
{
}

/** \brief Destructor
 */

VRMLLODDesc::~VRMLLODDesc(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLLODDesc::init(const Char8 *szName)
{
    indentLog(getIndent(), PNOTICE);
    PNOTICE << "LODDesc::init : " << szName << endl;

    _pNodeProto     = Node::create();
    _pNodeCoreProto = DistanceLOD::create();

    _pGenAtt        = GenericAtt::create();
}

/*---------------------------- properties ---------------------------------*/
 
Bool VRMLLODDesc::prototypeAddField(const Char8  *szFieldType,
                                    const UInt32  uiFieldTypeId,
                                    const Char8  *szFieldname)
{
    Bool bFound;

    _pCurrField = NULL;

    if(stringcasecmp("level", szFieldname) == 0)
    {
        bFound = true;
    }
    else if(stringcasecmp("center", szFieldname) == 0)
    {
        bFound = true;
    }
    else if(stringcasecmp("range", szFieldname) == 0)
    {
        bFound = true;
    }

    if(bFound == true)
    {
        return true;
    }
    else
    {
        return Inherited::prototypeAddField(szFieldType,
                                            uiFieldTypeId,
                                            szFieldname);
    }
}

void VRMLLODDesc::endProtoInterface(void)
{
}

void VRMLLODDesc::getFieldAndDesc(      
          FieldContainerPtr  pFC,
    const Char8            * szFieldname,
          Field            *&pField,
    const FieldDescription *&pDesc)
{
    if(szFieldname == NULL)
        return;

    if(pFC == NullFC)
        return;

    NodePtr pNode = NodePtr::dcast(pFC);

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "VRMLShapeDesc::getFieldAndDesc : looking for " 
            << szFieldname 
            << endl;

    if(pNode == NullFC)
    {
        PWARNING <<  "VRMLLODDesc::getFieldAndDesc : No Node" << endl;
        return;
    }

    NodeCorePtr pNodeCore = pNode->getCore();

    DistanceLODPtr pLOD      = DistanceLODPtr::dcast(pNodeCore);

    if(pLOD == NullFC)
    {
        PWARNING <<  "VRMLLODDesc::getFieldAndDesc : No LOD" << endl;
        return;
    }

    incIndent();

    if(stringcasecmp("level", szFieldname) == 0)
    {
        indentLog(getIndent(), PNOTICE);
        PNOTICE << "VRMLLODDesc::getFieldAndDesc :  : request internal "
                << szFieldname
                << endl;

        pField = pNode->getField("children");
        
        if(pField != NULL)
            pDesc = pNode->getType().findFieldDescription("children");
    }
    else if(stringcasecmp("center", szFieldname) == 0)
    {
        indentLog(getIndent(), PNOTICE);
        PNOTICE << "VRMLLODDesc::getFieldAndDesc :  : request internal "
                << szFieldname
                << endl;

        pField = pLOD->getField("center");
        
        if(pField != NULL)
            pDesc = pLOD->getType().findFieldDescription("children");
    }
    else if(stringcasecmp("range", szFieldname) == 0)
    {
        indentLog(getIndent(), PNOTICE);
        PNOTICE << "VRMLLODDesc::getFieldAndDesc :  : request internal "
                << szFieldname
                << endl;

        pField = pLOD->getField("range");
        
        if(pField != NULL)
            pDesc = pLOD->getType().findFieldDescription("range");
    }
    else
    {
        VRMLNodeDesc::getFieldAndDesc(pLOD, 
                                      szFieldname, 
                                      pField,
                                      pDesc);
    }

    decIndent();
}

/*-------------------------- your_category---------------------------------*/

FieldContainerPtr VRMLLODDesc::beginNode(
    const Char8       *,
    const Char8       *,
    FieldContainerPtr  pCurrentFC)
{
    FieldContainerPtr pFC         = NullFC;
    NodePtr           pNode       = NullNode;
    NodeCorePtr       pNodeCore   = NullNodeCore;
    GenericAttPtr     pAtt        = GenericAttPtr::NullPtr;

    if(_pNodeProto != NullNode)
    {
        FieldContainerPtr pAttClone = _pGenAtt->emptyCopy();
        
        pAtt = GenericAttPtr::dcast(pAttClone);

        pFC = _pNodeProto->shallowCopy();

        pNode = NodePtr::dcast(pFC);

        pFC = _pNodeCoreProto->shallowCopy();

        pNodeCore = NodeCorePtr::dcast(pFC);
       
        pNode    ->setCore      (pNodeCore);
        pNodeCore->addAttachment(pAtt);
    }

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "Begin LOD " << &(*pNode) << endl;

    incIndent();

    return pNode;
}

void VRMLLODDesc::endNode(FieldContainerPtr pFC)
{    
    decIndent();

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "End LOD " 
            << &(*pFC) << endl;
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */

/** \brief equal
 */

/** \brief unequal
 */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char VRMLSwitchDesc::cvsid[] = "@(#)$Id: $";

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

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

VRMLSwitchDesc::VRMLSwitchDesc(void) :
    Inherited()
{
}

/** \brief Destructor
 */

VRMLSwitchDesc::~VRMLSwitchDesc(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLSwitchDesc::init(const Char8 *szName)
{
    indentLog(getIndent(), PNOTICE);
    PNOTICE << "SwitchDesc::init : " << szName << endl;

    _pNodeProto     = Node::create();
    _pNodeCoreProto = Switch::create();

    _pGenAtt        = GenericAtt::create();
}

/*---------------------------- properties ---------------------------------*/
 
Bool VRMLSwitchDesc::prototypeAddField(const Char8  *szFieldType,
                                       const UInt32  uiFieldTypeId,
                                       const Char8  *szFieldname)
{
    Bool bFound;

    _pCurrField = NULL;

    if(stringcasecmp("choice", szFieldname) == 0)
    {
        bFound = true;
    }
    else if(stringcasecmp("whichChoice", szFieldname) == 0)
    {
        bFound = true;
    }

    if(bFound == true)
    {
        return true;
    }
    else
    {
        return Inherited::prototypeAddField(szFieldType,
                                            uiFieldTypeId,
                                            szFieldname);
    }
}

void VRMLSwitchDesc::endProtoInterface(void)
{
}

void VRMLSwitchDesc::getFieldAndDesc(      
          FieldContainerPtr  pFC,
    const Char8            * szFieldname,
          Field            *&pField,
    const FieldDescription *&pDesc)
{
    if(szFieldname == NULL)
        return;

    if(pFC == NullFC)
        return;

    NodePtr pNode = NodePtr::dcast(pFC);

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "VRMLShapeDesc::getFieldAndDesc : looking for " 
            << szFieldname 
            << endl;

    if(pNode == NullFC)
    {
        PWARNING << "VRMLSwitchDesc::getFieldAndDesc : No Node" << endl;
        return;
    }

    NodeCorePtr pNodeCore = pNode->getCore();

    SwitchPtr pSwitch      = SwitchPtr::dcast(pNodeCore);

    if(pSwitch == NullFC)
    {
        PWARNING << "VRMLSwitchDesc::getFieldAndDesc : No Switch" << endl;
        return;
    }

    incIndent();

    if(stringcasecmp("choice", szFieldname) == 0)
    {
        indentLog(getIndent(), PNOTICE);
        PNOTICE << "VRMLSwitchDesc::getFieldAndDesc :  : request internal "
                << szFieldname
                << endl;

        pField = pNode->getField("children");
        
        if(pField != NULL)
            pDesc = pNode->getType().findFieldDescription("children");
    }
    else if(stringcasecmp("whichChoice", szFieldname) == 0)
    {
        indentLog(getIndent(), PNOTICE);
        PNOTICE << "VRMLSwitchDesc::getFieldAndDesc :  : request internal "
                << szFieldname
                << endl;

        pField = pSwitch->getField("choice");
        
        if(pField != NULL)
            pDesc = pSwitch->getType().findFieldDescription("whichChoice");
    }
    else
    {
        VRMLNodeDesc::getFieldAndDesc(pSwitch, 
                                      szFieldname, 
                                      pField,
                                      pDesc);
    }

    decIndent();
}

/*-------------------------- your_category---------------------------------*/

FieldContainerPtr VRMLSwitchDesc::beginNode(
    const Char8       *,
    const Char8       *,
    FieldContainerPtr  pCurrentFC)
{
    FieldContainerPtr pFC         = NullFC;
    NodePtr           pNode       = NullNode;
    NodeCorePtr       pNodeCore   = NullNodeCore;
    GenericAttPtr     pAtt        = GenericAttPtr::NullPtr;

    if(_pNodeProto != NullNode)
    {
        FieldContainerPtr pAttClone = _pGenAtt->emptyCopy();
        
        pAtt = GenericAttPtr::dcast(pAttClone);

        pFC = _pNodeProto->shallowCopy();

        pNode = NodePtr::dcast(pFC);

        pFC = _pNodeCoreProto->shallowCopy();

        pNodeCore = NodeCorePtr::dcast(pFC);
       
        pNode    ->setCore      (pNodeCore);
        pNodeCore->addAttachment(pAtt);
    }

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "Begin Switch " << &(*pNode) << endl;

    incIndent();

    return pNode;
}

void VRMLSwitchDesc::endNode(FieldContainerPtr pFC)
{    
    decIndent();

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "End Switch " 
            << &(*pFC) << endl;
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */

/** \brief equal
 */

/** \brief unequal
 */



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char VRMLGroupDesc::cvsid[] = "@(#)$Id: $";

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

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

VRMLGroupDesc::VRMLGroupDesc(void) :
    Inherited(),
    
    _defaultBoxCenter(),
    _defaultBoxSize  (),

    _boxCenter       (),
    _boxSize         ()
{
}

/** \brief Destructor
 */

VRMLGroupDesc::~VRMLGroupDesc(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLGroupDesc::init(const Char8 *szName)
{
    indentLog(getIndent(), PNOTICE);
    PNOTICE << "GroupDesc::init : " << szName << endl;

    _pNodeProto     = Node::create();
    _pNodeCoreProto = Group::create();

    _pGenAtt        = GenericAtt::create();
}

/*---------------------------- properties ---------------------------------*/
 
Bool VRMLGroupDesc::prototypeAddField(const Char8  *szFieldType,
                                      const UInt32  uiFieldTypeId,
                                      const Char8  *szFieldname)
{
    Bool bFound;

    _pCurrField = NULL;

    if(stringcasecmp("bboxCenter", szFieldname) == 0)
    {
        _pCurrField = &_defaultBoxCenter;
        bFound = true;
    }
    else if(stringcasecmp("bboxSize", szFieldname) == 0)
    {
        _pCurrField = &_defaultBoxSize;
        bFound = true;
    }
    else if(stringcasecmp("children", szFieldname) == 0)
    {
        bFound = true;
    }

    if(bFound == true)
    {
        return true;
    }
    else
    {
        return Inherited::prototypeAddField(szFieldType,
                                            uiFieldTypeId,
                                            szFieldname);
    }
}

void VRMLGroupDesc::endProtoInterface(void)
{
}

void VRMLGroupDesc::getFieldAndDesc(      
          FieldContainerPtr  pFC,
    const Char8            * szFieldname,
          Field            *&pField,
    const FieldDescription *&pDesc)
{
    if(szFieldname == NULL)
        return;

    if(pFC == NullFC)
        return;

    NodePtr pNode = NodePtr::dcast(pFC);

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "VRMLGroupDesc::getFieldAndDesc : looking for " 
            << szFieldname 
            << endl;

    if(pNode == NullFC)
    {
        PWARNING << "VRMLGroupDesc::getFieldAndDesc : No Node" << endl;
        return;
    }

    NodeCorePtr pNodeCore = pNode->getCore();

    GroupPtr pGroup       = GroupPtr::dcast(pNodeCore);

    if(pGroup == NullFC)
    {
        PWARNING << "VRMLGroupDesc::getFieldAndDesc : No Group" << endl;
        return;
    }

    incIndent();

    if(stringcasecmp("bboxCenter", szFieldname) == 0)
    {
        indentLog(getIndent(), PNOTICE);
        PNOTICE << "VRMLGroupDesc::getFieldAndDesc :  : request internal "
                << szFieldname
                << endl;

        pField = &_boxCenter;
        pDesc  = NULL;
    }
    else if(stringcasecmp("whichChoice", szFieldname) == 0)
    {
        indentLog(getIndent(), PNOTICE);
        PNOTICE << "VRMLGroupDesc::getFieldAndDesc :  : request internal "
                << szFieldname
                << endl;

        pField = &_boxSize;
        pDesc  = NULL;
    }
    else if(stringcasecmp("children", szFieldname) == 0)
    {
        indentLog(getIndent(), PNOTICE);
        PNOTICE << "VRMLGroupDesc::getFieldAndDesc :  : request internal "
                << szFieldname
                << endl;

        pField = pNode->getField("children");
        
        if(pField != NULL)
            pDesc = pNode->getType().findFieldDescription("children");
    }
    else
    {
        VRMLNodeDesc::getFieldAndDesc(pGroup, 
                                      szFieldname, 
                                      pField,
                                      pDesc);
    }

    decIndent();
}

/*-------------------------- your_category---------------------------------*/

FieldContainerPtr VRMLGroupDesc::beginNode(
    const Char8       *,
    const Char8       *,
    FieldContainerPtr  pCurrentFC)
{
    FieldContainerPtr pFC         = NullFC;
    NodePtr           pNode       = NullNode;
    NodeCorePtr       pNodeCore   = NullNodeCore;
    GenericAttPtr     pAtt        = GenericAttPtr::NullPtr;

    if(_pNodeProto != NullNode)
    {
        FieldContainerPtr pAttClone = _pGenAtt->emptyCopy();
        
        pAtt = GenericAttPtr::dcast(pAttClone);

        pFC = _pNodeProto->shallowCopy();

        pNode = NodePtr::dcast(pFC);

        pFC = _pNodeCoreProto->shallowCopy();

        pNodeCore = NodeCorePtr::dcast(pFC);
       
        pNode    ->setCore      (pNodeCore);
        pNodeCore->addAttachment(pAtt);
    }

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "Begin Group " << &(*pNode) << endl;

    incIndent();

    return pNode;
}

void VRMLGroupDesc::endNode(FieldContainerPtr pFC)
{    
    decIndent();

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "End Group " 
            << &(*pFC) << endl;    
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */

/** \brief equal
 */

/** \brief unequal
 */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char VRMLInlineDesc::cvsid[] = "@(#)$Id: $";

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

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

VRMLInlineDesc::VRMLInlineDesc(void) :
    Inherited(),
    
    _defaultBoxCenter(),
    _defaultBoxSize  (),

    _boxCenter       (),
    _boxSize         ()
{
}

/** \brief Destructor
 */

VRMLInlineDesc::~VRMLInlineDesc(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLInlineDesc::init(const Char8 *szName)
{
    indentLog(getIndent(), PNOTICE);
    PNOTICE << "InlineDesc::init : " << szName << endl;

    _pNodeProto     = Node::create();
    _pNodeCoreProto = Inline::create();

    _pGenAtt        = GenericAtt::create();
}

/*---------------------------- properties ---------------------------------*/
 
Bool VRMLInlineDesc::prototypeAddField(const Char8  *szFieldType,
                                       const UInt32  uiFieldTypeId,
                                       const Char8  *szFieldname)
{
    Bool bFound;

    _pCurrField = NULL;

    if(stringcasecmp("bboxCenter", szFieldname) == 0)
    {
        _pCurrField = &_defaultBoxCenter;
        bFound = true;
    }
    else if(stringcasecmp("bboxSize", szFieldname) == 0)
    {
        _pCurrField = &_defaultBoxSize;
        bFound = true;
    }
    else if(stringcasecmp("url", szFieldname) == 0)
    {
        bFound = true;
    }

    if(bFound == true)
    {
        return true;
    }
    else
    {
        return Inherited::prototypeAddField(szFieldType,
                                            uiFieldTypeId,
                                            szFieldname);
    }
}

void VRMLInlineDesc::endProtoInterface(void)
{
}

void VRMLInlineDesc::getFieldAndDesc(      
          FieldContainerPtr  pFC,
    const Char8            * szFieldname,
          Field            *&pField,
    const FieldDescription *&pDesc)
{
    if(szFieldname == NULL)
        return;

    if(pFC == NullFC)
        return;

    NodePtr pNode = NodePtr::dcast(pFC);

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "VRMLInlineDesc::getFieldAndDesc : looking for " 
            << szFieldname 
            << endl;

    if(pNode == NullFC)
    {
        PWARNING <<  "VRMLInlineDesc::getFieldAndDesc : No Node" << endl;
        return;
    }

    NodeCorePtr pNodeCore = pNode->getCore();

    InlinePtr pInline     = InlinePtr::dcast(pNodeCore);

    if(pInline == NullFC)
    {
        PWARNING <<  "VRMLInlineDesc::getFieldAndDesc : No Inline" << endl;
        return;
    }

    incIndent();

    if(stringcasecmp("bboxCenter", szFieldname) == 0)
    {
        indentLog(getIndent(), PNOTICE);
        PNOTICE << "VRMLInlineDesc::getFieldAndDesc :  : request internal "
                << szFieldname
                << endl;

        pField = &_boxCenter;
        pDesc  = NULL;
    }
    else if(stringcasecmp("whichChoice", szFieldname) == 0)
    {
        indentLog(getIndent(), PNOTICE);
        PNOTICE << "VRMLInlineDesc::getFieldAndDesc :  : request internal "
                << szFieldname
                << endl;

        pField = &_boxSize;
        pDesc  = NULL;
    }
    else
    {
        VRMLNodeDesc::getFieldAndDesc(pInline, 
                                      szFieldname, 
                                      pField,
                                      pDesc);
    }

    decIndent();
}

/*-------------------------- your_category---------------------------------*/

FieldContainerPtr VRMLInlineDesc::beginNode(
    const Char8       *,
    const Char8       *,
    FieldContainerPtr  pCurrentFC)
{
    FieldContainerPtr pFC         = NullFC;
    NodePtr           pNode       = NullNode;
    NodeCorePtr       pNodeCore   = NullNodeCore;
    GenericAttPtr     pAtt        = GenericAttPtr::NullPtr;

    if(_pNodeProto != NullNode)
    {
        FieldContainerPtr pAttClone = _pGenAtt->emptyCopy();
        
        pAtt = GenericAttPtr::dcast(pAttClone);

        pFC = _pNodeProto->shallowCopy();

        pNode = NodePtr::dcast(pFC);

        pFC = _pNodeCoreProto->shallowCopy();

        pNodeCore = NodeCorePtr::dcast(pFC);
       
        pNode    ->setCore      (pNodeCore);
        pNodeCore->addAttachment(pAtt);
    }

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "Begin Inline" << &(*pNode) << endl;

    incIndent();

    return pNode;
}

void VRMLInlineDesc::endNode(FieldContainerPtr pFC)
{    
    decIndent();

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "End Inline " 
            << &(*pFC) << endl;   
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */

/** \brief equal
 */

/** \brief unequal
 */



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char VRMLViewpointDesc::cvsid[] = "@(#)$Id: $";

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

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

VRMLViewpointDesc::VRMLViewpointDesc(void) :
    Inherited()
{
}

/** \brief Destructor
 */

VRMLViewpointDesc::~VRMLViewpointDesc(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLViewpointDesc::init(const Char8 *szName)
{
    fprintf(stderr, "Viewpoint init : %s \n", szName);

    _pNodeProto     = Node::create();
    _pNodeCoreProto = VRMLTransform::create();
    _pGenAtt        = GenericAtt::create();    

    FieldDescription *pDesc = 
        new FieldDescription(SFBool::getClassType(), 
                             "isViewpoint", 
                             0, 0,
                             false,
                             (FieldIndexAccessMethod) 
                             &GenericAtt::getDynamicField);
        

    _pGenAtt->addField(*pDesc);
}

void VRMLViewpointDesc::reset(void)
{
 //   _pCamera = PerspectiveCamera::NullFC;
        
//    _beaconNode = NullNode;
///    _beaconCore = VRMLTransformPtr::NullPtr;
//    _viewpointAttachment = ViewpointAttachmentPtr::NullPtr;
//
//    _defaultOrientation.setValue(_orientation);
//    _defaultPosition   .setValue(_position);
}

VRMLTransformPtr VRMLViewpointDesc::getDefaultBeacon(void)
{
    return VRMLTransformPtr::NullPtr;
}

/*
FieldContainerPtr VRMLViewpointDesc::getSaveFieldContainer(void)
{
    return getDefaultBeacon();
}
*/

/*---------------------------- properties ---------------------------------*/
 
Bool VRMLViewpointDesc::prototypeAddField(const Char8  *szFieldType,
                                         const UInt32  uiFieldTypeId,
                                         const Char8  *szFieldname)
{
    Bool bFound = false;

    _pCurrField = NULL;

    if(stringcasecmp("orientation", szFieldname) == 0)
    {
        _pCurrField = _pNodeCoreProto->getField("rotation");

        bFound = true;
    }
    else if(stringcasecmp("position", szFieldname) == 0)
    {
        _pCurrField = _pNodeCoreProto->getField("translation");

        bFound = true;
    }

    if(bFound == true)
    {
        return true;
    }
    else
    {
        return Inherited::prototypeAddField(szFieldType,
                                            uiFieldTypeId,
                                            szFieldname); 
    }
}

void VRMLViewpointDesc::endProtoInterface(void)
{
}

void VRMLViewpointDesc::getFieldAndDesc(      
          FieldContainerPtr  pFC,
    const Char8            * szFieldname,
          Field            *&pField,
    const FieldDescription *&pDesc)
{
    indentLog(getIndent(), PNOTICE);
    PNOTICE << "ViewpointDesc::getFieldAndDesc : request " 
            << szFieldname 
            << endl;

    if(szFieldname == NULL)
        return;

    if(pFC == NullFC)
        return;

    NodePtr pNode = NodePtr::dcast(pFC);

    if(pNode == NullFC)
    {
        PWARNING << "ViewpointDesc::getFieldAndDesc : No Node" << endl;
        return;
    }

    NodeCorePtr pNodeCore = pNode->getCore();

    VRMLTransformPtr pTransform = VRMLTransformPtr::dcast(pNodeCore);

    if(pTransform == NullFC)
    {
        PWARNING << "ViewpointDesc::getFieldAndDesc : No Geo" << endl;
        return;
    }

    if(stringcasecmp("orientation", szFieldname) == 0)
    {
        indentLog(getIndent(), PNOTICE);
        PNOTICE << "ViewpointDesc::getFieldAndDesc : internal " 
                << szFieldname << endl;

        pField = pTransform->getField("rotation");
        
        if(pField != NULL)
            pDesc = pTransform->getType().findFieldDescription("rotation");
    }
    else if(stringcasecmp("position", szFieldname) == 0)
    {
        indentLog(getIndent(), PNOTICE);
        PNOTICE << "ViewpointDesc::getFieldAndDesc : internal " 
                << szFieldname << endl;

        pField = pTransform->getField("translation");
        
        if(pField != NULL)
            pDesc = pTransform->getType().findFieldDescription("translation");
    }
    else
    {
        VRMLNodeDesc::getFieldAndDesc(pTransform, 
                                      szFieldname, 
                                      pField,
                                      pDesc);
    }
}

/*-------------------------- your_category---------------------------------*/

FieldContainerPtr VRMLViewpointDesc::beginNode(
    const Char8       *,
    const Char8       *,
    FieldContainerPtr  pCurrentFC)
{
    FieldContainerPtr pFC         = NullFC;
    NodePtr           pNode       = NullNode;
    NodeCorePtr       pNodeCore   = NullNodeCore;
    GenericAttPtr     pAtt        = GenericAttPtr::NullPtr;

    if(_pNodeProto != NullNode)
    {
        FieldContainerPtr pAttClone = _pGenAtt->clone();
        
        pAtt = GenericAttPtr::dcast(pAttClone);

        pFC = _pNodeProto->shallowCopy();

        pNode = NodePtr::dcast(pFC);

        pFC = _pNodeCoreProto->shallowCopy();

        pNodeCore = NodeCorePtr::dcast(pFC);
       
        pNode    ->setCore      (pNodeCore);
        pNodeCore->addAttachment(pAtt);
    }

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "Begin Viewpoint " << &(*pNode) << endl;

    incIndent();
    
    return pNode;
}

void VRMLViewpointDesc::endNode(FieldContainerPtr pFC)
{ 
    decIndent();

    indentLog(getIndent(), PNOTICE);
    PNOTICE << "End Viewpoint " << &(*pFC) << endl;
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */

/** \brief equal
 */

/** \brief unequal
 */


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

