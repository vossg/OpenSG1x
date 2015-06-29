/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#ifndef _OSGMETADATAATTACHMENT_H_
#define _OSGMETADATAATTACHMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#include "OSGMetaDataAttachmentBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief MetaDataAttachment class. See \ref 
           PageSystemMetaDataAttachment for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING MetaDataAttachment : 
    public MetaDataAttachmentBase
{
  private:

    typedef MetaDataAttachmentBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */

    inline const MFString& getKeys() const;

    void setAttribute(const std::string& key, const std::string& value);

    inline bool hasAttribute(const std::string& key) const;

    bool getAttribute(const std::string& key, std::string& value) const;

    inline const std::string getAttribute(const std::string& key) const;

    inline std::string& operator[](const std::string& key);

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in MetaDataAttachmentBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MetaDataAttachment(void);
    MetaDataAttachment(const MetaDataAttachment &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MetaDataAttachment(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class MetaDataAttachmentBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const MetaDataAttachment &source);
};

typedef MetaDataAttachment *MetaDataAttachmentP;

class AttachmentContainerPtr;

OSG_SYSTEMLIB_DLLMAPPING
MetaDataAttachmentPtr metaData(AttachmentContainerPtr container);

OSG_END_NAMESPACE

#include "OSGMetaDataAttachmentBase.inl"
#include "OSGMetaDataAttachment.inl"

#define OSGMETADATAATTACHMENT_HEADER_CVSID "@(#)$Id: OSGMetaDataAttachment.h,v 1.1 2005/09/25 23:00:54 dirk Exp $"

#endif /* _OSGMETADATAATTACHMENT_H_ */
