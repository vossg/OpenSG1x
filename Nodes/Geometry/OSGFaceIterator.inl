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

/*! Return the index of the current face. The index runs from 0 to the
    number of faces in the geometry. Its main use is as an input to seek().
*/
inline       
Int32 FaceIterator::getIndex( void ) const
{
    return _faceIndex;
}

/*! Return the type of the current primitive. Mainly useful to be able
    to treat e.g. polygons differently than other triangle-generating
    primitives.
*/
inline       
UInt32 FaceIterator::getType( void ) const
{
    return _primIt.getType();
}


/*! Return the length of the current face. 3 or 4, depending on the current 
    primitive.
*/
inline       
UInt32 FaceIterator::getLength( void) const
{
    return _facePntIndex[3] == -1 ? 3 : 4;
}


/*! Return the position index of a point in the current face. 
    \param which the point to access. Must be between 0 and getLength().
*/
inline       
Int32 FaceIterator::getPositionIndex( Int32 which ) const
{
    if ( _facePntIndex[which] >= 0 )
        return _primIt.getPositionIndex( _facePntIndex[which] );
    else 
        return -1;
}


/*! Return the position of a point in the current face. 
    \param which the point to access. Must be between 0 and getLength().
*/
inline       
Pnt3f FaceIterator::getPosition( Int32 which ) const
{
    Int32 ind = getPositionIndex( which );
    
    if ( ind < 0 )
        return Pnt3f::Null;
    
    return _geo->getPositions()->getValue( ind );
}

/*! Return the normal index of a point in the current face. 
    \param which the point to access. Must be between 0 and getLength().
*/
inline       
Int32 FaceIterator::getNormalIndex( Int32 which ) const
{
    if ( _facePntIndex[which] >= 0 )
        return _primIt.getNormalIndex( _facePntIndex[which] );
    else 
        return -1;
}

/*! Return the normal of a point in the current face. 
    \param which the point to access. Must be between 0 and getLength().
*/
inline 
Vec3f FaceIterator::getNormal( Int32 which ) const
{   
    Int32 ind = getNormalIndex( which );
    
    if ( ind < 0 )
        return Vec3f::Null;
        
    return _geo->getNormals()->getValue( ind );
}

/*! Return the color index of a point in the current face. 
    \param which the point to access. Must be between 0 and getLength().
*/
inline       
Int32 FaceIterator::getColorIndex( Int32 which ) const
{
    if ( _facePntIndex[which] >= 0 )
        return _primIt.getColorIndex( _facePntIndex[which] );
    else 
        return -1;
}

/*! Return the color of a point in the current face. 
    \param which the point to access. Must be between 0 and getLength().
*/
inline 
Color3f FaceIterator::getColor( Int32 which ) const
{   
    Int32 ind = getColorIndex( which );
    
    if ( ind < 0 )
        return NullColor3f;
        
    return _geo->getColors()->getValue( ind );
}


/*! Return the texture coordinate index of a point in the current face. 
    \param which the point to access. Must be between 0 and getLength().
*/
inline       
Int32 FaceIterator::getTexCoordsIndex( Int32 which ) const
{
    if ( _facePntIndex[which] >= 0 )
        return _primIt.getTexCoordsIndex( _facePntIndex[which] );
    else 
        return -1;
}

/*! Return the texture coordinate of a point in the current face. 
    \param which the point to access. Must be between 0 and getLength().
*/
inline 
Vec2f FaceIterator::getTexCoords( Int32 which ) const
{   
    Int32 ind = getTexCoordsIndex( which );
    
    if ( ind < 0 )
        return Vec2f::Null;
        
    return _geo->getTexCoords()->getValue( ind );
}


/*! Return the index index of a point in the current face. 
    \param which the point to access. Must be between 0 and getLength().
*/
inline       
Int32 FaceIterator::getIndexIndex( Int32 which ) const
{
    if ( _facePntIndex[which] >= 0 )
        return _primIt.getIndexIndex( _facePntIndex[which] );
    else 
        return -1;
}

OSG_END_NAMESPACE
