/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#if defined(__sgi) || defined(__linux)

template <class Tp, class Alloc> inline
MFieldVector<Tp, Alloc>::MFieldVector(const allocator_type& __a) :
    Inherited(__a) 
{
}

template <class Tp, class Alloc> inline
MFieldVector<Tp, Alloc>::MFieldVector(      size_type       __n, 
                                      const Tp             &__value,
                                      const allocator_type &__a    ) :
    Inherited(__n, __value, __a)
{
}
    
template <class Tp, class Alloc> inline
MFieldVector<Tp, Alloc>::MFieldVector(size_type __n) :
    Inherited(__n)
{
}
    
template <class Tp, class Alloc> inline
MFieldVector<Tp, Alloc>::MFieldVector(const vector<Tp, Alloc>& __x) :
    Inherited(__x.size())
{
}

template <class Tp, class Alloc> inline
MFieldVector<Tp, Alloc>::MFieldVector(const MFieldVector<Tp, Alloc>& __x) :
    Inherited(__x.size())
{
}

#ifdef __STL_MEMBER_TEMPLATES
  // Check whether it's an integral type.  If so, it's not an iterator.
template <class Tp, class Alloc> 
template <class InputIterator> inline
MFieldVector<Tp, Alloc>::MFieldVector(      InputIterator   __first, 
                                            InputIterator   __last,
                                      const allocator_type &__a    ) :
    Inherited(__first, __last, __a) 
{
}

#else

template <class Tp, class Alloc> inline
MFieldVector<Tp, Alloc>::MFieldVector(const Tp             *__first, 
                                      const Tp             *__last,
                                      const allocator_type &__a    ) :
    Inherited(__first, __last, __a) 
{
}

#endif /* __STL_MEMBER_TEMPLATES */

MFieldVector<Tp, Alloc>::~MFieldVector() 
{
}

#elif defined(WIN32)

template<class Ty, class A> inline
MFieldVector<Ty, A>::MFieldVector(const A &_Al) : 
    Inherited(_Al) 
{
}

template<class Ty, class A> inline
MFieldVector<Ty, A>::MFieldVector(      size_type  _N, 
                                  const Ty        &_V,
                                  const A         &_Al) : 
    Inherited(_N, _V, _Al)
{
}

template<class Ty, class A> inline
MFieldVector<Ty, A>::MFieldVector(const vector<Ty, A> &_X) :
    Inherited(_X)
{
}


template<class Ty, class A> inline
MFieldVector<Ty, A>::MFieldVector(      It  _F, 
                                        It  _L, 
                                  const A  &_Al) :
    Inherited(_F, _L, _Al)
{
}

template<class Ty, class A> inline
MFieldVector<Ty, A>::~MFieldVector()
{
}

#endif

OSG_END_NAMESPACE

#define OSGMFIELDVECTOR_INLINE_CVSID "@(#)$Id: $"

