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

#include "OSGConfig.h"

#include <iostream>
#include <string>

#include "OSGFieldContainerFactory.h"
#include "OSGIDStringLink.h"
#include "OSGLog.h"
#include "OSGThreadManager.h"
#include "OSGLock.h"
#include "OSGFieldContainerType.h"
#include "OSGTypeFactory.h"
#include "OSGFieldFactory.h"
#include "OSGFieldDescription.h"

#include "OSGNodePtr.h"
#include "OSGAttachmentPtr.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: $";
    static char cvsid_hpp[] = OSGFIELDCONTAINERFACTORY_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

FieldContainerFactory *FieldContainerFactory::_the          = NULL;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

Bool FieldContainerFactory::initializeFactory(int &argc, char **argv)
{
    return the()->initialize(argc, argv);
}

Bool FieldContainerFactory::terminateFactory(void)
{
    return the()->terminate();
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

FieldContainerFactory *FieldContainerFactory::the(void)
{
    if(_the == NULL)
        _the = new FieldContainerFactory();

    return _the;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

FieldContainerFactory::FieldContainerFactory(void) :
    _bInitialized    (false),
    _pTypeIdMap     (NULL ),
    _pTypeNameMap   (NULL),
    _pGroupMap      (NULL),
    _pUnitTypesStore(NULL),
    _pFieldContainerStore(NULL),
    _pStoreLock     (NULL),
    _pMapLock       (NULL),
    _pMapper        (NULL)
{
    addInitFunction(&FieldContainerPtr::initialize);
    addInitFunction(&FieldContainerFactory::initializeFactory);

    addExitFunction(&FieldContainerPtr::terminate);
    addExitFunction(&FieldContainerFactory::terminateFactory);

    initTypeMap();
}

/** \brief Destructor
 */

FieldContainerFactory::~FieldContainerFactory(void)
{
}

void FieldContainerFactory::initTypeMap(void)
{
    if(_pTypeIdMap   == NULL &&
       _pTypeNameMap == NULL)
    {
        _pTypeIdMap      = new TypeIdMap;
        _pTypeNameMap    = new TypeNameMap;
        _pGroupMap       = new GroupMap;
        _pUnitTypesStore = new UninitializedTypeStore;
    }
}


Bool FieldContainerFactory::initializePendingTypes(void)
{
    Bool           returnValue = true;
    FieldContainerType *pType       = NULL;

    if(_bInitialized == false)
        return false;

    SINFO << "OSGFieldContainerFactory init pending types" << endl;

    if(_pUnitTypesStore != NULL)
    {
        if(_pMapLock != NULL)
            _pMapLock->aquire();

        UninitTypeStoreIt uninitIt = _pUnitTypesStore->begin();

        while(uninitIt != _pUnitTypesStore->end())
        {
            pType = *uninitIt;

            if(pType->isInitialized() == true)
            {
                uninitIt = _pUnitTypesStore->erase(uninitIt);

                (*_pTypeIdMap  )[pType->getId()               ] = pType;
                (*_pTypeNameMap)[IDStringLink(pType->getCName())] = pType;
            }
            else
            {
                if(pType->initialize() == true)
                {
                    uninitIt = _pUnitTypesStore->erase(uninitIt);

                    (*_pTypeIdMap  )[pType->getId()               ] = pType;
                    (*_pTypeNameMap)[IDStringLink(pType->getCName())] = pType;
                }
                else
                {
                    returnValue = false;

                    uninitIt++;
                }
            }
        }

        if(_pMapLock != NULL)
            _pMapLock->release();

        PINFO << "("
                 << returnValue
                 << "|"
                 << _pUnitTypesStore->size()
                 << ")"
                 << endl;
    }

    return returnValue;
}

Bool FieldContainerFactory::initialize(int &argc, char **argv)
{
    TypeIdMapIt typeIt;

    if(_bInitialized == true)
        return true;

    SINFO << "init singleton FieldContainerFactory" << endl;

    _pStoreLock = ThreadManager::the()->getLock(
        "OSGFieldContainerFactory::_pStoreLock");

    addRefP(_pStoreLock);

    _pMapLock   = ThreadManager::the()->getLock(
        "OSGFieldContainerFactory::_pMaoLock");

    addRefP(_pMapLock);

        FDEBUG( ("Got shore lock %d, Got map %d",
                        int (_pStoreLock), int(_pMapLock)) );

    _bInitialized = true;

    initializePendingTypes();

    return _pStoreLock != NULL && _pMapLock != NULL;
}

Bool FieldContainerFactory::terminate(void)
{
    TypeIdMapIt typeIt;

    SINFO << "terminate singleton FieldContainerFactory" << endl;

    if(_bInitialized == false)
        return true;

    if(_pTypeIdMap != NULL)
    {
        int i = 0;
        for(  typeIt  = _pTypeIdMap->begin();
              typeIt != _pTypeIdMap->end();
            ++typeIt)
        {
            (*typeIt).second->terminate();

            i++;
        }
    }

    subRefP(_pStoreLock);
    subRefP(_pMapLock);

    _bInitialized = false;

    return true;
}

UInt32 FieldContainerFactory::registerFieldContainer(
    const FieldContainerPtr &pFieldContainer)
{
    UInt32 returnValue = 0;

    if(_pStoreLock != NULL)
        _pStoreLock->aquire();

    if(_pFieldContainerStore == NULL)
    {
        _pFieldContainerStore = new FieldContainerStore;

        _pFieldContainerStore->push_back(NullFC);
    }

    _pFieldContainerStore->push_back(pFieldContainer);

    returnValue = _pFieldContainerStore->size() - 1;

    if(_pStoreLock != NULL)
        _pStoreLock->release();

    return returnValue;
}

void FieldContainerFactory::unregisterFieldContainer(
    const FieldContainerPtr &pFieldContainer)
{
    if(pFieldContainer == NullFC)
        return;

    if(_pStoreLock != NULL)
        _pStoreLock->aquire();

    if(_pFieldContainerStore != NULL)
    {
        (*_pFieldContainerStore)[pFieldContainer.getFieldContainerId()] =
            NullFC;
    }

    if(_pStoreLock != NULL)
        _pStoreLock->release();
}


UInt32 FieldContainerFactory::registerType(FieldContainerType *pType)
{
    UInt32 returnValue = TypeFactory::the()->registerType(pType);

    if(_pMapLock != NULL)
        _pMapLock->aquire();

    if(returnValue != 0)
    {
        _pUnitTypesStore->push_back(pType);
    }

    if(_pMapLock != NULL)
        _pMapLock->release();

    return returnValue;
}

UInt16 FieldContainerFactory::registerGroup(const Char8 *szName)
{
    UInt16 returnValue;

    if(szName == NULL || *szName == '\0')
    {
        SWARNING << "Group without name" << endl;
        return 0;
    }

    returnValue = findGroupId(szName);

    if(returnValue == 0)
    {
        if(_pMapLock != NULL)
            _pMapLock->aquire();

        returnValue                       = _pGroupMap->size() + 1;

        (*_pGroupMap)[IDStringLink(szName)] = returnValue;

        if(_pMapLock != NULL)
            _pMapLock->release();
    }

    return returnValue;
}

void  FieldContainerFactory::unregisterType(FieldContainerType *pType)
{
    TypeIdMapIt   typeIdIt;
    TypeNameMapIt typeNameIt;

    if(pType == NULL)
        return;

    if(_pTypeIdMap)
    {
        typeIdIt = _pTypeIdMap->find(pType->getId());

        if(typeIdIt != _pTypeIdMap->end())
        {
            _pTypeIdMap->erase(typeIdIt);
        }
    }

    if(_pTypeNameMap)
    {
        typeNameIt = _pTypeNameMap->find(IDStringLink(pType->getCName()));

        if(typeNameIt != _pTypeNameMap->end())
        {
            _pTypeNameMap->erase(typeNameIt);
        }
    }
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------------------------ access -----------------------------------*/

/*! \brief method to find a type
 */

FieldContainerType *FieldContainerFactory::findType(UInt32 uiTypeId) const
{
    TypeIdMapConstIt  typeIt;
    FieldContainerType    *pType = NULL;

    if(_pTypeIdMap)
    {
        typeIt = _pTypeIdMap->find(uiTypeId);
        pType   = (typeIt == _pTypeIdMap->end()) ? NULL : (*typeIt).second;
    }

    return pType;
}

FieldContainerType *FieldContainerFactory::findType(const Char8 *szName) const
{
    TypeNameMapCnstIt   typeIt;
    FieldContainerType *pType = NULL;

    if(_pTypeNameMap)
    {
        typeIt = _pTypeNameMap->find(IDStringLink(szName));
        pType  = (typeIt == _pTypeNameMap->end()) ? NULL : (*typeIt).second;
    }

    return pType;
}

FieldContainerType *FieldContainerFactory::findUninitializedType(
    const Char8  *szName) const
{
    FieldContainerType *returnValue = NULL;

    if(_pUnitTypesStore == NULL || szName == NULL)
        return returnValue;

    for(UInt32 i = 0; i < _pUnitTypesStore->size(); i++)
    {
        if(stringcmp(szName, (*_pUnitTypesStore)[i]->getCName()) == 0)
        {
            returnValue = (*_pUnitTypesStore)[i];
            break;
        }
    }

    return returnValue;
}

UInt32 FieldContainerFactory::getNumTypes(void) const
{
    return _pTypeNameMap ? _pTypeNameMap->size() : 0;
}


UInt16 FieldContainerFactory::findGroupId(const Char8 *szName) const
{
    GroupMapConstIt gIt;

    if (_pGroupMap)
    {
        gIt = _pGroupMap->find(IDStringLink(szName));
        return ((gIt == _pGroupMap->end()) ? 0 : (*gIt).second);
    }

    return 0;
}

const Char8 *FieldContainerFactory::findGroupName(UInt16 uiGroupId) const
{
    GroupMapConstIt gIt;

    for(gIt = _pGroupMap->begin(); gIt != _pGroupMap->end(); gIt++)
    {
        if((*gIt).second == uiGroupId)
            return (*gIt).first.str();
    }

    return NULL;
}

UInt16 FieldContainerFactory::getNumGroups (void) const
{
    return _pGroupMap ? _pGroupMap->size() : 0;
}

/*------------------------------ get --------------------------------------*/

void FieldContainerFactory::setMapper(FieldContainerMapper *pMapper)
{
    _pMapper = pMapper;
}


/*------------------------------ get --------------------------------------*/

FieldContainerPtr FieldContainerFactory::getContainer(
    UInt32 uiContainerId) const
{
    FieldContainerPtr returnValue = NullFC;

    _pStoreLock->aquire();

    if(uiContainerId < _pFieldContainerStore->size())
    {
        returnValue = (*_pFieldContainerStore)[uiContainerId];
    }

    _pStoreLock->release();

    return returnValue;
}

FieldContainerPtr FieldContainerFactory::getMappedContainer(
    UInt32 uiContainerId) const
{
    if(_pMapper != NULL)
    {
        return getContainer(_pMapper->map(uiContainerId));
    }
    else
    {
        return getContainer(uiContainerId);
    }
}

/*---------------------------- properties ---------------------------------*/

FieldContainerPtr FieldContainerFactory::createFieldContainer(
    const Char8 *name) const
{
    FieldContainerPtr returnValue;

    const FieldContainerType *pType = findType(name);

    if(pType != NULL)
        returnValue = pType->createFieldContainer();

    return returnValue;
}

NodePtr FieldContainerFactory::createNode(const Char8 *name) const
{
    NodePtr returnValue;

    const FieldContainerType *pType = findType(name);

    if(pType != NULL)
        returnValue = pType->createNode();

    return returnValue;
}

NodeCorePtr FieldContainerFactory::createNodeCore(
    const Char8 *name) const
{
    NodeCorePtr returnValue;

    const FieldContainerType *pType = findType(name);

    if(pType != NULL)
        returnValue = pType->createNodeCore();

    return returnValue;
}

AttachmentPtr FieldContainerFactory::createAttachment(
    const Char8 *name) const
{
    AttachmentPtr returnValue;

    const FieldContainerType *pType = findType(name);

    if(pType != NULL)
        returnValue = pType->createAttachment();

    return returnValue;
}

/*-------------------------- your_category---------------------------------*/

/* output */

void FieldContainerFactory::writeSingleTypeFCD( ostream &out, const FieldContainerType *t )
{
    FieldContainerType * parent = t->getParent();

    out << "<FieldContainer" << endl;
    out << "\tname=\"" << t->getCName() << "\"" << endl;
    if ( parent )
        out << "\tparent=\"" << parent->getCName() << "\"" << endl;
    out << "\tlibrary=\"" << "???" << "\"" << endl;
    out << "\tstructure=\"" << ( t->isAbstract()?"abstract":"concrete" ) << "\""
        << endl;

    // look for pointerfield types
    string s;
    int pt = 0;
    static char *pftypes[] = { "none", "single", "multi", "both" };

    s  = "SF";
    s += t->getCName();
    s += "Ptr";
    if ( FieldFactory::the().getFieldType( s.c_str() ) != NULL )
        pt |= 1;

    s  = "MF";
    s += t->getCName();
    s += "Ptr";
    if ( FieldFactory::the().getFieldType( s.c_str() ) != NULL )
        pt |= 2;

    out << "\tpointerfieldtypes=\"" << pftypes[ pt ] << "\"" << endl;
    out << ">" << endl;

    // Print the fields in this FC, ignore the parents' fields
    // !!! This should start at 0, FIX ME

    for ( int i = parent ? parent->getNumFieldDescs() + 1 : 1;
            i <= t->getNumFieldDescs(); i++ )
    {
        const FieldDescription *f = t->getFieldDescription( i );

        out << "\t<Field" << endl;
        out << "\t\tname=\"" << f->getCName() << "\"" << endl;

        // Filter the SF/MF from the type
        const Char8 * c = FieldFactory::the().getFieldType( f->getTypeId() )->getCName();
        if ( ! strncmp( c, "SF", 2 ) || ! strncmp( c, "MF", 2 ) )
            c += 2;
        out << "\t\ttype=\"" << c << "\"" << endl;

        out << "\t\tcardinality=\""
            << ( FieldFactory::the().getFieldType( f->getTypeId() )->getCardinality()
                 ? "multi" : "single"  )
            << "\"" << endl;
        out << "\t\tvisibility=\"" << (f->isInternal() ? "internal" : "external" )
            << "\"" << endl;
        out << "\t>" << endl;
        out << "\t</Field>" << endl;
    }
    out << "</FieldContainer>" << endl;

}
    /* type output */
    /* name given: output only the given type,
       out given: output all types into the stream,
       no name, no out: output all types into separate files
       */

void FieldContainerFactory::writeFCD( char * name, ostream * out )
{
    TypeIdMapIt type;
    const FieldContainerType *pType;

    if(_pTypeIdMap == NULL)
        return;

    if ( name )
    {
        pType  = findType( name );

        if ( ! pType )
        {
            SWARNING << "FieldContainerFactory::writeFCD: type " << name
                     << " is unknown!" << endl;
            return;
        }

        if ( out )
        {
            writeSingleTypeFCD( *out, pType );
        }
        else
        {
            string s( pType->getCName() );
            s.append( ".fcd" );

            ofstream f( s.c_str() );

            writeSingleTypeFCD( f, pType );
        }

        return;
    }

    // write header once?
    if ( out )
    {
        *out << "<?xml version=\"1.0\" ?>" << endl << endl;
    }

    for(  type  = _pTypeIdMap->begin();
          type != _pTypeIdMap->end();
        ++type)
    {
        if ( out )
            writeSingleTypeFCD( *out, (*type).second );
        else
        {
            string s( (*type).second->getCName() );
            s.append( ".fcd" );

            ofstream f( s.c_str() );

            f << "<?xml version=\"1.0\" ?>" << endl << endl;
            writeSingleTypeFCD( f, (*type).second );
        }
        *out << endl;
    }
}

/*-------------------------- assignment -----------------------------------*/

const FieldContainerFactory::FieldContainerStore *
    FieldContainerFactory::getFieldContainerStore(void) const
{
    return _pFieldContainerStore;
}

/*-------------------------- comparison -----------------------------------*/



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

