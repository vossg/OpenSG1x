/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                *
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

#ifndef _OSGSIMPLEATTACHMENTS_H_
#define _OSGSIMPLEATTACHMENTS_H_
#ifdef __sgi
#pragma once
#endif

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGSimpleAttachments.h
    \ingroup GrpSystemFieldContainer
 */
#endif

#include <OSGBaseTypes.h>
#include <OSGAttachment.h>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpSystemFieldContainer
    \hideinhierarchy
 */

struct NameAttachmentDesc
{
    static  FieldDescription *_desc[];

    typedef SFString           FieldTypeT;

    static const Char8         *getTypeName  (void) 
    {
        return "Name";          
    }

    static const Char8         *getFieldName (void) 
    {
        return "name";          
    }

    static const Char8         *getGroupName (void) 
    { 
        return "name";          
    }

    static const Char8         *getParentTypeName(void) 
    {
        return "Attachment";    
    }

    static InitContainerF     getInitMethod(void) { return NULL;  }

    static FieldDescription **getDesc      (void) { return _desc; }
};

/*! \ingroup GrpSystemFieldContainer
 */

typedef SimpleAttachment<NameAttachmentDesc  > Name;

/*! \ingroup GrpSystemFieldContainer
 */

typedef FCPtr           <AttachmentPtr,  Name> NamePtr;


class AttachmentContainerPtr;

/*! \ingroup GrpSystemFieldContainerFuncs
 */

OSG_SYSTEMLIB_DLLMAPPING
const Char8 *getName(      AttachmentContainerPtr  container);

/*! \ingroup GrpSystemFieldContainerFuncs
 */

OSG_SYSTEMLIB_DLLMAPPING
      void   setName(      AttachmentContainerPtr  container, 
                     const std::string            &name     );

/*! \ingroup GrpSystemFieldContainerFuncs
 */

OSG_SYSTEMLIB_DLLMAPPING
      void   setName(      AttachmentContainerPtr  container, 
                     const Char8                  *name     );
 

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#ifndef OSG_COMPILESIMPLEATTACHMENTSINST
OSG_FC_DLLEXPORT_DECL(SimpleAttachment, 
                      NameAttachmentDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif

#endif /* DOXYGEN_SHOULD_SKIP_THIS */


/*! \ingroup GrpSystemFieldContainer
    \hideinhierarchy
 */

struct VoidPAttachmentDesc
{
    static  FieldDescription *_desc[];

    typedef SFVoidP            FieldTypeT;

    static const Char8         *getTypeName  (void) 
    {
        return "VoidPAttachment";          
    }

    static const Char8         *getFieldName (void) 
    {
        return "data";          
    }

    static const Char8         *getGroupName (void) 
    { 
        return "voidp";          
    }

    static const Char8         *getParentTypeName(void) 
    {
        return "Attachment";    
    }

    static InitContainerF     getInitMethod(void) { return NULL;  }

    static FieldDescription **getDesc      (void) { return _desc; }
};

/*! \ingroup GrpSystemFieldContainer
 */

typedef SimpleAttachment<VoidPAttachmentDesc            > VoidPAttachment;

/*! \ingroup GrpSystemFieldContainer
 */

typedef FCPtr           <AttachmentPtr,  VoidPAttachment> VoidPAttachmentPtr;

/*! \ingroup GrpSystemFieldContainerFuncs
 */

OSG_SYSTEMLIB_DLLMAPPING
void *getVoidP(AttachmentContainerPtr  container);

/*! \ingroup GrpSystemFieldContainerFuncs
 */

OSG_SYSTEMLIB_DLLMAPPING
void  setVoidP(AttachmentContainerPtr  container, 
               void                   *pData,
               bool                   internal = false );

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#ifndef OSG_COMPILESIMPLEATTACHMENTSINST
OSG_FC_DLLEXPORT_DECL(SimpleAttachment, 
                      VoidPAttachmentDesc,
                      OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

OSG_END_NAMESPACE

#define OSGSIMPLEATTACHMENTS_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGSIMPLEATTACHMENTS_H_ */
