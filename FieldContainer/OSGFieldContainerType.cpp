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

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <algorithm>

#define OSG_COMPILEFIELDCONTAINER

#include "OSGLog.h"

#include "OSGFieldDescription.h"
#include "OSGFieldContainerType.h"
#include "OSGFieldContainerFactory.h"

#include "OSGNode.h"
#include "OSGAttachment.h"
#include "OSGNodeCore.h"

#include "OSGFieldContainerPtr.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char FieldContainerType::cvsid[] = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

FieldContainerType::FieldContainerType(
    const Char8      *name,
    const Char8      *parentName,
    const Char8      *group,
    PrototypeCreateF  prototypeCreateF,
    InitContainerF    initMethod,
    FieldDescription *desc,
    UInt32            descByteCounter,
    Bool              descsAddable) :

    _name       (name), 
    _parentName (parentName),

    _initialized(false),
    _descsAddable(descsAddable),

    _Id     (0), 
    _groupId(0),

    _prototypeP      (NullFC),
    _prototypeCreateF(prototypeCreateF),

    _parentP(NULL), 

    _baseType(IsFieldContainer),

    _descA          (desc),
    _byteSizeOfDescA(descByteCounter)
{
	registerType(group);

	if(initMethod != NULL)
		initMethod();
}

/** \brief Copy Constructor
 */

FieldContainerType::FieldContainerType(const FieldContainerType &obj):
    _name       (obj._name), 
    _parentName (obj._parentName),

    _initialized(false),
    _descsAddable(obj._descsAddable),

    _Id     (obj._Id), 
    _groupId(obj._groupId),

    _prototypeP      (obj._prototypeP),
    _prototypeCreateF(obj._prototypeCreateF),

    _parentP(obj._parentP), 

    _baseType(obj._baseType),

    _descA          (obj._descA),
    _byteSizeOfDescA(obj._byteSizeOfDescA)
{
    if(_prototypeP != NullFC)
        osgAddRefCP(_prototypeP);        

    initFields();
    initParentFields();
    
    _initialized = true;
}

/** \brief Destructor
 */

FieldContainerType::~FieldContainerType(void)
{
}

/*------------------------------ access -----------------------------------*/

/** \brief Get method for attribute Id
 */

UInt32 FieldContainerType::getId(void) const 
{
    return _Id; 
}

/** \brief Get method for attribute Id
 */

UInt16 FieldContainerType::getGroupId (void) const 
{
    return _groupId; 
}

/** \brief Get method for attribute parent 
*/

FieldContainerType *FieldContainerType::getParent(void) const
{
    return _parentP; 
}

/** \brief Get method for attribute name 
 */

const Char8 *FieldContainerType::getName(void) const 
{
    return _name.str(); 
}

/** \brief Retrieve prototype object for type
 */

FieldContainerPtr FieldContainerType::getPrototype(void) const
{
    return _prototypeP;
}

Bool FieldContainerType::setPrototype(FieldContainerPtr prototypeP)
{
	Bool returnValue = false;

    if(prototypeP != NullFC)
    {
        osgSetRefdCP(_prototypeP, prototypeP);
		returnValue = true;
    }

	return returnValue;
}

FieldContainerPtr FieldContainerType::createFieldContainer(void) const
{
    FieldContainerPtr fc;

    if(isAbstract()       == false)
    {
#ifdef OSG_HAS_MEMBER_TEMPLATE_RETURNVALUES
        fc = _prototypeP->clone().dcast<FieldContainerPtr>();
#else
        _prototypeP->clone().dcast(fc);
#endif
    }

	return fc;
}


NodePtr  FieldContainerType::createNode(void) const
{
	NodePtr fc;

    if(isAbstract() == false &&
       isNode()     == true)
    {
#ifdef OSG_HAS_MEMBER_TEMPLATE_RETURNVALUES
        fc = _prototypeP->clone().dcast<NodePtr>();
#else
        _prototypeP->clone().dcast(fc);
#endif
    }

	return fc;
}

NodeCorePtr FieldContainerType::createNodeCore(void) const
{
	NodeCorePtr fc;

    if(isAbstract() == false &&
       isNodeCore() == true)
    {
#ifdef OSG_HAS_MEMBER_TEMPLATE_RETURNVALUES
        fc = _prototypeP->clone().dcast<NodeCorePtr>();
#else
        _prototypeP->clone().dcast(fc);
#endif
    }

	return fc;
}

