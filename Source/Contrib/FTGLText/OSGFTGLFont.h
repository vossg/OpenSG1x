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

#ifndef _OSGFTGLFONT_H_
#define _OSGFTGLFONT_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGFTGLFontBase.h>
#include <OSGWindow.h>

#include <FTGL/FTGLExtrdFont.h>
#include <FTGL/FTGLOutlineFont.h>
#include <FTGL/FTGLPolygonFont.h>
#include <FTGL/FTGLTextureFont.h>
#include <FTGL/FTGLPixmapFont.h>
#include <FTGL/FTGLBitmapFont.h>

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBLIB_DLLMAPPING FTGLFont : public FTGLFontBase
{
  private:

    typedef FTGLFontBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Font Types                                 */
    /*! \{                                                                 */

    enum {  Extrude = 1,
            Outline,
            Polygon,
            Texture,
            Pixmap,
            Bitmap
        };

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
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in FTGLFontBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FTGLFont(void);
    FTGLFont(const FTGLFont &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FTGLFont(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class FTGLFontBase;

    friend class FTGLText; // Needed to get access to the _font and GLId

    static void initMethod(void);

    // local variable. Not nice, but should work ok.
    
    FTFont *_font;

    /*---------------------------------------------------------------------*/
    /*! \name                 GL helper functions                          */
    /*! \{                                                                 */

    void handleGL(Window *win, UInt32 id);

    void onCreate(const FTGLFont *source = NULL);
    
    static void   handleGLDummy    (Window *win, UInt32 id);
    static void   osgGenTextures   (GLsizei n, GLuint *textures);
    static void   osgDeleteTextures(GLsizei n, const GLuint *textures);
    static GLuint osgGenLists      (GLsizei range);
    static void   osgDeleteLists   (GLuint list, GLsizei range);

    /*! \}                                                                 */
    
    // prohibit default functions (move to 'public' if you need one)

    void operator =(const FTGLFont &source);
};

typedef FTGLFont *FTGLFontP;

OSG_END_NAMESPACE

#include <OSGFTGLFontBase.inl>
#include <OSGFTGLFont.inl>

#define OSGFTGLFONT_HEADER_CVSID "@(#)$Id: OSGFTGLFont.h,v 1.1 2004/08/05 05:22:50 dirk Exp $"

#endif /* _OSGFTGLFONT_H_ */
