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
 * under the terms of th4e GNU Library General Public License as published    *
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

#ifndef WIN32
#include <netinet/in.h>
#endif
#include <sys/types.h>
OSG_BEGIN_NAMESPACE

// define helper functions
#if BYTE_ORDER == LITTLE_ENDIAN
inline
UInt64 htonl64(const UInt64 &src)  
{
#ifdef OSG_LONGLONG_HAS_LL
    return 
        ((src&0x00000000000000ffLL) << 56) |
        ((src&0x000000000000ff00LL) << 40) |
        ((src&0x0000000000ff0000LL) << 24) |
        ((src&0x00000000ff000000LL) << 8 ) |
        ((src&0x000000ff00000000LL) >> 8 ) |
        ((src&0x0000ff0000000000LL) >> 24) |
        ((src&0x00ff000000000000LL) >> 40) |
        ((src&0xff00000000000000LL) >> 56);
#else
    return 
        ((src&0x00000000000000ff) << 56) |
        ((src&0x000000000000ff00) << 40) |
        ((src&0x0000000000ff0000) << 24) |
        ((src&0x00000000ff000000) << 8 ) |
        ((src&0x000000ff00000000) >> 8 ) |
        ((src&0x0000ff0000000000) >> 24) |
        ((src&0x00ff000000000000) >> 40) |
        ((src&0xff00000000000000) >> 56);
#endif
}

inline
UInt64 ntohl64(const UInt64 &src)  
{
#ifdef OSG_LONGLONG_HAS_LL
    return
        ((src&0x00000000000000ffLL) << 56) |
        ((src&0x000000000000ff00LL) << 40) |
        ((src&0x0000000000ff0000LL) << 24) |
        ((src&0x00000000ff000000LL) << 8 ) |
        ((src&0x000000ff00000000LL) >> 8 ) |
        ((src&0x0000ff0000000000LL) >> 24) |
        ((src&0x00ff000000000000LL) >> 40) |
        ((src&0xff00000000000000LL) >> 56);
#else
    return
        ((src&0x00000000000000ff) << 56) |
        ((src&0x000000000000ff00) << 40) |
        ((src&0x0000000000ff0000) << 24) |
        ((src&0x00000000ff000000) << 8 ) |
        ((src&0x000000ff00000000) >> 8 ) |
        ((src&0x0000ff0000000000) >> 24) |
        ((src&0x00ff000000000000) >> 40) |
        ((src&0xff00000000000000) >> 56);
#endif
}
#else
inline
UInt64 htonl64(const UInt64 &src) 
{
    return src;   
} 

inline
UInt64 ntohl64(const UInt64 &src) 
{
    return src;   
} 
#endif


inline
BinaryDataHandler::ReadError::ReadError(const Char8 *reson) : 
    Exception() 
{
    _what += "BinaryDataHandler ReadError: ";
    _what += reson;
}

inline
BinaryDataHandler::WriteError::WriteError(const Char8 *reson) : 
    Exception() 
{
    _what += "BinaryDataHandler WriteError: ";
    _what += reson;
}

inline 
void BinaryDataHandler::putValue(const bool &value)
{
    put(&value, sizeof(bool));
}

inline 
void BinaryDataHandler::putValue(const UInt8 &value)
{
    put(&value, sizeof(UInt8));
}

inline 
void BinaryDataHandler::putValue(const UInt16 &value)
{
    UInt16 z = htons(value);
    put(&z, sizeof(UInt16));
}

inline 
void BinaryDataHandler::putValue(const UInt32 &value)
{
    UInt32 z = htonl(value);
    put(&z, sizeof(UInt32));
}

inline 
void BinaryDataHandler::putValue(const UInt64 &value)
{
    UInt64 z = htonl64(value);
    put(&z, sizeof(UInt64));
}

inline 
void BinaryDataHandler::putValue(const Int8 &value)
{
    put(&value, sizeof(Int8));
}

inline 
void BinaryDataHandler::putValue(const Int16 &value)
{
    Int16 z = htons(value);
    put(&z, sizeof(Int16));
}

inline 
void BinaryDataHandler::putValue(const Int32 &value)
{
    Int32 z = htonl(value);
    put(&z, sizeof(Int32));
}

inline 
void BinaryDataHandler::putValue(const Int64 &value)
{
    Int64 z = htonl64(value);
    put(&z, sizeof(Int64));
}

inline 
void BinaryDataHandler::putValue(const Real32 &value)
{
    UInt32 v = htonl( *((UInt32*)(&value)) );
    put(&v, sizeof(Real32));
}

