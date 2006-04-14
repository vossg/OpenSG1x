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

#ifndef _OSGCGCHUNK_H_
#define _OSGCGCHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include "OSGDrawActionBase.h"
#include "OSGWindow.h"

#include <map>
#include <vector>

#include <OSGCGChunkBase.h>

OSG_BEGIN_NAMESPACE

/*! \brief CGChunk class. See \ref
           PageKernelCGChunk for a description.
*/

class OSG_CONTRIBLIB_DLLMAPPING CGChunk : public CGChunkBase
{
  private:

    typedef CGChunkBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

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
    /*! \name                    Parameter Callbacks                       */
    /*! \{                                                                 */

    typedef void (*parametercbfp) (DrawActionBase *action, CGChunk *cgchunk);

    static void setParameterCallback(parametercbfp fp);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Parameters                             */
    /*! \{                                                                 */

    void updateParameters(Window *win, const MFShaderParameterPtr &parameters,
                          bool force = false);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       CG                                     */
    /*! \{                                                                 */

    typedef struct _OSGCGcontext    *OSGCGcontext;
    typedef struct _OSGCGprogram    *OSGCGprogram;
    typedef struct _OSGCGparameter  *OSGCGparameter;

    OSGCGcontext getContext (void);
    OSGCGprogram getVP      (void);
    bool         isVPValid  (void);
    OSGCGprogram getFP      (void);
    bool         isFPValid  (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       State                                  */
    /*! \{                                                                 */

    virtual void update     ( DrawActionBase * action );

    virtual void activate   ( DrawActionBase * action, UInt32 index = 0 );

    virtual void changeFrom ( DrawActionBase * action, StateChunk * old,
                             UInt32 index = 0 );

    virtual void deactivate ( DrawActionBase * action, UInt32 index = 0 );

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

    // Variables should all be in CGChunkBase.

    void onCreate(const CGChunk *source = NULL);
    void onDestroy(void);

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CGChunk(void);
    CGChunk(const CGChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CGChunk(void);

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class CGChunkBase;

    // class. Used for indexing in State
    static StateChunkClass _class;

    static void initMethod(void);

    void handleGL(Window *win, UInt32 id);

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CGChunk &source);

    static void cgErrorCallback(void);

    bool hasVP(void);
    bool hasFP(void);

    OSGCGcontext                _context;
    OSGCGprogram                _vProgram;
    bool                        _vp_isvalid;
    OSGCGprogram                _fProgram;
    bool                        _fp_isvalid;

    typedef void (*paramtercbfp) (DrawActionBase *action, CGChunk *cgchunk);

    std::vector<paramtercbfp>   _osgParametersCallbacks;
    UInt32 _oldParameterSize;

    void updateCGContext(void);

    void checkOSGParameters(void);
    void updateOSGParameters(DrawActionBase *action);

    typedef GLint (OSG_APIENTRY * PFNGLGETUNIFORMLOCATIONARBPROC)
            (GLuint programObj, const char *name);

    static void updateWorldMatrix       (DrawActionBase *action, CGChunk *cgchunk);
    static void updateInvWorldMatrix    (DrawActionBase *action, CGChunk *cgchunk);
    static void updateCameraOrientation (DrawActionBase *action, CGChunk *cgchunk);
    static void updateCameraPosition    (DrawActionBase *action, CGChunk *cgchunk);
    static void updateProjectionMatrix  (DrawActionBase *action, CGChunk *cgchunk);
    static void updateModelViewProjectionMatrix(DrawActionBase *action, CGChunk *cgchunk);
    static void updateTextureMatrix     (DrawActionBase *action, CGChunk *cgchunk);
    static void updateModelViewMatrix   (DrawActionBase *action, CGChunk *cgchunk);
    static void updateModelViewMatrixI  (DrawActionBase *action, CGChunk *cgchunk);
    static void updateModelViewMatrixIT (DrawActionBase *action, CGChunk *cgchunk);
    static void updateStereoLeftEye     (DrawActionBase *action, CGChunk *cgchunk);

#if 0
    void parseProgramParams(OSGCGprogram prog);
    void parseParams(OSGCGparameter param);
#endif

    static OSGCGcontext _current_context;
    static parametercbfp _userParametersCallback;
};

typedef CGChunk *CGChunkP;

OSG_END_NAMESPACE

#include <OSGCGChunkBase.inl>
#include <OSGCGChunk.inl>

#define OSGCGCHUNK_HEADER_CVSID "@(#)$Id: OSGCGChunk.h,v 1.1 2003/06/25 14:22:43 amz Exp $"

#endif /* _OSGCGCHUNK_H_ */
