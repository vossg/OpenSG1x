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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>

#include "OSGFTGLFont.h"

#include <FTGL/FTLibrary.h>
#include <FTGL/FTGLExtrdFont.h>
#include <FTGL/FTGLOutlineFont.h>
#include <FTGL/FTGLPolygonFont.h>
#include <FTGL/FTGLTextureFont.h>
#include <FTGL/FTGLPixmapFont.h>
#include <FTGL/FTGLBitmapFont.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::FTGLFont

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FTGLFont::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

static void   APIENTRY FTGLFontGenTextures   (GLsizei n, GLuint *textures);
static void   APIENTRY FTGLFontDeleteTextures(GLsizei n, const GLuint *textures);
static GLuint APIENTRY FTGLFontGenLists      (GLsizei range);
static void   APIENTRY FTGLFontDeleteLists   (GLuint list, GLsizei range);

FTGLFont::FTGLFont(void) :
    Inherited(),
    _fonts()
{
    // Set up FTGL
    
	FTLibrary::Instance().setGLCallbacks( (FTLibrary::GenTexturesCB)FTGLFontGenTextures, 
											(FTLibrary::DeleteTexturesCB)FTGLFontDeleteTextures, 
											(FTLibrary::GenListsCB)FTGLFontGenLists, 
											(FTLibrary::DeleteListsCB)FTGLFontDeleteLists);    
}

FTGLFont::FTGLFont(const FTGLFont &source) :
    Inherited(source),
    _fonts()
{
}

FTGLFont::~FTGLFont(void)
{
    for(std::map<Window *, FTFont *>::iterator it = _fonts.begin();
        it != _fonts.end();
        ++it)
    {
        if(it->second)
            delete it->second;
    }
}


void FTGLFont::onCreate(const FTGLFont *)
{
    if(GlobalSystemState == Startup)
        return;

    // !!! this temporary is needed to work around compiler problems (sgi)
    // CHECK CHECK
    //  TextureChunkPtr tmpPtr = FieldContainer::getPtr<TextureChunkPtr>(*this);
    FTGLFontPtr tmpPtr(*this);

    beginEditCP(tmpPtr, FTGLFont::GLIdFieldMask);

    setGLId(
        Window::registerGLObject(
            osgTypedMethodVoidFunctor2ObjCPtrPtr<FTGLFontPtr,
                                                 Window ,
                                                 UInt32>(
                                                     tmpPtr,
                                                     &FTGLFont::handleGL),
            1));

    endEditCP(tmpPtr, FTGLFont::GLIdFieldMask);
}

/*----------------------------- class specific ----------------------------*/

void FTGLFont::changed(BitVector whichField, UInt32 origin)
{
    if(whichField & (NameFieldMask | DrawTypeFieldMask))
    {
        Window::reinitializeGLObject(getGLId());
    }
    
    if(whichField & (SizeFieldMask | DepthFieldMask))
    {
        Window::refreshGLObject(getGLId());
    }
    
    Inherited::changed(whichField, origin);
}

void FTGLFont::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump FTGLFont NI" << std::endl;
}

/*! GL Handling
*/

void FTGLFont::handleGL(Window *win, UInt32 idstatus)
{
    Window::GLObjectStatusE mode;
    UInt32 id;

    Window::unpackIdStatus(idstatus, id, mode);

    FTFont *font = _fonts[win];    
    
    if(mode == Window::initialize || mode == Window::reinitialize)
    {
        if(font != NULL)
            delete font;
        
        switch(getDrawType())
        {
        case Extrude:   font = new FTGLExtrdFont  ( getName().c_str() );
                        break;
        case Outline:   font = new FTGLOutlineFont( getName().c_str() );
                        break;
        case Polygon:   font = new FTGLPolygonFont( getName().c_str() );
                        break;
        case Texture:   font = new FTGLTextureFont( getName().c_str() );
                        break;
        case Pixmap:    font = new FTGLPixmapFont ( getName().c_str() );
                        break;
        case Bitmap:    font = new FTGLBitmapFont ( getName().c_str() );
                        break;
        }
        
        if(font->Error())
        {
            FWARNING(("FTGLFont::handleGL: Couldn't open font '%s'!\n",
                getName().c_str() ));
        }
        font->FaceSize(getSize(), getRes());
        font->Depth(getDepth());
        font->CharMap(ft_encoding_unicode);
    }
    else if(mode == Window::needrefresh)
    {
        font->FaceSize(getSize());
        font->Depth(getDepth());
    }
    else if(mode == Window::destroy)
    {
        delete font;
        font = NULL;
    }
    else if(mode == Window::finaldestroy)
    {
    }
    else
    {
        SWARNING << "FTGLFont(" << this << ")::handleGL: Illegal mode: "
                 << mode << " for id " << id << std::endl;
    }
    
    _fonts[win] = font;  
}

/*! Helper functions to let FTGL use OpenSG GL object handling
*/

void FTGLFontHandleGLDummy(Window *, UInt32 )
{
}

void APIENTRY FTGLFontGenTextures(GLsizei n, GLuint *textures)
{
    for(UInt32 i = 0; i < n; ++i)
        textures[i] = Window::registerGLObject(osgTypedFunctionVoidFunctor2Ptr<
                                                 Window,
                                                 UInt32>(
                                                     &FTGLFontHandleGLDummy), 1);
}

void APIENTRY FTGLFontDeleteTextures(GLsizei n, const GLuint *textures)
{
    for(UInt32 i = 0; i < n; ++i)
        Window::destroyGLObject(textures[i], 1);
}

GLuint APIENTRY FTGLFontGenLists(GLsizei range)
{
    return Window::registerGLObject(osgTypedFunctionVoidFunctor2Ptr<
                                                 Window,
                                                 UInt32>(
                                                     &FTGLFontHandleGLDummy), range);
}

void APIENTRY FTGLFontDeleteLists(GLuint list, GLsizei range)
{
    Window::destroyGLObject(list, range);
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGFTGLFont.cpp,v 1.3 2004/09/07 00:05:42 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGFTGLFONTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGFTGLFONTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGFTGLFONTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

