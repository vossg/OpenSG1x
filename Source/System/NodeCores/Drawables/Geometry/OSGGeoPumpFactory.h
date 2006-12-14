/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifndef _OSGGEOPUMPFACTORY_H_
#define _OSGGEOPUMPFACTORY_H_
#ifdef __sgi
#pragma once
#endif

#include <utility>
#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>
#include <OSGGeometry.h>

OSG_BEGIN_NAMESPACE

class Window;

#ifdef OSG_SUPPORT_NO_GEO_INTERFACE
class GeoPositionsInterface;
class GeoNormalsInterface;
class GeoColorsInterface;
class GeoTexCoordsInterface;
class GeoPTypesInterface;
class GeoPLengthsInterface;
class GeoIndicesInterface;
#endif

/*! \brief Selects a pump function for drawing the given geometry.
*/

class OSG_SYSTEMLIB_DLLMAPPING GeoPumpFactory
{
    /*==========================  PUBLIC  =================================*/
  public:

    typedef UInt32 Index;

    /*---------------------------------------------------------------------*/
    /*! \name                    Pump Types                                */
    /*! \{                                                                 */

    typedef void (*GeoPump)( Window *win, Geometry * geo );

    typedef void (*PartialGeoPump)( Window *win, Geometry * geo,
        UInt32 primtype, UInt32 firstvert, UInt32 nvert );

    typedef void (*InterfacePump)( Window *win,
        GeoPositionsInterface *pos, GeoNormalsInterface *norm,
        GeoColorsInterface *col, GeoColorsInterface *seccol,
        GeoTexCoordsInterface *texcoords,
        GeoTexCoordsInterface *texcoords1,
        GeoTexCoordsInterface *texcoords2,
        GeoTexCoordsInterface *texcoords3,
        GeoPTypesInterface *type, GeoPLengthsInterface *len,
        GeoIndicesInterface *ind, UInt16 *map, UInt16 nmap );

    typedef void (*PartialInterfacePump)( Window *win,
        GeoPositionsInterface *pos, GeoNormalsInterface *norm,
        GeoColorsInterface *col, GeoColorsInterface *seccol,
        GeoTexCoordsInterface *texcoords,
        GeoTexCoordsInterface *texcoords1,
        GeoTexCoordsInterface *texcoords2,
        GeoTexCoordsInterface *texcoords3,
        GeoPTypesInterface *type, GeoPLengthsInterface *len,
        GeoIndicesInterface *ind, UInt16 *map, UInt16 nmap,
        UInt32 primtype, UInt32 firstvert, UInt32 nvert );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "GeoPumpFactory"; }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~GeoPumpFactory(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Get                                    */
    /*! \{                                                                 */

    Index                getIndex                (Geometry * geo          );

    GeoPump              getGeoPump              (Window *win, Index index);

    PartialGeoPump       getPartialGeoPump       (Window *win, Index index);

    InterfacePump        getInterfacePump        (Window *win, Index index);

    PartialInterfacePump getPartialInterfacePump (Window *win, Index index);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Access                                 */
    /*! \{                                                                 */

    static GeoPumpFactory *the( void );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               OpenGL Extension handling                      */
    /*! \{                                                                 */

    static UInt32           _extSecondaryColor;
    static UInt32           _extMultitexture;
    static UInt32           _extCompiledVertexArray;
    static UInt32           _extDrawRangeElements;
    static UInt32           _arbVBO;

    static UInt32           _funcglSecondaryColorPointer;
    static UInt32           _funcglClientActiveTextureARB;
    static UInt32           _funcglLockArraysEXT;
    static UInt32           _funcglUnlockArraysEXT;
    static UInt32           _funcglDrawRangeElementsEXT;

    static UInt32           _funcglGenBuffersARB;
    static UInt32           _funcglDeleteBuffersARB;
    static UInt32           _funcglBindBufferARB;
    static UInt32           _funcglBufferDataARB;
    static UInt32           _funcglBufferSubDataARB;

    static UInt32           _funcglGenBuffers;
    static UInt32           _funcglDeleteBuffers;
    static UInt32           _funcglBindBuffer;
    static UInt32           _funcglBufferData;
    static UInt32           _funcglBufferSubData;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    virtual Index numIndices(void);

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    GeoPumpFactory(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    static char cvsid[];

    static GeoPumpFactory *_the;
    static GeoPump GeoPumps[131];

    /*---------------------------------------------------------------------*/
    /*! \name               OpenGL Extension handling                      */
    /*! \{                                                                 */

    static bool             glextInitFunction(void);
    static InitFuncWrapper _glextInitFuncWrapper;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       The Pumps                              */
    /*! \{                                                                 */

    static void masterGeoPump(Window *win, Geometry *geo);

    static void masterPartialGeoPump(Window *win, Geometry *geo,
        UInt32 primtype, UInt32 firstvert, UInt32 nvert);

    static void masterInterfacePump(Window *win,
        GeoPositionsInterface *pos, GeoNormalsInterface *norm,
        GeoColorsInterface *col, GeoColorsInterface *seccol,
        GeoTexCoordsInterface *texcoords,
        GeoTexCoordsInterface *texcoords2,
        GeoTexCoordsInterface *texcoords3,
        GeoTexCoordsInterface *texcoords4,
        GeoPTypesInterface *type, GeoPLengthsInterface*len,
        GeoIndicesInterface *ind, UInt16 *map, UInt16 nmap);

    static void masterPartialInterfacePump(Window *win,
        GeoPositionsInterface *pos, GeoNormalsInterface *norm,
        GeoColorsInterface *col, GeoColorsInterface *seccol,
        GeoTexCoordsInterface *texcoords,
        GeoTexCoordsInterface *texcoords2,
        GeoTexCoordsInterface *texcoords3,
        GeoTexCoordsInterface *texcoords4,
        GeoPTypesInterface *type, GeoPLengthsInterface*len,
        GeoIndicesInterface *ind, UInt16 *map, UInt16 nmap,
        UInt32 primtype, UInt32 firstvert, UInt32 nvert);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    GeoPumpFactory(const GeoPumpFactory &source);

    /*! \}                                                                 */

    void operator =(const GeoPumpFactory &source);

};

class OSG_SYSTEMLIB_DLLMAPPING GeoVBO
{
public:

    GeoVBO(Window *win, Geometry *geo);
    ~GeoVBO();

    void update(void);
    void draw(void);

private:

    GLuint _positions;
    GLuint _normals;
    GLuint _colors;
    GLuint _secColors;
    GLuint _texCoords;
    GLuint _texCoords1;
    GLuint _texCoords2;
    GLuint _texCoords3;
    GLuint _texCoords4;
    GLuint _texCoords5;
    GLuint _texCoords6;
    GLuint _texCoords7;
    GLuint _indices;

    Window   *_win;
    Geometry *_geo;
};

OSG_END_NAMESPACE

#include "OSGGeoPumpFactory.inl"

#define OSGGEOPUMPFACTORY_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGGEOPUMPFACTORY_H_ */
