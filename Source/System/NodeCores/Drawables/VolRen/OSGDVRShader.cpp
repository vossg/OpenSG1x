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

#include "OSGDVRShader.h"

OSG_USING_NAMESPACE

/*! \class osg::DVRShader
Abstract shader class - not to be instantiated. Is intended to be stateless - NO FIELDS!!
*/


bool DVRShader::initialize(DVRVolume      * /* volume */, 
                           DrawActionBase * /* action */) 
{
    SLOG << "DVRShader::initialize - NI" << std::endl;

    return false;
}


void DVRShader::activate(DVRVolume      * /* volume */, 
                         DrawActionBase * /* action */) 
{
    SLOG << "DVRShader::activate - NI" << std::endl;
}

void DVRShader::brickActivate(DVRVolume      * /* volume */, 
                              DrawActionBase * /* action */,
                              Brick          * /* brick  */ ) 
{
    SLOG << "DVRShader::brickActivate - NI" << std::endl;
}

void DVRShader::deactivate(DVRVolume      * /* volume */, 
                           DrawActionBase * /* action */) 
{
    SLOG << "DVRShader::brickActivate - NI" << std::endl;
}

void DVRShader::renderSlice(DVRVolume      * /* volume   */, 
                            DrawActionBase * /* action   */,
                            Real32         * /* data     */, 
                            UInt32           /* vertices */, 
                            UInt32           /* values   */) 
{
    SLOG << "DVRShader::renderSlice - NI" << std::endl;
}

void DVRShader::renderSlice(DVRVolume      * /* volume       */, 
                            DrawActionBase * /* action       */,
                            DVRRenderSlice * /* clippedSlice */) 
{
    SLOG << "DVRShader::renderSlice - NI" << std::endl;
}

bool DVRShader::hasRenderCallback(void)
{
    return false; 
}

bool DVRShader::useMTSlabs(void)
{
    return false; 
}; 

/*----------------------- constructors & destructors ----------------------*/

//! Constructor
DVRShader::DVRShader(void) :
    Inherited()
{
}

//! Copy Constructor
DVRShader::DVRShader(const DVRShader &source) :
    Inherited(source)
{
}

//! Destructor
DVRShader::~DVRShader(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks
void DVRShader::initMethod (void)
{
}

//! react to field changes
void DVRShader::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

//! output the instance for debug purposes
void DVRShader::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DVRShader NI" << std::endl;
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
    static char cvsid_hpp[] = OSGDVRSHADER_HEADER_CVSID;
    static char cvsid_inl[] = OSGDVRSHADER_INLINE_CVSID;
}

