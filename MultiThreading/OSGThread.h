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


#ifndef _OSGTHREAD_H_
#define _OSGTHREAD_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGBaseThread.h>

#include <utility>

#include <OSGBaseTypes.h>

#if ! defined (OSG_USE_PTHREADS)   && \
    ! defined (OSG_USE_SPROC)      && \
    ! defined (OSG_USE_WINTHREADS)
#error "No threading model defined,  check your system/compiler combination"
#endif

OSG_BEGIN_NAMESPACE

class Thread;
class ChangeList;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! ThreadCommonBase
//! \ingroup BaseThreading

class OSG_SYSTEMLIB_DLLMAPPING ThreadCommonBase : public BaseThread
{
    /*==========================  PUBLIC  =================================*/
  public :

    static const UInt32 InvalidAspect;

    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    ChangeList *getChangeList(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    typedef BaseThread Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    UInt32      _uiAspectId;
    ChangeList *_pChangeList;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ThreadCommonBase(void);
    ThreadCommonBase(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ThreadCommonBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void setAspect    (UInt32      uiAspectId);
    void setChangeList(ChangeList *pChangeList);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class ThreadManager;

    /*!\brief prohibit default function (move to 'public' if needed) */
    ThreadCommonBase(const ThreadCommonBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const ThreadCommonBase &source);
};




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#ifdef OSG_USE_PTHREADS

//! PThreadBase
//! \ingroup BaseThreading

class PThreadBase : public ThreadCommonBase
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    static UInt32       getAspect           (void);
    static ChangeList  *getCurrentChangeList(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Run                                     */
    /*! \{                                                                 */

    Bool run      (ThreadFuncF  fThreadFunc, 
                   UInt32       uiAspectId,
                   void        *pThreadArg);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    typedef ThreadCommonBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

#ifdef OSG_ASPECT_USE_PTHREADKEY
    static pthread_key_t  _aspectKey;
    static pthread_key_t  _changeListKey;
#endif

#if defined(OSG_ASPECT_USE_PTHREADSELF) || defined(OSG_ASPECT_USE_CUSTOMSELF)
    static vector<UInt16       > _vAspects;
    static vector<ChangeList  *> _vChangelists;
#endif

#ifdef OSG_ASPECT_USE_PTHREADKEY
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Free                                     */
    /*! \{                                                                 */

    static void  freeAspect    (void *pAspect);
    static void  freeChangeList(void *pChangeList);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    PThreadBase(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~PThreadBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Setup                                   */
    /*! \{                                                                 */

    virtual void init           (void);
    
            void setupAspect    (void);
            void setupChangeList(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class ThreadManager;

    /*!\brief prohibit default function (move to 'public' if needed) */
    PThreadBase(const PThreadBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const PThreadBase &source);
};

typedef PThreadBase ThreadBase;

#endif /* OSG_USE_PTHREADS */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#ifdef OSG_USE_SPROC

//! SprocBase
//! \ingroup BaseThreading

class SprocBase : public ThreadCommonBase
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    static UInt32      getAspect           (void);
    static ChangeList *getCurrentChangeList(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Run                                     */
    /*! \{                                                                 */

    Bool run      (ThreadFuncF  fThreadFunc, 
                   UInt32       uiAspectId,
                   void        *pThreadArg);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    typedef ThreadCommonBase Inherited;

    struct OSGProcessData : public ProcessData
    {
        UInt32      _uiAspectId;
        ChangeList *_pChangeList;
    };

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SprocBase(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~SprocBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    void setAspectInternal(UInt32 uiAspect);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Setup                                   */
    /*! \{                                                                 */

    virtual void init                   (void);

            void setupChangeListInternal(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  private:

    friend class ThreadManager;

    /*!\brief prohibit default function (move to 'public' if needed) */
    SprocBase(const SprocBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const SprocBase &source);
};

typedef SprocBase ThreadBase;

#endif /* OSG_USE_SPROC */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#ifdef OSG_USE_WINTHREADS

//! WinThreadBase
//! \ingroup BaseThreading

class OSG_SYSTEMLIB_DLLMAPPING WinThreadBase : public ThreadCommonBase
{
    /*==========================  PUBLIC  =================================*/
  public :

    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    static UInt32      getAspect           (void);
    static ChangeList *getCurrentChangeList(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Run                                     */
    /*! \{                                                                 */

    Bool run      (ThreadFuncF  fThreadFunc, 
                   UInt32       uiAspectId,
                   void        *pThreadArg);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    typedef ThreadCommonBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

#if defined(OSG_ASPECT_USE_LOCALSTORAGE)
    static UInt32 _aspectKey;
    static UInt32 _changeListKey;
#endif
#if defined(OSG_ASPECT_USE_DECLSPEC)
    static __declspec (thread) UInt32      _uiAspectLocal;
    static __declspec (thread) ChangeList *_pChangeListLocal;
#endif

#ifdef OSG_ASPECT_USE_LOCALSTORAGE
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Free                                   */
    /*! \{                                                                 */

    static void freeAspect    (void);
    static void freeChangeList(void);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    WinThreadBase(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~WinThreadBase(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Init                                     */
    /*! \{                                                                 */

    virtual void init            (void);

            void setupAspect     (void);
            void setupChangeList (void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class ThreadManager;

    /*!\brief prohibit default function (move to 'public' if needed) */
    WinThreadBase(const WinThreadBase &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const WinThreadBase &source);
};

typedef WinThreadBase ThreadBase;

#endif /* OSG_USE_WINTHREADS */




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! Thread
//! \ingroup BaseThreading

class OSG_SYSTEMLIB_DLLMAPPING Thread : public ThreadBase
{
    /*==========================  PUBLIC  =================================*/
  public :

    typedef      MPThreadType Type;

    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */
    
    static ThreadBase *getCurrent(void);

    static Thread     *get       (const Char8 *szName);
    static Thread     *find      (const Char8 *szName);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    typedef ThreadBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static MPThreadType _type;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static Thread *create       (const Char8 *szName, UInt32 uiId);

    static void    initThreading(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Thread(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~Thread(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class ThreadManager;
    friend class MPFieldStore<BaseThread>;

    /*!\brief prohibit default function (move to 'public' if needed) */
    Thread(const Thread &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const Thread &source);
};



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! ExternalThread
//! \ingroup BaseThreading

class OSG_SYSTEMLIB_DLLMAPPING ExternalThread : public ThreadBase
{
    /*==========================  PUBLIC  =================================*/
  public :

    typedef MPThreadType Type;

    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */
    
    static ThreadBase     *getCurrent(void);

    static ExternalThread *get       (const Char8 *szName);
    static ExternalThread *find      (const Char8 *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    void initialize   (UInt32 uiAspectId);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    typedef ThreadBase Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    static MPThreadType _type;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static ExternalThread *create       (const Char8 *szName, UInt32 uiId);

//    static void            initThreading(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ExternalThread(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ExternalThread(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class ThreadManager;
    friend class MPFieldStore<BaseThread>;

    /*!\brief prohibit default function (move to 'public' if needed) */
    ExternalThread(const ExternalThread &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const ExternalThread &source);
};

OSG_END_NAMESPACE

#define OSGTHREAD_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGTHREAD_H_ */
