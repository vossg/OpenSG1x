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

inline const PrintNameActorBase::PrintNameActorStateBase *
PrintNameActorBase::getCastStatePtr(void) const
{
    return reinterpret_cast<const StateType *>(getState());
}

inline  PrintNameActorBase::PrintNameActorStateBase *
PrintNameActorBase::getCastStatePtr(void)
{
    return reinterpret_cast<StateType *>(getState());
}


inline const bool &
PrintNameActorBase::getPrintOnEnter(void) const
{
    return _asPrintOnEnter;
}

inline void
PrintNameActorBase::setPrintOnEnter(const bool &stateVal)
{
    _asPrintOnEnter = stateVal;
}
inline const bool &
PrintNameActorBase::getPrintOnLeave(void) const
{
    return _asPrintOnLeave;
}

inline void
PrintNameActorBase::setPrintOnLeave(const bool &stateVal)
{
    _asPrintOnLeave = stateVal;
}


OSG_END_NAMESPACE

#define OSGPRINTNAMEACTORBASE_INLINE_CVSID "@(#)$Id: OSGPrintNameActorBase.inl,v 1.1 2003/10/10 13:51:07 neumannc Exp $"
