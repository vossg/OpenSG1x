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

OSG_BEGIN_NAMESPACE

#ifdef OSG_NEWACTION_STATISTICS

//----------------------------------------------------------------------------
//    Statistics
//----------------------------------------------------------------------------

inline const StatCollector *
NewActionBase::getStatistics(void) const
{
    return _pStatistics;
}

inline StatCollector *
NewActionBase::getStatistics(void)
{
    return _pStatistics;
}

inline void
NewActionBase::setStatistics(StatCollector *pStatistics)
{
    _pStatistics = pStatistics;
}

#endif /* OSG_NEWACTION_STATISTICS */

//----------------------------------------------------------------------------
//    Traversal Mask
//----------------------------------------------------------------------------

/*! Return the traversal mask of this action. The action will only traverse
    a node if the bitwise AND of its traversal mask with the actions is nonzero.
 */

inline UInt32
NewActionBase::getTravMask(void) const
{
    return _travMask;
}

/*! Set the actions traversal maks. The action will only traverse a node if
    the bitwise AND of its traversal mask with the actions is nonzero.
 */

inline void
NewActionBase::setTravMask(UInt32 travMask)
{
    _travMask = travMask;
}

//----------------------------------------------------------------------------
//    ChildrenList/ExtraChildrenList Access
//----------------------------------------------------------------------------

/*! Return if the children list is enabled.
 */

inline bool
NewActionBase::getChildrenListEnabled(void) const
{
    return _childrenListEnabled;
}

/*! Enable or disable the children list.

\ext
    Actors should avoid enabling the children list without need as it has
    a negative impact on performance, e.g. if you do not want to traverse
    any children it is far more effective to return NewActionTypes::Skip
    instead of enabling the children list and setting all children inactive.
\endext
 */

inline void
NewActionBase::setChildrenListEnabled(bool enabled)
{
    if((enabled == true) && (_childrenListEnabled == false))
    {
        _childrenList.reset();
    }

    _childrenListEnabled = enabled;
}

/*! Return a const reference to the children list.

\ext
    ExtendActorBase and BasicActorBase have convenience functions for
    children management, use them instead of manipulating the list directly.
\endext
 */

inline const ChildrenList &
NewActionBase::getChildrenList(void) const
{
    return _childrenList;
}

/*! Return a reference to the children list.

\ext
    ExtendActorBase and BasicActorBase have convenience functions for
    children management, use them instead of manipulating the list directly.
\endext
 */

inline ChildrenList &
NewActionBase::getChildrenList(void)
{
    return _childrenList;
}

/*! Return a const reference to the extra children list.

\ext
    ExtendActorBase and BasicActorBase have convenience functions for extra
    children management, use them instead of manipulating the list directly.
\endext
 */

inline const ExtraChildrenList &
NewActionBase::getExtraChildrenList(void) const
{
    return _extraChildrenList;
}

/*! Return a reference to the children list.

\ext
    ExtendActorBase and BasicActorBase have convenience functions for extra
    children management, use them instead of manipulating the list directly.
\endext
 */

inline ExtraChildrenList &
NewActionBase::getExtraChildrenList(void)
{
    return _extraChildrenList;
}

//----------------------------------------------------------------------------
//    MultiPass Setup
//----------------------------------------------------------------------------

inline UInt32
NewActionBase::getNumPasses(void) const
{
    return _numPasses;
}

inline void
NewActionBase::setNumPasses(UInt32 numPasses)
{
    _numPasses = numPasses;
}

//----------------------------------------------------------------------------
//    Actor Access
//----------------------------------------------------------------------------

/*! Return a const iterator to the beginning of the extend actors.
 */

inline NewActionBase::ExtendActorStoreConstIt
NewActionBase::beginExtend(void) const
{
    return _extendActors.begin();
}

/*! Return an iterator to the beginning of the extend actors.
 */

inline NewActionBase::ExtendActorStoreIt
NewActionBase::beginExtend(void)
{
    return _extendActors.begin();
}

/*! Return a const iterator to the end of the extend actors.
 */

inline NewActionBase::ExtendActorStoreConstIt
NewActionBase::endExtend(void) const
{
    return _extendActors.end();
}

/*! Return an iterator to the end of the extend actors.
 */

inline NewActionBase::ExtendActorStoreIt
NewActionBase::endExtend(void)
{
    return _extendActors.end();
}

/*! Return a const iterator to the beginning of the basic actors.
 */

inline NewActionBase::BasicActorStoreConstIt
NewActionBase::beginBasic(void) const
{
    return _basicActors.begin();
}

/*! Return an iterator to the beginning of the basic actors.
 */

inline NewActionBase::BasicActorStoreIt
NewActionBase::beginBasic(void)
{
    return _basicActors.begin();
}

/*! Return a const iterator to the end of the basic actors.
 */

inline NewActionBase::BasicActorStoreConstIt
NewActionBase::endBasic(void) const
{
    return _basicActors.end();
}

/*! Return an iterator to the end of the basic actors.
 */

inline NewActionBase::BasicActorStoreIt
NewActionBase::endBasic(void)
{
    return _basicActors.end();
}

OSG_END_NAMESPACE

#define OSGNEWACTIONBASE_INLINE_CVSID "@(#)$Id: OSGNewActionBase.inl,v 1.3 2004/09/17 14:09:43 neumannc Exp $"
