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

#define OSG_COMPILESYSTEMLIB

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <GL/gl.h>

#include "OSGDrawAction.h"
#include "OSGWindow.h"

#include "OSGBlendChunk.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::BlendChunk
	\ingroup StateChunks

The blending chunk handles OpenGL blending, i.e. the definition how incoming 
pixel are combined with the pixel already in the frame buffer. 	

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char BlendChunk::cvsid[] = "@(#)$Id: OSGBlendChunk.cpp,v 1.2 2001/06/10 12:42:07 vossg Exp $";

StateChunkClass BlendChunk::_class(String("Blend"));

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

void BlendChunk::initMethod (void)
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

BlendChunk::BlendChunk(void) :
    Inherited()
{
//	_GLId = Window::registerExtension( "EXT_blend_color" );
	_GLId.setValue( Window::registerFunction( String("glBlendColorEXT") ) );
}

/** \brief Copy Constructor
 */

BlendChunk::BlendChunk(const BlendChunk &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

BlendChunk::~BlendChunk(void)
{
}


/** \brief react to field changes
 */

void BlendChunk::changed(BitVector, ChangeMode)
{
}

/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void BlendChunk::dump(      UInt32     uiIndent, 
                         const BitVector &bvFlags) const
{
   Inherited::dump(uiIndent, bvFlags);
}

/*-------------------------- your_category---------------------------------*/

void BlendChunk::activate ( DrawAction *action, UInt32 )
{
	// get "glBlendFuncEXT" function pointer	
	
	if ( _SrcFactor.getValue() != GL_NONE )
	{
		void *p = action->getWindow()->getFunction( _GLId.getValue() );

		glBlendFunc( _SrcFactor.getValue(), _DestFactor.getValue() );
			
		( (void (*)(GLclampf red,GLclampf green,GLclampf blue,GLclampf alpha )) 		    
			   p  )( _Color.getValue().red(), 
					 _Color.getValue().green(), 
				 _Color.getValue().blue(), 
				 _Color.getValue().alpha() );	

		glEnable( GL_BLEND );
	} 	
}

void BlendChunk::changeFrom( DrawAction *, StateChunk * old_chunk, UInt32 )
{
}

void BlendChunk::deactivate ( DrawAction *, UInt32 )
{
	if ( _SrcFactor.getValue() != GL_NONE )
	{
		glDisable( GL_BLEND );	
	}
}

/*-------------------------- comparison -----------------------------------*/

Real32 BlendChunk::switchCost( StateChunk * chunk )
{
	return 0;
}

/** \brief assignment
 */

Bool BlendChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

/** \brief equal
 */

Bool BlendChunk::operator == (const StateChunk &other) const
{
	BlendChunk const *tother = dynamic_cast<BlendChunk const*>(&other);

	if ( !tother )
		return false;

	if(getColor() != tother->getColor())
	   
		return false;
		
	return true;
}

/** \brief unequal
 */

Bool BlendChunk::operator != (const StateChunk &other) const
{
	return ! (*this == other);
}

    

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

