#ifndef METHOD_H
#define METHOD_H

#include "List.h"

#include "AccessType.h"
#include "MemoryModel.h"
#include "MethodType.h"
#include "ImplementType.h"

#include "List.h"

#include "Base.h"

///
class Attribute;
class Class;

///
class Method : public Base {

	static unsigned _objCount;

///
	Class *_class;

///
	MethodType _methodType;
///
	MemoryModel _memoryModel;
///
	AccessType _accessType;
///
	ImplementType _implementType;

///
	unsigned _id;
	unsigned _listId;

	///

	char *_name;
///
	char *_type;
///
	char *_param;

	///
	char *_description;

	Attribute *_dependAttribute;

///
	bool _defaultModelValues;

	static char tmpNameBuffer[256];
	static char tmpParamBuffer[256];
	static char tmpDescriptionBuffer[256];

public:
	
	///
	Method (Class *c, char *name = 0);
	Method (Method &method);

	///
	virtual ~Method(void);

	Class *getClass (void) { return _class; }
///
	void setClass (Class *c);

///
	bool defaultModelValues (void) { return _defaultModelValues; }
///
	void touchModelValues (void) { _defaultModelValues = false; }

	unsigned id(void) { return _id; }

	unsigned listId(void) { return _listId; }
	void setListId(unsigned listId) { _listId = listId; }
///
	char *name (void);
///
	void setName (char *name);

///
	char *type (void);
///
	void setType (char *type);

///
	char *param(void);
///
	void setParam (char *param);

///
	char *description (void);
///
	void setDescription (char *description);

///
	MethodType methodType(void) { return _methodType; }
///
	void setMethodType (MethodType methodType) { _methodType = methodType; }

	///
	MemoryModel memoryModel (void) { return _memoryModel; }
	///
	void setMemoryModel (MemoryModel memoryModel) { _memoryModel = memoryModel; }

	ImplementType implementType (void) { return _implementType; }
///
	void setImplementType (ImplementType iT) { _implementType = iT; }
	///
	AccessType accessType (void) { return _accessType; }
	///
	void setAccessType (AccessType accessType) { _accessType = accessType; }

	Attribute *dependence (void) { return _dependAttribute; }
///
	void setDependence (Attribute *attribute, MethodType methodType);
	
///
	virtual void popupAttribView(void);	
};

#endif // METHOD_H








