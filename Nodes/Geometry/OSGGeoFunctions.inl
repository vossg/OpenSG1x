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


/*! function comment
 *
 */

inline       
Int32 IndexDic::entry(vector<Int32> &indexVec)
{
  std::map< std::vector<Int32>, Int32>::iterator iI;
  pair< std::map< std::vector<Int32>,Int32>::iterator, bool > mapRes;

  iI = _indexMap.find(indexVec);
  if (iI == _indexMap.end())
    {
      mapRes = _indexMap.insert (std::map< std::vector<Int32>, Int32>::value_type(indexVec,_indexVec.size()));
      if (mapRes.second)
        {
          iI = mapRes.first;
          _indexVec.push_back(&(iI->first));
        }
      else
        {
          FFATAL (("IndexDic::entry() map insert error\n"));
        }
    }
  
  return iI->second;
}
    
inline const vector<Int32> &IndexDic::entry(Int32 index)
{
    return *(_indexVec[index]);
}          

inline
UInt32 IndexDic::entryCount(void) const
{
    return _indexVec.size();
}

OSG_END_NAMESPACE

#define OSGGEOFUNCTIONS_INLINE_CVSID "@(#)$Id: $"

