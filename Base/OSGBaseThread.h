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


#ifndef _OSGBASETHREAD_H_
#define _OSGBASETHREAD_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBase.h>
#include <OSGBaseTypes.h>
#include <OSGMPBase.h>

#ifdef OSG_USE_PTHREADS
#include <pthread.h>
#endif

#include <utility>

#include <OSGBaseTypes.h>

#if ! defined (OSG_USE_PTHREADS)   && \
    ! defined (OSG_USE_SPROC)      && \
    ! defined (OSG_USE_WINTHREADS)
#error "No threading model defined,  check your system/compiler combination"
#endif


OSG_BEGIN_NAMESPACE

class BaseThread;

template <class MPFieldT>
class MPFieldStore;

/*! \ingroup BaseThreading
 *  \brief ThreadCommonBase
 */

class OSG_BASE_DLLMAPPING BaseThreadCommonBase : public MPBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*==========================  PRIVATE  ================================*/
  private:

    typedef MPBase Inherited;

    friend class ThreadManager;

    static char cvsid[];

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    BaseThreadCommonBase(const BaseThreadCommonBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Operators                                  */
    /*! \{                                                                 */

    void operator =(const BaseThreadCommonBase &source);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    UInt32      _uiThreadId;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    BaseThreadCommonBase(void);
    BaseThreadCommonBase(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~BaseThreadCommonBase(void);

    /*! \}                                                                 */
};

#ifdef OSG_USE_PTHREADS

/*! \ingroup BaseThreading
 *  \brief PThreadBase
 */

class BasePThreadBase : public BaseThreadCommonBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    typedef void *(*ThreadFuncF)(void *pThreadArg);

    /*==========================  PRIVATE  ================================*/
  private:

    typedef BaseThreadCommonBase Inherited;

    friend class ThreadManager;

    static char cvsid[];

    /*=========================  PROTECTED  ===============================*/
  protected:

#ifdef OSG_ASPECT_USE_PTHREADKEY
    static pthread_key_t        _threadKey;
#endif

#if defined(OSG_ASPECT_USE_PTHREADSELF) || defined(OSG_ASPECT_USE_CUSTOMSELF)
    static vector<BaseThread *> _vThreads;
#endif

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    static void *threadFunc(void *pThreadArg);

#ifdef OSG_ASPECT_USE_PTHREADKEY
    static void  freeThread(void *pThread);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Instance Variables                         */
    /*! \{                                                                 */

    void            *_pThreadData[3];
    pthread_t       *_pThreadDesc;

    pthread_cond_t  *_pBlockCond;
    pthread_mutex_t *_pBlockMutex;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    BasePThreadBase(const Char8 *szName, UInt32 uiId);
    BasePThreadBase(const BasePThreadBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~BasePThreadBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    virtual void  init   (void);

    void  setupThread    (void);
    void  setupBlockCond (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Operators                                  */
    /*! \{                                                                 */

    void operator =(const BasePThreadBase &source);

    /*! \}                                                                 */
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    static BaseThread  *getCurrent(void);
    static void         join      (BasePThreadBase *threadP);
    Bool run (ThreadFuncF  fThreadFunc,
              void        *pThreadArg);

    void block  (void);
    void unblock(void);

    void print  (void);
    /*! \}                                                                 */
};

typedef BasePThreadBase BaseThreadBase;

#endif /* OSG_USE_PTHREADS */


#ifdef OSG_USE_SPROC

/*! \ingroup BaseThreading
 *  \brief Brief SprocBase
 */

class BaseSprocBase : public BaseThreadCommonBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    typedef void *(*ThreadFuncF)(void *pThreadArg);

    /*==========================  PRIVATE  ================================*/
  private:

    typedef BaseThreadCommonBase Inherited;

    friend class ThreadManager;

    static char cvsid[];

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    BaseSprocBase(const BaseSprocBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Operators                                  */
    /*! \{                                                                 */

    void operator =(const BaseSprocBase &source);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    struct ProcessData
    {
        BaseThread *_pThread;
    };

    static void threadFunc(void       *pThreadArgP);

    /*---------------------------------------------------------------------*/
    /*! \name                   Instance Variables                         */
    /*! \{                                                                 */

    void      *_pThreadData[3];
    pid_t      _pid;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    BaseSprocBase(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Destructors                               */
    /*! \{                                                                 */

    virtual ~BaseSprocBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    virtual void init      (void);

    void setPid            (void);
    void setCurrentInternal(BaseThread *pThread);

    /*! \}                                                                 */
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    static BaseThread *getCurrent(void);
    static void        join      (BaseSprocBase *pThread);

    Bool run      (ThreadFuncF  fThreadFunc,
                   void        *pThreadArg);

    void block    (void);
    void unblock  (void);

    Bool exists   (void);

    void    terminate(void);
    void    kill     (void);

    void    print    (void);
    /*! \}                                                                 */
};

typedef BaseSprocBase BaseThreadBase;

#endif /* OSG_USE_SPROC */

#ifdef OSG_USE_WINTHREADS

/*! \ingroup BaseThreading
 *  \brief Brief WinThreadBase
 */

class OSG_BASE_DLLMAPPING BaseWinThreadBase : public BaseThreadCommonBase
{
    /*==========================  PUBLIC  =================================*/
   public:

    typedef void *(*ThreadFuncF)(void *pThreadArg);

    /*==========================  PRIVATE  ================================*/
   private:

    typedef BaseThreadCommonBase Inherited;

    friend class ThreadManager;

    static char cvsid[];

    /*=========================  PROTECTED  ===============================*/
  protected:

#if defined(OSG_ASPECT_USE_LOCALSTORAGE)
    static UInt32 _threadKey;
#endif
#if defined(OSG_ASPECT_USE_DECLSPEC)
    static __declspec (thread) BaseThread *_pThreadLocal;
#endif

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

#ifdef OSG_ASPECT_USE_LOCALSTORAGE
    static void  freeThread    (void);
#endif

    static void threadFunc(void       *pThreadArg);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Instance Variables                         */
    /*! \{                                                                 */

    void *_pThreadData[3];

    Handle  _pThreadHandle;
    Handle  _pExternalHandle;
    UInt32  _uiNativeThreadId;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    BaseWinThreadBase(const Char8 *szName, UInt32 uiId);
    BaseWinThreadBase(const BaseWinThreadBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Destructors                               */
    /*! \{                                                                 */

    virtual ~BaseWinThreadBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    virtual void init     (void);

    void setPid           (void);
    void setExternalHandle(Handle pExternalHandle);

    void  setupThread     (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Operators                                  */
    /*! \{                                                                 */

    void operator =(const BaseWinThreadBase &source);
    /*! \}                                                                 */
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    static BaseThread *getCurrent(void);

    static void        join      (BaseWinThreadBase *pThread);

    Bool run      (ThreadFuncF fThreadFunc,
                   void        *pThreadArg);

    void block    (void);
    void unblock  (void);

    Bool exists   (void);

    void terminate(void);
    void kill     (void);

    void print    (void);
    /*! \}                                                                 */
};

typedef BaseWinThreadBase BaseThreadBase;

#endif /* OSG_USE_WINTHREADS */

/*! \ingroup BaseThreading
 *  \brief Thread
 */

class OSG_BASE_DLLMAPPING BaseThread : public BaseThreadBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    typedef MPThreadType Type;

    /*==========================  PRIVATE  ================================*/
  private:

    typedef BaseThreadBase Inherited;

    friend class ThreadManager;
    friend class MPFieldStore<BaseThread>;

    static char cvsid[];

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    BaseThread(const BaseThread &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Operators                                  */
    /*! \{                                                                 */

    void operator =(const BaseThread &source);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    static MPThreadType _type;

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    static BaseThread *create       (const Char8 *szName, UInt32 uiId);

    static void        initThreading(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    BaseThread(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Destructors                               */
    /*! \{                                                                 */

    virtual ~BaseThread(void);

    /*! \}                                                                 */
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */
    
    static BaseThread *get (const Char8 *szName);
    static BaseThread *find(const Char8 *szName);

    /*! \}                                                                 */
};

typedef BaseThread *BaseThreadP;

OSG_END_NAMESPACE

#endif /* _OSGTHREAD_H_ */
