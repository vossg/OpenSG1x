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

#include <OSGConfig.h>
#include <OSGSystemDef.h>

#include <OSGBaseTypes.h>
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
    /*! \name                        Get                                   */
    /*! \{                                                                 */
    
    Matrix &getMatrix();
	Pnt3f &getFrom();
	Pnt3f &getAt();
	Vec3f &getUp();
    
    /*! \}                                                                 */    
    /*---------------------------------------------------------------------*/
    /*! \name                        Set                                   */
    /*! \{                                                                 */
    
    void setFrom   (Pnt3f new_from);
    void setAt     (Pnt3f new_at);
    void setUp     (Vec3f new_up);
	void set       (Pnt3f new_from, Pnt3f new_at, Vec3f new_up);
    
    /*! \}                                                                 */        
    /*---------------------------------------------------------------------*/
    /*! \name                  Flyer Transformations                       */
    /*! \{                                                                 */
          
    void rotate (Real32 deltaX, Real32 deltaY);
    void forward(Real32 step);
    void right  (Real32 step); 
        
    /*! \}                                                                 */    
    /*==========================  PRIVATE  ================================*/
  private:   
    /*---------------------------------------------------------------------*/
    /*! \name                     Members                                  */
    /*! \{                                                                 */
          
    Pnt3f _rFrom,_rAt;
    Vec3f  _vUp;
    Matrix _tMatrix;
          
    /*! \}                                                                 */
};

OSG_END_NAMESPACE

#define OSGFLYNAVIGATOR_HEADER_CVSID "@(#)$Id: OSGFlyNavigator.h,v 1.3 2002/05/24 14:45:11 istoynov Exp $"

#endif
