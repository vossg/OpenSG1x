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

#ifndef _OSGVRMLWRITEACTION_H_
#define _OSGVRMLWRITEACTION_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <vector>

#include <OSGBaseTypes.h>
#include <OSGAction.h>
#include <OSGGeometry.h>

#if defined(WIN32) && defined(OSG_BUILD_DLL)
#    if defined(OSG_COMPILESYSTEMLIB)
#        define OSG_VRMLWRITER_DLLMAPPING __declspec(dllexport)
#    else
#        define OSG_VRMLWRITER_DLLMAPPING __declspec(dllimport)
#    endif
#else
#define OSG_VRMLWRITER_DLLMAPPING
#endif

#include <OSGGroup.h>

#include <map>


OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class Node;
class Action;
class Material;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief DrawAction class
 */

class OSG_VRMLWRITER_DLLMAPPING VRMLWriteAction : public Action
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    enum TraversalMode
    {
        OSGCollectFC = 0x0001,
        OSGWrite     = 0x0002
    };

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "VRMLWriteAction"; };

    // create a new DrawAction by cloning the prototype
    static VRMLWriteAction * create( void );
    
    // prototype access
    // after setting the prototype all new DrawActions are clones of it
    static void             setPrototype(VRMLWriteAction * proto);
    static VRMLWriteAction *getPrototype(void);

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    virtual ~VRMLWriteAction(void); 

    /*------------------------- your_category -------------------------------*/
    
    // default registration. static, so it can be called during static init
    
    static void registerEnterDefault(   const FieldContainerType &type, 
                                        const Functor            &func);
    
    static void registerLeaveDefault(   const FieldContainerType &type, 
                                        const Functor            &func);

    
    // rendering state handling
    
    Material   *getMaterial(void) const;
    void        setMaterial(Material *material);

    FILE          *getFilePtr(void) const;
    TraversalMode  getMode   (void) const;

    /*------------------------- your_operators ------------------------------*/

    Bool open (const Char8 *szFilename);
    void close(void);

    /*------------------------- assignment ----------------------------------*/

	virtual Action::ResultE write(NodePtr node);

    /*------------------------- comparison ----------------------------------*/

    Bool operator < (const VRMLWriteAction &other) const;
    
    Bool operator == (const VRMLWriteAction &other) const;
    Bool operator != (const VRMLWriteAction &other) const;

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

    // access default functors

    virtual vector<Functor>* getDefaultEnterFunctors( void );
    virtual vector<Functor>* getDefaultLeaveFunctors( void );

	virtual Action::ResultE apply(vector<NodePtr>::iterator begin, 
                                  vector<NodePtr>::iterator end);

	virtual Action::ResultE apply(NodePtr node);

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef Action Inherited;

    struct ActionInitializer
    {
        ActionInitializer(void);
        ~ActionInitializer(void);
    };

    struct FCInfo
    {
      private:

        Int32  _iTimesUsed;
        Bool   _bOwnName;
        Char8 *_szName;
        
      public:

        FCInfo(void);
        FCInfo(const FCInfo &source);
        ~FCInfo(void);

        void setName  (const Char8  *szName);
        void buildName(const Char8  *szTypename,
                             UInt32  uiContainerId);
        void incUse   (void);
        
              UInt32  getUse (void) const;
        const Char8  *getName(void) const;

        Bool  getWriten(void) const;
        void  setWriten (void);

        // returnvalue required by MS
        Int32 clear    (void);
    };

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

    // the prototype which is copied to create new actions
    static VRMLWriteAction * _prototype;

    // default functors for instantiation
    static vector<Functor> *_defaultEnterFunctors;
    static vector<Functor> *_defaultLeaveFunctors;
    
    static ActionInitializer _actionInitializer;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static Action::ResultE writeGroupEnter(CNodePtr &pGroup,
                                           Action   *pAction);
    static Action::ResultE writeGroupLeave(CNodePtr &pGroup,
                                           Action   *pAction);


    static Action::ResultE writeVTransformEnter(CNodePtr &pGroup,
                                                Action   *pAction);
    static Action::ResultE writeVTransformLeave(CNodePtr &pGroup,
                                                Action   *pAction);

    static void writePoints   (GeometryPtr      pGeo, 
                               FILE            *pFile,
                               VRMLWriteAction *pWriter);
    static void writeNormals  (GeometryPtr      pGeo, 
                               FILE            *pFile,
                               VRMLWriteAction *pWriter);
    static void writeTexCoords(GeometryPtr      pGeo, 
                               FILE            *pFile,
                               VRMLWriteAction *pWriter);

    static void writeIndex    (GeometryPtr      pGeo, 
                               FILE            *pFile,
                               VRMLWriteAction *pWriter);

    static void writeMaterial (GeometryPtr      pGeo, 
                               FILE            *pFile,
                               VRMLWriteAction *pWriter);

    static Action::ResultE writeGeoEnter(CNodePtr &pGroup,
                                         Action   *pAction);
    static Action::ResultE writeGeoLeave(CNodePtr &pGroup,
                                         Action   *pAction);

    static Bool initializeAction(int &argc, char **argv);
    static Bool terminateAction(void);

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    Material      *_material;

    UInt32         _uiIndent;
    FILE          *_pFile;

    TraversalMode  _eTraversalMode;    

    vector<FCInfo> _vFCInfos;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    // prohibit default functions (move to 'public' if you need one)

    VRMLWriteAction(void);
    VRMLWriteAction(const VRMLWriteAction &source);
    VRMLWriteAction& operator =(const VRMLWriteAction &source);

    void incIndent  (UInt32 uiDelta);
    void decIndent  (UInt32 uiDelta);
    void printIndent(void);

    void    addNodeUse     (CNodePtr          &pNode);
    void    addContainerUse(FieldContainerPtr &pContainter);

    FCInfo *getInfo(CNodePtr &pNode);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef VRMLWriteAction *VRMLWriteActionP;

OSG_END_NAMESPACE

#include "OSGVRMLWriteAction.inl"

#endif /* _OSGVRMLWRITEACTION_H_ */
