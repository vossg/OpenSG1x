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
SimpleFunctorStore::SimpleFunctorStore(void)
    : _func       (     ),
      _bHasFunctor(false)
{
}

/*-------------------------------------------------------------------------*/
/*    Destructor                                                           */

inline
SimpleFunctorStore::~SimpleFunctorStore(void)
{
}

/*-------------------------------------------------------------------------*/
/*    Empty                                                                */

inline bool
SimpleFunctorStore::empty(void) const
{
    return _bHasFunctor;
}

/*-------------------------------------------------------------------------*/
/*    Functor Registration                                                 */

inline void 
SimpleFunctorStore::regFunctor(const Functor &refFunc)
{
    _func        = refFunc;
    _bHasFunctor = true;
}

inline void
SimpleFunctorStore::unregFunctor(void)
{
    _bHasFunctor = false;
}

/*-------------------------------------------------------------------------*/
/*    Functor Access                                                       */

inline SimpleFunctorStore::Functor *
SimpleFunctorStore::getFunctor(void)
{
    Functor *pRetFunc = NULL;

    if(_bHasFunctor)
    {
        pRetFunc =  &_func;
    }
 
    return pRetFunc;
}

OSG_END_NAMESPACE

#define OSGSIMPLEFUNCTORSTORE_INLINE_CVSID "@(#)$Id: OSGSimpleFunctorStore.inl,v 1.4 2004/04/20 13:47:08 neumannc Exp $"
