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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGGeometry.h"


OSG_BEGIN_NAMESPACE

inline
Bool PrimitiveIterator::isAtEnd( void ) const
{
#if 1
    return _ended;
#else
// this trigger a bug in sgi compiler in collision between
// FCPtr::getSize() and GeoProperty::getSize(). Don't use right now.
    return _primIndex >= _types->getSize();
#endif
}

inline
Int32 PrimitiveIterator::getIndex( void ) const
{
    return _primIndex;
}

inline
UInt32 PrimitiveIterator::getLength( void ) const
{
    return _actPrimLength;
}

inline
UInt32 PrimitiveIterator::getType( void ) const
{
    return _actPrimType;
}

inline
Int32 PrimitiveIterator::getPositionIndex( Int32 which ) const
{
    if ( _geo->getIndex() != NullFC )
    {
        if ( _positionIndex != -1 )
            return _indices->getValue( ( _actPointIndex + which ) *
                                    _nmappings + _positionIndex );
        else
        return _indices->getValue( _actPointIndex * _nmappings + which  );
    }
    else
        return _actPointIndex + which;
}

inline
Pnt3f PrimitiveIterator::getPosition( Int32 which ) const
{
    Int32 ind = getPositionIndex( which );

    return _geo->getPositions()->getValue( ind );
}

inline
Int32 PrimitiveIterator::getNormalIndex( Int32 which ) const
{
    if ( _geo->getNormals() == NullFC )
        return -1;

    if ( _geo->getIndex() != NullFC )
    {
        if ( _normalIndex != -1 )
            return _indices->getValue( ( _actPointIndex + which ) *
                                    _nmappings + _normalIndex );
        else
        return _indices->getValue( _actPointIndex * _nmappings + which  );
    }
    else
        return _actPointIndex + which;
}

inline
Vec3f PrimitiveIterator::getNormal( Int32 which ) const
{
    Int32 ind = getNormalIndex( which );

    if ( ind < 0 )
        return NullVec3f;

    return _geo->getNormals()->getValue( ind );
}

inline
Int32 PrimitiveIterator::getColorIndex( Int32 which ) const
{
    if ( _geo->getColors() == NullFC )
        return -1;

    if ( _geo->getIndex() != NullFC )
    {
        if ( _colorIndex != -1 )
            return _indices->getValue( ( _actPointIndex + which ) *
                                    _nmappings + _colorIndex );
        else
        return _indices->getValue( _actPointIndex * _nmappings + which  );
    }
    else
        return _actPointIndex + which;
}

inline
Color3f PrimitiveIterator::getColor( Int32 which ) const
{
    Int32 ind = getColorIndex( which );

    if ( ind < 0 )
        return NullColor3f;

    return _geo->getColors()->getValue( ind );
}



inline
Int32 PrimitiveIterator::getTexCoordsIndex( Int32 which ) const
{
    if ( _geo->getTexCoords() == NullFC )
        return -1;

    if ( _geo->getIndex() != NullFC )
    {
        if ( _texcoordsIndex != -1 )
            return _indices->getValue( ( _actPointIndex + which ) *
                                    _nmappings + _texcoordsIndex );
        else
        return _indices->getValue( _actPointIndex * _nmappings + which  );
    }
    else
        return _actPointIndex + which;
}

inline
Vec2f PrimitiveIterator::getTexCoords( Int32 which ) const
{
    Int32 ind = getTexCoordsIndex( which );

    if ( ind < 0 )
        return NullVec2f;

    return _geo->getTexCoords()->getValue( ind );
}

inline
Int32 PrimitiveIterator::getIndexIndex( Int32 which ) const
{
    if ( _geo->getIndex() != NullFC )
    {
        return ( _actPointIndex + which ) * _nmappings;
    }
    else
        return -1;
}

OSG_END_NAMESPACE
