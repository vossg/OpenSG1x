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

/*! \ingroup TypeLib
 *  \brief TypeFactory
 */

class OSG_BASE_DLLMAPPING TypeFactory
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*==========================  PRIVATE  ================================*/
  private:

    /*---------------------------------------------------------------------*/
    /*! \name                      Types                                   */
    /*! \{                                                                 */

    typedef std::map<IDStringLink, UInt32>     TypeNameMap;

    typedef TypeNameMap::iterator            TypeNameMapIt;
    typedef TypeNameMap::const_iterator      TypeNameMapCnstIt;

    /*! \}                                                                 */

    static char        cvsid[];

    static TypeFactory *_the;


    // prohibit default functions (move to 'public' if you need one)

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    TypeFactory(void);
    TypeFactory(const TypeFactory &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~TypeFactory(void);

    /*! \}                                                                 */

    void operator =(const TypeFactory &source);

    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Friend Classes                              */
    /*! \{                                                                 */

    friend class TypeBase;
    friend class FieldFactory;
    friend class FieldContainerFactory;

    /*! \}                                                                 */

    TypeNameMap _mTypeNameMap;

    /*==========================  PUBLIC  =================================*/
  public :


    static TypeFactory *the(void);

    /*---------------------------------------------------------------------*/
    /*! \name                  Your Category                               */
    /*! \{                                                                 */

    UInt32 registerType  (      TypeBase *pType);
    UInt32 findTypeStatic(const Char8    *szName);

    /*! \}                                                                 */
};

typedef TypeFactory *TypeFactoryP;

OSG_END_NAMESPACE

#endif /* _OSGTYPEFACTORY_H_ */
