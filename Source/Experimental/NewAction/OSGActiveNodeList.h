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

#ifndef _OSGACTIVENODELIST_H_
#define _OSGACTIVENODELIST_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGNewActionBase.h"
#include <OSGBaseTypes.h>
#include <OSGNodePtr.h>

#include <vector>
#include <algorithm>

OSG_BEGIN_NAMESPACE

class ActiveNodeListConstIt;
class ActiveNodeListIt;

class OSG_SYSTEMLIB_DLLMAPPING ActiveNodeList
{
public:
    typedef NewActionBase::PriorityType      PriorityType;

    inline           ActiveNodeList(void         );
    inline explicit  ActiveNodeList(NodePtr pNode);
    inline          ~ActiveNodeList(void         );

    inline void                  setParent    (NodePtr       pNode     );
    inline NodePtr               getParent    (void                    ) const;

    inline bool                  getActive    (UInt32        uiIndex   ) const;
    inline void                  deactivate   (UInt32        uiIndex   );

    inline PriorityType          getPriority  (UInt32        uiIndex   ) const;
    inline void                  setPriority  (UInt32        uiIndex, 
                                               PriorityType  priority  );

    inline void                  clear        (void                    );
    inline UInt32                size         (void                    ) const;
    inline UInt32                getNumActive (void                    ) const;
    inline void                  swap         (ActiveNodeList &other   );

    inline ActiveNodeListIt      begin(void);
    inline ActiveNodeListIt      end  (void);
    
    inline ActiveNodeListConstIt begin(void) const;
    inline ActiveNodeListConstIt end  (void) const;
    
private:
    friend class ActiveNodeListConstIt;
    friend class ActiveNodeListIt;
    
    class ListEntry
    {
    public:
        inline ListEntry(bool         bActive  = true, 
                         PriorityType priority = PriorityType());

        inline bool         getActive  (void                 ) const;
        inline void         setActive  (bool         bActive);

        inline PriorityType getPriority(void                 ) const;
        inline void         setPriority(PriorityType priority);

    private:
        bool         _bActive;
        PriorityType _priority;
    };

    typedef std::vector<ListEntry>       InternalList;
    typedef InternalList::iterator       InternalListIt;
    typedef InternalList::const_iterator InternalListConstIt;

    NodePtr          _pNode;
    InternalList     _list;
    UInt32           _uiNumActive;
};

OSG_END_NAMESPACE

namespace std
{
    template <>
    inline void swap(OSG::ActiveNodeList &list1, OSG::ActiveNodeList &list2);
}    

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING ActiveNodeListConstIt
{
public:
    typedef ActiveNodeList::PriorityType PriorityType;

    inline ActiveNodeListConstIt(const ActiveNodeList        &refList,
                                       UInt32                 uiIndex);
    
    inline ActiveNodeListConstIt(const ActiveNodeListConstIt &source );

    inline ActiveNodeListConstIt &operator++ (void                 );
    inline ActiveNodeListConstIt  operator++ (int                  );

    inline ActiveNodeListConstIt &operator-- (void                 );
    inline ActiveNodeListConstIt  operator-- (int                  );

    inline const ActiveNodeList &      getList(void) const;

    inline NodePtr                getNode    (void                 ) const;
    inline UInt32                 getIndex   (void                 ) const;
    inline bool                   getActive  (void                 ) const;
    inline PriorityType           getPriority(void                 ) const;

private:
    const ActiveNodeList *_pList;
          UInt32          _uiIndex;
};

class OSG_SYSTEMLIB_DLLMAPPING ActiveNodeListIt
{
public:
    typedef ActiveNodeList::PriorityType   PriorityType;
    typedef ActiveNodeList::InternalListIt InternalListIt;

    inline ActiveNodeListIt(      ActiveNodeList   &refList,
                                  UInt32            uiIndex    );
     
    inline ActiveNodeListIt(const ActiveNodeListIt &source     );
    
    inline operator ActiveNodeListConstIt(void                 ) const;

    inline ActiveNodeListIt &operator++  (void                 );
    inline ActiveNodeListIt  operator++  (int                  );

    inline ActiveNodeListIt &operator--  (void                 );
    inline ActiveNodeListIt  operator--  (int                  );

    inline ActiveNodeList &      getList(void) const;

    inline NodePtr           getNode     (void                 ) const;
    inline UInt32            getIndex    (void                 ) const;
    inline bool              getActive   (void                 ) const;
    inline PriorityType      getPriority (void                 ) const;

    inline void              deactivate  (void                 ) const;
    inline void              setPriority (PriorityType priority) const;

private:
    ActiveNodeList *_pList;
    UInt32          _uiIndex;
};

inline bool operator==(const ActiveNodeListConstIt &lhs, 
                       const ActiveNodeListConstIt &rhs );

inline bool operator!=(const ActiveNodeListConstIt &lhs,
                       const ActiveNodeListConstIt &rhs );

inline bool operator==(const ActiveNodeListIt      &lhs,
                       const ActiveNodeListIt      &rhs );

inline bool operator!=(const ActiveNodeListIt      &lhs,
                       const ActiveNodeListIt      &rhs );

OSG_END_NAMESPACE

#include "OSGActiveNodeList.inl"

#define OSGACTIVENODELIST_HEADER_CVSID "@(#)$Id: OSGActiveNodeList.h,v 1.1 2003/10/10 13:51:06 neumannc Exp $"

#endif /* _OSGACTIVENODELIST_H_ */
