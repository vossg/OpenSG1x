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

#define OSG_COMPILEDATASTORE

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include <algorithm>

//#include "OSGDataStoreType.h"
//#include "OSGDataStoreFactory.h"

#include "OSGReflexiveContainerType.h"
#include "OSGDataElementDesc.h"
#include "OSGLog.h"

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

bool ReflexiveContainerType::initBaseType(void)
{
    return true;
}

bool ReflexiveContainerType::initFields(void)
{
    bool      returnValue = true;
    UInt32    i;
	DescMapIt descIt;

    for(i = 0; i < _vDesc.size(); i++) 
    {
        if(_vDesc[i]->isValid()) 
        {
            descIt = _mDescMap.find(IDStringLink(_vDesc[i]->getCName()));

            if(descIt == _mDescMap.end())
            {
                _mDescMap[IDStringLink(_vDesc[i]->getCName())] = _vDesc[i];

                _vDescVec.push_back(_vDesc[i]); 
            }
            else
            {
                SWARNING << "ERROR: Double field description " 
                         << "in " << _szName.str() << "from " 
                         << _vDesc[i]->getCName() 
                         << _vDesc[i]->getTypeId() << endl;

                returnValue = false;
            }
        }
        else
        {
            SWARNING << "ERROR: Invalid field description " 
                     << "in " << _szName.str() << "from " 
                     << _vDesc[i]->getTypeId() << endl;
            
            returnValue = false;
        }

    }

    sort(_vDescVec.begin(), _vDescVec.end(), DataElementDescPLT());

    return returnValue;
}

bool ReflexiveContainerType::initParentFields(void)
{
    bool      returnValue = false;
	DescMapIt dPIt;

    if(_bTypeBaseInitialized == false)
        return returnValue;
            
    returnValue = true;

    _pReflexParent = dynamic_cast<ReflexiveContainerType *>(_pParentType);

    if(_pReflexParent != NULL) 
    {
        if(_pReflexParent->isInitialized() == true)
        {
            for(  dPIt  = _pReflexParent->_mDescMap.begin();
                  dPIt != _pReflexParent->_mDescMap.end(); 
                ++dPIt) 
            {
                if(_mDescMap.find((*dPIt).first) == _mDescMap.end())
                {
                    _mDescMap[(*dPIt).first] = (*dPIt).second;
                }
                else
                {
                    SWARNING << "ERROR: Can't add field "
                             << "description a second time: " 
                             << (*dPIt).first.str() << endl; 
                }
            } 				
            
            _vDescVec.insert(_vDescVec.end(),
                             _pReflexParent->_vDescVec.begin(),
                             _pReflexParent->_vDescVec.end());
            
        }
        else 
        {
            SWARNING << "ERROR: parent not initialized "
                     << "name " << _szParentName.str() 
                     << endl;
            
            returnValue = false;
        }
    }

    return returnValue;
}

bool ReflexiveContainerType::initialize(void)
{
    if(Inherited::initialize() == false)
    {
        _bReflexTypeInitialized = false;

        return _bReflexTypeInitialized;
    }

    if(_bReflexTypeInitialized == true)
        return _bReflexTypeInitialized;

    if(_descInsertFunc != NULL)
    {
        _descInsertFunc(this);
    }

    _bReflexTypeInitialized = initParentFields();

    if(_bReflexTypeInitialized == false)
        return _bReflexTypeInitialized;

    _bReflexTypeInitialized = initFields      ();

    if(_bReflexTypeInitialized == false)
        return _bReflexTypeInitialized;

    _bReflexTypeInitialized = initBaseType    ();
    
    PINFO << "init ReflexiveContainerType (" 
          << _bReflexTypeInitialized
          << ")" 
          << endl;

    return _bReflexTypeInitialized;
}

