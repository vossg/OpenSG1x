/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000,2001 by OpenSG Forum                   *
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

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

inline
BinaryDataHandler::ReadError::ReadError(const string &reson) : 
    Exception() 
{
    _what += "BinaryDataHandler ReadError: " + reson;
}

inline
BinaryDataHandler::WriteError::WriteError(const string &reson) : 
    Exception() 
{
    _what += "BinaryDataHandler WriteError: " + reson;
}


/** \brief store 8 bit
 **/

inline 
void BinaryDataHandler::putUInt8(const UInt8 &value)
{
    put(&value,sizeof(value));
}

/** \brief store 32 bit
 *  \bug network order?
 **/

inline 
void BinaryDataHandler::putUInt32(const UInt32 &value)
{
    put(&value,sizeof(value));
}

inline 
void BinaryDataHandler::putString(const string &value)
{
    UInt32 len;

    len=strlen(value.c_str())+1;
    putUInt32(len);
    put(value.c_str(),len);
}

inline 
void BinaryDataHandler::getUInt8(UInt8 &value)
{
    get(&value,sizeof(value));
}

inline 
void BinaryDataHandler::getUInt32(UInt32 &value)
{
    get(&value,sizeof(value));
}

inline 
void BinaryDataHandler::getString(string &value)
{
    UInt32 len;
    char *str;

    getUInt32(len);
    str=new char[len];
    get(str,len);
    value=str;
    delete str;
}

inline
BinaryDataHandler::BuffersT::iterator BinaryDataHandler::readBufBegin( void )
{
    return _readBuffers.begin();
}

inline
BinaryDataHandler::BuffersT::iterator BinaryDataHandler::readBufEnd( void )
{
    return _readBuffers.end();
}

inline
BinaryDataHandler::BuffersT::iterator BinaryDataHandler::writeBufBegin( void )
{
    return _writeBuffers.begin();
}

inline
BinaryDataHandler::BuffersT::iterator BinaryDataHandler::writeBufEnd( void )
{
    return _writeBuffers.end();
}

inline
BinaryDataHandler::MemoryBlock::MemoryBlock(MemoryHandle m,
                                            UInt32       s,
                                            UInt32       ds) : 
    _mem     ( m ),
    _size    ( s ),
    _dataSize( ds )
{
}

inline
MemoryHandle BinaryDataHandler::MemoryBlock::getMem(void)
{
    return _mem;
}

inline
UInt32 BinaryDataHandler::MemoryBlock::getSize(void)
{
    return _size;
}

inline
UInt32 BinaryDataHandler::MemoryBlock::getDataSize(void)
{
    return _dataSize;
}

inline
void BinaryDataHandler::MemoryBlock::setDataSize(UInt32 dataSize)
{
    _dataSize=dataSize;
}

inline
void BinaryDataHandler::MemoryBlock::setSize(UInt32 size)
{
    _size=size;
}

inline
void BinaryDataHandler::MemoryBlock::setMem(MemoryHandle mem)
{
    _mem=mem;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/*--------------------------- type information-----------------------------*/

/*------------------------------ access -----------------------------------*/

/*------------------------------ access -----------------------------------*/

/*------------------------------- size ----------------------------------*/

/*------------------------------- dump ----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

OSG_END_NAMESPACE

#define OSGBINARYDATAHANDLER_INLINE_CVSID "@(#)$Id: $"
