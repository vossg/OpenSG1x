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

#include "OSGActorDescReader.h"
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGLog.h>

#include <fstream>

OSG_USING_NAMESPACE

/*------------------------------------------------------------------------*/
/*    Static Member Init                                                  */

ActorDescReader              *ActorDescReader::_the         = NULL;

ActorDescReader::NodeTypeMap  ActorDescReader::_nodeTypes[] =
{
    { "Actor",                 ActorDescReader::Actor_Node                 },
    { "Name",                  ActorDescReader::Name_Node                  },
    { "ParentName",            ActorDescReader::ParentName_Node            },
    { "EnterFunctorStore",     ActorDescReader::EnterFunctorStore_Node     },
    { "LeaveFunctorStore",     ActorDescReader::LeaveFunctorStore_Node     },
    { "UseLocalIncludes",      ActorDescReader::UseLocalIncludes_Node      },
    { "SystemComponent",       ActorDescReader::SystemComponent_Node       },
    { "ParentSystemComponent", ActorDescReader::ParentSystemComponent_Node },
    { "LibraryName",           ActorDescReader::LibraryName_Node           },
    { "StateElements",         ActorDescReader::StateElements_Node         },
    { "StateElement",          ActorDescReader::StateElement_Node          },
    { "Type",                  ActorDescReader::Type_Node                  },
    { "Access",                ActorDescReader::Access_Node                },
    { "Hierarchical",          ActorDescReader::Hierarchical_Node          },
    { "Header",                ActorDescReader::Header_Node                },
    { "DefaultValue",          ActorDescReader::DefaultValue_Node          },

    { NULL,                    ActorDescReader::Unknown_Node               }
};

/*------------------------------------------------------------------------*/
/*    Singleton Access                                                    */

ActorDescReader &
ActorDescReader::the(void)
{
    if(_the == NULL)
    {
        _the = new ActorDescReader();
    }

    return *_the;
}

/*------------------------------------------------------------------------*/
/*    Destructor                                                          */

ActorDescReader::~ActorDescReader(void)
{
    delete[] _pHandleFuncs;
}

/*------------------------------------------------------------------------*/
/*    Read                                                                */

bool
ActorDescReader::readDesc(std::istream &inStream, ActorDesc *pActorDesc)
{
    xmlpp::xmlcontextptr context (new xmlpp::xmlcontext);
    xmlpp::xmldocument   node    (context              );

    if(!inStream)
        return false;

    try
    {
        _pActorDesc = pActorDesc;
        _pStateElem = NULL;

        _pActorDesc->clear();

        node.load(inStream, context);

        if(stringcasecmp(node.get_name().c_str(),
                         _nodeTypes[Actor_Node]._nodeName) == 0)
        {
            xmlpp::xmlnodelist::const_iterator iterNode =
                node.get_nodelist().begin();
            xmlpp::xmlnodelist::const_iterator endNode  =
                node.get_nodelist().end  ();

            for(; iterNode != endNode; ++iterNode)
            {
                _pHandleFuncs[Actor_Node                ] =
                    &ActorDescReader::handleIllegalNode;
                _pHandleFuncs[Name_Node                 ] =
                    &ActorDescReader::handleNameNode;
                _pHandleFuncs[ParentName_Node           ] =
                    &ActorDescReader::handleParentNameNode;
                _pHandleFuncs[EnterFunctorStore_Node    ] =
                    &ActorDescReader::handleEnterFunctorStoreNode;
                _pHandleFuncs[LeaveFunctorStore_Node    ] =
                    &ActorDescReader::handleLeaveFunctorStoreNode;
                _pHandleFuncs[UseLocalIncludes_Node     ] =
                    &ActorDescReader::handleUseLocalIncludesNode;
                _pHandleFuncs[SystemComponent_Node      ] =
                    &ActorDescReader::handleSystemComponentNode;
                _pHandleFuncs[ParentSystemComponent_Node] =
                    &ActorDescReader::handleParentSystemComponentNode;
                _pHandleFuncs[LibraryName_Node          ] =
                    &ActorDescReader::handleLibraryNameNode;
                _pHandleFuncs[StateElements_Node        ] =
                    &ActorDescReader::handleStateElementsNode;
                _pHandleFuncs[StateElement_Node         ] =
                    &ActorDescReader::handleIllegalNode;
                _pHandleFuncs[Type_Node                 ] =
                    &ActorDescReader::handleIllegalNode;
                _pHandleFuncs[Access_Node               ] =
                    &ActorDescReader::handleIllegalNode;
                _pHandleFuncs[Hierarchical_Node         ] =
                    &ActorDescReader::handleIllegalNode;
                _pHandleFuncs[Header_Node               ] =
                    &ActorDescReader::handleIllegalNode;
                _pHandleFuncs[DefaultValue_Node         ] =
                    &ActorDescReader::handleIllegalNode;

                handleNode(*iterNode);
            }
        }
        else
        {
            SWARNING << "Root node does not have expected name <Actor>. "
                     << "aborting." << endLog;
        }
    }
    catch(xmlpp::xmlerror err)
    {
    }

    return true;
}

