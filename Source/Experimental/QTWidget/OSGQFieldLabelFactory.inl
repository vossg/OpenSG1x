
OSG_BEGIN_NAMESPACE

template <class FieldLabelType>
QLabelRegisterWrapper<FieldLabelType>::QLabelRegisterWrapper(
    const std::string &strFieldContentsName)
{
    QFieldLabelFactory::the().registerLabel(strFieldContentsName,
                                            &FieldLabelType::create);
}

OSG_END_NAMESPACE

#define OSGQFIELDLABELFACTORY_INLINE_CVSID "@(#)$Id: OSGQFieldLabelFactory.inl,v 1.1 2003/05/07 14:03:40 neumannc Exp $"

