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

#ifndef _OSGATTACHMENTPTRIMPL_H_
#define _OSGATTACHMENTPTRIMPL_H_
#ifdef __sgi
#pragma once
#endif

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGAttachmentPtrImpl.h
    \ingroup GrpSystemFieldContainer
 */
#endif

#include <OSGBaseTypes.h>
#include <OSGSystemDef.h>
#include <OSGFieldContainerPtr.h>
#include <OSGRefPtr.h>

OSG_BEGIN_NAMESPACE

class Attachment;

#ifdef __sgi
#pragma set woff 1375,1424
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 444 )
#endif

/*! \ingroup GrpSystemFieldContainer
 */

class OSG_SYSTEMLIB_DLLMAPPING AttachmentPtr : public FieldContainerPtr
{
    /*==========================  PUBLIC  =================================*/

  public:

    typedef Attachment        StoredObjectType;
    typedef AttachmentPtr     ObjectType;

    typedef FieldContainerPtr Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      dcast                                   */
    /*! \{                                                                 */

    template <class InTypeT>
    static AttachmentPtr dcast(const InTypeT oIn);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    AttachmentPtr(void);
    AttachmentPtr(const AttachmentPtr         &source);
    AttachmentPtr(const NullFieldContainerPtr &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    ~AttachmentPtr(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Container Access                             */
    /*! \{                                                                 */

    Attachment *operator->(void);
    Attachment *operator->(void) const;

    Attachment &operator *(void);
    Attachment &operator *(void) const;

    Attachment *getCPtr   (void);
    Attachment *getCPtr   (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Assignment                                */
    /*! \{                                                                 */

    void operator =(const AttachmentPtr         &source);
    void operator =(const NullFieldContainerPtr &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Container Constructors                           */
    /*! \{                                                                 */
    /*! \brief Container Constructor, used to work around MS Bugs,  
     *  use them only if you really now what you are doing ;-)             */

    explicit AttachmentPtr(const Attachment &source);
    explicit AttachmentPtr(const Attachment *source);
    
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name             Internal Constructors                            */
    /*! \{                                                                 */

    AttachmentPtr(const Attachment *source,
                  const UInt16      uiSize,
                  const UInt16      uiParentPos);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
};

typedef RefPtr<AttachmentPtr> AttachmentRefPtr;

#ifdef OSG_LINUX_ICC
#pragma warning( default : 444 )
#endif

#ifdef __sgi
#pragma reset woff 1375,1424
#endif

/*! \ingroup GrpSystemFieldContainerFuncs
 */

OSG_SYSTEMLIB_DLLMAPPING
std::ostream &operator <<(      std::ostream  &os,
                          const AttachmentPtr &fc);
OSG_END_NAMESPACE

#define OSGATTACHMENTPTR_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGATTACHMENTPTRIMPL_H_ */
