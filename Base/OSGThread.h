/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

#ifndef _OSGTHREAD_H_
#define _OSGTHREAD_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGConfig.h>

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

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class ChangeList;
class Thread;


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseThreading
 *  \brief ThreadCommonBase
 */

class OSG_BASE_DLLMAPPING ThreadCommonBase 
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "ThreadCommonBase"; }
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*------------------------- your_category -------------------------------*/

    ChangeList *getChangeList(void);

    /*------------------------- your_operators ------------------------------*/

    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    static UInt32 _threadCount;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    Char8      *_szName;

    UInt32      _threadId;
    Int32       _refCount;

    UInt32      _aspectId;
    ChangeList *_changeListP;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    ThreadCommonBase(void);
	ThreadCommonBase(const Char8 *szName);
    virtual ~ThreadCommonBase(void); 

    void    addRef(void);
    void    subRef(void);

    Bool inUse (void);

    void setAspect    (UInt32      aspectId);
    void setChangeList(ChangeList *changeListP);

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class ThreadManager;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

    ThreadCommonBase(const ThreadCommonBase &source);
    void operator =(const ThreadCommonBase &source);
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#ifdef OSG_USE_PTHREADS

/*! \ingroup BaseThreading
 *  \brief PThreadBase
 */

class PThreadBase : public ThreadCommonBase
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef void *(*ThreadFuncF)(void *threadArgP);

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char  *getClassname(void) { return "PThreadBase"; };

    static UInt32       getAspect           (void);
    static Thread      *getCurrent          (void);
    static ChangeList  *getCurrentChangeList(void);

    static void         join                (PThreadBase *threadP);

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*------------------------- your_category -------------------------------*/

    Bool run(ThreadFuncF  threadFunc, 
             UInt32       aspectId,
             void        *threadArgP);

    void block  (void);
    void unblock(void);

    void print(void);

    /*------------------------- your_operators ------------------------------*/


    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	PThreadBase(const Char8 *szName);
    virtual ~PThreadBase(void); 
  
  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef ThreadCommonBase Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class ThreadManager;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

#ifdef OSG_ASPECT_USE_PTHREADKEY
    static pthread_key_t  _aspectKey;
    static pthread_key_t  _threadKey;
    static pthread_key_t  _changeListKey;
#endif

#if defined(OSG_ASPECT_USE_PTHREADSELF) || \
    defined(OSG_ASPECT_USE_CUSTOMSELF)

#ifdef OSG_COMPILETIME_NUM_ASPECTS
    static UInt16       _aspectsA    [OSG_NUM_ASPECTS];
    static Thread      *_threadsA    [OSG_NUM_ASPECTS];
    static ChangeList  *_changelistsA[OSG_NUM_ASPECTS];
#endif
#ifdef OSG_RUNTIME_NUM_ASPECTS
    static UInt16      *_aspectsA;
    static Thread     **_threadsA;
    static ChangeList **_changelistsA;
#endif

#endif

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static void *threadFunc(void *threadArgP);
    static void        init(Thread *thisP);


    static PThreadBase  *create (const Char8 *szName);
    static void          destroy(PThreadBase *threadP);


#ifdef OSG_ASPECT_USE_PTHREADKEY
    static void  freeAspect     (void *aspectP);
    static void  freeThreadP    (void *threadP);
    static void  freeChangeListP(void *changeListP);
#endif

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    void      *_threadDataA[3];
	pthread_t *_threadDescP;

    pthread_cond_t  *_blockCondP;
    pthread_mutex_t *_blockMutexP;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    void  setupAspect     (void);
    void  setupThreadP    (void);
    void  setupChangeListP(void);
    void  setupBlockCond  (void);

    PThreadBase(const PThreadBase &source);
    void operator =(const PThreadBase &source);
};

typedef PThreadBase ThreadBase;

#endif /* OSG_USE_PTHREADS */


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#ifdef OSG_USE_SPROC

/*! \ingroup BaseThreading
 *  \brief SprocBase
 */

