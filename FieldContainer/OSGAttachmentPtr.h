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

#ifndef _OSGATTACHMENTPTR_H_
#define _OSGATTACHMENTPTR_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBaseTypes.h>
#include <OSGString.h>
#include <OSGSystemDef.h>
#include <OSGFieldContainerPtr.h>

OSG_BEGIN_NAMESPACE

class Attachment;

/*! \ingroup FieldContainerLib
 *  \brief Pointer to an attachment 
 */

#ifdef __sgi
#pragma set woff 1375,1424
#endif

class OSG_SYSTEMLIB_DLLMAPPING AttachmentPtr : public FieldContainerPtr
{
    /*==========================  PUBLIC  =================================*/
  public:

//    static const AttachmentPtr NullPtr;

    typedef Attachment        ObjectType;

    typedef FieldContainerPtr Inherited;

    /*---------------------------------------------------------------------*/
    /*! \name                      dcast                                   */
    /*! \{                                                                 */

    template <class InTypeT> inline
    static AttachmentPtr dcast(const InTypeT oIn)
    {
        return AttachmentPtr(
            (dynamic_cast<const Attachment *>(oIn.getCPtr())),
             oIn.getContainerSize(),
             oIn.getParentFieldPos());
    }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    AttachmentPtr(void);
    AttachmentPtr(const AttachmentPtr         &source);
    AttachmentPtr(const NullFieldContainerPtr &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
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

#ifdef __sgi
#pragma reset woff 1375,1424
#endif

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

OSG_SYSTEMLIB_DLLMAPPING
ostream &operator <<(      ostream       &os,
                     const AttachmentPtr &fc);
OSG_END_NAMESPACE

#define OSGATTACHMENTPTR_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGATTACHMENTPTR_H_ */
