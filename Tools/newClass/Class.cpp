#include <sysConfig.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "Method.h"
#include "Attribute.h"

#include "XMNewClass.h"

#include "Class.h"

char *Class::_decFileSuffix = "h";
char *Class::_impFileSuffix = "cpp";

Class::Class (XMNewClass *view,char *name)
{
	_view = view;

	_name = 0;
	setName (name);

	_parent = 0;
	_description = 0;
	_responsibility = 0;
}

Class::~Class (void)
{
	;
}

void Class::setName (char *name)
{
	delete [] _name;

	if (name) {
		_name = new char [strlen(name) + 1];
		strcpy (_name, name);
	}
	else {
		_name = 0;
	}
}

void Class::setParent (char *parent)
{
	delete [] _parent;

	if (parent) {
		_parent = new char [strlen(parent) + 1];
		strcpy (_parent, parent);
	}
	else {
		_parent = 0;
	}
}

bool Class::createParentList(void)
{
	char *beginToken, *c;
	bool inToken;
	char *token;
	unsigned size;

	_parentList.deleteAllElem();

	if (!_parent || *_parent == 0)
		return false;
	else
		c = beginToken = _parent;

	inToken = false;
	for (;true; c++) {
		if ( *c == ' ' || *c == '\t' || *c == ',' || *c == 0 ) {
			if (inToken) {
			  size = c - beginToken;
				token = new char [size + 1];
				strncpy (token, beginToken, size);
				token[size] = '\0';
				_parentList.append(token);
				inToken = false;
			}
			if (*c == 0)
				break;
		}
		else {
			if (!inToken) {
				beginToken = c;
			  inToken = true;
			}
		}
	}
	
	return true;
}

bool Class::createLineList (char *text, unsigned lineLen)
{
	char *beginLine, *endLine, *c;
	bool inToken;
	char *line;
	unsigned size;

	_lineList.deleteAllElem();

	if (!text || *text == 0)
		return false;

	c = text;
	beginLine = endLine = 0;
	inToken = false;
	for (;true; c++) {
		if ( *c == ' ' || *c == '\t' || *c == 0 ) {
			if (inToken) {
				if ((c - beginLine) > int(lineLen)) {
					if (!endLine)
						endLine = c - 1;
					size = endLine - beginLine + 1;
					line = new char [size + 1];
					strncpy (line, beginLine, size);
					line[size] = '\0';
					_lineList.append(line);
					c = endLine + 1;
					beginLine = endLine = 0;
				}
				else
					endLine = c - 1;
				inToken = false;
			}
			if (*c == 0) {
				if (beginLine && endLine && endLine > beginLine) {
					size = endLine - beginLine + 1;
					line = new char [size + 1];
					strncpy (line, beginLine, size);
					line[size] = '\0';
					_lineList.append(line);
				}
				break;
			}
		}
		else {
			if (!inToken) {
				if (!beginLine)
					beginLine = c;
				inToken = true;
			}
		}
	}
	
	return true;
}

void Class::setDescription (char *description)
{
	delete [] _description;

	if (description) {
		_description = new char [strlen(description) + 1];
		strcpy (_description, description);
	}
	else {
		_description = 0;
	}
}

void Class::setResponsibility (char *responsibility)
{
	delete [] _responsibility;

	if (responsibility) {
		_responsibility = new char [strlen(responsibility) + 1];
		strcpy (_responsibility, responsibility);
	}
	else {
		_responsibility = 0;
	}
}

void Class::write (void)
{
	cerr << "INFO: Write class dec/imp files";

	writeDec();
	writeImp();

	return;
}


