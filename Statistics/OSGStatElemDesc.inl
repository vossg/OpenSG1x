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

/*-------------------------------------------------------------------------*/

inline Bool StatElemDescBase::isValidID (Int32 ID)
{ 
  return (_descVec && (ID >= 0) && (ID < Int32(_descVec->size()))); 
}

/*-------------------------------------------------------------------------*/

inline  StatElemDescBase *StatElemDescBase::getDesc (Int32 ID)
{ 
  return (*_descVec)[ID]; 
}

/*-------------------------------------------------------------------------*/

inline  Int32 StatElemDescBase::getNumOfDescs(void)
{ 
  return _descVec ? _descVec->size() : 0; 
}

/*-------------------------------------------------------------------------*/

inline const Char8 *StatElemDescBase::getClassname(void)
{ 
  return "StatElemDescBase"; 
}

/*-------------------------------------------------------------------------*/

inline        Int32   StatElemDescBase::getID            (void) 
{ 
  return _ID; 
}

/*-------------------------------------------------------------------------*/

inline  const IDString &StatElemDescBase::getName        (void) 
{ 
  return _name; 
}

/*-------------------------------------------------------------------------*/

inline  const IDString &StatElemDescBase::getDescription (void) 
{ 
  return _description; 
}



// The templated StatElemDesc

template <class T>
static char StatElemDesc<T>::cvsid[] = "@(#)$Id: OSGStatElemDesc.inl,v 1.2 2002/01/20 11:10:28 dirk Exp $";


template <class T>
StatElemDesc<T>::StatElemDesc( const Char8 *name, const Char8 *description ) :
    StatElemDescBase(name, description)
{
}


template <class T>
StatElemDesc<T>::~StatElemDesc()
{
}


template <class T>
StatElem *StatElemDesc<T>::createElem(void)
{
    return T::create(this);
}




OSG_END_NAMESPACE
