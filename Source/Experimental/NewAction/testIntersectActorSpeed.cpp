
// New Action Stuff
#include <OSGNewAction.h>
#include <OSGPriorityIterator.h>
#include <OSGIntersectActor.h>

// Old Action Stuff
#include <OSGAction.h>
#include <OSGIntersectAction.h>

#include <OSGGroup.h>
#include <OSGTransform.h>
#include <OSGSimpleGeometry.h>
#include <OSGTime.h>

#include <OSGGLUT.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>

#include <vector>

OSG_USING_NAMESPACE

struct ResultStore
{
    bool    _hit;
    NodePtr _obj;
    Int32   _tri;
    Real32  _dist;
};

SimpleSceneManager *mgr;

int setupGLUT(int *argc, char *argv[]);

NodePtr buildScene    (UInt32 xSize, UInt32 ySize, UInt32 zSize);
NodePtr buildDeepScene(UInt32 xSize, UInt32 ySize, UInt32 zSize);

void    createRays  (UInt32 numRays, UInt32 xSize, UInt32 ySize, UInt32 zSize,
                     std::vector<Line> &lines);
void    checkResults(std::vector<ResultStore> &newRes,
                     std::vector<ResultStore> &oldRes, UInt32 &uiErrorCount );

int main(int argc, char *argv[])
{
    osgLogP->setLogLevel(LOG_NOTICE);

    osgInit(argc, argv);

    int winid = setupGLUT(&argc, argv);

    GLUTWindowPtr gwin = GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();

    osgLogP->setLogLevel(LOG_DEBUG);

    UInt32 xSize   =   5;
    UInt32 ySize   =   5;
    UInt32 zSize   =  10;
    UInt32 numRays = 100;

    Time tStart;
    Time tStop;
    Time tNewTotal = 0.0;
    Time tOldTotal = 0.0;        

    UInt32 uiErrorCount = 0;

    // NewAction
    NewAction          *pAction    = NewAction         ::create();
    PriorityIterator   *pPIter     = PriorityIterator  ::create();
    IntersectActor     *pIntActor  = IntersectActor  ::create();

    // old Action
    IntersectAction    *pIntAction = IntersectAction ::create();

    pAction->setIterator(pPIter   );
    pAction->addActor   (pIntActor);

    IntersectActor::regDefaultClassEnter(
        osgTypedFunctionFunctor2CPtrRef<NewActionBase::ResultE,
                                        NodeCorePtr           ,
                                        ActorBase            *>
                                      (&IntersectActor::defaultFunctor));
    
//    NodePtr           scene = buildScene(xSize, ySize, zSize);
    NodePtr                  scene = buildDeepScene(xSize, ySize, zSize);

    std::vector<Line>        lines;
    std::vector<ResultStore> newResults;
    std::vector<ResultStore> oldResults;

    createRays(numRays, xSize, ySize, zSize, lines);
    
    newResults.reserve(numRays);
    oldResults.reserve(numRays);
      
    std::vector<Line>::iterator itLines  = lines.begin();
    std::vector<Line>::iterator endLines = lines.end  ();

    std::cerr << "\n RUNNING New Action... ";

    for(; itLines != endLines; ++itLines)
    {
        tStart = getSystemTime();

        pIntActor->setLine   (*itLines);
        pIntActor->setMaxDist(Inf     );

        pAction->apply(scene);

        tStop = getSystemTime();

        tNewTotal += (tStop - tStart);

        if(pIntActor->getHit() == true)
        {
            ResultStore res;

            res._hit  = true;
            res._obj  = pIntActor->getHitObject  ();
            res._tri  = pIntActor->getHitTriangle();
            res._dist = pIntActor->getHitDist    ();

            newResults.push_back(res);
        }
        else
        {
            ResultStore res;

            res._hit  = false;
            res._obj  = NullFC;
            res._tri  = -1;
            res._dist = 0.0;

            newResults.push_back(res);
        }                             
    }

    std::cerr << "done." << std::endl;

    itLines = lines.begin();

    std::cerr << "\n RUNNING Old Action... ";

    for(; itLines != endLines; ++itLines)
    {
        tStart = getSystemTime();
        
        pIntAction->setLine(*itLines);
        
        pIntAction->apply(scene);

        tStop = getSystemTime();

        tOldTotal += (tStop - tStart);

        if(pIntAction->didHit() == true)
        {
            ResultStore res;

            res._hit  = true;
            res._obj  = pIntAction->getHitObject  ();
            res._tri  = pIntAction->getHitTriangle();
            res._dist = pIntAction->getHitT       ();

            oldResults.push_back(res);
        }
        else
        {
            ResultStore res;

            res._hit  = false;
            res._obj  = NullFC;
            res._tri  = -1;
            res._dist = 0.0;

            oldResults.push_back(res);
        }
    }

    std::cerr << "done." << std::endl;


    std::cerr << "New Action total: " << tNewTotal << std::endl;
    std::cerr << "Old Action total: " << tOldTotal << std::endl;     

    checkResults(newResults, oldResults, uiErrorCount);

    std::cerr << "New Action total: " << tNewTotal    << std::endl;
    std::cerr << "Old Action total: " << tOldTotal    << std::endl;    
    std::cerr << "Missmatches: "      << uiErrorCount << std::endl;
    
    osgLogP->setLogLevel(LOG_NOTICE);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();

    // GLUT main loop
    glutMainLoop();

    return 0;
}


NodePtr
buildScene(UInt32 xSize, UInt32 ySize, UInt32 zSize)
{
    std::cerr << "Building scene... ";

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

                pGeo = makeBox(0.5, 0.5, 0.5, 1, 1, 1);

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

    std::cerr << "done." << std::endl;

    return pRoot;
}

