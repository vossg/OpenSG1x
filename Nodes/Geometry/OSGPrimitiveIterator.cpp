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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"
#include "OSGNodePtr.h"
#include "OSGPrimitiveIterator.h"

OSG_USING_NAMESPACE



/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \defgroup GeoIterators OpenSG Geometry Iterators
    \ingroup GeometryLib

Access to Geometry is complicated by its flexibility and the fact that it is
somewhat heavily OpenGL-centric.

The GeoIterators simplify this access by putting an iterator interface on top 
of the Geometry that provides access to single primitives, i.e. single
stripes, polygons, lines etc. and allow access to the primitive's
attributes independent of it's actual representation. Thus it is
posssible to access the color of a specific vertex of a specific
primitive no matter if it's indexed or not and what type it has.

*/

/*! \class osg::PrimitiveIterator

The PrimitiveIterator is the highest level iterator and splits the
primitives of the geometry into single primitives. It also abstracts
away the indexing and types of the attributes.

For finer-level iterators see \sa FaceIterator \sa TriangleIterator.

*/


/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char PrimitiveIterator::cvsid[] = "@(#)$Id: OSGPrimitiveIterator.cpp,v 1.25 2002/09/03 09:15:09 vossg Exp $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/



/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

PrimitiveIterator::PrimitiveIterator(void) :
    _geo           (      ), 
    _ended         (  true),
    _primIndex     (     0), 
    _actPointIndex (     0),
    _actPrimType   (     0), 
    _actPrimLength (     0),
    _types         (NullFC), 
    _lengths       (NullFC), 
    _indices       (NullFC), 
    _nmappings     (     0),
    _positionIndex (    -1), 
    _normalIndex   (    -1), 
    _colorIndex    (    -1), 
    _texcoordsIndex(    -1) 
{
}

PrimitiveIterator::PrimitiveIterator( const GeometryPtr& geo ) :
    _geo           (      ), 
    _ended         (  true),
    _primIndex     (     0), 
    _actPointIndex (     0),
    _actPrimType   (     0), 
    _actPrimLength (     0),
    _types         (NullFC), 
    _lengths       (NullFC), 
    _indices       (NullFC), 
    _nmappings     (     0),
    _positionIndex (    -1), 
    _normalIndex   (    -1), 
    _colorIndex    (    -1), 
    _texcoordsIndex(    -1) 
{
    setGeo(geo);
}

PrimitiveIterator::PrimitiveIterator( const NodePtr& geo ) :
    _geo           (      ), 
    _ended         (  true),
    _primIndex     (     0), 
    _actPointIndex (     0),
    _actPrimType   (     0), 
    _actPrimLength (     0),
    _types         (NullFC), 
    _lengths       (NullFC), 
    _indices       (NullFC), 
    _nmappings     (     0),
    _positionIndex (    -1), 
    _normalIndex   (    -1), 
    _colorIndex    (    -1), 
    _texcoordsIndex(    -1) 
{
    setGeo( geo );
}


PrimitiveIterator::PrimitiveIterator(const PrimitiveIterator &source) :
    _geo           (source._geo           ),
    _ended         (source._ended         ),
    _primIndex     (source._primIndex     ), 
    _actPointIndex (source._actPointIndex ),
    _actPrimType   (source._actPrimType   ), 
    _actPrimLength (source._actPrimLength ),  
    _types         (source._types         ), 
    _lengths       (source._lengths       ), 
    _indices       (source._indices       ), 
    _nmappings     (source._nmappings     ),
    _positionIndex (source._positionIndex ),
    _normalIndex   (source._normalIndex   ),
    _colorIndex    (source._colorIndex    ),
    _texcoordsIndex(source._texcoordsIndex)
    
{
}

/** \brief Destructor
 */

