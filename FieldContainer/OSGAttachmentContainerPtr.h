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

#ifndef _OSGATTACHMENTCONTAINERPTR_H_
#define _OSGATTACHMENTCONTAINERPTR_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBaseTypes.h>
#include <OSGSystemDef.h>
#include <OSGFieldContainerPtr.h>

OSG_BEGIN_NAMESPACE

class AttachmentContainer;

//! Pointer to an attachment container
//! \ingroup FieldContainerLib

#ifdef __sgi
#pragma set woff 1375,1424
#endif

class OSG_SYSTEMLIB_DLLMAPPING AttachmentContainerPtr : 
    public FieldContainerPtr
{
    /*==========================  PUBLIC  =================================*/
  public:

    typedef AttachmentContainer    StoredObjectType;
    typedef AttachmentContainerPtr ObjectType;

    typedef FieldContainerPtr   Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      dcast                                   */
    /*! \{                                                                 */

    template <class InTypeT> inline
    static AttachmentContainerPtr dcast(const InTypeT oIn)
    {
        return AttachmentContainerPtr(
            (dynamic_cast<const AttachmentContainer *>(oIn.getCPtr())),
             oIn.getContainerSize(),
             oIn.getParentFieldPos());
    }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    AttachmentContainerPtr(void);
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

#ifdef __sgi
#pragma reset woff 1375,1424
#endif

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

OSG_SYSTEMLIB_DLLMAPPING
ostream &operator <<(      ostream                &os,
                     const AttachmentContainerPtr &fc);
OSG_END_NAMESPACE

#define OSGATTACHMENTCONTAINERPTR_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGATTACHMENTCONTAINERPTR_H_ */
