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

#ifndef _OSGFIELDCONTAINERFACTORY_H_
#define _OSGFIELDCONTAINERFACTORY_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <map>
#include <vector>
#include <OSGStringLink.h>
#include <OSGFieldContainerBase.h>
#include <OSGFieldContainerPtr.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class FieldContainer;
class FieldContainerType;
class Lock;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \brief FieldContainerFactory
 */

class OSG_FIELDCONTAINER_DLLMAPPING FieldContainerFactory 
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

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const FieldContainerFactory &the(void);

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

   /*--------------------------- types -------------------------------------*/
        
    FieldContainerType *findType    (      UInt32  Id)   const;
    FieldContainerType *findType    (const Char8  *name) const;
    UInt32              getTypeCount(void)                  const;

   /*--------------------------- groups ------------------------------------*/

          UInt16  findGroupId  (const Char8  *name) const;
    const Char8  *findGroupName(      UInt16  Id)   const;
        
          UInt16  getGroupCount(void)                  const;

   /*---------------------------- create -----------------------------------*/

    FieldContainerPtr createFieldContainer(const Char8 *name) const;
    NodePtr           createNode          (const Char8 *name) const;
    NodeCorePtr       createNodeCore      (const Char8 *name) const;
    AttachmentPtr     createAttachment    (const Char8 *name) const;

   /*------------------------------- get -----------------------------------*/

    FieldContainerPtr getContainer(UInt32 uiContainerId) const;

   /*---------------------------- dump -------------------------------------*/

    void dump(void) const;
    
  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef map<UInt32, FieldContainerType *>  TypeIdMap;
    typedef map<String, FieldContainerType *>  TypeNameMap;
    typedef map<String, UInt16>                GroupMap;

    typedef vector<FieldContainerPtr>          FieldContainerStore;

    typedef TypeIdMap::iterator           TypeIdMapIt;
    typedef TypeNameMap::iterator         TypeNameMapIt;
    typedef GroupMap::iterator            GroupMapIt;
    typedef FieldContainerStore::iterator FieldContainerStoreIt;

    typedef TypeIdMap::const_iterator     TypeIdMapConstIt;
    typedef TypeNameMap::const_iterator   TypeNameMapCnstIt;
    typedef GroupMap::const_iterator      GroupMapConstIt;

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static void      initTypeMap(void);

    static Bool   initialize (int argc, char **argv);
    static Bool   terminate  (void);


    static UInt32 registerFieldContainer(
        const FieldContainerPtr &fieldP);

    static const FieldContainerStore *getFieldStore(void);

    static FieldContainerType *findTypeStatic   (const Char8  *name);
    static FieldContainerType *findTypeStatic   (      UInt32 typeId);
    static UInt16              findGroupIdStatic(const Char8  *name);

    static UInt32 registerType (      FieldContainerType *typeP);
    static UInt16 registerGroup(const Char8              *name);

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class FieldContainer;
    friend class FieldContainerType;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

    static FieldContainerFactory  _the;

    static Bool                   _initialized;

    static TypeIdMap             *_typeIdMap;
    static TypeNameMap           *_typeNameMap;
    static GroupMap              *_groupMap;

    static FieldContainerStore   *_fieldcontainerStoreV;

    static Lock                  *_storeLock;
    static Lock                  *_mapLock;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    FieldContainerFactory (void);
    virtual ~FieldContainerFactory (void);

    // prohibit default functions (move to 'public' if you need one)

    FieldContainerFactory (const FieldContainerFactory &obj);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef FieldContainerFactory* FieldContainerFactoryP;

OSG_END_NAMESPACE

#endif /* _OSGFIELDCONTAINERFACTORY_H_ */
