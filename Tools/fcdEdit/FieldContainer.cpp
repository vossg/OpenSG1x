// System declarations
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <xmlpp.hpp>

using namespace std;
using namespace xmlpp;

// Application declarations


// Class declarations
#include "FieldContainer.h"


// Static Class Varible implementations: 
const char FieldContainer::_descFileSuffix[] = "fcd";
const char FieldContainer::_decFileSuffix[] = "h";
const char FieldContainer::_inlFileSuffix[] = "inl";
const char FieldContainer::_impFileSuffix[] = "cpp";
const char FieldContainer::_nil[] = "nil";

FieldContainer::KeyDic FieldContainer::_keyDic[] = {
	{ FieldContainer::NAME_FIELD,         "name" },
	{ FieldContainer::PARENT_FIELD,       "parent" },
	{ FieldContainer::LIBRARY_FIELD,      "library" },	
	{ FieldContainer::POINTERFIELDTYPES_FIELD,  "pointerfieldtypes" },
	{ FieldContainer::TYPE_FIELD,         "type" },
	{ FieldContainer::CARDINALITY_FIELD,  "cardinality" },
	{ FieldContainer::VISIBILITY_FIELD,   "visibility" },
	{ FieldContainer::DEFAULTVALUE_FIELD, "defaultValue" },
	{ FieldContainer::UNKNOWN_FIELD,      0 }
};

const char *FieldContainer::_pointerFieldTypesName[] = {
	"none", "single", "multi", "both"
};

//----------------------------------------------------------------------
// Method: FieldContainer
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         Class Constructor
//----------------------------------------------------------------------
FieldContainer::FieldContainer (void )
: _name(0), _parentFieldContainer(0), _description(0),
	_library(0), _pointerFieldTypes(0)
{
	return;
}

//----------------------------------------------------------------------
// Method: FieldContainer
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         Class Copy Constructor
//----------------------------------------------------------------------
FieldContainer::FieldContainer (FieldContainer &obj )
: _name(0), _parentFieldContainer(0), _description(0),
	_library(0), _pointerFieldTypes(0)
{
	return;
}

//----------------------------------------------------------------------
// Method: ~FieldContainer
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         Class Descructor
//----------------------------------------------------------------------
FieldContainer::~FieldContainer (void )
{
	return;
}

//----------------------------------------------------------------------
// Method: clear
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//       
//----------------------------------------------------------------------
void FieldContainer::clear (void)
{
	setName(0);
	setParentFieldContainer(0);
	setLibrary(0);
	setDescription(0);
	_pointerFieldTypes = 0;
	
	_fieldList.clear();

	return;
}

//----------------------------------------------------------------------
// Method: getField
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
FieldContainer::FieldKey FieldContainer::findFieldKey  ( const char *key)
{
	FieldContainer::FieldKey keyValue = UNKNOWN_FIELD;
	int i;

	for (i = 0; _keyDic[i].name; i++) {
		if (!strcmp(_keyDic[i].name,key)) {
			keyValue = _keyDic[i].key;
			break;
		}
	}

	return keyValue;
}

//----------------------------------------------------------------------
// Method: putField
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
void FieldContainer::putField ( ofstream &out, const char *prefix,
											FieldContainer::FieldKey key, const char *value)
{
	int i;
	char *name = 0;

	for (i = 0; _keyDic[i].name; i++)
		if (_keyDic[i].key == key) {
			name = _keyDic[i].name;
			break;
		}

	if (name && value && *value) 
		out << prefix << name << "=" << "\"" << value << "\"" << '\n';
}

//----------------------------------------------------------------------
// Method: pointerFieldTypes
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
const char *FieldContainer::pointerFieldTypesStr(int i)
{
	int vecSize = sizeof(_pointerFieldTypesName )/ sizeof(char*);

	return (i >= 0 && i < vecSize) ? _pointerFieldTypesName[i] : 0;
}

