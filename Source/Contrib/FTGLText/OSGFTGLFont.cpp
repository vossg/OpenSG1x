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
#include "OSGRemoteAspect.h"

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

FTGLFont::FTGLFont(void) :
    Inherited(),
    _fonts()
{
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
    //  TextureChunkPtr tmpPtr =
    // FieldContainer::getPtr<TextureChunkPtr>(*this);

    RemoteAspect::addFieldFilter(FTGLFont::getClassType().getId(), 
                                 FTGLFont::GLIdFieldMask);

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

    std::map<Window *, FTFont *>::iterator fIt = _fonts.find(win);

    FTFont *font = NULL;

    if(fIt != _fonts.end())
    {
        font = fIt->second;    
    }

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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGFTGLFont.cpp,v 1.5 2006/08/15 09:32:58 vossg Exp $";
    static Char8 cvsid_hpp       [] = OSGFTGLFONTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGFTGLFONTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGFTGLFONTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

