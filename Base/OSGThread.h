/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
 *                                                                           *
 *          contact: {reiners|vossg}@igd.fhg.de, jbehr@zgdv.de               *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

class OSGChangeList;
class OSGThread;


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseThreading
 *  \brief OSGThreadCommonBase
 */

class OSGThreadCommonBase 
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

    static const char *getClassname(void) { return "OSGThreadCommonBase"; }
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*------------------------- your_category -------------------------------*/

    OSGChangeList *getChangeList(void);

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

    static OSGUInt32 _threadCount;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    OSGChar8      *_szName;

    OSGUInt32      _threadId;
    OSGInt32       _refCount;

    OSGUInt32      _aspectId;
    OSGChangeList *_changeListP;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGThreadCommonBase(void);
	OSGThreadCommonBase(const OSGChar8 *szName);
    virtual ~OSGThreadCommonBase(void); 

    void    addRef(void);
    void    subRef(void);

    OSGBool inUse (void);

    void setAspect    (OSGUInt32      aspectId);
    void setChangeList(OSGChangeList *changeListP);

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

    friend class OSGThreadManager;

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

    OSGThreadCommonBase(const OSGThreadCommonBase &source);
    void operator =(const OSGThreadCommonBase &source);
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#ifdef OSG_USE_PTHREADS

/*! \ingroup BaseThreading
 *  \brief OSGPThreadBase
 */

class OSGPThreadBase : public OSGThreadCommonBase
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef void *(*OSGThreadFuncF)(void *threadArgP);

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char     *getClassname(void) { return "OSGPThreadBase"; };

    static OSGUInt32       getAspect           (void);
    static OSGThread      *getCurrent          (void);
    static OSGChangeList  *getCurrentChangeList(void);

    static void            join                (OSGPThreadBase *threadP);

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*------------------------- your_category -------------------------------*/

    OSGBool run(OSGThreadFuncF threadFunc, 
                OSGUInt32      aspectId,
                void          *threadArgP);

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

	OSGPThreadBase(const OSGChar8 *szName);
    virtual ~OSGPThreadBase(void); 
  
  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGThreadCommonBase Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class OSGThreadManager;

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
    static OSGUInt16       _aspectsA    [OSG_NUM_ASPECTS];
    static OSGThread      *_threadsA    [OSG_NUM_ASPECTS];
    static OSGChangeList  *_changelistsA[OSG_NUM_ASPECTS];
#endif
#ifdef OSG_RUNTIME_NUM_ASPECTS
    static OSGUInt16      *_aspectsA;
    static OSGThread     **_threadsA;
    static OSGChangeList **_changelistsA;
#endif

#endif

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static void *threadFunc(void *threadArgP);
    static void        init(OSGThread *thisP);


    static OSGPThreadBase  *create (const OSGChar8 *szName);
    static void             destroy(OSGPThreadBase *threadP);


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

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    void  setupAspect     (void);
    void  setupThreadP    (void);
    void  setupChangeListP(void);

    OSGPThreadBase(const OSGPThreadBase &source);
    void operator =(const OSGPThreadBase &source);
};

typedef OSGPThreadBase OSGThreadBase;

#endif /* OSG_USE_PTHREADS */


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#ifdef OSG_USE_SPROC

/*! \ingroup BaseThreading
 *  \brief OSGSprocBase
 */

