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

#ifndef _BINARYDATAHANDLER_H_
#define _BINARYDATAHANDLER_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBase.h>
#include <OSGBaseTypes.h>
#include <OSGException.h>

#include <vector>
#include <list>
#include <string>

OSG_BEGIN_NAMESPACE

//! Data handler for fields copyToBin, copyFromBin 
//! \ingroup FieldLib

class OSG_BASE_DLLMAPPING BinaryDataHandler 
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Exceptions                                 */
    /*! \{                                                                 */

    struct ReadError : public Exception 
    {
        ReadError(const string &reson);
    };
    
    struct WriteError : public Exception 
    {
        WriteError(const string &reson);
    };
 
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    BinaryDataHandler(UInt32 zeroCopyThreshold=0);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~BinaryDataHandler(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    void put       (      void const   *src, UInt32 size);
    void putAndFree(      MemoryHandle  src, UInt32 size);

    void putUInt8  (const UInt8        &value);
    void putUInt32 (const UInt32       &value);
    void putString (const string       &value);

    void get        (     void         *dst, UInt32 size);
    void getAndAlloc(     MemoryHandle &src, UInt32 size);

    void getUInt8   (     UInt8        &value);
    void getUInt32  (     UInt32       &value);
    void getString  (     string       &value);

    void flush      (     void               );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    struct MemoryBlock 
    {
      public:
        MemoryBlock             (MemoryHandle m, UInt32 s, UInt32 ds = 0);
        MemoryHandle getMem     (void                                   );
        UInt32       getSize    (void                                   );
        UInt32       getDataSize(void                                   );
        void         setDataSize(UInt32 dataSize                        );
        void         setSize    (UInt32 dataSize                        );
        void         setMem     (MemoryHandle m                         );

      private:
        MemoryHandle  _mem;
        UInt32        _size;
        UInt32        _dataSize;
    };

    typedef vector<MemoryBlock>  BuffersT;

    typedef list  <MemoryHandle> FreeMemT;
    
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

            BuffersT::iterator readBufBegin(void                             );
            BuffersT::iterator readBufEnd  (void                             );
            void               readBufAdd  (MemoryHandle   mem, 
                                            UInt32         size,
                                            UInt32         dataSize = 0      );
            void               readBufClear(void                             );

            BuffersT::iterator writeBufBegin(void                            );
            BuffersT::iterator writeBufEnd  (void                            );
            void               writeBufAdd  (MemoryHandle  mem, 
                                            UInt32         size,
                                            UInt32         dataSize = 0      );
            void               writeBufClear(void);

    virtual void               read       (MemoryHandle   OSG_CHECK_ARG(src),
                                           UInt32         OSG_CHECK_ARG(size));
    virtual void               readBuffer (void                              );
    virtual void               write      (MemoryHandle   src,    UInt32 size);
    virtual void               writeBuffer(void                              );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    /*---------------------------------------------------------------------*/
    /*                          Class Specific                             */

    BuffersT           _readBuffers;
    BuffersT           _writeBuffers;
    BuffersT           _zeroCopyBuffers;
    UInt32             _zeroCopyThreshold;

    FreeMemT           _freeMem;
    BuffersT::iterator _currentReadBuffer;
    UInt32             _currentReadBufferPos;
    BuffersT::iterator _currentWriteBuffer;
    UInt32             _currentWriteBufferPos;

    void pushBuffer(void);
    void pullBuffer(void);
    void freeMem   (void);

    /*!\brief prohibit default function (move to 'public' if needed) */
    BinaryDataHandler(const BinaryDataHandler &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const BinaryDataHandler &source);

    /*---------------------------------------------------------------------*/
};

OSG_END_NAMESPACE

#include "OSGBinaryDataHandler.inl"

#define OSGBINARYDATAHANDLER_HEADER_CVSID "@(#)$Id: $"

#endif /* _BINARYDATAHANDLER_H_ */
