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

#include <OSGFieldContainerBase.h>
#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>
#include <OSGString.h>

#if defined(OSG_USE_SPROC)
#include <ulocks.h>
#endif

#include <map>

#include <OSGThread.h>
#include <OSGBarrier.h>
#include <OSGLock.h>
#include <OSGLog.h>

//OSG_USING_STD_NAMESPACE

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class ChangeList;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup 
 *  \brief Brief
 *
 *  detailed
 */

template <class MPFieldT>
class OSG_MULTITHREADING_DLLMAPPING MPFieldStore 
{
  public:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef typename MPFieldT::Type MPFieldType;

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef map<StringLink, MPFieldType  *> MPFieldTypeMap;
    typedef typename MPFieldTypeMap::iterator  MPFieldTypeMapIt;

    typedef typename MPFieldTypeMap::const_iterator 
        MPFieldTypeMapCIt;

    typedef map<StringLink, MPFieldT *>     MPFieldMap;
    typedef typename MPFieldMap::iterator      MPFieldMapIt;

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

    MPFieldStore(const MPFieldStore &source);
    void operator =(const MPFieldStore &source);

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

    MPFieldTypeMap _mFieldTypeMap;
    MPFieldMap     _mFieldMap;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    UInt32 registerMPType(MPFieldType *pType);

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    MPFieldStore(void);

    virtual ~MPFieldStore(void); 

    /*------------------------- your_category -------------------------------*/

    MPFieldT *getMPField   (const Char8      *szName,
                                   const Char8      *szTypeName);

    MPFieldT *findMPField  (const Char8      *szName);

    void           removeMPField(      MPFieldT *pField);

    /*------------------------- your_operators ------------------------------*/

    void clear(void);

    /*------------------------- assignment ----------------------------------*/

    MPFieldType *findMPFieldType(const Char8 *szName) const;

    /*------------------------- comparison ----------------------------------*/
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup BaseThreading
 *  \brief ThreadManager
 */

class OSG_MULTITHREADING_DLLMAPPING ThreadManager 
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

    typedef MPFieldStore<Thread  > ThreadStore;
    typedef MPFieldStore<Barrier > BarrierStore;
    typedef MPFieldStore<Lock    > LockStore;
    typedef MPFieldStore<LockPool> LockPoolStore;

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

    friend class MPThreadType;
    friend class MPBarrierType;
    friend class MPLockType;
    friend class MPLockPoolType;

    friend class Thread;
    friend class Barrier;
    friend class Lock;
    friend class LockPool;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

    static ThreadManager   *_pThreadManager;
    static Thread          *_pAppThread;

    static Bool             _bShutdownInProgress;

    static UInt32          _uiNumAspects;

#ifdef OSG_RUNTIME_NUM_ASPECTS 
    static Bool            _bNumAspectSet;
#endif

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    ThreadStore    _sThreadStore;
    BarrierStore   _sBarrierStore;
    LockStore      _sLockStore;
    LockPoolStore  _sLockPoolStore;

    Lock            *_storePLock;

#if defined(OSG_USE_SPROC)
    usptr_t *_pArena;
#endif

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

    ThreadManager(const ThreadManager &source);
    void operator =(const ThreadManager &source);

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

    static Bool initialize(Int32 &argc, Char8 **argv);
    static Bool terminate (void);

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    void removeThread  (Thread   *pThread);
    void removeBarrier (Barrier  *pBarrier);
    void removeLock    (Lock     *pLock);
    void removeLockPool(LockPool *pLockPool);

    UInt32 registerThreadType  (MPThreadType   *pType);
    UInt32 registerBarrierType (MPBarrierType  *pType);
    UInt32 registerLockType    (MPLockType     *pType);
    UInt32 registerLockPoolType(MPLockPoolType *pType);

    Bool init    (void);
    Bool shutdown(void);

    ThreadManager(void);
    virtual ~ThreadManager(void); 

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static ThreadManager *the          (void);

    static Thread        *getAppThread (void);

    static void              setNumAspects(UInt32 uiNumApects);
    static UInt32         getNumAspects(void);

    static ChangeList    *getChangeList(UInt32 aspectId);

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

     /*--------------------- create threading element ----------------------*/

    Thread   *getThread   (const Char8     *szName,
                              const Char8     *szTypeName = "OSGThread");
    Barrier  *getBarrier  (const Char8     *szName,
                              const Char8     *szTypeName = "OSGBarrier");
    Lock     *getLock     (const Char8     *szName,
                              const Char8     *szTypeName = "OSGLock");
    LockPool *getLockPool (const Char8     *szName,
                              const Char8     *szTypeName = "OSGLockPool");

    Thread   *findThread  (const Char8 *szName);
    Barrier  *findBarrier (const Char8 *szName);
    Lock     *findLock    (const Char8 *szName);    
    LockPool *findLockPool(const Char8 *szName);    

#if defined(OSG_USE_SPROC)
    usptr_t *getArena(void);
#endif

    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer
typedef ThreadManager *ThreadManagerP;

OSG_END_NAMESPACE

#include <OSGThreadManager.inl>

#endif /* _OSGTHREADMANAGER_H_ */


