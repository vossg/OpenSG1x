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

#ifndef _OSGACTIVECHILDRENLIST_H_
#define _OSGACTIVECHILDRENLIST_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGSystemDef.h>
#include "OSGNewActionTypes.h"

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING ActiveChildrenList
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name    Types                                                     */
    /*! \{                                                                 */

    typedef NewActionTypes::PriorityType PriorityType;
    typedef MFNodePtr::iterator          MFNodePtrIt;
    typedef MFNodePtr::const_iterator    MFNodePtrConstIt;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Constructors                                              */
    /*! \{                                                                 */

    inline  ActiveChildrenList(void                      );
    inline  ActiveChildrenList(const NodePtr &pParentNode);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Destructor                                                */
    /*! \{                                                                 */

    inline ~ActiveChildrenList(void                      );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Parent Access                                             */
    /*! \{                                                                 */

    inline void    buildList    (void                      );

    inline NodePtr getParentNode(void                      ) const;
    inline void    setParentNode(const NodePtr &pParentNode);

    inline UInt32  getNumActive (void                      ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Children Active Access                                   */
    /*! \{                                                                 */

    inline bool         getActive  (MFNodePtrConstIt itChild ) const;
    inline bool         getActive  (UInt32           uiIndex ) const;
    inline void         setActive  (MFNodePtrConstIt itChild,
                                    bool             bActive );
    inline void         setActive  (UInt32           uiIndex,
                                    bool             bActive );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Children Priority Access                                  */
    /*! \{                                                                 */

    inline PriorityType getPriority(MFNodePtrConstIt itChild ) const;
    inline PriorityType getPriority(UInt32           uiIndex ) const;
    inline void         setPriority(MFNodePtrConstIt itChild,
                                    PriorityType     priority);
    inline void         setPriority(UInt32           uiIndex,
                                    PriorityType     priority);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Children Iterator Access                                  */
    /*! \{                                                                 */

    inline MFNodePtrConstIt beginChildren(void) const;
    inline MFNodePtrIt      beginChildren(void);

    inline MFNodePtrConstIt endChildren  (void) const;
    inline MFNodePtrIt      endChildren  (void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    /*---------------------------------------------------------------------*/
    /*! \name    Types                                                     */
    /*! \{                                                                 */

    class ChildrenListEntry
    {
      public:
        inline ChildrenListEntry(void                               );
        inline ChildrenListEntry(bool bActive, PriorityType priority);

        inline bool         getActive  (void                 ) const;
        inline void         setActive  (bool         bActive );

        inline PriorityType getPriority(void                 ) const;
        inline void         setPriority(PriorityType priority);

      private:
        bool         _bActive;
        PriorityType _priority;
    };

    typedef std::vector<ChildrenListEntry> ChildrenList;
    typedef ChildrenList::iterator         ChildrenListIt;
    typedef ChildrenList::const_iterator   ChildrenListConstIt;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    NodePtr      _pParentNode;
    UInt32       _uiNumActive;
    ChildrenList _children;
};

OSG_END_NAMESPACE

#include "OSGActiveChildrenList.inl"

#define OSGACTIVECHILDRENLIST_HEADER_CVSID "@(#)$Id: OSGActiveChildrenList.h,v 1.1 2004/04/20 13:47:08 neumannc Exp $"

#endif /* _OSGACTIVECHILDRENLIST_H_ */
