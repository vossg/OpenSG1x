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

#include "OSGFaceIterator.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::FaceIterator

The FaceIterator iterates through the geometry one face at a time. A
face in this case is a triangle or quad. Larger primtitives like strips
are automatically split into triangles and quads, non-polygonal
primitives like lines and points are ignored.

Only quad-based primitives (Quadstrips and Quads) are split into quads, 
everything else is split into triangles. Testing if a polygon is a quad
is just too expensive and rarely useful.

\sa PrimitiveIterator TriangleIterator

*/


/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char FaceIterator::cvsid[] = "@(#)$Id: OSGFaceIterator.cpp,v 1.13 2001/11/01 09:03:28 vossg Exp $";

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

FaceIterator::FaceIterator(void) : 
    _primIt(), _geo(),
    _faceIndex(0), _actPrimIndex(), _facePntIndex()
{
}

FaceIterator::FaceIterator(const FaceIterator &source) :
    _primIt( source._primIt ), 
    _geo( source._geo ),
    _faceIndex(source._faceIndex),
    _actPrimIndex(source._actPrimIndex),
    _facePntIndex()
{
    _facePntIndex[0] = source._facePntIndex[0];
    _facePntIndex[1] = source._facePntIndex[1];
    _facePntIndex[2] = source._facePntIndex[2];
    _facePntIndex[3] = source._facePntIndex[3];
}

/*! 
These constructors create an iterator for the given geometry/node.
They are useful to create an iterator to be used to seek() to a specific
indexed face. Otherwise, use Geometry::beginFaces() resp. Geometry::endFaces()
to create an iterator.
*/

FaceIterator::FaceIterator( const NodePtr& geo ) :
    _primIt(), _geo( GeometryPtr::dcast(geo->getCore()) ),
    _faceIndex(0), _actPrimIndex(), _facePntIndex()
{
    _primIt.setGeo( geo );
}

FaceIterator::FaceIterator( const GeometryPtr& geo ) :
    _primIt(), _geo( geo ),
    _faceIndex(0), _actPrimIndex(), _facePntIndex()
{
    _primIt.setGeo( geo );
}


