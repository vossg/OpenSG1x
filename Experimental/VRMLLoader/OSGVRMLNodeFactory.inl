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

#include <OSGConfig.h>
#include <OSGLog.h>

#include <OSGFieldFactory.h>
#include <OSGTransform.h>

#include <iostream>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

template <class BaseT>
char VRMLNodeFactory<BaseT>::cvsid[] = "@(#)$Id: $";

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

template <class BaseT> inline
VRMLNodeDesc *
    VRMLNodeFactory<BaseT>::findNodeDesc(const Char8 *szNodeTypename)
{
    VRMLNodeDesc *returnValue = NULL;

    NodeNameDescHash::iterator mNodeDescIt =
        _mNodeDescHash.find(szNodeTypename);

    if(mNodeDescIt != _mNodeDescHash.end())
    {
        fprintf(stderr, "Found Node %s (%s)\n", 
                mNodeDescIt->first, szNodeTypename);

        returnValue = mNodeDescIt->second;
    }

    return returnValue;
}

template <class BaseT> inline
void VRMLNodeFactory<BaseT>::addNodeDesc(const Char8        *szNodeTypename,
                                               VRMLNodeDesc *pDesc)
{
    Char8 *szName = NULL;

    if(szNodeTypename == NULL || pDesc == NULL)
        return;

    stringDup(szNodeTypename, szName);

    _mNodeDescHash[szName] = pDesc; 

    _pCurrentNodeDesc = pDesc;
}

template <class BaseT> inline
void VRMLNodeFactory<BaseT>::preStandardProtos (void)
{
}

template <class BaseT> inline
void VRMLNodeFactory<BaseT>::postStandardProtos(void)
{
    VRMLNodeDesc         *pNodeDesc         = NULL;
    VRMLShapeDesc        *pShapeDesc        = NULL;
    VRMLAppearanceDesc   *pAppearanceDesc   = NULL;
    VRMLMaterialDesc     *pMaterialDesc     = NULL;

    pNodeDesc = findNodeDesc("Shape");

    if(pNodeDesc != NULL)
    {
        pShapeDesc = dynamic_cast<VRMLShapeDesc *>(pNodeDesc);
    }

    pNodeDesc = findNodeDesc("Appearance");

    if(pNodeDesc != NULL)
    {
        pAppearanceDesc = dynamic_cast<VRMLAppearanceDesc *>(pNodeDesc);
    }

    pNodeDesc = findNodeDesc("Material");

    if(pNodeDesc != NULL)
    {
        pMaterialDesc = dynamic_cast<VRMLMaterialDesc *>(pNodeDesc);
    }

    if(pShapeDesc != NULL)
    {
        pShapeDesc->setMaterialDesc(pMaterialDesc);
    }

    if(pAppearanceDesc != NULL)
    {
        pAppearanceDesc->setMaterialDesc(pMaterialDesc);
    }
}


    
/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

template <class BaseT> inline
VRMLNodeFactory<BaseT>::VRMLNodeFactory(void) :
    Inherited(),

    _pCurrentNodeDesc(NULL),
    _mNodeDescHash   (),
    
    _bInFieldProto   (false),

    _bIgnoreProto    (false)
{
}


/** \brief Destructor
 */

template <class BaseT> inline
VRMLNodeFactory<BaseT>::~VRMLNodeFactory(void)
{
}

/*------------------------------ access -----------------------------------*/

template <class BaseT> inline
void VRMLNodeFactory<BaseT>::beginProtoInterface(
    const Char8 *szProtoname)
{
    PLOG << "Begin Proto " << szProtoname << endl;

    Char8 *szName = NULL;

    NodeNameDescHash::iterator mNodeDescIt = 
        _mNodeDescHash.find(szProtoname);

    if(mNodeDescIt == _mNodeDescHash.end())
    {
        if(stringcasecmp("IndexedFaceSet", szProtoname) == 0)
        {
            stringDup(szProtoname, szName);
            
            _pCurrentNodeDesc = new VRMLGeometryDesc(true);
            
            _pCurrentNodeDesc->init(szProtoname);
            
            _mNodeDescHash[szName] = _pCurrentNodeDesc; 
        }
        else if(stringcasecmp("IndexedLineSet", szProtoname) == 0)
        {
            stringDup(szProtoname, szName);
            
            _pCurrentNodeDesc = new VRMLGeometryDesc(false);
            
            _pCurrentNodeDesc->init(szProtoname);
            
            _mNodeDescHash[szName] = _pCurrentNodeDesc; 
        }
        else if(stringcasecmp("Shape", szProtoname) == 0)
        {
            stringDup(szProtoname, szName);
            
            _pCurrentNodeDesc = new VRMLShapeDesc;
            
            _pCurrentNodeDesc->init(szProtoname);
            
            _mNodeDescHash[szName] = _pCurrentNodeDesc; 
        }
        else if(stringcasecmp("Coordinate", szProtoname) == 0)
        {
            stringDup(szProtoname, szName);
            
            _pCurrentNodeDesc = new VRMLGeometryPartDesc("point",
                                                         "positions",
                                                         "GeoPosition3f");
            
            _pCurrentNodeDesc->init(szProtoname);
            
            _mNodeDescHash[szName] = _pCurrentNodeDesc; 
        }
        else if(stringcasecmp("Normal", szProtoname) == 0)
        {
            stringDup(szProtoname, szName);
            
            _pCurrentNodeDesc = new VRMLGeometryPartDesc("vector",
                                                         "Normals",
                                                         "GeoNormal3f");
            
            _pCurrentNodeDesc->init(szProtoname);
            
            _mNodeDescHash[szName] = _pCurrentNodeDesc; 
        }
        else if(stringcasecmp("Color", szProtoname) == 0)
        {
            stringDup(szProtoname, szName);
            
            _pCurrentNodeDesc = new VRMLGeometryPartDesc("color",
                                                         "Colors",
                                                         "GeoColor3f");
            
            _pCurrentNodeDesc->init(szProtoname);
            
            _mNodeDescHash[szName] = _pCurrentNodeDesc; 
        }
        else if(stringcasecmp("TextureCoordinate", szProtoname) == 0)
        {
            stringDup(szProtoname, szName);
            
            _pCurrentNodeDesc = new VRMLGeometryPartDesc("point",
                                                         "TexCoords",
                                                         "GeoTexCoords2f");
            
            _pCurrentNodeDesc->init(szProtoname);
            
            _mNodeDescHash[szName] = _pCurrentNodeDesc; 
        }
        else if(stringcasecmp("Appearance", szProtoname) == 0)
        {
            stringDup(szProtoname, szName);
            
            _pCurrentNodeDesc = new VRMLAppearanceDesc();
            
            _pCurrentNodeDesc->init(szProtoname);
            
            _mNodeDescHash[szName] = _pCurrentNodeDesc; 
        }
        else if(stringcasecmp("Material", szProtoname) == 0)
        {
            stringDup(szProtoname, szName);
            
            _pCurrentNodeDesc = new VRMLMaterialDesc();
            
            _pCurrentNodeDesc->init(szProtoname);
            
            _mNodeDescHash[szName] = _pCurrentNodeDesc; 
        }
        else if(stringcasecmp("Box", szProtoname) == 0)
        {
            stringDup(szProtoname, szName);
            
            _pCurrentNodeDesc = new VRMLGeometryObjectDesc("Box");
            
            _pCurrentNodeDesc->init(szProtoname);
            
            _mNodeDescHash[szName] = _pCurrentNodeDesc; 
        }
        else if(stringcasecmp("Cone", szProtoname) == 0)
        {
            stringDup(szProtoname, szName);
            
            _pCurrentNodeDesc = new VRMLGeometryObjectDesc("Cone");
            
            _pCurrentNodeDesc->init(szProtoname);
            
            _mNodeDescHash[szName] = _pCurrentNodeDesc; 
        }
        else if(stringcasecmp("Cylinder", szProtoname) == 0)
        {
            stringDup(szProtoname, szName);
            
            _pCurrentNodeDesc = new VRMLGeometryObjectDesc("Cylinder");
            
            _pCurrentNodeDesc->init(szProtoname);
            
            _mNodeDescHash[szName] = _pCurrentNodeDesc; 
        }
        else if(stringcasecmp("Sphere", szProtoname) == 0)
        {
            stringDup(szProtoname, szName);
            
            _pCurrentNodeDesc = new VRMLGeometryObjectDesc("Sphere");
            
            _pCurrentNodeDesc->init(szProtoname);
            
            _mNodeDescHash[szName] = _pCurrentNodeDesc; 
        }
        else if(stringcasecmp("ImageTexture", szProtoname) == 0)
        {
            stringDup(szProtoname, szName);
            
            _pCurrentNodeDesc = new VRMLImageTextureDesc();
            
            _pCurrentNodeDesc->init(szProtoname);
            
            _mNodeDescHash[szName] = _pCurrentNodeDesc; 
        }
        else if(stringcasecmp("PixelTexture", szProtoname) == 0)
        {
            stringDup(szProtoname, szName);
            
            _pCurrentNodeDesc = new VRMLPixelTextureDesc();
            
            _pCurrentNodeDesc->init(szProtoname);
            
            _mNodeDescHash[szName] = _pCurrentNodeDesc; 
        }
        else if(stringcasecmp("LOD", szProtoname) == 0)
        {
            stringDup(szProtoname, szName);
            
            _pCurrentNodeDesc = new VRMLLODDesc();
            
            _pCurrentNodeDesc->init(szProtoname);
            
            _mNodeDescHash[szName] = _pCurrentNodeDesc; 
        }
        else if(stringcasecmp("Switch", szProtoname) == 0)
        {
            stringDup(szProtoname, szName);
            
            _pCurrentNodeDesc = new VRMLSwitchDesc();
            
            _pCurrentNodeDesc->init(szProtoname);
            
            _mNodeDescHash[szName] = _pCurrentNodeDesc; 
        }
        else if(stringcasecmp("Group", szProtoname) == 0)
        {
            stringDup(szProtoname, szName);
            
            _pCurrentNodeDesc = new VRMLGroupDesc();
            
            _pCurrentNodeDesc->init(szProtoname);
            
            _mNodeDescHash[szName] = _pCurrentNodeDesc; 
        }
        else if(stringcasecmp("Inline", szProtoname) == 0)
        {
            stringDup(szProtoname, szName);
            
            _pCurrentNodeDesc = new VRMLInlineDesc();
            
            _pCurrentNodeDesc->init(szProtoname);
            
            _mNodeDescHash[szName] = _pCurrentNodeDesc; 
        }
        else
        {
            stringDup(szProtoname, szName);
            
            _pCurrentNodeDesc = new VRMLNodeDesc;
            
            _pCurrentNodeDesc->init(szProtoname);
            
            _mNodeDescHash[szName] = _pCurrentNodeDesc; 
        }
    }
    else
    {
        PLOG << "Could not add second proto named " 
                << szProtoname 
                << endl;

        _bIgnoreProto = true;
    }
}

