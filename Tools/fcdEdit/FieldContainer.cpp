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

// Include the template strings
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
			sprintf(decFile,"%s%sBase.%s", filePrefix(), name(), 
											decFileSuffix());
			sprintf(inlFile,"%s%sBase.%s", filePrefix(), name(), 
											inlFileSuffix());
			sprintf(impFile,"%s%sBase.%s", filePrefix(), name(), 
											impFileSuffix());

			retCode &= writeBaseCodeDec(decFile);
			retCode &= writeBaseCodeInl(inlFile);
			retCode &= writeBaseCodeImp(decFile,impFile);

			if (retCode)
				cerr << "Write OK, Wrote base dec,inl and imp file" << endl;
			else
				cerr << "Write error: Couldn't write the dec,inl and imp file" << endl;
		}
		
		if (fc) {
			retCode = true;
			sprintf(decFile,"%s%s.%s", filePrefix(), name(), decFileSuffix());
			sprintf(inlFile,"%s%s.%s", filePrefix(), name(), inlFileSuffix());
			sprintf(impFile,"%s%s.%s", filePrefix(), name(), impFileSuffix());
			
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

	for ( char *s = libnameUpper; s && *s; *s = toupper(*s), s++ ) {}
	for ( char *s = fcnameUpper; s && *s; *s = toupper(*s), s++ ) {}
	for ( char *s = parentnameUpper; s && *s; *s = toupper(*s), s++ ) {}

	// field loop
	// useful strings
	const char	*fieldname = NULL,
				*fieldtype = NULL, *fieldcardinality = NULL;
	char 		*fieldnameCaps = NULL, *fieldnameUpper = NULL;
	
	// state
	char ** flStart;
	list<Field>::iterator fieldIt;
	bool inFieldLoop = false;
	bool skipFieldLoop = false;
	
	bool retCode = true;

	for ( ; *templ; templ++ )
	{
		char *s = *templ;

		// if in field loop, prepare the strings
		if ( inFieldLoop && ! skipFieldLoop)
		{
			static char *cardnames[] = { "SF", "MF" };
			
			fieldname = fieldIt->name();
			fieldtype = fieldIt->typeStr();
			fieldcardinality = cardnames[ fieldIt->cardinality() ];
			
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
			// Pointer Fields
			else if ( ! strcmp( s, "@@PointerFieldDecl@@" ) )
			{
				if ( pointerFieldTypes() == 0 )
					continue;
				
				out << "/** \\ingroup FieldLib " 
				    << fcname << endl;
				out << " *  \\brief " << fcname << "Ptr field traits" << endl;
				out << " */" << endl << endl;
				
				out << "template <>" << endl;
				out << "struct FieldDataTraits<" << fcname << "Ptr> : "
				    << "public Traits" << endl;
				out << "{" << endl;
				out << "	enum                         { StringConvertable "
					<< " = 0x00      };" << endl << endl;
				out << "    static char *getSName(void) { return \"SF"
					<< fcname << "Ptr\"; }" << endl;
				out << "    static char *getMName(void) { return \"MF"
					<< fcname << "Ptr\"; }" << endl;
				out << "};" << endl << endl;
				
				if ( pointerFieldTypes() & 1 )
				{
					out << "/**  \\brief SF" << fcname << "Ptr" << endl;
					out << " */" << endl << endl;
					out << "typedef SField<" << fcname << "Ptr> SF" 
						<< fcname << "Ptr;" << endl;
					out << "" << endl;
					out << "#ifndef OSG_COMPILE" << fcnameUpper << "INST" 
						<< endl;
					out << "#if defined(__sgi)" << endl << endl;
					out << "#pragma do_not_instantiate SField<" << fcname 
						<< "Ptr>::_fieldType" << endl << endl;
					out << "#else" << endl << endl;
					out << "OSG_DLLEXPORT_DECL1(SField, " << fcname 
						<< "Ptr, OSG_MISC_DLLTMPLMAPPING)" << endl << endl;
					out << "#endif" << endl;
					out << "#endif" << endl << endl;
				}
				
				if ( pointerFieldTypes() & 2 )
				{
					out << "/**  \\brief MF" << fcname << "Ptr" << endl;
					out << " */" << endl << endl;
					out << "typedef MField<" << fcname << "Ptr> MF" 
						<< fcname << "Ptr;" << endl;
					out << "" << endl;
					out << "#ifndef OSG_COMPILE" << fcnameUpper << "INST" 
						<< endl;
					out << "#if defined(__sgi)" << endl << endl;
					out << "#pragma do_not_instantiate MField<" << fcname 
						<< "Ptr>::_fieldType" << endl << endl;
					out << "#else" << endl << endl;
					out << "OSG_DLLEXPORT_DECL1(MField, " << fcname 
						<< "Ptr, OSG_MISC_DLLTMPLMAPPING)" << endl << endl;
					out << "#endif" << endl;
					out << "#endif" << endl << endl;
				}
			}			
			else if ( ! strcmp( s, "@@PointerFieldDef@@" ) )
			{
				if ( pointerFieldTypes() == 0 )
					continue;
				out << "OSG_BEGIN_NAMESPACE" << endl;
				out << "" << endl;
				out << "#if defined(__sgi)" << endl;
				out << "" << endl;
				
				if ( pointerFieldTypes() & 1 )
					out << "#pragma instantiate SField<" << fcname 
						<< "Ptr>::_fieldType" << endl;
				
				if ( pointerFieldTypes() & 2 )
					out << "#pragma instantiate MField<" << fcname 
						<< "Ptr>::_fieldType" << endl;

				out << "" << endl;
				out << "#else" << endl;
				out << "" << endl;
				
				if ( pointerFieldTypes() & 1 )
					out << "OSG_DLLEXPORT_DEF1(SField, " << fcname 
						<< "Ptr, OSG_MISC_DLLTMPLMAPPING)" << endl;
							
				if ( pointerFieldTypes() & 2 )
					out << "OSG_DLLEXPORT_DEF1(MField, " << fcname 
						<< "Ptr, OSG_MISC_DLLTMPLMAPPING)" << endl;

				out << "" << endl;
				out << "#endif" << endl;
				out << "OSG_END_NAMESPACE" << endl;
			}			
			// loop specials 
			else if ( ! strcmp( s, "@@BeginFieldLoop@@" ) )
			{
				inFieldLoop = true;
				flStart = templ;
				fieldIt = _fieldList.begin();
			}
			else if ( ! strcmp( s, "@@EndFieldLoop@@" ) )
			{
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
				"@!Classname!@", 	"@!CLASSNAME!@", 
				"@!Libname!@",  	"@!LIBNAME!@",
				"@!Parent!@", 		"@!PARENT!@",
				"@!CARDINALITY!@", 	"@!Fieldtype!@",
				"@!fieldname!@", 	"@!Fieldname!@", 
				"@!FIELDNAME!@", 	"@!fieldvisibility!@",
				"@!FieldTypedDefault!@",
				NULL };
			static int keylen[] = { 13,13, 11,11, 10,10, 
				15,13, 13,13, 13,19,  21, -1 };
			const char *values[ sizeof(keys) / sizeof( char * ) ];
			
			values[0] = fcname;
			values[1] = fcnameUpper;
			values[2] = libname;
			values[3] = libnameUpper;
			values[4] = parentname;
			values[5] = parentnameUpper;

			if ( inFieldLoop )
			{
				values[6] = fieldcardinality;
				values[7] = fieldtype;
				values[8] = fieldname;
				values[9] = fieldnameCaps;
				values[10] = fieldnameUpper;
				values[11] = fieldIt->visibility() ? "false" : "true";
				if ( fieldIt->defaultValue() )
				{
					char * s = new char [ strlen(fieldtype) + 
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
					char *s = new char [1];
					*s = 0;
					values[12] = s;	
				}
			}
			else
			{
				values[6] = values[7] = values[8] = values[9] = 
				values[10] = values[11] = values[12] = NULL;
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
					if ( ! strncmp( ce, keys[i], keylen[i] ) )
					{
						if ( ! values[i] ) 
						{
							cerr << "Replacement for " << keys[i] << " is NULL"
								 << " in line " << *templ << endl;
						}
						else
						{
							char tmp = *ce;
							*ce = 0;
							out << cs << values[i];
							*ce = tmp;
						}
						ce += keylen[i];	// get behind the !@-string
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
			
			if ( values[12] )
				delete [] values[12];

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
	
	
		

			