void Class::writeDec(void)
{
	// Attribute *attribute;

	AccessType accessType;
	char *ws = "  ";	            
	char *wss = "    ";	            
	char decFileName[512];
	char defineName[512];
//	char *date, *user;
	char *text;
//	time_t sec;

	/*
	sec = time(0);
	date = ctime(&sec);
	user = getenv("USERNAME");
	if (!user)
		user = getenv("USER");
	*/
  
  sprintf (decFileName,"%s.%s", name(), _decFileSuffix);
	sprintf (defineName,"_%s_H_", name());

	text = defineName;
	for (;*text; text++)
		if (*text >= 'a' && *text <= 'z')
			*text = *text + 'A' - 'a';

  ofstream decStream (decFileName);


	writeBaseHead(decStream);

   decStream << "#ifndef " << defineName << endl;
	decStream << "#define " << defineName << endl;

	decStream << "#ifdef " <<  " __sgi" << endl;
	decStream << "#pragma " << " once "<< endl;
	decStream << "#endif " << endl;
	decStream << endl << endl;

   writeDecHead(decStream); 
  
	decStream << endl << endl << "class " << name();

	if (_parentList.numOfElem() != 0) {
    _parentList.begin();
    decStream << " : public " << _parentList.current();
    for (_parentList.next(); _parentList.current(); _parentList.next())
      decStream << ", " << _parentList.current();
  }
  decStream << " {" << endl << endl;
	
	for ( accessType = PUBLIC_ACCESS; 
			  accessType >= PRIVATE_ACCESS; 
			  accessType = AccessType(accessType - 1) ) 
		{
			switch (accessType) 
				{
				case PRIVATE_ACCESS:
					decStream << ws << "private:" << endl << endl;
					break;
				case PROTECTED_ACCESS:
					decStream << ws << "protected:" << endl << endl;
					break;
				case PUBLIC_ACCESS:
					decStream << ws << "public:" << endl << endl;
					break;
				default:
				case UNDEF_ACCESS:
					decStream << "//* ERROR: UNDEF_ACCESS as accessType in"
										<< " Class::write()! */" << endl;
					break;
				}
			
			decStream << wss <<"//-------------------------------------------------------" <<	endl;
			decStream << wss <<"//enums    		 " <<	endl;
			decStream << wss <<"//-------------------------------------------------------" <<	endl;
			decStream << endl << endl;
			
			decStream << wss <<"//-------------------------------------------------------" <<	endl;
			decStream << wss <<"//types " <<	endl;
			decStream << wss <<"//-------------------------------------------------------" <<	endl;
			decStream << wss << endl << endl;
			
			if (accessType == PRIVATE_ACCESS)
				if (_parentList.numOfElem() == 1)
					decStream << "\ttypedef " << _parentList.first() << " Inherited;\n";
			
			decStream << wss <<"//-------------------------------------------------------" <<	endl;
			decStream << wss <<"//friend Classes   " <<	endl;
			decStream << wss <<"//-------------------------------------------------------" <<	endl;
			decStream << endl << endl;
			
			decStream << wss <<"//-------------------------------------------------------" <<	endl;
			decStream << wss <<"//friend functions " <<	endl;
			decStream << wss <<"//-------------------------------------------------------" <<	endl;
			decStream << endl << endl;
			
			decStream << wss <<"//-------------------------------------------------------" <<	endl;
			decStream << wss <<"//class Variables " <<	endl;
			decStream << wss <<"//-------------------------------------------------------" <<	endl;
			decStream << wss << endl << endl;
			
			writeAttribList(decStream, accessType, STATIC_MODEL);
			
			decStream << wss <<"//-------------------------------------------------------" <<	endl;
			decStream << wss <<"//class functions" <<	endl;
			decStream << wss <<"//-------------------------------------------------------" <<	endl;
			decStream << endl << endl;
			
			writeMethodList(decStream,accessType, STATIC_MODEL);
			
			decStream << wss <<"//-------------------------------------------------------" <<	endl;
			decStream << wss <<"//instance Variables  " <<	endl;
			decStream << wss <<"//-------------------------------------------------------" <<	endl;
			decStream << endl << endl;
			
			writeAttribList(decStream, accessType, DEFAULT_MODEL);
			
			decStream << wss <<"//-------------------------------------------------------" <<	endl;
			decStream << wss <<"//instance functions   " <<	endl;
			decStream << wss <<"//-------------------------------------------------------" <<	endl;
			decStream << endl << endl;
			
			writeMethodList(decStream,accessType, DEFAULT_MODEL);
			writeMethodList(decStream,accessType, VIRTUAL_MODEL); 
			
		}				
	
	decStream << "};" << endl << endl; //hier end the class declaration
	
	decStream << "typedef " << name() << "* " << name() << "P;" << endl << endl;
	
	decStream << "OSG_END_NAMESPACE" << endl << endl;
	
  decStream << "#endif // " << defineName << endl;
	
	decStream.close();
}

