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

#ifndef _OSGCHILDRENLIST_H_
#define _OSGCHILDRENLIST_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGSystemDef.h>
#include "OSGNewActionTypes.h"

#include <vector>

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING ChildrenList
{
    /*==========================  PUBLIC  =================================*/
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

    inline  ChildrenList(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Destructor                                                */
    /*! \{                                                                 */

    inline ~ChildrenList(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Parent                                                    */
    /*! \{                                                                 */

    inline void    reset        (void                      );

    inline NodePtr getParentNode(void                      ) const;
    inline void    setParentNode(const NodePtr &pParentNode);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Child                                                     */
    /*! \{                                                                 */

    inline NodePtr      getChild   (UInt32       childIndex ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Active                                                    */
    /*! \{                                                                 */

    inline bool         getActive  (UInt32       childIndex ) const;
    inline void         setActive  (UInt32       childIndex,
                                    bool         active     );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Priority                                                  */
    /*! \{                                                                 */

    inline PriorityType getPriority(UInt32       childIndex ) const;
    inline void         setPriority(UInt32       childIndex,
                                    PriorityType prio       );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Misc                                                      */
    /*! \{                                                                 */

    inline UInt32 getSize(void) const;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    /*---------------------------------------------------------------------*/
    /*! \name    Types                                                     */
    /*! \{                                                                 */

    class ChildrenListEntry
    {
      public:
        inline ChildrenListEntry(void                          );
        inline ChildrenListEntry(bool active, PriorityType prio);

        inline bool         getActive  (void               ) const;
        inline void         setActive  (bool         active);

        inline PriorityType getPriority(void               ) const;
        inline void         setPriority(PriorityType prio  );

      private:
        bool         _active;
        PriorityType _priority;
    };

    typedef std::vector<ChildrenListEntry>       InternalChildrenList;
    typedef InternalChildrenList::iterator       InternalChildrenListIt;
    typedef InternalChildrenList::const_iterator InternalChildrenListConstIt;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    NodePtr              _pParentNode;
    InternalChildrenList _childrenList;
};

OSG_END_NAMESPACE

#include "OSGChildrenList.inl"

#define OSGCHILDRENLIST_HEADER_CVSID "@(#)$Id: OSGChildrenList.h,v 1.2 2004/09/17 14:09:42 neumannc Exp $"

#endif /* _OSGCHILDRENLIST_H_ */
