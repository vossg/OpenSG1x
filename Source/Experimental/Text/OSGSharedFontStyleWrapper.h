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

#ifndef _OSGSHAREDFONTSTYLEWRAPPER_H_
#define _OSGSHAREDFONTSTYLEWRAPPER_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <OSGSharedFontStyleWrapperBase.h>

OSG_BEGIN_NAMESPACE

/*! rief SharedFontStyleWrapper class. See ef 
           PageSYSTEMSharedFontStyleWrapper for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING SharedFontStyleWrapper : public SharedFontStyleWrapperBase
{
  private:

    typedef SharedFontStyleWrapperBase Inherited;

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
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in SharedFontStyleWrapperBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SharedFontStyleWrapper(void);
    SharedFontStyleWrapper(const SharedFontStyleWrapper &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SharedFontStyleWrapper(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class SharedFontStyleWrapperBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const SharedFontStyleWrapper &source);
};

typedef SharedFontStyleWrapper *SharedFontStyleWrapperP;

OSG_END_NAMESPACE

#include <OSGSharedFontStyleWrapperBase.inl>
#include <OSGSharedFontStyleWrapper.inl>

#define OSGSHAREDFONTSTYLEWRAPPER_HEADER_CVSID "@(#)$Id: OSGSharedFontStyleWrapper.h,v 1.1 2003/02/24 16:05:14 trembilski Exp $"

#endif /* _OSGSHAREDFONTSTYLEWRAPPER_H_ */
