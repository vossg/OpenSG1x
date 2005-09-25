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

#ifndef _OSGSTRINGATTRIBUTEMAP_H_
#define _OSGSTRINGATTRIBUTEMAP_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGStringAttributeMapBase.h>

OSG_BEGIN_NAMESPACE

/*! \brief StringAttributeMap class. See \ref 
           PageSystemStringAttributeMap for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING StringAttributeMap : public StringAttributeMapBase
{
  private:

    typedef StringAttributeMapBase Inherited;

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

    // Variables should all be in StringAttributeMapBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    StringAttributeMap(void);
    StringAttributeMap(const StringAttributeMap &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~StringAttributeMap(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class StringAttributeMapBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const StringAttributeMap &source);
};

typedef StringAttributeMap *StringAttributeMapP;

class AttachmentContainerPtr;

OSG_SYSTEMLIB_DLLMAPPING
StringAttributeMapPtr stringAttributeMap(AttachmentContainerPtr container);

OSG_END_NAMESPACE

#include <OSGStringAttributeMapBase.inl>
#include <OSGStringAttributeMap.inl>

#define OSGSTRINGATTRIBUTEMAP_HEADER_CVSID "@(#)$Id: OSGStringAttributeMap.h,v 1.1 2005/09/25 23:00:54 dirk Exp $"

#endif /* _OSGSTRINGATTRIBUTEMAP_H_ */
