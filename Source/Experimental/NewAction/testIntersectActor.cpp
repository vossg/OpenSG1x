
// Basic OpenSG
#include <OSGConfig.h>
#include <OSGBaseTypes.h>
#include <OSGLog.h>

// New Action Stuff
#include <OSGDepthFirstAction.h>
#include <OSGDepthFirstStateAction.h>
#include <OSGPriorityAction.h>

#include <OSGIntersectActor.h>
#include <OSGTriangleIterator.h>

// Old Action Stuff
#include <OSGAction.h>
#include <OSGIntersectAction.h>

// Scenegraph components
#include <OSGGroup.h>
#include <OSGSwitch.h>
#include <OSGTransform.h>
#include <OSGSimpleGeometry.h>
#include <OSGSimpleMaterial.h>
#include <OSGSimpleAttachments.h>

// Rendering Stuff
#include <OSGGLUT.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>

// Misc
#include <OSGStatCollector.h>
#include <OSGTime.h>

// STL
#include <vector>

#define SCENE_DEPTH 4
#define RAY_COUNT   500
#define X_SIZE      20.0
#define Y_SIZE      20.0
#define Z_SIZE      20.0


OSG_USING_NAMESPACE

struct IntersectResult
{
    bool    _hit;
    NodePtr _pObj;
    Int32   _tri;
    Real32  _dist;

    Time    _time;
};

SimpleSceneManager   *mgr;
GeoPositions3fPtr     pPoints;

std::vector<Line>            testRays;

std::vector<IntersectResult> resultsDF;
std::vector<IntersectResult> resultsDFS;
std::vector<IntersectResult> resultsP;
std::vector<IntersectResult> resultsO;

UInt32 uiNumRays    = RAY_COUNT;
UInt32 uiCurrentRay = 0;
Real32 rayLength    = 10.0;


int  setupGLUT(int *argc, char *argv[]);

NodePtr buildGraph(void                                     );
void    createRays(UInt32 uiNumRays, std::vector<Line> &rays);

// Intersect callbacks

NewActionTypes::ResultE
enterDefault(NodeCorePtr pNodeCore, ActorBase::FunctorArgumentType &funcArg);

// MAIN

