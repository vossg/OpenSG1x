/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#include <OSGViewport.h>
#include <OSGMaterial.h>
#include <OSGCamera.h>
#include <OSGTileCameraDecorator.h>

#include "OSGPolygonForeground.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PolygonForeground
    \ingroup GrpSystemWindowForegrounds
    
A foreground that renders a single polygon used the specified material, 
see \ref PageSystemPolygonForeground for a
description. 

The polygon material is defined by _sfMaterial, the positions by _mfPositions,
the texture coordinates by _mfTexCoords. The interpretation of the positions is
controlled by _sfNormalizedX and _sfNormalizedY.

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PolygonForeground::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PolygonForeground::PolygonForeground(void) :
    Inherited()
{
}

PolygonForeground::PolygonForeground(const PolygonForeground &source) :
    Inherited(source)
{
}

PolygonForeground::~PolygonForeground(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PolygonForeground::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PolygonForeground::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PolygonForeground NI" << std::endl;
}

Real32 PolygonForeground::mapCoordinate(Real32 val, Real32 max, bool norm)
{
    if(val >= 0)
    {
        if (norm)
            val *= max;
    }
    else
    {
        val += 1;
        
        if (norm)
            val *= max;
        
        val = max + val;
    }
   
    return val;
}
    
void PolygonForeground::draw(DrawActionBase *act, Viewport *port)
{
    if(getActive() == false)
        return;
	
    if(getPositions().getSize() == 0) // nothing to render
        return;

    if(port->getPixelWidth()  == 0 ||
       port->getPixelHeight() == 0   ) // nothing to render to
        return;
        
    if(getPositions().getSize() != getTexCoords().getSize())
    {
        FWARNING(("PolygonForeground::draw: positions and texcoords have "
                  "different sizes (%d vs. %d)!\n", 
                  getPositions().getSize(), getTexCoords().getSize()));
        return;
    }
       
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    Real32 aspectX = 1.0f, aspectY = 1.0f;
    
    if (getAspectHeight() && getAspectWidth())
    {
        aspectX = ((Real32)port->getPixelHeight()/getAspectHeight()) /
                  ((Real32)port->getPixelWidth() / getAspectWidth());
    }
 
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
	
	Real32 sFac = getScale() > 0 ? getScale() : 1.0f;
	
	UInt32 width  = port->getPixelWidth(),
		   height = port->getPixelHeight();
    
    Camera *cP = act->getCamera();
    TileCameraDecorator *cdP = dynamic_cast<TileCameraDecorator*>(cP);
	
	while (cdP != NULL)
	{
		width  = cdP->getFullWidth()  ? cdP->getFullWidth()  : width;
		height = cdP->getFullHeight() ? cdP->getFullHeight() : height;
		
		cP  = cdP->getDecoratee().getCPtr();
		cdP = dynamic_cast<TileCameraDecorator*>(cP);
	}
	
	cP = act->getCamera();
	cdP = dynamic_cast<TileCameraDecorator*>(cP);
    
    if (cdP && !getTile())
    {
        Real32 t = 0,
               left   = cdP->getLeft(),
               right  = cdP->getRight(),
               top    = cdP->getTop(),
               bottom = cdP->getBottom();
        
        if (getAspectHeight() && getAspectWidth() &&
            height != 0 && width != 0)
        {
            aspectX = ((Real32)height/getAspectHeight()) /
                      ((Real32)width / getAspectWidth());
            t  = (Real32)width * (1 - aspectX) * 0.5f;
            t *= (Real32)port->getPixelWidth() / width;
        }
		
		Matrix sm;
		cP->getDecoration(sm, width, height);
        
        glLoadMatrixf(sm.getValues());
        glOrtho(0, port->getPixelWidth(), 0, port->getPixelHeight(), 0, 1);

        glTranslatef(t, 0, 0);
        glScalef(aspectX, aspectY, 1);

        float t1 = (1 - sFac) * 0.5f * (Real32)port->getPixelWidth();
        float t2 = (1 - sFac) * 0.5f * (Real32)port->getPixelHeight();
        glTranslatef(t1, t2, 0);
        glScalef(sFac,sFac,1);
    }
    else
    {
        glScalef(sFac,sFac,1);
        
        glScalef(aspectX, aspectY, 1);
        glOrtho(0, port->getPixelWidth(), 0, port->getPixelHeight(), 0, 1);    
    }
    
    getMaterial()->getState()->activate(act);
    
    Vec3f *tc  = &getTexCoords()[0];
    Pnt2f *pos = &getPositions()[0];
    
    glBegin(GL_POLYGON);
    
    for (UInt16 i = 0; i < getPositions().size(); i++)
    {
        glTexCoord3fv( tc[i].getValues() );
        glVertex2f( mapCoordinate(pos[i][0], Real32(port->getPixelWidth()),
                                             getNormalizedX()),
                    mapCoordinate(pos[i][1], Real32(port->getPixelHeight()),
                                             getNormalizedY()) );
    }

    glEnd();
    
    getMaterial()->getState()->deactivate(act);

    glScalef(1, 1, 1);
    
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glPopAttrib();
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGPolygonForeground.cpp,v 1.5 2007/03/09 16:59:50 yjung Exp $";
    static Char8 cvsid_hpp       [] = OSGPOLYGONFOREGROUNDBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPOLYGONFOREGROUNDBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPOLYGONFOREGROUNDFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

