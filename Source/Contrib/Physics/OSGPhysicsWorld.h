/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#ifndef _OSGPHYSICSWORLD_H_
#define _OSGPHYSICSWORLD_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include <ode/ode.h>

#include "OSGPhysicsWorldBase.h"

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBLIB_DLLMAPPING PhysicsWorld : public PhysicsWorldBase
{
  private:

    typedef PhysicsWorldBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific Get Field                    */
	/*! \{                                                                 */
	Real32	getErp(void);
	Real32	getCfm(void);
	Vec3f	getGravity(void);
	Int32	getAutoDisableFlag(void);
	Real32	getAutoDisableLinearThreshold(void);
	Real32	getAutoDisableAngularThreshold(void);
	Int32	getAutoDisableSteps(void);
	Real32	getAutoDisableTime(void);
	Int32	getWorldQuickStepNumIterations(void);
	Real32	getWorldContactMaxCorrectingVel(void);
	Real32	getWorldContactSurfaceLayer(void);
    dWorldID getWorldID(void);

	/*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific Set Field                    */
	/*! \{                                                                 */
	void setErp(const Real32 &value);
	void setCfm(const Real32 &value);
	void setGravity(const Vec3f &value );
	void setAutoDisableFlag(const Int32 &value );
	void setAutoDisableLinearThreshold(const Real32 &value );
	void setAutoDisableAngularThreshold(const Real32 &value );
	void setAutoDisableSteps(const Int32 &value );
	void setAutoDisableTime(const Real32 &value );
	void setWorldQuickStepNumIterations(const Int32 &value );
	void setWorldContactMaxCorrectingVel(const Real32 &value );
	void setWorldContactSurfaceLayer(const Real32 &value );
	/*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void worldImpulseToForce(Real32 stepsize, Real32 x, Real32 y, Real32 z, Vec3f force);
	void worldStep(Real32 stepsize);
	void worldQuickStep(Real32 stepsize);
    void initWorld();
	/*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in PhysicsWorldBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PhysicsWorld(void);
    PhysicsWorld(const PhysicsWorld &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PhysicsWorld(void); 

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */

	void onCreate(const PhysicsWorld *id = NULL);
	void onDestroy();
	
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class PhysicsWorldBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const PhysicsWorld &source);

    //ODE worldID
    dWorldID id;
};

typedef PhysicsWorld *PhysicsWorldP;

OSG_END_NAMESPACE

#include "OSGPhysicsWorldBase.inl"
#include "OSGPhysicsWorld.inl"

#define OSGPHYSICSWORLD_HEADER_CVSID "@(#)$Id: OSGPhysicsWorld.h,v 1.2 2006/08/19 00:21:47 dirk Exp $"

#endif /* _OSGPHYSICSWORLD_H_ */