PrimitiveIterator::~PrimitiveIterator(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

void PrimitiveIterator::setGeo( const GeometryPtr& geo )
{
    _geo = geo;
    _types = geo->getTypes();
    _lengths = geo->getLengths();
    _indices = geo->getIndices();
    
    setToBegin();
}

void PrimitiveIterator::setGeo( const NodePtr& geo )
{
    setGeo(GeometryPtr::dcast(geo->getCore()));
}

/** \brief increment
 */

void PrimitiveIterator::operator++ ()
{
    if ( isAtEnd() )
    {
        return;
    }

    _actPointIndex += _actPrimLength;
    
    ++_primIndex;

    if ( _primIndex >= _types->getSize() )
    {
        _ended = true;
    }
    else
    {
        _actPrimType = _types->getValue( _primIndex );
        if(_lengths != NullFC)
        {
            _actPrimLength = _lengths->getValue( _primIndex );
        }
        else if(_indices != NullFC)
        {
            _actPrimLength = _indices->getSize() / _nmappings;
        }
        else
        {
            _actPrimLength = _geo->getPositions()->getSize() / _nmappings;
        }
    }
}

void PrimitiveIterator::setToBegin( void )
{
    _primIndex = 0;
    _actPointIndex = 0;
    _ended = false;
    _nmappings      = _geo->getIndexMapping().size();
    _positionIndex  = _geo->calcMappingIndex( Geometry::MapPosition );
    _normalIndex    = _geo->calcMappingIndex( Geometry::MapNormal );
    _colorIndex     = _geo->calcMappingIndex( Geometry::MapColor );
    _texcoordsIndex = _geo->calcMappingIndex( Geometry::MapTexCoords );

    if ( _nmappings == 0 )
        _nmappings = 1;
                  
    if ( _types != NullFC && _types->getSize() > 0 )
    {
        _actPrimType = _types->getValue( _primIndex );
        if(_lengths != NullFC)
        {
            _actPrimLength = _lengths->getValue( _primIndex );
        }
        else if(_indices != NullFC)
        {
            _actPrimLength = _indices->getSize() / _nmappings;
        }
        else
        {
            _actPrimLength = _geo->getPositions()->getSize() / _nmappings;
        }
    }
    else
    {
        setToEnd();
    }
}

void PrimitiveIterator::setToEnd( void )
{
    if ( _types != NullFC )
        _primIndex = _types->getSize();
    else
        _primIndex = 0;
    _actPointIndex = 0;
    _ended = true;
}

void PrimitiveIterator::seek( Int32 index )
{   
    _actPointIndex = 0;
    _ended = false;

    if ( index >= _types->getSize() )
    {
        _primIndex = _types->getSize();
        _ended = true;
    }
    else
    {
        _primIndex = osgMax(0, index);   
        
        for ( UInt32 j = 0; j < _primIndex; j++ )
            _actPointIndex += _lengths->getValue( j );
            
        _actPrimType = _types->getValue( _primIndex );
        _actPrimLength = _lengths->getValue( _primIndex );
    }
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

PrimitiveIterator& PrimitiveIterator::operator = (const PrimitiveIterator &source)
{
    if (this == &source)
        return *this;

    // free mem alloced by members of 'this'

    // alloc new mem for members

    // copy 
    
    this->_geo                  = source._geo;
    this->_primIndex        = source._primIndex;
    this->_actPrimType          = source._actPrimType;
    this->_actPrimLength    = source._actPrimLength;
    this->_actPointIndex    = source._actPointIndex;
    this->_types            = source._types;
    this->_lengths              = source._lengths;
    this->_indices              = source._indices;
    this->_ended            = source._ended;
    this->_nmappings        = source._nmappings;
    this->_positionIndex        = source._positionIndex;
    this->_normalIndex          = source._normalIndex;
    this->_colorIndex       = source._colorIndex;
    this->_texcoordsIndex       = source._texcoordsIndex;

    return *this;
}

/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */

bool PrimitiveIterator::operator < (const PrimitiveIterator &other) const
{
    return _geo == other._geo &&
           _primIndex <= other._primIndex;
}

/** \brief equal
 */

bool PrimitiveIterator::operator == (const PrimitiveIterator &other) const
{
    return _ended == other._ended &&
            _geo == other._geo &&
            _primIndex == other._primIndex;
}

/** \brief unequal
 */

bool PrimitiveIterator::operator != (const PrimitiveIterator &other) const
{
    return ! (*this == other);
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



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

