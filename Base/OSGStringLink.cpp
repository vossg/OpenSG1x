
// System declarations

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#define OSG_COMPILEBASE

// Class declarations
#include "OSGStringLink.h"

OSG_USING_NAMESPACE

// Static Class Variable implementations: 


//----------------------------------------------------------------------
// Method: StringLink
// Author: jbehr
// Date:   Tue Jan 13 15:14:22 1998
// Description:
//         Class DefaultConstructor
//----------------------------------------------------------------------
StringLink::StringLink(const char *str)
: String(str, String::LINK)
{}

//----------------------------------------------------------------------
// Method: StringLink
// Author: jbehr
// Date:   Tue Jan 13 15:14:22 1998
// Description:
//         Class Copy Constructor
//----------------------------------------------------------------------
StringLink::StringLink(const StringLink &obj)
: String(obj.str(), String::LINK)
{}

//----------------------------------------------------------------------
// Method: StringLink
// Author: jbehr
// Date:   Tue Jan 13 15:14:22 1998
// Description:
//         Class Copy Constructor
//----------------------------------------------------------------------
StringLink::StringLink(const String &obj)
: String(obj.str(), String::LINK)
{}

//----------------------------------------------------------------------
// Method: ~StringLink
// Author: jbehr
// Date:   Tue Jan 13 15:14:22 1998
// Description:
//         Class Destructor
//----------------------------------------------------------------------
StringLink::~StringLink()
{}
