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

#ifndef _OSGQTYPEDFIELDVALUELABEL_H_
#define _OSGQTYPEDFIELDVALUELABEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGQTWidgetDef.h"
#include "OSGQFieldValueLabel.h"

OSG_BEGIN_NAMESPACE

/*! \brief Flyweight label template, which can be specialized for different 
 *  field types.
 */

template <class FieldContentsTypeT>
class OSG_QTWIDGETLIB_DLLTMPLMAPPING QTypedFieldValueLabel : 
    public QGenericFieldValueLabel
{
public:
    typedef FieldContentsTypeT      FieldContentsType;

private:
    typedef QGenericFieldValueLabel Inherited;
};

OSG_END_NAMESPACE

#define OSGQTYPEDFIELDVALUELABEL_HEADER_CVSID "@(#)$Id: OSGQTypedFieldValueLabel.h,v 1.3 2003/05/19 07:36:41 neumannc Exp $"

// #include "OSGQTypedFieldValueLabel.inl"

#endif /* _OSGQTYPEDFIELDVALUELABEL_H_ */
