
// Basic OpenSG
#include <OSGConfig.h>
#include <OSGBaseTypes.h>
#include <OSGLog.h>

// New Action Stuff
#include <OSGDepthFirstAction.h>
#include <OSGPriorityAction.h>

#include <OSGIntersectActor.h>
#include <OSGTriangleIterator.h>

// Old Action Stuff
#include <OSGAction.h>
#include <OSGIntersectAction.h>

// Scenegraph components
#include <OSGGroup.h>
#include <OSGTransform.h>
#include <OSGSimpleGeometry.h>
#include <OSGSimpleMaterial.h>
#include <OSGSimpleAttachments.h>

// Rendering Stuff
#include <OSGGLUT.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>

// Misc
#include <OSGTime.h>

// STL
#include <vector>

OSG_USING_NAMESPACE

struct RayData
{
    Line    _ray;
    bool    _hit;
    NodePtr _pObj;
    Int32   _tri;
    Real32  _dist;
};

SimpleSceneManager   *mgr;
GeoPositions3fPtr     pPoints;
std::vector<RayData>  testRaysNew;
std::vector<RayData>  testRaysOld;
UInt32                uiCurrentRay = 0;
Real32                rayLength    = 10.0;

UInt32                uiVisitedNodes;
std::vector<UInt32>   visitedNodesHistory;

int     setupGLUT(int *argc, char *argv[]);

void buildScene(Real32 xSize, Real32 ySize, Real32 zSize, NodePtr pRoot,
                UInt32 depth                                            );

void createRays(Real32 xSize, Real32 ySize, Real32 zSize,
                UInt32 uiNumRays,
                std::vector<RayData> *newRays,
                std::vector<RayData> *oldRays            );

// Intersect callbacks

#if 0 // Moved these to the respective cores.
NewActionTypes::ResultE
enterTransform(NodeCorePtr pNodeCore, ActorBase *pActor);

NewActionTypes::ResultE
leaveTransform(NodeCorePtr pNodeCore, ActorBase *pActor);

NewActionTypes::ResultE
enterGeometry(NodeCorePtr pNodeCore, ActorBase *pActor);
#endif

NewActionTypes::ResultE
enterDefault(NodeCorePtr pNodeCore, ActorBase *pActor);

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
    NodePtr  pScene     = Node ::create();
    GroupPtr pSceneCore = Group::create();

    UInt32   uiDepth    = 3;
    UInt32   uiNumRays  = 2000;
    UInt32   uiProgress = uiNumRays / 10;

    Real32   xSize      = 10.0;
    Real32   ySize      = 10.0;
    Real32   zSize      = 15.0;

    Time     tStart;
    Time     tStop;
    Time     tNewActionTotal = 0.0;
    Time     tOldActionTotal = 0.0;

    beginEditCP(pRoot, Node::CoreFieldId | Node::ChildrenFieldId);
    pRoot->setCore (pRootCore);
    pRoot->addChild(pScene   );
    pRoot->addChild(pRayGeo  );
    endEditCP  (pRoot, Node::CoreFieldId | Node::ChildrenFieldId);

    beginEditCP(pScene, Node::CoreFieldId);
    pScene->setCore(pSceneCore);
    endEditCP  (pScene, Node::CoreFieldId);

    buildScene(xSize, ySize, zSize, pScene,     uiDepth                  );
    createRays(xSize, ySize, zSize, uiNumRays, &testRaysNew, &testRaysOld);

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

#if 0 // Moved these to the respective cores.
    // NewAction setup
    IntersectActor::regClassEnter(
        osgTypedFunctionFunctor2CPtr<NewActionTypes::ResultE,
                                     NodeCorePtr,
                                     ActorBase *             >(enterTransform),
        Transform::getClassType());

    IntersectActor::regClassLeave(
        osgTypedFunctionFunctor2CPtr<NewActionTypes::ResultE,
                                     NodeCorePtr,
                                     ActorBase *             >(leaveTransform),
        Transform::getClassType());

    IntersectActor::regClassEnter(
        osgTypedFunctionFunctor2CPtr<NewActionTypes::ResultE,
                                     NodeCorePtr,
                                     ActorBase *             >(enterGeometry),
        Geometry::getClassType());
