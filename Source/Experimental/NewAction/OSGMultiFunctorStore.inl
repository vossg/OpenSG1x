/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*    Constructors                                                         */

inline
MultiFunctorStore::MultiFunctorStore(void)
    : _funcStore         (     ),
      _funcMap           (     ),
      _defaultFunc       (     ),
      _bHasDefaultFunctor(false)
{
}

/*-------------------------------------------------------------------------*/
/*    Destructor                                                           */

inline
MultiFunctorStore::~MultiFunctorStore(void)
{
}

/*-------------------------------------------------------------------------*/
/*    Empty                                                                */

inline bool
MultiFunctorStore::empty(void) const
{
    return _funcStore.empty() && !_bHasDefaultFunctor;
}

/*-------------------------------------------------------------------------*/
/*    Functor Registration                                                 */

inline void
MultiFunctorStore::regFunctor(const Functor            &refFunc,
                              const FieldContainerType &refType)
{
    _funcStore.push_front(refFunc);

    if(_funcMap.size() <= refType.getId())
    {
        _funcMap.resize(refType.getId() + 1, _funcStore.end());
    }

    _funcMap[refType.getId()] = _funcStore.begin();
}

inline void
MultiFunctorStore::unregFunctor(const FieldContainerType &refType)
{
    FunctorStoreIt funcIter = _funcMap[refType.getId()];

    if(funcIter != _funcStore.end())
        _funcStore.erase(funcIter);

    _funcMap[refType.getId()] = _funcStore.end();
}

inline void
MultiFunctorStore::regDefaultFunctor(const Functor &refFunc)
{
    _defaultFunc        = refFunc;
    _bHasDefaultFunctor = true;
}

inline void
MultiFunctorStore::unregDefaultFunctor(void)
{
    _bHasDefaultFunctor = false;
}

/*-------------------------------------------------------------------------*/
/*    Functor Access                                                       */

inline MultiFunctorStore::Functor *
MultiFunctorStore::getFunctor(const FieldContainerType &refType)
{
    Functor        *pRetFunc = NULL;
    FunctorStoreIt  funcIter = _funcStore.end();

    if(refType.getId() < _funcMap.size())
    {
        funcIter = _funcMap[refType.getId()];
    }

    if(funcIter != _funcStore.end())
    {
        pRetFunc =  &(*funcIter);
    }
    else if(_bHasDefaultFunctor)
    {
        pRetFunc = &_defaultFunc;
    }

    return pRetFunc;
}

inline MultiFunctorStore::Functor *
MultiFunctorStore::getDefaultFunctor(void)
{
    Functor *pRetFunc = NULL;

    if(_bHasDefaultFunctor)
    {
        pRetFunc = &_defaultFunc;
    }

    return pRetFunc;
}

OSG_END_NAMESPACE

#define OSGMULTIFUNCTORSTORE_INLINE_CVSID "@(#)$Id: OSGMultiFunctorStore.inl,v 1.5 2004/04/20 13:47:08 neumannc Exp $"
