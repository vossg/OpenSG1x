/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#include <OSGConfig.h>
#include <OSGWindow.h>
#include <OSGTextureChunkBase.h>

OSG_BEGIN_NAMESPACE

#define osgMaxTextures 4

//! chunk for single texture attributes

class OSG_SYSTEMLIB_DLLMAPPING TextureChunk : public TextureChunkBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                Instance Functions                            */
    /*! \{                                                                 */

    virtual const StateChunkClass *getClass(void) const;

    virtual      bool              isTransparent(void) const;

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

    inline void imageContentChanged( void );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Multitexture handling                            */
    /*! \{                                                                 */

    static inline bool hasMultiTexture(Window *win);
    static inline void activeTexture  (Window *win, UInt16 texture);
    static inline void activateTexture(Window *win, UInt16 texture);

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    void onCreate(const TextureChunk *source = NULL);

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

    void handleTexture(Window *win, UInt32 id, GLenum bindtarget,
                       GLenum paramtarget,
                       GLenum imgtarget, 
                       Window::GLObjectStatusE mode, Image *img);

    /*! \}                                                                 */ 

    // extension indices for used extensions;
    static UInt32 _extTex3D;
    static UInt32 _arbMultiTex;
    
    // extension indices for used fucntions;
    static UInt32 _funcTexImage3D;
    static UInt32 _funcTexSubImage3D;
    static UInt32 _funcActiveTexture;
    static UInt32 _arbCubeTex;

    /*==========================  PRIVATE  ================================*/
  private:

    typedef TextureChunkBase Inherited;

    friend class FieldContainer;
    friend class TextureChunkBase;

    static char cvsid[];

    // class. Used for indexing in State
    static StateChunkClass _class;

    static void initMethod( void );

    /*---------------------------------------------------------------------*/
    /*! \name                         GL                                   */
    /*! \{                                                                 */

    void handleGL( Window *win, UInt32 id );
    
   /*! \}                                                                 */

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const TextureChunk &source);
};

typedef TextureChunk *TextureChunkP;

OSG_END_NAMESPACE

#include <OSGTextureChunkBase.inl>
#include <OSGTextureChunk.inl>

#endif /* _OSGTEXTURECHUNK_H_ */
