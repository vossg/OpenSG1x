/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     * 
 *                                                                           * 
 *                                                                           * 
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                * 
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

OSG_BEGIN_NAMESPACE

inline
ActorStateChunk::ActorStateChunk(UInt32 uiSize)
    : _uiSize        (uiSize                      ),
      _pStatePtrArray(new ActorStateBase *[uiSize])
{
}

inline
ActorStateChunk::ActorStateChunk(const ActorStateChunk &source)
    : _uiSize        (source._uiSize               ),
      _pStatePtrArray(new ActorStateBase *[_uiSize])
{
    for(UInt32 i = 0; i < _uiSize; ++i)
    {
        _pStatePtrArray[i] = source._pStatePtrArray[i];
    }
}

inline
ActorStateChunk::~ActorStateChunk(void)
{
    delete[] _pStatePtrArray;
}

inline ActorStateChunk::ActorStateBase *
ActorStateChunk::getEntry(UInt32 uiIndex) const
{
    return _pStatePtrArray[uiIndex];
}

inline void
ActorStateChunk::setEntry(UInt32 uiIndex, ActorStateBase *pState)
{
    _pStatePtrArray[uiIndex] = pState;
}

inline UInt32
ActorStateChunk::getSize(void) const
{
    return _uiSize;
}

inline void
ActorStateChunk::freeEntry(UInt32 uiIndex)
{
    delete _pStatePtrArray[uiIndex];

           _pStatePtrArray[uiIndex] = NULL;
}

inline void
ActorStateChunk::freeAll(void)
{
    for(UInt32 uiIndex = 0; uiIndex < _uiSize; ++uiIndex)
    {
        delete _pStatePtrArray[uiIndex];
    }
}

inline bool
ActorStateChunk::operator==(const ActorStateChunk &other) const
{
    bool   bRetVal = true;

    if(this->getSize() != other.getSize())
    {
        bRetVal = false;
    }
    else
    {
        for(UInt32 uiIndex = 0; uiIndex < this->getSize(); ++uiIndex)
        {
            if(this->getEntry(uiIndex) != other.getEntry(uiIndex))
            {
                bRetVal = false;

                break;
            }
        }
    }

    return bRetVal;
}

OSG_END_NAMESPACE

#define OSGACTORSTATECHUNK_INLINE_CVSID "@(#)$Id: OSGActorStateChunk.inl,v 1.1 2003/10/10 13:51:06 neumannc Exp $"
