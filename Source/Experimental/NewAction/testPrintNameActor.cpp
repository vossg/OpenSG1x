
// Basic OpenSG
#include <OSGConfig.h>
#include <OSGLog.h>

// Scene loader
#include <OSGSceneFileHandler.h>

// Scenegraph components
#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGSwitch.h>
#include <OSGTransform.h>
#include <OSGSimpleGeometry.h>

#include "OSGDepthFirstAction.h"
#include "OSGDepthFirstStateAction.h"
#include "OSGPriorityAction.h"

#include "OSGPrintNameActor.h"


OSG_USING_NAMESPACE


NewActionTypes::ResultE
enterFunc(NodeCorePtr pNodeCore, ActorBase *pActor);

NewActionTypes::ResultE
leaveFunc(NodeCorePtr pNodeCore, ActorBase *pActor);

NodePtr
buildGraph(void);

int main(int argc, char *argv[])
{
    // avoid OpenSG startup noise
    osgLogP->setLogLevel(LOG_NOTICE);
    osgInit(argc, argv);
    osgLogP->setLogLevel(LOG_DEBUG);

    PrintNameActor   *pActorDF1  = PrintNameActor::create();
    PrintNameActor   *pActorDFS1 = PrintNameActor::create();
    PrintNameActor   *pActorP1   = PrintNameActor::create();

    PrintNameActor   *pActorDF2  = PrintNameActor::create();
    PrintNameActor   *pActorDFS2 = PrintNameActor::create();
    PrintNameActor   *pActorP2   = PrintNameActor::create();

    DepthFirstAction      *pDFAction  = DepthFirstAction     ::create();
    DepthFirstStateAction *pDFSAction = DepthFirstStateAction::create();
    PriorityAction        *pPAction   = PriorityAction       ::create();

    PrintNameActor::regClassEnter(
        osgTypedFunctionFunctor2CPtr<NewActionTypes::ResultE,
                                     NodeCorePtr,
                                     ActorBase *             >(enterFunc));
    PrintNameActor::regClassLeave(
        osgTypedFunctionFunctor2CPtr<NewActionTypes::ResultE,
                                     NodeCorePtr,
                                     ActorBase *             >(leaveFunc));

    pDFAction->addActor(pActorDF1);
    pDFAction->addActor(pActorDF2);

    pDFSAction->addActor(pActorDFS1);

    pPAction ->addActor(pActorP1 );
    pPAction ->addActor(pActorP2 );

    SLOG << "Building scene graph:" << endLog;
    NodePtr pRoot = buildGraph();

    //SLOG << "Running DepthFirstAction:" << endLog;
    //pDFAction->apply(pRoot);

    SLOG << "Running DepthFirstStateAction:" << endLog;
    pDFSAction->apply(pRoot);

    //SLOG << "Running PriorityAction:" << endLog;
    //pPAction->apply(pRoot);

    // avoid OpenSG shutdown noise.
    osgLogP->setLogLevel(LOG_NOTICE);

    return 0;
}

NewActionTypes::ResultE
enterFunc(NodeCorePtr pNodeCore, ActorBase *pActor)
{
    PrintNameActor *pPNActor  = dynamic_cast<PrintNameActor *>(pActor);
    UInt32          treeLevel = pPNActor->getTreeLevel();

//    SLOG << "pre-enter tree level: " << pPNActor->getTreeLevel()
//         << " num nodes: "  << pPNActor->getNumNodes () << endLog;

    SLOG << "";

    for(UInt32 i = 0; i < treeLevel; ++i)
    {
        PLOG << "  ";
    }

    PLOG << "ENTER ("   << treeLevel << ") "
         << " Node: "   << pPNActor ->getNode()
         << " ["        << pNodeCore->getType().getCName() << "]";

    if(pPNActor->getParentNode() != NullFC)
    {
        PLOG << " Parent: " << pPNActor ->getParentNode()
             << " ["        << pPNActor ->getParentNode()->getCore()->getType().getCName() << "]"
             << endLog;
    }
    else
    {
        PLOG << " Parent: <no parent>" << endLog;
    }

    pPNActor->beginEditState();
    pPNActor->getTreeLevel (                   ) += 1;
    pPNActor->getNumNodes  (                   ) += 1;
    pPNActor->setParentNode(pPNActor->getNode());
    pPNActor->endEditState  ();

//    SLOG << "post-enter tree level: " << pPNActor->getTreeLevel()
//         << " num nodes: "  << pPNActor->getNumNodes () << endLog;

    return NewActionTypes::Continue;
}