//=============================== =============================== 
void Class::writeImp (void)
{
	Attribute* attribute;
	Method* method;
	char decFileName[512];
	char impFileName[512];
	char attribInit[2048];
	AccessType accessType;

	sprintf (decFileName, "%s.%s", name(), _decFileSuffix);
	sprintf (impFileName, "%s.%s", name(), _impFileSuffix);

	ofstream impStream (impFileName);
  
  writeBaseHead(impStream);

  impStream <<"//---------------------------------------------------------" <<	endl;
	impStream <<"// 	Includes  " <<	endl;
  impStream <<"//---------------------------------------------------------" <<	endl;
	impStream << endl << endl;
	impStream << "#include <stdlib.h>" << endl;
	impStream << "#include <stdio.h>" << endl << endl;

	impStream << "#include \"OSGConfig.h\"" << endl << endl;

	impStream << "#ifdef OSG_STREAM_IN_STD_NAMESPACE" << endl;
	impStream << "#include <iostream>" << endl;
	impStream << "#else" << endl;
	impStream << "#include <iostream.h>" << endl;
	impStream << "#endif" << endl;
	impStream << endl << endl;

	if (_parentList.numOfElem()) 
	{
		for (_parentList.begin(); _parentList.current(); _parentList.next()) 
				impStream << "#include <" << _parentList.current() << ">" << endl;
								
    	impStream << endl << endl;
	}


	impStream << "#include \"" << decFileName << "\"" << endl;
	impStream << endl << endl;



   impStream <<"/**\\enum OSGVecBase::VectorSizeE" <<	endl;
	impStream <<" * \\brief " <<	endl;
	impStream <<"*/" << endl;
	impStream << endl << endl;

  impStream <<"/**\\var OSGVecBase::VectorSizeE OSGVecBase::_iSize" <<	endl;
	impStream <<" *" <<	endl;
	impStream <<"*/" << endl;
	impStream << endl << endl;

  impStream <<"/**\\const char *OSGVecBase::getClassName(void)" <<	endl;
	impStream <<" *\\brief Classname" <<	endl;
	impStream <<"*/" << endl;
	impStream << endl << endl;

  impStream <<"/**\\var OSGValueTypeT OSGVecBase:: _value[Size];" <<	endl;
	impStream <<" *\\brief value store" <<	endl;
	impStream <<"*/" << endl;
	impStream << endl << endl;
	
	impStream <<"/********************************************************" <<	endl;
	impStream <<" *   Types" <<	endl;
	impStream <<"\\********************************************************/" <<	endl;
	impStream << endl << endl;

	impStream <<"/********************************************************" <<	endl;
	impStream <<" *	  Classvariables" <<	endl;
	impStream <<"\\********************************************************/" <<	endl;
	impStream << endl << endl;

   createLineList (attribInit, 70);
	attribInit[0] = 0;
	for ( accessType = UNDEF_ACCESS; 
			  accessType >= PRIVATE_ACCESS; 
			  accessType = AccessType(accessType - 1)
			) 
  {
		for ( _attributeList.begin();
					_attributeList.current();
					_attributeList.next()
					) 
     {
			attribute = _attributeList.current();
			if ( attribute->accessType() == accessType)
				if (attribute->memoryModel() == STATIC_MODEL) 
         {
					impStream << attribute->type() << " " 
										<< name() << "::" << attribute->name()
										<< " = " << attribute->initialValue()
										<< endl;
				 }
				 else {
					if (*attribInit == 0) {
						if (attribute->underscorePrefix()) {
							strcpy (attribInit, "_");
							strcat (attribInit, attribute->name());
						}
						else
							strcpy ( attribInit, attribute->name());
					}
					else {
						if (attribute->underscorePrefix()) 
							strcat ( attribInit, ", _");
						else
							strcat ( attribInit, ", ");
						strcat ( attribInit, (attribute->name()));
					}
					strcat (attribInit, "(");
					strcat (attribInit, rmWS(attribute->initialValue()));
					strcat (attribInit, ")");
				}
		}
	
  } 
  
  impStream << endl << endl;

	impStream <<"/********************************************************" <<	endl;
	impStream <<" *	  Class methodes" <<	endl;
  	impStream <<"\\********************************************************/" <<	endl;
	impStream << endl << endl;
  
  	 impStream <<"/********************************************************" <<	endl;
    impStream <<"*instance methodes " <<	endl;
    impStream <<"\\*********************************************************/" <<	endl;
    impStream << endl << endl;
    	    	    	
	int enterd_private   = 0;	
	int enterd_public    = 0;	
	int enterd_protected = 0;	

  
  for ( accessType = PUBLIC_ACCESS; 
				accessType >= PRIVATE_ACCESS; 
				accessType = AccessType(accessType - 1)
			) 
    {

			if (accessType == PUBLIC_ACCESS && !enterd_public)
			{
				impStream <<"/********************************************************" <<	endl;
      	impStream <<"*public" <<	endl;
				impStream <<"\\********************************************************/" <<	endl;
      	impStream << endl << endl;

				enterd_public++;	
  				 
			}
			if (accessType == PROTECTED_ACCESS && !enterd_protected)
			{
				impStream <<"/********************************************************" <<	endl;
      	   impStream <<"*protected" <<	endl;
            impStream <<"\\*********************************************************/" <<	endl;           	    	  	
            impStream << endl << endl;

				enterd_protected++;	
  				 
			}
			if (accessType == PRIVATE_ACCESS && !enterd_private)
			{
            impStream <<"/*********************************************************" <<	endl;
      	   impStream <<"*private	" <<	endl;
				impStream <<"\\**********************************************************/" <<	endl;
      	   impStream << endl << endl;

				enterd_private++;	
  				 
			}

		   for ( _methodList.begin(); _methodList.current(); _methodList.next()) 
         {
				method = _methodList.current();


				if ( method->accessType() == accessType &&
				     method->implementType() == IMPFILE_IMP &&
					  !( method->methodType() == CONSTRUCTOR_METHOD ||
					     method->methodType() == DESTRUCTOR_METHOD  
					   ) 
				   ) 
            {
  	    						   		  			     
				   impStream <<"//--------------------------------------------------------" <<	endl;
    		      impStream <<"// Function name: " <<method->name()  <<	endl;
			      impStream <<"//--------------------------------------------------------" <<	endl;
    				impStream <<"//" << endl;
			  	   impStream <<"//Parameters:" << endl;
					impStream <<"//p: " <<(method->param() ? method->param() : "void")<< endl;
			  	   impStream <<"//GlobalVars:" << endl;
					impStream <<"//g: " << endl;
			  	   impStream <<"//Returns:" << endl;
					impStream <<"//r:" <<(method->type() ? method->type() : "void") << endl;
			  	   impStream <<"// Caution" << endl;
					impStream <<"//c: " << endl;
			  	   impStream <<"//Assumations:" << endl;
					impStream <<"//a: " << endl;
					impStream <<"//Describtions:" << endl;
  				   impStream <<"//d: " << method->description() << endl;
					impStream <<"//SeeAlso:" << endl;
					impStream <<"//s:" << endl;
					impStream <<"//" << endl;
			      impStream <<"//--------------------------------------------------------" <<	endl;

				   impStream << (method->type() ? method->type() : "void")
									<< " " << name() << "::" << method->name() << " (" 
									<< (method->param() ? method->param() : "void")
									<< " )" << endl;
				   impStream << "{" << endl
									<< "\treturn;" << endl
									<< "}" << endl
									<< endl;

		  }
		 } 
	  } 
   

  	 impStream <<"/*********************************************************" <<	endl;
    impStream <<"*public" <<	endl;
    impStream <<"\\**********************************************************/" <<	endl;
    impStream << endl << endl;

    impStream <<"/**constructors & destructors**/" <<	endl;
    impStream << endl << endl;

  	 for ( _methodList.begin(); _methodList.current(); _methodList.next()) 
     {
				method = _methodList.current();
	    if ( method->implementType() == IMPFILE_IMP &&
					 ( method->methodType()  == CONSTRUCTOR_METHOD ||
					   method->methodType()  == DESTRUCTOR_METHOD  
	   			 ) 
				 ) 
			 {


 			   	impStream <<"//--------------------------------------------------------" <<	endl;
			      impStream <<"// Function name: " <<method->name()  <<	endl;
			      impStream <<"//--------------------------------------------------------" <<	endl;
					impStream <<"//" << endl;
			  	   impStream <<"//Parameters:" << endl;
					impStream <<"//p: " <<(method->param() ? method->param() : "void")<< endl;
			  	   impStream <<"//GlobalVars:" << endl;
					impStream <<"//g: " << endl;
			  	   impStream <<"//Returns:" << endl;
					impStream <<"//r:" <<(method->type() ? method->type() : "void") << endl;
			  	   impStream <<"// Caution" << endl;
					impStream <<"//c: " << endl;
			  	   impStream <<"//Assumations:" << endl;
					impStream <<"//a: " << endl;
					impStream <<"//Describtions:" << endl;
  				   impStream <<"//d: " << method->description() << endl;
					impStream <<"//SeeAlso:" << endl;
					impStream <<"//s:" << endl;
					impStream <<"//" << endl;
			      impStream <<"//---------------------------------------------------------" <<	endl;
    	    	    	    	    	
				  impStream << name() << "::" << method->name() << " (" 
									<< (method->param() ? method->param() : "void") 
									<< " )" << endl;
				  if (method->methodType() == CONSTRUCTOR_METHOD)
					for (_lineList.begin(); _lineList.current(); _lineList.next()) 
						impStream << ": " << _lineList.current() << endl;
				  impStream << "{" << endl
									<< "\treturn;" << endl
									<< "}" << endl
									<< endl;			
			}

		 }
    	    	     
   impStream <<"/*----------------------access----------------------------*/"
	 	    	  << endl << endl;
   impStream <<"/*----------------------properies-------------------------*/"
	 	    	 << endl << endl;
   impStream <<"/*----------------------your Category---------------------*/" 
	 	    	 << endl << endl;
   impStream <<"/*----------------------Operators-------------------------*/" 
						 << endl << endl;
	 
	 impStream << endl << endl;
	 
	 impStream <<"/**********************************************************/" <<	endl;
   impStream <<"*protected	" <<	endl;
	 impStream <<"\\**********************************************************/" <<	endl;
   impStream << endl << endl;
	 
	 impStream <<"/*********************************************************" <<	endl;
   impStream <<"*private" <<	endl;
   impStream <<"\\***********************************************************/" <<	endl;
   impStream << endl << endl;
	 
	 
	 impStream.close();

}

