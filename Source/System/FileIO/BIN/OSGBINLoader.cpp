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

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

BINLoader::BINLoader(FILE *file) :
            _inFileHandler(file),
            _countContainers(0)
{
}


BINLoader::FCInfoStruct::FCInfoStruct() :
            newId (0),
            ptr   (NullFC),
            read  (false)
{
}

BINLoader::FCIdMapper::FCIdMapper(IDLookupMap *m) :
		                                ptrMap(m)	
{
	
}
		

BINLoader::BinaryFileHandler::BinaryFileHandler(FILE *file)
		: BinaryDataHandler(0), _file(file)
{
    _readMemory .resize(10000);
    _writeMemory.resize(10000);
    readBufAdd  (&_readMemory [0], _readMemory.size());
    writeBufAdd (&_writeMemory[0], _writeMemory.size());
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */
BINLoader::~BINLoader()
{
}

BINLoader::BinaryFileHandler::~BinaryFileHandler()
{
}

/*-------------------------------------------------------------------------*\
 -  PUBLIC                                                                 -
\*-------------------------------------------------------------------------*/
void BINLoader::read()
{
    _vec_pRootNodes.clear();
    createFieldContainers();
	chargeFieldContainers();
}

NodePtr BINLoader::getRootNode()
{
    return _vec_pRootNodes[0];
}

std::vector<NodePtr> BINLoader::getRootNodes()
{
    return _vec_pRootNodes;
}

/*-------------------------------------------------------------------------*\
 -  PROTECTED                                                              -
\*-------------------------------------------------------------------------*/

/*creates a mapper for FieldContainerFactory*/
UInt32 BINLoader::FCIdMapper::map(UInt32 uiId)
{
    //returns id=0 if nil
	UInt32 id=0;
	IDLookupMap::const_iterator iterID = ptrMap->find(uiId);
	if (!(iterID == ptrMap->end()))
	{
		id = iterID->second.newId;
	}
	return id;
}


void BINLoader::BinaryFileHandler::read(MemoryHandle mem, UInt32 size)
{
	fread(mem, size, 1, _file);
}

void BINLoader::BinaryFileHandler::write(MemoryHandle mem, UInt32 size)
{
	fwrite(mem, size, 1, _file);
}

void BINLoader::createFieldContainers()
{
	UInt32 countTypes       = 0,
		   countCurrentType = 0,
		   oldFCId          = 0,
           numOfRoots       = 0,
           currentId        = 0,
           i, j;
	std::string         fcTypeCName;
         FCInfoStruct   newFCInfo;	
    std::set<UInt32>    setOfRootIds;
	
    //fetch the number of roots
    _inFileHandler.getValue(numOfRoots);    
    //fetch the root IDs
    for (i=0; i!=numOfRoots; ++i)
    {
       _inFileHandler.getValue(currentId);
       setOfRootIds.insert(currentId);
    }
    
    //fetch number of different types
    _inFileHandler.getValue(countTypes);
    //fetch number of and IDs themselves
    for(i=0; i!=countTypes; ++i)
	{
        _inFileHandler.getValue(fcTypeCName);
		_inFileHandler.getValue(countCurrentType);
		for(j=0; j!=countCurrentType; j++)
		{
			_inFileHandler.getValue(oldFCId);
			newFCInfo.ptr = FieldContainerFactory::the()
                               ->createFieldContainer(fcTypeCName.c_str());
            _countContainers++;
            
            //det. all RootNodes
            if (setOfRootIds.find(oldFCId) != setOfRootIds.end())
            {
                _vec_pRootNodes.push_back(NodePtr::dcast(newFCInfo.ptr));
            }
			
			newFCInfo.newId = newFCInfo.ptr.getFieldContainerId();

			if (_fcInfoMap.insert(std::make_pair(oldFCId, 
                                                 newFCInfo)).second==false)
			{
				std::cerr << "ERROR in BINLoader::createFieldContainers()"
                          << std::endl;
			}
		}
	}

	SINFO << "created "
          << _countContainers
          << " containers"
          << std::endl;
}



void BINLoader::chargeFieldContainers()
{
    FCIdMapper mapper(&_fcInfoMap);
          IDLookupMap::iterator fcInfoIter = _fcInfoMap.begin();
    const IDLookupMap::iterator fcInfoEnd  = _fcInfoMap.end();

    UInt32 mapSize = _fcInfoMap.size(),
           mask,
           currentFieldContainerOldId,
           count = 0;
	FieldContainerFactory *factory = FieldContainerFactory::the();
	
    factory->setMapper(&mapper);
    while(count < mapSize)
    {
        count++;

        SINFO<<"loading container "
             << std::setw(4)
             << count
             << "/" 
             << mapSize
             << "..." 
             << std::endl;

        //fetch container id
        _inFileHandler.getValue(currentFieldContainerOldId);
        fcInfoIter = _fcInfoMap.find(currentFieldContainerOldId);
        
        if (fcInfoIter == fcInfoEnd)
        {
            SWARNING << "ERROR in BINLoader::chargeFieldContainers():"
                     << std::endl
                     << "no matching container found for ID "
                     << currentFieldContainerOldId
                     << std::endl
                     << "THIS SHOULD NOT HAPPEN!!!"
                     << std::endl;

            continue;
        }
        
        if (fcInfoIter->second.read)
        {
            SWARNING << "ERROR in BINLoader::chargeFieldContainers():"
                     << std::endl
                     << "original ID: "
                     << currentFieldContainerOldId   
                     << std::endl
                     << "new ID     : "
                     << fcInfoIter->second.newId     
                     << std::endl
                     << "CONTAINER ALREADY WRITTEN! CONTAINER "
                     << "WILL BE OVERWRITTEN!"
                     << std::endl
                     << "THIS SHOULD NOT HAPPEN!!!"
                     << std::endl;
        }
        
        //fetch mask
        _inFileHandler.getValue(mask);
        //fetch container data
        beginEditCP(fcInfoIter->second.ptr, 
                    mask,
                    ChangedOrigin::Abstract        |
                    ChangedOrigin::AbstrIncRefCount);
        {
            fcInfoIter->second.ptr->copyFromBin(_inFileHandler, 
                                                BitVector(mask));
        }
        endEditCP  (fcInfoIter->second.ptr, 
                    mask,
                    ChangedOrigin::Abstract        |
                    ChangedOrigin::AbstrIncRefCount);

        fcInfoIter->second.read = true;
    }
    factory->setMapper(NULL);
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
    static Char8 cvsid_hpp[] = OSGBINLOADER_HEADER_CVSID;
}
