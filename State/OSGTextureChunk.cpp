/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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
#include <GL/glu.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#define OSG_COMPILESTATE

#include "OSGDrawAction.h"
#include "OSGWindow.h"

#include "OSGTextureChunk.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::TextureChunk
	\ingroup StateChunks

The texture chunk class.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

OSG_FC_FIRST_FIELD_IDM_DEF(TextureChunk, ImageField)
OSG_FC_FIELD_IDM_DEF      (TextureChunk, MinFilterField, 	ImageField )  
OSG_FC_FIELD_IDM_DEF      (TextureChunk, MagFilterField, 	MinFilterField )  
OSG_FC_FIELD_IDM_DEF      (TextureChunk, WrapSField, 		MagFilterField )  
OSG_FC_FIELD_IDM_DEF      (TextureChunk, WrapTField, 		WrapSField )  
OSG_FC_FIELD_IDM_DEF      (TextureChunk, WrapRField, 		WrapTField )  
OSG_FC_FIELD_IDM_DEF      (TextureChunk, EnvModeField, 		WrapRField )  
OSG_FC_FIELD_IDM_DEF      (TextureChunk, GenFuncSField, 	EnvModeField )  
OSG_FC_FIELD_IDM_DEF      (TextureChunk, GenFuncTField,  	GenFuncSField )  
OSG_FC_FIELD_IDM_DEF      (TextureChunk, GenFuncRField, 	GenFuncTField )  
OSG_FC_FIELD_IDM_DEF      (TextureChunk, GenFuncQField, 	GenFuncRField )  
OSG_FC_FIELD_IDM_DEF      (TextureChunk, GenFuncSPlaneField,GenFuncQField )  
OSG_FC_FIELD_IDM_DEF      (TextureChunk, GenFuncTPlaneField,GenFuncSPlaneField )  
OSG_FC_FIELD_IDM_DEF      (TextureChunk, GenFuncRPlaneField,GenFuncTPlaneField )  
OSG_FC_FIELD_IDM_DEF      (TextureChunk, GenFuncQPlaneField,GenFuncRPlaneField )  
OSG_FC_FIELD_IDM_DEF      (TextureChunk, GLIdField, 		GenFuncQPlaneField )  
OSG_FC_LAST_FIELD_IDM_DEF (TextureChunk, GLIdField)

char TextureChunk::cvsid[] = "@(#)$Id: OSGTextureChunk.cpp,v 1.4 2001/02/13 15:57:39 dirk Exp $";

StateChunkClass TextureChunk::_class(String("Texture"));


