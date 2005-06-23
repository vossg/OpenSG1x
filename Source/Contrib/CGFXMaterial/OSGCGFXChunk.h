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

#include <OSGConfig.h>
#include <OSGDrawActionBase.h>
#include <OSGWindow.h>
#include <OSGTextureChunk.h>
#include <OSGMaterial.h>
#include <OSGMultiPassMaterial.h>

#include <string>
#include <vector>
#include <map>

#include "OSGCGFXChunkBase.h"

class ICgFXEffect;
struct CgFXPARAMETER_DESC;
struct CgFXEFFECT_DESC;

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
        OSG_CG_VIEW,
        OSG_CG_VIEWI,
        OSG_CG_VIEWIT,
        OSG_CG_TIME,
        OSG_CG_LAST
    };

    virtual const StateChunkClass * getClass         (void) const;

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
    /*! \name                       Paramerters                            */
    /*! \{                                                                 */

    void updateEffect(Window *win);

    void setParentMaterial(const MultiPassMaterialPtr &parentMaterial);

    void updateParameters(Window *win);

    void setEffectFile(const std::string &effectFile);
    void setEffectString(const std::string &effectString);
    void setTechnique(Int32 technique);
    std::string getTechniqueString(Int32 index);

    bool isTextureParameter(const std::string &name);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       State                                  */
    /*! \{                                                                 */

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

    struct EffectS
    {
        ICgFXEffect *effect;
        UInt32 pass;

        EffectS(void);
        void reset(void);
    };

    std::vector<EffectS> _effect;
    typedef std::map<std::string, std::pair<TextureChunkPtr, std::string> > TexturesMap;
    TexturesMap _textures;

    bool _cgfx_changed;
    UInt32 _npasses;

    std::vector<std::string> _state_parameters;
    DrawActionBase          *_action;
    MultiPassMaterialPtr     _parentMat;
    std::string              _effectFile;
    std::string              _effectString;
    Int32                   _technique;

    // class. Used for indexing in State
    static StateChunkClass _class;
    static bool _initializedCGFXGL;
    static Real64 _time;

    static void initMethod(void);

    void handleGL(Window *win, UInt32 id);
    void updateStateParameters(DrawActionBase *action);
    
    void addTextureSearchPaths(void);
    void subTextureSearchPaths(void);
    void initCGFXGL(void);
    bool read(const std::string &filename, std::string &data);
    bool updateTechnique(Window *win, ICgFXEffect *effect = NULL);

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CGFXChunk &source);
};

typedef CGFXChunk *CGFXChunkP;

OSG_END_NAMESPACE

#include <OSGCGFXChunkBase.inl>
#include <OSGCGFXChunk.inl>

#define OSGCGFXCHUNK_HEADER_CVSID "@(#)$Id: OSGCGFXChunk.h,v 1.3 2005/06/23 09:04:45 a-m-z Exp $"

#endif /* _OSGCGFXCHUNK_H_ */
