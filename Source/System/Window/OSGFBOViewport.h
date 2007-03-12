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

#ifndef _OSGFBOVIEWPORT_H_
#define _OSGFBOVIEWPORT_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGGL.h>
#include <OSGGLEXT.h>
#include <OSGWindow.h>
#include <OSGAction.h>
#include <OSGRenderAction.h>

#include "OSGFBOViewportBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief FBOViewport class. See \ref 
           PageExtentionFBOViewport for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING FBOViewport : public FBOViewportBase
{
  private:

    typedef FBOViewportBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
  
     enum RenderBufferAttachmentType
     {
        NONE            = 0,
        FBO_DEPTH_16    = 1,
        FBO_DEPTH_24    = 2,
        FBO_DEPTH_32    = 4,
        FBO_STENCIL_1   = 8,
        FBO_STENCIL_4   = 16,
        FBO_STENCIL_8   = 32,
        FBO_STENCIL_16  = 64
     };

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */
    
    static const char *getClassname(void) { return "FBOViewport"; }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Render                                    */
    /*! \{                                                                 */

    virtual void render(RenderActionBase *action);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

     bool initialize(Window *win, Int32 format = NONE);
     void setTarget(Window *win, UInt32 id, GLenum attachment, GLenum target);
     void bind(Window *win);
     void stop(Window *win);
     bool checkFrameBufferStatus(Window *win);
     Int32 getMaxBuffers(void);

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
    /*---------------------------------------------------------------------*/
    /*! \name                     Callbacks                                */
    /*! \{                                                                 */

    enum
    {
        FBO_RP_NONE = 0,
        FBO_RP_EFFECTS = 1
    };

    typedef void (*renderparamscbfp) (UInt32 params);
    static void setRenderParamsCB(renderparamscbfp fp);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in FBOViewportBase.

    bool extensionCheck(void);

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FBOViewport(void);
    FBOViewport(const FBOViewport &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FBOViewport(void); 

    void onCreate(const FBOViewport *source = NULL);
    void onDestroy(void);

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class FBOViewportBase;
    
    /*---------------------------------------------------------------------*/
    /*! \name            OpenGL Extension Handling                         */
    /*! \{                                                                 */

    static UInt32 _framebuffer_object_extension;
    static UInt32 _draw_buffers_extension;

    static UInt32 _funcDrawBuffers;
    static UInt32 _funcBindFramebuffer;
    static UInt32 _funcBindRenderbuffer;
    static UInt32 _funcCheckFramebufferStatus;
    static UInt32 _funcDeleteFramebuffers;
    static UInt32 _funcDeleteRenderbuffers;
    static UInt32 _funcFramebufferRenderbuffer;
    static UInt32 _funcFramebufferTexture1D;
    static UInt32 _funcFramebufferTexture2D;
    static UInt32 _funcFramebufferTexture3D;
    static UInt32 _funcGenFramebuffers;
    static UInt32 _funcGenRenderbuffers;
    static UInt32 _funcGenerateMipmap;
    static UInt32 _funcGetFramebufferAttachmentParameteriv;
    static UInt32 _funcGetRenderbufferParameteriv;
    static UInt32 _funcIsFramebuffer;
    static UInt32 _funcIsRenderbuffer;
    static UInt32 _funcRenderbufferStorage;

    static renderparamscbfp _renderParamsFP;
    /*! \}                                                                 */
    
    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const FBOViewport &source);
};

typedef FBOViewport *FBOViewportP;

OSG_END_NAMESPACE

#include "OSGFBOViewportBase.inl"
#include "OSGFBOViewport.inl"

#define OSGFBOVIEWPORT_HEADER_CVSID "@(#)$Id: OSGFBOViewport.h,v 1.1 2007/03/12 15:03:01 a-m-z Exp $"

#endif /* _OSGFBOVIEWPORT_H_ */
