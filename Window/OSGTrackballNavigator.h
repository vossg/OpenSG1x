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

#ifndef _OSG_TRACKBALLNAVIGATOR_H_
#define _OSG_TRACKBALLNAVIGATOR_H_

#include <OSGVector.h>
#include <OSGQuaternion.h>
#include <OSGViewport.h>

OSG_BEGIN_NAMESPACE

/*! \brief TrackballNavigator class
 */

class OSG_SYSTEMLIB_DLLMAPPING TrackballNavigator
{
    /*==========================  PUBLIC  =================================*/
  public:

    enum State
    {
        IDLE=0,
        ROTATING,
        TRANSLATING_XY,
        TRANSLATING_Z
    };


    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TrackballNavigator(Real32 rSize=0.8);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    ~TrackballNavigator();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    const char *getClassname(void) { return "TrackballNavigator"; }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Get                                   */
    /*! \{                                                                 */

    inline Matrix &getMatrix();
    inline State   getState();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Set                                   */
    /*! \{                                                                 */

    inline void setCenter  (Pnt3f new_center);
    inline void setDistance(Real32 new_distance);
    inline void setUp      (Vec3f new_up);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Trackball Transformations                       */
    /*! \{                                                                 */

    inline void rotate     (Real32 fromX, Real32 fromY, 
                            Real32 toX, Real32 toY);
    inline void translateXY(Real32 distanceX, Real32 distanceY);
    inline void translateZ (Real32 distance);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    /*---------------------------------------------------------------------*/
    /*! \name                     Members                                  */
    /*! \{                                                                 */

    Real32 _rRadius,_rDistance;
    Matrix _tMatrix,_finalMatrix;
    State  _currentState;

    /*! \}                                                                 */
    inline Real32 projectToSphere(Real32 rRadius, Real32 rX, Real32 rY);
};


OSG_END_NAMESPACE

#include <OSGTrackballNavigator.inl>

#endif
