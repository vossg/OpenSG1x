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

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! ThreadCommonBase
//! \ingroup BaseThreading

class OSG_BASE_DLLMAPPING BaseThreadCommonBase : public MPBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*=========================  PROTECTED  ===============================*/
  protected:

    typedef MPBase Inherited;

    UInt32 _uiThreadId;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    BaseThreadCommonBase(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~BaseThreadCommonBase(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class ThreadManager;

    /*!\brief prohibit default function (move to 'public' if needed) */
    BaseThreadCommonBase(const BaseThreadCommonBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const BaseThreadCommonBase &source);
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#ifdef OSG_USE_PTHREADS

//! PThreadBase
//! \ingroup BaseThreading

class BasePThreadBase : public BaseThreadCommonBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    typedef void *(*ThreadFuncF)(void *pThreadArg);

    /*---------------------------------------------------------------------*/
    /*! \name                       Get                                    */
    /*! \{                                                                 */

    static BaseThread *getCurrent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Join                                    */
    /*! \{                                                                 */

    static void join(BasePThreadBase *threadP);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Run                                     */
    /*! \{                                                                 */

    Bool run(ThreadFuncF  fThreadFunc,
             void        *pThreadArg );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Blocking                                   */
    /*! \{                                                                 */

    void block  (void);
    void unblock(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Dump                                      */
    /*! \{                                                                 */

    void print(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    typedef BaseThreadCommonBase Inherited;

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

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~BasePThreadBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    virtual void init          (void);

            void setupThread   (void);
            void setupBlockCond(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class ThreadManager;

    /*!\brief prohibit default function (move to 'public' if needed) */
    BasePThreadBase(const BasePThreadBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const BasePThreadBase &source);
};

typedef BasePThreadBase BaseThreadBase;

#endif /* OSG_USE_PTHREADS */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#ifdef OSG_USE_SPROC

//! Brief SprocBase
//! \ingroup BaseThreading

class BaseSprocBase : public BaseThreadCommonBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    typedef void *(*ThreadFuncF)(void *pThreadArg);

    /*---------------------------------------------------------------------*/
    /*! \name                       Get                                    */
    /*! \{                                                                 */

    static BaseThread *getCurrent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Join                                    */
    /*! \{                                                                 */

    static void join(BaseSprocBase *pThread);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Run                                     */
    /*! \{                                                                 */

    Bool run(ThreadFuncF  fThreadFunc,
             void        *pThreadArg);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Blocking                                   */
    /*! \{                                                                 */

    void block    (void);
    void unblock  (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    Bool exists   (void);

    void terminate(void);
    void kill     (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Dump                                      */
    /*! \{                                                                 */

    void print(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    typedef BaseThreadCommonBase Inherited;

    struct ProcessData
    {
        BaseThread *_pThread;
    };

    static void threadFunc(void       *pThreadArgP);

    /*---------------------------------------------------------------------*/
    /*! \name                   Instance Variables                         */
    /*! \{                                                                 */

    void  *_pThreadData[3];
    pid_t  _pid;

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

    virtual void init              (void);

            void setPid            (void);
            void setCurrentInternal(BaseThread *pThread);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class ThreadManager;

    /*!\brief prohibit default function (move to 'public' if needed) */
    BaseSprocBase(const BaseSprocBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const BaseSprocBase &source);
};

typedef BaseSprocBase BaseThreadBase;

#endif /* OSG_USE_SPROC */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#ifdef OSG_USE_WINTHREADS

//! Brief WinThreadBase
//! \ingroup BaseThreading

class OSG_BASE_DLLMAPPING BaseWinThreadBase : public BaseThreadCommonBase
{
    /*==========================  PUBLIC  =================================*/
   public:

    typedef void *(*ThreadFuncF)(void *pThreadArg);

    /*---------------------------------------------------------------------*/
    /*! \name                       Get                                    */
    /*! \{                                                                 */

    static BaseThread *getCurrent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Join                                    */
    /*! \{                                                                 */

    static void join(BaseWinThreadBase *pThread);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Run                                     */
    /*! \{                                                                 */

    Bool run(ThreadFuncF fThreadFunc,
             void        *pThreadArg);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Blocking                                   */
    /*! \{                                                                 */

    void block  (void);
    void unblock(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Helper                                    */
    /*! \{                                                                 */

    Bool exists   (void);

    void terminate(void);
    void kill     (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Dump                                      */
    /*! \{                                                                 */

    void print(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    typedef BaseThreadCommonBase Inherited;

#if defined(OSG_ASPECT_USE_LOCALSTORAGE)
    static UInt32 _threadKey;
#endif
#if defined(OSG_ASPECT_USE_DECLSPEC)
    static __declspec (thread) BaseThread *_pThreadLocal;
#endif

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    static void threadFunc (void *pThreadArg);

#ifdef OSG_ASPECT_USE_LOCALSTORAGE
    static void  freeThread(void);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Instance Variables                         */
    /*! \{                                                                 */

    void   *_pThreadData[3];

    Handle  _pThreadHandle;
    Handle  _pExternalHandle;
    UInt32  _uiNativeThreadId;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    BaseWinThreadBase(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Destructors                               */
    /*! \{                                                                 */

    virtual ~BaseWinThreadBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    virtual void init             (void);

            void setPid           (void);
            void setExternalHandle(Handle pExternalHandle);

            void setupThread      (void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
   private:

    friend class ThreadManager;

    /*!\brief prohibit default function (move to 'public' if needed) */
    BaseWinThreadBase(const BaseWinThreadBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const BaseWinThreadBase &source);
};

typedef BaseWinThreadBase BaseThreadBase;

#endif /* OSG_USE_WINTHREADS */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! Thread
//! \ingroup BaseThreading

class OSG_BASE_DLLMAPPING BaseThread : public BaseThreadBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    typedef MPThreadType Type;

    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */
    
    static BaseThread *get (const Char8 *szName);
    static BaseThread *find(const Char8 *szName);

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
    /*==========================  PRIVATE  ================================*/
  private:

    typedef BaseThreadBase Inherited;

    friend class ThreadManager;
    friend class MPFieldStore<BaseThread>;

    /*!\brief prohibit default function (move to 'public' if needed) */
    BaseThread(const BaseThread &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const BaseThread &source);
};

OSG_END_NAMESPACE

#define OSGBASETHREAD_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGBASETHREAD_H_ */
