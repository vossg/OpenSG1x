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
#include <OSGGLEXT.h>

#include <OSGConfig.h>

#include <OSGConfig.h>
#include <OSGMaterial.h>
#include <OSGRenderAction.h>

#include <OSGFontStyle.h>
#include <OSGFontStyleFactory.h>
#include <OSGText.h>

#include <OSGSimpleGeometry.h>
#include <OSGSimpleTexturedMaterial.h>
#include <OSGSimpleSceneManager.h>
#include <OSGBaseFunctions.h>
#include <OSGTransform.h>
#include <OSGGroup.h>
#include <OSGGeometry.h>

#include <OSGFontStyleFactory.h>
#include <OSGTXFFont.h>
#include <OSGTXFFontStyle.h>
#include <OSGTTFontStyle.h>

#include <OSGSharedFontStyleFields.h>
#include <OSGSharedFontStyle.h>
#include <OSGSharedFontStyleWrapper.h>

#include "OSGScreenAlignedText.h"

OSG_USING_NAMESPACE

/*! \class osg::ScreenAlignedText

*/

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

ScreenAlignedText::ScreenAlignedText(void) :
    Inherited()
{
}

//! Copy Constructor

ScreenAlignedText::ScreenAlignedText(const ScreenAlignedText &source) :
    Inherited(source)
{
}

//! Destructor

ScreenAlignedText::~ScreenAlignedText(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void ScreenAlignedText::initMethod (void)
{
  DrawAction::registerEnterDefault( getClassType(),
                                    osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
									MaterialDrawablePtr,
                                    CNodePtr      ,
                                    Action       *>(&MaterialDrawable::drawActionHandler));
  
  RenderAction::registerEnterDefault( getClassType(),
                                      osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE,
                                      MaterialDrawablePtr  ,
                                      CNodePtr      ,
                                      Action       *>(&MaterialDrawable::renderActionHandler));

}

//! react to field changes

void ScreenAlignedText::changed(BitVector whichField, UInt32 origin)
{
	//cout << "******** ScreenAlignedText::changed called ********** " << endl;

  if( whichField & PositionFieldMask ||
      whichField & FontFieldMask ||
      whichField & TextFieldMask ||
      whichField & VerticalLineDistanceFieldMask ||
      whichField & AlignmentFieldMask ) 
  {
	  tessellate();
  }

    Inherited::changed(whichField, origin);
}

void ScreenAlignedText::tessellate(void)
{

	//cout << "ScreenAlignedText::tessellate called" << endl;

	if( _mfText.empty() )
		return;
	Text fontText;

	//SFSharedFontStylePtr *psfsp = getSFFont();
	//SFSharedFontStyleWrapperPtr *wrapperPtr = getSFFont();
	SharedFontStyleWrapperPtr wrapperPtr = getFont();
		   
	//SFSharedFontStylePtr psfsp = wrapperPtr->getSFFStyleContainer();

	//SharedFontStylePtr psfs = psfsp->getValue();
	SharedFontStylePtr psfs = wrapperPtr->getFStyleContainer();

	if( psfs == NullFC )
	{
		cerr << "ScreenAlignedText::tessellate:  psfs = NullFC ! " << endl;
		return;
	}
	FontStyleP pFS = psfs->getContainedFontStyle();
	if( pFS == NULL )
	{		
		cerr << "ScreenAlignedText::tessellate:  pFS = NULL ! " << endl;
		return;
	}

    fontText.setFontStyle( pFS );
    fontText.setJustifyMajor(MIDDLE_JT);

	// Colors are changed during rendering, 
	// but are needed for 
	// calling the fillImage routine
    Color4ub    col1( 255, 255, 255, 255);
    Color4ub    col2( 0, 0, 0, 0 );
	ImagePtr pImg = Image::create();

	std::vector<std::string> lineVec;

	for(unsigned int i = 0; i < _mfText.size(); i++ )
	{
		lineVec.push_back( _mfText[i] );
	}

	vector<NodePtr> cNodes;

    if(fontText.fillImage(pImg, lineVec, &col1, &col2,
						  false, 0, 0, SET_TEX_TCM, CLEAR_ADD_MM, 1, true ) )
    {	
		_sfRenderImage.setValue( pImg );
	}

	// cout << "ScreenAlignedText::tessellate(void)" << endl;
}

//! output the instance for debug purposes

void ScreenAlignedText::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ScreenAlignedText NI" << endl;
}
Action::ResultE ScreenAlignedText::drawPrimitives( DrawActionBase * )
{
    // some variables for faster access
    SFVec3f *pos = getSFPosition();
    Vec3f   &vec = pos->getValue();
	ImagePtr pImage =_sfRenderImage.getValue();
	GLubyte *pImageData = _sfRenderImage.getValue()->getData();
	
	
	glRasterPos3f( vec[0], vec[1], vec[2] );
	glBitmap( pImage->getWidth()*8,
			  pImage->getHeight(),
			  .0,.0,
			  GLfloat(pImage->getWidth()), 
			  GLfloat(pImage->getHeight()),
			  pImageData );
    
    return Action::Continue;
}

void ScreenAlignedText::adjustVolume( Volume & volume )
{   
    volume.setValid();
    volume.setEmpty();

    SFVec3f *sfpos = getSFPosition();
	Vec3f   &pos = sfpos->getValue();

    // go through all the cubes adjusting the volume
	volume.extendBy( Pnt3f( pos[0] + 0.0000001f,
							pos[1] + 0.0000001f,
							pos[2] + 0.0000001f ) );
	volume.extendBy( Pnt3f( pos[0] - 0.0000001f,
							pos[1] - 0.0000001f,
							pos[2] - 0.0000001f ) );
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.14 2002/06/30 05:04:23 vossg Exp $";
    static Char8 cvsid_hpp       [] = OSGSCREENALIGNEDTEXTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSCREENALIGNEDTEXTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSCREENALIGNEDTEXTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

