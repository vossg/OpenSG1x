#include <sysConfig.h>
#include <iostream>
#include <stdio.h>

#include <Xm/Form.h>
#include <Xm/TextF.h>
#include <Xm/RowColumn.h>
#include <Xm/List.h>

#include "XMNewClass.h"
#include "XMApp.h"
#include "XMHelp.h"

#include "Class.h"
#include "Attribute.h"
#include "Method.h"

XMNewClass::XMNewClass (Widget parent, char *className)
	: XMBase ("XMNewClass")
{
	_class = new Class (this, 0);
	
	createWidgetTree(parent, className);
}

XMNewClass::~XMNewClass (void)
{
	;
}

bool XMNewClass::createWidgetTree (Widget parent, char *className) 
{
	Widget form, desk, sep, buttonBar, listBox, textRowColumn;
	Widget attributeButtonBox, methodButtonBox;
	Widget scrolledWindow;

	if (!parent) { 
		cout << "ERROR: Need parent Widget in XMNewClass::createWidgetTree()!\n";
		return false;
	}
 
  form = XtVaCreateManagedWidget ( "form", xmFormWidgetClass, parent, 0 );
	setTopWidget(form);

	buttonBar = createHorRowColumn ( "buttonBar", form);
	setAttachment (buttonBar, 0, form, form, form);

	sep = createHorSeparator ( "sep", form );
	setAttachment (sep, 0, buttonBar, form, form);

	desk = XtVaCreateManagedWidget ( "desk", xmFormWidgetClass, form, 0 );
	setAttachment (desk, form, sep, form, form);

	_ok = createPushButton ("Ok", buttonBar, okCB);
	new XMHelp (_ok, "Write the class Dec/Imp files");

	_cancel = createPushButton ("Cancel", buttonBar, cancelCB);
	new XMHelp (_cancel, "Cancel the process");

	//- desk ---------------------------------------------

	textRowColumn = XtVaCreateManagedWidget ( "textRowColumn",
																						xmRowColumnWidgetClass, desk,
																					  XmNorientation, XmVERTICAL,
																						XmNpacking, XmPACK_COLUMN,
																						XmNnumColumns, 2,
																						0
																					);
	setAttachment (textRowColumn, desk, 0, desk, desk );

	_classNameLabel = createLabel ("classNameLabel", textRowColumn);
	setLabel (_classNameLabel, "Class name");
	new XMHelp (_classNameLabel, "Defines the class name");

	_parentNameLabel = createLabel ("parentNameLabel", textRowColumn);
	setLabel (_parentNameLabel, "include file(s)");
	new XMHelp (_parentNameLabel, "Define the include files");

	_publicClassNameLabel = createLabel ("publicClassNameLabel", textRowColumn);
	setLabel (_publicClassNameLabel, "pub. Class(es)");
	new XMHelp (_publicClassNameLabel, "Define the public classes");


	_descriptionLabel = createLabel ( "descriptionLabel", textRowColumn );
	setLabel (_descriptionLabel, "Description");
	new XMHelp (_descriptionLabel, "write describtion");

	_responsibilityLabel = createLabel ( "responsibilityLabel", textRowColumn );
	setLabel ( _responsibilityLabel, "Responsibility" );
	new XMHelp (_responsibilityLabel, "write responsiblity");

	_classNameInput = XtVaCreateManagedWidget  ( "classNameInput", 
																							 xmTextFieldWidgetClass, 
																							 textRowColumn,
																							 0
																						 );


	_parentNameInput = XtVaCreateManagedWidget ( "parentNameInput",
																							 xmTextFieldWidgetClass,
																							 textRowColumn,
																							 0
																						 );

	_publicClassName = XtVaCreateManagedWidget  ( "publicClassName", 
																							 xmTextFieldWidgetClass, 
																							 textRowColumn,
																							 0
																						 );

	_descriptionInput = XtVaCreateManagedWidget  ( "descriptionInput",
																								 xmTextFieldWidgetClass, 
																								 textRowColumn,
																								 0
																							 );

	_responsibilityInput = XtVaCreateManagedWidget  ( "responsibilityInput",
																								 xmTextFieldWidgetClass, 
																								 textRowColumn,
																								 0
																							 );

	//- list -----------------------------------------------------------------
	sep = createHorSeparator ("sep1", desk);
	setAttachment (sep, textRowColumn, 0, desk, desk);

	listBox = XtVaCreateManagedWidget ( "listBox", xmFormWidgetClass, desk, 
																			XmNfractionBase, 10000,
																			0
																		);
	setAttachment (listBox, sep, desk, desk, desk);

	/// attribute secton
	attributeButtonBox = createHorRowColumn ( "attributeButtonBox", listBox);
	XtVaSetValues ( attributeButtonBox,
									XmNbottomAttachment, XmATTACH_FORM,
									XmNleftAttachment, XmATTACH_FORM,
									XmNrightAttachment, XmATTACH_POSITION,
									XmNrightPosition, 5000,
									0
								);

	_attributeListInput = XmCreateScrolledList( listBox, "attributeListInput",
																							0,0
																							);
	XtAddCallback ( _attributeListInput, XmNdefaultActionCallback,
									editAttributeCB, this
								);

	scrolledWindow = XtParent (_attributeListInput);

	XtVaSetValues ( scrolledWindow, 
									XmNtopAttachment, XmATTACH_FORM,
									XmNbottomAttachment, XmATTACH_WIDGET,
									XmNbottomWidget, attributeButtonBox,
									XmNleftAttachment, XmATTACH_FORM,

									XmNrightAttachment, XmATTACH_POSITION,
									XmNrightPosition, 5000,
							
						      0
								);
	XtManageChild ( _attributeListInput );

	/// method section
  methodButtonBox = createHorRowColumn ( "methodButtonBox", listBox);
	XtVaSetValues ( methodButtonBox,
									XmNbottomAttachment, XmATTACH_FORM,
									XmNleftAttachment, XmATTACH_POSITION,
									XmNleftPosition, 5000,
									XmNrightAttachment, XmATTACH_FORM,
									0
								);

 
	_methodListInput = XmCreateScrolledList( listBox, "methodListInput",
																					 0, 0
																				 );
	XtAddCallback ( _methodListInput, XmNdefaultActionCallback,
									editMethodCB, this
								);

	scrolledWindow = XtParent (_methodListInput);
	XtVaSetValues ( scrolledWindow,
									XmNtopAttachment, XmATTACH_FORM,
									XmNbottomAttachment, XmATTACH_WIDGET,
									XmNbottomWidget, methodButtonBox,
									XmNleftAttachment, XmATTACH_POSITION,
									XmNleftPosition, 5000,
									XmNrightAttachment, XmATTACH_FORM,
									0
								);
	XtManageChild ( _methodListInput );

	// attribute button section
	_attributeLabel = createLabel ("attributeLabel", attributeButtonBox);
	setLabel (_attributeLabel, "Attribute");
	
 	_newAttribute = createPushButton ("New", attributeButtonBox, newAttributeCB);
	new XMHelp (_newAttribute, "Create a new Attribute");

	_editAttribute = createPushButton ("Edit", 
																		 attributeButtonBox, editAttributeCB
																		);
	new XMHelp (_editAttribute, "Edit the selected Attribute");

	_cloneAttribute = createPushButton ( "Clone", 
																			 attributeButtonBox, cloneAttributeCB
																		 );
	new XMHelp ( _cloneAttribute, "Clone the selected Attribute");

	_deleteAttribute = createPushButton ("Delete", 
																			 attributeButtonBox, deleteAttributeCB
																			);
	new XMHelp (_deleteAttribute, "Delete the selected Attribute");


	// method button secton
	_methodLabel = createLabel ("methodLabel", methodButtonBox);
	setLabel ( _methodLabel, "Method" );

 	_newMethod = createPushButton ("New", methodButtonBox, newMethodCB);
	new XMHelp (_newMethod, "Create a new Method");

	_editMethod = createPushButton ("Edit", methodButtonBox, editMethodCB);
	new XMHelp ( _editMethod, "Edit the selected Method");

	_cloneMethod = createPushButton ("Clone", methodButtonBox, cloneMethodCB);
	new XMHelp ( _cloneMethod, "Clone the selected Method");

	_deleteMethod = createPushButton ("Delete", methodButtonBox, deleteMethodCB);
	new XMHelp (_deleteMethod, "Delete the selected Method");

	// class name set callback
	if (className) {
		XtVaSetValues (_classNameInput, XmNvalue, className, 0);
		setClassName();   
	}

  XtAddCallback ( _classNameInput, XmNactivateCallback, 
									setClassNameCB, this
								);
  XtAddCallback ( _classNameInput, XmNlosingFocusCallback, 
									setClassNameCB, this
								);     
	
  //----------------------------------------------------

	return true;
}

