/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright(C) 2000-2002 by the OpenSG Forum                    *
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


/*! Check if the iterator has already reached the end of the geometry.
*/
inline
bool PrimitiveIterator::isAtEnd(void) const
{
    return _ended;
}


/*! Return the index of the current primitive. The index runs from 0 to the
    number of faces in the geometry. Its main use is as an input to seek().
*/
inline
Int32 PrimitiveIterator::getIndex(void) const
{
    return _primIndex;
}

/*! Return the length(i.e. number of used vertices) of the current primitive.
*/
inline
UInt32 PrimitiveIterator::getLength(void) const
{
    return _actPrimLength;
}

/*! Return the type of the current primitive.
*/
inline
UInt32 PrimitiveIterator::getType(void) const
{
    return _actPrimType;
}


/*! Return the position index (i.e. the number of the entry in the positions
    property which is used) of a point in the current primitive. 
    \a which is the point to access. Must be between 0 and getLength().
*/
inline
Int32 PrimitiveIterator::getPositionIndex(Int32 which) const
{
    if(_geo->getIndices() != NullFC)
    {
        if(_positionIndex != -1)
        {
            return _indices->getValue((_actPointIndex + which) *
                                      _nmappings + _positionIndex);
        }
        else
        {
            return _indices->getValue(_actPointIndex * _nmappings + which );
        }
    }
    else
    {
        return _actPointIndex + which;
    }
}


/*! Return the position of a point in the current primitive. 
    \a which is the point to access. Must be between 0 and getLength().
*/
inline
Pnt3f PrimitiveIterator::getPosition(Int32 which) const
{
    Int32 ind = getPositionIndex(which);

    return _geo->getPositions()->getValue(ind);
}


/*! Return the normal index (i.e. the number of the entry in the normal
    property which is used) of a point in the current primitive. 
    \a which is the point to access. Must be between 0 and getLength().
    
    If the geometry has no normals, -1 is returned.
*/
inline
Int32 PrimitiveIterator::getNormalIndex(Int32 which) const
{
    if(_geo->getNormals() == NullFC)
        return -1;

    if(_geo->getIndices() != NullFC)
    {
        if(_normalIndex != -1)
        {
            return _indices->getValue((_actPointIndex + which) *
                                      _nmappings + _normalIndex);
        }
        else
        {
            return _indices->getValue(_actPointIndex * _nmappings + which );
        }
    }
    else
    {
        return _actPointIndex + which;
    }
}


/*! Return the normal of a point in the current primitive. 
    \a which is the point to access. Must be between 0 and getLength().
    
    If the geometry has no normals, Vec3f::Null is returned.
*/
inline
Vec3f PrimitiveIterator::getNormal(Int32 which) const
{
    Int32 ind = getNormalIndex(which);

    if(ind < 0)
        return Vec3f::Null;

    return _geo->getNormals()->getValue(ind);
}

/*! Return the color index (i.e. the number of the entry in the color
    property which is used) of a point in the current primitive. 
    \a which is the point to access. Must be between 0 and getLength().
    
    If the geometry has no colors, -1 is returned.
*/
inline
Int32 PrimitiveIterator::getColorIndex(Int32 which) const
{
    if(_geo->getColors() == NullFC)
        return -1;

    if(_geo->getIndices() != NullFC)
    {
        if(_colorIndex != -1)
        {
            return _indices->getValue((_actPointIndex + which) *
                                      _nmappings + _colorIndex);
        }
        else
        {
            return _indices->getValue(_actPointIndex * _nmappings + which );
        }
    }
    else
    {
        return _actPointIndex + which;
    }
}

/*! Return the color of a point in the current primitive. 
    \a which is the point to access. Must be between 0 and getLength().
    
    If the geometry has no colors, Color3f::Null is returned.
*/
inline
Color3f PrimitiveIterator::getColor(Int32 which) const
{
    Int32 ind = getColorIndex(which);

    if(ind < 0)
        return Color3f::Null;

    return _geo->getColors()->getValue(ind);
}


