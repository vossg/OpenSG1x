
OSG_BEGIN_NAMESPACE

template <class TagTypeT>
inline
SingleFunctorStore<TagTypeT>::SingleFunctorStore(void)
    : _func              (     ),
      _defaultFunc       (     ),
      _bHasFunctor       (false),
      _bHasDefaultFunctor(false)
{
}

template <class TagTypeT>
inline
SingleFunctorStore<TagTypeT>::~SingleFunctorStore(void)
{
}

template <class TagTypeT>
inline bool
SingleFunctorStore<TagTypeT>::empty(void) const
{
    return _bHasFunctor | _bHasDefaultFunctor;
}

template <class TagTypeT>
inline void
SingleFunctorStore<TagTypeT>::regFunctor(
    const Functor &refFunc, const FieldContainerType &refType)
{
    _func        = refFunc;
    _bHasFunctor = true;
}

template <class TagTypeT>
inline void
SingleFunctorStore<TagTypeT>::unregFunctor(const FieldContainerType &refType)
{
    _bHasFunctor = false;
}

template <class TagTypeT>
inline void
SingleFunctorStore<TagTypeT>::regDefaultFunctor(const Functor &refFunc)
{
    _defaultFunc        = refFunc;
    _bHasDefaultFunctor = true;
}

template <class TagTypeT>
inline void
SingleFunctorStore<TagTypeT>::unregDefaultFunctor(void)
{
    _bHasDefaultFunctor = false;
}

template <class TagTypeT>
inline typename SingleFunctorStore<TagTypeT>::Functor *
SingleFunctorStore<TagTypeT>::getFunctor(const FieldContainerType &refType)
{
    Functor *pRetFunc = NULL;

    if(_bHasFunctor)
    {
	pRetFunc = &_func;
    }
    else if(_bHasDefaultFunctor)
    {
	pRetFunc = &_defaultFunc;
    }
 
    return pRetFunc;        
}

template <class TagTypeT>
inline typename SingleFunctorStore<TagTypeT>::Functor *
SingleFunctorStore<TagTypeT>::getDefaultFunctor(void)
{
    if(_bHasDefaultFunctor)
    {
	return &_defaultFunc;
    }
    else
    {
	return NULL;
    }
}

OSG_END_NAMESPACE

#define OSGSINGLEFUNCTORSTORE_INLINE_CVSID "@(#)$Id: OSGSingleFunctorStore.inl,v 1.1 2003/10/10 13:51:06 neumannc Exp $"
