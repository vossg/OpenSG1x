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

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE
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

char VRMLNodeDesc::cvsid[] = "@(#)$Id: $";

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

    cerr << "\tTrying to find field : " << szFieldname << endl;

    if(pFC1 != NullFC)
    {
        returnValue = pFC1->getField(szFieldname);
    }

    cerr << "\t\tGot this from node : " << returnValue << endl;

    if(returnValue != NULL)
        return returnValue;

    if(pFC2 != NullFC)
    {
        returnValue = pFC2->getField(szFieldname);
        cerr << "\t\tGot this from nodecore : " << returnValue << endl;
    }
    else
    {
        cerr << "\tStrange no core " << endl;
    }


    if(returnValue != NULL)
        return returnValue;

    if(pGenAtt != GenericAtt::NullPtr)
    {
        returnValue = pGenAtt->getField(szFieldname);
    }

    cerr << "\t\tGot this from attachment : " << returnValue << endl;

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

    fprintf(stderr, "Looking for : %s\n", szFieldname);

    pField = pFC->getField(szFieldname);

    fprintf(stderr, "Got that from FC %d\n", pField);

    if(pField != NULL)
    {
        pDesc = pFC->getType().findFieldDescription(szFieldname);
        return;
    }

    if(pFC->getType().isNode() == true)
    {
        pNode     = NodePtr::dcast(pFC);

        pNodeCore = pNode->getCore();

        if(pNodeCore != NullFC)
        {
            pField    = pNodeCore->getField(szFieldname);
            
            fprintf(stderr, "Got that from NodeCore %d\n", pField);
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

            fprintf(stderr, "Got that from NodeAtt %d\n", pField);

            if(pField == NULL)
            {
                pTmpFC = 
                    pNodeCore->findAttachment(
                        GenericAtt::getClassType().getGroupId());

                if(pTmpFC != NullFC)
                {
                    pField = pTmpFC->getField(szFieldname);
                }

                fprintf(stderr, "Got that from NodeCoreAtt %d\n", pField);
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

        fprintf(stderr, "Got that from FCNodeCoreAtt %d\n", pField);

        if(pTmpFC != NullFC)
        {
            pField = pTmpFC->getField(szFieldname);
        }
        
        if(pField != NULL)
        {
            pDesc = pTmpFC->getType().findFieldDescription(szFieldname);
        }        
    }
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

    cerr << "\t\tBPF|Got Field " << pField << endl;

    if(pField == NULL)
    {
        pType = FieldFactory::the().getFieldType(uiFieldTypeId);

        if(pType == NULL)
        {
            cerr << "\tCould not get type " 
                 << uiFieldTypeId << " " 
                 << endl;
            
            return false;
        }
        
        cerr << "\t\tGot type "                
             << uiFieldTypeId
             << " "
             << pType->getName()
             << " " 
             << pType->getId()
             << endl;
        
        pDesc = new FieldDescription(
            *pType, 
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
    
        PLOG << "\t\tAddField " 
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
        cerr << "\tCould not add second field " << szFieldName << endl;
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
    fprintf(stderr, "Shape init : %s\n", szName);

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
    fprintf(stderr, "Shape Proto add request : %s\n", szFieldname);

    _pCurrField = NULL;

    if(szFieldname == NULL)
        return false;

    if(stringcasecmp("geometry", szFieldname) == 0)
    {
        fprintf(stderr, "Request Geometry : \n");

        _pCurrField = _pNodeProto->getField("children");
    }

    if(stringcasecmp("apperance", szFieldname) == 0)
    {
        fprintf(stderr, "Request Appearance : \n");

        _pCurrField = _pNodeProto->getField("core");
    }

    fprintf(stderr, "Got This Internaly %d\n", _pCurrField);

    if(_pCurrField == NULL)
    {
        return Inherited::prototypeAddField(szFieldType,
                                            uiFieldTypeId,
                                            szFieldname);
    }
    else
    {
        return true;
    }
}
 
void VRMLShapeDesc::getFieldAndDesc(
          FieldContainerPtr   pFC,
    const Char8             * szFieldname,
          Field             *&pField,
    const FieldDescription  *&pDesc)
{
    fprintf(stderr, "Shape request : %s\n", szFieldname);

    if(szFieldname == NULL)
        return;

    if(pFC == NullFC)
        return;

    if(stringcasecmp("geometry", szFieldname) == 0)
    {
        fprintf(stderr, "Request Geometry : \n");

        pField = pFC->getField("children");
        
        if(pField != NULL)
            pDesc = pFC->getType().findFieldDescription("children");
    }
    else if(stringcasecmp("appearance", szFieldname) == 0)
    {
        fprintf(stderr, "Request App : \n");

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

    return returnValue;
}

void VRMLShapeDesc::endNode(FieldContainerPtr pFC)
{
    fprintf(stderr, "ShapeEnd\n");

    if(pFC != NullFC)
    {
        NodePtr pNode = NodePtr::dcast(pFC);

        if(pNode != NullFC && pNode->getCore() == NullFC)
        {
            MaterialGroupPtr pMatGroup = MaterialGroup::create();

            pMatGroup->setMaterial(_pMaterialDesc->getDefaultMaterial());

            pNode->setCore(pMatGroup);
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
    fprintf(stderr, "Geo init : %s\n", szName);

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
        fprintf(stderr, "Request Geometry Node: %s\n", szFieldname);
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
    fprintf(stderr, "Geometry request : %s\n", szFieldname);

    if(szFieldname == NULL)
        return;

    if(pFC == NullFC)
        return;

    NodePtr pNode = NodePtr::dcast(pFC);

    if(pNode == NullFC)
    {
        fprintf(stderr, "No Node\n");
        return;
    }

    NodeCorePtr pNodeCore = pNode->getCore();

    GeometryPtr pGeo      = GeometryPtr::dcast(pNodeCore);

    if(pGeo == NullFC)
    {
        fprintf(stderr, "No Geo\n");
        return;
    }

    _bInIndex = false;

    if(stringcasecmp("coord", szFieldname) == 0)
    {
        fprintf(stderr, "Request Geometry : coord \n");

        pField = pGeo->getField("positions");
        
        if(pField != NULL)
            pDesc = pGeo->getType().findFieldDescription("positions");
    }
    else if(stringcasecmp("normal", szFieldname) == 0)
    {
        fprintf(stderr, "Request Geometry : normal\n");

        pField = pGeo->getField("normals");
        
        if(pField != NULL)
            pDesc = pGeo->getType().findFieldDescription("normals");
    }
    else if(stringcasecmp("color", szFieldname) == 0)
    {
        fprintf(stderr, "Request Geometry : color \n");

        pField = pGeo->getField("colors");
        
        if(pField != NULL)
            pDesc = pGeo->getType().findFieldDescription("colors");
    }
    else if(stringcasecmp("texCoord", szFieldname) == 0)
    {
        fprintf(stderr, "Request Geometry : texCoord \n");

        pField = pGeo->getField("texCoords");
        
        if(pField != NULL)
            pDesc = pGeo->getType().findFieldDescription("texCoords");
    }

/*
    else if(stringcasecmp("coordIndex", szFieldname) == 0)
    {
        FieldContainerPtr pIndexFC = NullFC;

        if(pGeo->getIndex() == NullFC)
        {
            GeoIndexUI32Ptr   pIndex   = GeoIndexUI32::create();

            _pTypeField   = GeoPType::create();
            _pLengthField = GeoPLength::create();
             pIndexFC     = pIndex;

            pGeo->setTypes     (_pTypeField);
            pGeo->setLengths   (_pLengthField);

            pGeo->setIndex(pIndex);
        }
        else
        {
            _pTypeField   = pGeo->getTypes();
            _pLengthField = pGeo->getLengths();
             pIndexFC     = pGeo->getIndex();
        }

        _uiNumVertices = 0;

        fprintf(stderr, "Request Geometry : \n");

        pField = pIndexFC->getField("Indices");
        
        if(pField != NULL)
        {
            pDesc = pIndexFC->getType().findFieldDescription("Indices");
        }

        _bInIndex = true;
    }
    */
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
        FieldContainerPtr pAttClone = _pGenAtt->emptyCopy();
        
        pAtt = GenericAttPtr::dcast(pAttClone);

        pFC = _pNodeProto->shallowCopy();

        pNode = NodePtr::dcast(pFC);

        pFC = _pNodeCoreProto->shallowCopy();

        pNodeCore = NodeCorePtr::dcast(pFC);
       
        pNode    ->setCore      (pNodeCore);
        pNodeCore->addAttachment(pAtt);
    }

    fprintf(stderr, "Begin Geo %x\n", &(*pNode));

    return pNode;
}

void VRMLGeometryDesc::endNode(FieldContainerPtr pFC)
{
    fprintf(stderr, "End Geo\n");

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
            setIndexFromVRMLData(pGeo,
                                 pCoordIndex     ->getValues(),
                                 pNormalIndex    ->getValues(),
                                 pColorIndex     ->getValues(),
                                 pTexCoordIndex  ->getValues(),
                                 pConvex         ->getValue() ,
                                 pCcw            ->getValue() ,
                                 pNormalPerVertex->getValue() ,
                                 pColorPerVertex ->getValue() ,
                                 true);
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
            setIndexFromVRMLData(pGeo,
                                 pCoordIndex    ->getValues(),
                                 dummyVec ,
                                 pColorIndex    ->getValues(),
                                 dummyVec ,
                                 dummyBool,
                                 dummyBool,
                                 dummyBool,
                                 pColorPerVertex->getValue() ,
                                 false);
        }
    }
}

void VRMLGeometryDesc::addFieldValue(      Field *pField,
                                     const Char8 *szFieldVal)
{
/*
    if(_bInIndex == true)
    {
        if(pField != NULL && szFieldVal[0] != '-')
        {
            pField->pushValueByStr(szFieldVal);
            _uiNumVertices++;
        }
        else
        {
            _pTypeField  ->getFieldPtr()->addValue(GL_POLYGON);
            _pLengthField->getFieldPtr()->addValue(_uiNumVertices);

            _uiNumVertices = 0;
        }
    }
    else
    {
        if(pField != NULL)
        {
            pField->pushValueByStr(szFieldVal);
        }
    }
    */

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
    fprintf(stderr, "GeoPart init : %s %s %s %s\n", 
            szName,
            _szVRMLPartname,
            _szOSGPartname,
            _szOSGProtoname);

    _pNodeProto =
       FieldContainerFactory::the()->createFieldContainer(_szOSGProtoname);

    if(_pNodeProto == NullFC)
    {
        fprintf(stderr, "ERROR no prototype available\n");
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
        fprintf(stderr, "Add GeometryPart : %s\n", szFieldname);

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
    fprintf(stderr, "GeometryPart request : %s\n", szFieldname);

    if(szFieldname == NULL)
        return;

    if(pFC == NullFC)
        return;

    if(stringcasecmp(_szVRMLPartname, szFieldname) == 0)
    {
        fprintf(stderr, "Request GeometryPart : \n");

        pField = pFC->getField(_szOSGPartname);
        
        if(pField != NULL)
            pDesc = pFC->getType().findFieldDescription(_szOSGPartname);

        if(pField == NULL)
        {
            fprintf(stderr, "ERROR no part mapping yet\n");
        }
    }
    else
    {
        Inherited::getFieldAndDesc(pFC, 
                                   szFieldname, 
                                   pField,
                                   pDesc);
    }
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
    fprintf(stderr, "GeoObject init : %s %s\n", 
            szName,
            _szVRMLObjectname);

    _pNodeProto = Node::create();

    if(_pNodeProto == NullFC)
    {
        fprintf(stderr, "ERROR no prototype available\n");
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

    _pGenAtt->dump(0,0);

    return rc;
}

void VRMLGeometryObjectDesc::getFieldAndDesc(      
          FieldContainerPtr  pFC,
    const Char8            * szFieldname,
          Field            *&pField,
    const FieldDescription *&pDesc)
{
    fprintf(stderr, "GeometryObject request : %s\n", szFieldname);

    if(szFieldname == NULL)
        return;

    if(pFC == NullFC)
        return;

    pFC->dump(0, 0);

    Inherited::getFieldAndDesc(pFC, 
                               szFieldname, 
                               pField,
                               pDesc);
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
            fprintf(stderr, "Create Cone\n");

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
            fprintf(stderr, "Create Cylinder\n");

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
    fprintf(stderr, "Appearance init :  %s\n", szName);

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

    fprintf(stderr, "Appearance request : %s\n", szFieldname);

    if(pFC == NullFC)
        return;

    if(szFieldname == NULL)
        return;

    if(stringcasecmp("material", szFieldname) == 0)
    {
        fprintf(stderr, "Request Appearance : material \n");
        
        pField = pFC->getField("material");
        
        if(pField != NULL)
            pDesc = pFC->getType().findFieldDescription("material");
    }
    else if(stringcasecmp("texture", szFieldname) == 0)
    {
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

    return returnValue;
}

void VRMLAppearanceDesc::endNode(FieldContainerPtr pFC)
{
    fprintf(stderr, "EndNode Apperance %p\n", &(*(_sfTexture.getValue())));

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
                    pChunkMat->addChunk(pTexture);
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
                            pChunkMat->addChunk(pTexture);
                        }

                        pMatGroup->setMaterial(pChunkMat);
                    }
                }
                else
                {
                    pMatGroup->setMaterial(
                        _pMaterialDesc->getDefaultMaterial());
                }
            }
        }
    }
}