class OSGSprocBase : public OSGThreadCommonBase
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef void *(*OSGThreadFuncF)(void *threadArgP);

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char    *getClassname(void) { return "OSGSprocBase"; };

    static OSGUInt32      getAspect(void);
    static OSGThread     *getCurrent(void);
    static OSGChangeList *getCurrentChangeList(void);

    static void           join(OSGSprocBase *threadP);

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*------------------------- your_category -------------------------------*/

    OSGBool run(OSGThreadFuncF gThreadFunc, 
                OSGUInt32      aspectId,
                void          *threadArgP);


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

	OSGSprocBase(const OSGChar8 *szName);
    virtual ~OSGSprocBase(void); 
  
  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGThreadCommonBase Inherited;

    typedef struct OSGProcessData
    {
        OSGUInt32      _aspectId;
        OSGThread     *_threadP;
        OSGChangeList *_changeListP;

    } OSGProcessData;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class OSGThreadManager;

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

    static void          threadFunc(void *threadArgP);
    static void          init      (OSGThread *thisP);

    static OSGSprocBase *create    (const OSGChar8 *szName);
    static void          destroy   (OSGSprocBase *threadP);

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    void      *_threadDataA[3];
    pid_t      _pid;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    void setPid(void);

    void setAspectInternal      (OSGUInt32  aspect);
    void setCurrentInternal     (OSGThread *threadP);
    void setupChangeListInternal(void);

    OSGSprocBase(const OSGSprocBase &source);
    void operator =(const OSGSprocBase &source);
};

typedef OSGSprocBase OSGThreadBase;

#endif /* OSG_USE_SPROC */

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#ifdef OSG_USE_WINTHREADS

/*! \ingroup BaseThreading
 *  \brief OSGWinThreadBase
 */

class OSGWinThreadBase : public OSGThreadCommonBase
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef void *(*OSGThreadFuncF)(void *threadArgP);

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char    *getClassname(void) { return "OSGWinThreadBase"; };

    static OSGUInt32      getAspect           (void);
    static OSGThread     *getCurrent          (void);
    static OSGChangeList *getCurrentChangeList(void);

    static void           join(OSGWinThreadBase *threadP);

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*------------------------- your_category -------------------------------*/

    OSGBool run(OSGThreadFuncF  gThreadFunc, 
                OSGUInt32       aspectId,
                void           *threadArgP);

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

	OSGWinThreadBase(const OSGChar8 *szName);
    virtual ~OSGWinThreadBase(void); 
  
  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGThreadCommonBase Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class OSGThreadManager;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

#if defined(OSG_ASPECT_USE_LOCALSTORAGE)
	static OSGUInt32 _aspectKey;
	static OSGUInt32 _threadKey;
	static OSGUInt32 _changeListKey;
#endif
#if defined(OSG_ASPECT_USE_DECLSPEC)
	static __declspec (thread) OSGUInt32      _aspectLocal;
	static __declspec (thread) OSGThread     *_threadLocalP;
	static __declspec (thread) OSGChangeList *_changeListLocalP;
#endif

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

#ifdef OSG_ASPECT_USE_LOCALSTORAGE
    static void  freeAspect     (void);
    static void  freeThreadP    (void);
    static void  freeChangeListP(void);
#endif

    static void              threadFunc(void *threadArgP);
    static void              init      (OSGThread *thisP);

    static OSGWinThreadBase *create    (const char *szName);
    static void              destroy   (OSGWinThreadBase *threadP);

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    void *_threadDataA[3];

	OSGHandle  _threadHandle;
	OSGHandle  _externalHandle;
	OSGUInt32  _nativeThreadId;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    void setPid(void);
	void setExternalHandle(OSGHandle externalHandle);


    static void setCurrent   (OSGThread *threadP);
    void  setupAspect     (void);
    void  setupThreadP    (void);
    void  setupChangeListP(void);

    OSGWinThreadBase(const OSGWinThreadBase &source);
    void operator =(const OSGWinThreadBase &source);
};

typedef OSGWinThreadBase OSGThreadBase;

#endif /* OSG_USE_SPROC */

/*! \ingroup BaseThreading
 *  \brief OSGThread
 */

class OSGThread : public OSGThreadBase
{
  public:

    static const OSGUInt32 OSGInvalidAspect;

    virtual ~OSGThread(void) {};

  protected:

    OSGThread(const OSGThread &source);
    void operator =(const OSGThread &source);
};


//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

typedef OSGThread *OSGThreadP;

OSG_END_NAMESPACE

#endif /* OSGTHREAD_H */
