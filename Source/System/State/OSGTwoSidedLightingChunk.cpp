/*!
 * \class TwoSidedLightingChunk
 * \brief
 * \author Andreas Zieringer AMZ GmbH
 */

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>

#include <OSGGL.h>

#include "OSGTwoSidedLightingChunk.h"
#include <OSGWindow.h>
#include <OSGDrawActionBase.h>
#include <OSGCamera.h>
#include <OSGTextureChunk.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass TwoSidedLightingChunk::_class("TwoSidedLighting");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TwoSidedLightingChunk::initMethod (void)
{
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

TwoSidedLightingChunk::TwoSidedLightingChunk(void) :
    Inherited(),
    _state(GL_FALSE)
{
}

TwoSidedLightingChunk::TwoSidedLightingChunk(const TwoSidedLightingChunk &source) :
    Inherited(source),
    _state(source._state)
{
}

TwoSidedLightingChunk::~TwoSidedLightingChunk(void)
{
}

/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *TwoSidedLightingChunk::getClass(void) const
{
    return &_class;
}

/*------------------------------- Sync -----------------------------------*/

void TwoSidedLightingChunk::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

/*------------------------------ Output ----------------------------------*/

void TwoSidedLightingChunk::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump TwoSidedLightingChunk NI" << std::endl;
}

/*------------------------------ State ------------------------------------*/

void TwoSidedLightingChunk::activate ( DrawActionBase * action, UInt32 idx )
{
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}

void TwoSidedLightingChunk::changeFrom( DrawActionBase *action, StateChunk *old_chunk, UInt32 idx )
{
    TwoSidedLightingChunk *old = dynamic_cast<TwoSidedLightingChunk *>(old_chunk);

    if(old == NULL)
    {
        FWARNING(( "TwoSidedLightingChunk::changeFrom: caught non-TwoSidedLightingChunk!\n"));
        return;
    }

    // TwoSidedLightingChunk didn't change so do nothing.
    if(old == this)
        return;
    
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}

void TwoSidedLightingChunk::deactivate ( DrawActionBase * action, UInt32 idx )
{
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
}


/*-------------------------- Comparison -----------------------------------*/

Real32 TwoSidedLightingChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool TwoSidedLightingChunk::operator <(const StateChunk &other) const
{
    return this < &other;
}

bool TwoSidedLightingChunk::operator ==(const StateChunk &other) const
{
    TwoSidedLightingChunk const *tother = 
                dynamic_cast<TwoSidedLightingChunk const*>(&other);

    if(!tother)
        return false;

    if(tother == this)
        return true;

    return true;
}

bool TwoSidedLightingChunk::operator !=(const StateChunk &other) const
{
    return !(*this == other);
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: OSGTwoSidedLightingChunk.cpp,v 1.2 2006/04/25 05:49:02 dirk Exp $";
    static char cvsid_hpp[] = OSGTWOSIDEDLIGHTINGCHUNK_HEADER_CVSID;
    static char cvsid_inl[] = OSGTWOSIDEDLIGHTINGCHUNK_HEADER_CVSID;
}
