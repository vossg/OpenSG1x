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

#include <OSGLog.h>
#include <OSGFieldContainer.h>
#include <OSGFieldContainerPtr.h>
#include <OSGNode.h>
#include <OSGNodeCore.h>
#include <OSGGroup.h>
#include <OSGGeometry.h>
#include <OSGComponentTransform.h>
#include <OSGGeoPropPtrs.h>
#include <OSGSimpleMaterial.h>
#include <OSGMaterialGroup.h>
#include "OSGAction.h"
#include "OSGVRMLWriteAction.h"

#include <GL/gl.h>

#include "functional"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DrawAction
    \ingroup ActionLib

The draw action class.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

VRMLWriteAction::ActionInitializer::ActionInitializer(void)
{
    addInitFunction(&VRMLWriteAction::initializeAction);
    addExitFunction(&VRMLWriteAction::terminateAction);
}

VRMLWriteAction::ActionInitializer::~ActionInitializer(void)
{
}

VRMLWriteAction::FCInfo::FCInfo(void) :
    _iTimesUsed(0),
    _bOwnName   (false),
    _szName     (NULL)
{
}

VRMLWriteAction::FCInfo::FCInfo(const FCInfo &source) :
    _iTimesUsed(source._iTimesUsed),
    _bOwnName  (source._bOwnName),
    _szName    (NULL)
{
    if(_bOwnName == true)
    {
        stringDup(source._szName, _szName);
    }
}

VRMLWriteAction::FCInfo::~FCInfo(void)
{
    if(_bOwnName == true)
        delete [] _szName;
}

void VRMLWriteAction::FCInfo::convertName(Char8 *szName)
{
    if(szName == NULL)
        return;

    switch(szName[0])
    {
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x34:
        case 0x35:
        case 0x36:
        case 0x37:
        case 0x38:
        case 0x39:
        case 0x2b: 
        case 0x2d:
        {
            szName[0]='_';
            break;
        }
    }
    
    for(UInt32 i = 0; i < strlen(szName); i++)
    {
        if(szName[i] <= 0x20)
        {
            szName[i]='_';
        }
        else
        {
            switch(szName[i])
            {
                case 0x22: 
                case 0x23:
                case 0x27:
                case 0x2c:
                case 0x2e:
                case 0x5b:
                case 0x5c:
                case 0x5d:
                case 0x7b:
                case 0x7d:
                case 0x7f:
                {
                    szName[i]='_';
                    break;
                }
            }
        }
    }
}

void VRMLWriteAction::FCInfo::setName(const Char8 *szName)
{
    stringDup(szName, _szName);
    convertName(_szName);
    _bOwnName = true;
}

void VRMLWriteAction::FCInfo::buildName(const Char8  *szTypename,
                                              UInt32  uiContainerId)
{
    if(_szName != NULL)
        return;

    if(szTypename != NULL)
    {
        _szName = new Char8[strlen(szTypename) + 32];

        sprintf(_szName, "%s_%d", szTypename, uiContainerId);
    }
    else
    {
        _szName = new Char8[64];
        
        sprintf(_szName, "UType_%d", uiContainerId);
    }

    _bOwnName = true;
}

void VRMLWriteAction::FCInfo::incUse(void)
{
    _iTimesUsed++;
}

UInt32 VRMLWriteAction::FCInfo::getUse(void) const
{
    return _iTimesUsed;
}

const Char8 *VRMLWriteAction::FCInfo::getName(void) const
{
    return _szName;
}

Bool VRMLWriteAction::FCInfo::getWriten(void) const
{
    return _iTimesUsed < 0;
}

void VRMLWriteAction::FCInfo::setWriten(void)
{
    _iTimesUsed = -1;
}

Int32 VRMLWriteAction::FCInfo::clear(void)
{
    _iTimesUsed = 0;

    if(_bOwnName == true)
    {
        delete [] _szName;
    }

    _bOwnName = false;
    _szName   = NULL;

    return 0;
}

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char VRMLWriteAction::cvsid[] = "@(#)$Id: $";

VRMLWriteAction * VRMLWriteAction::_prototype = NULL;

vector<Action::Functor> *VRMLWriteAction::_defaultEnterFunctors;
vector<Action::Functor> *VRMLWriteAction::_defaultLeaveFunctors;

VRMLWriteAction::ActionInitializer VRMLWriteAction::_actionInitializer;


/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/



/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

void VRMLWriteAction::registerEnterDefault(const FieldContainerType &type, 
                                           const Action::Functor    &func)
{
    if(!_defaultEnterFunctors)
        _defaultEnterFunctors = new vector<Action::Functor>;

    while(type.getId() >= _defaultEnterFunctors->size())
    {
        _defaultEnterFunctors->push_back( 
                osgFunctionFunctor2(&Action::_defaultEnterFunction));
    }
    
    (*_defaultEnterFunctors)[ type.getId() ] = func;
}

