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

OSG_BEGIN_NAMESPACE

inline const IntersectActorBase::IntersectActorStateBase *
IntersectActorBase::getCastStatePtr(void) const
{
    return reinterpret_cast<const StateType *>(getState());
}

inline  IntersectActorBase::IntersectActorStateBase *
IntersectActorBase::getCastStatePtr(void)
{
    return reinterpret_cast<StateType *>(getState());
}

inline const Line &
IntersectActorBase::IntersectActorStateBase::getLine(void) const
{
    return _asLine;
}

inline Line &
IntersectActorBase::IntersectActorStateBase::getLine(void)
{
    return _asLine;
}
inline const Real32 &
IntersectActorBase::IntersectActorStateBase::getScaleFactor(void) const
{
    return _asScaleFactor;
}

inline Real32 &
IntersectActorBase::IntersectActorStateBase::getScaleFactor(void)
{
    return _asScaleFactor;
}

inline const Line &
IntersectActorBase::getLine(void) const
{
    this->emitStateRead();

    return getCastStatePtr()->getLine();
}

inline void
IntersectActorBase::setLine(const Line &stateVal)
{
    this->emitStateWrite();

    getCastStatePtr()->getLine() = stateVal;
}
inline const Real32 &
IntersectActorBase::getMaxDist(void) const
{
    return _asMaxDist;
}

inline void
IntersectActorBase::setMaxDist(const Real32 &stateVal)
{
    _asMaxDist = stateVal;
}
inline const Real32 &
IntersectActorBase::getScaleFactor(void) const
{
    this->emitStateRead();

    return getCastStatePtr()->getScaleFactor();
}

inline void
IntersectActorBase::setScaleFactor(const Real32 &stateVal)
{
    this->emitStateWrite();

    getCastStatePtr()->getScaleFactor() = stateVal;
}
inline const Real32 &
IntersectActorBase::getHitDist(void) const
{
    return _asHitDist;
}

inline void
IntersectActorBase::setHitDist(const Real32 &stateVal)
{
    _asHitDist = stateVal;
}
inline const NodePtr &
IntersectActorBase::getHitObject(void) const
{
    return _asHitObject;
}

inline void
IntersectActorBase::setHitObject(const NodePtr &stateVal)
{
    _asHitObject = stateVal;
}
inline const Int32 &
IntersectActorBase::getHitTriangle(void) const
{
    return _asHitTriangle;
}

inline void
IntersectActorBase::setHitTriangle(const Int32 &stateVal)
{
    _asHitTriangle = stateVal;
}
inline const bool &
IntersectActorBase::getHit(void) const
{
    return _asHit;
}

inline void
IntersectActorBase::setHit(const bool &stateVal)
{
    _asHit = stateVal;
}


OSG_END_NAMESPACE

#define OSGINTERSECTACTORBASE_INLINE_CVSID "@(#)$Id: OSGIntersectActorBase.inl,v 1.1 2003/10/10 13:51:07 neumannc Exp $"
