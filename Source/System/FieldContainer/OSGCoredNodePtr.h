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

#ifndef _OSGCOREDNODEPTR_H_
#define _OSGCOREDNODEPTR_H_
#ifdef __sgi
#pragma once
#endif

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGCoredNodePtr.h
    \ingroup GrpSystemFieldContainer
 */
#endif

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGNodePtr.h>
#include <OSGNodeCore.h>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpSystemFieldContainer
 */

class /*OSG_SYSTEMLIB_DLLMAPPING*/ CoredNodePtrBase
{
    /*==========================  PUBLIC  =================================*/
  public: 
 
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
  
    inline CoredNodePtrBase(void);
  
    inline CoredNodePtrBase(NodePtr node);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */
 
    virtual ~CoredNodePtrBase();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */
    
    inline NodePtr node(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    /*=========================  PROTECTED  ===============================*/    
  protected:
  
    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */

    virtual NodeCorePtr getCoreV(void) const = 0;
    
    inline void setNode(const NodePtr &node);
    
    inline void setNode(const NullFieldContainerPtr &);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    /*==========================  PRIVATE  ================================*/
  private:
    
    NodePtr _node;
};

/*! \ingroup GrpSystemFieldContainer
 */

template< class Core >
class CoredNodePtr : public CoredNodePtrBase
{
    /*==========================  PUBLIC  =================================*/
  public:
  
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
  
    CoredNodePtr(void);
    
    // make them explicit to prevent unexpected construction/cast paths
    
    explicit CoredNodePtr(const NodePtr& node);
    
    explicit CoredNodePtr(const NodeCorePtr& core);
    
    explicit CoredNodePtr(const typename Core::Ptr& core);
     
    CoredNodePtr(const CoredNodePtr<Core>& ptr);
   
    static CoredNodePtr<Core> create(void);
     
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */
 
    virtual ~CoredNodePtr();
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */
    
    void coreChanged(void);
  
    typename Core::Ptr core(void) const;

    typename Core::Ptr& operator->(void);
    
    /* Note: these only work for a RHS */
    operator NodePtr();

    operator typename Core::Ptr();

    /* Assignment. Create a new CNP if necessary */
    
    CoredNodePtr<Core>& operator =(const NodePtr& node);

    CoredNodePtr<Core>& operator =(const typename Core::Ptr& core);

    CoredNodePtr<Core>& operator =(const CoredNodePtr<Core>& cnp);

    CoredNodePtr<Core>& operator =(const NullFieldContainerPtr &);
   
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    /*=========================  PROTECTED  ===============================*/    
  protected:
  
    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */

    NodeCorePtr getCoreV(void) const;
    
    void setCore(const NodeCorePtr &core);
    
    void setCore(const typename Core::Ptr &core);

    void setCore(const NullFieldContainerPtr&);
    
    void updateNode(void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    /*==========================  PRIVATE  ================================*/
  private:
  
    typename Core::Ptr _core;
};

// begin/endEdit functions. 

template< class Core > inline
void beginEditCP(const CoredNodePtr<Core> &objectP, 
                       BitVector         whichField = FieldBits    ::AllFields,
                       UInt32            origin     = ChangedOrigin::External);

template< class Core > inline
void endEditCP  (const CoredNodePtr<Core> &objectP, 
                       BitVector         whichField = FieldBits    ::AllFields,
                       UInt32            origin     = ChangedOrigin::External);

// Output operator

template< class Core >
inline std::ostream &operator << (std::ostream &str, 
                                  const CoredNodePtr<Core>& cnp);

OSG_END_NAMESPACE

#include "OSGCoredNodePtr.inl"

#define OSGCOREDNODEPTR_HEADER_CVSID "@(#)$Id: OSGCoredNodePtr.h,v 1.7 2006/02/20 23:31:04 dirk Exp $"

#endif /* _OSGCOREDNODEPTR_H_ */
