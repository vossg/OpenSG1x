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


#ifndef _OSGBARRIER_H_
#define _OSGBARRIER_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBase.h>
#include <OSGBaseTypes.h>
#include <OSGMPBase.h>

#if defined (OSG_USE_PTHREADS)
#include <pthread.h>
#endif /* OSG_USE_PTHREADS */

#if defined (OSG_USE_SPROC)
#include <ulocks.h>
#endif /* OSG_USE_SPROC */

OSG_BEGIN_NAMESPACE

template <class MPFieldT>
class MPFieldStore;

/*! \ingroup BaseThreading
 *  \brief BarrierCommonBase
 */

class OSG_BASE_DLLMAPPING BarrierCommonBase : public MPBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*==========================  PRIVATE  ================================*/
  private:

    typedef MPBase Inherited;

    static char cvsid[];

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    BarrierCommonBase(const BarrierCommonBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    void operator =(const BarrierCommonBase &source);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    UInt32  _uiBarrierId;
    Int32   _iRefCount;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    BarrierCommonBase(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~BarrierCommonBase(void);
};

#if defined (OSG_USE_PTHREADS)

/*! \ingroup BaseThreading
 *  \brief PThreadBarrierBase
 */

class PThreadBarrierBase : public BarrierCommonBase
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    void enter(UInt32 uiNumWaitFor);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef BarrierCommonBase Inherited;

    static char cvsid[];

    pthread_mutex_t _pLockOne;
    pthread_mutex_t _pLockTwo;
    pthread_cond_t  _pWakeupCondition;
    UInt32       _uiCount;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    PThreadBarrierBase(const PThreadBarrierBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    void operator =(const PThreadBarrierBase &source);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    PThreadBarrierBase(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PThreadBarrierBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    Bool init    (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destruction                                */
    /*! \{                                                                 */

    void    shutdown(void);

    /*! \}                                                                 */
};

typedef PThreadBarrierBase BarrierBase;

#endif /* OSG_USE_PTHREADS */

#if defined (OSG_USE_SPROC)

/*! \ingroup BaseThreading
 *  \brief SprocBarrierBase
 */

class SprocBarrierBase : public BarrierCommonBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    void enter(UInt32 uiNumWaitFor);
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    typedef BarrierCommonBase Inherited;

    static char cvsid[];

    barrier_t      *_pBarrier;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SprocBarrierBase(const SprocBarrierBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    void operator =(const SprocBarrierBase &source);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SprocBarrierBase(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SprocBarrierBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    Bool init    (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destruction                                */
    /*! \{                                                                 */

    void    shutdown(void);

    /*! \}                                                                 */
};

typedef SprocBarrierBase BarrierBase;

#endif /* OSG_USE_SPROC */


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if defined (OSG_USE_WINTHREADS)

/*! \ingroup BaseThreading
 *  \brief WinThreadBarrierBase
 */

class OSG_BASE_DLLMAPPING WinThreadBarrierBase :
    public BarrierCommonBase
{
    /*==========================  PUBLIC  =================================*/
  public:
    void enter(UInt32 uiNumWaitFor);

    /*==========================  PRIVATE  ================================*/
  private:

    typedef BarrierCommonBase Inherited;

    static char cvsid[];

    Handle       _pMutex1;
    Handle       _pMutex2;
    Handle       _pConditionEvent;
    UInt32       _uiCount;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    WinThreadBarrierBase(const WinThreadBarrierBase &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    void operator =(const WinThreadBarrierBase &source);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    WinThreadBarrierBase(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~WinThreadBarrierBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    Bool init    (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destruction                                */
    /*! \{                                                                 */

    void    shutdown(void);

    /*! \}                                                                 */
};

typedef WinThreadBarrierBase BarrierBase;

#endif /* OSG_USE_WINTHREADS */

/*! \ingroup BaseThreading
 *  \brief Barrier
 */

class OSG_BASE_DLLMAPPING Barrier : public BarrierBase
{
    /*==========================  PUBLIC  =================================*/
  public:
    typedef MPBarrierType Type;

    /*==========================  PRIVATE  ================================*/
  private:

    typedef BarrierBase Inherited;

    friend class MPFieldStore<Barrier>;

    static char cvsid[];

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Barrier(const Barrier &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Operators                                 */
    /*! \{                                                                 */

    void operator =(const Barrier &source);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    static MPBarrierType _type;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Barrier(const Char8 *szName, UInt32 uiId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Barrier(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    static Barrier *create (const Char8  *szName,
                                     UInt32  uiId);

    /*! \}                                                                 */
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */
    
    static Barrier *get (const Char8 *szName);
    static Barrier *find(const Char8 *szName);

    /*! \}                                                                 */
};

typedef Barrier *BarrierP;

OSG_END_NAMESPACE

#endif /* _OSGBARRIER_H_ */
