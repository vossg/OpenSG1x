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
#include "Method.h"

#include "XMHelp.h"
#include "XMMethodView.h"

XMMethodView::XMMethodView (Method *method)
: XMAttribView ("Method View", method, 0)
{
	addButton ("Dismiss", DISMISS);
	addButton ("Engage", ENGAGE);
	addButton ("Delete", DELETE);

	createWidgetTree (desk());

	refresh();
}

XMMethodView::~XMMethodView (void)
{
	;
}

void XMMethodView::createWidgetTree (Widget desk)
{
	Widget rowColumn, sep1, sep2, frameLabel;
	Widget memoryModelFrame, accessTypeFrame, implementationFrame;

	rowColumn = XtVaCreateManagedWidget ( "textRowColumn",
																				xmRowColumnWidgetClass, desk,
																			  XmNorientation, XmVERTICAL,
																				XmNpacking, XmPACK_COLUMN,
																				XmNnumColumns, 2,
																				0
																			);

	setAttachment (rowColumn, desk, 0, desk, desk );

	_nameLabel = createLabel ("nameLabel", rowColumn);
	setLabel (_nameLabel, "Name");
	new XMHelp (_nameLabel, "Defines the method name");

	_typeLabel = createLabel ("typeLabel", rowColumn);
	setLabel (_typeLabel, "Type");
	new XMHelp (_typeLabel, "Defines the method type");

	_paramLabel = createLabel ("paramLabel", rowColumn);
	setLabel (_paramLabel, "Parameter");
	new XMHelp (_paramLabel, "Defines the method parameter");

	_descriptionLabel = createLabel ( "descriptionLabel", rowColumn );
	setLabel (_descriptionLabel, "Description");
	new XMHelp (_descriptionLabel, "Method Description");

	_taskLabel = createLabel ( "taskLabel", rowColumn );
	setLabel (_taskLabel, "Task");
	new XMHelp (_taskLabel, "Method Task");

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

	_paramInput = XtVaCreateManagedWidget  ( "paramInput", 
																					xmTextFieldWidgetClass, 
																					rowColumn,
																					0
																			 );

	_descriptionInput = XtVaCreateManagedWidget  ( "descriptionInput",
																								 xmTextFieldWidgetClass, 
																								 rowColumn,
																								 0
																							 );

	_taskText = XtVaCreateManagedWidget  ( "taskInput", xmLabelWidgetClass, 
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
																					XmNchildType, XmFRAME_TITLE_CHILD,
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
	_virtualMemoryInput = createToggleIndicatorButton ( "Virtual", rowColumn,
																											setMemoryModelCB
																									  );
	_defaultMemoryInput = createToggleIndicatorButton ( "Default", rowColumn,
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
	implementationFrame = XtVaCreateManagedWidget ( "implementationFrame", 
																							 xmFrameWidgetClass, desk,
																							 XmNshadowType,
																							 XmSHADOW_ETCHED_OUT,
																							 XmNshadowThickness, 2,
																							 0
																						 );
  frameLabel = XtVaCreateManagedWidget  ( "frameLabel", xmLabelWidgetClass, 
																					implementationFrame,
																					XmNchildType, XmFRAME_TITLE_CHILD,
																					0
																				);
	setLabel (frameLabel, "Implementation");

	rowColumn = XtVaCreateManagedWidget ( "implementationRowColumn",
																			  xmRowColumnWidgetClass, 
																				implementationFrame,
																				XmNradioBehavior, True,
																				XmNradioAlwaysOne, True,
																				XmNorientation, XmVERTICAL,
																				0
																			);

	_abstractInput = createToggleIndicatorButton ( "Abstract", rowColumn,
																											 setImplementationCB
																										 );
	_inlineInput = createToggleIndicatorButton ( "Inline", rowColumn,
																							 setImplementationCB
																						 );
	_impFileInput = createToggleIndicatorButton ( "Imp File", rowColumn,
																								setImplementationCB
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
	setAttachment ( implementationFrame, sep1, sep2, accessTypeFrame, desk);
	//	setAttachment ( taskFrame, sep1, sep2, implementationFrame, desk);

	setAttachment (sep2, 0, desk, desk, desk);
	
	return;
}

void XMMethodView::setMemoryModel(Widget,XtPointer)
{
	;
}

void XMMethodView::setAccessType(Widget,XtPointer)
{
	;
}

void XMMethodView::setImplementation(Widget,XtPointer)
{
	;
}

void XMMethodView::setTask(Widget,XtPointer)
{
	;
}

Method *XMMethodView::method (void)
{
	return (Method*)base();
}

void XMMethodView::refresh(void)
{
	char buffer[256];

	setText (_nameInput, method()->name());

	switch (method()->methodType()) {
		case CONSTRUCTOR_METHOD:
			setSensitive (_nameInput, false);
	    setSensitive (_typeInput, false);
			setSensitive (_paramInput, true);
			setText (_typeInput, "None");
			setText (_paramInput, method()->param());
			setLabel (_taskText, "Constructor");
			break;
		case DESTRUCTOR_METHOD:
			setSensitive (_nameInput, false);
	    setSensitive (_typeInput, false);
			setSensitive (_paramInput, false);
			setText (_typeInput, "None");
			setText (_paramInput, "None");
			setLabel (_taskText, "Descructor");
			break;
	  case SET_METHOD:
			setSensitive (_nameInput, true);
	    setSensitive (_typeInput, true);
			setSensitive (_paramInput, true);
			setText (_typeInput, method()->type());
			setText (_paramInput, method()->param());
			sprintf ( buffer, "set method for attribute %s", 
								method()->dependence() ? method()->dependence()->name() : 0
							);
			setLabel (_taskText, buffer);
			break;
	  case GET_METHOD:
			setSensitive (_nameInput, true);
	    setSensitive (_typeInput, true);
			setSensitive (_paramInput, true);
			setText (_typeInput, method()->type());
			setText (_paramInput, method()->param());
			sprintf ( buffer, "get method for attribute %s", 
								method()->dependence() ? method()->dependence()->name() : 0
							);
			setLabel (_taskText, buffer);
			break;
 	  default:
	  case UNDEF_METHOD:
			setSensitive (_nameInput, true);
	    setSensitive (_typeInput, true);
			setSensitive (_paramInput, true);
			setText (_typeInput, method()->type());
			setText (_paramInput, method()->param());
			setLabel (_taskText, "message");
			break;			
	};
	
	setText (_descriptionInput, method()->description());

	switch (method()->memoryModel()) {
		case STATIC_MODEL:
			setToggle (_staticMemoryInput, true);
			setToggle (_virtualMemoryInput, false);
			setToggle (_defaultMemoryInput, false);
			break;
		case VIRTUAL_MODEL:
			setToggle (_staticMemoryInput, false);
			setToggle (_virtualMemoryInput, true);
			setToggle (_defaultMemoryInput, false);
			break;
	  default:
		case DEFAULT_MODEL:
			setToggle (_staticMemoryInput, false);
			setToggle (_virtualMemoryInput, false);
			setToggle (_defaultMemoryInput, true);
			break;
	};

	switch (method()->accessType()) {
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

	switch (method()->implementType()) {
	  case ABSTRACT_IMP:
			setToggle (_abstractInput, true);
			setToggle (_inlineInput, false);
			setToggle (_impFileInput, false);
			break;
	  case INLINE_IMP:
			setToggle (_abstractInput, false);
			setToggle (_inlineInput, true);
			setToggle (_impFileInput, false);
			break;
	  case IMPFILE_IMP:
			setToggle (_abstractInput, false);
			setToggle (_inlineInput, false);
			setToggle (_impFileInput, true);
			break;
	}
		
	return;
}

void XMMethodView::updateModel (void)
{
	char *modelStr, *viewStr;

	switch (method()->methodType()) {
		case CONSTRUCTOR_METHOD:
			method()->setParam(getText(_paramInput));
			break;
		case DESTRUCTOR_METHOD:
			break;
	  case SET_METHOD:
	  case GET_METHOD:
			modelStr = method()->name();
			viewStr = getText(_nameInput);
			if (strcmp(modelStr, viewStr))
				method()->setName(viewStr);

			modelStr = method()->type();
			viewStr = getText(_typeInput);
			if (strcmp(modelStr, viewStr))
				method()->setType(viewStr);

			modelStr = method()->param();
			viewStr = getText(_paramInput);
			if (strcmp(modelStr, viewStr))
				method()->setParam(viewStr);

			modelStr = method()->description();
			viewStr = getText(_descriptionInput);
			if (strcmp(modelStr, viewStr))
				method()->setDescription(viewStr);

			break;
		default:
	  case UNDEF_METHOD:
			method()->setName(getText(_nameInput));
			method()->setType(getText(_typeInput));
			method()->setParam(getText(_paramInput));
			break;			
	};
	method()->setDescription(getText(_descriptionInput));

	if (getToggle(_staticMemoryInput))
		method()->setMemoryModel (STATIC_MODEL);
	else {
		if (getToggle(_virtualMemoryInput))
			method()->setMemoryModel (VIRTUAL_MODEL);
	  else
			if (getToggle (_defaultMemoryInput))
				method()->setMemoryModel (DEFAULT_MODEL);
		  else
				cerr << "ERROR: No XmToggle set for memoryModel !" << endl;
	}

	if (getToggle(_privateInput))
		method()->setAccessType (PRIVATE_ACCESS);
	else {
		if (getToggle (_protectedInput))
			method()->setAccessType (PROTECTED_ACCESS);
		else
			if (getToggle (_publicInput))
				method()->setAccessType (PUBLIC_ACCESS);
			else
				method()->setAccessType (UNDEF_ACCESS);
	}

	if (getToggle(_abstractInput))
		method()->setImplementType (ABSTRACT_IMP);
	else
		if (getToggle(_inlineInput))
			method()->setImplementType (INLINE_IMP);
	  else
			method()->setImplementType (IMPFILE_IMP);

	method()->touchModelValues();

	return;
}

void XMMethodView::pushAction (int code)
{
	switch (CallbackCode(code)) {
	  case DISMISS:
			popdown();
			if (method()->defaultModelValues()) {
				destroyBase();
				this->suicide();
			}
			break;
	  case ENGAGE:
			updateModel();
		  method()->getClass()->refreshView();
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

void XMMethodView::setType(Widget, XtPointer)
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
			case 'f':
				exStr = "float";
				break;
			case 'v':
				exStr = "void";
				break;
			case 'b':
				exStr = "bool";
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
	}
}

