#include <sysConfig.h>

#include <iostream>
#include <stdio.h>

#include <Xm/Form.h>
#include <Xm/TextF.h>
#include <Xm/RowColumn.h>
#include <Xm/List.h>
#include <Xm/Label.h>
#include <Xm/Frame.h>

#include "Class.h"
#include "Attribute.h"

#include "XMHelp.h"
#include "XMAttributeView.h"

XMAttributeView::XMAttributeView (Attribute *attribute)
: XMAttribView ("Attribute View", attribute, 0)
{
	addButton ("Dismiss", DISMISS);
	addButton ("Engage", ENGAGE);
	addButton ("Delete", DELETE);

	createWidgetTree (desk());

	refresh();
}

XMAttributeView::~XMAttributeView (void)
{
	;
}

void XMAttributeView::createWidgetTree (Widget desk)
{
	Widget rowColumn, sep1, sep2, frameLabel;
	Widget memoryModelFrame, accessTypeFrame, methodBindingFrame;

	rowColumn = XtVaCreateManagedWidget ( "textRowColumn",
																				xmRowColumnWidgetClass, desk,
																			  XmNorientation, XmVERTICAL,
																				XmNpacking, XmPACK_COLUMN,
																				XmNnumColumns, 2,
																				0
																			);

	setAttachment (rowColumn, desk, 0, desk, desk );

	_nameLabel = createLabel ("nameLabel", rowColumn);
	setLabel (_nameLabel, "Name / Elements");
	new XMHelp (_nameLabel, "Defines the attribute name");

	_typeLabel = createLabel ("typeLabel", rowColumn);
	setLabel (_typeLabel, "Type");
	new XMHelp (_typeLabel, "Defines the attribute type");

	_descriptionLabel = createLabel ( "descriptionLabel", rowColumn );
	setLabel (_descriptionLabel, "Description");
	new XMHelp (_descriptionLabel, "Attribute Description");

	_initialValueLabel = createLabel ( "initailValueLabel", rowColumn );
	setLabel (_initialValueLabel, "Initial value");
	new XMHelp (_initialValueLabel, "Initail value used in all constructors");

	_nameInput = XtVaCreateManagedWidget  ( "nameInput", 
																					xmTextFieldWidgetClass, 
																					rowColumn,
																					0
																			 );

	_typeInput = XtVaCreateManagedWidget  ( "typeInput", 
																					xmTextFieldWidgetClass, 
																					rowColumn,
																					0
																			 );


	_descriptionInput = XtVaCreateManagedWidget  ( "descriptionInput",
																								 xmTextFieldWidgetClass, 
																								 rowColumn,
																								 0
																							 );

	_initialValueInput = XtVaCreateManagedWidget  ( "initailValueInput",
																								 xmTextFieldWidgetClass, 
																								 rowColumn,
																								 0
																							 );
	
	XtAddCallback ( _typeInput, XmNactivateCallback, 
									setTypeCB, this
								);

  XtAddCallback ( _typeInput, XmNlosingFocusCallback, 
									setTypeCB, this
								);     
	

	sep1 = createHorSeparator("sep1", desk);
	setAttachment (sep1, rowColumn, 0, desk, desk);

	//----------------------------------------------------------------------
	memoryModelFrame = XtVaCreateManagedWidget ( "memoryModelFrame", 
																							 xmFrameWidgetClass, desk,
																							 XmNshadowType,
																							 XmSHADOW_ETCHED_OUT,
																							 XmNshadowThickness, 2,
																							 0
																						 );
  frameLabel = XtVaCreateManagedWidget  ( "frameLabel", xmLabelWidgetClass, 
																					memoryModelFrame,
																					XmNchildType,            	XmFRAME_TITLE_CHILD,
																					0
																				);
	setLabel (frameLabel, "Memory Model");

	rowColumn = XtVaCreateManagedWidget ( "memoryModelRowColumn",
																			  xmRowColumnWidgetClass, 
																				memoryModelFrame,
																				XmNorientation, XmVERTICAL,
																				XmNradioBehavior, True,
																				XmNradioAlwaysOne, True,
																				0
																		  );
	_staticMemoryInput = createToggleIndicatorButton ( "Static", rowColumn,
	 	    	    	    	    	    	    	    	    	 setMemoryModelCB
																									 );
	_defaultMemoryInput = createToggleIndicatorButton ( "Default", rowColumn,
	 	    	    	    	    	    	    	    	 	 	  setMemoryModelCB
																									  );

   _enumMemoryInput = createToggleIndicatorButton ( "Enum", rowColumn,
	 	    	    	    	    	    	    	    	 	 	  setMemoryModelCB
																									  );
   _typedefMemoryInput = createToggleIndicatorButton  ( "Typedef", rowColumn,
	 	    	    	    	    	    	    	    	 	 	  setMemoryModelCB
																									  );
	//-----------------------------------------------------------------------
	accessTypeFrame = XtVaCreateManagedWidget ( "accessTypeFrame", 
																							 xmFrameWidgetClass, desk,
																							 XmNshadowType,
																							 XmSHADOW_ETCHED_OUT,
																							 XmNshadowThickness, 2,
																							 0
																						 );
  frameLabel = XtVaCreateManagedWidget  ( "frameLabel", xmLabelWidgetClass, 
																					accessTypeFrame,
																					XmNchildType, XmFRAME_TITLE_CHILD,
																					0
																				);
	setLabel (frameLabel, "Access Type");

	rowColumn = XtVaCreateManagedWidget ( "accessTypeRowColumn",
																			  xmRowColumnWidgetClass, 
																				accessTypeFrame,
																				XmNorientation, XmVERTICAL,
																				XmNradioBehavior, True,
																				XmNradioAlwaysOne, True,
																				0
																		  );
	_privateInput = createToggleIndicatorButton ( "Private", rowColumn,
																										 setAccessTypeCB
																									 );
	_protectedInput = createToggleIndicatorButton ( "Protected", rowColumn,
																											setAccessTypeCB
																									  );
	_publicInput = createToggleIndicatorButton ( "Public", rowColumn,
																											setAccessTypeCB
 																									  );
	//-----------------------------------------------------------------------
	methodBindingFrame = XtVaCreateManagedWidget ( "methodBindingFrame", 
																							 xmFrameWidgetClass, desk,
																							 XmNshadowType,
																							 XmSHADOW_ETCHED_OUT,
																							 XmNshadowThickness, 2,
																							 0
																						 );
  frameLabel = XtVaCreateManagedWidget  ( "frameLabel", xmLabelWidgetClass, 
																					methodBindingFrame,
																					XmNchildType, XmFRAME_TITLE_CHILD,
																					0
																				);
	setLabel (frameLabel, "MethodBinding");

	rowColumn = XtVaCreateManagedWidget ( "methodBindingRowColumn",
																			  xmRowColumnWidgetClass, 
																				methodBindingFrame,
																				XmNorientation, XmVERTICAL,
																				0
																			);

	_setMethodInput = createToggleIndicatorButton ( "Set Method", rowColumn,
																									 setMethodBindingCB
              																 );
	_getMethodInput = createToggleIndicatorButton ( "Get Method", rowColumn,
																							 setMethodBindingCB
																						 );
	_prefixInput = createToggleIndicatorButton ( "Underscore prefix", rowColumn,
																								setMethodBindingCB
																							);
	_getPrefixInput = createToggleIndicatorButton ( "get prefix", rowColumn,
																									setMethodBindingCB
																									);
	/*
	//-----------------------------------------------------------------------
	taskFrame = XtVaCreateManagedWidget ( "taskFrame", 
																							 xmFrameWidgetClass, desk,
																							 XmNshadowType,
																							 XmSHADOW_ETCHED_OUT,
																							 XmNshadowThickness, 2,
																							 0
																						 );
  frameLabel = XtVaCreateManagedWidget  ( "frameLabel", xmLabelWidgetClass, 
																					taskFrame,
																					XmNchildType, XmFRAME_TITLE_CHILD,
																					0
																				);
	setLabel (frameLabel, "Task");

	rowColumn = XtVaCreateManagedWidget ( "taskRowColumn",
																			  xmRowColumnWidgetClass, 
																				taskFrame,
																				XmNorientation, XmVERTICAL,
																				XmNradioBehavior, True,
																				XmNradioAlwaysOne, True,
																				0
																		  );
	_constructorInput = createToggleIndicatorButton ( "Constructor", rowColumn,
																										 setTaskCB
																									 );
	_descructorInput = createToggleIndicatorButton ( "Descructor", rowColumn,
																											setTaskCB
																									  );
	_messageInput = createToggleIndicatorButton ( "Message", rowColumn,
																											setTaskCB
 																									  );
																										
																										*/
	//-------------------------------------------------------------------------
	sep2 = createHorSeparator("sep2", desk);
	
	setAttachment ( memoryModelFrame, sep1, sep2, desk, 0);
	setAttachment ( accessTypeFrame, sep1, sep2, memoryModelFrame, 0);
	setAttachment ( methodBindingFrame, sep1, sep2, accessTypeFrame, desk);
	//	setAttachment ( taskFrame, sep1, sep2, methodBindingFrame, desk);

	setAttachment (sep2, 0, desk, desk, desk);
	
	return;
}

