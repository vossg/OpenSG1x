
#include "OSGQSceneGraphViewFunctions.h"

#include "OSGQSceneGraphView_qt.h"

#include <OSGLog.h>
#include <OSGThread.h>

#include <qapplication.h>

OSG_BEGIN_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGQSceneGraphViewFunctions.cpp,v 1.1 2003/05/07 14:03:40 neumannc Exp $";
    static Char8 cvsid_hpp[] = OSGQSCENEGRAPHVIEWFUNCTIONS_HEADER_CVSID;
//    static Char8 cvsid_inl[] = OSGQSCENEGRAPHVIEWFUNCTIONS_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

void sceneGraphViewThreadFunc(void *pThreadArg)
{
    NodePtr        pRootNode = *(reinterpret_cast<NodePtr *>(pThreadArg));

    int            argc      = 0;
    char         **argv      = NULL;
    bool           bOwnQTApp = false;
    QApplication  *pOwnQTApp = NULL;

    if(qApp == NULL)
    {
        bOwnQTApp = true;
        pOwnQTApp = new QApplication(argc, argv);
    }

    QSceneGraphView *pSGView = new QSceneGraphView(NULL, "pSGView");

    pSGView->setRoot(pRootNode);
    pSGView->show   (         );

    if(bOwnQTApp)
        pOwnQTApp->exec();
}

bool startSceneGraphViewThread(NodePtr &pRootNode)
{
    Thread *pSGVThread = Thread::find("osg::SceneGraphViewThread");

    if(pSGVThread != NULL)
    {
        FWARNING(("startSceneGraphViewThread: thread already running.\n"));

        return false;
    }

    pSGVThread = Thread::get("osg::SceneGraphViewThread");
    
    if(pSGVThread == NULL)
    {
        FFATAL(("startSceneGraphViewThread: could not create thread."));
        
        return false;
    }
    
    return pSGVThread->runFunction(&sceneGraphViewThreadFunc, 
                                    0, (void *) &pRootNode   );
}

bool stopSceneGraphViewThread(void)
{
    Thread *pSGVThread = Thread::find("osg::SceneGraphViewThread");

    if(pSGVThread == NULL)
    {
        FFATAL(("stopSceneGraphViewThread: could not find thread."));

        return false;
    }

    qApp->quit();

//    pSGVThread->kill();

    return true;
}

OSG_END_NAMESPACE
