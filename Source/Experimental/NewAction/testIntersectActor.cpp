
#include <OSGNewAction.h>
#include <OSGPriorityIterator.h>
#include <OSGPrintNameActor.h>
#include <OSGIntersectActor.h>

#include <OSGGroup.h>
#include <OSGTransform.h>
#include <OSGSimpleAttachments.h>
#include <OSGSimpleGeometry.h>

OSG_USING_NAMESPACE

NodePtr buildTestScene (void);
NodePtr buildLargeScene(void);

int main(int argc, char *argv[])
{
    osgLogP->setLogLevel(LOG_NOTICE);

    osgInit(argc, argv);

    osgLogP->setLogLevel(LOG_DEBUG);

    NewAction        *pAction   = NewAction       ::create();
    PriorityIterator *pPIter    = PriorityIterator::create();
    PrintNameActor   *pPrintAct = PrintNameActor  ::create();
    IntersectActor   *pIntAct   = IntersectActor  ::create();

    NodePtr           scene     = buildTestScene();

    pAction->setIterator(pPIter   );

    pPrintAct->setPrintOnEnter(true);
    pPrintAct->setPrintOnLeave(true);

    pAction->addActor(pPrintAct);
    pAction->addActor(pIntAct  );

    Pnt3f pnts[] = { Pnt3f(0,0,1), Pnt3f(1,0,1), Pnt3f(2,0,1),
                     Pnt3f(3,0,1), 
                     Pnt3f(-Inf, -Inf, -Inf) };

    Vec3f dirs[] = { Vec3f(0,0,-1), Vec3f(0,0,-1), Vec3f(0,0,-1), 
                     Vec3f(0,0,-1),
                     Vec3f(-Inf, -Inf, -Inf) };

   IntersectActor::regDefaultClassEnter(
       osgTypedFunctionFunctor2CPtrRef<NewActionBase::ResultE,
                                       NodeCorePtr           ,
                                       ActorBase            *>
                                      (&IntersectActor::defaultFunctor));
    
    for(int i = 0; pnts[i][0] != -Inf; ++i)
    {
        pIntAct->setLine   (Line(pnts[i], dirs[i]));
        pIntAct->setMaxDist(Inf                   );

        pAction->apply(scene);

        SLOG << "Line: " << pIntAct->getLine().getPosition ()
             << " dir: " << pIntAct->getLine().getDirection()
             << " hit: " << pIntAct->getHit ()
             << "\n";

        if(pIntAct->getHit() == true)
        {
            PLOG << " object: "   << pIntAct->getHitObject()
                 << " tri: "      << pIntAct->getHitTriangle()
                 << " HitDist: "  << pIntAct->getHitDist()
                 << " HitPoint: " 
                 << pnts[i] + (pIntAct->getHitDist() * dirs[i]);
        }

        PLOG << endLog;
    }

    return 0;
}


NodePtr buildTestScene(void)
{
    NodePtr  pNode0     = Node ::create();
    GroupPtr pNode0Core = Group::create();

    setName(pNode0,     "Node_0"             );
    setName(pNode0Core, "Node_0_Core (Group)");

    NodePtr  pNode01     = Node ::create();
    GroupPtr pNodeCore01 = Group::create();

    setName(pNode01,     "Node_0_1"             );
    setName(pNodeCore01, "Node_0_1_Core (Group)");
    
    NodePtr      pNode02     = Node     ::create();
    TransformPtr pNodeCore02 = Transform::create();

    setName(pNode02,     "Node_0_2"                 );
    setName(pNodeCore02, "Node_0_2_Core (Transform)");

    NodePtr pNode013 = makePlane(2,2,2,2);

    setName(pNode013,            "Node_0_1_3"             );
    setName(pNode013->getCore(), "Node_0_1_3_Core (Plane)");

    NodePtr pNode024 = makePlane(2,2,2,2);

    setName(pNode024,            "Node_0_2_4"             );
    setName(pNode024->getCore(), "Node_0_2_4_Core (Plane)");

    beginEditCP(pNodeCore02);
    {
        pNodeCore02->getMatrix().setTranslate(2,0,0);
    }
    endEditCP(pNodeCore02);

    beginEditCP(pNode02);
    {
        pNode02->setCore (pNodeCore02);
        pNode02->addChild(pNode024   );
    }
    endEditCP(pNode02);

    beginEditCP(pNode01);
    {
        pNode01->setCore (pNodeCore01);
        pNode01->addChild(pNode013   );
    }
    endEditCP(pNode01);

    beginEditCP(pNode0);
    {
        pNode0->setCore (pNode0Core);
        pNode0->addChild(pNode01   );
        pNode0->addChild(pNode02   );
    }
    endEditCP(pNode0);

    return pNode0;
}

NodePtr
buildLargeScene(UInt32 xSize, UInt32 ySize, UInt32 zSize)
{
    NodePtr  pRoot     = Node ::create();
    GroupPtr pRootCore = Group::create();

    beginEditCP(pRoot, Node::CoreFieldId);
    {
        pRoot->setCore(pRootCore);
    }
    endEditCP(pRoot, Node::CoreFieldId);

    for(UInt32 x = 0; x < xSize; ++x)
    {
        for(UInt32 y = 0; y < ySize; ++y)
        {
            for(UInt32 z = 0; z < zSize; ++z)
            {
                NodePtr      pTrans     = Node     ::create();
                TransformPtr pTransCore = Transform::create();
                NodePtr      pGeo;
                
                if( (x + y + z) % 2 == 0)
                {
                    pGeo = makeBox(0.5, 0.5, 0.5, 1, 1, 1);
                }
                else
                {
                    pGeo = makeSphere(2, 0.5);
                }

                beginEditCP(pTransCore, Transform::MatrixFieldId);
                {
                    pTransCore->getMatrix().setTranslate(x, y, z);
                }
                endEditCP(pTransCore, Transform::MatrixFieldId);

                beginEditCP(pTrans, Node::CoreFieldId | Node::ChildrenFieldId);
                {
                    pTrans->setCore (pTransCore);
                    pTrans->addChild(pGeo      );
                }
                endEditCP(pTrans, Node::CoreFieldId | Node::ChildrenFieldId);

                beginEditCP(pRoot, Node::ChildrenFieldId);
                {
                    pRoot->addChild(pTrans);
                }
                endEditCP(pRoot, Node::ChildrenFieldId);
            }
        }
    }

    return pRoot;
}