Bool VRMLAppearanceDesc::use(FieldContainerPtr pFC)
{
    return true;
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
    fprintf(stderr, "Material init : %s \n", szName);
}

void VRMLMaterialDesc::reset(void)
{
    _pMat = SimpleMaterial::NullPtr;

//    _defaultAmbientIntensity.setValue(_ambientIntensity);
//    _defaultDiffuseColor    .setValue(_diffuseColor);
//    _defaultEmissiveColor   .setValue(_emissiveColor);
//    _defaultShininess       .setValue(_shininess);
//    _defaultSpecularColor   .setValue(_specularColor);
//    _defaultTransparency    .setValue(_transparency);
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
        fprintf(stderr, "Add MatPart : %s\n", szFieldname);
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

        _pMat->setAmbient     ( cAmbient                );
        _pMat->setDiffuse     (_diffuseColor.getValue() );
        _pMat->setSpecular    (_specularColor.getValue());
        _pMat->setShininess   (_shininess.getValue()    );
        _pMat->setEmission    (_emissiveColor.getValue());
        _pMat->setTransparency(_transparency.getValue() );
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
    fprintf(stderr, "Material init : %s \n", szName);
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
        fprintf(stderr, "Add ImageTexturePart : %s\n", szFieldname);
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

    fprintf(stderr, "BeginNode Image Texture %p\n", &(*(returnValue)));

    _url.clear();

    _repeatS = _defaultRepeatS;
    _repeatT = _defaultRepeatT;

    return returnValue;
}