//----------------------------------------------------------------------
// Method: setName
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         set method for attribute name
//----------------------------------------------------------------------
void FieldContainer::setName (const char* name )
{
	delete _name;

	if (name && *name && strcmp(name,_nil)) {
		_name = new char [strlen(name)+1];
		strcpy(_name,name);
	}
	else 
		_name = 0;
}

//----------------------------------------------------------------------
// Method: setParentFieldContainer
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         set method for attribute parentFieldContainer
//----------------------------------------------------------------------
void FieldContainer::setParentFieldContainer (const char* parentFieldContainer )
{
	delete _parentFieldContainer;

	if (parentFieldContainer && *parentFieldContainer) {
		_parentFieldContainer = new char [strlen(parentFieldContainer)+1];
		strcpy(_parentFieldContainer,parentFieldContainer);
	}
	else 
		_parentFieldContainer = 0;
}

//----------------------------------------------------------------------
// Method: setDescription
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         set method for attribute description
//----------------------------------------------------------------------
void FieldContainer::setDescription (const char* description )
{
	delete _description;

	if (description && *description) {
		_description = new char [strlen(description)+1];
		strcpy(_description,description);
	}
	else 
		_description = 0;
}

//----------------------------------------------------------------------
// Method: setLibrary
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Library:
//         set method for attribute library
//----------------------------------------------------------------------
void FieldContainer::setLibrary (const char* library )
{
	delete _library;

	if (library && *library) {
		_library = new char [strlen(library)+1];
		strcpy(_library,library);
	}
	else 
		_library = 0;
}

//----------------------------------------------------------------------
// Method: setPointerFieldTypes
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         set method for attribute pointerFieldTypes
//----------------------------------------------------------------------
void FieldContainer::setPointerFieldTypes (const char* str )
{
	int i, n = sizeof(_pointerFieldTypesName)/sizeof(const char *);

	for (i = 0; i < n; ++i) 
		if (!strcasecmp(str, _pointerFieldTypesName[i]))
			_pointerFieldTypes = i;
}

//----------------------------------------------------------------------
// Method: readDesc
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
bool FieldContainer::readDesc (const char *fn)
{
	bool retCode = false;

	ifstream istr( fn );

	int nodeCount;
	list<Field>::iterator npI = _fieldList.end();
	xmlcontextptr               context( new xmlcontext );
	xmldocument                 node( context );
	xmlnodeptr                  nP;
	xmlnodelist::const_iterator nI;
	xmlattributes               attr;
	xmlattributes::iterator     aI;

	clear();

	if (istr) {
		try
			{
				node.load( istr, context ); 
				attr = node.get_attrmap();
				for (aI = attr.begin(); aI != attr.end(); aI++)
					switch (findFieldKey(aI->first.c_str())) {
					case NAME_FIELD:
						setName(aI->second.c_str());
						break;
					case PARENT_FIELD:
						setParentFieldContainer(aI->second.c_str());
						break;
					case LIBRARY_FIELD:
						setLibrary(aI->second.c_str());
						break;
					case POINTERFIELDTYPES_FIELD:
						setPointerFieldTypes(aI->second.c_str());
						break;
					default:
						break;
					}
				
				for ( nI = node.get_nodelist().begin();
							nI != node.get_nodelist().end(); nI++) {
					nP = *nI;		
					attr = nP->get_attrmap();                                     
					if (attr.empty()) {
						if (nP->get_nodelist().size()) {
							nP = nP->get_nodelist().front();
							setDescription (nP->get_cdata().c_str());
						}
					}
					else {
						npI = _fieldList.insert(_fieldList.end());
						for (aI = attr.begin(); aI != attr.end(); aI++) {
							switch (findFieldKey(aI->first.c_str())) {
							case NAME_FIELD:
								npI->setName(aI->second.c_str());
								break;
							case TYPE_FIELD:
								npI->setType(aI->second.c_str());
								break;
							case CARDINALITY_FIELD:
								npI->setCardinality(aI->second.c_str());
								break;
							case VISIBILITY_FIELD:
								npI->setVisibility(aI->second.c_str());
								break;
							case DEFAULTVALUE_FIELD:
								npI->setDefaultValue(aI->second.c_str());
								break;
							default:
							case UNKNOWN_FIELD:
								break;	
							}
						}
						while ((nodeCount = nP->get_nodelist().size())) {
							if (nodeCount == 1) {
								nP = nP->get_nodelist().front();
								if (nP->get_type() == xml_nt_cdata) {
									npI->setDescription(nP->get_cdata().c_str());
									break;
								}
							}
							else {
								cerr << "ERROR: Field can't have children nodes" << endl;
							}
						}
					}
				}
			}
		catch (xmlerror e)
			{
				xmllocation where( context->get_location() );
				xmlstring errmsg( e.get_strerror() );
				
				// print out where the error occured
				cout << fn << ":" << where.get_line() << " ";
				cout << "at position " << where.get_pos();
				cout << ": error: " << errmsg.c_str();
				cout << endl;
				
				// print out line where the error occured
				ifstream errfile( fn );
				int linenr = where.get_line();
				char linebuffer[1024];
				for(int i=0;i<linenr&&!errfile.eof();i++)
					errfile.getline(linebuffer,1024);
				
				int pos = where.get_pos();
				if (pos>=80) pos%=80;
				
				std::string line( linebuffer + (where.get_pos()-pos) );
				if (line.length()>=79) line.erase(79);
				cout << line.c_str() << endl;
				for(int j=2;j<pos;j++)
					cout << ' ';
				cout << '^' << endl;
			}
		istr.close();
	}

	return retCode;
}


