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

    typedef OSGThread  *(*OSGCreateThreadF) (const char *szName, 
                                             OSGUInt32   uiThreadId);

    typedef OSGBarrier *(*OSGCreateBarrierF)(const char *szName, 
                                             OSGUInt32   uiBarrierId);

    typedef OSGLock    *(*OSGCreateLockF)   (const char *szName, 
                                             OSGUInt32   uiLockId);

    typedef vector<OSGThread *>                           OSGThreadStore;
    typedef map<const char *, OSGThread *, OSGLTString >  OSGThreadMap;
    typedef OSGThreadMap::iterator                        OSGThreadMapIt;

    typedef vector<OSGLock *>                             OSGLockStore;
    typedef map<const char *, OSGLock *, OSGLTString >    OSGLockMap;
    typedef OSGLockMap::iterator                          OSGLockMapIt;

    typedef vector<OSGBarrier *>                          OSGBarrierStore;
    typedef map<const char *, OSGBarrier *, OSGLTString > OSGBarrierMap;
    typedef OSGBarrierMap::iterator                       OSGBarrierMapIt;

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

    virtual ~OSGThreadManager(void); 

    /*--------------------- create threading element ----------------------*/

    void setThreadCreateFunc (OSGCreateThreadF  create);
    void setBarrierCreateFunc(OSGCreateBarrierF create);
    void setLockCreateFunc   (OSGCreateLockF    create);

    OSGThread  *createThread (const char *szName);
    OSGBarrier *createBarrier(const char *szName);
    OSGLock    *createLock   (const char *szName);

    void destroyBarrier(OSGBarrier *barrierP);
    void destroyLock   (OSGLock    *lockP);

    OSGThread  *findThread (const char *szName);
    OSGBarrier *findBarrier(const char *szName);
    OSGLock    *findLock   (const char *szName);    

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

    bool init(void);

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

    OSGCreateThreadF  _createThreadF;
    OSGCreateBarrierF _createBarrierF;
    OSGCreateLockF    _createLockF;

    OSGThreadStore    _threadStoreV;
    OSGThreadMap      _threadMapM;

    OSGLockStore      _lockStoreV;
    OSGLockMap        _lockMapM;

    OSGBarrierStore   _barrierStoreV;
    OSGBarrierMap     _barrierMapM;

#if defined(OSG_USE_SPROC)
    usptr_t *_arenaP;
#endif

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGThreadManager(void);

    OSGThreadManager(const OSGThreadManager &source);
    void operator =(const OSGThreadManager &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

typedef OSGThreadManager *OSGThreadManagerP;

OSG_END_NAMESPACE

#endif /* _OSGTHREADMANAGER_H_ */
