/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, vossg@users.sourceforge.net, jbehr@zgdv.de    *
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
#include <OSGFieldContainerPtr.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class OSGFieldContainer;
class OSGFieldContainerType;
class OSGLock;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \brief OSGFieldContainerFactory
 */

class OSGFieldContainerFactory 
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

    static const OSGFieldContainerFactory &the(void);

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

   /*--------------------------- types -------------------------------------*/
        
    OSGFieldContainerType *findType    (      OSGUInt32  Id)   const;
    OSGFieldContainerType *findType    (const OSGChar8  *name) const;
    OSGUInt32              getTypeCount(void)                  const;

   /*--------------------------- groups ------------------------------------*/

          OSGUInt16  findGroupId  (const OSGChar8  *name) const;
    const OSGChar8  *findGroupName(      OSGUInt16  Id)   const;
        
          OSGUInt16  getGroupCount(void)                  const;

   /*---------------------------- create -----------------------------------*/

    OSGFieldContainerPtr createFieldContainer(const OSGChar8 *name) const;
    OSGNodePtr           createNode          (const OSGChar8 *name) const;
    OSGNodeCorePtr       createNodeCore      (const OSGChar8 *name) const;
    OSGAttachmentPtr     createAttachment    (const OSGChar8 *name) const;

   /*------------------------------- get -----------------------------------*/

    OSGFieldContainerPtr getContainer(OSGUInt32 uiContainerId) const;

   /*---------------------------- dump -------------------------------------*/

    void dump(void) const;
    
  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef map<OSGUInt32, OSGFieldContainerType *>  OSGTypeIdMap;
    typedef map<OSGString, OSGFieldContainerType *>  OSGTypeNameMap;
    typedef map<OSGString, OSGUInt16>                OSGGroupMap;

    typedef vector<OSGFieldContainerPtr>             OSGFieldContainerStore;

    typedef OSGTypeIdMap::iterator           OSGTypeIdMapIt;
    typedef OSGTypeNameMap::iterator         OSGTypeNameMapIt;
    typedef OSGGroupMap::iterator            OSGGroupMapIt;
    typedef OSGFieldContainerStore::iterator OSGFieldContainerStoreIt;

    typedef OSGTypeIdMap::const_iterator           OSGTypeIdMapConstIt;
    typedef OSGTypeNameMap::const_iterator         OSGTypeNameMapCnstIt;
    typedef OSGGroupMap::const_iterator            OSGGroupMapConstIt;

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static void      initTypeMap(void);

    static OSGBool   initialize (int argc, char **argv);
    static OSGBool   terminate  (void);


    static OSGUInt32 registerFieldContainer(
        const OSGFieldContainerPtr &fieldP);

    static const OSGFieldContainerStore *getFieldStore(void);

    static OSGFieldContainerType *findTypeStatic   (const OSGChar8  *name);
    static OSGFieldContainerType *findTypeStatic   (      OSGUInt32 typeId);
    static OSGUInt16              findGroupIdStatic(const OSGChar8  *name);

    static OSGUInt32 registerType (      OSGFieldContainerType *typeP);
    static OSGUInt16 registerGroup(const OSGChar8              *name);

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

    friend class OSGFieldContainer;
    friend class OSGFieldContainerType;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

    static OSGFieldContainerFactory  _the;

    static OSGBool                   _initialized;

    static OSGTypeIdMap             *_typeIdMap;
    static OSGTypeNameMap           *_typeNameMap;
    static OSGGroupMap              *_groupMap;

    static OSGFieldContainerStore   *_fieldcontainerStoreV;

    static OSGLock                  *_storeLock;
    static OSGLock                  *_mapLock;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGFieldContainerFactory (void);
    virtual ~OSGFieldContainerFactory (void);

    // prohibit default functions (move to 'public' if you need one)

    OSGFieldContainerFactory (const OSGFieldContainerFactory &obj);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef OSGFieldContainerFactory* OSGFieldContainerFactoryP;

OSG_END_NAMESPACE

#endif // OSGFIELDCONTAINERFACTORY_CLASS_DECLARATION
