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

#ifndef _OSG_FRUSTUMVOLUME_H_
#define _OSG_FRUSTUMVOLUME_H_

#include "OSGConfig.h"
#include "OSGBase.h"
#include "OSGVolume.h"
#include "OSGPlane.h"
#include "OSGMatrix.h"

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseBaseVolume
 */

class OSG_BASE_DLLMAPPING FrustumVolume : public Volume
{
    /*==========================  PUBLIC  =================================*/

  public:
    
    /*---------------------------------------------------------------------*/
    /*! \name                 Plane Selection                              */
    /*! \{                                                                 */
    
    enum { P_NONE   = 0,
           P_NEAR   = 1, 
           P_FAR    = 2,
           P_LEFT   = 4,
           P_RIGHT  = 8,
           P_TOP    = 16,
           P_BOTTOM = 32,
           P_ALL    = P_NEAR | P_FAR | P_LEFT | P_RIGHT | P_TOP | P_BOTTOM
         };
         
    typedef UInt8 PlaneSet;
         
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
      
    FrustumVolume(      void                                     ); 
    FrustumVolume(const Plane         &pnear, const Plane &pfar,
                  const Plane         &left,  const Plane &right,
                  const Plane         &top,   const Plane &bottom);
    FrustumVolume(const FrustumVolume &obj                       );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
    
    ~FrustumVolume(void); 
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Get                                       */
    /*! \{                                                                 */
    
            const Plane  &getNear        (void         ) const;
            const Plane  &getFar         (void         ) const;
            const Plane  &getLeft        (void         ) const;
            const Plane  &getRight       (void         ) const;
            const Plane  &getTop         (void         ) const;
            const Plane  &getBottom      (void         ) const;
            const Plane  *getPlanes      (void         ) const; 

    virtual       void    getCenter      (Pnt3f &center) const;
    virtual       Real32  getScalarVolume(void         ) const;
    virtual       void    getBounds      (Pnt3f &minPnt,
                                          Pnt3f &maxPnt) const;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Get                                       */
    /*! \{                                                                 */

    void setPlanes(const Plane  &pnear, const Plane &pfar,
                   const Plane  &left,  const Plane &right,
                   const Plane  &top,   const Plane &bottom);
    void setPlanes(const Pnt3f  &nlt,   const Pnt3f &nlb,
                   const Pnt3f  &nrt,   const Pnt3f &nrb,
                   const Pnt3f  &flt,   const Pnt3f &flb,
                   const Pnt3f  &frt,   const Pnt3f &frb   );
    void setPlanes(const Matrix &matrix                    );
                                    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Extending                                 */
    /*! \{                                                                 */

    virtual void extendBy(const Pnt3f         &pt    );
    virtual void extendBy(const Volume        &volume);   
    inline  void extendBy(const FrustumVolume &bb    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Intersection                              */
    /*! \{                                                                 */
  
    virtual bool intersect  (const Pnt3f         &point  ) const;
    virtual bool intersect  (const Line          &line   ) const;
    virtual bool intersect  (const Line          &line,
                                   Real32        &minDist,
                                   Real32        &maxDist) const;
    virtual bool intersect  (const Volume        &volume ) const;
            bool intersect  (const FrustumVolume &bb     ) const;
    virtual bool isOnSurface(const Pnt3f         &point  ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Transformation                            */
    /*! \{                                                                 */
  
    virtual void transform(const Matrix &m);

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
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*==========================  PRIVATE  ================================*/

  private:

    Plane _planeVec[6];

};

OSG_BASE_DLLMAPPING
bool operator ==(const FrustumVolume &b1, const FrustumVolume &b2);

inline
bool operator !=(const FrustumVolume &b1, const FrustumVolume &b2);

OSG_BASE_DLLMAPPING 
bool intersect(const FrustumVolume &frustum, const Volume &vol, 
               FrustumVolume::PlaneSet &inplanes);

OSG_END_NAMESPACE

#include <OSGFrustumVolume.inl>

#endif /* _OSG_FRUSTUMVOLUME_H_ */

