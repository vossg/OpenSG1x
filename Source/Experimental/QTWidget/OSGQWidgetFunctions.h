
#ifndef _OSGQWIDGETFUNCTIONS_H_
#define _OSGQWIDGETFUNCTIONS_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGField.h>
#include <OSGFieldContainer.h>

OSG_BEGIN_NAMESPACE

inline Field *getParentsField      (FieldContainerPtr  pFC,   UInt32 uiAspect);

inline bool   isSFFieldContainerPtr(Field             *pField                );

inline bool   isMFFieldContainerPtr(Field             *pField                );


OSG_END_NAMESPACE

#define OSGQWIDGETFUNCTIONS_HEADER_CVSID "@(#)$Id: OSGQWidgetFunctions.h,v 1.2 2003/05/11 10:33:26 dirk Exp $"

#include "OSGQWidgetFunctions.inl"

#endif /* _OSGQWIDGETFUNCTIONS_H_ */
