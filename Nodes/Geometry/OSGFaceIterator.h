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


#ifndef _OSGFACEITERATOR_H_
#define _OSGFACEITERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBaseTypes.h>
#include <OSGFieldContainerPtr.h>
#include <OSGNodePtr.h>
#include <OSGNodeCore.h>
#include <OSGSystemDef.h>
#include <OSGGeoProperty.h>
#include <OSGPrimitiveIterator.h>

OSG_BEGIN_NAMESPACE


class Geometry;
typedef FCPtr<NodeCorePtr, Geometry> GeometryPtr;

/*! \brief The FaceIterator allows iteration through faces, i.e. tris and/or quads.
 *  \ingroup GeoIterators
 */

class OSG_SYSTEMLIB_DLLMAPPING FaceIterator
{
    /*==========================  PUBLIC  =================================*/    
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "FaceIterator"; }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */  

    FaceIterator( void );
    FaceIterator( const FaceIterator &source);
    FaceIterator( const GeometryPtr& geo );
    FaceIterator( const NodePtr& geo );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
    
    virtual ~FaceIterator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Access                                     */
    /*! \{                                                                 */
    
    inline Int32        getIndex            ( void        ) const;
    inline UInt32       getType             ( void        ) const;
    inline UInt32       getLength           ( void        ) const;
    
    inline Int32        getPositionIndex    ( Int32 which ) const;
    inline Pnt3f        getPosition         ( Int32 which ) const;

    inline Int32        getNormalIndex      ( Int32 which ) const;
    inline Vec3f        getNormal           ( Int32 which ) const;

    inline Int32        getColorIndex       ( Int32 which ) const;
    inline Color3f      getColor            ( Int32 which ) const;

    inline Int32        getTexCoordsIndex   ( Int32 which ) const;
    inline Vec2f        getTexCoords        ( Int32 which ) const;

    inline Int32        getIndexIndex       ( Int32 which ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Your operators                         */
    /*! \{                                                                 */

    void           seek        (Int32 index);    
    void           operator ++ (void);
    FaceIterator & operator =  (const FaceIterator &source);
    Bool           operator <  (const FaceIterator &other) const;
    Bool           operator == (const FaceIterator &other) const;
    Bool           operator != (const FaceIterator &other) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */

    void setToBegin( void );
    void setToEnd  ( void );

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
  protected:
          
   /*==========================  PRIVATE  ================================*/    
  private:
    static char cvsid[];
  
    PrimitiveIterator _primIt;
    GeometryPtr       _geo;
    Int32             _faceIndex;
    UInt32            _actPrimIndex;
    Int32             _facePntIndex[4];
    
    void startPrim( void );
};

typedef FaceIterator *FaceIteratorP;

OSG_END_NAMESPACE

#include "OSGFaceIterator.inl"

#endif /* _OSGTRIANGLEITERATOR_H_ */
