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

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGString.h>
#include <OSGFieldContainerPtrForward.h>
#include <map>
#include <vector>


OSG_BEGIN_NAMESPACE

class Lock;
class FieldContainerType;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \brief FieldContainerMapper
 */

struct OSG_SYSTEMLIB_DLLMAPPING FieldContainerMapper
{
    virtual UInt32 map(UInt32 uiId) = 0;
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \brief FieldContainerFactory
 */

class OSG_SYSTEMLIB_DLLMAPPING FieldContainerFactory
{
    /*==========================  PRIVATE  ================================*/
  private:

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


    friend class FieldContainerType;
    friend class FieldContainer;
    friend class FieldContainerPtrBase;


	/*!\brief prohibit default function (move to 'public' if needed) */

    FieldContainerFactory(const FieldContainerFactory &source);

	/*!\brief prohibit default function (move to 'public' if needed) */

    void operator =(const FieldContainerFactory &source);

    /*=========================  PROTECTED  ===============================*/
  protected:

    static FieldContainerFactory *_the;

    /*---------------------------------------------------------------------*/
    /*! \name             Intialization / Termination                      */
    /*! \{                                                                 */

    static Bool   initializeFactory (int &argc, char **argv);
    static Bool   terminateFactory  (void                  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    Bool                    _bInitialized;

    TypeIdMap              *_pTypeIdMap;
    TypeNameMap            *_pTypeNameMap;
    GroupMap               *_pGroupMap;
    UninitializedTypeStore *_pUnitTypesStore;
    FieldContainerStore    *_pFieldContainerStore;

    Lock                   *_pStoreLock;
    Lock                   *_pMapLock;

    FieldContainerMapper   *_pMapper;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    FieldContainerFactory(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~FieldContainerFactory(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name         Instance Initialization / Termination                */
    /*! \{                                                                 */

    Bool   initialize            (int &argc, char **argv);
    Bool   terminate             (void                  );

    void   initTypeMap           (void                  );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Register                                  */
    /*! \{                                                                 */

    void   unregisterFieldContainer(const FieldContainerPtr  &pFieldContainer);
    UInt32   registerFieldContainer(const FieldContainerPtr  &pFieldContainer);

    UInt32 registerType            (      FieldContainerType *pType          );
    UInt16 registerGroup           (const Char8              *szName         );
    void   unregisterType          (      FieldContainerType *pType          );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Write FCD From Type                          */
    /*! \{                                                                 */

	void writeSingleTypeFCD(ostream &out, const FieldContainerType *type);

    /*! \}                                                                 */
    /*==========================  PUBLIC  =================================*/
  public :

    static FieldContainerFactory *the(void);

    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */
        
    FieldContainerType *findType    (      UInt32  uiTypeId) const;
    FieldContainerType *findType    (const Char8  *szName  ) const;
    UInt32              getNumTypes (void                  ) const;

    FieldContainerType *findUninitializedType (const Char8  *szName) const;

    Bool                initializePendingTypes(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Groups                                   */
    /*! \{                                                                 */

          UInt16  findGroupId  (const Char8  *szName   ) const;
    const Char8  *findGroupName(      UInt16  uiGroupId) const;
        
          UInt16  getNumGroups (void                   ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Mapper                                  */
    /*! \{                                                                 */

    void setMapper(FieldContainerMapper *pMapper);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Get FieldContainer                          */
    /*! \{                                                                 */

    FieldContainerPtr getContainer      (UInt32 uiFieldContainerId) const;
    FieldContainerPtr getMappedContainer(UInt32 uiFieldContainerId) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Create Base FieldContainer                      */
    /*! \{                                                                 */

    FieldContainerPtr createFieldContainer(const Char8 *name) const;
    NodePtr           createNode          (const Char8 *name) const;
    NodeCorePtr       createNodeCore      (const Char8 *name) const;
    AttachmentPtr     createAttachment    (const Char8 *name) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Write FCD From Name                            */
    /*! \{                                                                 */

	void writeFCD( char * name = NULL, ostream * out = NULL );
	
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Get Containerstore                             */
    /*! \{                                                                 */

    const FieldContainerStore *getFieldContainerStore(void) const;

    /*! \}                                                                 */
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

typedef FieldContainerFactory *FieldContainerFactoryP;

OSG_END_NAMESPACE

#define OSGFIELDCONTAINERFACTORY_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGFIELDCONTAINERFACTORY_H_ */
