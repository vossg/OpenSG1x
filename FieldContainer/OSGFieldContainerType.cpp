/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
 *                                                                           *
 *          contact: {reiners|vossg}@igd.fhg.de, jbehr@zgdv.de               *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

#include "OSGLog.h"

#include "OSGFieldDescription.h"
#include "OSGFieldContainerType.h"
#include "OSGFieldContainerFactory.h"

#include "OSGNode.h"
#include "OSGAttachment.h"
#include "OSGNodeCore.h"

#include "OSGFieldContainerPtr.h"

OSG_USING_OSG_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char OSGFieldContainerType::cvsid[] = "@(#)$Id: OSGFieldContainerType.cpp,v 1.25 2000/06/16 17:08:29 vossg Exp $";

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

OSGFieldContainerType::OSGFieldContainerType(
    const OSGChar *name,
    const OSGChar *parentName,
    const OSGChar *group,
    OSGPrototypeCreateF            prototypeCreateF,
    OSGInitContainerMethod         initMethod,
    OSGFieldDescription           *desc,
    OSGUInt32                      descByteCounter) :

    _name(name), 
    _parentName(parentName),
    _initialized(false),
    _Id(0), 
    _groupId(0),
    _parent(NULL), 
    _baseType(OSGIsFieldContainer),
    _prototypeP(OSGNullFC),
    _prototypeCreateF(prototypeCreateF),
    _descA(desc),
    _byteSizeOfDescA(descByteCounter)
{
	registerType(group);

	if(initMethod != NULL)
		initMethod();
}

/** \brief Destructor
 */

OSGFieldContainerType::~OSGFieldContainerType (void )
{
}

/*------------------------------ access -----------------------------------*/

/** \brief Get method for attribute Id
 */

OSGUInt32 OSGFieldContainerType::getId(void) const 
{
    return _Id; 
}

/** \brief Get method for attribute Id
 */

OSGUInt16 OSGFieldContainerType::getGroupId (void) const 
{
    return _groupId; 
}

/** \brief Get method for attribute parent 
*/

OSGFieldContainerType *OSGFieldContainerType::getParent(void)
{
    return _parent; 
}

/** \brief Get method for attribute name 
 */

const char *OSGFieldContainerType::getName(void) const 
{
    return _name.str(); 
}

/** \brief Retrieve prototype object for type
 */

OSGFieldContainerPtr OSGFieldContainerType::getPrototype(void)
{
    return _prototypeP;
}

OSGBool OSGFieldContainerType::setPrototype(OSGFieldContainerPtr prototypeP)
{
	OSGBool returnValue = false;

    if(prototypeP != OSGNullFC)
    {
        osgSetRefdCP(_prototypeP, prototypeP);
		returnValue = true;
    }

	return returnValue;
}

OSGNodePtr  OSGFieldContainerType::createNode(void)
{
	OSGNodePtr fc;

    if(isAbstract() == false &&
       isNode()     == true)
    {
#ifdef OSG_HAS_MEMBER_TEMPLATE_RETURNVALUES
        fc = _prototypeP->clone().dcast<OSGNodePtr>();
#else
        _prototypeP->clone().dcast(fc);
#endif
    }

	return fc;
}

OSGNodeCorePtr OSGFieldContainerType::createNodeCore(void)
{
	OSGNodeCorePtr fc;

    if(isAbstract() == false &&
       isNodeCore() == true)
    {
#ifdef OSG_HAS_MEMBER_TEMPLATE_RETURNVALUES
        fc = _prototypeP->clone().dcast<OSGNodeCorePtr>();
#else
        _prototypeP->clone().dcast(fc);
#endif
    }

	return fc;
}

OSGAttachmentPtr OSGFieldContainerType::createAttachment(void)
{
	OSGAttachmentPtr fc;

    if(isAbstract()   == false &&
       isAttachment() == true)
    {
#ifdef OSG_HAS_MEMBER_TEMPLATE_RETURNVALUES
    fc = _prototypeP->clone().dcast<OSGAttachmentPtr>();
#else
    _prototypeP->clone().dcast(fc);
#endif
    }

	return fc;
}

OSGBool OSGFieldContainerType::isAbstract(void)
{
    return (_prototypeP != OSGNullFC) ? false : true;
}

OSGBool OSGFieldContainerType::isNode(void)
{
    return (_baseType == OSGIsNode);
}

OSGBool OSGFieldContainerType::isNodeCore(void)
{
    return (_baseType == OSGIsNodeCore);
}

OSGBool OSGFieldContainerType::isAttachment(void)
{
    return (_baseType == OSGIsAttachment);
}

OSGBool OSGFieldContainerType::isDerivedFrom(
    const OSGFieldContainerType &other)
{
    OSGBool                returnValue = false;
    OSGFieldContainerType *currTypeP   = _parent;

    if(_Id == other._Id)
    {
        returnValue = true;
    }
    else
    {
        while(currTypeP != NULL && returnValue == false)
        {
            if(_Id == currTypeP->_Id)
            {
                returnValue = true;
            }
            else
            {
                currTypeP = currTypeP->_parent;
            }
        }
    }

    return returnValue;
}
 
OSGFieldDescription *OSGFieldContainerType::findFieldDescription(
    const char *fieldName) const 
{
    map<OSGStringLink, OSGFieldDescription *>::const_iterator fI = 
        _descriptionMap.find(fieldName);

    return (fI == _descriptionMap.end()) ? 0 : (*fI).second;
}     