int main(int argc, char *argv[])
{
    osgLogP->setLogLevel(LOG_NOTICE);

    osgInit(argc, argv);

    int winid = setupGLUT(&argc, argv);

    // create a GLUT window
    GLUTWindowPtr gwin = GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();

    osgLogP->setLogLevel(LOG_DEBUG);

    // build the test scene
    NodePtr  pRoot      = Node ::create();
    GroupPtr pRootCore  = Group::create();
    NodePtr  pRayGeo    = Node ::create();
    NodePtr  pScene     = buildGraph();
    GroupPtr pSceneCore = Group::create();

    Time     tStart;
    Time     tStop;
    Time     tDFTotal  = 0.0;
    Time     tDFSTotal = 0.0;
    Time     tPTotal   = 0.0;
    Time     tOTotal   = 0.0;

    StatCollector statP;
    StatCollector statDF;
    StatCollector statDFS;

    beginEditCP(pRoot, Node::CoreFieldId | Node::ChildrenFieldId);
    pRoot->setCore (pRootCore   );
    pRoot->addChild(pScene      );
    pRoot->addChild(pRayGeo     );
    endEditCP  (pRoot, Node::CoreFieldId | Node::ChildrenFieldId);

    createRays(uiNumRays, testRays);

    // build the geometry to visualize the rays
    pPoints = GeoPositions3f::create();
    beginEditCP(pPoints);
    pPoints->addValue(Pnt3f(0.0, 0.0, 0.0));
    pPoints->addValue(Pnt3f(0.0, 0.0, 0.0));
    pPoints->addValue(Pnt3f(0.0, 0.0, 0.0));
    pPoints->addValue(Pnt3f(0.0, 0.0, 0.0));
    pPoints->addValue(Pnt3f(0.0, 0.0, 0.0));
    endEditCP  (pPoints);

    GeoIndicesUI32Ptr pIndices = GeoIndicesUI32::create();
    beginEditCP(pIndices);
    pIndices->addValue(0);
    pIndices->addValue(1);
    pIndices->addValue(2);
    pIndices->addValue(3);
    pIndices->addValue(4);
    endEditCP  (pIndices);

    GeoPLengthsPtr pLengths = GeoPLengthsUI32::create();
    beginEditCP(pLengths);
    pLengths->addValue(2);
    pLengths->addValue(3);
    endEditCP  (pLengths);

    GeoPTypesPtr pTypes = GeoPTypesUI8::create();
    beginEditCP(pTypes);
    pTypes->addValue(GL_LINES    );
    pTypes->addValue(GL_TRIANGLES);
    endEditCP  (pTypes);

    GeoColors3fPtr pColors = GeoColors3f::create();
    beginEditCP(pColors);
    pColors->addValue(Color3f(1.0, 1.0, 1.0));
    pColors->addValue(Color3f(1.0, 0.0, 0.0));
    pColors->addValue(Color3f(1.0, 0.0, 0.0));
    pColors->addValue(Color3f(1.0, 0.0, 0.0));
    pColors->addValue(Color3f(1.0, 0.0, 0.0));
    endEditCP  (pColors);

    SimpleMaterialPtr pMaterial = SimpleMaterial::create();
    beginEditCP(pMaterial);
    pMaterial->setLit(false);
    endEditCP  (pMaterial);

    GeometryPtr pRayGeoCore = Geometry::create();
    beginEditCP(pRayGeoCore);
    pRayGeoCore->setPositions(pPoints  );
    pRayGeoCore->setIndices  (pIndices );
    pRayGeoCore->setLengths  (pLengths );
    pRayGeoCore->setTypes    (pTypes   );
    pRayGeoCore->setColors   (pColors  );
    pRayGeoCore->setMaterial (pMaterial);
    endEditCP  (pRayGeoCore);

    beginEditCP(pRayGeo, Node::CoreFieldId);
    pRayGeo->setCore(pRayGeoCore);
    endEditCP  (pRayGeo, Node::CoreFieldId);

    IntersectActor::regDefaultClassEnter(
        osgTypedFunctionFunctor2CPtr<
            NewActionTypes::ResultE,          NodeCorePtr,
            ActorBase::FunctorArgumentType &              >(enterDefault));


    NewActionBase  *pDFAction  = DepthFirstAction     ::create();
    NewActionBase  *pDFSAction = DepthFirstStateAction::create();
    NewActionBase  *pPAction   = PriorityAction       ::create();
    IntersectActor *pIActorDF  = IntersectActor       ::create();
    IntersectActor *pIActorDFS = IntersectActor       ::create();
    IntersectActor *pIActorP   = IntersectActor       ::create();

    pDFAction ->setStatistics(&statDF );
    pDFSAction->setStatistics(&statDFS);
    pPAction  ->setStatistics(&statP  );

    // IntersectActor with DFS-Action does not need leave calls
    pIActorDFS->setLeaveNodeFlag(false);

    pDFAction ->addActor(pIActorDF );
    pDFSAction->addActor(pIActorDFS);
    pPAction  ->addActor(pIActorP  );

    // create old action
    IntersectAction *pIntAction = IntersectAction ::create();

    // make sure bv are up to date
    pScene->updateVolume();


    SINFO << "-=< Intersect >=-" << endLog;

    std::vector<Line>::iterator itRays  = testRays.begin();
    std::vector<Line>::iterator endRays = testRays.end  ();

    for(; itRays != endRays; ++itRays)
    {
        // DepthFirst

        tStart = getSystemTime();

        pIActorDF->setRay        (*itRays);
        pIActorDF->setMaxDistance(10000.0);
        pIActorDF->reset         (       );

        pDFAction->apply(pScene);

        tStop            =  getSystemTime();
        tDFTotal += (tStop - tStart);

        if(pIActorDF->getHit() == true)
        {
            IntersectResult result;

            result._hit  = true;
            result._pObj = pIActorDF->getHitObject       ();
            result._tri  = pIActorDF->getHitTriangleIndex();
            result._dist = pIActorDF->getHitDistance     ();
            result._time = (tStop - tStart);

            resultsDF.push_back(result);
        }
        else
        {
            IntersectResult result;

            result._hit  = false;
            result._pObj = NullFC;
            result._tri  = -1;
            result._dist = 0.0;
            result._time = (tStop - tStart);

            resultsDF.push_back(result);
        }

        std::string strStatDF;
        statDF.putToString(strStatDF);

        //SINFO << "stat DF:  " << strStatDF << endLog;

        // Depth First State

        tStart = getSystemTime();

        pIActorDFS->setRay        (*itRays);
        pIActorDFS->setMaxDistance(10000.0);
        pIActorDFS->reset         (       );

        pDFSAction->apply(pScene);

        tStop     =  getSystemTime();
        tDFSTotal += (tStop - tStart);

        if(pIActorDFS->getHit() == true)
        {
            IntersectResult result;

            result._hit  = true;
            result._pObj = pIActorDFS->getHitObject       ();
            result._tri  = pIActorDFS->getHitTriangleIndex();
            result._dist = pIActorDFS->getHitDistance     ();
            result._time = (tStop - tStart);

            resultsDFS.push_back(result);
        }
        else
        {
            IntersectResult result;

            result._hit  = false;
            result._pObj = NullFC;
            result._tri  = -1;
            result._dist = 0.0;
            result._time = (tStop - tStart);

            resultsDFS.push_back(result);
        }

        std::string strStatDFS;
        statDFS.putToString(strStatDFS);

        //SINFO << "stat DFS: " << strStatDFS << endLog;

        // Priority

        tStart = getSystemTime();

        pIActorP->setRay        (*itRays);
        pIActorP->setMaxDistance(10000.0);
        pIActorP->reset         (       );

        pPAction->apply(pScene);

        tStop          =  getSystemTime();
        tPTotal += (tStop - tStart);

        if(pIActorP->getHit() == true)
        {
            IntersectResult result;

            result._hit  = true;
            result._pObj = pIActorP->getHitObject       ();
            result._tri  = pIActorP->getHitTriangleIndex();
            result._dist = pIActorP->getHitDistance     ();
            result._time = (tStop - tStart);

            resultsP.push_back(result);
        }
        else
        {
            IntersectResult result;

            result._hit  = false;
            result._pObj = NullFC;
            result._tri  = -1;
            result._dist = 0.0;
            result._time = (tStop - tStart);

            resultsP.push_back(result);
        }

        std::string strStatP;
        statP.putToString(strStatP);

        //SINFO << "stat P:   " << strStatP << endLog;

        // Old

        tStart = getSystemTime();

        pIntAction->setLine(*itRays, 100000);
        pIntAction->apply  (pScene         );

        tStop     =  getSystemTime();
        tOTotal += (tStop - tStart);

        if(pIntAction->didHit() == true)
        {
            IntersectResult result;

            result._hit  = true;
            result._pObj = pIntAction->getHitObject  ();
            result._tri  = pIntAction->getHitTriangle();
            result._dist = pIntAction->getHitT       ();
            result._time = (tStop - tStart);

            resultsO.push_back(result);
        }
        else
        {
            IntersectResult result;

            result._hit  = false;
            result._pObj = NullFC;
            result._tri  = -1;
            result._dist = 0.0;
            result._time = (tStop - tStart);

            resultsO.push_back(result);
        }
    }

    UInt32 DFwins      = 0;
    UInt32 DFwinsHit   = 0;
    UInt32 DFwinsMiss  = 0;

    UInt32 DFSwins     = 0;
    UInt32 DFSwinsHit  = 0;
    UInt32 DFSwinsMiss = 0;

    UInt32 Pwins       = 0;
    UInt32 PwinsHit    = 0;
    UInt32 PwinsMiss   = 0;

    UInt32 Owins       = 0;
    UInt32 OwinsHit    = 0;
    UInt32 OwinsMiss   = 0;

    UInt32 failCount   = 0;
    UInt32 passCount   = 0;
    UInt32 hitCount    = 0;
    UInt32 missCount   = 0;

    for(UInt32 i = 0; i < uiNumRays; ++i)
    {
        bool DFfastest  = ((resultsDF [i]._time <= resultsDFS[i]._time) &&
                           (resultsDF [i]._time <= resultsP  [i]._time) &&
                           (resultsDF [i]._time <= resultsO  [i]._time)   );
        bool DFSfastest = ((resultsDFS[i]._time <= resultsDF [i]._time) &&
                           (resultsDFS[i]._time <= resultsP  [i]._time) &&
                           (resultsDFS[i]._time <= resultsO  [i]._time)   );
        bool Pfastest   = ((resultsP  [i]._time <= resultsDF [i]._time) &&
                           (resultsP  [i]._time <= resultsDFS[i]._time) &&
                           (resultsP  [i]._time <= resultsO  [i]._time)   );
        bool Ofastest   = ((resultsO  [i]._time <= resultsDF [i]._time) &&
                           (resultsO  [i]._time <= resultsDFS[i]._time) &&
                           (resultsO  [i]._time <= resultsP  [i]._time)   );

        if((resultsDF [i]._hit == resultsDFS[i]._hit) &&
           (resultsDFS[i]._hit == resultsP  [i]._hit) &&
           (resultsP  [i]._hit == resultsO  [i]._hit)    )
        {
            if((osgabs(resultsDF [i]._dist - resultsDFS[i]._dist) >= 0.001) ||
               (osgabs(resultsDFS[i]._dist - resultsP  [i]._dist) >= 0.001) ||
               (osgabs(resultsP  [i]._dist - resultsO  [i]._dist) >= 0.001) ||
               (osgabs(resultsO  [i]._dist - resultsDF [i]._dist) >= 0.001)   )
            {
                ++failCount;

                SINFO << "FAIL: df: " << resultsDF [i]._dist
                      << " dfs: "     << resultsDFS[i]._dist
                      << " p: "       << resultsP  [i]._dist
                      << " o: "       << resultsO  [i]._dist
                      << endLog;
                SINFO << "FAIL: df: " << resultsDF [i]._tri
                      << " dfs: "     << resultsDFS[i]._tri
                      << " p: "       << resultsP  [i]._tri
                      << " o: "       << resultsO  [i]._tri
                      << endLog;
            }
            else
            {
                ++passCount;
            }

            if(resultsDF[i]._hit == true)
            {
                ++hitCount;

                DFwinsHit  = DFfastest  ? DFwinsHit  + 1 : DFwinsHit;
                DFSwinsHit = DFSfastest ? DFSwinsHit + 1 : DFSwinsHit;
                PwinsHit   = Pfastest   ? PwinsHit   + 1 : PwinsHit;
                OwinsHit   = Ofastest   ? OwinsHit   + 1 : OwinsHit;
            }
            else
            {
                ++missCount;

                DFwinsMiss  = DFfastest  ? DFwinsMiss  + 1 : DFwinsMiss;
                DFSwinsMiss = DFSfastest ? DFSwinsMiss + 1 : DFSwinsMiss;
                PwinsMiss   = Pfastest   ? PwinsMiss   + 1 : PwinsMiss;
                OwinsMiss   = Ofastest   ? OwinsMiss   + 1 : OwinsMiss;
            }

            DFwins  = DFfastest  ? DFwins  + 1 : DFwins;
            DFSwins = DFSfastest ? DFSwins + 1 : DFSwins;
            Pwins   = Pfastest   ? Pwins   + 1 : Pwins;
            Owins   = Ofastest   ? Owins   + 1 : Owins;
        }
        else
        {
            ++failCount;
        }

        //SINFO << i << " \t" << (DFfastest  ? "D ->" : "    ") << " hit: " << resultsDF [i]._hit << " time: " << resultsDF [i]._time << endLog;
        //SINFO << "  \t"     << (DFSfastest ? "S ->" : "    ") << " hit: " << resultsDFS[i]._hit << " time: " << resultsDFS[i]._time << endLog;
        //SINFO << "  \t"     << (Pfastest   ? "P ->" : "    ") << " hit: " << resultsP  [i]._hit << " time: " << resultsP  [i]._time << endLog;
        //SINFO << "  \t"     << (Ofastest   ? "O ->" : "    ") << " hit: " << resultsO  [i]._hit << " time: " << resultsO  [i]._time << endLog;
    }

    SINFO << " df total:  "    << tDFTotal   << (tDFTotal < tDFSTotal && tDFTotal < tPTotal && tDFTotal < tOTotal ? " *" : "  ") 
          << " wins: "         << DFwins     << " (" << (static_cast<Real32>(DFwins)     / static_cast<Real32>(passCount)) * 100.0 << "%)\t"
          << " wins on hit: "  << DFwinsHit  << " (" << (static_cast<Real32>(DFwinsHit)  / static_cast<Real32>(hitCount )) * 100.0 << "%)\t"
          << " wins on miss: " << DFwinsMiss << " (" << (static_cast<Real32>(DFwinsMiss) / static_cast<Real32>(missCount)) * 100.0 << "%)"
          << endLog;

    SINFO << " dfs total: "    << tDFSTotal  << (tDFSTotal < tDFTotal && tDFSTotal < tPTotal && tDFSTotal < tOTotal ? " *" : "  ") 
          << " wins: "         << DFSwins     << " (" << (static_cast<Real32>(DFSwins)     / static_cast<Real32>(passCount)) * 100.0 << "%)\t"
          << " wins on hit: "  << DFSwinsHit  << " (" << (static_cast<Real32>(DFSwinsHit)  / static_cast<Real32>(hitCount )) * 100.0 << "%)\t"
          << " wins on miss: " << DFSwinsMiss << " (" << (static_cast<Real32>(DFSwinsMiss) / static_cast<Real32>(missCount)) * 100.0 << "%)"
          << endLog;

    SINFO << " p total:   "    << tPTotal   << (tPTotal < tDFTotal && tPTotal < tDFSTotal && tPTotal < tOTotal ? " *" : "  ") 
          << " wins: "         << Pwins     << " (" << (static_cast<Real32>(Pwins)     / static_cast<Real32>(passCount)) * 100.0 << "%)\t"
          << " wins on hit: "  << PwinsHit  << " (" << (static_cast<Real32>(PwinsHit)  / static_cast<Real32>(hitCount )) * 100.0 << "%)\t"
          << " wins on miss: " << PwinsMiss << " (" << (static_cast<Real32>(PwinsMiss) / static_cast<Real32>(missCount)) * 100.0 << "%)"
          << endLog;

    SINFO << " o total:   "    << tOTotal   << (tOTotal < tDFTotal && tOTotal < tDFSTotal && tOTotal < tPTotal ? " *" : "  ") 
          << " wins: "         << Owins     << " (" << (static_cast<Real32>(Owins)     / static_cast<Real32>(passCount)) * 100.0 << "%)\t"
          << " wins on hit: "  << OwinsHit  << " (" << (static_cast<Real32>(OwinsHit)  / static_cast<Real32>(hitCount )) * 100.0 << "%)\t"
          << " wins on miss: " << OwinsMiss << " (" << (static_cast<Real32>(OwinsMiss) / static_cast<Real32>(missCount)) * 100.0 << "%)"
          << endLog;

    SINFO << "pass: " << passCount << " fail: " << failCount
          << " hit: " << hitCount  << " miss: " << missCount << endLog;

    osgLogP->setLogLevel(LOG_NOTICE);

#if 0
    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (pRoot);

    // show the whole scene
    mgr->showAll();

    // GLUT main loop
    glutMainLoop();
#endif


    return 0;
}

