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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include <algorithm>

#include "OSGFieldContainerType.h"
#include "OSGFieldContainerFactory.h"
#include "OSGFieldDescription.h"

#include "OSGNode.h"
#include "OSGNodeCore.h"
#include "OSGAttachment.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGFIELDCONTAINERTYPE_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class osg::FieldContainerType
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

FieldContainerType::FieldContainerType(const Char8    *szName,
                                   const Char8        *szParentName,
                                   const Char8        *szGroupName,
                                   PrototypeCreateF    fPrototypeCreate,
                                   InitContainerF      fInitMethod,
                                   FieldDescription  **pDesc,
                                   UInt32              uiDescByteCounter,
                                   Bool                bDescsAddable) :
     Inherited        (szName, 
                       szParentName     ),
    _uiGroupId        (0                ),

    _bInitialized     (false            ),
    _bDescsAddable    (bDescsAddable    ),

    _baseType         (IsFieldContainer ),

    _pParent          (NULL             ),

    _szParentName     (szParentName     ),
    _szGroupName      (szGroupName      ),

    _pPrototype       (NullFC           ),
    _fPrototypeCreate (fPrototypeCreate ),

    _pDesc            (pDesc            ),
    _uiDescByteCounter(uiDescByteCounter),

    _mDescMap         (                 ),
    _vDescVec         (0                )
{
    registerType(szGroupName);

    if(fInitMethod != NULL)
        fInitMethod();
}