Method *Class::method (unsigned id)
{
	for (_methodList.begin(); _methodList.current(); _methodList.next())
		if (_methodList.current()->listId() == id)
			return _methodList.current();

	return 0;
}

void Class::addMethod (Method *method)
{
	if (!_methodList.find(method)) {
		_methodList.append(method);
		method->setClass(this);
		refreshView();
	}
}

void Class::removeMethod (Method *method)
{
	if (_methodList.find(method)) {
		_methodList.exclude();
		method->setClass(0);
		refreshView();
	}
}

bool Class::isMethod (Method *method)
{
	for (_methodList.begin(); _methodList.current(); _methodList.next())
		if (_methodList.current() == method)
			return true;

	return false;
}

Attribute *Class::attribute (unsigned id)
{
	for (_attributeList.begin(); _attributeList.current(); _attributeList.next())
		if (_attributeList.current()->listId() == id)
			return _attributeList.current();

	return 0;
}

void Class::addAttribute (Attribute *attribute)
{
	if (!_attributeList.find(attribute)) {
		_attributeList.append(attribute);
		attribute->setClass(this);
		refreshView();
	}
}

void Class::removeAttribute (Attribute *attribute)
{
	if (_attributeList.find(attribute)) {
		_attributeList.exclude();
		attribute->setClass(0);
		refreshView();
	}
}

