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

//-------------------------------
// 	Includes 					 			    
//-------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <OSGLog.h>
#include <OSGBaseTypes.h>

#include "OSGSceneFileHandler.h"
#include "OSGNode.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGSCENEFILEHANDLER_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/* enum VecBase::VectorSizeE
 * brief 
*/


/* var VecBase::VectorSizeE VecBase::_iSize
 *
*/


/* const char *VecBase::getClassName(void)
 *  brief Classname
*/


/* var ValueTypeT VecBase:: _value[Size];
 * brief value store
*/


/*****************************
 *   Types
 *****************************/


/*****************************
 *	  Classvariables
 *****************************/


SceneFileHandler * SceneFileHandler::_the = NULL;


/********************************
 *	  Class methodes
 *******************************/


/*******************************
*public
*******************************/


//----------------------------
// Function name: getFileType
//----------------------------
//
//Parameters:
//p: const char *fileName
//GlobalVars:
//g: 
//Returns:
//r:SceneFileType
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: getFileType
//SeeAlso:
//s:
//
//------------------------------

SceneFileType *SceneFileHandler::getFileType(const Char8 *fileName)
{
	      Int32                  i;
          Int32                  l;
          IDString               suffix;
	const Char8                  separator = '.';
	      SceneFileType         *type = NULL;
	      FileTypeMap::iterator  sI;
          ifstream               fin;

	if(fileName) 
    {
        l = strlen(fileName);
        
        for(i = l - 1; i >= 0; i--) 
        {
            if(fileName[i] == separator) 
                break;
        }
        
        if(i >= 0) 
        {
            suffix.set(&(fileName[i+1]));
            suffix.toLower();
            
            sI = _suffixTypeMap.find(suffix);
            
            type = (sI == _suffixTypeMap.end()) ? 0 : sI->second->front();
        }
    }
    		
	return type;
}

Int32 SceneFileHandler::getSuffixList(list<const char *> & suffixList)
{
	Int32 count = 0;
	FileTypeMap::iterator sI;

	for ( sI = _suffixTypeMap.begin(); sI != _suffixTypeMap.end(); sI++)
    {
      suffixList.push_back(sI->first.str());
      count++;
    }

  return count;
}
	
//----------------------------
// Function name: read
//----------------------------
//
//Parameters:
//p: Scene &image, const char *fileName
//GlobalVars:
//g: 
//Returns:
//r:Bool
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: 
//SeeAlso:
//s:
//
//------------------------------
NodePtr SceneFileHandler::readOptReplace(const Char8  *fileName,  
                                               UInt32  uiReplaceOptions)
{
	SceneFileType *type = getFileType(fileName);
	NodePtr        node = NullFC;

	if(! fileName)
	{
		SWARNING << "cannot read NULL file" << endl;
		return node;
	}
	
	if (type) 
    {
		SINFO << "try to read " << fileName 
              << " as "         << type->getName() << endl;

        node = type->read(fileName, uiReplaceOptions);

		if (node != NullFC)
        {
			SINFO    << "read ok:"        << endl;
        }
		else
        {
			SWARNING << "could not read " << endl;
        }
	}
	else
    {
		SWARNING << "could not read "       << fileName 
                 << "; unknown file format" << endl;
    }

	return node;
}

NodePtr SceneFileHandler::read(const  Char8  *fileName,
                                      UInt32  uiAddOptions,
                                      UInt32  uiSubOptions)
{
	SceneFileType *type = getFileType(fileName);
	NodePtr        node = NullFC;

	if(! fileName)
	{
		SWARNING << "cannot read NULL file" << endl;
		return node;
	}
	
	if (type) 
    {
		SINFO << "try to read " << fileName 
              << " as "         << type->getName() << endl;

        node = type->read(fileName, uiAddOptions, uiSubOptions);

		if (node != NullFC)
        {
			SINFO    << "read ok:"        << endl;
        }
		else
        {
			SWARNING << "could not read " << endl;
        }
	}
	else
    {
		SWARNING << "could not read "       << fileName 
                 << "; unknown file format" << endl;
    }

	return node;
}


//----------------------------
// Function name: readTopNodes
//----------------------------
//
//Parameters:
//p: Scene &image, const char *fileName
//GlobalVars:
//g: 
//Returns:
//r:vector<NodePtr>
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: 
//SeeAlso:
//s:
//
//------------------------------
SceneFileHandler::FCPtrStore SceneFileHandler::readTopNodesOptReplace(
    const Char8  *fileName,
          UInt32  uiReplaceOptions)
{
	SceneFileType *type = getFileType(fileName);
	vector<FieldContainerPtr> nodeVec;
	
	if(! fileName)
	{
		SWARNING << "cannot read NULL file" << endl;
		return nodeVec;
	}
	
	if (type) 
    {
		SINFO << "try to read " << fileName 
              << " as "         << type->getName() << endl;

        nodeVec = type->readTopNodes(fileName, uiReplaceOptions);

		for( UInt32 i=0; i<nodeVec.size(); ++i )
		{
			if( nodeVec[i] == NullFC )
			{
				SWARNING << "could not read node " << i << endl;
				return nodeVec;
			}
        }
		SWARNING << "read ok. " << endl;
	}
	else
    {
		SWARNING << "could not read "       << fileName 
                 << "; unknown file format" << endl;
    }

	return nodeVec;
}

