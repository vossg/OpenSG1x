/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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


#ifndef FRUSTUMVOLUME_CLASS_DECLARATION
#define FRUSTUMVOLUME_CLASS_DECLARATION

#include "OSGConfig.h"
#include "OSGBase.h"
#include "OSGVolume.h"
#include "OSGPlane.h"
#include "OSGMatrix.h"

OSG_BEGIN_NAMESPACE

#ifdef WIN32 // Workaround for a bug in Visual C++ 6.0
class FrustumVolume;

OSG_BASE_DLLMAPPING
bool operator ==(const FrustumVolume &b1, const FrustumVolume &b2);

OSG_BASE_DLLMAPPING
inline
bool operator !=(const FrustumVolume &b1, const FrustumVolume &b2);

ostream& operator<< (ostream & os, const FrustumVolume &obj);
#endif

/** 
@brief 3D frustum defined by 6 planes.
@author jbehr

This box class is used by other classes in ase for data exchange
and storage. It provides representation of the defining corners of a
box in 3D space.

*/

class OSG_BASE_DLLMAPPING FrustumVolume : public Volume
{
    /*==========================  PUBLIC  =================================*/
  public:
    
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
      
    inline FrustumVolume (                                              ); 
    inline FrustumVolume ( const Plane &pnear, const Plane &pfar,
                           const Plane &left,  const Plane &right,
                           const Plane &top,   const Plane &bottom          );
    inline FrustumVolume ( const FrustumVolume &obj                         );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
    
    inline ~FrustumVolume(); 
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Get                                       */
    /*! \{                                                                 */
    
    inline  const   Plane & getNear         (void           ) const;
    inline  const   Plane & getFar          (void           ) const;
    inline  const   Plane & getLeft         (void           ) const;
    inline  const   Plane & getRight        (void           ) const;
    inline  const   Plane & getTop          (void           ) const;
    inline  const   Plane & getBottom       (void           ) const;
    inline  const   Plane * getPlanes       (void           ); 
    inline  const   Plane * getPlanes       (void           ) const; 
    virtual         void    getCenter       (Pnt3f &center  ) const;
    virtual         Real32  getScalarVolume (void           ) const;
    virtual         void    getBounds       ( Pnt3f &minPnt,
                                              Pnt3f &maxPnt ) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Get                                       */
    /*! \{                                                                 */

    void setPlanes(const Plane      &pnear,     const Plane &pfar,
                   const Plane      &left,  const Plane &right,
                   const Plane      &top,   const Plane &bottom         );
    void setPlanes(const Pnt3f      &nlt,   const Pnt3f &nlb,
                   const Pnt3f      &nrt,   const Pnt3f &nrb,
                   const Pnt3f      &flt,   const Pnt3f &flb,
                   const Pnt3f      &frt,   const Pnt3f &frb        );
    void setPlanes(const Matrix &matrix                             );
                                    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Extending                                 */
    /*! \{                                                                 */

    virtual     void extendBy   (const Pnt3f            &pt         );
    inline          void extendBy   (const Volume           &volume     );   
    inline          void extendBy   (const FrustumVolume    &bb         );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Intersection                              */
    /*! \{                                                                 */
  
            bool intersect      (const Pnt3f            &point      ) const;
            bool intersect          (const Line             &line       ) const;
            bool intersect          (const Line             &line,
                                       Real32           &minDist,
                                       Real32           &maxDist    ) const;
    inline      bool intersect          (const Volume           &volume         ) const;
    inline      bool intersect      (const FrustumVolume    &bb             ) const;
    virtual bool isOnSurface    (const Pnt3f            &point      ) const;


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Transformation                            */
    /*! \{                                                                 */
  
    virtual void transform      (const Matrix           &m          );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Assignment                                 */
    /*! \{                                                                 */
    
    const FrustumVolume &operator =(const FrustumVolume &b1);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Output                                  */
    /*! \{                                                                 */


    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const;
    
    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    Plane _planeVec[6];

};

OSG_END_NAMESPACE

#include <OSGFrustumVolume.inl>

#endif /* FRUSTUMVOLUME_CLASS_DECLARATION */