NodePtr
buildDeepScene(UInt32 xSize, UInt32 ySize, UInt32 zSize)
{
    std::cerr << "Building deep scene... ";

    NodePtr  pRoot     = Node ::create();
    GroupPtr pRootCore = Group::create();

    beginEditCP(pRoot, Node::CoreFieldId | Node::ChildrenFieldId);
    {
        pRoot->setCore(pRootCore);
        
        for(UInt32 x = 0; x < xSize; ++x)
        {
            NodePtr      xTrans     = Node     ::create();
            TransformPtr xTransCore = Transform::create();

            NodePtr      xGeo       = makeBox(0.2, 0.2, 0.2, 1, 1, 1);

            beginEditCP(xTransCore, Transform::MatrixFieldId);
            {
                xTransCore->getMatrix().setTranslate(x + 1, 0, 0);
            }
            endEditCP(xTransCore, Transform::MatrixFieldId);

            beginEditCP(xTrans, Node::ChildrenFieldId |  Node::CoreFieldId);
            {
                xTrans->setCore (xTransCore);
                xTrans->addChild(xGeo      );

                for(UInt32 y = 0; y < ySize; ++y)
                {
                    NodePtr      yTrans     = Node     ::create();
                    TransformPtr yTransCore = Transform::create();

                    NodePtr      yGeo       = makeBox(0.4, 0.4, 0.4, 1, 1, 1);

                    beginEditCP(yTransCore, Transform::MatrixFieldId);
                    {
                        yTransCore->getMatrix().setTranslate(0, y + 1, 0);
                    }
                    endEditCP(yTransCore, Transform::MatrixFieldId);
                    
                    beginEditCP(yTrans, Node::ChildrenFieldId |  
                                        Node::CoreFieldId       );
                    {
                        yTrans->setCore (yTransCore);
                        yTrans->addChild(yGeo      );

                        for(UInt32 z = 0; z < zSize; ++z)
                        {
                            NodePtr      zTrans     = Node     ::create();
                            TransformPtr zTransCore = Transform::create();

                            NodePtr     zGeo = makeBox(0.6, 0.6, 0.6, 1, 1, 1);

                            beginEditCP(zTransCore, Transform::MatrixFieldId);
                            {
                                zTransCore->getMatrix().setTranslate(
                                    0, 0, z + 1);
                            }
                            endEditCP(zTransCore, Transform::MatrixFieldId);
                
                            beginEditCP(zTrans, Node::ChildrenFieldId |  
                                                Node::CoreFieldId   );
                            {
                                zTrans->setCore (zTransCore);
                                zTrans->addChild(zGeo      );
                            }
                            endEditCP(zTrans, Node::ChildrenFieldId |  
                                              Node::CoreFieldId       );

                            yTrans->addChild(zTrans);
                        }
                    }
                    endEditCP(yTrans, Node::ChildrenFieldId |  
                                      Node::CoreFieldId      );
                
                    xTrans->addChild(yTrans);
                }
            }
            endEditCP(xTrans, Node::ChildrenFieldId |  Node::CoreFieldId);

            pRoot->addChild(xTrans);
        }
    }
    endEditCP(pRoot, Node::ChildrenFieldId |  Node::CoreFieldId);
                
    std::cerr << "done." << std::endl;

    return pRoot;
}




void
createRays(UInt32 numRays, UInt32 xSize, UInt32 ySize, UInt32 zSize,
           std::vector<Line> &lines)
{
    std::cerr << "Creating rays... ";

    for(UInt32 i = 0; i < numRays; ++i)
    {
        Real32 xPos =(1.4 * xSize) * osgrand() - (0.2 * xSize);
        Real32 yPos =(1.4 * ySize) * osgrand() - (0.2 * ySize);
        Real32 zPos =(1.4 * zSize) * osgrand() - (0.2 * zSize);

        lines.push_back(Line(Pnt3f(xPos, yPos, zPos               ), 
                             Vec3f(osgrand(), osgrand(), osgrand()) ));
    }

    std::cerr << "done." << std::endl;
}

void
checkResults(std::vector<ResultStore> &newRes,
             std::vector<ResultStore> &oldRes, UInt32 &uiErrorCount )
{
    std::vector<ResultStore>::iterator itNew  = newRes.begin();
    std::vector<ResultStore>::iterator endNew = newRes.end  ();
    std::vector<ResultStore>::iterator itOld  = oldRes.begin();

    for(UInt32 i = 0; itNew != endNew; ++itNew, ++itOld, ++i)
    {
        std::cerr << i << " NEW: ";

        if(itNew->_hit == true)
        {
            std::cerr << "hit  obj " << itNew->_obj 
                      << " tri "     << itNew->_tri
                      << " dist "    << itNew->_dist;
        }
        else
        {
            std::cerr << "miss ";
        }

        std::cerr << " OLD: ";
        
        if(itOld->_hit == true)
        {
            std::cerr << "hit  obj " << itOld->_obj 
                      << " tri "     << itOld->_tri
                      << " dist "    << itOld->_dist;
        }
        else
        {
            std::cerr << "miss ";
        }

        std::cerr << std::endl;


        if(itNew->_hit != itOld->_hit)
        {
            std::cerr << "\n WARNING WARNING MISSMATCH\n" << std::endl;

            ++uiErrorCount;
        }
        else if(itNew->_obj != itOld->_obj)
        {
            std::cerr << "\n WARNING WARNING MISSMATCH\n" << std::endl;

            ++uiErrorCount;
        }
    }
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
//    glutKeyboardFunc(keyboard);

    return winid;
}
