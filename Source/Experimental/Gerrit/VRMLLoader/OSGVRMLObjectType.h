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

#ifndef _OSGVRMLOBJECTTYPE_HPP_
#define _OSGVRMLOBJECTTYPE_HPP_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGReflexiveContainerType.h>
#include <OSGVRMLBase.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class VRMLObject;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

typedef void         (*VRMLInitObjectF )(void);
typedef VRMLObject * (*VRMLProtoCreateF)(void);

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! VRMLObjectType
//! \ingroup VRMLBaseLib

class OSG_VRML_DLLMAPPING VRMLObjectType : public ReflexiveContainerType
{
  private:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef ReflexiveContainerType Inherited;

  public:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

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
    VRMLObjectType(const VRMLObjectType &source);
    //! prohibit default function (move to 'public' if needed) 
    void operator =(const VRMLObjectType &source);

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

    VRMLObject       *_pPrototype;
    VRMLProtoCreateF  _fPrototypeCreate;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    bool initPrototype(void);
	bool initialize   (void);
    void terminate    (void);

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    VRMLObjectType(const Char8                *szName,
                   const Char8                *szParentName     = NULL,
                   const Char8                *szGroupName      = NULL,
                         VRMLProtoCreateF      fPrototypeCreate = NULL,
                         VRMLInitObjectF       fInitMethod      = NULL,
                         InitalInsertDescFunc  descInsertFunc   = NULL,
                         bool                  bDescsAddable    = false);

    virtual ~VRMLObjectType(void); 

    /*------------------------- prototye ------------------------------------*/

    VRMLObject *getPrototype(void                  ) const;
    bool        setPrototype(VRMLObject *pPrototype);

    /*-------------------------- properties ---------------------------------*/

    bool isAbstract(void) const;

    /*----------------------------- create ----------------------------------*/

    VRMLObject *createObject(void) const;
};

OSG_END_NAMESPACE

#define OSGVRMLOBJECTTYPE_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGVRMLOBJECTTYPE_HPP_ */
