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

#define OSG_COMPILEBASELIB

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"
#include "OSGLog.h"
#include "OSGBinaryDataHandler.h"
#include "OSGBaseFunctions.h"

OSG_USING_NAMESPACE

namespace 
{
    static char cvsid_cpp[] = "@(#)$Id: $";
    static char cvsid_hpp[] = OSGBINARYDATAHANDLER_HEADER_CVSID;
    static char cvsid_inl[] = OSGBINARYDATAHANDLER_INLINE_CVSID;
}

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

/** \brief Constructor
 */
BinaryDataHandler::BinaryDataHandler(void) :
    _buffers(),
    _zeroCopyBuffers(),
    _zeroCopyThreshold(0),
    _freeMem(),
    _currentReadBuffer(),
    _currentReadBufferPos(0),
    _currentWriteBuffer(),
    _readBufferEnd()
{
}

/** \brief Destructor
 */
BinaryDataHandler::~BinaryDataHandler(void)
{
    freeMem();
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/** \brief but binary data
 */
void BinaryDataHandler::put(void const *src,UInt32 size)
{
    UInt8 const *data=static_cast<UInt8 const *>(src);

    if(_zeroCopyThreshold && size>_zeroCopyThreshold)
    {
        UInt8 tag=1;
        // we have to write a tag, to indicate the membership
        // of this zero copy block to the current data block
        put(&tag,sizeof(tag));
        _zeroCopyBuffers.push_back(MemoryBlock(
            const_cast<MemoryHandle>(data),size));
    }
    else
    {
        int copySize;
        while(size)
        {
            // skip to next buffer if current buffer is full
            if(_currentWriteBuffer->dataSize == _currentWriteBuffer->size)
            {
                _currentWriteBuffer++;
                if(_currentWriteBuffer == _buffers.end())
                    pushBuffer();
                _currentWriteBuffer->dataSize=0;
            }
            copySize=osgMin(_currentWriteBuffer->size    -
                            _currentWriteBuffer->dataSize,
                             size);
            memcpy(_currentWriteBuffer->mem + _currentWriteBuffer->dataSize,
                    data,
                    copySize);
            size                         -=copySize;
            _currentWriteBuffer->dataSize+=copySize;
            data                         +=copySize;
        }
    }
}

/** Put data from dynamic allocated block
 *
 * The caller doesn't know, when the block will be written. So we are
 * responsible for freeing this block.
 */
void BinaryDataHandler::putAndFree(MemoryHandle src,UInt32 size)
{
    put(src,size);
    if(_zeroCopyThreshold && size>_zeroCopyThreshold)
    {
        _freeMem.push_back(src);
    }
    else
    {
        delete [] src;
    }
}

/** \brief get binary data
 */
void BinaryDataHandler::get(void *dst,UInt32 size)
{
    MemoryHandle data=static_cast<MemoryHandle>(dst);

    if(_zeroCopyThreshold && size>_zeroCopyThreshold)
    {
        UInt8 tag;
        // we have to read the tag, to force reading of data blocks
        // if the first data field was zero copied
        get(&tag,sizeof(tag));
        // read direct into destination
        read(data,size);
    }
    else
    {
        int copySize;
        while(size)
        {
            // skip to next buffer if current buffer is full
            if(_currentReadBufferPos == _currentReadBuffer->dataSize)
            {
                _currentReadBuffer++;
                // read new data if no space left
                if(_currentReadBuffer == _readBufferEnd)
                {
                    pullBuffer();
                }
                _currentReadBufferPos=0;
            }
            copySize=osgMin(_currentReadBuffer->dataSize -
                            _currentReadBufferPos,
                            size);
            memcpy(data,
                   _currentReadBuffer->mem+_currentReadBufferPos,
                   copySize);
            size                 -=copySize;
            _currentReadBufferPos+=copySize;
            data                 +=copySize;
        }
    }
}

/** read data in a dynamic allocated block
 *
 * If data was compressed or converted then it is not possible to 
 * write it into the destination memory. BinaryDataHandler doesn't
 * store data in continous memory areas. If the caller needs a
 * continuous memory then we provide a dynamic allocated block.
 * The caller is responsible to free this block.
 */
void BinaryDataHandler::getAndAlloc(MemoryHandle &src,UInt32 size)
{
    src=new UInt8 [size];
    get(src,size);
}

/** \brief write data not written 
 */
void BinaryDataHandler::flush()
{
    pushBuffer();
}

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

void BinaryDataHandler::reset()
{
    UInt32 size=0;

    // set read write buffer pos
    _currentWriteBuffer          =_buffers.begin();
    _currentWriteBuffer->dataSize=0;
    // set read buffer so that next get will cause a read
    _currentReadBuffer           =_buffers.begin();
    _readBufferEnd               =_buffers.begin();
    _readBufferEnd++;
    _currentReadBufferPos        =_currentReadBuffer->dataSize;
    // clear zero copy buffers
    _zeroCopyBuffers.clear();
}

/** \brief default buffer read
 *
 * Use direct read to implement buffer read. First read buffer size
 * and then read rest of buffer
 *
 * @return buffer iterator points behind the last buffer containing data
 */
BinaryDataHandler::BuffersT::iterator BinaryDataHandler::read()
{
    BuffersT::iterator i=_buffers.begin();
    OSG::UInt32 size,readSize;
    OSG::UInt32 p;

    // read buffer size
    read((MemoryHandle)&size,sizeof(size));
    // read rest of buffer
    for(;size;++i)
    {
        readSize=osgMin(size, i->size);
        read(i->mem,readSize);
        i->dataSize=readSize;
        size-=readSize;
    }
    // read end
    return i;
}

/** \brief direct buffer read
 *
 * \param mem    destination 
 * \param size   destination size
 *
 * write data into given buffer
 *
 */
void BinaryDataHandler::read(MemoryHandle mem,int size)
{
    SWARNING << "BinaryDataHandler::read(MemoryHandle mem,int size) called" 
             << endl;
}

/** \brief default buffer write
 *
 * @param writeEnd  iterator points behind the last buffer containing data
 *
 * Use direct write to implement buffer write.
 *
 */
void BinaryDataHandler::write(BuffersT::iterator writeEnd)
{
    BuffersT::iterator i;
    UInt32 size=0;

    // calculate blocksize
    for(i=_buffers.begin(); i!=writeEnd; ++i)
        size+=i->dataSize;
    // write buffer size
    write((MemoryHandle)&size,sizeof(size));
    // write buffers
    for(i =_buffers.begin(); i!=writeEnd; ++i)
        write(i->mem,i->dataSize);
}

/** \brief direct buffer write
 *
 * \param mem    source
 * \param size   source size
 *
 * write data into given buffer
 *
 */
void BinaryDataHandler::write(MemoryHandle mem,int size)
{
    SWARNING << "BinaryDataHandler::write(MemoryHandle mem,int size) called" 
             << endl;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void BinaryDataHandler::pushBuffer()
{
    BuffersT::iterator i,writeEnd;

    writeEnd=_currentWriteBuffer;
    if(writeEnd != _buffers.end())
        writeEnd++;
    // write buffers
    write(writeEnd);
    // direct write zero copy buffers
    for(i =_zeroCopyBuffers.begin();
        i!=_zeroCopyBuffers.end();++i)
        write(i->mem,i->size);
    _zeroCopyBuffers.clear();
    // remove bufers given with getAndFree
    freeMem();
    // reset buffer pos
    _currentWriteBuffer          =_buffers.begin();
    _currentWriteBuffer->dataSize=0;
}

void BinaryDataHandler::pullBuffer()
{
    // read buffers
    _readBufferEnd = read();
    _currentReadBuffer   =_buffers.begin();
    _currentReadBufferPos=0;
}

void BinaryDataHandler::freeMem()
{
    for(FreeMemT::iterator i=_freeMem.begin();i!=_freeMem.end();++i)
        delete [] *i;
    _freeMem.clear();
}




