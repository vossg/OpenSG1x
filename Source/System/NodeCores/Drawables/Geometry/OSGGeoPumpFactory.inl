/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include "OSGGeoPumpFactory.h"


OSG_BEGIN_NAMESPACE

/*! Access the GeoPumpFactory Singleton.
*/
inline
GeoPumpFactory *GeoPumpFactory::the(void)
{
    if(_the == NULL)
    {
        _the = new GeoPumpFactory();
    }

    return _the;
}

inline
GLuint GeoVBO::getPositions(void) const
{
    return _positions;
}

inline
GLuint GeoVBO::getNormals(void) const
{ 
    return _normals;
}

inline
GLuint GeoVBO::getColors(void) const
{
    return _colors;
}

inline
GLuint GeoVBO::getSecColors(void) const
{
    return _secColors;
}

inline
GLuint GeoVBO::getTexCoords(void) const
{
    return _texCoords;
}

inline
GLuint GeoVBO::getTexCoords1(void) const
{
    return _texCoords1;
}

inline
GLuint GeoVBO::getTexCoords2(void) const
{
    return _texCoords2;
}

inline
GLuint GeoVBO::getTexCoords3(void) const
{
    return _texCoords3;
}

inline
GLuint GeoVBO::getTexCoords4(void) const
{
    return _texCoords4;
}

inline
GLuint GeoVBO::getTexCoords5(void) const
{
    return _texCoords5;
}

inline
GLuint GeoVBO::getTexCoords6(void) const
{
    return _texCoords6;
}

inline
GLuint GeoVBO::getTexCoords7(void) const
{
    return _texCoords7;
}

inline
GLuint GeoVBO::getIndices(void) const
{
    return _indices;
}

inline
void GeoVBO::setDrawPropertiesMask(const UInt16 draw_properties_mask)
{
    _draw_properties_mask = draw_properties_mask;
}

inline
UInt16 GeoVBO::getDrawPropertiesMask(void) const
{
    return _draw_properties_mask;
}

OSG_END_NAMESPACE

#define OSGGEOPUMPFACTORY_INLINE_CVSID "@(#)$Id: $"
