/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#define OSG_COMPILEGEOMETRY

#include <OSGGeometryBase.h>

#include <OSGLog.h>

#include "OSGSimpleGeometry.h"
#include "OSGGeometry.h"

OSG_USING_NAMESPACE

/** \enum VecBase::VectorSizeE
 *  \brief 
 */

/** \var VecBase::VectorSizeE VecBase::_iSize
 * 
 */

/** \fn const char *VecBase::getClassname(void)
 *  \brief Classname
 */

/** \var ValueTypeT VecBase::_values[iSize];
 *  \brief Value store
 */

#ifdef __sgi
#pragma set woff 1174
#endif

static char cvsid[] = "@(#)$Id: $";

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_GEOMETRY_DLLMAPPING
NodePtr OSG::makePlane( Real32 xsize, Real32 ysize, UInt16 hor, UInt16 vert )
{
	GeoPosition3fPtr		pnts  = GeoPosition3f::create();
	GeoNormal3fPtr		norms = GeoNormal3f::create();
	GeoIndexUI32Ptr		index = GeoIndexUI32::create();	
	GeoPLengthPtr		lens  = GeoPLength::create();	
	GeoPTypePtr			types = GeoPType::create();	
	
	UInt16 x,y;
	Real32 xstep,ystep;
	xstep = xsize / hor;
	ystep = ysize / vert;

	// calc the vertices

	GeoPosition3f::FieldType * p = pnts->getFieldPtr();
	GeoNormal3f::FieldType   * n = norms->getFieldPtr();

	osgBeginEditCP(pnts);
	osgBeginEditCP(norms);
	
	for ( y = 0; y <= vert; y++ )
	{
		for ( x = 0; x <= hor; x++ )
		{
			p->addValue( Pnt3f( x * xstep - xsize / 2, y * ystep - ysize / 2, 0 ) );
			n->addValue( Vec3f( 0, 0, 1) );
		}
	}

	osgEndEditCP(pnts);
	osgEndEditCP(norms);

	// create the faces
	
	GeoIndexUI32::FieldType * i = index->getFieldPtr();
	GeoPLength::FieldType   * l = lens->getFieldPtr();
	GeoPType::FieldType     * t = types->getFieldPtr();

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
	
    GeometryPtr geo = Geometry::create();

 	osgBeginEditCP(geo);
	geo->setPositions( pnts );
	geo->setNormals( norms );
	geo->setNormalPerVertex( true );
	geo->setIndex( index );
	geo->setTypes( types );
	geo->setLengths( lens );
	osgEndEditCP(geo);
		
    NodePtr node = Node::create();
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

