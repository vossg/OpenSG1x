#ifndef OSGSTRINGLINK_CLASS_DECLARATION
#define OSGSTRINGLINK_CLASS_DECLARATION

#include "OSGString.h"



OSG_BEGIN_NAMESPACE

/** String which always links to the data.


@author jbehr, Tue Jan 13 15:14:22 1998

*/

class OSGStringLink : public OSGString {
	typedef OSGString ParentClass;

public:

	/// Default Constructor
	OSGStringLink (const char *str = 0);

	/// Copy Constructor
	OSGStringLink (const OSGStringLink &obj);

	/// Copy Constructor
	OSGStringLink(const OSGString &obj);

	/// Destructor
	virtual ~OSGStringLink();

};

typedef OSGStringLink* OSGStringLinkP;

OSG_END_NAMESPACE

#endif // OSGSTRINGLINK_CLASS_DECLARATION
