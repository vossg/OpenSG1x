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

const OSGFieldDescription *OSGFieldContainerType::getFieldDescription(
    OSGUInt32 index) const
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
         << ", parentP: "  << (_parentP ? _parentP->getName() : "NONE")
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

void OSGFieldContainerType::registerType(const OSGChar8 *group)
{
	_Id      = OSGFieldContainerFactory::registerType (this);
	_groupId = OSGFieldContainerFactory::registerGroup( 
        group != NULL ? group : _name.str());
}

void OSGFieldContainerType::initialize(void)
{
    OSGUInt32      i;

	OSGDescMapIt dPI;

    if(_initialized == true)
        return;

    for(i = 0; i < _byteSizeOfDescA / sizeof(OSGFieldDescription); i++) 
    {
        if (_descA[i].isValid()) 
        {
            _descriptionMap[OSGStringLink(_descA[i].getName())] = &_descA[i];
            _descriptionVec.push_back(&_descA[i]);
        }
        else
        {
            SWARNING << "ERROR: Invalid field description " 
                     << "in " << _name << "from " 
                     << _descA[i].getName() 
                     << _descA[i].getTypeId() << endl;
        }
    }

    if(_prototypeCreateF != NULL)
    {
        _prototypeP = _prototypeCreateF();
    }

    osgAddRefCP(_prototypeP);
	
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
    
    SDEBUG << "init OSGFieldContainerType " << _name << endl;

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