//----------------------------------------------------------------------
// Method: writeDesc
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
bool FieldContainer::writeDesc (const char *fN)
{
	bool retCode = false;

  list<Field>::iterator npI;
  char fileName[512];
  ofstream out;
  const char *nprefix = "\t", *pprefix = "\t\t";
 
  if (fN)
    out.open(fN);
  else {
    sprintf (fileName,"%s.%s", name(), _descFileSuffix);
    out.open(fileName);
  }
 
  if (out) {
    out << "<?xml version=\"1.0\"?>" << endl << endl;
    out << "<FieldContainer" << endl;
 
    putField(out, nprefix, NAME_FIELD, _name);
    putField(out, nprefix, PARENT_FIELD, _parentFieldContainer);
    putField(out, nprefix, LIBRARY_FIELD, _library);
    putField(out, nprefix, POINTERFIELDTYPES_FIELD, 
						 _pointerFieldTypesName[_pointerFieldTypes]);
    out << ">" << endl;
    out << _description << endl;
 
    for (npI = _fieldList.begin(); npI != _fieldList.end(); npI++) {
      out << nprefix << "<Field" << endl;
      putField(out, pprefix, NAME_FIELD, npI->name());
      putField(out, pprefix, TYPE_FIELD, npI->typeStr());
      putField(out, pprefix, CARDINALITY_FIELD, npI->cardinalityStr());
      putField(out, pprefix, VISIBILITY_FIELD, npI->visibilityStr());
      putField(out, pprefix, DEFAULTVALUE_FIELD, npI->defaultValue());
      out << nprefix << ">" << endl;
      out << nprefix << npI->description() << endl;
      out << nprefix << "</Field>" << endl;
    }
 
    out << "</FieldContainer>" << endl;
 
    retCode = true;
  }
 
 	return retCode;
}