NodePtr
buildGraphRecurse(UInt32 depth, UInt32 maxDepth, GeometryPtr pGeo);

NodePtr
buildGraph(void)
{
    GeometryPtr pGeo = makeBoxGeo(0.08 * X_SIZE * (1.0 / (SCENE_DEPTH + 1.0)),
                                  0.08 * Y_SIZE * (1.0 / (SCENE_DEPTH + 1.0)),
                                  0.08 * Z_SIZE * (1.0 / (SCENE_DEPTH + 1.0)),
                                  1, 1, 1                                    );

    return buildGraphRecurse(0, SCENE_DEPTH, pGeo);
}

NodePtr
buildGraphRecurse(UInt32 depth, UInt32 maxDepth, GeometryPtr pGeo)
{
    if(depth == maxDepth)
    {
        NodePtr pNodeGeo = Node::create();

        beginEditCP(pNodeGeo, Node::CoreFieldId);
        pNodeGeo->setCore(pGeo);
        endEditCP  (pNodeGeo, Node::CoreFieldId);

        return pNodeGeo;
    }
    else
    {
        NodePtr   pNodeGroup  = Node  ::create();
        GroupPtr  pGroup      = Group ::create();

        NodePtr   pNodeSwitch = Node  ::create();
        SwitchPtr pSwitch     = Switch::create();

        beginEditCP(pNodeGroup, Node::CoreFieldId | Node::ChildrenFieldId);
        pNodeGroup->setCore (pGroup     );
        pNodeGroup->addChild(pNodeSwitch);
        endEditCP  (pNodeGroup, Node::CoreFieldId | Node::ChildrenFieldId);

        beginEditCP(pSwitch, Switch::ChoiceFieldId);
        pSwitch->getChoice() = Switch::ALL;
        endEditCP  (pSwitch, Switch::ChoiceFieldId);

        beginEditCP(pNodeSwitch, Node::CoreFieldId | Node::ChildrenFieldId);
        pNodeSwitch->setCore(pSwitch);

        for(UInt32 i = 0; i < 8; ++i)
        {
            NodePtr      pNodeTrans  = Node     ::create();
            TransformPtr pTrans      = Transform::create();

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
            pNodeTrans->addChild(buildGraphRecurse(depth + 1, maxDepth, pGeo));
            endEditCP  (pNodeTrans, Node::CoreFieldId | Node::ChildrenFieldId);

            pNodeSwitch->addChild(pNodeTrans);
        }

        endEditCP  (pNodeSwitch, Node::CoreFieldId | Node::ChildrenFieldId);

        return pNodeGroup;
    }
}