#endif

    IntersectActor::regDefaultClassEnter(
        osgTypedFunctionFunctor2CPtr<NewActionTypes::ResultE,
                                     NodeCorePtr,
                                     ActorBase *             >(enterDefault));


    NewAction      *pDFAction = DepthFirstAction::create();
    NewAction      *pPAction  = PriorityAction  ::create();
    IntersectActor *pIActor   = IntersectActor  ::create();

    pIActor->setApplyEnter(true);
    pIActor->setApplyLeave(true);

    //pDFAction->attachActor(pIActor);
    pPAction->attachActor(pIActor);

    // create old action
    IntersectAction *pIntAction = IntersectAction ::create();

    // make sure bv are up to date
    pScene->updateVolume();

    //
    // New Action
    //

    SINFO << "Running New Action ";

    std::vector<RayData>::iterator itTestRays  = testRaysNew.begin();
    std::vector<RayData>::iterator endTestRays = testRaysNew.end  ();

    for(UInt32 i = 0; itTestRays != endTestRays; ++itTestRays, ++i)
    {
        uiVisitedNodes = 0;

        tStart = getSystemTime();

        pIActor->setRay        (itTestRays->_ray);
        pIActor->setMaxDistance(100000.0        );
        pIActor->reset         (                );

        //pDFAction->apply(pScene);
        pPAction->apply(pScene);

        tStop = getSystemTime();

        tNewActionTotal += (tStop - tStart);

        if(pIActor->getHit() == true)
        {
            itTestRays->_hit  = true;
            itTestRays->_pObj = pIActor->getHitObject       ();
            itTestRays->_tri  = pIActor->getHitTriangleIndex();
            itTestRays->_dist = pIActor->getHitDistance     ();
        }
        else
        {
            itTestRays->_hit  = false;
            itTestRays->_pObj = NullFC;
            itTestRays->_tri  = -1;
            itTestRays->_dist =  0;
        }

        visitedNodesHistory.push_back(uiVisitedNodes);

        if((i % uiProgress) == 0)
        {
            PINFO << ".";
        }
    }

    SINFO << "done." << endLog;

    itTestRays  = testRaysNew.begin();
    endTestRays = testRaysNew.end  ();

    SINFO << "\n"                            << endLog;
    SINFO << " <<-- New Action Results -->>" << endLog;

    for(UInt32 i = 0; itTestRays != endTestRays; ++itTestRays, ++i)
    {
        if(itTestRays->_hit == true)
        {
            SINFO << "HIT  (" << i                 << ") "
                  << "vis Nodes: " << visitedNodesHistory[i] << " "
                  << "dist: " << itTestRays->_dist << "  "
                  << "tri: "  << itTestRays->_tri  << " NAME: ";

            if(getName(itTestRays->_pObj->getCore()) != NULL)
                PINFO << getName(itTestRays->_pObj->getCore());

            PINFO << endLog;
        }
        else
        {
            SINFO << "MISS (" << i << ")"
                  << " vis Nodes " << visitedNodesHistory[i] << endLog;
        }
    }

    //
    // Old Action
    //

    SINFO << "Running Old Action ";

    itTestRays  = testRaysOld.begin();
    endTestRays = testRaysOld.end  ();

    for(UInt32 i = 0; itTestRays != endTestRays; ++itTestRays, ++i)
    {
        tStart = getSystemTime();

        pIntAction->setLine(itTestRays->_ray, 100000);

        pIntAction->apply(pScene);

        tStop = getSystemTime();

        tOldActionTotal += (tStop - tStart);

        if(pIntAction->didHit() == true)
        {
            itTestRays->_hit  = true;
            itTestRays->_pObj = pIntAction->getHitObject  ();
            itTestRays->_tri  = pIntAction->getHitTriangle();
            itTestRays->_dist = pIntAction->getHitT       ();
        }
        else
        {
            itTestRays->_hit  = false;
            itTestRays->_pObj = NullFC;
            itTestRays->_tri  = -1;
            itTestRays->_dist =  0;
        }

        if((i % uiProgress) == 0)
        {
            PINFO << ".";
        }
    }

    SINFO << "done." << endLog;

    itTestRays  = testRaysOld.begin();
    endTestRays = testRaysOld.end  ();

    SINFO << "\n"                            << endLog;
    SINFO << " <<-- Old Action Results -->>" << endLog;

    for(UInt32 i = 0; itTestRays != endTestRays; ++itTestRays, ++i)
    {
        if(itTestRays->_hit == true)
        {
            SINFO << "HIT  (" << i                 << ") "
                  << "dist: " << itTestRays->_dist << "  "
                  << "tri: "  << itTestRays->_tri  << " NAME: ";

            if(getName(itTestRays->_pObj->getCore()) != NULL)
                PINFO << getName(itTestRays->_pObj->getCore());

            PINFO << endLog;
        }
        else
        {
            SINFO << "MISS (" << i << ")" << endLog;
        }
    }

    SINFO << "Total Time New: " << tNewActionTotal << endLog;
    SINFO << "Total Time Old: " << tOldActionTotal << endLog;

    osgLogP->setLogLevel(LOG_NOTICE);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (pRoot);

    // show the whole scene
    mgr->showAll();

    // GLUT main loop
    glutMainLoop();

    return 0;
}


