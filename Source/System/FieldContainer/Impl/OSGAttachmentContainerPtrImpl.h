/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifndef _OSGATTACHMENTCONTAINERPTRIMPL_H_
#define _OSGATTACHMENTCONTAINERPTRIMPL_H_
#ifdef __sgi
#pragma once
#endif

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGAttachmentContainerPtrImpl.h
    \ingroup GrpSystemFieldContainer
 */
#endif

#include <OSGBaseTypes.h>
#include <OSGSystemDef.h>
#include <OSGFieldContainerPtr.h>
#include <OSGRefPtr.h>

OSG_BEGIN_NAMESPACE

class AttachmentContainer;

#ifdef __sgi
#pragma set woff 1375,1424
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 444 )
#endif

/*! \ingroup GrpSystemFieldContainer
 */

class OSG_SYSTEMLIB_DLLMAPPING AttachmentContainerPtr : 
    public FieldContainerPtr
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef AttachmentContainer    StoredObjectType;
    typedef AttachmentContainerPtr ObjectType;

    typedef FieldContainerPtr      Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      dcast                                   */
    /*! \{                                                                 */

    template <class InTypeT> 
    static AttachmentContainerPtr dcast(const InTypeT oIn);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    AttachmentContainerPtr(      void                          );
    AttachmentContainerPtr(const AttachmentContainerPtr &source);
    AttachmentContainerPtr(const NullFieldContainerPtr  &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~AttachmentContainerPtr(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Container Access                             */
    /*! \{                                                                 */

    AttachmentContainer *operator->(void);
    AttachmentContainer *operator->(void) const;

    AttachmentContainer &operator *(void);
    AttachmentContainer &operator *(void) const;

    AttachmentContainer *getCPtr   (void);
    AttachmentContainer *getCPtr   (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Assignment                                */
    /*! \{                                                                 */

    void operator =(const AttachmentContainerPtr  &source);
    void operator =(const NullFieldContainerPtr   &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Container Constructors                           */
    /*! \{                                                                 */
    /*! \brief Container Constructor, used to work around MS Bugs,  
        use them only if you really now what you are doing ;-)             */

    explicit AttachmentContainerPtr(const AttachmentContainer &source);
    explicit AttachmentContainerPtr(const AttachmentContainer *source);
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name             Internal Constructors                            */
    /*! \{                                                                 */

    AttachmentContainerPtr(const AttachmentContainer *source,
                           const UInt16               uiSize,
                           const UInt16               uiParentPos);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
};

typedef RefPtr<AttachmentContainerPtr> AttachmentContainerRefPtr;

#ifdef OSG_LINUX_ICC
#pragma warning( default : 444 )
#endif

#ifdef __sgi
#pragma reset woff 1375,1424
#endif

/*! \ingroup GrpSystemFieldContainerFuncs
 */

OSG_SYSTEMLIB_DLLMAPPING
std::ostream &operator <<(      std::ostream           &os,
                          const AttachmentContainerPtr &fc);
OSG_END_NAMESPACE

#define OSGATTACHMENTCONTAINERPTR_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGATTACHMENTCONTAINERPTR_IMPL_ */

