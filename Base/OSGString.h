#ifndef OSGSTRING_CLASS_DECLARATION
#define OSGSTRING_CLASS_DECLARATION

#include "string.h"

#include <OSGConfig.h>

OSG_BEGIN_NAMESPACE

#ifdef WIN32 // Workaround for a bug in Visual C++ 6.0
class OSGString;
ostream& operator<< (ostream & os, const OSGString &obj);
#endif

/** Basic ASCII string container.


@author jbehr, Sat Dec 20 20:39:23 1997

*/

class OSGString {

public:

	/// TODOC
	enum MemType { COPY, LINK };

private:

	/// TODOC
	char *_str;

	/// TODOC
	MemType _memType;

public:

	/// Default Constructor
	explicit OSGString(unsigned size = 0);

	/// Constructor
	explicit OSGString(const char *str, MemType memType = COPY);

	/// Copy Constructor
	OSGString (const OSGString &obj, MemType memType = COPY);

	/// Destructor
	virtual ~OSGString();

	/// get method for attribute str
	inline const char * str(void) const { return _str; }

	/// 
  bool empty(void) const { return (_str && *_str) ? false : true; }
	
	/// set method for attribute str
	void set(const char *str, MemType memType  = COPY);

	/// change all char to upper
	void toupper (void);

	/// change all char to lower
	void tolower (void);

	/// get the str length
	unsigned length (void) const;

	/// TODOC
	void setLength(unsigned length);

	/// TODOC
	inline bool operator <(const OSGString &obj) const
  	{ return (_str && obj._str && (strcmp(_str, obj._str) < 0)); }

	/// TODOC
	inline bool operator ==(const OSGString &o) const
	{ return ((_str == o._str) ? 1 : (_str && o._str && !strcmp(_str, o._str))); }

	/// write str value in stream
	friend ostream &operator <<(ostream &os, 
                                const OSGString &obj);

};

typedef OSGString* OSGStringP;

OSG_END_NAMESPACE

#endif // OSGSTRING_CLASS_DECLARATION