void ReflexiveContainerType::terminate(void)
{
    _bReflexTypeInitialized = false;

    for(UInt32 i = 0; i < _vDesc.size(); ++i)
    {
        delete _vDesc[i];
    }
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

ReflexiveContainerType::ReflexiveContainerType(
    const Char8                *szName,
    const Char8                *szParentName,
    const Char8                *szGroupName,
    const UInt32                uiNameSpace,
          InitalInsertDescFunc  descInsertFunc,
          bool                  bDescsAddable) :

     Inherited(szName, szParentName, uiNameSpace),
    _uiGroupId(0),

    _bReflexTypeInitialized(false),
    _bDescsAddable         (bDescsAddable),
    _pReflexParent         (NULL),

    _szParentName  (szParentName),
    _szGroupName   (szGroupName),

    _vDesc         (),

	_mDescMap      (),
    _vDescVec      (),

    _descInsertFunc(descInsertFunc)
{
}

ReflexiveContainerType::~ReflexiveContainerType(void)
{
    terminate();
}


/*------------------------------ access -----------------------------------*/

UInt16 ReflexiveContainerType::getGroupId (void) const 
{
    return _uiGroupId; 
}

ReflexiveContainerType *ReflexiveContainerType::getParent(void) const
{
    return _pReflexParent; 
}


DataElementDesc *ReflexiveContainerType::getElementDesc(UInt32 uiElemId)
{
    if(uiElemId < _vDescVec.size())
        return _vDescVec[uiElemId];
    else
        return NULL;
}

const DataElementDesc *ReflexiveContainerType::getElementDesc(
    UInt32 uiElemId) const
{
    if(uiElemId < _vDescVec.size())
        return _vDescVec[uiElemId];
    else
        return NULL;
}

DataElementDesc *ReflexiveContainerType::findElementDesc(
    const Char8 *szElement)
{
    DescMapIt descIt = _mDescMap.find(IDStringLink(szElement));

    return (descIt == _mDescMap.end()) ? NULL : (*descIt).second;
}     

const DataElementDesc *ReflexiveContainerType::findElementDesc(
    const Char8 *szElement) const
{
    DescMapConstIt descIt = _mDescMap.find(IDStringLink(szElement));

    return (descIt == _mDescMap.end()) ? NULL : (*descIt).second;
}     

UInt32 ReflexiveContainerType::getNumElemDescs(void) const
{
    return _vDescVec.size();
}

UInt32 ReflexiveContainerType::addDescription(
    const DataElementDesc &desc)
{
    UInt32            returnValue = 0;
    DescMapConstIt    descIt;
    DescVecIt         descVIt;

    DataElementDesc  *pDesc;
    DataElementDesc  *pNullDesc = NULL;

    if(_bDescsAddable == false)
        return returnValue;

    descIt = _mDescMap.find(IDStringLink(desc.getCName()));

    if(desc.isValid())
    {
        if(descIt == _mDescMap.end()) 
        {
            pDesc = new DataElementDesc(desc);

            _mDescMap[IDStringLink(pDesc->getCName())] = pDesc;

            descVIt = find(_vDescVec.begin(), 
                           _vDescVec.end(),
                           pNullDesc);

            if(descVIt == _vDescVec.end())
            {
                _vDescVec.push_back(pDesc);

                returnValue = _vDescVec.size();
            }
            else
            {
                (*descVIt) = pDesc;

                returnValue  = descVIt - _vDescVec.begin();
            }
        }
        else
        {
            SWARNING << "ERROR: Double field description " 
                     << "in " << _szName.str() << "from " 
                     << desc.getCName() 
                     << desc.getTypeId() << endl;
        }
    }
    else
    {
        SWARNING << "ERROR: Invalid field description " 
                 << "in " << _szName.str() << "from " 
                 << desc.getTypeId() << endl;
    }

    return returnValue;
}

bool ReflexiveContainerType::subDescription(UInt32 uiFieldId)
{
    DataElementDesc  *pDesc = getElementDesc(uiFieldId);
    DescMapIt         descMIt;
    DescVecIt         descVIt;
    bool              returnValue = true;

    if(pDesc == NULL || _bDescsAddable == false)
        return false;

    descMIt = _mDescMap.find(IDStringLink(pDesc->getCName()));

    if(descMIt != _mDescMap.end())
    {
        _mDescMap.erase(descMIt);       
    }
    else
    {
        returnValue = false;
    }

    descVIt = find(_vDescVec.begin(), _vDescVec.end(), pDesc);

    if(descVIt != _vDescVec.end())
    {
        (*descVIt) = NULL;

        returnValue &= true;
    }
    else
    {
        returnValue = false;
    }

    delete pDesc;

    return returnValue;
}

bool ReflexiveContainerType::isInitialized(void) const
{
    return _bReflexTypeInitialized;
}

void ReflexiveContainerType::addInitialDesc(DataElementDesc *pDesc)
{
    if(pDesc != NULL)
    {
        _vDesc.push_back(pDesc);
    }
}

/*-------------------------- your_category---------------------------------*/

void ReflexiveContainerType::dump(      UInt32    uiIndent, 
                                  const BitVector bvFlags) const
{
    indentLog(uiIndent, PLOG);
    PLOG << "ReflexiveContainerType : " << endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << endl;

    uiIndent += 4;

    Inherited::dump(uiIndent, bvFlags);

    indentLog(uiIndent, PLOG);
    PLOG << "Descriptions" << endl;

    indentLog(uiIndent, PLOG);
    PLOG << "{" << endl;

    if(_vDescVec.size() == 0)
    {
        indentLog(uiIndent + 4, PLOG);
        PLOG << "<No Descriptions>" << endl;
    }
    else
    {
        for(UInt32 i = 0; i < _vDescVec.size(); i++)
        {
            _vDescVec[i]->dump(uiIndent + 4, bvFlags);
        }
    }

    indentLog(uiIndent, PLOG);
    PLOG << "}" << endl;

    uiIndent -= 4;
    
    indentLog(uiIndent, PLOG);
    PLOG << "}" << endl;
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGREFLEXIVECONTAINERTYPE_HEADER_CVSID;
}
