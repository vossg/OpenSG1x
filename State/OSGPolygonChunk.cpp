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

#include "OSGPolygonChunk.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PolygonChunk
    \ingroup StateChunks

The polygon chunk contains the parameter that is specific set for filled surfaces,
i.e. polygons.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char PolygonChunk::cvsid[] = "@(#)$Id: OSGPolygonChunk.cpp,v 1.12 2002/02/04 20:14:10 dirk Exp $";

StateChunkClass PolygonChunk::_class("Polygon");

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

void PolygonChunk::initMethod (void)
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

PolygonChunk::PolygonChunk(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

PolygonChunk::PolygonChunk(const PolygonChunk &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

PolygonChunk::~PolygonChunk(void)
{
}


/** \brief react to field changes
 */

void PolygonChunk::changed(BitVector, ChangeMode)
{
}

/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void PolygonChunk::dump(      UInt32    uiIndent,
                        const BitVector bvFlags) const
{
   Inherited::dump(uiIndent, bvFlags);
}


/*-------------------------- your_category---------------------------------*/

void PolygonChunk::activate ( DrawActionBase *, UInt32 )
{

// cullFace

    if ( _sfCullFace.getValue() != GL_NONE )
    {
        glCullFace( _sfCullFace.getValue() );
        glEnable( GL_CULL_FACE );
    }

// frontFace

    if ( _sfFrontFace.getValue() != GL_CCW )
        glFrontFace( _sfFrontFace.getValue() );

// smooth

    if ( _sfSmooth.getValue() ) 
        glEnable( GL_POLYGON_SMOOTH );

// mode

    if ( _sfModeFace.getValue() != GL_FRONT || _sfMode.getValue() != GL_FILL )
        glPolygonMode( _sfModeFace.getValue(), _sfMode.getValue() );

// offset
   
    if ( _sfOffsetFactor.getValue() != 0.f || _sfOffsetBias.getValue() != 0.f )    
        glPolygonOffset( _sfOffsetFactor.getValue(), _sfOffsetBias.getValue() );

    if ( _sfOffsetPoint.getValue() )    
        glEnable( GL_POLYGON_OFFSET_POINT );

    if ( _sfOffsetLine.getValue() ) 
        glEnable( GL_POLYGON_OFFSET_LINE );

    if ( _sfOffsetFill.getValue() ) 
        glEnable( GL_POLYGON_OFFSET_FILL );

// stipple

    if ( _mfStipple.size() == 32 )
    {
        glPolygonStipple( (const GLubyte *) &(_mfStipple[0]) );
        glEnable( GL_POLYGON_STIPPLE );
    }
}


void PolygonChunk::changeFrom( DrawActionBase *, StateChunk * old_chunk, UInt32 )
{
    PolygonChunk const *old = dynamic_cast<PolygonChunk const*>(old_chunk);

    // change from me to me?
    // this assumes I haven't changed in the meantime. is that a valid assumption?
    if ( old == this )
        return;

// cullFace

    if ( _sfCullFace.getValue() != old->_sfCullFace.getValue() )
    {
        if ( _sfCullFace.getValue() != GL_NONE )
        {
            glCullFace( _sfCullFace.getValue() );
            glEnable( GL_CULL_FACE );
        }
        else  
        {
            glDisable( GL_CULL_FACE );
        }
    }

// frontFace

    if ( _sfFrontFace.getValue() != old->_sfFrontFace.getValue() )
    {
        glFrontFace( _sfFrontFace.getValue() );
    }

// smooth

    if ( _sfSmooth.getValue() != old->_sfSmooth.getValue() )
    {
        if ( _sfSmooth.getValue() )   
        {
            glEnable( GL_POLYGON_SMOOTH );
        }
        else
        {
            glDisable( GL_POLYGON_SMOOTH );
        }
    }

// mode

    if ( _sfModeFace.getValue() !=  old->_sfModeFace.getValue()
        || _sfMode.getValue() != old->_sfMode.getValue() )
    {
        glPolygonMode( _sfModeFace.getValue(), _sfMode.getValue() );
    }

// offset

    if ( _sfOffsetFactor.getValue() != old->_sfOffsetFactor.getValue() ||
         _sfOffsetBias.getValue()   != old->_sfOffsetBias.getValue() )
    {
        glPolygonOffset( _sfOffsetFactor.getValue(), _sfOffsetBias.getValue() );
    }

    if ( _sfOffsetPoint.getValue() != old->_sfOffsetPoint.getValue() )
    {
        if ( _sfOffsetPoint.getValue() )  
        {
            glEnable( GL_POLYGON_OFFSET_POINT );
        }
        else                            
        {
            glDisable( GL_POLYGON_OFFSET_POINT );
        }
    }

    if ( _sfOffsetLine.getValue() != old->_sfOffsetLine.getValue() )
    {
        if ( _sfOffsetLine.getValue() )  
        {
            glEnable( GL_POLYGON_OFFSET_LINE );
        }
        else                            
        {
            glDisable( GL_POLYGON_OFFSET_LINE );
        }
    }

    if ( _sfOffsetFill.getValue() != old->_sfOffsetFill.getValue() )
    {
        if ( _sfOffsetFill.getValue() )  
        {
            glEnable( GL_POLYGON_OFFSET_FILL );
        }
        else                            
        {
            glDisable( GL_POLYGON_OFFSET_FILL );
        }
    }

// stipple

    if ( _mfStipple.getValues() != old->_mfStipple.getValues() )
    {
        if ( _mfStipple.size() == 32 )
        {
            glPolygonStipple( (const GLubyte *) &(_mfStipple[0]) );
            glEnable( GL_POLYGON_STIPPLE );
        }
        else glDisable( GL_POLYGON_STIPPLE );
    }

}

void PolygonChunk::deactivate ( DrawActionBase *, UInt32 )
{

// cullFace

    if ( _sfCullFace.getValue() != GL_NONE )
        glDisable( GL_CULL_FACE );

// frontFace

    if ( _sfFrontFace.getValue() != GL_CCW )
        glFrontFace( GL_CCW );

// smooth

    if ( _sfSmooth.getValue() )
        glDisable( GL_POLYGON_SMOOTH );

// mode

    if ( _sfModeFace.getValue() != GL_FRONT || _sfMode.getValue() != GL_FILL )
        glPolygonMode( GL_FRONT, GL_FILL );

// offset

    if ( _sfOffsetPoint.getValue() )
        glDisable( GL_POLYGON_OFFSET_POINT );

    if ( _sfOffsetLine.getValue() )
        glDisable( GL_POLYGON_OFFSET_LINE );

    if ( _sfOffsetFill.getValue() )
        glDisable( GL_POLYGON_OFFSET_FILL );

// stipple

    if ( _mfStipple.size() == 32 )
        glDisable( GL_POLYGON_STIPPLE );

}


/*-------------------------- comparison -----------------------------------*/

Real32 PolygonChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

/** \brief assignment
 */

bool PolygonChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

/** \brief equal
 */

bool PolygonChunk::operator == (const StateChunk &other) const
{
    PolygonChunk const *tother = dynamic_cast<PolygonChunk const*>(&other);

    if ( !tother )
        return false;

    if ( _sfCullFace.getValue() != tother->_sfCullFace.getValue() )
        return false;

    if ( _sfFrontFace.getValue() != tother->_sfFrontFace.getValue() )
        return false;

    if ( _sfSmooth.getValue() != tother->_sfSmooth.getValue() )
        return false;

    if ( _sfModeFace.getValue() != tother->_sfModeFace.getValue() )
        return false;

    if ( _sfMode.getValue() != tother->_sfMode.getValue() )
        return false;

    if ( _sfOffsetPoint.getValue() != tother->_sfOffsetPoint.getValue() )
        return false;

    if ( _sfOffsetLine.getValue() != tother->_sfOffsetLine.getValue() )
        return false;

    if ( _sfOffsetFill.getValue() != tother->_sfOffsetFill.getValue() )
        return false;

    if ( _sfOffsetFactor.getValue() != tother->_sfOffsetFactor.getValue() )
        return false;

    if ( _sfOffsetBias.getValue() != tother->_sfOffsetBias.getValue() )
        return false;

    if ( _mfStipple.begin() != tother->_mfStipple.begin() )
//  if ( _stipple.getValues() != tother->_stipple.getValues() )
        return false;

    return true;
}

/** \brief unequal
 */

bool PolygonChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}



/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