bool Class::isAttribute (Attribute *attribute)
{
	for (_attributeList.begin(); _attributeList.current(); _attributeList.next())
		if (_attributeList.current() == attribute)
			return true;

	return false;
}

void Class::refreshView (void)
{
	_view->refresh();
}

char *Class::rmWS (char *str)
{
	static char *emptyStr = "";
	char *begin;
	char *end;

	if (!str || *str == 0) {
		return emptyStr;
	}

	end = str + strlen(str);

	for (begin = str; *begin == ' ' || *begin == '\t'; begin++) {
		if (begin == end)
			return emptyStr;
	}

	for ( end = str + strlen(str) - 1; 
				*end == ' ' || *end == '\t';
				end--
			) {
		if (begin == end)
			return emptyStr;
	}
	end[1] = 0;

	return begin;
}

void Class::writeBaseHead (ofstream & ostream)
{
   char *ws = "                                                                           ";
	  	    	    	    	   
  ostream << "/*---------------------------------------------------------------------------*\\" << endl;     
  ostream << " *                                OpenSG                                     *" << endl; 
  ostream << " *" << ws << "*" << endl;      
  ostream << " *     	  Copyright 2000 by OpenSG Forum ( http://www.opensg.org )           *" << endl;  
  ostream << " *" << ws << "*" << endl;      
  ostream << " *        contact: {reiners|vossg}@igd.fhg.de,                               *" << endl;      
  ostream << " *                 jbehr@zgdv.de                                             *" << endl;      
  ostream << " *" << ws << "*" << endl;      
  ostream << "\\*---------------------------------------------------------------------------*/" << endl;
  ostream << "/*---------------------------------------------------------------------------*\\" << endl;  
  ostream << " *                                License                                    *" << endl;
  ostream << " *                                                                           *" << endl;
  ostream << " * This library is free software; you can redistribute it and/or modify it   *" << endl;
  ostream << " * under the terms of the GNU Library General Public License as published    *" << endl;
  ostream << " * by the Free Software Foundation, version 2.                               *" << endl;
  ostream << " *                                                                           *" << endl;
  ostream << " * This library is distributed in the hope that it will be useful, but       *" << endl;
  ostream << " * WITHOUT ANY WARRANTY; without even the implied warranty of                *" << endl;
  ostream << " * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *" << endl;
  ostream << " * Library General Public License for more details.                          *" << endl;
  ostream << " *                                                                           *" << endl;
  ostream << " * You should have received a copy of the GNU Library General Public         *" << endl;
  ostream << " * License along with this library; if not, write to the Free Software       *" << endl;
  ostream << " * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *" << endl;
  ostream << " *                                                                           *" << endl;
  ostream << "\\*---------------------------------------------------------------------------*/" << endl;  	
  ostream << "/*---------------------------------------------------------------------------*\\" << endl;  
  ostream << " *                                 Changes                                   *" << endl; 
  ostream << " *" << ws << "*" << endl;      
  ostream << " *" << ws << "*" << endl;      
  ostream << " *" << ws << "*" << endl;      
  ostream << " *" << ws << "*" << endl;      
  ostream << " *" << ws << "*" << endl;      
  ostream << " *" << ws << "*" << endl;      
  ostream << "\\*---------------------------------------------------------------------------*/" << endl;  	    ostream << endl << endl;

}
//=============================== =============================== 

