/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
 *                                                                           *
 *          contact: {reiners|vossg}@igd.fhg.de, jbehr@zgdv.de               *
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

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <OSGLog.h>

#include "OSGSimpleGeometry.h"
#include "OSGGeometry.h"

OSG_USING_NAMESPACE

/** \enum OSGVecBase::VectorSizeE
 *  \brief 
 */

/** \var OSGVecBase::VectorSizeE OSGVecBase::_iSize
 * 
 */

/** \fn const char *OSGVecBase::getClassname(void)
 *  \brief Classname
 */

/** \var OSGValueTypeT OSGVecBase::_values[iSize];
 *  \brief Value store
 */

#ifdef __sgi
#pragma set woff 1174
#endif

static char cvsid[] = "@(#)$Id: $";

#ifdef __sgi
#pragma reset woff 1174
#endif

OSGNodePtr OSG::osgMakePlane( OSGReal32 xsize, OSGReal32 ysize, OSGUInt16 hor, OSGUInt16 vert )
{
	OSGGeoPosition3fPtr		pnts  = OSGGeoPosition3f::create();
	OSGGeoNormal3fPtr		norms = OSGGeoNormal3f::create();
	OSGGeoIndexUI32Ptr		index = OSGGeoIndexUI32::create();	
	OSGGeoPLengthPtr		lens  = OSGGeoPLength::create();	
	OSGGeoPTypePtr			types = OSGGeoPType::create();	
	
	OSGUInt16 x,y;
	OSGReal32 xstep,ystep;
	xstep = xsize / hor;
	ystep = ysize / vert;

	// calc the vertices

	OSGGeoPosition3f::OSGFieldType * p = pnts->getFieldPtr();
	OSGGeoNormal3f::OSGFieldType   * n = norms->getFieldPtr();

	osgBeginEditCP(pnts);
	osgBeginEditCP(norms);
	
	for ( y = 0; y <= vert; y++ )
	{
		for ( x = 0; x <= hor; x++ )
		{
			p->addValue( OSGPnt3f( x * xstep - xsize / 2, y * ystep - ysize / 2, 0 ) );
			n->addValue( OSGVec3f( 0, 0, 1) );
		}
	}

	osgEndEditCP(pnts);
	osgEndEditCP(norms);

	// create the faces
	
	OSGGeoIndexUI32::OSGFieldType * i = index->getFieldPtr();
	OSGGeoPLength::OSGFieldType   * l = lens->getFieldPtr();
	OSGGeoPType::OSGFieldType     * t = types->getFieldPtr();

	osgBeginEditCP(index);
	osgBeginEditCP(lens);
	osgBeginEditCP(types);

	for ( y = 0; y < vert; y++ )
	{
		t->addValue( GL_TRIANGLE_STRIP );
		l->addValue( 2 * ( hor + 1 ) );
		
		for ( x = 0; x <= hor; x++ )
		{
			i->addValue(   y      * ( hor + 1 ) + x );
			i->addValue( ( y + 1) * ( hor + 1 ) + x );
		}
	}

	osgEndEditCP(index);
	osgEndEditCP(lens);
	osgEndEditCP(types);
	
	// create the geometry
	
    OSGGeometryPtr geo = OSGGeometry::create();

 	osgBeginEditCP(geo);
	geo->setPositions( pnts );
	geo->setNormals( norms );
	geo->setNormalPerVertex( true );
	geo->setIndex( index );
	geo->setTypes( types );
	geo->setLengths( lens );
	osgEndEditCP(geo);
		
    OSGNodePtr node = OSGNode::create();
	osgBeginEditCP(node);
	node->setCore( geo );
	osgEndEditCP(node);
	
	return node;
}


///---------------------------------------------------------------------------
///  FUNCTION: 
///---------------------------------------------------------------------------
//:  Example for the head comment of a function
///---------------------------------------------------------------------------
///
//p: Paramaters: 
//p: 
///
//g: GlobalVars:
//g: 
///
//r: Return:
//r: 
///
//c: Caution:
//c: 
///
//a: Assumptions:
//a: 
///
//d: Description:
//d: 
///
//s: SeeAlso:
//s: 
///---------------------------------------------------------------------------

