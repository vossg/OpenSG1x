
#ifndef _OSGSIMPLEFUNCTORSTORE_H_
#define _OSGSIMPLEFUNCTORSTORE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGNewActionBase.h"
#include "OSGFunctorStoreTags.h"

OSG_BEGIN_NAMESPACE

template <class TagTypeT>
class OSG_SYSTEMLIB_DLLMAPPING SimpleFunctorStore
{
public:
    typedef TagTypeT               TagType;
    typedef NewActionBase::Functor Functor;

    enum
    {
	bHasFunctors = 1
    };

    inline  SimpleFunctorStore  (      void            );
    inline ~SimpleFunctorStore  (      void            );
    
    inline bool     empty       (      void            ) const;

    inline void     regFunctor  (const Functor &refFunc);
    inline void     unregFunctor(      void            );

    inline Functor *getFunctor  (      void            );

private:
    Functor _func;
    bool    _bHasFunctor;
};

OSG_END_NAMESPACE

#include "OSGSimpleFunctorStore.inl"

#define OSGSIMPLEFUNCTORSTORE_HEADER_CVSID "@(#)$Id: OSGSimpleFunctorStore.h,v 1.1 2003/10/10 13:51:06 neumannc Exp $"

#endif /* _OSGSIMPLEFUNCTORSTORE_H_ */