void Class::writeDecHead(ofstream &ostream)
{

	ostream <<"//-------------------------------------------------------" <<	endl;
	ostream <<"//Includes"<< endl;
	ostream <<"//-------------------------------------------------------" <<	endl;
	ostream << endl << endl;

	ostream << "#include" <<  "<OSGBaseType.h>" << endl;
	ostream << endl << "OSG_BEGIN_NAMESPACE"<< endl;
	ostream << endl << endl;

	if (_parentList.numOfElem()) {
		for (_parentList.begin(); _parentList.current(); _parentList.next()) 
			ostream << "#include <" << _parentList.current() << ">" << endl;
		ostream << endl << endl << endl;
	}

	ostream <<"//-------------------------------------------------------" <<	endl;
	ostream <<"//Forward References	 "<< endl;
	ostream <<"//-------------------------------------------------------" <<	endl;
	ostream << endl << endl;

	ostream <<"//-------------------------------------------------------" <<	endl;
	ostream <<"//Types		 "<< endl;
	ostream <<"//-------------------------------------------------------" <<	endl;
	ostream << endl << endl;
   
	
	ostream <<"//-------------------------------------------------------" <<	endl;
	ostream <<"//Class 	   "<< endl;
   ostream <<"//-------------------------------------------------------" <<	endl;
	ostream << endl << endl;


  ostream << "/*!\\ingroup baselib "<< endl;
  ostream << " * \\brief Brief "<< endl;
  ostream << " * "<< endl;  
  ostream << " * detailed "<< endl;
  ostream << " */ "<< endl;

}

