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


#ifndef BOX3F_CLASS_DECLARATION
#define BOX3F_CLASS_DECLARATION

#include "OSGConfig.h"
#include "OSGVolume.h"

OSG_BEGIN_NAMESPACE

#ifdef WIN32 // Workaround for a bug in Visual C++ 6.0
class BoxVolume;
OSG_BASE_DLLMAPPING bool          operator ==(const BoxVolume &b1, 
                                              const BoxVolume &b2);
OSG_BASE_DLLMAPPING bool          operator !=(const BoxVolume &b1, 
                                              const BoxVolume &b2);
OSG_BASE_DLLMAPPING std::ostream &operator <<(      std::ostream &os, 
                                              const BoxVolume    &obj);
#endif

/** 3D box defined by min and max point.

This box class is used by other classes in ase for data exchange
and storage. It provides representation of the defining corners of a
box in 3D space.

@author jbehr, Mon Dec 22 11:32:31 1997

*/

class OSG_BASE_DLLMAPPING BoxVolume : public Volume
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    inline BoxVolume();
    inline BoxVolume ( float xmin, float ymin, float zmin,
                       float xmax, float ymax, float zmax) ;
    inline BoxVolume(const Pnt3f &min, const Pnt3f &max);
    inline BoxVolume(const BoxVolume &obj);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
    
    inline ~BoxVolume();
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */
    
    inline const Pnt3f &getMin() const;    
    inline const Pnt3f &getMax() const;

            void     getCenter(Pnt3f &center) const;

    virtual Real32   getScalarVolume (void) const;
    inline  void     getBounds(float &xmin, float &ymin, float &zmin,
                               float &xmax, float &ymax, float &zmax ) const;
    
    inline  void     getBounds(Pnt3f &min, Pnt3f &max) const;
    inline  void     getOrigin(float &originX, float &originY, 
                               float &originZ) const;
    inline  void     getSize  (float &sizeX, float &sizeY, 
                               float &sizeZ) const;
    inline  void     getSize  (Vec3f &vec) const;    

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    inline void setBounds(float w, float h, float d);
    inline void setBounds(float xmin, float ymin, float zmin,
                          float xmax, float ymax, float zmax);
    inline void setBounds(const Pnt3f &min, const Pnt3f &max);

    void setBoundsByCenterAndSize(const Pnt3f &center, const Vec3f &size);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Extend                                  */
    /*! \{                                                                 */

    virtual void extendBy (const Pnt3f &pt);
    inline  void extendBy (const Volume &volume);
    inline  void extendBy (const BoxVolume &bb);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Intersect                               */
    /*! \{                                                                 */

    bool intersect (const Pnt3f &point) const;
    bool intersect (const Line &line) const;
    bool intersect (const Line &line,Real32 &min, Real32 &max) const;
    inline bool intersect (const Volume &volume) const;
    inline bool intersect(const BoxVolume &bb) const;
    virtual bool isOnSurface (const Pnt3f &point) const;

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
                  bool        operator ==(const BoxVolume &b1, const BoxVolume &b2);
  
    inline friend bool operator !=(const BoxVolume &b1, const BoxVolume &b2);

    const BoxVolume   &operator  =(const BoxVolume &b1);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Output                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:
    Pnt3f _min;
    Pnt3f _max;
};

OSG_END_NAMESPACE

#include <OSGBoxVolume.inl>

#endif // BOX_CLASS_DECLARATION
