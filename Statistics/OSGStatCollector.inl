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
inline  UInt32 StatCollector::getNumOfElems (void)
{ 
  return _elemVec.size(); 
}

/*-------------------------------------------------------------------------*/
inline  bool StatCollector::isValidID     (Int32 id)
{ 
  return ((id >= 0) && (id < Int32(_elemVec.size()))); 
}

/*-------------------------------------------------------------------------*/
inline  StatElem *StatCollector::getElem (Int32 id, bool create)  
{
  StatElem *elem = _elemVec[id];

  if (!elem && create) 
    {
      StatElemDescBase *desc = StatElemDescBase::getDesc(id);
      elem =_elemVec[id] = desc->createElem();
    }
  
  return elem;
}

/*-------------------------------------------------------------------------*/
inline  StatElem  *StatCollector::getElem  (StatElemDescBase &desc, 
                                            bool create)
{ 
  return getElem(desc.getID(),create); 
}

/*-------------------------------------------------------------------------*/

template<class T> inline 
T *StatCollector::getElem(StatElemDesc<T> &desc, bool create)
{
    return reinterpret_cast<T*>(getElem(desc.getID(),create));
}

OSG_END_NAMESPACE

#define OSGSTATCOLLECTOR_INLINE_CVSID "@(#)$Id: OSGStatCollector.inl,v 1.7 2002/02/04 20:14:11 dirk Exp $"