void XMNewClass::newAttribute (Widget, XtPointer)
{
	Attribute *attribute = new Attribute (_class);

	attribute->popupAttribView ();
}

void XMNewClass::deleteAttribute (Widget, XtPointer)
{
	int i, n = _class->numOfAttributes();

	cout << "Delete Attribute" << endl;

	if (n)
		for (i = 1; i <= n; i++)
			if (XmListPosSelected(_attributeListInput, i)) {
				delete _class->attribute(i);
			}
	return;
}

void XMNewClass::editAttribute (Widget, XtPointer)
{
	int i, n = _class->numOfAttributes();

	cout << "Edit Attribute" << endl;

	if (n)
		for (i = 1; i <= n; i++)
			if (XmListPosSelected(_attributeListInput, i)) {
				_class->attribute(i)->popupAttribView();
			}
	return;
}

void XMNewClass::cloneAttribute (Widget, XtPointer)
{
	Attribute *attribute;
	int i, n = _class->numOfAttributes();
		
	cout << "Clone Attribute" << endl;

	if (n)
		for (i = 1; i <= n; i++)
			if (XmListPosSelected(_attributeListInput, i)) {
				attribute = _class->attribute(i);
			  attribute = new Attribute(*attribute);
				attribute->popupAttribView();
			}
	return;
}
			

