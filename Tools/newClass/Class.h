#ifndef CLASS_H
#define CLASS_H

#include "List.h"
#include "Attribute.h"
#include "Method.h"

#include "Base.h"

#include <fstream>

///
class XMNewClass;

///
class Class : public Base {

///
	XMNewClass *_view;

///
	char *_name;
///
	char *_parent;
	List<char> _parentList;
	List<char> _lineList;

	char *_description;
	char *_responsibility;
	
///
	List<Attribute> _attributeList;
///
	List<Method> _methodList;

	bool createParentList(void);
	bool createLineList(char *text, unsigned lineLen);

	static char *_decFileSuffix;
	static char *_impFileSuffix;

	void writeDec(void);
	void writeImp(void);

  void writeBaseHead   (ofstream & ostream);
	void writeDecHead    (ofstream & ostream);

  void writeAttribList (ofstream &ostream, 
												AccessType accessType, MemoryModel memModel );
  void writeMethodList (ofstream &ostream, 
												AccessType accessType, MemoryModel memModel );
 
	char *rmWS (char *str);

public:

///
	Class (XMNewClass *view, char *name = 0);
///
	virtual ~Class (void);

///
	char *name(void) { return _name; }
///
	void setName (char *name);

	char *parent(void) { return _parent; }
	void setParent (char *name);

///
	char *description (void) { return _description;}
///
	void setDescription (char *description);

///
	char *responsibility (void) { return _responsibility;}
///
	void setResponsibility (char *responsibility);



	List<Attribute> *attributeList(void) { return &_attributeList; }
///
	List<Method> *methodList(void) { return &_methodList; }

///
	unsigned numOfMethods (void) { return _methodList.numOfElem(); }
///
	Method *method (unsigned methodID);
///
	void addMethod (Method *method);
///
	void removeMethod (Method *method);
///
	bool isMethod (Method *method);

///
	unsigned numOfAttributes (void) { return _attributeList.numOfElem(); }
///
	Attribute *attribute (unsigned attributeID);
///
	void addAttribute (Attribute *attribute);
///
	void removeAttribute (Attribute *attribute);
///
	bool isAttribute (Attribute *attribute);

///
	void refreshView (void);	
///
	void write (void);

};
	
#endif // CLASS_H









