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
inline  Bool StatCollector::isValidID     (Int32 ID)
{ 
  return ((ID >= 0) && (ID < Int32(_elemVec.size()))); 
}

/*-------------------------------------------------------------------------*/
inline  StatElem *StatCollector::getElem (Int32 ID, Bool create)  
{
  StatElem *elem = _elemVec[ID];

  if (!elem && create) 
    {
      StatElemDescBase *desc = StatElemDescBase::getDesc(ID);
      elem =_elemVec[ID] = desc->createElem();
    }
  
  return elem;
}

/*-------------------------------------------------------------------------*/
inline  StatElem  *StatCollector::getElem  (StatElemDescBase &desc, 
                                            Bool create)
{ 
  return getElem(desc.getID(),create); 
}

/*-------------------------------------------------------------------------*/

template<class T> inline 
T *StatCollector::getElem(StatElemDesc<T> &desc, Bool create)
{
    return reinterpret_cast<T*>(getElem(desc.getID(),create));
}

OSG_END_NAMESPACE