void XMNewClass::newMethod (Widget, XtPointer)
{
	Method *method = new Method (_class);

	method->popupAttribView();
}

void XMNewClass::deleteMethod (Widget, XtPointer)
{
 	int i, n = _class->numOfMethods();

	cout << "Delete Method" << endl;

	if (n)
		for (i = 1; i <= n; i++)
			if (XmListPosSelected(_methodListInput, i)) {
				delete _class->method(i);
			}
	return;
}

void XMNewClass::editMethod (Widget, XtPointer)
{
 	int i, n = _class->numOfMethods();

	cout << "Edit Method" << endl;

	if (n)
		for (i = 1; i <= n; i++)
			if (XmListPosSelected(_methodListInput, i)) {
				_class->method(i)->popupAttribView();
			}
	return;
}

void XMNewClass::cloneMethod (Widget, XtPointer)
{
	Method *method;

	int i, n = _class->numOfMethods();
		
	cout << "Clone Method" << endl;

	if (n)
		for (i = 1; i <= n; i++)
			if (XmListPosSelected(_methodListInput, i)) {
				method = _class->method(i);
				method = new Method (*method);
				method->popupAttribView();
			}
	return;
}
			
void XMNewClass::ok (Widget, XtPointer)
{
	_class->setName(getText(_classNameInput));
	_class->setPublicClass(getText(_publicClassName));
	_class->setParent(getText(_parentNameInput));
	_class->setDescription(getText(_descriptionInput));
	_class->setResponsibility(getText(_responsibilityInput));

	_class->write();
	XMApp::current()->end();
}

void XMNewClass::cancel (Widget, XtPointer)
{
	XMApp::current()->end();
}

void XMNewClass::setClassName (Widget, XtPointer)
{
	char tmpBuffer[256];
	List<Method> *methodList = _class->methodList();
	Method *method;
	char *valueStr;

	XtVaGetValues ( _classNameInput, XmNvalue, &valueStr, 0 );

	if (valueStr == 0 || *valueStr == 0)
		return;

	_class->setName(valueStr);
	 sprintf (tmpBuffer, "const %s &obj", _class->name());

	for (methodList->begin(); methodList->current(); methodList->next())
		if (methodList->current()->methodType() == CONSTRUCTOR_METHOD)
			break;

	if (methodList->current() == 0) {
		method = new Method (_class);
		method->setMethodType(CONSTRUCTOR_METHOD);
		method->setMemoryModel (DEFAULT_MODEL);
		method->setDescription ("Default Constructor");
		method->touchModelValues();

		method = new Method (_class);
		method->setMethodType(CONSTRUCTOR_METHOD);
		method->setMemoryModel (DEFAULT_MODEL);
		method->setParam(tmpBuffer);
		method->setDescription ("Copy Constructor");
		method->touchModelValues();
	}


	for (methodList->begin(); methodList->current(); methodList->next())
		if (methodList->current()->methodType() == DESTRUCTOR_METHOD)
			break;
	
	if (methodList->current() == 0) {
		method = new Method (_class);
		method->setMethodType(DESTRUCTOR_METHOD);
		method->setMemoryModel (VIRTUAL_MODEL);
		method->setDescription ("Destructor");
		method->touchModelValues();
	}
	
	for (methodList->begin(); methodList->current(); methodList->next())
		if (methodList->current()->methodType() == OPERATOR_METHOD)
			break;
	
	
	if (methodList->current() == 0)
	{
		method = new Method (_class);
		method->setMethodType(OPERATOR_METHOD);
		method->setMemoryModel (DEFAULT_MODEL);
		method->setDescription ("Equal operator");
		method->setName("operator ==") ; 
    	method->setType("bool") ; 
    	method->setParam(tmpBuffer);  
		method->touchModelValues();
	}

	if (methodList->current() == 0) {
		method = new Method (_class);
		method->setMethodType(OPERATOR_METHOD);
		method->setMemoryModel (DEFAULT_MODEL);
		method->setDescription ("assignment operator");
		method->setName("operator =") ; 
    	method->setType("bool") ; 
    	method->setParam(tmpBuffer);  
		method->touchModelValues();
	}

	if (methodList->current() == 0) {
		method = new Method (_class);
		method->setMethodType(OPERATOR_METHOD);
		method->setMemoryModel (DEFAULT_MODEL);
		method->setDescription ("lower or equal operator");
    	method->setName("operator <") ; 
    	method->setType("bool") ; 
    	method->setParam(tmpBuffer);  
    	method->touchModelValues();
	}

	refreshMethodList();
 
	cout << "ClassName: " << valueStr << endl;
}

