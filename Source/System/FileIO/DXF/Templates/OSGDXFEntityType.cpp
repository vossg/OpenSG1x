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

#include "OSGDXFentityname.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class DXFentityname
    \ingroup GrpSystemFileIO

  Parses and dispatches the file section between the groups (0,SECTION),
  (2,ENTITYNAME) and (0,ENDSEC). entityname subsections are dispatched to
  DXF???.

  ------ YOU MAY USE THE PREVIOUS OR THE FOLLOWING COMMENT PARAGRAPH --------

  Parses and evaluates the file subsection inside a ENTITYNAME between the
  group (0,ENTITYNAME) and any other group with group code 0.

 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/*! \enum DXFentityname::ENUMNAME
  
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/*! Pointer to singleton of this class. There is exactly one instance for each
 * derived class which can be instantiated.
 */
DXFentityname *DXFentityname::_the = new DXFentityname();

/* \var VARTYPE DXFentityname::_VARNAME
    variable documentation
 */

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

/*================================ PRIVATE ================================*/

/*! Evalute records for ENTITYNAME with the following group codes:
 * - X -- (currently none)
 */
DXFResult DXFentityname::evalRecord(void)
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

/*! Clear internal data.
 */
DXFResult DXFentityname::beginEntity(void)
{
	DXFResult state;
	state = Inherited::beginEntity();
	
	// clear own data here

	return state;
}

/*! Create ... from fetched data.
 */
DXFResult DXFentityname::endEntity(void)
{
	return DXFStateContinue;
}

/*-------------------------------------------------------------------------*/

/*------------------------- constructors ----------------------------------*/

/*! Add ENTITYCLASSNAME:ENTITYNAME entity type to DXF hierarchy as child of
 *  _DXFPARENTCLASS_:_DXFPARENT_ (see DXFparent).
 */
DXFentityname::DXFentityname(void) :
    Inherited()
{
	_entityClassName   = "ENTITYCLASSNAME"; // Remove, if set by parentclass
	_entityTypeName    = "ENTITYNAME";

	_childBeginKeyword = "_LEVEL_";		// Remove if not needed
	_childEndKeyword   = "_ENDLVL_";	// Remove if not needed

	registerToParentEntityType("_DXFPARENTCLASS_:_DXFPARENT_");
}

/*-------------------------- destructor -----------------------------------*/

/*! Does nothing.
 */
DXFentityname::~DXFentityname(void)
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
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGDXFEntityType.cpp,v 1.1 2004/02/19 16:45:44 a-m-z Exp $";
    static Char8 cvsid_hpp[] = OSGDXFENTITYNAME_HEADER_CVSID;
//    static Char8 cvsid_inl[] = OSGDXFENTITYNAME_INLINE_CVSID;
}