/*------------------------------------------------------------------------*/
/*    Constructors                                                        */

ActorDescReader::ActorDescReader(void)
    : _pHandleFuncs(new NodeHandleFuncP[Unknown_Node + 1]),
      _pActorDesc  (NULL                                 ),
      _pStateElem  (NULL                                 )
{
    _pHandleFuncs[Actor_Node                ] = &ActorDescReader::handleIllegalNode;
    _pHandleFuncs[Name_Node                 ] = &ActorDescReader::handleIllegalNode;
    _pHandleFuncs[ParentName_Node           ] = &ActorDescReader::handleIllegalNode;
    _pHandleFuncs[EnterFunctorStore_Node    ] = &ActorDescReader::handleIllegalNode;
    _pHandleFuncs[LeaveFunctorStore_Node    ] = &ActorDescReader::handleIllegalNode;
    _pHandleFuncs[UseLocalIncludes_Node     ] = &ActorDescReader::handleIllegalNode;
    _pHandleFuncs[SystemComponent_Node      ] = &ActorDescReader::handleIllegalNode;
    _pHandleFuncs[ParentSystemComponent_Node] = &ActorDescReader::handleIllegalNode;
    _pHandleFuncs[LibraryName_Node          ] = &ActorDescReader::handleIllegalNode;
    _pHandleFuncs[StateElements_Node        ] = &ActorDescReader::handleIllegalNode;
    _pHandleFuncs[StateElement_Node         ] = &ActorDescReader::handleIllegalNode;
    _pHandleFuncs[Type_Node                 ] = &ActorDescReader::handleIllegalNode;
    _pHandleFuncs[Access_Node               ] = &ActorDescReader::handleIllegalNode;
    _pHandleFuncs[Hierarchical_Node         ] = &ActorDescReader::handleIllegalNode;
    _pHandleFuncs[Header_Node               ] = &ActorDescReader::handleIllegalNode;
    _pHandleFuncs[DefaultValue_Node         ] = &ActorDescReader::handleIllegalNode;

    _pHandleFuncs[Unknown_Node              ] = &ActorDescReader::handleUnknownNode;
}

/*------------------------------------------------------------------------*/
/*    Node Handler                                                        */

void
ActorDescReader::handleNode(xmlpp::xmlnodeptr pNode)
{
    SINFO << " Node name:" << pNode->get_name() << endLog;

    UInt32 handleFuncIndex = Unknown_Node;

    for(UInt32 i = 0; i < ActorDescReader::Unknown_Node; ++i)
    {
        if(stringcasecmp(pNode->get_name().c_str(),
                         _nodeTypes[i]._nodeName ) == 0)
        {
            handleFuncIndex = i;
            break;
        }
    }

    (this->*_pHandleFuncs[handleFuncIndex])(pNode);
}

