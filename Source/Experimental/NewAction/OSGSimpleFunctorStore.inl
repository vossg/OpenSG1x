
OSG_BEGIN_NAMESPACE

template <class TagTypeT>
inline
SimpleFunctorStore<TagTypeT>::SimpleFunctorStore(void)
    : _func       (     ),
      _bHasFunctor(false)
{
}

template <class TagTypeT>
inline
SimpleFunctorStore<TagTypeT>::~SimpleFunctorStore(void)
{
}

template <class TagTypeT>
inline bool
SimpleFunctorStore<TagTypeT>::empty(void) const
{
    return _bHasFunctor;
}

template <class TagTypeT>
inline void 
SimpleFunctorStore<TagTypeT>::regFunctor(const Functor &refFunc)
{
    _func        = refFunc;
    _bHasFunctor = true;
}

template <class TagTypeT>
inline void
SimpleFunctorStore<TagTypeT>::unregFunctor(void)
{
    _bHasFunctor = false;
}

template <class TagTypeT>
inline typename SimpleFunctorStore<TagTypeT>::Functor *
SimpleFunctorStore<TagTypeT>::getFunctor(void)
{
    Functor *pRetFunc = NULL;

    if(_bHasFunctor)
    {
	pRetFunc =  &_func;
    }
 
    return pRetFunc;
}

OSG_END_NAMESPACE

#define OSGSIMPLEFUNCTORSTORE_INLINE_CVSID "@(#)$Id: OSGSimpleFunctorStore.inl,v 1.1 2003/10/10 13:51:06 neumannc Exp $"