inline 
void BinaryDataHandler::putValue(const Real64 &value)
{
    UInt64 v = htonl64( *((UInt64*)(&value)) );
    put(&v, sizeof(Real64));
}

inline 
void BinaryDataHandler::putValue(const string &value)
{
    UInt32 len = strlen(value.c_str()) + 1;

    putValue(len);
    if(len)
        put(value.c_str(), len);
}


inline 
void BinaryDataHandler::putValues(const bool *value, UInt32 size)
{
    put(value, size*sizeof(bool));
}

inline 
void BinaryDataHandler::putValues(const UInt8 *value, UInt32 size)
{
    put(value, size*sizeof(UInt8));
}

inline 
void BinaryDataHandler::putValues(const UInt16 *value, UInt32 size)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder)
    {
        UInt32 i;
        for(i = 0; i<size; ++i)
            putValue(value[i]);
    }
    else
#endif
    {
        put(value, size*sizeof(UInt16));
    }
}



inline 
void BinaryDataHandler::putValues(const UInt32 *value, UInt32 size)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder)
    {
        UInt32 i;
        for(i = 0; i<size; ++i)
            putValue(value[i]);
    }
    else
#endif
    {
        put(value, size*sizeof(UInt32));
    }
}


inline 
void BinaryDataHandler::putValues(const UInt64 *value, UInt32 size)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder)
    {
        UInt32 i;
        for(i = 0; i<size; ++i)
            putValue(value[i]);
    }
    else
#endif
    {
        put(value, size*sizeof(UInt64));
    }
}


inline 
void BinaryDataHandler::putValues(const Int8 *value, UInt32 size)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder)
    {
        UInt32 i;
        for(i = 0; i<size; ++i)
            putValue(value[i]);
    }
    else
#endif
    {
        put(value, size*sizeof(Int8));
    }
}



inline 
void BinaryDataHandler::putValues(const Int16 *value, UInt32 size)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder)
    {
        UInt32 i;
        for(i = 0; i<size; ++i)
            putValue(value[i]);
    }
    else
#endif
    {
        put(value, size*sizeof(Int16));
    }
}



inline 
void BinaryDataHandler::putValues(const Int32 *value, UInt32 size)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder)
    {
        UInt32 i;
        for(i = 0; i<size; ++i)
            putValue(value[i]);
    }
    else
#endif
    {
        put(value, size*sizeof(Int32));
    }
}


inline 
void BinaryDataHandler::putValues(const Int64 *value, UInt32 size)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder)
    {
        UInt32 i;
        for(i = 0; i<size; ++i)
            putValue(value[i]);
    }
    else
#endif
    {
        put(value, size*sizeof(Int64));
    }
}


inline 
void BinaryDataHandler::putValues(const Real32 *value, UInt32 size)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder)
    {
        UInt32 i;
        for(i = 0; i<size; ++i)
            putValue(value[i]);
    }
    else
#endif
    {
        put(value, size*sizeof(Real32));
    }
}


inline 
void BinaryDataHandler::putValues(const Real64 *value, UInt32 size)
{
#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder)
    {
        UInt32 i;
        for(i = 0; i<size; ++i)
            putValue(value[i]);
    }
    else
#endif
    {
        put(value, size*sizeof(Real64));
    }
}


inline 
void BinaryDataHandler::putValues(const string *value, UInt32 size)
{
    UInt32 i;
    for(i = 0; i<size; ++i)
        putValue(value[i]);    
}

inline 
void BinaryDataHandler::getValue(bool &value)
{
    get(&value, sizeof(bool));
}

inline 
void BinaryDataHandler::getValue(UInt8 &value)
{
    get(&value, sizeof(UInt8));
}

inline 
void BinaryDataHandler::getValue(UInt16 &value)
{
    get(&value, sizeof(UInt16));
    value = ntohs(value);
}

inline 
void BinaryDataHandler::getValue(UInt32 &value)
{
    get(&value, sizeof(UInt32));
    value = ntohl(value);
}

inline 
void BinaryDataHandler::getValue(UInt64 &value)
{
    get(&value, sizeof(UInt64));
    value = ntohl64(value);
}

inline 
void BinaryDataHandler::getValue(Int8 &value)
{
    get(&value, sizeof(Int8));
}

inline 
void BinaryDataHandler::getValue(Int16 &value)
{
    get(&value, sizeof(Int16));
    value = ntohs(value);
}

inline 
void BinaryDataHandler::getValue(Int32 &value)
{
    get(&value, sizeof(Int32));
    value = ntohl(value);
}

inline 
void BinaryDataHandler::getValue(Int64 &value)
{
    get(&value, sizeof(Int64));
    value = ntohl64(value);
}

