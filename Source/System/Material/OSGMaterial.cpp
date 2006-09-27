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

#include "OSGConfig.h"

#include <OSGGL.h>
#include "OSGMaterial.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Material
    \ingroup GrpSystemMaterial

The material base class.

\ext The Material has two interfaces to return a State that represents it.
osg::Material::makeState() creates a new osg::State and returns it. This is ok
for rare use, but for every frame this is going to be too expensive. For these
cases osg::Material::rebuildState() and osg::Material::getState() are used, which
modify and return an internal copy of the State. 

The other method to implement is osg::Material::isTransparent(), to identify
transparent materials to be rendered after the opaque ones.
\endext
*/

/*! \fn osg::Material::makeState()

    Creates an instance of a osg::State that is used to represent the material.
    This is used by the osg::DrawAction.  
*/

/*! \fn osg::Material::rebuildState()

    Update the internal osg::State. 
*/

/*! \fn osg::Material::getState()

    Access the internal osg::State, used by the osg::RenderAction.
*/

/*! \fn osg::Material::isTransparent()

    Check if the Material is transparent and thus has to be rendered afte the
    opaque ones.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

OSG_BEGIN_NAMESPACE
OSG_SYSTEMLIB_DLLMAPPING MaterialPtr NullMaterial;
OSG_END_NAMESPACE

const Int32 Material::NoStateSorting = 0x7fffffff;
const Int32 Material::TransparencyAutoDetection = 0;
const Int32 Material::TransparencyForceTransparent = 1;
const Int32 Material::TransparencyForceOpaque = 2;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void Material::initMethod (void)
{
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

Material::Material(void) :
    Inherited(),
    _pState  ()
{
}

Material::Material(const Material &source) :
    Inherited(source),
    _pState  ()
{
// Doing this kills using prototypes with preset states. 
// What's the point of this anyway? Sharing _pState between Materials never
// makes sense
//    setRefdCP(_pState, source._pState); 
}

Material::~Material(void)
{
    subRefCP(_pState);
}

#if defined(OSG_FIXED_MFIELDSYNC)
void Material::onDestroyAspect(UInt32 uiId, UInt32 uiAspect)
{
    Inherited::onDestroyAspect(uiId, uiAspect);

    subRefCP(_pState);
    
    _pState = NullFC;
}
#endif

StatePtr Material::getState(UInt32 OSG_CHECK_ARG(index))
{
    return _pState;
}

bool Material::isMultiPass(void) const
{
    return false;
}

UInt32 Material::getNPasses(void) const
{
    return 1;
}

void Material::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    rebuildState();
}

Int32 Material::getRealSortKey(void) const
{
    return _sfSortKey.getValue();
}

/*------------------------------- dump ----------------------------------*/

void Material::dump(      UInt32    ,
                    const BitVector ) const
{
    SLOG << "Material::dump called: NIY!" << std::endl;
//   Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------- comparison -----------------------------------*/

bool Material::operator < (const Material &other) const
{
    return this < &other;
}

bool Material::operator == (const Material& other) const
{
    return _pState == other._pState;
}

bool Material::operator != (const Material &other) const
{
    return ! (*this == other);
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.13 2002/06/01 10:37:25 vossg Exp $";
    static Char8 cvsid_hpp       [] = OSGMATERIAL_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGMATERIAL_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGMATERIALFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