//----------------------------------------------------------------------
// Method: writeDec
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
bool FieldContainer::writeCode (bool base, bool fc)
{	
	bool retCode = false;
	char decFile[256];
	char inlFile[256];
	char impFile[256];

	if (name()) {

		if (base) {
			retCode = true;
			sprintf(decFile,"%sBase.%s", name(), decFileSuffix());
			sprintf(decFile,"%sBase.%s", name(), inlFileSuffix());
			sprintf(impFile,"%sBase.%s", name(), impFileSuffix());

			retCode &= writeBaseCodeDec(decFile);
			retCode &= writeBaseCodeInl(decFile);
			retCode &= writeBaseCodeImp(decFile,impFile);

			if (retCode)
				cerr << "Write OK, Wrote base dec,inl and imp file" << endl;
			else
				cerr << "Write error: Couldn't write the dec,inl and imp file" << endl;
		}
		
		if (fc) {
			retCode = true;
			sprintf(decFile,"%s.%s", name(), decFileSuffix());
			sprintf(decFile,"%s.%s", name(), inlFileSuffix());
			sprintf(impFile,"%s.%s", name(), impFileSuffix());
			
			retCode &= writeCodeDec(decFile);
			retCode &= writeCodeInl(decFile);
			retCode &= writeCodeImp(decFile,impFile);

			if (retCode)
				cerr << "Write OK, Wrote dec,inl and imp file" << endl;
			else
				cerr << "Write error: Couldn't write the dec,inl and imp file" << endl;
		}
		
	}
	else
		cerr <<  "ERROR: No node name" << endl;

	
	return retCode;
}


//----------------------------------------------------------------------
// Method: writeDec
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
bool FieldContainer::writeBaseCodeDec (const char *decFile)
{
	bool retCode = false;

	return retCode;
}

//----------------------------------------------------------------------
// Method: writeDec
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
bool FieldContainer::writeBaseCodeInl (const char *InlFile)
{
	bool retCode = false;

	return retCode;
}
	
	//----------------------------------------------------------------------
	// Method: writeImp
	// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
bool FieldContainer::writeBaseCodeImp ( const char *decFile, 
																				const char *impFile)
{
	bool retCode = false;

	return retCode;
}


//----------------------------------------------------------------------
// Method: writeDec
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
bool FieldContainer::writeCodeDec (const char *decFile)
{
	bool retCode = false;

	return retCode;
}

//----------------------------------------------------------------------
// Method: writeInl
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
bool FieldContainer::writeCodeInl (const char *decFile)
{
	bool retCode = false;

	return retCode;
}
	
//----------------------------------------------------------------------
// Method: writeImp
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
bool FieldContainer::writeCodeImp ( const char *decFile, 
																		const char *impFile)
{
	bool retCode = false;

	return retCode;
}


//----------------------------------------------------------------------
// Method: newField
// Author: jbehr
// Date:   Thu Jan  24 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
int FieldContainer::newField(const Field &part)
{
	int i = _fieldList.size();

  _fieldList.push_back(part); 
	
	return i;
}

//----------------------------------------------------------------------
// Method: delField
// Author: jbehr
// Date:   Thu Jan  24 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
void FieldContainer::delField(unsigned index)
{
	list<Field>::iterator partI;

	for (partI = _fieldList.begin(); partI != _fieldList.end(); partI++)
		if (!index--) {
			_fieldList.erase(partI);
			break;
		}
}

//----------------------------------------------------------------------
// Method: getField
// Author: jbehr
// Date:   Thu Jan  24 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
Field *FieldContainer::getField(unsigned index)
{
	list<Field>::iterator partI;

	for (partI = _fieldList.begin(); partI != _fieldList.end(); partI++)
		if (!index--) 
			return &(*partI);

	return 0;
}

//----------------------------------------------------------------------
// Method: moveFieldLeft
// Author: jbehr
// Date:   Thu Jan  24 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
bool FieldContainer::moveFieldLeft(unsigned index)
{
	bool retCode = false;
	list<Field>::iterator partI,prevI,nextI;

	if (index > 0) {
		for ( partI = _fieldList.begin(); 
					partI != _fieldList.end(); partI++)
			if (!index--) {
				nextI = partI;
				++nextI;
				_fieldList.splice(prevI,_fieldList,partI,nextI);
				retCode = true;
			}
			else
				prevI = partI;
	}

	return retCode;
}

//----------------------------------------------------------------------
// Method: moveFieldRight
// Author: jbehr
// Date:   Thu Jan  24 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
bool FieldContainer::moveFieldRight (unsigned index)
{
	return moveFieldLeft(index+1);
}
	
	
		

			

