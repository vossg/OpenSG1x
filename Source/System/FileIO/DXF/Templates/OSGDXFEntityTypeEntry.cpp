/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2003 by the OpenSG Forum                 *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGDXFentityentryname.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class DXFentityentryname
    \ingroup GrpSystemFileIO

  This class implements the evaluation of group codes common for all entries
  of the ENTITYTYPENAME-ENTRY sections.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/*! \enum DXFentityentryname::ENUMNAME
  
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*================================ PUBLIC =================================*/

/*=============================== PROTECTED ===============================*/

/*================================ PRIVATE ================================*/


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*================================ PUBLIC =================================*/

/*=============================== PROTECTED ===============================*/

/*! Evaluate records for all entities inside ENTITYENTRYNAME - ENTRY structures
 *  with the follwing codes:
 *  - X -- (currently none)
 */

DXFResult DXFentityentryname::evalRecord(void)
{
	DXFResult state = DXFStateContinue;
	switch( DXFRecord::getGroupCode() )
	{
		default:
			state = DXFStateUnknown;
	}
	if(state == DXFStateUnknown)
		state == Inherited::evalRecord(); // don't remove this!
	return state;
}

DXFResult DXFentityentryname::beginEntity(void)
{	
	DXFResult state;
	state = Inherited::beginEntity();

	return state;
}


/*================================ PRIVATE ================================*/

/*-------------------------------------------------------------------------*/

/*------------------------- constructors ----------------------------------*/

/*! Define derived entity types as of class ENTITYCLASSNAME.
 */
DXFentityentryname::DXFentityentryname(void) :
    Inherited()
{
	_entityClassName = "ENTITYCLASSNAME";
}

/*-------------------------- destructor -----------------------------------*/

/*! Does nothing.
 */
DXFentityentryname::~DXFentityentryname(void)
{
}

/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGDXFEntityTypeEntry.cpp,v 1.1 2004/02/19 16:45:44 a-m-z Exp $";
    static Char8 cvsid_hpp[] = OSGDXFENTITYENTRYNAME_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGDXFENTITYENTRYNAME_INLINE_CVSID;
}