AttachmentPtr FieldContainerType::createAttachment(void) const
{
	AttachmentPtr fc;

    if(isAbstract()   == false &&
       isAttachment() == true)
    {
#ifdef OSG_HAS_MEMBER_TEMPLATE_RETURNVALUES
    fc = _prototypeP->clone().dcast<AttachmentPtr>();
#else
    _prototypeP->clone().dcast(fc);
#endif
    }

	return fc;
}

Bool FieldContainerType::isAbstract(void) const
{
    return (_prototypeP != NullFC) ? false : true;
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

Bool FieldContainerType::isDerivedFrom(
    const FieldContainerType &other) const
{
    Bool                returnValue = false;
    FieldContainerType *currTypeP   = _parentP;

    if(_Id == other._Id)
    {
        returnValue = true;
    }
    else
    {
        while(currTypeP != NULL && returnValue == false)
        {
            if(other._Id == currTypeP->_Id)
            {
                returnValue = true;
            }
            else
            {
                currTypeP = currTypeP->_parentP;
            }
        }
    }

    return returnValue;
}
 
const FieldDescription *FieldContainerType::findFieldDescription(
    const Char8 *fieldName) const 
{
    DescMapConstIt descIt = _descriptionMap.find(StringLink(fieldName));

    return (descIt == _descriptionMap.end()) ? NULL : (*descIt).second;
}     

FieldDescription *FieldContainerType::getFieldDescription(
    UInt32 index)
{
    if(index > 0 && (index - 1) < _descriptionVec.size())
        return _descriptionVec[index - 1];
    else
        return NULL;
}

const FieldDescription *FieldContainerType::getFieldDescription(
    UInt32 index) const
{
    if(index > 0 && (index - 1) < _descriptionVec.size())
        return _descriptionVec[index - 1];
    else
        return NULL;
}

UInt32 FieldContainerType::addDescription(
    const FieldDescription &desc)
{
    UInt32            returnValue = 0;
    DescMapConstIt    descIt;
    DescVecIt         descVIt;

    FieldDescription *descP;
    FieldDescription *nullDescP = NULL;

    if(_descsAddable == false)
        return returnValue;

    descIt = _descriptionMap.find(StringLink(desc.getName()));

    if(desc.isValid())
    {
        if(descIt == _descriptionMap.end()) 
        {
            descP = new FieldDescription(desc);

            _descriptionMap[StringLink(descP->getName())] = descP;

            descVIt = find(_descriptionVec.begin(), 
                           _descriptionVec.end(),
                           nullDescP);

            if(descVIt == _descriptionVec.end())
            {
                _descriptionVec.push_back(descP);

                returnValue = _descriptionVec.size();
            }
            else
            {
                (*descVIt) = descP;

                returnValue  = descVIt - _descriptionVec.begin();
                returnValue += 1;
            }
        }
        else
        {
            SWARNING << "ERROR: Double field description " 
                     << "in " << _name << "from " 
                     << desc.getName() 
                     << desc.getTypeId() << endl;
        }
    }
    else
    {
        SWARNING << "ERROR: Invalid field description " 
                 << "in " << _name << "from " 
                 << desc.getTypeId() << endl;
    }

    return returnValue;
}

Bool FieldContainerType::subDescription(UInt32 fieldId)
{
    FieldDescription *descP = getFieldDescription(fieldId);
    DescMapIt         descMIt;
    DescVecIt         descVIt;
    Bool              returnValue = true;

    if(descP == NULL || _descsAddable == false)
        return false;

    descMIt = _descriptionMap.find(StringLink(descP->getName()));

    if(descMIt != _descriptionMap.end())
    {
        _descriptionMap.erase(descMIt);       
    }
    else
    {
        returnValue = false;
    }

    descVIt = find(_descriptionVec.begin(), _descriptionVec.end(), descP);

    if(descVIt != _descriptionVec.end())
    {
        (*descVIt) = NULL;

        returnValue &= true;
    }
    else
    {
        returnValue = false;
    }

    delete descP;

    return returnValue;
}

UInt32 FieldContainerType::getNumFieldDescriptions(void) const
{
    return _descriptionVec.size();
}

void FieldContainerType::print(void) const
{
	map    <StringLink, FieldDescription *>::const_iterator dI;
	vector <               FieldDescription *>::const_iterator dVI;

 	cerr << "FieldContainerType: " << _name 
         << ", Id: "      << _Id 
         << ", parentP: "  << (_parentP ? _parentP->getName() : "NONE")
         << ", groupId: " << _groupId 
         << ", abstract: " 
         << ((_prototypeP != NullFC) ? "false" : "true")
         << endl;

	for (	dVI  = _descriptionVec.begin(); 
            dVI != _descriptionVec.end(); 
          ++dVI)
    {
        if( (*dVI) != NULL)
            (*dVI)->print();        
        else
            fprintf(stderr, "NULL DESC\n");
    }
}

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

Bool FieldContainerType::operator ==(const FieldContainerType &other)
{
    return (_Id == other._Id);
}

Bool FieldContainerType::operator !=(const FieldContainerType &other)
{
    return ! (*this == other);
}


/*-------------------------- assignment -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

void FieldContainerType::registerType(const Char8 *group)
{
	_Id      = FieldContainerFactory::registerType (this);
	_groupId = FieldContainerFactory::registerGroup( 
        group != NULL ? group : _name.str());
}

void FieldContainerType::initPrototype(void)
{
    if(_initialized == true)
        return;

    if(_prototypeCreateF != NULL)
    {
        _prototypeP = _prototypeCreateF();

        
        osgAddRefCP(_prototypeP);
    }	
}

void FieldContainerType::initBaseType(void)
{
    if(_initialized == true)
        return;

    if     (isDerivedFrom(NodeCore::getStaticType())   == true)
    {
        _baseType = IsNodeCore;
    }
    else if(isDerivedFrom(Attachment::getStaticType()) == true)
    {
        _baseType = IsAttachment;
    }
    else if(isDerivedFrom(Node::getStaticType())       == true)
    {
        _baseType = IsNode;
    }
}

void FieldContainerType::initFields(void)
{
    UInt32         i;
    DescMapConstIt descIt;

    if(_initialized == true)
        return;

    for(i = 0; i < _byteSizeOfDescA / sizeof(FieldDescription); i++) 
    {
        if(_descA[i].isValid())
        {
            descIt = _descriptionMap.find(StringLink(_descA[i].getName()));
            
            if(descIt == _descriptionMap.end())
            {
                _descriptionMap[StringLink(_descA[i].getName())] = 
                    &_descA[i];
                _descriptionVec.push_back(&_descA[i]);
            }
            else
            {
                SWARNING << "ERROR: Double field description " 
                         << "in " << _name << "from " 
                         << _descA[i].getName() 
                         << _descA[i].getTypeId() << endl;
            }
        }
        else
        {
            SWARNING << "ERROR: Invalid field description " 
                     << "in " << _name << "from " 
                     << _descA[i].getTypeId() << endl;
        }
    }
}

void FieldContainerType::initParentFields(void)
{
	DescMapIt dPI;

    if(_initialized == true)
        return;

    if(_parentName.str() != NULL) 
    {
        _parentP = FieldContainerFactory::the().findType(_parentName.str());
        
        if(_parentP != NULL) 
        {
            _parentP->initialize();
            
            for(  dPI  = _parentP->_descriptionMap.begin();
                  dPI != _parentP->_descriptionMap.end(); 
                ++dPI) 
            {
                if(_descriptionMap.find((*dPI).first) == 
                   _descriptionMap.end())
                {
                    _descriptionMap[(*dPI).first] = (*dPI).second;
                }
                else
                {
                    SWARNING << "ERROR: Can't add field "
                             << "description a second time: " 
                             << (*dPI).first << endl; 
                }
            } 				
            
            _descriptionVec.insert(_descriptionVec.end(),
                                   _parentP->_descriptionVec.begin(),
                                   _parentP->_descriptionVec.end());
            
            sort(_descriptionVec.begin(),
                 _descriptionVec.end(),
                 FieldDescriptionPLT());
        }
        else 
        {
            SWARNING << "ERROR: Can't find type with "
                     << "name " << _parentName.str() 
                     << endl;
        }
    }
    
}

void FieldContainerType::initialize(void)
{
    if(_initialized == true)
        return;

    initFields();

    initPrototype();

    initParentFields();

    initBaseType();

    SDEBUG << "init FieldContainerType " << _name << endl;

    _initialized = true;
}

void FieldContainerType::terminate(void)
{
    osgSubRefCP(_prototypeP);    

    _initialized = false;
}

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