void VRMLImageTextureDesc::endNode(FieldContainerPtr pFC)
{    
    fprintf(stderr, "EndNode ImageTexture %s %d %d %p\n",
            _url.getValue(0).str(),
            _repeatS.getValue(),
            _repeatT.getValue(),
            &(*(pFC)));

    TextureChunkPtr  pTexture = TextureChunkPtr::NullPtr;

    Image           *pImage   = new Image();

    pTexture = TextureChunkPtr::dcast(pFC);

    if(pTexture != NullFC)
    {
        cerr << "Reading texture " << _url.getValue(0).str() << endl;
        
        if(pImage->read(_url.getValue(0).str()))
        {
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
        }
        else
        {
            cerr << "Couldn't read texture " 
                 << _url.getValue(0).str()  
                 << "!!!" << endl;
            
            delete pImage;
        }
    }
    else
    {
        fprintf(stderr, "Invalid texture ptr\n");
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
    fprintf(stderr, "Pixel Texture init : %s \n", szName);
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
        fprintf(stderr, "Add PixelTexturePart : %s\n", szFieldname);
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

    fprintf(stderr, "BeginNode Pixel Texture %p\n", &(*(returnValue)));

    _image.setValue(new Image());

    _repeatS = _defaultRepeatS;
    _repeatT = _defaultRepeatT;

    return returnValue;
}

void VRMLPixelTextureDesc::endNode(FieldContainerPtr pFC)
{    
    fprintf(stderr, "EndNode Pixel Texture %d %d %p\n",
            _repeatS.getValue(),
            _repeatT.getValue(),
            &(*(pFC)));

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
        fprintf(stderr, "Invalid texture ptr\n");
    }
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
    fprintf(stderr, "LOD init : %s \n", szName);

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

    if(pNode == NullFC)
    {
        fprintf(stderr, "No Node\n");
        return;
    }

    NodeCorePtr pNodeCore = pNode->getCore();

    DistanceLODPtr pLOD      = DistanceLODPtr::dcast(pNodeCore);

    if(pLOD == NullFC)
    {
        fprintf(stderr, "No LOD\n");
        return;
    }

    if(stringcasecmp("level", szFieldname) == 0)
    {
        fprintf(stderr, "Request LOD : level \n");

        pField = pNode->getField("children");
        
        if(pField != NULL)
            pDesc = pNode->getType().findFieldDescription("children");
    }
    else if(stringcasecmp("center", szFieldname) == 0)
    {
        fprintf(stderr, "Request LOD : center \n");

        pField = pLOD->getField("center");
        
        if(pField != NULL)
            pDesc = pLOD->getType().findFieldDescription("children");
    }
    else if(stringcasecmp("range", szFieldname) == 0)
    {
        fprintf(stderr, "Request LOD : range \n");

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

    fprintf(stderr, "Begin LOD %x\n", &(*pNode));

    return pNode;
}

void VRMLLODDesc::endNode(FieldContainerPtr pFC)
{    
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

