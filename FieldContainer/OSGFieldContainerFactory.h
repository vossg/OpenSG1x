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


#ifndef _OSGFIELDCONTAINERFACTORY_H_
#define _OSGFIELDCONTAINERFACTORY_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGString.h>
#include <OSGFieldContainerPtr.h>

#include <map>
#include <vector>


OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class Lock;
class FieldContainerType;

class NodePtr;

class NodeCore;
typedef FCPtr<FieldContainerPtr, NodeCore  > NodeCorePtr;

class Attachment;
typedef FCPtr<FieldContainerPtr, Attachment> AttachmentPtr;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \brief FieldContainerFactory
 */

class OSG_SYSTEMLIB_DLLMAPPING FieldContainerFactory
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

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef map<UInt32,     FieldContainerType *>  TypeIdMap;
    typedef map<StringLink, FieldContainerType *>  TypeNameMap;
    typedef map<StringLink, UInt16              >  GroupMap;

    typedef vector<FieldContainerType          *>  UninitializedTypeStore;
    typedef vector<FieldContainerPtr            >  FieldContainerStore;

    typedef TypeIdMap::iterator                    TypeIdMapIt;
    typedef TypeNameMap::iterator                  TypeNameMapIt;
    typedef GroupMap::iterator                     GroupMapIt;
    typedef UninitializedTypeStore::iterator       UninitTypeStoreIt;
    typedef FieldContainerStore::iterator          FieldContainerStoreIt;

    typedef TypeIdMap::const_iterator              TypeIdMapConstIt;
    typedef TypeNameMap::const_iterator            TypeNameMapCnstIt;
    typedef GroupMap::const_iterator               GroupMapConstIt;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class FieldContainerType;
    friend class FieldContainer;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

    FieldContainerFactory(const FieldContainerFactory &source);
    void operator =(const FieldContainerFactory &source);

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

    static FieldContainerFactory *_the;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static Bool   initializeFactory (int &argc, char **argv);
    static Bool   terminateFactory  (void);

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    Bool                    _bInitialized;

    TypeIdMap              *_pTypeIdMap;
    TypeNameMap            *_pTypeNameMap;
    GroupMap               *_pGroupMap;
    UninitializedTypeStore *_pUnitTypesStore;
    FieldContainerStore    *_pFieldContainerStore;

    Lock                   *_pStoreLock;
    Lock                   *_pMapLock;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    FieldContainerFactory(void);
    virtual ~FieldContainerFactory(void); 

    Bool   initialize            (int &argc, char **argv);
    Bool   terminate             (void);

    void   initTypeMap           (void);

    UInt32 registerFieldContainer(const FieldContainerPtr &pFieldContainer);

    UInt32 registerType          (      FieldContainerType *pType );
    UInt16 registerGroup         (const Char8              *szName);
    void   unregisterType        (      FieldContainerType *pType );

	void writeSingleTypeFCD( ostream &out, const FieldContainerType *type );

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static FieldContainerFactory *the(void);

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

   /*--------------------------- types -------------------------------------*/
        
    FieldContainerType *findType    (      UInt32  uiTypeId) const;
    FieldContainerType *findType    (const Char8  *szName  ) const;
    UInt32              getNumTypes (void                  ) const;

    FieldContainerType *findUninitializedType (const Char8  *szName) const;

    Bool                initializePendingTypes(void);

   /*--------------------------- groups ------------------------------------*/

          UInt16  findGroupId  (const Char8  *szName   ) const;
    const Char8  *findGroupName(      UInt16  uiGroupId) const;
        
          UInt16  getNumGroups (void)                       const;

   /*------------------------------- get -----------------------------------*/

    FieldContainerPtr getContainer(UInt32 uiFieldContainerId) const;

   /*---------------------------- create -----------------------------------*/

    FieldContainerPtr createFieldContainer(const Char8 *name) const;
    NodePtr           createNode          (const Char8 *name) const;
    NodeCorePtr       createNodeCore      (const Char8 *name) const;
    AttachmentPtr     createAttachment    (const Char8 *name) const;

    /*------------------------- your_category -------------------------------*/

	/* type output */
	/* name given: output only the given type,
	   out given: output all types into the stream, 
	   no name, no out: output all types into separate files
	 */
	void writeFCD( char * name = NULL, ostream * out = NULL );
	
    /*------------------------- your_operators ------------------------------*/

    const FieldContainerStore *getFieldContainerStore(void) const;

    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef FieldContainerFactory *FieldContainerFactoryP;

OSG_END_NAMESPACE

#endif /* _OSGFIELDCONTAINERFACTORY_H_ */
