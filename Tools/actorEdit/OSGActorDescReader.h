/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifndef _OSGACTORDESCREADER_H_
#define _OSGACTORDESCREADER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGXmlpp.h>

#include "OSGActorDesc.h"
#include "OSGActorStateElemDesc.h"

#include <istream>

OSG_USING_NAMESPACE

class ActorDescReader
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name    Singleton Access                                          */
    /*! \{                                                                 */

    static ActorDescReader &the(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Destructor                                                */
    /*! \{                                                                 */

    ~ActorDescReader(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Read                                                      */
    /*! \{                                                                 */

    bool readDesc(std::istream &inStream, ActorDesc *pActorDesc);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    typedef void (ActorDescReader::*NodeHandleFuncP)(xmlpp::xmlnodeptr node);

    enum NodeTypeE
    {
        Actor_Node                 =  0,
        Name_Node                  =  1,
        ParentName_Node            =  2,
        EnterFunctorStore_Node     =  3,
        LeaveFunctorStore_Node     =  4,
        UseLocalIncludes_Node      =  5,
        SystemComponent_Node       =  6,
        ParentSystemComponent_Node =  7,
        LibraryName_Node           =  8,
        StateElements_Node         =  9,
        StateElement_Node          = 10,
        Type_Node                  = 11,
        Access_Node                = 12,
        Hierarchical_Node          = 13,
        Header_Node                = 14,
        DefaultValue_Node          = 15,

        Unknown_Node               = 16
    };

    struct NodeTypeMap
    {
        const char      *_nodeName;
        NodeTypeE        _nodeType;
    };

    /*---------------------------------------------------------------------*/
    /*! \name    Constructor                                               */
    /*! \{                                                                 */

    ActorDescReader(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Node Handler                                              */
    /*! \{                                                                 */

    void handleNode                     (xmlpp::xmlnodeptr pNode);

    void handleActorNode                (xmlpp::xmlnodeptr pNode);
    void handleNameNode                 (xmlpp::xmlnodeptr pNode);
    void handleParentNameNode           (xmlpp::xmlnodeptr pNode);
    void handleEnterFunctorStoreNode    (xmlpp::xmlnodeptr pNode);
    void handleLeaveFunctorStoreNode    (xmlpp::xmlnodeptr pNode);
    void handleUseLocalIncludesNode     (xmlpp::xmlnodeptr pNode);
    void handleSystemComponentNode      (xmlpp::xmlnodeptr pNode);
    void handleParentSystemComponentNode(xmlpp::xmlnodeptr pNode);
    void handleLibraryNameNode          (xmlpp::xmlnodeptr pNode);
    void handleStateElementsNode        (xmlpp::xmlnodeptr pNode);
    void handleStateElementNode         (xmlpp::xmlnodeptr pNode);
    void handleStateNameNode            (xmlpp::xmlnodeptr pNode);
    void handleTypeNode                 (xmlpp::xmlnodeptr pNode);
    void handleAccessNode               (xmlpp::xmlnodeptr pNode);
    void handleHierarchicalNode         (xmlpp::xmlnodeptr pNode);
    void handleHeaderNode               (xmlpp::xmlnodeptr pNode);
    void handleDefaultValueNode         (xmlpp::xmlnodeptr pNode);

    void handleUnknownNode              (xmlpp::xmlnodeptr pNode);
    void handleIllegalNode              (xmlpp::xmlnodeptr pNode);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    static ActorDescReader *_the;
    static NodeTypeMap      _nodeTypes[];

    NodeHandleFuncP        *_pHandleFuncs;
    ActorDesc              *_pActorDesc;
    ActorStateElemDesc     *_pStateElem;
};

//#include "OSGActorDescReader.inl"

#define OSGACTORDESCREADER_HEADER_CVSID "@(#)$Id: OSGActorDescReader.h,v 1.1 2004/04/20 13:06:50 neumannc Exp $"

#endif /* _OSGACTORDESCREADER_H_ */
