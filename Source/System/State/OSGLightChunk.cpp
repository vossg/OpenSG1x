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
 * License along with this library; ifnot, write to the Free Software       *
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
#include <OSGGLU.h>

#include "OSGLightChunk.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::LightChunk
    \ingroup GrpSystemState

See \ref PageSystemLightChunk for a description.

This chunk wraps glLight() (osg::LightChunk::_sfAmbient,
osg::LightChunk::_sfDiffuse, osg::LightChunk::_sfSpecular,
osg::LightChunk::_sfEmission, osg::LightChunk::_sfPosition,
osg::LightChunk::_sfDirection, osg::LightChunk::_sfExponent,
osg::LightChunk::_sfCutoff, osg::LightChunk::_sfConstantAttenuation,
osg::LightChunk::_sfLinearAttenuation,
osg::LightChunk::_sfQuadraticAttenuation).

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass LightChunk::_class("Light", 8);

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void LightChunk::initMethod (void)
{
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

LightChunk::LightChunk(void) :
    Inherited()
{
}

LightChunk::LightChunk(const LightChunk &source) :
    Inherited(source)
{
}

LightChunk::~LightChunk(void)
{
}

/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *LightChunk::getClass(void) const
{
    return &_class;
}

/*------------------------------- Sync -----------------------------------*/

void LightChunk::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

/*------------------------------ Output ----------------------------------*/

void LightChunk::dump(      UInt32    OSG_CHECK_ARG(uiIndent),
                      const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump LightChunk NI" << std::endl;
}


/*------------------------------ State ------------------------------------*/

void LightChunk::activate(DrawActionBase *, UInt32 index)
{
	glErr("light:activate:precheck");

    glLightfv(GL_LIGHT0 + index, GL_DIFFUSE,
                            _sfDiffuse.getValue().getValuesRGBA());
    glLightfv(GL_LIGHT0 + index, GL_AMBIENT,
                            _sfAmbient.getValue().getValuesRGBA());
    glLightfv(GL_LIGHT0 + index, GL_SPECULAR,
                            _sfSpecular.getValue().getValuesRGBA());
    glLightfv(GL_LIGHT0 + index, GL_POSITION,
                            _sfPosition.getValue().getValues());
    glLightf (GL_LIGHT0 + index, GL_CONSTANT_ATTENUATION,
                            _sfConstantAttenuation.getValue());
    glLightf (GL_LIGHT0 + index, GL_LINEAR_ATTENUATION,
                            _sfLinearAttenuation.getValue());
    glLightf (GL_LIGHT0 + index, GL_QUADRATIC_ATTENUATION,
                            _sfQuadraticAttenuation.getValue());

    glLightf( GL_LIGHT0 + index, GL_SPOT_CUTOFF, _sfCutoff.getValue());

    if(_sfCutoff.getValue() < 180)
    {
        glLightfv(GL_LIGHT0 + index, GL_SPOT_DIRECTION,
                                        _sfDirection.getValue().getValues());
        glLightf( GL_LIGHT0 + index, GL_SPOT_EXPONENT, _sfExponent.getValue());
    }
    glEnable(GL_LIGHT0 + index);

	glErr("light:activate:postcheck");
}

void LightChunk::changeFrom(DrawActionBase *, StateChunk * old_chunk, UInt32 index)
{
	glErr("light:changed:precheck");

    LightChunk const *old = dynamic_cast<LightChunk const*>(old_chunk);

    // change from me to me?
    // this assumes I haven't changed in the meantime. is that a valid assumption?
    if(old == this)
        return;

    // it could theoretically be more efficient to turn the light off before
    // changing its parameters, have to try that sometime
    glLightfv(GL_LIGHT0 + index, GL_DIFFUSE,
                            _sfDiffuse.getValue().getValuesRGBA());
    glLightfv(GL_LIGHT0 + index, GL_AMBIENT,
                            _sfAmbient.getValue().getValuesRGBA());
    glLightfv(GL_LIGHT0 + index, GL_SPECULAR,
                            _sfSpecular.getValue().getValuesRGBA());
    glLightfv(GL_LIGHT0 + index, GL_POSITION,
                            _sfPosition.getValue().getValues());
    glLightf (GL_LIGHT0 + index, GL_CONSTANT_ATTENUATION,
                            _sfConstantAttenuation.getValue());
    glLightf (GL_LIGHT0 + index, GL_LINEAR_ATTENUATION,
                            _sfLinearAttenuation.getValue());
    glLightf (GL_LIGHT0 + index, GL_QUADRATIC_ATTENUATION,
                            _sfQuadraticAttenuation.getValue());

    glLightf( GL_LIGHT0 + index, GL_SPOT_CUTOFF, _sfCutoff.getValue());
    if(_sfCutoff.getValue() < 180)
    {
        glLightfv(GL_LIGHT0 + index, GL_SPOT_DIRECTION,
                                        _sfDirection.getValue().getValues());
        glLightf( GL_LIGHT0 + index, GL_SPOT_EXPONENT, _sfExponent.getValue());
    }

	glErr("light:changed:postcheck");
}

void LightChunk::deactivate(DrawActionBase *, UInt32 index)
{
    glDisable(GL_LIGHT0 + index);
}


/*-------------------------- Comparison -----------------------------------*/

Real32 LightChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool LightChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool LightChunk::operator == (const StateChunk &other) const
{
    LightChunk const *tother = dynamic_cast<LightChunk const*>(&other);

    if(!tother)
        return false;

    if(tother == this)
        return true;

    if(!getAmbient  ().equals(tother->getAmbient  (), Eps) ||
       !getDiffuse  ().equals(tother->getDiffuse  (), Eps) ||
       !getSpecular ().equals(tother->getSpecular (), Eps) ||
       !getPosition ().equals(tother->getPosition (), Eps) ||
       !getDirection().equals(tother->getDirection(), Eps) ||
        getConstantAttenuation()  != tother->getConstantAttenuation()  ||
        getLinearAttenuation()    != tother->getLinearAttenuation()    ||
        getQuadraticAttenuation() != tother->getQuadraticAttenuation() ||
        getCutoff()               != tother->getCutoff()               ||
        getExponent()             != tother->getExponent()
      )
        return false;

    return true;
}

bool LightChunk::operator != (const StateChunk &other) const
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
    static Char8 cvsid_hpp       [] = OSGLIGHTCHUNK_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGLIGHTCHUNK_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGLIGHTCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif


