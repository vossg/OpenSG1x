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
            pTmpFC = pNode->findAttachment(GenericAtt::getClassTypeId());
            
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
    Inherited   (),
    _pAppearanceDesc(NULL)
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
    fprintf(stderr, "Geo init : %s\n", szName);

    _pNodeProto = Node::create();

    _pGenAtt = GenericAtt::create();
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

        pField = pFC->getField("core");
        
        if(pField != NULL)
            pDesc = pFC->getType().findFieldDescription("core");
    }
    else if(stringcasecmp("appearance", szFieldname) == 0)
    {
        fprintf(stderr, "Request App : \n");

        pField = getField(NullFC, NullFC, _pGenAtt, szFieldname);
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
    GenericAttPtr     pAtt        = GenericAttPtr::NullPtr;

    if(_pNodeProto != NullNode)
    {
//        FieldContainerPtr pAttClone = _pGenAtt->emptyCopy();
        
//        pAtt = pAttClone.dcast<GenericAttPtr>();
        
        returnValue = _pNodeProto->shallowCopy();
        
//        pNode = returnValue.dcast<NodePtr>();
        
//        pNode->addAttachment(pAtt);
    }

    if(_pAppearanceDesc != NULL)
        _pAppearanceDesc->resetMat();

    return returnValue;
}

void VRMLShapeDesc::endNode(FieldContainerPtr pFC)
{
    fprintf(stderr, "ShapeEnd\n");

    if(_pAppearanceDesc != NULL)
    {
        NodePtr     pNode =  NodePtr::dcast(pFC);
        MaterialPtr pMat  = _pAppearanceDesc->getMat();

        if(pNode != NullFC)
        {
            GeometryPtr pGeo = GeometryPtr::dcast(pNode->getCore());

            if(pGeo != NullFC)
            {
                pGeo->setMaterial(pMat);
            }
        }
    }
}

void VRMLShapeDesc::setAppearanceDesc(VRMLAppearanceDesc *pAppearanceDesc)
{
    _pAppearanceDesc = pAppearanceDesc;
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

VRMLGeometryDesc::VRMLGeometryDesc(void) :
    Inherited     (),

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

    _pNodeProto = Geometry::create();

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
    else if(stringcasecmp("coordIndex", szFieldname) == 0)
    {
        bFound = true;
    }

    if(bFound == true)
    {
        fprintf(stderr, "Request Geometry Node: %s\n", szFieldname);
        return true;
    }
        

    if(stringcasecmp("normalPerVertex", szFieldname) == 0)
    {
        fprintf(stderr, "Request Geometry : NormalPV\n");

        _pCurrField = _pNodeProto->getField("normalPerVertex");       
    }
    else if(stringcasecmp("colorPerVertex", szFieldname) == 0)
    {
        fprintf(stderr, "Request Geometry : ColorPV\n");

        _pCurrField = _pNodeProto->getField("colorPerVertex");       
    }

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

    GeometryPtr pGeo = GeometryPtr::dcast(pFC);

    _bInIndex = false;

    if(stringcasecmp("coord", szFieldname) == 0)
    {
        fprintf(stderr, "Request Geometry : \n");

        pField = pFC->getField("positions");
        
        if(pField != NULL)
            pDesc = pFC->getType().findFieldDescription("positions");
    }
    else if(stringcasecmp("normal", szFieldname) == 0)
    {
        fprintf(stderr, "Request Geometry : \n");

        pField = pFC->getField("normals");
        
        if(pField != NULL)
            pDesc = pFC->getType().findFieldDescription("normals");
    }
    else if(stringcasecmp("color", szFieldname) == 0)
    {
        fprintf(stderr, "Request Geometry : color \n");

        pField = pFC->getField("colors");
        
        if(pField != NULL)
            pDesc = pFC->getType().findFieldDescription("colors");
    }
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
    else if(stringcasecmp("normalPerVertex", szFieldname) == 0)
    {
        fprintf(stderr, "Request Geometry : Normal\n");
        pField = pGeo->getField("normalPerVertex");
        
        if(pField != NULL)
        {
            pDesc = pGeo->getType().findFieldDescription("normalPerVertex");
        }
    }
    else if(stringcasecmp("colorPerVertex", szFieldname) == 0)
    {
        fprintf(stderr, "Request Geometry : Normal\n");
        pField = pGeo->getField("colorPerVertex");
        
        if(pField != NULL)
        {
            pDesc = pGeo->getType().findFieldDescription("colorPerVertex");
        }
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

FieldContainerPtr VRMLGeometryDesc::beginNode(
    const Char8       *szTypename,
    const Char8       *szName,
    FieldContainerPtr)
{
    FieldContainerPtr returnValue = NullFC;
    NodeCorePtr       pNodeCore   = NullNodeCore;
    GenericAttPtr     pAtt        = GenericAttPtr::NullPtr;

    if(_pNodeProto != NullNode)
    {
        FieldContainerPtr pAttClone = _pGenAtt->emptyCopy();
        
        pAtt = GenericAttPtr::dcast(pAttClone);

        returnValue = _pNodeProto->shallowCopy();

        pNodeCore = NodeCorePtr::dcast(returnValue);
       
        pNodeCore->addAttachment(pAtt);
    }

    fprintf(stderr, "Begin Geo %x\n", &(*returnValue));

    return returnValue;
}

void VRMLGeometryDesc::endNode(FieldContainerPtr pFC)
{
    fprintf(stderr, "End Geo\n");
}

void VRMLGeometryDesc::addFieldValue(      Field *pField,
                                     const Char8 *szFieldVal)
{
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
    Inherited     (),

    _pMaterialDesc(NULL)
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

    _pGenAtt    = GenericAtt::create();
}

void VRMLAppearanceDesc::resetMat(void)
{
    Field *pField = Inherited::getField(NullFC, NullFC, _pGenAtt, "material");

    if(pField != NULL)
    {
        ((SFFieldContainerPtr *) pField)->setValue(NullFC);
    }
}

MaterialPtr VRMLAppearanceDesc::getMat(void)
{
    MaterialPtr returnValue = NullMaterial;

    Field *pField = Inherited::getField(NullFC, NullFC, _pGenAtt, "material");

    if(pField != NULL)
    {
        returnValue = ((SFMaterialPtr *) pField)->getValue();
    }

    if(returnValue == NullFC && _pMaterialDesc != NULL)
    {
        returnValue = _pMaterialDesc->getDefaultMaterial();
    }

    return returnValue;
}

void VRMLAppearanceDesc::setMaterialDesc(VRMLMaterialDesc *pMaterialDesc)
{
    _pMaterialDesc = pMaterialDesc;
}

FieldContainerPtr VRMLAppearanceDesc::getSaveFieldContainer(void)
{
    return getMat();
}

/*---------------------------- properties ---------------------------------*/
 
Bool VRMLAppearanceDesc::prototypeAddField(const Char8  *szFieldType,
                                           const UInt32  uiFieldTypeId,
                                           const Char8  *szFieldname)
{
    _pCurrField = NULL;
    
    return VRMLNodeDesc::prototypeAddField(szFieldType,
                                           uiFieldTypeId,
                                           szFieldname);
}

void VRMLAppearanceDesc::getFieldAndDesc(      
          FieldContainerPtr  pFC,
    const Char8            * szFieldname,
          Field            *&pField,
    const FieldDescription *&pDesc)
{

    fprintf(stderr, "Appearance request : %s\n", szFieldname);

    if(szFieldname == NULL)
        return;

    pField = Inherited::getField( NullFC,
                                  NullFC,
                                 _pGenAtt,
                                  szFieldname);
/*
    Inherited::getFieldAndDesc(pFC, 
                               szFieldname, 
                               pField,
                               pDesc);
*/
}

/*-------------------------- your_category---------------------------------*/

FieldContainerPtr VRMLAppearanceDesc::beginNode(
    const Char8       *szTypename,
    const Char8       *szName,
    FieldContainerPtr  pCurrentFC)
{
    FieldContainerPtr returnValue = NullFC;

    return returnValue;
}

Bool VRMLAppearanceDesc::use(FieldContainerPtr pFC)
{
    Field *pField = Inherited::getField(NullFC, NullFC, _pGenAtt, "material");

    if(pField != NULL)
    {
        ((SFFieldContainerPtr *) pField)->setValue(pFC);
    }

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

//    _pNodeProto = SimpleMaterial::create();

/*
    _pNodeProto =
       FieldContainerFactory::the().createFieldContainer("Material");

    if(_pNodeProto == NullFC)
    {
        fprintf(stderr, "ERROR no prototype available\n");
    }
    */
}

void VRMLMaterialDesc::reset(void)
{
    _pMat = SimpleMaterial::NullPtr;

    _defaultAmbientIntensity.setValue(_ambientIntensity);
    _defaultDiffuseColor    .setValue(_diffuseColor);
    _defaultEmissiveColor   .setValue(_emissiveColor);
    _defaultShininess       .setValue(_shininess);
    _defaultSpecularColor   .setValue(_specularColor);
    _defaultTransparency    .setValue(_transparency);
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

