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

#ifndef _OSGFIELDFACTORY_H_
#define _OSGFIELDFACTORY_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBase.h>
#include <OSGBaseTypes.h>
#include <OSGFieldDataType.h>

#include <map>

OSG_BEGIN_NAMESPACE

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGFieldFactory.h
    \ingroup GrpBaseField
 */
#endif

class Field;
class FieldType;

/*! \ingroup GrpBaseField
 */

class OSG_BASE_DLLMAPPING FieldFactory 
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~FieldFactory (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Create                                   */
    /*! \{                                                                 */

    Field *createField(      UInt32  typeId);
    Field *createField(const Char8  *szName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    static UInt32     getNFieldTypes  (void                );
    
    static FieldType *getFieldType    (      UInt32  typeId);
    static FieldType *getFieldType    (const Char8  *szName);

    const  Char8     *getFieldTypeName(UInt32 typeId       );
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      The                                     */
    /*! \{                                                                 */

    static FieldFactory &the(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    FieldFactory (void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldType;
    friend class Field;

    /*---------------------------------------------------------------------*/
    /*                             Member                                  */

    static      FieldFactory              _the;
    
    static std::map<UInt32, FieldType *> *_fieldTypeM;


    static void addType(FieldType *pType);

    /*---------------------------------------------------------------------*/

    /*!\brief prohibit default function (move to 'public' if needed) */
    FieldFactory(const FieldFactory &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const FieldFactory &source);
};

OSG_END_NAMESPACE

#define OSGFIELDFACTORY_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGFIELDFACTORY_H_ */