void buildScene(Real32 xSize, Real32 ySize, Real32 zSize, NodePtr pRoot,
                UInt32 depth                                            )
{
    SINFO << "buildScene( " << xSize << ", " << ySize << ", " << zSize
          << ", "
          << ((getName(pRoot->getCore()) != NULL) ?
                        getName(pRoot->getCore()) :
                        "(unnamed)")
          << ", " << depth << ")" << endLog;

    NodePtr     pGroup     = Node ::create();
    GroupPtr    pGroupCore = Group::create();
    std::string strGroupName;
    Pnt3f       geoPos[12];

    geoPos[ 0][0] =  0.0         + 0.25 * xSize * (osgrand() - 0.5);
    geoPos[ 0][1] = -0.5 * ySize + 0.25 * ySize * (osgrand() - 0.5);
    geoPos[ 0][2] = -0.5 * zSize + 0.25 * zSize * (osgrand() - 0.5);

    geoPos[ 1][0] =  0.5 * xSize + 0.25 * xSize * (osgrand() - 0.5);
    geoPos[ 1][1] =  0.0         + 0.25 * ySize * (osgrand() - 0.5);
    geoPos[ 1][2] = -0.5 * zSize + 0.25 * zSize * (osgrand() - 0.5);

    geoPos[ 2][0] =  0.0         + 0.25 * xSize * (osgrand() - 0.5);
    geoPos[ 2][1] = +0.5 * ySize + 0.25 * ySize * (osgrand() - 0.5);
    geoPos[ 2][2] = -0.5 * zSize + 0.25 * zSize * (osgrand() - 0.5);

    geoPos[ 3][0] = -0.5 * xSize + 0.25 * xSize * (osgrand() - 0.5);
    geoPos[ 3][1] =  0.0         + 0.25 * ySize * (osgrand() - 0.5);
    geoPos[ 3][2] = -0.5 * zSize + 0.25 * zSize * (osgrand() - 0.5);

    geoPos[ 4][0] = -0.5 * xSize + 0.25 * xSize * (osgrand() - 0.5);
    geoPos[ 4][1] = -0.5 * ySize + 0.25 * ySize * (osgrand() - 0.5);
    geoPos[ 4][2] =  0.0         + 0.25 * zSize * (osgrand() - 0.5);

    geoPos[ 5][0] =  0.5 * xSize + 0.25 * xSize * (osgrand() - 0.5);
    geoPos[ 5][1] = -0.5 * ySize + 0.25 * ySize * (osgrand() - 0.5);
    geoPos[ 5][2] =  0.0         + 0.25 * zSize * (osgrand() - 0.5);

    geoPos[ 6][0] =  0.5 * xSize + 0.25 * xSize * (osgrand() - 0.5);
    geoPos[ 6][1] =  0.5 * ySize + 0.25 * ySize * (osgrand() - 0.5);
    geoPos[ 6][2] =  0.0         + 0.25 * zSize * (osgrand() - 0.5);

    geoPos[ 7][0] = -0.5 * xSize + 0.25 * xSize * (osgrand() - 0.5);
    geoPos[ 7][1] =  0.5 * ySize + 0.25 * ySize * (osgrand() - 0.5);
    geoPos[ 7][2] =  0.0         + 0.25 * zSize * (osgrand() - 0.5);

    geoPos[ 8][0] =  0.0         + 0.25 * xSize * (osgrand() - 0.5);
    geoPos[ 8][1] = -0.5 * ySize + 0.25 * ySize * (osgrand() - 0.5);
    geoPos[ 8][2] =  0.5 * zSize + 0.25 * zSize * (osgrand() - 0.5);

    geoPos[ 9][0] =  0.5 * xSize + 0.25 * xSize * (osgrand() - 0.5);
    geoPos[ 9][1] =  0.0         + 0.25 * ySize * (osgrand() - 0.5);
    geoPos[ 9][2] =  0.5 * zSize + 0.25 * zSize * (osgrand() - 0.5);

    geoPos[10][0] =  0.0         + 0.25 * xSize * (osgrand() - 0.5);
    geoPos[10][1] = +0.5 * ySize + 0.25 * ySize * (osgrand() - 0.5);
    geoPos[10][2] =  0.5 * zSize + 0.25 * zSize * (osgrand() - 0.5);

    geoPos[11][0] = -0.5 * xSize + 0.25 * xSize * (osgrand() - 0.5);
    geoPos[11][1] =  0.0         + 0.25 * ySize * (osgrand() - 0.5);
    geoPos[11][2] =  0.5 * zSize + 0.25 * zSize * (osgrand() - 0.5);

    if(getName(pRoot->getCore()) != NULL)
    {
        strGroupName += getName(pRoot->getCore());
    }

    strGroupName += " -> Group ";

    beginEditCP(pGroup, Node::CoreFieldId | Node::ChildrenFieldId);
    pGroup->setCore(pGroupCore);

    for(UInt32 i = 0; i < 12; ++i)
    {
        NodePtr      pTrans     = Node     ::create();
        TransformPtr pTransCore = Transform::create();
        NodePtr      pGeo       = makeBox(xSize/10.0, ySize/10.0, zSize/10.0,
                                          1,          1,          1          );

        std::string  strTransName("");
        std::string  strGeoName  ("");

        beginEditCP(pTransCore, Transform::MatrixFieldId);
        pTransCore->getMatrix().setTranslate(geoPos[i]);
        endEditCP  (pTransCore, Transform::MatrixFieldId);

        strTransName += strGroupName;
        strTransName += " -> Geo-Trans <";
        strTransName += TypeTraits<UInt32>::putToString(i);
        strTransName += "> ";
        setName(pTransCore, strTransName);

        beginEditCP(pTrans, Node::CoreFieldId | Node::ChildrenFieldId);
        pTrans->setCore (pTransCore);
        pTrans->addChild(pGeo      );
        endEditCP  (pTrans, Node::CoreFieldId | Node::ChildrenFieldId);

        strGeoName += strTransName;
        strGeoName += " -> Geo <";
        strGeoName += TypeTraits<UInt32>::putToString(i);
        strGeoName += "> ";
        setName(pGeo->getCore(), strGeoName);

        pGroup->addChild(pTrans);
    }
    endEditCP(pGroup, Node::CoreFieldId | Node::ChildrenFieldId);

    beginEditCP(pRoot, Node::ChildrenFieldId);
    pRoot->addChild(pGroup);
    endEditCP  (pRoot, Node::ChildrenFieldId);

    if(depth > 0)
    {
        Pnt3f center[8];

        center[0][0] =  0.25 * xSize;
        center[0][1] =  0.25 * ySize;
        center[0][2] =  0.25 * zSize;

        center[1][0] = -0.25 * xSize;
        center[1][1] =  0.25 * ySize;
        center[1][2] =  0.25 * zSize;

        center[2][0] = -0.25 * xSize;
        center[2][1] =  0.25 * ySize;
        center[2][2] = -0.25 * zSize;

        center[3][0] =  0.25 * xSize;
        center[3][1] =  0.25 * ySize;
        center[3][2] = -0.25 * zSize;

        center[4][0] =  0.25 * xSize;
        center[4][1] = -0.25 * ySize;
        center[4][2] =  0.25 * zSize;

        center[5][0] = -0.25 * xSize;
        center[5][1] = -0.25 * ySize;
        center[5][2] =  0.25 * zSize;

        center[6][0] = -0.25 * xSize;
        center[6][1] = -0.25 * ySize;
        center[6][2] = -0.25 * zSize;

        center[7][0] =  0.25 * xSize;
        center[7][1] = -0.25 * ySize;
        center[7][2] = -0.25 * zSize;

        for(UInt32 i = 0; i < 8; ++i)
        {
            NodePtr      pTrans     = Node     ::create();
            TransformPtr pTransCore = Transform::create();
            std::string  strTransName("");

            if(getName(pRoot->getCore()) != NULL)
            {
                strTransName += getName(pRoot->getCore());
            }

            strTransName += " -> Subtree-Trans <";
            strTransName += TypeTraits<UInt32>::putToString(i);
            strTransName += "> ";
            setName(pTransCore, strTransName);

            beginEditCP(pTransCore, Transform::MatrixFieldId);
            pTransCore->getMatrix().setTranslate(center[i]);
            endEditCP  (pTransCore, Transform::MatrixFieldId);

            beginEditCP(pTrans, Node::CoreFieldId);
            pTrans->setCore(pTransCore);
            endEditCP  (pTrans, Node::CoreFieldId);

            buildScene(0.5 * xSize, 0.5 * ySize, 0.5 * zSize,
                       pTrans, depth - 1                     );

            beginEditCP(pRoot, Node::ChildrenFieldId);
            pRoot->addChild(pTrans);
            endEditCP  (pRoot, Node::ChildrenFieldId);
        }
    }
}

