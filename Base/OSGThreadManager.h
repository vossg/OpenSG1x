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


#ifndef _OSGTHREADMANAGER_H_
#define _OSGTHREADMANAGER_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <map>
#include <vector>

#include "OSGConfig.h"

#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>

#if defined(OSG_USE_SPROC)
#include <ulocks.h>
#endif

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class OSGThread;
class OSGBarrier;
class OSGLock;
class OSGLockPool;
class OSGChangeList;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

class OSGThreadManager 
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGThread   *(*OSGCreateThreadF)   (const OSGChar8  *szName);
    typedef OSGBarrier  *(*OSGCreateBarrierF)  (const OSGChar8  *szName);
    typedef OSGLock     *(*OSGCreateLockF)     (const OSGChar8  *szName);
    typedef OSGLockPool *(*OSGCreateLockPoolF) (const OSGChar8  *szName);

    typedef void         (*OSGDestroyThreadF)  (      OSGThread   *threadP);
    typedef void         (*OSGDestroyBarrierF) (      OSGBarrier  *barrierP);
    typedef void         (*OSGDestroyLockF)    (      OSGLock     *lockP);
    typedef void         (*OSGDestroyLockPoolF)(      OSGLockPool *lockPoolP);

    typedef map<const OSGChar8 *, OSGThread *, OSGLTString >  OSGThreadMap;
    typedef OSGThreadMap::iterator                            OSGThreadMapIt;

    typedef map<const OSGChar8 *, OSGLock *, OSGLTString >    OSGLockMap;
    typedef OSGLockMap::iterator                              OSGLockMapIt;

    typedef map<const OSGChar8 *, OSGLockPool *, OSGLTString> OSGLockPoolMap;
    typedef OSGLockPoolMap::iterator                          OSGLockPoolMapIt;

    typedef map<const OSGChar8 *, OSGBarrier *, OSGLTString>  OSGBarrierMap;
    typedef OSGBarrierMap::iterator                           OSGBarrierMapIt;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "OSGThreadManager"; };

    static OSGThreadManager *the(void);

    static void      setNumAspects(OSGUInt32 numApects);
    static OSGUInt32 getNumAspects(void);

    static OSGChangeList *getChangeList(OSGUInt32 aspectId);

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*--------------------- create threading element ----------------------*/

    void setThreadCreateFunc    (OSGCreateThreadF    create);
    void setBarrierCreateFunc   (OSGCreateBarrierF   create);
    void setLockCreateFunc      (OSGCreateLockF      create);
    void setLockPoolCreateFunc  (OSGCreateLockPoolF  create);

    void setThreadDestroyFunc   (OSGDestroyThreadF   destroy);
    void setBarrierDestroyFunc  (OSGDestroyBarrierF  destroy);
    void setLockDestroyFunc     (OSGDestroyLockF     destroy);
    void setLockPoolDestroyFunc (OSGDestroyLockPoolF destroy);

    OSGThread   *getThread   (const OSGChar8     *szName);
    OSGBarrier  *getBarrier  (const OSGChar8     *szName);
    OSGLock     *getLock     (const OSGChar8     *szName);
    OSGLockPool *getLockPool (const OSGChar8     *szName);

    void         freeBarrier (OSGBarrier  *barrierP);
    void         freeLock    (OSGLock     *lockP);
    void         freeLockPool(OSGLockPool *lockPoolP);

    OSGThread   *findThread  (const OSGChar8 *szName);
    OSGBarrier  *findBarrier (const OSGChar8 *szName);
    OSGLock     *findLock    (const OSGChar8 *szName);    
    OSGLockPool *findLockPool(const OSGChar8 *szName);    

#if defined(OSG_USE_SPROC)
    usptr_t *getArena(void);
#endif

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

    void removeBarrier (OSGBarrier  *barrierP);
    void removeLock    (OSGLock     *lockP);
    void removeLockPool(OSGLockPool *lockPoolP);

    OSGBool init    (void);
    void    shutdown(void);

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

    friend class OSGFieldType;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    friend OSGBool OSG::osgInit(int argc, char **argv);
    friend OSGBool OSG::osgExit(void);

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

    static OSGThreadManager   _threadManagerP;

    static OSGUInt32          _numAspects;

#ifdef OSG_RUNTIME_NUM_ASPECTS 
    static OSGBool            _numAspectSet;
#endif

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    OSGCreateThreadF    _createThreadF;
    OSGCreateBarrierF   _createBarrierF;
    OSGCreateLockF      _createLockF;
    OSGCreateLockPoolF  _createLockPoolF;

    OSGDestroyThreadF   _destroyThreadF;
    OSGDestroyBarrierF  _destroyBarrierF;
    OSGDestroyLockF     _destroyLockF;
    OSGDestroyLockPoolF _destroyLockPoolF;

    OSGThreadMap        _threadMapM;
    OSGLockMap          _lockMapM;
    OSGLockPoolMap      _lockPoolMapM;
    OSGBarrierMap       _barrierMapM;

    OSGLock            *_tableLockP;

#if defined(OSG_USE_SPROC)
    usptr_t *_arenaP;
#endif

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGThreadManager(void);
    virtual ~OSGThreadManager(void); 

    OSGThreadManager(const OSGThreadManager &source);
    void operator =(const OSGThreadManager &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

typedef OSGThreadManager *OSGThreadManagerP;

OSG_END_NAMESPACE

#endif /* _OSGTHREADMANAGER_H_ */





