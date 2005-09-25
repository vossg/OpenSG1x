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

#ifndef _OSGFCPTRATTRIBUTEMAP_H_
#define _OSGFCPTRATTRIBUTEMAP_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGFCPtrAttributeMapBase.h>

OSG_BEGIN_NAMESPACE

/*! \brief FCPtrAttributeMap class. See \ref 
           PageSystemFCPtrAttributeMap for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING FCPtrAttributeMap : public FCPtrAttributeMapBase
{
  private:

    typedef FCPtrAttributeMapBase Inherited;

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

    void setAttribute(const std::string& key, FieldContainerPtr value);

    inline bool hasAttribute(const std::string& key) const;

    bool getAttribute(const std::string& key, FieldContainerPtr& value) const;

    inline FieldContainerPtr getAttribute(const std::string& key) const;

    inline FieldContainerPtr& operator[](const std::string& key);

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in FCPtrAttributeMapBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FCPtrAttributeMap(void);
    FCPtrAttributeMap(const FCPtrAttributeMap &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FCPtrAttributeMap(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class FCPtrAttributeMapBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const FCPtrAttributeMap &source);
};

typedef FCPtrAttributeMap *FCPtrAttributeMapP;

class AttachmentContainerPtr;

OSG_SYSTEMLIB_DLLMAPPING
FCPtrAttributeMapPtr fcptrAttributeMap(AttachmentContainerPtr container);

OSG_END_NAMESPACE

#include <OSGFCPtrAttributeMapBase.inl>
#include <OSGFCPtrAttributeMap.inl>

#define OSGFCPTRATTRIBUTEMAP_HEADER_CVSID "@(#)$Id: OSGFCPtrAttributeMap.h,v 1.1 2005/09/25 23:00:54 dirk Exp $"

#endif /* _OSGFCPTRATTRIBUTEMAP_H_ */