/*! Return the secondary color index (i.e. the number of the entry in the 
    secondary color property which is used) of a point in the current
    primitive. \a which is the point to access. Must be between 0 and
    getLength().

    If the geometry has no secondary colors, -1 is returned.
*/
inline
Int32 PrimitiveIterator::getSecondaryColorIndex(Int32 which) const
{
    if(_geo->getSecondaryColors() == NullFC)
        return -1;

    if(_geo->getIndices() != NullFC)
    {
        if(_secondaryColorIndex != -1)
        {
            return _indices->getValue((_actPointIndex + which) *
                                      _nmappings + _secondaryColorIndex);
        }
        else
        {
            return _indices->getValue(_actPointIndex * _nmappings + which );
        }
    }
    else
    {
        return _actPointIndex + which;
    }
}

/*! Return the secondary color of a point in the current primitive. 
    \a which is the point to access. Must be between 0 and getLength().
    
    If the geometry has no secondary colors, Color3f::Null is returned.
*/
inline
Color3f PrimitiveIterator::getSecondaryColor(Int32 which) const
{
    Int32 ind = getSecondaryColorIndex(which);

    if(ind < 0)
        return Color3f::Null;

    return _geo->getSecondaryColors()->getValue(ind);
}

/*! Return the texture coordinates index (i.e. the number of the entry in the 
    texture coordinates property which is used) of a point in the current
    primitive.  \a which is the point to access. Must be between 0 and
    getLength().
    
    If the geometry has no texture coordinates, -1 is returned.
*/
inline
Int32 PrimitiveIterator::getTexCoordsIndex(Int32 which) const
{
    if(_geo->getTexCoords() == NullFC)
        return -1;

    if(_geo->getIndices() != NullFC)
    {
        if(_texcoordsIndex != -1)
        {
            return _indices->getValue((_actPointIndex + which) *
                                      _nmappings + _texcoordsIndex);
        }
        else
        {
            return _indices->getValue(_actPointIndex * _nmappings + which );
        }
    }
    else
    {
        return _actPointIndex + which;
    }
}

/*! Return the texture coordinates of a point in the current primitive. 
    \a which is the point to access. Must be between 0 and getLength().
    
    If the geometry has no texture coordinates, Vec2f::Null is returned.
*/
inline
Vec2f PrimitiveIterator::getTexCoords(Int32 which) const
{
    Int32 ind = getTexCoordsIndex(which);

    if(ind < 0)
        return Vec2f::Null;

    return _geo->getTexCoords()->getValue(ind);
}


/*! Return the second texture coordinates index (i.e. the number of the entry
    in the textureCoordinates1 property which is used) of a point in the
    current primitive. \a which is the point to access. Must be between 0 and
    getLength().
    
    If the geometry has no second texture coordinates, -1 is returned.
*/
inline
Int32 PrimitiveIterator::getTexCoordsIndex1(Int32 which) const
{
    if(_geo->getTexCoords1() == NullFC)
        return -1;

    if(_geo->getIndices() != NullFC)
    {
        if(_texcoordsIndex1 != -1)
        {
            return _indices->getValue((_actPointIndex + which) *
                                      _nmappings + _texcoordsIndex1);
        }
        else
        {
            return _indices->getValue(_actPointIndex * _nmappings + which );
        }
    }
    else
    {
        return _actPointIndex + which;
    }
}


/*! Return the second texture coordinates of a point in the current primitive. 
    \a which is the point to access. Must be between 0 and getLength().
    
    If the geometry has no second texture coordinates, Vec2f::Null is returned.
*/
inline
Vec2f PrimitiveIterator::getTexCoords1(Int32 which) const
{
    Int32 ind = getTexCoordsIndex1(which);

    if(ind < 0)
        return Vec2f::Null;

    return _geo->getTexCoords1()->getValue(ind);
}


/*! Return the third texture coordinates index (i.e. the number of the entry
    in the textureCoordinates2 property which is used) of a point in the
    current primitive. \a which is the point to access. Must be between 0 and
    getLength().
    
    If the geometry has no third texture coordinates, -1 is returned.
*/
inline
Int32 PrimitiveIterator::getTexCoordsIndex2(Int32 which) const
{
    if(_geo->getTexCoords2() == NullFC)
        return -1;

    if(_geo->getIndices() != NullFC)
    {
        if(_texcoordsIndex2 != -1)
        {
            return _indices->getValue((_actPointIndex + which) *
                                      _nmappings + _texcoordsIndex2);
        }
        else
        {
            return _indices->getValue(_actPointIndex * _nmappings + which );
        }
    }
    else
    {
        return _actPointIndex + which;
    }
}


/*! Return the third texture coordinates of a point in the current primitive. 
    \a which is the point to access. Must be between 0 and getLength().
    
    If the geometry has no third texture coordinates, Vec2f::Null is returned.
*/
inline
Vec2f PrimitiveIterator::getTexCoords2(Int32 which) const
{
    Int32 ind = getTexCoordsIndex2(which);

    if(ind < 0)
        return Vec2f::Null;

    return _geo->getTexCoords2()->getValue(ind);
}


/*! Return the fourth texture coordinates index (i.e. the number of the entry
    in the textureCoordinates3 property which is used) of a point in the
    current primitive. \a which is the point to access. Must be between 0 and
    getLength().
    
    If the geometry has no fourth texture coordinates, -1 is returned.
*/
inline
Int32 PrimitiveIterator::getTexCoordsIndex3(Int32 which) const
{
    if(_geo->getTexCoords3() == NullFC)
        return -1;

    if(_geo->getIndices() != NullFC)
    {
        if(_texcoordsIndex3 != -1)
        {
            return _indices->getValue((_actPointIndex + which) *
                                      _nmappings + _texcoordsIndex3);
        }
        else
        {
            return _indices->getValue(_actPointIndex * _nmappings + which );
        }
    }
    else
    {
        return _actPointIndex + which;
    }
}


/*! Return the fourth texture coordinates of a point in the current primitive. 
    \a which is the point to access. Must be between 0 and getLength().
    
    If the geometry has no fourth texture coordinates, Vec2f::Null is returned.
*/
inline
Vec2f PrimitiveIterator::getTexCoords3(Int32 which) const
{
    Int32 ind = getTexCoordsIndex3(which);

    if(ind < 0)
        return Vec2f::Null;

    return _geo->getTexCoords3()->getValue(ind);
}

/*! Return the fifth texture coordinates index (i.e. the number of the entry
    in the textureCoordinates4 property which is used) of a point in the
    current primitive. \a which is the point to access. Must be between 0 and
    getLength().
    
    If the geometry has no fifth texture coordinates, -1 is returned.
*/
inline
Int32 PrimitiveIterator::getTexCoordsIndex4(Int32 which) const
{
    if(_geo->getTexCoords4() == NullFC)
        return -1;

    if(_geo->getIndices() != NullFC)
    {
        if(_texcoordsIndex4 != -1)
        {
            return _indices->getValue((_actPointIndex + which) *
                                      _nmappings + _texcoordsIndex4);
        }
        else
        {
            return _indices->getValue(_actPointIndex * _nmappings + which );
        }
    }
    else
    {
        return _actPointIndex + which;
    }
}


/*! Return the fifth texture coordinates of a point in the current primitive. 
    \a which is the point to access. Must be between 0 and getLength().
    
    If the geometry has no fifth texture coordinates, Vec2f::Null is returned.
*/
inline
Vec2f PrimitiveIterator::getTexCoords4(Int32 which) const
{
    Int32 ind = getTexCoordsIndex4(which);

    if(ind < 0)
        return Vec2f::Null;

    return _geo->getTexCoords4()->getValue(ind);
}

/*! Return the sixth texture coordinates index (i.e. the number of the entry
    in the textureCoordinates5 property which is used) of a point in the
    current primitive. \a which is the point to access. Must be between 0 and
    getLength().
    
    If the geometry has no sixth texture coordinates, -1 is returned.
*/
inline
Int32 PrimitiveIterator::getTexCoordsIndex5(Int32 which) const
{
    if(_geo->getTexCoords5() == NullFC)
        return -1;

    if(_geo->getIndices() != NullFC)
    {
        if(_texcoordsIndex5 != -1)
        {
            return _indices->getValue((_actPointIndex + which) *
                                      _nmappings + _texcoordsIndex5);
        }
        else
        {
            return _indices->getValue(_actPointIndex * _nmappings + which );
        }
    }
    else
    {
        return _actPointIndex + which;
    }
}


/*! Return the sixth texture coordinates of a point in the current primitive. 
    \a which is the point to access. Must be between 0 and getLength().
    
    If the geometry has no sixth texture coordinates, Vec2f::Null is returned.
*/
inline
Vec2f PrimitiveIterator::getTexCoords5(Int32 which) const
{
    Int32 ind = getTexCoordsIndex5(which);

    if(ind < 0)
        return Vec2f::Null;

    return _geo->getTexCoords5()->getValue(ind);
}

/*! Return the seventh texture coordinates index (i.e. the number of the entry
    in the textureCoordinates6 property which is used) of a point in the
    current primitive. \a which is the point to access. Must be between 0 and
    getLength().
    
    If the geometry has no seventh texture coordinates, -1 is returned.
*/
inline
Int32 PrimitiveIterator::getTexCoordsIndex6(Int32 which) const
{
    if(_geo->getTexCoords6() == NullFC)
        return -1;

    if(_geo->getIndices() != NullFC)
    {
        if(_texcoordsIndex6 != -1)
        {
            return _indices->getValue((_actPointIndex + which) *
                                      _nmappings + _texcoordsIndex6);
        }
        else
        {
            return _indices->getValue(_actPointIndex * _nmappings + which );
        }
    }
    else
    {
        return _actPointIndex + which;
    }
}


/*! Return the seventh texture coordinates of a point in the current primitive. 
    \a which is the point to access. Must be between 0 and getLength().
    
    If the geometry has no seventh texture coordinates, Vec2f::Null is returned.
*/
inline
Vec2f PrimitiveIterator::getTexCoords6(Int32 which) const
{
    Int32 ind = getTexCoordsIndex6(which);

    if(ind < 0)
        return Vec2f::Null;

    return _geo->getTexCoords6()->getValue(ind);
}

/*! Return the eighth texture coordinates index (i.e. the number of the entry
    in the textureCoordinates7 property which is used) of a point in the
    current primitive. \a which is the point to access. Must be between 0 and
    getLength().
    
    If the geometry has no eighth texture coordinates, -1 is returned.
*/
inline
Int32 PrimitiveIterator::getTexCoordsIndex7(Int32 which) const
{
    if(_geo->getTexCoords7() == NullFC)
        return -1;

    if(_geo->getIndices() != NullFC)
    {
        if(_texcoordsIndex7 != -1)
        {
            return _indices->getValue((_actPointIndex + which) *
                                      _nmappings + _texcoordsIndex7);
        }
        else
        {
            return _indices->getValue(_actPointIndex * _nmappings + which );
        }
    }
    else
    {
        return _actPointIndex + which;
    }
}


/*! Return the eighth texture coordinates of a point in the current primitive. 
    \a which is the point to access. Must be between 0 and getLength().
    
    If the geometry has no eighth texture coordinates, Vec2f::Null is returned.
*/
inline
Vec2f PrimitiveIterator::getTexCoords7(Int32 which) const
{
    Int32 ind = getTexCoordsIndex7(which);

    if(ind < 0)
        return Vec2f::Null;

    return _geo->getTexCoords7()->getValue(ind);
}

/*! Return the index index of a point in the current primitive. The index
    index is the number of the index used for this point in the index
    property. \a which is the point to access. Must be between 0 and
    getLength(). 
    
    For multi-indexed geometry it is the index of the beginning of the index
    block used. See \ref PageSystemGeoIndexing for details on indexing.
    
    If the geometry has no indices, -1 is returned.
*/
inline
Int32 PrimitiveIterator::getIndexIndex(Int32 which) const
{
    if(_geo->getIndices() != NullFC)
    {
        return(_actPointIndex + which) * _nmappings;
    }
    else
        return -1;
}

/*! Return the geometry the iterator is currently attached to.
*/
inline
GeometryPtr PrimitiveIterator::getGeometry(void) const
{
    return _geo;
}

OSG_END_NAMESPACE
