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

#ifdef WIN32
#define strcasecmp stricmp
#endif

// Class declarations
#include "FieldContainer.h"

// Include the template strings
#include "FCFieldsTemplate_h.h"
#include "FCBaseTemplate_h.h"
#include "FCBaseTemplate_inl.h"
#include "FCBaseTemplate_cpp.h"
#include "FCTemplate_h.h"
#include "FCTemplate_inl.h"
#include "FCTemplate_cpp.h"


// Static Class Varible implementations: 
const char FieldContainer::_filePrefix[] = "OSG";
const char FieldContainer::_descFileSuffix[] = "fcd";
const char FieldContainer::_decFileSuffix[] = "h";
const char FieldContainer::_inlFileSuffix[] = "inl";
const char FieldContainer::_impFileSuffix[] = "cpp";
const char FieldContainer::_nil[] = "nil";

FieldContainer::KeyDic FieldContainer::_keyDic[] = {
	{ FieldContainer::NAME_FIELD,              "name" },
	{ FieldContainer::PARENT_FIELD,            "parent" },
	{ FieldContainer::LIBRARY_FIELD,           "library" },	
	{ FieldContainer::STRUCTURE_FIELD,         "structure" },
	{ FieldContainer::POINTERFIELDTYPES_FIELD, "pointerfieldtypes" },
	{ FieldContainer::TYPE_FIELD,              "type" },
	{ FieldContainer::CARDINALITY_FIELD,       "cardinality" },
	{ FieldContainer::VISIBILITY_FIELD,        "visibility" },
	{ FieldContainer::DEFAULTVALUE_FIELD,      "defaultValue" },
	{ FieldContainer::DEFAULTHEADER_FIELD,     "defaultHeader" },
	{ FieldContainer::HEADER_FIELD,            "header" },
	{ FieldContainer::ACCESS_FIELD,            "access" },
	{ FieldContainer::SYSTEMCOMPONENT_FIELD,   "systemcomponent" },
	{ FieldContainer::PARENTSYSTEMCOMPONENT_FIELD,   "parentsystemcomponent" },
	{ FieldContainer::UNKNOWN_FIELD, 0}
};

const char *FieldContainer::_pointerFieldTypesName[] = {
	"none", "single", "multi", "both"
};

