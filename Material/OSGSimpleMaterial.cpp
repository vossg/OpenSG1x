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
 * MERCHANTABILITY or FITNESS forA PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License formore details.                          *
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

#include <OSGAction.h>
#include <OSGDrawAction.h>
#include <OSGGeometry.h>

#include <OSGStateChunk.h>
#include <OSGState.h>
#include <OSGMaterialChunk.h>

#include "OSGSimpleMaterial.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SimpleMaterial
    \ingroup MaterialLib

The simple material class.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char SimpleMaterial::cvsid[] = "@(#)$Id: OSGSimpleMaterial.cpp,v 1.23 2002/02/26 06:10:16 vossg Exp $";

const SimpleMaterialPtr SimpleMaterial::NullPtr;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

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

void SimpleMaterial::initMethod (void)
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

SimpleMaterial::SimpleMaterial(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

SimpleMaterial::SimpleMaterial(const SimpleMaterial &source) :
    Inherited(source)
{
    _materialChunk = MaterialChunk::create();
    _blendChunk    = BlendChunk::create();

    beginEditCP(_blendChunk);
    _blendChunk->setSrcFactor (GL_SRC_ALPHA);
    _blendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
    endEditCP  (_blendChunk);
}

/** \brief Destructor
 */

SimpleMaterial::~SimpleMaterial(void)
{
    subRefCP(_materialChunk);
    subRefCP(_blendChunk);    
}


/** \brief react to field changes
 */

void SimpleMaterial::changed(BitVector, ChangeMode)
{
}

/*-------------------------- your_category---------------------------------*/

StatePtr SimpleMaterial::makeState(void)
{
    StatePtr state = State::create();

    Color3f v3;
    Color4f v4;
    float alpha = 1.f - getTransparency();

    beginEditCP(_materialChunk);

    v3 = getAmbient(); v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
    _materialChunk->setAmbient(v4);
    v3 = getDiffuse(); v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
    _materialChunk->setDiffuse(v4);
    v3 = getSpecular(); v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
    _materialChunk->setSpecular(v4);
    _materialChunk->setShininess(getShininess());
    v3 = getEmission(); v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
    _materialChunk->setEmission(v4);

    _materialChunk->setLit(getLit());
    _materialChunk->setColorMaterial(getColorMaterial());

    endEditCP(_materialChunk);

    state->addChunk(_materialChunk);

    if(isTransparent())
        state->addChunk(_blendChunk);
    
    for(MFStateChunkPtr::iterator i = _mfChunks.begin();
            i != _mfChunks.end(); ++i)
        state->addChunk(*i);

    return state;
}

void SimpleMaterial::rebuildState(void)
{
    Color3f v3;
    Color4f v4;
    Real32  alpha = 1.f - getTransparency();

    if(_pState != NullFC)
    {
        _pState->clearChunks();
    }
    else
    {
        _pState = State::create();
    }

    beginEditCP(_materialChunk);

    v3 = getAmbient();
    v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);

    _materialChunk->setAmbient(v4);

    v3 = getDiffuse();
    v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);

    _materialChunk->setDiffuse(v4);

    v3 = getSpecular();
    v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);

    _materialChunk->setSpecular(v4);

    _materialChunk->setShininess(getShininess());

    v3 = getEmission();
    v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);

    _materialChunk->setEmission(v4);

    _materialChunk->setLit(getLit());
    _materialChunk->setColorMaterial(getColorMaterial());

    endEditCP(_materialChunk);

    _pState->addChunk(_materialChunk);

    if(isTransparent())
        _pState->addChunk(_blendChunk);

    MFStateChunkPtr::iterator it        = _mfChunks.begin();
    MFStateChunkPtr::iterator chunksEnd = _mfChunks.end();

    for(; it != chunksEnd; ++it)
    {
        _pState->addChunk(*it);
    }
}

bool SimpleMaterial::isTransparent(void) const
{
    return ((getTransparency() > Eps) || (Inherited::isTransparent()));
}

/*-------------------------- assignment -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

void SimpleMaterial::dump(     UInt32    OSG_CHECK_ARG(uiIndent),
                          const BitVector OSG_CHECK_ARG(bvFlags)) const
{
    SLOG << "SimpleMaterial at " << this << endl;
    PLOG << "\tambient: " << getAmbient() << endl;
    PLOG << "\tdiffuse: " << getDiffuse()  << endl;
    PLOG << "\tspecular: " << getSpecular()  << endl;
    PLOG << "\tshininess: " << getShininess()  << endl;
    PLOG << "\temission: " << getEmission()  << endl;
    PLOG << "\ttransparency: " << getTransparency()  << endl;
    PLOG << "\tChunks: " << endl;

    for(MFStateChunkPtr::const_iterator i = _mfChunks.begin();
            i != _mfChunks.end(); i++)
        PLOG << "\t" << *i << endl;
}



/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

