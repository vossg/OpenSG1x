#
#include <OSGConfig.h>
#include <OSGBaseTypes.h>
#include "OSGActorInfo.h"
#include "OSGStateElemInfo.h"

#include <iostream>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ActorInfo
 */    

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*--------------------------- constructor ---------------------------------*/

ActorInfo::ActorInfo(const std::string &name,
                     const std::string &parentName,
                     const std::string &parentHeader,
                     const std::string &parentHeaderPrefix,
                     const std::string &libName,
                     const std::string &headerPrefix,
                           ActorStoreE  enterStore,
                           ActorStoreE  leaveStore,
                           bool         acceptStateAwareIter,
                           bool         acceptStateUnawareIter,
                           bool         useLocalIncludes       )
    : _name                  (name                  ),
      _parentName            (parentName            ),
      _parentHeader          (parentHeader          ),
      _parentHeaderPrefix    (parentHeaderPrefix    ),
      _libName               (libName               ),
      _headerPrefix          (headerPrefix          ),
      _enterStoreStr         (""                    ),
      _leaveStoreStr         (""                    ),
      _enterStore            (enterStore            ),
      _leaveStore            (leaveStore            ),
      _acceptStateAwareIter  (acceptStateAwareIter  ),
      _acceptStateUnawareIter(acceptStateUnawareIter),
      _useLocalIncludes      (useLocalIncludes      ),
      _stateElems            (                      ),
      _extraHeaders          (                      )
{
    updateStoreStr(_enterStore, _enterStoreStr);
    updateStoreStr(_leaveStore, _leaveStoreStr);
}

/*----------------------------- set & get ---------------------------------*/

void
ActorInfo::setName(const std::string &name)
{
    _name = name;
}

const std::string &
ActorInfo::getName(void) const
{
    return _name;
}

void
ActorInfo::setParentName(const std::string &parentName)
{
    _parentName = parentName;
}

const std::string &
ActorInfo::getParentName(void) const
{
    return _parentName;
}

void
ActorInfo::setParentHeader(const std::string &parentHeader)
{
    _parentHeader = parentHeader;
}

const std::string &
ActorInfo::getParentHeader(void) const
{
    return _parentHeader;
}

void
ActorInfo::setParentHeaderPrefix(const std::string &prefix)
{
    _parentHeaderPrefix = prefix;
}

const std::string &
ActorInfo::getParentHeaderPrefix(void) const
{
    return _parentHeaderPrefix;
}

void
ActorInfo::setLibName(const std::string &libName)
{
    _libName = libName;
}

const std::string &
ActorInfo::getLibName(void) const
{
    return _libName;
}

void
ActorInfo::setHeaderPrefix(const std::string &headerPrefix)
{
    _headerPrefix = headerPrefix;
}

const std::string &
ActorInfo::getHeaderPrefix(void) const
{
    return _headerPrefix;
}

void
ActorInfo::setEnterStore(ActorStoreE enterStore)
{
    _enterStore = enterStore;

    updateStoreStr(_enterStore, _enterStoreStr);
}

void
ActorInfo::setEnterStore(const std::string &enterStore)
{
    if(!mapActorStoreName(enterStore, _enterStore))
    {
        std::cerr << "ActorInfo::setEnterStore: Error " << enterStore
                  << " is not valid. Permissable values are: \"empty\","
                  << " \"simple\", \"single\" and \"multi\"."
                  << std::endl;
    }

    updateStoreStr(_enterStore, _enterStoreStr);
}

ActorInfo::ActorStoreE
ActorInfo::getEnterStore(void) const
{
    return _enterStore;
}

const std::string &
ActorInfo::getEnterStoreStr(void) const
{
    return _enterStoreStr;
}

void
ActorInfo::setLeaveStore(ActorStoreE leaveStore)
{
    _leaveStore = leaveStore;

    updateStoreStr(_leaveStore, _leaveStoreStr);
}

void
ActorInfo::setLeaveStore(const std::string &leaveStore)
{
    if(!mapActorStoreName(leaveStore, _leaveStore))
    {
        std::cerr << "ActorInfo::setLeaveStore: Error " << leaveStore
                  << " is not valid. Permissable values are: \"empty\","
                  << " \"simple\", \"single\" and \"multi\"."
                  << std::endl;
    }   

    updateStoreStr(_leaveStore, _leaveStoreStr);
}

