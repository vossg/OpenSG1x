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

#ifndef _OSGCGFXCHUNK_H_
#define _OSGCGFXCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include <string>
#include <vector>
#include <map>

#include "OSGConfig.h"
#include "OSGDrawActionBase.h"
#include "OSGWindow.h"
#include "OSGTextureChunk.h"
#include "OSGMaterial.h"
#include "OSGChunkMaterial.h"
#include "OSGShaderParameterString.h"

#include "OSGCGFXChunkBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief CGFXChunk class. See \ref
           PageKernelCGFXChunk for a description.
*/

class OSG_CONTRIBLIB_DLLMAPPING CGFXChunk : public CGFXChunkBase
{
  private:

    typedef CGFXChunkBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    enum
    {
        OSG_CG_PROJECTION = 0,
        OSG_CG_WORLDVIEWPROJECTION,
        OSG_CG_WORLD,
        OSG_CG_WORLDI,
        OSG_CG_WORLDIT,
        OSG_CG_WORLDVIEW,
        OSG_CG_WORLDVIEWI,
        OSG_CG_WORLDVIEWIT,
        OSG_CG_VIEW,
        OSG_CG_VIEWI,
        OSG_CG_VIEWIT,
        OSG_CG_VIEWPROJECTION,
        OSG_CG_TIME,
        OSG_CG_LAST
    };

    /*---------------------------------------------------------------------*/
    /*! \name                 Chunk Class Access                           */
    /*! \{                                                                 */

    virtual const StateChunkClass * getClass         (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Static Chunk Class Access                       */
    /*! \{                                                                 */

    inline static        UInt32            getStaticClassId (void);
    inline static  const StateChunkClass * getStaticClass   (void);

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
    /*! \name                    Parameter Callbacks                       */
    /*! \{                                                                 */

    typedef struct _OSGCGeffect     *OSGCGeffect;

    typedef void (*parametercbfp) (DrawActionBase *action, OSGCGeffect effect);

    static void setParameterCallback(parametercbfp fp);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Parameters                            */
    /*! \{                                                                 */

    void setParentMaterial(const ChunkMaterialPtr &parentMaterial);

    void prepareParameters(void);
    void notifyParametersChanged(void);

    void updateImages(void);
    void updateTextureParameter( ShaderParameterStringPtr parameter );

    void setEffectFile(const std::string &effectFile);
    void setEffectString(const std::string &effectString);
    void setCompilerOptions(const std::vector<std::string> &compilerOptions);
    void setTechnique(Int32 technique);
    Int32 getTechniqueIndex(const std::string &name) const;
    std::string getTechniqueString(Int32 index) const;


    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       State                                  */
    /*! \{                                                                 */

    virtual void update     ( DrawActionBase * action );

    virtual void activate   ( DrawActionBase * action, UInt32 index = 0 );

    virtual void changeFrom ( DrawActionBase * action, StateChunk * old,
                             UInt32 index = 0 );

    virtual void deactivate ( DrawActionBase * action, UInt32 index = 0 );

    virtual bool isTransparent (void) const;

    UInt32 getNPasses(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    virtual Real32 switchCost  ( StateChunk * chunk );

    virtual bool   operator <  (const StateChunk &other) const;

    virtual bool   operator == (const StateChunk &other) const;
    virtual bool   operator != (const StateChunk &other) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in CGFXChunkBase.

    void onCreate(const CGFXChunk *source = NULL);
    void onDestroy(void);

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CGFXChunk(void);
    CGFXChunk(const CGFXChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CGFXChunk(void);

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    void setStateParameter(UInt32 type, const std::string &parameterName);

    friend class FieldContainer;
    friend class CGFXChunkBase;

    typedef struct _OSGCGcontext    *OSGCGcontext;
    typedef struct _OSGCGparameter  *OSGCGparameter;
    typedef struct _OSGCGtechnique  *OSGCGtechnique;
    typedef struct _OSGCGpass       *OSGCGpass;

    typedef std::vector< std::pair< std::string, std::string > > Dictionary;
    // maps interface parameters to concrete implementation types
    Dictionary _interfaceImplTypes;

    struct EffectS
    {
        OSGCGcontext context;
        OSGCGeffect effect;
        OSGCGtechnique technique;
        OSGCGpass pass;

        EffectS(void);
        void reset(void);
    };
    void compileEffect( EffectS& effect );
    void extractParametersOfEffect( EffectS& effect );
    void updateParametersOfEffect( EffectS& effect );

    std::vector<EffectS> _effect;

    UInt32 _npasses;

    std::vector<std::string> _state_parameters;
    DrawActionBase          *_action;
    ChunkMaterialPtr         _parentMat;
    std::string              _effectFile;
    std::string              _effectFilePath;
    std::string              _effectString;
    std::vector<std::string> _compilerOptions;
    Int32                   _technique;

    // class. Used for indexing in State
    static StateChunkClass _class;
//    static bool _initializedCGFXGL;
    static Real64 _time;

    static void initMethod(void);

    static void cgErrorCallback(void);

    static void cgIncludeCallback( OSGCGcontext context, const char* filename );
    static void registerIncludeCallback( OSGCGcontext context, CGFXChunk* chunk );
    static std::map< OSGCGcontext, CGFXChunk* > _includeCallbackInstances;

    void initCGFXGL(void);

    void handleGL(Window *win, UInt32 id);
    void updateEffect(Window *win);
    bool updateTechnique(Window *win, OSGCGeffect effect = NULL);
    void updateParameters(Window *win);
    void updateStateParameters(DrawActionBase *action);
    void checkTextureIds(DrawActionBase *action, OSGCGeffect effect);

    void addTextureSearchPaths(void);
    void subTextureSearchPaths(void);
    bool read(const std::string &filename, std::string &data);
    void extractParametersRecursiveHelper(
        const OSGCGparameter &firstParam,
        EffectS& effect,
        Dictionary& interfaceNameMappings );
    void processIncludeCallback( OSGCGcontext context, const char* filename );

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CGFXChunk &source);

    static parametercbfp       _userParametersCallback;
};

typedef CGFXChunk *CGFXChunkP;

OSG_END_NAMESPACE

#include "OSGCGFXChunkBase.inl"
#include "OSGCGFXChunk.inl"

#define OSGCGFXCHUNK_HEADER_CVSID "@(#)$Id: OSGCGFXChunk.h,v 1.10 2009/11/19 16:32:57 macnihilist Exp $"

#endif /* _OSGCGFXCHUNK_H_ */
