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

#ifndef _OSGDVRSHADER_H_
#define _OSGDVRSHADER_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGDVRShaderBase.h>

#include <OSGDrawActionBase.h>
#include <OSGGL.h>

OSG_BEGIN_NAMESPACE

//! forward declatations
class DVRVolume;
class DVRRenderSlice;
class Brick;

/*! \brief *put brief class description here* 
 */


class OSG_SYSTEMLIB_DLLMAPPING DVRShader : public DVRShaderBase
{
  private:

    typedef DVRShaderBase Inherited;

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
    virtual bool initialize       (DVRVolume      *volume, 
                                   DrawActionBase *action      );

    // Callback before any slice is rendered - setup per volume
    virtual void activate         (DVRVolume      *volume, 
                                   DrawActionBase *action      );

    // Callback before any brick - state setup per brick
    virtual void brickActivate    (DVRVolume      *volume, 
                                   DrawActionBase *action,
                                   Brick          *brick       );

    // Callback after all rendering of the volume is done
    virtual void deactivate       (DVRVolume      *volume, 
                                   DrawActionBase *action      );

    // Callback for rendering non-clipped slices
    virtual void renderSlice      (DVRVolume      *volume, 
                                   DrawActionBase *action,
                                   Real32         *data, 
                                   UInt32          vertices, 
                                   UInt32          values      ); 
    
    // Callback for rendering clipped slices
    virtual void renderSlice      (DVRVolume      *volume, 
                                   DrawActionBase *action,
                                   DVRRenderSlice *clippedSlice);

    // Returns whether the shader has an implementation of 'renderSlice'
    virtual bool hasRenderCallback(void                        );

    // Returns whether the shader requires multitextured slabs instead
    // of bricks
    virtual bool useMTSlabs       (void                        );

    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in DVRShaderBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DVRShader(void);
    DVRShader(const DVRShader &source);

    /*! \}
     */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DVRShader(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DVRShaderBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const DVRShader &source);
};

OSG_END_NAMESPACE

#include <OSGDVRShader.inl>
#include <OSGDVRShaderBase.inl>

#define OSGDVRSHADER_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGDVRSHADER_H_ */
