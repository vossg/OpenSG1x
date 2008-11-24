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
#include <OSGTextureChunk.h>
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
    virtual bool        isMultiPass     (void) const;
    virtual UInt32      getNPasses      (void) const;
    virtual bool        isTransparent   (void) const;

    bool        isTextureParameter(const std::string &name);

    Int32       getTechniqueIndex(const std::string &name);
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
    bool    setParameter(const char *name, TextureChunkPtr chunk);

    bool    getParameter(const char *name, bool   &value);
    bool    getParameter(const char *name, Int32  &value);
    bool    getParameter(const char *name, Real32 &value);
    bool    getParameter(const char *name, Vec2f  &value);
    bool    getParameter(const char *name, Vec3f  &value);
    bool    getParameter(const char *name, Vec4f  &value);
    bool    getParameter(const char *name, Matrix &value);
    bool    getParameter(const char *name, std::string &value);
    bool    getParameter(const char *name, TextureChunkPtr &chunk);

    bool    subParameter(const char *name);

    /// Deprecated. Use #prepareParameters().
    void updateImages(void);

    /// Can be called to populate the shader parameter list and load
    /// images needed for texture parameters.
    /// Normally this is done upon the first activate, but this can
    /// cause problems in clusters that discard changelists that are
    /// build during rendering.
    void prepareParameters(void);

    // Image handling. Images are assigned via name to sampler params.
    void addImage(ImagePtr img);
    void subImage(ImagePtr img);
    bool hasImage(ImagePtr img);
    void clearImages(void);
    ImagePtr    findImage(const std::string &name);
    Int32       findImage(const ImagePtr &img);

    // From cg v2.1 on this can be used to provide code of include files that an effect
    // may need, but that are not available on the local file system.
    // (useful for cluster rendering).
    void addVirtualIncludeFile( const std::string& filename, const std::string& filecontent );
    void clearVirtualIncludeFiles();

    // model is 'bool someFunc( std::string const* filename, std::string& filecontent )'
    // filename is passed by pointer, because (by the time of this writing) osg has no
    // means to wrap a instance member function call into a matching functor.
    typedef TypedFunctor2Base<
        bool, PtrCallArg< std::string const >, ArgsCollector< std::string& >
    > VirtualIncludeFileCallback;

    // From cg 2.1 on, every time the cg compiler encounters a #include directive,
    // - first the virtual include files will be searched for a matching filename
    // - if no match is found, this callback is called to give the user of this
    //   material the chance to provide the file's content
    // - if the callback returns false (or is not set), the local filesystem is
    //   searched
    void setVirtualIncludeFileCallback( const VirtualIncludeFileCallback& cb );
    void clearVirtualIncludeFileCallback();

    // FIXME: this is only called by CGFXChunk and should be more private...
    bool requestVirtualIncludeFile( const std::string& filename, std::string& filecontent );

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
    std::vector< VirtualIncludeFileCallback > _virtualIncludeFileCBs;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CGFXMaterial &source);
};

typedef CGFXMaterial *CGFXMaterialP;

OSG_END_NAMESPACE

#include <OSGCGFXMaterialBase.inl>
#include <OSGCGFXMaterial.inl>

#define OSGCGFXMATERIAL_HEADER_CVSID "@(#)$Id: OSGCGFXMaterial.h,v 1.6 2008/11/24 16:05:59 macnihilist Exp $"

#endif /* _OSGCGFXMATERIAL_H_ */
