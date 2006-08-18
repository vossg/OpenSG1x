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


#ifndef _OSGPRIMITIVEITERATOR_H_
#define _OSGPRIMITIVEITERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBaseTypes.h>
#include <OSGFieldContainerPtr.h>
#include <OSGNodeCore.h>
#include <OSGSystemDef.h>
#include <OSGGeoProperty.h>
#include <OSGMaterialDrawable.h>

OSG_BEGIN_NAMESPACE

class Geometry;
typedef FCPtr<MaterialDrawablePtr, Geometry> GeometryPtr;

/*! \brief Geometry Iterator for primitives. See \ref 
    PageSystemGeometryIterators for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING PrimitiveIterator
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "PrimitiveIterator"; }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    PrimitiveIterator(void);

    PrimitiveIterator(const PrimitiveIterator &source);

    PrimitiveIterator(const GeometryPtr& geo);
    PrimitiveIterator(const NodePtr& geo);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PrimitiveIterator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Set                                    */
    /*! \{                                                                 */

    void setGeo(const GeometryPtr& geo);
    void setGeo(const NodePtr& geo);

    void setToBegin(void);
    void setToEnd  (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Get                                    */
    /*! \{                                                                 */

    inline bool         isAtEnd                (void       ) const;

    inline Int32        getIndex               (void       ) const;
    inline UInt32       getLength              (void       ) const;
    inline UInt32       getType                (void       ) const;

    inline Int32        getPositionIndex       (Int32 which) const;
    inline Pnt3f        getPosition            (Int32 which) const;

    inline Int32        getNormalIndex         (Int32 which) const;
    inline Vec3f        getNormal              (Int32 which) const;

    inline Int32        getColorIndex          (Int32 which) const;
    inline Color3f      getColor               (Int32 which) const;

    inline Int32        getSecondaryColorIndex (Int32 which) const;
    inline Color3f      getSecondaryColor      (Int32 which) const;

    inline Int32        getTexCoordsIndex      (Int32 which) const;
    inline Vec2f        getTexCoords           (Int32 which) const;

    inline Int32        getTexCoordsIndex1     (Int32 which) const;
    inline Vec2f        getTexCoords1          (Int32 which) const;

    inline Int32        getTexCoordsIndex2     (Int32 which) const;
    inline Vec2f        getTexCoords2          (Int32 which) const;

    inline Int32        getTexCoordsIndex3     (Int32 which) const;
    inline Vec2f        getTexCoords3          (Int32 which) const;

    inline Int32        getTexCoordsIndex4      (Int32 which) const;
    inline Vec2f        getTexCoords4           (Int32 which) const;

    inline Int32        getTexCoordsIndex5      (Int32 which) const;
    inline Vec2f        getTexCoords5           (Int32 which) const;

    inline Int32        getTexCoordsIndex6      (Int32 which) const;
    inline Vec2f        getTexCoords6           (Int32 which) const;

    inline Int32        getTexCoordsIndex7      (Int32 which) const;
    inline Vec2f        getTexCoords7           (Int32 which) const;

    inline Int32        getIndexIndex          (Int32 which) const;

    inline GeometryPtr  getGeometry            (void        ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Operators                              */
    /*! \{                                                                 */

    void operator ++(void);
    void seek(Int32 index);

    PrimitiveIterator & operator =(const PrimitiveIterator &source);

    bool operator <  (const PrimitiveIterator &other) const;

    bool operator == (const PrimitiveIterator &other) const;
    bool operator != (const PrimitiveIterator &other) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:


    /*==========================  PRIVATE  ================================*/
  private:

    friend class Geometry;

    static char cvsid[];

    /*---------------------------------------------------------------------*/
    /*! \name                       Data                                   */
    /*! \{                                                                 */

    GeometryPtr     _geo;
    bool            _ended;
    UInt32          _primIndex;
    UInt32          _actPointIndex;
    UInt32          _actPrimType;
    UInt32          _actPrimLength;
    GeoPTypesPtr    _types;
    GeoPLengthsPtr  _lengths;
    GeoIndicesPtr   _indices;
    UInt16          _nmappings;
    Int16           _positionIndex;
    Int16           _normalIndex;
    Int16           _colorIndex;
    Int16           _secondaryColorIndex;
    Int16           _texcoordsIndex;
    Int16           _texcoordsIndex1;
    Int16           _texcoordsIndex2;
    Int16           _texcoordsIndex3;
    Int16           _texcoordsIndex4;
    Int16           _texcoordsIndex5;
    Int16           _texcoordsIndex6;
    Int16           _texcoordsIndex7;

    /*! \}                                                                 */
};

typedef PrimitiveIterator *PrimitiveIteratorP;

OSG_END_NAMESPACE

#include "OSGPrimitiveIterator.inl"

#endif /* _OSGPRIMITIVEITERATOR_H_ */