template <class BaseT> inline
void VRMLNodeFactory<BaseT>::endProtoInterface  (void)
{
    if(_pCurrentNodeDesc != NULL)
        _pCurrentNodeDesc->endProtoInterface();

    _bIgnoreProto = false;
}

template <class BaseT> inline
void VRMLNodeFactory<BaseT>::addProtoEventIn(
    const Char8 *szEventType,
    const Char8 *szEventName)
{
    if(_bIgnoreProto == true)
        return;

    PLOG << "\tAddEventIn " << szEventType << " " << szEventName << endl;
}

template <class BaseT> inline
void VRMLNodeFactory<BaseT>::addProtoEventOut(
    const Char8 *szEventType,
    const Char8 *szEventName)
{
    if(_bIgnoreProto == true)
        return;

    PLOG << "\tAddEventOut " << szEventType << " " << szEventName << endl;
}

template <class BaseT> inline
void VRMLNodeFactory<BaseT>::beginProtoField(
    const Char8  *szFieldType,
    const UInt32  uiFieldTypeId,
    const Char8  *szFieldName)
{
    Bool rc;

    if(_bIgnoreProto == true)
        return;

    if(_pCurrentNodeDesc != NULL)
    {
        rc = _pCurrentNodeDesc->prototypeAddField(
            szFieldType,
            mapIntExtFieldType(uiFieldTypeId),
            szFieldName);

        if(rc == true)
        {
            _bInFieldProto = true;
        }
    }
}

template <class BaseT> inline
void VRMLNodeFactory<BaseT>::endProtoField(void)
{
    _bInFieldProto = false;
}

template <class BaseT> inline
void VRMLNodeFactory<BaseT>::beginProtoExposedField(
    const Char8  *szFieldType,
    const UInt32  uiFieldTypeId,
    const Char8  *szFieldName)
{
    beginProtoField(szFieldType, uiFieldTypeId, szFieldName);
}

template <class BaseT> inline
void VRMLNodeFactory<BaseT>::endProtoExposedField(void)
{
    endProtoField();
}

#if 0
template <class BaseT> inline
OSG::NodePtr VRMLNodeFactory<BaseT>::getNode(const Char8 *szNodename)
{
    OSG::NodePtr              returnValue = OSG::NullNode;
    OSG::FieldContainerPtr    pTmp;
    NodeProtoMap::iterator gIt;
    
    if(szNodename == NULL)
        return returnValue;

    gIt = _mNodeProtos.find(StringLink(szNodename));

    if(gIt != _mNodeProtos.end())
    {
        pTmp = (*gIt).second->clone();

        if(pTmp != OSG::NullFC)
            returnValue = pTmp.dcast<OSG::NodePtr>();
    }

    return returnValue;
}
#endif   

/*---------------------------- properties ---------------------------------*/

template <class BaseT> inline
void VRMLNodeFactory<BaseT>::addFieldValue(const Char8 *szFieldVal)
{
    if(_bInFieldProto == true)
        PLOG << "\t\tVNF: FV : " << szFieldVal << endl;

    if(_pCurrentNodeDesc != NULL)
    {
        _pCurrentNodeDesc->prototypeAddFieldValue(szFieldVal);
    }
}


/*-------------------------- your_category---------------------------------*/

template <class BaseT> inline
void VRMLNodeFactory<BaseT>::dumpTable(void)
{
#if 0
    NodeNameDescHash::iterator  mNodeDescIt = _mNodeDescHash.begin();
    FieldNameTypeHash::iterator mFieldHashIt;

    while(mNodeDescIt != _mNodeDescHash.end())
    {
        PLOG << "Node : " << mNodeDescIt->first << " "
                << mNodeDescIt->second << endl;
        
        mFieldHashIt = mNodeDescIt->second->_mFieldTypes.begin();

        while(mFieldHashIt != mNodeDescIt->second->_mFieldTypes.end())
        {
            PLOG << "\tField : " << mFieldHashIt->first << " "
                    << mFieldHashIt->second << endl;

             mFieldHashIt++;
        }

        mNodeDescIt++;
    }
#endif
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

OSG_END_NAMESPACE
