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

#ifndef _OSGDVRMTEXLUTSHADER_H_
#define _OSGDVRMTEXLUTSHADER_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGDVRMtexLUTShaderBase.h>

OSG_BEGIN_NAMESPACE

// forward reference
class DVRRenderSlice;

/*! \brief *put brief class description here* 
 */

class OSG_SYSTEMLIB_DLLMAPPING DVRMtexLUTShader : public DVRMtexLUTShaderBase
{
private:

    typedef DVRMtexLUTShaderBase Inherited;

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

    // Callback after all rendering of the volume is done
    virtual void deactivate       (DVRVolume      *volume, 
                                   DrawActionBase *action      );

    // Callback for rendering slices
    virtual void renderSlice      (DVRVolume      *volume, 
                                   DrawActionBase *action,
                                   Real32         *data, 
                                   UInt32          vertices, 
                                   UInt32          values      );

    // Callback for rendering slices
    virtual void renderSlice      (DVRVolume      *volume, 
                                   DrawActionBase *action,
                                   DVRRenderSlice *clippedSlice);

    // Callback to clean up shader resources
    virtual void cleanup          (DVRVolume      *volume, 
                                   DrawActionBase *action      );

    // Returns whether the shader has an implementation of 'renderSlice'
    virtual bool hasRenderCallback(void                        );
    
    // Returns whether the shader requires multitextured slabs instead of
    // bricks
    virtual bool useMTSlabs       (void                        ); 

    /*! \{                                                                 */
    /*=========================  PROTECTED  ===============================*/
  
  protected:

    // Variables should all be in DVRMtexLUTShaderBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DVRMtexLUTShader(void);
    DVRMtexLUTShader(const DVRMtexLUTShader &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DVRMtexLUTShader(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/

  private:

    // extension indices for used extensions;
    static UInt32 _arbMultitexture;
    static UInt32 _nvRegisterCombiners;
    
    // extension indices for used fucntions;
    static UInt32 _funcMultiTexCoord2dARB;
    static UInt32 _funcCombinerParameteriNV;
    static UInt32 _funcCombinerParameterfvNV;
    static UInt32 _funcCombinerInputNV;
    static UInt32 _funcCombinerOutputNV;
    static UInt32 _funcFinalCombinerInputNV;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Volume Rendering                             */
    /*! \{                                                                 */

    // Set up correct register combiner state
    void initCombiners(DrawActionBase *action); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    
    friend class FieldContainer;
    friend class DVRMtexLUTShaderBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DVRMtexLUTShader &source);
};

typedef DVRMtexLUTShader *DVRMtexLUTShaderP;

OSG_END_NAMESPACE

#include <OSGDVRMtexLUTShader.inl>
#include <OSGDVRMtexLUTShaderBase.inl>

#define OSGDVRMTEXLUTSHADER_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGDVRMTEXLUTSHADER_H_ */
