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


#ifndef _OSGTEXTURECHUNK_H_
#define _OSGTEXTURECHUNK_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGWindow.h>
#include <OSGTextureChunkBase.h>

OSG_BEGIN_NAMESPACE

//! chunk for single texture attributes

class OSG_SYSTEMLIB_DLLMAPPING TextureChunk : public TextureChunkBase
{
    /*==========================  PUBLIC  =================================*/
  public:

#ifdef OSG_NOFUNCTORS
    typedef void (TextureChunk::*FunctorFunc)(Window *, UInt32);

    struct TexGLObjectFunctor : public Window::GLObjectFunctor
    {
       public:

        TextureChunkPtr _pObj;
        FunctorFunc     _func;

        virtual void call(Window *win, UInt32 uiOpt)
        {
            (_pObj.getCPtr()->*_func)(win, uiOpt);
        }
    };

    static TexGLObjectFunctor osgMethodFunctor2CPtr(TextureChunkPtr pTexChunk,
                                                    FunctorFunc     func)
    {
        TexGLObjectFunctor result;

        result._pObj = pTexChunk;
        result._func = func;

        return result;
    }
#endif

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "TextureChunk"; };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Instance Functions                            */
    /*! \{                                                                 */

    virtual const StateChunkClass *  getClass( void ) const;

    virtual      bool               isTransparent(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField,
                        ChangeMode from);

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

    virtual void activate   ( DrawActionBase * action, UInt32 index = 0 );

    virtual void changeFrom ( DrawActionBase * action, StateChunk * old,
                             UInt32 index = 0 );

    virtual void deactivate ( DrawActionBase * action, UInt32 index = 0 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Comparison                                 */
    /*! \{                                                                 */

    virtual Real32 switchCost  ( StateChunk * chunk );

    virtual bool   operator <  (const StateChunk &other) const;

    virtual bool   operator == (const StateChunk &other) const;
    virtual bool   operator != (const StateChunk &other) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Texture specific                              */
    /*! \{                                                                 */

    inline void imageContentChanged( void );

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                       Init                                   */
    /*! \{                                                                 */

    void onCreate(const FieldContainer &source);

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

    /*==========================  PRIVATE  ================================*/
  private:

    typedef TextureChunkBase Inherited;

    friend class FieldContainer;
    friend class TextureChunkBase;

    static char cvsid[];

    // class. Used for indexing in State
    static StateChunkClass _class;

    // extension indices for used extensions;
    static UInt32 _extTex3D;

    // extension indices for used fucntions;
    static UInt32 _funcTexImage3D;
    static UInt32 _funcTexSubImage3D;

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

#include <OSGTextureChunk.inl>
#include <OSGTextureChunkBase.inl>

#endif /* _OSGTEXTURECHUNK_H_ */
