
// Basic OpenSG
#include <OSGConfig.h>
#include <OSGLog.h>
#include <OSGBaseFunctions.h>

// Scenegraph components
#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGSwitch.h>
#include <OSGTransform.h>
#include <OSGSimpleGeometry.h>

// Attachments
#include <OSGSimpleAttachments.h>

// NewAction components
#include "OSGDepthFirstAction.h"
#include "OSGDepthFirstStateAction.h"
#include "OSGPriorityAction.h"

#include "OSGTestingExtendActor.h"

#define SCENE_DEPTH 2
#define X_SIZE      20.0
#define Y_SIZE      20.0
#define Z_SIZE      20.0

// This test is intended to demonstrate how one can use the new actions to
// do multiple passes over a subtree of the scenegraph
// The most interesting stuff happens in the enterGroupFunc, below main().

OSG_USING_NAMESPACE

// Forward decls.

NewActionTypes::ResultE
enterGroupFunc(NodeCorePtr pNodeCore, ActorBase::FunctorArgumentType &funcArg);
NewActionTypes::ResultE
leaveGroupFunc(NodeCorePtr pNodeCore, ActorBase::FunctorArgumentType &funcArg);

NewActionTypes::ResultE
enterTransformFunc(NodeCorePtr pNodeCore, ActorBase::FunctorArgumentType &funcArg);
NewActionTypes::ResultE
leaveTransformFunc(NodeCorePtr pNodeCore, ActorBase::FunctorArgumentType &funcArg);

NewActionTypes::ResultE
enterDefaultFunc(NodeCorePtr pNodeCore, ActorBase::FunctorArgumentType &funcArg);
NewActionTypes::ResultE
leaveDefaultFunc(NodeCorePtr pNodeCore, ActorBase::FunctorArgumentType &funcArg);

NodePtr
buildGraph(void);

