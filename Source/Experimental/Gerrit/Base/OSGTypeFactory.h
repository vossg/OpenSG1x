/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

#ifndef _OSGTYPEFACTORY_HPP_
#define _OSGTYPEFACTORY_HPP_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBase.h>
#include <OSGBaseTypes.h>
#include <OSGIDString.h>
#include <OSGFactoryBase.h>

#include <map>
#include <vector>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class TypeBase;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! TypeFactory
//! \ingroup BaseTypeLib

class OSG_BASE_DLLMAPPING TypeFactory : public FactoryBase
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef FactoryBase Inherited;

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef map   <IDStringLink, UInt32>  TypeNameMap;

    typedef TypeNameMap::iterator         TypeNameMapIt;
    typedef TypeNameMap::const_iterator   TypeNameMapConstIt;

    typedef vector<TypeBase           *>  TypeStore;

    typedef TypeStore::iterator           TypeStoreIt;
    typedef TypeStore::const_iterator     TypeStoreConstIt;

    typedef vector<TypeNameMap        *>  TypeMapsStore;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class FactoryController;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    static TypeFactory *_the;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    //! \brief prohibit default function (move to 'public' if needed) 
    TypeFactory(const TypeFactory &source);
    //! \brief prohibit default function (move to 'public' if needed) 
    void operator =(const TypeFactory &source);

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static void writeTypeDot(FILE     *pOut,
                             TypeBase *pTypeBase);

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    TypeMapsStore _vTypeNameMaps;
    TypeStore     _vTypeStore;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    TypeFactory(const Char8 *szName);

    virtual ~TypeFactory(void); 

    virtual bool initialize      (void);
    virtual bool terminate       (void);

    virtual bool onLoadInitialize(void);

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static TypeFactory *the(void);

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    UInt32    registerType(      TypeBase *pType      );

    UInt32    findTypeId  (const Char8    *szName,
                           const UInt32    uiNameSpace);

    TypeBase *findType    (      UInt32    uiTypeId   );
    TypeBase *findType    (const Char8    *szName  ,
                           const UInt32    uiNameSpace);

    UInt32    getNumTypes (      void                 );

    void writeDot(FILE *pOut); 
};

OSG_END_NAMESPACE

#define OSGTYPEFACTORY_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGTYPEFACTORY_HPP_ */
