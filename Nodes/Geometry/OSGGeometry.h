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


#ifndef _OSGGEOMETRY_H_
#define _OSGGEOMETRY_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGAction.h>
#include <OSGWindow.h>
#include <OSGStatElemTypes.h>

#include <OSGGeometryBase.h>
#include <OSGGeoPropPtrs.h>

OSG_BEGIN_NAMESPACE

class DrawActionBase;

class TriangleIterator;
class PrimitiveIterator;
class FaceIterator;

//! \ingroup GeometryLib
//! Geometry base class

class OSG_SYSTEMLIB_DLLMAPPING Geometry : public GeometryBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    static const UInt16 MapPosition;
    static const UInt16 MapNormal;
    static const UInt16 MapColor;
    static const UInt16 MapTexcoords;
    static const UInt16 MapTexcoords2;  // not used yet
    static const UInt16 MapTexcoords3;  // not used yet
    static const UInt16 MapTexcoords4;  // not used yet
    static const UInt16 MapEmpty;

    static StatElemDesc<StatIntElem>  statNTriangles;
    static StatElemDesc<StatIntElem>  statNLines;
    static StatElemDesc<StatIntElem>  statNPoints;
    static StatElemDesc<StatIntElem>  statNVertices;

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "Geometry"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Class Specific                         */
    /*! \{                                                                 */

    static const char *mapType          (UInt8 type);

    virtual void       changed          (BitVector whichField,
                                         ChangeMode from);

    GeometryPtr        getPtr           (void) const;

    
    virtual 
    AbstractGeoPropertyInterface * getProperty (int mapID);

                                        
    Int16              calcMappingIndex (UInt16 attrib) const;

    GeometryPtr        clone            (void);

    virtual void       dump             (      UInt32    uiIndent = 0,
                                         const BitVector bvFlags = 0) const;

    bool               isMergeable      (const GeometryPtr other);

    bool               merge            (const GeometryPtr other);

    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

    void setTypes    (const GeoPTypesPtr    &value);
    void setLengths  (const GeoPLengthsPtr  &value);
    void setPositions(const GeoPositionsPtr &value);
    void setNormals  (const GeoNormalsPtr   &value);
    void setColors   (const GeoColorsPtr    &value);
    void setTexCoords(const GeoTexCoordsPtr &value);
    void setIndices  (const GeoIndicesPtr   &value);
    void setMaterial (const MaterialPtr     &value);

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

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Draw                                   */
    /*! \{                                                                 */

    // should these be public?	
    Action::ResultE doDraw               (Action * action );
    Action::ResultE draw                 (DrawActionBase *action);
    Action::ResultE render               (Action *action);
    Action::ResultE intersect            (Action * action );

    void            invalidateDlistCache (void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      NodeCore Specific                       */
    /*! \{                                                                 */

    void               adjustVolume     (Volume & volume);

    /*! \}                                                                 */
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

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef GeometryBase Inherited;

    friend class FieldContainer;
    friend class GeometryBase;

    static char cvsid[];

    static void initMethod( void );

    void operator =(const Geometry &source);

};

typedef Geometry *GeometryP;

OSG_END_NAMESPACE

#include <OSGGeometryBase.inl>
#include <OSGGeometry.inl>

#endif /* _OSGGEOMETRY_H_ */
