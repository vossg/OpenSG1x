
#include <OSGLog.h>

#include "OSGPrintNameActor.h"

#include "OSGNewAction.h"
#include "OSGPriorityIterator.h"

#include <OSGNodePtr.h>
#include <OSGGroup.h>
#include <OSGSimpleAttachments.h>
#include <OSGBaseTypes.h>

#include <OSGTime.h>

#include <string>


OSG_USING_NAMESPACE

NodePtr buildTestTreeWide (UInt32 uiNumChildren, std::string strPre = "");
NodePtr buildTestTreeDeep (UInt32 uiNumChildren, std::string strPre = "");
NodePtr buildTestTreeMixed(UInt32 uiNumChildren, std::string strPre = "");

int main(int argc, char *argv[])
{
    osgLogP->setLogLevel(LOG_NOTICE);

    osgInit(argc, argv);

    osgLogP->setLogLevel(LOG_DEBUG);

    bool              bRunSmallWide  = false;
    bool              bRunLargeWide  = false;
    bool              bRunSmallDeep  = false;
    bool              bRunLargeDeep  = false;
    bool              bRunSmallMixed = false;
    bool              bRunLargeMixed = false;

    Time              tStart;
    Time              tStop;

    NodePtr           pRootSmallW    = NullFC;
    NodePtr           pRootLargeW    = NullFC;

    NodePtr           pRootSmallD    = NullFC;
    NodePtr           pRootLargeD    = NullFC;

    NodePtr           pRootSmallM    = NullFC;
    NodePtr           pRootLargeM    = NullFC;

    NewAction        *pNewAct        = NewAction       ::create();
    PriorityIterator *pPIter         = PriorityIterator::create();
    PrintNameActor   *pActor         = PrintNameActor  ::create();
    

    if(argc > 1)
    {
        std::string strArgv(argv[1]);

        if(strArgv.find('1') != std::string::npos)
        {
            pRootSmallW   = buildTestTreeWide(   10);
            bRunSmallWide = true;
        }
        
        if(strArgv.find('2') != std::string::npos)
        {
            pRootLargeW   = buildTestTreeWide(10000);
            bRunLargeWide = true;
        }

        if(strArgv.find('3') != std::string::npos)
        {
            pRootSmallD   = buildTestTreeDeep(   10);
            bRunSmallDeep = true;
        }

        if(strArgv.find('4') != std::string::npos)
        {
            pRootLargeD   = buildTestTreeDeep(10000);
            bRunLargeDeep = true;
        }

        if(strArgv.find('5') != std::string::npos)
        {
            pRootSmallM    = buildTestTreeMixed(   50);
            bRunSmallMixed = true;
        }
        
        if(strArgv.find('6') != std::string::npos)
        {
            pRootLargeM    = buildTestTreeMixed(1000);
            bRunLargeMixed = true;
        }
    }
    else
    {
        FNOTICE(("USAGE %s {1|2|3|4|5|6}\n", argv[0]));
        FNOTICE(("    1 - run small wide tree  (root    10 children).\n"));
        FNOTICE(("    2 - run large wide tree  (root 10000 children).\n"));
        FNOTICE(("    3 - run small deep tree  (        10 nodes   ).\n"));
        FNOTICE(("    4 - run large deep tree  (     10000 nodes   ).\n"));
        FNOTICE(("    5 - run small mixed tree (       ~50 nodes   ).\n"));
        FNOTICE(("    6 - run large mixed tree (     ~1000 nodes   ).\n"));

        pRootSmallW    = buildTestTreeWide (   10);
        pRootLargeW    = buildTestTreeWide (10000);
        pRootSmallD    = buildTestTreeDeep (   10);
        pRootLargeD    = buildTestTreeDeep (10000);
        pRootSmallM    = buildTestTreeMixed(   5);
        pRootLargeM    = buildTestTreeMixed( 1000);

        bRunSmallWide  = true;
        bRunLargeWide  = true;
        bRunSmallDeep  = true;
        bRunLargeDeep  = true;
        bRunSmallMixed = true;
        bRunLargeMixed = true;
    }

    pNewAct->addActor   (pActor);
    pNewAct->setIterator(pPIter);

    if(bRunSmallWide)
    {
        FLOG(("\n Running action on small tree (wide, 10).\n"));

        tStart = getSystemTime();

        pNewAct->apply(pRootSmallW);

        tStop = getSystemTime();

        FLOG((" tStart: %g  tStop: %g  tDelta: %g\n", 
              tStart, tStop, tStop - tStart        ));
    }

    if(bRunLargeWide)
    {

        FLOG(("\n Running action on large tree (wide, 10000).\n"));

        tStart = getSystemTime();

        pNewAct->apply(pRootLargeW);

        tStop = getSystemTime();

        FLOG((" tStart: %g  tStop: %g  tDelta: %g\n", 
              tStart, tStop, tStop - tStart        ));
    }

    if(bRunSmallDeep)
    {
        FLOG(("\n Running action on small tree (deep, 10).\n"));
    
        tStart = getSystemTime();

        pNewAct->apply(pRootSmallD);

        tStop = getSystemTime();

        FLOG((" tStart: %g  tStop: %g  tDelta: %g\n", 
              tStart, tStop, tStop - tStart        ));
    }

    if(bRunLargeDeep)
    {
        FLOG(("\n Running action on large tree (deep, 10000).\n"));

        tStart = getSystemTime();

        pNewAct->apply(pRootLargeD);

        tStop = getSystemTime();

        FLOG((" tStart: %g  tStop: %g  tDelta: %g\n", 
              tStart, tStop, tStop - tStart        ));
    }

    if(bRunSmallMixed)
    {
        FLOG(("\n Running action on small tree (mixed, ~50).\n"));

        tStart = getSystemTime();

        pNewAct->apply(pRootSmallM);

        tStop = getSystemTime();

        FLOG((" tStart: %g  tStop: %g  tDelta: %g\n", 
              tStart, tStop, tStop - tStart        ));
    }
    
    if(bRunLargeMixed)
    {
        FLOG(("\n Running acion an large tree (mixed, ~1000).\n"));

        tStart = getSystemTime();

        pNewAct->apply(pRootLargeM);

        tStop = getSystemTime();

        FLOG((" tStart: %g  tStop: %g  tDelta: %g\n", 
              tStart, tStop, tStop - tStart        ));
    }
        
    return 0;
}


NodePtr
buildTestTreeWide(UInt32 uiNumChildren, std::string strPre)
{
    NodePtr  root = Node ::create();
    GroupPtr grp  = Group::create();

    beginEditCP(root);
    {
        root->setCore(grp);

        for(UInt32 i=0; i < uiNumChildren; ++i)
        {
            NodePtr  pChild = Node ::create();
            GroupPtr pCore  = Group::create();

            beginEditCP(pChild);
            {
                pChild->setCore(pCore);
            }
            endEditCP(pChild);

            setName(pCore, 
                    strPre + std::string("w") + 
                    TypeTraits<UInt32>::putToString(i)
                   );

            root->addChild(pChild);
        }
    }
    endEditCP(root);

    setName(grp, strPre + std::string("w_root"));

    return root;
}

NodePtr
buildTestTreeDeep(UInt32 uiNumChildren, std::string strPre)
{
    NodePtr  pNode = Node ::create();
    GroupPtr pCore = Group::create();

    strPre.append(std::string("d") + 
                  TypeTraits<UInt32>::putToString(uiNumChildren));

    setName(pCore, strPre);

    if(uiNumChildren == 1)
    {
        beginEditCP(pNode);
        {
            pNode->setCore(pCore);
        }
        endEditCP(pNode);
    }
    else
    {
        beginEditCP(pNode);
        {
            pNode->setCore (pCore);
            pNode->addChild(buildTestTreeDeep(--uiNumChildren, strPre));
        }
        endEditCP(pNode);
    }

    return pNode;
}
    
NodePtr
buildTestTreeMixed(UInt32 uiNumChildren, std::string strPre)
{
    UInt32   uiSubSize = uiNumChildren / 10;

    NodePtr  pRoot     = Node ::create();
    GroupPtr pCore     = Group::create();

    beginEditCP(pRoot);
    {
        pRoot->setCore(pCore);
        
        for(UInt32 i = 0; i < uiSubSize; ++i)
        {
            if((i % 2) == 0)
            {
                pRoot->addChild(
                    buildTestTreeWide(uiSubSize, 
                                      std::string("W") +
                                      TypeTraits<UInt32>::putToString(i)));
            }
            else
            {
                NodePtr pDeepTop = 
                    buildTestTreeDeep(uiSubSize,
                                      std::string("D") + 
                                      TypeTraits<UInt32>::putToString(i));
                NodePtr pDeepBot = pDeepTop;

                while(pDeepBot->getNChildren() > 0)
                {
                    pDeepBot = pDeepBot->getChild(0);
                }

                beginEditCP(pDeepBot);
                {
                    pDeepBot->addChild(
                        buildTestTreeWide(uiSubSize, 
                                          strPre + 
                                          getName(pDeepBot->getCore())));
                }
                endEditCP(pDeepBot);

                pRoot->addChild(pDeepTop);
            }
        }
    }
    endEditCP(pRoot);

    return pRoot;
}
