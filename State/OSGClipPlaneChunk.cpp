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

#define OSG_COMPILELIB

#include <OSGConfig.h>

#include <OSGDrawActionBase.h>
#include <OSGRenderAction.h>
#include <OSGCamera.h>

#include "OSGClipPlaneChunk.h"

#include <OSGGL.h>



#define	MAT16DUMP(m)	#m << " =\n"<<setiosflags(ios::right|ios::fixed|ios::showpoint)<<setprecision(3)\
   <<"[ "<<setw(9)<<m[0]<<", "<<setw(9)<<m[4]<<", "<<setw(9)<<m[8] <<", "<<setw(9)<<m[12]<<"\n"\
   <<"  "<<setw(9)<<m[1]<<", "<<setw(9)<<m[5]<<", "<<setw(9)<<m[9] <<", "<<setw(9)<<m[13]<<"\n"\
   <<"  "<<setw(9)<<m[2]<<", "<<setw(9)<<m[6]<<", "<<setw(9)<<m[10]<<", "<<setw(9)<<m[14]<<"\n"\
   <<"  "<<setw(9)<<m[3]<<", "<<setw(9)<<m[7]<<", "<<setw(9)<<m[11]<<", "<<setw(9)<<m[15]<<" ]"\
   << setprecision(6) << resetiosflags(ios::right | ios::fixed | ios::showpoint)


OSG_USING_NAMESPACE

/*! \class osg::ClipPlaneChunk
The clipPlane chunk contains the parameter that is specific set for clip planes.
*/

/*----------------------- class variables ---------------------------------*/
   
StateChunkClass ClipPlaneChunk::_class("ClipPlane", 4);

   
/*----------------------- constructors & destructors ----------------------*/

//! Constructor

ClipPlaneChunk::ClipPlaneChunk(void) :
    Inherited()
{
}

//! Copy Constructor

ClipPlaneChunk::ClipPlaneChunk(const ClipPlaneChunk &source) :
    Inherited(source)
{
}

//! Destructor

ClipPlaneChunk::~ClipPlaneChunk(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void ClipPlaneChunk::initMethod (void)
{
}

//! react to field changes

void ClipPlaneChunk::changed(BitVector, UInt32)
{
}

//! output the instance for debug purposes

void ClipPlaneChunk::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ClipPlaneChunk NI" << endl;
}


/*-------------------------- your_category---------------------------------*/

void ClipPlaneChunk::activate ( DrawActionBase *action, UInt32 idx)
{
//    SWARNING << "ClipPlaneChunk::activate(idx:" << idx << ") : " << this << endl;

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

//    SWARNING << "cameraMat:" << endl << cameraMat << endl;

    if(getBeacon() != NullFC) 
    {
        getBeacon()->getToWorld(beaconMat);
//	SWARNING << "beaconMat:" << endl << beaconMat << endl;
    }
    else
    {
        SWARNING << "NO beacon" << endl;
    }

    cameraMat.mult(beaconMat);
//    SWARNING << "productMat:" << endl << cameraMat << endl;

    
    if ( _sfEnable.getValue() != GL_FALSE )
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
        
        glClipPlane( GL_CLIP_PLANE0 + idx, glEq );
        glEnable( GL_CLIP_PLANE0 + idx );
        
        glPopMatrix();
	
//	SWARNING << " - ENABLED plane" << endl;
    }
}




void ClipPlaneChunk::changeFrom( DrawActionBase *action, StateChunk * old_chunk, UInt32 idx)
{
//    SWARNING << "ClipPlaneChunk::changeFrom(idx:" << idx << ") : " << this << endl;

    ClipPlaneChunk const *old = dynamic_cast<ClipPlaneChunk const*>(old_chunk);

    // change from me to me?
    // this assumes I haven't changed in the meantime. is that a valid assumption?
    if ( old == this )
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
//    SWARNING << "cameraMat:" << endl << cameraMat << endl;

    if (getBeacon() != NullFC) 
    {
        getBeacon()->getToWorld(beaconMat);
//	SWARNING << "beaconMat:" << endl << beaconMat << endl;
    }
    else
    {
        SWARNING << "ClipPlaneChunk::changeFrom: NO beacon" << endl;
    }
    
    cameraMat.mult(beaconMat);
//    SWARNING << "productMat:" << endl << cameraMat << endl;
    
    
    if ( _sfEnable.getValue() != old->_sfEnable.getValue() )
    {
//        SWARNING << " - SOMETHING is different" << endl;
	    
        if ( _sfEnable.getValue() != GL_FALSE )
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
	
	    glClipPlane( GL_CLIP_PLANE0 + idx, glEq );
	    glEnable( GL_CLIP_PLANE0 + idx );

	    glPopMatrix();

//            SWARNING << " - ENABLED plane" << endl;
	}
        else  
        {
	    glDisable( GL_CLIP_PLANE0 + idx );

//            SWARNING << " - DISABLED plane" << endl;
        }
    }
    else
    {
//        SWARNING << " - are the SAME" <<  endl;
    }
}


void ClipPlaneChunk::deactivate ( DrawActionBase *, UInt32 idx)
{
//    SWARNING << "ClipPlaneChunk::deactivate(idx:" << idx << ") : " << this << endl;

    if ( _sfEnable.getValue() != GL_FALSE )
    {
        glDisable( GL_CLIP_PLANE0 + idx );

//        SWARNING << " - DISABLED plane" << endl;
    }
}


/*-------------------------- comparison -----------------------------------*/

Real32 ClipPlaneChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

/** \brief assignment
 */

bool ClipPlaneChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

/** \brief equal
 */

bool ClipPlaneChunk::operator == (const StateChunk &other) const
{
    ClipPlaneChunk const *tother = dynamic_cast<ClipPlaneChunk const*>(&other);

    if ( !tother )
        return false;

    if ( _sfEnable.getValue() != tother->_sfEnable.getValue() )
        return false;

    if ( _sfEquation.getValue() != tother->_sfEquation.getValue() )
        return false;

    if ( _sfBeacon.getValue() != tother->_sfBeacon.getValue() )
        return false;
    
    return true;
}

/** \brief unequal
 */

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
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGClipPlaneChunk.cpp,v 1.2 2002/08/26 07:38:54 vossg Exp $";
    static Char8 cvsid_hpp       [] = OSGCLIPPLANECHUNKBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCLIPPLANECHUNKBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCLIPPLANECHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

