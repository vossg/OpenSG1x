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


#ifndef CYLINDERVOLUME_CLASS_DECLARATION
#define CYLINDERVOLUME_CLASS_DECLARATION

#include "OSGLine.h"
#include "OSGVolume.h"
#include "OSGVector.h"

OSG_BEGIN_NAMESPACE

/** 3D cylinder in space defined by axis and radius.

This class is used within other classes in ase. It contains data to
represent a cylinder by an axis and a radius. The height of the
cylinder is defined by the length of the axis, i.e. its apex is at
_axisPos + _axisDir.

*/

class OSG_BASE_DLLMAPPING CylinderVolume : public Volume
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    inline CylinderVolume(void);

    inline CylinderVolume(const Pnt3f &p, const Vec3f &d, float r);

    inline CylinderVolume(const CylinderVolume &c);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    inline ~CylinderVolume(void); // {;}

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Set                                   */
    /*! \{                                                                 */

    inline void setValue  (const Pnt3f &p, const Vec3f &d, float r);
    inline void setAxis   (const Pnt3f &p, const Vec3f &d);
    inline void setRadius (float r);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Get                                   */
    /*! \{                                                                 */
    
    inline  void  getAxis         (Pnt3f &apos, Vec3f &adir) const;
    inline  float getRadius       (void) const;
    virtual void  getCenter       (Pnt3f &center) const;
    virtual float getScalarVolume (void) const;
    virtual void  getBounds       ( Pnt3f &min, Pnt3f &max ) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Extend                                */
    /*! \{                                                                 */

    virtual void extendBy (const Pnt3f &pt);
    inline  void extendBy (const Volume &volume);
    inline  void extendBy (const CylinderVolume &obj);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Intersect                             */
    /*! \{                                                                 */

    virtual Bool intersect   (const Pnt3f &point) const;
    Bool intersect           (const Line &line) const;
    virtual Bool intersect   (const Line &line,
                              Real32 &enter, Real32 &exit  ) const;

    virtual Bool intersect   (const Volume &volume) const;
    virtual Bool intersect   (const CylinderVolume &volume) const;
    virtual Bool isOnSurface (const Pnt3f &point) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Transform                             */
    /*! \{                                                                 */

    virtual void transform (const Matrix &mat);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Output                                */
    /*! \{                                                                 */

    virtual void dump(UInt32 uiIndent = 0,
                      const BitVector & bvFlags = 0) const;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    Pnt3f _axisPos;
    Vec3f _axisDir;
    float _radius;

};

OSG_END_NAMESPACE

#include <OSGCylinderVolume.inl>

#endif //CYLINDERVOLUME_CLASS_DECLARATION