class SprocBase : public ThreadCommonBase
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef void *(*ThreadFuncF)(void *threadArgP);

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "SprocBase"; };

    static UInt32      getAspect           (void);
    static Thread     *getCurrent          (void);
    static ChangeList *getCurrentChangeList(void);

    static void        join                (SprocBase *threadP);

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*------------------------- your_category -------------------------------*/

    Bool run    (ThreadFuncF  gThreadFunc, 
                 UInt32       aspectId,
                 void        *threadArgP);

    Bool run    (UInt32      aspectId);

    void block  (void);
    void unblock(void);

    void print  (void);

    /*------------------------- your_operators ------------------------------*/


    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	SprocBase(const Char8 *szName);
    virtual ~SprocBase(void); 

    virtual void threadFunc(void);
  
  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef ThreadCommonBase Inherited;

    typedef struct ProcessData
    {
        UInt32      _aspectId;
        Thread     *_threadP;
        ChangeList *_changeListP;

    } ProcessData;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class ThreadManager;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static void      *runInternal(void *threadP);

    static void       threadFunc (void   *threadArgP);
    static void       init       (Thread *thisP);

    static SprocBase *create     (const Char8 *szName);
    static void       destroy    (SprocBase   *threadP);

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    void      *_threadDataA[3];
    pid_t      _pid;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    void setPid(void);

    void setAspectInternal      (UInt32  aspect);
    void setCurrentInternal     (Thread *threadP);
    void setupChangeListInternal(void);

    SprocBase(const SprocBase &source);
    void operator =(const SprocBase &source);
};

typedef SprocBase ThreadBase;

#endif /* OSG_USE_SPROC */

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#ifdef OSG_USE_WINTHREADS

/*! \ingroup BaseThreading
 *  \brief WinThreadBase
 */

class OSG_BASE_DLLMAPPING WinThreadBase : public ThreadCommonBase
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef void *(*ThreadFuncF)(void *threadArgP);

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "WinThreadBase"; };

    static UInt32      getAspect           (void);
    static Thread     *getCurrent          (void);
    static ChangeList *getCurrentChangeList(void);

    static void           join(WinThreadBase *threadP);

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*------------------------- your_category -------------------------------*/

    Bool run(ThreadFuncF  gThreadFunc, 
             UInt32       aspectId,
             void        *threadArgP);

    void block  (void);
    void unblock(void);

    void print(void);

    /*------------------------- your_operators ------------------------------*/

    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	WinThreadBase(const Char8 *szName);
    virtual ~WinThreadBase(void); 
  
  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef ThreadCommonBase Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class ThreadManager;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

#if defined(OSG_ASPECT_USE_LOCALSTORAGE)
	static UInt32 _aspectKey;
	static UInt32 _threadKey;
	static UInt32 _changeListKey;
#endif
#if defined(OSG_ASPECT_USE_DECLSPEC)
	static __declspec (thread) UInt32      _aspectLocal;
	static __declspec (thread) Thread     *_threadLocalP;
	static __declspec (thread) ChangeList *_changeListLocalP;
#endif

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

#ifdef OSG_ASPECT_USE_LOCALSTORAGE
    static void  freeAspect     (void);
    static void  freeThreadP    (void);
    static void  freeChangeListP(void);
#endif

    static void           threadFunc(void *threadArgP);
    static void           init      (Thread *thisP);
    static void           setCurrent(Thread *threadP);

    static WinThreadBase *create    (const char *szName);
    static void           destroy   (WinThreadBase *threadP);

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    void *_threadDataA[3];

	Handle  _threadHandle;
	Handle  _externalHandle;
	UInt32  _nativeThreadId;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    void setPid(void);
	void setExternalHandle(Handle externalHandle);

    void setupAspect     (void);
    void setupThreadP    (void);
    void setupChangeListP(void);

    WinThreadBase(const WinThreadBase &source);
    void operator =(const WinThreadBase &source);
};

typedef WinThreadBase ThreadBase;

#endif /* OSG_USE_SPROC */

/*! \ingroup BaseThreading
 *  \brief Thread
 */

class OSG_BASE_DLLMAPPING Thread : public ThreadBase
{
  public:

    static const UInt32 InvalidAspect;

    Thread(const Char8 *szName) : ThreadBase(szName) {}
    virtual ~Thread(void) {}

  protected:

    Thread(const Thread &source);
    void operator =(const Thread &source);
};


//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

typedef Thread *ThreadP;

OSG_END_NAMESPACE

#endif /* OSGTHREAD_H */
