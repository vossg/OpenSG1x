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

#ifndef _OSGCGFXMATERIAL_H_
#define _OSGCGFXMATERIAL_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGMaterialChunk.h>
#include <OSGTextureChunk.h>
#include <OSGTexGenChunk.h>
#include <OSGBlendChunk.h>
#include <OSGShaderParameterAccess.h>
#include <OSGCGFXChunk.h>

#include <OSGCGFXMaterialBase.h>

OSG_BEGIN_NAMESPACE

/*! \brief CGFXMaterial class. See \ref
           PageKernelCGFXMaterial for a description.
*/

class OSG_CONTRIBLIB_DLLMAPPING CGFXMaterial : public CGFXMaterialBase
{
  private:

    typedef CGFXMaterialBase Inherited;

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

    virtual StatePtr    makeState       (void);
    virtual void        rebuildState    (void);
    virtual StatePtr    getState        (UInt32 index);
    virtual UInt32      getNPasses      (void) const;
    virtual bool        isTransparent   (void) const;

            bool        isTextureParameter(const std::string &name);

            ImagePtr    findImage(const std::string &name);
            Int32       findImage(const ImagePtr &img);
            std::string getTechniqueString(Int32 index);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Timer                                      */
    /*! \{                                                                 */

    typedef Real64 (*timercbfp) (void);
    static void setTimerCB(timercbfp fp);
    static timercbfp getTimerCB(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Parameter Access                             */
    /*! \{                                                                 */

    bool    setParameter(const char *name, bool   value       );
    bool    setParameter(const char *name, Int32  value       );
    bool    setParameter(const char *name, Real32 value       );
    bool    setParameter(const char *name, const Vec2f  &value);
    bool    setParameter(const char *name, const Vec3f  &value);
    bool    setParameter(const char *name, const Vec4f  &value);
    bool    setParameter(const char *name, const Matrix &value);
    bool    setParameter(const char *name, const std::string &value);

    bool    getParameter(const char *name, bool   &value);
    bool    getParameter(const char *name, Int32  &value);
    bool    getParameter(const char *name, Real32 &value);
    bool    getParameter(const char *name, Vec2f  &value);
    bool    getParameter(const char *name, Vec3f  &value);
    bool    getParameter(const char *name, Vec4f  &value);
    bool    getParameter(const char *name, Matrix &value);
    bool    getParameter(const char *name, std::string &value);

    bool    subParameter(const char *name);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Texture specific                              */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in CGFXMaterialBase.

    void onCreate(const CGFXMaterial *source = NULL);
    void onDestroy(void);

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CGFXMaterial(void);
    CGFXMaterial(const CGFXMaterial &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CGFXMaterial(void);

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class CGFXMaterialBase;

    static void initMethod(void);

    static timercbfp _timerFP;

    CGFXChunkPtr          _cgfxChunk;
    ShaderParameterAccess *_parameter_access;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CGFXMaterial &source);
};

typedef CGFXMaterial *CGFXMaterialP;

OSG_END_NAMESPACE

#include <OSGCGFXMaterialBase.inl>
#include <OSGCGFXMaterial.inl>

#define OSGCGFXMATERIAL_HEADER_CVSID "@(#)$Id: OSGCGFXMaterial.h,v 1.1 2006/04/05 16:10:24 a-m-z Exp $"

#endif /* _OSGCGFXMATERIAL_H_ */
