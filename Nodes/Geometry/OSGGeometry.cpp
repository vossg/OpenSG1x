/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#define OSG_COMPILESYSTEMLIB

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"
#include <GL/gl.h>

#include <OSGAction.h>
#include <OSGDrawAction.h>
#include <OSGIntersectAction.h>
#include <OSGMaterial.h>
#include "OSGGeometry.h"
#include "OSGGeoPumpFactory.h"

#include "OSGPrimitiveIterator.h"
#include "OSGTriangleIterator.h"
#include "OSGFaceIterator.h"

#include "OSGGeoPropPtrs.h"
OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \defgroup GeometryLib
	\ingroup NodeCores

The basic polygonal geometry library.

*/

/*! \class osg::Geometry

The base class for all Geometry node types. Defines the common interface
for all geometry, so for general tools use these interfaces. They are pretty general
and minimal though, so don't expect them to be blindingly fast.

*/

OSG_SYSTEMLIB_DLLMAPPING GeometryPtr OSG::NullGeo;

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char Geometry::cvsid[] = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

const char *Geometry::mapType( UInt8 type )
{
	switch ( type )
	{
	case GL_POINTS: 		return "Points";
	case GL_LINES: 			return "Lines";
	case GL_LINE_LOOP: 		return "LineLoop";
	case GL_LINE_STRIP: 	return "LineStrip";
	case GL_TRIANGLES: 		return "Triangles";
	case GL_TRIANGLE_STRIP: return "TriangleStrip";
	case GL_TRIANGLE_FAN: 	return "TriangleFan";
	case GL_QUADS: 			return "Quads";
	case GL_QUAD_STRIP:  	return "QuadStrip";
	case GL_POLYGON: 		return "Polygon";
	}
	
	return "Unknown Primitive";
}
	
/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/** \brief initialize the static features of the class, e.g. action callbacks
 */

void Geometry::initMethod (void)
{
	DrawAction::registerEnterDefault( getClassType(), 
		osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
								CNodePtr,  
								GeometryPtr, 
								Action *>(&Geometry::doDraw));

	IntersectAction::registerEnterDefault( getClassType(), 
		osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
								CNodePtr,  
								GeometryPtr, 
								Action *>(&Geometry::intersect));
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

Geometry::Geometry(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

Geometry::Geometry(const Geometry &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

Geometry::~Geometry(void)
{
}

/*------------------------------ access -----------------------------------*/

void Geometry::adjustVolume( Volume & volume )
{
    GeoPositionPtr pos = getPositions();

	if ( pos == NullFC )
		return;				// Node has no points, no volume
	
	volume.setValid();
	volume.setEmpty();
	
	for ( int i = 0; i < pos->getSize(); i++ )
	{
		Vec3f p;
		pos->getValue( p, i );
		
		volume.extendBy( p );
	}
}

/*---------------------------- pointer ------------------------------------*/

GeometryPtr Geometry::getPtr(void) const
{
    return FieldContainer::getPtr<GeometryPtr>(*this);
}


/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void Geometry::dump(      UInt32     uiIndent, 
                         const BitVector &bvFlags) const
{
   Inherited::dump(uiIndent, bvFlags);
}

    

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/** \brief Actions
 */
	
Action::ResultE Geometry::doDraw(Action * action )
{
	DrawAction *a = dynamic_cast<DrawAction*>(action);

  if(a->getMaterial() != NULL)
  {
    a->getMaterial()->draw(this, a);
  }
  else if ( getMaterial() != NullFC )
  {
		getMaterial()->draw( this, a );
  }
	else
  {
		draw( a );
  }
	return Action::Continue;
}
	
Action::ResultE Geometry::draw(DrawAction * action )
{
	GeoPumpFactory::Index ind = GeoPumpFactory::the().getIndex( this );
	GeoPumpFactory::Pump p = GeoPumpFactory::the().getPump( action, ind );

	// call the pump

	if ( p )
		p( action, this );
	else
	{
		SWARNING << "draw: no Pump found for geometry " << this << endl;
	}
	
	return Action::Continue;
}

Action::ResultE Geometry::intersect(Action * action )
{ 
	IntersectAction * ia = dynamic_cast<IntersectAction*>(action);

	TriangleIterator it;
	Real32 t;
	
	for ( it = this->beginTriangles(); it != this->endTriangles(); ++it )
	{
		if ( ia->getLine().intersect( 	it.getPosition(0), 
										it.getPosition(1),
										it.getPosition(2), t ) )
		{
			ia->setHit( t, ia->getActNode(), it.getIndex() );
		}
	}
	
	return Action::Continue; 
}




/** \brief react to field changes
 */

void Geometry::changed(BitVector whichField, ChangeMode from)
{
    UInt32 i;

    if(whichField & PositionsFieldMask)
    {
        for(i = 0; i < _parents.size(); i++)
        {
            _parents[i]->invalidateVolume();
        }            
    }
}

    
/** Triangle iterator functions */
    

TriangleIterator Geometry::beginTriangles( void ) const
{
	TriangleIterator it( this->getPtr() );

	it.setToBegin();
	
	return it;
}


TriangleIterator Geometry::endTriangles  ( void ) const
{
	TriangleIterator it( this->getPtr() );

	it.setToEnd();
	
	return it;
}
    
/** Primitive iterator functions */
    

PrimitiveIterator Geometry::beginPrimitives( void ) const
{
	PrimitiveIterator it( this->getPtr() );

	it.setToBegin();
	
	return it;
}


PrimitiveIterator Geometry::endPrimitives  ( void ) const
{
	PrimitiveIterator it( this->getPtr() );

	it.setToEnd();
	
	return it;
}
    
/** Face iterator functions */
    

FaceIterator Geometry::beginFaces( void ) const
{
	FaceIterator it( this->getPtr() );

	it.setToBegin();
	
	return it;
}


FaceIterator Geometry::endFaces  ( void ) const
{
	FaceIterator it( this->getPtr() );

	it.setToEnd();
	
	return it;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

