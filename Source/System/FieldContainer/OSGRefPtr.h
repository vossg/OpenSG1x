/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000-2002 by OpenSG Forum                   *
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

#ifndef _OSGREFPTR_H_
#define _OSGREFPTR_H_
#ifdef __sgi
#pragma once
#endif

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGRefPtr.h
    \ingroup GrpSystemFieldContainer
 */
#endif

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGFieldContainerPtr.h>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpSystemFieldContainer
 */

template< class Ref >
class RefPtr
{
    /*==========================  PUBLIC  =================================*/
  public:
    /** The full type of the FC Ptr wrapped. */
    typedef  Ref FCPtrType;
    /** The full type of the object referenced by the wrapped fcptr. */
    typedef  typename Ref::StoredObjectType  StoredObjectType;
    typedef  const Ref RefPtr::*unspecified_bool_type;
    
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
  
    RefPtr(void);
    
    // make it explicit to prevent unexpected construction/cast paths
    
    explicit RefPtr(const Ref& fcp);
     
    RefPtr(const RefPtr<Ref>& ptr);
     
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */
 
    virtual ~RefPtr();
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */
    
    operator Ref(void) const;
    
    typename Ref::StoredObjectType* operator->(void) const;
    typename Ref::StoredObjectType* getCPtr   (void) const;
    
    Ref get(void) const;
    
    RefPtr<Ref>& operator =(const Ref &fcp);    
    RefPtr<Ref>& operator =(const RefPtr<Ref> &rcp);
    RefPtr<Ref>& operator =(const NullFieldContainerPtr& );    
   
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    bool operator <  (const NullFieldContainerPtr &     ) const;   
    bool operator == (const NullFieldContainerPtr &other) const;
    bool operator != (const NullFieldContainerPtr &other) const;

    bool operator <  (const FieldContainerPtr     &other) const;
    bool operator == (const FieldContainerPtr     &other) const;
    bool operator != (const FieldContainerPtr     &other) const;

    bool operator <  (const RefPtr<Ref>           &other) const;
    bool operator == (const RefPtr<Ref>           &other) const;
    bool operator != (const RefPtr<Ref>           &other) const;

    bool operator !  (void                              ) const;

    operator unspecified_bool_type() const;
   
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    /*=========================  PROTECTED  ===============================*/    
  protected:

    /*==========================  PRIVATE  ================================*/
  private:
  
    void setRef(const Ref& ref);
    
    Ref _ref;
};

// Some base types

typedef RefPtr<FieldContainerPtr> FieldContainerRefPtr;

OSG_END_NAMESPACE

#include "OSGRefPtr.inl"

#define OSGREFPTR_HEADER_CVSID "@(#)$Id: OSGRefPtr.h,v 1.7 2006/09/05 01:24:28 allenb Exp $"

#endif /* _OSGREFPTR_H_ */