void
ActorDescReader::handleActorNode(xmlpp::xmlnodeptr pNode)
{
    xmlpp::xmlnodelist::const_iterator iterNode;
    xmlpp::xmlnodelist::const_iterator endNode;

    iterNode = pNode->get_nodelist().begin();
    endNode  = pNode->get_nodelist().end  ();

    for(; iterNode != endNode; ++iterNode)
    {
        _pHandleFuncs[Actor_Node                ] =
            &ActorDescReader::handleIllegalNode;
        _pHandleFuncs[Name_Node                 ] =
            &ActorDescReader::handleNameNode;
        _pHandleFuncs[ParentName_Node           ] =
            &ActorDescReader::handleParentNameNode;
        _pHandleFuncs[EnterFunctorStore_Node    ] =
            &ActorDescReader::handleEnterFunctorStoreNode;
        _pHandleFuncs[LeaveFunctorStore_Node    ] =
            &ActorDescReader::handleLeaveFunctorStoreNode;
        _pHandleFuncs[UseLocalIncludes_Node     ] =
            &ActorDescReader::handleUseLocalIncludesNode;
        _pHandleFuncs[SystemComponent_Node      ] =
            &ActorDescReader::handleSystemComponentNode;
        _pHandleFuncs[ParentSystemComponent_Node] =
            &ActorDescReader::handleParentSystemComponentNode;
        _pHandleFuncs[LibraryName_Node          ] =
            &ActorDescReader::handleLibraryNameNode;
        _pHandleFuncs[StateElements_Node        ] =
            &ActorDescReader::handleStateElementsNode;
        _pHandleFuncs[StateElement_Node         ] =
            &ActorDescReader::handleIllegalNode;
        _pHandleFuncs[Type_Node                 ] =
            &ActorDescReader::handleIllegalNode;
        _pHandleFuncs[Access_Node               ] =
            &ActorDescReader::handleIllegalNode;
        _pHandleFuncs[Hierarchical_Node         ] =
            &ActorDescReader::handleIllegalNode;
        _pHandleFuncs[Header_Node               ] =
            &ActorDescReader::handleIllegalNode;
        _pHandleFuncs[DefaultValue_Node         ] =
            &ActorDescReader::handleIllegalNode;

        handleNode(*iterNode);
    }
}

void
ActorDescReader::handleNameNode(xmlpp::xmlnodeptr pNode)
{
    if((pNode->get_nodelist().empty()                         == false) &&
       (pNode->get_nodelist().front()->get_nodelist().empty() == false)   )
    {
        _pActorDesc->setActorName(
            pNode->get_nodelist().front()->get_nodelist().front()->get_cdata());
    }
}

void
ActorDescReader::handleParentNameNode(xmlpp::xmlnodeptr pNode)
{
    if((pNode->get_nodelist().empty()                         == false) &&
       (pNode->get_nodelist().front()->get_nodelist().empty() == false)   )
    {
        _pActorDesc->setParentName(
            pNode->get_nodelist().front()->get_nodelist().front()->get_cdata());
    }
}

void
ActorDescReader::handleEnterFunctorStoreNode(xmlpp::xmlnodeptr pNode)
{
    if((pNode->get_nodelist().empty()                         == false) &&
       (pNode->get_nodelist().front()->get_nodelist().empty() == false)   )
    {
        _pActorDesc->setEnterFunctorStore(
            pNode->get_nodelist().front()->get_nodelist().front()->get_cdata());
    }
}

void
ActorDescReader::handleLeaveFunctorStoreNode(xmlpp::xmlnodeptr pNode)
{
    if((pNode->get_nodelist().empty()                         == false) &&
       (pNode->get_nodelist().front()->get_nodelist().empty() == false)   )
    {
        _pActorDesc->setLeaveFunctorStore(
            pNode->get_nodelist().front()->get_nodelist().front()->get_cdata());
    }
}

void
ActorDescReader::handleUseLocalIncludesNode(xmlpp::xmlnodeptr pNode)
{
    if((pNode->get_nodelist().empty()                         == false) &&
       (pNode->get_nodelist().front()->get_nodelist().empty() == false)   )
    {
        _pActorDesc->setUseLocalIncludes(
            pNode->get_nodelist().front()->get_nodelist().front()->get_cdata());
    }
}

void
ActorDescReader::handleSystemComponentNode(xmlpp::xmlnodeptr pNode)
{
    if((pNode->get_nodelist().empty()                         == false) &&
       (pNode->get_nodelist().front()->get_nodelist().empty() == false)   )
    {
        _pActorDesc->setSystemComponent(
            pNode->get_nodelist().front()->get_nodelist().front()->get_cdata());
    }
}

