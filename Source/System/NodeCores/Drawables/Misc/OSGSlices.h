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

#ifndef _OSGSLICES_H_
#define _OSGSLICES_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGSlicesBase.h>

#include <OSGAction.h>
#include <OSGDrawActionBase.h>

OSG_BEGIN_NAMESPACE

/*! \brief Simple Dynamic Slices Geo

This is meant as very simple dynamic, view dep. geo (example).
You can use it to slice a 3D-texture block but for
real full-feature volume rendering you should checkout
the OpenSG-Plus Volume-code from the University of Stuttgart.
(Department Visualisation and Interactive Systems)

 */

class OSG_SYSTEMLIB_DLLMAPPING Slices : public SlicesBase
{
  private:

    typedef SlicesBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   action handler                             */
    /*! \{                                                                 */

    // draw the object
    virtual Action::ResultE drawPrimitives (DrawActionBase *action);
    Action::ResultE intersect              (Action * action );

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                      update                                  */
    /*! \{                                                                 */

    void adjustVolume( Volume & volume );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Field Set                                 */
    /*! \{                                                                 */
    
    void setMaterial       (const MaterialPtr     &value);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed ( BitVector  whichField, 
                           UInt32 from);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in SlicesBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Slices(void);
    Slices(const Slices &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Slices(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class SlicesBase;

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)

    struct Edge {
      
      // index in to corner points
      UInt32 pointIndexA;
      UInt32 pointIndexB;
      UInt32 edgeTag;
      
      // pos+vec line def., it's redundant but there is
      // always a need for speed
      Line line;
      
    };

    struct Slice {
      
      /// ccw flag (default: TRUE)
      bool ccw;

      /// number of intersection
      UInt32 numOfIntersection;
      
      /// intersection edge index Vec
      UInt32 edgeVec[6];

      /// intersection point Vec
      Vec3f  pointVec[6];
            
    };

#endif // remove from all but dev docs

    std::vector<Pnt3f> _pointVec;
        
    std::vector<Edge>  _edgeVec;

    static UInt32 _arbMultitexture;
    static UInt32 _funcMultiTexCoord3fARB;
    
    void initEdgeVec     ( void );
    
    unsigned createSlice ( const OSG::Plane &plane, Slice &result );
    
    void     drawSlices  (Window *win, const Vec3f &planeNormal,
                          UInt32 & triCount, UInt32 & vertexCount);

    static void initMethod(void);
    
    // prohibit default functions (move to 'public' if you need one)
    
    void operator =(const Slices &source);
};

typedef Slices *SlicesP;

OSG_END_NAMESPACE

#include <OSGSlicesBase.inl>
#include <OSGSlices.inl>

#define OSGSLICES_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.14 2002/03/25 01:26:00 vossg Exp $"

#endif /* _OSGSLICES_H_ */
