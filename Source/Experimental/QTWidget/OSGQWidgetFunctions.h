
#ifndef _OSGQWIDGETFUNCTIONS_H_
#define _OSGQWIDGETFUNCTIONS_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGField.h>
#include <OSGFieldContainer.h>

OSG_BEGIN_NAMESPACE

Field *getParentsField      (FieldContainerPtr  pFC,   UInt32 uiAspect);

bool   isSFFieldContainerPtr(Field             *pField                );

bool   isMFFieldContainerPtr(Field             *pField                );


OSG_END_NAMESPACE

#define OSGQWIDGETFUNCTIONS_HEADER_CVSID "@(#)$Id: OSGQWidgetFunctions.h,v 1.1 2003/05/07 14:03:40 neumannc Exp $"

#include "OSGQWidgetFunctions.inl"

#endif /* _OSGQWIDGETFUNCTIONS_H_ */
