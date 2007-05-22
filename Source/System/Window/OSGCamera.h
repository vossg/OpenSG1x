/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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


#ifndef _OSGCAMERA_H_
#define _OSGCAMERA_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGMatrix.h>
#include <OSGFrustumVolume.h>

#include <OSGCameraBase.h>

OSG_BEGIN_NAMESPACE

class Viewport;
class DrawAction;
class DrawActionBase;
class FrustumVolume;
class Line;

/*! \brief Camera base class. See \ref PageSystemWindowCamera for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING Camera : public CameraBase
{
     /*==========================  PUBLIC  =================================*/
 public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "Camera"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   transformation                             */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Setup Rendering                            */
    /*! \{                                                                 */

    virtual void setup          (DrawActionBase *action, const Viewport& port);

    virtual void setupProjection(DrawActionBase *action, const Viewport& port);

    virtual void draw           (DrawAction     *action, const Viewport& port);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Access Parameters                           */
    /*! \{                                                                 */

    virtual void getProjection           (Matrix        &result, 
                                          UInt32 width, UInt32 height);

    virtual void getProjectionTranslation(Matrix        &result, 
                                          UInt32 width, UInt32 height);

    virtual void getViewing              (Matrix        &result, 
                                          UInt32 width, UInt32 height);

    virtual void getFrustum              (FrustumVolume &result,
                                          const Viewport& port);
	
	virtual void getFrustum              (FrustumVolume &result,
                                          UInt32 width, UInt32 height);
	
    virtual void getWorldToScreen        (Matrix        &result, 
                                          const Viewport& port);
										  
	virtual void getDecoration           (Matrix        &result, 
                                          UInt32 width, UInt32 height);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Intersection Helper                          */
    /*! \{                                                                 */
    
    bool calcViewRay(Line & line, Int32 x, Int32 y, const Viewport& port);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    dump                                      */
    /*! \{                                                                 */
    
    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
 protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Camera(void);
    Camera(const Camera &source);
   
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Camera(void); 
    
 
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
 private:
 
    typedef CameraBase Inherited;

    friend class FieldContainer;
    friend class CameraBase;

    static void initMethod( void );

    void operator =(const Camera &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

typedef Camera *CameraP;

OSG_END_NAMESPACE

#include <OSGCameraBase.inl>
#include <OSGCamera.inl>

#define OSGCAMERA_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.15 2002/06/01 10:37:25 vossg Exp $"

#endif /* _OSGCAMERA_H_ */
