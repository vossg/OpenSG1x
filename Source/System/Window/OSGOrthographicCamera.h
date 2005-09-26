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

#ifndef _OSGORTHOGRAPHICCAMERA_H_
#define _OSGORTHOGRAPHICCAMERA_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGOrthographicCameraBase.h>

OSG_BEGIN_NAMESPACE

/*! \brief OrthographicCamera class. See \ref 
           PageSystemOrthographicCamera for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING OrthographicCamera : public OrthographicCameraBase
{
  private:

    typedef OrthographicCameraBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Camera-specific                             */
    /*! \{                                                                 */

    virtual void draw( DrawAction * action, const Viewport& port );

    virtual void getProjection( Matrix& result, UInt32 width, UInt32 height );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in OrthographicCameraBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    OrthographicCamera(void);
    OrthographicCamera(const OrthographicCamera &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~OrthographicCamera(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class OrthographicCameraBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const OrthographicCamera &source);
};

typedef OrthographicCamera *OrthographicCameraP;

OSG_END_NAMESPACE

#include <OSGOrthographicCameraBase.inl>
#include <OSGOrthographicCamera.inl>

#define OSGORTHOGRAPHICCAMERA_HEADER_CVSID "@(#)$Id: OSGOrthographicCamera.h,v 1.1 2005/09/26 00:08:18 dirk Exp $"

#endif /* _OSGORTHOGRAPHICCAMERA_H_ */
