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

#ifndef _OSGDVRSIMPLESHADER_H_
#define _OSGDVRSIMPLESHADER_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGDVRSimpleShaderBase.h>

OSG_BEGIN_NAMESPACE

/*! \brief *put brief class description here* 
 */

class OSG_SYSTEMLIB_DLLMAPPING DVRSimpleShader : public DVRSimpleShaderBase
{
  private:

    typedef DVRSimpleShaderBase Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     from);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Volume Rendering                             */
    /*! \{                                                                 */

    // Callback to set up shader - register textures here
    virtual bool initialize   (DVRVolume      *volume, 
                               DrawActionBase *action);
    
    // Callback before any slice is rendered - setup per volume
    virtual void activate     (DVRVolume      *volume, 
                               DrawActionBase *action);

    // Callback before any brick - state setup per brick
    virtual void brickActivate(DVRVolume      *volume, 
                               DrawActionBase *action, 
                               Brick          *brick );

    // Callback after all rendering of the volume is done
    virtual void deactivate   (DVRVolume      *volume, 
                               DrawActionBase *action);

    // Callback to clean up shader resources
    virtual void cleanup      (DVRVolume      *volume, 
                               DrawActionBase *action);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in DVRSimpleShaderBase.

    Int32 m_nTextureId;
	 
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DVRSimpleShader(void);
    DVRSimpleShader(const DVRSimpleShader &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DVRSimpleShader(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DVRSimpleShaderBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DVRSimpleShader &source);
};

typedef DVRSimpleShader *DVRSimpleShaderP;

OSG_END_NAMESPACE

#include <OSGDVRSimpleShader.inl>
#include <OSGDVRSimpleShaderBase.inl>

#define OSGDVRSIMPLESHADER_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGDVRSIMPLESHADER_H_ */
