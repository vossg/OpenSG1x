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

#define OSG_COMPILESYSTEMLIB

// System declarations
#include <OSGConfig.h>
#include <iostream>


// Application declarations


// Class declarations

#include "OSGImageFileType.h"
#include "OSGImageFileHandler.h"
#include "OSGLog.h"


OSG_USING_NAMESPACE

// Static Class Varible implementations: 


//----------------------------------------------------------------------
// Method: ImageFileType
// Author: jbehr
// Date:   Tue Apr 11 15:32:43 2000
// Description:
//         Default Constructor
//----------------------------------------------------------------------
ImageFileType::ImageFileType ( const Char8 * suffixArray[], 
                               UInt16 suffixByteCount )
{
	Int32 suffixCount = suffixByteCount / sizeof(const Char8 *);
  Int32 i = 0;
	list<String>::iterator sI;

	_suffixList.resize(suffixCount);
	for (sI = _suffixList.begin(); sI != _suffixList.end(); sI++) {
		sI->set(suffixArray[i++]);
    SINFO << "add image suffix: " << *sI << endLog;
  }

	ImageFileHandler::addImageFileType(*this);
}

//----------------------------------------------------------------------
// Method: ImageFileType
// Author: jbehr
// Date:   Tue Apr 11 15:32:43 2000
// Description:
//         Copy Constructor
//----------------------------------------------------------------------
ImageFileType::ImageFileType (const ImageFileType &obj )
	: _suffixList(obj._suffixList)
{
	SWARNING << "In ImageFileType copy constructor" << endl;
}

//----------------------------------------------------------------------
// Method: ~ImageFileType
// Author: jbehr
// Date:   Tue Apr 11 15:32:43 2000
// Description:
//         Destructor
//----------------------------------------------------------------------
ImageFileType::~ImageFileType (void )
{
	return;
}

//----------------------------------------------------------------------
// Method: print
// Author: jbehr
// Date:   Tue Apr 11 15:32:43 2000
// Description:
//         Destructor
//----------------------------------------------------------------------
UInt64 ImageFileType::restore ( Image &image, const UChar8 *buffer,
                                Int32 memSize )
{
  return 0;
}

//----------------------------------------------------------------------
// Method: print
// Author: jbehr
// Date:   Tue Apr 11 15:32:43 2000
// Description:
//         Destructor
//----------------------------------------------------------------------
UInt64 ImageFileType::store ( const Image &image, UChar8 *buffer,
                              Int32 memSize )
{
  return 0;
}

//----------------------------------------------------------------------
// Method: print
// Author: jbehr
// Date:   Tue Apr 11 15:32:43 2000
// Description:
//         Destructor
//----------------------------------------------------------------------
UInt64 ImageFileType::maxBufferSize(const Image &image )
{
  return 0;
}

//----------------------------------------------------------------------
// Method: print
// Author: jbehr
// Date:   Tue Apr 11 15:32:43 2000
// Description:
//         Destructor
//----------------------------------------------------------------------
void ImageFileType::print(void)
{
	list<String>::iterator sI;

	SLOG << getMimeType();

	if (_suffixList.empty())
    {
      SLOG << ": Suffix: ";
			for (sI = _suffixList.begin(); sI != _suffixList.end(); sI++) 
				Log().stream(OSG::LOG_DEBUG) << sI->str() << " ";
    }

	cerr << endl;
}

