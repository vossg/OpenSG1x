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

#ifndef _OSGTYPEFACTORY_H_
#define _OSGTYPEFACTORY_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBase.h>
#include <OSGBaseTypes.h>
#include <OSGIDStringLink.h>

#include <map>

OSG_BEGIN_NAMESPACE

class TypeBase;

/*! \ingroup GrpBaseBaseTypeSystem
 */

class OSG_BASE_DLLMAPPING TypeFactory
{
    /*==========================  PUBLIC  =================================*/

  public :

    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    static TypeFactory *the(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Type Info                                   */
    /*! \{                                                                 */

    UInt32    registerType  (      TypeBase *pType          );

    UInt32    findTypeId    (const Char8    *szName,
                             const UInt32    uiNameSpace = 0);

    TypeBase *findType      (      UInt32    uiTypeId       );
    TypeBase *findType      (const Char8    *szName  ,
                             const UInt32    uiNameSpace = 0);


    UInt32    getNumTypes   (      void                     );

    void      writeTypeGraph(const Char8    *szFilename     );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    typedef std::map   <IDStringLink, UInt32>  TypeNameMap;

    typedef TypeNameMap::iterator              TypeNameMapIt;
    typedef TypeNameMap::const_iterator        TypeNameMapConstIt;


    typedef std::vector<TypeBase           *>  TypeStore;

    typedef TypeStore::iterator                TypeStoreIt;
    typedef TypeStore::const_iterator          TypeStoreConstIt;


    typedef std::vector<TypeNameMap        *>  TypeMapsStore;

    /*! \{                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Static Variables                             */
    /*! \{                                                                 */

    static TypeFactory   *_the;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Members                                 */
    /*! \{                                                                 */

           TypeMapsStore  _vTypeNameMaps;
           TypeStore      _vTypeStore;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TypeFactory(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~TypeFactory(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Helper                                   */
    /*! \{                                                                 */

    static void writeTypeDot(FILE     *pOut,
                             TypeBase *pTypeBase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    TypeFactory(const TypeFactory &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const TypeFactory &source);
};

OSG_END_NAMESPACE

#define OSGTYPEFACTORY_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGTYPEFACTORY_H_ */
