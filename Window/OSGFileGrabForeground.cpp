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

#include "OSGFileGrabForeground.h"

OSG_USING_NAMESPACE

/*! \class osg::FileGrabForeground
Background is the base class for all background clearing.  	 	
*/

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

FileGrabForeground::FileGrabForeground(void) :
    Inherited()
{
}

//! Copy Constructor

FileGrabForeground::FileGrabForeground(const FileGrabForeground &source) :
    Inherited(source)
{
}

//! Destructor

FileGrabForeground::~FileGrabForeground(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void FileGrabForeground::initMethod (void)
{
}

//! react to field changes

void FileGrabForeground::changed(BitVector, UInt32)
{
}

//! output the instance for debug purposes

void FileGrabForeground::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump FileGrabForeground NI" << endl;
}


/** \brief grab the image and write it to the file
 */
    
void FileGrabForeground::draw(DrawActionBase *action, Viewport *port)
{
    if(getActive() == false)
        return;
    
    if(getName().empty())
    {
        FWARNING(("GrabForeground::draw: no name ?!?\n"));
        return;
    }
    
    // do we have an image yet? If not, create one.
    if(getImage() == NULL)
    {
        beginEditCP(this->getPtr(), FileGrabForeground::ImageFieldMask);
        {
            setImage(new Image(Image::OSG_RGB_PF, 1));
        }
        endEditCP  (this->getPtr(), FileGrabForeground::ImageFieldMask);
    }
    
    Inherited::draw(action,port);
    
    Char8 *name = new Char8 [ getName().size() + 32 ]; // this is really 
                                                       // arbitrary... :(

    sprintf(name, getName().c_str(), getFrame());
        
    ImageP i = getImage();

    i->write(name);
    
    delete [] name;
    
    if(getIncrement() != false)
    {
        beginEditCP(this->getPtr(), FileGrabForeground::FrameFieldMask);
        {
            setFrame(getFrame() + 1);
        }
        endEditCP  (this->getPtr(), FileGrabForeground::FrameFieldMask);
    }   
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
    static char cvsid_cpp[] = "@(#)$Id: OSGFileGrabForeground.cpp,v 1.3 2002/06/01 10:37:26 vossg Exp $";
    static char cvsid_hpp[] = OSGFILEGRABFOREGROUND_HEADER_CVSID;
    static char cvsid_inl[] = OSGFILEGRABFOREGROUND_INLINE_CVSID;
}
