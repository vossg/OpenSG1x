
#ifndef _OSGQTYPEDFIELDVALUELABEL_H_
#define _OSGQTYPEDFIELDVALUELABEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGQTWidgetDef.h"
#include "OSGQFieldValueLabel.h"

OSG_BEGIN_NAMESPACE

/*! \brief Flyweight label template, which can be specialized for different 
 *  field types.
 */

template <class FieldContentsTypeT>
class OSG_QTWIDGETLIB_DLLTMPLMAPPING QTypedFieldValueLabel : 
    public QGenericFieldValueLabel
{
public:
    typedef FieldContentsTypeT      FieldContentsType;

private:
    typedef QGenericFieldValueLabel Inherited;
};

OSG_END_NAMESPACE

#define OSGQTYPEDFIELDVALUELABEL_HEADER_CVSID "@(#)$Id: OSGQTypedFieldValueLabel.h,v 1.2 2003/05/16 13:54:29 neumannc Exp $"

// #include "OSGQTypedFieldValueLabel.inl"

#endif /* _OSGQTYPEDFIELDVALUELABEL_H_ */
