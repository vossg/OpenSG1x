
#include <OSGActorWriter.h>
#include <OSGActorInfo.h>
#include <OSGStateElemInfo.h>

#include <iostream>

OSG_USING_NAMESPACE

int main(int argc, char *argv[])
{
    ActorInfo ainfo("TestActor1",                    // name
                    "ActorBase",                     // parent
                    "OSGActorBase.h",                // parentHeader
                    "",                              // parentHeaderPrefix
                    "System",                        // library
                    "",                              // headerPrefix
                    ActorInfo::SingleStore,          // enterStore
                    ActorInfo::SimpleStore,          // leaveStore
                    true,                            // acceptStateAwareIter
                    true,                            // acceptStateUnawareIter
                    false                            // useLocalIncludes
        ); 

    ainfo.addStateElem(StateElemInfo("UInt32PubOrd",              // name
                                     "UInt32",                    // type
                                     "OSGBaseTypes.h",            // typeHeader
                                     "0",                         // defaultVal
                                     StateElemInfo::PublicAccess, // access
                                     StateElemInfo::Ordered)      // ordered
        );
    ainfo.addStateElem(StateElemInfo("Real32ProtOrd", 
                                     "Real32",
                                     "OSGBaseTypes.h",
                                     "0.0",
                                     StateElemInfo::ProtectedAccess,
                                     StateElemInfo::Ordered)        );

    ainfo.addStateElem(StateElemInfo("UInt32PubUnord",
                                     "UInt32",
                                     "OSGBaseTypes.h",
                                     "0",      
                                     StateElemInfo::PublicAccess,
                                     StateElemInfo::Unordered)      );

    ainfo.addStateElem(StateElemInfo("Real32ProtUnord",
                                     "Real32",
                                     "OSGBaseTypes.h",
                                     "0.0",
                                     StateElemInfo::ProtectedAccess,
                                     StateElemInfo::Unordered)      );

                      
    ActorWriter awriter(&ainfo);

    awriter.writeCodeBaseDec(std::cout);
    awriter.writeCodeBaseImp(std::cout);
    awriter.writeCodeBaseInl(std::cout);

    return 0;
}
