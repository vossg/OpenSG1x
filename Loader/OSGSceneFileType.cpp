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


//---------------------------------------------------------
// 	Includes  
//---------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <OSGLog.h>

#include "OSGSceneFileType.h"
#include "OSGSceneFileHandler.h"

OSG_USING_NAMESPACE

namespace 
{
    char cvsid_cpp[] = "@(#)$Id: $";
    char cvsid_hpp[] = OSGSCENEFILETYPE_HEADER_CVSID;
}

//---------------------------------------------------------

SceneFileType::SceneFileType(const Char8  *suffixArray[], 
                                   UInt16  suffixByteCount,
                                   Bool    override,
                                   UInt32  overridePriority) :
    _suffixList      (                ),
    _override        (override        ),
    _overridePriority(overridePriority)
{
    FINFO(( "Init %s Scene File Type %d\n", suffixArray[0], this ));

	int count = (suffixByteCount / sizeof(const Char8 *)), i = 0;
	list<IDString>::iterator sI;

	_suffixList.resize(count);
	for (sI = _suffixList.begin(); sI != _suffixList.end(); sI++)
		sI->set(suffixArray[i++]);

	SceneFileHandler::addSceneFileType(*this);
}

//---------------------------------------------------------
SceneFileType::SceneFileType(const SceneFileType &obj) :
	_suffixList      (obj._suffixList      ),
    _override        (obj._override        ),
    _overridePriority(obj._overridePriority)
{
	SWARNING << "In SceneFileType copy constructor" << endl;
}

//---------------------------------------------------------
SceneFileType::~SceneFileType(void)
{
	return;
}

//---------------------------------------------------------
void SceneFileType::print(void)
{
	list<IDString>::iterator sI;

	osgLog() << getName();

	if (_suffixList.empty())
		osgLog() << "NONE";
	else
		for (sI = _suffixList.begin(); sI != _suffixList.end(); sI++) 
			osgLog().stream(OSG::LOG_DEBUG) << sI->str() << " ";

	osgLog() << endl;
}

//---------------------------------------------------------

list<IDString> &SceneFileType::suffixList(void)
{
    return _suffixList;
}

//---------------------------------------------------------

Bool SceneFileType::doOverride(void)
{
    return _override;
}

//---------------------------------------------------------

UInt32 SceneFileType::getOverridePriority(void)
{
    return _overridePriority;
}

//---------------------------------------------------------

SceneFileType::FCPtrStore SceneFileType::readTopNodes(
    const Char8  *fileName,
          UInt32  uiReplaceOptions) const 
{
  FieldContainerPtr fcPtr = read(fileName, uiReplaceOptions);

  vector<FieldContainerPtr> fcVec;

  FDEBUG (("Running generic SceneFileType::readTopNodes()\n"));

  if (fcPtr != osg::NullFC)
    fcVec.push_back(fcPtr);

  return fcVec;
}

SceneFileType::FCPtrStore SceneFileType::readTopNodes(
    const Char8  *fileName,
          UInt32  uiAddOptions,
          UInt32  uiSubOptions) const 
{
  FieldContainerPtr fcPtr = read(fileName, uiAddOptions, uiSubOptions);
  vector<FieldContainerPtr> fcVec;

  FDEBUG (("Running generic SceneFileType::readTopNodes()\n"));

  if (fcPtr != osg::NullFC)
    fcVec.push_back(fcPtr);

  return fcVec;
}
