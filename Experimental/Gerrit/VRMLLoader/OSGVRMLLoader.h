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

#ifndef _OSGVRMLLOADER_HPP_
#define _OSGVRMLLOADER_HPP_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGScanParseSkel.h>
#include <OSGScanParseFieldTypeMapper.h>
#include <OSGVRMLBase.h>
#include <OSGIDString.h>

#include <stack>
#include <vector>
#include <map>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class VRMLNode;
class Field;
class DataElementDesc;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! VRMLLoader
//! \ingroup VRMLLoader

class OSG_VRML_DLLMAPPING VRMLLoader : 
    public ScanParseFieldTypeMapper<ScanParseSkel>
{
  private:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef ScanParseFieldTypeMapper<ScanParseSkel> Inherited;

  public:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef stack <      VRMLNode          *> NodeStack;
    typedef stack <      Field             *> FieldStack;
    typedef stack <const DataElementDesc   *> ElementDescStack;

    typedef vector<      VRMLNode          *> ResultStore;

    typedef map   <IDStringLink, VRMLNode  *> NameNodeMap;

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
    VRMLLoader(const VRMLLoader &source);
    //! prohibit default function (move to 'public' if needed) 
    void operator =(const VRMLLoader &source);

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

    static UInt32  _uiIndent;
    static UInt32  _uiIndentIndex;
    static UInt32  _uiMaxIndent;
    static Char8  *_szIndents;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static void incIndent(void              );
    static void decIndent(void              );
    static void doIndent (ostream &outstream);

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

          ResultStore       _vResultStore;
          VRMLNode         *_pFileTree;

          VRMLNode         *_pCurrentNode;

          Field            *_pCurrentField;
    const DataElementDesc  *_pCurrentFieldDesc;

          NodeStack         _sNodeStack;
          FieldStack        _sFieldStack;
          ElementDescStack  _sElementDescStack;

          NameNodeMap      *_pNameNodeMap;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    void initFieldTypeMapper(void              );
    void setNodeValue       (VRMLNode *pNewNode);

    void insertNamedNode    (VRMLNode *pNode   );

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    VRMLLoader(void);

    virtual ~VRMLLoader(void); 

    /*------------------------- your_operators ------------------------------*/

    virtual void      beginNode              (const Char8 *szNodeTypename,
                                              const Char8 *szNodename);
    
    virtual void      endNode                (void);

    virtual void      beginScript            (const Char8 *szNodename);
    
    virtual void      endScript              (void);

    virtual void      use                    (const Char8 *szName);

    virtual void      beginField             (const Char8 *szFieldname,
                                              const UInt32 uiFieldTypeId);

    virtual void      endField               (void);

    /*------------------------- your_operators ------------------------------*/

    virtual void      addFieldValue          (const Char8 *szFieldVal);

    virtual void      addRoute               (const Char8 *szOutNodename,
                                              const Char8 *szOutFieldname,
                                              const Char8 *szInNodename,
                                              const Char8 *szInFieldname);

    /*---------------------------- support ----------------------------------*/

    virtual UInt32 getFieldType           (const Char8 *szFieldname);

    /*------------------------------ scan -----------------------------------*/

    virtual void scanFile(const Char8 *szFilename, UInt32 uiOptions);

    virtual void scanFile(const Char8  *szFilename, 
                                UInt32  uiAddOptions, 
                                UInt32  uiSubOptions);

    /*---------------------------- result -----------------------------------*/

    ResultStore &getResultStore(void);
    
    VRMLNode    *getFileTree   (void);

    NameNodeMap *getNameNodeMap(void);
};

OSG_END_NAMESPACE

#define OSGVRMLLOADER_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGVRMLLOADER_HPP_ */