FieldDescription TextureChunk::_desc[] = 
{
        FieldDescription(
        SFImageP::getClassType(), 
        "image", 
        OSG_FC_FIELD_IDM_DESC(ImageField),
        false,
        (FieldAccessMethod) &TextureChunk::getSFImage,
        ""),
        FieldDescription(
        SFUInt32::getClassType(), 
        "minFilter", 
        OSG_FC_FIELD_IDM_DESC(MinFilterField),
        false,
        (FieldAccessMethod) &TextureChunk::getSFMinFilter,
        ""),
        FieldDescription(
        SFUInt32::getClassType(), 
        "magFilter", 
        OSG_FC_FIELD_IDM_DESC(MagFilterField),
        false,
        (FieldAccessMethod) &TextureChunk::getSFMagFilter,
        ""),
        FieldDescription(
        SFUInt32::getClassType(), 
        "wrapS", 
        OSG_FC_FIELD_IDM_DESC(WrapSField),
        false,
        (FieldAccessMethod) &TextureChunk::getSFWrapS,
        ""),
        FieldDescription(
        SFUInt32::getClassType(), 
        "wrapT", 
        OSG_FC_FIELD_IDM_DESC(WrapTField),
        false,
        (FieldAccessMethod) &TextureChunk::getSFWrapT,
        ""),
        FieldDescription(
        SFUInt32::getClassType(), 
        "wrapR", 
        OSG_FC_FIELD_IDM_DESC(WrapRField),
        false,
        (FieldAccessMethod) &TextureChunk::getSFWrapR,
        ""),
        FieldDescription(
        SFUInt32::getClassType(), 
        "envMode", 
        OSG_FC_FIELD_IDM_DESC(EnvModeField),
        false,
        (FieldAccessMethod) &TextureChunk::getSFEnvMode,
        ""),
        FieldDescription(
        SFUInt32::getClassType(), 
        "genFuncS", 
        OSG_FC_FIELD_IDM_DESC(GenFuncSField),
        false,
        (FieldAccessMethod) &TextureChunk::getSFGenFuncS,
        ""),
        FieldDescription(
        SFUInt32::getClassType(), 
        "genFuncT", 
        OSG_FC_FIELD_IDM_DESC(GenFuncTField),
        false,
        (FieldAccessMethod) &TextureChunk::getSFGenFuncT,
        ""),
        FieldDescription(
        SFUInt32::getClassType(), 
        "genFuncR", 
        OSG_FC_FIELD_IDM_DESC(GenFuncRField),
        false,
        (FieldAccessMethod) &TextureChunk::getSFGenFuncR,
        ""),
        FieldDescription(
        SFUInt32::getClassType(), 
        "genFuncQ", 
        OSG_FC_FIELD_IDM_DESC(GenFuncQField),
        false,
        (FieldAccessMethod) &TextureChunk::getSFGenFuncQ,
        ""),
        FieldDescription(
        SFPlane::getClassType(), 
        "genFuncSPlane", 
        OSG_FC_FIELD_IDM_DESC(GenFuncSPlaneField),
        false,
        (FieldAccessMethod) &TextureChunk::getSFGenFuncSPlane,
        ""),
        FieldDescription(
        SFPlane::getClassType(), 
        "genFuncTPlane", 
        OSG_FC_FIELD_IDM_DESC(GenFuncTPlaneField),
        false,
        (FieldAccessMethod) &TextureChunk::getSFGenFuncTPlane,
        ""),
        FieldDescription(
        SFPlane::getClassType(), 
        "genFuncRPlane", 
        OSG_FC_FIELD_IDM_DESC(GenFuncRPlaneField),
        false,
        (FieldAccessMethod) &TextureChunk::getSFGenFuncRPlane,
        ""),
        FieldDescription(
        SFPlane::getClassType(), 
        "genFuncQPlane", 
        OSG_FC_FIELD_IDM_DESC(GenFuncQPlaneField),
        false,
        (FieldAccessMethod) &TextureChunk::getSFGenFuncQPlane,
        ""),
        FieldDescription(
        SFUInt32::getClassType(), 
        "GLId", 
        OSG_FC_FIELD_IDM_DESC(GLIdField),
        true,
        (FieldAccessMethod) &TextureChunk::getSFGLId,
        "")
};

FieldContainerType TextureChunk::_type(
	"TextureChunk", 
	"StateChunk", 
	NULL,
	(PrototypeCreateF) &TextureChunk::createEmpty,
	NULL,
	_desc, 
	sizeof(_desc));

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

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

// this should go somewhere central...

#include <GL/glu.h>
#define glErr( text )							\
{									\
        GLenum glerr;							\
        glerr=glGetError();						\
        if (glerr!=GL_NO_ERROR)						\
        {								\
                fprintf(stderr, "%s failed: %s (%#x)\n", (text),	\
                                        gluErrorString(glerr), glerr);	\
        }								\
}



/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

