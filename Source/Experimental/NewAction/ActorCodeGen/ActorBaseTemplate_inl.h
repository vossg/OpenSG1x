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

inline const @!Classname!@Base::@!Classname!@StateBase *
@!Classname!@Base::getCastStatePtr(void) const
{
    return reinterpret_cast<const StateType *>(getState());
}

inline  @!Classname!@Base::@!Classname!@StateBase *
@!Classname!@Base::getCastStatePtr(void)
{
    return reinterpret_cast<StateType *>(getState());
}

@@BeginStateLoop@@
@@if StateElemIsOrdered
inline const @!StateElemType!@ &
@!Classname!@Base::@!Classname!@StateBase::get@!StateElemName!@(void) const
{
    return _as@!StateElemName!@;
}

inline @!StateElemType!@ &
@!Classname!@Base::@!Classname!@StateBase::get@!StateElemName!@(void)
{
    return _as@!StateElemName!@;
}
@@endif
@@EndStateLoop@@

@@BeginStateLoop@@
@@if StateElemIsPublic
@@if !StateElemIsOrdered
inline const @!StateElemType!@ &
@!Classname!@Base::get@!StateElemName!@(void) const
{
    return _as@!StateElemName!@;
}

inline void
@!Classname!@Base::set@!StateElemName!@(const @!StateElemType!@ &stateVal)
{
    _as@!StateElemName!@ = stateVal;
}
@@else
inline const @!StateElemType!@ &
@!Classname!@Base::get@!StateElemName!@(void) const
{
    this->emitStateRead();

    return getCastStatePtr()->get@!StateElemName!@();
}

inline void
@!Classname!@Base::set@!StateElemName!@(const @!StateElemType!@ &stateVal)
{
    this->emitStateWrite();

    getCastStatePtr()->get@!StateElemName!@() = stateVal;
}
@@endif
@@endif
@@EndStateLoop@@

@@BeginStateLoop@@
@@if StateElemIsProtected
@@if !StateElemIsOrdered
inline const @!StateElemType!@ &
@!Classname!@Base::get@!StateElemName!@(void) const
{
    return _as@!StateElemName!@;
}

inline void
@!Classname!@Base::set@!StateElemName!@(const @!StateElemType!@ &stateVal)
{
    _as@!StateElemName!@ = stateVal;
}
@@else
inline const @!StateElemType!@ &
@!Classname!@Base::get@!StateElemName!@(void) const
{
    this->emitStateRead();

    return getCastStatePtr()->get@!StateElemName!@();
}

inline void
@!Classname!@Base::set@!StateElemName!@(const @!StateElemType!@ &stateVal)
{
    this->emitStateWrite();

    getCastStatePtr()->get@!StateElemName!@() = stateVal;
}
@@endif
@@endif
@@EndStateLoop@@

OSG_END_NAMESPACE

#define OSG@!CLASSNAME!@BASE_INLINE_CVSID "@(#)$Id: ActorBaseTemplate_inl.h,v 1.1 2003/10/10 13:51:07 neumannc Exp $"
