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

#include <OSGGL.h>

#include "OSGTransformChunk.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::TransformChunk
    \ingroup StateChunks

The transformation chunk class.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char TransformChunk::cvsid[] = "@(#)$Id: $";

StateChunkClass TransformChunk::_class("Transform");

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

void TransformChunk::initMethod (void)
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

TransformChunk::TransformChunk(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

TransformChunk::TransformChunk(const TransformChunk &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

TransformChunk::~TransformChunk(void)
{
}


/** \brief react to field changes
 */

void TransformChunk::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void TransformChunk::dump(      UInt32    OSG_CHECK_ARG(uiIndent),
                          const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump TransformChunk NI" << endl;
}


/*-------------------------- your_category---------------------------------*/

void TransformChunk::activate ( DrawActionBase *,  UInt32 )
{
    glPushMatrix();
    glMultMatrixf( getMatrix().getValues() );
}

void TransformChunk::changeFrom( DrawActionBase *,  StateChunk * old, UInt32 )
{
    // change from me to me?
    // this assumes I haven't changed in the meantime. is that a valid assumption?
    if ( old == this )
        return;

    glPopMatrix();
    glPushMatrix();
    glMultMatrixf( getMatrix().getValues() );
}

void TransformChunk::deactivate ( DrawActionBase *,  UInt32 )
{
    glPopMatrix();
}

/*-------------------------- comparison -----------------------------------*/

Real32 TransformChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

/** \brief assignment
 */

bool TransformChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

/** \brief equal
 */

bool TransformChunk::operator == (const StateChunk &other) const
{
    TransformChunk const *tother = dynamic_cast<TransformChunk const*>(&other);

    if ( !tother )
        return false;

    return getMatrix().equals( tother->getMatrix(), Eps );
}

/** \brief unequal
 */

bool TransformChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

