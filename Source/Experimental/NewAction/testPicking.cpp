
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

// Rendering/Loading Stuff
#include <OSGGLUT.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSceneFileHandler.h>

// Misc
#include <OSGTime.h>

// STL
#include <vector>


OSG_USING_NAMESPACE

struct RayData
{
    bool    _bHit;
    NodePtr _pObj;
    Int32   _tri;
    Real32  _dist;

    Time    _time;
};

SimpleSceneManager  *mgr;
GeoPositions3fPtr    pPoints;

NodePtr              pScene;

std::vector<Line>    randomRays;  // random rays into the scene
std::vector<RayData> resultsNew;  // results of the NewAction/IntersectActor
std::vector<RayData> resultsOld;  // results of the IntersectAction

// Visualize the results
bool                 bDisplayNewResults = true;
UInt32               uiCurrentRay       = 0;
Real32               rayLength          = 10.0;

// Timing
Time     tStart;
Time     tStop;
Time     tNewActionTotal = 0.0;
Time     tOldActionTotal = 0.0;

// NewAction
NewAction       *pPrioAction;
IntersectActor  *pIActor;

// IntersectAction
IntersectAction *pIntAction;

// this will move to the IntersectActor
NewActionTypes::ResultE
enterDefault(NodeCorePtr pNodeCore, ActorBase *pActor);

// forward declaration for some helper functions
int  setupGLUT(int *argc, char *argv[]);
void buildScene(Real32 xSize, Real32 ySize, Real32 zSize, NodePtr pRoot,
                UInt32 depth                                             );
void createRays(Real32 xSize, Real32 ySize, Real32 zSize, UInt32 numRays,
                std::vector<Line> *pRays                                 );
void buildRayGeo(NodePtr pRayGeo);
void printResult(UInt32  uiIndex, std::vector<Line>    *pRays,
                                  std::vector<RayData> *pResNew,
                                  std::vector<RayData> *pResOld );


// **** MAIN ****

