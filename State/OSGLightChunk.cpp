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

#include "OSGConfig.h"

#include <GL/gl.h>

#include "OSGLightChunk.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::LightChunk
    \ingroup StateChunks

The light chunk contains the parameter set for a single light source.
It's taken straight from the glLight() manpage.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char LightChunk::cvsid[] = "@(#)$Id: $";

StateChunkClass LightChunk::_class("Light", 8);

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/** \brief initialize the static features of the class, e.g. action callbacks
 */

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

/** \brief Constructor
 */

LightChunk::LightChunk(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

LightChunk::LightChunk(const LightChunk &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

LightChunk::~LightChunk(void)
{
}


/** \brief react to field changes
 */

void LightChunk::changed(BitVector, ChangeMode)
{
}

/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void LightChunk::dump(      UInt32     uiIndent,
                         const BitVector &bvFlags) const
{
    SLOG << "Dump LightChunk NI" << endl;
}


/*-------------------------- your_category---------------------------------*/

void LightChunk::activate( DrawActionBase *, UInt32 index )
{
    glLightfv( GL_LIGHT0 + index, GL_DIFFUSE,
                            _sfDiffuse.getValue().getValueRef() );
    glLightfv( GL_LIGHT0 + index, GL_AMBIENT,
                            _sfAmbient.getValue().getValueRef() );
    glLightfv( GL_LIGHT0 + index, GL_SPECULAR,
                            _sfSpecular.getValue().getValueRef() );
    glLightfv( GL_LIGHT0 + index, GL_POSITION,
                            _sfPosition.getValue().getValues() );
    glLightf ( GL_LIGHT0 + index, GL_CONSTANT_ATTENUATION,
                            _sfConstantAttenuation.getValue() );
    glLightf ( GL_LIGHT0 + index, GL_LINEAR_ATTENUATION,
                            _sfLinearAttenuation.getValue() );
    glLightf ( GL_LIGHT0 + index, GL_QUADRATIC_ATTENUATION,
                            _sfQuadraticAttenuation.getValue() );

    glLightf(  GL_LIGHT0 + index, GL_SPOT_CUTOFF, _sfCutoff.getValue() );
    if ( _sfCutoff.getValue() < 180 )
    {
        glLightfv( GL_LIGHT0 + index, GL_SPOT_DIRECTION,
                                        _sfDirection.getValue().getValues() );
        glLightf(  GL_LIGHT0 + index, GL_SPOT_EXPONENT, _sfExponent.getValue() );
    }
    glEnable( GL_LIGHT0 + index );
}

void LightChunk::changeFrom( DrawActionBase *, StateChunk * old_chunk, UInt32 index )
{
    LightChunk const *old = dynamic_cast<LightChunk const*>(old_chunk);

    // change from me to me?
    // this assumes I haven't changed in the meantime. is that a valid assumption?
    if ( old == this )
        return;

    // it could theoretically be more efficient to turn the light off before
    // changing its parameters, have to try that sometime
    glLightfv( GL_LIGHT0 + index, GL_DIFFUSE,
                            _sfDiffuse.getValue().getValueRef() );
    glLightfv( GL_LIGHT0 + index, GL_AMBIENT,
                            _sfAmbient.getValue().getValueRef() );
    glLightfv( GL_LIGHT0 + index, GL_SPECULAR,
                            _sfSpecular.getValue().getValueRef() );
    glLightfv( GL_LIGHT0 + index, GL_POSITION,
                            _sfPosition.getValue().getValues() );
    glLightf ( GL_LIGHT0 + index, GL_CONSTANT_ATTENUATION,
                            _sfConstantAttenuation.getValue() );
    glLightf ( GL_LIGHT0 + index, GL_LINEAR_ATTENUATION,
                            _sfLinearAttenuation.getValue() );
    glLightf ( GL_LIGHT0 + index, GL_QUADRATIC_ATTENUATION,
                            _sfQuadraticAttenuation.getValue() );

    glLightf(  GL_LIGHT0 + index, GL_SPOT_CUTOFF, _sfCutoff.getValue() );
    if ( _sfCutoff.getValue() < 180 )
    {
        glLightfv( GL_LIGHT0 + index, GL_SPOT_DIRECTION,
                                        _sfDirection.getValue().getValues() );
        glLightf(  GL_LIGHT0 + index, GL_SPOT_EXPONENT, _sfExponent.getValue() );
    }
}

void LightChunk::deactivate( DrawActionBase *, UInt32 index )
{
    glDisable( GL_LIGHT0 + index );
}


/*-------------------------- comparison -----------------------------------*/

Real32 LightChunk::switchCost( StateChunk * chunk )
{
    return 0;
}

/** \brief assignment
 */

Bool LightChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

/** \brief equal
 */

Bool LightChunk::operator == (const StateChunk &other) const
{
    LightChunk const *tother = dynamic_cast<LightChunk const*>(&other);

    if ( !tother )
        return false;

    if ( ! getDiffuse().equals( tother->getDiffuse(), Eps ) )
        return false;

    return true;
}

/** \brief unequal
 */

Bool LightChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}




/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

