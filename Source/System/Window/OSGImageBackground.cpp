/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include <OSGNodePtr.h>
#include <OSGViewport.h>
#include <OSGDrawActionBase.h>
#include <OSGImage.h>

#include "OSGImageBackground.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ImageBackground
    \ingroup GrpSystemWindowBackgrounds
    
A background showing an image, see \ref PageSystemWindowBackgroundImage for a
description.

The background color is defined by _sfColor, the image by _sfImage, and the
scaling by _sfScale.

*/

/*----------------------- constructors & destructors ----------------------*/

ImageBackground::ImageBackground(void) :
    Inherited()
{
}

ImageBackground::ImageBackground(const ImageBackground &source) :
    Inherited(source)
{
}

ImageBackground::~ImageBackground(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ImageBackground::initMethod (void)
{
}

void ImageBackground::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ImageBackground::clear(DrawActionBase *, Viewport *vp)
{
    glClearColor(_sfColor.getValue()[0],
                 _sfColor.getValue()[1],
                 _sfColor.getValue()[2],
                 1);                 
    
    ImagePtr img = getImage();

    if(img == NullFC || img->getWidth() <= 0 || img->getHeight() <= 0)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        return; 
    }

    glClear(GL_COLOR_BUFFER_BIT);
    
    GLboolean depth = glIsEnabled(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);

    glDisable(GL_TEXTURE_2D);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, 0, 1);
  
    if(getScale())
    {   
        glPixelZoom(vp->getPixelWidth () / (Real32)img->getWidth (),
                    vp->getPixelHeight() / (Real32)img->getHeight());
    }

    glRasterPos2f(0, 0);
    glDrawPixels(img->getWidth(), img->getHeight(),
                 img->getPixelFormat(), GL_UNSIGNED_BYTE,
                 img->getData() );

    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    if(getScale())
        glPixelZoom(1, 1);

    if(depth == GL_TRUE)    
        glEnable(GL_DEPTH_TEST);
    
    glClear(GL_DEPTH_BUFFER_BIT);
}

void ImageBackground::dump(      UInt32     , 
                           const BitVector  ) const
{
    SLOG << "Dump ImageBackground NI" << std::endl;
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: $";
    static char cvsid_hpp[] = OSGIMAGEBACKGROUND_HEADER_CVSID;
    static char cvsid_inl[] = OSGIMAGEBACKGROUND_INLINE_CVSID;
}

