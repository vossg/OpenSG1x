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


#ifndef _OSGVRMLNODEFACTORY_H_
#define _OSGVRMLNODEFACTORY_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>
#include <OSGString.h>

#ifdef OSG_SGI_STL
#ifdef OSG_HASH_MAP_AS_EXT
#include <ext/hash_map>
#else
#include <hash_map>
#endif
#else
#include <map>
#endif

#include <stack>

#include <OSGNode.h>
#include <OSGNodeCore.h>
#include <OSGAttachment.h>
#include <OSGGroup.h>
#include <OSGGeometry.h>

#include <OSGVRMLNodeDescs.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup 
 *  \brief Brief
 *
 *  detailed
 */

template <class BaseT>
class VRMLNodeFactory : public BaseT
{
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

#ifdef OSG_SGI_STL
    typedef hash_map<     const Char8 *,  VRMLNodeDesc *, 
                     hash<const Char8 *>, EQString      > NodeNameDescHash;
#else
    typedef map     <     const Char8 *,  VRMLNodeDesc *, 
                                          LTString      > NodeNameDescHash;
#endif
   
    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

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

    VRMLNodeDesc     *_pCurrentNodeDesc;
    NodeNameDescHash  _mNodeDescHash;

    Bool             _bInFieldProto;
    Bool             _bIgnoreProto;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------
   
	// prohibit default functions (move to 'public' if you need one)

    VRMLNodeFactory(const VRMLNodeFactory &source);
    void operator =(const VRMLNodeFactory &source);

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef BaseT Inherited;

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

    VRMLNodeDesc *findNodeDesc(const Char8 *szNodeTypename);
    void          addNodeDesc (const Char8        *szNodeTypename,
                                     VRMLNodeDesc *pDesc);

    virtual void preStandardProtos (void);
    virtual void postStandardProtos(void);
    
  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    VRMLNodeFactory(void);

    virtual ~VRMLNodeFactory(void); 

    /*------------------------- your_category -------------------------------*/

    virtual void beginProtoInterface    (const Char8 *szProtoname);
    virtual void endProtoInterface      (void);

    virtual void addProtoEventIn        (const Char8 *szEventType,
                                         const Char8 *szEventName); 

    virtual void addProtoEventOut       (const Char8 *szEventType,
                                         const Char8 *szEventName); 

    virtual void beginProtoField        (const Char8  *szFieldType,
                                         const UInt32  uiFieldTypeId,
                                         const Char8  *szFieldName); 

    virtual void endProtoField          (void);

    virtual void beginProtoExposedField (const Char8  *szFieldType,
                                         const UInt32  uiFieldTypeId,
                                         const Char8  *szFieldName); 

    virtual void endProtoExposedField   (void);


    /*------------------------- your_operators ------------------------------*/

    virtual void addFieldValue          (const Char8 *szFieldVal);

    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

    void dumpTable(void);
};

OSG_END_NAMESPACE

#include <OSGVRMLNodeFactory.inl>

#endif /* _OSGVRMLNODEFACTORY_H_ */