void
createRays(Real32 xSize, Real32 ySize, Real32 zSize, UInt32 uiNumRays,
           std::vector<RayData> *newRays, std::vector<RayData> *oldRays)
{
    SINFO << "Creating " << uiNumRays << " rays...";

    newRays->clear  (         );
    newRays->reserve(uiNumRays);
    oldRays->clear  (         );
    oldRays->reserve(uiNumRays);

    for(UInt32 i = 0; i < uiNumRays; ++i)
    {
        Real32 xPos = (osgrand() - 0.5) * xSize * 2.5;
        Real32 yPos = (osgrand() - 0.5) * ySize * 2.5;
        Real32 zPos = (osgrand() - 0.5) * zSize * 2.5;

        Real32 xDir = (osgrand() - 0.5);
        Real32 yDir = (osgrand() - 0.5);
        Real32 zDir = (osgrand() - 0.5);

        if((xPos * xDir) > 0)
            xDir *= -1.0;

        if((yPos * yDir) > 0)
            yDir *= -1.0;

        if((zPos * zDir) > 0)
            zDir *= -1.0;

        RayData raydata;

        raydata._ray  = Line(Pnt3f(xPos, yPos, zPos), Vec3f(xDir, yDir, zDir));
        raydata._hit  = false;
        raydata._pObj = NullFC;
        raydata._tri  = -1;
        raydata._dist = 0;

        newRays->push_back(raydata);
        oldRays->push_back(raydata);
    }

    PINFO << "done." << endLog;
}

