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

#include <OSGConfig.h>

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

class Thread;
class Barrier;
class Lock;
class LockPool;
class ChangeList;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseThreading
 *  \brief ThreadManager
 */

class OSG_BASE_DLLMAPPING ThreadManager 
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef Thread   *(*CreateThreadF)   (const Char8  *szName);
    typedef Barrier  *(*CreateBarrierF)  (const Char8  *szName);
    typedef Lock     *(*CreateLockF)     (const Char8  *szName);
    typedef LockPool *(*CreateLockPoolF) (const Char8  *szName);

    typedef void      (*DestroyThreadF)  (      Thread   *threadP);
    typedef void      (*DestroyBarrierF) (      Barrier  *barrierP);
    typedef void      (*DestroyLockF)    (      Lock     *lockP);
    typedef void      (*DestroyLockPoolF)(      LockPool *lockPoolP);

    typedef map<const Char8 *, Thread *, LTString >  ThreadMap;
    typedef ThreadMap::iterator                      ThreadMapIt;

    typedef map<const Char8 *, Lock *, LTString >    LockMap;
    typedef LockMap::iterator                        LockMapIt;

    typedef map<const Char8 *, LockPool *, LTString> LockPoolMap;
    typedef LockPoolMap::iterator                    LockPoolMapIt;

    typedef map<const Char8 *, Barrier *, LTString>  BarrierMap;
    typedef BarrierMap::iterator                     BarrierMapIt;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "ThreadManager"; };

    static ThreadManager *the(void);

    static void   setNumAspects(UInt32 numApects);
    static UInt32 getNumAspects(void);

    static ChangeList *getChangeList(UInt32 aspectId);

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*--------------------- create threading element ----------------------*/

    void setThreadCreateFunc    (CreateThreadF    create);
    void setBarrierCreateFunc   (CreateBarrierF   create);
    void setLockCreateFunc      (CreateLockF      create);
    void setLockPoolCreateFunc  (CreateLockPoolF  create);

    void setThreadDestroyFunc   (DestroyThreadF   destroy);
    void setBarrierDestroyFunc  (DestroyBarrierF  destroy);
    void setLockDestroyFunc     (DestroyLockF     destroy);
    void setLockPoolDestroyFunc (DestroyLockPoolF destroy);

    Thread   *getThread         (const Char8     *szName);
    Barrier  *getBarrier        (const Char8     *szName);
    Lock     *getLock           (const Char8     *szName);
    LockPool *getLockPool       (const Char8     *szName);

    void         freeBarrier (Barrier  *barrierP);
    void         freeLock    (Lock     *lockP);
    void         freeLockPool(LockPool *lockPoolP);

    Thread   *findThread  (const Char8 *szName);
    Barrier  *findBarrier (const Char8 *szName);
    Lock     *findLock    (const Char8 *szName);    
    LockPool *findLockPool(const Char8 *szName);    

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

    void removeBarrier (Barrier  *barrierP);
    void removeLock    (Lock     *lockP);
    void removeLockPool(LockPool *lockPoolP);

    Bool init    (void);
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

    friend class FieldType;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    friend Bool OSG::osgInit(int argc, char **argv);
    friend Bool OSG::osgExit(void);

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

    static ThreadManager   _threadManagerP;

    static UInt32          _numAspects;

#ifdef OSG_RUNTIME_NUM_ASPECTS 
    static Bool            _numAspectSet;
#endif

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    CreateThreadF    _createThreadF;
    CreateBarrierF   _createBarrierF;
    CreateLockF      _createLockF;
    CreateLockPoolF  _createLockPoolF;

    DestroyThreadF   _destroyThreadF;
    DestroyBarrierF  _destroyBarrierF;
    DestroyLockF     _destroyLockF;
    DestroyLockPoolF _destroyLockPoolF;

    ThreadMap        _threadMapM;
    LockMap          _lockMapM;
    LockPoolMap      _lockPoolMapM;
    BarrierMap       _barrierMapM;

    Lock            *_tableLockP;

#if defined(OSG_USE_SPROC)
    usptr_t *_arenaP;
#endif

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    ThreadManager(void);
    virtual ~ThreadManager(void); 

    ThreadManager(const ThreadManager &source);
    void operator =(const ThreadManager &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

typedef ThreadManager *ThreadManagerP;

OSG_END_NAMESPACE

#endif /* _OSGTHREADMANAGER_H_ */





