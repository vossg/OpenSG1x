
// System declarations

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

// Application declarations


// Class declarations
#include "OSGStringLink.h"

using OSG::OSGStringLink;

#ifdef WIN32
using OSG::OSGString;
#endif

// Static Class Variable implementations: 


//----------------------------------------------------------------------
// Method: OSGStringLink
// Author: jbehr
// Date:   Tue Jan 13 15:14:22 1998
// Description:
//         Class DefaultConstructor
//----------------------------------------------------------------------
OSGStringLink::OSGStringLink(const char *str)
: OSGString(str, OSGString::LINK)
{}

//----------------------------------------------------------------------
// Method: OSGStringLink
// Author: jbehr
// Date:   Tue Jan 13 15:14:22 1998
// Description:
//         Class Copy Constructor
//----------------------------------------------------------------------
OSGStringLink::OSGStringLink(const OSGStringLink &obj)
: OSGString(obj.str(), OSGString::LINK)
{}

//----------------------------------------------------------------------
// Method: OSGStringLink
// Author: jbehr
// Date:   Tue Jan 13 15:14:22 1998
// Description:
//         Class Copy Constructor
//----------------------------------------------------------------------
OSGStringLink::OSGStringLink(const OSGString &obj)
: OSGString(obj.str(), OSGString::LINK)
{}

//----------------------------------------------------------------------
// Method: ~OSGStringLink
// Author: jbehr
// Date:   Tue Jan 13 15:14:22 1998
// Description:
//         Class Destructor
//----------------------------------------------------------------------
OSGStringLink::~OSGStringLink()
{}