void XMNewClass::refreshAttributeList(void)
{
	char buffer[128], *accessStr;
	List<Attribute> *attributeList;
	Attribute *attribute;
	int n, numOfElem;
	char *name, *description;

	cout << "INFO: Refresh Attribute List" << endl;

	XtVaGetValues ( _attributeListInput, XmNitemCount, &numOfElem, 0);

	for (n = 0; n < numOfElem; n++)
		XmListDeletePos ( _attributeListInput, 0);

	n = 1;
	attributeList = _class->attributeList();
	for ( attributeList->begin(); 
				attributeList->current(); 
				attributeList->next()
			) { 
		attribute = attributeList->current();
		switch (attribute->accessType()) {
			case PRIVATE_ACCESS:
				accessStr = "PRI";
				break;
		  case PROTECTED_ACCESS:
				accessStr = "PRO";
				break;
		  case PUBLIC_ACCESS:
				accessStr = "PUB";
				break;
		  case UNDEF_ACCESS:
		  default:
				accessStr = "UND";
				break;
		};
		
		name = attribute->name();
		description = attribute->description();

		sprintf ( buffer, "%d %s %s %s", n, accessStr, 
							name ? name : "None", description ? description : "None"
						);		

		XmListAddItem ( _attributeListInput, XmStringCreateSimple(buffer), 0);

		attribute->setListId(n++);
	}
}

void XMNewClass::refreshMethodList(void)
{
	char buffer[128];
	char *accessStr = 0, *methodStr = 0, *memoryStr = 0;
	char *name, *description;
	List<Method> *methodList;
	Method *method;
	int n, numOfElem;

	cout << "INFO: refresh MethodList" << endl;

	XtVaGetValues ( _methodListInput, XmNitemCount, &numOfElem, 0);

	for (n = 0; n < numOfElem; n++)
		XmListDeletePos ( _methodListInput, 0);

	n = 1;
	methodList = _class->methodList();
	for ( methodList->begin(); 
				methodList->current(); 
				methodList->next()
			) { 
		method = methodList->current();
		switch (method->accessType()) {
			case PRIVATE_ACCESS:
				accessStr = "PRI";
				break;
		  case PROTECTED_ACCESS:
				accessStr = "PRO";
				break;
		  case PUBLIC_ACCESS:
				accessStr = "PUB";
				break;
		  case UNDEF_ACCESS:
				accessStr = "UND";
				break;  
		  default:
				break;
		};
		switch (method->methodType()) {
		  case UNDEF_METHOD:
				methodStr = "FUN";
				break;
		  case CONSTRUCTOR_METHOD:
				methodStr = "CON";
				break;
		  case DESTRUCTOR_METHOD:
				methodStr = "DES";
				break;
		  case SET_METHOD:
				methodStr = "SET";
				break;
		  case GET_METHOD:
				methodStr = "GET";
				break;
    	  case OPERATOR_METHOD:
				methodStr = "OPE";
				break;
				
        case FRIEND_METHOD:
				methodStr = "FRI";
				break;
			default :	
				methodStr = "FUN";
				break;
		 		
		 }

		switch (method->memoryModel()) {
		  case STATIC_MODEL:
				memoryStr = "STA";
				break;
		  case VIRTUAL_MODEL:
				memoryStr = "VIR";
				break;
		  case DEFAULT_MODEL:
				memoryStr = "DEF";
				break;
		  default:
				memoryStr = "UND";
				break;
		}
		
		name = method->name();
		description = method->description();

		method->setListId(n++);

		sprintf ( buffer, "%2d %s %s %s %s %s",
							method->listId(),
							accessStr, methodStr, memoryStr,
							name ? name : "NONE",
							description ? description : "NONE"
						);		
		XmListAddItem ( _methodListInput, XmStringCreateSimple(buffer), 0);
	}
}

void XMNewClass::refresh(void)
{
	refreshAttributeList();
	refreshMethodList();

	return;
}









