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

#ifndef _OSG_FLYNAVIGATOR_H_
#define _OSG_FLYNAVIGATOR_H_

#include <OSGVector.h>
#include <OSGQuaternion.h>

OSG_BEGIN_NAMESPACE

/*! \brief FlyNavigator class
 */

class OSG_SYSTEMLIB_DLLMAPPING FlyNavigator
{
    /*==========================  PUBLIC  =================================*/
  public:    
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
                
    FlyNavigator();
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
    
    ~FlyNavigator();
    
    /*! \}                                                                 */    
    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */    
 
    const char *getClassname(void) { return "FlyNavigator"; }
    
    /*! \}                                                                 */    
    /*---------------------------------------------------------------------*/
    /*! \name                        Get                                   */
    /*! \{                                                                 */
    
    inline Matrix &getMatrix();
    
    /*! \}                                                                 */    
    /*---------------------------------------------------------------------*/
    /*! \name                        Set                                   */
    /*! \{                                                                 */
    
    inline void setFrom(Pnt3f new_eye);
    inline void setAt  (Pnt3f new_center);
    inline void setUp  (Vec3f new_up);
    
    /*! \}                                                                 */        
    /*---------------------------------------------------------------------*/
    /*! \name                  Flyer Transformations                       */
    /*! \{                                                                 */
          
    inline void rotate (Real32 deltaX, Real32 deltaY);
    inline void forward(Real32 step);
    inline void right  (Real32 step); 
        
    /*! \}                                                                 */    
    /*==========================  PRIVATE  ================================*/
  private:   
    /*---------------------------------------------------------------------*/
    /*! \name                     Members                                  */
    /*! \{                                                                 */
          
    Pnt3f _rEye,_rCenter;
    Vec3f  _vUp;
    Matrix _tMatrix;
          
    /*! \}                                                                 */
};


OSG_END_NAMESPACE
        
#include <OSGFlyNavigator.inl>

#endif