void
createRays(UInt32 uiNumRays, std::vector<Line> &rays)
{
    SINFO << "Creating " << uiNumRays << " rays...";

    rays.clear  (         );
    rays.reserve(uiNumRays);

    for(UInt32 i = 0; i < uiNumRays; ++i)
    {
        Real32 xPos = (osgrand() - 0.5) * X_SIZE * 2.5;
        Real32 yPos = (osgrand() - 0.5) * Y_SIZE * 2.5;
        Real32 zPos = (osgrand() - 0.5) * Z_SIZE * 2.5;

        Real32 xDir = (osgrand() - 0.5);
        Real32 yDir = (osgrand() - 0.5);
        Real32 zDir = (osgrand() - 0.5);

        if((xPos * xDir) > 0)
            xDir *= -1.0;

        if((yPos * yDir) > 0)
            yDir *= -1.0;

        if((zPos * zDir) > 0)
            zDir *= -1.0;

        rays.push_back(Line(Pnt3f(xPos, yPos, zPos),
                            Vec3f(xDir, yDir, zDir) ));
    }

    PINFO << "done." << endLog;
}

// This is the default operation of the IntersectActor
NewActionTypes::ResultE
enterDefault(NodeCorePtr pNodeCore, ActorBase::FunctorArgumentType &funcArg)
{
    IntersectActor *pIA = dynamic_cast<IntersectActor *>(funcArg.getActor());

    pIA->setupChildrenPriorities();

    return NewActionTypes::Continue;
}