OSG_FIELD_CONTAINER_DEF(TextureChunk, TextureChunkPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

// only used to create the prototype. don't use to create real chunks 

TextureChunk::TextureChunk(void) :
	Inherited(),
	_Image(), _MinFilter( GL_LINEAR_MIPMAP_LINEAR), _MagFilter(GL_LINEAR), 
	_WrapS(GL_REPEAT), _WrapT(GL_REPEAT), _WrapR(GL_REPEAT), 
	_GenFuncS( GL_NONE ), _GenFuncT( GL_NONE ), _GenFuncR( GL_NONE ), 
	_GenFuncQ( GL_NONE ), 
	_GenFuncSPlane(), _GenFuncTPlane(), _GenFuncRPlane(), _GenFuncQPlane(), 
	_GLId(0)
{
	_ownClass = _class.getID();
}


TextureChunk::TextureChunk( const TextureChunk& source ) :
	Inherited(source),
	_Image( source._Image ), _MinFilter( source._MinFilter ), 
	_MagFilter( source._MagFilter ), _WrapS( source._WrapS ), 
	_WrapT( source._WrapT ), _WrapR( source._WrapR ), 
	_GenFuncS( source._GenFuncS ), _GenFuncT( source._GenFuncT ), 
	_GenFuncR( source._GenFuncR ), _GenFuncQ( source._GenFuncQ ), 
	_GenFuncSPlane( source._GenFuncSPlane ), 
	_GenFuncTPlane( source._GenFuncTPlane ), 
	_GenFuncRPlane( source._GenFuncRPlane ), 
	_GenFuncQPlane( source._GenFuncQPlane ), 
	_GLId( source._GLId )
{
	// already assigned a GLId?
	// if not this is the copy from the prototype
	
	// !!! this temporary is needed to work around compiler problems (sgi)
	TextureChunkPtr tmpPtr = FieldContainer::getPtr<TextureChunkPtr>(*this);
	
	if ( ! getGLId() )	
		setGLId( Window::registerGLObject( 
						osgMethodFunctor2CPtr<
										void,
										Window::GLObjectFlagE,
										UInt32,
										TextureChunkPtr
										>( tmpPtr, &TextureChunk::handleGL ), 1 
			   )                         );
}


/** \brief Destructor
 */

TextureChunk::~TextureChunk(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/


/*-------------------------- your_category---------------------------------*/

// GL object handler
// create the texture and destroy it
void TextureChunk::handleGL( Window::GLObjectFlagE mode, UInt32 id )
{
	if ( mode == Window::destroy )
	{
		GLuint tex = id;
		glDeleteTextures( 1, &tex );
	}
	else if ( mode == Window::finaldestroy )
	{
		//SWARNING << "Last texture user destroyed" << endl;
	}
	else if ( mode == Window::initialize )
	{		
		ImageP img = getImage();
		
		if ( ! img ) // no image ?
			return;
			
		GLenum target;		
		if ( img->getDepth() > 1 )			
		{
			SWARNING << "TextureChunk::initialize: 3D textures not supported "
					 << "yet!" << endl;
			return;
		}
		else if ( img->getHeight() > 1 )		target = GL_TEXTURE_2D;
		else									target = GL_TEXTURE_1D;

		// activate the texture
		glBindTexture( target, id );
		
		// set the parameters 
		glTexParameteri( target, GL_TEXTURE_MIN_FILTER, getMinFilter() );
		glTexParameteri( target, GL_TEXTURE_MAG_FILTER, getMagFilter() );
		glTexParameteri( target, GL_TEXTURE_WRAP_S, getWrapS() );
		if ( target == GL_TEXTURE_2D )
			glTexParameteri( target, GL_TEXTURE_WRAP_T, getWrapT() );
		
		glErr( "TextureChunk::initialize params" );
		
		// set the image
		GLenum internalFormat = img->getPixelFormat();
		GLenum externalFormat = img->getPixelFormat();
		GLenum type = GL_UNSIGNED_BYTE;
		UInt32 width = img->getWidth();
		UInt32 height = img->getHeight();
		
		Bool defined = false;	// Texture defined ?
		Bool needMipmaps = getMinFilter() == GL_NEAREST_MIPMAP_NEAREST ||
							getMinFilter() == GL_LINEAR_MIPMAP_NEAREST ||
							getMinFilter() == GL_NEAREST_MIPMAP_LINEAR ||
							getMinFilter() == GL_LINEAR_MIPMAP_LINEAR ;
							
		// do we need mipmaps?
		if ( needMipmaps )
		{
			// do we have mipmaps ?
			
			// NIY   if ( img->hasMipmaps() )
			
			// Nope, try to use gluBuild?DMipmaps
			{
				void * data = NULL;
				
				// can we use it directly?
				if ( ! osgispower2( width ) ||
					 ! osgispower2( height )
				   )
				{
					// scale is only implemented for 2D
					if ( target != GL_TEXTURE_2D )
					{
						SWARNING << "TextureChunk::initialize: can't mipmap "
								 << "non-2D textures that are not 2^x !!!"
								 << endl;
					}
					else // use gluScaleImage to get to 2^
					{
						UInt32 outw = osgnextpower2( width );
						UInt32 outh = osgnextpower2( height );
						
						// biggest possible: RGBA FLOAT
						data = malloc( outw * outh * sizeof( GL_FLOAT ) * 4 );
						
						GLint res = gluScaleImage( externalFormat, 
										width, height, type, img->getData(),
										outw, outh, type, data );
						
						if ( res )
						{
							SWARNING << "TextureChunk::initialize: "
									 << "gluScaleImage failed: " 
									 << gluErrorString( res ) << "("
									 << res << ")!" << endl;
							free( data );
							data = NULL;
						}
						else
						{
							width = outw;
							height = outh;					
						}
					}
				}
				else
					data = img->getData();
				
				if ( data )
				{
					switch ( target )
					{
					case GL_TEXTURE_1D: 
							gluBuild1DMipmaps( target, internalFormat, width,
												externalFormat, type, data );
							break;		
					case GL_TEXTURE_2D: 
							gluBuild2DMipmaps( target, internalFormat, 
												width, height,
												externalFormat, type, data );
							break;
					default:
							SFATAL << "TextureChunk::initialize: unknown target "
								   << target << "!!!" << endl;
					}

					if ( data != img->getData() )
						free( data );
					defined = true;
				} // data
			} // use gluBuildMipmaps
		} // need mipmaps?
		
		// no mipmaps, or mipmapping failed?
		if ( ! defined )
		{
			// got here needing mipmaps?
			if ( needMipmaps )	// turn them off
				glTexParameteri( target, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			
			void * data = NULL;
			// can we use the texture directly?
			if ( ! osgispower2( width ) ||
				 ! osgispower2( height )
			   )
			{
				// scale is only implemented for 2D
				if ( target != GL_TEXTURE_2D )
				{
					SWARNING << "TextureChunk::initialize: can't scale "
							 << "non-2D textures that are not 2^x !!!"
							 << endl;
				}
				else // use gluScaleImage to get to 2^
				{
					UInt32 outw = osgnextpower2( width );
					UInt32 outh = osgnextpower2( height );
					
					// biggest possible: RGBA FLOAT
					data = malloc( outw * outh * sizeof( GL_FLOAT ) * 4 );
					
					GLint res = gluScaleImage( externalFormat, 
									width, height, type, img->getData(),
									outw, outh, type, data );
					
					if ( res )
					{
						SWARNING << "TextureChunk::initialize: "
								 << "gluScaleImage failed: " 
								 << gluErrorString( res ) << "("
								 << res << ")!" << endl;
						free( data );
						data = NULL;
					}
					else
					{
						width = outw;
						height = outh;					
					}
				}
			}
			else
				data = img->getData();
			
			if ( data )
				switch ( target )
				{
				case GL_TEXTURE_1D:
					glTexImage1D( GL_TEXTURE_1D, 0, internalFormat, 
									width, 0,
									externalFormat, type, 
									data );					
					break;
				case GL_TEXTURE_2D:					
					glTexImage2D( GL_TEXTURE_2D, 0, internalFormat, 
									width, height, 0,
									externalFormat, type, 
									data );
					break;
					default:
						SFATAL << "TextureChunk::initialize: unknown target "
							   << target << "!!!" << endl;	
				}					

			if ( data != img->getData() )
				free( data );
		}
		
		glErr( "TextureChunk::initialize image" );
	}
	else if ( mode == Window::needrefresh )
	{
		SWARNING 	<< "TextureChunk(" << this << ")::handleGL: needrefresh: " 
			 		<< "not implemented yet!" << endl;		
	}
	else
	{
		SWARNING << "TextureChunk(" << this << "::handleGL: Illegal mode: " 
			 << mode << " for id " << id << endl;
	}
	
}

// little helper macro to activate genfuncs
#define setGenFunc( func, genfunc, getfunc, getplane )					\
	if ( getfunc() != GL_NONE ) 										\
	{ 																	\
		GLfloat p[4] = { getplane().getNormal()[0], 					\
						 getplane().getNormal()[1], 					\
						 getplane().getNormal()[2], 					\
						 getplane().getDistanceFromOrigin() };			\
		glTexGeni( func, GL_TEXTURE_GEN_MODE, getfunc() );				\
		if ( getfunc() == GL_OBJECT_LINEAR )							\
			glTexGenfv( func, GL_OBJECT_PLANE, p );						\
		else if ( getfunc() == GL_EYE_LINEAR )							\
			glTexGenfv( func, GL_EYE_PLANE, p );						\
		glEnable( genfunc );											\
	}																	\
	else																\
		glDisable( genfunc )

void TextureChunk::activate ( DrawAction *action, UInt32 )
{
	action->getWindow()->validateGLObject( getGLId() );

	ImageP img = getImage();
	GLenum target;		
	if ( img->getDepth() > 1 )			
	{
		SWARNING << "TextureChunk::activate: 3D textures not supported "
				 << "yet!" << endl;
		return;
	}
	else if ( img->getHeight() > 1 )		target = GL_TEXTURE_2D;
	else									target = GL_TEXTURE_1D;

	
	glBindTexture( target, getGLId() );

	// texture env	
	glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, getEnvMode() );
	
	// register combiners etc. goes here
	
	// genfuncs	
	setGenFunc( GL_S, GL_TEXTURE_GEN_S, getGenFuncS, getGenFuncSPlane );
	setGenFunc( GL_T, GL_TEXTURE_GEN_T, getGenFuncT, getGenFuncTPlane );
	setGenFunc( GL_R, GL_TEXTURE_GEN_R, getGenFuncR, getGenFuncRPlane );
	setGenFunc( GL_Q, GL_TEXTURE_GEN_Q, getGenFuncQ, getGenFuncQPlane );

	glEnable( target );
	
	glErr( "TextureChunk::activate" );
}

void TextureChunk::changeFrom( DrawAction *action, StateChunk * old, UInt32 )
{
	// change from me to me?
	// this assumes I haven't changed in the meantime. is that a valid assumption?
	if ( old == this )
		return;

	TextureChunk * oldp = dynamic_cast<TextureChunk *>(old);
	ImageP img = getImage();
	GLenum target, oldtarget;		

	if ( img->getDepth() > 1 )			
	{
		SWARNING << "TextureChunk::changeFrom: 3D textures not supported "
				 << "yet!" << endl;
		return;
	}
	else if ( img->getHeight() > 1 )		target = GL_TEXTURE_2D;
	else									target = GL_TEXTURE_1D;

	if ( oldp->getImage()->getDepth() > 1 )			
	{
		SWARNING << "TextureChunk::changeFrom: 3D textures not supported "
				 << "yet!" << endl;
		return;
	}
	else if ( oldp->getImage()->getHeight() > 1 )	oldtarget = GL_TEXTURE_2D;
	else											oldtarget = GL_TEXTURE_1D;

	if ( target != oldtarget )
		glDisable( oldtarget );
	
	action->getWindow()->validateGLObject( getGLId() );
	
	// just set them
	glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, getEnvMode() );
	setGenFunc( GL_S, GL_TEXTURE_GEN_S, getGenFuncS, getGenFuncSPlane );
	setGenFunc( GL_T, GL_TEXTURE_GEN_T, getGenFuncT, getGenFuncTPlane );
	setGenFunc( GL_R, GL_TEXTURE_GEN_R, getGenFuncR, getGenFuncRPlane );
	setGenFunc( GL_Q, GL_TEXTURE_GEN_Q, getGenFuncQ, getGenFuncQPlane );

	glBindTexture( target, getGLId() );

	if ( target != oldtarget )
		glEnable( target );
	
	glErr( "TextureChunk::changeFrom" );
}

void TextureChunk::deactivate ( DrawAction *, UInt32 )
{
	ImageP img = getImage();
	GLenum target;		
	
	if ( img->getDepth() > 1 )			
	{
		SWARNING << "TextureChunk::deactivate: 3D textures not supported "
				 << "yet!" << endl;
		return;
	}
	else if ( img->getHeight() > 1 )		target = GL_TEXTURE_2D;
	else									target = GL_TEXTURE_1D;

	glDisable( target );

	// not really needed, the init sets/resets it anyway, but cleaner
	if ( getGenFuncS() != GL_NONE ) 	glDisable( GL_TEXTURE_GEN_S );
	if ( getGenFuncT() != GL_NONE ) 	glDisable( GL_TEXTURE_GEN_T );
	if ( getGenFuncR() != GL_NONE ) 	glDisable( GL_TEXTURE_GEN_R );
	if ( getGenFuncQ() != GL_NONE ) 	glDisable( GL_TEXTURE_GEN_Q );

	glBindTexture( target, 0 );
	
	glErr( "TextureChunk::deactivate" );
}


/*-------------------------- assignment -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

void TextureChunk::dump(      UInt32     uiIndent, 
                        const BitVector &bvFlags) const
{
    SDEBUG << "Dump TextureChunk NI" << endl;
}

/*-------------------------- comparison -----------------------------------*/

Real32 TextureChunk::switchCost( StateChunk * chunk )
{
	return 0;
}

/** \brief assignment
 */

Bool TextureChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

/** \brief equal
 */

Bool TextureChunk::operator == (const StateChunk &other) const
{
	TextureChunk const *tother = dynamic_cast<TextureChunk const*>(&other);

	if ( !tother )
		return false;

	if ( tother == this )
		return true;
		
	return getImage() 		== tother->getImage() &&
			getMinFilter()	== tother->getMinFilter() &&
			getMagFilter()  == tother->getMagFilter() &&
			getWrapS()  	== tother->getWrapS() &&
			getWrapT()  	== tother->getWrapT() &&
			getWrapR()  	== tother->getWrapR() &&
			getEnvMode()  	== tother->getEnvMode() &&
			getGenFuncS()	== tother->getGenFuncS() &&
			getGenFuncT()	== tother->getGenFuncT() &&
			getGenFuncR()	== tother->getGenFuncR() &&
			getGenFuncQ()	== tother->getGenFuncQ() &&
			// not quite right. needs only to be tested for genfuncs using them
			getGenFuncSPlane()	== tother->getGenFuncSPlane() &&
			getGenFuncTPlane()	== tother->getGenFuncTPlane() &&
			getGenFuncRPlane()	== tother->getGenFuncRPlane() &&
			getGenFuncQPlane()	== tother->getGenFuncQPlane() ;
}

/** \brief unequal
 */

Bool TextureChunk::operator != (const StateChunk &other) const
{
	return ! (*this == other);
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



///---------------------------------------------------------------------------
///  FUNCTION: 
///---------------------------------------------------------------------------
//:  Example for the head comment of a function
///---------------------------------------------------------------------------
///
//p: Paramaters: 
//p: 
///
//g: GlobalVars:
//g: 
///
//r: Return:
//r: 
///
//c: Caution:
//c: 
///
//a: Assumptions:
//a: 
///
//d: Description:
//d: 
///
//s: SeeAlso:
//s: 
///---------------------------------------------------------------------------

