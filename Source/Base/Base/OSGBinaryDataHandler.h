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

#ifndef _BINARYDATAHANDLER_H_
#define _BINARYDATAHANDLER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGBase.h"
#include "OSGBaseTypes.h"
#include "OSGException.h"
#include "OSGBaseFunctions.h"

#include <vector>
#include <list>
#include <string>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseBase
 */

class OSG_BASE_DLLMAPPING BinaryDataHandler 
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Exceptions                                 */
    /*! \{                                                                 */

    struct ReadError : public Exception 
    {
        ReadError(const Char8 *reason);
    };
    
    struct WriteError : public Exception 
    {
        WriteError(const Char8 *reason);
    };
 
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    BinaryDataHandler(UInt32 zeroCopyThreshold = 0,
                      bool   networkOrder      = true);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~BinaryDataHandler(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Put                                   */
    /*! \{                                                                 */

    void put       (      void const   *src,   UInt32 size);
    void putAndFree(      MemoryHandle  src,   UInt32 size);

    void putValue  (const bool         &value              );
    void putValue  (const UInt8        &value              );
    void putValue  (const UInt16       &value              );
    void putValue  (const UInt32       &value              );
    void putValue  (const UInt64       &value              );
    void putValue  (const Int8         &value              );
    void putValue  (const Int16        &value              );
    void putValue  (const Int32        &value              );
    void putValue  (const Int64        &value              );
    void putValue  (const Real16       &value              );
    void putValue  (const Real32       &value              );
    void putValue  (const Real64       &value              );
    void putValue  (const Real128      &value              );
    void putValue  (const std::string  &value              );

    void putValues (const bool         *value, UInt32 size);
    void putValues (const UInt8        *value, UInt32 size);
    void putValues (const UInt16       *value, UInt32 size);
    void putValues (const UInt32       *value, UInt32 size);
    void putValues (const UInt64       *value, UInt32 size);
    void putValues (const Int8         *value, UInt32 size);
    void putValues (const Int16        *value, UInt32 size);
    void putValues (const Int32        *value, UInt32 size);
    void putValues (const Int64        *value, UInt32 size);
    void putValues (const Real16       *value, UInt32 size);
    void putValues (const Real32       *value, UInt32 size);
    void putValues (const Real64       *value, UInt32 size);
    void putValues (const Real128      *value, UInt32 size);
    void putValues (const std::string  *value, UInt32 size);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Get                                   */
    /*! \{                                                                 */

    void get        (void         *dst,   UInt32 size);
    void getAndAlloc(MemoryHandle &src,   UInt32 size);

    void getValue   (bool         &value             );
    void getValue   (UInt8        &value             );
    void getValue   (UInt16       &value             );
    void getValue   (UInt32       &value             );
    void getValue   (UInt64       &value             );
    void getValue   (Int8         &value             );
    void getValue   (Int16        &value             );
    void getValue   (Int32        &value             );
    void getValue   (Int64        &value             );
    void getValue   (Real16       &value             );
    void getValue   (Real32       &value             );
    void getValue   (Real64       &value             );
    void getValue   (Real128      &value             );
    void getValue   (std::string  &value             );
    
    void getValues  (bool         *value, UInt32 size);
    void getValues  (UInt8        *value, UInt32 size);
    void getValues  (UInt16       *value, UInt32 size);
    void getValues  (UInt32       *value, UInt32 size);
    void getValues  (UInt64       *value, UInt32 size);
    void getValues  (Int8         *value, UInt32 size);
    void getValues  (Int16        *value, UInt32 size);
    void getValues  (Int32        *value, UInt32 size);
    void getValues  (Int64        *value, UInt32 size);
    void getValues  (Real16       *value, UInt32 size);
    void getValues  (Real32       *value, UInt32 size);
    void getValues  (Real64       *value, UInt32 size);
    void getValues  (Real128      *value, UInt32 size);
    void getValues  (std::string  *value, UInt32 size);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Helper                                  */
    /*! \{                                                                 */

    virtual void forceCopy      (void      );
    virtual void forceDirectIO  (void      );

            void flush          (void      );

            void setNetworkOrder(bool value);
            bool getNetworkOrder(void      );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*! \hideinhierarchy */

    struct MemoryBlock 
    {
      public:

        MemoryBlock             (MemoryHandle m, UInt32 s, UInt32 ds = 0);

        MemoryHandle getMem     (void                                   );
        void         setMem     (MemoryHandle m                         );

        UInt32       getSize    (void                                   );
        void         setSize    (UInt32 dataSize                        );

        UInt32       getDataSize(void                                   );
        void         setDataSize(UInt32 dataSize                        );

      private:

        MemoryHandle  _mem;
        UInt32        _size;
        UInt32        _dataSize;
    };

    typedef std::vector<MemoryBlock>  BuffersT;
    typedef std::list  <MemoryHandle> FreeMemT;

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    BuffersT           _readBuffers;
    BuffersT           _writeBuffers;
    BuffersT           _zeroCopyBuffers;
    UInt32             _zeroCopyThreshold;

    FreeMemT           _freeMem;
    BuffersT::iterator _currentReadBuffer;
    UInt32             _currentReadBufferPos;
    BuffersT::iterator _currentWriteBuffer;
    UInt32             _currentWriteBufferPos;
    
    bool               _networkOrder;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Read                                    */
    /*! \{                                                                 */

            BuffersT::iterator readBufBegin(void                      );
            BuffersT::iterator readBufEnd  (void                      );
            void               readBufAdd  (MemoryHandle  mem, 
                                            UInt32        size,
                                            UInt32        dataSize = 0);
            void               readBufClear(void                      );

    virtual void               read        (MemoryHandle   src,
                                            UInt32         size       );
    virtual void               readBuffer  (void                      );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                          Write                               */
    /*! \{                                                                 */

            BuffersT::iterator writeBufBegin(void                     );
            BuffersT::iterator writeBufEnd  (void                     );
            void               writeBufAdd  (MemoryHandle mem, 
                                             UInt32       size,
                                             UInt32       dataSize = 0);
            void               writeBufClear(void                     );

    virtual void               write        (MemoryHandle   src,    
                                             UInt32         size      );
    virtual void               writeBuffer  (void                     );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Helper                                  */
    /*! \{                                                                 */

    bool isReadBufferEmpty(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name                     Internal Helper                          */
    /*! \{                                                                 */

    void pushBuffer(void);
    void pullBuffer(void);
    void freeMem   (void);

    /*! \}                                                                 */
    /*!\brief prohibit default function (move to 'public' if needed)       */
    BinaryDataHandler(const BinaryDataHandler &source);
    /*!\brief prohibit default function (move to 'public' if needed)       */
    void operator =(const BinaryDataHandler &source);
};

OSG_END_NAMESPACE

#include "OSGBinaryDataHandler.inl"

#define OSGBINARYDATAHANDLER_HEADER_CVSID "@(#)$Id: $"

#endif /* _BINARYDATAHANDLER_H_ */
