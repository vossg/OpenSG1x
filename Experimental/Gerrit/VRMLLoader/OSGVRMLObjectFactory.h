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

#ifndef _OSGVRMLOBJECTFACTORY_HPP_
#define _OSGVRMLOBJECTFACTORY_HPP_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGVRMLBase.h>
#include <OSGContainerFactoryMixin.h>
#include <OSGVRMLObjectType.h>
#include <OSGVRMLChangeList.h>
#include <OSGVRMLObject.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class VRMLObjectFactory;
class VRMLObjectType;
class VRMLNode;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

struct VRMLObjectFactoryDesc
{
    typedef VRMLObjectFactory FactoryT;
    typedef VRMLObject        ContainerT;
    typedef VRMLObjectType    ContainerTypeT;
    typedef VRMLObject       *ContainerPtrT;
    typedef VRMLChangeList    ChangeListT;

    static const Char8 *getName(void) { return "VRMLObjectFactory"; }

    static VRMLObject *createContainer(const VRMLObjectType *pType)
    {
        return pType->createObject();
    }

    static VRMLObject *getNullPtr(void)
    {
        return NULL;
    }

    static const Char8 *getMapLockName(void)
    {
        return "ObjectFactory::_pMapLock";
    }

    static const Char8 *getStoreLockName(void)
    {
        return "VRMLObjectFactory::_pStoreLock";
    }

    static UInt32 getChangedId(VRMLObject *pObject)
    {
        return pObject->getId();
    }
};

typedef ContainerFactoryMixin     <VRMLObjectFactoryDesc> CFVO;
typedef PrototypeFactoryMixin     <CFVO                 > VOFP;
typedef ContainerStoreFactoryMixin<VOFP                 > VOCS;
typedef ChangeListFactoryMixin    <VOCS                 > VOCL;

#ifndef OSG_COMPILEVRMLOBJECTFACTORYINST

#ifdef __sgi

#pragma do_not_instantiate ContainerFactoryMixin<VRMLObjectFactoryDesc>

#pragma do_not_instantiate PrototypeFactoryMixin< ContainerFactoryMixin<VRMLObjectFactoryDesc> >

#pragma do_not_instantiate ContainerStoreFactoryMixin< PrototypeFactoryMixin< ContainerFactoryMixin<VRMLObjectFactoryDesc> > >

#pragma do_not_instantiate ChangeListFactoryMixin< ContainerStoreFactoryMixin< PrototypeFactoryMixin< ContainerFactoryMixin<VRMLObjectFactoryDesc> > > >

#else

#if !defined(__hpux) && !defined(OSG_LINUX_ICC)
extern template class OSG_VRML_DLLMAPPING 
    ContainerFactoryMixin<VRMLObjectFactoryDesc>;

extern template class OSG_VRML_DLLMAPPING
    PrototypeFactoryMixin<
        ContainerFactoryMixin<VRMLObjectFactoryDesc> >;

extern template class OSG_VRML_DLLMAPPING
    ContainerStoreFactoryMixin<
        PrototypeFactoryMixin<
            ContainerFactoryMixin<VRMLObjectFactoryDesc> > >;

extern template class OSG_VRML_DLLMAPPING
    ChangeListFactoryMixin<
        ContainerStoreFactoryMixin<
            PrototypeFactoryMixin<
                ContainerFactoryMixin<VRMLObjectFactoryDesc> > > >;
#endif

#endif

#endif

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! VRMLObjectFactory
//! \ingroup VRMLBaseLib 

class OSG_VRML_DLLMAPPING VRMLObjectFactory : public VOCL
{
  private:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

  public:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef VOCL Inherited;

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   enums                                                               
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

    template <class FactoryDescT>
    friend class ContainerFactoryMixin;

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

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    //! prohibit default function (move to 'public' if needed) 
    VRMLObjectFactory(const VRMLObjectFactory &source);
    //! prohibit default function (move to 'public' if needed) 
    void operator =(const VRMLObjectFactory &source);

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

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    VRMLObjectFactory(const Char8 *szName);
    virtual ~VRMLObjectFactory(void); 

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    VRMLNode *createNode(const Char8  *szName  );
    VRMLNode *getNode   (      UInt32  uiNodeId);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

OSG_END_NAMESPACE

#define OSGVRMLOBJECTFACTORY_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGVRMLOBJECTFACTORY_HPP_ */