FieldContainerType::FieldContainerType(const FieldContainerType &obj) :

     Inherited        (obj.getCName(), 
                       obj.getCParentName()  ),
    _uiGroupId        (obj._uiGroupId        ),

    _bInitialized     (false                 ),
    _bDescsAddable    (obj._bDescsAddable    ),

    _baseType         (obj._baseType         ),

    _pParent          (obj._pParent          ),

    _szParentName     (obj._szParentName     ),
    _szGroupName      (obj._szGroupName      ),

    _pPrototype       (obj._pPrototype       ),
    _fPrototypeCreate (obj._fPrototypeCreate ),

    _pDesc            (obj._pDesc            ),
    _uiDescByteCounter(obj._uiDescByteCounter),

    _mDescMap         (                      ),
    _vDescVec         (0                     )
{
    if(_pPrototype != NullFC)
        addRefCP(_pPrototype);

    initFields();
    initParentFields();

    _bInitialized = true;
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

FieldContainerType::~FieldContainerType(void)
{
    if(GlobalSystemState != Shutdown)
    {
        terminate();
        FieldContainerFactory::the()->unregisterType(this);
    }
}


/*-------------------------------------------------------------------------*/
/*                                Get                                      */

UInt16 FieldContainerType::getGroupId (void) const
{
    return _uiGroupId;
}

FieldContainerType *FieldContainerType::getParent(void) const
{
    return _pParent;
}

FieldDescription *FieldContainerType::getFieldDescription(UInt32 uiFieldId)
{
    if(uiFieldId - 1 < _vDescVec.size())
        return _vDescVec[uiFieldId - 1];
    else
        return NULL;
}

const FieldDescription *FieldContainerType::getFieldDescription(
    UInt32 uiFieldId) const
{
    if(uiFieldId - 1 < _vDescVec.size())
        return _vDescVec[uiFieldId - 1];
    else
        return NULL;
}

FieldDescription *FieldContainerType::findFieldDescription(
    const Char8 *szFieldName)
{
    DescMapIt descIt = _mDescMap.find(IDStringLink(szFieldName));

    return (descIt == _mDescMap.end()) ? NULL : (*descIt).second;
}

const FieldDescription *FieldContainerType::findFieldDescription(
    const Char8 *szFieldName) const
{
    DescMapConstIt descIt = _mDescMap.find(IDStringLink(szFieldName));

    return (descIt == _mDescMap.end()) ? NULL : (*descIt).second;
}

UInt32 FieldContainerType::getNumFieldDescs(void) const
{
    return _vDescVec.size();
}

UInt32 FieldContainerType::addDescription(const FieldDescription &desc)
{
    UInt32            returnValue = 0;
    DescMapConstIt    descIt;
    DescVecIt         descVIt;

    FieldDescription  *pDesc;
    FieldDescription  *pNullDesc = NULL;

    if(_bDescsAddable == false)
        return returnValue;

    descIt = _mDescMap.find(IDStringLink(desc.getCName()));

    if(desc.isValid())
    {
        if(descIt == _mDescMap.end())
        {
            pDesc = new FieldDescription(desc);

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
                returnValue += 1;
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

Bool FieldContainerType::subDescription(UInt32 uiFieldId)
{
    FieldDescription  *pDesc = getFieldDescription(uiFieldId);
    DescMapIt          descMIt;
    DescVecIt          descVIt;
    Bool               returnValue = true;

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

/*-------------------------------------------------------------------------*/
/*                           Prototype                                     */

FieldContainerPtr FieldContainerType::getPrototype(void) const
{
    return _pPrototype;
}

Bool FieldContainerType::setPrototype(FieldContainerPtr pPrototype)
{
    Bool returnValue = false;

    if(pPrototype != NullFC)
    {
        setRefdCP(_pPrototype, pPrototype);
        returnValue = true;
    }

    return returnValue;
}

/*-------------------------------------------------------------------------*/
/*                                 Is                                      */

Bool FieldContainerType::isInitialized(void) const
{
    return _bInitialized;
}

Bool FieldContainerType::isAbstract(void) const
{
    return (_pPrototype != NullFC) ? false : true;
}

Bool FieldContainerType::isDerivedFrom(const TypeBase &other) const
{
    return Inherited::isDerivedFrom(other);
}

Bool FieldContainerType::isDerivedFrom(const FieldContainerType &other) const
{
    Bool                returnValue = false;
    FieldContainerType *pCurrType   = _pParent;

    if(_uiTypeId == other._uiTypeId)
    {
        returnValue = true;
    }
    else
    {
        while(pCurrType != NULL && returnValue == false)
        {
            if(other._uiTypeId == pCurrType->_uiTypeId)
            {
                returnValue = true;
            }
            else
            {
                pCurrType = pCurrType->_pParent;
            }
        }
    }

    return returnValue;
}

Bool FieldContainerType::isNode(void) const
{
    return (_baseType == IsNode);
}

Bool FieldContainerType::isNodeCore(void) const
{
    return (_baseType == IsNodeCore);
}

Bool FieldContainerType::isAttachment(void) const
{
    return (_baseType == IsAttachment);
}

/*-------------------------------------------------------------------------*/
/*                               Create                                    */

FieldContainerPtr FieldContainerType::createFieldContainer(void) const
{
    FieldContainerPtr fc;

    if(isAbstract()       == false)
    {
        fc = _pPrototype->shallowCopy();
    }

    return fc;
}

NodePtr  FieldContainerType::createNode(void) const
{
    NodePtr fc;

    if(isAbstract() == false &&
       isNode()     == true)
    {
        fc = NodePtr::dcast(_pPrototype->shallowCopy());
    }

    return fc;
}

NodeCorePtr FieldContainerType::createNodeCore(void) const
{
    NodeCorePtr fc;

    if(isAbstract() == false &&
       isNodeCore() == true)
    {
        fc = NodeCorePtr::dcast(_pPrototype->shallowCopy());
    }

    return fc;
}

AttachmentPtr FieldContainerType::createAttachment(void) const
{
    AttachmentPtr fc;

    if(isAbstract()   == false &&
       isAttachment() == true)
    {
        fc = AttachmentPtr::dcast(_pPrototype->shallowCopy());
    }

    return fc;
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void FieldContainerType::dump(      UInt32    OSG_CHECK_ARG(uiIndent),
                              const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "FieldContainerType: "
         << getCName()
         << ", Id: "       
         << getId()
         << ", parentP: " 
         << (_pParent ? _pParent->getCName() : "NONE")
         << ", groupId: "  
         << _uiGroupId
         << ", abstract: "
         << ((_pPrototype != NullFC) ? "false" : "true")
         << endl;
}

/*-------------------------------------------------------------------------*/
/*                              Register                                   */

void FieldContainerType::registerType(const Char8 *szGroupName)
{
    _uiTypeId  = FieldContainerFactory::the()->registerType (this);

    _uiGroupId = FieldContainerFactory::the()->registerGroup(
        szGroupName != NULL ? szGroupName : _szName.str());
}

/*-------------------------------------------------------------------------*/
/*                                Init                                     */

Bool FieldContainerType::initPrototype(void)
{
    _bInitialized = true;

    if(_fPrototypeCreate != NULL)
    {
        _pPrototype = _fPrototypeCreate();

        addRefCP(_pPrototype);
    }

    return _bInitialized;
}

Bool FieldContainerType::initBaseType(void)
{
    if     (isDerivedFrom(NodeCore::getClassType())   == true)
    {
        _baseType = IsNodeCore;
    }
    else if(isDerivedFrom(Attachment::getClassType()) == true)
    {
        _baseType = IsAttachment;
    }
    else if(isDerivedFrom(Node::getClassType())       == true)
    {
        _baseType = IsNode;
    }

    return true;
}

Bool FieldContainerType::initFields(void)
{
    UInt32    i;
    DescMapIt descIt;

    _bInitialized = true;

    for(i = 0; i < _uiDescByteCounter / sizeof(FieldDescription *); i++)
    {
        if(_pDesc[i]->isValid())
        {
            descIt = _mDescMap.find(IDStringLink(_pDesc[i]->getCName()));

            if(descIt == _mDescMap.end())
            {
                _mDescMap[IDStringLink(_pDesc[i]->getCName())] = _pDesc[i];

                _vDescVec.push_back(_pDesc[i]);
            }
            else
            {
                SWARNING << "ERROR: Double field description "
                            << "in " << _szName.str() << "from "
                            << _pDesc[i]->getCName()
                            << _pDesc[i]->getTypeId() << endl;

                _bInitialized = false;
            }
        }
        else
        {
            SWARNING << "ERROR: Invalid field description "
                        << "in " << _szName.str() << "from "
                        << (_pDesc[i]?_pDesc[i]->getTypeId():0) << endl;

            _bInitialized = false;
        }

    }

    sort(_vDescVec.begin(), _vDescVec.end(), FieldDescriptionPLT());

    return _bInitialized;
}

Bool FieldContainerType::initParentFields(void)
{
    DescMapIt dPIt;

    _bInitialized = true;

    if(_szParentName.str() != NULL)
    {
        _pParent =
            FieldContainerFactory::the()->findType(_szParentName.str());

        if(_pParent == NULL)
        {
            _pParent =
                FieldContainerFactory::the()->findUninitializedType(
                    _szParentName.str());
        }

        if(_pParent != NULL)
        {
            _bInitialized = _pParent->initialize();

            if(_bInitialized == false)
            {
                return _bInitialized;
            }

            for(  dPIt  = _pParent->_mDescMap.begin();
                  dPIt != _pParent->_mDescMap.end();
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
                             _pParent->_vDescVec.begin(),
                             _pParent->_vDescVec.end());

        }
        else
        {
            SWARNING << "ERROR: Can't find type with "
                        << "name " << _szParentName.str()
                        << endl;

            _bInitialized = false;
        }
    }

    return _bInitialized;
}

Bool FieldContainerType::initialize(void)
{
    if(_bInitialized == true)
        return _bInitialized;

    _bInitialized = initParentFields();

    if(_bInitialized == false)
        return _bInitialized;

    _bInitialized = initFields      ();

    if(_bInitialized == false)
        return _bInitialized;

    _bInitialized = initPrototype   ();

    if(_bInitialized == false)
        return _bInitialized;

    _bInitialized = initBaseType    ();

    FDEBUG ( ( "init FieldContainerType %s (%d)\n",
               _szName.str(), int(_bInitialized) ));

    return _bInitialized;
}

void FieldContainerType::terminate(void)
{
    UInt32 i;

    if(_pPrototype != NullFC)
    {
        if(GlobalSystemState == Shutdown)
        {
            _pPrototype.subRefUntraced();
        }
        else
        {
            _pPrototype.subRefUnlocked();
        }
    }

    _bInitialized = false;

    for(i = 0; i < _uiDescByteCounter / sizeof(FieldDescription *); i++)
    {
        delete _pDesc[i];
    }
}
