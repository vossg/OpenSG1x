/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000-2002,2002 by the OpenSG Forum                *
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

#ifndef _OSGFIELDCONTAINERTYPEDEPIMPL_INL_
#define _OSGFIELDCONTAINERTYPEDEPIMPL_INL_

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGFieldContainerTypeDepImpl.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                           Prototype                                     */

inline
FieldContainerPtr FieldContainerType::getPrototype(void) const
{
    return _pPrototype;
}

inline
bool FieldContainerType::setPrototype(FieldContainerPtr pPrototype)
{
    bool returnValue = false;

    if(pPrototype != NullFC)
    {
        setRefdCP(_pPrototype, pPrototype);
        returnValue = true;
    }

    return returnValue;
}

inline
bool FieldContainerType::isAbstract(void) const
{
    return (_pPrototype != NullFC) ? false : true;

}

OSG_END_NAMESPACE

#define OSGFIELDCONTAINERTYPEDEPIMPL_INLINE_CVSID "@(#)$Id: $"

#endif /* _OSGFIELDCONTAINERTYPEDEPIMPL_INL_ */
