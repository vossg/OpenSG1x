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

#ifndef _OSGTYPEBASE_H_
#define _OSGTYPEBASE_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBase.h>
#include <OSGBaseTypes.h>
#include <OSGIDString.h>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseBaseTypeSystem
 */

class OSG_BASE_DLLMAPPING TypeBase
{
    /*==========================  PUBLIC  =================================*/

  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructor                                */
    /*! \{                                                                 */

    TypeBase(const Char8  *szName, 
             const Char8  *szParentName,
             const UInt32  uiNameSpace = 0);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~TypeBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Id                                     */
    /*! \{                                                                 */

          UInt32    getId         (void) const;

    const IDString &getName       (void) const;
    const Char8    *getCName      (void) const;

    const IDString &getParentName (void) const;
    const Char8    *getCParentName(void) const;

          UInt32    getNameSpace  (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Operators                                */
    /*! \{                                                                 */

    virtual bool isDerivedFrom(const TypeBase &other) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    bool operator ==(const TypeBase &other) const;
    bool operator !=(const TypeBase &other) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Members                                 */
    /*! \{                                                                 */

    UInt32    _uiTypeId;
    UInt32    _uiTypeRootId;

    TypeBase *_pParent;

    IDString  _szName;
    IDString  _szParentName;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TypeBase(const TypeBase &source);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const TypeBase &source);
};

OSG_END_NAMESPACE

#define OSGTYPEBASE_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGTYPEBASE_H_ */




