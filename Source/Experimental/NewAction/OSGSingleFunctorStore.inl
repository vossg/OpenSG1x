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
SingleFunctorStore::SingleFunctorStore(void)
    : _uiTypeId          (0    ),
      _func              (     ),
      _defaultFunc       (     ),
      _bHasFunctor       (false),
      _bHasDefaultFunctor(false)
{
}

/*-------------------------------------------------------------------------*/
/*    Destructor                                                           */

inline
SingleFunctorStore::~SingleFunctorStore(void)
{
}

/*-------------------------------------------------------------------------*/
/*    Empty                                                                */

inline bool
SingleFunctorStore::empty(void) const
{
    return _bHasFunctor | _bHasDefaultFunctor;
}

/*-------------------------------------------------------------------------*/
/*    Functor Registration                                                 */

inline void
SingleFunctorStore::regFunctor(
    const Functor &refFunc, const FieldContainerType &refType)
{
    _uiTypeId    = refType.getId();
    _func        = refFunc;
    _bHasFunctor = true;
}

inline void
SingleFunctorStore::unregFunctor(void)
{
    _bHasFunctor = false;
}

inline void
SingleFunctorStore::regDefaultFunctor(const Functor &refFunc)
{
    _defaultFunc        = refFunc;
    _bHasDefaultFunctor = true;
}

inline void
SingleFunctorStore::unregDefaultFunctor(void)
{
    _bHasDefaultFunctor = false;
}

/*-------------------------------------------------------------------------*/
/*    Functor Access                                                       */

inline SingleFunctorStore::Functor *
SingleFunctorStore::getFunctor(const FieldContainerType &refType)
{
    Functor *pRetFunc = NULL;

    if(_bHasFunctor && (refType.getId() == _uiTypeId))
    {
        pRetFunc = &_func;
    }
    else if(_bHasDefaultFunctor)
    {
        pRetFunc = &_defaultFunc;
    }

    return pRetFunc;
}

inline SingleFunctorStore::Functor *
SingleFunctorStore::getDefaultFunctor(void)
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

#define OSGSINGLEFUNCTORSTORE_INLINE_CVSID "@(#)$Id: OSGSingleFunctorStore.inl,v 1.4 2004/04/20 13:47:08 neumannc Exp $"
