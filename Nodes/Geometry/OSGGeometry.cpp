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

    
const UInt16 Geometry::MapPosition   = 1;
const UInt16 Geometry::MapNormal     = Geometry::MapPosition << 1;
const UInt16 Geometry::MapColor      = Geometry::MapNormal << 1;
const UInt16 Geometry::MapTexcoords  = Geometry::MapColor << 1;
const UInt16 Geometry::MapTexcoords2 = Geometry::MapTexcoords << 1;
const UInt16 Geometry::MapTexcoords3 = Geometry::MapTexcoords2 << 1;
const UInt16 Geometry::MapTexcoords4 = Geometry::MapTexcoords3 << 1;
const UInt16 Geometry::MapEmpty      = Geometry::MapTexcoords4 << 1;

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

#ifdef OSG_NOFUNCTORS
OSG::Action::ResultE Geometry::GeoDrawEnter(CNodePtr &cnode, 
                                            Action  *pAction)
{
    NodeCore *pNC = cnode.getCPtr();
    Geometry *pSC = dynamic_cast<Geometry *>(pNC);

    if(pSC == NULL)
    {
        fprintf(stderr, "GEDE: core NULL\n");
        return Action::Skip;
    }
    else
    {
        return pSC->doDraw(pAction);
    }
}

OSG::Action::ResultE Geometry::GeoIntEnter(CNodePtr &cnode, 
                                           Action  *pAction)
{
    NodeCore *pNC = cnode.getCPtr();
    Geometry *pSC = dynamic_cast<Geometry *>(pNC);

    if(pSC == NULL)
    {
        fprintf(stderr, "GEIE: core NULL\n");
        return Action::Skip;
    }
    else
    {
        return pSC->intersect(pAction);
    }
}
#endif

void Geometry::initMethod (void)
{
#ifndef OSG_NOFUNCTORS
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
#else

    DrawAction::registerEnterDefault(getClassType(), 
                                     Action::osgFunctionFunctor2(
                                        Geometry::GeoDrawEnter));

    IntersectAction::registerEnterDefault(getClassType(), 
                                     Action::osgFunctionFunctor2(
                                        Geometry::GeoIntEnter));

#endif
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

/** \brief instance initialization
 */

void Geometry::onCreate( const FieldContainer & )
{
	// !!! this temporary is needed to work around compiler problems (sgi)
	// CHECK CHECK
	//	TextureChunkPtr tmpPtr = FieldContainer::getPtr<TextureChunkPtr>(*this);
	GeometryPtr tmpPtr(*this);

	beginEditCP( tmpPtr, Geometry::GLIdFieldMask );
#ifndef OSG_NOFUNCTORS
	setGLId( Window::registerGLObject( 
						osgMethodFunctor2CPtr<
										void,
										Window*,
										UInt32,
										GeometryPtr
										>( tmpPtr, &Geometry::handleGL ), 1 
	)                         );
#else
	setGLId(Window::registerGLObject( 
						osgMethodFunctor2CPtr(tmpPtr, 
                                              &Geometry::handleGL), 
                    1));
#endif
	endEditCP( tmpPtr, Geometry::GLIdFieldMask );
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
    return GeometryPtr(*this);
}


// GL object handler
// put the geometry into a display list
void Geometry::handleGL( Window* win, UInt32 id )
{
	Window::GLObjectStatusE mode = win->getGLObjectStatus( id );
	
	if ( mode == Window::initialize || mode == Window::needrefresh )
	{		
   	    glNewList( id, GL_COMPILE );
		
		GeoPumpFactory::Index ind = GeoPumpFactory::the().getIndex( this );
		GeoPumpFactory::GeoPump p = 
		    GeoPumpFactory::the().getGeoPump( win, ind );

		// call the pump

		if ( p )
			p( win, this );
		else
		{
			SWARNING << "Geometry::handleGL: no Pump found for geometry " << this << endl;
		}
		
		glEndList();
	}
	else if ( mode == Window::destroy )
	{
		glDeleteLists( id, 1 );
	}
	else if ( mode == Window::finaldestroy )
	{
		//SWARNING << "Last geometry user destroyed" << endl;
	}
	else
	{
		SWARNING << "Geometry(" << this << "::handleGL: Illegal mode: " 
			 << mode << " for id " << id << endl;
	}
	
}

/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void Geometry::dump(      UInt32     uiIndent, 
                         const BitVector &bvFlags) const
{
   Inherited::dump(uiIndent, bvFlags);
}


/*------------------------------- dump ----------------------------------*/

/** \brief calc the indices into the index field for the given attributes
 */

Int16  Geometry::calcMappingIndex( UInt16 attrib ) const
{
    const UInt16 *mappings = &getIndexMapping().getValues()[0];
    UInt16 nmappings = getIndexMapping().size();
    
    int i;
    for ( i = nmappings-1; i >= 0; i-- )
    {
	if ( mappings[i] & attrib  ) 
	    break;
    }   
    
    return i;
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
	if ( getDlistCache() == true )
	{
		action->getWindow()->validateGLObject( getGLId() );
		glCallList( getGLId() );
	}
	else
	{
		GeoPumpFactory::Index ind = GeoPumpFactory::the().getIndex( this );
		GeoPumpFactory::GeoPump p = 
	    	GeoPumpFactory::the().getGeoPump( action->getWindow(), ind );

		// call the pump

		if ( p )
			p( action->getWindow(), this );
		else
		{
			SWARNING << "draw: no Pump found for geometry " << this << endl;
		}
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
	// invalidate the dlist cache
	Window::refreshGLObject( getGLId() );
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

