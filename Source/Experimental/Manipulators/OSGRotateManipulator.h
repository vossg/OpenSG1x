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

#ifndef _OSGROTATEMANIPULATOR_H_
#define _OSGROTATEMANIPULATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGRotateManipulatorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief RotateManipulator class. See \ref 
           PageManipulatorsRotateManipulator for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING RotateManipulator : public RotateManipulatorBase
{
  private:

    typedef RotateManipulatorBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

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

    // Variables should all be in RotateManipulatorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    RotateManipulator(void);
    RotateManipulator(const RotateManipulator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~RotateManipulator(void); 

    /*! \}                                                                 */

	virtual NodePtr makeHandleGeo();    
	virtual void    doMovement(TransformPtr t,
							   Int32 coord,
							   Real32 value,
							   const Vec3f      &translation,
							   const Quaternion &rotation,
							   const Vec3f      &scaleFactor,
							   const Quaternion &scaleOrientation );

    /*==========================  PRIVATE  ================================*/
private:

    friend class FieldContainer;
    friend class RotateManipulatorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const RotateManipulator &source);
};

typedef RotateManipulator *RotateManipulatorP;

OSG_END_NAMESPACE

#include "OSGRotateManipulatorBase.inl"
#include "OSGRotateManipulator.inl"

#define OSGROTATEMANIPULATOR_HEADER_CVSID "@(#)$Id: OSGRotateManipulator.h,v 1.1 2005/06/26 12:44:40 a-m-z Exp $"

#endif /* _OSGROTATEMANIPULATOR_H_ */
