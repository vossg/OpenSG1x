

#include "OSGQFieldLabelFactory.h"
#include "OSGQFieldView_qt.h"

#include "OSGQFieldValueLabel.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGQFieldLabelFactory.cpp,v 1.1 2003/05/07 14:03:40 neumannc Exp $";
    static Char8 cvsid_hpp[] = OSGQFIELDLABELFACTORY_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGQFIELDLABELFACTORY_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

QFieldLabelFactory *QFieldLabelFactory::_the = 0;

QFieldLabelFactory::~QFieldLabelFactory(void)
{
}

QFieldLabelFactory &
QFieldLabelFactory::the(void)
{
    if(!_the)
        _the = new QFieldLabelFactory;

    return *_the;
}

bool
QFieldLabelFactory::registerLabel(const std::string  &strFieldContentName,
                                        LabelCreateF  labelCreateFunc     )
{
    _labelMap[strFieldContentName] = labelCreateFunc;

    return true;
}

QFieldValueLabelBase *
QFieldLabelFactory::createLabel(QFieldViewBase *pView, UInt32 uiIndex)
{
    const Char8 *szContentTypeName = 
        pView->getFieldPtr()->getContentType().getCName();

    LabelMapIt iter = _labelMap.find(szContentTypeName);

    if(iter != _labelMap.end())
    {
        return (*iter).second(pView, uiIndex);
    }
    else
    {
        return _defaultLabelCreateFunc(pView, uiIndex);
    }
}

QFieldLabelFactory::QFieldLabelFactory(void)
    : _labelMap              (                                ),
      _defaultLabelCreateFunc(&QGenericFieldValueLabel::create)
{
}

