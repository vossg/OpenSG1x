
#ifndef _OSGQTYPEDFIELDVALUELABEL_H_
#define _OSGQTYPEDFIELDVALUELABEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGQFieldValueLabel.h"

OSG_BEGIN_NAMESPACE

/*! \brief Flyweight label template, which can be specialized for different 
 *  field types.
 */

template <class FieldContentsTypeT>
class QTypedFieldValueLabel : public QGenericFieldValueLabel
{
public:
    typedef FieldContentsTypeT      FieldContentsType;

private:
    typedef QGenericFieldValueLabel Inherited;
};

OSG_END_NAMESPACE

#define OSGQTYPEDFIELDVALUELABEL_HEADER_CVSID "@(#)$Id: OSGQTypedFieldValueLabel.h,v 1.1 2003/05/07 14:03:40 neumannc Exp $"

// #include "OSGQTypedFieldValueLabel.inl"

#endif /* _OSGQTYPEDFIELDVALUELABEL_H_ */