void
ActorDescReader::handleParentSystemComponentNode(xmlpp::xmlnodeptr pNode)
{
    if((pNode->get_nodelist().empty()                         == false) &&
       (pNode->get_nodelist().front()->get_nodelist().empty() == false)   )
    {
        _pActorDesc->setParentSystemComponent(
            pNode->get_nodelist().front()->get_nodelist().front()->get_cdata());
    }
}

void
ActorDescReader::handleLibraryNameNode(xmlpp::xmlnodeptr pNode)
{
    if((pNode->get_nodelist().empty()                         == false) &&
       (pNode->get_nodelist().front()->get_nodelist().empty() == false)   )
    {
        _pActorDesc->setLibraryName(
            pNode->get_nodelist().front()->get_nodelist().front()->get_cdata());
    }
}

void
ActorDescReader::handleStateElementsNode(xmlpp::xmlnodeptr pNode)
{
    xmlpp::xmlnodelist::const_iterator iterNode;
    xmlpp::xmlnodelist::const_iterator endNode;

    iterNode = pNode->get_nodelist().begin();
    endNode  = pNode->get_nodelist().end  ();

    for(; iterNode != endNode; ++iterNode)
    {
        _pHandleFuncs[Actor_Node                ] =
            &ActorDescReader::handleIllegalNode;
        _pHandleFuncs[Name_Node                 ] =
            &ActorDescReader::handleIllegalNode;
        _pHandleFuncs[ParentName_Node           ] =
            &ActorDescReader::handleIllegalNode;
        _pHandleFuncs[EnterFunctorStore_Node    ] =
            &ActorDescReader::handleIllegalNode;
        _pHandleFuncs[LeaveFunctorStore_Node    ] =
            &ActorDescReader::handleIllegalNode;
        _pHandleFuncs[UseLocalIncludes_Node     ] =
            &ActorDescReader::handleIllegalNode;
        _pHandleFuncs[SystemComponent_Node      ] =
            &ActorDescReader::handleIllegalNode;
        _pHandleFuncs[ParentSystemComponent_Node] =
            &ActorDescReader::handleIllegalNode;
        _pHandleFuncs[LibraryName_Node          ] =
            &ActorDescReader::handleIllegalNode;
        _pHandleFuncs[StateElements_Node        ] =
            &ActorDescReader::handleIllegalNode;
        _pHandleFuncs[StateElement_Node         ] =
            &ActorDescReader::handleStateElementNode;
        _pHandleFuncs[Type_Node                 ] =
            &ActorDescReader::handleIllegalNode;
        _pHandleFuncs[Access_Node               ] =
            &ActorDescReader::handleIllegalNode;
        _pHandleFuncs[Hierarchical_Node         ] =
            &ActorDescReader::handleIllegalNode;
        _pHandleFuncs[Header_Node               ] =
            &ActorDescReader::handleIllegalNode;
        _pHandleFuncs[DefaultValue_Node         ] =
            &ActorDescReader::handleIllegalNode;

        handleNode(*iterNode);
    }
}

void
ActorDescReader::handleStateElementNode(xmlpp::xmlnodeptr pNode)
{
    xmlpp::xmlnodelist::const_iterator iterNode;
    xmlpp::xmlnodelist::const_iterator endNode;

    iterNode = pNode->get_nodelist().begin();
    endNode  = pNode->get_nodelist().end  ();

    _pActorDesc->getStateElemList().push_back(ActorStateElemDesc());
    _pStateElem = &(_pActorDesc->getStateElemList().back());

    for(; iterNode != endNode; ++iterNode)
    {
        _pHandleFuncs[Actor_Node               ] =
            &ActorDescReader::handleIllegalNode;
        _pHandleFuncs[Name_Node                 ] =
            &ActorDescReader::handleStateNameNode;
        _pHandleFuncs[ParentName_Node           ] =
            &ActorDescReader::handleIllegalNode;
        _pHandleFuncs[EnterFunctorStore_Node    ] =
            &ActorDescReader::handleIllegalNode;
        _pHandleFuncs[LeaveFunctorStore_Node    ] =
            &ActorDescReader::handleIllegalNode;
        _pHandleFuncs[UseLocalIncludes_Node     ] =
            &ActorDescReader::handleIllegalNode;
        _pHandleFuncs[SystemComponent_Node      ] =
            &ActorDescReader::handleIllegalNode;
        _pHandleFuncs[ParentSystemComponent_Node] =
            &ActorDescReader::handleIllegalNode;
        _pHandleFuncs[LibraryName_Node          ] =
            &ActorDescReader::handleIllegalNode;
        _pHandleFuncs[StateElements_Node        ] =
            &ActorDescReader::handleIllegalNode;
        _pHandleFuncs[StateElement_Node         ] =
            &ActorDescReader::handleIllegalNode;
        _pHandleFuncs[Type_Node                 ] =
            &ActorDescReader::handleTypeNode;
        _pHandleFuncs[Access_Node               ] =
            &ActorDescReader::handleAccessNode;
        _pHandleFuncs[Hierarchical_Node         ] =
            &ActorDescReader::handleHierarchicalNode;
        _pHandleFuncs[Header_Node               ] =
            &ActorDescReader::handleHeaderNode;
        _pHandleFuncs[DefaultValue_Node         ] =
            &ActorDescReader::handleDefaultValueNode;

        handleNode(*iterNode);
    }
}

