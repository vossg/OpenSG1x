
#ifndef _OSGACTORDESCREADER_H_
#define _OSGACTORDESCREADER_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGXmlpp.h>

#include "OSGActorInfo.h"
#include "OSGStateElemInfo.h"

#include <string>

OSG_BEGIN_NAMESPACE

class ActorDescReader
{
public:
    enum NodeTypeE
    {
        ACTOR_NODE,
        STATEELEM_NODE,
        EXTRAHEADER_NODE,

        UNKNOWN_NODE
    };

    enum ActorNodeAttribE
    {
        ACTORNAME_ATTR,
        PARENTNAME_ATTR,
        PARENTHEADER_ATTR,
        PARENTHEADERPREFIX_ATTR,
        LIBNAME_ATTR,
        HEADERPREFIX_ATTR,
        ENTERSTORE_ATTR,
        LEAVESTORE_ATTR,
        ACCEPTSTATEAWAREITER_ATTR,
        ACCEPTSTATEUNAWAREITER_ATTR,
        USELOCALINCLUDES_ATTR,
        
        UNKNOWNACTOR_ATTR
    };

    enum StateElemNodeAttribE
    {
        STATENAME_ATTR,
        TYPE_ATTR,
        TYPEHEADER_ATTR,
        DEFAULTVALUE_ATTR,
        ACCESS_ATTR,
        ORDERED_ATTR,

        UNKNOWNSTATE_ATTR
    };

    struct NodeTypeNameMap
    {
        NodeTypeE  _type;
        char      *_name;
    };            

    struct ActorNodeAttribNameMap
    {
        ActorNodeAttribE  _attr;
        char             *_name;
    };          

    struct StateElemNodeAttribNameMap
    {
        StateElemNodeAttribE  _attr;
        char                 *_name;
    };

     ActorDescReader(void);
     ActorDescReader(ActorInfo *pActorInfo);
    ~ActorDescReader(void);

    void       setActorInfo(      ActorInfo   *pActorInfo);
    ActorInfo *getActorInfo(      void                   );

    bool       read        (const std::string &inFileName);

private:
    bool strToBool            (const std::string &str, bool &retVal);

    void handleActorNode      (xmlpp::xmlnode &node);
    void handleStateElemNode  (xmlpp::xmlnode &node);
    void handleExtraHeaderNode(xmlpp::xmlnode &node);

    NodeTypeE            mapNodeTypeName       (const std::string &nodeName  );
    ActorNodeAttribE     mapActorNodeAttrib    (const std::string &attribName);
    StateElemNodeAttribE mapStateElemNodeAttrib(const std::string &attribName);

    static NodeTypeNameMap            _nodeTypeMap           [];
    static ActorNodeAttribNameMap     _actorNodeAttribMap    [];
    static StateElemNodeAttribNameMap _stateElemNodeAttribMap[];

    ActorInfo *_pActorInfo;
};

OSG_END_NAMESPACE

#include "OSGActorDescReader.inl"

#define OSGACTORDESCREADER_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGACTORDESCREADER_H_ */
