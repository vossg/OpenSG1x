/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include <OSGConfig.h>
#include <stdio.h>

#include <string>
#include <map>
#include <set>
#include <vector>
#include <fstream>

#include <OSGFieldContainer.h>
#include <OSGBinaryDataHandler.h>

#include "OSGBINLoader.h"

OSG_USING_NAMESPACE

/*! \class osg::BINLoader
    \ingroup GrpSystemFileIO

    OpenSG propritrary file loader

    <pre>
    UInt32          num of root nodes
      // for each root node
      UInt32        root node field container id

    UInt32          num of types
    // for each type
      UInt32        type name len
      Char8         len bytes
      UInt32        num of instances
      // for each instance
        UInt32      field container id

    // for each instance
    UInt32          field container id
    ...             field values written by copyToBin

    </pre>
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors/Destructor                      */

/*! constructor
 */
BINLoader::BINLoader(std::istream &is) :
    _inFileHandler(is),
    _fcInfoMap(),
    _countContainers(0),
    _vec_pRootNodes(),
    _valid_stream(is)
{
}

/*! destructor
 */
BINLoader::~BINLoader(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             read / root access                          */

/*! process the whole input file
 */
void BINLoader::read(void)
{
    if(!_valid_stream)
    {
        SFATAL << "BINLoader::read : Stream is invalid!" << std::endl;
        return;
    }

    _vec_pRootNodes.clear();
    if(!createFieldContainers())
    {
        _valid_stream = false;
        return;
    }

    chargeFieldContainers();
}

/*! return first root node
 */
NodePtr BINLoader::getRootNode(void)
{
    if(!_valid_stream)
    {
        return NullFC;
    }

    return _vec_pRootNodes[0];
}

/*! return all root nodes
 */
std::vector<NodePtr> BINLoader::getRootNodes(void)
{
    return _vec_pRootNodes;
}

/*-------------------------------------------------------------------------*/
/*                         private helper functions                        */

/*! create all fieldcontainers with default values
 */
bool BINLoader::createFieldContainers(void)
{
    UInt32 countTypes = 0, countCurrentType = 0, oldFCId = 0, numOfRoots = 0,
        currentId = 0, i, j;
    std::string fcTypeCName;
    FCInfoStruct newFCInfo;
    std::set < UInt32 > setOfRootIds;

    //fetch the number of roots
    _inFileHandler.getValue(numOfRoots);

    //fetch the root IDs
    for(i = 0; i != numOfRoots; ++i)
    {
        _inFileHandler.getValue(currentId);
        setOfRootIds.insert(currentId);
    }

    //fetch number of different types
    _inFileHandler.getValue(countTypes);

    //fetch number of and IDs themselves
    for(i = 0; i != countTypes; ++i)
    {
        _inFileHandler.getValue(fcTypeCName);
        _inFileHandler.getValue(countCurrentType);
        for(j = 0; j != countCurrentType; j++)
        {
            _inFileHandler.getValue(oldFCId);
            newFCInfo.ptr = FieldContainerFactory::the()->createFieldContainer(fcTypeCName.c_str());

            if(newFCInfo.ptr == NullFC)
            {
                SFATAL << "Couldn't create unknown FieldContainer with type '" <<
                       fcTypeCName << "'!" << std::endl;
                return false;
            }
            _countContainers++;

            //det. all RootNodes
            if(setOfRootIds.find(oldFCId) != setOfRootIds.end())
            {
                _vec_pRootNodes.push_back(NodePtr::dcast(newFCInfo.ptr));
            }

            newFCInfo.newId = newFCInfo.ptr.getFieldContainerId();

            if(_fcInfoMap.insert(std::make_pair(oldFCId, newFCInfo)).second
               == false)
            {
                std::cerr <<
                    "ERROR in BINLoader::createFieldContainers()" <<
                    std::endl;
            }
        }
    }

    SINFO << "created " << _countContainers << " containers" << std::endl;
    return true;
}

/*! apply field values to the field containers
 */
void BINLoader::chargeFieldContainers(void)
{
    FCIdMapper                  mapper(&_fcInfoMap);
    IDLookupMap::iterator       fcInfoIter = _fcInfoMap.begin();
    const IDLookupMap::iterator fcInfoEnd = _fcInfoMap.end();

    UInt32 mapSize = _fcInfoMap.size(), currentFieldContainerOldId, count = 0;
    BitVector mask;
    FieldContainerFactory *factory = FieldContainerFactory::the();

    factory->setMapper(&mapper);
    while(count < mapSize)
    {
        count++;

        SINFO <<
            "loading container " <<
            std::setw(4) <<
            count <<
            "/" <<
            mapSize <<
            "..." <<
            std::endl;

        //fetch container id
        _inFileHandler.getValue(currentFieldContainerOldId);
        fcInfoIter = _fcInfoMap.find(currentFieldContainerOldId);

        if(fcInfoIter == fcInfoEnd)
        {
            SWARNING <<
                "ERROR in BINLoader::chargeFieldContainers():" <<
                std::endl <<
                "no matching container found for ID " <<
                currentFieldContainerOldId <<
                std::endl <<
                "THIS SHOULD NOT HAPPEN!!!" <<
                std::endl;

            continue;
        }

        if(fcInfoIter->second.read)
        {
            SWARNING <<
                "ERROR in BINLoader::chargeFieldContainers():" <<
                std::endl <<
                "original ID: " <<
                currentFieldContainerOldId <<
                std::endl <<
                "new ID     : " <<
                fcInfoIter->second.newId <<
                std::endl <<
                "CONTAINER ALREADY WRITTEN! CONTAINER " <<
                "WILL BE OVERWRITTEN!" <<
                std::endl <<
                "THIS SHOULD NOT HAPPEN!!!" <<
                std::endl;
        }

        // fetch mask
        _inFileHandler.getValue(mask);

        // fetch container data
        beginEditCP(fcInfoIter->second.ptr, mask,
                            ChangedOrigin::Abstract | ChangedOrigin::AbstrIncRefCount);
        {
            fcInfoIter->second.ptr->copyFromBin(_inFileHandler, BitVector(mask));
        }

        endEditCP(fcInfoIter->second.ptr, mask,
                          ChangedOrigin::Abstract | ChangedOrigin::AbstrIncRefCount);

        fcInfoIter->second.read = true;
    }

    factory->setMapper(NULL);
}

/*-------------------------------------------------------------------------*/
/*                              FCInfoStruct                               */

/*! constructor
 */
BINLoader::FCInfoStruct::FCInfoStruct(void) :
    newId(0),
    ptr(NullFC),
    read(false)
{
}

/*-------------------------------------------------------------------------*/
/*                              FCIdMapper                                 */

/*! constructor
 */
BINLoader::FCIdMapper::FCIdMapper(IDLookupMap *m) :
    ptrMap(m)
{
}

/*! mapper for FieldContainerFactory
 */
UInt32 BINLoader::FCIdMapper::map(UInt32 uiId)
{
    //returns id=0 if nil
    UInt32 id = 0;
    IDLookupMap::const_iterator iterID = ptrMap->find(uiId);
    if(!(iterID == ptrMap->end()))
    {
        id = iterID->second.newId;
    }

    return id;
}

/*-------------------------------------------------------------------------*/
/*                              BinaryFileHandler                          */

/*! constructor
 */
BINLoader::BinaryFileHandler::BinaryFileHandler(std::istream &is) :
    BinaryDataHandler(0),
    _is(is)
{
    _readMemory.resize(10000);
    readBufAdd(&_readMemory[0], _readMemory.size());
}

/*! destructor
 */
BINLoader::BinaryFileHandler::~BinaryFileHandler(void)
{
}

/*! read
 */
void BINLoader::BinaryFileHandler::read(MemoryHandle mem, UInt32 size)
{
    _is.read((char *) mem, size);
}

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif
#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGBINLOADER_HEADER_CVSID;
}
