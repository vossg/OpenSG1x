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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>

#include <OSGViewport.h>
#include <OSGDrawActionBase.h>

#include "OSGImageBackground.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: OSGImageBackground.cpp,v 1.3 2001/11/01 09:03:30 vossg Exp $";
    static char cvsid_hpp[] = OSGIMAGEBACKGROUND_HEADER_CVSID;
    static char cvsid_inl[] = OSGIMAGEBACKGROUND_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/*! \class osg::ImageBackground
A background showing an image.
*/

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

ImageBackground::ImageBackground(void) :
    Inherited()
{
}

//! Copy Constructor

ImageBackground::ImageBackground(const ImageBackground &source) :
    Inherited(source)
{
}

//! Destructor

ImageBackground::~ImageBackground(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void ImageBackground::initMethod (void)
{
}

//! react to field changes

void ImageBackground::changed(BitVector, ChangeMode)
{
}

//! clear the background

void ImageBackground::clear(DrawActionBase *, Viewport *)
{
    ImageP img = getImage();
    
    if(!img)
        return; 
    
    if(getScale())
    {
        FWARNING(("ImageBackground::clear: scale not supported yet,"
                  " ignored!\n"));
    }

    Bool depth=glIsEnabled(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);

    glDisable(GL_TEXTURE_2D);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, 0, 1);

    glRasterPos2f(0, 0);
    glDrawPixels(img->getWidth(), img->getHeight(),
                 img->getPixelFormat(), GL_UNSIGNED_BYTE,
                 img->getData() );

    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    if(depth)    glEnable(GL_DEPTH_TEST);
    
    glClear(GL_DEPTH_BUFFER_BIT);
}

//! output the instance for debug purposes

void ImageBackground::dump(      UInt32     , 
                           const BitVector  ) const
{
    SLOG << "Dump ImageBackground NI" << endl;
}

