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

#ifndef _OSGEXTRACHILDRENLIST_H_
#define _OSGEXTRACHILDRENLIST_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGSystemDef.h>
#include "OSGNewActionTypes.h"

#include <vector>

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING ExtraChildrenList
{
  public:
    /*---------------------------------------------------------------------*/
    /*! \name    Types                                                     */
    /*! \{                                                                 */

    typedef NewActionTypes::PriorityType       PriorityType;
    typedef NewActionTypes::PriorityTypeTraits PriorityTypeTraits;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Constructors                                              */
    /*! \{                                                                 */

    inline ExtraChildrenList(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Destructor                                                */
    /*! \{                                                                 */

    inline ~ExtraChildrenList(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Add                                                       */
    /*! \{                                                                 */

    inline UInt32 addChild(const NodePtr &pChild                   );
    inline UInt32 addChild(const NodePtr &pChild, PriorityType prio);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Access                                                    */
    /*! \{                                                                 */

    inline NodePtr      getChild   (UInt32       childIndex ) const;

    inline PriorityType getPriority(UInt32       childIndex ) const;
    inline void         setPriority(UInt32       childIndex,
                                    PriorityType prio       );

    inline bool         getActive  (UInt32       childIndex ) const;
    inline void         setActive  (UInt32       childIndex,
                                    bool         active     );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Misc                                                      */
    /*! \{                                                                 */

    inline UInt32       getSize    (void                    ) const;
    inline void         clear      (void                    );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    /*---------------------------------------------------------------------*/
    /*! \name    Types                                                     */
    /*! \{                                                                 */

    class ChildrenListEntry
    {
      public:
        inline ChildrenListEntry(void                                   );
        inline ChildrenListEntry(const NodePtr &pNode                   );
        inline ChildrenListEntry(const NodePtr &pNode, PriorityType prio);

        inline NodePtr      getNode    (      void                ) const;
        inline void         setNode    (const NodePtr      &pNode );

        inline PriorityType getPriority(      void                ) const;
        inline void         setPriority(      PriorityType  prio  );

        inline bool         getActive  (      void                ) const;
        inline void         setActive  (      bool          active);

      private:
        NodePtr      _pNode;
        PriorityType _priority;
        bool         _active;
    };

    typedef std::vector<ChildrenListEntry>       InternalChildrenList;
    typedef InternalChildrenList::iterator       InternalChildrenListIt;
    typedef InternalChildrenList::const_iterator InternalChildrenListConstIt;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    InternalChildrenList _childrenList;
};

OSG_END_NAMESPACE

#include "OSGExtraChildrenList.inl"

#define OSGEXTRACHILDRENLIST_HEADER_CVSID "@(#)$Id: OSGExtraChildrenList.h,v 1.2 2004/09/17 14:09:43 neumannc Exp $"

#endif /* _OSGEXTRACHILDRENLIST_H_ */