inline 
void BinaryDataHandler::getValue(Real32 &value)
{
    UInt32 v;
    get(&v, sizeof(Real32));
    v = ntohl(v);
    value = *((Real32*)(&v));
}

inline 
void BinaryDataHandler::getValue(Real64 &value)
{
    UInt64 v;
    get(&v, sizeof(Real64));
    v = ntohl64(v);
    value = *((Real64*)(&v));
}

inline 
void BinaryDataHandler::getValue(string &value)
{
    UInt32  len;
    Char8  *str = NULL;

    getValue(len);
    if(len)
    {
	str = new Char8[len];

	get(str, len);
	value = str;

	delete [] str;
    }
    else
    {
        value.erase();
    }
}

inline 
void BinaryDataHandler::getValues(bool *value, UInt32 size)
{
    get(value, size*sizeof(bool));
}

inline 
void BinaryDataHandler::getValues(UInt8 *value, UInt32 size)
{
    get(value, size*sizeof(UInt8));
}

inline 
void BinaryDataHandler::getValues(UInt16 *value, UInt32 size)
{
    get(value, size*sizeof(UInt16));
#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder)
    {
        for(UInt32 i = 0; i<size; ++i)
            value[i] = ntohs(value[i]);
    }
#endif
}

inline 
void BinaryDataHandler::getValues(UInt32 *value, UInt32 size)
{
    get(value, size*sizeof(UInt32));
#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder)
    {
        for(UInt32 i = 0; i<size; ++i)
            value[i] = ntohl(value[i]);
    }
#endif
}


inline 
void BinaryDataHandler::getValues(UInt64 *value, UInt32 size)
{
    get(value, size*sizeof(UInt64));
#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder)
    {
        for(UInt32 i = 0; i<size; ++i)
            value[i] = ntohl64(value[i]);
    }
#endif
}

inline 
void BinaryDataHandler::getValues(Int8 *value, UInt32 size)
{
    get(value, size*sizeof(Int8));
}

inline 
void BinaryDataHandler::getValues(Int16 *value, UInt32 size)
{
    get(value, size*sizeof(Int16));
#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder)
    {
        for(UInt32 i = 0; i<size; ++i)
            value[i] = ntohs(value[i]);
    }
#endif
}

inline 
void BinaryDataHandler::getValues(Int32 *value, UInt32 size)
{
    get(value, size*sizeof(Int32));
#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder)
    {
        for(UInt32 i = 0; i<size; ++i)
            value[i] = ntohl(value[i]);
    }
#endif
}

inline 
void BinaryDataHandler::getValues(Int64 *value, UInt32 size)
{
    get(value, size*sizeof(Int64));
#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder)
    {
        for(UInt32 i = 0; i<size; ++i)
            value[i] = ntohl64(value[i]);
    }
#endif
}

inline 
void BinaryDataHandler::getValues(Real32 *value, UInt32 size)
{
    get(value, size*sizeof(Real32));
#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder)
    {
        UInt32 *intValue=(UInt32*)(value);
        for(UInt32 i = 0; i<size; ++i)
            intValue[i]=ntohl(intValue[i]);
    }
#endif
}

inline 
void BinaryDataHandler::getValues(Real64 *value, UInt32 size)
{
    get(value, size*sizeof(Real64));
#if BYTE_ORDER == LITTLE_ENDIAN
    if(_networkOrder)
    {
        UInt64 *longValue=(UInt64*)(value);
        for(UInt32 i = 0; i<size; ++i)
            longValue[i]=ntohl64(longValue[i]);
    }
#endif
}

inline 
void BinaryDataHandler::getValues(string *value, UInt32 size)
{
    UInt32 i;
    for(i = 0; i<size; ++i)
        getValue(value[i]);
}

inline
BinaryDataHandler::MemoryBlock::MemoryBlock(MemoryHandle m,
                                            UInt32       s,
                                            UInt32       ds) : 
    _mem     (m ),
    _size    (s ),
    _dataSize(ds)
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

inline
BinaryDataHandler::BuffersT::iterator BinaryDataHandler::readBufBegin(void)
{
    return _readBuffers.begin();
}

inline
BinaryDataHandler::BuffersT::iterator BinaryDataHandler::readBufEnd(void)
{
    return _readBuffers.end();
}

inline
BinaryDataHandler::BuffersT::iterator BinaryDataHandler::writeBufBegin(void)
{
    return _writeBuffers.begin();
}

inline
BinaryDataHandler::BuffersT::iterator BinaryDataHandler::writeBufEnd(void)
{
    return _writeBuffers.end();
}

OSG_END_NAMESPACE

#define OSGBINARYDATAHANDLER_INLINE_CVSID "@(#)$Id: $"
