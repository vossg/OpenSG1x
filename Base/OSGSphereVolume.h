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


#ifndef _OSGSPHEREVOLUME_H_
#define _OSGSPHEREVOLUME_H_

#include <OSGVolume.h>

OSG_BEGIN_NAMESPACE

class Line;

/** Sphere in 3D space defined by center and radius.


@author jbehr, dorfmuel, Mon Dec 22 11:32:31 1997

*/

class OSG_BASE_DLLMAPPING SphereVolume : public Volume {

    /*==========================  PUBLIC  =================================*/
public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Constructor                               */
    /*! \{                                                                 */

    SphereVolume(void);
    SphereVolume(const SphereVolume &obj);
    SphereVolume(const Pnt3f &c, float r);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Destructor                                */
    /*! \{                                                                 */

    ~SphereVolume();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Feature                                  */
    /*! \{                                                                 */

    inline void setValue(const Pnt3f &c, float r);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Set Values                                */
    /*! \{                                                                 */

    inline void setCenter(const Pnt3f &c);

    inline void setRadius(float r);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Get Values                                */
    /*! \{                                                                 */

    inline  void  getCenter       (Pnt3f &center)            const;

    inline  const Pnt3f& getCenter( void )                   const;

    inline  float getRadius()                                const;

    virtual float getScalarVolume (void )                    const;

    virtual void  getBounds       ( Pnt3f &min, Pnt3f &max ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Extending                                  */
    /*! \{                                                                 */

    virtual void extendBy (const Pnt3f &pt);

    inline  void extendBy (const Volume &volume);

    inline  void extendBy (const SphereVolume &bb);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Intersection                                 */
    /*! \{                                                                 */

    virtual Bool intersect   (const Pnt3f &point)             const;

            Bool intersect   (const Line &line)               const;

    virtual Bool intersect   ( const Line &line,
                               Real32 &enter, Real32 &exit  ) const;

    inline  Bool intersect   (const Volume &volume)           const;

    inline  Bool intersect   (const SphereVolume &sphere)     const;

    virtual Bool isOnSurface (const Pnt3f &point)             const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Transformation                             */
    /*! \{                                                                 */

    virtual void transform(const Matrix &mat);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Output                                  */
    /*! \{                                                                 */

    virtual void dump(  UInt32              uiIndent = 0,
                        const BitVector &   bvFlags = 0) const;
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    Pnt3f _center;

    float _radius;

};

OSG_END_NAMESPACE

#include <OSGSphereVolume.inl>

#endif // _OSGSPHEREVOLUME_H_
