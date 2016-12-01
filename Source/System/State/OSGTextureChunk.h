/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zghdv.de          *
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


#ifndef _OSGTEXTURECHUNK_H_
#define _OSGTEXTURECHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGGLEXT.h"
#include "OSGWindow.h"
#include "OSGMatrix.h"
#include "OSGTextureChunkBase.h"

OSG_BEGIN_NAMESPACE

#define osgMaxTexImages 16
#define osgMaxTexCoords 8

/*! \brief State chunk for textures. See \ref PageSystemTextureChunk 
    for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING TextureChunk : public TextureChunkBase
{
    /*==========================  PUBLIC  =================================*/
  public:

	/// Flags can be OR-ed, e.g. NPotTexScale for old gpu and YFlip for videos.
	enum NPOTMatrixScaleE 
    { 
        None_TT = 0, 
        NPotTexScale_TT = 1, 
        XFlip_TT = 2, 
        YFlip_TT = 4, 
        ZFlip_TT = 8 
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

    virtual void changed(BitVector whichField,
                         UInt32    origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Output                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       State                                  */
    /*! \{                                                                 */

    virtual void activate   (DrawActionBase * action, UInt32 index = 0);

    virtual void changeFrom (DrawActionBase * action, StateChunk * old,
                             UInt32 index = 0);

    virtual void deactivate (DrawActionBase * action, UInt32 index = 0);

    virtual bool isTransparent (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Comparison                                 */
    /*! \{                                                                 */

    virtual Real32 switchCost  (StateChunk * chunk);

    virtual bool   operator <  (const StateChunk &other) const;

    virtual bool   operator == (const StateChunk &other) const;
    virtual bool   operator != (const StateChunk &other) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Texture specific                              */
    /*! \{                                                                 */

    void imageContentChanged(Int32 minx = -1, Int32 maxx = -1, 
                             Int32 miny = -1, Int32 maxy = -1,
                             Int32 minz = -1, Int32 maxz = -1 );

    void setImage           (const ImagePtr &pImage);

    inline void setShaderOffsetMatrix(Real32 m11, Real32 m12, 
                                      Real32 m21, Real32 m22);
	
	static bool activeMatrix(Matrix &texMat, UInt16 texture);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Multitexture handling                            */
    /*! \{                                                                 */

    static bool hasMultiTexture(Window *win);
    static void activeTexture  (Window *win, UInt16 texture);
    static bool activateTexture(Window *win, UInt16 texture);

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name             some statistics stuff                            */
    /*! \{                                                                 */

    static UInt32 getNumTexCreate(void) { return _numTexCreate; }
    static Time getSummedTexCreateTime(void) { return _summedTexCreateTime; }

    /*! \}                                                                 */
    
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    void onCreate(const TextureChunk *source = NULL);
    void onDestroy(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TextureChunk(void);
    TextureChunk(const TextureChunk &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TextureChunk(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                         GL                                   */
    /*! \{                                                                 */

    inline void triggerRefresh(void);
    inline void triggerReInit (void);
    
    void handleTexture(Window *win, UInt32 id, GLenum bindtarget,
                       GLenum paramtarget,
                       GLenum imgtarget, 
                       Window::GLObjectStatusE mode, 
                       ImagePtr img, int side = 0);

    void handleTextureShader(Window *win, GLenum bindtarget);

    /*! \}                                                                 */ 

    // extension indices for used extensions;
    static UInt32 _extTex3D;
    static UInt32 _arbMultiTex;
    static UInt32 _nvPointSprite;
    static UInt32 _nvTextureShader;
    static UInt32 _nvTextureShader2;
    static UInt32 _nvTextureShader3;
    static UInt32 _sgisGenerateMipmap;
    static UInt32 _extTextureLodBias;
    static UInt32 _arbTextureCompression;
    static UInt32 _arbTextureRectangle;
    static UInt32 _arbTextureNonPowerOfTwo;
    static UInt32 _extTextureFilterAnisotropic;
    
    // extension indices for used fucntions;
    static UInt32 _funcTexImage3D;
    static UInt32 _funcTexSubImage3D;
    static UInt32 _funcActiveTexture;
    static UInt32 _arbCubeTex;
    static UInt32 _funcCompressedTexImage1D;
    static UInt32 _funcCompressedTexSubImage1D;
    static UInt32 _funcCompressedTexImage2D;
    static UInt32 _funcCompressedTexSubImage2D;
    static UInt32 _funcCompressedTexImage3D;
    static UInt32 _funcCompressedTexSubImage3D;

    // class. Used for indexing in State
    // protected to give CubeTextureChunk access
    static StateChunkClass _class;

    // protected to give CubeTextureChunk access
    static void initMethod(void);
    
    
    /*---------------------------------------------------------------------*/
	
  	// defined by NpotMatScale
	static std::vector<bool> _needTexMat;
	
	// the matrix for NpotMatScale
	static std::vector<Matrix> _lastTexMat;
	
	
    // number of texture objects created
    static UInt32 _numTexCreate;

    // summed texture object creation time
    static Time _summedTexCreateTime;

    /*==========================  PRIVATE  ================================*/
  private:

    typedef TextureChunkBase Inherited;

    friend class FieldContainer;
    friend class TextureChunkBase;

    static char cvsid[];

    /*---------------------------------------------------------------------*/
    /*! \name                         GL                                   */
    /*! \{                                                                 */

    void handleGL(Window *win, UInt32 id);
    
   /*! \}                                                                 */

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const TextureChunk &source);
};

typedef TextureChunk *TextureChunkP;

OSG_END_NAMESPACE

#include "OSGTextureChunkBase.inl"
#include "OSGTextureChunk.inl"

#define OSGTEXTURECHUNK_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.15 2002/06/01 10:37:25 vossg Exp $"

#endif /* _OSGTEXTURECHUNK_H_ */