void
updateRayGeo(void)
{
    Line            &ray = testRays[uiCurrentRay];
    IntersectResult &res = resultsP[uiCurrentRay];

    Pnt3f startPnt = ray.getPosition();
    Pnt3f endPnt   = startPnt + (rayLength * ray.getDirection());

    beginEditCP(pPoints);
    pPoints->setValue(startPnt, 0);
    pPoints->setValue(endPnt,   1);

    if(res._hit == true)
    {
        TriangleIterator triIt(res._pObj);
        Matrix           matrix;
        Pnt3f            point;

        triIt.seek(res._tri);
        res._pObj->getToWorld(matrix);

        point = triIt.getPosition(0);
        matrix.multMatrixPnt(point);
        pPoints->setValue(point, 2);

        point = triIt.getPosition(1);
        matrix.multMatrixPnt(point);
        pPoints->setValue(point, 3);

        point = triIt.getPosition(2);
        matrix.multMatrixPnt(point);
        pPoints->setValue(point, 4);
    }
    else
    {
        pPoints->setValue(Pnt3f(0.0, 0.0, 0.0), 2);
        pPoints->setValue(Pnt3f(0.0, 0.0, 0.0), 3);
        pPoints->setValue(Pnt3f(0.0, 0.0, 0.0), 4);
    }
    endEditCP  (pPoints);
}

//
// GLUT callback functions
//

// redraw the window
void display(void)
{
    mgr->redraw();
}

// react to size changes
void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);

    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

// react to key presses
void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 'a':
        if(uiCurrentRay > 0)
            --uiCurrentRay;

        updateRayGeo();
        break;

    case 's':
        if(uiCurrentRay + 1 < uiNumRays)
            ++uiCurrentRay;

        updateRayGeo();
        break;

    case 'd':
        rayLength += 2.0;
        updateRayGeo();
        break;

    case 'c':
        rayLength -= 2.0;
        updateRayGeo();
        break;
    };

    glutPostRedisplay();
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    int winid = glutCreateWindow("OpenSG");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    return winid;
}
