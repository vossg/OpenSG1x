#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "AccessType.h"
#include "MemoryModel.h"

#include "List.h"

///
class Class;

#include "Base.h"

class Method;

///
class XMAttributeView;

///
class Attribute : public Base{

///
	Class *_class;

///
	static unsigned _objCount;

	unsigned _id;
	unsigned _listId;

///
	char *_name;
///
	char *_type;
///
	char *_description;

	char *_initialValue;

	///
	AccessType _accessType;
	MemoryModel _memoryModel;
	
	/// 
	Method *_setMethod;
///
	Method *_getMethod;

	bool _underscorePrefix;

	bool _getPrefix;

///
	bool _defaultModelValues;

public:

///
	Attribute ( Class *c, char *name = 0);
	Attribute ( Attribute &attribue);
///
	virtual ~Attribute (void);

	bool defaultModelValues (void) { return _defaultModelValues; }
///
	void touchModelValues (void) { _defaultModelValues = false; }

///
	Class *getClass (void) { return _class; }
///
	void setClass (Class *c);

	/*
///
	unsigned id (void) { return _id; }
///
	void setID (unsigned id) { _id = id; }
	*/

	unsigned listId (void) { return _listId; }
///
	void setListId (unsigned listId) { _listId = listId; }

	
///
	char *name   (void) { return _name; }
	void setName (char *line);

///
	char *type (void) { return _type; }
///
	void setType (char *type);
///
	char *description(void) { return _description; }
	void setDescription (char *description);

	char *initialValue(void) { return _initialValue; }
	void setInitialValue (char *initialValue);

///
	AccessType accessType (void) { return _accessType; }
///
	void setAccessType (AccessType accessType) { _accessType = accessType; }

	Method *getMethod(void) { return _getMethod; }\
  ///
  bool createGetMethod (void);

	MemoryModel memoryModel(void) { return _memoryModel; }
	void setMemoryModel (MemoryModel mm) { _memoryModel = mm; }

	bool underscorePrefix(void) { return _underscorePrefix; }
	void setUnderscorePrefix (bool prefix = true) { _underscorePrefix = prefix; }

	bool getPrefix(void) { return _getPrefix; }
	void setGetPrefix (bool prefix = true) { _getPrefix = prefix; }

	///
	Method *setMethod(void) { return _setMethod; }
  ///
  bool createSetMethod (void);

	bool releaseMethodDepend(Method *method);

///
	virtual void popupAttribView(void);
};

#endif // ATTRIBUTE_H