NewActionTypes::ResultE
enterTransform(NodeCorePtr pNodeCore, ActorBase *pActor)
{
    IntersectActor *pIA    = dynamic_cast<IntersectActor *>(pActor);
    TransformPtr    pTrans = TransformPtr::dcast(pNodeCore);

    Matrix          matrix = pTrans->getMatrix  ();
    Line            transLine;
    Pnt3f           pos;
    Vec3f           dir;

    matrix.invert();

    matrix.multFullMatrixPnt(pIA->getRay().getPosition (), pos);
    matrix.multMatrixVec    (pIA->getRay().getDirection(), dir);

    transLine.setValue(pos, dir);

    pIA->beginEditState();
    {
        pIA->setRay        (transLine                           );
        pIA->setScaleFactor(pIA->getScaleFactor() / dir.length());
    }
    pIA->endEditState  ();

    pIA->prioritizeChildren();

    // DEBUG
    ++uiVisitedNodes;

    return NewActionTypes::Continue;
}

NewActionTypes::ResultE
leaveTransform(NodeCorePtr pNodeCore, ActorBase *pActor)
{
    IntersectActor *pIA    = dynamic_cast<IntersectActor *>(pActor);
    TransformPtr    pTrans = TransformPtr::dcast(pNodeCore);

    const Matrix   &matrix = pTrans->getMatrix();
          Pnt3f     pos;
          Vec3f     dir;

    matrix.multFullMatrixPnt(pIA->getRay().getPosition (), pos);
    matrix.multMatrixVec    (pIA->getRay().getDirection(), dir);

    pIA->beginEditState();
    {
        pIA->setRay        (Line(pos, dir)                      );
        pIA->setScaleFactor(pIA->getScaleFactor() / dir.length());
    }
    pIA->endEditState  ();

    return NewActionTypes::Continue;
}