//=============================== =============================== 

void Class::writeAttribList ( ofstream &ostream, 
															AccessType accessType, 
															MemoryModel memModel )
{
	Attribute *attribute;
	char *wss = "    ";
	
	for ( _attributeList.begin();
				_attributeList.current();
				_attributeList.next()
				) 
		{
			
     attribute = _attributeList.current();
     if ( (attribute->accessType() == accessType) &&
					(attribute->memoryModel() == memModel) )
  	 {
		  ostream << wss << "/** " 
	 		 	<<  attribute->description() 
		    	<< " */" << endl;
		  ostream << wss 
					<< ((attribute->memoryModel() ==	STATIC_MODEL) ? "static " : "") 
					<< attribute->type() << " " 
					<< (attribute->underscorePrefix() ? "_" : "")
					<< attribute->name() << ";"
				<< endl << endl;
	  }
	}

}	 				

//=============================== =============================== 

void Class::writeMethodList(ofstream &ostream, 
														AccessType accessType, MemoryModel memModel)
{
	Method    *method;
	Attribute *attribute;
	char *wss = "    ",*param, *type;
	
	for ( _methodList.begin(); _methodList.current(); _methodList.next()) {
		method = _methodList.current();
		if ( (method->accessType() == accessType) &&
				 (method->memoryModel() == memModel) )
			{

				ostream << wss << "/** " 
								<< method->description() 
								<< " */" << endl;
				ostream << wss;	
				
				switch (method->memoryModel()) 
					{
					case STATIC_MODEL:
						ostream << "static ";
						break;
					case VIRTUAL_MODEL:
						ostream << "virtual ";
						break;
					default:
						break;
					}
				
				type = method->type();
				param = const_cast<char *> (method->param() ?method->param() : "void");												
				
				if (!type || *type == 0)
					ostream << method->name();
				else
					ostream << type << " " << method->name();
				
				ostream << " (" << param << ")";		
				
				switch (method->implementType()) 
				  {
					case ABSTRACT_IMP:
						ostream << " = 0;";
						break;
					case INLINE_IMP:
						attribute = method->dependence();
						
						switch (method->methodType()) 
							{
							case SET_METHOD:
								if (attribute->underscorePrefix())
									ostream << endl << wss 
													<< " { _" << attribute->name() 
													<< " = " << attribute->name() << "; }" 
													<< endl;
								else
									ostream << endl << wss 
													<< " { " << attribute->name()
													<< " = " << attribute->name() << "New; }"
													<< endl;
								break;
							case GET_METHOD:
								ostream << endl << wss
												<< " { return "
												<<(attribute->underscorePrefix() ?	"_" : "")
												<< attribute->name() << "; }"
												<< endl;
								break;
							case CONSTRUCTOR_METHOD:
							case DESTRUCTOR_METHOD:
							default:
								ostream << " {;}";
								break;
							}
							break;
					default:
					case IMPFILE_IMP:
						ostream << ";";
						break;
						
					}// end switch()		
				ostream << endl << endl;
			}//end if 
	}// end for	
	
}








