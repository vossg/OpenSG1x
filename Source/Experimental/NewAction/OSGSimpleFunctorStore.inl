/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     * 
 *                                                                           * 
 *                                                                           * 
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                * 
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

#define OSGSIMPLEFUNCTORSTORE_INLINE_CVSID "@(#)$Id: OSGSimpleFunctorStore.inl,v 1.2 2003/10/10 14:27:44 neumannc Exp $"
