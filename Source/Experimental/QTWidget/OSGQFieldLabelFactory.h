
#ifndef _OSGQFIELDLABELFACTORY_H_
#define _OSGQFIELDLABELFACTORY_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBaseTypes.h>

#include <string>
#include <map>

#include <qnamespace.h>

OSG_BEGIN_NAMESPACE

class QFieldViewBase;
class QFieldValueLabelBase;

class QFieldLabelFactory : public Qt
{
public:
    typedef QFieldValueLabelBase *(*LabelCreateF)(QFieldViewBase *, UInt32);

    ~QFieldLabelFactory(void);

    static QFieldLabelFactory &the();
    
    bool registerLabel       (const std::string  &strFieldContentsName,
                                    LabelCreateF  labelCreateFunc      );
    bool registerDefaultLabel(const std::string  &strFieldContentsName,
                                    LabelCreateF  labelCreateFunc      );

    QFieldValueLabelBase *createLabel(QFieldViewBase *pView, UInt32 uiIndex);

private:
    typedef std::map<std::string, LabelCreateF>           LabelMap;
    typedef std::map<std::string, LabelCreateF>::iterator LabelMapIt;

    QFieldLabelFactory(void);

    static QFieldLabelFactory *_the;

    LabelMap                   _labelMap;
    LabelCreateF               _defaultLabelCreateFunc;
};

template <class FieldLabelType>
struct QLabelRegisterWrapper
{
    explicit QLabelRegisterWrapper(const std::string &strFieldContentsName);
};

OSG_END_NAMESPACE

#define OSGQFIELDLABELFACTORY_HEADER_CVSID "@(#)$Id: OSGQFieldLabelFactory.h,v 1.1 2003/05/07 14:03:40 neumannc Exp $"

#include "OSGQFieldLabelFactory.inl"

#endif /* _OSGQFIELDLABELFACTORY_H_ */
