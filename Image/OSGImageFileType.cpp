// System declarations
#include <OSGConfig.h>
#include <iostream>


// Application declarations


// Class declarations
#include "OSGImageFileType.h"
#include "OSGImageFileHandler.h"
#include "OSGLog.h"


using OSG::OSGImageFileType;

// Static Class Varible implementations: 


//----------------------------------------------------------------------
// Method: OSGImageFileType
// Author: jbehr
// Date:   Tue Apr 11 15:32:43 2000
// Description:
//         Default Constructor
//----------------------------------------------------------------------
OSGImageFileType::OSGImageFileType ( const char * suffixArray[], 
																		 OSGUInt16 suffixByteCount,
																		 OSGInt16 majorMagic, 
																		 OSGInt16 minorMagic )
	: _majorMagic(majorMagic), _minorMagic(minorMagic)
{
	int count = suffixByteCount / sizeof(const char *), i = 0;
	list<OSGString>::iterator sI;

	_suffixList.resize(count);
	for (sI = _suffixList.begin(); sI != _suffixList.end(); sI++)
		sI->set(suffixArray[i++]);

	OSGImageFileHandler::addImageFileType(*this);
}

//----------------------------------------------------------------------
// Method: OSGImageFileType
// Author: jbehr
// Date:   Tue Apr 11 15:32:43 2000
// Description:
//         Copy Constructor
//----------------------------------------------------------------------
OSGImageFileType::OSGImageFileType (const OSGImageFileType &obj )
	: _suffixList(obj._suffixList)
{
	SWARNING << "In OSGImageFileType copy constructor" << endl;
}

//----------------------------------------------------------------------
// Method: ~OSGImageFileType
// Author: jbehr
// Date:   Tue Apr 11 15:32:43 2000
// Description:
//         Destructor
//----------------------------------------------------------------------
OSGImageFileType::~OSGImageFileType (void )
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
void OSGImageFileType::print(void)
{
	list<OSGString>::iterator sI;

	SDEBUG << getName() 
				 << ": Magic: " << _majorMagic << ", " << _minorMagic
				 << ": Suffix: ";

	if (_suffixList.empty())
    {
			SDEBUG << "NONE";
    }
	else
    {
			for (sI = _suffixList.begin(); sI != _suffixList.end(); sI++) 
				osgLog().stream(OSG::LOG_DEBUG) << sI->str() << " ";
    }

	cerr << endl;
}

