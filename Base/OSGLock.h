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


#ifndef _OSGLOCK_H_
#define _OSGLOCK_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBase.h>
#include <OSGConfig.h>

#if ! defined (OSG_USE_PTHREADS)   && \
    ! defined (OSG_USE_SPROC)      && \
    ! defined (OSG_USE_WINTHREADS)
#error "No threading model defined,  check your system/compiler combination"
#endif

#include <OSGBaseTypes.h>
#include <OSGMPBase.h>

#if defined (OSG_USE_PTHREADS)
#include <pthread.h>
#endif

#if defined (OSG_USE_SPROC)
#include <ulocks.h>
#endif

OSG_BEGIN_NAMESPACE

static const UInt32 uiLockPoolSize = 32;
static const UInt32 uiLockPoolMask = 0x0f80;

template <class MPFieldT>
class MPFieldStore;

/*! \ingroup BaseThreading
 *  \brief LockCommonBase
 */

class OSG_BASE_DLLMAPPING LockCommonBase : public MPBase
{
    /*==========================  PRIVATE  ================================*/
  private:

    typedef MPBase Inherited;
  
    static char cvsid[];

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    LockCommonBase  (const LockCommonBase &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Assignment                                 */
    /*! \{                                                                 */

    void operator =     (const LockCommonBase &source);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    UInt32  _uiLockId;
  
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    LockCommonBase(          void                               );
    LockCommonBase(const Char8 *szName, UInt32 uiId     );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~LockCommonBase(void); 
    
    /*! \}                                                                 */

};

#if defined (OSG_USE_PTHREADS)

/*! \ingroup BaseThreading
 *  \brief PThreadLockBase
 */

class PThreadLockBase : public LockCommonBase
{

    /*==========================  PRIVATE  ================================*/
  private:
    
    typedef LockCommonBase Inherited;

    friend class LockPool;

    static char cvsid[];

    pthread_mutex_t _pLowLevelLock;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    PThreadLockBase(const PThreadLockBase &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Assignment                                 */
    /*! \{                                                                 */

    void operator =(const PThreadLockBase &source);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    PThreadLockBase(        void                        );
    PThreadLockBase(const   Char8 *szName, UInt32 uiId  );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~PThreadLockBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    Bool    init    (void);
    void    shutdown(void);

    /*! \}                                                                 */
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    void    aquire (void);
    void    release(void);
    Bool    request(void);
    
    /*! \}                                                                 */

};

typedef PThreadLockBase LockBase;

#endif /* OSG_USE_PTHREADS */

#if defined (OSG_USE_SPROC)

/*! \ingroup BaseThreading
 *  \brief SprocLockBase
 */

class SprocLockBase : public LockCommonBase
{
    /*==========================  PRIVATE  ================================*/
  private:

    typedef LockCommonBase Inherited;

    friend class LockPool;

    static char cvsid[];

    ulock_t    _pLowLevelLock;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */
    
    SprocLockBase(const SprocLockBase &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Assignment                                 */
    /*! \{                                                                 */

    void operator =(const SprocLockBase &source);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SprocLockBase(      void                        );
    SprocLockBase(const Char8 *szName, UInt32 uiId  );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~SprocLockBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    Bool    init    (void);
    void    shutdown(void);
    
    /*! \}                                                                 */
    /*==========================  PUBLIC  =================================*/
  public :
    
      /*-------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    void    aquire (void);
    void    release(void);
    Bool    request(void);

    /*! \}                                                                     */   
};

typedef SprocLockBase LockBase;

#endif /* OSG_USE_SPROC */


#if defined (OSG_USE_WINTHREADS)

#if _WIN32_WINNT < 0x0400
#define OSG_WINLOCK_USE_MUTEX
#endif

/*! \ingroup BaseThreading
 *  \brief WinThreadLockBase
 */

class OSG_BASE_DLLMAPPING WinThreadLockBase : public LockCommonBase
{

    /*==========================  PRIVATE  ================================*/
  private:

    typedef LockCommonBase Inherited;

    friend class LockPool;

    static char cvsid[];

#ifdef OSG_WINLOCK_USE_MUTEX
    Handle  _pMutex;
#else
    CRITICAL_SECTION _pCriticalSection;
#endif
  
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    WinThreadLockBase(const WinThreadLockBase &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Assignment                                 */
    /*! \{                                                                 */

    void operator =(const WinThreadLockBase &source);
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:
    
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    WinThreadLockBase(      void                        );
    WinThreadLockBase(const Char8 *szName, UInt32 uiId  );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~WinThreadLockBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */
    
    Bool    init    (void);
    void    shutdown(void);

    /*! \}                                                                 */
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    void    aquire (void);
    void    release(void);
    Bool    request(void);
    
    /*! \}                                                                 */

};

typedef WinThreadLockBase LockBase;

#endif /* OSG_USE_WINTHREADS */


/*! \ingroup BaseThreading
 *  \brief Lock
 */

class OSG_BASE_DLLMAPPING Lock : public LockBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    typedef MPLockType Type;

    /*==========================  PRIVATE  ================================*/
  private:

    typedef LockBase Inherited;

    friend class LockPool;
    friend class MPFieldStore<Lock>;

    static char cvsid[];

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    Lock(const Lock &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Assignment                                 */
    /*! \{                                                                 */

    void operator =(const Lock &source);
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    static MPLockType _type;
  
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    static Lock *create(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Lock(      void                             );
    Lock(const Char8 *szName, UInt32 uiId   );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~Lock(void);

    /*! \}                                                                 */
};

/*! \ingroup BaseThreading
 *  \brief LockPool
 */

class OSG_BASE_DLLMAPPING LockPool : public LockCommonBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    typedef MPLockPoolType Type;

    /*==========================  PRIVATE  ================================*/
  private:

    typedef LockCommonBase Inherited;

    friend class MPFieldStore<LockPool>;

    static char cvsid[];

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    LockPool(const LockPool &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Assignment                                 */
    /*! \{                                                                 */

    void operator =(const LockPool &source);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    static MPLockPoolType _type;
    
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    static LockPool *create(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    Lock    _pLocks    [uiLockPoolSize];

#ifdef OSG_DEBUG_LOCK_STAT
    UInt32  _pLockStats[uiLockPoolSize];
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    LockPool(const Char8 *szName, UInt32 uiId);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~LockPool(void);
     
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    Bool    init    (void);
    void    shutdown(void);
        
    /*! \}                                                                 */
    /*==========================  PUBLIC  =================================*/
  public :
    
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    void    aquire (void *keyP);
    void    release(void *keyP);
    Bool    request(void *keyP);
    
    /*! \}                                                                 */

};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef Lock     *LockP;
typedef LockPool *LockPoolP;

OSG_END_NAMESPACE

#endif /* _OSGLOCK_H_ */
