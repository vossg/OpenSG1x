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

OSG_USING_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char OSGFieldContainerType::cvsid[] = "@(#)$Id: $";

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
    const OSGChar8      *name,
    const OSGChar8      *parentName,
    const OSGChar8      *group,
    OSGPrototypeCreateF  prototypeCreateF,
    OSGInitContainerF    initMethod,
    OSGFieldDescription *desc,
    OSGUInt32            descByteCounter) :

    _name       (name), 
    _parentName (parentName),

    _initialized(false),

    _Id     (0), 
    _groupId(0),

    _prototypeP      (OSGNullFC),
    _prototypeCreateF(prototypeCreateF),

    _parentP(NULL), 

    _baseType(OSGIsFieldContainer),

    _descA          (desc),
    _byteSizeOfDescA(descByteCounter)
{
	registerType(group);

	if(initMethod != NULL)
		initMethod();
}

/** \brief Copy Constructor
 */

OSGFieldContainerType::OSGFieldContainerType(const OSGFieldContainerType &obj):
    _name       (obj._name), 
    _parentName (obj._parentName),

    _initialized(false),

    _Id     (obj._Id), 
    _groupId(obj._groupId),

    _prototypeP      (obj._prototypeP),
    _prototypeCreateF(obj._prototypeCreateF),

    _parentP(obj._parentP), 

    _baseType(obj._baseType),

    _descA          (obj._descA),
    _byteSizeOfDescA(obj._byteSizeOfDescA)
{
    if(_prototypeP != OSGNullFC)
        osgAddRefCP(_prototypeP);        

    initFields();
    initParentFields();
    
    _initialized = true;
}

/** \brief Destructor
 */

OSGFieldContainerType::~OSGFieldContainerType(void)
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

OSGFieldContainerType *OSGFieldContainerType::getParent(void) const
{
    return _parentP; 
}

/** \brief Get method for attribute name 
 */

const OSGChar8 *OSGFieldContainerType::getName(void) const 
{
    return _name.str(); 
}

/** \brief Retrieve prototype object for type
 */

OSGFieldContainerPtr OSGFieldContainerType::getPrototype(void) const
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

OSGFieldContainerPtr OSGFieldContainerType::createFieldContainer(void) const
{
    OSGFieldContainerPtr fc;

    if(isAbstract()       == false &&
       isFieldContainer() == true)
    {
#ifdef OSG_HAS_MEMBER_TEMPLATE_RETURNVALUES
        fc = _prototypeP->clone().dcast<OSGFieldContainerPtr>();
#else
        _prototypeP->clone().dcast(fc);
#endif
    }

	return fc;
}


OSGNodePtr  OSGFieldContainerType::createNode(void) const
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

OSGNodeCorePtr OSGFieldContainerType::createNodeCore(void) const
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

OSGAttachmentPtr OSGFieldContainerType::createAttachment(void) const
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

OSGBool OSGFieldContainerType::isAbstract(void) const
{
    return (_prototypeP != OSGNullFC) ? false : true;
}

OSGBool OSGFieldContainerType::isFieldContainer(void) const
{
    return (_baseType == OSGIsFieldContainer);
}

OSGBool OSGFieldContainerType::isNode(void) const
{
    return (_baseType == OSGIsNode);
}

OSGBool OSGFieldContainerType::isNodeCore(void) const
{
    return (_baseType == OSGIsNodeCore);
}

OSGBool OSGFieldContainerType::isAttachment(void) const
{
    return (_baseType == OSGIsAttachment);
}

