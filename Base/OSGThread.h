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

#ifdef OSG_USE_PTHREADS

/*! \ingroup baselib
 *  \brief OSGPThreadBase
 *
 *  
 */
class OSGPThreadBase
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef void *(*OSGPThreadFuncF)(void *threadArgP);

    typedef         OSGPThreadFuncF OSGThreadFuncF;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char     *getClassname(void) { return "OSGPThreadBase"; };

    static void            setAspect(OSGUInt32 aspect);

    static OSGUInt32       getAspect(void);

    static OSGThread      *getCurrent(void);
        
    static OSGChangeList  *getCurrentChangeList(void);

    static void            join(OSGPThreadBase *threadP);

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    virtual ~OSGPThreadBase(void); 

    /*------------------------- your_category -------------------------------*/

    OSGBool run(OSGThreadFuncF threadFunc, void *threadArgP);

    void print(void);

    /*------------------------- your_operators ------------------------------*/


    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

    OSGBool operator < (const OSGPThreadBase &other);
    
	//bool operator == (const OSGPThreadBase &other);
	//bool operator != (const OSGPThreadBase &other);

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

	OSGPThreadBase(const char *szName, OSGUInt32 threadId);
  
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

#ifdef OSG_ASPECT_USE_PTHREADKEY
    static pthread_key_t  _aspectKey;
    static pthread_key_t  _threadKey;
    static pthread_key_t  _changelistKey;
#endif

#if defined(OSG_ASPECT_USE_PTHREADSELF) || \
    defined(OSG_ASPECT_USE_CUSTOMSELF)

#ifdef OSG_COMPILETIME_NUM_ASPECTS
    static OSGUInt16       _aspectsA[OSG_NUM_ASPECTS];
    static OSGThread      *_threadsA[OSG_NUM_ASPECTS];
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

    static void  createAspect     (void);
    static void  createThreadP    (void);
    static void  createChangeListP(void);

#ifdef OSG_ASPECT_USE_PTHREADKEY
    static void  freeAspect     (void *aspectP);
    static void  freeThreadP    (void *threadP);
    static void  freeChangeListP(void *changelistP);
#endif

    static void setCurrent      (OSGThread *threadP);

    static void             init(OSGThread *thisP);

    static OSGPThreadBase  *create(const char *szName, OSGUInt32 threadId);

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    void      *_threadDataA[3];

    char      *_szName;
    OSGUInt32  _threadId;

	pthread_t *_threadDescP;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGPThreadBase(const OSGPThreadBase &source);
    void operator =(const OSGPThreadBase &source);
};

typedef OSGPThreadBase OSGThreadBase;

#endif /* OSG_USE_PTHREADS */


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#ifdef OSG_USE_SPROC

/*! \ingroup baselib
 *  \brief OSGSprocBase
 *
 *  
 */

class OSGSprocBase
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef void *(*OSGSprocFuncF)(void *threadArgP);

    typedef         OSGSprocFuncF OSGThreadFuncF;

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

    virtual ~OSGSprocBase(void); 

    /*------------------------- your_category -------------------------------*/

    OSGBool run(OSGSprocFuncF  gThreadFunc, 
                OSGUInt32      aspectId,
                void          *threadArgP);

    OSGChangeList *getChangeList(void);

    void print(void);

    /*------------------------- your_operators ------------------------------*/


    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

    OSGBool operator < (const OSGSprocBase &other);
    
	//bool operator == (const OSGSprocBase &other);
	//bool operator != (const OSGSprocBase &other);

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

	OSGSprocBase(const char *szName, OSGUInt32 threadId);
  
  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef struct ProcessData
    {
        OSGUInt32      aspectId;
        OSGThread     *threadP;
        OSGChangeList *changelistP;

    } ProcessData;

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

    static void setCurrent         (OSGThread *threadP);

    static void          threadFunc(void *threadArgP);

    static void          init      (OSGThread *thisP);

    static OSGSprocBase *create    (const char *szName, OSGUInt32 threadId);

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    void      *_threadDataA[3];

    char      *_szName;
    OSGUInt32  _threadId;    

    OSGUInt32      _aspectId;
    OSGChangeList *_changeListP;

    pid_t      _pid;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    void setPid(void);

    void setAspectInternal(OSGUInt32 aspect);

    OSGSprocBase(const OSGSprocBase &source);
    void operator =(const OSGSprocBase &source);
};

typedef OSGSprocBase OSGThreadBase;

#endif /* OSG_USE_SPROC */

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#ifdef OSG_USE_WINTHREADS

/*! \ingroup baselib
 *  \brief OSGSprocBase
 *
 *  
 */

class OSGWinThreadBase
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef void *(*OSGWinThreadFuncF)(void *threadArgP);

    typedef         OSGWinThreadFuncF OSGThreadFuncF;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char    *getClassname(void) { return "OSGWinThreadBase"; };

    static void           setAspect(OSGUInt32 aspect);

    static OSGUInt32      getAspect(void);

    static OSGThread     *getCurrent(void);
        
    static OSGChangeList *getCurrentChangeList(void);

    static void           join(OSGWinThreadBase *threadP);

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    virtual ~OSGWinThreadBase(void); 

    /*------------------------- your_category -------------------------------*/

    OSGBool run(OSGWinThreadFuncF gThreadFunc, void *threadArgP);

    void print(void);

    /*------------------------- your_operators ------------------------------*/


    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

    OSGBool operator < (const OSGWinThreadBase &other);
    
	//bool operator == (const OSGSprocBase &other);
	//bool operator != (const OSGSprocBase &other);

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

	OSGWinThreadBase(const char *szName, OSGUInt32 threadId);
  
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

#if defined(OSG_ASPECT_USE_LOCALSTORAGE)
	static OSGUInt32 _aspectKey;
	static OSGUInt32 _threadKey;
	static OSGUInt32 _changelistKey;
#endif
#if defined(OSG_ASPECT_USE_DECLSPEC)
	static __declspec (thread) OSGUInt32      _aspectKey;
	static __declspec (thread) OSGThread     *_threadP;
	static __declspec (thread) OSGChangeList *_changelistP;
#endif

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static void  createAspect     (void);
    static void  createThreadP    (void);
    static void  createChangeListP(void);

#ifdef OSG_ASPECT_USE_LOCALSTORAGE
    static void  freeAspect     (void *aspectP);
    static void  freeThreadP    (void *threadP);
    static void  freeChangeListP(void *changelistP);
#endif

    static void setCurrent   (OSGThread *threadP);

    static void              threadFunc(void *threadArgP);

    static void              init      (OSGThread *thisP);

    static OSGWinThreadBase *create    (const char *szName, 
                                        OSGUInt32 threadId);

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    void *_threadDataA[3];

    char      *_szName;
    OSGUInt32  _threadId;    

	OSGHandle  _threadHandle;
	OSGHandle  _externalHandle;
	OSGUInt32  _nativeThreadId;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    void setPid(void);
	void setExternalHandle(OSGHandle externalHandle);

    OSGWinThreadBase(const OSGWinThreadBase &source);
    void operator =(const OSGWinThreadBase &source);
};

typedef OSGWinThreadBase OSGThreadBase;

#endif /* OSG_USE_SPROC */

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