NewActionTypes::ResultE
enterGeometry(NodeCorePtr pNodeCore, ActorBase *pActor)
{
    IntersectActor   *pIA         = dynamic_cast<IntersectActor *>(pActor);
    GeometryPtr       pGeo        = GeometryPtr::dcast(pNodeCore);
    Real32            scaleFactor = pIA->getScaleFactor();

    TriangleIterator  itTris      = pGeo->beginTriangles();
    TriangleIterator  endTris     = pGeo->endTriangles  ();

    Real32            hitDist;
    Vec3f             hitNormal;

    for(; itTris != endTris; ++itTris)
    {
        if(pIA->getRay().intersect(itTris.getPosition(0),
                                   itTris.getPosition(1),
                                   itTris.getPosition(2),
                                   hitDist,                &hitNormal) == true)
        {
            pIA->setHit(hitDist * scaleFactor, pIA->getCurrNode(),
                        itTris.getIndex(),     hitNormal          );
        }
    }

    pIA->prioritizeChildren();

    // DEBUG
    ++uiVisitedNodes;

    return NewActionTypes::Continue;
}

NewActionTypes::ResultE
enterDefault(NodeCorePtr pNodeCore, ActorBase *pActor)
{
    IntersectActor *pIA = dynamic_cast<IntersectActor *>(pActor);

    pIA->prioritizeChildren();

    // DEBUG
    ++uiVisitedNodes;

    return NewActionTypes::Continue;
}

void
updateRayGeo(void)
{
    RayData &raydata = testRaysNew[uiCurrentRay];

    Pnt3f startPnt = raydata._ray.getPosition();
    Pnt3f endPnt   = startPnt + (rayLength * raydata._ray.getDirection());

    beginEditCP(pPoints);
    pPoints->setValue(startPnt, 0);
    pPoints->setValue(endPnt,   1);

    if(raydata._hit == true)
    {
        TriangleIterator triIt(raydata._pObj);
        Matrix           matrix;
        Pnt3f            point;

        triIt.seek(raydata._tri);
        raydata._pObj->getToWorld(matrix);

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
        if(uiCurrentRay + 1 < testRaysNew.size())
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
