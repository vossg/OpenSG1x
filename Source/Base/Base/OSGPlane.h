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

#ifndef _OSGPLANE_H_
#define _OSGPLANE_H_

#include "OSGBaseTypes.h"
#include "OSGBaseFunctions.h"

#include "OSGVector.h"
#include "OSGMatrix.h"

OSG_BEGIN_NAMESPACE

class Line;

/*! \ingroup GrpBaseBase
 */

class OSG_BASE_DLLMAPPING Plane 
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Constructor                               */
    /*! \{                                                                 */

    Plane(      void                                        );
    Plane(const Plane &obj                                  );
    Plane(const Pnt3f &p0, const Pnt3f  &p1, const Pnt3f &p2);
    Plane(const Vec3f &n,        Real32  d                  );
    Plane(const Vec3f &n, const  Pnt3f  &p                  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~Plane(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Assignment                                */
    /*! \{                                                                 */
    
    Plane &operator =(const Plane &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Offset                                  */
    /*! \{                                                                 */

    void offset(Real32 d);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Intersection                              */
    /*! \{                                                                 */

    bool   intersect        (const Plane  &pl, Line   &intersection) const;
    bool   intersect        (const Line   &l,  Pnt3f  &intersection) const;
    bool   intersect        (const Line   &l,  Real32 &t           ) const;

    bool   intersectInfinite(const Line   &l,  Real32 &t           ) const;
    bool   intersectInfinite(const Line   &l,  Pnt3f  &intersection) const;

    void   transform        (const Matrix &matrix                  );

    int    clip             (Pnt3f *polyIn, Pnt3f *polyOut, int count) const;

    inline bool   isOnPlane          (const Pnt3f  &point          ) const;
    inline bool   isInHalfSpace      (const Pnt3f  &point          ) const;
    inline Real32 distance           (const Pnt3f  &point          ) const;

    inline bool   isInHalfSpace  (const Pnt3f  &min, const Pnt3f  &max) const;
    inline bool   isOutHalfSpace (const Pnt3f  &min, const Pnt3f  &max) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Set Values                                */
    /*! \{                                                                 */

    inline void set(const Vec3f  &normal, 
                          Real32  distance);
    inline void set(      Real32  x, 
                          Real32  y, 
                          Real32  z, 
                          Real32  distance);
    inline void set(const Vec4f  &plane   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */

    inline const Vec3f  &getNormal            (void) const;
    inline       Real32  getDistanceFromOrigin(void) const;


    inline void  setDirectionIndexPoint(
                        const Pnt3f &min, const Pnt3f & max,
                        const UInt8 index,      Pnt3f & pnt) const;
 
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    OSG_BASE_DLLMAPPING
    friend bool operator ==(const Plane &p1, const Plane &p2);

    inline 
    friend bool operator !=(const Plane &p1, const Plane &p2);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:
   
    void updateDirectionIndex(void);

    Vec3f  _normalVec;
    Real32 _distance;
    UInt8  _directionIndex;
};

OSG_BASE_DLLMAPPING 
std::ostream &operator <<(      std::ostream &os, 
                          const Plane        &obj);

OSG_END_NAMESPACE

#include "OSGPlane.inl"

#endif // _OSG_PLANE_H_
