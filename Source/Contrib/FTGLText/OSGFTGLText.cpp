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

#include <OSGDrawAction.h>
#include <OSGRenderAction.h>

#include "OSGFTGLFont.h"
#include "OSGFTGLText.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::FTGLText

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FTGLText::initMethod (void)
{
    DrawAction::registerEnterDefault( getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, MaterialDrawablePtr,
              CNodePtr, Action *>(&MaterialDrawable::drawActionHandler));
  
    RenderAction::registerEnterDefault( getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, MaterialDrawablePtr,
              CNodePtr, Action *>(&MaterialDrawable::renderActionHandler));
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FTGLText::FTGLText(void) :
    Inherited()
{
}

FTGLText::FTGLText(const FTGLText &source) :
    Inherited(source)
{
}

FTGLText::~FTGLText(void)
{
}


Action::ResultE FTGLText::drawPrimitives(DrawActionBase *action )
{
    FTGLFontPtr font = getFont();
    
    if(font == NullFC)
    {
        FWARNING(("FTGLText::drawPrimitives: no font set!\n"));
        return Action::Continue;
    }
    
    action->getWindow()->validateGLObject(font->getGLId());
    
    FTFont *ftf = font->_fonts[action->getWindow()];
    
    switch(font->getDrawType())
    {
    case FTGLFont::Texture:   
    case FTGLFont::Polygon:   
    case FTGLFont::Extrude:   
    case FTGLFont::Outline: glPushMatrix();
                            glTranslatef(getPosition()[0], 
                                         getPosition()[1], 
                                         getPosition()[2]);
                            glNormal3f(0,0,1);
                            break;
    case FTGLFont::Pixmap:   
    case FTGLFont::Bitmap:  glRasterPos3f(getPosition()[0], 
                                          getPosition()[1], 
                                          getPosition()[2]);
                            break;
    }
   
    ftf->Render(getText().c_str());
    
    switch(font->getDrawType())
    {
    case FTGLFont::Texture:   
    case FTGLFont::Polygon:   
    case FTGLFont::Extrude:   
    case FTGLFont::Outline: glPopMatrix();
                            break;
    case FTGLFont::Pixmap:   
    case FTGLFont::Bitmap:  break;
    }

    return Action::Continue;
}

void FTGLText::adjustVolume(Volume & volume)
{
    FTGLFontPtr font = getFont();
    
    if(font == NullFC)
    {
        FWARNING(("FTGLText::adjustVolume: no font set!\n"));
        return;
    }

    FTFont *f = font->_fonts[NULL];
    if(f == NULL)
    {
        font->handleGL(NULL, Window::reinitialize);
        f = font->_fonts[NULL];
    }
    
    volume.setValid();
    volume.setEmpty();

    volume.extendBy(getPosition());
    
    float x1, y1, z1, x2, y2, z2, px, py, pz;
    f->BBox(getText().c_str(), x1, y1, z1, x2, y2, z2);

    px = getPosition()[0];
    py = getPosition()[1];
    pz = getPosition()[2];
    
    volume.extendBy(Pnt3f(px + x1, py + y1, pz + z1));
    volume.extendBy(Pnt3f(px + x2, py + y1, pz + z1));
    volume.extendBy(Pnt3f(px + x1, py + y2, pz + z1));
    volume.extendBy(Pnt3f(px + x2, py + y2, pz + z1));
    volume.extendBy(Pnt3f(px + x1, py + y1, pz + z2));
    volume.extendBy(Pnt3f(px + x2, py + y1, pz + z2));
    volume.extendBy(Pnt3f(px + x1, py + y2, pz + z2));
    volume.extendBy(Pnt3f(px + x2, py + y2, pz + z2));
}

/*----------------------------- class specific ----------------------------*/

void FTGLText::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void FTGLText::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump FTGLText NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGFTGLText.cpp,v 1.2 2004/09/07 00:05:43 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGFTGLTEXTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGFTGLTEXTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGFTGLTEXTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