void VRMLWriteAction::registerLeaveDefault(const FieldContainerType &type, 
                                           const Action::Functor    &func)
{
    if(! _defaultLeaveFunctors)
        _defaultLeaveFunctors = new vector<Action::Functor>;

    while(type.getId() >= _defaultLeaveFunctors->size())
    {
        _defaultLeaveFunctors->push_back( 
                osgFunctionFunctor2(&Action::_defaultLeaveFunction));
    }
    
    (*_defaultLeaveFunctors)[ type.getId() ] = func;
}


void VRMLWriteAction::setPrototype(VRMLWriteAction *proto)
{
    _prototype = proto;
}

VRMLWriteAction *VRMLWriteAction::getPrototype( void )
{
    return _prototype;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

Action::ResultE VRMLWriteAction::writeGroupEnter(CNodePtr &pGroup,
                                                 Action   *pAction)
{
    VRMLWriteAction *pWriter = dynamic_cast<VRMLWriteAction *>(pAction);

    NodePtr pNode(pGroup);

    if(pWriter == NULL)
    {
        return Action::Quit;
    }

    fprintf(stderr, "Write Group Enter 0x%04x\n", pWriter->getMode());

    if(pWriter->getMode() == VRMLWriteAction::OSGCollectFC)
    {
        pWriter->addNodeUse(pGroup);
    }
    else
    {
        FILE *pFile = pWriter->getFilePtr();
        
        if(pFile == NULL)    
        {
            return Action::Quit;
        }

        FCInfo *pInfo = pWriter->getInfo(pGroup);

        if(pInfo == NULL)
        {
            return Action::Quit;
        }

        if((pInfo->getName()    != NULL ) &&
           (pInfo->getWriten() == false))
        {
            pWriter->printIndent();
            fprintf(pFile, "DEF %s Group\n", pInfo->getName());

            pInfo->setWriten();
        }
        else
        {
            pWriter->printIndent();
            fprintf(pFile, "Group\n");
        }
                    
        pWriter->printIndent();
        fprintf(pFile, "{\n");

        if(pNode->getNChildren() != 0)
        {
            pWriter->incIndent(4);
            
            pWriter->printIndent();
            fprintf(pFile, "children [\n");
        
            pWriter->incIndent(4);        
        }
    }

    return Action::Continue;
}

Action::ResultE VRMLWriteAction::writeGroupLeave(CNodePtr &pGroup,
                                                 Action   *pAction)
{
    VRMLWriteAction *pWriter = dynamic_cast<VRMLWriteAction *>(pAction);

    NodePtr pNode(pGroup);

    if(pWriter == NULL)
    {
        return Action::Quit;
    }

    fprintf(stderr, "Write Group Leave 0x%04x\n", pWriter->getMode());

    if(pWriter->getMode() != VRMLWriteAction::OSGCollectFC)
    {
        FILE *pFile = pWriter->getFilePtr();
        
        if(pFile == NULL)    
        {
            return Action::Quit;
        }

        if(pNode->getNChildren() != 0)
        {
            pWriter->decIndent(4);
            
            pWriter->printIndent();
            fprintf(pFile, "]\n");

            pWriter->decIndent(4);
        }

        pWriter->printIndent();
        fprintf(pFile, "}\n");
    }

    return Action::Continue;
}

Action::ResultE VRMLWriteAction::writeVTransformEnter(CNodePtr &pGroup,
                                                      Action   *pAction)
{
    VRMLWriteAction *pWriter = dynamic_cast<VRMLWriteAction *>(pAction);

    ComponentTransformPtr pTrans = 
        ComponentTransformPtr::dcast(pGroup.getNode()->getCore());

    Real32 rQX;
    Real32 rQY;
    Real32 rQZ;
    Real32 rQW;

    if(pWriter == NULL)
    {
        return Action::Quit;
    }

    fprintf(stderr, "Write VTransform Enter 0x%04x\n", pWriter->getMode());

    if(pWriter->getMode() == VRMLWriteAction::OSGCollectFC)
    {
        pWriter->addNodeUse(pGroup);
    }
    else
    {
        FILE *pFile = pWriter->getFilePtr();
        
        if(pFile == NULL)    
        {
            return Action::Quit;
        }

        FCInfo *pInfo = pWriter->getInfo(pGroup);

        if(pInfo == NULL)
        {
            return Action::Quit;
        }

        if((pInfo->getName() != NULL) &&
           (pInfo->getWriten() == false))
        {
            pWriter->printIndent();
            fprintf(pFile, "DEF %s Transform\n", pInfo->getName());

            pInfo->setWriten();
        }
        else
        {
            pWriter->printIndent();
            fprintf(pFile, "Transform\n");
        }

        pWriter->printIndent();
        fprintf(pFile, "{\n");

        pWriter->incIndent(4);

        pWriter->printIndent();
        fprintf(pFile, "center %f %f %f\n",
                pTrans->getCenter()[0],
                pTrans->getCenter()[1],
                pTrans->getCenter()[2]);

        pTrans->getRotation().getValueAsAxisRad(rQX, rQY, rQZ, rQW);

        pWriter->printIndent();
        fprintf(pFile, "rotation %f %f %f %f\n",
                rQX, rQY, rQZ, rQW);

        pWriter->printIndent();
        fprintf(pFile, "scale %f %f %f\n",
                pTrans->getScale()[0],
                pTrans->getScale()[1],
                pTrans->getScale()[2]);

        pTrans->getScaleOrientation().getValueAsAxisRad(rQX, rQY, rQZ, rQW);

        pWriter->printIndent();
        fprintf(pFile, "scaleOrientation %f %f %f %f\n",
                rQX, rQY, rQZ, rQW);

        pWriter->printIndent();
        fprintf(pFile, "translation %f %f %f\n", 
                pTrans->getTranslation()[0],
                pTrans->getTranslation()[1],
                pTrans->getTranslation()[2]);

        pWriter->printIndent();
        fprintf(pFile, "children [\n");

        pWriter->incIndent(4);
    }

    return Action::Continue;
}

Action::ResultE VRMLWriteAction::writeVTransformLeave(CNodePtr &pGroup,
                                                      Action   *pAction)
{
    VRMLWriteAction *pWriter = dynamic_cast<VRMLWriteAction *>(pAction);

    if(pWriter == NULL)
    {
        return Action::Quit;
    }

    fprintf(stderr, "Write VTransform Leave 0x%04x\n", pWriter->getMode());

    if(pWriter->getMode() != VRMLWriteAction::OSGCollectFC)
    {
        FILE *pFile = pWriter->getFilePtr();
        
        if(pFile == NULL)    
        {
            return Action::Quit;
        }

        pWriter->decIndent(4);

        pWriter->printIndent();
        fprintf(pFile, "]\n");

        pWriter->decIndent(4);

        pWriter->printIndent();
        fprintf(pFile, "}\n");
    }

    return Action::Continue;
}

void VRMLWriteAction::writePoints(GeometryPtr      pGeo, 
                                  FILE            *pFile,
                                  VRMLWriteAction *pWriter)
{
    if(pGeo == NullFC)
        return;

    GeoPositions3fPtr pPos = GeoPositions3fPtr::dcast(pGeo->getPositions());

    if(pPos == NullFC)
        return;

    GeoPositions3f::StoredFieldType *pPosField = pPos->getFieldPtr();

    if(pPosField         == NULL ||
       pPosField->size() == 0)
    {
        return;
    }

    pWriter->printIndent();
    fprintf(pFile, "coord Coordinate\n");

    pWriter->printIndent();
    fprintf(pFile, "{\n");
    pWriter->incIndent(4);

    pWriter->printIndent();
    fprintf(pFile, "point [\n");
    pWriter->incIndent(4);

    for(UInt32 i = 0; i < pPosField->size(); i++)
    {
        pWriter->printIndent();

        fprintf(pFile, "%f %f %f", 
                (*pPosField)[i][0],
                (*pPosField)[i][1],
                (*pPosField)[i][2]);

        if(i == pPosField->size() - 1)
        {
            fprintf(pFile, "\n");
        }
        else
        {
            fprintf(pFile, ",\n");
        }
    }

    pWriter->decIndent(4);
    pWriter->printIndent();
    fprintf(pFile, "]\n");

    pWriter->decIndent(4);
    pWriter->printIndent();
    fprintf(pFile, "}\n");

}

void VRMLWriteAction::writeNormals(GeometryPtr      pGeo, 
                                   FILE            *pFile,
                                   VRMLWriteAction *pWriter)
{
    if(pGeo == NullFC)
        return;

    GeoNormals3fPtr pNorm = GeoNormals3fPtr::dcast(pGeo->getNormals());

    if(pNorm == NullFC)
        return;

    GeoNormals3f::StoredFieldType *pNormField = pNorm->getFieldPtr();

    if(pNormField         == NULL ||
       pNormField->size() == 0)
    {
        return;
    }

    pWriter->printIndent();
    fprintf(pFile, "normal Normal\n");

    pWriter->printIndent();
    fprintf(pFile, "{\n");
    pWriter->incIndent(4);

    pWriter->printIndent();
    fprintf(pFile, "vector [\n");
    pWriter->incIndent(4);

    for(UInt32 i = 0; i < pNormField->size(); i++)
    {
        pWriter->printIndent();

        fprintf(pFile, "%f %f %f", 
                (*pNormField)[i][0],
                (*pNormField)[i][1],
                (*pNormField)[i][2]);

        if(i == pNormField->size() - 1)
        {
            fprintf(pFile, "\n");
        }
        else
        {
            fprintf(pFile, ",\n");
        }
    }

    pWriter->decIndent(4);
    pWriter->printIndent();
    fprintf(pFile, "]\n");

    pWriter->decIndent(4);
    pWriter->printIndent();
    fprintf(pFile, "}\n");
}

void VRMLWriteAction::writeTexCoords(GeometryPtr      pGeo, 
                                     FILE            *pFile,
                                     VRMLWriteAction *pWriter)
{
    if(pGeo == NullFC)
        return;

    GeoTexCoords2fPtr pTex = GeoTexCoords2fPtr::dcast(pGeo->getTexCoords());

    if(pTex == NullFC)
        return;

    GeoTexCoords2f::StoredFieldType *pTexField = pTex->getFieldPtr();

    if(pTexField         == NULL ||
       pTexField->size() == 0)
    {
        return;
    }

    pWriter->printIndent();
    fprintf(pFile, "texCoord TextureCoordinate\n");

    pWriter->printIndent();
    fprintf(pFile, "{\n");
    pWriter->incIndent(4);

    pWriter->printIndent();
    fprintf(pFile, "point [\n");
    pWriter->incIndent(4);

    for(UInt32 i = 0; i < pTexField->size(); i++)
    {
        pWriter->printIndent();

        fprintf(pFile, "%f %f %f", 
                (*pTexField)[i][0],
                (*pTexField)[i][1],
                (*pTexField)[i][2]);

        if(i == pTexField->size() - 1)
        {
            fprintf(pFile, "\n");
        }
        else
        {
            fprintf(pFile, ",\n");
        }
    }

    pWriter->decIndent(4);
    pWriter->printIndent();
    fprintf(pFile, "]\n");

    pWriter->decIndent(4);
    pWriter->printIndent();
    fprintf(pFile, "}\n");
}

void VRMLWriteAction::writeIndex(GeometryPtr      pGeo, 
                                 FILE            *pFile,
                                 VRMLWriteAction *pWriter)
{
    UInt32 j;

    if(pGeo == NullFC)
        return;

    GeoIndicesUI32Ptr   pIndex  = GeoIndicesUI32Ptr::dcast(pGeo->getIndices());
    GeoPTypesUI8Ptr    pTypes  = GeoPTypesUI8Ptr::dcast(pGeo->getTypes());
    GeoPLengthsUI32Ptr pLength = GeoPLengthsUI32Ptr::dcast(pGeo->getLengths());

    if((pIndex  == NullFC) ||
       (pTypes  == NullFC) ||
       (pLength == NullFC))
    {
        return;
    }

    GeoIndicesUI32::StoredFieldType   *pIndexField  = pIndex->getFieldPtr();
    GeoPTypesUI8::StoredFieldType    *pTypeField   = pTypes->getFieldPtr();
    GeoPLengthsUI32::StoredFieldType *pLengthField = pLength->getFieldPtr();

    if(pIndexField          == NULL ||
       pIndexField->size()  == 0    ||
       pTypeField           == NULL ||
       pTypeField->size()   == 0    ||
       pLengthField         == NULL ||
       pLengthField->size() == 0)
    {
        return;
    }

    UInt32 uiCurrentIndex = 0;

    pWriter->printIndent();
    fprintf(pFile, "coordIndex [\n");
    pWriter->incIndent(4);


    for(UInt32 i = 0; i < pLengthField->size(); i++)
    {
        switch((*pTypeField)[i])
        {
            case GL_TRIANGLES:
                for(j = 0; j < (*pLengthField)[i]; j+=3)
                {
                    pWriter->printIndent();
                    fprintf(pFile, "%d,", (*pIndexField)[uiCurrentIndex++]);
                    fprintf(pFile, "%d,", (*pIndexField)[uiCurrentIndex++]);
                    fprintf(pFile, "%d,", (*pIndexField)[uiCurrentIndex++]);

                    if(j == (*pLengthField)[i] - 4)
                    {
                        fprintf(pFile, "-1\n");
                    }
                    else
                    {
                        fprintf(pFile, "-1,\n");
                    }
                }
                break;

            case GL_TRIANGLE_STRIP:
                for(j = 0; j < (*pLengthField)[i]; j++)
                {
                    pWriter->printIndent();
                    fprintf(pFile, "%d,", (*pIndexField)[uiCurrentIndex]);
					if ( uiCurrentIndex & 1 )
					{
                    	fprintf(pFile, "%d,", (*pIndexField)[uiCurrentIndex+2]);
                    	fprintf(pFile, "%d,", (*pIndexField)[uiCurrentIndex+1]);
					}
					else
					{
                    	fprintf(pFile, "%d,", (*pIndexField)[uiCurrentIndex+1]);
                    	fprintf(pFile, "%d,", (*pIndexField)[uiCurrentIndex+2]);
					}
					uiCurrentIndex++;
					
                    if(j == (*pLengthField)[i] - 4)
                    {
                        fprintf(pFile, "-1\n");
                    }
                    else
                    {
                        fprintf(pFile, "-1,\n");
                    }
                }
                break;

            case GL_POLYGON:
                pWriter->printIndent();

                for(j = 0; j < (*pLengthField)[i]; j++)
                {
                    fprintf(pFile, "%d, ", (*pIndexField)[uiCurrentIndex++]);
                }

                if(i == pLengthField->size() - 1)
                {
                    fprintf(pFile, "-1\n");
                }
                else
                {
                    fprintf(pFile, "-1,\n");
                }
                break;
            
            default:
                fprintf(stderr, "Primitive %d currently not supported\n",
                        (*pTypeField)[i]);
                break;
        }
    }

    pWriter->decIndent(4);
    pWriter->printIndent();
    fprintf(pFile, "]\n");
}

void VRMLWriteAction::writeMaterial(GeometryPtr      pGeo, 
                                    FILE            *pFile,
                                    VRMLWriteAction *pWriter)
{
    if(pGeo == NullFC)
        return;

    MaterialPtr pMat = pGeo->getMaterial();

    SimpleMaterialPtr pSMat = SimpleMaterialPtr::dcast(pMat);

    if(pSMat == NullFC)
        return;

    pWriter->printIndent();
    fprintf(pFile, "appearance Appearance\n");
    
    pWriter->printIndent();
    fprintf(pFile, "{\n");
    
    pWriter->incIndent(4);
    
    pWriter->printIndent();
    fprintf(pFile, "material Material\n");
    
    pWriter->printIndent();
    fprintf(pFile, "{\n");
    
    pWriter->incIndent(4);

    Real32 rAmbient = 0.f;

    if(osgabs(pSMat->getDiffuse()[0]) > Eps)
    {
        rAmbient = pSMat->getAmbient()[0] / pSMat->getDiffuse()[0];
    }
    else if(osgabs(pSMat->getDiffuse()[1]) > Eps)
    {
        rAmbient = pSMat->getAmbient()[1] / pSMat->getDiffuse()[1];
    }
    else if(osgabs(pSMat->getDiffuse()[2]) > Eps)
    {
        rAmbient = pSMat->getAmbient()[2] / pSMat->getDiffuse()[2];
    }


    pWriter->printIndent();
    fprintf(pFile, "ambientIntensity %f\n", rAmbient);

    pWriter->printIndent();
    fprintf(pFile, "diffuseColor %f %f %f\n",
            pSMat->getDiffuse()[0],
            pSMat->getDiffuse()[1],
            pSMat->getDiffuse()[2]);

    pWriter->printIndent();
    fprintf(pFile, "emissiveColor %f %f %f\n",
            pSMat->getEmission()[0],
            pSMat->getEmission()[1],
            pSMat->getEmission()[2]);

    pWriter->printIndent();
    fprintf(pFile, "shininess %f\n",
            pSMat->getShininess());

    pWriter->printIndent();
    fprintf(pFile, "specularColor %f %f %f\n",
            pSMat->getSpecular()[0],
            pSMat->getSpecular()[1],
            pSMat->getSpecular()[2]);

    pWriter->printIndent();
    fprintf(pFile, "transparency %f\n",
            pSMat->getTransparency());
    
    pWriter->decIndent(4);
    
    pWriter->printIndent();
    fprintf(pFile, "}\n");

    
    pWriter->decIndent(4);
    
    pWriter->printIndent();
    fprintf(pFile, "}\n");
}

Action::ResultE VRMLWriteAction::writeGeoEnter(CNodePtr &pGroup,
                                               Action   *pAction)
{
    VRMLWriteAction *pWriter = dynamic_cast<VRMLWriteAction *>(pAction);

    GeometryPtr pGeo = 
        GeometryPtr::dcast(pGroup.getNode()->getCore());

    if(pWriter == NULL || pGeo == NullFC)
    {
        return Action::Quit;
    }

    fprintf(stderr, "Write Geo Enter 0x%04x\n", pWriter->getMode());

    if(pWriter->getMode() == VRMLWriteAction::OSGCollectFC)
    {
        pWriter->addNodeUse(pGroup);

        pWriter->addContainerUse(pGeo->getPositions());
        pWriter->addContainerUse(pGeo->getNormals  ());
        pWriter->addContainerUse(pGeo->getColors   ());
        pWriter->addContainerUse(pGeo->getTexCoords());
    }
    else
    {
        FILE *pFile = pWriter->getFilePtr();
        
        if(pFile == NULL)    
        {
            return Action::Quit;
        }

        FCInfo *pInfo = pWriter->getInfo(pGroup);
//        FCInfo *pGeoInfo

        if(pInfo == NULL)
        {
            return Action::Quit;
        }

        if(pInfo->getName() != NULL)
        {
            pWriter->printIndent();
            fprintf(pFile, "DEF %s Shape\n", pInfo->getName());
            pInfo->setWriten();
        }
        else
        {
            pWriter->printIndent();
            fprintf(pFile, "Shape\n");
        }

        pWriter->printIndent();
        fprintf(pFile, "{\n");

        pWriter->incIndent(4);

        pWriter->printIndent();
        fprintf(pFile, "geometry IndexedFaceSet\n");

        pWriter->printIndent();
        fprintf(pFile, "{\n");

        pWriter->incIndent(4);

        pWriter->printIndent();
// !!!        fprintf(pFile, "colorPerVertex  %s\n", 
// !!!                pGeo->getColorPerVertex() ? "TRUE" : "FALSE");

        pWriter->printIndent();
// !!!        fprintf(pFile, "normalPerVertex %s\n",
// !!!                pGeo->getNormalPerVertex() ? "TRUE" : "FALSE");

        writePoints   (pGeo, pFile, pWriter);
        writeNormals  (pGeo, pFile, pWriter);
        writeTexCoords(pGeo, pFile, pWriter);
        writeIndex    (pGeo, pFile, pWriter);
        pWriter->decIndent(4);

        pWriter->printIndent();
        fprintf(pFile, "}\n");

        writeMaterial(pGeo, pFile, pWriter);
    }

    return Action::Continue;
}

Action::ResultE VRMLWriteAction::writeGeoLeave(CNodePtr &pGroup,
                                               Action   *pAction)
{
    VRMLWriteAction *pWriter = dynamic_cast<VRMLWriteAction *>(pAction);

    if(pWriter == NULL)
    {
        return Action::Quit;
    }

    fprintf(stderr, "Write Geo Leave 0x%04x\n", pWriter->getMode());

    if(pWriter->getMode() != VRMLWriteAction::OSGCollectFC)
    {
        FILE *pFile = pWriter->getFilePtr();
        
        if(pFile == NULL)    
        {
            return Action::Quit;
        }

        pWriter->decIndent(4);

        pWriter->printIndent();
        fprintf(pFile, "}\n");
    }

    return Action::Continue;
}

Action::ResultE VRMLWriteAction::writeMatGroupEnter(CNodePtr &pGroup,
                                                    Action   *pAction)
{
    
    return Action::Continue;
}

Action::ResultE VRMLWriteAction::writeMatGroupLeave(CNodePtr &pGroup,
                                                    Action   *pAction)
{

    return Action::Continue;
}


Bool VRMLWriteAction::initializeAction(int &, char **)
{
    FINFO(( "Init VRMLWriter\n" ));

#ifndef OSG_NOFUNCTORS

    VRMLWriteAction::registerEnterDefault( 
        Group::getClassType(), 
        osgFunctionFunctor2<Action::ResultE,
                            CNodePtr &, 
                            Action *>(VRMLWriteAction::writeGroupEnter));

    VRMLWriteAction::registerEnterDefault( 
        ComponentTransform::getClassType(), 
        osgFunctionFunctor2<Action::ResultE,
                            CNodePtr &, 
                            Action *>(VRMLWriteAction::writeVTransformEnter));

    VRMLWriteAction::registerEnterDefault( 
        Geometry::getClassType(), 
        osgFunctionFunctor2<Action::ResultE,
                            CNodePtr &, 
                            Action *>(VRMLWriteAction::writeGeoEnter));

    VRMLWriteAction::registerEnterDefault( 
        MaterialGroup::getClassType(), 
        osgFunctionFunctor2<Action::ResultE,
                            CNodePtr &, 
                            Action *>(VRMLWriteAction::writeMatGroupEnter));



    VRMLWriteAction::registerLeaveDefault(
        Group::getClassType(), 
        osgFunctionFunctor2<Action::ResultE,
                            CNodePtr &,
                            Action *>(&VRMLWriteAction::writeGroupLeave));

    VRMLWriteAction::registerLeaveDefault(
        ComponentTransform::getClassType(), 
        osgFunctionFunctor2<Action::ResultE,
                            CNodePtr &,
                            Action *>(&VRMLWriteAction::writeVTransformLeave));

    VRMLWriteAction::registerLeaveDefault(
        Geometry::getClassType(), 
        osgFunctionFunctor2<Action::ResultE,
                            CNodePtr &,
                            Action *>(&VRMLWriteAction::writeGeoLeave));

    VRMLWriteAction::registerLeaveDefault(
        Group::getClassType(), 
        osgFunctionFunctor2<Action::ResultE,
                            CNodePtr &,
                            Action *>(&VRMLWriteAction::writeMatGroupLeave));

#else

    VRMLWriteAction::registerEnterDefault( 
        Group::getClassType(), 
        Action::osgFunctionFunctor2(VRMLWriteAction::writeGroupEnter));

    VRMLWriteAction::registerEnterDefault( 
        ComponentTransform::getClassType(), 
        Action::osgFunctionFunctor2(VRMLWriteAction::writeVTransformEnter));

    VRMLWriteAction::registerEnterDefault( 
        Geometry::getClassType(), 
        Action::osgFunctionFunctor2(VRMLWriteAction::writeGeoEnter));



    VRMLWriteAction::registerLeaveDefault(
        Group::getClassType(), 
        Action::osgFunctionFunctor2(&VRMLWriteAction::writeGroupLeave));

    VRMLWriteAction::registerLeaveDefault(
        ComponentTransform::getClassType(), 
        Action::osgFunctionFunctor2(&VRMLWriteAction::writeVTransformLeave));

    VRMLWriteAction::registerLeaveDefault(
        Geometry::getClassType(), 
        Action::osgFunctionFunctor2(&VRMLWriteAction::writeGeoLeave));

#endif

    return true;
}

Bool VRMLWriteAction::terminateAction(void)
{
    fprintf(stderr, "Terminate VRMLWriter\n");

    return true;
}


void VRMLWriteAction::incIndent(UInt32 uiDelta)
{
    _uiIndent += uiDelta;
}

void VRMLWriteAction::decIndent(UInt32 uiDelta)
{
    _uiIndent -= uiDelta;
}

void VRMLWriteAction::printIndent(void)
{
    if(_pFile != NULL)
    {
        for(UInt32 i = 0; i < _uiIndent; i++)
        {
            fprintf(_pFile, " ");
        }
    }
}

void VRMLWriteAction::addNodeUse(CNodePtr &pCNode)
{ 
    if(pCNode == NullFC)
        return;
    
    NodePtr     pNode(pCNode);
    NodeCorePtr pCore = pNode->getCore();

    if((pNode.getFieldContainerId() >= _vFCInfos.size()) ||
       (pCore.getFieldContainerId() >= _vFCInfos.size()))
    {
        return;
    }
    
    FCInfo *pInfoNode = &(_vFCInfos[pNode.getFieldContainerId()]);
    FCInfo *pInfoCore = &(_vFCInfos[pCore.getFieldContainerId()]);

    NamePtr pNodename =
        NamePtr::dcast(pNode->findAttachment(
            Name::getClassType().getGroupId()));

    NamePtr pCorename =
        NamePtr::dcast(pCore->findAttachment(
            Name::getClassType().getGroupId()));

    pInfoNode->incUse();
    pInfoCore->incUse();

    if(pNodename != NullFC)
    {
        pInfoNode->setName(pNodename->getFieldPtr()->getValue().c_str());
    }

    if(pCorename != NullFC)
    {
        pInfoCore->setName(pCorename->getFieldPtr()->getValue().c_str());
    }

    if(pInfoCore->getUse() > 1)
    {
        pInfoCore->buildName(pCore->getTypeName(), 
                             pCore. getFieldContainerId());
    }
}

void VRMLWriteAction::addContainerUse(FieldContainerPtr &pContainer)
{
    if(pContainer == NullFC)
        return;
    
    if(pContainer.getFieldContainerId() >= _vFCInfos.size())
    {
        return;
    }
    
    FCInfo *pInfo = &(_vFCInfos[pContainer.getFieldContainerId()]);

    pInfo->incUse();

    if(pInfo->getUse() > 1)
    {
        pInfo->buildName(pContainer->getTypeName(), 
                         pContainer. getFieldContainerId());
    }
}

VRMLWriteAction::FCInfo *VRMLWriteAction::getInfo(CNodePtr &pNode)
{
    if(pNode == NullFC)
        return NULL;

    if(pNode.getFieldContainerId() >= _vFCInfos.size())
        return NULL;

    return &(_vFCInfos[pNode.getFieldContainerId()]);
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

VRMLWriteAction::VRMLWriteAction(void) :
     Inherited     (),
    _material      (NULL),
    _uiIndent      (0),
    _pFile         (NULL),
    _eTraversalMode(OSGCollectFC),
    _vFCInfos      ()
{
    if(_defaultEnterFunctors)
        _enterFunctors = *_defaultEnterFunctors;

    if(_defaultLeaveFunctors)
        _leaveFunctors = *_defaultLeaveFunctors;
}


/** \brief Copy-Constructor
 */

VRMLWriteAction::VRMLWriteAction(const VRMLWriteAction &source) :
     Inherited     (source),
    _material      (source._material),
    _uiIndent      (source._uiIndent),
    _pFile         (NULL),
    _eTraversalMode(source._eTraversalMode),
    _vFCInfos      (source._vFCInfos)
{
    if(_defaultEnterFunctors)
        _enterFunctors = *_defaultEnterFunctors;

    if(_defaultLeaveFunctors)
        _leaveFunctors = *_defaultLeaveFunctors;
}

/** \brief create a new action
 */

VRMLWriteAction *VRMLWriteAction::create( void )
{
    VRMLWriteAction * act;
    
    if(_prototype)
        act = new VRMLWriteAction(*_prototype);
    else
        act = new VRMLWriteAction();
    
    return act;
}


/** \brief Destructor
 */

VRMLWriteAction::~VRMLWriteAction(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/
    
void VRMLWriteAction::setMaterial(Material *material)
{
    _material = material;
}

Bool VRMLWriteAction::open(const Char8 *szFilename)
{
    if(szFilename != NULL)
    {
        _pFile = fopen(szFilename, "w");

        if(_pFile != NULL)
        {
            fprintf(_pFile, "#VRML V2.0 utf8 \n");
        }
    }

    return _pFile != NULL;
}

void VRMLWriteAction::close(void)
{
    if(_pFile != NULL)
    {
        fclose(_pFile);
    }
}

Action::ResultE VRMLWriteAction::write(NodePtr node)
{
    Action::ResultE returnValue = Action::Continue;
    
    _eTraversalMode = OSGCollectFC;

    for_each(_vFCInfos.begin(), 
             _vFCInfos.end(), 
             mem_fun_ref(&FCInfo::clear));
    
    _vFCInfos.resize(
        FieldContainerFactory::the()->getFieldContainerStore()->size());

    returnValue = Inherited::apply(node);

    if(returnValue == Action::Continue)
    {
        _eTraversalMode = OSGWrite;
        returnValue = Inherited::apply(node);
    }

    return returnValue;
}

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

/*

DrawAction& DrawAction::operator = (const DrawAction &source)
{
    if (this == &source)
        return *this;

    // copy parts inherited from parent
    *(static_cast<Inherited *>(this)) = source;

    // free mem alloced by members of 'this'

    // alloc new mem for members

    // copy 
}

*/

/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */

Bool VRMLWriteAction::operator < (const VRMLWriteAction &other) const
{
    return this < &other;
}

/** \brief equal
 */

Bool VRMLWriteAction::operator == (const VRMLWriteAction &other) const
{
    return false;
}

/** \brief unequal
 */

Bool VRMLWriteAction::operator != (const VRMLWriteAction &other) const
{
    return ! (*this == other);
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


vector<VRMLWriteAction::Functor> *VRMLWriteAction::getDefaultEnterFunctors(
    void)
{
    return _defaultEnterFunctors;
}

vector<VRMLWriteAction::Functor> *VRMLWriteAction::getDefaultLeaveFunctors(
    void)
{
    return _defaultLeaveFunctors;
}

Action::ResultE VRMLWriteAction::apply(vector<NodePtr>::iterator begin, 
                                       vector<NodePtr>::iterator end)
{
    return Inherited::apply(begin, end);
}

Action::ResultE VRMLWriteAction::apply(NodePtr node)
{
    return Inherited::apply(node);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



///---------------------------------------------------------------------------
///  FUNCTION: 
///---------------------------------------------------------------------------
//:  Example for the head comment of a function
///---------------------------------------------------------------------------
///
//p: Paramaters: 
//p: 
///
//g: GlobalVars:
//g: 
///
//r: Return:
//r: 
///
//c: Caution:
//c: 
///
//a: Assumptions:
//a: 
///
//d: Description:
//d: 
///
//s: SeeAlso:
//s: 
///---------------------------------------------------------------------------

