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


#ifndef _OSGVRMLFILE_H_
#define _OSGVRMLFILE_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGSystemDef.h>

#include <map>

#include <OSGBaseTypes.h>
#include <OSGScanParseSkel.h>
#include <OSGScanParseFieldTypeMapper.h>

#include <OSGFieldContainerPtr.h>
#include <OSGField.h>
#include <OSGFieldContainer.h>

#include <stack>
#include <vector>

#include <OSGVRMLNodeFactory.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

typedef VRMLNodeFactory<ScanParseFieldTypeMapper<ScanParseSkel> > 
    Parent;

#ifndef OSG_COMPILEVRMLLOADERINST

#ifndef __sgi
extern 
template OSG_SYSTEMLIB_DLLMAPPING 
ScanParseFieldTypeMapper<ScanParseSkel>;

extern 
template OSG_SYSTEMLIB_DLLMAPPING 
VRMLNodeFactory<ScanParseFieldTypeMapper<ScanParseSkel> >;
#endif

#endif

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup 
 *  \brief Brief
 *
 *  detailed
 */

class OSG_SYSTEMLIB_DLLMAPPING VRMLFile : public Parent
{
  public:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef Parent Inherited;

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    enum 
    {
        CreateNormals       = Inherited::LastOption << 1,
        LogProtoGeneration  = CreateNormals         << 1,
        LogObjectGeneration = LogProtoGeneration    << 1,

        LastOption          = LogObjectGeneration
    };

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

    VRMLFile(const VRMLFile &source);
    void operator =(const VRMLFile &source);

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef map<String, FieldContainerPtr> NameContainerMap;
    typedef map<String, VRMLNodeDesc    *> NameDescriptionMap;
 
    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

          NodePtr          _pRootNode;

          VRMLNodeDesc *   _pCurrNodeDesc;
    stack<VRMLNodeDesc *>  _sNodeDescs;

          FieldContainerPtr  _pCurrentFC;
          Field             *_pCurrentField;
    const FieldDescription  *_pCurrentFieldDesc;

    stack<      FieldContainerPtr > _fcStack;
    stack<      Field            *> _fStack;
    stack<const FieldDescription *> _fdStack;

    NameContainerMap                _nameFCMap;
    NameDescriptionMap              _nameDescMap;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    void initIntExtFieldTypeMapper(void);
    void initExtIntFieldTypeMapper(void);

    FieldContainerPtr findFCByName          (const Char8  *szName,
                                                   NodePtr pNode);

    void              setContainerFieldValue(const FieldContainerPtr &pFC);

    FieldContainerPtr findReference         (const Char8 *szName);

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    VRMLFile(void);
    virtual ~VRMLFile(void); 

    virtual void scanFile(const Char8 *szFilename, UInt32 uiOptions);

    /*------------------------- your_category -------------------------------*/

    virtual void  beginNode               (const Char8 *szNodeTypename,
                                           const Char8 *szNodename);
    
    virtual void  endNode                 (void);


    virtual void  beginField              (const Char8 *szFieldname,
                                           const UInt32 uiFieldTypeId);

    virtual void  endField                (void);

    /*------------------------- your_operators ------------------------------*/

    virtual void  addFieldValue           (const Char8 *szFieldVal);

    /*------------------------- assignment ----------------------------------*/

    virtual UInt32  getFieldType          (const Char8 *szFieldname);

    /*------------------------- comparison ----------------------------------*/

    virtual void    use                   (const Char8 *szName);
    
            void    scanStandardPrototypes(const Char8  *szFilename, 
                                           UInt32  uiOptions);

            NodePtr getRoot               (void);

            NodePtr cloneTree             (NodePtr pRootNode);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef VRMLFile *VRMLFileP;

OSG_END_NAMESPACE

#endif /* _OSGVRMLFILE_H_ */
