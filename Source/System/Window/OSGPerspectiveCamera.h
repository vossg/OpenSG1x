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


#ifndef _OSGPERSPECTIVECAMERA_H_
#define _OSGPERSPECTIVECAMERA_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGPerspectiveCameraBase.h>

OSG_BEGIN_NAMESPACE

class DrawAction;

/*! \brief Perspective Camera class. See \ref PageSystemWindowCameraPerspective 
    for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING PerspectiveCamera : public PerspectiveCameraBase
{
   /*==========================  PUBLIC  =================================*/
 public:
    
    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "PerspectiveCamera"; };
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    transformation                            */
    /*! \{                                                                 */

    virtual void changed(BitVector whichField, 
                         UInt32    origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_category                              */
    /*! \{                                                                 */

    virtual void draw( DrawAction * action, const Viewport& port );

    virtual void getProjection( Matrix& result, UInt32 width, UInt32 height );

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
    /*! \name                    Constructors                              */
    /*! \{                                                                 */

    PerspectiveCamera(void);
    PerspectiveCamera(const PerspectiveCamera &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Destructors                               */
    /*! \{                                                                 */

    virtual ~PerspectiveCamera(void); 
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/  
 private:

    typedef PerspectiveCameraBase Inherited;

    friend class FieldContainer;
    friend class PerspectiveCameraBase;

    static void initMethod( void );

    void operator =(const PerspectiveCamera &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

typedef PerspectiveCamera *PerspectiveCameraP;

OSG_END_NAMESPACE

#include <OSGPerspectiveCameraBase.inl>
#include <OSGPerspectiveCamera.inl>

#define OSGPERSPECTIVECAMERA_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.15 2002/06/01 10:37:25 vossg Exp $"

#endif /* _OSGPERSPECTIVECAMERA_H_ */