NewActionTypes::ResultE
leaveFunc(NodeCorePtr pNodeCore, ActorBase *pActor)
{
    PrintNameActor *pPNActor = dynamic_cast<PrintNameActor *>(pActor);

    pPNActor->beginEditState();
    pPNActor->getTreeLevel() -= 1;
    pPNActor->endEditState  ();

    UInt32 treeLevel = pPNActor->getTreeLevel();

    SLOG << "";

    for(UInt32 i = 0; i < treeLevel; ++i)
    {
        PLOG << "  ";
    }

    PLOG << "LEAVE ("   << treeLevel << ") "
         << " Node: "   << pPNActor ->getNode()
         << " ["        << pNodeCore->getType().getCName() << "]"
         << endLog;

    return NewActionTypes::Continue;
}

NodePtr
buildGraphRecurse(UInt32 depth, UInt32 maxDepth);

NodePtr
buildGraph(void)
{
    //return SceneFileHandler::the().read("../../../Tutorials/Data/tie.wrl");

    return buildGraphRecurse(0, 1);
}

NodePtr
buildGraphRecurse(UInt32 depth, UInt32 maxDepth)
{
#define X_SIZE 1.0
#define Y_SIZE 1.0
#define Z_SIZE 1.0

    if(depth == maxDepth)
    {
        NodePtr pNodeGeo = makeBox(0.125 * X_SIZE * (1.0 / (depth + 1.0)),
                                   0.125 * Y_SIZE * (1.0 / (depth + 1.0)),
                                   0.125 * Z_SIZE * (1.0 / (depth + 1.0)),
                                   1, 1, 1                                );

        return pNodeGeo;
    }
    else
    {
        NodePtr   pNodeGroup  = Node  ::create();
        GroupPtr  pGroup      = Group ::create();

        beginEditCP(pNodeGroup, Node::CoreFieldId | Node::ChildrenFieldId);
        pNodeGroup->setCore(pGroup);

        for(UInt32 i = 0; i < 8; ++i)
        {
            NodePtr      pNodeSwitch = Node     ::create();
            SwitchPtr    pSwitch     = Switch   ::create();

            NodePtr      pNodeTrans  = Node     ::create();
            TransformPtr pTrans      = Transform::create();

            Vec3f       vecTrans;

            if(i & 0x01)
            {
                vecTrans[0] =  0.25 * X_SIZE * (1.0 / (depth + 1.0));
            }
            else
            {
                vecTrans[0] = -0.25 * X_SIZE * (1.0 / (depth + 1.0));
            }

            if(i & 0x02)
            {
                vecTrans[1] =  0.25 * Y_SIZE * (1.0 / (depth + 1.0));
            }
            else
            {
                vecTrans[1] = -0.25 * Y_SIZE * (1.0 / (depth + 1.0));
            }

            if(i & 0x04)
            {
                vecTrans[2] =  0.25 * Z_SIZE * (1.0 / (depth + 1.0));
            }
            else
            {
                vecTrans[2] = -0.25 * Z_SIZE * (1.0 / (depth + 1.0));
            }

            beginEditCP(pSwitch, Switch::ChoiceFieldId);
            pSwitch->getChoice() = Switch::ALL;
            endEditCP  (pSwitch, Switch::ChoiceFieldId);

            beginEditCP(pNodeSwitch, Node::CoreFieldId | Node::ChildrenFieldId);
            pNodeSwitch->setCore (pSwitch   );
            pNodeSwitch->addChild(pNodeTrans);
            endEditCP  (pNodeSwitch, Node::CoreFieldId | Node::ChildrenFieldId);

            beginEditCP(pTrans, Transform::MatrixFieldId);
            pTrans->getMatrix().setTranslate(vecTrans);
            endEditCP  (pTrans, Transform::MatrixFieldId);

            beginEditCP(pNodeTrans, Node::CoreFieldId | Node::ChildrenFieldId);
            pNodeTrans->setCore (pTrans                                );
            pNodeTrans->addChild(buildGraphRecurse(depth + 1, maxDepth));
            endEditCP  (pNodeTrans, Node::CoreFieldId | Node::ChildrenFieldId);

            pNodeGroup->addChild(pNodeSwitch);
        }

        endEditCP  (pNodeGroup, Node::CoreFieldId | Node::ChildrenFieldId);

        return pNodeGroup;
    }

#undef X_SIZE
#undef Y_SIZE
#undef Z_SIZE
}
