
#ifndef _OSGSINGLEFUNCTORSTORE_H_
#define _OSGSINGLEFUNCTORSTORE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGNewActionBase.h"
#include "OSGFunctorStoreTags.h"

OSG_BEGIN_NAMESPACE

template <class TagTypeT>
class OSG_SYSTEMLIB_DLLMAPPING SingleFunctorStore
{
public:
    typedef TagTypeT               TagType;
    typedef NewActionBase::Functor Functor;

    enum
    {
	bHasFunctors = 1
    };

    inline  SingleFunctorStore(void);
    inline ~SingleFunctorStore(void);

    inline bool     empty              (      void                     ) const;

    inline void     regFunctor         (const Functor            &refFunc,
			                const FieldContainerType &refType);
    inline void     unregFunctor       (const FieldContainerType &refType);

    inline void     regDefaultFunctor  (const Functor            &refFunc);
    inline void     unregDefaultFunctor(      void                       );

    inline Functor *getFunctor         (const FieldContainerType &refType);
    inline Functor *getDefaultFunctor  (      void                       );

private:
    Functor _func;
    Functor _defaultFunc;

    bool    _bHasFunctor;
    bool    _bHasDefaultFunctor;
};

OSG_END_NAMESPACE

#include "OSGSingleFunctorStore.inl"

#define OSGSINGLEFUNCTORSTORE_HEADER_CVSID "@(#)$Id: OSGSingleFunctorStore.h,v 1.1 2003/10/10 13:51:06 neumannc Exp $"

#endif /* _OSGSINGLEFUNCTORSTORE_H_ */
