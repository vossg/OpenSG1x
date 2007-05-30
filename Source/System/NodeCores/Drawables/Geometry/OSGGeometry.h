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


#ifndef _OSGGEOMETRY_H_
#define _OSGGEOMETRY_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGAction.h>
#include <OSGWindow.h>

#include <OSGGeometryBase.h>
#include <OSGGeoPropPtrs.h>
#include <OSGMaterial.h>

#include <OSGActorBase.h>


OSG_BEGIN_NAMESPACE

class DrawActionBase;

class TriangleIterator;
class PrimitiveIterator;
class FaceIterator;
class LineIterator;
class EdgeIterator;
class GeoVBO;

/*! The Geometry class, see \ref PageSystemGeometry for a description.
*/
class OSG_SYSTEMLIB_DLLMAPPING Geometry : public GeometryBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                IndexMapping Constants                        */
    /*! \{                                                                 */

    static const UInt16 MapPosition;
    static const UInt16 MapNormal;
    static const UInt16 MapColor;
    static const UInt16 MapSecondaryColor;
    static const UInt16 MapTexCoords;
    static const UInt16 MapTexCoords1;
    static const UInt16 MapTexCoords2;
    static const UInt16 MapTexCoords3;
    static const UInt16 MapTexCoords4;
    static const UInt16 MapTexCoords5;
    static const UInt16 MapTexCoords6;
    static const UInt16 MapTexCoords7;
    static const UInt16 MapEmpty;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "Geometry"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Class Specific                         */
    /*! \{                                                                 */

    static const char *mapType          (UInt8 type);

    Int16              calcMappingIndex (UInt16 attrib) const;

    virtual void       changed          (BitVector whichField,
                                         UInt32    origin    );

    GeometryPtr        getPtr           (void) const;

    GeometryPtr        clone            (void);

    virtual void       dump             (      UInt32    uiIndent = 0,
                                         const BitVector bvFlags = 0) const;

    bool               isMergeable      (const GeometryPtr other);

    bool               merge            (const GeometryPtr other);

    UInt32             getCachedGfxMemoryUsage(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Abstract                                  */
    /*! \{                                                                 */

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    virtual GeoPropertyArrayInterface *getProperty(Int32 mapID);
#endif


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

    void setTypes          (const GeoPTypesPtr    &value);
    void setLengths        (const GeoPLengthsPtr  &value);
    void setPositions      (const GeoPositionsPtr &value);
    void setNormals        (const GeoNormalsPtr   &value);
    void setColors         (const GeoColorsPtr    &value);
    void setSecondaryColors(const GeoColorsPtr    &value);
    void setTexCoords      (const GeoTexCoordsPtr &value);
    void setTexCoords1     (const GeoTexCoordsPtr &value);
    void setTexCoords2     (const GeoTexCoordsPtr &value);
    void setTexCoords3     (const GeoTexCoordsPtr &value);
    void setTexCoords4     (const GeoTexCoordsPtr &value);
    void setTexCoords5     (const GeoTexCoordsPtr &value);
    void setTexCoords6     (const GeoTexCoordsPtr &value);
    void setTexCoords7     (const GeoTexCoordsPtr &value);
    void setIndices        (const GeoIndicesPtr   &value);
    void setMaterial       (const MaterialPtr     &value);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Iterator Access                        */
    /*! \{                                                                 */

    TriangleIterator   beginTriangles   (void) const;
    TriangleIterator   endTriangles     (void) const;

    PrimitiveIterator  beginPrimitives  (void) const;
    PrimitiveIterator  endPrimitives    (void) const;

    FaceIterator       beginFaces       (void) const;
    FaceIterator       endFaces         (void) const;

    LineIterator       beginLines       (void) const;
    LineIterator       endLines         (void) const;

    EdgeIterator       beginEdges       (void) const;
    EdgeIterator       endEdges         (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Draw                                   */
    /*! \{                                                                 */

    // should these be public?
    virtual Action::ResultE drawPrimitives (DrawActionBase * action );
            Action::ResultE intersect      (Action * action );

    NewActionTypes::ResultE intersectActor(ActorBase::FunctorArgumentType &funcArg);

    void            invalidateDlistCache (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      NodeCore Specific                       */
    /*! \{                                                                 */

    // this only calculates a bbox - therefore it is useful and does no harm
    void            adjustVolume     (Volume & volume);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Geometry(void);
    Geometry(const Geometry &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Geometry(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    void handleGL(Window* win, UInt32 id);

    void onCreate(const Geometry *source = NULL);
    void onDestroy(void);

    bool CompareMaterials(MaterialPtr m1, MaterialPtr m2);
    Int16 MergeIndex( const GeometryPtr other );

    void merge0( const GeometryPtr other );
    void merge1( const GeometryPtr other );
    void merge2( const GeometryPtr other );
    void merge3( const GeometryPtr other );
    void merge4( const GeometryPtr other );
    void merge5( const GeometryPtr other );
    void merge6( const GeometryPtr other );

    bool updateLowHighIndices( void );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef GeometryBase Inherited;

    friend class FieldContainer;
    friend class GeometryBase;

    static void initMethod( void );

    void operator =(const Geometry &source);

    void createVBO(Window *win, UInt32 id);
    void destroyVBO(Window *win, UInt32 id);
    void updateVBO(Window *win, UInt32 id);
    bool drawVBO(Window *win, UInt32 id);

    static std::vector<GeoVBO *> _vbos;

    UInt32 _numBytesOnGfxCard;
};

typedef Geometry *GeometryP;

OSG_END_NAMESPACE

#include <OSGGeometryBase.inl>
#include <OSGGeometry.inl>

#define OSGGEOMETRY_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGGEOMETRY_H_ */