ActorInfo::ActorStoreE
ActorInfo::getLeaveStore(void) const
{
    return _leaveStore;
}

const std::string &
ActorInfo::getLeaveStoreStr(void) const
{
    return _leaveStoreStr;
}

void
ActorInfo::setAcceptStateAwareIter(bool val)
{
    _acceptStateAwareIter = val;
}

bool
ActorInfo::getAcceptStateAwareIter(void) const
{
    return _acceptStateAwareIter;
}

void
ActorInfo::setAcceptStateUnawareIter(bool val)
{
    _acceptStateUnawareIter = val;
}

bool
ActorInfo::getAcceptStateUnawareIter(void) const
{
    return _acceptStateUnawareIter;
}

void
ActorInfo::setUseLocalIncludes(bool val)
{
    _useLocalIncludes = val;
}

bool
ActorInfo::getUseLocalIncludes(void) const
{
    return _useLocalIncludes;
}

void
ActorInfo::addStateElem(const StateElemInfo &stateElem)
{
    _stateElems.push_back(stateElem);
}

void
ActorInfo::addExtraHeader(const std::string &extraHeader)
{
    _extraHeaders.push_back(extraHeader);
}

void
ActorInfo::dump(void)
{
    std::cerr << " Name: \""                 << _name                 << "\""
              << " ParentName: \""           << _parentName           << "\""
              << " ParentHeader: \""         << _parentHeader         << "\""
              << " ParentHeaderPrefix: \""   <<  _parentHeaderPrefix  << "\""
              << " LibName: \""              << _libName              << "\""
              << " HeaderPrefix: \""         << _headerPrefix         << "\""
              << " EnterStore: \""           << _enterStore           << "\""
              << " EnterStoreStr: \""        << _enterStoreStr        << "\""
              << " LeaveStore: \""           << _leaveStore           << "\""
              << " LeaveStoreStr: \""        << _leaveStoreStr        << "\""
              << " acceptStateAwareIter: \"" << _acceptStateAwareIter << "\""
              << " accpetStateUnawareIter: \"" 
              << _acceptStateUnawareIter << "\""
              << " useLocalIncludes: \""     << _useLocalIncludes     << "\""
              << std::endl;
}

/*-------------------------- state iterators ------------------------------*/

ActorInfo::StateElemBagIt
ActorInfo::beginStateElems(void)
{
    return _stateElems.begin();
}

ActorInfo::StateElemBagIt
ActorInfo::endStateElems(void)
{
    return _stateElems.end();
}

/*----------------------- extra header iterators ---------------------------*/

ActorInfo::ExtraHeaderBagIt
ActorInfo::beginExtraHeaders(void)
{
    return _extraHeaders.begin();
}

ActorInfo::ExtraHeaderBagIt
ActorInfo::endExtraHeaders(void)
{
    return _extraHeaders.end();
}

/*=============================  PRIVATE  ==================================*/

bool
ActorInfo::mapActorStoreName(const std::string &store, ActorStoreE &outVar)
{
    bool retVal = false;

    if(strcmp(store.c_str(), "empty") == 0)
    {
        outVar = EmptyStore;
        retVal = true;
    }
    else if(strcmp(store.c_str(), "simple") == 0)
    {
        outVar = SimpleStore;
        retVal = true;
    }
    else if(strcmp(store.c_str(), "single") == 0)
    {
        outVar = SingleStore;
        retVal = true;
    }
    else if(strcmp(store.c_str(), "multi") == 0)
    {
        outVar = MultiStore;
        retVal = true;
    }

    return retVal;
}

void
ActorInfo::updateStoreStr(ActorStoreE store, std::string &storeStr)
{
    switch(store)
    {
    case ActorInfo::EmptyStore:  storeStr = "Empty";  break;
    case ActorInfo::SimpleStore: storeStr = "Simple"; break;
    case ActorInfo::SingleStore: storeStr = "Single"; break;
    case ActorInfo::MultiStore:  storeStr = "Multi";  break;
    };
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
    static Char8 cvsid_cpp     [] = "@(#)$Id: OSGActorInfo.cpp,v 1.1 2003/10/10 13:51:07 neumannc Exp $";
    static Char8 cvsid_hpp     [] = OSGACTORINFO_HEADER_CVSID;
    static Char8 cvsid_inl     [] = OSGACTORINFO_INLINE_CVSID;
}