OSGBool OSGFieldContainerType::isDerivedFrom(
    const OSGFieldContainerType &other) const
{
    OSGBool                returnValue = false;
    OSGFieldContainerType *currTypeP   = _parentP;

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
 
const OSGFieldDescription *OSGFieldContainerType::findFieldDescription(
    const OSGChar8 *fieldName) const 
{
    OSGDescMapConstIt descIt = _descriptionMap.find(OSGStringLink(fieldName));

    return (descIt == _descriptionMap.end()) ? NULL : (*descIt).second;
}     

OSGFieldDescription *OSGFieldContainerType::getFieldDescription(
    OSGUInt32 index)
{
    if(index > 0 && (index - 1) < _descriptionVec.size())
        return _descriptionVec[index - 1];
    else
        return NULL;
}

const OSGFieldDescription *OSGFieldContainerType::getFieldDescription(
    OSGUInt32 index) const
{
    if(index > 0 && (index - 1) < _descriptionVec.size())
        return _descriptionVec[index - 1];
    else
        return NULL;
}

OSGUInt32 OSGFieldContainerType::addDescription(
    const OSGFieldDescription &desc)
{
    OSGUInt32            returnValue = 0;
    OSGDescMapConstIt    descIt;
    OSGDescVecIt         descVIt;

    OSGFieldDescription *descP;
    OSGFieldDescription *nullDescP = NULL;

    descIt = _descriptionMap.find(OSGStringLink(desc.getName()));

    if(desc.isValid())
    {
        if(descIt == _descriptionMap.end()) 
        {
            descP = new OSGFieldDescription(desc);

            _descriptionMap[OSGStringLink(descP->getName())] = descP;

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

OSGBool OSGFieldContainerType::subDescription(OSGUInt32 fieldId)
{
    OSGFieldDescription *descP = getFieldDescription(fieldId);
    OSGDescMapIt         descMIt;
    OSGDescVecIt         descVIt;
    OSGBool              returnValue = true;

    if(descP == NULL)
        return false;

    descMIt = _descriptionMap.find(OSGStringLink(descP->getName()));

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
         << ", parentP: "  << (_parentP ? _parentP->getName() : "NONE")
         << ", groupId: " << _groupId 
         << ", abstract: " 
         << ((_prototypeP != OSGNullFC) ? "false" : "true")
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

/*-------------------------- assignment -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

void OSGFieldContainerType::registerType(const OSGChar8 *group)
{
	_Id      = OSGFieldContainerFactory::registerType (this);
	_groupId = OSGFieldContainerFactory::registerGroup( 
        group != NULL ? group : _name.str());
}

void OSGFieldContainerType::initPrototype(void)
{
    if(_initialized == true)
        return;

    if(_prototypeCreateF != NULL)
    {
        _prototypeP = _prototypeCreateF();

        
        osgAddRefCP(_prototypeP);
    }	
}

void OSGFieldContainerType::initBaseType(void)
{
    if(_initialized == true)
        return;

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
}

void OSGFieldContainerType::initFields(void)
{
    OSGUInt32         i;
    OSGDescMapConstIt descIt;

    if(_initialized == true)
        return;

    for(i = 0; i < _byteSizeOfDescA / sizeof(OSGFieldDescription); i++) 
    {
        if(_descA[i].isValid())
        {
            descIt = _descriptionMap.find(OSGStringLink(_descA[i].getName()));
            
            if(descIt == _descriptionMap.end())
            {
                _descriptionMap[OSGStringLink(_descA[i].getName())] = 
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

void OSGFieldContainerType::initParentFields(void)
{
	OSGDescMapIt dPI;

    if(_initialized == true)
        return;

    if(_parentName.str() != NULL) 
    {
        _parentP = OSGFieldContainerFactory::the().findType(_parentName.str());
        
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
                 OSGFieldDescriptionPLT());
        }
        else 
        {
            SWARNING << "ERROR: Can't find type with "
                     << "name " << _parentName.str() 
                     << endl;
        }
    }
    
}

void OSGFieldContainerType::initialize(void)
{
    if(_initialized == true)
        return;

    initFields();

    initPrototype();

    initParentFields();

    initBaseType();

    SDEBUG << "init OSGFieldContainerType " << _name << endl;

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
