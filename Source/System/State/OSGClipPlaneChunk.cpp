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

#include <OSGConfig.h>

#include <OSGGL.h>

#include <OSGDrawActionBase.h>
#include <OSGRenderAction.h>
#include <OSGCamera.h>

#include "OSGClipPlaneChunk.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ClipPlaneChunk
    \ingroup GrpSystemState
    
See \ref PageSystemClipPlaneChunk for a description.

This chunk wraps glCLipPlane() (osg::ClipPlaneChunk::_sfEquation) and
glEnable(GL_CLIP_PLANEi) (osg::ClipPlaneChunk::_sfEnable). The coordinate
system the plane is in is defined by osg::ClipPlaneChunk::_sfBeacon.

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/
   
StateChunkClass ClipPlaneChunk::_class("ClipPlane", 6);

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/
   
/*----------------------- constructors & destructors ----------------------*/

ClipPlaneChunk::ClipPlaneChunk(void) :
    Inherited()
{
}

ClipPlaneChunk::ClipPlaneChunk(const ClipPlaneChunk &source) :
    Inherited(source)
{
}

ClipPlaneChunk::~ClipPlaneChunk(void)
{
}

/*------------------------------- Sync -----------------------------------*/

void ClipPlaneChunk::changed(BitVector, UInt32)
{
}

/*------------------------------ Output ----------------------------------*/

void ClipPlaneChunk::dump(      UInt32    , 
                          const BitVector) const
{
    SLOG << "Dump ClipPlaneChunk NI" << std::endl;
}


/*------------------------------ State ------------------------------------*/

void ClipPlaneChunk::activate(DrawActionBase *action, UInt32 idx)
{
//    SWARNING << "ClipPlaneChunk::activate(idx:" << idx << ") : " << this << std::endl;

    RenderAction *ra = dynamic_cast<RenderAction *>(action);

    Matrix beaconMat;

    if(ra != NULL)
    {
        beaconMat = ra->top_matrix();
    }
    else
    {
        beaconMat = action->getActNode()->getToWorld();
    }


    Matrix cameraMat = action->getCameraToWorld();

    cameraMat.invert();

//    SWARNING << "cameraMat:" << std::endl << cameraMat << std::endl;

    if(getBeacon() != NullFC) 
    {
        getBeacon()->getToWorld(beaconMat);
//	SWARNING << "beaconMat:" << std::endl << beaconMat << std::endl;
    }
    else
    {
        SWARNING << "NO beacon" << std::endl;
    }

    cameraMat.mult(beaconMat);
//    SWARNING << "productMat:" << std::endl << cameraMat << std::endl;

    
    if(_sfEnable.getValue() != GL_FALSE)
    {
        GLdouble glEq[4];
        Vec4f   & eq = _sfEquation.getValue();
        glEq[0] = eq[0];
        glEq[1] = eq[1];
        glEq[2] = eq[2];
        glEq[3] = eq[3];
        
        glMatrixMode(GL_MODELVIEW_MATRIX);
        glPushMatrix();
        glLoadMatrixf(cameraMat.getValues());
        
        glClipPlane( GL_CLIP_PLANE0 + idx, glEq);
        glEnable( GL_CLIP_PLANE0 + idx);
        
        glPopMatrix();
	
//	SWARNING << " - ENABLED plane" << std::endl;
    }
}




void ClipPlaneChunk::changeFrom(DrawActionBase *action, StateChunk * old_chunk, 
                                UInt32 idx)
{
//    SWARNING << "ClipPlaneChunk::changeFrom(idx:" << idx << ") : " << this << std::endl;

    ClipPlaneChunk const *old = dynamic_cast<ClipPlaneChunk const*>(old_chunk);

    // change from me to me?
    // this assumes I haven't changed in the meantime. is that a valid assumption?
    if(old == this)
        return;


    RenderAction *ra = dynamic_cast<RenderAction *>(action);

    Matrix beaconMat;

    if(ra != NULL)
    {
        beaconMat = ra->top_matrix();
    }
    else
    {
        beaconMat = action->getActNode()->getToWorld();
    }


    Matrix cameraMat = action->getCameraToWorld();

    cameraMat.invert();
//    SWARNING << "cameraMat:" << std::endl << cameraMat << std::endl;

    if (getBeacon() != NullFC) 
    {
        getBeacon()->getToWorld(beaconMat);
//	SWARNING << "beaconMat:" << std::endl << beaconMat << std::endl;
    }
    else
    {
        SWARNING << "ClipPlaneChunk::changeFrom: NO beacon" << std::endl;
    }
    
    cameraMat.mult(beaconMat);
//    SWARNING << "productMat:" << std::endl << cameraMat << std::endl;
    
    
    if(_sfEnable.getValue() != old->_sfEnable.getValue())
    {
//        SWARNING << " - SOMETHING is different" << std::endl;
	    
        if(_sfEnable.getValue() != GL_FALSE)
        {
	    GLdouble glEq[4];
	    Vec4f   & eq = _sfEquation.getValue();
	    glEq[0] = eq[0];
	    glEq[1] = eq[1];
	    glEq[2] = eq[2];
	    glEq[3] = eq[3];
	    
	    glMatrixMode(GL_MODELVIEW_MATRIX);
	    glPushMatrix();
	    glLoadMatrixf(cameraMat.getValues());
	
	    glClipPlane( GL_CLIP_PLANE0 + idx, glEq);
	    glEnable( GL_CLIP_PLANE0 + idx);

	    glPopMatrix();

//            SWARNING << " - ENABLED plane" << std::endl;
	}
        else  
        {
	    glDisable( GL_CLIP_PLANE0 + idx);

//            SWARNING << " - DISABLED plane" << std::endl;
        }
    }
    else
    {
//        SWARNING << " - are the SAME" <<  std::endl;
    }
}


void ClipPlaneChunk::deactivate(DrawActionBase *, UInt32 idx)
{
//    SWARNING << "ClipPlaneChunk::deactivate(idx:" << idx << ") : " << this << std::endl;

    if(_sfEnable.getValue() != GL_FALSE)
    {
        glDisable( GL_CLIP_PLANE0 + idx);

//        SWARNING << " - DISABLED plane" << std::endl;
    }
}


/*-------------------------- Comparison -----------------------------------*/

Real32 ClipPlaneChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool ClipPlaneChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool ClipPlaneChunk::operator == (const StateChunk &other) const
{
    ClipPlaneChunk const *tother = dynamic_cast<ClipPlaneChunk const*>(&other);

    if(!tother)
        return false;

    if(_sfEnable.getValue() != tother->_sfEnable.getValue())
        return false;

    if(_sfEquation.getValue() != tother->_sfEquation.getValue())
        return false;

    if(_sfBeacon.getValue() != tother->_sfBeacon.getValue())
        return false;
    
    return true;
}

bool ClipPlaneChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177)
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.13 2002/06/01 10:37:25 vossg Exp $";
    static Char8 cvsid_hpp       [] = OSGCLIPPLANECHUNK_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCLIPPLANECHUNK_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCLIPPLANECHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