SceneFileHandler::FCPtrStore SceneFileHandler::readTopNodes(
    const  Char8  *fileName,
           UInt32  uiAddOptions,
           UInt32  uiSubOptions)
{
	SceneFileType *type = getFileType(fileName);
	vector<FieldContainerPtr> nodeVec;
	
	if(! fileName)
	{
		SWARNING << "cannot read NULL file" << endl;
		return nodeVec;
	}
	
	if (type) 
    {
		SINFO << "try to read " << fileName 
              << " as "         << type->getName() << endl;

        nodeVec = type->readTopNodes(fileName, uiAddOptions, uiSubOptions);

		for( UInt32 i=0; i<nodeVec.size(); ++i )
		{
			if( nodeVec[i] == NullFC )
			{
				SWARNING << "could not read node " << i << endl;
				return nodeVec;
			}
        }
		SWARNING << "read ok. " << endl;
	}
	else
    {
		SWARNING << "could not read "       << fileName 
                 << "; unknown file format" << endl;
    }

	return nodeVec;
}

//----------------------------
// Function name: write
//----------------------------
//
//Parameters:
//p: const Scene &image, const char *fileName
//GlobalVars:
//g: 
//Returns:
//r:Bool
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: 
//SeeAlso:
//s:
//
//------------------------------
Bool SceneFileHandler::write ( const NodePtr node, const char *fileName )
{
	Bool retCode = false;
	SceneFileType *type = getFileType(fileName);

	if (type) {
		SINFO << "try to write " << fileName << " as " << type->getName() << endl;
		retCode = type->write(node,fileName);
	}
	else
		SWARNING << "can't write " << fileName << "; unknown scene format" 
						 << endl;

	return retCode;
}

//----------------------------
// Function name: print
//----------------------------
//
//Parameters:
//p: void
//GlobalVars:
//g: 
//Returns:
//r:void
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: print debug info to cerr
//SeeAlso:
//s:
//
//------------------------------
void SceneFileHandler::print (void )
{
	FileTypeMap::iterator sI;

	for(sI = _suffixTypeMap.begin(); sI != _suffixTypeMap.end(); sI++)
    {
		cerr << "suffix: " << sI->first.str() 
             << ", type: " << sI->second->front()->getName()
             << endl;
    }
}

/******************************
*protected
******************************/


/******************************
*private	
******************************/


//----------------------------
// Function name: addSceneFileType
//----------------------------
//
//Parameters:
//p: SceneFileType *fileType
//GlobalVars:
//g: 
//Returns:
//r:Bool
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: 
//SeeAlso:
//s:
//
//------------------------------

Bool SceneFileHandler::FindOverride::operator() (SceneFileType *fileTypeP)
{
    if(fileTypeP == NULL)
        return false;

    if(fileTypeP->doOverride() == false)
        return true;

    if(fileTypeP->getOverridePriority() <= uiRefPriority)
        return true;

    return false;
}

Bool SceneFileHandler::addSceneFileType(SceneFileType &fileType)
{
	Bool retCode = false;

	list<IDString>::iterator sI;
	FileTypeMap   ::iterator smI;

	IDString suffix;

	if(_the == NULL)
    {
		_the = new SceneFileHandler;
    }

	for(  sI  = fileType.suffixList().begin();
          sI != fileType.suffixList().end(); 
        ++sI) 
    {
		suffix.set(sI->str());
		suffix.toLower();

		smI = _the->_suffixTypeMap.find(suffix);

		if (smI != _the->_suffixTypeMap.end()) 
        {
            if(fileType.doOverride() == true)
            {
                FindOverride           overrideFinder;
                FileTypeList::iterator lIt;
                
                overrideFinder.uiRefPriority = fileType.getOverridePriority();

                lIt = ::find_if(_the->_suffixTypeMap[suffix]->begin(),
                                _the->_suffixTypeMap[suffix]->end(),
                                 overrideFinder);

                _the->_suffixTypeMap[suffix]->insert(lIt, &fileType);

                SWARNING << "Added an file type with suffix "
                         << suffix 
                         << " overriding "
                         << endl;
            }
            else
            {
                _the->_suffixTypeMap[suffix]->push_back(&fileType);

                SWARNING << "Added an file type with suffix "
                         << suffix 
                         << " non overriding at the end of the list"
                         << endl;
            }
		}
		else 
        {
            FileTypeList *pTmpList = new FileTypeList;

            pTmpList->push_back(&fileType);

			_the->_suffixTypeMap[suffix] = pTmpList;

			retCode = true;
		}
	}

	return retCode;
}

/***************************
*instance methodes 
***************************/


/***************************
*public
***************************/


/**constructors & destructors**/


//----------------------------
// Function name: SceneFileHandler
//----------------------------
//
//Parameters:
//p: void
//GlobalVars:
//g: 
//Returns:
//r:
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: Default Constructor
//SeeAlso:
//s:
//
//------------------------------
SceneFileHandler::SceneFileHandler (void )
{
	return;
}

//----------------------------
// Function name: SceneFileHandler
//----------------------------
//
//Parameters:
//p: const SceneFileHandler &obj
//GlobalVars:
//g: 
//Returns:
//r:
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: Copy Constructor
//SeeAlso:
//s:
//
//------------------------------
SceneFileHandler::SceneFileHandler (const SceneFileHandler & )
{
	SWARNING << "In copy constructor; I shouldn't be in this corner" << endl; 
}

//----------------------------
// Function name: ~SceneFileHandler
//----------------------------
//
//Parameters:
//p: void
//GlobalVars:
//g: 
//Returns:
//r:
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: Destructor
//SeeAlso:
//s:
//
//------------------------------

SceneFileHandler &SceneFileHandler::the(void) 
{
    return *_the;
}

SceneFileHandler::~SceneFileHandler(void)
{
}

/*------------access----------------*/

/*------------properies-------------*/

/*------------your Category---------*/

/*------------Operators-------------*/



/****************************
*protected	
****************************/


/****************************
*private
****************************/


