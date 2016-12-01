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

#ifndef _OSGPHYSICSGEOM_H_
#define _OSGPHYSICSGEOM_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGSimpleAttachments.h"
#include <ode/ode.h>

#include "OSGPhysicsGeomBase.h"

OSG_BEGIN_NAMESPACE

class  OSG_CONTRIBLIB_DLLMAPPING PhysicsGeom : public PhysicsGeomBase
{
  private:

    typedef PhysicsGeomBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
	  /*---------------------------------------------------------------------*/
	  /*! \name                   Class Specific Get Field                    */
	  /*! \{                                                                 */
	  PhysicsBodyPtr getBody(void);
	  Vec3f getPosition(void);
	  Matrix getRotation(void);
	  Quaternion getQuaternion(void);
	  UInt64 getCategoryBits(void);
	  UInt64 getCollideBits(void);
      PhysicsSpacePtr getSpace(void);
      bool getEnable(void);
      dGeomID getGeomID(void);
	  /*! \}                                                                 */

	  /*---------------------------------------------------------------------*/
	  /*! \name                   Class Specific Set Field                    */
	  /*! \{                                                                 */
	  void setBody(const PhysicsBodyPtr &value);
	  void setPosition(const Vec3f &value );
	  void setRotation(const Matrix &value );
	  void setQuaternion(const Quaternion &value );
	  void setCategoryBits(const UInt64 &value );
	  void setCollideBits(const UInt64 &value );
      void setSpace(const PhysicsSpacePtr &value );
      void setEnable(const bool &value );
      void setGeomID(const dGeomID &value);
	  /*! \}                                                                 */

	  /*---------------------------------------------------------------------*/
	  /*! \name                   Class Specific                             */
	  /*! \{																*/
	  void getAABB(Real32 aabb[6]);
	  Int32 isSpace(void);
	  Int32 getGeomClass(void);
	  bool isEnabled(void);
	  void setData(void* someData);
	  void* getData(void);
	  void Collide2(dGeomID  otherGID, void* someData, dNearCallback* callback);
      void initGeom();
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

    // Variables should all be in PhysicsGeomBase.
    // hmmm...not for this class
    //ode Geometry Id
    dGeomID id;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PhysicsGeom(void);
    PhysicsGeom(const PhysicsGeom &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PhysicsGeom(void); 

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const PhysicsGeom *id = NULL);
	void onDestroy();
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class PhysicsGeomBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const PhysicsGeom &source);
};

typedef PhysicsGeom *PhysicsGeomP;

OSG_END_NAMESPACE

#include "OSGPhysicsGeomBase.inl"
#include "OSGPhysicsGeom.inl"

#define OSGPHYSICSGEOM_HEADER_CVSID "@(#)$Id: OSGPhysicsGeom.h,v 1.2 2006/08/19 00:21:46 dirk Exp $"

#endif /* _OSGPHYSICSGEOM_H_ */