void
ActorDescReader::handleStateNameNode(xmlpp::xmlnodeptr pNode)
{
    if((pNode->get_nodelist().empty()                         == false) &&
       (pNode->get_nodelist().front()->get_nodelist().empty() == false)   )
    {
        _pStateElem->setName(
            pNode->get_nodelist().front()->get_nodelist().front()->get_cdata());
    }
}

void
ActorDescReader::handleTypeNode(xmlpp::xmlnodeptr pNode)
{
    if((pNode->get_nodelist().empty()                         == false) &&
       (pNode->get_nodelist().front()->get_nodelist().empty() == false)   )
    {
        _pStateElem->setType(
            pNode->get_nodelist().front()->get_nodelist().front()->get_cdata());
    }
}

void
ActorDescReader::handleAccessNode(xmlpp::xmlnodeptr pNode)
{
    if((pNode->get_nodelist().empty()                         == false) &&
       (pNode->get_nodelist().front()->get_nodelist().empty() == false)   )
    {
        _pStateElem->setAccess(
            pNode->get_nodelist().front()->get_nodelist().front()->get_cdata());
    }
}

void
ActorDescReader::handleHierarchicalNode(xmlpp::xmlnodeptr pNode)
{
    if((pNode->get_nodelist().empty()                         == false) &&
       (pNode->get_nodelist().front()->get_nodelist().empty() == false)   )
    {
        _pStateElem->setHierarchical(
            pNode->get_nodelist().front()->get_nodelist().front()->get_cdata());
    }
}

void
ActorDescReader::handleHeaderNode(xmlpp::xmlnodeptr pNode)
{
    if((pNode->get_nodelist().empty()                         == false) &&
       (pNode->get_nodelist().front()->get_nodelist().empty() == false)   )
    {
        _pStateElem->setHeader(
            pNode->get_nodelist().front()->get_nodelist().front()->get_cdata());
    }
}

void
ActorDescReader::handleDefaultValueNode(xmlpp::xmlnodeptr pNode)
{
    if((pNode->get_nodelist().empty()                         == false) &&
       (pNode->get_nodelist().front()->get_nodelist().empty() == false)   )
    {
        _pStateElem->setDefaultValue(
            pNode->get_nodelist().front()->get_nodelist().front()->get_cdata());
    }
}

void
ActorDescReader::handleUnknownNode(xmlpp::xmlnodeptr pNode)
{
    SWARNING << "ActorDescReader: encountered unknown node: "
             << pNode->get_name()
             << ". ignoring."
             << endLog;
}

void
ActorDescReader::handleIllegalNode(xmlpp::xmlnodeptr pNode)
{
    SWARNING << "ActorDescReader: encountered illegal node: "
             << pNode->get_name()
             << ". ignoring."
             << endLog;
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8 cvsid_cpp     [] = "@(#)$Id: OSGActorDescReader.cpp,v 1.1 2004/04/20 13:06:50 neumannc Exp $";
    static Char8 cvsid_hpp     [] = OSGACTORDESCREADER_HEADER_CVSID;
//    static Char8 cvsid_inl     [] = OSGACTORDESCREADER_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
