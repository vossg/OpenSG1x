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

#ifndef _OSGMPBASE_H_
#define _OSGMPBASE_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBase.h>
#include <OSGBaseTypes.h>
#include <OSGString.h>
#include <OSGTypeBase.h>
#include <OSGMemoryObject.h>

OSG_BEGIN_NAMESPACE

class MPBase;
class BaseThread;
class Barrier;
class Lock;
class LockPool;

typedef BaseThread *(*CreateThreadF  )(const Char8  *szName,
                                             UInt32  uiId);
typedef Barrier    *(*CreateBarrierF )(const Char8  *szName,
                                             UInt32  uiId);
typedef Lock       *(*CreateLockF    )(const Char8  *szName,
                                             UInt32  uiId);
typedef LockPool   *(*CreateLockPoolF)(const Char8  *szName,
	                                         UInt32  uiId);
typedef void        (*InitThreadingF) (void);


/*! \ingroup BaseThreading
 *  \brief MPType
 */

class OSG_BASE_DLLMAPPING MPType : public TypeBase
{
	/*==========================  PRIVATE  ================================*/
  private:

    typedef TypeBase Inherited;

	/*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    MPType(const MPType &source);
	
	/*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Assignment                                 */
    /*! \{                                                                 */

    void operator =(const MPType &source);
    
	/*! \}                                                                 */
	/*==========================  PUBLIC  =================================*/
  public :

	/*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    MPType(const Char8 *szName, 
           const Char8 *szParentName,
                 Bool   bRegister = false);
				 
	/*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */
			 
    virtual ~MPType(void); 
 	
	/*! \}                                                                 */
};


/*! \ingroup FieldContainerLib
 *  \brief TypeBase
 */

class OSG_BASE_DLLMAPPING MPThreadType : public MPType
{
	/*==========================  PRIVATE  ================================*/
  private:

    typedef MPType Inherited;

	/*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    MPThreadType(const MPThreadType &source);
	
	/*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Assignment                                 */
    /*! \{                                                                 */

    void operator =(const MPThreadType &source);

	/*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

	/*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */
 
    static UInt32 _uiThreadCount;
	CreateThreadF _fCreateThread;

	/*! \}                                                                 */
	/*==========================  PUBLIC  =================================*/
  public :

	/*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    MPThreadType(const Char8         *szName, 
                 const Char8         *szParentName,
                       CreateThreadF  fCreateThread,
                       InitThreadingF fInitThreading);
					   
	/*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~MPThreadType(void); 

	/*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    BaseThread *create(const Char8 *szName);
 	
	/*! \}                                                                 */
};

/*! \ingroup FieldContainerLib
 *  \brief TypeBase
 */

class OSG_BASE_DLLMAPPING MPBarrierType : public MPType
{
	/*==========================  PRIVATE  ================================*/
  private:

    typedef MPType Inherited;

	/*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    MPBarrierType(const MPBarrierType &source);
	
	/*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Assignment                                 */
    /*! \{                                                                 */

    void operator =(const MPBarrierType &source);

	/*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

	/*---------------------------------------------------------------------*/
    /*! \name                       Class Specific                         */
    /*! \{                                                                 */

    static UInt32 			_uiBarrierCount;
    	   CreateBarrierF 	_fCreateBarrier;

	/*! \}                                                                 */   
    /*==========================  PUBLIC  =================================*/
  public :

	/*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    MPBarrierType(const Char8          *szName, 
                  const Char8          *szParentName,
                        CreateBarrierF  fCreateBarrier);
						
	/*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */
					
    virtual ~MPBarrierType(void); 

	/*! \}                                                                 */   
	/*---------------------------------------------------------------------*/
    /*! \name                   Construction                                */
    /*! \{                                                                 */

    Barrier *create(const Char8 *szName);

/*! \}                                                                 */   
};

/*! \ingroup FieldContainerLib
 *  \brief TypeBase
 */

class OSG_BASE_DLLMAPPING MPLockType : public MPType
{
	/*==========================  PRIVATE  ================================*/
  private:

    typedef MPType Inherited;

	/*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    MPLockType(const MPLockType &source);
	
	/*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Assignment                                 */
    /*! \{                                                                 */
	
    void operator =(const MPLockType &source);

	/*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

	/*---------------------------------------------------------------------*/
    /*! \name                  Class Specific                              */
    /*! \{                                                                 */

    static UInt32 		_uiLockCount;
    	   CreateLockF 	_fCreateLock;
	
	/*! \}                                                                 */
	/*==========================  PUBLIC  =================================*/
  public :

	/*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    MPLockType(const Char8       *szName, 
               const Char8       *szParentName,
                     CreateLockF  fCreateLock);
					 
	/*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */
				 
    virtual ~MPLockType(void); 

	/*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    Lock *create(const Char8 *szName);

	/*! \}                                                                 */
};

/*! \ingroup FieldContainerLib
 *  \brief TypeBase
 */

class OSG_BASE_DLLMAPPING MPLockPoolType : public MPType
{
	/*==========================  PRIVATE  ================================*/
  private:

    typedef MPType Inherited;

	/*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    MPLockPoolType(const MPLockPoolType &source);
	
	/*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Assignment                                 */
    /*! \{                                                                 */

    void operator =(const MPLockPoolType &source);

	/*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

	/*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

    static 	UInt32			_uiLockPoolCount;
    		CreateLockPoolF _fCreateLockPool;

	/*! \}                                                                 */
	/*==========================  PUBLIC  =================================*/
  public :

	/*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    MPLockPoolType(const Char8           *szName, 
                   const Char8           *szParentName,
                         CreateLockPoolF  fCreateLockPool);
						 
	/*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~MPLockPoolType(void); 

	/*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Construction                              */
    /*! \{                                                                 */

    LockPool *create(const Char8 *szName);
	
	/*! \}                                                                 */
};

/*! \ingroup 
 *  \brief Brief
 *
 *  detailed
 */

class OSG_BASE_DLLMAPPING MPBase : public MemoryObject
{
	/*==========================  PRIVATE  ================================*/
  private:

    typedef MemoryObject Inherited;

	/*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    MPBase(const MPBase &source);
	
	/*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Assignment                                 */
    /*! \{                                                                 */

    void operator =(const MPBase &source);

	/*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

	/*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{                                                                 */

	static 	MPType 		_type;
    		Char8      *_szName;

	/*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    MPBase(const Char8 *szName);

	/*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~MPBase(void); 

	/*! \}                                                                 */
	/*==========================  PUBLIC  =================================*/
  public :

	/*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const MPType &getStaticType  (void);
    static       UInt32  getStaticTypeId(void);

	/*! \}                                                                 */
	/*---------------------------------------------------------------------*/
    /*! \name                    Get                                       */
    /*! \{                                                                 */

    virtual       MPType &getType  (void);
    virtual const MPType &getType  (void) const;
                  UInt32  getTypeId(void);
            const Char8  *getCName (void) const;

	/*! \}                                                                 */

};

OSG_END_NAMESPACE

#define OSGMPBASE_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGMPBASE_H_ */