OSGFieldDescription *OSGFieldContainerType::getFieldDescription(
    const OSGUInt32 index) const
{
    if(index < _descriptionVec.size())
        return _descriptionVec[index];
    else
        return NULL;
}

OSGUInt32 OSGFieldContainerType::getNumFieldDescriptions(void) const
{
    return _descriptionVec.size();
}

void OSGFieldContainerType::print(void) const
{
	map    <OSGStringLink, OSGFieldDescription *>::const_iterator dI;
	vector <               OSGFieldDescription *>::const_iterator dVI;

 	cerr << "OSGFieldContainerType: " << _name 
         << ", Id: "      << _Id 
         << ", parent: "  << (_parent ? _parent->getName() : "NONE")
         << ", groupId: " << _groupId 
         << ", abstract: " 
         << ((_prototypeP != OSGNullFC) ? "false" : "true")
         << endl;

	for (	dVI  = _descriptionVec.begin(); 
            dVI != _descriptionVec.end(); 
          ++dVI)
    {
        (*dVI)->print();
    }
}

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

void OSGFieldContainerType::registerType(const OSGChar *group)
{
	OSGFieldContainerType *idType, *nameType;
	const OSGChar *groupName = group ? group : _name.str();
	OSGInt32 i;
	OSGInt16 groupId;

	OSGFieldContainerFactory::initTypeMap();

	if(_name.empty()) 
    {
		SFATAL << "FieldContainerType without name" << endl;
		return;
	}

	_Id = OSGFieldContainerFactory::_typeIdMap->size() + 1;

	groupId = OSGFieldContainerFactory::the().findGroupId ( groupName );

	if(groupId) 
    {
		_groupId = groupId;
    }
	else 
    {
		_groupId = _Id;
		(*OSGFieldContainerFactory::_groupMap)[groupName] = _groupId;
	}	

	idType = OSGFieldContainerFactory::the().findType(_Id);
	nameType = OSGFieldContainerFactory::the().findType(_name.str());

	if(_Id <= 0)
    {
		SWARNING << "ERROR: Node Id must be > 0" << endl;
    }
	else 
    {
		if(_name.length())
        {
			if(idType) 
            {
				SWARNING << "ERROR: Can't add a second "
                         << "type with the Id" << _Id << endl;
            }
			else
            {
				if(nameType)
                {
					SWARNING << "ERROR: Can't add a second "
                             << "type with the name" <<_name<<endl;
                }
				else 
                {

					(*OSGFieldContainerFactory::_typeIdMap)[_Id] = this;
					(*OSGFieldContainerFactory::_typeNameMap)[_name.str()] = 
                        this;
                }
            }
        }
    }

	return;
}

//----------------------------------------------------------------------
// Method: initialize
// Author: jbehr
// Date:   Sat Mar 18 13:39:15 2000
// Description:
//         
//----------------------------------------------------------------------

void OSGFieldContainerType::initialize(void)
{
    OSGUInt32            i;
	OSGFieldDescription *fieldDesc;

	map    <OSGStringLink, OSGFieldDescription *>::iterator         dPI;
	vector <               OSGFieldDescription *>::reverse_iterator dVPI;

    if(_initialized == true)
        return;

    for(i = 0; i < _byteSizeOfDescA / sizeof(OSGFieldDescription); i++) 
    {
        if (_descA[i].valid()) 
        {
            fieldDesc = new OSGFieldDescription(_descA[i]);
            _descriptionMap[fieldDesc->name()] = fieldDesc;
            _descriptionVec.push_back(fieldDesc);
        }
        else
        {
            SWARNING << "ERROR: Invalid field description " 
                     << "in " << _name << "from " 
                     << _descA[i].name() 
                     << _descA[i].getTypeId() << endl;
        }
    }

    if(_prototypeCreateF != NULL)
    {
        _prototypeP = _prototypeCreateF();
    }

    osgAddRefCP(_prototypeP);
	
	if(!_parent) 
    {
		if(_parentName.str()) 
        {
			_parent = 
                OSGFieldContainerFactory::the().findType(_parentName.str());

			if(_parent) 
            {
				_parent->initialize();

				for(  dPI  = _parent->_descriptionMap.begin();
                      dPI != _parent->_descriptionMap.end(); 
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

                reverse(_descriptionVec.begin(), _descriptionVec.end());

                for(  dVPI  = _parent->_descriptionVec.rbegin();
                      dVPI != _parent->_descriptionVec.rend();
                    ++dVPI)
                {
                    _descriptionVec.push_back(*dVPI);
                }

                reverse(_descriptionVec.begin(), _descriptionVec.end());
			}
			else 
            {
				SWARNING << "ERROR: Can't find type with "
                         << "name " << _parentName.str() 
                         << endl;
			}
		}

		SDEBUG << "init OSGFieldContainerType " << _name << endl;
	}

    if     (isDerivedFrom(OSGNodeCore::getStaticType())   == true)
    {
        _baseType = OSGIsNodeCore;
    }
    else if(isDerivedFrom(OSGAttachment::getStaticType()) == true)
    {
        _baseType = OSGIsAttachment;
    }
    else if(isDerivedFrom(OSGNode::getStaticType())       == true)
    {
        _baseType = OSGIsNode;
    }

    _initialized = true;
}

void OSGFieldContainerType::terminate(void)
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