FaceIterator::~FaceIterator(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*! The increment operator steps the iterator to the next face. If it is
already beyond the last face it does not change.
*/

void FaceIterator::operator++ ()
{
    // already at end?
    if ( _primIt.isAtEnd() )
        return;
    
    ++_faceIndex;

    // at end of primitive?
    if ( _actPrimIndex >= _primIt.getLength() )
    {
        ++_primIt;
        
        startPrim();
        
        return;
    }

    switch ( _primIt.getType() )
    {
    case GL_TRIANGLES:      _facePntIndex[0] = _actPrimIndex++;
                            _facePntIndex[1] = _actPrimIndex++;
                            _facePntIndex[2] = _actPrimIndex++;
                            _facePntIndex[3] = -1;
                            break;
    case GL_QUAD_STRIP:     _facePntIndex[0] = _facePntIndex[3];
                            _facePntIndex[1] = _facePntIndex[2];
                            _facePntIndex[3] = _actPrimIndex++;
                            _facePntIndex[2] = _actPrimIndex++;
                            break;
    case GL_TRIANGLE_STRIP: if ( _actPrimIndex & 1 )
                            {
                                _facePntIndex[0] = _facePntIndex[2];
                            }
                            else
                            {
                                _facePntIndex[1] = _facePntIndex[2];
                            }                           
                            _facePntIndex[2] = _actPrimIndex++;
                            break;
    case GL_POLYGON:
    case GL_TRIANGLE_FAN:   _facePntIndex[1] = _facePntIndex[2];
                            _facePntIndex[2] = _actPrimIndex++;
                            break;
    case GL_QUADS:          _facePntIndex[0] = _actPrimIndex++;
                            _facePntIndex[1] = _actPrimIndex++;
                            _facePntIndex[2] = _actPrimIndex++;
                            _facePntIndex[3] = _actPrimIndex++;
                            break;
    default:                SWARNING << "FaceIterator::++: encountered " 
                                      << "unknown primitive type " 
                                      << _primIt.getType()
                                      << ", ignoring!" << endl;
                            startPrim();
                            break;
    }           
}


/*! Helper function to reset all state to the beginning of a new primitive.
Also skips non-polygonal primitives (lines, points).
*/

void FaceIterator::startPrim( void )
{
    // already at end?
    if ( _primIt.isAtEnd() )
        return;

    _facePntIndex[0] = 0;
    _facePntIndex[1] = 1;
    _facePntIndex[2] = 2;
    _facePntIndex[3] = -1;
    _actPrimIndex = 3;
    
    // loop until you find a useful primitive or run out
    while ( ! _primIt.isAtEnd() )
    {
        switch ( _primIt.getType() )
        {
        case GL_POINTS:     // non-polygon types: ignored
        case GL_LINES:
        case GL_LINE_STRIP: 
        case GL_LINE_LOOP:  
                            break;
        case GL_TRIANGLES: 
        case GL_TRIANGLE_STRIP:
        case GL_TRIANGLE_FAN:   
                                if ( _primIt.getLength() >= 3 )
                                    return;
                                break;
        case GL_POLYGON:        switch ( _primIt.getLength() )
                                {
                                case 0: 
                                case 1: 
                                case 2: 
                                            break;
                                case 4:
                                            _facePntIndex[3] = _actPrimIndex++;     
                                            return;
                                default:
                                            return;
                                }
                                break;
        case GL_QUADS:          if ( _primIt.getLength() >= 4 )
                                {
                                    _facePntIndex[3] = _actPrimIndex++;                         
                                    return;
                                }
                                break;
        case GL_QUAD_STRIP:         if ( _primIt.getLength() >= 4 )
                                {
                                    _facePntIndex[3] = _facePntIndex[2];                        
                                    _facePntIndex[2] = _actPrimIndex++;                         
                                    return;
                                }
                                break;
        default:            SWARNING << "FaceIterator::startPrim: encountered " 
                                      << "unknown primitive type " 
                                      << _primIt.getType()
                                      << ", ignoring!" << endl;
                            break;
        }   
        
        ++_primIt;
    }       
}

void FaceIterator::seek( Int32 index )
{
    _primIt.setToBegin();
    _faceIndex = 0;
    startPrim();
    
    while ( getIndex() != index )
        ++(*this);
}

void FaceIterator::setToBegin( void )
{
    _primIt.setToBegin();
    _faceIndex = 0;
    startPrim();
}

void FaceIterator::setToEnd( void )
{
    _primIt.setToEnd();
    _actPrimIndex = 0;
}

/*-------------------------- assignment -----------------------------------*/

FaceIterator& FaceIterator::operator = (const FaceIterator &source)
{
    if (this == &source)
        return *this;

    // free mem alloced by members of 'this'

    // alloc new mem for members

    // copy 
    
    this->_geo                  = source._geo;
    this->_primIt           = source._primIt;
    this->_faceIndex        = source._faceIndex;
    this->_actPrimIndex     = source._actPrimIndex;
    this->_facePntIndex[0]      = source._facePntIndex[0];
    this->_facePntIndex[1]      = source._facePntIndex[1];
    this->_facePntIndex[2]      = source._facePntIndex[2];
    this->_facePntIndex[3]      = source._facePntIndex[3];

    return *this;
}

/*-------------------------- comparison -----------------------------------*/

Bool FaceIterator::operator < (const FaceIterator &other) const
{
    return _primIt < other._primIt ||
            ( _primIt == other._primIt &&
              _actPrimIndex < other._actPrimIndex );
}

Bool FaceIterator::operator == (const FaceIterator &other) const
{
    if ( _primIt.isAtEnd() && other._primIt.isAtEnd() )
        return true;
    if ( _primIt.isAtEnd() || other._primIt.isAtEnd() )
        return false;
    return _primIt == other._primIt &&
            _actPrimIndex == other._actPrimIndex;
}

Bool FaceIterator::operator != (const FaceIterator &other) const
{
    return ! (*this == other);
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

