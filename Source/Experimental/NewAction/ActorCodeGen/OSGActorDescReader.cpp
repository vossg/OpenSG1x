
#include <OSGConfig.h>
#include <OSGBaseTypes.h>
#include "OSGActorDescReader.h"

#include <string>
#include <iostream>
#include <fstream>

OSG_USING_NAMESPACE

ActorDescReader::NodeTypeNameMap ActorDescReader::_nodeTypeMap[] =
{
    { ActorDescReader::ACTOR_NODE,       "Actor"       },
    { ActorDescReader::STATEELEM_NODE,   "StateElem"   },
    { ActorDescReader::EXTRAHEADER_NODE, "ExtraHeader" },

    { ActorDescReader::UNKNOWN_NODE,     NULL          }
};




ActorDescReader::ActorNodeAttribNameMap 
ActorDescReader::_actorNodeAttribMap[] =
{
    { ActorDescReader::ACTORNAME_ATTR,              "name"                   },
    { ActorDescReader::PARENTNAME_ATTR,             "parentName"             },
    { ActorDescReader::PARENTHEADER_ATTR,           "parentHeader"           },
    { ActorDescReader::PARENTHEADERPREFIX_ATTR,     "parentHeaderPrefix"     },
    { ActorDescReader::LIBNAME_ATTR,                "libName"                },
    { ActorDescReader::HEADERPREFIX_ATTR,           "headerPrefix"           },
    { ActorDescReader::ENTERSTORE_ATTR,             "enterStore"             },
    { ActorDescReader::LEAVESTORE_ATTR,             "leaveStore"             },
    { ActorDescReader::ACCEPTSTATEAWAREITER_ATTR,   "acceptStateAwareIter"   },
    { ActorDescReader::ACCEPTSTATEUNAWAREITER_ATTR, "acceptStateUnawareIter" },
    { ActorDescReader::USELOCALINCLUDES_ATTR,       "useLocalIncludes"       },

    { ActorDescReader::UNKNOWNACTOR_ATTR,           NULL                     }
};

ActorDescReader::StateElemNodeAttribNameMap
ActorDescReader::_stateElemNodeAttribMap[] =
{
    { ActorDescReader::STATENAME_ATTR,             "name"         },
    { ActorDescReader::TYPE_ATTR,                  "type"         },
    { ActorDescReader::TYPEHEADER_ATTR,            "typeHeader"   },
    { ActorDescReader::DEFAULTVALUE_ATTR,          "defaultValue" },
    { ActorDescReader::ACCESS_ATTR,                "access"       },
    { ActorDescReader::ORDERED_ATTR,               "ordered"      },

    { ActorDescReader::UNKNOWNSTATE_ATTR,          NULL           }
}; 

ActorDescReader::ActorDescReader(void)
    : _pActorInfo(NULL)
{
}

ActorDescReader::ActorDescReader(ActorInfo *pActorInfo)
    : _pActorInfo(pActorInfo)
{
}

ActorDescReader::~ActorDescReader(void)
{
}

void
ActorDescReader::setActorInfo(ActorInfo *pActorInfo)
{
    _pActorInfo = pActorInfo;
}

ActorInfo *
ActorDescReader::getActorInfo(void)
{
    return _pActorInfo;
}

bool
ActorDescReader::read(const std::string &inFileName)
{
    std::ifstream inStream(inFileName.c_str());

    xmlpp::xmlcontextptr               context(new xmlpp::xmlcontext);
    xmlpp::xmldocument                 node   (context              );
    xmlpp::xmlnodeptr                  pNode;
    xmlpp::xmlnodelist::const_iterator iterNode;
    xmlpp::xmlnodelist::const_iterator endNode;

    if(inStream)
    {
        try
        {
            ActorDescReader::NodeTypeE ntype = UNKNOWN_NODE;

            node.load(inStream, context);
 
            // handle root node

            ntype = mapNodeTypeName(node.get_name());
            
            if(ntype == ActorDescReader::ACTOR_NODE)
            {
                handleActorNode(node);
            }

            // handle sub nodes

            iterNode = node.get_nodelist().begin();
            endNode  = node.get_nodelist().end  ();
            
            for(; iterNode != endNode; ++iterNode)
            {
                pNode = *iterNode;
                ntype = mapNodeTypeName(pNode->get_name());

                switch(ntype)
                {
                case ActorDescReader::STATEELEM_NODE:
                {
                    handleStateElemNode(*pNode);

                    break;
                }

                case ActorDescReader::EXTRAHEADER_NODE:
                {
                    handleExtraHeaderNode(*pNode);

                    break;
                }
                
                case ActorDescReader::ACTOR_NODE:
                case ActorDescReader::UNKNOWN_NODE:
                default:
                {
                    std::cerr << "ERROR: Node name " << pNode->get_name()
                              << " not recognized or not allowed here."
                              << std::endl;

                    break;
                }
                };
            }
        }
        catch(xmlpp::xmlerror err)
        {
            std::cerr << "Caught xmlpp::xmlerror!\n";

            xmlpp::xmllocation where (context->get_location());
            xmlpp::xmlstring   errmsg(err.get_strerror()     );

            // print out where the error occured
            std::cerr << inFileName << ":" << where.get_line() << " ";
            std::cerr << "at position " << where.get_pos();
            std::cerr << ": error: "    << errmsg.c_str();
            std::cerr << std::endl;

            return false;
        }
    }

    return true;
}

void
ActorDescReader::handleActorNode(xmlpp::xmlnode &node)
{
    xmlpp::xmlattributes::iterator itAttr  = node.get_attrmap().begin();
    xmlpp::xmlattributes::iterator endAttr = node.get_attrmap().end  ();

    ActorDescReader::ActorNodeAttribE attrType = UNKNOWNACTOR_ATTR;

    for(; itAttr != endAttr; ++itAttr)
    {
        attrType = mapActorNodeAttrib(itAttr->first);

        switch(attrType)
        {
        case ActorDescReader::ACTORNAME_ATTR:
        {
            _pActorInfo->setName(itAttr->second);

            break;
        }
        
        case ActorDescReader::PARENTNAME_ATTR:
        {
            _pActorInfo->setParentName(itAttr->second);

            break;
        }

        case ActorDescReader::PARENTHEADER_ATTR:
        {
            _pActorInfo->setParentHeader(itAttr->second);

            break;
        }

        case ActorDescReader::PARENTHEADERPREFIX_ATTR:
        {
            _pActorInfo->setParentHeaderPrefix(itAttr->second);

            break;
        }

        case ActorDescReader::LIBNAME_ATTR:
        {
            _pActorInfo->setLibName(itAttr->second);

            break;
        }
        
        case ActorDescReader::HEADERPREFIX_ATTR:
        {
            _pActorInfo->setHeaderPrefix(itAttr->second);

            break;
        }

        case ActorDescReader::ENTERSTORE_ATTR:
        {
            _pActorInfo->setEnterStore(itAttr->second);
            
            break;
        }

        case ActorDescReader::LEAVESTORE_ATTR:
        {
            _pActorInfo->setLeaveStore(itAttr->second);

            break;
        }

        case ActorDescReader::ACCEPTSTATEAWAREITER_ATTR:
        {
            bool attribVal;
            
            if(strToBool(itAttr->second, attribVal) == true)
            {
                _pActorInfo->setAcceptStateAwareIter(attribVal);
            }
            else
            {
                std::cerr << "ERROR: " << itAttr->second
                          << " not allowed here. Allowed values are: "
                          << "\"true\", \"false\"."
                          << std::endl;
            }

            break;
        }

        case ActorDescReader::ACCEPTSTATEUNAWAREITER_ATTR:
        {
            bool attribVal;
            
            if(strToBool(itAttr->second, attribVal) == true)
            {
                _pActorInfo->setAcceptStateUnawareIter(attribVal);
            }
            else
            {
                std::cerr << "ERROR: " << itAttr->second
                          << " not allowed here. Allowed values are: "
                          << "\"true\", \"false\"."
                          << std::endl;
            }

            break;
        }

        case ActorDescReader::USELOCALINCLUDES_ATTR:
        {
            bool attribVal;

            if(strToBool(itAttr->second, attribVal) == true)
            {
                _pActorInfo->setUseLocalIncludes(attribVal);
            }
            else
            {
                std::cerr << "ERROR: " << itAttr->second
                          << " not allowed here. Allowed value are: "
                          << "\"true\", \"false\"."
                          << std::endl;
            }

            break;
        }

        case ActorDescReader::UNKNOWNACTOR_ATTR:
        default:
        {
            std::cerr << "ActorDescReader::read: ERROR: attribute "
                      << itAttr->first << " is not recognized."
                      << std::endl;

            break;
        }
        }
    }
}

void
ActorDescReader::handleStateElemNode(xmlpp::xmlnode &node)
{
    xmlpp::xmlattributes::iterator itAttr  = node.get_attrmap().begin();
    xmlpp::xmlattributes::iterator endAttr = node.get_attrmap().end  ();

    ActorDescReader::StateElemNodeAttribE attrType = UNKNOWNSTATE_ATTR;
    StateElemInfo                         seInfo;

    for(; itAttr != endAttr; ++itAttr)
    {
        attrType = mapStateElemNodeAttrib(itAttr->first);

        switch(attrType)
        {
        case ActorDescReader::STATENAME_ATTR:
        {
            seInfo.setName(itAttr->second);

            break;
        }

        case ActorDescReader::TYPE_ATTR:
        {
            seInfo.setType(itAttr->second);
            
            break;
        }

        case ActorDescReader::TYPEHEADER_ATTR:
        {
            seInfo.setTypeHeader(itAttr->second);

            break;
        }

        case ActorDescReader::DEFAULTVALUE_ATTR:
        {
            seInfo.setDefaultValue(itAttr->second);

            break;
        }

        case ActorDescReader::ACCESS_ATTR:
        {
            seInfo.setAccess(itAttr->second);
            
            break;
        }

        case ActorDescReader::ORDERED_ATTR:
        {
            seInfo.setOrder(itAttr->second);
            
            break;
        }

        case ActorDescReader::UNKNOWNSTATE_ATTR:
        default:
        {
            std::cerr << "ActorDescReader::read: ERROR: attribute "
                      << itAttr->first << " is not recognized."
                      << std::endl;

            break;
        }
        }
    }

    _pActorInfo->addStateElem(seInfo);
}

void
ActorDescReader::handleExtraHeaderNode(xmlpp::xmlnode &node)
{
    _pActorInfo->addExtraHeader(node.get_cdata());
}    

ActorDescReader::NodeTypeE
ActorDescReader::mapNodeTypeName(const std::string &nodeName)
{
    ActorDescReader::NodeTypeE retVal = UNKNOWN_NODE;

    for(unsigned int i = 0; _nodeTypeMap[i]._name != NULL; ++i)
    {
        if(strcmp(_nodeTypeMap[i]._name, nodeName.c_str()) == 0)
        {
            retVal = _nodeTypeMap[i]._type;
            
            break;
        }
    }

    return retVal;
}

ActorDescReader::ActorNodeAttribE
ActorDescReader::mapActorNodeAttrib(const std::string &attribName)
{
    ActorDescReader::ActorNodeAttribE retVal = UNKNOWNACTOR_ATTR;

    for(unsigned int i = 0; _actorNodeAttribMap[i]._name != NULL; ++i)
    {
        if(strcmp(_actorNodeAttribMap[i]._name, attribName.c_str()) == 0)
        {
            retVal = _actorNodeAttribMap[i]._attr;
        
            break;
        }
    }

    return retVal;
}

ActorDescReader::StateElemNodeAttribE
ActorDescReader::mapStateElemNodeAttrib(const std::string &attrName)
{
    ActorDescReader::StateElemNodeAttribE retVal = UNKNOWNSTATE_ATTR;

    for(unsigned int i = 0; _stateElemNodeAttribMap[i]._name != NULL; ++i)
    {
        if(strcmp(_stateElemNodeAttribMap[i]._name, attrName.c_str()) == 0)
        {
            retVal = _stateElemNodeAttribMap[i]._attr;
         
            break;
        }
    }

    return retVal;
}

bool
ActorDescReader::strToBool(const std::string &str, bool &retVal)
{
    if(strcmp("true", str.c_str()) == 0)
    {
        retVal = true;
        return true;
    }
    else if(strcmp("false", str.c_str()) == 0)
    {
        retVal = false;
        return true;
    }

    return false;
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
    static Char8 cvsid_cpp     [] = "@(#)$Id: OSGActorDescReader.cpp,v 1.1 2003/10/10 13:51:07 neumannc Exp $";
    static Char8 cvsid_hpp     [] = OSGACTORDESCREADER_HEADER_CVSID;
    static Char8 cvsid_inl     [] = OSGACTORDESCREADER_INLINE_CVSID;
}
