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

#ifndef _OSGMANIPULATOR_H_
#define _OSGMANIPULATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGManipulatorBase.h"
#include "OSGExternalUpdateHandler.h"

#include "OSGComponentTransform.h"

OSG_BEGIN_NAMESPACE

/*! \brief Manipulator class. See \ref 
           PageManipulatorsManipulator for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING Manipulator : public ManipulatorBase
{
  private:

    typedef ManipulatorBase Inherited;

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
    
    virtual void mouseMove          (Int16 x, Int16 y);
    virtual void mouseButtonPress   (UInt16 button, Int16 x, Int16 y);
    virtual void mouseButtonRelease (UInt16 button, Int16 x, Int16 y);
    
	inline
    virtual bool hasSubHandle(const NodePtr& n);    
    
    void         setExternalUpdateHandler(ExternalUpdateHandler* h);
    void         callExternalUpdateHandler();

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ManipulatorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Manipulator(void);
    Manipulator(const Manipulator &source);

  	void	onCreate();	
    void    onCreate(const Manipulator* source);


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Manipulator(void); 

    void    onDestroy();    

    /*! \}                                                                 */
    
	
	virtual NodePtr makeHandleGeo() = 0;        
    virtual void    addHandleGeo(NodePtr n);
    virtual void    subHandleGeo(NodePtr n);
    void            reverseTransform();
    
	virtual void    doMovement(TransformPtr t,
							   Int32 coord,
							   Real32 value,
							   const Vec3f      &translation,
							   const Quaternion &rotation,
							   const Vec3f      &scaleFactor,
							   const Quaternion &scaleOrientation ) = 0;
	

    Pnt2f calcScreenProjection(const Pnt3f&, const ViewportPtr& port);
    
    NodePtr                 _activeParent;              
    ExternalUpdateHandler*  _externalUpdateHandler;
              
    /*==========================  PRIVATE  ================================*/
  private:

    ComponentTransformPtr _transHandleXC;
    ComponentTransformPtr _transHandleYC;
    ComponentTransformPtr _transHandleZC;

    friend class FieldContainer;
    friend class ManipulatorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Manipulator &source);
};

typedef Manipulator *ManipulatorP;

OSG_END_NAMESPACE

#include "OSGManipulatorBase.inl"
#include "OSGManipulator.inl"

#define OSGMANIPULATOR_HEADER_CVSID "@(#)$Id: OSGManipulator.h,v 1.1 2005/06/26 12:44:40 a-m-z Exp $"

#endif /* _OSGMANIPULATOR_H_ */