const char *FieldContainer::_abstractName[] = {
	"concrete", "abstract"
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
	_library(0), _pointerFieldTypes(0), _abstract(0),
	_systemComponent(false), _parentSystemComponent(true)
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
	_library(0), _pointerFieldTypes(0), _abstract(0),
	_systemComponent(false), _parentSystemComponent(true)
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
	_abstract = 0;
	_systemComponent = false;
	_parentSystemComponent = true;
	
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
// Method: abstractStr
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
const char *FieldContainer::abstractStr(int i)
{
	int vecSize = sizeof(_abstractName )/ sizeof(char*);

	return (i >= 0 && i < vecSize) ? _abstractName[i] : 0;
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
		{
			_pointerFieldTypes = i;
			break;
		}

	if ( i == n )
	{
		cerr << "FieldContainer::setPointerFieldTypes: string " << str 
			 << " not recognized!" << endl;
	}
}

//----------------------------------------------------------------------
// Method: setAbstract
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         set method for attribute abstract
//----------------------------------------------------------------------
void FieldContainer::setAbstract (const char* str )
{
	int i, n = sizeof(_abstractName)/sizeof(const char *);

	for (i = 0; i < n; ++i) 
		if (!strcasecmp(str, _abstractName[i])) 
			{
				_abstract = i;
				break;
			}

	if ( i == n )
	{
		cerr << "FieldContainer::setAbstract: string " << str << " not recognized!"
			 << endl;
	}
}

//----------------------------------------------------------------------
// Method: setSystemComponent
// Author: dr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         set method for attribute systemComponent
//----------------------------------------------------------------------
void FieldContainer::setSystemComponent (const char* str )
{
	if ( ! strcasecmp(str, "true" ) )
		_systemComponent = true;
	else if ( ! strcasecmp(str, "false" ) )
		_systemComponent = false;
	else
	{
		cerr << "FieldContainer::setSystemComponent: string " << str 
			 << " not recognized!" << endl;
	}
}

//----------------------------------------------------------------------
// Method: setParentSystemComponent
// Author: dr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         set method for attribute systemComponent
//----------------------------------------------------------------------
void FieldContainer::setParentSystemComponent (const char* str )
{
	if ( ! strcasecmp(str, "true" ) )
		_parentSystemComponent = true;
	else if ( ! strcasecmp(str, "false" ) )
		_parentSystemComponent = false;
	else
	{
		cerr << "FieldContainer::setParentSystemComponent: string " << str 
			 << " not recognized!" << endl;
	}
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
					case STRUCTURE_FIELD:
						setAbstract(aI->second.c_str());
						break;
					case SYSTEMCOMPONENT_FIELD:
						setSystemComponent(aI->second.c_str());
						break;
					case PARENTSYSTEMCOMPONENT_FIELD:
						setParentSystemComponent(aI->second.c_str());
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
							case ACCESS_FIELD:
								npI->setAccess(aI->second.c_str());
								break;
							case DEFAULTHEADER_FIELD:
								npI->setDefaultHeader(aI->second.c_str());
								break;
							case HEADER_FIELD:
								npI->setHeader(aI->second.c_str());
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
								cerr << "ERROR: Fields can't have children nodes" << endl;
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
    sprintf (fileName,"%s%s.%s", filePrefix(), name(), _descFileSuffix);
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
    putField(out, nprefix, STRUCTURE_FIELD, _abstractName[_abstract]);
    putField(out, nprefix, SYSTEMCOMPONENT_FIELD, 
			 _systemComponent?"true":"false");
    putField(out, nprefix, PARENTSYSTEMCOMPONENT_FIELD, 
			 _parentSystemComponent?"true":"false");
    out << ">" << endl;
		if (_description && *_description)
	    out << _description << endl;
 
    for (npI = _fieldList.begin(); npI != _fieldList.end(); npI++) {
      out << nprefix << "<Field" << endl;
      putField(out, pprefix, NAME_FIELD, npI->name());
      putField(out, pprefix, TYPE_FIELD, npI->typeStr());
      putField(out, pprefix, CARDINALITY_FIELD, npI->cardinalityStr());
      putField(out, pprefix, VISIBILITY_FIELD, npI->visibilityStr());
      putField(out, pprefix, DEFAULTVALUE_FIELD, npI->defaultValue());
      putField(out, pprefix, DEFAULTHEADER_FIELD, npI->defaultHeader());
      putField(out, pprefix, HEADER_FIELD, npI->header());
      putField(out, pprefix, ACCESS_FIELD, npI->accessStr());
      out << nprefix << ">" << endl;
			if (npI->description() && *npI->description())
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
	char fldFile[256];
	char decFile[256];
	char inlFile[256];
	char impFile[256];

	if (name()) {

		if (base) {
			retCode = true;
			sprintf(fldFile,"%s%sFields.%s", filePrefix(), name(), 
											decFileSuffix());
			sprintf(decFile,"%s%sBase.%s", filePrefix(), name(), 
											decFileSuffix());
			sprintf(inlFile,"%s%sBase.%s", filePrefix(), name(), 
											inlFileSuffix());
			sprintf(impFile,"%s%sBase.%s", filePrefix(), name(), 
											impFileSuffix());

			retCode &= writeCodeFields(fldFile);
			retCode &= writeBaseCodeDec(decFile);
			retCode &= writeBaseCodeInl(inlFile);
			retCode &= writeBaseCodeImp(decFile,impFile);

			if (retCode)
				cerr << "Write OK, Wrote base fields,dec,inl and imp file" << endl;
			else
				cerr << "Write error: Couldn't write the dec,inl and imp file" << endl;
		}
		
		if (fc) {
			retCode = true;
			sprintf(decFile,"%s%s.%s", filePrefix(), name(), decFileSuffix());
			sprintf(inlFile,"%s%s.%s", filePrefix(), name(), inlFileSuffix());
			sprintf(impFile,"%s%s.%s", filePrefix(), name(), impFileSuffix());
			
			FILE *f;
			if ( f = fopen( decFile, "r" ) )
			{
				fclose(f);
				cerr << decFile << " exists, please remove it and try again!" << endl;
				retCode = false;
			}
			if ( f = fopen( inlFile, "r" ) )
			{
				fclose(f);
				cerr << inlFile << " exists, please remove it and try again!" << endl;
				retCode = false;
			}
			if ( f = fopen( impFile, "r" ) )
			{
				fclose(f);
				cerr << impFile << " exists, please remove it and try again!" << endl;
				retCode = false;
			}
			if ( ! retCode )
				return retCode;
				
			retCode &= writeCodeDec(decFile);
			retCode &= writeCodeInl(inlFile);
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
// Method: writeTempl
// Author: reiners
// Date:   Thu Mar 29 01:00:00 2001
// Description:
//         
//----------------------------------------------------------------------
bool FieldContainer::writeTempl( ofstream & out, char ** templ )
{
	// file loop
	// some useful strings
	char *libname = _library;
	char *libnameUpper = strdup( _library );
	char *fcname = _name;
	char *fcnameUpper = strdup( _name );
	char *parentname = _parentFieldContainer;
	char *parentnameUpper = strdup( _parentFieldContainer );
	const char *description = _description ? _description : "";
	const char *headerPrefix = _systemComponent ? "" : "OpenSG/";
	const char *parentHeaderPrefix = 
			( _parentSystemComponent == _systemComponent ) ? "" : "OpenSG/";

	char *s;
	for (  s = libnameUpper; s && *s; *s = toupper(*s), s++ ) {}
	for (  s = fcnameUpper; s && *s; *s = toupper(*s), s++ ) {}
	for (  s = parentnameUpper; s && *s; *s = toupper(*s), s++ ) {}

	// field loop
	// useful strings
	const char	*fieldname        = NULL,
				*fieldtype        = NULL;
	char		*fieldcardinality = NULL, 
				*fielddescription = NULL;
	char 		*fieldnameCaps = NULL, 
				*fieldnameUpper = NULL;
	
	// state
	char ** flStart;
	list<Field>::iterator fieldIt;
	bool inFieldLoop = false;
	bool skipFieldLoop = false;
	int skipIf = 0;	// count of open if or else clauses
	
	bool retCode = true;

	for ( ; *templ; templ++ )
	{
		char *s = *templ;

		// just skipping to else of endif?
		if ( skipIf > 0 )
		{
			if ( strncmp( s, "@@", 2 ) )
				continue;
				
			if ( ! strncmp( s, "@@if", 4 ) )
				skipIf ++;
			else if ( ! strcmp( s, "@@endif" ) )
				skipIf --;
			else if ( ! strcmp( s, "@@else" ) )
			{
				if ( skipIf == 1) 
					skipIf = 0;
			}
			continue;
		}
		
		// if in field loop, prepare the strings
		if ( inFieldLoop && ! skipFieldLoop)
		{
			static char *cardnames[] = { "SF", "MF" };
			
			fieldname = fieldIt->name();
			fieldtype = fieldIt->typeStr();
			fieldcardinality = cardnames[ fieldIt->cardinality() ];
			fielddescription = (char*)( fieldIt->description() ? 
                                  fieldIt->description() : "" );
			
			if ( fieldnameCaps ) free( fieldnameCaps );
			fieldnameCaps = strdup( fieldname );
			fieldnameCaps[0] = toupper( fieldnameCaps[0] );
		
			if ( fieldnameUpper ) free( fieldnameUpper );
			fieldnameUpper = strdup( fieldname );
			for ( char *s = fieldnameUpper; s && *s; *s = toupper(*s), s++ ) {}
			
		}

		// is it a special line?
		if ( ! strncmp( s, "@@", 2 ) )
		{
			// specials
			// field ids/masks
			if ( ! strcmp( s, "@@FieldIdsAndMasksDecl@@" ) )
			{
				fieldIt = _fieldList.begin();
				if ( fieldIt == _fieldList.end() )
				{
					continue;
				}
				const char *name, *prevname;
				name = fieldIt->name();
				// first field: refer to parent's last field
				out << "\tstatic const osg::UInt32    " 
				    << (char)toupper( name[0] ) << name + 1 << "FieldId"
					<< "\t= Inherited::NextFieldId;" << endl;
				out << "\tstatic const osg::BitVector " 
				    << (char)toupper( name[0] ) << name + 1 << "FieldMask"
					<< "\t= Inherited::NextFieldMask;" << endl << endl;
				// loop: refer to previous field
				for ( fieldIt++; fieldIt != _fieldList.end(); fieldIt++ )
				{
					prevname = name;
					name = fieldIt->name();
					out << "\tstatic const osg::UInt32    " 
				    	<< (char)toupper( name[0] ) << name + 1 << "FieldId"
						<< "   = " << (char)toupper( prevname[0] ) 
						<< prevname + 1 << "FieldId + 1;" << endl;
					out << "\tstatic const osg::BitVector " 
				    	<< (char)toupper( name[0] ) << name + 1 << "FieldMask"
						<< " = " << (char)toupper( prevname[0] ) 
						<< prevname + 1 << "FieldMask << 1;" << endl << endl;
				}
				// Last field: prepare for use by inherited types
				out << "\tstatic const osg::UInt32\tNextFieldId   = " 
				    << (char)toupper( name[0] ) << name + 1 << "FieldId + 1;" 
					<< endl;
				out << "\tstatic const osg::BitVector\tNextFieldMask = " 
				    << (char)toupper( name[0] ) << name + 1 << "FieldMask << 1;" 
					<< endl << endl;
			}		
			// loop specials 
			else if ( ! strcmp( s, "@@BeginFieldLoop@@" ) )
			{
				inFieldLoop = true;
				flStart = templ;
				fieldIt = _fieldList.begin();
				if ( fieldIt == _fieldList.end() ) 
					skipFieldLoop = true;
			}
			else if ( ! strcmp( s, "@@EndFieldLoop@@" ) )
			{
				if ( skipFieldLoop )
				{
					inFieldLoop = false;
					skipFieldLoop = false;
					continue;					
				}
				
				fieldIt++;
				if ( fieldIt != _fieldList.end() ) 
				{
					templ = flStart;
				}
				else
				{
					inFieldLoop = false;
					skipFieldLoop = false;
				}
			}
			else if ( ! strcmp( s, "@@BeginSFFieldLoop@@" ) )
			{
				inFieldLoop = true;
				flStart = templ;
				
				for ( 	fieldIt = _fieldList.begin();
						fieldIt != _fieldList.end() && 
						fieldIt->cardinality() != 0;
						fieldIt++ ) {}
						
				if ( fieldIt == _fieldList.end() ) // No singlefields
					skipFieldLoop = true;
			}
			else if ( ! strcmp( s, "@@EndSFFieldLoop@@" ) )
			{
				if ( skipFieldLoop )
				{
					skipFieldLoop = false;
					inFieldLoop = false;
					continue;
				}
				
				for ( 	fieldIt++;
						fieldIt != _fieldList.end() && 
						fieldIt->cardinality() != 0;
						fieldIt++ ) {}
						
				if ( fieldIt != _fieldList.end() ) 
				{
					templ = flStart;
				}
				else
				{
					inFieldLoop = false;
				}
			}
			else if ( ! strcmp( s, "@@BeginMFFieldLoop@@" ) )
			{
				inFieldLoop = true;
				flStart = templ;
				
				for ( 	fieldIt = _fieldList.begin();
						fieldIt != _fieldList.end() && 
						fieldIt->cardinality() != 1;
						fieldIt++ ) {}
						
				if ( fieldIt == _fieldList.end() ) // No singlefields
					skipFieldLoop = true;
			}
			else if ( ! strcmp( s, "@@EndMFFieldLoop@@" ) )
			{
				if ( skipFieldLoop )
				{
					skipFieldLoop = false;
					inFieldLoop = false;
					continue;
				}
				
				for ( 	fieldIt++;
						fieldIt != _fieldList.end() && 
						fieldIt->cardinality() != 1;
						fieldIt++ ) {}
						
				if ( fieldIt != _fieldList.end() ) 
				{
					templ = flStart;
				}
				else
				{
					inFieldLoop = false;
				}
			}
			else if ( skipFieldLoop )	// skip if processing
				continue;
			// if else endif handling
			else if ( ! strncmp( s, "@@if", 4 ) )
			{
				static char * keys[] = {
					"Pointerfield", "SFPointerfield", "MFPointerfield",
					"Abstract", "hasFields", 
					"hasPrivateFields", "hasProtectedFields", "hasPublicFields", 
					"isPrivate", "isProtected", "isPublic",
					"hasDefaultHeader",
					NULL };
				
				char *key = s + strcspn( s, " \t");
				key += strspn( key, " \t");
				
				bool notElem = false;				
				if ( *key == '!' )
				{
					key++;
					key += strspn( key, " \t");
					notElem = true;
				}
				
				int i;
				for ( i = 0; keys[i]; i++ )
					if ( ! strcasecmp( key, keys[i] ) )
						break;
						
				skipIf = 0;
				
				switch( i )
				{
				case 0:		// Pointerfield
				 			if ( ! pointerFieldTypes() )
								skipIf = 1;
							break;
				case 1:		// SFPointerfield
						 	if ( ( pointerFieldTypes() & 1 ) == 0 )
								skipIf = 1;
							break;
				case 2:		// MFPointerfield
						 	if ( ( pointerFieldTypes() & 2 ) == 0 )
								skipIf = 1;
							break;
				case 3:		// Abstract
						 	if ( ! abstract() )
								skipIf = 1;
							break;
				case 4:		// hasFields
						 	if ( _fieldList.begin() == _fieldList.end() )
								skipIf = 1;
							break;

				case 5:		// hasPrivateFields
							{		
							list<Field>::iterator fieldIt;
		
							if ( _fieldList.begin() == _fieldList.end() )
							{
								skipIf = 1;
								break;
							}
								
							for ( 	fieldIt = _fieldList.begin();
									fieldIt != _fieldList.end() && 
									fieldIt->access() != 2;
									fieldIt++ ) {}
							if ( fieldIt == _fieldList.end() )
								skipIf = 1;
							}
							break;
				case 6:		// hasProtectedFields
							{		
							list<Field>::iterator fieldIt;
		
							if ( _fieldList.begin() == _fieldList.end() )
							{
								skipIf = 1;
								break;
							}
		
							for ( 	fieldIt = _fieldList.begin();
									fieldIt != _fieldList.end() && 
									fieldIt->access() != 1;
									fieldIt++ ) {}
							if ( fieldIt == _fieldList.end() )
								skipIf = 1;
							}
							break;
				case 7:		// hasPublicFields
							{		
							list<Field>::iterator fieldIt;
		
							if ( _fieldList.begin() == _fieldList.end() )
							{
								skipIf = 1;
								break;
							}
		
							for ( 	fieldIt = _fieldList.begin();
									fieldIt != _fieldList.end() && 
									fieldIt->access() != 0;
									fieldIt++ ) {}
							if ( fieldIt == _fieldList.end() )
								skipIf = 1;
							}
							break;
							
				case 8:		// isPrivate
							if ( fieldIt->access() != 2 )
								skipIf = 1;
							break;
				case 9:		// isProtected
							if ( fieldIt->access() != 1 )
								skipIf = 1;
							break;
				case 10:	// isPublic
							if ( fieldIt->access() != 0 )
								skipIf = 1;
							break;
				case 11:	// hasDefaultHeader
							if ( ! fieldIt->defaultHeader() || 
								  *fieldIt->defaultHeader() == 0 )
								skipIf = 1;
							break;
							
				default:
							cerr << "Unknown if clause \"" << s + 5 << "\"" 
								 << endl;
							break;
				}			
				if ( notElem )
					skipIf = 1 - skipIf;	
			}
			else if ( ! strcmp( s, "@@else" ) )
			{
				skipIf = 1;
			}
			else if ( ! strcmp( s, "@@endif" ) )
			{
				skipIf = 0;
			}
			// unknown special??
			else if ( ! strncmp( s, "@@", 2 ) ) 
			{
				cerr << "FieldContainer::writeBaseCodeImp: unknown "
					 << "command " << s << " in line "
					 << *templ << "!!" << endl;
				// retCode = false;
				// break;
			}
		}
		else if ( skipFieldLoop )	// skip text processing
			continue;
		else // verbatim text
		{
			// replace @!classname!@ etc. with the names
			static char *keys[] = { 
				"@!Classname!@", 		"@!CLASSNAME!@", 
				"@!Libname!@",  		"@!LIBNAME!@",
				"@!Parent!@", 			"@!PARENT!@",
				"@!CARDINALITY!@",		"@!Fieldtype!@",
				"@!fieldname!@", 		"@!Fieldname!@", 
				"@!FIELDNAME!@", 		"@!fieldvisibility!@",
				"@!FieldTypedDefault!@","@!FieldtypeInclude!@",
				"@!Description!@",		"@!Fielddescription!@", 
				"@!FieldSeparator!@",	"@!FieldDefaultHeader!@",
				"@!HeaderPrefix!@", 	"@!ParentHeaderPrefix!@",
				NULL };
			char *values[ sizeof(keys) / sizeof( char * ) ];
			
			values[0] = fcname;
			values[1] = fcnameUpper;
			values[2] = libname;
			values[3] = libnameUpper;
			values[4] = parentname;
			values[5] = parentnameUpper;
			values[14] = (char*)(description);
			values[18] = (char*)(headerPrefix);
			values[19] = (char*)(parentHeaderPrefix);

			if ( inFieldLoop )
			{
				char * s;

				values[6] = fieldcardinality;
				values[7] = strdup(fieldtype);
				values[8] = strdup(fieldname);
				values[9] = fieldnameCaps;
				values[10] = fieldnameUpper;
				values[11] = (char*)(fieldIt->visibility() ? "false" : "true");
				if ( fieldIt->defaultValue() )
				{
					s = new char [ strlen(fieldtype) + 
										   1 + 
										   strlen( fieldIt->defaultValue() ) +
										   1 + 1];
					strcpy( s, fieldtype );
					strcat( s, "(" );
					strcat( s, fieldIt->defaultValue() );
					strcat( s, ")" );	
					values[12] = s;		
				}
				else
				{
					s = new char [1];
					*s = 0;
					values[12] = s;	
				}
				
				// FieldtypeInclude
				if ( ! fieldIt->header() || ! strcmp( fieldIt->header(), "auto" ) )
				{
					s = new char [ strlen(fieldtype) + 20];
					if ( _systemComponent )
						strcpy( s, "OSG" );
					else
						strcpy( s, "OpenSG/OSG" );
					strcat( s, fieldtype );
					// remove the Ptr suffix
					if ( !strcmp( &s[strlen(s) - 3], "Ptr" ) )
						s[strlen(s) - 3] = 0;
					// Append 'Fields' to get the header
					strcat( s, "Fields.h" );
				}
				else
				{
					s = new char [ strlen(fieldIt->header()) + 1];
					strcpy( s, fieldIt->header() );					
				}
				values[13] = s;
				
				values[15] = fielddescription;	

				if ( fieldIt == --_fieldList.end() )
					values[16] = "";
				else
					values[16] = ",";

				if ( fieldIt->defaultHeader() && *fieldIt->defaultHeader())
					values[17] = fieldIt->defaultHeader();
				else
					values[17] = "";
			}
			else
			{
				values[6] = values[7] = values[8] = values[9] = 
				values[10] = values[11] = values[12] = values[13] = 
				values[15] = values[16] = values[17] = NULL;
			}


			char *cs = s, *ce = strchr( cs, '@' );

			while ( ce )
			{
				if ( !ce[1] || ce[1] != '!' )
				{
					ce = strchr( ce + 1, '@' );;
					continue;
				}
				
				int i;
				for ( i = 0; keys[i] ; i++ )
					if ( ! strncmp( ce, keys[i], strlen( keys[i] ) ) )
					{
						if ( ! values[i] ) 
						{
							cerr << "Replacement for " << keys[i] << " is NULL"
								 << " in line " << *templ << endl;
						}
						else
						{
							char *p;
							for ( p = cs; p < ce; p++ )
								out << *p;
							if ( strlen( values[i] ) )
								out << values[i];
						}
						ce += strlen( keys[i] );	// get behind the !@-string
						cs = ce;
						break;
					}
				
				if ( ! keys[i] )
				{
					cerr << "No replacement found for " << ce << " in line " 
						 << *templ <<  endl;
					ce++;
				}
				
				ce = strchr( ce, '@' );
			}
			
			if ( values[12] )	delete [] values[12];		
			if ( values[13] )	delete [] values[13];
			if ( values[7] )	free( values[7] );
			if ( values[8] )	free( values[8] );

			out << cs << endl;
		}
	}

		
	if ( fieldnameCaps ) free( fieldnameCaps );
	if ( fieldnameUpper ) free( fieldnameUpper );
	free( fcnameUpper );
	free( libnameUpper );
	free( parentnameUpper );
	return retCode;
}


//----------------------------------------------------------------------
// Method: writeFields
// Author: dr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
bool FieldContainer::writeCodeFields (const char *decFile)
{
	bool retCode = false;

	ofstream out;

	if (decFile)
		out.open(decFile);
 
	if (out) 
	{
		retCode = writeTempl( out, FCPtrTemplate_h );
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
bool FieldContainer::writeBaseCodeDec (const char *decFile)
{
	bool retCode = false;

	ofstream out;

	if (decFile)
		out.open(decFile);
 
	if (out) 
	{
		retCode = writeTempl( out, FCBaseTemplate_h );
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
bool FieldContainer::writeBaseCodeInl (const char *InlFile)
{
	bool retCode = false;

	ofstream out;

	if (InlFile)
		out.open(InlFile);
 
	if (out) 
	{
		retCode = writeTempl( out, FCBaseTemplate_inl );
 	}
 
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

	ofstream out;

	if (impFile)
		out.open(impFile);
 
	if (out) 
	{
		retCode = writeTempl( out, FCBaseTemplate_cpp );
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
bool FieldContainer::writeCodeDec (const char *decFile)
{
	bool retCode = false;

	ofstream out;

	if (decFile)
		out.open(decFile);
 
	if (out) 
	{
		retCode = writeTempl( out, FCTemplate_h );
 	}
 
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

	ofstream out;

	if (decFile)
		out.open(decFile);
 
	if (out) 
	{
		retCode = writeTempl( out, FCTemplate_inl );
 	}
 
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

	ofstream out;

	if (impFile)
		out.open(impFile);
 
	if (out) 
	{
		retCode = writeTempl( out, FCTemplate_cpp );
 	}
 
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
	
	
		

			

