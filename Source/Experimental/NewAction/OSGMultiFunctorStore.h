
#ifndef _OSGMULTIFUNCTORSTORE_H_
#define _OSGMULTIFUNCTORSTORE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGNewActionBase.h"
#include "OSGFunctorStoreTags.h"

#include <list>
#include <vector>

OSG_BEGIN_NAMESPACE

template <class TagTypeT>
class OSG_SYSTEMLIB_DLLMAPPING MultiFunctorStore
{
public:
    typedef TagTypeT               TagType;
    typedef NewActionBase::Functor Functor;

    enum
    {
	bHasFunctors = 1
    };

    inline  MultiFunctorStore(void);
    inline ~MultiFunctorStore(void);

    inline bool     empty              (      void                     ) const;

    inline void     regFunctor         (const Functor            &refFunc,
			                const FieldContainerType &refType);
    inline void     unregFunctor       (const FieldContainerType &refType);

    inline void     regDefaultFunctor  (const Functor            &refFunc);
    inline void     unregDefaultFunctor(      void                       );

    inline Functor *getFunctor         (const FieldContainerType &refType);
    inline Functor *getDefaultFunctor  (      void                       );

private:
    typedef std::list<Functor>           FunctorStore;
    typedef FunctorStore::iterator       FunctorStoreIt;
    typedef FunctorStore::const_iterator FunctorStoreConstIt;

    typedef std::vector<FunctorStoreIt>  FunctorMap;
    typedef FunctorMap::iterator         FunctorMapIt;
    typedef FunctorMap::const_iterator   FunctorMapConstIt;

    FunctorStore _funcStore;
    FunctorMap   _funcMap;

    Functor      _defaultFunc;
    bool         _bHasDefaultFunctor;
};

OSG_END_NAMESPACE

#include "OSGMultiFunctorStore.inl"

#define OSGMULTIFUNCTORSTORE_HEADER_CVSID "@(#)$Id: OSGMultiFunctorStore.h,v 1.1 2003/10/10 13:51:06 neumannc Exp $"

#endif /* _OSGMULTIFUNCTORSTORE_H_ */
