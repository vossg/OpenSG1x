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

#ifndef _OSGBOXVOLUME_H_
#define _OSGBOXVOLUME_H_

#include "OSGConfig.h"
#include "OSGVolume.h"

OSG_BEGIN_NAMESPACE

class BoxVolume;

OSG_BASE_DLLMAPPING
bool operator ==(const BoxVolume &b1, const BoxVolume &b2);

inline
bool operator !=(const BoxVolume &b1, const BoxVolume &b2);


/*! 3D box defined by min and max point.

    \ingroup GrpBaseBaseVolume
 */

class OSG_BASE_DLLMAPPING BoxVolume : public Volume
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    BoxVolume(void);

    BoxVolume(Real32 xmin, Real32 ymin, Real32 zmin,
              Real32 xmax, Real32 ymax, Real32 zmax);

    BoxVolume(const Pnt3f     &min,
              const Pnt3f     &max);
    BoxVolume(const BoxVolume &obj);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
    
    ~BoxVolume();
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */
    
            const Pnt3f  &getMin         (void           ) const;    
            const Pnt3f  &getMax         (void           ) const;

    virtual       void    getCenter      (Pnt3f  &center ) const;

    virtual       Real32  getScalarVolume(void           ) const;

    virtual       void    getBounds      (Pnt3f  &min, 
                                          Pnt3f  &max    ) const;


                  void    getBounds      (Real32 &xmin, 
                                          Real32 &ymin, 
                                          Real32 &zmin,
                                          Real32 &xmax,
                                          Real32 &ymax, 
                                          Real32 &zmax   ) const;
    

                  void    getOrigin      (Real32 &originX, 
                                          Real32 &originY, 
                                          Real32 &originZ) const;
                  void    getSize        (Real32 &sizeX, 
                                          Real32 &sizeY, 
                                          Real32 &sizeZ  ) const;
                  void    getSize        (Vec3f  &vec    ) const;    

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void setBounds(      Real32  w,         Real32  h,    Real32 d   );
    void setBounds(      Real32  xmin,      Real32  ymin, Real32 zmin,
                         Real32  xmax,      Real32  ymax, Real32 zmax);
    void setBounds(const Pnt3f  &min, const Pnt3f  &max              );

    void setBoundsByCenterAndSize   ( const Pnt3f &center, 
                                      const Vec3f &size              );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Extend                                  */
    /*! \{                                                                 */

    virtual void extendBy(const Pnt3f     &pt    );
    virtual void extendBy(const Volume    &volume);
            void extendBy(const BoxVolume &bb    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Intersect                               */
    /*! \{                                                                 */

    virtual bool intersect  (const Pnt3f     &point ) const;
    virtual bool intersect  (const Line      &line  ) const;
    virtual bool intersect  (const Line      &line,
                                   Real32    &min, 
                                   Real32    &max   ) const;
    virtual bool intersect  (const Volume    &volume) const;

            bool intersect  (const BoxVolume &bb    ) const;

    virtual bool isOnSurface(const Pnt3f     &point ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Transform                               */
    /*! \{                                                                 */

    virtual void transform(const Matrix &m);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Operators                               */
    /*! \{                                                                 */

    friend OSG_BASE_DLLMAPPING
    bool operator ==(const BoxVolume &b1, const BoxVolume &b2);
  
    const BoxVolume &operator =(const BoxVolume &b1);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Output                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:

    Pnt3f _min;
    Pnt3f _max;
};

OSG_END_NAMESPACE

#include <OSGBoxVolume.inl>

#endif // _OSGBOXVOLUME_H_
