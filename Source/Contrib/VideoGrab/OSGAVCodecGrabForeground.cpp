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
#include <OSGGL.h>

#include <OSGNodePtr.h>
#include <OSGImage.h>
#include <OSGViewport.h>


#include "OSGAVCodecGrabForeground.h"
#include "OSGAV.h"

OSG_USING_NAMESPACE

/*! \class osg::AVCodecGrabForeground
    \ingroup GrpSystemWindowForegrounds

The AVCodecGrabForeground is used for grabbing a frame or sequence of frames to
disk.  See \ref
PageSystemWindowForegroundGrabFile for a description.

The name of the file(s) grabbed to are defined by the _sfName Field, the
current frame number by _sfFrame. _sfIncrement can be used to automatically
increment the frame number after each image is written. The whole grabber can
be activated/deactivated using _sfActive.

*/

/*----------------------- constructors & destructors ----------------------*/

AVCodecGrabForeground::AVCodecGrabForeground(void) :
    Inherited(),
    encoder(0)
{
}

AVCodecGrabForeground::AVCodecGrabForeground(const AVCodecGrabForeground &source) :
    Inherited(source),
    encoder(0)
{
}

AVCodecGrabForeground::~AVCodecGrabForeground(void)
{
  if ( encoder )
    delete encoder;
}

/*----------------------------- class specific ----------------------------*/

void AVCodecGrabForeground::initMethod (void)
{
}

void AVCodecGrabForeground::changed(BitVector whichField, UInt32 origin)
{
    if(whichField & KbitFieldMask)
    {
        if(encoder)
        {
            encoder->setBitrate(getKbit());
        }
    }
    
    Inherited::changed(whichField, origin);
}

void AVCodecGrabForeground::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AVCodecGrabForeground NI" << std::endl;
}


/*! Grab the image and write it to the file. The name needs to be set.
*/

void AVCodecGrabForeground::draw(DrawActionBase *action, Viewport *port)
{
    if(getActive() == false)
        return;

    if(getName().empty())
    {
        FWARNING(("GrabForeground::draw: no name ?!?\n"));
        return;
    }

    ImagePtr i = getImage();

    if(i == NullFC)       // No image, make one.
    {
        i = Image::create();
        beginEditCP(i);
        i->set(Image::OSG_RGB_PF, 1);
        endEditCP(i);
        setImage(i);
    }

    UInt32 w= ( port->getPixelWidth() / 2 ) * 2;
    UInt32 h= ( port->getPixelHeight() / 2 ) * 2;

    if(i->getWidth() <= 1 && i->getHeight() <= 1)
    {
        i->set(i->getPixelFormat(), w, h);
    }

    // do we have an encoder
    if( !encoder )
    {
        encoder= new AVVideoEncoder(getName().c_str(), w, h, getKbit());
    }

    encoder->setRgb(i->getData());
    //encoder->getCodecContext()->strict_std_compliance=-1;

    bool storeChanged = false;
    if(encoder->width() != port->getPixelWidth() )
    {
        glPixelStorei(GL_PACK_ROW_LENGTH, encoder->width());
        storeChanged = true;
    }

    glReadPixels(port->getPixelLeft(), port->getPixelBottom(),
        encoder->width(), encoder->height(), i->getPixelFormat(),
        GL_UNSIGNED_BYTE, i->getData());

    if(storeChanged)
        glPixelStorei(GL_PACK_ROW_LENGTH, 0);

    if(getAutoWrite())
        writeFrame();
        
    return;
}

void AVCodecGrabForeground::writeFrame(void)
{
    if ( encoder && getActive() )
    {
        encoder->write_video_frame();
    }

  return;
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
    static char cvsid_hpp[] = OSGAVCODECGRABFOREGROUND_HEADER_CVSID;
    static char cvsid_inl[] = OSGAVCODECGRABFOREGROUND_INLINE_CVSID;
}