void XMAttributeView::setMemoryModel(Widget,XtPointer)
{
	;
}

void XMAttributeView::setAccessType(Widget,XtPointer)
{
	;
}

void XMAttributeView::setMethodBinding(Widget,XtPointer)
{
	;
}

Attribute *XMAttributeView::attribute (void)
{
	return (Attribute*)base();
}

void XMAttributeView::refresh(void)
{
	setText (_nameInput, attribute()->name());
	setText (_typeInput, attribute()->type());
	setText (_descriptionInput, attribute()->description());
	setText (_initialValueInput, attribute()->initialValue());

	switch (attribute()->memoryModel()) {
		case STATIC_MODEL:
			setToggle (_staticMemoryInput, true);
			setToggle (_defaultMemoryInput, false);
			break;
	  default:
		case DEFAULT_MODEL:
	  case VIRTUAL_MODEL:
			setToggle (_staticMemoryInput, false);
			setToggle (_defaultMemoryInput, true);
			break;
	};

	switch (attribute()->accessType()) {
		case PRIVATE_ACCESS:
	  case UNDEF_ACCESS:
			setToggle (_privateInput, true);
			setToggle (_protectedInput, false);
			setToggle (_publicInput, false);
			break;
	  case PROTECTED_ACCESS:
			setToggle (_privateInput, false);
			setToggle (_protectedInput, true);
			setToggle (_publicInput, false);
			break;
	  case PUBLIC_ACCESS:
			setToggle (_privateInput, false);
			setToggle (_protectedInput, false);
			setToggle (_publicInput, true);
			break;
	};

	setToggle (_prefixInput, attribute()->underscorePrefix());
	setToggle (_getPrefixInput, attribute()->getPrefix());
	setToggle (_setMethodInput, attribute()->setMethod() ? true : false);
	setToggle (_getMethodInput, attribute()->getMethod() ? true : false);

	return;
}

void XMAttributeView::updateModel (void)
{
	attribute()->setName(getText(_nameInput));
	attribute()->setType(getText(_typeInput));
	attribute()->setDescription(getText(_descriptionInput));
	attribute()->setInitialValue(getText(_initialValueInput));

	if (getToggle(_staticMemoryInput))
		attribute()->setMemoryModel (STATIC_MODEL);
	else {
		if (getToggle (_defaultMemoryInput))
			attribute()->setMemoryModel (DEFAULT_MODEL);
		else
		  if (getToggle (_enumMemoryInput))
			   attribute()->setMemoryModel (ENUM_MODEL);
        else
		    if (getToggle (_typedefMemoryInput))
			      attribute()->setMemoryModel (TYPEDEF_MODEL);
    	     else    	  
    			cerr << "ERROR: No XmToggle set for memoryModel !" << endl;
	}

	if (getToggle(_privateInput))
		attribute()->setAccessType (PRIVATE_ACCESS);
	else {
		if (getToggle (_protectedInput))
			attribute()->setAccessType (PROTECTED_ACCESS);
		else
			if (getToggle (_publicInput))
				attribute()->setAccessType (PUBLIC_ACCESS);
			else
				attribute()->setAccessType (UNDEF_ACCESS);
	}

  attribute()->setUnderscorePrefix(getToggle(_prefixInput));
  attribute()->setGetPrefix(getToggle(_getPrefixInput));

	if (getToggle(_getMethodInput)) {
		if (!attribute()->getMethod())
			attribute()->createGetMethod();
	}
	else
		if (attribute()->getMethod()) {
			delete attribute()->getMethod();
		}

	if (getToggle(_setMethodInput)) {
		if (!attribute()->setMethod())
			attribute()->createSetMethod();
	}
	else
		if (attribute()->setMethod()) {
			delete attribute()->setMethod();
		}

	attribute()->touchModelValues();

	return;
}

void XMAttributeView::pushAction (int code)
{
	switch (CallbackCode(code)) {
	  case DISMISS:
			popdown();
			if (attribute()->defaultModelValues()) {
				destroyBase();
				this->suicide();
			}
			break;
	  case ENGAGE:
			updateModel();
		  attribute()->getClass()->refreshView();
			popdown();
			break;
	  case DELETE:
			popdown();
			destroyBase();
			this->suicide();
			break;
	};

	return;
}

void XMAttributeView::setType(Widget, XtPointer)
{
	char *exStr = 0;
	char *str = getText(_typeInput);
	char typeBuffer[32];
	bool setUnsigned;
	
	if (!str)
		return;

	if (strlen(str) == 2 && *str == 'u') {
		setUnsigned = true;
		str++;
	}
	else
		setUnsigned = false;

	if (strlen(str) == 1)
		switch (*str) 
			{	
			case 'i':
				exStr = "int";
			break;
		  case 's':
				exStr = "short";
				break;
		  case 'l':
				exStr = "long";
				break;
		  case 'd':
				exStr = "double";
				break;
			case 'v':
				exStr = "void*";
				break;
			case 'b':
				exStr = "bool";
				break;
			case 'f':
				exStr = "float";
				break;
			case 't':
				exStr = "char*";
				break;
			}

	if (exStr) {
		if (setUnsigned) {
			sprintf(typeBuffer, "unsigned %s", exStr);
			exStr = typeBuffer;
		}
		setText (_typeInput, exStr);
		setText (_initialValueInput, "0");
	}
}