int main(int argc, char *argv[])
{
    // Init OpenSG - we do not need to be verbose here
    osgLogP->setLogLevel(LOG_NOTICE);

    osgInit(argc, argv);

    int winid = setupGLUT(&argc, argv);

    // create a GLUT window
    GLUTWindowPtr gwin = GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();

    osgLogP->setLogLevel(LOG_DEBUG);

    // load/build a scene
    NodePtr  pRoot      = Node ::create();
    GroupPtr pRootCore  = Group::create();

    NodePtr  pRayGeo    = Node ::create();
             pScene     = Node ::create();

    Real32   xSize      = 10.0;
    Real32   ySize      =  5.0;
    Real32   zSize      = 10.0;

    UInt32   numRays    = 1000;
    UInt32   uiProgress = numRays / 10;

    if(argc < 2)
    {
        FWARNING(("No file given, using a generated scene.\n"));

        GroupPtr pSceneCore = Group::create();

        beginEditCP(pScene, Node::CoreFieldId);
        pScene->setCore(pSceneCore);
        endEditCP  (pScene, Node::CoreFieldId);

        buildScene(xSize, ySize, zSize, pScene, 3);
    }
    else
    {
        pScene = SceneFileHandler::the().read(argv[1]);

    }

    if(argc >= 3)
    {
        numRays = TypeTraits<UInt32>::getFromString(argv[2]);
    }

    buildRayGeo(pRayGeo);

    beginEditCP(pRoot, Node::CoreFieldId | Node::ChildrenFieldId);
    pRoot->setCore (pRootCore);
    pRoot->addChild(pScene   );
    pRoot->addChild(pRayGeo  );
    endEditCP  (pRoot, Node::CoreFieldId | Node::ChildrenFieldId);

    // make sure bv are up to date
    pScene->updateVolume();

    xSize = pScene->getVolume().getMax()[0] - pScene->getVolume().getMin()[0];
    ySize = pScene->getVolume().getMax()[1] - pScene->getVolume().getMin()[1];
    zSize = pScene->getVolume().getMax()[2] - pScene->getVolume().getMin()[2];

    createRays(xSize, ySize, zSize, numRays, &randomRays);

    // this will move to the IntersectActor
    IntersectActor::regDefaultClassEnter(
        osgTypedFunctionFunctor2CPtr<NewActionTypes::ResultE,
                                     NodeCorePtr,
                                     ActorBase *             >(enterDefault));

    // create new action and intersect actor
    pPrioAction = PriorityAction  ::create();
    pIActor     = IntersectActor  ::create();

    pPrioAction->attachActor(pIActor);

    // create old action
    pIntAction  = IntersectAction ::create();

    //
    // New Action
    //

    SINFO << "Running New Action ";

    std::vector<Line>::iterator itRays  = randomRays.begin();
    std::vector<Line>::iterator endRays = randomRays.end  ();

    for(UInt32 i = 0; itRays != endRays; ++itRays, ++i)
    {
        tStart = getSystemTime();

        pIActor->setRay        (*itRays );
        pIActor->setMaxDistance(100000.0);
        pIActor->reset         (        );

        pPrioAction->apply(pScene);

        tStop = getSystemTime();

        tNewActionTotal += (tStop - tStart);

        RayData raydata;

        if(pIActor->getHit() == true)
        {
            raydata._bHit = true;
            raydata._pObj = pIActor->getHitObject       ();
            raydata._tri  = pIActor->getHitTriangleIndex();
            raydata._dist = pIActor->getHitDistance     ();

            raydata._time = (tStop - tStart);
        }
        else
        {
            raydata._bHit = false;
            raydata._pObj = NullFC;
            raydata._tri  = -1;
            raydata._dist =  0;

            raydata._time = (tStop - tStart);
        }

        resultsNew.push_back(raydata);

        if((i % uiProgress) == 0)
        {
            PINFO << ".";
        }
    }

    SINFO << "done." << endLog;

    //
    // Old Action
    //

    SINFO << "Running Old Action ";

    itRays  = randomRays.begin();
    endRays = randomRays.end  ();

    for(UInt32 i = 0; itRays != endRays; ++itRays, ++i)
    {
        tStart = getSystemTime();

        pIntAction->setLine(*itRays, 100000);
        pIntAction->apply  (pScene         );

        tStop = getSystemTime();

        tOldActionTotal += (tStop - tStart);

        RayData raydata;

        if(pIntAction->didHit() == true)
        {
            raydata._bHit = true;
            raydata._pObj = pIntAction->getHitObject  ();
            raydata._tri  = pIntAction->getHitTriangle();
            raydata._dist = pIntAction->getHitT       ();

            raydata._time = (tStop - tStart);
        }
        else
        {
            raydata._bHit = false;
            raydata._pObj = NullFC;
            raydata._tri  = -1;
            raydata._dist =  0;

            raydata._time = (tStop - tStart);
        }

        resultsOld.push_back(raydata);

        if((i % uiProgress) == 0)
        {
            PINFO << ".";
        }
    }

    SINFO << "done." << endLog;

    for(UInt32 i = 0; i < numRays; ++i)
    {
        printResult(i, &randomRays, &resultsNew, &resultsOld);
    }

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


// **** Helper functions ****

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
createRays(Real32 xSize, Real32 ySize, Real32 zSize, UInt32 numRays,
           std::vector<Line> *pRays                                 )
{
    SINFO << "Creating " << numRays << " rays...";

    pRays->clear  (           );
    pRays->reserve(numRays + 1);

    pRays->push_back(Line(Pnt3f(0.0, 0.0, 0.0), Vec3f(1.0, 0.0, 0.0)));

    for(UInt32 i = 0; i < numRays; ++i)
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

         pRays->push_back(Line(Pnt3f(xPos, yPos, zPos),
                               Vec3f(xDir, yDir, zDir) ));
    }

    PINFO << "done." << endLog;
}

void
buildRayGeo(NodePtr pRayGeo)
{
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
}

NewActionTypes::ResultE
enterDefault(NodeCorePtr pNodeCore, ActorBase *pActor)
{
    IntersectActor *pIA = dynamic_cast<IntersectActor *>(pActor);

    pIA->prioritizeChildren();

    return NewActionTypes::Continue;
}

void
updateRayGeo(void)
{
    Line    &ray     = randomRays[uiCurrentRay];
    RayData &raydata = bDisplayNewResults ? resultsNew[uiCurrentRay] :
                                            resultsOld[uiCurrentRay];

    Pnt3f startPnt = ray.getPosition();
    Pnt3f endPnt   = startPnt + (rayLength * ray.getDirection());

    beginEditCP(pPoints);
    pPoints->setValue(startPnt, 0);
    pPoints->setValue(endPnt,   1);

    if(raydata._bHit == true)
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

void
printResult(UInt32 uiIndex, std::vector<Line>    *pRays,
                            std::vector<RayData> *pResNew,
                            std::vector<RayData> *pResOld )
{
    std::cerr << "Line: (" << (*pRays)[uiIndex].getPosition()   << ") ("
                       << (*pRays)[uiIndex].getDirection()  << ") "
          << "\n   res New: " << (*pResNew)[uiIndex]._bHit << " "
                              << (*pResNew)[uiIndex]._pObj << " "
                              << (*pResNew)[uiIndex]._tri  << " "
                              << (*pResNew)[uiIndex]._dist << " "
          << "\n   res Old: " << (*pResOld)[uiIndex]._bHit << " "
                              << (*pResOld)[uiIndex]._pObj << " "
                              << (*pResOld)[uiIndex]._tri  << " "
                              << (*pResOld)[uiIndex]._dist << " "
                              << std::endl;
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
        if(uiCurrentRay + 1 < randomRays.size())
            ++uiCurrentRay;

        updateRayGeo();
        break;

    case 'o':
        bDisplayNewResults = !bDisplayNewResults;
        std::cerr << "Showing " << (bDisplayNewResults ? "new" : "old")
                  << " results." << std::endl;
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

    case ' ':
        randomRays[0] = mgr->calcViewRay(x, y);

        tStart = getSystemTime();

        pIActor->setRay        (randomRays[0]);
        pIActor->setMaxDistance(100000.0     );
        pIActor->reset         (             );

        pPrioAction->apply(pScene);

        tStop = getSystemTime();

        if(pIActor->getHit() == true)
        {
            resultsNew[0]._bHit = true;
            resultsNew[0]._pObj = pIActor->getHitObject       ();
            resultsNew[0]._tri  = pIActor->getHitTriangleIndex();
            resultsNew[0]._dist = pIActor->getHitDistance     ();

            resultsNew[0]._time = (tStop - tStart);
        }
        else
        {
            resultsNew[0]._bHit = false;
            resultsNew[0]._pObj = NullFC;
            resultsNew[0]._tri  = -1;
            resultsNew[0]._dist =  0;

            resultsNew[0]._time = (tStop - tStart);
        }

        tStart = getSystemTime();

        pIntAction->setLine(randomRays[0], 10000.0);
        pIntAction->apply  (pScene                );

        tStop  = getSystemTime();

        if(pIntAction->didHit() == true)
        {
            resultsOld[0]._bHit = true;
            resultsOld[0]._pObj = pIntAction->getHitObject  ();
            resultsOld[0]._tri  = pIntAction->getHitTriangle();
            resultsOld[0]._dist = pIntAction->getHitT       ();

            resultsOld[0]._time = (tStop - tStart);
        }
        else
        {
            resultsOld[0]._bHit = false;
            resultsOld[0]._pObj = NullFC;
            resultsOld[0]._tri  = -1;
            resultsOld[0]._dist =  0;

            resultsOld[0]._time = (tStop - tStart);
        }

        printResult(0, &randomRays, &resultsNew, &resultsOld);

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