int main(int argc, char *argv[])
{
    // avoid OpenSG startup noise
    osgLogP->setLogLevel(LOG_NOTICE);
    osgInit(argc, argv);
    osgLogP->setLogLevel(LOG_DEBUG);

    // Create one action of each type.
    DepthFirstAction      *pDFAction  = DepthFirstAction     ::create();
    DepthFirstStateAction *pDFSAction = DepthFirstStateAction::create();
    PriorityAction        *pPAction   = PriorityAction       ::create();

    // Actors can only be attached to one action - create one for each action.
    TestingExtendActor    *pActorDF   = TestingExtendActor   ::create();
    TestingExtendActor    *pActorDFS  = TestingExtendActor   ::create();
    TestingExtendActor    *pActorP    = TestingExtendActor   ::create();

    // register some Functors.
    TestingExtendActor::regClassEnter(
        osgTypedFunctionFunctor2CPtr<
            NewActionTypes::ResultE,          NodeCorePtr,
            ActorBase::FunctorArgumentType &              >(enterGroupFunc),
        Group::getClassType()                                               );
    TestingExtendActor::regClassLeave(
        osgTypedFunctionFunctor2CPtr<
            NewActionTypes::ResultE,           NodeCorePtr,
             ActorBase::FunctorArgumentType &              >(leaveGroupFunc),
        Group::getClassType()                                                );

    TestingExtendActor::regClassEnter(
        osgTypedFunctionFunctor2CPtr<
            NewActionTypes::ResultE,          NodeCorePtr,
            ActorBase::FunctorArgumentType &              >(enterTransformFunc),
        Transform::getClassType()                                               );
    TestingExtendActor::regClassLeave(
        osgTypedFunctionFunctor2CPtr<
            NewActionTypes::ResultE,          NodeCorePtr,
            ActorBase::FunctorArgumentType &              >(leaveTransformFunc),
        Transform::getClassType()                                               );

    TestingExtendActor::regDefaultClassEnter(
        osgTypedFunctionFunctor2CPtr<
            NewActionTypes::ResultE,          NodeCorePtr,
            ActorBase::FunctorArgumentType &              >(enterDefaultFunc));
    TestingExtendActor::regDefaultClassLeave(
        osgTypedFunctionFunctor2CPtr<
            NewActionTypes::ResultE,          NodeCorePtr,
            ActorBase::FunctorArgumentType &              >(leaveDefaultFunc));

    // add actors to the actions
    pDFAction ->addActor(pActorDF );
    pDFSAction->addActor(pActorDFS);
    pPAction  ->addActor(pActorP  );

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


//==== Group =================================================================

NewActionTypes::ResultE
enterGroupFunc(NodeCorePtr pNodeCore, ActorBase::FunctorArgumentType &funcArg)
{
    TestingExtendActor *pActor = dynamic_cast<TestingExtendActor *>(funcArg.getActor());

    SINFO << "ENTER Group: (pass: " << funcArg.getPass() << ") " 
          << (getName(pActor->getNode()) ? getName(pActor->getNode()) : "<unnamed>")
          << endLog;

    // In this example there is no real need to do any multi passing, so abuse
    // the travMask to decide if it's "required"

    if((funcArg.getPass() == 0) && (pActor->getNode()->getTravMask() & 0x07) == 0)
    {
        SINFO << "  Requesting 3 passes." << endLog;

        // !! The call this test is all about - ask the action to do 3 instead
        // of just on pass over this node. !!
        
        pActor->setNumPasses(3);
    }
    else if(funcArg.getPass() == 1)
    {
        // Just make a pointless change to the state, so it's possible
        // to trace the passes in the output

        SINFO << "  Setting state for pass 1." << endLog;

        pActor->beginEditState();
        {
            pActor->getWorldMatrix()[3][3] += 1.0;
        }
        pActor->endEditState  ();
    }
    else if(funcArg.getPass() == 2)
    {
        // Just make a pointless change to the state, so it's possible
        // to trace the passes in the output

        SINFO << "  Setting state for pass 2." << endLog;

        pActor->beginEditState();
        {
            pActor->getWorldMatrix()[3][3] += 10.0;
        }
        pActor->endEditState  ();
    }

    return NewActionTypes::Continue;
}

NewActionTypes::ResultE
leaveGroupFunc(NodeCorePtr pNodeCore, ActorBase::FunctorArgumentType &funcArg)
{
    SINFO << "LEAVE Group: (pass: " << funcArg.getPass() << ") " 
          << (getName(funcArg.getNode()) ? getName(funcArg.getNode()) : "<unnamed>")
          << endLog;

    return NewActionTypes::Continue;
}

//==== Transform =============================================================

NewActionTypes::ResultE
enterTransformFunc(NodeCorePtr pNodeCore, ActorBase::FunctorArgumentType &funcArg)
{
    TestingExtendActor *pActor = dynamic_cast<TestingExtendActor *>(funcArg.getActor());
    TransformPtr        pTrans = TransformPtr::dcast(pNodeCore);

    SINFO << "ENTER Transform: (pass: " << funcArg.getPass() << ") " 
          << (getName(pActor->getNode()) ? getName(pActor->getNode()) : "<unnamed>") 
          << endLog;

    SINFO << "Matrix before:\n"  
          << pActor->getWorldMatrix() << endLog;

    pActor->beginEditState();
    {
        pActor->getWorldMatrix().mult(pTrans->getMatrix());
    }
    pActor->endEditState();

    SINFO << "Matrix after:\n"  
          << pActor->getWorldMatrix() << endLog;

    return NewActionTypes::Continue;
}

NewActionTypes::ResultE
leaveTransformFunc(NodeCorePtr pNodeCore, ActorBase::FunctorArgumentType &funcArg)
{
    TestingExtendActor *pActor = dynamic_cast<TestingExtendActor *>(funcArg.getActor());
    TransformPtr        pTrans = TransformPtr::dcast(pNodeCore);
    Matrix              mInv;

    SINFO << "LEAVE Transform: (pass: " << funcArg.getPass() << ") " 
          << (getName(funcArg.getNode()) ? getName(funcArg.getNode()) : "<unnamed>")
          << endLog;

    pTrans->getMatrix().inverse(mInv);

    pActor->beginEditState();
    {
        pActor->getWorldMatrix().mult(mInv);
    }
    pActor->endEditState();

    return NewActionTypes::Continue;
}

//==== Default ===============================================================

NewActionTypes::ResultE
enterDefaultFunc(NodeCorePtr pNodeCore, ActorBase::FunctorArgumentType &funcArg)
{
    TestingExtendActor *pActor = dynamic_cast<TestingExtendActor *>(funcArg.getActor());

    SINFO << "ENTER default: (pass: " << funcArg.getPass() << ") " 
          << (getName(pActor->getNode()) ? getName(pActor->getNode()) : "<unnamed>")
          << endLog;

    return NewActionTypes::Continue;
}

NewActionTypes::ResultE
leaveDefaultFunc(NodeCorePtr pNodeCore, ActorBase::FunctorArgumentType &funcArg)
{
    SINFO << "LEAVE default: (pass: " << funcArg.getPass() << ") " 
          << (getName(funcArg.getNode()) ? getName(funcArg.getNode()) : "<unnamed>")
          << endLog;

    return NewActionTypes::Continue;
}

//==== Build graph ===========================================================

NodePtr
buildGraphRecurse(UInt32 depth, UInt32 maxDepth, UInt32 &count, GeometryPtr pGeo);

NodePtr
buildGraph(void)
{
    GeometryPtr pGeo = makeBoxGeo(0.08 * X_SIZE * (1.0 / (SCENE_DEPTH + 1.0)),
                                  0.08 * Y_SIZE * (1.0 / (SCENE_DEPTH + 1.0)),
                                  0.08 * Z_SIZE * (1.0 / (SCENE_DEPTH + 1.0)),
                                  1, 1, 1                                    );
    UInt32      count = 0;

    return buildGraphRecurse(0, SCENE_DEPTH, count, pGeo);
}

NodePtr
buildGraphRecurse(UInt32 depth, UInt32 maxDepth, UInt32 &count, GeometryPtr pGeo)
{
    typedef TypeTraits<UInt32> TT;

    std::string strNodeName;

    if(depth == maxDepth)
    {
        NodePtr pNodeGeo = Node::create();

        strNodeName.assign(TT::putToString(3 * depth));
        strNodeName.append(" "                       );
        strNodeName.append(TT::putToString(count++  ));
        setName           (pNodeGeo, strNodeName     );

        beginEditCP(pNodeGeo, Node::CoreFieldId);
        pNodeGeo->setCore(pGeo);
        endEditCP  (pNodeGeo, Node::CoreFieldId);

        return pNodeGeo;
    }
    else
    {
        NodePtr   pNodeGroup  = Node  ::create();
        GroupPtr  pGroup      = Group ::create();

        strNodeName.assign(TT::putToString(3 * depth));
        strNodeName.append(" "                       );
        strNodeName.append(TT::putToString(count++)  );
        setName           (pNodeGroup, strNodeName   );

        NodePtr   pNodeSwitch = Node  ::create();
        SwitchPtr pSwitch     = Switch::create();

        strNodeName.assign(TT::putToString(3 * depth + 1));
        strNodeName.append(" "                           );
        strNodeName.append(TT::putToString(count++      ));
        setName           (pNodeSwitch, strNodeName      );

        beginEditCP(pNodeGroup, Node::CoreFieldId | Node::ChildrenFieldId |
                                Node::TravMaskFieldId                      );
        pNodeGroup->setCore (pGroup     );
        pNodeGroup->addChild(pNodeSwitch);

        // about 50% of the group nodes will request multi pass.
        // This is just a hack to avoid doing it on every group core.
        if(osgrand() > 0.5)
        {
            SINFO << "Creating Multi-Pass node" << endLog;

            pNodeGroup->setTravMask(TypeTraits<UInt32>::BitsSet - 0x07);
        }

        endEditCP  (pNodeGroup, Node::CoreFieldId | Node::ChildrenFieldId |
                                Node::TravMaskFieldId                      );

        beginEditCP(pSwitch, Switch::ChoiceFieldId);
        pSwitch->getChoice() = Switch::ALL;
        endEditCP  (pSwitch, Switch::ChoiceFieldId);

        beginEditCP(pNodeSwitch, Node::CoreFieldId | Node::ChildrenFieldId);
        pNodeSwitch->setCore(pSwitch);

        for(UInt32 i = 0; i < 8; ++i)
        {
            NodePtr      pNodeTrans  = Node     ::create();
            TransformPtr pTrans      = Transform::create();

            strNodeName.assign(TT::putToString(3 * depth + 2));
            strNodeName.append(" "                           );
            strNodeName.append(TT::putToString(count++      ));
            setName           (pNodeTrans, strNodeName       );

            Vec3f       vecTrans;

            if(i & 0x01)
            {
                vecTrans[0] =  0.25 * X_SIZE * (1.0 / (depth + 1.0)) + 0.2 * (osgrand() - 0.5);
            }
            else
            {
                vecTrans[0] = -0.25 * X_SIZE * (1.0 / (depth + 1.0)) + 0.2 * (osgrand() - 0.5);
            }

            if(i & 0x02)
            {
                vecTrans[1] =  0.25 * Y_SIZE * (1.0 / (depth + 1.0)) + 0.2 * (osgrand() - 0.5);
            }
            else
            {
                vecTrans[1] = -0.25 * Y_SIZE * (1.0 / (depth + 1.0)) + 0.2 * (osgrand() - 0.5);
            }

            if(i & 0x04)
            {
                vecTrans[2] =  0.25 * Z_SIZE * (1.0 / (depth + 1.0)) + 0.2 * (osgrand() - 0.5);
            }
            else
            {
                vecTrans[2] = -0.25 * Z_SIZE * (1.0 / (depth + 1.0)) + 0.2 * (osgrand() - 0.5);
            }

            beginEditCP(pTrans, Transform::MatrixFieldId);
            pTrans->getMatrix().setTranslate(vecTrans);
            endEditCP  (pTrans, Transform::MatrixFieldId);

            beginEditCP(pNodeTrans, Node::CoreFieldId | Node::ChildrenFieldId);
            pNodeTrans->setCore (pTrans                                      );
            pNodeTrans->addChild(buildGraphRecurse(depth + 1, maxDepth, count, pGeo));
            endEditCP  (pNodeTrans, Node::CoreFieldId | Node::ChildrenFieldId);

            pNodeSwitch->addChild(pNodeTrans);
        }

        endEditCP  (pNodeSwitch, Node::CoreFieldId | Node::ChildrenFieldId);

        return pNodeGroup;
    }
}
