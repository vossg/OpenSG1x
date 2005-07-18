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


#ifndef _OSGOFFCENTERPERSPECTIVECAMERA_H_
#define _OSGOFFCENTERPERSPECTIVECAMERA_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGOffCenterPerspectiveCameraBase.h>

OSG_BEGIN_NAMESPACE

class DrawAction;

/*! \brief OffCenter Perspective Camera class. 
  See for example \ref PageSystemWindowCameraPerspective 
    for a description or take a look at the details.
*/

class OSG_SYSTEMLIB_DLLMAPPING OffCenterPerspectiveCamera : public OffCenterPerspectiveCameraBase
{
   /*==========================  PUBLIC  =================================*/
 public:
    
    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "OffCenterPerspectiveCamera"; };
    
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

    OffCenterPerspectiveCamera(void);
    OffCenterPerspectiveCamera(const OffCenterPerspectiveCamera &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Destructors                               */
    /*! \{                                                                 */

    virtual ~OffCenterPerspectiveCamera(void); 
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/  
 private:

    typedef OffCenterPerspectiveCameraBase Inherited;

    friend class FieldContainer;
    friend class OffCenterPerspectiveCameraBase;

    static void initMethod( void );

    void operator =(const OffCenterPerspectiveCamera &source);


    bool MatrixPerspectivePrincipalPnt(Matrix &result,
				       Real32 rFovy,
				       Real32 rAspect,
				       Real32 rNear,
				       Real32 rFar,
				       Real32 rPrincipalPointX,
				       Real32 rPrincipalPointY);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

typedef OffCenterPerspectiveCamera *OffCenterPerspectiveCameraP;

OSG_END_NAMESPACE

#include <OSGOffCenterPerspectiveCameraBase.inl>
#include <OSGOffCenterPerspectiveCamera.inl>

#define OSGOFFCENTERPERSPECTIVECAMERA_HEADER_CVSID "@(#)$Id: OSGOffCenterPerspectiveCamera.h,v 1.1 2005/07/18 18:46:23 dirk Exp $"

#endif /* _OSGOFFCENTERPERSPECTIVECAMERA_H_ */
